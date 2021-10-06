/******************************************************************************
*                                                                             *
* xfscrd.h    XFS - Card Dispenser (CRD) definitions                          *
*                                                                             *
*             Version 3.20  (March 02 2011)                                   *
*                                                                             *
******************************************************************************/

#ifndef __INC_XFSCRD__H
#define __INC_XFSCRD__H

#ifdef __cplusplus
extern "C" {
#endif

#include "xfsapi.h"

/*   be aware of alignment   */
#pragma pack(push,1)

/* values of WFSCRDCAPS.wClass */

#define     WFS_SERVICE_CLASS_CRD               (14)
#define     WFS_SERVICE_CLASS_VERSION_CRD       (0x1403) /* Version 3.20 */
#define     WFS_SERVICE_CLASS_NAME_CRD          "CRD"

#define     CRD_SERVICE_OFFSET                  (WFS_SERVICE_CLASS_CRD * 100)

/* CRD Info Commands */

#define     WFS_INF_CRD_STATUS                  (CRD_SERVICE_OFFSET + 1)
#define     WFS_INF_CRD_CAPABILITIES            (CRD_SERVICE_OFFSET + 2)
#define     WFS_INF_CRD_CARD_UNIT_INFO          (CRD_SERVICE_OFFSET + 3)

/* CRD Execute Commands */

#define     WFS_CMD_CRD_DISPENSE_CARD           (CRD_SERVICE_OFFSET + 1)
#define     WFS_CMD_CRD_EJECT_CARD              (CRD_SERVICE_OFFSET + 2)
#define     WFS_CMD_CRD_RETAIN_CARD             (CRD_SERVICE_OFFSET + 3)
#define     WFS_CMD_CRD_RESET                   (CRD_SERVICE_OFFSET + 4)
#define     WFS_CMD_CRD_SET_GUIDANCE_LIGHT      (CRD_SERVICE_OFFSET + 5)
#define     WFS_CMD_CRD_SET_CARD_UNIT_INFO      (CRD_SERVICE_OFFSET + 6)
#define     WFS_CMD_CRD_POWER_SAVE_CONTROL      (CRD_SERVICE_OFFSET + 7)

/* CRD Events  */

#define     WFS_SRVE_CRD_MEDIAREMOVED           (CRD_SERVICE_OFFSET + 1)
#define     WFS_SRVE_CRD_CARDUNITINFOCHANGED    (CRD_SERVICE_OFFSET + 2)
#define     WFS_SRVE_CRD_MEDIADETECTED          (CRD_SERVICE_OFFSET + 3)
#define     WFS_USRE_CRD_CARDUNITTHRESHOLD      (CRD_SERVICE_OFFSET + 4)
#define     WFS_EXEE_CRD_CARDUNITERROR          (CRD_SERVICE_OFFSET + 5)
#define     WFS_SRVE_CRD_DEVICEPOSITION         (CRD_SERVICE_OFFSET + 6)
#define     WFS_SRVE_CRD_POWER_SAVE_CHANGE      (CRD_SERVICE_OFFSET + 7)

/* values of WFSCRDSTATUS.fwDevice */

#define     WFS_CRD_DEVONLINE                   WFS_STAT_DEVONLINE
#define     WFS_CRD_DEVOFFLINE                  WFS_STAT_DEVOFFLINE
#define     WFS_CRD_DEVPOWEROFF                 WFS_STAT_DEVPOWEROFF
#define     WFS_CRD_DEVNODEVICE                 WFS_STAT_DEVNODEVICE
#define     WFS_CRD_DEVHWERROR                  WFS_STAT_DEVHWERROR
#define     WFS_CRD_DEVUSERERROR                WFS_STAT_DEVUSERERROR
#define     WFS_CRD_DEVBUSY                     WFS_STAT_DEVBUSY
#define     WFS_CRD_DEVFRAUDATTEMPT             WFS_STAT_DEVFRAUDATTEMPT
#define     WFS_CRD_DEVPOTENTIALFRAUD           WFS_STAT_DEVPOTENTIALFRAUD

/* values of WFSCRDSTATUS.fwDispenser */

#define     WFS_CRD_DISPCUOK                    (0)
#define     WFS_CRD_DISPCUSTATE                 (1)
#define     WFS_CRD_DISPCUSTOP                  (2)
#define     WFS_CRD_DISPCUUNKNOWN               (3)

/* values of WFSCRDSTATUS.fwMedia,
             WFSCRDRETAINCARD.fwPosition, and
             WFSCRDMEDIADETECTED.wPosition */

#define     WFS_CRD_MEDIAPRESENT                (1)
#define     WFS_CRD_MEDIANOTPRESENT             (2)
#define     WFS_CRD_MEDIAJAMMED                 (3)
#define     WFS_CRD_MEDIANOTSUPP                (4)
#define     WFS_CRD_MEDIAUNKNOWN                (5)
#define     WFS_CRD_MEDIAEXITING                (6)
#define     WFS_CRD_MEDIARETAINED               (7)

/* values of WFSCRDSTATUS.fwTransport */

#define     WFS_CRD_TPOK                        (0)
#define     WFS_CRD_TPINOP                      (1)
#define     WFS_CRD_TPUNKNOWN                   (2)
#define     WFS_CRD_TPNOTSUPPORTED              (3)

/* Size and max index of dwGuidLights array */

#define     WFS_CRD_GUIDLIGHTS_SIZE             (32)
#define     WFS_CRD_GUIDLIGHTS_MAX              (WFS_CRD_GUIDLIGHTS_SIZE - 1)

/* Indices of WFSCRDSTATUS.dwGuidLights [...]
              WFSCRDCAPS.dwGuidLights [...] */

#define     WFS_CRD_GUIDANCE_CARDDISP           (0)

/* Values of WFSCRDSTATUS.dwGuidLights [...]
             WFSCRDCAPS.dwGuidLights [...] */

#define     WFS_CRD_GUIDANCE_NOT_AVAILABLE      (0x00000000)
#define     WFS_CRD_GUIDANCE_OFF                (0x00000001)
#define     WFS_CRD_GUIDANCE_SLOW_FLASH         (0x00000004)
#define     WFS_CRD_GUIDANCE_MEDIUM_FLASH       (0x00000008)
#define     WFS_CRD_GUIDANCE_QUICK_FLASH        (0x00000010)
#define     WFS_CRD_GUIDANCE_CONTINUOUS         (0x00000080)
#define     WFS_CRD_GUIDANCE_RED                (0x00000100)
#define     WFS_CRD_GUIDANCE_GREEN              (0x00000200)
#define     WFS_CRD_GUIDANCE_YELLOW             (0x00000400)
#define     WFS_CRD_GUIDANCE_BLUE               (0x00000800)
#define     WFS_CRD_GUIDANCE_CYAN               (0x00001000)
#define     WFS_CRD_GUIDANCE_MAGENTA            (0x00002000)
#define     WFS_CRD_GUIDANCE_WHITE              (0x00004000)

/* values of WFSCRDSTATUS.wDevicePosition
             WFSCRDDEVICEPOSITION.wPosition */

#define     WFS_CRD_DEVICEINPOSITION            (0)
#define     WFS_CRD_DEVICENOTINPOSITION         (1)
#define     WFS_CRD_DEVICEPOSUNKNOWN            (2)
#define     WFS_CRD_DEVICEPOSNOTSUPP            (3)

/*values of WFSCRDCAPS.fwDispenseTo */

#define     WFS_CRD_DISPTO_CONSUMER             (0x0001)
#define     WFS_CRD_DISPTO_TRANSPORT            (0x0002)

/*values of WFSCRDCARDUNIT.usStatus */

#define    WFS_CRD_STATCUOK                     (0)
#define    WFS_CRD_STATCULOW                    (1)
#define    WFS_CRD_STATCUEMPTY                  (2)
#define    WFS_CRD_STATCUINOP                   (3)
#define    WFS_CRD_STATCUMISSING                (4)
#define    WFS_CRD_STATCUHIGH                   (5)
#define    WFS_CRD_STATCUFULL                   (6)
#define    WFS_CRD_STATCUUNKNOWN                (7)

/*values of WFSCRDCARDUNIT.usType */

#define    WFS_CRD_SUPPLYBIN                    (1)
#define    WFS_CRD_RETAINBIN                    (2)

/* values of WFSCRDSTATUS.fwShutter */

#define     WFS_CRD_SHTCLOSED                   (0)
#define     WFS_CRD_SHTOPEN                     (1)
#define     WFS_CRD_SHTJAMMED                   (2)
#define     WFS_CRD_SHTUNKNOWN                  (3)
#define     WFS_CRD_SHTNOTSUPPORTED             (4)

/* values of WFSCRDCAPS.fwPowerOnOption,
             WFSCRDCAPS.fwPowerOffOption,
             WFSCRDRESET.usAction  */

#define     WFS_CRD_NOACTION                    (1)
#define     WFS_CRD_EJECT                       (2)
#define     WFS_CRD_RETAIN                      (3)
#define     WFS_CRD_EJECTTHENRETAIN             (4)

/*values of WFSCRDCUERROR.wFailure */

#define WFS_CRD_CARDUNITEMPTY                   (1)
#define WFS_CRD_CARDUNITERROR                   (2)
#define WFS_CRD_CARDUNITINVALID                 (3)

/* values of WFSCRDSTATUS.wAntiFraudModule */

#define     WFS_CRD_AFMNOTSUPP                  (0)
#define     WFS_CRD_AFMOK                       (1)
#define     WFS_CRD_AFMINOP                     (2)
#define     WFS_CRD_AFMDEVICEDETECTED           (3)
#define     WFS_CRD_AFMUNKNOWN                  (4)

/* XFS CRD Errors */

#define WFS_ERR_CRD_MEDIAJAM                    (-(CRD_SERVICE_OFFSET + 0))
#define WFS_ERR_CRD_NOMEDIA                     (-(CRD_SERVICE_OFFSET + 1))
#define WFS_ERR_CRD_MEDIARETAINED               (-(CRD_SERVICE_OFFSET + 2))
#define WFS_ERR_CRD_RETAINBINFULL               (-(CRD_SERVICE_OFFSET + 3))
#define WFS_ERR_CRD_SHUTTERFAIL                 (-(CRD_SERVICE_OFFSET + 4))
#define WFS_ERR_CRD_DEVICE_OCCUPIED             (-(CRD_SERVICE_OFFSET + 5))
#define WFS_ERR_CRD_CARDUNITERROR               (-(CRD_SERVICE_OFFSET + 6))
#define WFS_ERR_CRD_INVALIDCARDUNIT             (-(CRD_SERVICE_OFFSET + 7))
#define WFS_ERR_CRD_INVALID_PORT                (-(CRD_SERVICE_OFFSET + 8))
#define WFS_ERR_CRD_INVALIDRETAINBIN            (-(CRD_SERVICE_OFFSET + 9))
#define WFS_ERR_CRD_POWERSAVETOOSHORT           (-(CRD_SERVICE_OFFSET + 10))
#define WFS_ERR_CRD_POWERSAVEMEDIAPRESENT       (-(CRD_SERVICE_OFFSET + 11))

/*=================================================================*/
/* CRD Info Command Structures and variables */
/*=================================================================*/

typedef struct _wfs_crd_status
{
    WORD             fwDevice;
    WORD             fwDispenser;
    WORD             fwTransport;
    WORD             fwMedia;
    WORD             fwShutter;
    LPSTR            lpszExtra;
    DWORD            dwGuidLights[WFS_CRD_GUIDLIGHTS_SIZE];
    WORD             wDevicePosition;
    USHORT           usPowerSaveRecoveryTime;
    WORD             wAntiFraudModule;
} WFSCRDSTATUS, *LPWFSCRDSTATUS;

typedef struct _wfs_crd_caps
{
    WORD             wClass;
    BOOL             bCompound;
    WORD             fwPowerOnOption;
    WORD             fwPowerOffOption;
    BOOL             bCardTakenSensor;
    WORD             fwDispenseTo;
    LPSTR            lpszExtra;
    DWORD            dwGuidLights[WFS_CRD_GUIDLIGHTS_SIZE];
    BOOL             bPowerSaveControl;
    BOOL             bAntiFraudModule;

} WFSCRDCAPS, *LPWFSCRDCAPS;

typedef struct _wfs_crd_cardunit
{
    USHORT           usNumber;
    LPSTR            lpszCardName;
    USHORT           usType;
    ULONG            ulInitialCount;
    ULONG            ulCount;
    ULONG            ulRetainCount;
    ULONG            ulThreshold;
    USHORT           usStatus;
    BOOL             bHardwareSensor;
} WFSCRDCARDUNIT, *LPWFSCRDCARDUNIT;

typedef struct _wfs_crd_cu_info
{
    USHORT           usCount;
    LPWFSCRDCARDUNIT *lppList;
} WFSCRDCUINFO, *LPWFSCRDCUINFO;

/*=================================================================*/
/* CRD Execute Command Structures */
/*=================================================================*/

typedef struct _wfs_crd_dispense
{
    USHORT           usNumber;
    BOOL             bPresent;
} WFSCRDDISPENSE, *LPWFSCRDDISPENSE;

typedef struct _wfs_crd_retain_card
{
    USHORT           usNumber;
} WFSCRDRETAINCARD, *LPWFSCRDRETAINCARD;

typedef struct _wfs_crd_reset
{
    USHORT           usAction;
} WFSCRDRESET, *LPWFSCRDRESET;

typedef struct _wfs_crd_set_guidlight
{
    WORD             wGuidLight;
    DWORD            dwCommand;
} WFSCRDSETGUIDLIGHT, *LPWFSCRDSETGUIDLIGHT;

typedef struct _wfs_crd_power_save_control
{
    USHORT           usMaxPowerSaveRecoveryTime;
} WFSCRDPOWERSAVECONTROL, *LPWFSCRDPOWERSAVECONTROL;

/*=================================================================*/
/* CRD Message Structures */
/*=================================================================*/

typedef struct _wfs_crd_media_detected
{
    WORD             wPosition;
    USHORT           usNumber;
} WFSCRDMEDIADETECTED, *LPWFSCRDMEDIADETECTED;

typedef struct _wfs_crd_cu_error
{
    WORD             wFailure;
    LPWFSCRDCARDUNIT lpCardUnit;
} WFSCRDCUERROR, *LPWFSCRDCUERROR;

typedef struct _wfs_crd_device_position
{
    WORD             wPosition;
} WFSCRDDEVICEPOSITION, *LPWFSCRDDEVICEPOSITION;

typedef struct _wfs_crd_power_save_change
{
    USHORT           usPowerSaveRecoveryTime;
} WFSCRDPOWERSAVECHANGE, *LPWFSCRDPOWERSAVECHANGE;

/*   restore alignment   */
#pragma pack(pop)

#ifdef __cplusplus
}       /*extern "C"*/
#endif

#endif  /* __INC_XFSCRD__H */
