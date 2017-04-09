/******************************************************************************
*                                                                             *
* xfschk.h      XFS - Check reader/scanner (CHK) definitions                  *
*                                                                             *
*             Version 3.20  (March 02 2011                                    *
*                                                                             *
******************************************************************************/

#ifndef __INC_XFSCHK__H
#define __INC_XFSCHK__H

#ifdef __cplusplus
extern "C" {
#endif

#include "xfsapi.h"

/*   be aware of alignment   */
#pragma pack(push,1)


/* value of WFSCHKCAPS.wClass */

#define    WFS_SERVICE_CLASS_CHK             (5)
#define    WFS_SERVICE_VERSION_CHK           (0x1403) /* Version 3.20 */
#define    WFS_SERVICE_NAME_CHK              "CHK"

#define    CHK_SERVICE_OFFSET                (WFS_SERVICE_CLASS_CHK * 100)


/* CHK Info Commands */

#define    WFS_INF_CHK_STATUS                (CHK_SERVICE_OFFSET + 1)
#define    WFS_INF_CHK_CAPABILITIES          (CHK_SERVICE_OFFSET + 2)
#define    WFS_INF_CHK_FORM_LIST             (CHK_SERVICE_OFFSET + 3)
#define    WFS_INF_CHK_MEDIA_LIST            (CHK_SERVICE_OFFSET + 4)
#define    WFS_INF_CHK_QUERY_FORM            (CHK_SERVICE_OFFSET + 5)
#define    WFS_INF_CHK_QUERY_MEDIA           (CHK_SERVICE_OFFSET + 6)
#define    WFS_INF_CHK_QUERY_FIELD           (CHK_SERVICE_OFFSET + 7)


/* CHK Command Verbs */

#define    WFS_CMD_CHK_PROCESS_FORM          (CHK_SERVICE_OFFSET + 1)
#define    WFS_CMD_CHK_RESET                 (CHK_SERVICE_OFFSET + 2)
#define    WFS_CMD_CHK_SET_GUIDANCE_LIGHT    (CHK_SERVICE_OFFSET + 3)
#define    WFS_CMD_CHK_POWER_SAVE_CONTROL    (CHK_SERVICE_OFFSET + 4)


/* CHK Messages */

#define    WFS_EXEE_CHK_NOMEDIA              (CHK_SERVICE_OFFSET + 1)
#define    WFS_EXEE_CHK_MEDIAINSERTED        (CHK_SERVICE_OFFSET + 2)
#define    WFS_SRVE_CHK_MEDIAINSERTED        (CHK_SERVICE_OFFSET + 3)
#define    WFS_EXEE_CHK_FIELDERROR           (CHK_SERVICE_OFFSET + 4)
#define    WFS_EXEE_CHK_FIELDWARNING         (CHK_SERVICE_OFFSET + 5)
#define    WFS_USRE_CHK_INKTHRESHOLD         (CHK_SERVICE_OFFSET + 6)
#define    WFS_SRVE_CHK_MEDIADETECTED        (CHK_SERVICE_OFFSET + 7)
#define    WFS_SRVE_CHK_DEVICEPOSITION       (CHK_SERVICE_OFFSET + 8)
#define    WFS_SRVE_CHK_POWER_SAVE_CHANGE    (CHK_SERVICE_OFFSET + 9)


/* values of WFSCHKSTATUS.fwDevice  */

#define    WFS_CHK_DEVONLINE                 WFS_STAT_DEVONLINE
#define    WFS_CHK_DEVOFFLINE                WFS_STAT_DEVOFFLINE
#define    WFS_CHK_DEVPOWEROFF               WFS_STAT_DEVPOWEROFF
#define    WFS_CHK_DEVNODEVICE               WFS_STAT_DEVNODEVICE
#define    WFS_CHK_DEVUSERERROR              WFS_STAT_DEVUSERERROR
#define    WFS_CHK_DEVHWERROR                WFS_STAT_DEVHWERROR
#define    WFS_CHK_DEVBUSY                   WFS_STAT_DEVBUSY
#define    WFS_CHK_DEVFRAUDATTEMPT           WFS_STAT_DEVFRAUDATTEMPT
#define    WFS_CHK_DEVPOTENTIALFRAUD         WFS_STAT_DEVPOTENTIALFRAUD

/* values of WFSCHKSTATUS.fwMedia,
             WFS_SRVE_CHK_MEDIADETECTED event */

#define    WFS_CHK_MEDIANOTSUPP              (0)
#define    WFS_CHK_MEDIANOTPRESENT           (1)
#define    WFS_CHK_MEDIAREQUIRED             (2)
#define    WFS_CHK_MEDIAPRESENT              (3)
#define    WFS_CHK_MEDIAJAMMED               (4)
#define    WFS_CHK_MEDIAEJECTED              (5)
#define    WFS_CHK_MEDIARETAINED             (6)

/* Size and max index of dwGuidLights array */

#define     WFS_CHK_GUIDLIGHTS_SIZE          (32)
#define     WFS_CHK_GUIDLIGHTS_MAX           (WFS_CHK_GUIDLIGHTS_SIZE - 1)


/* Indices of WFSCHKSTATUS.dwGuidLights [...]
              WFSCHKCAPS.dwGuidLights [...]
*/

#define     WFS_CHK_GUIDANCE_CHECKUNIT       (0)


/* Values of WFSCHKSTATUS.dwGuidLights [...]
             WFSCHKCAPS.dwGuidLights [...]
*/

#define     WFS_CHK_GUIDANCE_NOT_AVAILABLE   (0x00000000)
#define     WFS_CHK_GUIDANCE_OFF             (0x00000001)
#define     WFS_CHK_GUIDANCE_SLOW_FLASH      (0x00000004)
#define     WFS_CHK_GUIDANCE_MEDIUM_FLASH    (0x00000008)
#define     WFS_CHK_GUIDANCE_QUICK_FLASH     (0x00000010)
#define     WFS_CHK_GUIDANCE_CONTINUOUS      (0x00000080)
#define     WFS_CHK_GUIDANCE_RED             (0x00000100)
#define     WFS_CHK_GUIDANCE_GREEN           (0x00000200)
#define     WFS_CHK_GUIDANCE_YELLOW          (0x00000400)
#define     WFS_CHK_GUIDANCE_BLUE            (0x00000800)
#define     WFS_CHK_GUIDANCE_CYAN            (0x00001000)
#define     WFS_CHK_GUIDANCE_MAGENTA         (0x00002000)
#define     WFS_CHK_GUIDANCE_WHITE           (0x00004000)


/* Values of WFSCHKSTATUS.wDevicePosition
             WFSCHKDEVICEPOSITION.wPosition */

#define     WFS_CHK_DEVICEINPOSITION         (0)
#define     WFS_CHK_DEVICENOTINPOSITION      (1)
#define     WFS_CHK_DEVICEPOSUNKNOWN         (2)
#define     WFS_CHK_DEVICEPOSNOTSUPP         (3)


/* values of WFSCHKCAPS.fwType */

#define    WFS_CHK_TYPECHK                   (1)

/* values of WFSCHKSTATUS.fwInk,
             lpwInkThreshold */

#define    WFS_CHK_INKNOTSUPP                (0)
#define    WFS_CHK_INKFULL                   (1)
#define    WFS_CHK_INKLOW                    (2)
#define    WFS_CHK_INKOUT                    (3)


/* values of WFSCHKCAPS.fwStamp */

#define    WFS_CHK_STAMPNONE                 (1)
#define    WFS_CHK_STAMPFRONT                (2)
#define    WFS_CHK_STAMPBACK                 (3)
#define    WFS_CHK_STAMPBOTH                 (4)


/* values of WFSCHKCAPS.wImageCapture */

#define    WFS_CHK_ICAPNONE                  (1)
#define    WFS_CHK_ICAPFRONT                 (2)
#define    WFS_CHK_ICAPBACK                  (3)
#define    WFS_CHK_ICAPBOTH                  (4)


/* values of WFSCHKCAPS.fwCharSupport,
             WFSCHKFRMHEADER.fwCharSupport  */

#define    WFS_CHK_ASCII                     (0x0001)
#define    WFS_CHK_UNICODE                   (0x0002)


/* values of WFSCHKFRMHEADER.wBase,
             WFSCHKFRMMEDIA.wBase  */

#define    WFS_CHK_INCH                      (1)
#define    WFS_CHK_MM                        (2)
#define    WFS_CHK_ROWCOLUMN                 (3)


/* values of WFSCHKFRMHEADER.wAlignment */

#define    WFS_CHK_TOPLEFT                   (1)
#define    WFS_CHK_TOPRIGHT                  (2)
#define    WFS_CHK_BOTTOMLEFT                (3)
#define    WFS_CHK_BOTTOMRIGHT               (4)


/* values of WFSCHKFRMMEDIA.fwMediaType  */

#define    WFS_CHK_MEDIACHECK                (1)


/* values of WFSCHKFRMFIELD.fwType  */

#define    WFS_CHK_FIELDTEXT                 (1)
#define    WFS_CHK_FIELDMICR                 (2)
#define    WFS_CHK_FIELDOCR                  (3)
#define    WFS_CHK_FIELDGRAPHIC              (4)


/* values of WFSCHKFRMFIELD.fwClass  */

#define    WFS_CHK_CLASSSTATIC               (1)
#define    WFS_CHK_CLASSOPTIONAL             (2)
#define    WFS_CHK_CLASSREQUIRED             (3)


/* values of WFSCHKFRMFIELD.fwAccess  */

#define    WFS_CHK_ACCESSREAD                (1)
#define    WFS_CHK_ACCESSWRITE               (2)


/* values of WFSCHKFRMFIELD.fwOverflow */

#define    WFS_CHK_OVFTERMINATE              (0)
#define    WFS_CHK_OVFTRUNCATE               (1)
#define    WFS_CHK_OVFBESTFIT                (2)
#define    WFS_CHK_OVFOVERWRITE              (3)
#define    WFS_CHK_OVFWORDWRAP               (4)


/* values of WFSCHKINPROCESSFORM.dwOptions  */

#define    WFS_CHK_OPT_AUTOFEED              0x0001
#define    WFS_CHK_OPT_ICAPFRONT             0x0002
#define    WFS_CHK_OPT_ICAPBACK              0x0004
#define    WFS_CHK_OPT_NO_MICR_OCR           0x0008
#define    WFS_CHK_OPT_NO_WRITE              0x0010


/* values of WFSCHKOUTPROCESSFORM.wFrontImageType,
             WFSCHKOUTPROCESSFORM.wBackImageType */

#define    WFS_CHK_IMAGETIF                  (1)
#define    WFS_CHK_IMAGEMTF                  (2)
#define    WFS_CHK_IMAGEBMP                  (3)


/* input values to WFS_CMD_CHK_RESET */

#define    WFS_CHK_RESET_EJECT               (1)
#define    WFS_CHK_RESET_CAPTURE             (2)
#define    WFS_CHK_RESET_NOACTION            (3)


/* CHK Errors */

#define    WFS_ERR_CHK_FORMNOTFOUND          (-(CHK_SERVICE_OFFSET + 0))
#define    WFS_ERR_CHK_FORMINVALID           (-(CHK_SERVICE_OFFSET + 1))
#define    WFS_ERR_CHK_MEDIANOTFOUND         (-(CHK_SERVICE_OFFSET + 2))
#define    WFS_ERR_CHK_MEDIAINVALID          (-(CHK_SERVICE_OFFSET + 3))
#define    WFS_ERR_CHK_MEDIAOVERFLOW         (-(CHK_SERVICE_OFFSET + 4))
#define    WFS_ERR_CHK_FIELDNOTFOUND         (-(CHK_SERVICE_OFFSET + 5))
#define    WFS_ERR_CHK_FIELDINVALID          (-(CHK_SERVICE_OFFSET + 6))
#define    WFS_ERR_CHK_FIELDERROR            (-(CHK_SERVICE_OFFSET + 7))
#define    WFS_ERR_CHK_REQDFIELDMISSING      (-(CHK_SERVICE_OFFSET + 8))
#define    WFS_ERR_CHK_FIELDSPECFAILURE      (-(CHK_SERVICE_OFFSET + 9))
#define    WFS_ERR_CHK_CHARSETDATA           (-(CHK_SERVICE_OFFSET + 10))
#define    WFS_ERR_CHK_MEDIAJAM              (-(CHK_SERVICE_OFFSET + 11))
#define    WFS_ERR_CHK_SHUTTERFAIL           (-(CHK_SERVICE_OFFSET + 12))
#define    WFS_ERR_CHK_INVALID_PORT          (-(CHK_SERVICE_OFFSET + 13))
#define    WFS_ERR_CHK_POWERSAVETOOSHORT     (-(CHK_SERVICE_OFFSET + 14))
#define    WFS_ERR_CHK_POWERSAVEMEDIAPRESENT (-(CHK_SERVICE_OFFSET + 15))


/* values of WFSCHKFIELDFAIL.wFailure */

#define    WFS_CHK_FIELDREQUIRED             (1)
#define    WFS_CHK_FIELDSTATICOVWR           (2)
#define    WFS_CHK_FIELDOVERFLOW             (3)
#define    WFS_CHK_FIELDNOTFOUND             (4)
#define    WFS_CHK_FIELDNOTREAD              (5)
#define    WFS_CHK_FIELDNOTWRITE             (6)
#define    WFS_CHK_FIELDHWERROR              (7)
#define    WFS_CHK_FIELDTYPENOTSUPPORTED     (8)

/* values of WFSCHKSTATUS.wAntiFraudModule */

#define    WFS_CHK_AFMNOTSUPP                (0)
#define    WFS_CHK_AFMOK                     (1)
#define    WFS_CHK_AFMINOP                   (2)
#define    WFS_CHK_AFMDEVICEDETECTED         (3)
#define    WFS_CHK_AFMUNKNOWN                (4)



/*=================================================================*/
/* CHK Info Command Structures */
/*=================================================================*/

typedef struct _wfs_chk_status
{
    WORD            fwDevice;
    WORD            fwMedia;
    WORD            fwInk;
    LPSTR           lpszExtra;
    DWORD           dwGuidLights[WFS_CHK_GUIDLIGHTS_SIZE];
    WORD            wDevicePosition;
    USHORT          usPowerSaveRecoveryTime;
    WORD            wAntiFraudModule;
} WFSCHKSTATUS, *LPWFSCHKSTATUS;

typedef struct _wfs_chk_caps
{
    WORD            wClass;
    WORD            fwType;
    BOOL            bCompound;
    BOOL            bMICR;
    BOOL            bOCR;
    BOOL            bAutoFeed;
    BOOL            bEndorser;
    BOOL            bEncoder;
    WORD            fwStamp;
    WORD            wImageCapture;
    LPSTR           lpszFontNames;
    LPSTR           lpszEncodeNames;
    WORD            fwCharSupport;
    LPSTR           lpszExtra;
    DWORD           dwGuidLights[WFS_CHK_GUIDLIGHTS_SIZE];
    BOOL            bPowerSaveControl;
    BOOL            bAntiFraudModule;
} WFSCHKCAPS, *LPWFSCHKCAPS;

typedef struct _wfs_chk_frm_header
{
    LPSTR           lpszFormName;
    WORD            wBase;
    WORD            wUnitX;
    WORD            wUnitY;
    WORD            wWidth;
    WORD            wHeight;
    WORD            wAlignment;
    WORD            wOffsetX;
    WORD            wOffsetY;
    WORD            wVersionMajor;
    WORD            wVersionMinor;
    WORD            fwCharSupport;
    LPSTR           lpszFields;
} WFSCHKFRMHEADER, *LPWFSCHKFRMHEADER;

typedef struct _wfs_chk_frm_media
{
    WORD            fwMediaType;
    WORD            wBase;
    WORD            wUnitX;
    WORD            wUnitY;
    WORD            wSizeWidth;
    WORD            wSizeHeight;
    WORD            wCheckAreaX;
    WORD            wCheckAreaY;
    WORD            wCheckAreaWidth;
    WORD            wCheckAreaHeight;
    WORD            wRestrictedAreaX;
    WORD            wRestrictedAreaY;
    WORD            wRestrictedAreaWidth;
    WORD            wRestrictedAreaHeight;
} WFSCHKFRMMEDIA, *LPWFSCHKFRMMEDIA;

typedef struct _wfs_chk_query_field
{
    LPSTR           lpszFormName;
    LPSTR           lpszFieldName;
} WFSCHKQUERYFIELD, *LPWFSCHKQUERYFIELD;

typedef struct _wfs_chk_frm_field
{
    LPSTR           lpszFieldName;
    WORD            fwType;
    WORD            fwClass;
    WORD            fwAccess;
    WORD            fwOverflow;
    LPSTR           lpszInitialValue;
    LPWSTR          lpszUNICODEInitialValue;
    LPSTR           lpszFormat;
    LPWSTR          lpszUNICODEFormat;
} WFSCHKFRMFIELD, *LPWFSCHKFRMFIELD;


/*=================================================================*/
/* CHK Execute Command Structures */
/*=================================================================*/

typedef struct _wfs_chk_in_process_form
{
    LPSTR           lpszFormName;
    LPSTR           lpszMediaName;
    LPSTR           lpszInputFields;
    LPSTR           lpszOutputFields;
    LPWSTR          lpszUNICODEOutputFields;
    DWORD           dwOptions;
} WFSCHKINPROCESSFORM, *LPWFSCHKINPROCESSFORM;

typedef struct _wfs_chk_out_process_form
{
    LPSTR           lpszInputFields;
    LPWSTR          lpszUNICODEInputFields;
    WORD            wFrontImageType;
    ULONG           ulFrontImageSize;
    LPBYTE          lpFrontImage;
    WORD            wBackImageType;
    ULONG           ulBackImageSize;
    LPBYTE          lpBackImage;
} WFSCHKOUTPROCESSFORM, *LPWFSCHKOUTPROCESSFORM;

typedef struct _wfs_chk_set_guidlight
{
    WORD            wGuidLight;
    DWORD           dwCommand;
} WFSCHKSETGUIDLIGHT, *LPWFSCHKSETGUIDLIGHT;

typedef struct _wfs_chk_power_save_control
{
    USHORT          usMaxPowerSaveRecoveryTime;
} WFSCHKPOWERSAVECONTROL, *LPWFSCHKPOWERSAVECONTROL;


/*=================================================================*/
/* CHK Message Structures */
/*=================================================================*/

typedef struct _wfs_chk_field_failure
{
    LPSTR           lpszFormName;
    LPSTR           lpszFieldName;
    WORD            wFailure;
} WFSCHKFIELDFAIL, *LPWFSCHKFIELDFAIL;

typedef struct _wfs_chk_device_position
{
    WORD            wPosition;
} WFSCHKDEVICEPOSITION, *LPWFSCHKDEVICEPOSITION;

typedef struct _wfs_chk_power_save_change
{
    USHORT          usPowerSaveRecoveryTime;
} WFSCHKPOWERSAVECHANGE, *LPWFSCHKPOWERSAVECHANGE;

/* restore alignment */
#pragma pack(pop)

#ifdef __cplusplus
}       /*extern "C"*/
#endif

#endif	/* __INC_XFSCHK__H */
