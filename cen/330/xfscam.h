/******************************************************************************
*                                                                             *
* xfscam.h      XFS - Camera (CAM) definitions                                *
*                                                                             *
*             Version 3.30  (March 19 2015)                                   *
*                                                                             *
******************************************************************************/

#ifndef __INC_XFSCAM__H
#define __INC_XFSCAM__H

#ifdef __cplusplus
extern "C" {
#endif

#include "xfsapi.h"

	/* be aware of alignment */
#pragma pack (push, 1)

	/* values of WFSCAMCAPS.wClass */

#define     WFS_SERVICE_CLASS_CAM               (10)
#define     WFS_SERVICE_VERSION_CAM             (0x1E03) /* Version 3.30 */
#define     WFS_SERVICE_NAME_CAM                "CAM"

#define     CAM_SERVICE_OFFSET                  (WFS_SERVICE_CLASS_CAM * 100)

	/* CAM Info Commands */

#define     WFS_INF_CAM_STATUS                  (CAM_SERVICE_OFFSET + 1)
#define     WFS_INF_CAM_CAPABILITIES            (CAM_SERVICE_OFFSET + 2)

	/* CAM Execute Commands */

#define     WFS_CMD_CAM_TAKE_PICTURE            (CAM_SERVICE_OFFSET + 1)
#define     WFS_CMD_CAM_RESET                   (CAM_SERVICE_OFFSET + 2)
#define     WFS_CMD_CAM_TAKE_PICTURE_EX         (CAM_SERVICE_OFFSET + 3)
#define     WFS_CMD_CAM_SYNCHRONIZE_COMMAND     (CAM_SERVICE_OFFSET + 4)

	/* CAM Messages */

#define     WFS_USRE_CAM_MEDIATHRESHOLD         (CAM_SERVICE_OFFSET + 1)
#define     WFS_EXEE_CAM_INVALIDDATA            (CAM_SERVICE_OFFSET + 2)

	/* values of WFSCAMSTATUS.fwDevice */

#define     WFS_CAM_DEVONLINE                   WFS_STAT_DEVONLINE
#define     WFS_CAM_DEVOFFLINE                  WFS_STAT_DEVOFFLINE
#define     WFS_CAM_DEVPOWEROFF                 WFS_STAT_DEVPOWEROFF
#define     WFS_CAM_DEVNODEVICE                 WFS_STAT_DEVNODEVICE
#define     WFS_CAM_DEVHWERROR                  WFS_STAT_DEVHWERROR
#define     WFS_CAM_DEVUSERERROR                WFS_STAT_DEVUSERERROR
#define     WFS_CAM_DEVBUSY                     WFS_STAT_DEVBUSY
#define     WFS_CAM_DEVFRAUDATTEMPT             WFS_STAT_DEVFRAUDATTEMPT
#define     WFS_CAM_DEVPOTENTIALFRAUD           WFS_STAT_DEVPOTENTIALFRAUD

	/* number of cameras supported/length of WFSCAMSTATUS.fwCameras field */

#define     WFS_CAM_CAMERAS_SIZE                (8)
#define     WFS_CAM_CAMERAS_MAX                 (WFS_CAM_CAMERAS_SIZE - 1)

	/* indices of WFSCAMSTATUS.fwMedia[...]
	WFSCAMSTATUS.fwCameras [...]
	WFSCAMSTATUS.usPictures[...]
	WFSCAMCAPS.fwCameras [...]
	WFSCAMTAKEPICT.wCamera             */

#define     WFS_CAM_ROOM                        (0)
#define     WFS_CAM_PERSON                      (1)
#define     WFS_CAM_EXITSLOT                    (2)

	/* values of WFSCAMSTATUS.fwMedia */

#define     WFS_CAM_MEDIAOK                     (0)
#define     WFS_CAM_MEDIAHIGH                   (1)
#define     WFS_CAM_MEDIAFULL                   (2)
#define     WFS_CAM_MEDIAUNKNOWN                (3)
#define     WFS_CAM_MEDIANOTSUPP                (4)

	/* values of WFSCAMSTATUS.fwCameras */

#define     WFS_CAM_CAMNOTSUPP                  (0)
#define     WFS_CAM_CAMOK                       (1)
#define     WFS_CAM_CAMINOP                     (2)
#define     WFS_CAM_CAMUNKNOWN                  (3)

	/* values of WFSCAMCAPS.fwType */

#define     WFS_CAM_TYPE_CAM                    (1)

	/* values of WFSCAMCAPS.fwCameras */

#define     WFS_CAM_NOT_AVAILABLE               (0)
#define     WFS_CAM_AVAILABLE                   (1)

	/* values of WFSCAMCAPS.fwCamData */

#define     WFS_CAM_NOTADD                      (0)
#define     WFS_CAM_AUTOADD                     (1)
#define     WFS_CAM_MANADD                      (2)

	/* values of WFSCAMCAPS.fwCharSupport */

#define     WFS_CAM_ASCII                       (0x0001)
#define     WFS_CAM_UNICODE                     (0x0002)

	/* values of WFSCAMSTATUS.wAntiFraudModule */

#define     WFS_CAM_AFMNOTSUPP                  (0)
#define     WFS_CAM_AFMOK                       (1)
#define     WFS_CAM_AFMINOP                     (2)
#define     WFS_CAM_AFMDEVICEDETECTED           (3)
#define     WFS_CAM_AFMUNKNOWN                  (4)

	/* XFS CAM Errors */

#define WFS_ERR_CAM_CAMNOTSUPP                  (-(CAM_SERVICE_OFFSET + 0))
#define WFS_ERR_CAM_MEDIAFULL                   (-(CAM_SERVICE_OFFSET + 1))
#define WFS_ERR_CAM_CAMINOP                     (-(CAM_SERVICE_OFFSET + 2))
#define WFS_ERR_CAM_CHARSETNOTSUPP              (-(CAM_SERVICE_OFFSET + 3))
#define WFS_ERR_CAM_FILEIOERROR                 (-(CAM_SERVICE_OFFSET + 4))
#define WFS_ERR_CAM_COMMANDUNSUPP               (-(CAM_SERVICE_OFFSET + 5))
#define WFS_ERR_CAM_SYNCHRONIZEUNSUPP           (-(CAM_SERVICE_OFFSET + 6))

	/*=================================================================*/
	/* CAM Info Command Structures */
	/*=================================================================*/

	typedef struct _wfs_cam_status
	{
		WORD             fwDevice;
		WORD             fwMedia[WFS_CAM_CAMERAS_SIZE];
		WORD             fwCameras[WFS_CAM_CAMERAS_SIZE];
		USHORT           usPictures[WFS_CAM_CAMERAS_SIZE];
		LPSTR            lpszExtra;
		WORD             wAntiFraudModule;
	} WFSCAMSTATUS, *LPWFSCAMSTATUS;

	typedef struct _wfs_cam_caps
	{
		WORD             wClass;
		WORD             fwType;
		WORD             fwCameras[WFS_CAM_CAMERAS_SIZE];
		USHORT           usMaxPictures;
		WORD             fwCamData;
		USHORT           usMaxDataLength;
		WORD             fwCharSupport;
		LPSTR            lpszExtra;
		BOOL             bPictureFile;
		BOOL             bAntiFraudModule;
		LPDWORD          lpdwSynchronizableCommands;
	} WFSCAMCAPS, *LPWFSCAMCAPS;

	/*=================================================================*/
	/* CAM Execute Command Structures */
	/*=================================================================*/

	typedef struct _wfs_cam_take_picture
	{
		WORD             wCamera;
		LPSTR            lpszCamData;
		LPWSTR           lpszUNICODECamData;
	} WFSCAMTAKEPICT, *LPWFSCAMTAKEPICT;

	typedef struct _wfs_cam_take_picture_ex
	{
		WORD             wCamera;
		LPSTR            lpszCamData;
		LPWSTR           lpszUNICODECamData;
		LPSTR            lpszPictureFile;
	} WFSCAMTAKEPICTEX, *LPWFSCAMTAKEPICTEX;

	typedef struct _wfs_cam_synchronize_command
	{
		DWORD            dwCommand;
		LPVOID           lpCmdData;
	} WFSCAMSYNCHRONIZECOMMAND, *LPWFSCAMSYNCHRONIZECOMMAND;

	/* restore alignment */
#pragma pack (pop)

#ifdef __cplusplus
}       /*extern "C"*/
#endif

#endif  /* __INC_XFSCAM__H */
