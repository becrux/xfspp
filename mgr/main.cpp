#include "xfsapi.h"
#include "xfsadmin.h"
#include "xfsconf.h"

#include "win32/synch.hpp"

namespace
{
  HINSTANCE dllInstance;
  HANDLE mutexHandle = NULL;
}

extern "C" HRESULT WINAPI WFSCancelAsyncRequest(HSERVICE hService, REQUESTID RequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSCancelBlockingCall(DWORD dwThreadID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSCleanUp()
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSClose(HSERVICE hService)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSAsyncClose(HSERVICE hService, HWND hWnd, LPREQUESTID lpRequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSCreateAppHandle(LPHAPP lphApp)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSDeregister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSAsyncDeregister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, LPREQUESTID lpRequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSDestroyAppHandle(HAPP hApp)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSExecute(HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, LPWFSRESULT * lppResult)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSAsyncExecute(HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSFreeResult(LPWFSRESULT lpResult)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSGetInfo(HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, LPWFSRESULT * lppResult)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSAsyncGetInfo(HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" BOOL WINAPI WFSIsBlocking()
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return FALSE;
}

extern "C" HRESULT WINAPI WFSLock(HSERVICE hService, DWORD dwTimeOut, LPWFSRESULT * lppResult)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSAsyncLock(HSERVICE hService, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSOpen(LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion, LPWFSVERSION lpSPIVersion, LPHSERVICE lphService)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSAsyncOpen(LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, LPHSERVICE lphService, HWND hWnd, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion, LPWFSVERSION lpSPIVersion, LPREQUESTID lpRequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSRegister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSAsyncRegister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, LPREQUESTID lpRequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSSetBlockingHook(XFSBLOCKINGHOOK lpBlockFunc, LPXFSBLOCKINGHOOK lppPrevFunc)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSStartUp(DWORD dwVersionsRequired, LPWFSVERSION lpWFSVersion)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSUnhookBlockingHook()
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSUnlock(HSERVICE hService)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSAsyncUnlock(HSERVICE hService, HWND hWnd, LPREQUESTID lpRequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMSetTraceLevel(HSERVICE hService, DWORD dwTraceLevel)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMAllocateBuffer(ULONG ulSize, ULONG ulFlags, LPVOID * lppvData)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMAllocateMore(ULONG ulSize, LPVOID lpvOriginal, LPVOID * lppvData)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFMFreeBuffer(LPVOID lpvData)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

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
