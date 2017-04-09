#include "xfsapi.h"
#include "xfsadmin.h"
#include "xfsconf.h"

namespace
{
  HINSTANCE dllInstance;
  HANDLE mutexHandle = NULL;
}

extern "C" HRESULT WINAPI WFSCancelAsyncRequest(HSERVICE hService, REQUESTID RequestID)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSCancelBlockingCall(DWORD dwThreadID)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSCleanUp()
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSClose(HSERVICE hService)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSAsyncClose(HSERVICE hService, HWND hWnd, LPREQUESTID lpRequestID)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSCreateAppHandle(LPHAPP lphApp)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSDeregister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSAsyncDeregister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, LPREQUESTID lpRequestID)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSDestroyAppHandle(HAPP hApp)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSExecute(HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, LPWFSRESULT * lppResult)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSAsyncExecute(HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSFreeResult(LPWFSRESULT lpResult)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSGetInfo(HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, LPWFSRESULT * lppResult)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSAsyncGetInfo(HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID)
{
  return WFS_SUCCESS;
}

extern "C" BOOL WINAPI WFSIsBlocking()
{
  return FALSE;
}

extern "C" HRESULT WINAPI WFSLock(HSERVICE hService, DWORD dwTimeOut, LPWFSRESULT * lppResult)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSAsyncLock(HSERVICE hService, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSOpen(LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion, LPWFSVERSION lpSPIVersion, LPHSERVICE lphService)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSAsyncOpen(LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, LPHSERVICE lphService, HWND hWnd, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion, LPWFSVERSION lpSPIVersion, LPREQUESTID lpRequestID)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSRegister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSAsyncRegister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, LPREQUESTID lpRequestID)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSSetBlockingHook(XFSBLOCKINGHOOK lpBlockFunc, LPXFSBLOCKINGHOOK lppPrevFunc)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSStartUp(DWORD dwVersionsRequired, LPWFSVERSION lpWFSVersion)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSUnhookBlockingHook()
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSUnlock(HSERVICE hService)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSAsyncUnlock(HSERVICE hService, HWND hWnd, LPREQUESTID lpRequestID)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMSetTraceLevel(HSERVICE hService, DWORD dwTraceLevel)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMAllocateBuffer(ULONG ulSize, ULONG ulFlags, LPVOID * lppvData)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMAllocateMore(ULONG ulSize, LPVOID lpvOriginal, LPVOID * lppvData)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMFreeBuffer(LPVOID lpvData)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMGetTraceLevel(HSERVICE hService, LPDWORD lpdwTraceLevel)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMKillTimer(WORD wTimerID)
{
  return WFS_SUCCESS;
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
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI  WFMCloseKey(HKEY hKey)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI  WFMCreateKey(HKEY hKey, LPSTR lpszSubKey, PHKEY phkResult, LPDWORD lpdwDisposition)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI  WFMDeleteKey(HKEY hKey, LPSTR lpszSubKey)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI  WFMDeleteValue(HKEY hKey, LPSTR lpszValue)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI  WFMEnumKey(HKEY hKey, DWORD iSubKey, LPSTR lpszName, LPDWORD lpcchName, PFILETIME lpftLastWrite)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI  WFMEnumValue(HKEY hKey, DWORD iValue, LPSTR lpszValue, LPDWORD lpcchValue, LPSTR lpszData, LPDWORD lpcchData)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI  WFMOpenKey(HKEY hKey, LPSTR lpszSubKey, PHKEY phkResult)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI  WFMQueryValue(HKEY hKey, LPSTR lpszValueName, LPSTR lpszData, LPDWORD lpcchData)
{
  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI  WFMSetValue(HKEY hKey, LPSTR lpszValueName, LPSTR lpszData, DWORD cchData)
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
