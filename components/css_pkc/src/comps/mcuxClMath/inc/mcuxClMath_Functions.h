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

/**
 * @file  mcuxClMath_Functions.h
 * @brief APIs of mcuxClMath component
 */


#ifndef MCUXCLMATH_FUNCTIONS_H_
#define MCUXCLMATH_FUNCTIONS_H_


#include <stdint.h>
#include <stdbool.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClPkc.h>
#include <mcuxClMath_Types.h>


/**
 * @defgroup mcuxClMath_Functions mcuxClMath_Functions
 * @brief Defines all functions of @ref mcuxClMath
 * @ingroup mcuxClMath
 * @{
 */


/** Initializes the new UPTRT and returns the address of existing UPTRT.
 * This function copies up to 8 offsets of PKC operands from existing UPTRT to the new UPTRT,
 * sets PKC to be with the new UPTRT, and returns the address of original UPTRT.
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_InitLocalUptrt)
mcuxClMath_Status_Protected_t mcuxClMath_InitLocalUptrt(
    uint32_t i3_i2_i1_i0,        ///< [in] the first 4 indices of offsets to be copied.
    uint32_t i7_i6_i5_i4,        ///< [in] the second 4 indices of offsets to be copied.
    uint16_t *localPtrUptrt,     ///< [out] pointer to the new UPTRT to be filled.
    uint8_t noOfIndices,         ///< [in] number of offsets to be copied from existing UPTRT to new UPTRT.
    const uint16_t **oldPtrUptrt ///< [out] pointer which receives the pointer to the old UPTRT.
    );
/** Helper macro to call #mcuxClMath_InitLocalUptrt with flow protection. */
#define MCUXCLMATH_FP_INITLOCALUPTRT(i3_i2_i1_i0, i7_i6_i5_i4, localPtrUptrt, noOfIndices)  \
    ({ \
        const uint16_t *oldPtrUptrt_;  \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClMath_InitLocalUptrt(i3_i2_i1_i0, i7_i6_i5_i4, localPtrUptrt, noOfIndices, &oldPtrUptrt_));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
        (oldPtrUptrt_);  \
    })

/** Counts number of leading zeros of operand in the given buffer (length = ps1 OPLEN).
 * @attention The offset (UPTRT[iX]) must be initialized properly (equal to a multiple of PKC wordsize).
 * @attention The length (ps1 OPLEN) must be initialized properly (equal to a multiple of PKC wordsize).
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_LeadingZeros)
mcuxClMath_Status_Protected_t mcuxClMath_LeadingZeros(
    uint8_t iX,              ///< [in] index of operand buffer.
    uint32_t *nLeadingZeros  ///< [out] the number of leading zero bits.
    );
/** Helper macro to call #mcuxClMath_LeadingZeros with flow protection. */
#define MCUXCLMATH_FP_LEADINGZEROS(iX)  \
    ({ \
        uint32_t nLeadingZeros_;  \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClMath_LeadingZeros(iX, &nLeadingZeros_));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
        (nLeadingZeros_);  \
    })

/** Counts number of trailing zeros of operand in the given buffer (length = ps1 OPLEN).
 * @attention The offset (UPTRT[iX]) must be initialized properly (equal to a multiple of PKC wordsize).
 * @attention The length (ps1 OPLEN) must be initialized properly (equal to a multiple of PKC wordsize).
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_TrailingZeros)
mcuxClMath_Status_Protected_t mcuxClMath_TrailingZeros(
    uint8_t iX,               ///< [in] index of operand buffer.
    uint32_t *nTrailingZeros  ///< [out] the number of trailing zero bits.
    );
/** Helper macro to call #mcuxClMath_TrailingZeros with flow protection. */
#define MCUXCLMATH_FP_TRAILINGZEROS(iX)  \
    ({ \
        uint32_t nTrailingZeros_;  \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClMath_TrailingZeros(iX, &nTrailingZeros_));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
        (nTrailingZeros_);  \
    })

