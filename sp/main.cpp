/* sp/main.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include "xfsspi.h"

#include "win32/synch.hpp"

namespace
{
  HINSTANCE dllInstance;
  HANDLE mutexHandle = NULL;

  struct Context
  {
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
}

extern "C" HRESULT WINAPI WFPCancelAsyncRequest(HSERVICE hService, REQUESTID RequestID)
{
  initializeContext();

  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFPClose(HSERVICE hService, HWND hWnd, REQUESTID ReqID)
{
  initializeContext();

  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFPDeregister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, REQUESTID ReqID)
{
  initializeContext();

  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFPExecute(HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID)
{
  initializeContext();

  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFPGetInfo(HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID)
{
  initializeContext();

  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFPLock(HSERVICE hService, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID)
{
  initializeContext();

  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFPOpen(HSERVICE hService, LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID, HPROVIDER hProvider, DWORD dwSPIVersionsRequired, LPWFSVERSION lpSPIVersion, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion)
{
  initializeContext();

  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFPRegister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, REQUESTID ReqID)
{
  initializeContext();

  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFPSetTraceLevel(HSERVICE hService, DWORD dwTraceLevel)
{
  initializeContext();

  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFPUnloadService(void)
{
  initializeContext();

  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFPUnlock(HSERVICE hService, HWND hWnd, REQUESTID ReqID)
{
  initializeContext();

  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID)
{
  switch (fdwReason)
  {
    case DLL_PROCESS_ATTACH:
      dllInstance = hinstDLL;
      mutexHandle = CreateMutex(NULL,FALSE,NULL);
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
