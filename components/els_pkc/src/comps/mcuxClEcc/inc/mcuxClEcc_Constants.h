/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
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
 * @file  mcuxClEcc_Constants.h
 * @brief Constants definition for domain parameters of supported curves
 */

/* TODO: domain parameters are not verified, and will be verified in CLNS-5817 */

#ifndef MCUXCLECC_CONSTANTS_H_
#define MCUXCLECC_CONSTANTS_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClEcc_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup mcuxClEcc_Constants mcuxClEcc_Constants
 * @brief Defines constants of @ref mcuxClEcc
 * @ingroup mcuxClEcc
 * @{
 */


/* Curve25519 domain parameters */
extern const mcuxClEcc_MontDH_DomainParams_t mcuxClEcc_MontDH_DomainParams_Curve25519;

/* Curve448 domain parameters */
extern const mcuxClEcc_MontDH_DomainParams_t mcuxClEcc_MontDH_DomainParams_Curve448;

/* secp160k1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_secp160k1;

/* secp192k1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_secp192k1;

/* sec224k1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_secp224k1;

/* secp256k1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_secp256k1;

/* secp192r1 (nistp192r1, ansix9p192r1) domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_secp192r1;
#define mcuxClEcc_Weier_DomainParams_NIST_P192 mcuxClEcc_Weier_DomainParams_secp192r1
#define mcuxClEcc_Weier_DomainParams_ansix9p192r1 mcuxClEcc_Weier_DomainParams_secp192r1

/* secp224r1 (nistp224r1, ansix9p224r1) domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_secp224r1;
#define mcuxClEcc_Weier_DomainParams_NIST_P224 mcuxClEcc_Weier_DomainParams_secp224r1
#define mcuxClEcc_Weier_DomainParams_ansix9p224r1 mcuxClEcc_Weier_DomainParams_secp224r1

/* secp256r1 (nistp256r1, ansix9p256r1) domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_secp256r1;
#define mcuxClEcc_Weier_DomainParams_NIST_P256 mcuxClEcc_Weier_DomainParams_secp256r1
#define mcuxClEcc_Weier_DomainParams_ansix9p256r1 mcuxClEcc_Weier_DomainParams_secp256r1

/* secp384r1 (nistp384r1, ansix9p384r1) domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_secp384r1;
#define mcuxClEcc_Weier_DomainParams_NIST_P384 mcuxClEcc_Weier_DomainParams_secp384r1
#define mcuxClEcc_Weier_DomainParams_ansix9p384r1 mcuxClEcc_Weier_DomainParams_secp384r1

/* secp521r1 (nistp521r1, ansix9p521r1) domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_secp521r1;
#define mcuxClEcc_Weier_DomainParams_NIST_P521 mcuxClEcc_Weier_DomainParams_secp521r1
#define mcuxClEcc_Weier_DomainParams_ansix9p521r1 mcuxClEcc_Weier_DomainParams_secp521r1

/* brainpoolP160r1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP160r1;

/* brainpoolP192r1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP192r1;

/* brainpoolP224r1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP224r1;

/* brainpoolP256r1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP256r1;

/* brainpoolP320r1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP320r1;

/* brainpoolP384r1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP384r1;

/* brainpoolP512r1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP512r1;

/* brainpoolP160t1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP160t1;

/* brainpoolP192t1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP192t1;

/* brainpoolP224t1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP224t1;

/* brainpoolP256t1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP256t1;

/* brainpoolP320t1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP320t1;

/* brainpoolP384t1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP384t1;

/* brainpoolP512t1 domain parameters */
extern const mcuxClEcc_Weier_DomainParams_t mcuxClEcc_Weier_DomainParams_brainpoolP512t1;


/* Ed25519 domain parameters */
extern const mcuxClEcc_EdDSA_DomainParams_t mcuxClEcc_EdDSA_DomainParams_Ed25519;

/* Ed448 domain parameters */
extern const mcuxClEcc_EdDSA_DomainParams_t mcuxClEcc_EdDSA_DomainParams_Ed448;

/* phflag values for EdDSA */
#define MCUXCLECC_EDDSA_PHFLAG_ZERO    0u
#define MCUXCLECC_EDDSA_PHFLAG_ONE     1u

/**
 * @}
 */ /* mcuxClEcc_Constants */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLECC_CONSTANTS_H_ */