/** Left shifts modulus until most significant bit of the buffer (length = ps1 OPLEN) is 1,
 * and stores the result in the buffer specified.
 * @attention The modulus must be non-zero.
 * @attention The offset (UPTRT[iN]) must be initialized properly (equal to a multiple of PKC wordsize).
 * @attention The length (ps1 OPLEN) must be initialized properly (equal to a multiple of PKC wordsize).
 * @attention The PKC calculation might be still on-going, call #mcuxClPkc_WaitForFinish before CPU accesses to the result.
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_ShiftModulus)
mcuxClMath_Status_Protected_t mcuxClMath_ShiftModulus(
    uint16_t iNShifted_iN  ///< [in] iNShifted: index of buffer in which the result will be stored.
                           ///< <br> iN: index of modulus buffer.
    );
/** Helper macro for #mcuxClMath_ShiftModulus. */
#define MCUXCLMATH_SHIFTMODULUS(iNShifted, iN)  \
    mcuxClMath_ShiftModulus(MCUXCLPKC_PACKARGS2(iNShifted, iN))
/** Helper macro for #mcuxClMath_ShiftModulus with flow protection. */
#define MCUXCLMATH_FP_SHIFTMODULUS(iNShifted, iN)  \
    do {  \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, MCUXCLMATH_SHIFTMODULUS(iNShifted, iN));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while(false)

/** Prepares modulus buffer (initializes NDash) to be used in modular multiplication (inversion, ...) with odd modulus.
 * This function calculates NDash = (-n)^(-1) mod 256^("PKC wordsize"), and stores the result in the PKC word in front of the modulus (n) buffer.
 * @attention The modulus must be an odd number.
 * @attention The offset (UPTRT[iN]) must be initialized properly (equal to a multiple of PKC wordsize).
 * @attention The PKC calculation might be still on-going, call #mcuxClPkc_WaitForFinish before CPU accesses to the result.
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_NDash)
mcuxClMath_Status_Protected_t mcuxClMath_NDash(
    uint16_t iN_iT  ///< [in] iN: index of modulus buffer. The result (NDash) will be stored in the PKC word in front of the modulus buffer.
                    ///< <br> iT: index of temp buffer, of which the size should be at least 2 PKC words.
    );
/** Helper macro for #mcuxClMath_NDash. */
#define MCUXCLMATH_NDASH(iN, iT)  \
    mcuxClMath_NDash(MCUXCLPKC_PACKARGS2(iN, iT))
/** Helper macro for #mcuxClMath_NDash with flow protection. */
#define MCUXCLMATH_FP_NDASH(iN, iT)  \
    do {  \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, MCUXCLMATH_NDASH(iN, iT));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while(false)

/** Calculates Q * Q' mod n, where Q = 256^(ps1 OPLEN) mod n, and Q' = 256^len mod n.
 * @attention Both ps1 (OP)LEN and MCLEN need to be initialized (MCLEN = OPLEN = operandSize).
 * @attention The PKC calculation might be still on-going, call #mcuxClPkc_WaitForFinish before CPU accesses to the result.
 * <br> The result might be greater than the modulus.
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_QDash)
mcuxClMath_Status_Protected_t mcuxClMath_QDash(
    uint32_t iQDash_iNShifted_iN_iT,  ///< [in] iQDash: index of QDash buffer, in which the result will be stored.
                                      ///< <br> iNShifted: index of shifted modulus. If the bit length of modulus is equal to the operand size (i.e., most significant bit is 1), it can be the same as iN.
                                      ///< <br> iN: index of modulus buffer. NDash of the modulus should be store in front of it.
                                      ///< <br> iT: index of temp buffer, of which the size should be at least operandSize + PKC wordsize.
    uint16_t len                      ///< [in] specify Q' = 256^len mod n.
    );
/** Helper macro for #mcuxClMath_QDash. */
#define MCUXCLMATH_QDASH(iQDash, iNShifted, iN, iT, len)  \
    mcuxClMath_QDash(MCUXCLPKC_PACKARGS4(iQDash, iNShifted, iN, iT), len)
/** Helper macro for #mcuxClMath_QDash with flow protection. */
#define MCUXCLMATH_FP_QDASH(iQDash, iNShifted, iN, iT, len)  \
    do {  \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, MCUXCLMATH_QDASH(iQDash, iNShifted, iN, iT, len));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while(false)

