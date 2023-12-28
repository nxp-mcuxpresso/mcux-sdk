/*--------------------------------------------------------------------------*/
/* Copyright 2022-2023 NXP                                                  */
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
 *
 * @file:   mcuxClRandomModes_Internal_SizeDefinitions.h
 * @brief:  This file contains size definitions to share them with other components
 *
 */

#ifndef MCUXCLRANDOMMODES_INTERNAL_SIZEDEFINITIONS_H_
#define MCUXCLRANDOMMODES_INTERNAL_SIZEDEFINITIONS_H_

#define MCUXCLRANDOMMODES_MAX( x, y ) ( ( x ) > ( y ) ? ( x ) : ( y ) )

#include <mcuxClConfig.h> // Exported features flags header
#if defined(MCUXCL_FEATURE_RANDOMMODES_DERIVATION_FUNCTION)
#include <mcuxClAes.h>
#endif
#include <stdint.h>
#include <stdbool.h>
#ifdef MCUXCL_FEATURE_RANDOMMODES_CTRDRBG
#include <internal/mcuxClRandomModes_Private_CtrDrbg.h>
#include <mcuxClRandom_Types.h>
#include <internal/mcuxClRandomModes_Private_Drbg.h>
#endif /* MCUXCL_FEATURE_RANDOMMODES_CTRDRBG */


/**************************************************************************************************/
/*                                                                                                */
/* Definition of max workarea sizes allocated by internal DRBG algorithm related helper functions */
/*                                                                                                */
/**************************************************************************************************/
#ifdef MCUXCL_FEATURE_RANDOMMODES_CTRDRBG
#ifdef MCUXCL_FEATURE_RANDOMMODES_DERIVATION_FUNCTION
/*
 * Description of how much cpuWa mcuxClRandomModes_CtrDrbg_bcc uses
 */
#define MCUXCLRANDOMMODES_CTRDRBG_BCC_CPUWA_SIZE     MCUXCLAES_BLOCK_SIZE

/*
 * Description of how much cpuWa mcuxClRandomModes_CtrDrbg_df uses at most, i.e. for the AES-256 CTR_DRBG case
 *
 * cpuWa          | IV | L | N | Seed | 0x80 | Padding over (L,N,Seed,0x80) | K            | X  | additionBlock  |
 * size in byte   | 16 | 4 | 4 | 64   | 1    |         0-7 => max=7         | 256 \ 8 = 32 | 16 |       16       |
 *
 */
#define MCUXCLRANDOMMODES_CTRDRBG_AES256_DF_IV                MCUXCLAES_BLOCK_SIZE
#define MCUXCLRANDOMMODES_CTRDRBG_AES256_DF_L                 (4)
#define MCUXCLRANDOMMODES_CTRDRBG_AES256_DF_N                 (4)
#define MCUXCLRANDOMMODES_CTRDRBG_AES256_DF_SEED              MCUXCLRANDOMMODES_ENTROPYINPUT_SIZE_INIT_CTR_DRBG_AES256
#define MCUXCLRANDOMMODES_CTRDRBG_AES256_DF_0X80              (1)
#define MCUXCLRANDOMMODES_CTRDRBG_AES256_DF_MAXPADDING        (7)
#define MCUXCLRANDOMMODES_CTRDRBG_AES256_DF_K_MAXSIZE         MCUXCLAES_AES256_KEY_SIZE
#define MCUXCLRANDOMMODES_CTRDRBG_AES256_DF_X                 MCUXCLAES_BLOCK_SIZE

#define MCUXCLRANDOMMODES_CTRDRBG_DERIVATIONFUNCTION_CPUWA_MAXSIZE     (\
                                                                        MCUXCLRANDOMMODES_CTRDRBG_AES256_DF_IV + \
                                                                        MCUXCLRANDOMMODES_ROUNDED_UP_CPU_WORDSIZE( \
                                                                        MCUXCLRANDOMMODES_CTRDRBG_AES256_DF_L + \
                                                                        MCUXCLRANDOMMODES_CTRDRBG_AES256_DF_N + \
                                                                        MCUXCLRANDOMMODES_CTRDRBG_AES256_DF_SEED + \
                                                                        MCUXCLRANDOMMODES_CTRDRBG_AES256_DF_0X80 + \
                                                                        MCUXCLRANDOMMODES_CTRDRBG_AES256_DF_MAXPADDING) * sizeof(uint32_t) + \
                                                                        MCUXCLRANDOMMODES_CTRDRBG_AES256_DF_K_MAXSIZE + \
                                                                        MCUXCLRANDOMMODES_CTRDRBG_AES256_DF_X + \
                                                                        MCUXCLRANDOMMODES_CTRDRBG_BCC_CPUWA_SIZE \
                                                                      )
