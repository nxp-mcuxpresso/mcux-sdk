/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021 NXP                                                  */
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

/** @file  mcuxClEcc_Internal.h
 *  @brief Internal header of mcuxClEcc component
 */


#ifndef MCUXCLECC_INTERNAL_H_
#define MCUXCLECC_INTERNAL_H_

#include <stdbool.h>
#include <mcuxClMemory.h>
#include <mcuxCsslFlowProtection.h>

#include <internal/mcuxClPkc_FupMacros.h>

#include <mcuxClEcc_FUP.h>
#include <mcuxClEcc_Internal_KeyGen_FUP.h>
#include <mcuxClEcc_KeyGen_FUP.h>
#include <mcuxClEcc_Sign_FUP.h>
#include <mcuxClEcc_PointMult_FUP.h>
#include <mcuxClEcc_Internal_PointCheck_FUP.h>
#include <mcuxClEcc_Internal_SecurePointMult_CoZMontLadder_FUP.h>
#include <mcuxClEcc_Internal_FUP.h>

#include <mcuxClEcc.h>


/**********************************************************/
/* Internal return codes of mcuxClEcc                      */
/**********************************************************/


#define MCUXCLECC_INTSTATUS_POINTCHECK_OK           ((mcuxClEcc_Status_t) 0x55AAC33Cu)
#define MCUXCLECC_INTSTATUS_POINTCHECK_NOTOK        ((mcuxClEcc_Status_t) 0x55AAE817u)
#define MCUXCLECC_INTSTATUS_POINTADD_OK             ((mcuxClEcc_Status_t) 0x55AAC639u)
#define MCUXCLECC_INTSTATUS_POINTADD_NEUTRAL_POINT  ((mcuxClEcc_Status_t) 0x55AAD12Eu)
#define MCUXCLECC_INTSTATUS_RNG_ERROR               ((mcuxClEcc_Status_t) 0x55AAD827u)

/* Rule of ECC return codes:
 * All return codes are of the format: 0x55XXYYTT
 * API         : XX = 55
 * Internal    : XX = AA
 * HammingWeight(YY) = HammingWeight(TT) = 4, according to coding guidelines
 * YY needs to be a balanced byte, and TT = ~YY
 *
 * General  OK  : YYTT = 5555
 * Fault Attack : YYTT = F00F
 */


/**********************************************************/
/* Indices of operands in PKC workarea and UPTR table     */
/**********************************************************/
#define ECC_P    0x00u
#define ECC_N    0x01u
#define ECC_VT2  0x02u
#define ECC_VT3  0x03u

#define ECC_VX0  0x04u
#define ECC_VY0  0x05u
#define ECC_VZ0  0x06u
#define ECC_VZ   0x07u

#define ECC_VX1  0x08u
#define ECC_VY1  0x09u
#define ECC_VA   0x0Au
#define ECC_VB   0x0Bu

#define ECC_VX2  0x0Cu
#define ECC_VY2  0x0Du
#define ECC_VZ2  0x0Eu
#define ECC_VT   0x0Fu

#define ECC_PS   0x10u
#define ECC_NS   0x11u
#define ECC_R0   0x12u
#define ECC_R1   0x13u

#define ECC_PFULL  0x14u
#define ECC_NFULL  0x15u
#define ECC_PQSQR  0x16u
#define ECC_NQSQR  0x17u

#define ECC_S0  0x18u
#define ECC_S1  0x19u
#define ECC_S2  0x1Au
#define ECC_S3  0x1Bu
#define ECC_T0  0x1Cu
#define ECC_T1  0x1Du
#define ECC_T2  0x1Eu
#define ECC_T3  0x1Fu

#define ECC_XA  0x20u
#define ECC_YA  0x21u
#define ECC_ZA  0x22u
#define ECC_Z   0x23u
#define ECC_X0  0x24u
#define ECC_Y0  0x25u
#define ECC_X1  0x26u
#define ECC_Y1  0x27u
#define ECC_X2  0x28u
#define ECC_Y2  0x29u
#define ECC_X3  0x2Au
#define ECC_Y3  0x2Bu