/** Calculates Q^2 mod n, where Q = 256^(ps1 OPLEN) mod n.
 * @attention Both ps1 (OP)LEN and MCLEN need to be initialized (MCLEN = OPLEN = operandSize).
 * @attention The length (ps1 OPLEN) must be initialized properly (equal to a multiple of PKC wordsize).
 * @attention The PKC calculation might be still on-going, call #mcuxClPkc_WaitForFinish before CPU accesses to the result.
 * <br> The result might be greater than the modulus.
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_QSquared)
mcuxClMath_Status_Protected_t mcuxClMath_QSquared(
    uint32_t iQSqr_iNShifted_iN_iT  ///< [in] iQSqr: index of QSqr buffer, in which the result will be stored.
                                    ///< <br> iNShifted: index of shifted modulus. If the bit length of modulus is equal to the operand size (i.e., most significant bit is 1), it can be the same as iN.
                                    ///< <br> iN: index of modulus buffer. NDash of the modulus should be store in front of it.
                                    ///< <br> iT: index of temp buffer, of which the size should be at least operandSize + PKC wordsize.
    );
/** Helper macro for #mcuxClMath_QSquared. */
#define MCUXCLMATH_QSQUARED(iQSqr, iNShifted, iN, iT)  \
    mcuxClMath_QSquared(MCUXCLPKC_PACKARGS4(iQSqr, iNShifted, iN, iT))
/** Helper macro for #mcuxClMath_QSquared with flow protection. */
#define MCUXCLMATH_FP_QSQUARED(iQSqr, iNShifted, iN, iT)  \
    do {  \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, MCUXCLMATH_QSQUARED(iQSqr, iNShifted, iN, iT));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while(false)

/** Calculates modular inversion, X^(-1) mod n.
 * @attention Both ps1 (OP)LEN and MCLEN need to be initialized (MCLEN = OPLEN = operandSize).
 * @attention The offsets (UPTRT[iR] and UPTRT[iT]) must be initialized properly (equal to a multiple of PKC wordsize).
 * @attention if X and n are not coprime, the result will be incorrect, and the modulus n will be destroyed.
 * @attention The PKC calculation might be still on-going, call #mcuxClPkc_WaitForFinish before CPU accesses to the result.
 * <br> The result fits in operandSize but might be greater than the modulus.
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_ModInv)
mcuxClMath_Status_Protected_t mcuxClMath_ModInv(
    uint32_t iR_iX_iN_iT  ///< [in] iR: index of result buffer, of which the size should be at least operandSize + PKC wordsize.
                          ///< <br> iX: index of X buffer, of which the content (X) will be destroyed.
                          ///< <br> iN: index of modulus buffer. NDash of the modulus should be store in front of it.
                          ///< <br> iT: index of temp buffer, of which the size should be at least operandSize + PKC wordsize.
    );
/** Helper macro for #mcuxClMath_ModInv. */
#define MCUXCLMATH_MODINV(iR, iX, iN, iT)  \
    mcuxClMath_ModInv(MCUXCLPKC_PACKARGS4(iR, iX, iN, iT))
/** Helper macro for #mcuxClMath_ModInv with flow protection. */
#define MCUXCLMATH_FP_MODINV(iR, iX, iN, iT)  \
    do {  \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, MCUXCLMATH_MODINV(iR, iX, iN, iT));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while(false)