#endif /* MCUXCL_FEATURE_RANDOMMODES_DERIVATION_FUNCTION */

/*
 * Description of how much cpuWa mcuxClRandomModes_CtrDrbg_UpdateState uses at most, i.e. for the AES-256 CTR_DRBG case
 *
 * cpuWa          | Seed                                             |
 * size in byte   | entropy_input size for AES-256 for the init case |
 *
 */
#define MCUXCLRANDOMMODES_CTRDRBG_UPDATESTATE_CPUWA_MAXSIZE     (MCUXCLRANDOMMODES_ROUND_UP_TO_AES_BLOCKSIZE(MCUXCLRANDOMMODES_SEEDLEN_CTR_DRBG_AES256))
#endif /* MCUXCL_FEATURE_RANDOMMODES_CTRDRBG */


#if defined(MCUXCL_FEATURE_RANDOMMODES_NORMALMODE) || defined(MCUXCL_FEATURE_RANDOMMODES_TESTMODE)
/*********************************************************************************************/
/*                                                                                           */
/* Definition of max workarea sizes allocated by function pointer functions                  */
/*     - instantiateAlgorithm                                                                */
/*     - reseedAlgorithm                                                                     */
/*     - generateAlgorithm                                                                   */
/*     - selftestAlgorithm                                                                   */
/*                                                                                           */
/*********************************************************************************************/
#ifdef MCUXCL_FEATURE_RANDOMMODES_CTRDRBG
#define MCUXCLRANDOMMODES_CTRDRBG_AES256_INIT_SEEDMATERIAL_SIZE  (MCUXCLRANDOMMODES_ROUNDED_UP_CPU_WORDSIZE(MCUXCLRANDOMMODES_MAX(MCUXCLRANDOMMODES_ENTROPYINPUT_SIZE_INIT_CTR_DRBG_AES256, MCUXCLRANDOMMODES_SEEDLEN_CTR_DRBG_AES256)) * sizeof(uint32_t))
#if defined(MCUXCL_FEATURE_RANDOMMODES_DERIVATION_FUNCTION)
/*
 * Description of how much cpuWa mcuxClRandomModes_CtrDrbg_instantiateAlgorithm uses at most
 *
 * cpuWa          | Seed                                   | cpuWa used by called functions |
 * size in byte   | entropy_input size for the init case   | Max(cpuWaDF, cpuWaUpdateState) |
 *
 */
#define MCUXCLRANDOMMODES_CTRDRBG_INSTANTIATEALGO_CPUWA_MAXSIZE (       \
        MCUXCLRANDOMMODES_CTRDRBG_AES256_INIT_SEEDMATERIAL_SIZE + \
        MCUXCLRANDOMMODES_MAX( \
            MCUXCLRANDOMMODES_CTRDRBG_DERIVATIONFUNCTION_CPUWA_MAXSIZE, \
            MCUXCLRANDOMMODES_CTRDRBG_UPDATESTATE_CPUWA_MAXSIZE         \
        ) \
    )
#endif /* MCUXCL_FEATURE_RANDOMMODES_DERIVATION_FUNCTION */

#define MCUXCLRANDOMMODES_CTRDRBG_AES256_RESEED_SEEDMATERIAL_SIZE  (MCUXCLRANDOMMODES_ROUNDED_UP_CPU_WORDSIZE(MCUXCLRANDOMMODES_MAX(MCUXCLRANDOMMODES_ENTROPYINPUT_SIZE_RESEED_CTR_DRBG_AES256, MCUXCLRANDOMMODES_SEEDLEN_CTR_DRBG_AES256)) * sizeof(uint32_t))
#if defined(MCUXCL_FEATURE_RANDOMMODES_DERIVATION_FUNCTION)
/*
 * Description of how much cpuWa mcuxClRandomModes_CtrDrbg_reseedAlgorithm uses at most
 *
 * cpuWa          | Seed                                     | cpuWa used by called functions |
 * size in byte   | entropy_input size for the reseed case   | Max(cpuWaDF, cpuWaUpdateState) |
 *
 */
#define MCUXCLRANDOMMODES_CTRDRBG_RESEEDALGO_CPUWA_MAXSIZE (       \
        MCUXCLRANDOMMODES_CTRDRBG_AES256_RESEED_SEEDMATERIAL_SIZE + \
        MCUXCLRANDOMMODES_MAX( \
            MCUXCLRANDOMMODES_CTRDRBG_DERIVATIONFUNCTION_CPUWA_MAXSIZE, \
            MCUXCLRANDOMMODES_CTRDRBG_UPDATESTATE_CPUWA_MAXSIZE         \
        ) \
    )
