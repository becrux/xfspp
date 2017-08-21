/* sp/test/main.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "cen/320/xfsspi.h"
#include "win32/synch.hpp"
#include "win32/registry.hpp"
#include "win32/library.hpp"
#include "win32/thread.hpp"
#include "util/memory.hpp"
#include "fmt/format.h"
#include "xfs/registry.hpp"
#include "xfs/exception.hpp"
#include "xfs/version.hpp"
#include "sp/mgrtest/mgrtest.h"

#include <map>
#include <unordered_set>
#include <memory>
#include <utility>

namespace
{
  Windows::Synch::Mutex m;

  struct Request
  {
    HWND hWnd;
    DWORD timeOut;
    // Windows::Thread thread;

    explicit Request(HWND h, DWORD t, std::function< void () > f) :
      hWnd(h), timeOut(t)/* , thread(f) */ { }
  };

  std::map< HSERVICE,std::map< REQUESTID,Request > > instances;

  std::shared_ptr< Windows::Library > mgrLib;
}

HRESULT WINAPI WFPCancelAsyncRequest(HSERVICE hService, REQUESTID RequestID)
{
	Windows::Synch::Locker< Windows::Synch::Mutex > lck(m);

  return WFS_SUCCESS;
}

HRESULT WINAPI WFPClose(HSERVICE hService, HWND hWnd, REQUESTID ReqID)
{
  Windows::Synch::Locker< Windows::Synch::Mutex > lck(m);

  return WFS_SUCCESS;
}

HRESULT WINAPI WFPDeregister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, REQUESTID ReqID)
{
  Windows::Synch::Locker< Windows::Synch::Mutex > lck(m);

  return WFS_SUCCESS;
}

HRESULT WINAPI WFPExecute(HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID)
{
  Windows::Synch::Locker< Windows::Synch::Mutex > lck(m);

  return WFS_SUCCESS;
}

HRESULT WINAPI WFPGetInfo(HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID)
{
  Windows::Synch::Locker< Windows::Synch::Mutex > lck(m);

  return WFS_SUCCESS;
}

HRESULT WINAPI WFPLock(HSERVICE hService, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID)
{
  Windows::Synch::Locker< Windows::Synch::Mutex > lck(m);

  return WFS_SUCCESS;
}

HRESULT WINAPI WFPOpen(HSERVICE hService, LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID, HPROVIDER hProvider, DWORD dwSPIVersionsRequired, LPWFSVERSION lpSPIVersion, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion)
{
  Windows::Synch::Locker< Windows::Synch::Mutex > lck(m);

  if (!mgrLib)
    try
    {
      Windows::Registry::Key k(L"Software\\XFS\\XFS_MANAGER",false);

      std::wstring p = k.value(L"dllName",L"msxfs.dll");

      mgrLib = std::make_shared< Windows::Library >(p);
    }
    catch (const Windows::Exception &e)
    {
      return WFS_ERR_INTERNAL_ERROR;
    }

  if (!lpszLogicalName ||
      !lpSPIVersion ||
      !lpSrvcVersion)
    return WFS_ERR_INVALID_POINTER;

  clearMem(*lpSPIVersion);
  clearMem(*lpSrvcVersion);

  try
  {
    XFS::Registry::Key key(fmt::format("LOGICAL_SERVICES\\{}",lpszLogicalName),mgrLib);
    if (key.value("class") != WFS_SERVICE_CLASS_NAME_MGR_TEST)
      return WFS_ERR_INVALID_SERVPROV;

    XFS::Version currentVersion(WFS_SERVICE_CLASS_VERSION_MGR_TEST);

    lpSPIVersion->wLowVersion = 
      lpSPIVersion->wHighVersion = currentVersion.value();

    XFS::VersionRange versionRange(dwSPIVersionsRequired);

    if (currentVersion < versionRange.start())
    {
      lpSPIVersion->wVersion = 0;
      return WFS_ERR_SPI_VER_TOO_LOW;
    }
    else if (currentVersion > versionRange.end())
    {
      lpSPIVersion->wVersion = 0;
      return WFS_ERR_SPI_VER_TOO_HIGH;
    }
    else
      lpSPIVersion->wVersion = currentVersion.value();

    lpSrvcVersion->wVersion = currentVersion.value();
    lpSrvcVersion->szSystemStatus[0] = '\0';
    lpSrvcVersion->szDescription[0] = '\0';

    auto &inMap = instances[hService];
    inMap.emplace(ReqID,Request(hWnd,dwTimeOut,
      [hWnd, dwTimeOut] () -> void
        {
          SleepEx(1000,FALSE);
          PostMessage(hWnd,WFS_OPEN_COMPLETE,NULL,NULL);
        }));

    return WFS_SUCCESS;
  }
  catch (XFS::Exception &e)
  {
    return WFS_ERR_INVALID_SERVPROV;
  }

  return WFS_SUCCESS;
}

HRESULT WINAPI WFPRegister(HSERVICE hService,  DWORD dwEventClass, HWND hWndReg, HWND hWnd, REQUESTID ReqID)
{
  Windows::Synch::Locker< Windows::Synch::Mutex > lck(m);

  return WFS_SUCCESS;
}

HRESULT WINAPI WFPSetTraceLevel(HSERVICE hService, DWORD dwTraceLevel)
{
  Windows::Synch::Locker< Windows::Synch::Mutex > lck(m);

  return WFS_SUCCESS;
}

HRESULT WINAPI WFPUnloadService(void)
{
  Windows::Synch::Locker< Windows::Synch::Mutex > lck(m);

  return WFS_SUCCESS;
}

HRESULT WINAPI WFPUnlock(HSERVICE hService, HWND hWnd, REQUESTID ReqID)
{
  Windows::Synch::Locker< Windows::Synch::Mutex > lck(m);

  return WFS_SUCCESS;
}

extern "C" BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID)
{
  switch (fdwReason)
  {
    case DLL_PROCESS_ATTACH:
      break;

    case DLL_PROCESS_DETACH:
      break;

    default:
      break;
  }

  return TRUE;
}