/** Calculates modular reduction with even modulus, x mod n, where n is even.
 * @attention Both ps1 (OP)LEN and MCLEN need to be initialized (MCLEN = lenX = length of x, OPLEN = lenN = length of n).
 * @attention The lengths (ps1 OPLEN and MCLEN) must be initialized properly (equal to a multiple of PKC wordsize).
 * @attention The offset (UPTRT[iN]) must be initialized properly (equal to a multiple of PKC wordsize).
 * @attention The PKC calculation might be still on-going, call #mcuxClPkc_WaitForFinish before CPU accesses to the result.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_ReduceModEven)
mcuxClMath_Status_Protected_t mcuxClMath_ReduceModEven(
    uint32_t iR_iX_iN_iT0,  ///< [in] (bits 31~24) iR: index of result buffer, of which the size shall be at least (lenN + PKC wordsize).
                            ///< <br> (bits 23~16) iX: index of input buffer, of which the size shall be at least (lenX + PKC wordsize).
                            ///< <br> (bits 15~8)  iN: index of modulus buffer, of which the size is lenN.
                            ///< <br> (bits 7~0)   iT0: index of temp buffer, of which the size shall be at least (lenN + PKC wordsize). Buffer N can be used as T0.
    uint32_t iT1_iT2_iT3    ///< [in] (bits 23~16) iT1: index of temp buffer, of which the size shall be at least lenN. Buffer R can be used as T1.  TODO: use R (any reason not using R?)
                            ///< <br> (bits 15~8)  iT2: index of temp buffer, of which the size shall be at least lenN.
                            ///< <br> (bits 7~0)   iT3: index of temp buffer, of which the size shall be at least (lenN + PKC wordsize).
    );
/** Helper macro for #mcuxClMath_ReduceModEven. */
#define MCUXCLMATH_REDUCEMODEVEN(iR, iX, iN, iT0, iT1, iT2, iT3)  \
    mcuxClMath_ReduceModEven(MCUXCLPKC_PACKARGS4(iR, iX, iN, iT0), MCUXCLPKC_PACKARGS4(0u, iT1, iT2, iT3))
/** Helper macro for #mcuxClMath_ReduceModEven with flow protection. */
#define MCUXCLMATH_FP_REDUCEMODEVEN(iR, iX, iN, iT0, iT1, iT2, iT3)  \
    do {  \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, MCUXCLMATH_REDUCEMODEVEN(iR, iX, iN, iT0, iT1, iT2, iT3));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while(false)

/**
 * @brief Calculates modular exponentiation with left-to-right binary square and multiply algorithm.
 *
 * @param[in] pExp        pointer to exponent, which is stored as a big-endian octet string.
 * @param[in] byteLenExp  byte length of exponent.
 * @param[in] iR_iX_iN_iT indices of operands in PKC workarea.
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p pExp </dt>
 *       <dd>the exponent is a big-endian octet string and must be non-zero.</dd>
 *     <dt>@p iR_iX_iN_iT </dt>
 *       <dd> iR (bits 31~24): index of result. The size shall be at least (lenN + PKC wordsize).
 *       <br> iX (bits 23~16): index of base number.
 *       <br> iN (bits 15~8): index of modulus. NDash of the modulus should be stored in front of it.
 *       <br> iT (bits 7~0): index of temp operand. The size shall be at least (lenN + PKC wordsize). </dd>
 *   </dl></dd>
 * </dl>
 *
 * @attention Both ps1 (OP)LEN and MCLEN need to be initialized (OPLEN = MCLEN = lenX (= length of x) = lenN (= length of n)).
 * @attention The PKC calculation might be still on-going, call #mcuxClPkc_WaitForFinish before CPU accesses to the result.
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_ModExp_SqrMultL2R)
mcuxClMath_Status_Protected_t mcuxClMath_ModExp_SqrMultL2R(
    const uint8_t *pExp,
    uint32_t byteLenExp,
    uint32_t iR_iX_iN_iT
    );
/** Helper macro for #mcuxClMath_ModExp_SqrMultL2R. */
#define MCUXCLMATH_MODEXP_SQRMULTL2R(pExp, byteLenExp, iR, iX, iN, iT)  \
    mcuxClMath_ModExp_SqrMultL2R(pExp, byteLenExp, MCUXCLPKC_PACKARGS4(iR, iX, iN, iT))
/** Helper macro for #mcuxClMath_ModExp_SqrMultL2R with flow protection. */
#define MCUXCLMATH_FP_MODEXP_SQRMULTL2R(pExp, byteLenExp, iR, iX, iN, iT)  \
    do {  \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, MCUXCLMATH_MODEXP_SQRMULTL2R(pExp, byteLenExp, iR, iX, iN, iT));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while(false)