#endif /* MCUXCL_FEATURE_RANDOMMODES_DERIVATION_FUNCTION */

#define MCUXCLRANDOMMODES_CTRDRBG_AES256_GENERATE_ADDITIONALINPUT_SIZE  (MCUXCLRANDOMMODES_ROUNDED_UP_CPU_WORDSIZE(MCUXCLRANDOMMODES_SEEDLEN_CTR_DRBG_AES256) * sizeof(uint32_t))
/*
 * Description of how much cpuWa mcuxClRandomModes_CtrDrbg_generateAlgorithm uses at most
 *
 * cpuWa          | additional input | cpuWa used by called functions |
 * size in byte   |     seedlen      |        cpuWaUpdateState        |
 *
 */
#define MCUXCLRANDOMMODES_CTRDRBG_GENERATEALGO_CPUWA_MAXSIZE (       \
        MCUXCLRANDOMMODES_CTRDRBG_AES256_GENERATE_ADDITIONALINPUT_SIZE + \
        MCUXCLRANDOMMODES_CTRDRBG_UPDATESTATE_CPUWA_MAXSIZE \
    )
#endif /* MCUXCL_FEATURE_RANDOMMODES_CTRDRBG */
#endif /* MCUXCL_FEATURE_RANDOMMODES_NORMALMODE || MCUXCL_FEATURE_RANDOMMODES_TESTMODE */


/*********************************************************************************************/
/*                                                                                           */
/* Definition of max workarea sizes allocated by function pointer functions in test mode     */
/*     - initFunction                                                                        */
/*     - reseedFunction                                                                      */
/*     - generateFunction                                                                    */
/*                                                                                           */
/*********************************************************************************************/

#ifdef MCUXCL_FEATURE_RANDOMMODES_TESTMODE
/*
 * Description of how much cpuWa mcuxClRandomModes_TestMode_initFunction uses at most
 *
 * cpuWa          | Call to instantiateAlgo |
 * size in byte   | cpuWaInstantiateAlgo   |
 *
 */
#if defined(MCUXCL_FEATURE_RANDOMMODES_CTRDRBG)
#define MCUXCLRANDOMMODES_TESTMODE_INIT_CPUWA_MAXSIZE ( MCUXCLRANDOMMODES_CTRDRBG_INSTANTIATEALGO_CPUWA_MAXSIZE )
#endif /* MCUXCL_FEATURE_RANDOMMODES_CTRDRBG */

/*
 * Description of how much cpuWa mcuxClRandomModes_TestMode_reseedFunction uses at most
 *
 * cpuWa          | Call to reseedAlgo |
 * size in byte   |  cpuWaReseedAlgo   |
 *
 */
#if defined(MCUXCL_FEATURE_RANDOMMODES_CTRDRBG)
#define MCUXCLRANDOMMODES_TESTMODE_RESEED_CPUWA_MAXSIZE ( MCUXCLRANDOMMODES_CTRDRBG_RESEEDALGO_CPUWA_MAXSIZE )
#endif /* MCUXCL_FEATURE_RANDOMMODES_CTRDRBG */

/*
 * Description of how much cpuWa mcuxClRandomModes_generateFunction_PrDisabled/PTG3 uses at most
 *
 * cpuWa          | Call(s) to reseedFunc | Call(s) to generateAlgo |
 * size in byte   |    cpuWaReseedFunc    |    cpuWaGenerateAlgo    |
 *
 */
#if defined(MCUXCL_FEATURE_RANDOMMODES_CTRDRBG)
#define MCUXCLRANDOMMODES_TESTMODE_GENERATE_CPUWA_MAXSIZE ( \
            MCUXCLRANDOMMODES_MAX( \
                MCUXCLRANDOMMODES_TESTMODE_RESEED_CPUWA_MAXSIZE, \
                MCUXCLRANDOMMODES_CTRDRBG_GENERATEALGO_CPUWA_MAXSIZE) \
        )
#endif /* MCUXCL_FEATURE_RANDOMMODES_CTRDRBG */

/*
 * Description of how much cpuWa mcuxClRandomModes_TestMode_selftestFunction uses at most
 */
