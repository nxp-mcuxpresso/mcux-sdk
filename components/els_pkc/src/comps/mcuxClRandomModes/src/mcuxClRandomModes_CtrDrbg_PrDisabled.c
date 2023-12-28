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

#include <mcuxClRandomModes.h>
#include <mcuxClSession.h>
#include <mcuxCsslAnalysis.h>

#include <mcuxClRandomModes_MemoryConsumption.h>
#include <internal/mcuxClRandom_Internal_Types.h>
#include <internal/mcuxClRandomModes_Private_CtrDrbg.h>
#include <internal/mcuxClRandomModes_Private_NormalMode.h>
#ifdef MCUXCL_FEATURE_RANDOMMODES_TESTMODE
#include <internal/mcuxClRandomModes_Private_TestMode.h>
#endif /* MCUXCL_FEATURE_RANDOMMODES_TESTMODE */
#include <internal/mcuxClRandomModes_Private_PrDisabled.h>
#include <internal/mcuxClRandomModes_Private_Drbg.h>

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
const mcuxClRandomModes_DrbgAlgorithmsDescriptor_t mcuxClRandomModes_DrbgAlgorithmsDescriptor_CtrDrbg_PrDisabled =
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    .instantiateAlgorithm = mcuxClRandomModes_CtrDrbg_instantiateAlgorithm,
    .reseedAlgorithm = mcuxClRandomModes_CtrDrbg_reseedAlgorithm,
    .generateAlgorithm = mcuxClRandomModes_CtrDrbg_generateAlgorithm,
    .selftestAlgorithm = mcuxClRandomModes_PrDisabled_selftestAlgorithm,
    .protectionTokenInstantiateAlgorithm = MCUX_CSSL_FP_FUNCID_mcuxClRandomModes_CtrDrbg_instantiateAlgorithm,
    .protectionTokenReseedAlgorithm = MCUX_CSSL_FP_FUNCID_mcuxClRandomModes_CtrDrbg_reseedAlgorithm,
    .protectionTokenGenerateAlgorithm = MCUX_CSSL_FP_FUNCID_mcuxClRandomModes_CtrDrbg_generateAlgorithm,
    .protectionTokenSelftestAlgorithm = MCUX_CSSL_FP_FUNCID_mcuxClRandomModes_PrDisabled_selftestAlgorithm
};

#ifdef MCUXCL_FEATURE_RANDOMMODES_DERIVATION_FUNCTION
/* Constants for RNG health testing
 * This data originates from  NIST DRBG test vectors (NIST SP 800-90A DRBGVS)
 * Use DF,
 * No PR,
 * NonceLen = 0,
 * PersonalizationStringLen = 0,
 * AdditionalInputLen = 0
 * Random data is read after second generate call
 *
 * Data has been adapted from BE Byte Order to LE Byte Order
 */
#ifdef MCUXCL_FEATURE_RANDOMMODES_SECSTRENGTH_256
/* EntropyInput = 04e6975d5082bf4593c1fd93c2020624ee887666cec3fec73d6bcd376cba3f0f18c07c7ef6773a145a7f9e926cb3cd2c42cc66b30a52ec1c7a75964712933985f5e8b42d4af007 */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
static const uint32_t mcuxClRandomModes_TestVectors_Entropy_Init_Aes256_PrDisabled[] =
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    0x5d97e604u, 0x45bf8250u, 0x93fdc193u, 0x240602c2u, 0x667688eeu, 0xc7fec3ceu, 0x37cd6b3du, 0x0f3fba6cu,
    0x7e7cc018u, 0x143a77f6u, 0x929e7f5au, 0x2ccdb36cu, 0xb366cc42u, 0x1cec520au, 0x4796757au, 0x85399312u,
    0x2db4e8f5u, 0x0007f04au
};
#endif

#ifdef MCUXCL_FEATURE_RANDOMMODES_SECSTRENGTH_256
/* EntropyInputReseed = 41e7cf20e5b487d9d981ed7a0186872d774e610b4e246c5a899da1f4a0538c05c6d43b9726575560d3a6c4117f39cba6ba9eef65a8469d */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
static const uint32_t mcuxClRandomModes_TestVectors_Entropy_Reseed_Aes256_PrDisabled[] =
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    0x20cfe741u, 0xd987b4e5u, 0x7aed81d9u, 0x2d878601u, 0x0b614e77u, 0x5a6c244eu, 0xf4a19d89u, 0x058c53a0u,
    0x973bd4c6u, 0x60555726u, 0x11c4a6d3u, 0xa6cb397fu, 0x65ef9ebau, 0x009d46a8u
};
#endif