#define ECC_KEYGEN_NO_OF_VIRTUALS  0x10u
#define ECC_KEYGEN_NO_OF_BUFFERS0   0x8u  /* PS ~ NQSQR */
#define ECC_KEYGEN_NO_OF_BUFFERS1   0x8u  /* S0 ~ T3, interleaved (double-size) */
#define ECC_KEYGEN_NO_OF_BUFFERS2   0x8u  /* XA ~ Y1 */
#define ECC_KEYGEN_NO_OF_BUFFERS   0x18u

#define ECC_SIGN_NO_OF_VIRTUALS  0x10u
#define ECC_SIGN_NO_OF_BUFFERS0   0x8u  /* PS ~ NQSQR */
#define ECC_SIGN_NO_OF_BUFFERS1   0x8u  /* S0 ~ T3, interleaved (double-size) */
#define ECC_SIGN_NO_OF_BUFFERS2   0x8u  /* XA ~ Y1 */
#define ECC_SIGN_NO_OF_BUFFERS   0x18u

#define ECC_VERIFY_NO_OF_VIRTUALS  0x10u
#define ECC_VERIFY_NO_OF_BUFFERS   0x1Cu

#define ECC_POINTMULT_NO_OF_VIRTUALS  0x10u
#define ECC_POINTMULT_NO_OF_BUFFERS   0x18u


/**********************************************************/
/* Helper macros for accessing UPTRT table                */
/**********************************************************/
/** Macro for reading 2 offsets in UPTRT table.
 * [in] pOps: pointer to 16-bit offset table. This pointer must be 32-bit aligned;
 * [in] idx0, idx1: compile-time-constant indices of offsets in the table.
 * @attention not compile-time-constant indices will cause extra code size.
 * @attention if the two offsets are not in the same CPU word, this macro might cause extra code size.
 */
#define MCUXCLECC_LOAD_2OFFSETS(pOps, idx0, idx1)  \
    ({  \
        uint32_t offset1_offset0;  \
        if ( (0u == ((idx0) & (0x01u))) && ((idx1) == ((idx0) + (0x01u))) )  \
        { /* MISRA Ex. 9 - Rule 11.3 - UPTR table is 32-bit aligned in ECC component */ \
          offset1_offset0 = ((uint32_t *) (pOps))[(idx0) / 2u]; \
        }  \
        else  \
        { /* MISRA Ex. 9 - Rule 11.3 - Cast to 16-bit pointer table */ \
          offset1_offset0 = (uint32_t) ((uint16_t *) (pOps))[idx0] | ((uint32_t) ((uint16_t *) (pOps))[idx1] << 16); \
        }  \
        (offset1_offset0);  \
    })

/** Macro for writing 2 offsets to UPTRT table.
 * [in] pOps: pointer to 16-bit offset table. This pointer must be 32-bit aligned;
 * [in] idx0, idx1: compile-time-constant indices of offsets in the table.
 * @attention not compile-time-constant indices will cause extra code size.
 * @attention if the two offsets are not in the same CPU word, this macro might cause extra code size.
 */
#define MCUXCLECC_STORE_2OFFSETS(pOps, idx0, idx1, ofs1_ofs0)  \
    do{ \
        if ( (0u == ((idx0) & (0x01u))) && ((idx1) == ((idx0) + (0x01u))) )  \
        { /* MISRA Ex. 9 - Rule 11.3 - UPTR table is 32-bit aligned in ECC component */ \
          ((uint32_t *) (pOps))[(idx0) / 2u] = (ofs1_ofs0); \
        }  \
        else  \
        { /* MISRA Ex. 9 - Rule 11.3 - Cast to 16-bit pointer table */ \
          ((uint16_t *) (pOps))[idx0] = (uint16_t) ((ofs1_ofs0) & 0xFFFFu);  \
          ((uint16_t *) (pOps))[idx1] = (uint16_t) ((ofs1_ofs0) >> 16); \
        }  \
    } while(false)