#if defined(MCUXCL_FEATURE_RANDOMMODES_CTRDRBG)
#define MCUXCLRANDOMMODES_TESTMODE_SELFTEST_CPUWA_MAXSIZE 0u
#endif /* MCUXCL_FEATURE_RANDOMMODES_CTRDRBG */
#else /* MCUXCL_FEATURE_RANDOMMODES_TESTMODE */
#define MCUXCLRANDOMMODES_TESTMODE_INIT_CPUWA_MAXSIZE 0u
#define MCUXCLRANDOMMODES_TESTMODE_RESEED_CPUWA_MAXSIZE 0u
#define MCUXCLRANDOMMODES_TESTMODE_GENERATE_CPUWA_MAXSIZE 0u
#define MCUXCLRANDOMMODES_TESTMODE_SELFTEST_CPUWA_MAXSIZE 0u
#endif /* MCUXCL_FEATURE_RANDOMMODES_TESTMODE */

/*********************************************************************************************/
/*                                                                                           */
/* Definition of max workarea sizes allocated by function pointer functions in normal mode   */
/*     - initFunction                                                                        */
/*     - reseedFunction                                                                      */
/*     - generateFunction                                                                    */
/*     - selftestFunction                                                                    */
/*                                                                                           */
/*********************************************************************************************/

#ifdef MCUXCL_FEATURE_RANDOMMODES_NORMALMODE
/*
 * Description of how much cpuWa mcuxClRandomModes_NormalMode_initFunction uses at most
 *
 * cpuWa          | Seed                                   | Call to instantiateAlgo |
 * size in byte   | entropy_input size for the init case   |  cpuWaInstantiateAlgo   |
 *
 */
#if defined(MCUXCL_FEATURE_RANDOMMODES_CTRDRBG)
#define MCUXCLRANDOMMODES_NORMALMODE_INIT_CPUWA_MAXSIZE ( \
            MCUXCLRANDOMMODES_ROUNDED_UP_CPU_WORDSIZE(MCUXCLRANDOMMODES_ENTROPYINPUT_SIZE_INIT_CTR_DRBG_AES256) * sizeof(uint32_t) + \
            MCUXCLRANDOMMODES_CTRDRBG_INSTANTIATEALGO_CPUWA_MAXSIZE \
        )
#endif

/*
 * Description of how much cpuWa mcuxClRandomModes_NormalMode_reseedFunction uses at most
 *
 * cpuWa          | Seed                                     | Call to reseedAlgo |
 * size in byte   | entropy_input size for the reseed case   |  cpuWaReseedAlgo   |
 *
 */
#if defined(MCUXCL_FEATURE_RANDOMMODES_CTRDRBG)
#define MCUXCLRANDOMMODES_NORMALMODE_RESEED_CPUWA_MAXSIZE ( \
            MCUXCLRANDOMMODES_ROUNDED_UP_CPU_WORDSIZE(MCUXCLRANDOMMODES_ENTROPYINPUT_SIZE_RESEED_CTR_DRBG_AES256) * sizeof(uint32_t) + \
            MCUXCLRANDOMMODES_CTRDRBG_RESEEDALGO_CPUWA_MAXSIZE \
        )
#endif

/*
 * Description of how much cpuWa mcuxClRandomModes_generateFunction_PrDisabled/PTG3 uses at most
 *
 * cpuWa          | Call(s) to reseedFunc | Call(s) to generateAlgo |
 * size in byte   |    cpuWaReseedFunc    |    cpuWaGenerateAlgo    |
 *
 */
#if defined(MCUXCL_FEATURE_RANDOMMODES_CTRDRBG)
#define MCUXCLRANDOMMODES_NORMALMODE_GENERATE_CPUWA_MAXSIZE ( \
            MCUXCLRANDOMMODES_MAX( \
                MCUXCLRANDOMMODES_NORMALMODE_RESEED_CPUWA_MAXSIZE, \
                MCUXCLRANDOMMODES_CTRDRBG_GENERATEALGO_CPUWA_MAXSIZE) \
        )
#endif

/*
 * Description of how much cpuWa mcuxClRandomModes_NormalMode_selftestFunction uses at most
 *
 * cpuWa          | Call(s) to initFunc | Call(s) to reseedFunc | Call(s) to generateFunc |
 * size in byte   |    cpuWaInitFunc    |    cpuWaReseedFunc    |    cpuWaGenerateFunc    |
 */