/**
 * @brief Securely calculates modular exponentiation.
 *
 * @param[in] pExp           pointer to exponent, which is stored as a big-endian octet string.
 * @param[in] pExpTemp       pointer to temporary buffer, in either CPU or PKC workarea.
 * @param[in] byteLenExp     byte length of exponent.
 * @param[in] iT3_iX_iT2_iT1 indices of operands in PKC workarea.
 * @param[in] iN_iTE_iT0_iR  indices of operands in PKC workarea.
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p pExp </dt>
 *       <dd>the exponent is a big-endian octet string and must be non-zero.</dd>
 *     <dt>@p pExpTemp </dt>
 *       <dd>the temporary buffer shall be aligned to CPU word, and it's length shall be a multiple of CPU word and greater than @p byteLenExp. </dd>
 *     <dt>@p iT3_iX_iT2_iT1 </dt>
 *       <dd> iT3 (bits 31~24): index of temp3. The size shall be a multiple of PKC word and at least max(lenN, 2 * PKC wordsize).
 *       <br> iX  (bits 23~16): index of base number. The size shall be a multiple of PKC word and at least lenN.
 *       <br> iT2 (bits 15~8):  index of temp2. The size shall be a multiple of PKC word and at least max(lenN, 2 * PKC wordsize)
 *       <br> iT1 (bits 7~0):   index of temp1. The size shall be a multiple of PKC word and at least max(lenN, @p byteLenExp + 1, 2 * PKC wordsize). </dd>
 *     <dt>@p iN_iTE_iT0_iR </dt>
 *       <dd> iN  (bits 31~24): index of modulus. NDash of the modulus should be stored in front of it.
 *       <br> iTE (bits 23~16): index of temp4. The size shall be a multiple of PKC word and at least (5 * PKC wordsize).
 *       <br> iT0 (bits 15~8):  index of temp0. The size shall be a multiple of PKC word and at least max(@p byteLenExp + 1, lenN + PKC wordsize).
 *       <br> iR  (bits 7~0):   index of result. The size shall be a multiple of PKC word and at least max(@p byteLenExp + 1, lenN + PKC wordsize). </dd>
 *   </dl></dd>
 * </dl>
 *
 * @attention Both ps1 (OP)LEN and MCLEN need to be initialized (OPLEN = MCLEN = lenX (= length of x) = lenN (= length of n)).
 * @attention The lengths (ps1 OPLEN and MCLEN) must be initialized properly (equal to a multiple of PKC wordsize).
 * @attention The PKC calculation might be still on-going, call #mcuxClPkc_WaitForFinish before CPU accesses to the result.
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_SecModExp)
mcuxClMath_Status_Protected_t mcuxClMath_SecModExp(
    const uint8_t *pExp,
    uint32_t *pExpTemp,
    uint32_t byteLenExp,
    uint32_t iT3_iX_iT2_iT1,
    uint32_t iN_iTE_iT0_iR
    );
/** Helper macro for #mcuxClMath_SecModExp. */
#define MCUXCLMATH_SECMODEXP(pExp, pExpTemp, byteLenExp, iR, iX, iN, iTE, iT0, iT1, iT2, iT3)  \
    mcuxClMath_SecModExp(pExp, pExpTemp, byteLenExp, MCUXCLPKC_PACKARGS4(iT3, iX, iT2, iT1), MCUXCLPKC_PACKARGS4(iN, iTE, iT0, iR))
/** Helper macro for #mcuxClMath_SecModExp with flow protection. */
#define MCUXCLMATH_FP_SECMODEXP(pExp, pExpTemp, byteLenExp, iR, iX, iN, iTE, iT0, iT1, iT2, iT3)  \
    do {  \
        MCUX_CSSL_FP_FUNCTION_CALL(retVal, MCUXCLMATH_SECMODEXP(pExp, pExpTemp, byteLenExp, iR, iX, iN, iTE, iT0, iT1, iT2, iT3));  \
        if (MCUXCLMATH_ERRORCODE_OK != retVal)  \
        {  \
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClMath_SecModExp, MCUXCLMATH_ERRORCODE_ERROR);  \
        }  \
    } while(false)


