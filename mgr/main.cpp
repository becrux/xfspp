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
#include <string>
#include <sstream>
#include <algorithm>

#include "xfsapi.h"
#include "xfsadmin.h"
#include "xfsconf.h"

#include "win32/synch.hpp"
#include "win32/shmem.hpp"
#include "win32/library.hpp"
#include "win32/msgwnd.hpp"
#include "xfs/version.hpp"
#include "xfs/registry.hpp"
#include "util/memory.hpp"
#include "util/methodscope.hpp"
#include "util/constraints.hpp"
#include "log/log.hpp"

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

  HINSTANCE dllInstance = NULL;
  HANDLE mutexHandle = NULL;

  class Context
  {
    NON_COPYABLE(Context);
    NON_MOVEABLE(Context);

  public:
    Windows::SharedMemory< ShMemLayout > shMem;
    std::map< void *,std::list< void * > > allocMap;
    std::map< WORD,std::tuple< HWND,LPVOID > > timers;

    explicit Context() :
      shMem(L"XFSPP_MANAGER")
    {

    }
  } *_ctx = nullptr;

  void initializeContext()
  {
    if (!_ctx)
    {
      Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  	  if (!_ctx)
    	_ctx = new Context;
    }
  }

  VOID CALLBACK timerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
  {
    _ctx->shMem.access([hWnd, uMsg, idEvent, dwTime] (ShMemLayout *p)
      {
        PostMessage(p->timers[idEvent].hWnd,WFS_TIMER_EVENT,idEvent,reinterpret_cast< LPARAM >(p->timers[idEvent].lpContext));
      });
  }
}

