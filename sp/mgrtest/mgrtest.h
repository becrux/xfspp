/* sp/mgrtest/mgrtest.h
 *
 * Copyright (C) 2007 Antonio Di Monaco
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#pragma once
#ifndef __SP_MGR_TEST_H__
#define __SP_MGR_TEST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "xfsapi.h"

/*   be aware of alignment   */
#pragma pack(push,1)

#define WFS_SERVICE_CLASS_MGR_TEST                  (99)
#define WFS_SERVICE_CLASS_VERSION_MGR_TEST          (0x1403) /* Version 3.20 */
#define WFS_SERVICE_CLASS_NAME_MGR_TEST             "MGR_TEST"

#define MGR_TEST_SERVICE_OFFSET                     (WFS_SERVICE_CLASS_MGR_TEST * 100)

/* MGR_TEST Info Commands */

#define WFS_INF_PIN_STATUS                          (PIN_SERVICE_OFFSET + 1)
#define WFS_INF_PIN_CAPABILITIES                    (PIN_SERVICE_OFFSET + 2)
#define WFS_INF_PIN_KEY_DETAIL                      (PIN_SERVICE_OFFSET + 4)
#define WFS_INF_PIN_FUNCKEY_DETAIL                  (PIN_SERVICE_OFFSET + 5)
#define WFS_INF_PIN_HSM_TDATA                       (PIN_SERVICE_OFFSET + 6)
#define WFS_INF_PIN_KEY_DETAIL_EX                   (PIN_SERVICE_OFFSET + 7)
#define WFS_INF_PIN_SECUREKEY_DETAIL                (PIN_SERVICE_OFFSET + 8)
#define WFS_INF_PIN_QUERY_LOGICAL_HSM_DETAIL        (PIN_SERVICE_OFFSET + 9)
#define WFS_INF_PIN_QUERY_PCIPTS_DEVICE_ID          (PIN_SERVICE_OFFSET + 10)

/* MGR_TEST Command Verbs */

