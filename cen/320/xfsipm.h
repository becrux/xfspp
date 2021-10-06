/******************************************************************************
*                                                                             *
* xfsipm.h    XFS - Item Processing Module (IPM) definitions                  *
*                                                                             *
*             Version 3.20  (March 02 2011)                                   *
*                                                                             *
******************************************************************************/

#ifndef __INC_XFSIPM__H
#define  __INC_XFSIPM__H

#ifdef __cplusplus
extern "C" {
#endif

#include "xfsapi.h"

/*   be aware of alignment   */
#pragma pack(push,1)

/* Value of WFSIPMCAPS.wClass */

#define     WFS_SERVICE_CLASS_IPM               (16)
#define     WFS_SERVICE_CLASS_VERSION_IPM       (0x1403) /* Version 3.20 */
#define     WFS_SERVICE_CLASS_NAME_IPM          "IPM"

#define     IPM_SERVICE_OFFSET                  (WFS_SERVICE_CLASS_IPM * 100)

/* IPM Info Commands */

#define     WFS_INF_IPM_STATUS                  (IPM_SERVICE_OFFSET + 1)
#define     WFS_INF_IPM_CAPABILITIES            (IPM_SERVICE_OFFSET + 2)
#define     WFS_INF_IPM_CODELINE_MAPPING        (IPM_SERVICE_OFFSET + 3)
#define     WFS_INF_IPM_MEDIA_BIN_INFO          (IPM_SERVICE_OFFSET + 4)
#define     WFS_INF_IPM_TRANSACTION_STATUS      (IPM_SERVICE_OFFSET + 5)

/* IPM Execute Commands */

#define     WFS_CMD_IPM_MEDIA_IN                (IPM_SERVICE_OFFSET + 1)
#define     WFS_CMD_IPM_MEDIA_IN_END            (IPM_SERVICE_OFFSET + 2)
#define     WFS_CMD_IPM_MEDIA_IN_ROLLBACK       (IPM_SERVICE_OFFSET + 3)
#define     WFS_CMD_IPM_READ_IMAGE              (IPM_SERVICE_OFFSET + 4)
#define     WFS_CMD_IPM_SET_DESTINATION         (IPM_SERVICE_OFFSET + 5)
#define     WFS_CMD_IPM_PRESENT_MEDIA           (IPM_SERVICE_OFFSET + 6)
#define     WFS_CMD_IPM_RETRACT_MEDIA           (IPM_SERVICE_OFFSET + 7)
#define     WFS_CMD_IPM_PRINT_TEXT              (IPM_SERVICE_OFFSET + 8)
#define     WFS_CMD_IPM_SET_MEDIA_BIN_INFO      (IPM_SERVICE_OFFSET + 9)
#define     WFS_CMD_IPM_RESET                   (IPM_SERVICE_OFFSET + 10)
#define     WFS_CMD_IPM_SET_GUIDANCE_LIGHT      (IPM_SERVICE_OFFSET + 11)
#define     WFS_CMD_IPM_GET_NEXT_ITEM           (IPM_SERVICE_OFFSET + 12)
#define     WFS_CMD_IPM_ACTION_ITEM             (IPM_SERVICE_OFFSET + 13)
#define     WFS_CMD_IPM_EXPEL_MEDIA             (IPM_SERVICE_OFFSET + 14)
#define     WFS_CMD_IPM_GET_IMAGE_AFTER_PRINT   (IPM_SERVICE_OFFSET + 15)
#define     WFS_CMD_IPM_ACCEPT_ITEM             (IPM_SERVICE_OFFSET + 16)
#define     WFS_CMD_IPM_SUPPLY_REPLENISH        (IPM_SERVICE_OFFSET + 17)
#define     WFS_CMD_IPM_POWER_SAVE_CONTROL      (IPM_SERVICE_OFFSET + 18)
#define     WFS_CMD_IPM_SET_MODE                (IPM_SERVICE_OFFSET + 19)

/* IPM Messages */

#define     WFS_EXEE_IPM_NOMEDIA                (IPM_SERVICE_OFFSET + 1)
#define     WFS_EXEE_IPM_MEDIAINSERTED          (IPM_SERVICE_OFFSET + 2)
#define     WFS_USRE_IPM_MEDIABINTHRESHOLD      (IPM_SERVICE_OFFSET + 3)
#define     WFS_SRVE_IPM_MEDIABININFOCHANGED    (IPM_SERVICE_OFFSET + 4)
#define     WFS_EXEE_IPM_MEDIABINERROR          (IPM_SERVICE_OFFSET + 5)
#define     WFS_SRVE_IPM_MEDIATAKEN             (IPM_SERVICE_OFFSET + 6)
#define     WFS_USRE_IPM_TONERTHRESHOLD         (IPM_SERVICE_OFFSET + 7)
#define     WFS_USRE_IPM_SCANNERTHRESHOLD       (IPM_SERVICE_OFFSET + 8)
#define     WFS_USRE_IPM_INKTHRESHOLD           (IPM_SERVICE_OFFSET + 9)
#define     WFS_SRVE_IPM_MEDIADETECTED          (IPM_SERVICE_OFFSET + 10)
#define     WFS_EXEE_IPM_MEDIAPRESENTED         (IPM_SERVICE_OFFSET + 11)
#define     WFS_EXEE_IPM_MEDIAREFUSED           (IPM_SERVICE_OFFSET + 12)
#define     WFS_EXEE_IPM_MEDIADATA              (IPM_SERVICE_OFFSET + 13)
#define     WFS_USRE_IPM_MICRTHRESHOLD          (IPM_SERVICE_OFFSET + 14)
#define     WFS_EXEE_IPM_MEDIAREJECTED          (IPM_SERVICE_OFFSET + 15)
#define     WFS_SRVE_IPM_DEVICEPOSITION         (IPM_SERVICE_OFFSET + 16)
#define     WFS_SRVE_IPM_POWER_SAVE_CHANGE      (IPM_SERVICE_OFFSET + 17)

/* Values of WFSIPMSTATUS.fwDevice */

#define     WFS_IPM_DEVONLINE                   WFS_STAT_DEVONLINE
#define     WFS_IPM_DEVOFFLINE                  WFS_STAT_DEVOFFLINE
#define     WFS_IPM_DEVPOWEROFF                 WFS_STAT_DEVPOWEROFF
#define     WFS_IPM_DEVNODEVICE                 WFS_STAT_DEVNODEVICE
#define     WFS_IPM_DEVHWERROR                  WFS_STAT_DEVHWERROR
#define     WFS_IPM_DEVUSERERROR                WFS_STAT_DEVUSERERROR
#define     WFS_IPM_DEVBUSY                     WFS_STAT_DEVBUSY
#define     WFS_IPM_DEVFRAUDATTEMPT             WFS_STAT_DEVFRAUDATTEMPT
#define     WFS_IPM_DEVPOTENTIALFRAUD           WFS_STAT_DEVPOTENTIALFRAUD

/* Values of WFSIPMSTATUS.wAcceptor */

#define     WFS_IPM_ACCBINOK                    (0)
#define     WFS_IPM_ACCBINSTATE                 (1)
#define     WFS_IPM_ACCBINSTOP                  (2)
#define     WFS_IPM_ACCBINUNKNOWN               (3)

/* Values of WFSIPMSTATUS.wMedia and
             WFSIPMMEDIADETECTED.wPosition */

#define     WFS_IPM_MEDIAPRESENT                (0)
#define     WFS_IPM_MEDIANOTPRESENT             (1)
#define     WFS_IPM_MEDIAJAMMED                 (2)
#define     WFS_IPM_MEDIANOTSUPP                (3)
#define     WFS_IPM_MEDIAUNKNOWN                (4)
#define     WFS_IPM_MEDIAPOSITION               (5)
#define     WFS_IPM_MEDIARETRACTED              (6)
#define     WFS_IPM_MEDIARETURNED               (7)

/* Values of WFSIPMSTATUS.wToner and
             WFSIPMTHRESHOLD.wThreshold */

#define     WFS_IPM_TONERFULL                   (0)
#define     WFS_IPM_TONERLOW                    (1)
#define     WFS_IPM_TONEROUT                    (2)
#define     WFS_IPM_TONERNOTSUPP                (3)
#define     WFS_IPM_TONERUNKNOWN                (4)

/* Values of WFSIPMSTATUS.wInk and
             WFSIPMTHRESHOLD.wThreshold */

#define     WFS_IPM_INKFULL                     (0)
#define     WFS_IPM_INKLOW                      (1)
#define     WFS_IPM_INKOUT                      (2)
#define     WFS_IPM_INKNOTSUPP                  (3)
#define     WFS_IPM_INKUNKNOWN                  (4)

/* Values of WFSIPMSTATUS.wFrontImageScanner,
             WFSIPMSTATUS.wBackImageScanner and
             WFSIPMSCANNERTHRESHOLD.wThreshold */

#define     WFS_IPM_SCANNEROK                   (0)
#define     WFS_IPM_SCANNERFADING               (1)
#define     WFS_IPM_SCANNERINOP                 (2)
#define     WFS_IPM_SCANNERNOTSUPP              (3)
#define     WFS_IPM_SCANNERUNKNOWN              (4)

/* Values of WFSIPMSTATUS.wMICRReader and
             WFSIPMTHRESHOLD.wThreshold */

#define     WFS_IPM_MICROK                      (0)
#define     WFS_IPM_MICRFADING                  (1)
#define     WFS_IPM_MICRINOP                    (2)
#define     WFS_IPM_MICRNOTSUPP                 (3)
#define     WFS_IPM_MICRUNKNOWN                 (4)

/* Values of WFSIPMSTATUS.wStacker  */

#define     WFS_IPM_STACKEREMPTY                (0)
#define     WFS_IPM_STACKERNOTEMPTY             (1)
#define     WFS_IPM_STACKERFULL                 (2)
#define     WFS_IPM_STACKERINOP                 (3)
#define     WFS_IPM_STACKERUNKNOWN              (4)
#define     WFS_IPM_STACKERNOTSUPP              (5)

/* Values of WFSIPMSTATUS.wReBuncher       */

#define     WFS_IPM_REBUNCHEREMPTY              (0)
#define     WFS_IPM_REBUNCHERNOTEMPTY           (1)
#define     WFS_IPM_REBUNCHERFULL               (2)
#define     WFS_IPM_REBUNCHERINOP               (3)
#define     WFS_IPM_REBUNCHERUNKNOWN            (4)
#define     WFS_IPM_REBUNCHERNOTSUPP            (5)

/* Values of WFSIPMSTATUS.wMediaFeeder and
             WFSIPMMEDIAIN.wMediaFeeder*/

#define     WFS_IPM_FEEDEREMPTY                 (0)
#define     WFS_IPM_FEEDERNOTEMPTY              (1)
#define     WFS_IPM_FEEDERINOP                  (2)
#define     WFS_IPM_FEEDERUNKNOWN               (3)
#define     WFS_IPM_FEEDERNOTSUPP               (4)

/* Values of WFSIPMSTATUS.wDevicePosition and
             WFSIPMDEVICEPOSITION.wPosition */

#define     WFS_IPM_DEVICEINPOSITION            (0)
#define     WFS_IPM_DEVICENOTINPOSITION         (1)
#define     WFS_IPM_DEVICEPOSUNKNOWN            (2)
#define     WFS_IPM_DEVICEPOSNOTSUPP            (3)

/* Values of WFSIPMTRANSSTATUS.usMediaOnStacker,
             WFSIPMTRANSSTATUS.usLastMediaInTotal,
             WFSIPMTRANSSTATUS.usLastMediaAddedToStacker,
             WFSIPMTRANSSTATUS.usTotalItems,
             WFSIPMTRANSSTATUS.usTotalItemsRefused,
             WFSIPMTRANSSTATUS.usTotalBunchesRefused,
             WFSIPMMEDIAIN.usMediaOnStacker,
             WFSIPMMEDIAIN.usLastMedia,
             WFSIPMMEDIAIN.usLastMediaOnStacker and
             WFSIPMRETRACTMEDIAOUT.usMedia */

#define     WFS_IPM_MEDIANUMBERUNKNOWN          (0xFFFF)

/* Indices for WFSIPMSTATUS.lppPositions and
               WFSIPMCAPS.lppPositions,
   Values of WFSIPMPOSITION.wPosition and
             WFSIPMMEDIAPRESENTED.wPosition */

#define     WFS_IPM_POSINPUT                    (0)
#define     WFS_IPM_POSOUTPUT                   (1)
#define     WFS_IPM_POSREFUSED                  (2)

/* Values of WFSIPMPOS.wShutter */

#define     WFS_IPM_SHTCLOSED                   (0)
#define     WFS_IPM_SHTOPEN                     (1)
#define     WFS_IPM_SHTJAMMED                   (2)
#define     WFS_IPM_SHTUNKNOWN                  (3)
#define     WFS_IPM_SHTNOTSUPPORTED             (4)

/* Values of WFSIPMCAPS.wMixedMode */

#define     WFS_IPM_MIXEDMEDIANOTSUPP           (0)
#define     WFS_IPM_CIMMIXEDMEDIA               (1)

/* Values of WFSIPMSETMODE.wMixedMode and
             WFSIPMSTATUS.wMixedMode */

#define     WFS_IPM_MIXEDMEDIANOTACTIVE         (0)

/* Values of WFSIPMPOS.wPositionStatus */

#define     WFS_IPM_PSEMPTY                     (0)
#define     WFS_IPM_PSNOTEMPTY                  (1)
#define     WFS_IPM_PSUNKNOWN                   (2)
#define     WFS_IPM_PSNOTSUPPORTED              (3)

/* Values of WFSIPMPOS.wTransport */

#define     WFS_IPM_TPOK                        (0)
#define     WFS_IPM_TPINOP                      (1)
#define     WFS_IPM_TPUNKNOWN                   (2)
#define     WFS_IPM_TPNOTSUPPORTED              (3)

/* Values of WFSIPMPOS.wTransportMediaStatus */

#define     WFS_IPM_TPMEDIAEMPTY                (0)
#define     WFS_IPM_TPMEDIANOTEMPTY             (1)
#define     WFS_IPM_TPMEDIAUNKNOWN              (2)
#define     WFS_IPM_TPMEDIANOTSUPPORTED         (3)

/* Size and max index of dwGuidLights array */

#define     WFS_IPM_GUIDLIGHTS_SIZE             (32)
#define     WFS_IPM_GUIDLIGHTS_MAX              (WFS_IPM_GUIDLIGHTS_SIZE - 1)

/* Indices of WFSIPMSTATUS.dwGuidLights [...] and
              WFSIPMCAPS.dwGuidLights [...] and
   Values of WFSIPMSETGUIDLIGHT.wGuidLight */

#define     WFS_IPM_GUIDANCE_MEDIAIN            (0)
#define     WFS_IPM_GUIDANCE_MEDIAOUT           (1)
#define     WFS_IPM_GUIDANCE_MEDIAREFUSED       (2)

/* Values of WFSIPMSTATUS.dwGuidLights [...],
             WFSIPMCAPS.dwGuidLights [...] and
             WFSIPMSETGUIDLIGHT.dwCommand */

#define     WFS_IPM_GUIDANCE_NOT_AVAILABLE      (0x00000000)
#define     WFS_IPM_GUIDANCE_OFF                (0x00000001)
#define     WFS_IPM_GUIDANCE_SLOW_FLASH         (0x00000004)
#define     WFS_IPM_GUIDANCE_MEDIUM_FLASH       (0x00000008)
#define     WFS_IPM_GUIDANCE_QUICK_FLASH        (0x00000010)
#define     WFS_IPM_GUIDANCE_CONTINUOUS         (0x00000080)
#define     WFS_IPM_GUIDANCE_RED                (0x00000100)
#define     WFS_IPM_GUIDANCE_GREEN              (0x00000200)
#define     WFS_IPM_GUIDANCE_YELLOW             (0x00000400)
#define     WFS_IPM_GUIDANCE_BLUE               (0x00000800)
#define     WFS_IPM_GUIDANCE_CYAN               (0x00001000)
#define     WFS_IPM_GUIDANCE_MAGENTA            (0x00002000)
#define     WFS_IPM_GUIDANCE_WHITE              (0x00004000)

/* Values of WFSIPMCAPS.fwType */

#define     WFS_IPM_TYPESINGLEMEDIAINPUT        (0x0001)
#define     WFS_IPM_TYPEBUNCHMEDIAINPUT         (0x0002)

/* Values of WFSIPMCAPS.fwRetractLocation,
             WFSIPMPOSCAPS.fwRetractAreas,
             WFSIPMRETRACTMEDIA.wRetractLocation and
             WFSIPMRETRACTMEDIAOUT.wRetractLocation */

#define     WFS_IPM_CTRLRETRACTTOBIN            (0x0001)
#define     WFS_IPM_CTRLRETRACTTOTRANSPORT      (0x0002)
#define     WFS_IPM_CTRLRETRACTTOSTACKER        (0x0004)
#define     WFS_IPM_CTRLRETRACTTOREBUNCHER      (0x0008)

/* Values of WFSIPMCAPS.fwResetControl and
             WFSIPMRESET.wMediaControl */

#define     WFS_IPM_RESETEJECT                  (0x0001)
#define     WFS_IPM_RESETRETRACTTOBIN           (0x0002)
#define     WFS_IPM_RESETRETRACTTOTRANSPORT     (0x0004)
#define     WFS_IPM_RESETRETRACTTOREBUNCHER     (0x0008)

/* Values of WFSIPMCAPS.fwImageType,
             WFSIPMIMAGEREQUEST.wImageType and
             WFSIPMIMAGEDATA.wImageType */

#define     WFS_IPM_IMAGETIF                    (0x0001)
#define     WFS_IPM_IMAGEWMF                    (0x0002)
#define     WFS_IPM_IMAGEBMP                    (0x0004)
#define     WFS_IPM_IMAGEJPG                    (0x0008)

/* Values of WFSIPMCAPS.fwFrontImageColorFormat,
             WFSIPMCAPS.fwBackImageColorFormat,
             WFSIPMIMAGEREQUEST.wImageColorFormat and
             WFSIPMIMAGEDATA.wImageColorFormat */

#define     WFS_IPM_IMAGECOLORBINARY            (0x0001)
#define     WFS_IPM_IMAGECOLORGRAYSCALE         (0x0002)
#define     WFS_IPM_IMAGECOLORFULL              (0x0004)

/* Values of WFSIPMCAPS.fwFrontScanColor,
             WFSIPMCAPS.fwBackScanColor,
             WFSIPMCAPS.wDefaultFrontScanColor,
             WFSIPMCAPS.wDefaultBackScanColor,
             WFSIPMIMAGEREQUEST.wImageScanColor and
             WFSIPMIMAGEDATA.wImageScanColor */

#define     WFS_IPM_SCANCOLORDEFAULT            (0x0000)
#define     WFS_IPM_SCANCOLORRED                (0x0001)
#define     WFS_IPM_SCANCOLORBLUE               (0x0002)
#define     WFS_IPM_SCANCOLORGREEN              (0x0004)
#define     WFS_IPM_SCANCOLORYELLOW             (0x0008)
#define     WFS_IPM_SCANCOLORWHITE              (0x0010)

/* Values of WFSIPMCAPS.fwCodelineFormat,
             WFSIPMCODELINEMAPPING.wCodelineFormat,
             WFSIPMCODELINEMAPPINGOUT.wCodelineFormat,
             WFSIPMMEDIAINREQUEST.wCodelineFormat and
             WFSIPMREADIMAGEIN.wCodelineFomat */

#define     WFS_IPM_CODELINECMC7                (0x0001)
#define     WFS_IPM_CODELINEE13B                (0x0002)
#define     WFS_IPM_CODELINEOCR                 (0x0004)

/* Values of WFSIPMCAPS.fwDataSource,
             WFSIPMIMAGEREQUEST.wImageSource and
             WFSIPMIMAGEDATA.wImageSource */

#define     WFS_IPM_IMAGEFRONT                  (0x0001)
#define     WFS_IPM_IMAGEBACK                   (0x0002)
#define     WFS_IPM_CODELINE                    (0x0004)

/* Values of WFSIPMCAPS.fwReturnedItemsProcessing */

#define     WFS_IPM_RETITEMENDORSE              (0x0001)
#define     WFS_IPM_RETITEMENDORSEIMAGE         (0x0002)

/* Values of WFSIPMMEDIABIN.fwType */

#define     WFS_IPM_TYPEMEDIAIN                 (0x0001)
#define     WFS_IPM_TYPERETRACT                 (0x0002)

/* Values of WFSIPMMEDIABIN.wMediaType */

#define     WFS_IPM_MEDIATYPIPM                 (0x0001)
#define     WFS_IPM_MEDIATYPCOMPOUND            (0x0002)

/* Values of WFSIPMMEDIABIN.usStatus */

#define     WFS_IPM_STATMBOK                    (1)
#define     WFS_IPM_STATMBFULL                  (2)
#define     WFS_IPM_STATMBHIGH                  (3)
#define     WFS_IPM_STATMBINOP                  (4)
#define     WFS_IPM_STATMBMISSING               (5)
#define     WFS_IPM_STATMBUNKNOWN               (6)

/* Values of WFSIPMTRANSSTATUS.wMediaInTransaction */

#define     WFS_IPM_MITOK                       (0)
#define     WFS_IPM_MITACTIVE                   (1)
#define     WFS_IPM_MITROLLBACK                 (2)
#define     WFS_IPM_MITROLLBACKAFTERDEPOSIT     (3)
#define     WFS_IPM_MITRETRACT                  (4)
#define     WFS_IPM_MITFAILURE                  (5)
#define     WFS_IPM_MITUNKNOWN                  (6)
#define     WFS_IPM_MITRESET                    (7)

/* Values of WFSIPMMEDIASTATUS.wMediaLocation */

#define     WFS_IPM_LOCATION_DEVICE             (0)
#define     WFS_IPM_LOCATION_BIN                (1)
#define     WFS_IPM_LOCATION_CUSTOMER           (2)
#define     WFS_IPM_LOCATION_UNKNOWN            (3)

/* Values of WFSIPMMEDIASTATUS.wCustomerAccess */

#define     WFS_IPM_ACCESSUNKNOWN               (0)
#define     WFS_IPM_ACCESSCUSTOMER              (1)
#define     WFS_IPM_ACCESSNONE                  (2)

/* Values of WFSIPMIMAGEDATA.wImageStatus */

#define     WFS_IPM_DATAOK                      (0)
#define     WFS_IPM_DATASRCNOTSUPP              (1)
#define     WFS_IPM_DATASRCMISSING              (2)

/* Values of WFSIPMMEDIASTATUS.wMagneticReadIndicator and
             WFSIPMMEDIADATA.wMagneticReadIndicator */

#define     WFS_IPM_MRI_MICR                    (0)
#define     WFS_IPM_MRI_NOT_MICR                (1)
#define     WFS_IPM_MRI_NO_MICR                 (2)
#define     WFS_IPM_MRI_UNKNOWN                 (3)
#define     WFS_IPM_MRI_NOTMICRFORMAT           (4)
#define     WFS_IPM_MRI_NOT_READ                (5)

/* Values of WFSIPMCAPS.fwInsertOrientation,
             WFSIPMMEDIASTATUS.fwInsertOrientation and
             WFSIPMMEDIADATA.fwInsertOrientation */

#define     WFS_IPM_INSUNKNOWN                  (0x0000)
#define     WFS_IPM_INSCODELINERIGHT            (0x0001)
#define     WFS_IPM_INSCODELINELEFT             (0x0002)
#define     WFS_IPM_INSCODELINEBOTTOM           (0x0004)
#define     WFS_IPM_INSCODELINETOP              (0x0008)
#define     WFS_IPM_INSFACEUP                   (0x0010)
#define     WFS_IPM_INSFACEDOWN                 (0x0020)

/* Values of WFSIPMMEDIASTATUS.wMediaValidity and
             WFSIPMMEDIADATA.wMediaValidity */

#define     WFS_IPM_ITEMOK                      (0)
#define     WFS_IPM_ITEMSUSPECT                 (1)
#define     WFS_IPM_ITEMUNKNOWN                 (2)
#define     WFS_IPM_ITEMNOVALIDATION            (3)

/* Values of WFSIPMSUPPLYREPLEN.fwSupplyReplen */

#define     WFS_IPM_REPLEN_TONER                (0x0001)
#define     WFS_IPM_REPLEN_INK                  (0x0002)

/* Values of WFSIPMMEDIAREFUSED.wReason */

#define     WFS_IPM_REFUSED_FOREIGNITEMS        (1)
#define     WFS_IPM_REFUSED_STACKERFULL         (2)
#define     WFS_IPM_REFUSED_CODELINEINVALID     (3)
#define     WFS_IPM_REFUSED_INVALIDMEDIA        (4)
#define     WFS_IPM_REFUSED_TOOLONG             (5)
#define     WFS_IPM_REFUSED_TOOSHORT            (6)
#define     WFS_IPM_REFUSED_TOOWIDE             (7)
#define     WFS_IPM_REFUSED_TOONARROW           (8)
#define     WFS_IPM_REFUSED_TOOTHICK            (9)
#define     WFS_IPM_REFUSED_INVALIDORIENTATION  (10)
#define     WFS_IPM_REFUSED_DOUBLEDETECT        (11)
#define     WFS_IPM_REFUSED_REFUSEPOSFULL       (12)
#define     WFS_IPM_REFUSED_RETURNBLOCKED       (13)
#define     WFS_IPM_REFUSED_INVALIDBUNCH        (14)
#define     WFS_IPM_REFUSED_OTHERITEM           (15)
#define     WFS_IPM_REFUSED_OTHERBUNCH          (16)
#define     WFS_IPM_REFUSED_JAMMING             (17)
#define     WFS_IPM_REFUSED_METAL               (18)

/* Values of WFSIPMMEDIAREFUSED.wMediaLocation and
             WFSIPMPRESENTMEDIA.wPosition */

#define     WFS_IPM_REFUSE_INPUT                (1)
#define     WFS_IPM_REFUSE_REFUSED              (2)
#define     WFS_IPM_REFUSE_REBUNCHER            (3)
#define     WFS_IPM_REFUSE_STACKER              (4)

/* Values of WFSIPMMBERROR.wFailure */

#define     WFS_IPM_MEDIABINJAMMED              (1)
#define     WFS_IPM_MEDIABINERROR               (2)
#define     WFS_IPM_MEDIABINFULL                (3)
#define     WFS_IPM_MEDIABINNOTCONF             (4)
#define     WFS_IPM_MEDIABININVALID             (5)
#define     WFS_IPM_MEDIABINCONFIG              (6)
#define     WFS_IPM_MEDIABINFEEDPROBLEM         (7)

/* Values of WFSIPMMEDIAREJECTED.wReason */

#define     WFS_IPM_REJECT_LONG                 (1)
#define     WFS_IPM_REJECT_THICK                (2)
#define     WFS_IPM_REJECT_DOUBLE               (3)
#define     WFS_IPM_REJECT_TRANSPORT            (4)
#define     WFS_IPM_REJECT_SHUTTER              (5)
#define     WFS_IPM_REJECT_REMOVED              (6)
#define     WFS_IPM_REJECT_METAL                (7)
#define     WFS_IPM_REJECT_FOREIGNITEMS         (8)
#define     WFS_IPM_REJECT_OTHER                (9)

/* Values of WFSIPMSCANNERTHRESHOLD.wScanner */

#define     WFS_IPM_FRONTSCANNER                (1)
#define     WFS_IPM_BACKSCANNER                 (2)

/* Values of WFSIPMSTATUS.wAntiFraudModule */

#define     WFS_IPM_AFMNOTSUPP                  (0)
#define     WFS_IPM_AFMOK                       (1)
#define     WFS_IPM_AFMINOP                     (2)
#define     WFS_IPM_AFMDEVICEDETECTED           (3)
#define     WFS_IPM_AFMUNKNOWN                  (4)

/* XFS IPM Errors */

#define     WFS_ERR_IPM_NOMEDIAPRESENT          (-(IPM_SERVICE_OFFSET + 1))
#define     WFS_ERR_IPM_MEDIABINFULL            (-(IPM_SERVICE_OFFSET + 2))
#define     WFS_ERR_IPM_STACKERFULL             (-(IPM_SERVICE_OFFSET + 3))
#define     WFS_ERR_IPM_SHUTTERFAIL             (-(IPM_SERVICE_OFFSET + 4))
#define     WFS_ERR_IPM_MEDIAJAMMED             (-(IPM_SERVICE_OFFSET + 5))
#define     WFS_ERR_IPM_FILEIOERROR             (-(IPM_SERVICE_OFFSET + 6))
#define     WFS_ERR_IPM_INKOUT                  (-(IPM_SERVICE_OFFSET + 7))
#define     WFS_ERR_IPM_TONEROUT                (-(IPM_SERVICE_OFFSET + 8))
#define     WFS_ERR_IPM_SCANNERINOP             (-(IPM_SERVICE_OFFSET + 9))
#define     WFS_ERR_IPM_MICRINOP                (-(IPM_SERVICE_OFFSET + 10))
#define     WFS_ERR_IPM_SEQUENCEINVALID         (-(IPM_SERVICE_OFFSET + 11))
#define     WFS_ERR_IPM_INVALID_PORT            (-(IPM_SERVICE_OFFSET + 12))
#define     WFS_ERR_IPM_FOREIGNITEMSDETECTED    (-(IPM_SERVICE_OFFSET + 13))
#define     WFS_ERR_IPM_INVALIDMEDIAID          (-(IPM_SERVICE_OFFSET + 14))
#define     WFS_ERR_IPM_MEDIABINERROR           (-(IPM_SERVICE_OFFSET + 15))
#define     WFS_ERR_IPM_POSITIONNOTEMPTY        (-(IPM_SERVICE_OFFSET + 16))
#define     WFS_ERR_IPM_INVALIDBIN              (-(IPM_SERVICE_OFFSET + 17))
#define     WFS_ERR_IPM_NOBIN                   (-(IPM_SERVICE_OFFSET + 18))
#define     WFS_ERR_IPM_REFUSEDITEMS            (-(IPM_SERVICE_OFFSET + 19))
#define     WFS_ERR_IPM_ALLBINSFULL             (-(IPM_SERVICE_OFFSET + 20))
#define     WFS_ERR_IPM_FEEDERNOTEMPTY          (-(IPM_SERVICE_OFFSET + 21))
#define     WFS_ERR_IPM_MEDIAREJECTED           (-(IPM_SERVICE_OFFSET + 22))
#define     WFS_ERR_IPM_FEEDERINOPERATIVE       (-(IPM_SERVICE_OFFSET + 23))
#define     WFS_ERR_IPM_MEDIAPRESENT            (-(IPM_SERVICE_OFFSET + 24))
#define     WFS_ERR_IPM_POWERSAVETOOSHORT       (-(IPM_SERVICE_OFFSET + 25))
#define     WFS_ERR_IPM_POWERSAVEMEDIAPRESENT   (-(IPM_SERVICE_OFFSET + 26))
#define     WFS_ERR_IPM_CASHINACTIVE            (-(IPM_SERVICE_OFFSET + 27))
#define     WFS_ERR_IPM_MEDIAINACTIVE           (-(IPM_SERVICE_OFFSET + 28))

/*=================================================================*/
/* IPM Info Command Structures */
/*=================================================================*/

typedef struct _wfs_ipm_pos
{
    WORD                   wShutter;
    WORD                   wPositionStatus;
    WORD                   wTransport;
    WORD                   wTransportMediaStatus;
} WFSIPMPOS, *LPWFSIPMPOS;

typedef struct _wfs_ipm_status
{
    WORD                   fwDevice;
    WORD                   wAcceptor;
    WORD                   wMedia;
    WORD                   wToner;
    WORD                   wInk;
    WORD                   wFrontImageScanner;
    WORD                   wBackImageScanner;
    WORD                   wMICRReader;
    WORD                   wStacker;
    WORD                   wReBuncher;
    WORD                   wMediaFeeder;
    LPWFSIPMPOS            *lppPositions;
    DWORD                  dwGuidLights[WFS_IPM_GUIDLIGHTS_SIZE];
    LPSTR                  lpszExtra;
    WORD                   wDevicePosition;
    USHORT                 usPowerSaveRecoveryTime;
    WORD                   wMixedMode;
    WORD                   wAntiFraudModule;
} WFSIPMSTATUS, *LPWFSIPMSTATUS;

typedef struct _wfs_ipm_print_size
{
    WORD                   wRows;
    WORD                   wCols;
} WFSIPMPRINTSIZE, *LPWFSIPMPRINTSIZE;

typedef struct _wfs_ipm_pos_caps
{
    BOOL                   bItemsTakenSensor;
    BOOL                   bItemsInsertedSensor;
    WORD                   fwRetractAreas;
} WFSIPMPOSCAPS, *LPWFSIPMPOSCAPS;

/* WFS_INF_IPM_CAPABILITIES output structures */

typedef struct _wfs_ipm_caps
{
    WORD                   wClass;
    WORD                   fwType;
    BOOL                   bCompound;
    USHORT                 usMaxMediaOnStacker;
    LPWFSIPMPRINTSIZE      lpPrintSize;
    BOOL                   bStamp;
    BOOL                   bRescan;
    BOOL                   bPresentControl;
    BOOL                   bApplicationRefuse;
    WORD                   fwRetractLocation;
    WORD                   fwResetControl;
    BOOL                   bRetractCountsItems;
    WORD                   fwImageType;
    WORD                   fwFrontImageColorFormat;
    WORD                   fwBackImageColorFormat;
    WORD                   fwFrontScanColor;
    WORD                   wDefaultFrontScanColor;
    WORD                   fwBackScanColor;
    WORD                   wDefaultBackScanColor;
    WORD                   fwCodelineFormat;
    WORD                   fwDataSource;
    WORD                   fwInsertOrientation;
    LPWFSIPMPOSCAPS        *lppPositions;
    DWORD                  dwGuidLights[WFS_IPM_GUIDLIGHTS_SIZE];
    LPSTR                  lpszExtra;
    BOOL                   bPowerSaveControl;
    BOOL                   bImageAfterEndorse;
    WORD                   fwReturnedItemsProcessing;
    WORD                   wMixedMode;
    BOOL                   bMixedDepositAndRollback;
    BOOL                   bAntiFraudModule;
} WFSIPMCAPS, *LPWFSIPMCAPS;

typedef struct _wfs_ipm_hex_data
{
    USHORT                 usLength;
    LPBYTE                 lpbData;
} WFSIPMXDATA, *LPWFSIPMXDATA;

/* WFS_INF_IPM_CODELINE_MAPPING input and output structures */

typedef struct _wfs_ipm_codeline_mapping
{
    WORD                   wCodelineFormat;
} WFSIPMCODELINEMAPPING, *LPWFSIPMCODELINEMAPPING;

typedef struct _wfs_ipm_codeline_mapping_out
{
    WORD                   wCodelineFormat;
    LPWFSIPMXDATA          lpxCharMapping;
} WFSIPMCODELINEMAPPINGOUT, *LPWFSIPMCODELINEMAPPINGOUT;

/* WFS_INF_IPM_MEDIA_BIN_INFO output structures */

typedef struct _wfs_ipm_media_bin
{
    USHORT                 usBinNumber;
    LPSTR                  lpstrPositionName;
    WORD                   fwType;
    WORD                   wMediaType;
    LPSTR                  lpstrBinID;
    ULONG                  ulMediaInCount;
    ULONG                  ulCount;
    ULONG                  ulRetractOperations;
    BOOL                   bHardwareSensors;
    ULONG                  ulMaximumItems;
    ULONG                  ulMaximumRetractOperations;
    USHORT                 usStatus;
    LPSTR                  lpszExtra;
} WFSIPMMEDIABIN, *LPWFSIPMMEDIABIN;

typedef struct _wfs_ipm_media_bin_info
{
    USHORT                 usCount;
    LPWFSIPMMEDIABIN       *lppMediaBin;
} WFSIPMMEDIABININFO, *LPWFSIPMMEDIABININFO;

typedef struct _wfs_ipm_image_data
{
    WORD                   wImageSource;
    WORD                   wImageType;
    WORD                   wImageColorFormat;
    WORD                   wImageScanColor;
    WORD                   wImageStatus;
    LPSTR                  lpszImageFile;
} WFSIPMIMAGEDATA, *LPWFSIPMIMAGEDATA;

typedef struct _wfs_ipm_media_size
{
    ULONG                  ulSizeX;
    ULONG                  ulSizeY;
} WFSIPMMEDIASIZE, *LPWFSIPMMEDIASIZE;

typedef struct _wfs_ipm_mediastatus
{
    USHORT                 usMediaID;
    WORD                   wMediaLocation;
    USHORT                 usBinNumber;
    ULONG                  ulCodelineDataLength;
    LPBYTE                 lpbCodelineData;
    WORD                   wMagneticReadIndicator;
    LPWFSIPMIMAGEDATA      *lppImage;
    WORD                   fwInsertOrientation;
    LPWFSIPMMEDIASIZE      lpMediaSize;
    WORD                   wMediaValidity;
    WORD                   wCustomerAccess;
} WFSIPMMEDIASTATUS, *LPWFSIPMMEDIASTATUS;

/* WFS_INF_IPM_TRANSACTION_STATUS output structures */

typedef struct _wfs_ipm_trans_status
{
    WORD                   wMediaInTransaction;
    USHORT                 usMediaOnStacker;
    USHORT                 usLastMediaInTotal;
    USHORT                 usLastMediaAddedToStacker;
    USHORT                 usTotalItems;
    USHORT                 usTotalItemsRefused;
    USHORT                 usTotalBunchesRefused;
    LPWFSIPMMEDIASTATUS    *lppMediaInfo;
    LPSTR                  lpszExtra;
} WFSIPMTRANSSTATUS, *LPWFSIPMTRANSSTATUS;

/*=================================================================*/
/* IPM Execute Command Structures */
/*=================================================================*/

typedef struct _wfs_ipm_image_request
{
    WORD                   wImageSource;
    WORD                   wImageType;
    WORD                   wImageColorFormat;
    WORD                   wImageScanColor;
    LPSTR                  lpszImagePath;
} WFSIPMIMAGEREQUEST, *LPWFSIPMIMAGEREQUEST;

typedef struct _wfs_ipm_media_in_request
{
    WORD                   wCodelineFormat;
    LPWFSIPMIMAGEREQUEST   *lppImage;
    USHORT                 usMaxMediaOnStacker;
    BOOL                   bApplicationRefuse;
} WFSIPMMEDIAINREQUEST, *LPWFSIPMMEDIAINREQUEST;

typedef struct _wfs_ipm_media_in
{
    USHORT                 usMediaOnStacker;
    USHORT                 usLastMedia;
    USHORT                 usLastMediaOnStacker;
    WORD                   wMediaFeeder;
} WFSIPMMEDIAIN, *LPWFSIPMMEDIAIN;

/* WFS_CMD_IPM_MEDIA_IN_END structures */

typedef struct _wfs_ipm_media_in_end
{
    USHORT                 usItemsReturned;
    USHORT                 usItemsRefused;
    USHORT                 usBunchesRefused;
    LPWFSIPMMEDIABININFO   lpMediaBinInfo;
} WFSIPMMEDIAINEND, *LPWFSIPMMEDIAINEND;

typedef struct _wfs_ipm_read_image_request
{
    USHORT                 usMediaID;
    WORD                   wCodelineFormat;
    LPWFSIPMIMAGEREQUEST   *lppImage;
} WFSIPMREADIMAGEIN, *LPWFSIPMREADIMAGEIN;

typedef struct _wfs_ipm_mediadata
{
    USHORT                 usMediaID;
    ULONG                  ulCodelineDataLength;
    LPBYTE                 lpbCodelineData;
    WORD                   wMagneticReadIndicator;
    LPWFSIPMIMAGEDATA      *lppImage;
    WORD                   fwInsertOrientation;
    LPWFSIPMMEDIASIZE      lpMediaSize;
    WORD                   wMediaValidity;
} WFSIPMMEDIADATA, *LPWFSIPMMEDIADATA;

/* WFS_CMD_IPM_SET_DESTINATION structures */

typedef struct _wfs_ipm_set_destination
{
    USHORT                 usMediaID;
    USHORT                 usBinNumber;
} WFSIPMSETDESTINATION, *LPWFSIPMSETDESTINATION;

typedef struct _wfs_ipm_next_item_out
{
    WORD                   wMediaFeeder;
} WFSIPMNEXTITEMOUT, *LPWFSIPMNEXTITEMOUT;

/* WFS_CMD_IPM_PRESENT_MEDIA structures */

typedef struct _wfs_ipm_present_media
{
    WORD                   wPosition;
} WFSIPMPRESENTMEDIA, *LPWFSIPMPRESENTMEDIA;

/* WFS_CMD_IPM_RETRACT_MEDIA structures */

typedef struct _wfs_ipm_retract_media
{
    WORD                   wRetractLocation;
    USHORT                 usBinNumber;
} WFSIPMRETRACTMEDIA, *LPWFSIPMRETRACTMEDIA;

typedef struct _wfs_ipm_retract_media_out
{
    USHORT                 usMedia;
    WORD                   wRetractLocation;
    USHORT                 usBinNumber;
} WFSIPMRETRACTMEDIAOUT, *LPWFSIPMRETRACTMEDIAOUT;

/* WFS_CMD_IPM_PRINT_TEXT structures */

typedef struct _wfs_ipm_print_text
{
    USHORT                 usMediaID;
    BOOL                   bStamp;
    LPWSTR                 lpszPrintData;
} WFSIPMPRINTTEXT, *LPWFSIPMPRINTTEXT;

/* WFS_CMD_IPM_GET_IMAGE_AFTER_PRINT structures */

typedef struct _wfs_ipm_get_image_after_print
{
    USHORT                 usMediaID;
    LPWFSIPMIMAGEREQUEST   *lppImage;
} WFSIPMGETIMAGEAFTERPRINT, *LPWFSIPMGETIMAGEAFTERPRINT;

/* WFS_CMD_IPM_ACCEPT_ITEM structures */

typedef struct _wfs_ipm_accept_item
{
    BOOL                   bAccept;
} WFSIPMACCEPTITEM, *LPWFSIPMACCEPTITEM;

/* WFS_CMD_IPM_RESET structures */

typedef struct _wfs_ipm_reset
{
    WORD                   wMediaControl;
    USHORT                 usBinNumber;
} WFSIPMRESET, *LPWFSIPMRESET;

/* WFS_CMD_IPM_SUPPLY_REPLENISH structures */

typedef struct _wfs_ipm_supply_replen
{
    WORD                   fwSupplyReplen;
} WFSIPMSUPPLYREPLEN, *LPWFSIPMSUPPLYREPLEN;

/* WFS_CMD_IPM_SET_GUIDANCE_LIGHT structures */

typedef struct _wfs_ipm_set_guidlight
{
    WORD                   wGuidLight;
    DWORD                  dwCommand;
} WFSIPMSETGUIDLIGHT, *LPWFSIPMSETGUIDLIGHT;

/* WFS_CMD_IPM_POWER_SAVE_CONTROL structure */

typedef struct _wfs_ipm_power_save_control
{
    USHORT                 usMaxPowerSaveRecoveryTime;
} WFSIPMPOWERSAVECONTROL, *LPWFSIPMPOWERSAVECONTROL;

typedef struct _wfs_ipm_setmode
{
    WORD                   wMixedMode;
} WFSIPMSETMODE, *LPWFSIPMSETMODE;

/*=================================================================*/
/* IPM Message Structures */
/*=================================================================*/

/* WFS_EXEE_IPM_MEDIABINERROR structure */

typedef struct _wfs_ipm_mb_error
{
    WORD                   wFailure;
    LPWFSIPMMEDIABIN       lpMediaBin;
} WFSIPMMBERROR, *LPWFSIPMMBERROR;

/* WFS_SRVE_IPM_MEDIATAKEN structure */

typedef struct _wfs_ipm_position
{
    WORD                   wPosition;
} WFSIPMPOSITION, *LPWFSIPMPOSITION;

/* WFS_USRE_IPM_TONERTHRESHOLD and
   WFS_USRE_IPM_INKTHRESHOLD structures */

typedef struct _wfs_ipm_threshold
{
    WORD                   wThreshold;
} WFSIPMTHRESHOLD, *LPWFSIPMTHRESHOLD;

/* WFS_USRE_IPM_SCANNERTHRESHOLD structure */

typedef struct _wfs_ipm_scanner_threshold
{
    WORD                   wScanner;
    WORD                   wThreshold;
} WFSIPMSCANNERTHRESHOLD, *LPWFSIPMSCANNERTHRESHOLD;

/* WFS_SRVE_IPM_MEDIADETECTED structure */

typedef struct _wfs_ipm_media_detected
{
    WORD                   wPosition;
    USHORT                 usRetractBinNumber;
} WFSIPMMEDIADETECTED, *LPWFSIPMMEDIADETECTED;

/* WFS_EXEE_IPM_MEDIAPRESENTED structure */

typedef struct _wfs_ipm_media_presented
{
    WORD                   wPosition;
    USHORT                 usBunchIndex;
    USHORT                 usTotalBunches;
} WFSIPMMEDIAPRESENTED, *LPWFSIPMMEDIAPRESENTED;

/* WFS_EXEE_IPM_MEDIAREFUSED structure */

typedef struct _wfs_ipm_media_refused
{
    WORD                   wReason;
    WORD                   wMediaLocation;
    BOOL                   bPresentRequired;
    LPWFSIPMMEDIASIZE      lpMediaSize;
} WFSIPMMEDIAREFUSED, *LPWFSIPMMEDIAREFUSED;

/* WFS_EXEE_IPM_MEDIAREJECTED structure */

typedef struct _wfs_ipm_media_rejected
{
    WORD                   wReason;
} WFSIPMMEDIAREJECTED, *LPWFSIPMMEDIAREJECTED;

/* WFS_SRVE_IPM_DEVICEPOSITION structure */

typedef struct _wfs_ipm_device_position
{
    WORD                   wPosition;
} WFSIPMDEVICEPOSITION, *LPWFSIPMDEVICEPOSITION;

/* WFS_SRVE_IPM_POWERSAVECHANGE structure */

typedef struct _wfs_ipm_power_save_change
{
    USHORT                 usPowerSaveRecoveryTime;
} WFSIPMPOWERSAVECHANGE, *LPWFSIPMPOWERSAVECHANGE;

/*   restore alignment   */
#pragma pack(pop)

#ifdef __cplusplus
}       /*extern "C"*/
#endif

#endif    /* __INC_XFSIPM__H */