/** Macro for copying 2 offsets in UPTRT table.
 * [in] pOps: pointer to 16-bit offset table. This pointer must be 32-bit aligned;
 * [in] dIdx0, dIdx1, sIdx0, sIdx1: compile-time-constant indices of offsets in the table.
 * @attention not compile-time-constant indices will cause extra code size.
 */
#define MCUXCLECC_COPY_2OFFSETS(pOps, dIdx0, dIdx1, sIdx0, sIdx1)  \
    do{  \
        if (   (0u == ((dIdx0) & (0x01u)))         \
            && ((dIdx1) == ((dIdx0) + (0x01u)))    \
            && (0u == ((sIdx0) & (0x01u)))         \
            && ((sIdx1) == ((sIdx0) + (0x01u))) )  \
        {   /* MISRA Ex. 9 - Rule 11.3 - UPTR table is 32-bit aligned in ECC component */ \
            ((uint32_t *) (pOps))[(dIdx0) / 2u] = ((uint32_t *) (pOps))[(sIdx0) / 2u]; \
        }  \
        else  \
        {   /* MISRA Ex. 9 - Rule 11.3 - Cast to 16-bit pointer table */  \
            ((uint16_t *) (pOps))[dIdx0] = ((uint16_t *) (pOps))[sIdx0];  \
            ((uint16_t *) (pOps))[dIdx1] = ((uint16_t *) (pOps))[sIdx1];  \
        }  \
    } while (false)


/**********************************************************/
/* Helper macros of import/export with flow protection    */
/**********************************************************/
/** Helper macro to call #mcuxClMemory_copy with flow protection. */
#define MCUXCLECC_FP_MEMORY_COPY(pTarget, pSource, byteLen)  \
    do {  \
        MCUX_CSSL_FP_FUNCTION_CALL(retCodeTemp,  \
            mcuxClMemory_copy((uint8_t *) (pTarget), (const uint8_t *) (pSource), byteLen, byteLen)); \
        (void) retCodeTemp;  \
    } while(false)

/** Helper macro to call #mcuxClMemory_copy for importing data to PKC workarea with flow protection. */
#define MCUXCLECC_FP_IMPORT_TO_PKC_BUFFER(pOffsetTable, iTarget, pSource, byteLen)  \
    MCUXCLECC_FP_MEMORY_COPY(MCUXCLPKC_OFFSET2PTR((pOffsetTable)[iTarget]), pSource, byteLen)

#define MCUXCLECC_FP_CALLED_MEMORY_COPY  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)
#define MCUXCLECC_FP_CALLED_IMPORT_TO_PKC_BUFFER  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy)


/**********************************************************/
/* Internal function declaration                          */
/**********************************************************/

MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Interleave(uint16_t iScalar0_iScalar1, uint32_t bitLenScalar);
/** Helper macro to call #mcuxClEcc_Interleave with flow protection. */
#define MCUXCLECC_FP_INTERLEAVE(iS0_iS1, bitLenScalar)  \
    do{ \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClEcc_Interleave(iS0_iS1, bitLenScalar));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while (false)

/**********************************************************/
/* Internal function declaration - point check            */
/**********************************************************/
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_PointCheckAffineNR)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_PointCheckAffineNR(void);

/** Helper macro to call #mcuxClEcc_PointCheckAffineNR with flow protection. */
#define MCUXCLECC_FP_POINTCHECKAFFINENR()  \
    ({ \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClEcc_PointCheckAffineNR());  \
        (retValTemp);  \
    })


/**********************************************************/
/* Internal function declaration - point arithmetic       */
/**********************************************************/
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_RepeatPointDouble)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_RepeatPointDouble(uint32_t iteration);

/** Helper macro to call #mcuxClEcc_RepeatPointDouble with flow protection. */
#define MCUXCLECC_FP_REPEATPOINTDOUBLE(iteration)  \
    do{ \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClEcc_RepeatPointDouble(iteration));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while (false)

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_PointFullAdd)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_PointFullAdd(void);

/** Helper macro to call #mcuxClEcc_PointFullAdd with flow protection. */
#define MCUXCLECC_FP_POINTFULLADD()  \
    ({ \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClEcc_PointFullAdd());  \
        (retValTemp);  \
    })


