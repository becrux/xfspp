/******************************************************************************
*                                                                             *
* xfscdm.h      XFS - Cash Dispenser (CDM) definitions                        *
*                                                                             *
*               Version 3.30  (March 19 2015)                                 *
*                                                                             *
******************************************************************************/

#ifndef __INC_XFSCDM__H
#define __INC_XFSCDM__H

#ifdef __cplusplus
extern "C" {
#endif

#include "xfsapi.h"

	/* be aware of alignment */
#pragma pack (push, 1)

	/* values of WFSCDMCAPS.wClass */

#define     WFS_SERVICE_CLASS_CDM                     (3)
#define     WFS_SERVICE_CLASS_VERSION_CDM             (0x1E03) /* Version 3.30 */
#define     WFS_SERVICE_CLASS_NAME_CDM                "CDM"

#define     CDM_SERVICE_OFFSET                        (WFS_SERVICE_CLASS_CDM * 100)

	/* CDM Info Commands */

#define     WFS_INF_CDM_STATUS                        (CDM_SERVICE_OFFSET + 1)
#define     WFS_INF_CDM_CAPABILITIES                  (CDM_SERVICE_OFFSET + 2)
#define     WFS_INF_CDM_CASH_UNIT_INFO                (CDM_SERVICE_OFFSET + 3)
#define     WFS_INF_CDM_TELLER_INFO                   (CDM_SERVICE_OFFSET + 4)
#define     WFS_INF_CDM_CURRENCY_EXP                  (CDM_SERVICE_OFFSET + 6)
#define     WFS_INF_CDM_MIX_TYPES                     (CDM_SERVICE_OFFSET + 7)
#define     WFS_INF_CDM_MIX_TABLE                     (CDM_SERVICE_OFFSET + 8)
#define     WFS_INF_CDM_PRESENT_STATUS                (CDM_SERVICE_OFFSET + 9)
#define     WFS_INF_CDM_GET_ITEM_INFO                 (CDM_SERVICE_OFFSET + 10)
#define     WFS_INF_CDM_GET_BLACKLIST                 (CDM_SERVICE_OFFSET + 11)
#define     WFS_INF_CDM_GET_ALL_ITEMS_INFO            (CDM_SERVICE_OFFSET + 12)


	/* CDM Execute Commands */

#define     WFS_CMD_CDM_DENOMINATE                    (CDM_SERVICE_OFFSET + 1)
#define     WFS_CMD_CDM_DISPENSE                      (CDM_SERVICE_OFFSET + 2)
#define     WFS_CMD_CDM_PRESENT                       (CDM_SERVICE_OFFSET + 3)
#define     WFS_CMD_CDM_REJECT                        (CDM_SERVICE_OFFSET + 4)
#define     WFS_CMD_CDM_RETRACT                       (CDM_SERVICE_OFFSET + 5)
#define     WFS_CMD_CDM_OPEN_SHUTTER                  (CDM_SERVICE_OFFSET + 7)
#define     WFS_CMD_CDM_CLOSE_SHUTTER                 (CDM_SERVICE_OFFSET + 8)
#define     WFS_CMD_CDM_SET_TELLER_INFO               (CDM_SERVICE_OFFSET + 9)
#define     WFS_CMD_CDM_SET_CASH_UNIT_INFO            (CDM_SERVICE_OFFSET + 10)
#define     WFS_CMD_CDM_START_EXCHANGE                (CDM_SERVICE_OFFSET + 11)
#define     WFS_CMD_CDM_END_EXCHANGE                  (CDM_SERVICE_OFFSET + 12)
#define     WFS_CMD_CDM_OPEN_SAFE_DOOR                (CDM_SERVICE_OFFSET + 13)
#define     WFS_CMD_CDM_CALIBRATE_CASH_UNIT           (CDM_SERVICE_OFFSET + 15)
#define     WFS_CMD_CDM_SET_MIX_TABLE                 (CDM_SERVICE_OFFSET + 20)
#define     WFS_CMD_CDM_RESET                         (CDM_SERVICE_OFFSET + 21)
#define     WFS_CMD_CDM_TEST_CASH_UNITS               (CDM_SERVICE_OFFSET + 22)
#define     WFS_CMD_CDM_COUNT                         (CDM_SERVICE_OFFSET + 23)
#define     WFS_CMD_CDM_SET_GUIDANCE_LIGHT            (CDM_SERVICE_OFFSET + 24)
#define     WFS_CMD_CDM_POWER_SAVE_CONTROL            (CDM_SERVICE_OFFSET + 25)
#define     WFS_CMD_CDM_PREPARE_DISPENSE              (CDM_SERVICE_OFFSET + 26)
#define     WFS_CMD_CDM_SET_BLACKLIST                 (CDM_SERVICE_OFFSET + 27)
#define     WFS_CMD_CDM_SYNCHRONIZE_COMMAND           (CDM_SERVICE_OFFSET + 28)



	/* CDM Messages */

#define     WFS_SRVE_CDM_SAFEDOOROPEN                 (CDM_SERVICE_OFFSET + 1)
#define     WFS_SRVE_CDM_SAFEDOORCLOSED               (CDM_SERVICE_OFFSET + 2)
#define     WFS_USRE_CDM_CASHUNITTHRESHOLD            (CDM_SERVICE_OFFSET + 3)
#define     WFS_SRVE_CDM_CASHUNITINFOCHANGED          (CDM_SERVICE_OFFSET + 4)
#define     WFS_SRVE_CDM_TELLERINFOCHANGED            (CDM_SERVICE_OFFSET + 5)
#define     WFS_EXEE_CDM_DELAYEDDISPENSE              (CDM_SERVICE_OFFSET + 6)
#define     WFS_EXEE_CDM_STARTDISPENSE                (CDM_SERVICE_OFFSET + 7)
#define     WFS_EXEE_CDM_CASHUNITERROR                (CDM_SERVICE_OFFSET + 8)
#define     WFS_SRVE_CDM_ITEMSTAKEN                   (CDM_SERVICE_OFFSET + 9)
#define     WFS_EXEE_CDM_PARTIALDISPENSE              (CDM_SERVICE_OFFSET + 10)
#define     WFS_EXEE_CDM_SUBDISPENSEOK                (CDM_SERVICE_OFFSET + 11)
#define     WFS_SRVE_CDM_ITEMSPRESENTED               (CDM_SERVICE_OFFSET + 13)
#define     WFS_SRVE_CDM_COUNTS_CHANGED               (CDM_SERVICE_OFFSET + 14)
#define     WFS_EXEE_CDM_INCOMPLETEDISPENSE           (CDM_SERVICE_OFFSET + 15)
#define     WFS_EXEE_CDM_NOTEERROR                    (CDM_SERVICE_OFFSET + 16)
#define     WFS_SRVE_CDM_MEDIADETECTED                (CDM_SERVICE_OFFSET + 17)
#define     WFS_EXEE_CDM_INPUT_P6                     (CDM_SERVICE_OFFSET + 18)
#define     WFS_SRVE_CDM_DEVICEPOSITION               (CDM_SERVICE_OFFSET + 19)
#define     WFS_SRVE_CDM_POWER_SAVE_CHANGE            (CDM_SERVICE_OFFSET + 20)
#define     WFS_EXEE_CDM_INFO_AVAILABLE               (CDM_SERVICE_OFFSET + 21)
#define     WFS_EXEE_CDM_INCOMPLETERETRACT            (CDM_SERVICE_OFFSET + 22)
#define     WFS_SRVE_CDM_SHUTTERSTATUSCHANGED         (CDM_SERVICE_OFFSET + 23)

	/* values of WFSCDMSTATUS.fwDevice */

#define     WFS_CDM_DEVONLINE                         WFS_STAT_DEVONLINE
#define     WFS_CDM_DEVOFFLINE                        WFS_STAT_DEVOFFLINE
#define     WFS_CDM_DEVPOWEROFF                       WFS_STAT_DEVPOWEROFF
#define     WFS_CDM_DEVNODEVICE                       WFS_STAT_DEVNODEVICE
#define     WFS_CDM_DEVHWERROR                        WFS_STAT_DEVHWERROR
#define     WFS_CDM_DEVUSERERROR                      WFS_STAT_DEVUSERERROR
#define     WFS_CDM_DEVBUSY                           WFS_STAT_DEVBUSY
#define     WFS_CDM_DEVFRAUDATTEMPT                   WFS_STAT_DEVFRAUDATTEMPT
#define     WFS_CDM_DEVPOTENTIALFRAUD                 WFS_STAT_DEVPOTENTIALFRAUD

	/* values of WFSCDMSTATUS.fwSafeDoor */

#define     WFS_CDM_DOORNOTSUPPORTED                  (1)
#define     WFS_CDM_DOOROPEN                          (2)
#define     WFS_CDM_DOORCLOSED                        (3)
#define     WFS_CDM_DOORUNKNOWN                       (5)

	/* values of WFSCDMSTATUS.fwDispenser */

#define     WFS_CDM_DISPOK                            (0)
#define     WFS_CDM_DISPCUSTATE                       (1)
#define     WFS_CDM_DISPCUSTOP                        (2)
#define     WFS_CDM_DISPCUUNKNOWN                     (3)

	/* values of WFSCDMSTATUS.fwIntermediateStacker */

#define     WFS_CDM_ISEMPTY                           (0)
#define     WFS_CDM_ISNOTEMPTY                        (1)
#define     WFS_CDM_ISNOTEMPTYCUST                    (2)
#define     WFS_CDM_ISNOTEMPTYUNK                     (3)
#define     WFS_CDM_ISUNKNOWN                         (4)
#define     WFS_CDM_ISNOTSUPPORTED                    (5)

	/* Size and max index of dwGuidLights array */

#define     WFS_CDM_GUIDLIGHTS_SIZE                   (32)
#define     WFS_CDM_GUIDLIGHTS_MAX                    (WFS_CDM_GUIDLIGHTS_SIZE - 1)

	/* Indices of WFSCDMSTATUS.dwGuidLights [...]
	WFSCDMCAPS.dwGuidLights [...] */

#define     WFS_CDM_GUIDANCE_POSOUTNULL               (0)
#define     WFS_CDM_GUIDANCE_POSOUTLEFT               (1)
#define     WFS_CDM_GUIDANCE_POSOUTRIGHT              (2)
#define     WFS_CDM_GUIDANCE_POSOUTCENTER             (3)
#define     WFS_CDM_GUIDANCE_POSOUTTOP                (4)
#define     WFS_CDM_GUIDANCE_POSOUTBOTTOM             (5)
#define     WFS_CDM_GUIDANCE_POSOUTFRONT              (6)
#define     WFS_CDM_GUIDANCE_POSOUTREAR               (7)

	/* Values of WFSCDMSTATUS.dwGuidLights [...]
	WFSCDMCAPS.dwGuidLights [...] */

#define     WFS_CDM_GUIDANCE_OFF                      (0x00000001)
#define     WFS_CDM_GUIDANCE_SLOW_FLASH               (0x00000004)
#define     WFS_CDM_GUIDANCE_MEDIUM_FLASH             (0x00000008)
#define     WFS_CDM_GUIDANCE_QUICK_FLASH              (0x00000010)
#define     WFS_CDM_GUIDANCE_CONTINUOUS               (0x00000080)
#define     WFS_CDM_GUIDANCE_RED                      (0x00000100)
#define     WFS_CDM_GUIDANCE_GREEN                    (0x00000200)
#define     WFS_CDM_GUIDANCE_YELLOW                   (0x00000400)
#define     WFS_CDM_GUIDANCE_BLUE                     (0x00000800)
#define     WFS_CDM_GUIDANCE_CYAN                     (0x00001000)
#define     WFS_CDM_GUIDANCE_MAGENTA                  (0x00002000)
#define     WFS_CDM_GUIDANCE_WHITE                    (0x00004000)
#define     WFS_CDM_GUIDANCE_EXIT                     (0x00200000)

	/* Values of WFSCDMSTATUS.dwGuidLights [...]
	WFSCDMCAPS.dwGuidLights [...] */

#define     WFS_CDM_GUIDANCE_NOT_AVAILABLE            (0x0000)

	/* values of WFSCDMSTATUS.wDevicePosition
	WFSCDMDEVICEPOSITION.wPosition */

#define     WFS_CDM_DEVICEINPOSITION                  (0)
#define     WFS_CDM_DEVICENOTINPOSITION               (1)
#define     WFS_CDM_DEVICEPOSUNKNOWN                  (2)
#define     WFS_CDM_DEVICEPOSNOTSUPP                  (3)

	/* values of WFSCDMOUTPOS.fwShutter */

#define     WFS_CDM_SHTCLOSED                         (0)
#define     WFS_CDM_SHTOPEN                           (1)
#define     WFS_CDM_SHTJAMMED                         (2)
#define     WFS_CDM_SHTUNKNOWN                        (3)
#define     WFS_CDM_SHTNOTSUPPORTED                   (4)

	/* values of WFSCDMOUTPOS.fwPositionStatus */

#define     WFS_CDM_PSEMPTY                           (0)
#define     WFS_CDM_PSNOTEMPTY                        (1)
#define     WFS_CDM_PSUNKNOWN                         (2)
#define     WFS_CDM_PSNOTSUPPORTED                    (3)

	/* values of WFSCDMOUTPOS.fwTransport */

#define     WFS_CDM_TPOK                              (0)
#define     WFS_CDM_TPINOP                            (1)
#define     WFS_CDM_TPUNKNOWN                         (2)
#define     WFS_CDM_TPNOTSUPPORTED                    (3)

	/* values of WFSCDMOUTPOS.fwTransportStatus */

#define     WFS_CDM_TPSTATEMPTY                       (0)
#define     WFS_CDM_TPSTATNOTEMPTY                    (1)
#define     WFS_CDM_TPSTATNOTEMPTYCUST                (2)
#define     WFS_CDM_TPSTATNOTEMPTY_UNK                (3)
#define     WFS_CDM_TPSTATNOTSUPPORTED                (4)

	/* values of WFSCDMOUTPOS.fwJammedShutterPosition */

#define     WFS_CDM_SHUTTERPOS_NOTSUPPORTED           (0)
#define     WFS_CDM_SHUTTERPOS_NOTJAMMED              (1)
#define     WFS_CDM_SHUTTERPOS_OPEN                   (2)
#define     WFS_CDM_SHUTTERPOS_PARTIALLY_OPEN         (3)
#define     WFS_CDM_SHUTTERPOS_CLOSED                 (4)
#define     WFS_CDM_SHUTTERPOS_UNKNOWN                (5)

	/* values of WFSCDMCAPS.fwType */

#define     WFS_CDM_TELLERBILL                        (0)
#define     WFS_CDM_SELFSERVICEBILL                   (1)
#define     WFS_CDM_TELLERCOIN                        (2)
#define     WFS_CDM_SELFSERVICECOIN                   (3)

	/* values of WFSCDMCAPS.fwRetractAreas,
	WFSCDMRETRACT.usRetractArea */

#define     WFS_CDM_RA_RETRACT                        (0x0001)
#define     WFS_CDM_RA_TRANSPORT                      (0x0002)
#define     WFS_CDM_RA_STACKER                        (0x0004)
#define     WFS_CDM_RA_REJECT                         (0x0008)
#define     WFS_CDM_RA_NOTSUPP                        (0x0010)
#define     WFS_CDM_RA_ITEMCASSETTE                   (0x0020)

	/* values of WFSCDMCAPS.fwRetractTransportActions,
	WFSCDMCAPS.fwRetractStackerActions */

#define     WFS_CDM_PRESENT                           (0x0001)
#define     WFS_CDM_RETRACT                           (0x0002)
#define     WFS_CDM_REJECT                            (0x0004)
#define     WFS_CDM_NOTSUPP                           (0x0008)
#define     WFS_CDM_ITEMCASSETTE                      (0x0010)

	/* values of WFSCDMCAPS.fwMoveItems */

#define     WFS_CDM_FROMCU                            (0x0001)
#define     WFS_CDM_TOCU                              (0x0002)
#define     WFS_CDM_TOTRANSPORT                       (0x0004)
#define     WFS_CDM_TOSTACKER                         (0x0008)

	/* values of WFSCDMCASHUNIT.usType */

#define     WFS_CDM_TYPENA                            (1)
#define     WFS_CDM_TYPEREJECTCASSETTE                (2)
#define     WFS_CDM_TYPEBILLCASSETTE                  (3)
#define     WFS_CDM_TYPECOINCYLINDER                  (4)
#define     WFS_CDM_TYPECOINDISPENSER                 (5)
#define     WFS_CDM_TYPERETRACTCASSETTE               (6)
#define     WFS_CDM_TYPECOUPON                        (7)
#define     WFS_CDM_TYPEDOCUMENT                      (8)
#define     WFS_CDM_TYPEREPCONTAINER                  (11)
#define     WFS_CDM_TYPERECYCLING                     (12)

	/* values of WFSCDMCASHUNIT.usStatus */

#define     WFS_CDM_STATCUOK                          (0)
#define     WFS_CDM_STATCUFULL                        (1)
#define     WFS_CDM_STATCUHIGH                        (2)
#define     WFS_CDM_STATCULOW                         (3)
#define     WFS_CDM_STATCUEMPTY                       (4)
#define     WFS_CDM_STATCUINOP                        (5)
#define     WFS_CDM_STATCUMISSING                     (6)
#define     WFS_CDM_STATCUNOVAL                       (7)
#define     WFS_CDM_STATCUNOREF                       (8)
#define     WFS_CDM_STATCUMANIP                       (9)

	/* values of WFSCDMMIXTYPE.usMixType */

#define     WFS_CDM_MIXALGORITHM                      (1)
#define     WFS_CDM_MIXTABLE                          (2)

	/* values of WFSCDMMIXTYPE.usMixNumber */

#define     WFS_CDM_INDIVIDUAL                        (0)

	/* values of WFSCDMMIXTYPE.usSubType (predefined mix algorithms) */

#define     WFS_CDM_MIX_MINIMUM_NUMBER_OF_BILLS       (1)
#define     WFS_CDM_MIX_EQUAL_EMPTYING_OF_CASH_UNITS  (2)
#define     WFS_CDM_MIX_MAXIMUM_NUMBER_OF_CASH_UNITS  (3)

	/* values of WFSCDMPRESENTSTATUS.wPresentState */

#define     WFS_CDM_PRESENTED                         (1)
#define     WFS_CDM_NOTPRESENTED                      (2)
#define     WFS_CDM_UNKNOWN                           (3)

	/* values of WFSCDMDISPENSE.fwPosition,
	WFSCDMCAPS.fwPositions,
	WFSCDMOUTPOS.fwPosition,
	WFSCDMTELLERDETAILS.fwOutputPosition,
	WFSCDMPHYSICALCU.fwPosition */

#define     WFS_CDM_POSNULL                           (0x0000)
#define     WFS_CDM_POSLEFT                           (0x0001)
#define     WFS_CDM_POSRIGHT                          (0x0002)
#define     WFS_CDM_POSCENTER                         (0x0004)
#define     WFS_CDM_POSTOP                            (0x0040)
#define     WFS_CDM_POSBOTTOM                         (0x0080)
#define     WFS_CDM_POSFRONT                          (0x0800)
#define     WFS_CDM_POSREAR                           (0x1000)

	/* additional values of WFSCDMPHYSICALCU.fwPosition */
#define     WFS_CDM_POSREJECT                         (0x0100)

	/* values of WFSCDMTELLERDETAILS.ulInputPosition */

#define     WFS_CDM_POSINLEFT                         (0x0001)
#define     WFS_CDM_POSINRIGHT                        (0x0002)
#define     WFS_CDM_POSINCENTER                       (0x0004)
#define     WFS_CDM_POSINTOP                          (0x0008)
#define     WFS_CDM_POSINBOTTOM                       (0x0010)
#define     WFS_CDM_POSINFRONT                        (0x0020)
#define     WFS_CDM_POSINREAR                         (0x0040)

	/* values of fwExchangeType */

#define     WFS_CDM_EXBYHAND                          (0x0001)
#define     WFS_CDM_EXTOCASSETTES                     (0x0002)

	/* values of WFSCDMTELLERUPDATE.usAction */

#define     WFS_CDM_CREATE_TELLER                     (1)
#define     WFS_CDM_MODIFY_TELLER                     (2)
#define     WFS_CDM_DELETE_TELLER                     (3)

	/* values of WFSCDMCUERROR.wFailure */

#define     WFS_CDM_CASHUNITEMPTY                     (1)
#define     WFS_CDM_CASHUNITERROR                     (2)
#define     WFS_CDM_CASHUNITFULL                      (4)
#define     WFS_CDM_CASHUNITLOCKED                    (5)
#define     WFS_CDM_CASHUNITINVALID                   (6)
#define     WFS_CDM_CASHUNITCONFIG                    (7)
#define     WFS_CDM_CASHUNITNOTCONF                   (8)

	/* values of lpusReason in WFS_EXEE_CDM_NOTEERROR */

#define     WFS_CDM_DOUBLENOTEDETECTED                (1)
#define     WFS_CDM_LONGNOTEDETECTED                  (2)
#define     WFS_CDM_SKEWEDNOTE                        (3)
#define     WFS_CDM_INCORRECTCOUNT                    (4)
#define     WFS_CDM_NOTESTOOCLOSE                     (5)
#define     WFS_CDM_OTHERNOTEERROR                    (6)
#define     WFS_CDM_SHORTNOTEDETECTED                 (7)

	/* values of WFSCDMPREPAREDISPENSE.wAction */

#define     WFS_CDM_START                             (1)
#define     WFS_CDM_STOP                              (2)

	/* values of WFSCDMSTATUS.wAntiFraudModule */

#define     WFS_CDM_AFMNOTSUPP                        (0)
#define     WFS_CDM_AFMOK                             (1)
#define     WFS_CDM_AFMINOP                           (2)
#define     WFS_CDM_AFMDEVICEDETECTED                 (3)
#define     WFS_CDM_AFMUNKNOWN                        (4)

	/* values of WFSCDMGETITEMINFO.usLevel,
	WFSCDMITEMINFOSUMMARY.usLevel,
	WFSCDMGETALLITEMSINFO.usLevel,
	WFSCDMITEMINFOALL.usLevel */

#define     WFS_CDM_LEVEL_1                     (1)
#define     WFS_CDM_LEVEL_2                     (2)
#define     WFS_CDM_LEVEL_3                     (3)
#define     WFS_CDM_LEVEL_4                     (4)

	/* values of WFSCDMITEMINFOALL.usLevel */

#define     WFS_CDM_LEVEL_ALL                   (0)

	/* values for WFSCDMGETITEMINFO.dwItemInfoType */

#define     WFS_CDM_ITEM_SERIALNUMBER           (0x00000001)
#define     WFS_CDM_ITEM_SIGNATURE              (0x00000002)
#define     WFS_CDM_ITEM_IMAGEFILE              (0x00000004)

	/* values of lpusReason in WFS_EXEE_CDM_INCOMPLETERETRACT */

#define     WFS_CDM_IRRETRACTFAILURE                  (1)
#define     WFS_CDM_IRRETRACTAREAFULL                 (2)
#define     WFS_CDM_IRFOREIGNITEMSDETECTED            (3)
#define     WFS_CDM_IRINVALIDBUNCH                    (4)

	/* values for WFSCDMITEMINFOALL.wOnBlacklist */

#define     WFS_CDM_ONBLACKLIST                 (0x0001)
#define     WFS_CDM_NOTONBLACKLIST              (0x0002)
#define     WFS_CDM_BLACKLISTUNKNOWN            (0x0003)

	/* values for WFSCDMITEMINFOALL.wItemLocation */

#define     WFS_CDM_LOCATION_DEVICE             (0x0001)
#define     WFS_CDM_LOCATION_CASHUNIT           (0x0002)
#define     WFS_CDM_LOCATION_CUSTOMER           (0x0003)
#define     WFS_CDM_LOCATION_UNKNOWN            (0x0004)

	/* XFS CDM Errors */

#define WFS_ERR_CDM_INVALIDCURRENCY                   (-(CDM_SERVICE_OFFSET + 0))
#define WFS_ERR_CDM_INVALIDTELLERID                   (-(CDM_SERVICE_OFFSET + 1))
#define WFS_ERR_CDM_CASHUNITERROR                     (-(CDM_SERVICE_OFFSET + 2))
#define WFS_ERR_CDM_INVALIDDENOMINATION               (-(CDM_SERVICE_OFFSET + 3))
#define WFS_ERR_CDM_INVALIDMIXNUMBER                  (-(CDM_SERVICE_OFFSET + 4))
#define WFS_ERR_CDM_NOCURRENCYMIX                     (-(CDM_SERVICE_OFFSET + 5))
#define WFS_ERR_CDM_NOTDISPENSABLE                    (-(CDM_SERVICE_OFFSET + 6))
#define WFS_ERR_CDM_TOOMANYITEMS                      (-(CDM_SERVICE_OFFSET + 7))
#define WFS_ERR_CDM_UNSUPPOSITION                     (-(CDM_SERVICE_OFFSET + 8))
#define WFS_ERR_CDM_SAFEDOOROPEN                      (-(CDM_SERVICE_OFFSET + 10))
#define WFS_ERR_CDM_SHUTTERNOTOPEN                    (-(CDM_SERVICE_OFFSET + 12))
#define WFS_ERR_CDM_SHUTTEROPEN                       (-(CDM_SERVICE_OFFSET + 13))
#define WFS_ERR_CDM_SHUTTERCLOSED                     (-(CDM_SERVICE_OFFSET + 14))
#define WFS_ERR_CDM_INVALIDCASHUNIT                   (-(CDM_SERVICE_OFFSET + 15))
#define WFS_ERR_CDM_NOITEMS                           (-(CDM_SERVICE_OFFSET + 16))
#define WFS_ERR_CDM_EXCHANGEACTIVE                    (-(CDM_SERVICE_OFFSET + 17))
#define WFS_ERR_CDM_NOEXCHANGEACTIVE                  (-(CDM_SERVICE_OFFSET + 18))
#define WFS_ERR_CDM_SHUTTERNOTCLOSED                  (-(CDM_SERVICE_OFFSET + 19))
#define WFS_ERR_CDM_PRERRORNOITEMS                    (-(CDM_SERVICE_OFFSET + 20))
#define WFS_ERR_CDM_PRERRORITEMS                      (-(CDM_SERVICE_OFFSET + 21))
#define WFS_ERR_CDM_PRERRORUNKNOWN                    (-(CDM_SERVICE_OFFSET + 22))
#define WFS_ERR_CDM_ITEMSTAKEN                        (-(CDM_SERVICE_OFFSET + 23))
#define WFS_ERR_CDM_INVALIDMIXTABLE                   (-(CDM_SERVICE_OFFSET + 27))
#define WFS_ERR_CDM_OUTPUTPOS_NOT_EMPTY               (-(CDM_SERVICE_OFFSET + 28))
#define WFS_ERR_CDM_INVALIDRETRACTPOSITION            (-(CDM_SERVICE_OFFSET + 29))
#define WFS_ERR_CDM_NOTRETRACTAREA                    (-(CDM_SERVICE_OFFSET + 30))
#define WFS_ERR_CDM_NOCASHBOXPRESENT                  (-(CDM_SERVICE_OFFSET + 33))
#define WFS_ERR_CDM_AMOUNTNOTINMIXTABLE               (-(CDM_SERVICE_OFFSET + 34))
#define WFS_ERR_CDM_ITEMSNOTTAKEN                     (-(CDM_SERVICE_OFFSET + 35))
#define WFS_ERR_CDM_ITEMSLEFT                         (-(CDM_SERVICE_OFFSET + 36))
#define WFS_ERR_CDM_INVALID_PORT                      (-(CDM_SERVICE_OFFSET + 37))
#define WFS_ERR_CDM_POWERSAVETOOSHORT                 (-(CDM_SERVICE_OFFSET + 38))
#define WFS_ERR_CDM_POWERSAVEMEDIAPRESENT             (-(CDM_SERVICE_OFFSET + 39))
#define WFS_ERR_CDM_POSITION_NOT_EMPTY                (-(CDM_SERVICE_OFFSET + 40))
#define WFS_ERR_CDM_INCOMPLETERETRACT                 (-(CDM_SERVICE_OFFSET + 41))
#define WFS_ERR_CDM_COMMANDUNSUPP                     (-(CDM_SERVICE_OFFSET + 42))
#define WFS_ERR_CDM_SYNCHRONIZEUNSUPP                 (-(CDM_SERVICE_OFFSET + 43))

	/*=================================================================*/
	/* CDM Info Command Structures */
	/*=================================================================*/

	typedef struct _wfs_cdm_position
	{
		WORD                  fwPosition;
		WORD                  fwShutter;
		WORD                  fwPositionStatus;
		WORD                  fwTransport;
		WORD                  fwTransportStatus;
		WORD                  fwJammedShutterPosition;

	} WFSCDMOUTPOS, *LPWFSCDMOUTPOS;

	typedef struct _wfs_cdm_status
	{
		WORD                  fwDevice;
		WORD                  fwSafeDoor;
		WORD                  fwDispenser;
		WORD                  fwIntermediateStacker;
		LPWFSCDMOUTPOS        *lppPositions;
		LPSTR                 lpszExtra;
		DWORD                 dwGuidLights[WFS_CDM_GUIDLIGHTS_SIZE];
		WORD                  wDevicePosition;
		USHORT                usPowerSaveRecoveryTime;
		WORD                  wAntiFraudModule;
	} WFSCDMSTATUS, *LPWFSCDMSTATUS;

	typedef struct _wfs_cdm_caps
	{
		WORD                  wClass;
		WORD                  fwType;
		WORD                  wMaxDispenseItems;
		BOOL                  bCompound;
		BOOL                  bShutter;
		BOOL                  bShutterControl;
		WORD                  fwRetractAreas;
		WORD                  fwRetractTransportActions;
		WORD                  fwRetractStackerActions;
		BOOL                  bSafeDoor;
		BOOL                  bCashBox;
		BOOL                  bIntermediateStacker;
		BOOL                  bItemsTakenSensor;
		WORD                  fwPositions;
		WORD                  fwMoveItems;
		WORD                  fwExchangeType;
		LPSTR                 lpszExtra;
		DWORD                 dwGuidLights[WFS_CDM_GUIDLIGHTS_SIZE];
		BOOL                  bPowerSaveControl;
		BOOL                  bPrepareDispense;
		BOOL                  bAntiFraudModule;
		DWORD                 dwItemInfoTypes;
		BOOL                  bBlacklist;
		LPDWORD               lpdwSynchronizableCommands;
	} WFSCDMCAPS, *LPWFSCDMCAPS;

	typedef struct _wfs_cdm_physicalcu
	{
		LPSTR                 lpPhysicalPositionName;
		CHAR                  cUnitID[5];
		ULONG                 ulInitialCount;
		ULONG                 ulCount;
		ULONG                 ulRejectCount;
		ULONG                 ulMaximum;
		USHORT                usPStatus;
		BOOL                  bHardwareSensor;
		ULONG                 ulDispensedCount;
		ULONG                 ulPresentedCount;
		ULONG                 ulRetractedCount;
	} WFSCDMPHCU, *LPWFSCDMPHCU;

	typedef struct _wfs_cdm_cashunit
	{
		USHORT                usNumber;
		USHORT                usType;
		LPSTR                 lpszCashUnitName;
		CHAR                  cUnitID[5];
		CHAR                  cCurrencyID[3];
		ULONG                 ulValues;
		ULONG                 ulInitialCount;
		ULONG                 ulCount;
		ULONG                 ulRejectCount;
		ULONG                 ulMinimum;
		ULONG                 ulMaximum;
		BOOL                  bAppLock;
		USHORT                usStatus;
		USHORT                usNumPhysicalCUs;
		LPWFSCDMPHCU          *lppPhysical;
		ULONG                 ulDispensedCount;
		ULONG                 ulPresentedCount;
		ULONG                 ulRetractedCount;
	} WFSCDMCASHUNIT, *LPWFSCDMCASHUNIT;

	typedef struct _wfs_cdm_cu_info
	{
		USHORT                usTellerID;
		USHORT                usCount;
		LPWFSCDMCASHUNIT      *lppList;
	} WFSCDMCUINFO, *LPWFSCDMCUINFO;

	typedef struct _wfs_cdm_teller_info
	{
		USHORT                usTellerID;
		CHAR                  cCurrencyID[3];
	} WFSCDMTELLERINFO, *LPWFSCDMTELLERINFO;

	typedef struct _wfs_cdm_teller_totals
	{
		CHAR                  cCurrencyID[3];
		ULONG                 ulItemsReceived;
		ULONG                 ulItemsDispensed;
		ULONG                 ulCoinsReceived;
		ULONG                 ulCoinsDispensed;
		ULONG                 ulCashBoxReceived;
		ULONG                 ulCashBoxDispensed;
	} WFSCDMTELLERTOTALS, *LPWFSCDMTELLERTOTALS;

	typedef struct _wfs_cdm_teller_details
	{
		USHORT                usTellerID;
		ULONG                 ulInputPosition;
		WORD                  fwOutputPosition;
		LPWFSCDMTELLERTOTALS  *lppTellerTotals;
	} WFSCDMTELLERDETAILS, *LPWFSCDMTELLERDETAILS;


	typedef struct _wfs_cdm_currency_exp
	{
		CHAR                  cCurrencyID[3];
		SHORT                 sExponent;
	} WFSCDMCURRENCYEXP, *LPWFSCDMCURRENCYEXP;

	typedef struct _wfs_cdm_mix_type
	{
		USHORT                usMixNumber;
		USHORT                usMixType;
		USHORT                usSubType;
		LPSTR                 lpszName;
	} WFSCDMMIXTYPE, *LPWFSCDMMIXTYPE;

	typedef struct _wfs_cdm_mix_row
	{
		ULONG                 ulAmount;
		LPUSHORT              lpusMixture;
	} WFSCDMMIXROW, *LPWFSCDMMIXROW;

	typedef struct _wfs_cdm_mix_table
	{
		USHORT                usMixNumber;
		LPSTR                 lpszName;
		USHORT                usRows;
		USHORT                usCols;
		LPULONG               lpulMixHeader;
		LPWFSCDMMIXROW        *lppMixRows;
	} WFSCDMMIXTABLE, *LPWFSCDMMIXTABLE;

	typedef struct _wfs_cdm_denomination
	{
		CHAR                  cCurrencyID[3];
		ULONG                 ulAmount;
		USHORT                usCount;
		LPULONG               lpulValues;
		ULONG                 ulCashBox;
	} WFSCDMDENOMINATION, *LPWFSCDMDENOMINATION;

	typedef struct _wfs_cdm_present_status
	{
		LPWFSCDMDENOMINATION  lpDenomination;
		WORD                  wPresentState;
		LPSTR                 lpszExtra;
	} WFSCDMPRESENTSTATUS, *LPWFSCDMPRESENTSTATUS;

	typedef struct _wfs_cdm_signature
	{
		ULONG                 ulLength;
		LPVOID                lpData;
	} WFSCDMSIGNATURE, *LPWFSCDMSIGNATURE;

	typedef struct _wfs_cdm_get_item_info
	{
		USHORT                usLevel;
		USHORT                usIndex;
		DWORD                 dwItemInfoType;
	} WFSCDMGETITEMINFO, *LPWFSCDMGETITEMINFO;

	typedef struct _wfs_cdm_item_info
	{
		CHAR                  cCurrencyID[3];
		ULONG                 ulValue;
		USHORT                usRelease;
		LPWSTR                lpszSerialNumber;
		LPWFSCDMSIGNATURE     lpSignature;
		LPSTR                 lpszImageFileName;
	} WFSCDMITEMINFO, *LPWFSCDMITEMINFO;

	typedef struct _wfs_cdm_get_all_items_info
	{
		USHORT                usLevel;
	} WFSCDMGETALLITEMSINFO, *LPWFSCDMGETALLITEMSINFO;

	typedef struct _wfs_cdm_item_info_all
	{
		USHORT                usLevel;
		CHAR                  cCurrencyID[3];
		ULONG                 ulValue;
		USHORT                usRelease;
		LPWSTR                lpszSerialNumber;
		LPSTR                 lpszImageFileName;
		WORD                  wOnBlacklist;
		WORD                  wItemLocation;
		USHORT                usNumber;
	} WFSCDMITEMINFOALL, *LPWFSCDMITEMINFOALL;

	typedef struct _wfs_cdm_all_items_info
	{
		USHORT                usCount;
		LPWFSCDMITEMINFOALL   *lppItemsList;
	} WFSCDMALLITEMSINFO, *LPWFSCDMALLITEMSINFO;


	/*=================================================================*/
	/* CDM Execute Command Structures */
	/*=================================================================*/

	typedef struct _wfs_cdm_denominate
	{
		USHORT                usTellerID;
		USHORT                usMixNumber;
		LPWFSCDMDENOMINATION  lpDenomination;
	} WFSCDMDENOMINATE, *LPWFSCDMDENOMINATE;

	typedef struct _wfs_cdm_dispense
	{
		USHORT                usTellerID;
		USHORT                usMixNumber;
		WORD                  fwPosition;
		BOOL                  bPresent;
		LPWFSCDMDENOMINATION  lpDenomination;
	} WFSCDMDISPENSE, *LPWFSCDMDISPENSE;

	typedef struct _wfs_cdm_physical_cu
	{
		BOOL                  bEmptyAll;
		WORD                  fwPosition;
		LPSTR                 lpPhysicalPositionName;
	} WFSCDMPHYSICALCU, *LPWFSCDMPHYSICALCU;

	typedef struct _wfs_cdm_counted_phys_cu
	{
		LPSTR                 lpPhysicalPositionName;
		CHAR                  cUnitId[5];
		ULONG                 ulDispensed;
		ULONG                 ulCounted;
		USHORT                usPStatus;
	} WFSCDMCOUNTEDPHYSCU, *LPWFSCDMCOUNTEDPHYSCU;

	typedef struct _wfs_cdm_count
	{
		USHORT                usNumPhysicalCUs;
		LPWFSCDMCOUNTEDPHYSCU *lppCountedPhysCUs;
	} WFSCDMCOUNT, *LPWFSCDMCOUNT;


	typedef struct _wfs_cdm_retract
	{
		WORD                  fwOutputPosition;
		USHORT                usRetractArea;
		USHORT                usIndex;
	} WFSCDMRETRACT, *LPWFSCDMRETRACT;

	typedef struct _wfs_cdm_item_number
	{
		CHAR                  cCurrencyID[3];
		ULONG                 ulValues;
		USHORT                usRelease;
		ULONG                 ulCount;
		USHORT                usNumber;
	} WFSCDMITEMNUMBER, *LPWFSCDMITEMNUMBER;

	typedef struct _wfs_cdm_item_number_list
	{
		USHORT                usNumOfItemNumbers;
		LPWFSCDMITEMNUMBER    *lppItemNumber;
	} WFSCDMITEMNUMBERLIST, *LPWFSCDMITEMNUMBERLIST;

	typedef struct _wfs_cdm_teller_update
	{
		USHORT                usAction;
		LPWFSCDMTELLERDETAILS lpTellerDetails;
	} WFSCDMTELLERUPDATE, *LPWFSCDMTELLERUPDATE;

	typedef struct _wfs_cdm_start_ex
	{
		WORD                  fwExchangeType;
		USHORT                usTellerID;
		USHORT                usCount;
		LPUSHORT              lpusCUNumList;
	} WFSCDMSTARTEX, *LPWFSCDMSTARTEX;

	typedef struct _wfs_cdm_itemposition
	{
		USHORT                usNumber;
		LPWFSCDMRETRACT       lpRetractArea;
		WORD                  fwOutputPosition;
	} WFSCDMITEMPOSITION, *LPWFSCDMITEMPOSITION;

	typedef struct _wfs_cdm_calibrate
	{
		USHORT                usNumber;
		USHORT                usNumOfBills;
		LPWFSCDMITEMPOSITION  *lpPosition;
	} WFSCDMCALIBRATE, *LPWFSCDMCALIBRATE;

	typedef struct _wfs_cdm_set_guidlight
	{
		WORD                  wGuidLight;
		DWORD                 dwCommand;
	} WFSCDMSETGUIDLIGHT, *LPWFSCDMSETGUIDLIGHT;

	typedef struct _wfs_cdm_power_save_control
	{
		USHORT                usMaxPowerSaveRecoveryTime;
	} WFSCDMPOWERSAVECONTROL, *LPWFSCDMPOWERSAVECONTROL;

	typedef struct _wfs_cdm_prepare_dispense
	{
		WORD                  wAction;
	} WFSCDMPREPAREDISPENSE, *LPWFSCDMPREPAREDISPENSE;

	typedef struct _wfs_cdm_blacklist_element
	{
		LPWSTR                lpszSerialNumber;
		CHAR                  cCurrencyID[3];
		ULONG                 ulValue;
	} WFSCDMBLACKLISTELEMENT, *LPWFSCDMBLACKLISTELEMENT;

	typedef struct _wfs_cdm_blacklist
	{
		LPWSTR                lpszVersion;
		USHORT                usCount;
		LPWFSCDMBLACKLISTELEMENT *lppBlacklistElements;
	} WFSCDMBLACKLIST, *LPWFSCDMBLACKLIST;

	typedef struct _wfs_cdm_synchronize_command
	{
		DWORD                 dwCommand;
		LPVOID                lpCmdData;
	} WFSCDMSYNCHRONIZECOMMAND, *LPWFSCDMSYNCHRONIZECOMMAND;

	/*=================================================================*/
	/* CDM Message Structures */
	/*=================================================================*/

	typedef struct _wfs_cdm_cu_error
	{
		WORD                  wFailure;
		LPWFSCDMCASHUNIT      lpCashUnit;
	} WFSCDMCUERROR, *LPWFSCDMCUERROR;

	typedef struct _wfs_cdm_counts_changed
	{
		USHORT                usCount;
		LPUSHORT              lpusCUNumList;
	} WFSCDMCOUNTSCHANGED, *LPWFSCDMCOUNTSCHANGED;

	typedef struct _wfs_cdm_device_position
	{
		WORD                  wPosition;
	} WFSCDMDEVICEPOSITION, *LPWFSCDMDEVICEPOSITION;

	typedef struct _wfs_cdm_power_save_change
	{
		USHORT                usPowerSaveRecoveryTime;
	} WFSCDMPOWERSAVECHANGE, *LPWFSCDMPOWERSAVECHANGE;

	typedef struct _wfs_cdm_item_info_summary
	{
		USHORT                usLevel;
		USHORT                usNumOfItems;
	} WFSCDMITEMINFOSUMMARY, *LPWFSCDMITEMINFOSUMMARY;

	typedef struct _wfs_cdm_incomplete_retract
	{
		WFSCDMITEMNUMBERLIST  lpItemNumberList;
		USHORT                usReason;
	} WFSCDMINCOMPLETERETRACT, *LPWFSCDMINCOMPLETERETRACT;

	typedef struct _wfs_cdm_shutter_status_changed
	{
		WORD                  fwPosition;
		WORD                  fwShutter;
	} WFSCDMSHUTTERSTATUSCHANGED, *LPWFSCDMSHUTTERSTATUSCHANGED;

	/* restore alignment */
#pragma pack (pop)

#ifdef __cplusplus
}       /*extern "C"*/
#endif

#endif  /* __INC_XFSCDM__H */
