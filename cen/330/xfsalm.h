/******************************************************************************
*                                                                             *
* xfsalm.h      XFS – Alarm (ALM) definitions                                 *
*                                                                             *
*               Version 3.30  (March 19 2015)                                 *
*                                                                             *
******************************************************************************/

#ifndef __INC_XFSALM__H
#define __INC_XFSALM__H

#ifdef __cplusplus
extern "C" {
#endif

#include "xfsapi.h"

	/*   be aware of alignment   */
#pragma pack (push, 1)

	/* values of WFSALMCAPS.wClass */

#define     WFS_SERVICE_CLASS_ALM               (11)
#define     WFS_SERVICE_CLASS_VERSION_ALM       0x1E03 /*Version 3.30 */
#define     WFS_SERVICE_CLASS_NAME_ALM          "ALM"

#define     ALM_SERVICE_OFFSET                  (WFS_SERVICE_CLASS_ALM * 100)

	/* ALM Info Commands */

#define     WFS_INF_ALM_STATUS                  (ALM_SERVICE_OFFSET + 1)
#define     WFS_INF_ALM_CAPABILITIES            (ALM_SERVICE_OFFSET + 2)

	/* ALM Execute Commands */

#define     WFS_CMD_ALM_SET_ALARM               (ALM_SERVICE_OFFSET + 1)
#define     WFS_CMD_ALM_RESET_ALARM             (ALM_SERVICE_OFFSET + 2)
#define     WFS_CMD_ALM_RESET                   (ALM_SERVICE_OFFSET + 3)
#define     WFS_CMD_ALM_SYNCHRONIZE_COMMAND     (ALM_SERVICE_OFFSET + 4)

	/* ALM Messages */

#define     WFS_SRVE_ALM_DEVICE_SET             (ALM_SERVICE_OFFSET + 1)
#define     WFS_SRVE_ALM_DEVICE_RESET           (ALM_SERVICE_OFFSET + 2)

	/* values of WFSALMSTATUS.fwDevice */

#define     WFS_ALM_DEVONLINE                   WFS_STAT_DEVONLINE
#define     WFS_ALM_DEVOFFLINE                  WFS_STAT_DEVOFFLINE
#define     WFS_ALM_DEVPOWEROFF                 WFS_STAT_DEVPOWEROFF
#define     WFS_ALM_DEVNODEVICE                 WFS_STAT_DEVNODEVICE
#define     WFS_ALM_DEVHWERROR                  WFS_STAT_DEVHWERROR
#define     WFS_ALM_DEVUSERERROR                WFS_STAT_DEVUSERERROR
#define     WFS_ALM_DEVBUSY                     WFS_STAT_DEVBUSY
#define     WFS_ALM_DEVFRAUDATTEMPT             WFS_STAT_DEVFRAUDATTEMPT
#define     WFS_ALM_DEVPOTENTIALFRAUD           WFS_STAT_DEVPOTENTIALFRAUD

	/* values of WFSALMSTATUS.wAntiFraudModule */

#define     WFS_ALM_AFMNOTSUPP                  (0)
#define     WFS_ALM_AFMOK                       (1)
#define     WFS_ALM_AFMINOP                     (2)
#define     WFS_ALM_AFMDEVICEDETECTED           (3)
#define     WFS_ALM_AFMUNKNOWN                  (4)

	/* XFS ALM Errors */

#define WFS_ERR_ALM_COMMANDUNSUPP               (-(ALM_SERVICE_OFFSET + 0))
#define WFS_ERR_ALM_SYNCHRONIZEUNSUPP           (-(ALM_SERVICE_OFFSET + 1))

	/*=================================================================*/
	/* ALM Info Command Structures */
	/*=================================================================*/

	typedef struct _wfs_alm_status
	{
		WORD                   fwDevice;
		BOOL                   bAlarmSet;
		LPSTR                  lpszExtra;
		WORD                   wAntiFraudModule;
	} WFSALMSTATUS, *LPWFSALMSTATUS;

	typedef struct _wfs_alm_caps
	{
		WORD                   wClass;
		BOOL                   bProgrammaticallyDeactivate;
		LPSTR                  lpszExtra;
		BOOL                   bAntiFraudModule;
		LPDWORD                lpdwSynchronizableCommands;
	} WFSALMCAPS, *LPWFSALMCAPS;

	typedef struct _wfs_alm_synchronize_command
	{
		DWORD                  dwCommand;
		LPVOID                 lpCmdData;
	} WFSALMSYNCHRONIZECOMMAND, *LPWFSALMSYNCHRONIZECOMMAND;

	/*   restore alignment   */
#pragma pack(pop)

#ifdef __cplusplus
}       /*extern "C"*/
#endif
#endif    /* __INC_XFSALM__H */
