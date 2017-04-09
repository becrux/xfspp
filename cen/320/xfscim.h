/******************************************************************************
*                                                                             *
* xfscim.h      XFS - Cash Acceptor (CIM) definitions                         *
*                                                                             *
*               Version 3.20  (March 02 2011)                                 *
*                                                                             *
******************************************************************************/

#ifndef __INC_XFSCIM__H
#define __INC_XFSCIM__H

#ifdef __cplusplus
extern "C" {
#endif

#include "xfsapi.h"

/* be aware of alignment */
#pragma pack (push, 1)

/* values of WFSCIMCAPS.wClass */

#define     WFS_SERVICE_CLASS_CIM               (13)
#define     WFS_SERVICE_CLASS_VERSION_CIM       (0x1403) /* Version 3.20 */
#define     WFS_SERVICE_CLASS_NAME_CIM          "CIM"

#define     CIM_SERVICE_OFFSET                  (WFS_SERVICE_CLASS_CIM * 100)

/* CIM Info Commands */

#define     WFS_INF_CIM_STATUS                  (CIM_SERVICE_OFFSET + 1)
#define     WFS_INF_CIM_CAPABILITIES            (CIM_SERVICE_OFFSET + 2)
#define     WFS_INF_CIM_CASH_UNIT_INFO          (CIM_SERVICE_OFFSET + 3)
#define     WFS_INF_CIM_TELLER_INFO             (CIM_SERVICE_OFFSET + 4)
#define     WFS_INF_CIM_CURRENCY_EXP            (CIM_SERVICE_OFFSET + 5)
#define     WFS_INF_CIM_BANKNOTE_TYPES          (CIM_SERVICE_OFFSET + 6)
#define     WFS_INF_CIM_CASH_IN_STATUS          (CIM_SERVICE_OFFSET + 7)
#define     WFS_INF_CIM_GET_P6_INFO             (CIM_SERVICE_OFFSET + 8)
#define     WFS_INF_CIM_GET_P6_SIGNATURE        (CIM_SERVICE_OFFSET + 9)
#define     WFS_INF_CIM_GET_ITEM_INFO           (CIM_SERVICE_OFFSET + 10)
#define     WFS_INF_CIM_POSITION_CAPABILITIES   (CIM_SERVICE_OFFSET + 11)
#define     WFS_INF_CIM_REPLENISH_TARGET        (CIM_SERVICE_OFFSET + 12)
#define     WFS_INF_CIM_DEVICELOCK_STATUS       (CIM_SERVICE_OFFSET + 13)
#define     WFS_INF_CIM_CASH_UNIT_CAPABILITIES  (CIM_SERVICE_OFFSET + 14)

/* CIM Execute Commands */

#define     WFS_CMD_CIM_CASH_IN_START           (CIM_SERVICE_OFFSET + 1)
#define     WFS_CMD_CIM_CASH_IN                 (CIM_SERVICE_OFFSET + 2)
#define     WFS_CMD_CIM_CASH_IN_END             (CIM_SERVICE_OFFSET + 3)
#define     WFS_CMD_CIM_CASH_IN_ROLLBACK        (CIM_SERVICE_OFFSET + 4)
#define     WFS_CMD_CIM_RETRACT                 (CIM_SERVICE_OFFSET + 5)
#define     WFS_CMD_CIM_OPEN_SHUTTER            (CIM_SERVICE_OFFSET + 6)
#define     WFS_CMD_CIM_CLOSE_SHUTTER           (CIM_SERVICE_OFFSET + 7)
#define     WFS_CMD_CIM_SET_TELLER_INFO         (CIM_SERVICE_OFFSET + 8)
#define     WFS_CMD_CIM_SET_CASH_UNIT_INFO      (CIM_SERVICE_OFFSET + 9)
#define     WFS_CMD_CIM_START_EXCHANGE          (CIM_SERVICE_OFFSET + 10)
#define     WFS_CMD_CIM_END_EXCHANGE            (CIM_SERVICE_OFFSET + 11)
#define     WFS_CMD_CIM_OPEN_SAFE_DOOR          (CIM_SERVICE_OFFSET + 12)
#define     WFS_CMD_CIM_RESET                   (CIM_SERVICE_OFFSET + 13)
#define     WFS_CMD_CIM_CONFIGURE_CASH_IN_UNITS (CIM_SERVICE_OFFSET + 14)
#define     WFS_CMD_CIM_CONFIGURE_NOTETYPES     (CIM_SERVICE_OFFSET + 15)
#define     WFS_CMD_CIM_CREATE_P6_SIGNATURE     (CIM_SERVICE_OFFSET + 16)
#define     WFS_CMD_CIM_SET_GUIDANCE_LIGHT      (CIM_SERVICE_OFFSET + 17)
#define     WFS_CMD_CIM_CONFIGURE_NOTE_READER   (CIM_SERVICE_OFFSET + 18)
#define     WFS_CMD_CIM_COMPARE_P6_SIGNATURE    (CIM_SERVICE_OFFSET + 19)
#define     WFS_CMD_CIM_POWER_SAVE_CONTROL      (CIM_SERVICE_OFFSET + 20)
#define     WFS_CMD_CIM_REPLENISH               (CIM_SERVICE_OFFSET + 21)
#define     WFS_CMD_CIM_SET_CASH_IN_LIMIT       (CIM_SERVICE_OFFSET + 22)
#define     WFS_CMD_CIM_CASH_UNIT_COUNT         (CIM_SERVICE_OFFSET + 23)
#define     WFS_CMD_CIM_DEVICE_LOCK_CONTROL     (CIM_SERVICE_OFFSET + 24)
#define     WFS_CMD_CIM_SET_MODE                (CIM_SERVICE_OFFSET + 25)
#define     WFS_CMD_CIM_PRESENT_MEDIA           (CIM_SERVICE_OFFSET + 26)

/* CIM Messages */

#define     WFS_SRVE_CIM_SAFEDOOROPEN           (CIM_SERVICE_OFFSET + 1)
#define     WFS_SRVE_CIM_SAFEDOORCLOSED         (CIM_SERVICE_OFFSET + 2)
#define     WFS_USRE_CIM_CASHUNITTHRESHOLD      (CIM_SERVICE_OFFSET + 3)
#define     WFS_SRVE_CIM_CASHUNITINFOCHANGED    (CIM_SERVICE_OFFSET + 4)
#define     WFS_SRVE_CIM_TELLERINFOCHANGED      (CIM_SERVICE_OFFSET + 5)
#define     WFS_EXEE_CIM_CASHUNITERROR          (CIM_SERVICE_OFFSET + 6)
#define     WFS_SRVE_CIM_ITEMSTAKEN             (CIM_SERVICE_OFFSET + 7)
#define     WFS_SRVE_CIM_COUNTS_CHANGED         (CIM_SERVICE_OFFSET + 8)
#define     WFS_EXEE_CIM_INPUTREFUSE            (CIM_SERVICE_OFFSET + 9)
#define     WFS_SRVE_CIM_ITEMSPRESENTED         (CIM_SERVICE_OFFSET + 10)
#define     WFS_SRVE_CIM_ITEMSINSERTED          (CIM_SERVICE_OFFSET + 11)
#define     WFS_EXEE_CIM_NOTEERROR              (CIM_SERVICE_OFFSET + 12)
#define     WFS_EXEE_CIM_SUBCASHIN              (CIM_SERVICE_OFFSET + 13)
#define     WFS_SRVE_CIM_MEDIADETECTED          (CIM_SERVICE_OFFSET + 14)
#define     WFS_EXEE_CIM_INPUT_P6               (CIM_SERVICE_OFFSET + 15)
#define     WFS_EXEE_CIM_INFO_AVAILABLE         (CIM_SERVICE_OFFSET + 16)
#define     WFS_EXEE_CIM_INSERTITEMS            (CIM_SERVICE_OFFSET + 17)
#define     WFS_SRVE_CIM_DEVICEPOSITION         (CIM_SERVICE_OFFSET + 18)
#define     WFS_SRVE_CIM_POWER_SAVE_CHANGE      (CIM_SERVICE_OFFSET + 19)
#define     WFS_EXEE_CIM_INCOMPLETEREPLENISH    (CIM_SERVICE_OFFSET + 20)

/* values of WFSCIMSTATUS.fwDevice */

#define     WFS_CIM_DEVONLINE                   WFS_STAT_DEVONLINE
#define     WFS_CIM_DEVOFFLINE                  WFS_STAT_DEVOFFLINE
#define     WFS_CIM_DEVPOWEROFF                 WFS_STAT_DEVPOWEROFF
#define     WFS_CIM_DEVNODEVICE                 WFS_STAT_DEVNODEVICE
#define     WFS_CIM_DEVUSERERROR                WFS_STAT_DEVUSERERROR
#define     WFS_CIM_DEVHWERROR                  WFS_STAT_DEVHWERROR
#define     WFS_CIM_DEVBUSY                     WFS_STAT_DEVBUSY
#define     WFS_CIM_DEVFRAUDATTEMPT             WFS_STAT_DEVFRAUDATTEMPT
#define     WFS_CIM_DEVPOTENTIALFRAUD           WFS_STAT_DEVPOTENTIALFRAUD

/* values of WFSCIMSTATUS.fwSafeDoor */

#define     WFS_CIM_DOORNOTSUPPORTED            (1)
#define     WFS_CIM_DOOROPEN                    (2)
#define     WFS_CIM_DOORCLOSED                  (3)
#define     WFS_CIM_DOORUNKNOWN                 (4)

/* values of WFSCIMSTATUS.fwAcceptor */

#define     WFS_CIM_ACCOK                       (0)
#define     WFS_CIM_ACCCUSTATE                  (1)
#define     WFS_CIM_ACCCUSTOP                   (2)
#define     WFS_CIM_ACCCUUNKNOWN                (3)

/* values of WFSCIMSTATUS.fwIntermediateStacker */

#define     WFS_CIM_ISEMPTY                     (0)
#define     WFS_CIM_ISNOTEMPTY                  (1)
#define     WFS_CIM_ISFULL                      (2)
#define     WFS_CIM_ISUNKNOWN                   (4)
#define     WFS_CIM_ISNOTSUPPORTED              (5)

/* Size and max index of dwGuidLights array */
#define     WFS_CIM_GUIDLIGHTS_SIZE             (32)
#define     WFS_CIM_GUIDLIGHTS_MAX              (WFS_CIM_GUIDLIGHTS_SIZE - 1)

/* Indices of WFSCIMSTATUS.dwGuidLights [...]
              WFSCIMCAPS.dwGuidLights [...]
*/

#define     WFS_CIM_GUIDANCE_POSINNULL          (0)
#define     WFS_CIM_GUIDANCE_POSINLEFT          (1)
#define     WFS_CIM_GUIDANCE_POSINRIGHT         (2)
#define     WFS_CIM_GUIDANCE_POSINCENTER        (3)
#define     WFS_CIM_GUIDANCE_POSINTOP           (4)
#define     WFS_CIM_GUIDANCE_POSINBOTTOM        (5)
#define     WFS_CIM_GUIDANCE_POSINFRONT         (6)
#define     WFS_CIM_GUIDANCE_POSINREAR          (7)
#define     WFS_CIM_GUIDANCE_POSOUTLEFT         (8)
#define     WFS_CIM_GUIDANCE_POSOUTRIGHT        (9)
#define     WFS_CIM_GUIDANCE_POSOUTCENTER       (10)
#define     WFS_CIM_GUIDANCE_POSOUTTOP          (11)
#define     WFS_CIM_GUIDANCE_POSOUTBOTTOM       (12)
#define     WFS_CIM_GUIDANCE_POSOUTFRONT        (13)
#define     WFS_CIM_GUIDANCE_POSOUTREAR         (14)
#define     WFS_CIM_GUIDANCE_POSOUTNULL         (15)

/* Values of WFSCIMSTATUS.dwGuidLights [...]
             WFSCIMCAPS.dwGuidLights [...]
*/

#define     WFS_CIM_GUIDANCE_NOT_AVAILABLE      (0x00000000)
#define     WFS_CIM_GUIDANCE_OFF                (0x00000001)
#define     WFS_CIM_GUIDANCE_SLOW_FLASH         (0x00000004)
#define     WFS_CIM_GUIDANCE_MEDIUM_FLASH       (0x00000008)
#define     WFS_CIM_GUIDANCE_QUICK_FLASH        (0x00000010)
#define     WFS_CIM_GUIDANCE_CONTINUOUS         (0x00000080)
#define     WFS_CIM_GUIDANCE_RED                (0x00000100)
#define     WFS_CIM_GUIDANCE_GREEN              (0x00000200)
#define     WFS_CIM_GUIDANCE_YELLOW             (0x00000400)
#define     WFS_CIM_GUIDANCE_BLUE               (0x00000800)
#define     WFS_CIM_GUIDANCE_CYAN               (0x00001000)
#define     WFS_CIM_GUIDANCE_MAGENTA            (0x00002000)
#define     WFS_CIM_GUIDANCE_WHITE              (0x00004000)

/* values of WFSCIMSTATUS.wDevicePosition
             WFSCIMDEVICEPOSITION.wPosition */

#define     WFS_CIM_DEVICEINPOSITION            (0)
#define     WFS_CIM_DEVICENOTINPOSITION         (1)
#define     WFS_CIM_DEVICEPOSUNKNOWN            (2)
#define     WFS_CIM_DEVICEPOSNOTSUPP            (3)

/* values of WFSCIMSTATUS.fwStackerItems */

#define     WFS_CIM_CUSTOMERACCESS              (0)
#define     WFS_CIM_NOCUSTOMERACCESS            (1)
#define     WFS_CIM_ACCESSUNKNOWN               (2)
#define     WFS_CIM_NOITEMS                     (4)

/* values of WFSCIMSTATUS.fwBankNoteReader */

#define     WFS_CIM_BNROK                       (0)
#define     WFS_CIM_BNRINOP                     (1)
#define     WFS_CIM_BNRUNKNOWN                  (2)
#define     WFS_CIM_BNRNOTSUPPORTED             (3)

/* values of WFSCIMSTATUS.fwShutter */

#define     WFS_CIM_SHTCLOSED                   (0)
#define     WFS_CIM_SHTOPEN                     (1)
#define     WFS_CIM_SHTJAMMED                   (2)
#define     WFS_CIM_SHTUNKNOWN                  (3)
#define     WFS_CIM_SHTNOTSUPPORTED             (4)

/* values of WFSCIMCAPS.wMixedMode */

#define     WFS_CIM_MIXEDMEDIANOTSUPP           (0)
#define     WFS_CIM_IPMMIXEDMEDIA               (1)

/* values of WFSCIMSETMODE.wMixedMode */
/* values of WFSCIMSTATUS.wMixedMode.*/

#define     WFS_CIM_MIXEDMEDIANOTACTIVE         (0)

/* values of WFSCIMINPOS.fwPositionStatus */

#define     WFS_CIM_PSEMPTY                     (0)
#define     WFS_CIM_PSNOTEMPTY                  (1)
#define     WFS_CIM_PSUNKNOWN                   (2)
#define     WFS_CIM_PSNOTSUPPORTED              (3)
#define     WFS_CIM_PSFOREIGNITEMS              (4)

/* values of WFSCIMSTATUS.fwTransport */

#define     WFS_CIM_TPOK                        (0)
#define     WFS_CIM_TPINOP                      (1)
#define     WFS_CIM_TPUNKNOWN                   (2)
#define     WFS_CIM_TPNOTSUPPORTED              (3)

/* values of WFSCIMINPOS.fwTransportStatus */

#define     WFS_CIM_TPSTATEMPTY                 (0)
#define     WFS_CIM_TPSTATNOTEMPTY              (1)
#define     WFS_CIM_TPSTATNOTEMPTYCUST          (2)
#define     WFS_CIM_TPSTATNOTEMPTY_UNK          (3)
#define     WFS_CIM_TPSTATNOTSUPPORTED          (4)

/* values of WFSCIMCAPS.fwType */

#define     WFS_CIM_TELLERBILL                  (0)
#define     WFS_CIM_SELFSERVICEBILL             (1)
#define     WFS_CIM_TELLERCOIN                  (2)
#define     WFS_CIM_SELFSERVICECOIN             (3)

/* values of WFSCIMCAPS.fwExchangeType */
/* values of WFSCIMSTARTEX.fwExchangeType */

#define     WFS_CIM_EXBYHAND                    (0x0001)
#define     WFS_CIM_EXTOCASSETTES               (0x0002)
#define     WFS_CIM_CLEARRECYCLER               (0x0004)
#define     WFS_CIM_DEPOSITINTO                 (0x0008)

/* values of WFSCIMCAPS.fwRetractTransportActions */
/* values of WFSCIMCAPS.fwRetractStackerActions */

#define     WFS_CIM_PRESENT                     (0x0001)
#define     WFS_CIM_RETRACT                     (0x0002)
#define     WFS_CIM_NOTSUPP                     (0x0004)
#define     WFS_CIM_REJECT                      (0x0008)
#define     WFS_CIM_BILLCASSETTES               (0x0010)

/* values for WFSCIMCAPS.fwCashInLimit */

#define     WFS_CIM_LIMITNOTSUPP                (0x0000)
#define     WFS_CIM_LIMITBYTOTALITEMS           (0x0001)
#define     WFS_CIM_LIMITBYAMOUNT               (0x0002)

/* values of WFSCIMCASHIN.fwType */

#define     WFS_CIM_TYPERECYCLING               (1)
#define     WFS_CIM_TYPECASHIN                  (2)
#define     WFS_CIM_TYPEREPCONTAINER            (3)
#define     WFS_CIM_TYPERETRACTCASSETTE         (4)
#define     WFS_CIM_TYPEREJECT                  (5)
#define     WFS_CIM_TYPECDMSPECIFIC             (6)

/* values of WFSCIMCASHIN.fwItemType */
/* values of WFSCIMCASHINTYPE.dwType */

#define     WFS_CIM_CITYPALL                    (0x0001)
#define     WFS_CIM_CITYPUNFIT                  (0x0002)
#define     WFS_CIM_CITYPINDIVIDUAL             (0x0004)
#define     WFS_CIM_CITYPLEVEL3                 (0x0008)
#define     WFS_CIM_CITYPLEVEL2                 (0x0010)
#define     WFS_CIM_CITYPIPM                    (0x0020)

/* values of WFSCIMCASHIN.usStatus */
/* values of WFSCIMPHCU.usPStatus */

#define     WFS_CIM_STATCUOK                    (0)
#define     WFS_CIM_STATCUFULL                  (1)
#define     WFS_CIM_STATCUHIGH                  (2)
#define     WFS_CIM_STATCULOW                   (3)
#define     WFS_CIM_STATCUEMPTY                 (4)
#define     WFS_CIM_STATCUINOP                  (5)
#define     WFS_CIM_STATCUMISSING               (6)
#define     WFS_CIM_STATCUNOVAL                 (7)
#define     WFS_CIM_STATCUNOREF                 (8) /* NOTE: Not used in CIM */
#define     WFS_CIM_STATCUMANIP                 (9)

/* values of WFSCIMSTATUS.fwPositions */
/* values of WFSCIMCAPS.fwPositions */
/* values of WFSCIMINPOS.fwPosition */
/* values of WFSCIMTELLERDETAILS.fwInputPosition */
/* values of WFSCIMCASHINSTART.fwInputPosition */

#define     WFS_CIM_POSNULL                     (0x0000)
#define     WFS_CIM_POSINLEFT                   (0x0001)
#define     WFS_CIM_POSINRIGHT                  (0x0002)
#define     WFS_CIM_POSINCENTER                 (0x0004)
#define     WFS_CIM_POSINTOP                    (0x0008)
#define     WFS_CIM_POSINBOTTOM                 (0x0010)
#define     WFS_CIM_POSINFRONT                  (0x0020)
#define     WFS_CIM_POSINREAR                   (0x0040)

/* values of WFSCIMSTATUS.fwPositions */
/* values of WFSCIMCAPS.fwPositions */
/* values of WFSCIMTELLERDETAILS.fwOutputPosition */
/* values of WFSCIMCASHINSTART.fwOutputPosition */
/* values of WFSCIMOUTPUT.fwPosition */

#define     WFS_CIM_POSOUTLEFT                  (0x0080)
#define     WFS_CIM_POSOUTRIGHT                 (0x0100)
#define     WFS_CIM_POSOUTCENTER                (0x0200)
#define     WFS_CIM_POSOUTTOP                   (0x0400)
#define     WFS_CIM_POSOUTBOTTOM                (0x0800)
#define     WFS_CIM_POSOUTFRONT                 (0x1000)
#define     WFS_CIM_POSOUTREAR                  (0x2000)

/* values of WFSCIMCASHINSTATUS.wStatus */

#define     WFS_CIM_CIOK                        (0)
#define     WFS_CIM_CIROLLBACK                  (1)
#define     WFS_CIM_CIACTIVE                    (2)
#define     WFS_CIM_CIRETRACT                   (3)
#define     WFS_CIM_CIUNKNOWN                   (4)
#define     WFS_CIM_CIRESET                     (5)

/* values of WFSCIMCAPS.fwRetractAreas */
/* values of WFSCIMRETRACT.usRetractArea */

#define     WFS_CIM_RA_RETRACT                  (0x0001)
#define     WFS_CIM_RA_TRANSPORT                (0x0002)
#define     WFS_CIM_RA_STACKER                  (0x0004)
#define     WFS_CIM_RA_BILLCASSETTES            (0x0008)
#define     WFS_CIM_RA_NOTSUPP                  (0x0010)
#define     WFS_CIM_RA_REJECT                   (0x0020)

/* values of WFSCIMP6INFO.usLevel */
/* values of WFSCIMP6SIGNATURE.usLevel */

#define     WFS_CIM_LEVEL_2                     (2)
#define     WFS_CIM_LEVEL_3                     (3)
#define     WFS_CIM_LEVEL_4                     (4)

/* values of WFSCIMTELLERUPDATE.usAction */

#define     WFS_CIM_CREATE_TELLER               (1)
#define     WFS_CIM_MODIFY_TELLER               (2)
#define     WFS_CIM_DELETE_TELLER               (3)

/* values of WFSCIMCUERROR.wFailure */

#define     WFS_CIM_CASHUNITEMPTY               (1)
#define     WFS_CIM_CASHUNITERROR               (2)
#define     WFS_CIM_CASHUNITFULL                (3)
#define     WFS_CIM_CASHUNITLOCKED              (4)
#define     WFS_CIM_CASHUNITNOTCONF             (5)
#define     WFS_CIM_CASHUNITINVALID             (6)
#define     WFS_CIM_CASHUNITCONFIG              (7)
#define     WFS_CIM_FEEDMODULEPROBLEM           (8)
#define     WFS_CIM_CASHUNITPHYSICALLOCKED      (9)
#define     WFS_CIM_CASHUNITPHYSICALUNLOCKED    (10)

/*values of WFSCIMP6SIGNATURE.dwOrientation*/

#define     WFS_CIM_ORFRONTTOP                  (1)
#define     WFS_CIM_ORFRONTBOTTOM               (2)
#define     WFS_CIM_ORBACKTOP                   (3)
#define     WFS_CIM_ORBACKBOTTOM                (4)
#define     WFS_CIM_ORUNKNOWN                   (5)
#define     WFS_CIM_ORNOTSUPPORTED              (6)

/* values for WFSCIMGETITEMINFO.wItemInfoType */
#define     WFS_CIM_ITEM_SERIALNUMBER           (0x00000001)
#define     WFS_CIM_ITEM_SIGNATURE              (0x00000002)

/* values of lpusReason in WFS_EXEE_CIM_INPUTREFUSE */

#define     WFS_CIM_CASHINUNITFULL              (1)
#define     WFS_CIM_INVALIDBILL                 (2)
#define     WFS_CIM_NOBILLSTODEPOSIT            (3)
#define     WFS_CIM_DEPOSITFAILURE              (4)
#define     WFS_CIM_COMMINPCOMPFAILURE          (5)
#define     WFS_CIM_STACKERFULL                 (6)
#define     WFS_CIM_FOREIGN_ITEMS_DETECTED      (7)
#define     WFS_CIM_INVALIDBUNCH                (8)
#define     WFS_CIM_COUNTERFEIT                 (9)
#define     WFS_CIM_LIMITOVERTOTALITEMS         (10)
#define     WFS_CIM_LIMITOVERAMOUNT             (11)

/* values of lpusReason in WFS_EXEE_CIM_NOTESERROR */

#define     WFS_CIM_DOUBLENOTEDETECTED          (1)
#define     WFS_CIM_LONGNOTEDETECTED            (2)
#define     WFS_CIM_SKEWEDNOTE                  (3)
#define     WFS_CIM_INCORRECTCOUNT              (4)
#define     WFS_CIM_NOTESTOOCLOSE               (5)
#define     WFS_CIM_OTHERNOTEERROR              (6)
#define     WFS_CIM_SHORTNOTEDETECTED           (7)

/* Values of fwUsage in WFS_INF_CIM_POSITION_CAPABILITIES */

#define     WFS_CIM_POSIN                       (0x0001)
#define     WFS_CIM_POSREFUSE                   (0x0002)
#define     WFS_CIM_POSROLLBACK                 (0x0004)

/* values of WFSCIMPOSITIONINFO.wAdditionalBunches */

#define     WFS_CIM_ADDBUNCHNONE                (1)
#define     WFS_CIM_ADDBUNCHONEMORE             (2)
#define     WFS_CIM_ADDBUNCHUNKNOWN             (3)

/* values of WFSCIMPOSITIONINFO.usBunchesRemaining */

#define     WFS_CIM_NUMBERUNKNOWN               (255)

/* values of WFSCIMCAPS.fwCountActions */

#define     WFS_CIM_COUNTNOTSUPP                (0x0000)
#define     WFS_CIM_COUNTINDIVIDUAL             (0x0001)
#define     WFS_CIM_COUNTALL                    (0x0002)

/* values of WFSCIMDEVICELOCKCONTROL.wDeviceAction */
/* values of WFSCIMDEVICELOCKCONTROL.wCashUnitAction */
/* values of WFSCIMUNITLOCKCONTROL.wUnitAction */

#define     WFS_CIM_LOCK                        (1)
#define     WFS_CIM_UNLOCK                      (2)
#define     WFS_CIM_LOCKALL                     (3)
#define     WFS_CIM_UNLOCKALL                   (4)
#define     WFS_CIM_LOCKINDIVIDUAL              (5)
#define     WFS_CIM_NOLOCKACTION                (6)
#define     WFS_CIM_LOCKUNKNOWN                 (7)
#define     WFS_CIM_LOCKNOTSUPPORTED            (8)

/* values of WFSCIMSTATUS.wAntiFraudModule */

#define     WFS_CIM_AFMNOTSUPP                  (0)
#define     WFS_CIM_AFMOK                       (1)
#define     WFS_CIM_AFMINOP                     (2)
#define     WFS_CIM_AFMDEVICEDETECTED           (3)
#define     WFS_CIM_AFMUNKNOWN                  (4)

/* XFS CIM Errors */

#define WFS_ERR_CIM_INVALIDCURRENCY             (-(CIM_SERVICE_OFFSET + 0))
#define WFS_ERR_CIM_INVALIDTELLERID             (-(CIM_SERVICE_OFFSET + 1))
#define WFS_ERR_CIM_CASHUNITERROR               (-(CIM_SERVICE_OFFSET + 2))
#define WFS_ERR_CIM_TOOMANYITEMS                (-(CIM_SERVICE_OFFSET + 7))
#define WFS_ERR_CIM_UNSUPPOSITION               (-(CIM_SERVICE_OFFSET + 8))
#define WFS_ERR_CIM_SAFEDOOROPEN                (-(CIM_SERVICE_OFFSET + 10))
#define WFS_ERR_CIM_SHUTTERNOTOPEN              (-(CIM_SERVICE_OFFSET + 12))
#define WFS_ERR_CIM_SHUTTEROPEN                 (-(CIM_SERVICE_OFFSET + 13))
#define WFS_ERR_CIM_SHUTTERCLOSED               (-(CIM_SERVICE_OFFSET + 14))
#define WFS_ERR_CIM_INVALIDCASHUNIT             (-(CIM_SERVICE_OFFSET + 15))
#define WFS_ERR_CIM_NOITEMS                     (-(CIM_SERVICE_OFFSET + 16))
#define WFS_ERR_CIM_EXCHANGEACTIVE              (-(CIM_SERVICE_OFFSET + 17))
#define WFS_ERR_CIM_NOEXCHANGEACTIVE            (-(CIM_SERVICE_OFFSET + 18))
#define WFS_ERR_CIM_SHUTTERNOTCLOSED            (-(CIM_SERVICE_OFFSET + 19))
#define WFS_ERR_CIM_ITEMSTAKEN                  (-(CIM_SERVICE_OFFSET + 23))
#define WFS_ERR_CIM_CASHINACTIVE                (-(CIM_SERVICE_OFFSET + 25))
#define WFS_ERR_CIM_NOCASHINACTIVE              (-(CIM_SERVICE_OFFSET + 26))
#define WFS_ERR_CIM_POSITION_NOT_EMPTY          (-(CIM_SERVICE_OFFSET + 28))
#define WFS_ERR_CIM_INVALIDRETRACTPOSITION      (-(CIM_SERVICE_OFFSET + 34))
#define WFS_ERR_CIM_NOTRETRACTAREA              (-(CIM_SERVICE_OFFSET + 35))
#define WFS_ERR_CIM_INVALID_PORT                (-(CIM_SERVICE_OFFSET + 36))
#define WFS_ERR_CIM_FOREIGN_ITEMS_DETECTED      (-(CIM_SERVICE_OFFSET + 37))
#define WFS_ERR_CIM_LOADFAILED                  (-(CIM_SERVICE_OFFSET + 38))
#define WFS_ERR_CIM_CASHUNITNOTEMPTY            (-(CIM_SERVICE_OFFSET + 39))
#define WFS_ERR_CIM_INVALIDREFSIG               (-(CIM_SERVICE_OFFSET + 40))
#define WFS_ERR_CIM_INVALIDTRNSIG               (-(CIM_SERVICE_OFFSET + 41))
#define WFS_ERR_CIM_POWERSAVETOOSHORT           (-(CIM_SERVICE_OFFSET + 42))
#define WFS_ERR_CIM_POWERSAVEMEDIAPRESENT       (-(CIM_SERVICE_OFFSET + 43))
#define WFS_ERR_CIM_DEVICELOCKFAILURE           (-(CIM_SERVICE_OFFSET + 44))
#define WFS_ERR_CIM_TOOMANYITEMSTOCOUNT         (-(CIM_SERVICE_OFFSET + 45))
#define WFS_ERR_CIM_COUNTPOSNOTEMPTY            (-(CIM_SERVICE_OFFSET + 46))
#define WFS_ERR_CIM_MEDIAINACTIVE               (-(CIM_SERVICE_OFFSET + 47))

/*=================================================================*/
/* CIM Info Command Structures */
/*=================================================================*/

typedef struct _wfs_cim_inpos
{
    WORD                     fwPosition;
    WORD                     fwShutter;
    WORD                     fwPositionStatus;
    WORD                     fwTransport;
    WORD                     fwTransportStatus;
} WFSCIMINPOS, *LPWFSCIMINPOS;

typedef struct _wfs_cim_status
{
    WORD                     fwDevice;
    WORD                     fwSafeDoor;
    WORD                     fwAcceptor;
    WORD                     fwIntermediateStacker;
    WORD                     fwStackerItems;
    WORD                     fwBanknoteReader;
    BOOL                     bDropBox;
    LPWFSCIMINPOS            *lppPositions;
    LPSTR                    lpszExtra;
    DWORD                    dwGuidLights[WFS_CIM_GUIDLIGHTS_SIZE];
    WORD                     wDevicePosition;
    USHORT                   usPowerSaveRecoveryTime;
    WORD                     wMixedMode;
    WORD                     wAntiFraudModule;
} WFSCIMSTATUS, *LPWFSCIMSTATUS;

typedef struct _wfs_cim_caps
{
    WORD                     wClass;
    WORD                     fwType;
    WORD                     wMaxCashInItems;
    BOOL                     bCompound;
    BOOL                     bShutter;
    BOOL                     bShutterControl;
    BOOL                     bSafeDoor;
    BOOL                     bCashBox;
    BOOL                     bRefill;
    WORD                     fwIntermediateStacker;
    BOOL                     bItemsTakenSensor;
    BOOL                     bItemsInsertedSensor;
    WORD                     fwPositions;
    WORD                     fwExchangeType;
    WORD                     fwRetractAreas;
    WORD                     fwRetractTransportActions;
    WORD                     fwRetractStackerActions;
    LPSTR                    lpszExtra;
    DWORD                    dwGuidLights[WFS_CIM_GUIDLIGHTS_SIZE];
    DWORD                    dwItemInfoTypes;
    BOOL                     bCompareSignatures;
    BOOL                     bPowerSaveControl;
    BOOL                     bReplenish;
    WORD                     fwCashInLimit;
    WORD                     fwCountActions;
    BOOL                     bDeviceLockControl;
    WORD                     wMixedMode;
    BOOL                     bMixedDepositAndRollback;
    BOOL                     bAntiFraudModule;
} WFSCIMCAPS, *LPWFSCIMCAPS;

typedef struct _wfs_cim_physicalcu
{
    LPSTR                    lpPhysicalPositionName;
    CHAR                     cUnitID[5];
    ULONG                    ulCashInCount;
    ULONG                    ulCount;
    ULONG                    ulMaximum;
    USHORT                   usPStatus;
    BOOL                     bHardwareSensors;
    LPSTR                    lpszExtra;
    ULONG                    ulInitialCount;
    ULONG                    ulDispensedCount;
    ULONG                    ulPresentedCount;
    ULONG                    ulRetractedCount;
    ULONG                    ulRejectCount;
} WFSCIMPHCU, *LPWFSCIMPHCU;

typedef struct _wfs_cim_note_number
{
    USHORT                   usNoteID;
    ULONG                    ulCount;
} WFSCIMNOTENUMBER, *LPWFSCIMNOTENUMBER;

typedef struct _wfs_cim_note_number_list
{
    USHORT                   usNumOfNoteNumbers;
    LPWFSCIMNOTENUMBER       *lppNoteNumber;
} WFSCIMNOTENUMBERLIST, *LPWFSCIMNOTENUMBERLIST;

typedef struct _wfs_cim_cash_in
{
    USHORT                   usNumber;
    DWORD                    fwType;
    DWORD                    fwItemType;
    CHAR                     cUnitID[5];
    CHAR                     cCurrencyID[3];
    ULONG                    ulValues;
    ULONG                    ulCashInCount;
    ULONG                    ulCount;
    ULONG                    ulMaximum;
    USHORT                   usStatus;
    BOOL                     bAppLock;
    LPWFSCIMNOTENUMBERLIST   lpNoteNumberList;
    USHORT                   usNumPhysicalCUs;
    LPWFSCIMPHCU             *lppPhysical;
    LPSTR                    lpszExtra;
    LPUSHORT                 lpusNoteIDs;
    WORD                     usCDMType;
    LPSTR                    lpszCashUnitName;
    ULONG                    ulInitialCount;
    ULONG                    ulDispensedCount;
    ULONG                    ulPresentedCount;
    ULONG                    ulRetractedCount;
    ULONG                    ulRejectCount;
    ULONG                    ulMinimum;
} WFSCIMCASHIN, *LPWFSCIMCASHIN;

typedef struct _wfs_cim_cash_info
{
    USHORT                   usCount;
    LPWFSCIMCASHIN           *lppCashIn;
} WFSCIMCASHINFO, *LPWFSCIMCASHINFO;

typedef struct _wfs_cim_teller_info
{
    USHORT                   usTellerID;
    CHAR                     cCurrencyID[3];
} WFSCIMTELLERINFO, *LPWFSCIMTELLERINFO;

typedef struct _wfs_cim_teller_totals
{
   CHAR                      cCurrencyID[3];
   ULONG                     ulItemsReceived;
   ULONG                     ulItemsDispensed;
   ULONG                     ulCoinsReceived;
   ULONG                     ulCoinsDispensed;
   ULONG                     ulCashBoxReceived;
   ULONG                     ulCashBoxDispensed;
} WFSCIMTELLERTOTALS, *LPWFSCIMTELLERTOTALS;

typedef struct _wfs_cim_teller_details
{
    USHORT                   usTellerID;
    WORD                     fwInputPosition;
    WORD                     fwOutputPosition;
    LPWFSCIMTELLERTOTALS     *lppTellerTotals;
} WFSCIMTELLERDETAILS, *LPWFSCIMTELLERDETAILS;

typedef struct _wfs_cim_currency_exp
{
    CHAR                     cCurrencyID[3];
    SHORT                    sExponent;
} WFSCIMCURRENCYEXP, *LPWFSCIMCURRENCYEXP;


typedef struct _wfs_cim_note_type
{
    USHORT                   usNoteID;
    CHAR                     cCurrencyID[3];
    ULONG                    ulValues;
    USHORT                   usRelease;
    BOOL                     bConfigured;
} WFSCIMNOTETYPE, *LPWFSCIMNOTETYPE;

typedef struct _wfs_cim_note_type_list
{
    USHORT                   usNumOfNoteTypes;
    LPWFSCIMNOTETYPE         *lppNoteTypes;
} WFSCIMNOTETYPELIST, *LPWFSCIMNOTETYPELIST;

typedef struct _wfs_cim_cash_in_status
{
    WORD                     wStatus;
    USHORT                   usNumOfRefused;
    LPWFSCIMNOTENUMBERLIST   lpNoteNumberList;
    LPSTR                    lpszExtra;
} WFSCIMCASHINSTATUS, *LPWFSCIMCASHINSTATUS;

typedef struct _wfs_cim_P6_info
{
    USHORT                   usLevel;
    LPWFSCIMNOTENUMBERLIST   lpNoteNumberList;
    USHORT                   usNumOfSignatures;
} WFSCIMP6INFO, *LPWFSCIMP6INFO;

typedef struct _wfs_cim_get_P6_signature
{
    USHORT                   usLevel;
    USHORT                   usIndex;
} WFSCIMGETP6SIGNATURE, *LPWFSCIMGETP6SIGNATURE;

typedef struct _wfs_cim_P6_signature
{
    USHORT                   usNoteId;
    ULONG                    ulLength;
    DWORD                    dwOrientation;
    LPVOID                   lpSignature;
} WFSCIMP6SIGNATURE, *LPWFSCIMP6SIGNATURE;

typedef struct _wfs_cim_get_item_info
{
    USHORT                   usLevel;
    USHORT                   usIndex;
    DWORD                    dwItemInfoType;
} WFSCIMGETITEMINFO, *LPWFSCIMGETITEMINFO;

typedef struct _wfs_cim_item_info
{
    USHORT                   usNoteID;
    LPWSTR                   lpszSerialNumber;
    LPWFSCIMP6SIGNATURE      lpP6Signature;
 } WFSCIMITEMINFO, *LPWFSCIMITEMINFO;

typedef struct _wfs_cim_item_info_summary
{
    USHORT                   usLevel;
    USHORT                   usNumOfItems;
} WFSCIMITEMINFOSUMMARY, *LPWFSCIMITEMINFOSUMMARY;

typedef struct _wfs_cim_pos_caps
{
    WORD                     fwPosition;
    WORD                     fwUsage;
    BOOL                     bShutterControl;
    BOOL                     bItemsTakenSensor;
    BOOL                     bItemsInsertedSensor;
    WORD                     fwRetractAreas;
    LPSTR                    lpszExtra;
    BOOL                     bPresentControl;
} WFSCIMPOSCAPS, *LPWFSCIMPOSCAPS;

typedef struct _wfs_cim_pos_capabilities
{
    LPWFSCIMPOSCAPS          *lppPosCapabilities;
} WFSCIMPOSCAPABILITIES, *LPWFSCIMPOSCAPABILITIES;

typedef struct _wfs_cim_replenish_info
{
    USHORT                   usNumberSource;
} WFSCIMREPINFO, *LPWFSCIMREPINFO;

typedef struct _wfs_cim_replenish_info_target
{
    USHORT                   usNumberTarget;
} WFSCIMREPINFOTARGET, *LPWFSCIMREPINFOTARGET;

typedef struct _wfs_cim_replenish_info_result
{
    LPWFSCIMREPINFOTARGET    *lppReplenishTargets;
} WFSCIMREPINFORES, *LPWFSCIMREPINFORES;

typedef struct _wfs_cim_cash_unit_lock
{
    LPSTR                    lpPhysicalPositionName;
    WORD                     wCashUnitLockStatus;
} WFSCIMCASHUNITLOCK, *LPWFSCIMCASHUNITLOCK;

typedef struct _wfs_cim_device_lock_status
{
    WORD                     wDeviceLockStatus;
    LPWFSCIMCASHUNITLOCK     *lppCashUnitLock;
} WFSCIMDEVICELOCKSTATUS, *LPWFSCIMDEVICELOCKSTATUS;

typedef struct _wfs_cim_physicalcu_capabilities
{
    LPSTR                     lpPhysicalPositionName;
    ULONG                     ulMaximum;
    BOOL                      bHardwareSensors;
    LPSTR                     lpszExtra;
} WFSCIMPHCUCAPABILITIES, *LPWFSCIMPHCUCAPABILITIES;

typedef struct _wfs_cim_cash_unit_capabilities
{
    USHORT                   usNumber;
    USHORT                   usNumPhysicalCUs;
    LPWFSCIMPHCUCAPABILITIES *lppPhysical;
    BOOL                     bRetractNoteCountThresholds;
    LPSTR                    lpszExtra;
} WFSCIMCASHUNITCAPABILITIES, *LPWFSCIMCASHUNITCAPABILITIES;

typedef struct _wfs_cim_cash_caps
{
    USHORT                       usCount;
    LPWFSCIMCASHUNITCAPABILITIES *lppCashUnitCaps;
} WFSCIMCASHCAPABILITIES, *LPWFSCIMCASHCAPABILITIES;

/*=================================================================*/
/* CIM Execute Command Structures */
/*=================================================================*/

typedef struct _wfs_cim_cash_in_start
{
    USHORT                   usTellerID;
    BOOL                     bUseRecycleUnits;
    WORD                     fwOutputPosition;
    WORD                     fwInputPosition;
} WFSCIMCASHINSTART, *LPWFSCIMCASHINSTART;

typedef struct _wfs_cim_retract
{
    WORD                     fwOutputPosition;
    USHORT                   usRetractArea;
    USHORT                   usIndex;
} WFSCIMRETRACT, *LPWFSCIMRETRACT;

typedef struct _wfs_cim_teller_update
{
    USHORT                   usAction;
    LPWFSCIMTELLERDETAILS    lpTellerDetails;
} WFSCIMTELLERUPDATE,   *LPWFSCIMTELLERUPDATE;

typedef struct _wfs_cim_output
{
    USHORT                   usLogicalNumber;
    WORD                     fwPosition;
    USHORT                   usNumber;
} WFSCIMOUTPUT, *LPWFSCIMOUTPUT;

typedef struct _wfs_cim_start_ex
{
    WORD                     fwExchangeType;
    USHORT                   usTellerID;
    USHORT                   usCount;
    LPUSHORT                 lpusCUNumList;
    LPWFSCIMOUTPUT           lpOutput;
} WFSCIMSTARTEX, *LPWFSCIMSTARTEX;

typedef struct _wfs_cim_itemposition
{
    USHORT                   usNumber;
    LPWFSCIMRETRACT          lpRetractArea;
    WORD                     fwOutputPosition;
} WFSCIMITEMPOSITION, *LPWFSCIMITEMPOSITION;

typedef struct _wfs_cim_cash_in_type
{
    USHORT                   usNumber;
    DWORD                    dwType;
    LPUSHORT                 lpusNoteIDs;
} WFSCIMCASHINTYPE, *LPWFSCIMCASHINTYPE;

typedef struct _wfs_cim_set_guidlight
{
    WORD                     wGuidLight;
    DWORD                    dwCommand;
} WFSCIMSETGUIDLIGHT, *LPWFSCIMSETGUIDLIGHT;

typedef struct _wfs_cim_configure_note_reader
{
    BOOL                     bLoadAlways;
} WFSCIMCONFIGURENOTEREADER, *LPWFSCIMCONFIGURENOTEREADER;

typedef struct _wfs_cim_configure_note_reader_out
{
    BOOL                     bRebootNecessary;
} WFSCIMCONFIGURENOTEREADEROUT, *LPWFSCIMCONFIGURENOTEREADEROUT;

typedef struct _wfs_cim_P6_compare_signature
{
   LPWFSCIMP6SIGNATURE       *lppP6ReferenceSignatures;
   LPWFSCIMP6SIGNATURE       *lppP6Signatures;
} WFSCIMP6COMPARESIGNATURE, *LPWFSCIMP6COMPARESIGNATURE;

typedef struct _wfs_cim_P6_signatures_index
{
    USHORT                   usIndex;
    USHORT                   usConfidenceLevel;
    ULONG                    ulLength;
    LPVOID                   lpComparisonData;
} WFSCIMP6SIGNATURESINDEX, *LPWFSCIMP6SIGNATURESINDEX;

typedef struct _wfs_cim_P6_compare_result
{
   USHORT                    usCount;
   LPWFSCIMP6SIGNATURESINDEX *lppP6SignaturesIndex;
} WFSCIMP6COMPARERESULT, *LPWFSCIMP6COMPARERESULT;

typedef struct _wfs_cim_power_save_control
{
    USHORT                   usMaxPowerSaveRecoveryTime;
} WFSCIMPOWERSAVECONTROL, *LPWFSCIMPOWERSAVECONTROL;

typedef struct _wfs_cim_replenish_target
{
    USHORT                   usNumberTarget;
    ULONG                    ulNumberOfItemsToMove;
    BOOL                     bRemoveAll;
} WFSCIMREPTARGET, *LPWFSCIMREPTARGET;

typedef struct _wfs_cim_replenish
{
    USHORT                   usNumberSource;
    LPWFSCIMREPTARGET        *lppReplenishTargets;
} WFSCIMREP, *LPWFSCIMREP;

typedef struct _wfs_cim_replenish_target_result
{
    USHORT                   usNumberTarget;
    USHORT                   usNoteID;
    ULONG                    ulNumberOfItemsReceived;
} WFSCIMREPTARGETRES, *LPWFSCIMREPTARGETRES;

typedef struct _wfs_cim_replenish_result
{
    ULONG                    ulNumberOfItemsRemoved;
    ULONG                    ulNumberOfItemsRejected;
    LPWFSCIMREPTARGETRES     *lppReplenishTargetResults;
} WFSCIMREPRES, *LPWFSCIMREPRES;

typedef struct _wfs_cim_amount_limit
{
    CHAR                     cCurrencyID[3];
    ULONG                    ulAmount;
} WFSCIMAMOUNTLIMIT, *LPWFSCIMAMOUNTLIMIT;

typedef struct _wfs_cim_cash_in_limit
{
    ULONG                    ulTotalItemsLimit;
    LPWFSCIMAMOUNTLIMIT      lpAmountLimit;
} WFSCIMCASHINLIMIT, *LPWFSCIMCASHINLIMIT;

typedef struct _wfs_cim_count
{
    USHORT                   usCount;
    LPUSHORT                 lpusCUNumList;
} WFSCIMCOUNT, *LPWFSCIMCOUNT;

typedef struct _wfs_cim_unit_lock_control
{
    LPSTR                    lpPhysicalPositionName;
    WORD                     wUnitAction;
} WFSCIMUNITLOCKCONTROL, *LPWFSCIMUNITLOCKCONTROL;

typedef struct _wfs_cim_device_lock_control
{
    WORD                     wDeviceAction;
    WORD                     wCashUnitAction;
    LPWFSCIMUNITLOCKCONTROL  *lppUnitLockControl;
} WFSCIMDEVICELOCKCONTROL, *LPWFSCIMDEVICELOCKCONTROL;

typedef struct _wfs_cim_setmode
{
    WORD                     wMixedMode;
} WFSCIMSETMODE, *LPWFSCIMSETMODE;

typedef struct _wfs_cim_present
{
    WORD                     fwPosition;
} WFSCIMPRESENT, *LPWFSCIMPRESENT;

/*=================================================================*/
/* CIM Message Structures */
/*=================================================================*/

typedef struct _wfs_cim_cu_error
{
    WORD                     wFailure;
    LPWFSCIMCASHIN           lpCashUnit;
} WFSCIMCUERROR, *LPWFSCIMCUERROR;

typedef struct _wfs_cim_counts_changed
{
    USHORT                   usCount;
    LPUSHORT                 lpusCUNumList;
} WFSCIMCOUNTSCHANGED, *LPWFSCIMCOUNTSCHANGED;

typedef struct _wfs_cim_position_info
{
    WORD                     wPosition;
    WORD                     wAdditionalBunches;
    USHORT                   usBunchesRemaining;
} WFSCIMPOSITIONINFO, *LPWFSCIMPOSITIONINFO;

typedef struct _wfs_cim_device_position
{
    WORD                     wPosition;
} WFSCIMDEVICEPOSITION, *LPWFSCIMDEVICEPOSITION;

typedef struct _wfs_cim_power_save_change
{
    USHORT                   usPowerSaveRecoveryTime;
} WFSCIMPOWERSAVECHANGE, *LPWFSCIMPOWERSAVECHANGE;

typedef struct _wfs_cim_incomplete_replenish
{
    LPWFSCIMREPRES           lpReplenish;
} WFSCIMINCOMPLETEREPLENISH, *LPWFSCIMINCOMPLETEREPLENISH;

/* restore alignment */
#pragma pack (pop)

#ifdef __cplusplus
}       /*extern "C"*/
#endif

#endif  /* __INC_XFSCIM__H */