#define WFS_CMD_PIN_CRYPT                           (PIN_SERVICE_OFFSET + 1)
#define WFS_CMD_PIN_IMPORT_KEY                      (PIN_SERVICE_OFFSET + 3)
#define WFS_CMD_PIN_GET_PIN                         (PIN_SERVICE_OFFSET + 5)
#define WFS_CMD_PIN_GET_PINBLOCK                    (PIN_SERVICE_OFFSET + 7)
#define WFS_CMD_PIN_GET_DATA                        (PIN_SERVICE_OFFSET + 8)
#define WFS_CMD_PIN_INITIALIZATION                  (PIN_SERVICE_OFFSET + 9)
#define WFS_CMD_PIN_LOCAL_DES                       (PIN_SERVICE_OFFSET + 10)
#define WFS_CMD_PIN_LOCAL_EUROCHEQUE                (PIN_SERVICE_OFFSET + 11)
#define WFS_CMD_PIN_LOCAL_VISA                      (PIN_SERVICE_OFFSET + 12)
#define WFS_CMD_PIN_CREATE_OFFSET                   (PIN_SERVICE_OFFSET + 13)
#define WFS_CMD_PIN_DERIVE_KEY                      (PIN_SERVICE_OFFSET + 14)
#define WFS_CMD_PIN_PRESENT_IDC                     (PIN_SERVICE_OFFSET + 15)
#define WFS_CMD_PIN_LOCAL_BANKSYS                   (PIN_SERVICE_OFFSET + 16)
#define WFS_CMD_PIN_BANKSYS_IO                      (PIN_SERVICE_OFFSET + 17)
#define WFS_CMD_PIN_RESET                           (PIN_SERVICE_OFFSET + 18)
#define WFS_CMD_PIN_HSM_SET_TDATA                   (PIN_SERVICE_OFFSET + 19)
#define WFS_CMD_PIN_SECURE_MSG_SEND                 (PIN_SERVICE_OFFSET + 20)
#define WFS_CMD_PIN_SECURE_MSG_RECEIVE              (PIN_SERVICE_OFFSET + 21)
#define WFS_CMD_PIN_GET_JOURNAL                     (PIN_SERVICE_OFFSET + 22)
#define WFS_CMD_PIN_IMPORT_KEY_EX                   (PIN_SERVICE_OFFSET + 23)
#define WFS_CMD_PIN_ENC_IO                          (PIN_SERVICE_OFFSET + 24)
#define WFS_CMD_PIN_HSM_INIT                        (PIN_SERVICE_OFFSET + 25)
#define WFS_CMD_PIN_IMPORT_RSA_PUBLIC_KEY           (PIN_SERVICE_OFFSET + 26)
#define WFS_CMD_PIN_EXPORT_RSA_ISSUER_SIGNED_ITEM   (PIN_SERVICE_OFFSET + 27)
#define WFS_CMD_PIN_IMPORT_RSA_SIGNED_DES_KEY       (PIN_SERVICE_OFFSET + 28)
#define WFS_CMD_PIN_GENERATE_RSA_KEY_PAIR           (PIN_SERVICE_OFFSET + 29)
#define WFS_CMD_PIN_EXPORT_RSA_EPP_SIGNED_ITEM      (PIN_SERVICE_OFFSET + 30)
#define WFS_CMD_PIN_LOAD_CERTIFICATE                (PIN_SERVICE_OFFSET + 31)
#define WFS_CMD_PIN_GET_CERTIFICATE                 (PIN_SERVICE_OFFSET + 32)
#define WFS_CMD_PIN_REPLACE_CERTIFICATE             (PIN_SERVICE_OFFSET + 33)
#define WFS_CMD_PIN_START_KEY_EXCHANGE              (PIN_SERVICE_OFFSET + 34)
#define WFS_CMD_PIN_IMPORT_RSA_ENCIPHERED_PKCS7_KEY (PIN_SERVICE_OFFSET + 35)
#define WFS_CMD_PIN_EMV_IMPORT_PUBLIC_KEY           (PIN_SERVICE_OFFSET + 36)
#define WFS_CMD_PIN_DIGEST                          (PIN_SERVICE_OFFSET + 37)
#define WFS_CMD_PIN_SECUREKEY_ENTRY                 (PIN_SERVICE_OFFSET + 38)
#define WFS_CMD_PIN_GENERATE_KCV                    (PIN_SERVICE_OFFSET + 39)
#define WFS_CMD_PIN_SET_GUIDANCE_LIGHT              (PIN_SERVICE_OFFSET + 41)
#define WFS_CMD_PIN_MAINTAIN_PIN                    (PIN_SERVICE_OFFSET + 42)
#define WFS_CMD_PIN_KEYPRESS_BEEP                   (PIN_SERVICE_OFFSET + 43)
#define WFS_CMD_PIN_SET_PINBLOCK_DATA               (PIN_SERVICE_OFFSET + 44)
#define WFS_CMD_PIN_SET_LOGICAL_HSM                 (PIN_SERVICE_OFFSET + 45)
#define WFS_CMD_PIN_IMPORT_KEYBLOCK                 (PIN_SERVICE_OFFSET + 46)
#define WFS_CMD_PIN_POWER_SAVE_CONTROL              (PIN_SERVICE_OFFSET + 47)

/* MGR_TEST Messages */

#define WFS_EXEE_PIN_KEY                            (PIN_SERVICE_OFFSET + 1)
#define WFS_SRVE_PIN_INITIALIZED                    (PIN_SERVICE_OFFSET + 2)
#define WFS_SRVE_PIN_ILLEGAL_KEY_ACCESS             (PIN_SERVICE_OFFSET + 3)
#define WFS_SRVE_PIN_OPT_REQUIRED                   (PIN_SERVICE_OFFSET + 4)
#define WFS_SRVE_PIN_HSM_TDATA_CHANGED              (PIN_SERVICE_OFFSET + 5)
#define WFS_SRVE_PIN_CERTIFICATE_CHANGE             (PIN_SERVICE_OFFSET + 6)
#define WFS_SRVE_PIN_HSM_CHANGED                    (PIN_SERVICE_OFFSET + 7)
#define WFS_EXEE_PIN_ENTERDATA                      (PIN_SERVICE_OFFSET + 8)
#define WFS_SRVE_PIN_DEVICEPOSITION                 (PIN_SERVICE_OFFSET + 9)
#define WFS_SRVE_PIN_POWER_SAVE_CHANGE              (PIN_SERVICE_OFFSET + 10)

/* restore alignment */
#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif
