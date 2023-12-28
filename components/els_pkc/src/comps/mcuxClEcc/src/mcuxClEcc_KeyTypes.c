/*--------------------------------------------------------------------------*/
/* Copyright 2020, 2022-2023 NXP                                            */
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
 * @file  mcuxClEcc_KeyTypes.c
 * @brief mcuxClEcc: implementation of ECC related key type descriptors
 */

#include <mcuxClKey.h>

#include <mcuxClEcc_ParameterSizes.h>
#include <mcuxClEcc_Constants.h>
#include <mcuxClEcc_KeyMechanisms.h>
#include <mcuxCsslAnalysis.h>

#include <internal/mcuxClKey_Types_Internal.h>

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the key parameters.")
/* Key type structure for private and public ECC keys for Weierstrass curve secp160k1 */
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp160k1_Pub  = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PUBLIC_KEY, .size = MCUXCLECC_WEIERECC_SECP160K1_SIZE_PUBLICKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_secp160k1};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp160k1_Priv = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PRIVATE_KEY, .size = MCUXCLECC_WEIERECC_SECP160K1_SIZE_PRIVATEKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_secp160k1};

/* Key type structure for private and public ECC keys for Weierstrass curve secp192k1 */
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp192k1_Pub  = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PUBLIC_KEY, .size = MCUXCLECC_WEIERECC_SECP192K1_SIZE_PUBLICKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_secp192k1};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp192k1_Priv = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PRIVATE_KEY, .size = MCUXCLECC_WEIERECC_SECP192K1_SIZE_PRIVATEKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_secp192k1};

/* Key type structure for private and public ECC keys for Weierstrass curve secp224k1 */
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp224k1_Pub  = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PUBLIC_KEY, .size = MCUXCLECC_WEIERECC_SECP224K1_SIZE_PUBLICKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_secp224k1};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp224k1_Priv = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PRIVATE_KEY, .size = MCUXCLECC_WEIERECC_SECP224K1_SIZE_PRIVATEKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_secp224k1};

/* Key type structure for private and public ECC keys for Weierstrass curve secp256k1 */
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp256k1_Pub  = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PUBLIC_KEY, .size = MCUXCLECC_WEIERECC_SECP256K1_SIZE_PUBLICKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_secp256k1};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp256k1_Priv = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PRIVATE_KEY, .size = MCUXCLECC_WEIERECC_SECP256K1_SIZE_PRIVATEKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_secp256k1};

/* Key type structure for private and public ECC keys for Weierstrass curve secp192r1 */
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp192r1_Pub  = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PUBLIC_KEY, .size = MCUXCLECC_WEIERECC_SECP192R1_SIZE_PUBLICKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_secp192r1};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp192r1_Priv = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PRIVATE_KEY, .size = MCUXCLECC_WEIERECC_SECP192R1_SIZE_PRIVATEKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_secp192r1};

/* Key type structure for private and public ECC keys for Weierstrass curve secp224r1 */
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp224r1_Pub  = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PUBLIC_KEY, .size = MCUXCLECC_WEIERECC_SECP224R1_SIZE_PUBLICKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_secp224r1};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp224r1_Priv = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PRIVATE_KEY, .size = MCUXCLECC_WEIERECC_SECP224R1_SIZE_PRIVATEKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_secp224r1};

/* Key type structure for private and public ECC keys for Weierstrass curve secp256r1 */
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp256r1_Pub  = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PUBLIC_KEY, .size = MCUXCLECC_WEIERECC_SECP256R1_SIZE_PUBLICKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_secp256r1};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp256r1_Priv = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PRIVATE_KEY, .size = MCUXCLECC_WEIERECC_SECP256R1_SIZE_PRIVATEKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_secp256r1};

/* Key type structure for private and public ECC keys for Weierstrass curve secp384r1 */
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp384r1_Pub  = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PUBLIC_KEY, .size = MCUXCLECC_WEIERECC_SECP384R1_SIZE_PUBLICKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_secp384r1};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp384r1_Priv = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PRIVATE_KEY, .size = MCUXCLECC_WEIERECC_SECP384R1_SIZE_PRIVATEKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_secp384r1};

/* Key type structure for private and public ECC keys for Weierstrass curve secp521r1 */
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp521r1_Pub  = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PUBLIC_KEY, .size = MCUXCLECC_WEIERECC_SECP521R1_SIZE_PUBLICKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_secp521r1};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_secp521r1_Priv = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PRIVATE_KEY, .size = MCUXCLECC_WEIERECC_SECP521R1_SIZE_PRIVATEKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_secp521r1};

/* Key type structure for private and public ECC keys for Weierstrass curve brainpoolP160r1 */
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP160r1_Pub  = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PUBLIC_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP160R1_SIZE_PUBLICKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP160r1};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP160r1_Priv = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PRIVATE_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP160R1_SIZE_PRIVATEKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP160r1};

/* Key type structure for private and public ECC keys for Weierstrass curve brainpoolP192r1 */
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP192r1_Pub  = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PUBLIC_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP192R1_SIZE_PUBLICKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP192r1};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP192r1_Priv = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PRIVATE_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP192R1_SIZE_PRIVATEKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP192r1};

/* Key type structure for private and public ECC keys for Weierstrass curve brainpoolP224r1 */
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP224r1_Pub  = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PUBLIC_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP224R1_SIZE_PUBLICKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP224r1};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP224r1_Priv = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PRIVATE_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP224R1_SIZE_PRIVATEKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP224r1};

/* Key type structure for private and public ECC keys for Weierstrass curve brainpoolP256r1 */
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP256r1_Pub  = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PUBLIC_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP256R1_SIZE_PUBLICKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP256r1};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP256r1_Priv = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PRIVATE_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP256R1_SIZE_PRIVATEKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP256r1};

/* Key type structure for private and public ECC keys for Weierstrass curve brainpoolP320r1 */
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP320r1_Pub  = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PUBLIC_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP320R1_SIZE_PUBLICKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP320r1};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP320r1_Priv = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PRIVATE_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP320R1_SIZE_PRIVATEKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP320r1};

/* Key type structure for private and public ECC keys for Weierstrass curve brainpoolP384r1 */
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP384r1_Pub  = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PUBLIC_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP384R1_SIZE_PUBLICKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP384r1};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP384r1_Priv = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PRIVATE_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP384R1_SIZE_PRIVATEKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP384r1};

/* Key type structure for private and public ECC keys for Weierstrass curve brainpoolP512r1 */
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP512r1_Pub  = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PUBLIC_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP512R1_SIZE_PUBLICKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP512r1};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP512r1_Priv = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PRIVATE_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP512R1_SIZE_PRIVATEKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP512r1};

/* Key type structure for private and public ECC keys for Weierstrass curve brainpoolP160t1 */
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP160t1_Pub  = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PUBLIC_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP160T1_SIZE_PUBLICKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP160t1};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP160t1_Priv = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PRIVATE_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP160T1_SIZE_PRIVATEKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP160t1};

/* Key type structure for private and public ECC keys for Weierstrass curve brainpoolP192t1 */
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP192t1_Pub  = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PUBLIC_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP192T1_SIZE_PUBLICKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP192t1};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP192t1_Priv = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PRIVATE_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP192T1_SIZE_PRIVATEKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP192t1};

/* Key type structure for private and public ECC keys for Weierstrass curve brainpoolP224t1 */
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP224t1_Pub  = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PUBLIC_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP224T1_SIZE_PUBLICKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP224t1};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP224t1_Priv = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PRIVATE_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP224T1_SIZE_PRIVATEKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP224t1};

/* Key type structure for private and public ECC keys for Weierstrass curve brainpoolP256t1 */
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP256t1_Pub  = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PUBLIC_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP256T1_SIZE_PUBLICKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP256t1};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP256t1_Priv = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PRIVATE_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP256T1_SIZE_PRIVATEKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP256t1};

/* Key type structure for private and public ECC keys for Weierstrass curve brainpoolP320t1 */
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP320t1_Pub  = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PUBLIC_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP320T1_SIZE_PUBLICKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP320t1};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP320t1_Priv = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PRIVATE_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP320T1_SIZE_PRIVATEKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP320t1};

/* Key type structure for private and public ECC keys for Weierstrass curve brainpoolP384t1 */
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP384t1_Pub  = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PUBLIC_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP384T1_SIZE_PUBLICKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP384t1};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP384t1_Priv = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PRIVATE_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP384T1_SIZE_PRIVATEKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP384t1};

/* Key type structure for private and public ECC keys for Weierstrass curve brainpoolP512t1 */
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP512t1_Pub  = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PUBLIC_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP512T1_SIZE_PUBLICKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP512t1};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_WeierECC_brainpoolP512t1_Priv = {.algoId = MCUXCLKEY_ALGO_ID_ECC_SHWS_GFP + MCUXCLKEY_ALGO_ID_PRIVATE_KEY, .size = MCUXCLECC_WEIERECC_BRAINPOOLP512T1_SIZE_PRIVATEKEY, .info = (void *) &mcuxClEcc_Weier_DomainParams_brainpoolP512t1};

/* Key type structure for private and public EdDSA keys for twisted Edwards curve Ed25519 */
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_EdDSA_Ed25519_Priv = {.algoId = MCUXCLKEY_ALGO_ID_ECC_EDDSA | MCUXCLKEY_ALGO_ID_PRIVATE_KEY, .size = MCUXCLECC_EDDSA_ED25519_SIZE_PRIVATEKEY, .info = (void *) &mcuxClEcc_EdDSA_DomainParams_Ed25519};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_EdDSA_Ed25519_Pub = {.algoId = MCUXCLKEY_ALGO_ID_ECC_EDDSA | MCUXCLKEY_ALGO_ID_PUBLIC_KEY, .size = MCUXCLECC_EDDSA_ED25519_SIZE_PUBLICKEY, .info = (void *) &mcuxClEcc_EdDSA_DomainParams_Ed25519};

/* Key type structure for private and public EdDSA keys for twisted Edwards curve Ed448 */
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_EdDSA_Ed448_Priv = {.algoId = MCUXCLKEY_ALGO_ID_ECC_EDDSA | MCUXCLKEY_ALGO_ID_PRIVATE_KEY, .size = MCUXCLECC_EDDSA_ED448_SIZE_PRIVATEKEY, .info = (void *) &mcuxClEcc_EdDSA_DomainParams_Ed448};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_EdDSA_Ed448_Pub = {.algoId = MCUXCLKEY_ALGO_ID_ECC_EDDSA | MCUXCLKEY_ALGO_ID_PUBLIC_KEY, .size = MCUXCLECC_EDDSA_ED448_SIZE_PUBLICKEY, .info = (void *) &mcuxClEcc_EdDSA_DomainParams_Ed448};

const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_Ecc_MontDH_Curve25519_KeyPair = {.algoId = MCUXCLKEY_ALGO_ID_ECC_MONTDH | MCUXCLKEY_ALGO_ID_KEY_PAIR, .size = MCUXCLKEY_SIZE_NOTUSED, .info = (void *) &mcuxClEcc_MontDH_DomainParams_Curve25519};
const mcuxClKey_TypeDescriptor_t mcuxClKey_TypeDescriptor_Ecc_MontDH_Curve448_KeyPair = {.algoId = MCUXCLKEY_ALGO_ID_ECC_MONTDH | MCUXCLKEY_ALGO_ID_KEY_PAIR, .size = MCUXCLKEY_SIZE_NOTUSED, .info = (void *) &mcuxClEcc_MontDH_DomainParams_Curve448};
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