#define CHECK_IF_STARTED \
  bool ok = false; \
  _ctx->shMem.access([&ok](ShMemLayout *p) \
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
  _ctx->shMem.access([&ok, &lib, hService, lpRequestID] (ShMemLayout *p) \
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
  NON_COPYABLE(SynchMsgWnd);

public:
  explicit SynchMsgWnd(HINSTANCE hInstance, Windows::Synch::Semaphore &sem, HRESULT &hRes, DWORD msgId, LPWFSRESULT *lppResult = NULL) :
    Windows::MsgWnd(hInstance,[&sem, &hRes, msgId, lppResult] (UINT uMsg, WPARAM, LPARAM lParam)
      {
        if (uMsg == msgId)
        {
          hRes = reinterpret_cast< LPWFSRESULT >(lParam)->hResult;

          if (lppResult != NULL)
            *lppResult = reinterpret_cast< LPWFSRESULT >(lParam);

          sem.release();
        }
      })
  {

  }
};

extern "C" HRESULT WINAPI WFSCancelAsyncRequest(HSERVICE hService, REQUESTID RequestID)
{
  initializeContext();

  if (!hService)
    return WFS_ERR_INVALID_HSERVICE;

  bool ok = false;
  Windows::Library *lib = nullptr;
  _ctx->shMem.access([&ok, &lib, hService] (ShMemLayout *p)
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
  initializeContext();

  CHECK_IF_STARTED

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSCleanUp()
{
  initializeContext();

  bool ok = false;
  _ctx->shMem.access([&ok] (ShMemLayout *p)
    {
      auto it = std::find(std::begin(p->pidTable),std::end(p->pidTable),GetCurrentProcessId());
      
      if (it != std::end(p->pidTable))
      {
        *it = 0;
        ok = true;
      }
    });

  return (ok)? WFS_SUCCESS : WFS_ERR_NOT_STARTED;
}

extern "C" HRESULT WINAPI WFSClose(HSERVICE hService)
{
  initializeContext();

  CHECK_IF_STARTED

  Windows::Synch::Semaphore sem(0,1);
  HRESULT hRes = WFS_SUCCESS;

  SynchMsgWnd wnd(dllInstance,sem,hRes,WFS_CLOSE_COMPLETE);
  wnd.start();

  REQUESTID reqId;
  if ((hRes = WFSAsyncClose(hService,wnd.handle(),&reqId)) != WFS_SUCCESS)
    return hRes;

  sem.acquire();

  return hRes;
}

extern "C" HRESULT WINAPI WFSAsyncClose(HSERVICE hService, HWND hWnd, LPREQUESTID lpRequestID)
{
  initializeContext();

  GET_LIB_AND_REQUEST

  return lib->call< HRESULT >("WFPClose",hService,hWnd,*lpRequestID);
}

extern "C" HRESULT WINAPI WFSCreateAppHandle(LPHAPP lphApp)
{
  initializeContext();

  if (!lphApp)
    return WFS_ERR_INVALID_POINTER;

  bool ok = false;
  _ctx->shMem.access([&ok, lphApp] (ShMemLayout *p)
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
  initializeContext();

  CHECK_IF_STARTED

  Windows::Synch::Semaphore sem(0,1);
  HRESULT hRes = WFS_SUCCESS;

  SynchMsgWnd wnd(dllInstance,sem,hRes,WFS_DEREGISTER_COMPLETE);
  wnd.start();

  REQUESTID reqId;
  if ((hRes = WFSAsyncDeregister(hService,dwEventClass,hWndReg,wnd.handle(),&reqId)) != WFS_SUCCESS)
    return hRes;

  sem.acquire();

  return hRes;
}

extern "C" HRESULT WINAPI WFSAsyncDeregister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, LPREQUESTID lpRequestID)
{
  initializeContext();

  if (!hWndReg)
    return WFS_ERR_INVALID_HWNDREG;

  GET_LIB_AND_REQUEST

  return lib->call< HRESULT >("WFPDeregister",hService,dwEventClass,hWndReg,hWnd,*lpRequestID);
}

extern "C" HRESULT WINAPI WFSDestroyAppHandle(HAPP hApp)
{
  initializeContext();

  if (!hApp)
    return WFS_ERR_INVALID_APP_HANDLE;

  int idx = reinterpret_cast< int >(hApp) - 1;

  bool ok = false;
  _ctx->shMem.access([&ok, &idx] (ShMemLayout *p)
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
  initializeContext();

  CHECK_IF_STARTED

  Windows::Synch::Semaphore sem(0,1);
  HRESULT hRes = WFS_SUCCESS;

  SynchMsgWnd wnd(dllInstance,sem,hRes,WFS_EXECUTE_COMPLETE,lppResult);
  wnd.start();

  REQUESTID reqId;
  if ((hRes = WFSAsyncExecute(hService,dwCommand,lpCmdData,dwTimeOut,wnd.handle(),&reqId)) != WFS_SUCCESS)
    return hRes;

  sem.acquire();

  return hRes;
}

extern "C" HRESULT WINAPI WFSAsyncExecute(HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID)
{
  initializeContext();

  GET_LIB_AND_REQUEST

  return lib->call< HRESULT >("WFPExecute",hService,dwCommand,lpCmdData,dwTimeOut,hWnd,*lpRequestID);
}

extern "C" HRESULT WINAPI WFSFreeResult(LPWFSRESULT lpResult)
{
  initializeContext();

  CHECK_IF_STARTED

  return WFMFreeBuffer(lpResult);
}

extern "C" HRESULT WINAPI WFSGetInfo(HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, LPWFSRESULT *lppResult)
{
  initializeContext();

  CHECK_IF_STARTED

  Windows::Synch::Semaphore sem(0,1);
  HRESULT hRes = WFS_SUCCESS;

  SynchMsgWnd wnd(dllInstance,sem,hRes,WFS_GETINFO_COMPLETE,lppResult);
  wnd.start();

  REQUESTID reqId;
  if ((hRes = WFSAsyncGetInfo(hService,dwCategory,lpQueryDetails,dwTimeOut,wnd.handle(),&reqId)) != WFS_SUCCESS)
    return hRes;

  sem.acquire();

  return hRes;
}

extern "C" HRESULT WINAPI WFSAsyncGetInfo(HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID)
{
  initializeContext();

  GET_LIB_AND_REQUEST

  return lib->call< HRESULT >("WFPGetInfo",hService,dwCategory,lpQueryDetails,dwTimeOut,hWnd,*lpRequestID);
}

extern "C" BOOL WINAPI WFSIsBlocking()
{
  initializeContext();

  CHECK_IF_STARTED

  return FALSE;
}

extern "C" HRESULT WINAPI WFSLock(HSERVICE hService, DWORD dwTimeOut, LPWFSRESULT *lppResult)
{
  initializeContext();

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

  sem.acquire();

  return hRes;
}

extern "C" HRESULT WINAPI WFSAsyncLock(HSERVICE hService, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID)
{
  initializeContext();

  GET_LIB_AND_REQUEST

  return lib->call< HRESULT >("WFPLock",hService,dwTimeOut,hWnd,*lpRequestID);
}

extern "C" HRESULT WINAPI WFSOpen(LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion, LPWFSVERSION lpSPIVersion, LPHSERVICE lphService)
{
  initializeContext();

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

  sem.acquire();

  return hRes;
}

extern "C" HRESULT WINAPI WFSAsyncOpen(LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, LPHSERVICE lphService, HWND hWnd, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion, LPWFSVERSION lpSPIVersion, LPREQUESTID lpRequestID)
{
  initializeContext();

  if (!hApp)
    return WFS_ERR_INVALID_APP_HANDLE;

  if (!lpszLogicalName || !lpszAppID || !lphService || !lpSrvcVersion || !lpSPIVersion || !lpRequestID)
    return WFS_ERR_INVALID_POINTER;

  *lphService = 0;
  *lpRequestID = 0;
  clearMem(*lpSPIVersion);
  clearMem(*lpSrvcVersion);

  Windows::Library *lib = nullptr;
  HRESULT hRes = WFS_SUCCESS;
  _ctx->shMem.access([&lib, &hRes, &hApp, lphService, lpRequestID, lpszLogicalName] (ShMemLayout *p)
    {
      auto it = std::find(std::begin(p->pidTable),std::end(p->pidTable),GetCurrentProcessId());

      if (it == std::end(p->pidTable))
      {
        hRes = WFS_ERR_NOT_STARTED;
        return;
      }

      ShMemLayout::AppData &item = p->apps[std::distance(std::begin(p->pidTable),it)];

      if (!item.handles[reinterpret_cast< int >(hApp) - 1])
      {
        hApp = NULL;
        hRes = WFS_ERR_INVALID_APP_HANDLE;
        return;
      }

      auto sit = std::find_if(std::begin(item.hServices),std::end(item.hServices),[] (const ShMemLayout::AppData::SPData &x) { return x.reqId == 0; });
      if (sit == std::end(item.hServices))
      {
        hRes = WFS_ERR_INTERNAL_ERROR;
        return;
      }

      sit->reqId = 1;

      CHAR lglProvPath[MAX_PATH];

      {
        DWORD lglProvPathLength = MAX_PATH;
        clearMem(lglProvPath);

        HKEY lglKey;
        if (WFMOpenKey(
              WFS_CFG_HKEY_USER_DEFAULT_XFS_ROOT,
              const_cast<LPSTR>((std::string("LOGICAL_SERVICES\\") + std::string(lpszLogicalName)).c_str()),
              &lglKey) != WFS_SUCCESS)
        {
          hRes = WFS_ERR_INVALID_SERVPROV;
          return;
        }

        MethodScope keyScope([&lglKey] () { WFMCloseKey(lglKey); });

        if (WFMQueryValue(lglKey,"provider",lglProvPath,&lglProvPathLength) != WFS_SUCCESS)
        {
          hRes = WFS_ERR_INVALID_SERVPROV;
          return;
        }
      }

      CHAR phyProvPath[MAX_PATH];

      {
        DWORD phyProvPathLength = MAX_PATH;
        clearMem(phyProvPath);

        HKEY phyKey;
        if (WFMOpenKey(
          WFS_CFG_HKEY_MACHINE_XFS_ROOT,
          const_cast<LPSTR>((std::string("SERVICE_PROVIDERS\\") + std::string(lglProvPath)).c_str()),
          &phyKey) != WFS_SUCCESS)
        {
          hRes = WFS_ERR_INVALID_SERVPROV;
          return;
        }

        MethodScope keyScope([&phyKey] () { WFMCloseKey(phyKey); });

        if (WFMQueryValue(phyKey,"dllname",lglProvPath,&phyProvPathLength) != WFS_SUCCESS)
        {
          hRes = WFS_ERR_INVALID_SERVPROV;
          return;
        }
      }

      TCHAR wProvPath[MAX_PATH];
      clearMem(wProvPath);
      MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS | MB_PRECOMPOSED,phyProvPath,-1,wProvPath,MAX_PATH);

      try
      {
        lib = sit->spLib = new Windows::Library(wProvPath);
      }
      catch (const Windows::Exception &e)
      {
        hRes = WFS_ERR_INVALID_SERVPROV;
        return;
      }

      *lpRequestID = 1;
      *lphService = static_cast< HSERVICE >(std::distance(std::begin(item.hServices),sit) + 1);
  });

  if (hRes != WFS_SUCCESS)
    return hRes;

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
  initializeContext();

  CHECK_IF_STARTED

  Windows::Synch::Semaphore sem(0,1);
  HRESULT hRes = WFS_SUCCESS;

  SynchMsgWnd wnd(dllInstance,sem,hRes,WFS_REGISTER_COMPLETE);
  wnd.start();

  REQUESTID reqId;
  if ((hRes = WFSAsyncRegister(hService,dwEventClass,hWndReg,wnd.handle(),&reqId)) != WFS_SUCCESS)
    return hRes;

  sem.acquire();

  return hRes;
}

extern "C" HRESULT WINAPI WFSAsyncRegister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, LPREQUESTID lpRequestID)
{
  initializeContext();

  if (!hWndReg)
    return WFS_ERR_INVALID_HWNDREG;

  GET_LIB_AND_REQUEST

  return lib->call< HRESULT >("WFPRegister",hService,dwEventClass,hWndReg,hWnd,*lpRequestID);
}

extern "C" HRESULT WINAPI WFSSetBlockingHook(XFSBLOCKINGHOOK lpBlockFunc, LPXFSBLOCKINGHOOK lppPrevFunc)
{
  initializeContext();

  CHECK_IF_STARTED

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSStartUp(DWORD dwVersionsRequired, LPWFSVERSION lpWFSVersion)
{
  initializeContext();

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
  _ctx->shMem.access([&hRes] (ShMemLayout *p)
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
  initializeContext();

  CHECK_IF_STARTED

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSUnlock(HSERVICE hService)
{
  initializeContext();

  CHECK_IF_STARTED

  Windows::Synch::Semaphore sem(0,1);
  HRESULT hRes = WFS_SUCCESS;

  SynchMsgWnd wnd(dllInstance,sem,hRes,WFS_UNLOCK_COMPLETE);
  wnd.start();

  REQUESTID reqId;
  if ((hRes = WFSAsyncUnlock(hService,wnd.handle(),&reqId)) != WFS_SUCCESS)
    return hRes;

  sem.acquire();

  return hRes;
}

extern "C" HRESULT WINAPI WFSAsyncUnlock(HSERVICE hService, HWND hWnd, LPREQUESTID lpRequestID)
{
  initializeContext();

  GET_LIB_AND_REQUEST

  return lib->call< HRESULT >("WFPUnlock",hService,hWnd,*lpRequestID);
}

extern "C" HRESULT WINAPI WFMSetTraceLevel(HSERVICE hService, DWORD dwTraceLevel)
{
  initializeContext();

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMAllocateBuffer(ULONG ulSize, ULONG, LPVOID *lppvData)
{
  initializeContext();

  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!lppvData)
    return WFS_ERR_INVALID_POINTER;

  *lppvData = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,ulSize);

  if (!*lppvData)
    return WFS_ERR_OUT_OF_MEMORY;

  _ctx->allocMap.emplace(*lppvData,std::list< void * >());

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMAllocateMore(ULONG ulSize, LPVOID lpvOriginal, LPVOID *lppvData)
{
  initializeContext();

  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!lppvData)
    return WFS_ERR_INVALID_POINTER;

  auto it = _ctx->allocMap.find(lpvOriginal);
  
  if (it == _ctx->allocMap.cend())
    return WFS_ERR_INVALID_ADDRESS;

  *lppvData = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,ulSize);

  if (!*lppvData)
    return WFS_ERR_OUT_OF_MEMORY;

  _ctx->allocMap[lpvOriginal].push_back(*lppvData);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMFreeBuffer(LPVOID lpvData)
{
  initializeContext();

  Windows::Synch::Locker< HANDLE > lock(mutexHandle);
  
  if (!lpvData)
    return WFS_ERR_INVALID_POINTER;

  auto it = _ctx->allocMap.find(lpvData);

  if (it == _ctx->allocMap.cend())
    return WFS_ERR_INVALID_BUFFER;

  for (void *p : _ctx->allocMap.at(lpvData))
    HeapFree(GetProcessHeap(),0,p);

  HeapFree(GetProcessHeap(),0,lpvData);

  _ctx->allocMap.erase(it);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMGetTraceLevel(HSERVICE hService, LPDWORD lpdwTraceLevel)
{
  initializeContext();

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMKillTimer(WORD wTimerID)
{
  initializeContext();

  HRESULT hRes = WFS_SUCCESS;
  _ctx->shMem.access([&hRes, wTimerID]  (ShMemLayout *p)
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
  initializeContext();

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMReleaseDLL(HPROVIDER hProvider)
{
  initializeContext();

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMSetTimer(HWND hWnd, LPVOID lpContext, DWORD dwTimeVal, LPWORD lpwTimerID)
{
  initializeContext();

  if (!hWnd)
    return WFS_ERR_INVALID_HWND;

  if (!lpwTimerID)
    return WFS_ERR_INVALID_POINTER;

  if (!dwTimeVal)
    return WFS_ERR_INVALID_DATA;

  HRESULT hRes = WFS_SUCCESS;
  _ctx->shMem.access([&hRes, hWnd, lpContext, dwTimeVal] (ShMemLayout *p)
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
  initializeContext();

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
  initializeContext();

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
  initializeContext();

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
  initializeContext();

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
  initializeContext();

  if (!lpszName || !lpcchName || ((*lpcchName > 0) && !lpszName))
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
  initializeContext();

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
  initializeContext();

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
  initializeContext();

  if (!lpszValueName || !lpcchData || ((*lpcchData > 0) && !lpszData))
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
  initializeContext();

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
      mutexHandle = CreateMutex(NULL,FALSE,L"Local\\XFSPP_XFS_MANAGER_MUTEX");
      break;

    case DLL_PROCESS_DETACH:
      CloseHandle(mutexHandle);
      delete _ctx;
      break;

    default:
      break;
  }

  return TRUE;
}