/**********************************************************/
/* Internal function declaration - point multiplication   */
/**********************************************************/
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_Int_PointMult)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Int_PointMult(uint8_t iScalar, uint32_t scalarBitLen);

/** Helper macro to call #mcuxClEcc_Int_PointMult with flow protection. */
#define MCUXCLECC_FP_INT_POINTMULT(iScalar, scalarBitLen)  \
    do{ \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClEcc_Int_PointMult(iScalar, scalarBitLen));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while (false)

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_SecurePointMult)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_SecurePointMult(uint8_t iScalar,
                                                                       uint32_t scalarBitLen);
/** Helper macro to call #mcuxClEcc_SecurePointMult with flow protection. */
#define MCUXCLECC_FP_SECUREPOINTMULT(iScalar, scalarBitLen)  \
    do{ \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClEcc_SecurePointMult(iScalar, scalarBitLen));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while (false)


/**********************************************************/
/* Internal function declaration - key generation         */
/**********************************************************/
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClEcc_Int_CoreKeyGen)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClEcc_Status_t) mcuxClEcc_Int_CoreKeyGen(mcuxClSession_Handle_t pSession,
                                                                      uint32_t byteLenN);


/**********************************************************/
/* FUP program declaration                                */
/**********************************************************/
//MCUXCLPKC_FUP_EXT_ROM_DECLARE(mcuxClEcc_Fup_RepeatDouble);
#define mcuxClEcc_Fup_RepeatDouble_Len1  5u
#define mcuxClEcc_Fup_RepeatDouble_Len2  16u
#define mcuxClEcc_Fup_RepeatDouble_Len3  3u
#define mcuxClEcc_Fup_RepeatDouble_Len   24u

#define MCUXCLECC_CALCFUP_ONE_DOUBLE()  \
    mcuxClPkc_CalcFup(mcuxClEcc_Fup_RepeatDouble,  \
                     mcuxClEcc_Fup_RepeatDouble_Len1  \
                     + mcuxClEcc_Fup_RepeatDouble_Len2)
#define MCUXCLECC_FP_CALCFUP_ONE_DOUBLE()  \
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_RepeatDouble,  \
                        mcuxClEcc_Fup_RepeatDouble_Len1  \
                        + mcuxClEcc_Fup_RepeatDouble_Len2)
#define MCUXCLECC_FP_CALLED_CALCFUP_ONE_DOUBLE  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)

//MCUXCLPKC_FUP_EXT_ROM_DECLARE(mcuxClEcc_Fup_DoubleAdd);
#define mcuxClEcc_Fup_DoubleAdd_Len1   5u
#define mcuxClEcc_Fup_DoubleAdd_Len2  15u
#define mcuxClEcc_Fup_DoubleAdd_Len   20u

#define MCUXCLECC_CALCFUP_ADD_ONLY()  \
    mcuxClPkc_CalcFup(mcuxClEcc_Fup_DoubleAdd, mcuxClEcc_Fup_DoubleAdd_Len)
#define MCUXCLECC_FP_CALCFUP_ADD_ONLY()  \
    MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_DoubleAdd, mcuxClEcc_Fup_DoubleAdd_Len)
#define MCUXCLECC_FP_CALLED_CALCFUP_ADD_ONLY  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)

#define MCUXCLECC_CALCFUP_DOUBLE_ADD()  \
    do{  \
        mcuxClPkc_CalcFup(mcuxClEcc_Fup_DoubleAdd, mcuxClEcc_Fup_DoubleAdd_Len);  \
        mcuxClPkc_CalcFup(mcuxClEcc_Fup_DoubleAdd + (mcuxClEcc_Fup_DoubleAdd_Len1 * 3u),  \
                         mcuxClEcc_Fup_DoubleAdd_Len2);  \
    } while (false)
