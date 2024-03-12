/*--------------------------------------------------------------------------*/
/* Copyright 2020-2023 NXP                                                  */
/*                                                                          */
/* NXP Confidential. This software is owned or controlled by NXP and may    */
/* only be used strictly in accordance with the applicable license terms.   */
/* By expressly accepting such terms or by downloading, installing,         */
/* activating and/or otherwise using the software, you are agreeing that    */
/* you have read, and that you agree to comply with and are bound by, such  */
/* license terms. If you do not agree to be bound by the applicable license */
/* terms, then you may not retain, install, activate or otherwise use the   */
/* software.                                                                */
/*--------------------------------------------------------------------------*/

/**
 * @file  mcuxClEcc_ECDSA_Internal.h
 * @brief internal header for ECDSA
 */


#ifndef MCUXCLECC_ECDSA_INTERNAL_H_
#define MCUXCLECC_ECDSA_INTERNAL_H_


#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClEcc_Types.h>
#include <mcuxClKey_Types.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClSession.h>
#include <mcuxClBuffer.h>
#include <mcuxClMac.h>

#ifdef __cplusplus
extern "C" {
#endif


/**********************************************************/
/* Internal Weier ECC types                               */
/**********************************************************/

/**
 * Options for ECDSA signature generation descriptors
 */
#define MCUXCLECC_ECDSA_SIGNATURE_GENERATE_RANDOMIZED     0x5A5A5A5Au  ///< option for randomized ECDSA (according to FIPS 186-5)
#ifdef MCUXCL_FEATURE_ECC_ECDSA_DETERMINISTIC
#define MCUXCLECC_ECDSA_SIGNATURE_GENERATE_DETERMINISTIC  0xA5A5A5A5u  ///< option for deterministic ECDSA (according to rfc 6979)
#endif /* MCUXCL_FEATURE_ECC_ECDSA_DETERMINISTIC */

/**
 *  ECDSA SignatureProtocol variant structure.
 */
struct mcuxClEcc_ECDSA_SignatureProtocolDescriptor
{
    uint32_t generateOption;                        ///< option of signature generation
    uint32_t verifyOption;                          ///< option of signature verification
    const mcuxClMac_ModeDescriptor_t *pHmacModeDesc; ///< HMAC mode
};


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLECC_ECDSA_INTERNAL_H_ */
