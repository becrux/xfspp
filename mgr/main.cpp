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
    struct
    {
      REQUESTID reqId;
      Windows::Library *spLib;
    } hServices[32768];

    bool hApps[32768];
  };

  HINSTANCE dllInstance;
  HANDLE mutexHandle = NULL;
  HANDLE memMapHandle = NULL;
  bool initialized = false;
  bool firstInstance = false;
  Windows::SharedMemory shMem(sizeof(ShMemLayout));
  std::map< void *,std::list< void * > > *allocMap = nullptr;
}

extern "C" HRESULT WINAPI WFSCancelAsyncRequest(HSERVICE hService, REQUESTID RequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  if (!hService)
    return WFS_ERR_INVALID_HSERVICE;

  Windows::Library *lib = shMem.access< ShMemLayout >(0).hServices[hService - 1].spLib;
  if (!lib)
    return WFS_ERR_INVALID_HSERVICE;

  return lib->call< HRESULT >("WFPCancelAsyncRequest",hService,RequestID);
}

extern "C" HRESULT WINAPI WFSCancelBlockingCall(DWORD dwThreadID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSCleanUp()
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSClose(HSERVICE hService)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  Windows::Synch::Semaphore sem(0,1);
  HRESULT hRes = WFS_SUCCESS;
  Windows::MsgWnd wnd(dllInstance,[&sem, &hRes] (UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
      if (uMsg == WFS_CLOSE_COMPLETE)
      {
        hRes = reinterpret_cast< LPWFSRESULT >(lParam)->hResult;
        sem.unlock();
      }
    });

  wnd.start();

  REQUESTID reqId;
  if ((hRes = WFSAsyncClose(hService,wnd.handle(),&reqId)) != WFS_SUCCESS)
    return hRes;

  sem.lock();

  return hRes;
}

extern "C" HRESULT WINAPI WFSAsyncClose(HSERVICE hService, HWND hWnd, LPREQUESTID lpRequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  if (!hService)
    return WFS_ERR_INVALID_HSERVICE;

  if (!hWnd)
    return WFS_ERR_INVALID_HWND;

  if (!lpRequestID)
    return WFS_ERR_INVALID_POINTER;

  Windows::Library *lib = nullptr;
  shMem.access(0,[&lib, lpRequestID, hService] (uint8_t *ptr)
    {
      ShMemLayout *p = reinterpret_cast< ShMemLayout * >(ptr);

      if (p->hServices[hService - 1].reqId)
      {
        *lpRequestID = p->hServices[hService - 1].reqId++;
        lib = p->hServices[hService - 1].spLib;
      }
    });

  if (!lib)
    return WFS_ERR_INVALID_HSERVICE;

  return lib->call< HRESULT >("WFPClose",hService,hWnd,*lpRequestID);
}

extern "C" HRESULT WINAPI WFSCreateAppHandle(LPHAPP lphApp)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  if (!lphApp)
    return WFS_ERR_INVALID_POINTER;

  *lphApp = NULL;
  shMem.access(0,[lphApp] (uint8_t *bufPtr)
    {
      ShMemLayout *p = reinterpret_cast< ShMemLayout * >(bufPtr);

      auto it = std::find(std::begin(p->hApps),std::end(p->hApps),false);

      if (it != std::end(p->hApps))
      {
        *lphApp = reinterpret_cast< HAPP >(std::distance(std::begin(p->hApps),it) + 1);
        *it = true;
      }
    });

  return (*lphApp)? WFS_SUCCESS : WFS_ERR_INTERNAL_ERROR;
}

extern "C" HRESULT WINAPI WFSDeregister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  Windows::Synch::Semaphore sem(0,1);
  HRESULT hRes = WFS_SUCCESS;
  Windows::MsgWnd wnd(dllInstance,[&sem, &hRes] (UINT uMsg, WPARAM wParam, LPARAM lParam)
  {
    if (uMsg == WFS_DEREGISTER_COMPLETE)
    {
      hRes = reinterpret_cast< LPWFSRESULT >(lParam)->hResult;
      sem.unlock();
    }
  });

  wnd.start();

  REQUESTID reqId;
  if ((hRes = WFSAsyncDeregister(hService,dwEventClass,hWndReg,wnd.handle(),&reqId)) != WFS_SUCCESS)
    return hRes;

  sem.lock();

  return hRes;
}

