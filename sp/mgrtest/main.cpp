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
#include "util/memory.hpp"

#include <unordered_map>
#include <unordered_set>
#include <memory>

namespace
{
  Windows::Synch::Mutex m;

  struct Request
  {
    HWND hWnd;
    DWORD timeOut;
  };

  struct Instance
  {
    std::unordered_map< REQUESTID,Request > requests;
  };

  std::unordered_map< HSERVICE,Instance > instances;

  std::unique_ptr< Windows::Library > mgrLib;
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

      mgrLib = std::make_unique< Windows::Library >(p);
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
    /*
    mgrLib->call< HRESULT >(
      "WFMOpenKey",
      WFS_CFG_HKEY_USER_DEFAULT_XFS_ROOT,
      (boost::format("LOGICAL_SERVICES\\%s") % lpszLogicalName).str())
      */
  }
  catch (const Windows::Exception &e)
  {

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
