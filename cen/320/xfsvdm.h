/******************************************************************************
*                                                                             *
* xfsvdm.h    XFS - Vendor Dependent Mode (VDM) definitions                   *
*                                                                             *
*             Version 3.20  (March 02 2011)                                   *
*                                                                             *
******************************************************************************/

#ifndef __INC_XFSVDM__H
#define __INC_XFSVDM__H

#ifdef __cplusplus
extern "C" {
#endif

#include "xfsapi.h"

/*   be aware of alignment   */
#pragma pack(push,1)

/* values of WFSVDMCAPS.wClass */

#define WFS_SERVICE_CLASS_VDM                   (9)
#define WFS_SERVICE_CLASS_VERSION_VDM           (0x1403) /* Version 3.20 */
#define WFS_SERVICE_CLASS_NAME_VDM              "VDM"

#define VDM_SERVICE_OFFSET                      (WFS_SERVICE_CLASS_VDM * 100)

/* VDM Info Commands */

#define WFS_INF_VDM_STATUS                      (VDM_SERVICE_OFFSET + 1)
#define WFS_INF_VDM_CAPABILITIES                (VDM_SERVICE_OFFSET + 2)
#define WFS_INF_VDM_ACTIVE_INTERFACE            (VDM_SERVICE_OFFSET + 3)

/* VDM Execute Commands */

#define WFS_CMD_VDM_ENTER_MODE_REQ              (VDM_SERVICE_OFFSET + 1)
#define WFS_CMD_VDM_ENTER_MODE_ACK              (VDM_SERVICE_OFFSET + 2)
#define WFS_CMD_VDM_EXIT_MODE_REQ               (VDM_SERVICE_OFFSET + 3)
#define WFS_CMD_VDM_EXIT_MODE_ACK               (VDM_SERVICE_OFFSET + 4)
#define WFS_CMD_VDM_SET_ACTIVE_INTERFACE        (VDM_SERVICE_OFFSET + 5)

/* VDM Messages */

#define WFS_SRVE_VDM_ENTER_MODE_REQ             (VDM_SERVICE_OFFSET + 1)
#define WFS_SRVE_VDM_EXIT_MODE_REQ              (VDM_SERVICE_OFFSET + 2)
#define WFS_SYSE_VDM_MODEENTERED                (VDM_SERVICE_OFFSET + 3)
#define WFS_SYSE_VDM_MODEEXITED                 (VDM_SERVICE_OFFSET + 4)
#define WFS_SRVE_VDM_INTERFACE_CHANGED          (VDM_SERVICE_OFFSET + 5)

/* values of WFSVDMSTATUS.wDevice */

#define WFS_VDM_DEVONLINE                       WFS_STAT_DEVONLINE
#define WFS_VDM_DEVOFFLINE                      WFS_STAT_DEVOFFLINE

/* values of WFSVDMSTATUS.wService */

#define WFS_VDM_ENTERPENDING                    (0)
#define WFS_VDM_ACTIVE                          (1)
#define WFS_VDM_EXITPENDING                     (2)
#define WFS_VDM_INACTIVE                        (3)

/* values of WFSVDMACTIVEINTERFACE.wActiveInterface */

#define WFS_VDM_OPERATOR_INTERFACE              (0)
#define WFS_VDM_CONSUMER_INTERFACE              (1)


/*=================================================================*/
/* VDM Info Command Structures and variables */
/*=================================================================*/

typedef struct _wfs_vdm_appstatus
{
    LPSTR                  lpszAppID;
    WORD                   wAppStatus;
} WFSVDMAPPSTATUS, *LPWFSVDMAPPSTATUS;

typedef struct _wfs_vdm_status
{
     WORD                  wDevice;
     WORD                  wService;
     LPWFSVDMAPPSTATUS    *lppAppStatus;
     LPSTR              lpszExtra;
} WFSVDMSTATUS, *LPWFSVDMSTATUS;

typedef struct _wfs_vdm_caps
{
     WORD                  wClass;
     LPSTR                 lpszExtra;
} WFSVDMCAPS, *LPWFSVDMCAPS;

typedef struct _wfs_vdm_active_interface
{
     WORD                  wActiveInterface;
} WFSVDMACTIVEINTERFACE, *LPWFSVDMACTIVEINTERFACE;

/*=================================================================*/
/* VDM Execute Command Structures */
/*=================================================================*/

/*=================================================================*/
/* VDM Message Structures */
/*=================================================================*/

/*   restore alignment   */
#pragma pack(pop)

#ifdef __cplusplus
}       /*extern "C"*/
#endif
#endif    /* __INC_XFSVDM__H */