extern "C" HRESULT WINAPI WFSAsyncDeregister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, LPREQUESTID lpRequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  if (!hService)
    return WFS_ERR_INVALID_HSERVICE;

  if (!hWndReg)
    return WFS_ERR_INVALID_HWNDREG;

  if (!hWnd)
    return WFS_ERR_INVALID_HWND;

  if (!lpRequestID)
    return WFS_ERR_INVALID_POINTER;

  Windows::Library *lib = nullptr;
  shMem.access(0,[&lib, hService, lpRequestID] (uint8_t *ptr)
  {
    ShMemLayout *p = reinterpret_cast< ShMemLayout * >(ptr);

    if (p->hServices[hService - 1].reqId)
    {
      *lpRequestID = p->hServices[hService - 1].reqId++;
      lib = p->hServices[hService - 1].spLib;
    }
  });

  if (!lib)
    return WFS_ERR_INVALID_HSERVICE;

  return lib->call< HRESULT >("WFPDeregister",hService,dwEventClass,hWndReg,hWnd,*lpRequestID);
}

extern "C" HRESULT WINAPI WFSDestroyAppHandle(HAPP hApp)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  if (!hApp)
    return WFS_ERR_INVALID_APP_HANDLE;

  int idx = (reinterpret_cast< int >(hApp) - 1);
  shMem.access(0,[&idx](uint8_t *bufPtr)
    {
      ShMemLayout *p = reinterpret_cast< ShMemLayout * >(bufPtr);

      if (p->hApps[idx])
      {
        p->hApps[idx] = false;
        idx = 0;
      }
    });

  return (!idx)? WFS_SUCCESS : WFS_ERR_INVALID_APP_HANDLE;
}

extern "C" HRESULT WINAPI WFSExecute(HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, LPWFSRESULT * lppResult)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  Windows::Synch::Semaphore sem(0,1);
  HRESULT hRes = WFS_SUCCESS;
  Windows::MsgWnd wnd(dllInstance,[&sem, &hRes] (UINT uMsg, WPARAM wParam, LPARAM lParam)
  {
    if (uMsg == WFS_EXECUTE_COMPLETE)
    {
      hRes = reinterpret_cast< LPWFSRESULT >(lParam)->hResult;
      sem.unlock();
    }
  });

  wnd.start();

  REQUESTID reqId;
  if ((hRes = WFSAsyncExecute(hService,dwCommand,lpCmdData,dwTimeOut,wnd.handle(),&reqId)) != WFS_SUCCESS)
    return hRes;

  sem.lock();

  return hRes;
}

extern "C" HRESULT WINAPI WFSAsyncExecute(HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  if (!hService)
    return WFS_ERR_INVALID_HSERVICE;

  if (!hWnd)
    return WFS_ERR_INVALID_HWND;

  if (!lpRequestID)
    return WFS_ERR_INVALID_POINTER;

  Windows::Library *lib = nullptr;
  shMem.access(0,[&lib, hService, lpRequestID] (uint8_t *ptr)
  {
    ShMemLayout *p = reinterpret_cast< ShMemLayout * >(ptr);

    if (p->hServices[hService - 1].reqId)
    {
      *lpRequestID = p->hServices[hService - 1].reqId++;
      lib = p->hServices[hService - 1].spLib;
    }
  });

  if (!lib)
    return WFS_ERR_INVALID_HSERVICE;

  return lib->call< HRESULT >("WFPExecute",hService,dwCommand,lpCmdData,dwTimeOut,hWnd,*lpRequestID);
}

extern "C" HRESULT WINAPI WFSFreeResult(LPWFSRESULT lpResult)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSGetInfo(HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, LPWFSRESULT * lppResult)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  Windows::Synch::Semaphore sem(0,1);
  HRESULT hRes = WFS_SUCCESS;
  Windows::MsgWnd wnd(dllInstance,[&sem, &hRes] (UINT uMsg, WPARAM wParam, LPARAM lParam)
  {
    if (uMsg == WFS_GETINFO_COMPLETE)
    {
      hRes = reinterpret_cast< LPWFSRESULT >(lParam)->hResult;
      sem.unlock();
    }
  });

  wnd.start();

  REQUESTID reqId;
  if ((hRes = WFSAsyncGetInfo(hService,dwCategory,lpQueryDetails,dwTimeOut,wnd.handle(),&reqId)) != WFS_SUCCESS)
    return hRes;

  sem.lock();

  return hRes;
}

