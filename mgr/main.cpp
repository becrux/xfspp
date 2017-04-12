/* mgr/main.cpp
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <memory>
#include <sstream>

#include "xfsapi.h"
#include "xfsadmin.h"
#include "xfsconf.h"

#include "win32/synch.hpp"
#include "common/version.hpp"
#include "util/memory.hpp"

#include <shlwapi.h>

#include "sqlite/sqlite3.h"

#define HSERVICE_OFFSET 0
#define HAPP_OFFSET     HSERVICE_OFFSET + sizeof(DWORD)

namespace
{
  HINSTANCE dllInstance;
  HANDLE mutexHandle = NULL;
  HANDLE memMapHandle = NULL;
  bool initialized = false;
  bool firstInstance = false;
  sqlite3 *pDb;
}

extern "C" HRESULT WINAPI WFSCancelAsyncRequest(HSERVICE hService, REQUESTID RequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  return WFS_SUCCESS;
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

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSAsyncClose(HSERVICE hService, HWND hWnd, LPREQUESTID lpRequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSCreateAppHandle(LPHAPP lphApp)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  if (!lphApp)
    return WFS_ERR_INVALID_POINTER;

  sqlite3_stmt *pStmt;
  sqlite3_prepare_v2(pDb,"insert into apps(handle) values(default)",-1,&pStmt,NULL);
  sqlite3_step(pStmt);
  *lphApp = reinterpret_cast< HAPP >(sqlite3_last_insert_rowid(pDb));
  sqlite3_finalize(pStmt);

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSDeregister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSAsyncDeregister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, LPREQUESTID lpRequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSDestroyAppHandle(HAPP hApp)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  sqlite3_stmt *pStmt;
  sqlite3_prepare_v2(pDb,"delete from apps where handle = ?",-1,&pStmt,NULL);
  sqlite3_bind_int(pStmt,1,reinterpret_cast< int >(hApp));
  int res = sqlite3_step(pStmt);
  sqlite3_finalize(pStmt);

  return (res == SQLITE_DONE)? WFS_SUCCESS : WFS_ERR_INVALID_APP_HANDLE;
}

extern "C" HRESULT WINAPI WFSExecute(HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, LPWFSRESULT * lppResult)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSAsyncExecute(HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  return WFS_SUCCESS;
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

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSAsyncGetInfo(HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  return WFS_SUCCESS;
}

extern "C" BOOL WINAPI WFSIsBlocking()
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  return FALSE;
}

extern "C" HRESULT WINAPI WFSLock(HSERVICE hService, DWORD dwTimeOut, LPWFSRESULT * lppResult)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSAsyncLock(HSERVICE hService, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSOpen(LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion, LPWFSVERSION lpSPIVersion, LPHSERVICE lphService)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSAsyncOpen(LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, LPHSERVICE lphService, HWND hWnd, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion, LPWFSVERSION lpSPIVersion, LPREQUESTID lpRequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSRegister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSAsyncRegister(HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, LPREQUESTID lpRequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

  return WFS_SUCCESS;
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

  TCHAR tempPath[MAX_PATH];
  GetTempPath(MAX_PATH,tempPath);

  TCHAR dbFilePath[MAX_PATH];
  PathCombine(dbFilePath,tempPath,L"xfsppmgr.db3");

  if (firstInstance)
  {
    if (!DeleteFile(dbFilePath))
    {
      if (GetLastError() != ERROR_FILE_NOT_FOUND)
        return WFS_ERR_INTERNAL_ERROR;
    }
  }

  if (sqlite3_open16(dbFilePath,&pDb) != SQLITE_OK)
    return WFS_ERR_INTERNAL_ERROR;

  sqlite3_exec(pDb,"pragma synchronous = OFF",NULL,NULL,NULL);

  if (firstInstance)
  {
    if (sqlite3_exec(pDb,
      "create table services(" \
        "hService integer primary key, " \
        "name text not null, " \
        "timestamp integer not null); " \
      "create table apps(" \
        "handle integer primary key);",NULL,NULL,NULL) != SQLITE_OK)
      return WFS_ERR_INTERNAL_ERROR;
  }

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

  return WFS_SUCCESS;
}

extern "C" HRESULT WINAPI WFSAsyncUnlock(HSERVICE hService, HWND hWnd, LPREQUESTID lpRequestID)
{
  Windows::Synch::Locker< HANDLE > lock(mutexHandle);

  if (!initialized)
    return WFS_ERR_NOT_STARTED;

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
      dllInstance = hinstDLL;
      mutexHandle = CreateMutex(NULL,FALSE,L"Global\\XFSPP_XFS_MANAGER_MUTEX");
      memMapHandle = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,0,0,1,L"Global\\XFSPP_XFS_MANAGER");
      firstInstance = GetLastError() != ERROR_ALREADY_EXISTS;
      break;
    
    case DLL_PROCESS_DETACH:
      CloseHandle(mutexHandle);
      CloseHandle(memMapHandle);
      break;
    
    default:
      break;
  }

  return TRUE;
}
