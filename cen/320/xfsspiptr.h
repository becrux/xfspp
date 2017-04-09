#ifndef __inc_xfsspiptr__h
#define __inc_xfsspiptr__h

#ifdef __cplusplus
extern "C" {
#endif

typedef HANDLE HPROVIDER;

#include "xfsconf.h"
#include "xfsadmin.h"

/*   be aware of alignment   */
#pragma pack(push,1)

/****** SPI functions ********************************************************/

typedef HRESULT (WINAPI * WFPCancelAsyncRequestFunc)(HSERVICE hService, REQUESTID RequestID);
typedef HRESULT (WINAPI * WFPCloseFunc)(HSERVICE hService, HWND hWnd, REQUESTID ReqID);
typedef HRESULT (WINAPI * WFPDeregisterFunc)(HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, REQUESTID ReqID);
typedef HRESULT (WINAPI * WFPExecuteFunc)(HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID);
typedef HRESULT (WINAPI * WFPGetInfoFunc)(HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID);
typedef HRESULT (WINAPI * WFPLockFunc)(HSERVICE hService, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID);
typedef HRESULT (WINAPI * WFPOpenFunc)(HSERVICE hService, LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID, HPROVIDER hProvider, DWORD dwSPIVersionsRequired, LPWFSVERSION lpSPIVersion, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion);
typedef HRESULT (WINAPI * WFPRegisterFunc)(HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, REQUESTID ReqID);
typedef HRESULT (WINAPI * WFPSetTraceLevelFunc)(HSERVICE hService, DWORD dwTraceLevel);
typedef HRESULT (WINAPI * WFPUnloadServiceFunc)();
typedef HRESULT (WINAPI * WFPUnlockFunc)(HSERVICE hService, HWND hWnd, REQUESTID ReqID);


/*   restore alignment   */
#pragma pack(pop)

#ifdef __cplusplus
}    /*extern "C"*/
#endif

#endif  /* __inc_xfsspi__h */
