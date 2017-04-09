/******************************************************************************
*                                                                             *
* xfsbcr.h    XFS - Barcode Reader (BCR) definitions                          *
*                                                                             *
*             Version 3.20  (March 02 2011)                                   *
*                                                                             *
******************************************************************************/

#ifndef __INC_XFSBCR__H
#define __INC_XFSBCR__H

#ifdef __cplusplus
extern "C" {
#endif

#include "xfsapi.h"

/* be aware of alignment */
#pragma pack (push, 1)

/* values of WFSBCRCAPS.wClass */

#define     WFS_SERVICE_CLASS_BCR               (15)
#define     WFS_SERVICE_CLASS_VERSION_BCR       (0x1403) /* Version 3.20 */
#define     WFS_SERVICE_CLASS_NAME_BCR          "BCR"

#define     BCR_SERVICE_OFFSET                  (WFS_SERVICE_CLASS_BCR * 100)

/* BCR Info Commands */

#define     WFS_INF_BCR_STATUS                  (BCR_SERVICE_OFFSET + 1)
#define     WFS_INF_BCR_CAPABILITIES            (BCR_SERVICE_OFFSET + 2)

/* BCR Execute Commands */

#define     WFS_CMD_BCR_READ                    (BCR_SERVICE_OFFSET + 1)
#define     WFS_CMD_BCR_RESET                   (BCR_SERVICE_OFFSET + 2)
#define     WFS_CMD_BCR_SET_GUIDANCE_LIGHT      (BCR_SERVICE_OFFSET + 3)
#define     WFS_CMD_BCR_POWER_SAVE_CONTROL      (BCR_SERVICE_OFFSET + 4)

/* BCR Messages */

#define     WFS_SRVE_BCR_DEVICEPOSITION         (BCR_SERVICE_OFFSET + 1)
#define     WFS_SRVE_BCR_POWER_SAVE_CHANGE      (BCR_SERVICE_OFFSET + 2)

/* values of WFSBCRSTATUS.fwDevice */

#define     WFS_BCR_DEVONLINE                   WFS_STAT_DEVONLINE
#define     WFS_BCR_DEVOFFLINE                  WFS_STAT_DEVOFFLINE
#define     WFS_BCR_DEVPOWEROFF                 WFS_STAT_DEVPOWEROFF
#define     WFS_BCR_DEVNODEVICE                 WFS_STAT_DEVNODEVICE
#define     WFS_BCR_DEVHWERROR                  WFS_STAT_DEVHWERROR
#define     WFS_BCR_DEVUSERERROR                WFS_STAT_DEVUSERERROR
#define     WFS_BCR_DEVBUSY                     WFS_STAT_DEVBUSY
#define     WFS_BCR_DEVFRAUDATTEMPT             WFS_STAT_DEVFRAUDATTEMPT
#define     WFS_BCR_DEVPOTENTIALFRAUD           WFS_STAT_DEVPOTENTIALFRAUD

/* values of WFSBCRSTATUS.fwBCRScanner */

#define     WFS_BCR_SCANNERON                   (0)
#define     WFS_BCR_SCANNEROFF                  (1)
#define     WFS_BCR_SCANNERINOP                 (2)
#define     WFS_BCR_SCANNERUNKNOWN              (3)

/* values of WFSBCRSTATUS.wDevicePosition
             WFSBCRDEVICEPOSITION.wPosition */

#define     WFS_BCR_DEVICEINPOSITION            (0)
#define     WFS_BCR_DEVICENOTINPOSITION         (1)
#define     WFS_BCR_DEVICEPOSUNKNOWN            (2)
#define     WFS_BCR_DEVICEPOSNOTSUPP            (3)

/* values of WFSBCRCAPS.lpwSymbologies
             WFSBCRREADINPUT.lpwSymbologies
             WFSBCRREADOUTPUT.wSymbology */

#define     WFS_BCR_SYM_UNKNOWN                 (0)
#define     WFS_BCR_SYM_EAN128                  (1)
#define     WFS_BCR_SYM_EAN8                    (2)
#define     WFS_BCR_SYM_EAN8_2                  (3)
#define     WFS_BCR_SYM_EAN8_5                  (4)
#define     WFS_BCR_SYM_EAN13                   (5)
#define     WFS_BCR_SYM_EAN13_2                 (6)
#define     WFS_BCR_SYM_EAN13_5                 (7)
#define     WFS_BCR_SYM_JAN13                   (8)
#define     WFS_BCR_SYM_UPCA                    (9)
#define     WFS_BCR_SYM_UPCE0                   (10)
#define     WFS_BCR_SYM_UPCE0_2                 (11)
#define     WFS_BCR_SYM_UPCE0_5                 (12)
#define     WFS_BCR_SYM_UPCE1                   (13)
#define     WFS_BCR_SYM_UPCE1_2                 (14)
#define     WFS_BCR_SYM_UPCE1_5                 (15)
#define     WFS_BCR_SYM_UPCA_2                  (16)
#define     WFS_BCR_SYM_UPCA_5                  (17)
#define     WFS_BCR_SYM_CODABAR                 (18)
#define     WFS_BCR_SYM_ITF                     (19)
#define     WFS_BCR_SYM_11                      (20)
#define     WFS_BCR_SYM_39                      (21)
#define     WFS_BCR_SYM_49                      (22)
#define     WFS_BCR_SYM_93                      (23)
#define     WFS_BCR_SYM_128                     (24)
#define     WFS_BCR_SYM_MSI                     (25)
#define     WFS_BCR_SYM_PLESSEY                 (26)
#define     WFS_BCR_SYM_STD2OF5                 (27)
#define     WFS_BCR_SYM_STD2OF5_IATA            (28)
#define     WFS_BCR_SYM_PDF_417                 (29)
#define     WFS_BCR_SYM_MICROPDF_417            (30)
#define     WFS_BCR_SYM_DATAMATRIX              (31)
#define     WFS_BCR_SYM_MAXICODE                (32)
#define     WFS_BCR_SYM_CODEONE                 (33)
#define     WFS_BCR_SYM_CHANNELCODE             (34)
#define     WFS_BCR_SYM_TELEPEN_ORIGINAL        (35)
#define     WFS_BCR_SYM_TELEPEN_AIM             (36)
#define     WFS_BCR_SYM_RSS                     (37)
#define     WFS_BCR_SYM_RSS_EXPANDED            (38)
#define     WFS_BCR_SYM_RSS_RESTRICTED          (39)
#define     WFS_BCR_SYM_COMPOSITE_CODE_A        (40)
#define     WFS_BCR_SYM_COMPOSITE_CODE_B        (41)
#define     WFS_BCR_SYM_COMPOSITE_CODE_C        (42)
#define     WFS_BCR_SYM_POSICODE_A              (43)
#define     WFS_BCR_SYM_POSICODE_B              (44)
#define     WFS_BCR_SYM_TRIOPTIC_CODE_39        (45)
#define     WFS_BCR_SYM_CODABLOCK_F             (46)
#define     WFS_BCR_SYM_CODE_16K                (47)
#define     WFS_BCR_SYM_QRCODE                  (48)
#define     WFS_BCR_SYM_AZTEC                   (49)
#define     WFS_BCR_SYM_UKPOST                  (50)
#define     WFS_BCR_SYM_PLANET                  (51)
#define     WFS_BCR_SYM_POSTNET                 (52)
#define     WFS_BCR_SYM_CANADIANPOST            (53)
#define     WFS_BCR_SYM_NETHERLANDSPOST         (54)
#define     WFS_BCR_SYM_AUSTRALIANPOST          (55)
#define     WFS_BCR_SYM_JAPANESEPOST            (56)
#define     WFS_BCR_SYM_CHINESEPOST             (57)
#define     WFS_BCR_SYM_KOREANPOST              (58)

/* Size and max index of dwGuidLights array */

#define WFS_BCR_GUIDLIGHTS_SIZE                 (32)
#define WFS_BCR_GUIDLIGHTS_MAX                  (WFS_BCR_GUIDLIGHTS_SIZE - 1)

/* Indices of WFSBCRSTATUS.dwGuidLights [...]
              WFSBCRCAPS.dwGuidLights [...]
*/
#define     WFS_BCR_GUIDANCE_BCR                (0)

/* Values of WFSBCRSTATUS.dwGuidLights [...]
             WFSBCRCAPS.dwGuidLights [...],
             WFSBCRSETGUIDLIGHT.wGuidLight */

#define     WFS_BCR_GUIDANCE_NOT_AVAILABLE      (0x00000000)
#define     WFS_BCR_GUIDANCE_OFF                (0x00000001)
#define     WFS_BCR_GUIDANCE_ON                 (0x00000002)
#define     WFS_BCR_GUIDANCE_SLOW_FLASH         (0x00000004)
#define     WFS_BCR_GUIDANCE_MEDIUM_FLASH       (0x00000008)
#define     WFS_BCR_GUIDANCE_QUICK_FLASH        (0x00000010)
#define     WFS_BCR_GUIDANCE_CONTINUOUS         (0x00000080)
#define     WFS_BCR_GUIDANCE_RED                (0x00000100)
#define     WFS_BCR_GUIDANCE_GREEN              (0x00000200)
#define     WFS_BCR_GUIDANCE_YELLOW             (0x00000400)
#define     WFS_BCR_GUIDANCE_BLUE               (0x00000800)
#define     WFS_BCR_GUIDANCE_CYAN               (0x00001000)
#define     WFS_BCR_GUIDANCE_MAGENTA            (0x00002000)
#define     WFS_BCR_GUIDANCE_WHITE              (0x00004000)

/* values of WFSBCRSTATUS.wAntiFraudModule */

#define     WFS_BCR_AFMNOTSUPP                  (0)
#define     WFS_BCR_AFMOK                       (1)
#define     WFS_BCR_AFMINOP                     (2)
#define     WFS_BCR_AFMDEVICEDETECTED           (3)
#define     WFS_BCR_AFMUNKNOWN                  (4)

/* XFS BCR Errors */

#define WFS_ERR_BCR_BARCODEINVALID              (-(BCR_SERVICE_OFFSET + 0))
#define WFS_ERR_BCR_INVALID_PORT                (-(BCR_SERVICE_OFFSET + 1))
#define WFS_ERR_BCR_POWERSAVETOOSHORT           (-(BCR_SERVICE_OFFSET + 2))

/*=================================================================*/
/* BCR Info Command Structures */
/*=================================================================*/
typedef struct _wfs_bcr_status
{
    WORD             fwDevice;
    WORD             fwBCRScanner;
    DWORD            dwGuidLights[WFS_BCR_GUIDLIGHTS_SIZE];
    LPSTR            lpszExtra;
    WORD             wDevicePosition;
    USHORT           usPowerSaveRecoveryTime;
    WORD             wAntiFraudModule;
} WFSBCRSTATUS, *LPWFSBCRSTATUS;

typedef struct _wfs_bcr_caps
{
    WORD             wClass;
    BOOL             bCompound;
    BOOL             bCanFilterSymbologies;
    LPWORD           lpwSymbologies;
    DWORD            dwGuidLights[WFS_BCR_GUIDLIGHTS_SIZE];
    LPSTR            lpszExtra;
    BOOL             bPowerSaveControl;
    BOOL             bAntiFraudModule;
} WFSBCRCAPS, *LPWFSBCRCAPS;

/*=================================================================*/
/* BCR Execute Command Structures */
/*=================================================================*/
typedef struct _wfs_bcr_hex_data
{
    USHORT           usLength;
    LPBYTE           lpbData;
} WFSBCRXDATA, * LPWFSBCRXDATA;

typedef struct _wfs_bcr_read_input
{
    LPWORD           lpwSymbologies;
} WFSBCRREADINPUT, *LPWFSBCRREADINPUT;

typedef struct _wfs_bcr_read_output
{
    WORD             wSymbology;
    LPWFSBCRXDATA    lpxBarcodeData;
    LPSTR            lpszSymbologyName;
} WFSBCRREADOUTPUT, *LPWFSBCRREADOUTPUT;

typedef struct _wfs_bcr_set_guidlight
{
    WORD             wGuidLight;
    DWORD            dwCommand;
} WFSBCRSETGUIDLIGHT, *LPWFSBCRSETGUIDLIGHT;

typedef struct _wfs_bcr_power_save_control
{
    USHORT           usMaxPowerSaveRecoveryTime;
} WFSBCRPOWERSAVECONTROL, *LPWFSBCRPOWERSAVECONTROL;

/*=================================================================*/
/* BCR Message Structures */
/*=================================================================*/

typedef struct _wfs_bcr_device_position
{
    WORD             wPosition;
} WFSBCRDEVICEPOSITION, *LPWFSBCRDEVICEPOSITION;

typedef struct _wfs_bcr_power_save_change
{
    USHORT           usPowerSaveRecoveryTime;
} WFSBCRPOWERSAVECHANGE, *LPWFSBCRPOWERSAVECHANGE;

/*   restore alignment   */
#pragma pack(pop)
#ifdef __cplusplus
} /*extern "C"*/

#endif
#endif /* __INC_XFSBCR__H */