#define MCUXCLECC_FP_CALCFUP_DOUBLE_ADD()  \
    do{  \
        MCUXCLPKC_FP_CALCFUP(mcuxClEcc_Fup_DoubleAdd, mcuxClEcc_Fup_DoubleAdd_Len);  \
        MCUXCLPKC_FP_CALCFUP_OFFSET(mcuxClEcc_Fup_DoubleAdd, mcuxClEcc_Fup_DoubleAdd_Len1,  \
                                   mcuxClEcc_Fup_DoubleAdd_Len2);  \
    } while (false)
#define MCUXCLECC_FP_CALLED_CALCFUP_DOUBLE_ADD  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup),  \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup)

/* mcuxClEcc_Internal_KeyGen.fup.c */
//MCUXCLPKC_FUP_EXT_ROM_DECLARE(mcuxClEcc_Int_CoreKeyGen_Steps34);
//MCUXCLPKC_FUP_EXT_ROM_DECLARE(mcuxClEcc_Int_CoreKeyGen_Steps56);
//MCUXCLPKC_FUP_EXT_ROM_DECLARE(mcuxClEcc_Int_CoreKeyGen_Steps78);
#define mcuxClEcc_Int_CoreKeyGen_Steps34_LEN   6u
#define mcuxClEcc_Int_CoreKeyGen_Steps56_LEN   8u
#define mcuxClEcc_Int_CoreKeyGen_Steps78_LEN  11u

/* mcuxClEcc_KeyGen.fup.c */
//MCUXCLPKC_FUP_EXT_ROM_DECLARE(mcuxClEcc_KeyGen_Convert_PubKey);
#define mcuxClEcc_KeyGen_Convert_PubKey_LEN  11u

/* mcuxClEcc_Sign.fup.c */
//MCUXCLPKC_FUP_EXT_ROM_DECLARE(mcuxClEcc_Sign_CalculateS);
#define mcuxClEcc_Sign_CalculateS_LEN  13u

/* mcuxClEcc_PointMult.fup.c */
//MCUXCLPKC_FUP_EXT_ROM_DECLARE(mcuxClEcc_PointMult_SplitScalar_ConvertPoint2MR);
#define mcuxClEcc_PointMult_SplitScalar_ConvertPoint2MR_LEN  10u

//MCUXCLPKC_FUP_EXT_ROM_DECLARE(mcuxClEcc_Fup_PointCheckAffNR);
#define mcuxClEcc_Fup_PointCheckAffNR_LEN  10u  

//MCUXCLPKC_FUP_EXT_ROM_DECLARE(mcuxClEcc_Fup_CoZPointAddSub);
//MCUXCLPKC_FUP_EXT_ROM_DECLARE(mcuxClEcc_Fup_SecurePointMult_PrepareZA_UpdateZ_P0_P1);

#define mcuxClEcc_Fup_CoZPointAddSub_LEN1  16u
#define mcuxClEcc_Fup_CoZPointAddSub_LEN2   7u
#define mcuxClEcc_Fup_CoZPointAddSub_LEN  \
    (mcuxClEcc_Fup_CoZPointAddSub_LEN1 + mcuxClEcc_Fup_CoZPointAddSub_LEN2)


#define mcuxClEcc_Fup_SecurePointMult_PrepareZA_UpdateZ_P0_P1_LEN1  4u
#define mcuxClEcc_Fup_SecurePointMult_PrepareZA_UpdateZ_P0_P1_LEN2  9u
#define mcuxClEcc_Fup_SecurePointMult_PrepareZA_UpdateZ_P0_P1_LEN3  5u
#define mcuxClEcc_Fup_SecurePointMult_PrepareZA_UpdateZ_P0_P1_LEN  \
    (  mcuxClEcc_Fup_SecurePointMult_PrepareZA_UpdateZ_P0_P1_LEN1  \
     + mcuxClEcc_Fup_SecurePointMult_PrepareZA_UpdateZ_P0_P1_LEN2  \
     + mcuxClEcc_Fup_SecurePointMult_PrepareZA_UpdateZ_P0_P1_LEN3 )  

//MCUXCLPKC_FUP_EXT_ROM_DECLARE(mcuxClEcc_Fup_Interleave);
#define mcuxClEcc_Fup_Interleave_LEN  7u 


#endif /* MCUXCLECC_INTERNAL_H_ */
