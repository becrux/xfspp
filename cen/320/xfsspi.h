/******************************************************************************
*                                                                             *
* xfsspi.h      XFS - SPI functions, types, and definitions                   *
*                                                                             *
*               Version 3.20  (March 02 2011)                                 *
*                                                                             *
******************************************************************************/

#ifndef __inc_xfsspi__h
#define __inc_xfsspi__h

#ifdef __cplusplus
extern "C" {
#endif

#include "xfsapi.h"

typedef HANDLE HPROVIDER;

#include "xfsconf.h"
#include "xfsadmin.h"

/*   be aware of alignment   */
#pragma pack(push,1)

/****** SPI functions ********************************************************/

HRESULT WINAPI WFPCancelAsyncRequest ( HSERVICE hService, REQUESTID RequestID);

HRESULT WINAPI WFPClose ( HSERVICE hService, HWND hWnd, REQUESTID ReqID);

HRESULT WINAPI WFPDeregister ( HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, REQUESTID ReqID);

HRESULT WINAPI WFPExecute ( HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID);

HRESULT WINAPI WFPGetInfo ( HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID);

HRESULT  WINAPI WFPLock ( HSERVICE hService, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID);

HRESULT  WINAPI WFPOpen ( HSERVICE hService, LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID, HPROVIDER hProvider, DWORD dwSPIVersionsRequired, LPWFSVERSION lpSPIVersion, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion);

HRESULT  WINAPI WFPRegister ( HSERVICE hService,  DWORD dwEventClass, HWND hWndReg, HWND hWnd, REQUESTID ReqID);

HRESULT  WINAPI WFPSetTraceLevel ( HSERVICE hService, DWORD dwTraceLevel);

HRESULT  WINAPI WFPUnloadService ( void );

HRESULT  WINAPI WFPUnlock ( HSERVICE hService, HWND hWnd, REQUESTID ReqID);

/*   restore alignment   */
#pragma pack(pop)

#ifdef __cplusplus
}    /*extern "C"*/
#endif

#endif  /* __inc_xfsspi__h */