/**
 * @brief TODO
 *  1.pkcByteLenX and pkcByteLenY shall be a multiple of pkc wordsize.
 *  2.the most significant PKC word of Y shall be nonzero.
 *  3.size of temp (iT) is 3 pkc wordsizes.
 *  4.if lenX = lenY = pkc wordsize, this function will access to one extra pkc word on top of X.
 *    (i.e., read/write to X[pkc word 0], read X[pkc word 1]).
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_ExactDivideOdd)
mcuxClMath_Status_Protected_t mcuxClMath_ExactDivideOdd(uint32_t iR_iX_iY_iT, uint32_t pkcByteLenX, uint32_t pkcByteLenY);
/** Helper macro for #mcuxClMath_ExactDivideOdd. */
#define MCUXCLMATH_EXACTDIVIDEODD(iR, iX, iN, iT, pkcByteLenX, pkcByteLenY)  \
    mcuxClMath_ExactDivideOdd(MCUXCLPKC_PACKARGS4(iR, iX, iN, iT), pkcByteLenX, pkcByteLenY)
/** Helper macro for #mcuxClMath_ExactDivideOdd with flow protection. */
#define MCUXCLMATH_FP_EXACTDIVIDEODD(iR, iX, iN, iT, pkcByteLenX, pkcByteLenY)  \
    do {  \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, MCUXCLMATH_EXACTDIVIDEODD(iR, iX, iN, iT, pkcByteLenX, pkcByteLenY));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while(false)


/*!
 * @brief Exact division
 *
 * This function computes the exact division r = x / y.
 *
 * This function relies on mcuxClMath_ExactDivideOdd to compute the exact division of x / y.
 * Suppose X is a multiple of Y, this function finds R such that (-X) + Y * R = 0.
 * If there is a remainder to this division, this function will fail.
 * The function destroys the content of buffer x. If this content is needed after the function
 * call, it has to be backed up by the caller of this function.
 *
 * @param iR_iX_iY_iT     Pointer table indices of parameters
 * @param pkcByteLenX     Bytelength of parameter X
 * @param pkcByteLenY     Bytelength of parameter Y
 *
 ** <dl>
 *  <dt>Parameter properties</dt>
 *
 *  <dd><dl>
 *      <dt>iR_iX_iY_iT:</dt>
 *          <dd>iR - index of result buffer r;  the caller has to reserve a buffer of size
 *                   bytelen(x) - bytelen(y) + 2 * MCUXCLPKC_WORDSIZE
 *              iX - index of input buffer x; the content of buffer x is modified during processing of mcuxClMath_ExactDivide;
 *                   if it is still needed after the function call, the buffer should be backed up
 *              iY - index of input buffer y; the most significant PKC word of Y shall be nonzero
 *              iT - index of temporary buffer; the size of the temporary buffer is 3 * pkc wordsize
 *      <dt>pkcByteLenX:</dt>
 *          <dd>Must be a multiple of the pkc wordsize. If pkcByteLenX = pkcByteLenY = pkc wordsize,
 *              this function accesses one extra pkc word on top of X.
 *      <dt>pkcByteLenY:</dt>
 *          <dd>Must be a multiple of the pkc wordsize.
 *  </dl></dd>
 * </dl>
 *
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 * @retval MCUXCLMATH_ERRORCODE_OK      Division successful
 * @retval MCUXCLMATH_ERRORCODE_ERROR   Error occured during divide operation
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_ExactDivide)
mcuxClMath_Status_Protected_t mcuxClMath_ExactDivide(uint32_t iR_iX_iY_iT, uint32_t pkcByteLenX, uint32_t pkcByteLenY);
/** Helper macro for #mcuxClMath_ExactDivide. */
#define MCUXCLMATH_EXACTDIVIDE(iR, iX, iN, iT, pkcByteLenX, pkcByteLenY)  \
    mcuxClMath_ExactDivide(MCUXCLPKC_PACKARGS4(iR, iX, iN, iT), pkcByteLenX, pkcByteLenY)
/** Helper macro for #mcuxClMath_ExactDivide with flow protection. */
#define MCUXCLMATH_FP_EXACTDIVIDE(iR, iX, iN, iT, pkcByteLenX, pkcByteLenY)  \
    do {  \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, MCUXCLMATH_EXACTDIVIDE(iR, iX, iN, iT, pkcByteLenX, pkcByteLenY));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while(false)


/**
 * @}
 */ /* mcuxClMath_Functions */


#endif /* MCUXCLMATH_FUNCTIONS_H_ */
