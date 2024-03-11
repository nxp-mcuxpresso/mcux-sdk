/*--------------------------------------------------------------------------*/
/* Copyright 2018-2024 NXP                                                  */
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
 * @file  mcuxClOsccaSm2_Internal_FP.h
 * @brief flow protection definitions
 */


#ifndef MCUXCLOSCCASM2_INTERNAL_FP_H_
#define MCUXCLOSCCASM2_INTERNAL_FP_H_

#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>

#define MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_ECC_BALANCE_INIT_PART                                  \
        (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_StartFupProgram)                              \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish)                               \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareToZero))

#define MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_ECC_BALANCE_SECOND_PART                                \
        (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareToZero))

#define MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_ECC_BALANCE_FAIL_PART                                  \
        (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_StartFupProgram)                              \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish)                               \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareToZero))

#define MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_INVERTPRIVATEKEY_BALANCE_FINAL_PART                    \
        (3u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op)                                      \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_ComputeModInv)                               \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish)                               \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Export))

#define MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_VERIFY_BALANCE_COMMON_PART                             \
        (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccInit)                                      \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPrepareParameters)                        \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccGenerateZ)                                \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Import)                                      \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op)                                          \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish))

#define MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_VERIFY_BALANCE_SECOND_PART                             \
        (7u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op)                                      \
        + 3u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish)                          \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Import)                                      \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointWithInit)                 \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointYNegNoInit)               \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointMultMontgomery)                      \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccJacPointCheck))


#define MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_VERIFY_BALANCE_THIRD_PART                              \
        (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_StartFupProgram)                              \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish)                               \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareToZero))

#define MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_VERIFY_BALANCE_FINAL_PART                              \
        (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointWithInit)                  \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointYNegNoInit)               \
        + 2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op)                                     \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish)                               \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_StartFupProgram)                             \
        + 2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Import)                                 \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointAddOrDouble)                         \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointMultMontgomery)                      \
        + 2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointConvert2Affine)                 \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccTransAffinePoint2Jac)                     \
        + 2u * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccJacPointCheck)                       \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareToZero))

#define MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_ENCRYPT_BALANCE_LOOP                                   \
        (mainLoopCounterCheck1 * (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccGenRandomBytes)   \
                                + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op)                  \
                                + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish))      \
        + mainLoopCounterCheck2 * (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op)                 \
                                 + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_WaitforFinish))     \
        )

#define MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_ENCRYPT_BALANCE_INIT_POINTMULT                         \
        (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPrepareParameters)                         \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccGenerateZ)                                \
        + 2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointWithInit)            \
        + 2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointYNegNoInit)          \
        + 2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Export)                                 \
        + 4U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccJacPointCheck)                       \
        + 2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccSecurePointMult)                     \
        + 2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointConvert2Affine)                 \
        + MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_ENCRYPT_BALANCE_LOOP)

#define MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_ENCRYPT_BALANCE_INIT_PART                              \
        (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccInit)                                      \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Encrypt_Internal_PointMult)                  \
        + 2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Export)                                 \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)                                          \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_SecondPartOfInitPhase))

#define MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_ENCDEC_BALANCE_UPDATE_PART                             \
        (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EncDec_UpdatePhase))

#define MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_ENCRYPT_BALANCE_FINALIZE_PART                          \
        (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process)                                          \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_finish)                                          \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)                                          \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear))

//SM2 DECRYPT FP Balance counter
#define MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_DECRYPT_BALANCE_INIT_PART                              \
        ( MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccInit)                                     \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPrepareParameters)                        \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccGenerateZ)                                \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointWithInit)                 \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointYNegNoInit)               \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Import)                                      \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccSecurePointMult)                          \
        + 2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccJacPointCheck)                       \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointConvert2Affine)                      \
        + 2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Export)                                 \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_SecondPartOfInitPhase))

#define MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_DECRYPT_BALANCE_FINALIZE_PART                          \
        (MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_process)                                          \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClHash_finish)                                          \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareBoolean))

#define MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_DECRYPT_BALANCE_FINALIZE_C3_OK                         \
        (MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_DECRYPT_BALANCE_FINALIZE_PART                         \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear))

//SM2 KeyExchange FP Balance counter
#define MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_KEYEX_BALANCE_INIT                                     \
        ( MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate)                                    \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_KeyExchange_Init)                            \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_LeadingZeros)                                \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointWithInit)                 \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointYNegNoInit)               \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Import)                                      \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccJacPointCheck))

#define MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_KEYEX_BALANCE_PART1                                    \
        (MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_KEYEX_BALANCE_INIT                                    \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccImportInputPointWithInit)                 \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccJacPointCheck)                            \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointMultMontgomery)                      \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointAddOrDouble))

#define MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_KEYEX_BALANCE_PART2                                    \
        (MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_KEYEX_BALANCE_PART1                                   \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccJacPointCheck))

#define MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_KEYEX_BALANCE_PART3                                    \
        (MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_KEYEX_BALANCE_PART2                                   \
        + 3U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_Import)                                 \
        + 2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_StartFupProgram)                        \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate)                                    \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_RobustCompareToZero))

#define MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_KEYEX_BALANCE_PART4                                    \
        (MCUXCLOSCCASM2_SECURITYCOUNTER_VAL_KEYEX_BALANCE_PART3                                   \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccSecurePointMult)                          \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccJacPointCheck)                            \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_EccPointConvert2Affine)                      \
        + 2U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOscca_switch_endianness)                         \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_KDF)                                         \
        + MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm2_HandleKeyConfirmation))

#endif /* MCUXCLOSCCASM2_INTERNAL_FP_H_ */
