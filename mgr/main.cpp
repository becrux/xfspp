/* mgr/main.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <memory>
#include <map>
#include <list>
#include <sstream>
#include <algorithm>

#include "xfsapi.h"
#include "xfsadmin.h"
#include "xfsconf.h"

#include "win32/synch.hpp"
#include "win32/shmem.hpp"
#include "win32/library.hpp"
#include "win32/msgwnd.hpp"
#include "common/version.hpp"
#include "util/memory.hpp"

#include <shlwapi.h>

namespace
{
  struct ShMemLayout
  {
    struct AppData
    {
      struct SPData
      {
        REQUESTID reqId;
        Windows::Library *spLib;
      };

      SPData hServices[8192];
      bool handles[8192];
    };

    AppData apps[64];
    DWORD pidTable[64];

    struct Timer
    {
      LPVOID lpContext;
      HWND hWnd;
    };
    
    Timer timers[65535];
  };

  HINSTANCE dllInstance;
  HANDLE mutexHandle = NULL;
  Windows::SharedMemory< ShMemLayout > shMem;
  std::map< void *,std::list< void * > > *allocMap = nullptr;
  std::map< WORD,std::tuple< HWND,LPVOID > > *_timers = nullptr;

  VOID CALLBACK timerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
  {
    shMem.access([hWnd, uMsg, idEvent, dwTime] (ShMemLayout *p)
      {
        PostMessage(p->timers[idEvent].hWnd,WFS_TIMER_EVENT,idEvent,reinterpret_cast< LPARAM >(p->timers[idEvent].lpContext));
      });
  }
}

#define CHECK_IF_STARTED \
  bool ok = false; \
  shMem.access([&ok](ShMemLayout *p) \
    { \
      ok = (std::find(std::begin(p->pidTable),std::end(p->pidTable),GetCurrentProcessId()) != std::end(p->pidTable)); \
    }); \
  \
  if (!ok) \
    return WFS_ERR_NOT_STARTED;

#define GET_LIB_AND_REQUEST \
  if (!hService) \
    return WFS_ERR_INVALID_HSERVICE; \
  \
  if (!hWnd) \
    return WFS_ERR_INVALID_HWND; \
  \
  if (!lpRequestID) \
    return WFS_ERR_INVALID_POINTER; \
  \
  bool ok = false; \
  Windows::Library *lib = nullptr; \
  shMem.access([&ok, &lib, hService, lpRequestID] (ShMemLayout *p) \
    { \
      auto it = std::find(std::begin(p->pidTable),std::end(p->pidTable),GetCurrentProcessId()); \
      \
      if (it == std::end(p->pidTable)) \
        return; \
      \
      ok = true; \
      ShMemLayout::AppData::SPData &item = p->apps[std::distance(std::begin(p->pidTable),it)].hServices[hService - 1]; \
      lib = item.spLib; \
      *lpRequestID = item.reqId++; \
    }); \
  \
  if (!ok) \
    return WFS_ERR_NOT_STARTED; \
  \
  if (!lib) \
    return WFS_ERR_INVALID_HSERVICE;

class SynchMsgWnd : public Windows::MsgWnd
{
public:
  explicit SynchMsgWnd(HINSTANCE hInstance, Windows::Synch::Semaphore &sem, HRESULT &hRes, DWORD msgId, LPWFSRESULT *lppResult = NULL) :
    Windows::MsgWnd(hInstance,[&sem, &hRes, msgId, lppResult] (UINT uMsg, WPARAM, LPARAM lParam)
      {
        if (uMsg == msgId)
        {
          hRes = reinterpret_cast< LPWFSRESULT >(lParam)->hResult;

          if (lppResult != NULL)
            *lppResult = reinterpret_cast< LPWFSRESULT >(lParam);

          sem.unlock();
        }
      })
  {

  }
};

extern "C" HRESULT WINAPI WFSCancelAsyncRequest(HSERVICE hService, REQUESTID RequestID)
{
  if (!hService)
    return WFS_ERR_INVALID_HSERVICE;

  bool ok = false;
  Windows::Library *lib = nullptr;
  shMem.access([&ok, &lib, hService] (ShMemLayout *p)
    {
      auto it = std::find(std::begin(p->pidTable),std::end(p->pidTable),GetCurrentProcessId());

      if (it == std::end(p->pidTable))
        return;

      ok = true;
      lib = p->apps[std::distance(std::begin(p->pidTable),it)].hServices[hService - 1].spLib;
    });

  if (!ok)
    return WFS_ERR_NOT_STARTED;

  if (!lib)
    return WFS_ERR_INVALID_HSERVICE;

  return lib->call< HRESULT >("WFPCancelAsyncRequest",hService,RequestID);
}

extern "C" HRESULT WINAPI WFSCancelBlockingCall(DWORD dwThreadID)
{
  CHECK_IF_STARTED

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSCleanUp()
{
  CHECK_IF_STARTED

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSClose(HSERVICE hService)
{
  CHECK_IF_STARTED

  Windows::Synch::Semaphore sem(0,1);
  HRESULT hRes = WFS_SUCCESS;

  SynchMsgWnd wnd(dllInstance,sem,hRes,WFS_CLOSE_COMPLETE);
  wnd.start();

  REQUESTID reqId;
  if ((hRes = WFSAsyncClose(hService,wnd.handle(),&reqId)) != WFS_SUCCESS)
    return hRes;

  sem.lock();

  return hRes;
}

extern "C" HRESULT WINAPI WFSAsyncClose(HSERVICE hService, HWND hWnd, LPREQUESTID lpRequestID)
{
  GET_LIB_AND_REQUEST

  return lib->call< HRESULT >("WFPClose",hService,hWnd,*lpRequestID);
}

extern "C" HRESULT WINAPI WFSCreateAppHandle(LPHAPP lphApp)
{
  if (!lphApp)
    return WFS_ERR_INVALID_POINTER;

  bool ok = false;
  shMem.access([&ok, lphApp] (ShMemLayout *p)
    {
      auto it = std::find(std::begin(p->pidTable),std::end(p->pidTable),GetCurrentProcessId());

      if ((ok = (it != std::end(p->pidTable))))
      {
        ShMemLayout::AppData &item = p->apps[std::distance(std::begin(p->pidTable),it)];
        auto ait = std::find(std::begin(item.handles),std::end(item.handles),false);

        if (ait != std::end(item.handles))
        {
          *lphApp = reinterpret_cast< HAPP >(std::distance(std::begin(item.handles),ait) + 1);
          *ait = true;
        }
      }
    });

  if (!ok)
    return WFS_ERR_NOT_STARTED;

  return (*lphApp)? WFS_SUCCESS : WFS_ERR_INTERNAL_ERROR;
}

extern "C" HRESULT WINAPI WFSDeregister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg)
{
  CHECK_IF_STARTED

  Windows::Synch::Semaphore sem(0,1);
  HRESULT hRes = WFS_SUCCESS;

  SynchMsgWnd wnd(dllInstance,sem,hRes,WFS_DEREGISTER_COMPLETE);
  wnd.start();

  REQUESTID reqId;
  if ((hRes = WFSAsyncDeregister(hService,dwEventClass,hWndReg,wnd.handle(),&reqId)) != WFS_SUCCESS)
    return hRes;

  sem.lock();

  return hRes;
}

extern "C" HRESULT WINAPI WFSAsyncDeregister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, LPREQUESTID lpRequestID)
{
  if (!hWndReg)
    return WFS_ERR_INVALID_HWNDREG;

  GET_LIB_AND_REQUEST

  return lib->call< HRESULT >("WFPDeregister",hService,dwEventClass,hWndReg,hWnd,*lpRequestID);
}

extern "C" HRESULT WINAPI WFSDestroyAppHandle(HAPP hApp)
{
  if (!hApp)
    return WFS_ERR_INVALID_APP_HANDLE;

  int idx = reinterpret_cast< int >(hApp) - 1;

  bool ok = false;
  shMem.access([&ok, &idx] (ShMemLayout *p)
    {
      auto it = std::find(std::begin(p->pidTable),std::end(p->pidTable),GetCurrentProcessId());

      if ((ok = (it != std::end(p->pidTable))))
      {
        ShMemLayout::AppData &item = p->apps[std::distance(std::begin(p->pidTable),it)];
        if (item.handles[idx])
        {
          item.handles[idx] = false;
          idx = 0;
        }
      }
    });

  if (!ok)
    return WFS_ERR_NOT_STARTED;

  return (!idx)? WFS_SUCCESS : WFS_ERR_INVALID_APP_HANDLE;
}

extern "C" HRESULT WINAPI WFSExecute(HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, LPWFSRESULT *lppResult)
{
  CHECK_IF_STARTED

  Windows::Synch::Semaphore sem(0,1);
  HRESULT hRes = WFS_SUCCESS;

  SynchMsgWnd wnd(dllInstance,sem,hRes,WFS_EXECUTE_COMPLETE,lppResult);
  wnd.start();

  REQUESTID reqId;
  if ((hRes = WFSAsyncExecute(hService,dwCommand,lpCmdData,dwTimeOut,wnd.handle(),&reqId)) != WFS_SUCCESS)
    return hRes;

  sem.lock();

  return hRes;
}

extern "C" HRESULT WINAPI WFSAsyncExecute(HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID)
{
  GET_LIB_AND_REQUEST

  return lib->call< HRESULT >("WFPExecute",hService,dwCommand,lpCmdData,dwTimeOut,hWnd,*lpRequestID);
}

extern "C" HRESULT WINAPI WFSFreeResult(LPWFSRESULT lpResult)
{
  CHECK_IF_STARTED

  return WFMFreeBuffer(lpResult);
}

extern "C" HRESULT WINAPI WFSGetInfo(HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, LPWFSRESULT *lppResult)
{
  CHECK_IF_STARTED

  Windows::Synch::Semaphore sem(0,1);
  HRESULT hRes = WFS_SUCCESS;

  SynchMsgWnd wnd(dllInstance,sem,hRes,WFS_GETINFO_COMPLETE,lppResult);
  wnd.start();

  REQUESTID reqId;
  if ((hRes = WFSAsyncGetInfo(hService,dwCategory,lpQueryDetails,dwTimeOut,wnd.handle(),&reqId)) != WFS_SUCCESS)
    return hRes;

  sem.lock();

  return hRes;
}

extern "C" HRESULT WINAPI WFSAsyncGetInfo(HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID)
{
  GET_LIB_AND_REQUEST

  return lib->call< HRESULT >("WFPGetInfo",hService,dwCategory,lpQueryDetails,dwTimeOut,hWnd,*lpRequestID);
}

extern "C" BOOL WINAPI WFSIsBlocking()
{
  CHECK_IF_STARTED

  return FALSE;
}

extern "C" HRESULT WINAPI WFSLock(HSERVICE hService, DWORD dwTimeOut, LPWFSRESULT *lppResult)
{
  if (!lppResult)
    return WFS_ERR_INVALID_POINTER;

  CHECK_IF_STARTED

  Windows::Synch::Semaphore sem(0,1);
  HRESULT hRes = WFS_SUCCESS;

  SynchMsgWnd wnd(dllInstance,sem,hRes,WFS_LOCK_COMPLETE);
  wnd.start();

  REQUESTID reqId;
  if ((hRes = WFSAsyncLock(hService,dwTimeOut,wnd.handle(),&reqId)) != WFS_SUCCESS)
    return hRes;

  sem.lock();

  return hRes;
}

extern "C" HRESULT WINAPI WFSAsyncLock(HSERVICE hService, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID)
{
  GET_LIB_AND_REQUEST

  return lib->call< HRESULT >("WFPLock",hService,dwTimeOut,hWnd,*lpRequestID);
}

extern "C" HRESULT WINAPI WFSOpen(LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion, LPWFSVERSION lpSPIVersion, LPHSERVICE lphService)
{
  if (!hApp)
    return WFS_ERR_INVALID_APP_HANDLE;

  if (!lpszLogicalName || !lpszAppID || !lphService || !lpSrvcVersion || !lpSPIVersion)
    return WFS_ERR_INVALID_POINTER;

  CHECK_IF_STARTED

  Windows::Synch::Semaphore sem(0,1);
  HRESULT hRes = WFS_SUCCESS;

  SynchMsgWnd wnd(dllInstance,sem,hRes,WFS_OPEN_COMPLETE);
  wnd.start();

  REQUESTID reqId;
  if ((hRes = WFSAsyncOpen(lpszLogicalName,hApp,lpszAppID,dwTraceLevel,dwTimeOut,lphService,wnd.handle(),dwSrvcVersionsRequired,lpSrvcVersion,lpSPIVersion,&reqId)) != WFS_SUCCESS)
    return hRes;

  sem.lock();

  return hRes;
}

extern "C" HRESULT WINAPI WFSAsyncOpen(LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, LPHSERVICE lphService, HWND hWnd, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion, LPWFSVERSION lpSPIVersion, LPREQUESTID lpRequestID)
{
  if (!hApp)
    return WFS_ERR_INVALID_APP_HANDLE;

  if (!lpszLogicalName || !lpszAppID || !lphService || !lpSrvcVersion || !lpSPIVersion || !lpRequestID)
    return WFS_ERR_INVALID_POINTER;

  *lphService = 0;
  *lpRequestID = 0;
  clearMem(*lpSPIVersion);
  clearMem(*lpSrvcVersion);

  bool ok = false;
  Windows::Library *lib = nullptr;
  shMem.access([&ok, &lib, &hApp, lphService, lpRequestID] (ShMemLayout *p)
    {
      auto it = std::find(std::begin(p->pidTable),std::end(p->pidTable),GetCurrentProcessId());

      if (it == std::end(p->pidTable))
        return;

      ShMemLayout::AppData &item = p->apps[std::distance(std::begin(p->pidTable),it)];

      ok = true;

      if (!item.handles[reinterpret_cast< int >(hApp) - 1])
      {
        hApp = NULL;
        return;
      }

      auto sit = std::find_if(std::begin(item.hServices),std::end(item.hServices),[] (const ShMemLayout::AppData::SPData &x) { return x.reqId == 0; });
      if (sit == std::end(item.hServices))
        return;

      sit->reqId = 1;
      sit->spLib = new Windows::Library(L"sp.dll");
      *lpRequestID = 1;
      *lphService = static_cast< HSERVICE >(std::distance(std::begin(item.hServices),sit) + 1);
  });

  if (!ok)
    return WFS_ERR_NOT_STARTED;

  if (!hApp)
    return WFS_ERR_INVALID_APP_HANDLE;

  return lib->call< HRESULT >("WFPOpen",
    *lphService,
    lpszLogicalName,
    hApp,
    lpszAppID,
    dwTraceLevel,
    dwTimeOut,
    hWnd,
    *lpRequestID,
    lib->handle(),
    XFS::VersionRange(XFS::Version(3,0),XFS::Version(3,30)).value(),
    lpSPIVersion,
    dwSrvcVersionsRequired,
    lpSrvcVersion);
}

extern "C" HRESULT WINAPI WFSRegister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg)
{
  CHECK_IF_STARTED

  Windows::Synch::Semaphore sem(0,1);
  HRESULT hRes = WFS_SUCCESS;

  SynchMsgWnd wnd(dllInstance,sem,hRes,WFS_REGISTER_COMPLETE);
  wnd.start();

  REQUESTID reqId;
  if ((hRes = WFSAsyncRegister(hService,dwEventClass,hWndReg,wnd.handle(),&reqId)) != WFS_SUCCESS)
    return hRes;

  sem.lock();

  return hRes;
}

extern "C" HRESULT WINAPI WFSAsyncRegister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, LPREQUESTID lpRequestID)
{
  if (!hWndReg)
    return WFS_ERR_INVALID_HWNDREG;

  GET_LIB_AND_REQUEST

  return lib->call< HRESULT >("WFPRegister",hService,dwEventClass,hWndReg,hWnd,*lpRequestID);
}

extern "C" HRESULT WINAPI WFSSetBlockingHook(XFSBLOCKINGHOOK lpBlockFunc, LPXFSBLOCKINGHOOK lppPrevFunc)
{
  CHECK_IF_STARTED

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSStartUp(DWORD dwVersionsRequired, LPWFSVERSION lpWFSVersion)
{
  XFS::VersionRange vr(dwVersionsRequired);

  if (vr.start() > vr.end())
    return WFS_ERR_INTERNAL_ERROR;

  if (vr.start() > XFS::Version(3,20))
    return WFS_ERR_API_VER_TOO_HIGH;

  if (vr.end() < XFS::Version(3,20))
    return WFS_ERR_API_VER_TOO_LOW;

  if (!lpWFSVersion)
    return WFS_ERR_INVALID_POINTER;

  clearMem(*lpWFSVersion);

  lpWFSVersion->wVersion = XFS::Version(3,20).value();
  lpWFSVersion->wLowVersion = XFS::Version::min(3).value();
  lpWFSVersion->wHighVersion = XFS::Version::max(3).value();
  lpWFSVersion->szSystemStatus[0] = '\0';
  strcpy_s(lpWFSVersion->szDescription,"xfspp XFS Manager");

  HRESULT hRes = WFS_SUCCESS;
  shMem.access([&hRes] (ShMemLayout *p)
    {
      auto it = std::find(std::begin(p->pidTable),std::end(p->pidTable),GetCurrentProcessId());

      if (it != std::end(p->pidTable))
      {
        hRes = WFS_ERR_ALREADY_STARTED;
        return;
      }

      it = std::find(std::begin(p->pidTable),std::end(p->pidTable),0);

      if (it == std::end(p->pidTable))
      {
        hRes = WFS_ERR_INTERNAL_ERROR;
        return;
      }

      *it = GetCurrentProcessId();
      clearMem(p->apps[std::distance(std::begin(p->pidTable),it)]);
    });

  return hRes;
}

extern "C" HRESULT WINAPI WFSUnhookBlockingHook()
{
  CHECK_IF_STARTED

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSUnlock(HSERVICE hService)
{
  CHECK_IF_STARTED

  Windows::Synch::Semaphore sem(0,1);
  HRESULT hRes = WFS_SUCCESS;

  SynchMsgWnd wnd(dllInstance,sem,hRes,WFS_UNLOCK_COMPLETE);
  wnd.start();

  REQUESTID reqId;
  if ((hRes = WFSAsyncUnlock(hService,wnd.handle(),&reqId)) != WFS_SUCCESS)
    return hRes;

  sem.lock();

  return hRes;
}

extern "C" HRESULT WINAPI WFSAsyncUnlock(HSERVICE hService, HWND hWnd, LPREQUESTID lpRequestID)
{
  GET_LIB_AND_REQUEST

  return lib->call< HRESULT >("WFPUnlock",hService,hWnd,*lpRequestID);
}

extern "C" HRESULT WINAPI WFMSetTraceLevel(HSERVICE hService, DWORD dwTraceLevel)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMAllocateBuffer(ULONG ulSize, ULONG, LPVOID *lppvData)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!lppvData)
    return WFS_ERR_INVALID_POINTER;

  if (!allocMap)
    allocMap = new std::map< void *,std::list< void * > >();

  *lppvData = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,ulSize);

  if (!*lppvData)
    return WFS_ERR_OUT_OF_MEMORY;

  allocMap->emplace(*lppvData,std::list< void * >());

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMAllocateMore(ULONG ulSize, LPVOID lpvOriginal, LPVOID *lppvData)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!lppvData)
    return WFS_ERR_INVALID_POINTER;

  if (!allocMap)
    return WFS_ERR_INVALID_ADDRESS;

  auto it = allocMap->find(lpvOriginal);
  
  if (it == allocMap->cend())
    return WFS_ERR_INVALID_ADDRESS;

  *lppvData = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,ulSize);

  if (!*lppvData)
    return WFS_ERR_OUT_OF_MEMORY;

  (*allocMap)[lpvOriginal].push_back(*lppvData);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMFreeBuffer(LPVOID lpvData)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);
  
  if (!lpvData)
    return WFS_ERR_INVALID_POINTER;

  if (!allocMap)
    return WFS_ERR_INVALID_BUFFER;

  auto it = allocMap->find(lpvData);

  if (it == allocMap->cend())
    return WFS_ERR_INVALID_BUFFER;

  for (void *p : allocMap->at(lpvData))
    HeapFree(GetProcessHeap(),0,p);

  HeapFree(GetProcessHeap(),0,lpvData);

  allocMap->erase(it);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMGetTraceLevel(HSERVICE hService, LPDWORD lpdwTraceLevel)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMKillTimer(WORD wTimerID)
{
  HRESULT hRes = WFS_SUCCESS;
  shMem.access([&hRes, wTimerID]  (ShMemLayout *p)
    {
      if (p->timers[wTimerID].hWnd == NULL)
      {
        hRes = WFS_ERR_INVALID_TIMER;
        return;
      }

      if (!KillTimer(NULL,static_cast< UINT_PTR >(wTimerID)))
      {
        hRes = WFS_ERR_INTERNAL_ERROR;
        return;
      }

      p->timers[wTimerID].hWnd = NULL;
    });

  return hRes;
}

extern "C" HRESULT WINAPI WFMOutputTraceData(LPSTR lpszData)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMReleaseDLL(HPROVIDER hProvider)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMSetTimer(HWND hWnd, LPVOID lpContext, DWORD dwTimeVal, LPWORD lpwTimerID)
{
  if (!hWnd)
    return WFS_ERR_INVALID_HWND;

  if (!lpwTimerID)
    return WFS_ERR_INVALID_POINTER;

  if (!dwTimeVal)
    return WFS_ERR_INVALID_DATA;

  HRESULT hRes = WFS_SUCCESS;
  shMem.access([&hRes, hWnd, lpContext, dwTimeVal] (ShMemLayout *p)
    {
      auto it = std::find_if(std::begin(p->timers),std::end(p->timers),[] (const ShMemLayout::Timer &t) { return t.hWnd == NULL; });

      if (it == std::end(p->timers))
      {
        hRes = WFS_ERR_INTERNAL_ERROR;
        return;
      }

      it->hWnd = hWnd;
      it->lpContext = lpContext;

      UINT_PTR id = SetTimer(NULL,static_cast< UINT_PTR >(std::distance(std::begin(p->timers),it)),dwTimeVal,timerProc);
      if (!id)
      {
        hRes = WFS_ERR_INTERNAL_ERROR;
        it->hWnd = 0;
        return;
      }
    });

  return hRes;
}

extern "C" HRESULT WINAPI WFMCloseKey(HKEY hKey)
{
  switch (RegCloseKey(hKey))
  {
    case ERROR_SUCCESS:
      return WFS_SUCCESS;

    case ERROR_FILE_NOT_FOUND:
      return WFS_ERR_CFG_INVALID_HKEY;

    default:
      return WFS_ERR_INTERNAL_ERROR;
  }
}

extern "C" HRESULT WINAPI WFMCreateKey(HKEY hKey, LPSTR lpszSubKey, PHKEY phkResult, LPDWORD lpdwDisposition)
{
  if (!lpszSubKey || !phkResult || !lpdwDisposition)
    return WFS_ERR_INVALID_POINTER;

  DWORD dwDisposition = *lpdwDisposition = 0;
  CHAR subKeyBuf[1024];

  SecureZeroMemory(subKeyBuf,1024 * sizeof(CHAR));

  if (hKey == WFS_CFG_HKEY_XFS_ROOT)
  {
    strcpy_s(subKeyBuf,"WOSA/XFS_ROOT\\");
    hKey = HKEY_CLASSES_ROOT;
  }
  else if (hKey == WFS_CFG_HKEY_MACHINE_XFS_ROOT)
  {
    strcpy_s(subKeyBuf,"SOFTWARE\\XFS\\");
    hKey = HKEY_LOCAL_MACHINE;
  }
  else if (hKey == WFS_CFG_HKEY_USER_DEFAULT_XFS_ROOT)
  {
    strcpy_s(subKeyBuf,".DEFAULT\\XFS\\");
    hKey = HKEY_USERS;
  }

  strcat_s(subKeyBuf,lpszSubKey);

  switch (RegCreateKeyExA(hKey,subKeyBuf,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,phkResult,&dwDisposition))
  {
    case ERROR_SUCCESS:
      switch (dwDisposition)
      {
        case REG_CREATED_NEW_KEY:
          *lpdwDisposition = WFS_CFG_CREATED_NEW_KEY;
          break;

        case REG_OPENED_EXISTING_KEY:
          *lpdwDisposition = WFS_CFG_OPENED_EXISTING_KEY;
          break;

        default:
          break;
      }

      return WFS_SUCCESS;

    case ERROR_FILE_NOT_FOUND:
      return WFS_ERR_CFG_INVALID_HKEY;

    case ERROR_PATH_NOT_FOUND:
      return WFS_ERR_CFG_INVALID_SUBKEY;

    default:
      return WFS_ERR_INTERNAL_ERROR;
  }
}

extern "C" HRESULT WINAPI WFMDeleteKey(HKEY hKey, LPSTR lpszSubKey)
{
  if (!lpszSubKey)
    return WFS_ERR_INVALID_POINTER;

  switch (RegDeleteKeyExA(hKey,lpszSubKey,0,0))
  {
    case ERROR_SUCCESS:
      return WFS_SUCCESS;

    case ERROR_FILE_NOT_FOUND:
      return WFS_ERR_CFG_INVALID_HKEY;

    case ERROR_KEY_HAS_CHILDREN:
      return WFS_ERR_CFG_KEY_NOT_EMPTY;

    case ERROR_PATH_NOT_FOUND:
      return WFS_ERR_CFG_INVALID_SUBKEY;

    default:
      return WFS_ERR_INTERNAL_ERROR;
  }
}

extern "C" HRESULT WINAPI WFMDeleteValue(HKEY hKey, LPSTR lpszValue)
{
  if (!lpszValue)
    return WFS_ERR_INVALID_POINTER;

  switch (RegDeleteValueA(hKey,lpszValue))
  {
    case ERROR_SUCCESS:
      return WFS_SUCCESS;

    case ERROR_FILE_NOT_FOUND:
      return WFS_ERR_CFG_INVALID_HKEY;

    case ERROR_PATH_NOT_FOUND:
      return WFS_ERR_CFG_INVALID_VALUE;

    default:
      return WFS_ERR_INTERNAL_ERROR;
  }}

extern "C" HRESULT WINAPI WFMEnumKey(HKEY hKey, DWORD iSubKey, LPSTR lpszName, LPDWORD lpcchName, PFILETIME lpftLastWrite)
{
  if (!lpszName || !lpcchName || !lpftLastWrite)
    return WFS_ERR_INVALID_POINTER;

  SecureZeroMemory(lpszName,*lpcchName);

  switch (RegEnumKeyExA(hKey,iSubKey,lpszName,lpcchName,NULL,NULL,NULL,lpftLastWrite))
  {
    case ERROR_SUCCESS:
      return WFS_SUCCESS;

    case ERROR_FILE_NOT_FOUND:
      return WFS_ERR_CFG_INVALID_HKEY;

    case ERROR_MORE_DATA:
      return WFS_ERR_CFG_NAME_TOO_LONG;

    case ERROR_NO_MORE_ITEMS:
      return WFS_ERR_CFG_NO_MORE_ITEMS;

    default:
      return WFS_ERR_INTERNAL_ERROR;
  }
}

extern "C" HRESULT WINAPI WFMEnumValue(HKEY hKey, DWORD iValue, LPSTR lpszValue, LPDWORD lpcchValue, LPSTR lpszData, LPDWORD lpcchData)
{
  if (!lpszValue || !lpcchValue || !lpszData || !lpcchData)
    return WFS_ERR_INVALID_POINTER;

  SecureZeroMemory(lpszValue,*lpcchValue);
  SecureZeroMemory(lpszData,*lpcchData);

  switch (RegEnumValueA(hKey,iValue,lpszValue,lpcchValue,NULL,NULL,reinterpret_cast< BYTE * >(lpszData),lpcchData))
  {
    case ERROR_SUCCESS:
      return WFS_SUCCESS;

    case ERROR_FILE_NOT_FOUND:
      return WFS_ERR_CFG_INVALID_HKEY;

    case ERROR_PATH_NOT_FOUND:
      return WFS_ERR_CFG_INVALID_SUBKEY;

    case ERROR_MORE_DATA:
      return WFS_ERR_CFG_VALUE_TOO_LONG;

    case ERROR_NO_MORE_ITEMS:
      return WFS_ERR_CFG_NO_MORE_ITEMS;

    default:
      return WFS_ERR_INTERNAL_ERROR;
  }
}

extern "C" HRESULT WINAPI WFMOpenKey(HKEY hKey, LPSTR lpszSubKey, PHKEY phkResult)
{
  if (!lpszSubKey || !phkResult)
    return WFS_ERR_INVALID_POINTER;

  CHAR subKeyBuf[MAX_PATH];

  SecureZeroMemory(subKeyBuf,1024 * sizeof(CHAR));

  if (hKey == WFS_CFG_HKEY_XFS_ROOT)
  {
    strcpy_s(subKeyBuf,"WOSA/XFS_ROOT\\");
    hKey = HKEY_CLASSES_ROOT;
  }
  else if (hKey == WFS_CFG_HKEY_MACHINE_XFS_ROOT)
  {
    strcpy_s(subKeyBuf,"SOFTWARE\\XFS\\");
    hKey = HKEY_LOCAL_MACHINE;
  }
  else if (hKey == WFS_CFG_HKEY_USER_DEFAULT_XFS_ROOT)
  {
    strcpy_s(subKeyBuf,".DEFAULT\\XFS\\");
    hKey = HKEY_USERS;
  }

  strcat_s(subKeyBuf,lpszSubKey);

  switch (RegOpenKeyA(hKey,subKeyBuf,phkResult))
  {
    case ERROR_SUCCESS:
      return WFS_SUCCESS;

    case ERROR_FILE_NOT_FOUND:
      return WFS_ERR_CFG_INVALID_HKEY;

    case ERROR_PATH_NOT_FOUND:
      return WFS_ERR_CFG_INVALID_SUBKEY;

    default:
      return WFS_ERR_INTERNAL_ERROR;
  }
}

extern "C" HRESULT WINAPI WFMQueryValue(HKEY hKey, LPSTR lpszValueName, LPSTR lpszData, LPDWORD lpcchData)
{
  if (!lpszValueName || !lpszData || !lpcchData)
    return WFS_ERR_INVALID_POINTER;

  SecureZeroMemory(lpszData,*lpcchData);

  switch (RegQueryValueExA(hKey,lpszValueName,NULL,NULL,reinterpret_cast< BYTE * >(lpszData),lpcchData))
  {
    case ERROR_SUCCESS:
      return WFS_SUCCESS;

    case ERROR_FILE_NOT_FOUND:
      return WFS_ERR_CFG_INVALID_HKEY;

    case ERROR_PATH_NOT_FOUND:
      return WFS_ERR_CFG_INVALID_NAME;

    case ERROR_MORE_DATA:
      return WFS_ERR_CFG_VALUE_TOO_LONG;

    default:
      return WFS_ERR_INTERNAL_ERROR;
  }
}

extern "C" HRESULT WINAPI WFMSetValue(HKEY hKey, LPSTR lpszValueName, LPSTR lpszData, DWORD cchData)
{
  if (!lpszValueName || !lpszData)
    return WFS_ERR_INVALID_POINTER;

  switch (RegSetValueExA(hKey,lpszValueName,0,REG_SZ,reinterpret_cast< BYTE * >(lpszData),cchData))
  {
    case ERROR_SUCCESS:
      return WFS_SUCCESS;

    case ERROR_FILE_NOT_FOUND:
      return WFS_ERR_CFG_INVALID_HKEY;

    default:
      return WFS_ERR_INTERNAL_ERROR;
  }
}

extern "C" BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID)
{
  switch (fdwReason)
  {
    case DLL_PROCESS_ATTACH:
      dllInstance = hinstDLL;
      mutexHandle = CreateMutex(NULL,FALSE,L"Global\\XFSPP_XFS_MANAGER_MUTEX");
      break;

    case DLL_PROCESS_DETACH:
      CloseHandle(mutexHandle);
      delete allocMap;
      break;

    default:
      break;
  }

  return TRUE;
}
