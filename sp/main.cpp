#include "xfsspi.h"

namespace
{
  HINSTANCE dllInstance;
  HANDLE mutexHandle = NULL;
}

extern "C" HRESULT WINAPI WFPCancelAsyncRequest(HSERVICE hService, REQUESTID RequestID)
{
	return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFPClose(HSERVICE hService, HWND hWnd, REQUESTID ReqID)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFPDeregister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, REQUESTID ReqID)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFPExecute(HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFPGetInfo(HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFPLock(HSERVICE hService, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFPOpen(HSERVICE hService, LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID, HPROVIDER hProvider, DWORD dwSPIVersionsRequired, LPWFSVERSION lpSPIVersion, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFPRegister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, REQUESTID ReqID)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFPSetTraceLevel(HSERVICE hService, DWORD dwTraceLevel)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFPUnloadService(void)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFPUnlock(HSERVICE hService, HWND hWnd, REQUESTID ReqID)
{
  return WFS_SUCCESS;
}

extern "C" BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID)
{
  switch (fdwReason)
  {
    case DLL_PROCESS_ATTACH:
      mutexHandle = CreateMutex(NULL,FALSE,NULL);
      /* no break here */
    
    case DLL_THREAD_ATTACH:
      dllInstance = hinstDLL;
      break;
    
    case DLL_PROCESS_DETACH:
      CloseHandle(mutexHandle);
      break;
    
    default:
      break;
  }

  return TRUE;
}
