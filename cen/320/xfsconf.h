/******************************************************************************
*                                                                             *
* xfsconf.h     XFS - definitions for the Configuration functions             *
*                                                                             *
*               Version 3.20  (March 02 2011)                                 *
*                                                                             *
******************************************************************************/

#ifndef __INC_XFSCONF__H
#define __INC_XFSCONF__H

#ifdef __cplusplus
extern "C" {
#endif

/******* Common **************************************************************/

#include "xfsapi.h"

/*   be aware of alignment   */
#pragma pack(push,1)

// following HKEY and PHKEY are already defined in WINREG.H
// so definition has been removed
// typedef HANDLE  HKEY;
// typedef HANDLE * PHKEY;

/******* Value of hKey *******************************************************/
#define     WFS_CFG_HKEY_XFS_ROOT               ((HKEY)1)
#define     WFS_CFG_HKEY_MACHINE_XFS_ROOT       ((HKEY)2)
#define     WFS_CFG_HKEY_USER_DEFAULT_XFS_ROOT  ((HKEY)3)

/******* Values of lpdwDisposition *******************************************/
#define     WFS_CFG_CREATED_NEW_KEY             (0)
#define     WFS_CFG_OPENED_EXISTING_KEY         (1)

/******* Configuration Functions *********************************************/
HRESULT extern  WINAPI  WFMCloseKey ( HKEY hKey);

HRESULT extern  WINAPI  WFMCreateKey ( HKEY hKey, LPSTR lpszSubKey, PHKEY phkResult, LPDWORD lpdwDisposition);

HRESULT extern  WINAPI  WFMDeleteKey ( HKEY hKey, LPSTR lpszSubKey);

HRESULT extern  WINAPI  WFMDeleteValue ( HKEY hKey, LPSTR lpszValue );

HRESULT extern  WINAPI  WFMEnumKey ( HKEY hKey, DWORD iSubKey, LPSTR lpszName, LPDWORD lpcchName, PFILETIME lpftLastWrite);

HRESULT extern  WINAPI  WFMEnumValue ( HKEY hKey, DWORD iValue, LPSTR lpszValue, LPDWORD lpcchValue, LPSTR lpszData, LPDWORD lpcchData);

HRESULT extern  WINAPI  WFMOpenKey ( HKEY hKey, LPSTR lpszSubKey, PHKEY phkResult);

HRESULT extern  WINAPI  WFMQueryValue ( HKEY hKey, LPSTR lpszValueName, LPSTR lpszData, LPDWORD lpcchData);

HRESULT extern  WINAPI  WFMSetValue ( HKEY hKey, LPSTR lpszValueName, LPSTR lpszData, DWORD cchData);

/*   restore alignment   */
#pragma pack(pop)

#ifdef __cplusplus
}       /*extern "C"*/
#endif

#endif  /* __INC_XFSCONF__H */