#if defined(MCUXCL_FEATURE_RANDOMMODES_CTRDRBG)
#define MCUXCLRANDOMMODES_NORMALMODE_SELFTEST_CPUWA_MAXSIZE ( \
            sizeof(mcuxClRandom_ModeDescriptor_t) + \
            sizeof(mcuxClRandomModes_Context_CtrDrbg_Aes256_t) + \
            MCUXCLRANDOMMODES_MAX(MCUXCLRANDOMMODES_TESTMODE_INIT_CPUWA_MAXSIZE, \
                MCUXCLRANDOMMODES_MAX(MCUXCLRANDOMMODES_TESTMODE_RESEED_CPUWA_MAXSIZE, \
                    MCUXCLRANDOMMODES_TESTMODE_GENERATE_CPUWA_MAXSIZE \
                ) \
            ) \
        )
#endif
#else /* MCUXCL_FEATURE_RANDOMMODES_NORMALMODE */
#define MCUXCLRANDOMMODES_NORMALMODE_INIT_CPUWA_MAXSIZE 0u
#define MCUXCLRANDOMMODES_NORMALMODE_RESEED_CPUWA_MAXSIZE 0u
#define MCUXCLRANDOMMODES_NORMALMODE_GENERATE_CPUWA_MAXSIZE 0u
#define MCUXCLRANDOMMODES_NORMALMODE_SELFTEST_CPUWA_MAXSIZE 0u
#endif /* MCUXCL_FEATURE_RANDOMMODES_NORMALMODE */


/*********************************************************************************************/
/*                                                                                           */
/* Definition of workarea sizes for API functions                                            */
/*     - init                                                                                */
/*     - reseed                                                                              */
/*     - generate                                                                            */
/*     - selftest                                                                            */
/*                                                                                           */
/*********************************************************************************************/

/*
 * Maximum cpuWa size for init
 */
#define MCUXCLRANDOMMODES_INIT_WACPU_SIZE_MAX     ( \
        MCUXCLRANDOMMODES_MAX(MCUXCLRANDOMMODES_NORMALMODE_INIT_CPUWA_MAXSIZE, \
                             MCUXCLRANDOMMODES_MAX(MCUXCLRANDOMMODES_TESTMODE_INIT_CPUWA_MAXSIZE, \
                                                  4u \
                                                  ) \
                             ) \
        )

/*
 * Maximum cpuWa size for reseed
 */
#define MCUXCLRANDOMMODES_RESEED_WACPU_SIZE_MAX     ( \
        MCUXCLRANDOMMODES_MAX(MCUXCLRANDOMMODES_NORMALMODE_RESEED_CPUWA_MAXSIZE, \
                             MCUXCLRANDOMMODES_MAX(MCUXCLRANDOMMODES_TESTMODE_RESEED_CPUWA_MAXSIZE, \
                                                  4u \
                                                  ) \
                             ) \
        )

/*
 * Maximum cpuWa size for generate
 */
#define MCUXCLRANDOMMODES_GENERATE_WACPU_SIZE_MAX     ( \
        MCUXCLRANDOMMODES_MAX(MCUXCLRANDOMMODES_NORMALMODE_GENERATE_CPUWA_MAXSIZE, \
                             MCUXCLRANDOMMODES_MAX(MCUXCLRANDOMMODES_TESTMODE_GENERATE_CPUWA_MAXSIZE, \
                                                  4u \
                                                  ) \
                             ) \
        )

/*
 * Maximum cpuWa size for selftest
 */
#define MCUXCLRANDOMMODES_SELFTEST_WACPU_SIZE_MAX     ( \
        MCUXCLRANDOMMODES_MAX(MCUXCLRANDOMMODES_NORMALMODE_SELFTEST_CPUWA_MAXSIZE, \
                             MCUXCLRANDOMMODES_MAX(MCUXCLRANDOMMODES_TESTMODE_SELFTEST_CPUWA_MAXSIZE, \
                                                  4u \
                                                  ) \
                             ) \
        )

/*
 * Maximum cpuWa size over all API functions
 */
#define MCUXCLRANDOMMODES_CPUWA_MAXSIZE ( \
        MCUXCLRANDOMMODES_MAX(MCUXCLRANDOMMODES_INIT_WACPU_SIZE_MAX, \
                              MCUXCLRANDOMMODES_MAX(MCUXCLRANDOMMODES_RESEED_WACPU_SIZE_MAX, \
                                                    MCUXCLRANDOMMODES_MAX(MCUXCLRANDOMMODES_GENERATE_WACPU_SIZE_MAX, \
                                                                          MCUXCLRANDOMMODES_SELFTEST_WACPU_SIZE_MAX \
                                                                          )\
                                                    )\
                              ) \
        )

#endif /* MCUXCLRANDOMMODES_INTERNAL_SIZEDEFINITIONS_H_ */