extern "C" HRESULT WINAPI WFSAsyncGetInfo(HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  if (!hService)
    return WFS_ERR_INVALID_HSERVICE;

  if (!hWnd)
    return WFS_ERR_INVALID_HWND;

  if (!lpRequestID)
    return WFS_ERR_INVALID_POINTER;

  Windows::Library *lib = nullptr;
  shMem.access(0,[&lib, hService, lpRequestID] (uint8_t *ptr)
  {
    ShMemLayout *p = reinterpret_cast< ShMemLayout * >(ptr);

    if (p->hServices[hService - 1].reqId)
    {
      *lpRequestID = p->hServices[hService - 1].reqId++;
      lib = p->hServices[hService - 1].spLib;
    }
  });

  if (!lib)
    return WFS_ERR_INVALID_HSERVICE;

  return lib->call< HRESULT >("WFPGetInfo",hService,dwCategory,lpQueryDetails,dwTimeOut,hWnd,*lpRequestID);
}

extern "C" BOOL WINAPI WFSIsBlocking()
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  return FALSE;
}

extern "C" HRESULT WINAPI WFSLock(HSERVICE hService, DWORD dwTimeOut, LPWFSRESULT *lppResult)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  if (!lppResult)
    return WFS_ERR_INVALID_POINTER;

  Windows::Synch::Semaphore sem(0,1);
  HRESULT hRes = WFS_SUCCESS;
  Windows::MsgWnd wnd(dllInstance,[&sem, &hRes, &lppResult] (UINT uMsg, WPARAM wParam, LPARAM lParam)
  {
    if (uMsg == WFS_LOCK_COMPLETE)
    {
      *lppResult = reinterpret_cast< LPWFSRESULT >(lParam);
      hRes = reinterpret_cast< LPWFSRESULT >(lParam)->hResult;
      sem.unlock();
    }
  });

  wnd.start();

  REQUESTID reqId;
  if ((hRes = WFSAsyncLock(hService,dwTimeOut,wnd.handle(),&reqId)) != WFS_SUCCESS)
    return hRes;

  sem.lock();

  return hRes;
}

extern "C" HRESULT WINAPI WFSAsyncLock(HSERVICE hService, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  if (!hService)
    return WFS_ERR_INVALID_HSERVICE;

  if (!hWnd)
    return WFS_ERR_INVALID_HWND;

  if (!lpRequestID)
    return WFS_ERR_INVALID_POINTER;

  Windows::Library *lib = nullptr;
  shMem.access(0,[&lib, hService, lpRequestID] (uint8_t *ptr)
  {
    ShMemLayout *p = reinterpret_cast< ShMemLayout * >(ptr);

    if (p->hServices[hService - 1].reqId)
    {
      *lpRequestID = p->hServices[hService - 1].reqId++;
      lib = p->hServices[hService - 1].spLib;
    }
  });

  if (!lib)
    return WFS_ERR_INVALID_HSERVICE;

  return lib->call< HRESULT >("WFPLock",hService,dwTimeOut,hWnd,*lpRequestID);
}

extern "C" HRESULT WINAPI WFSOpen(LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion, LPWFSVERSION lpSPIVersion, LPHSERVICE lphService)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  Windows::Synch::Semaphore sem(0,1);
  HRESULT hRes = WFS_SUCCESS;
  Windows::MsgWnd wnd(dllInstance,[&sem, &hRes] (UINT uMsg, WPARAM wParam, LPARAM lParam)
  {
    if (uMsg == WFS_OPEN_COMPLETE)
    {
      hRes = reinterpret_cast< LPWFSRESULT >(lParam)->hResult;
      sem.unlock();
    }
  });

  wnd.start();

  REQUESTID reqId;
  if ((hRes = WFSAsyncOpen(lpszLogicalName,hApp,lpszAppID,dwTraceLevel,dwTimeOut,lphService,wnd.handle(),dwSrvcVersionsRequired,lpSrvcVersion,lpSPIVersion,&reqId)) != WFS_SUCCESS)
    return hRes;

  sem.lock();

  return hRes;
}

