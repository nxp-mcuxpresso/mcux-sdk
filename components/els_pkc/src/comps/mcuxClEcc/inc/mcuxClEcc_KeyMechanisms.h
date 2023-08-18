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
 * @file  mcuxClEcc_KeyMechanisms.h
 * @brief ECC related definitions to be used for key handling mechanisms of the mcuxClKey component
 */


#ifndef MCUXCLECC_KEYMECHANISMS_H_
#define MCUXCLECC_KEYMECHANISMS_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClEcc_Types.h>
#include <mcuxClCore_Analysis.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup mcuxClEcc_KeyTypeDescriptors mcuxClEcc_KeyTypeDescriptors
 * @brief Definitions of ECC related key type descriptors
 * @ingroup mcuxClEcc
 * @{
 */

/***********************************************/
/* Key types for secp160k1                     */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve secp160k1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp160k1_Pub;

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve secp160k1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_secp160k1_Pub = &mcuxClKey_TypeDescriptor_WeierECC_secp160k1_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve secp160k1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp160k1_Priv;

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve secp160k1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_secp160k1_Priv = &mcuxClKey_TypeDescriptor_WeierECC_secp160k1_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for secp192k1                     */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve secp192k1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp192k1_Pub;

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve secp192k1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_secp192k1_Pub = &mcuxClKey_TypeDescriptor_WeierECC_secp192k1_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve secp192k1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp192k1_Priv;

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve secp192k1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_secp192k1_Priv = &mcuxClKey_TypeDescriptor_WeierECC_secp192k1_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for secp224k1                     */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve secp224k1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp224k1_Pub;

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve secp224k1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_secp224k1_Pub = &mcuxClKey_TypeDescriptor_WeierECC_secp224k1_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve secp224k1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp224k1_Priv;

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve secp224k1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_secp224k1_Priv = &mcuxClKey_TypeDescriptor_WeierECC_secp224k1_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for secp256k1                     */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve secp256k1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp256k1_Pub;

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve secp256k1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_secp256k1_Pub = &mcuxClKey_TypeDescriptor_WeierECC_secp256k1_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve secp256k1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp256k1_Priv;

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve secp256k1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_secp256k1_Priv = &mcuxClKey_TypeDescriptor_WeierECC_secp256k1_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for secp192r1                     */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve secp192r1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp192r1_Pub;

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve secp192r1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_secp192r1_Pub = &mcuxClKey_TypeDescriptor_WeierECC_secp192r1_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve secp192r1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp192r1_Priv;

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve secp192r1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_secp192r1_Priv = &mcuxClKey_TypeDescriptor_WeierECC_secp192r1_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for secp224r1                     */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve secp224r1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp224r1_Pub;

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve secp224r1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_secp224r1_Pub = &mcuxClKey_TypeDescriptor_WeierECC_secp224r1_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve secp224r1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp224r1_Priv;

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve secp224r1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_secp224r1_Priv = &mcuxClKey_TypeDescriptor_WeierECC_secp224r1_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for secp256r1                     */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve secp256r1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp256r1_Pub;

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve secp256r1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_secp256r1_Pub = &mcuxClKey_TypeDescriptor_WeierECC_secp256r1_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve secp256r1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp256r1_Priv;

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve secp256r1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_secp256r1_Priv = &mcuxClKey_TypeDescriptor_WeierECC_secp256r1_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for secp384r1                     */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve secp384r1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp384r1_Pub;

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve secp384r1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_secp384r1_Pub = &mcuxClKey_TypeDescriptor_WeierECC_secp384r1_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve secp384r1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp384r1_Priv;

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve secp384r1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_secp384r1_Priv = &mcuxClKey_TypeDescriptor_WeierECC_secp384r1_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for secp521r1                     */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve secp521r1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp521r1_Pub;

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve secp521r1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_secp521r1_Pub = &mcuxClKey_TypeDescriptor_WeierECC_secp521r1_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve secp521r1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp521r1_Priv;

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve secp521r1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_secp521r1_Priv = &mcuxClKey_TypeDescriptor_WeierECC_secp521r1_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for NIST P-192                    */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve NIST P-192.
 *
 */
#define mcuxClKey_TypeDescriptor_WeierECC_NIST_P192_Pub mcuxClKey_TypeDescriptor_WeierECC_secp192r1_Pub

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve NIST P-192.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_NIST_P192_Pub = &mcuxClKey_TypeDescriptor_WeierECC_NIST_P192_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve NIST P-192.
 *
 */
#define mcuxClKey_TypeDescriptor_WeierECC_NIST_P192_Priv mcuxClKey_TypeDescriptor_WeierECC_secp192r1_Priv

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve NIST P-256.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_NIST_P192_Priv = &mcuxClKey_TypeDescriptor_WeierECC_NIST_P192_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for NIST P-224                    */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve NIST P-224.
 *
 */
#define mcuxClKey_TypeDescriptor_WeierECC_NIST_P224_Pub mcuxClKey_TypeDescriptor_WeierECC_secp224r1_Pub

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve NIST P-224.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_NIST_P224_Pub = &mcuxClKey_TypeDescriptor_WeierECC_NIST_P224_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve NIST P-224.
 *
 */
#define mcuxClKey_TypeDescriptor_WeierECC_NIST_P224_Priv mcuxClKey_TypeDescriptor_WeierECC_secp224r1_Priv

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve NIST P-224.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_NIST_P224_Priv = &mcuxClKey_TypeDescriptor_WeierECC_NIST_P224_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for NIST P-256                    */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve NIST P-256.
 *
 */
#define mcuxClKey_TypeDescriptor_WeierECC_NIST_P256_Pub mcuxClKey_TypeDescriptor_WeierECC_secp256r1_Pub

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve NIST P-256.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_NIST_P256_Pub = &mcuxClKey_TypeDescriptor_WeierECC_NIST_P256_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve NIST P-256.
 *
 */
#define mcuxClKey_TypeDescriptor_WeierECC_NIST_P256_Priv mcuxClKey_TypeDescriptor_WeierECC_secp256r1_Priv

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve NIST P-256.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_NIST_P256_Priv = &mcuxClKey_TypeDescriptor_WeierECC_NIST_P256_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for NIST P-384                    */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve NIST P-384.
 *
 */
#define mcuxClKey_TypeDescriptor_WeierECC_NIST_P384_Pub mcuxClKey_TypeDescriptor_WeierECC_secp384r1_Pub

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve NIST P-384.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_NIST_P384_Pub = &mcuxClKey_TypeDescriptor_WeierECC_NIST_P384_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve NIST P-384.
 *
 */
#define mcuxClKey_TypeDescriptor_WeierECC_NIST_P384_Priv mcuxClKey_TypeDescriptor_WeierECC_secp384r1_Priv

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve NIST P-384.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_NIST_P384_Priv = &mcuxClKey_TypeDescriptor_WeierECC_NIST_P384_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for NIST P-521                    */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve NIST P-521.
 *
 */
#define mcuxClKey_TypeDescriptor_WeierECC_NIST_P521_Pub mcuxClKey_TypeDescriptor_WeierECC_secp521r1_Pub

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve NIST P-521.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_NIST_P521_Pub = &mcuxClKey_TypeDescriptor_WeierECC_NIST_P521_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve NIST P-521.
 *
 */
#define mcuxClKey_TypeDescriptor_WeierECC_NIST_P521_Priv mcuxClKey_TypeDescriptor_WeierECC_secp521r1_Priv

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve NIST P-521.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_NIST_P521_Priv = &mcuxClKey_TypeDescriptor_WeierECC_NIST_P521_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for brainpoolP160r1               */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve brainpoolP160r1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP160r1_Pub;

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve brainpoolP160r1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP160r1_Pub = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP160r1_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve brainpoolP160r1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP160r1_Priv;

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve brainpoolP160r1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP160r1_Priv = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP160r1_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for brainpoolP192r1               */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve brainpoolP192r1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP192r1_Pub;

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve brainpoolP192r1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP192r1_Pub = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP192r1_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve brainpoolP192r1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP192r1_Priv;

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve brainpoolP192r1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP192r1_Priv = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP192r1_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for brainpoolP224r1               */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve brainpoolP224r1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP224r1_Pub;

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve brainpoolP224r1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP224r1_Pub = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP224r1_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve brainpoolP224r1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP224r1_Priv;

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve brainpoolP224r1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP224r1_Priv = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP224r1_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for brainpoolP256r1               */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve brainpoolP256r1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP256r1_Pub;

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve brainpoolP256r1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP256r1_Pub = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP256r1_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve brainpoolP256r1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP256r1_Priv;

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve brainpoolP256r1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP256r1_Priv = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP256r1_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for brainpoolP320r1               */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve brainpoolP320r1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP320r1_Pub;

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve brainpoolP320r1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP320r1_Pub = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP320r1_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve brainpoolP320r1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP320r1_Priv;

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve brainpoolP320r1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP320r1_Priv = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP320r1_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for brainpoolP384r1               */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve brainpoolP384r1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP384r1_Pub;

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve brainpoolP384r1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP384r1_Pub = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP384r1_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve brainpoolP384r1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP384r1_Priv;

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve brainpoolP384r1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP384r1_Priv = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP384r1_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for brainpoolP512r1               */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve brainpoolP512r1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP512r1_Pub;

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve brainpoolP512r1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP512r1_Pub = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP512r1_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve brainpoolP512r1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP512r1_Priv;

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve brainpoolP512r1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP512r1_Priv = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP512r1_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for brainpoolP160t1               */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve brainpoolP160t1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP160t1_Pub;

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve brainpoolP160t1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP160t1_Pub = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP160t1_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve brainpoolP160t1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP160t1_Priv;

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve brainpoolP160t1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP160t1_Priv = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP160t1_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for brainpoolP192t1               */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve brainpoolP192t1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP192t1_Pub;

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve brainpoolP192t1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP192t1_Pub = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP192t1_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve brainpoolP192t1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP192t1_Priv;

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve brainpoolP192t1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP192t1_Priv = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP192t1_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for brainpoolP224t1               */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve brainpoolP224t1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP224t1_Pub;

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve brainpoolP224t1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP224t1_Pub = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP224t1_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve brainpoolP224t1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP224t1_Priv;

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve brainpoolP224t1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP224t1_Priv = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP224t1_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for brainpoolP256t1               */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve brainpoolP256t1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP256t1_Pub;

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve brainpoolP256t1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP256t1_Pub = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP256t1_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve brainpoolP256t1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP256t1_Priv;

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve brainpoolP256t1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP256t1_Priv = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP256t1_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for brainpoolP320t1               */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve brainpoolP320t1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP320t1_Pub;

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve brainpoolP320t1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP320t1_Pub = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP320t1_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve brainpoolP320t1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP320t1_Priv;

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve brainpoolP320t1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP320t1_Priv = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP320t1_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for brainpoolP384t1               */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve brainpoolP384t1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP384t1_Pub;

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve brainpoolP384t1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP384t1_Pub = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP384t1_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve brainpoolP384t1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP384t1_Priv;

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve brainpoolP384t1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP384t1_Priv = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP384t1_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for brainpoolP512t1               */
/***********************************************/

/**
 * @brief Key type structure for public ECC keys for Weierstrass curve brainpoolP512t1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP512t1_Pub;

/**
 * @brief Key type pointer for public ECC Weierstrass keys for Weierstrass curve brainpoolP512t1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP512t1_Pub = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP512t1_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for private ECC keys for Weierstrass curve brainpoolP512t1.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP512t1_Priv;

/**
 * @brief Key type pointer for private ECC keys for Weierstrass curve brainpoolP512t1.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_WeierECC_brainpoolP512t1_Priv = &mcuxClKey_TypeDescriptor_WeierECC_brainpoolP512t1_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()



/***********************************************/
/* Key types for Ed25519                       */
/***********************************************/

/**
 * @brief Key type structure for ECC EdDSA Ed25519 private keys.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_EdDSA_Ed25519_Priv;

/**
 * @brief Key type pointer for ECC EdDSA Ed25519 private keys.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_EdDSA_Ed25519_Priv = &mcuxClKey_TypeDescriptor_EdDSA_Ed25519_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for ECC EdDSA Ed25519 public keys.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_EdDSA_Ed25519_Pub;

/**
 * @brief Key type pointer for ECC EdDSA Ed25519 public keys.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_EdDSA_Ed25519_Pub = &mcuxClKey_TypeDescriptor_EdDSA_Ed25519_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/***********************************************/
/* Key types for Ed448                         */
/***********************************************/

/**
 * @brief Key type structure for ECC EdDSA Ed448 private keys.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_EdDSA_Ed448_Priv;

/**
 * @brief Key type pointer for ECC EdDSA Ed448 private keys.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_EdDSA_Ed448_Priv = &mcuxClKey_TypeDescriptor_EdDSA_Ed448_Priv;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()

/**
 * @brief Key type structure for ECC EdDSA Ed448 public keys.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_EdDSA_Ed448_Pub;

/**
 * @brief Key type pointer for ECC EdDSA Ed448 public keys.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_EdDSA_Ed448_Pub = &mcuxClKey_TypeDescriptor_EdDSA_Ed448_Pub;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for Curve25519                    */
/***********************************************/

/**
 * @brief Key type structure for ECC MontDH Curve25519 Key pairs.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_Ecc_MontDH_Curve25519_KeyPair;

/**
 * @brief Key type pointer for ECC MontDH Curve25519 Key pairs.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_Ecc_MontDH_Curve25519_KeyPair = &mcuxClKey_TypeDescriptor_Ecc_MontDH_Curve25519_KeyPair;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()


/***********************************************/
/* Key types for Curve448                      */
/***********************************************/

/**
 * @brief Key type structure for ECC MontDH Curve448 Key pairs.
 *
 */
extern const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_Ecc_MontDH_Curve448_KeyPair;

/**
 * @brief Key type pointer for ECC MontDH Curve448 Key pairs.
 *
 */
MCUXCLCORE_ANALYSIS_START_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED("Consumed by mcuxClKey component. Hence, it is declared but never referenced.")
static const mcuxClKey_Type_t mcuxClKey_Type_Ecc_MontDH_Curve448_KeyPair = &mcuxClKey_TypeDescriptor_Ecc_MontDH_Curve448_KeyPair;
MCUXCLCORE_ANALYSIS_STOP_SUPPRESS_DECLARED_BUT_NEVER_REFERENCED()
/**
 * @}
 */ /* mcuxClEcc_KeyTypeDescriptors */






#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLECC_KEYMECHANISMS_H_ */