#ifdef MCUXCL_FEATURE_RANDOMMODES_SECSTRENGTH_256
/* ReturnedBits = 8e929981e59b246182c93b161a0f7900b1a65bff6579ab3dbf13ac040e9eb7964c23e17ece53d5e68adcae46c9feb06f4d48601f3483dbce99c314aa77a95f92 */
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
static const uint32_t mcuxClRandomModes_TestVectors_RandomData_Aes256_PrDisabled[] = {
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
    0x8199928eu, 0x61249be5u, 0x163bc982u, 0x00790f1au, 0xff5ba6b1u, 0x3dab7965u, 0x04ac13bfu, 0x96b79e0eu,
    0x7ee1234cu, 0xe6d553ceu, 0x46aedc8au, 0x6fb0fec9u, 0x1f60484du, 0xcedb8334u, 0xaa14c399u, 0x925fa977u
};
#endif

#ifdef MCUXCL_FEATURE_RANDOMMODES_SECSTRENGTH_256
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
static const uint32_t * const mcuxClRandomModes_TestVectors_Aes256_PrDisabled[MCUXCLRANDOMMODES_NO_OF_TESTVECTORS_PRDISABLED] =
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    mcuxClRandomModes_TestVectors_Entropy_Init_Aes256_PrDisabled,
    mcuxClRandomModes_TestVectors_Entropy_Reseed_Aes256_PrDisabled,
    mcuxClRandomModes_TestVectors_RandomData_Aes256_PrDisabled
};
#endif



#ifdef MCUXCL_FEATURE_RANDOMMODES_SECSTRENGTH_256
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
static const mcuxClRandomModes_DrbgModeDescriptor_t mcuxClRandomModes_DrbgModeDescriptor_CtrDrbg_AES256_PrDisabled =
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    .pDrbgAlgorithms = &mcuxClRandomModes_DrbgAlgorithmsDescriptor_CtrDrbg_PrDisabled,
    .pDrbgVariant = &mcuxClRandomModes_DrbgVariantDescriptor_CtrDrbg_AES256,
    .pDrbgTestVectors = mcuxClRandomModes_TestVectors_Aes256_PrDisabled,
    .continuousReseedInterval = 0u
};
#endif
#else
/* Constants for RNG health testing
 * This data originates from  NIST DRBG test vectors (NIST SP 800-90A DRBGVS)
 * No DF,
 * No PR,
 * NonceLen = 0,
 * PersonalizationStringLen = 0,
 * AdditionalInputLen = 0
 * Random data is read after second generate call
 *
 * Data has been adapted from BE Byte Order to LE Byte Order
 */

// TODO: Add test vectors for the "no derivation function case"

#endif /* MCUXCL_FEATURE_RANDOMMODES_DERIVATION_FUNCTION */




#ifdef MCUXCL_FEATURE_RANDOMMODES_SECSTRENGTH_256
MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to initialize the generic structure member.")
const mcuxClRandom_ModeDescriptor_t mcuxClRandomModes_mdCtrDrbg_AES256_DRG3 = {
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
    .pOperationMode   = &mcuxClRandomModes_OperationModeDescriptor_NormalMode_PrDisabled,
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST("Casts to void* are allowed")
    .pDrbgMode        = (void *) &mcuxClRandomModes_DrbgModeDescriptor_CtrDrbg_AES256_PrDisabled,
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST()
    .contextSize      = MCUXCLRANDOMMODES_CTR_DRBG_AES256_CONTEXT_SIZE,
#ifdef MCUXCL_FEATURE_RANDOMMODES_TESTMODE
    .auxParam         = (uint32_t) &mcuxClRandomModes_OperationModeDescriptor_TestMode_PrDisabled,
#else
    .auxParam         = 0u,
#endif /* MCUXCL_FEATURE_RANDOMMODES_TESTMODE */
    .securityStrength = MCUXCLRANDOMMODES_SECURITYSTRENGTH_CTR_DRBG_AES256
};
MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
#endif