extern "C" HRESULT WINAPI WFSAsyncOpen(LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, LPHSERVICE lphService, HWND hWnd, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion, LPWFSVERSION lpSPIVersion, LPREQUESTID lpRequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  if (!hApp)
    return WFS_ERR_INVALID_APP_HANDLE;

  if (!lpszLogicalName || !lpszAppID || !lphService || !lpSrvcVersion || !lpSPIVersion || !lpRequestID)
    return WFS_ERR_INVALID_POINTER;

  HRESULT res = WFS_SUCCESS;
  int idx = 0;
  *lphService = 0;
  *lpRequestID = 0;
  clearMem(*lpSPIVersion);
  clearMem(*lpSrvcVersion);

  shMem.access(0,[&res, &idx, hApp, lpRequestID, lphService] (uint8_t *ptr)
    {
      ShMemLayout *p = reinterpret_cast< ShMemLayout * >(ptr);

      if (!p->hApps[reinterpret_cast<int>(hApp) - 1])
      {
        res = WFS_ERR_INVALID_APP_HANDLE;
        return;
      }

      auto it = std::find_if(std::begin(p->hServices),std::end(p->hServices),[] (const auto &x) { return x.reqId == 0; });
      if (it == std::end(p->hServices))
      {
        res = WFS_ERR_INTERNAL_ERROR;
        return;
      }

      it->reqId = 1;
      it->spLib = new Windows::Library(L"sp.dll");
      *lpRequestID = 1;
      *lphService = static_cast< HSERVICE >(std::distance(std::begin(p->hServices),it) + 1);
    });

  if (res != WFS_SUCCESS)
    return res;

  Windows::Library *lib = shMem.access< ShMemLayout >(0).hServices[idx].spLib;

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
    XFS::VersionRange(XFS::Version(3,0),XFS::Version(3,30)).value(),
    lpSrvcVersion);
}

extern "C" HRESULT WINAPI WFSRegister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  Windows::Synch::Semaphore sem(0,1);
  HRESULT hRes = WFS_SUCCESS;
  Windows::MsgWnd wnd(dllInstance,[&sem, &hRes] (UINT uMsg, WPARAM wParam, LPARAM lParam)
  {
    if (uMsg == WFS_REGISTER_COMPLETE)
    {
      hRes = reinterpret_cast< LPWFSRESULT >(lParam)->hResult;
      sem.unlock();
    }
  });

  wnd.start();

  REQUESTID reqId;
  if ((hRes = WFSAsyncRegister(hService,dwEventClass,hWndReg,wnd.handle(),&reqId)) != WFS_SUCCESS)
    return hRes;

  sem.lock();

  return hRes;
}

extern "C" HRESULT WINAPI WFSAsyncRegister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, LPREQUESTID lpRequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  if (!hService)
    return WFS_ERR_INVALID_HSERVICE;

  if (!hWnd)
    return WFS_ERR_INVALID_HWND;

  if (!hWndReg)
    return WFS_ERR_INVALID_HWNDREG;

  if (!lpRequestID)
    return WFS_ERR_INVALID_POINTER;

  Windows::Library *lib = nullptr;
  shMem.access(0,[&lib, hService, lpRequestID] (uint8_t *ptr)
  {
    ShMemLayout *p = reinterpret_cast< ShMemLayout * >(ptr);

    if (p->hServices[hService - 1].reqId)
    {
      *lpRequestID = p->hServices[hService - 1].reqId++;
      lib = p->hServices[hService - 1].spLib;
    }
  });

  if (!lib)
    return WFS_ERR_INVALID_HSERVICE;

  return lib->call< HRESULT >("WFPRegister",hService,dwEventClass,hWndReg,hWnd,*lpRequestID);
}

extern "C" HRESULT WINAPI WFSSetBlockingHook(XFSBLOCKINGHOOK lpBlockFunc, LPXFSBLOCKINGHOOK lppPrevFunc)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSStartUp(DWORD dwVersionsRequired, LPWFSVERSION lpWFSVersion)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  XFS::VersionRange vr(dwVersionsRequired);

  if (vr.start() > vr.end())
    return WFS_ERR_INTERNAL_ERROR;

  if (vr.start() > XFS::Version(3,20))
    return WFS_ERR_API_VER_TOO_HIGH;

  if (vr.end() < XFS::Version(3,20))
    return WFS_ERR_API_VER_TOO_LOW;

  if (!lpWFSVersion)
    return WFS_ERR_INVALID_POINTER;

  if (initialized)
    return WFS_ERR_ALREADY_STARTED;

  clearMem(*lpWFSVersion);

  lpWFSVersion->wVersion = XFS::Version(3,20).value();
  lpWFSVersion->wLowVersion = XFS::Version::min(3).value();
  lpWFSVersion->wHighVersion = XFS::Version::max(3).value();
  lpWFSVersion->szSystemStatus[0] = '\0';
  strcpy_s(lpWFSVersion->szDescription,"xfspp XFS Manager");

  initialized = true;

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSUnhookBlockingHook()
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSUnlock(HSERVICE hService)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  Windows::Synch::Semaphore sem(0,1);
  HRESULT hRes = WFS_SUCCESS;
  Windows::MsgWnd wnd(dllInstance,[&sem, &hRes] (UINT uMsg, WPARAM wParam, LPARAM lParam)
  {
    if (uMsg == WFS_UNLOCK_COMPLETE)
    {
      hRes = reinterpret_cast< LPWFSRESULT >(lParam)->hResult;
      sem.unlock();
    }
  });

  wnd.start();

  REQUESTID reqId;
  if ((hRes = WFSAsyncUnlock(hService,wnd.handle(),&reqId)) != WFS_SUCCESS)
    return hRes;

  sem.lock();

  return hRes;
}

extern "C" HRESULT WINAPI WFSAsyncUnlock(HSERVICE hService, HWND hWnd, LPREQUESTID lpRequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  if (!hService)
    return WFS_ERR_INVALID_HSERVICE;

  if (!hWnd)
    return WFS_ERR_INVALID_HWND;

  if (!lpRequestID)
    return WFS_ERR_INVALID_POINTER;

  Windows::Library *lib = nullptr;
  shMem.access(0,[&lib, hService, lpRequestID] (uint8_t *ptr)
  {
    ShMemLayout *p = reinterpret_cast< ShMemLayout * >(ptr);

    if (p->hServices[hService - 1].reqId)
    {
      *lpRequestID = p->hServices[hService - 1].reqId++;
      lib = p->hServices[hService - 1].spLib;
    }
  });

  if (!lib)
    return WFS_ERR_INVALID_HSERVICE;

  return lib->call< HRESULT >("WFPUnlock",hService,hWnd,*lpRequestID);
}

extern "C" HRESULT WINAPI WFMSetTraceLevel(HSERVICE hService, DWORD dwTraceLevel)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMAllocateBuffer(ULONG ulSize, ULONG ulFlags, LPVOID *lppvData)
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
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMKillTimer(WORD wTimerID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMOutputTraceData(LPSTR lpszData)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMReleaseDLL(HPROVIDER hProvider)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMSetTimer(HWND hWnd, LPVOID lpContext, DWORD dwTimeVal, LPWORD lpwTimerID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI  WFMCloseKey(HKEY hKey)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI  WFMCreateKey(HKEY hKey, LPSTR lpszSubKey, PHKEY phkResult, LPDWORD lpdwDisposition)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI  WFMDeleteKey(HKEY hKey, LPSTR lpszSubKey)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI  WFMDeleteValue(HKEY hKey, LPSTR lpszValue)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI  WFMEnumKey(HKEY hKey, DWORD iSubKey, LPSTR lpszName, LPDWORD lpcchName, PFILETIME lpftLastWrite)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI  WFMEnumValue(HKEY hKey, DWORD iValue, LPSTR lpszValue, LPDWORD lpcchValue, LPSTR lpszData, LPDWORD lpcchData)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI  WFMOpenKey(HKEY hKey, LPSTR lpszSubKey, PHKEY phkResult)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI  WFMQueryValue(HKEY hKey, LPSTR lpszValueName, LPSTR lpszData, LPDWORD lpcchData)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI  WFMSetValue(HKEY hKey, LPSTR lpszValueName, LPSTR lpszData, DWORD cchData)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
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
      CloseHandle(memMapHandle);
      delete allocMap;
      break;
    
    default:
      break;
  }

  return TRUE;
}
