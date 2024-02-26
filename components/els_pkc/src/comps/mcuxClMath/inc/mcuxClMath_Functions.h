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
 * @file  mcuxClMath_Functions.h
 * @brief APIs of mcuxClMath component
 */


#ifndef MCUXCLMATH_FUNCTIONS_H_
#define MCUXCLMATH_FUNCTIONS_H_


#include <mcuxClCore_Platform.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClPkc.h>
#include <mcuxClSession.h>

#include <mcuxClMath_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup mcuxClMath_Functions mcuxClMath_Functions
 * @brief Defines all functions of @ref mcuxClMath
 * @ingroup mcuxClMath
 * @{
 */


/**
 * @brief Initializes and uses the new UPTRT and returns the address of original UPTRT.
 *
 * This function copies up to 8 offsets of PKC operands from current UPTRT to the new UPTRT,
 * sets PKC to use the new UPTRT, and returns the address of original UPTRT.
 *
 * @param[in]     i3_i2_i1_i0    the first 4 indices of offsets to be copied
 * @param[in]     i7_i6_i5_i4    the second 4 indices of offsets to be copied
 * @param[in,out] localPtrUptrt  address of the new UPTRT to be filled
 * @param[in]     noOfIndices    number of offsets to be copied from original UPTRT to new UPTRT
 * @param[out]    oldPtrUptrt    pointer to where receives the original UPTRT address
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p i3_i2_i1_i0</dt>
 *       <dd><code>i0</code> (bits 0~7):   originalUptrt[i0] will be copied to @p localPtrUptrt[0], if @p noOfIndices >= 1.
 *       <br><code>i1</code> (bits 8~15):  originalUptrt[i1] will be copied to @p localPtrUptrt[1], if @p noOfIndices >= 2.
 *       <br><code>i2</code> (bits 16~23): originalUptrt[i2] will be copied to @p localPtrUptrt[2], if @p noOfIndices >= 3.
 *       <br><code>i3</code> (bits 24~31): originalUptrt[i3] will be copied to @p localPtrUptrt[3], if @p noOfIndices >= 4.</dd>
 *     <dt>@p i7_i6_i5_i4</dt>
 *       <dd><code>i4</code> (bits 0~7):   originalUptrt[i4] will be copied to @p localPtrUptrt[4], if @p noOfIndices >= 5.
 *       <br><code>i5</code> (bits 8~15):  originalUptrt[i5] will be copied to @p localPtrUptrt[5], if @p noOfIndices >= 6.
 *       <br><code>i6</code> (bits 16~23): originalUptrt[i6] will be copied to @p localPtrUptrt[6], if @p noOfIndices >= 7.
 *       <br><code>i7</code> (bits 24~31): originalUptrt[i7] will be copied to @p localPtrUptrt[7], if @p noOfIndices >= 8.</dd>
 *     <dt>@p localPtrUptrt</dt>
 *       <dd>This address shall be 2-byte aligned.
 *       <br>Caller shall allocate at least @p noOfIndices 2-byte entries in this table.</dd>
 *   </dl></dd>
 * </dl>
 *
 * <dl>
 *   <dt>PKC properties</dt>
 *   <dd><dl>
 *     <dt>UPTRT</dt>
 *       <dd>This function will retrieve the original UPTRT address and return it to caller via @p oldPtrUptrt.
 *       <br>This function will overwrite this address by @p localPtrUptrt.</dd>
 *     <dt>PS1 lengths</dt>
 *       <dd>Unused.</dd>
 *     <dt>PS2 lengths</dt>
 *       <dd>Unused.</dd>
 *     <dt>ACTIV/GOANY</dt>
 *       <dd>This function shall not be called during a running FUP program (i.e., GOANY bit is set).
 *           Caller shall call #mcuxClPkc_WaitForReady before calling this function, if a FUP program has been called.</dd>
 *   </dl></dd>
 * </dl>
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_InitLocalUptrt)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClMath_InitLocalUptrt(
    uint32_t i3_i2_i1_i0,
    uint32_t i7_i6_i5_i4,
    uint16_t *localPtrUptrt,
    uint8_t noOfIndices,
    const uint16_t **oldPtrUptrt
    );


/**
 * @brief Counts number of leading zero bits of a PKC operand.
 *
 * This function counts the number of leading zero bits of a PKC operand
 * at offset UPTRT[iX] and of size PS1 OPLEN.
 *
 * @param[in]  iX                index of PKC operand
 * @param[out] pNumLeadingZeros  pointer to where the number of leading zero bits will be stored
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p iX</dt>
 *       <dd>index of X (PKC operand), size = operandSize.
 *       <br>The offset (UPTRT[iX]) shall be exactly a multiple of MCUXCLPKC_WORDSIZE.</dd>
 *   </dl></dd>
 * </dl>
 *
 * <dl>
 *   <dt>PKC properties</dt>
 *   <dd><dl>
 *     <dt>PS1 lengths</dt>
 *       <dd>PS1 OPLEN defines operandSize and shall be exactly a multiple of MCUXCLPKC_WORDSIZE.</dd>
 *     <dt>PS2 lengths</dt>
 *       <dd>Unused.</dd>
 *     <dt>ACTIV/GOANY</dt>
 *       <dd>This function will not use PKC, and assumes PKC will not modify the operand iX simultaneously.</dd>
 *   </dl></dd>
 * </dl>
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_LeadingZeros)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClMath_LeadingZeros(
    uint8_t iX,
    uint32_t *pNumLeadingZeros
    );


/**
 * @brief Counts number of trailing zero bits of a PKC operand.
 *
 * This function counts the number of trailing zero bits of a PKC operand
 * at offset UPTRT[iX] and of size PS1 OPLEN.
 *
 * @param[in]  iX                 index of PKC operand
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p iX</dt>
 *       <dd>index of X (PKC operand), size = operandSize.
 *       <br>The offset (UPTRT[iX]) shall be exactly a multiple of MCUXCLPKC_WORDSIZE.</dd>
 *   </dl></dd>
 * </dl>
 *
 * <dl>
 *   <dt>PKC properties</dt>
 *   <dd><dl>
 *     <dt>PS1 lengths</dt>
 *       <dd>PS1 OPLEN defines operandSize and shall be exactly a multiple of MCUXCLPKC_WORDSIZE.</dd>
 *     <dt>PS2 lengths</dt>
 *       <dd>Unused.</dd>
 *     <dt>ACTIV/GOANY</dt>
 *       <dd>This function will not use PKC, and assumes PKC will not modify the operand iX simultaneously.</dd>
 *   </dl></dd>
 * </dl>
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 * @retval #numTrailingZeroes    Number of trailing zeroes
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_TrailingZeros)
MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) mcuxClMath_TrailingZeros(
    uint8_t iX
    );


/**
 * @brief Prepares shifted modulus
 *
 * This function left shifts modulus (PKC operand iN) until there is no leading zero
 * and stores the result in PKC operand iNShifted.
 *
 * @param[in] iNShifted_iN  indices of PKC operands
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p iNShifted_iN</dt>
 *       <dd><code>iN</code> (bits 0~7): index of modulus (PKC operand), size = operandSize.
 *       <br>The modulus shall be non-zero.
 *       <br>The offset (UPTRT[iN]) shall be exactly a multiple of MCUXCLPKC_WORDSIZE.
 *       <br><code>iNShifted</code> (bits 8~15): index of shifted modulus (PKC operand), size = operandSize.
 *       <br>This function supports in-place operation, i.e., iNShifted = iN.</dd>
 *   </dl></dd>
 * </dl>
 *
 * <dl>
 *   <dt>PKC properties</dt>
 *   <dd><dl>
 *     <dt>PS1 lengths</dt>
 *       <dd>PS1 OPLEN defines operandSize and shall be exactly a multiple of MCUXCLPKC_WORDSIZE.</dd>
 *     <dt>PS2 lengths</dt>
 *       <dd>PS2 OPLEN and MCLEN will be modified, and original values will not be restored.</dd>
 *     <dt>ACTIV/GOANY</dt>
 *       <dd>The PKC calculation might be still on-going,
 *           call #mcuxClPkc_WaitForFinish before CPU accesses to the result.</dd>
 *   </dl></dd>
 * </dl>
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_ShiftModulus)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClMath_ShiftModulus(
    uint16_t iNShifted_iN
    );
/** Helper macro for #mcuxClMath_ShiftModulus. */
#define MCUXCLMATH_SHIFTMODULUS(iNShifted, iN)  \
    mcuxClMath_ShiftModulus(MCUXCLPKC_PACKARGS2(iNShifted, iN))
/** Helper macro for #mcuxClMath_ShiftModulus with flow protection. */
#define MCUXCLMATH_FP_SHIFTMODULUS(iNShifted, iN)  \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(MCUXCLMATH_SHIFTMODULUS(iNShifted, iN))


/**
 * @brief Prepares modulus (calculates NDash) for PKC modular multiplication.
 *
 * This function calculates NDash = (-modulus)^(-1) mod 256^(MCUXCLPKC_WORDSIZE)
 * and stores NDash in the PKC word in front of the PKC operand of modulus (iN).
 *
 * @param[in] iN_iT  indices of PKC operands
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p iN_iT</dt>
 *       <dd><code>iT</code> (bits 0~7): index of temp (PKC operand).
 *       <br>The size of temp shall be at least (2 * MCUXCLPKC_WORDSIZE).
 *       <br><code>iN</code> (bits 8~15): index of modulus (PKC operand).
 *       <br>The modulus shall be an odd number.
 *       <br>The result NDash will be stored in the PKC word before modulus,
 *           i.e., at the offset, (UPTRT[iN] - MCUXCLPKC_WORDSIZE).</dd>
 *   </dl></dd>
 * </dl>
 *
 * <dl>
 *   <dt>PKC properties</dt>
 *   <dd><dl>
 *     <dt>PS1 lengths</dt>
 *       <dd>Unused.</dd>
 *     <dt>PS2 lengths</dt>
 *       <dd>PS2 OPLEN and MCLEN will be modified, and original values will not be restored.</dd>
 *     <dt>ACTIV/GOANY</dt>
 *       <dd>#mcuxClPkc_WaitForReady will be called before returning to caller.
 *       <br>The PKC calculation might be still on-going,
 *           call #mcuxClPkc_WaitForFinish before CPU accesses to the result.</dd>
 *   </dl></dd>
 * </dl>
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_NDash)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClMath_NDash(
    uint16_t iN_iT
    );
/** Helper macro for #mcuxClMath_NDash. */
#define MCUXCLMATH_NDASH(iN, iT)  \
    mcuxClMath_NDash(MCUXCLPKC_PACKARGS2(iN, iT))
/** Helper macro for #mcuxClMath_NDash with flow protection. */
#define MCUXCLMATH_FP_NDASH(iN, iT)  \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(MCUXCLMATH_NDASH(iN, iT))


/**
 * @brief Calculates QDash = Q * Q' mod n, where Q = 256^(operandSize) mod n, and Q' = 256^length mod n.
 *
 * This function computes QDash which can be used to convert a PKC operand
 * (of the size @p length) to its Montgomery representation (of the size operandSize).
 *
 * @param[in] iQDash_iNShifted_iN_iT  indices of PKC operands
 * @param[in] length                  specify Q' = 256^length mod n
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p iQDash_iNShifted_iN_iT</dt>
 *       <dd><code>iT</code> (bits 0~7): index of temp (PKC operand).
 *       <br>The size of temp shall be at least (operandSize + MCUXCLPKC_WORDSIZE).
 *       <br><code>iN</code> (bits 8~15): index of modulus (PKC operand), size = operandSize.
 *       <br>NDash of modulus shall be stored in the PKC word before modulus.
 *       <br><code>iNShifted</code> (bits 16~23): index of shifted modulus (PKC operand), size = operandSize.
 *       <br>If there is no leading zero in the PKC operand modulus, it can be iN.
 *       <br><code>iQDash</code> (bits 24~31): index of result QDash (PKC operand), size = operandSize.
 *       <br>QDash might be greater than modulus.</dd>
 *     <dt>@p length</dt>
 *       <dd>It shall be nonzero. A zero length will cause undefined behavior.</dd>
 *   </dl></dd>
 * </dl>
 *
 * <dl>
 *   <dt>PKC properties</dt>
 *   <dd><dl>
 *     <dt>PS1 lengths</dt>
 *       <dd>PS1 OPLEN = MCLEN defines operandSize.</dd>
 *     <dt>PS2 lengths</dt>
 *       <dd>Unused.</dd>
 *     <dt>ACTIV/GOANY</dt>
 *       <dd>#mcuxClPkc_WaitForReady will be called before returning to caller.
 *       <br>The PKC calculation might be still on-going,
 *           call #mcuxClPkc_WaitForFinish before CPU accesses to the result.</dd>
 *   </dl></dd>
 * </dl>
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_QDash)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClMath_QDash(
    uint32_t iQDash_iNShifted_iN_iT,
    uint16_t length
    );
/** Helper macro for #mcuxClMath_QDash. */
#define MCUXCLMATH_QDASH(iQDash, iNShifted, iN, iT, len)  \
    mcuxClMath_QDash(MCUXCLPKC_PACKARGS4(iQDash, iNShifted, iN, iT), len)
/** Helper macro for #mcuxClMath_QDash with flow protection. */
#define MCUXCLMATH_FP_QDASH(iQDash, iNShifted, iN, iT, len)  \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(MCUXCLMATH_QDASH(iQDash, iNShifted, iN, iT, len))


/**
 * @brief Calculates QSquared = Q^2 mod n, where Q = 256^(operandSize) mod n.
 *
 * This function computes QSquared which can be used to convert a PKC operand
 * to its Montgomery representation (both are of the size operandSize).
 *
 * @param[in] iQSqr_iNShifted_iN_iT  indices of PKC operands
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p iQSqr_iNShifted_iN_iT</dt>
 *       <dd><code>iT</code> (bits 0~7): index of temp (PKC operand).
 *       <br>The size of temp shall be at least (operandSize + MCUXCLPKC_WORDSIZE).
 *       <br><code>iN</code> (bits 8~15): index of modulus (PKC operand), size = operandSize.
 *       <br>NDash of modulus shall be stored in the PKC word before modulus.
 *       <br><code>iNShifted</code> (bits 16~23): index of shifted modulus (PKC operand), size = operandSize.
 *       <br>If there is no leading zero in the PKC operand modulus, it can be iN.
 *       <br><code>iQSqr</code> (bits 24~31): index of result QSquared (PKC operand), size = operandSize.
 *       <br>QSquared might be greater than modulus.</dd>
 *   </dl></dd>
 * </dl>
 *
 * <dl>
 *   <dt>PKC properties</dt>
 *   <dd><dl>
 *     <dt>PS1 lengths</dt>
 *       <dd>PS1 OPLEN = MCLEN defines operandSize and shall be exactly a multiple of MCUXCLPKC_WORDSIZE.</dd>
 *     <dt>PS2 lengths</dt>
 *       <dd>Unused.</dd>
 *     <dt>ACTIV/GOANY</dt>
 *       <dd>#mcuxClPkc_WaitForReady will be called before returning to caller.
 *       <br>The PKC calculation might be still on-going,
 *           call #mcuxClPkc_WaitForFinish before CPU accesses to the result.</dd>
 *   </dl></dd>
 * </dl>
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_QSquared)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClMath_QSquared(
    uint32_t iQSqr_iNShifted_iN_iT
    );
/** Helper macro for #mcuxClMath_QSquared. */
#define MCUXCLMATH_QSQUARED(iQSqr, iNShifted, iN, iT)  \
    mcuxClMath_QSquared(MCUXCLPKC_PACKARGS4(iQSqr, iNShifted, iN, iT))
/** Helper macro for #mcuxClMath_QSquared with flow protection. */
#define MCUXCLMATH_FP_QSQUARED(iQSqr, iNShifted, iN, iT)  \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(MCUXCLMATH_QSQUARED(iQSqr, iNShifted, iN, iT))


/**
 * @brief Calculates modular inversion, with odd modulus
 *
 * This function calculates modular inversion, result = X^(-1) mod n.
 *
 * @param[in] iR_iX_iN_iT  indices of PKC operands
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p iR_iX_iN_iT</dt>
 *       <dd><code>iT</code> (bits 0~7): index of temp (PKC operand).
 *       <br>Its size shall be at least (operandSize + MCUXCLPKC_WORDSIZE).
 *       <br>The offset (UPTRT[iT]) shall be exactly a multiple of MCUXCLPKC_WORDSIZE.
 *       <br><code>iN</code> (bits 8~15): index of modulus (PKC operand), size = operandSize.
 *       <br>NDash of modulus shall be stored in the PKC word before modulus.
 *       <br><code>iX</code> (bits 16~23): index of X (PKC operand), size = operandSize.
 *       <br>X will be destroyed by this function.
 *       <br>X and the modulus shall be coprime, otherwise the result will be incorrect.
 *       <br><code>iR</code> (bits 24~31): index of result (PKC operand).
 *       <br>Its size shall be at least (operandSize + MCUXCLPKC_WORDSIZE).
 *       <br>The offset (UPTRT[iR]) shall be exactly a multiple of MCUXCLPKC_WORDSIZE.
 *       <br>The result fits in operandSize, but might be greater than modulus.</dd>
 *   </dl></dd>
 * </dl>
 *
 * <dl>
 *   <dt>PKC properties</dt>
 *   <dd><dl>
 *     <dt>PS1 lengths</dt>
 *       <dd>PS1 OPLEN = MCLEN defines operandSize.</dd>
 *     <dt>PS2 lengths</dt>
 *       <dd>PS2 OPLEN and MCLEN will be modified, and original values will not be restored.</dd>
 *     <dt>ACTIV/GOANY</dt>
 *       <dd>#mcuxClPkc_WaitForReady will be called before returning to caller.
 *       <br>The PKC calculation might be still on-going,
 *           call #mcuxClPkc_WaitForFinish before CPU accesses to the result.</dd>
 *   </dl></dd>
 * </dl>
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_ModInv)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClMath_ModInv(
    uint32_t iR_iX_iN_iT
    );
/** Helper macro for #mcuxClMath_ModInv. */
#define MCUXCLMATH_MODINV(iR, iX, iN, iT)  \
    mcuxClMath_ModInv(MCUXCLPKC_PACKARGS4(iR, iX, iN, iT))
/** Helper macro for #mcuxClMath_ModInv with flow protection. */
#define MCUXCLMATH_FP_MODINV(iR, iX, iN, iT)  \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(MCUXCLMATH_MODINV(iR, iX, iN, iT))


/**
 * @brief Calculates modular reduction with even modulus
 *
 * This function calculates modular reduction result = X mod n, where the modulus n is even.
 *
 * @param[in] iR_iX_iN_iT0  indices of PKC operands
 * @param[in] iT1_iT2_iT3   indices of PKC operands
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p iR_iX_iN_iT0</dt>
 *       <dd><code>iT0</code> (bits 0~7): index of temp0 (PKC operand).
 *       <br>Its size shall be at least (lenN + MCUXCLPKC_WORDSIZE).
 *       <br>The operand of modulus can be used as temp0 (i.e., iT0 = iN), but the modulus will be destroyed.
 *       <br><code>iN</code>  (bits 8~15): index of modulus (PKC operand), size = lenN.
 *       <br>The offset (UPTRT[iN]) shall be exactly a multiple of MCUXCLPKC_WORDSIZE.
 *       <br><code>iX</code>  (bits 16~23): index of X (PKC operand).
 *       <br>Its size shall be at least (lenX + MCUXCLPKC_WORDSIZE).
 *       <br><code>iR</code>  (bits 24~31): index of result (PKC operand).
 *       <br>Its size shall be at least (lenN + MCUXCLPKC_WORDSIZE).</dd>
 *     <dt>@p iT1_iT2_iT3</dt>
 *       <dd><code>iT3</code> (bits 0~7): index of temp3 (PKC operand).
 *       <br>Its size shall be at least (lenN + MCUXCLPKC_WORDSIZE).
 *       <br><code>iT2</code> (bits 8~15): index of temp2 (PKC operand).
 *       <br>Its size shall be at least lenN.
 *       <br><code>iT1</code> (bits 16~23): index of temp1 (PKC operand).
 *       <br>Its size shall be at least lenN.
 *       <br>The operand of result can be used as temp1 (i.e., iT1 = iR).
 *       TODO: always use R (any reason not using R?)</dd>
 *   </dl></dd>
 * </dl>
 *
 * <dl>
 *   <dt>PKC properties</dt>
 *   <dd><dl>
 *     <dt>PS1 lengths</dt>
 *       <dd>PS1 OPLEN defines lenN (length of modulus n), and MCLEN defines lenX (length of X).
 *       <br>Both OPLEN and MCLEN shall be exactly a multiple of MCUXCLPKC_WORDSIZE.</dd>
 *     <dt>PS2 lengths</dt>
 *       <dd>PS2 OPLEN and MCLEN will be modified, and original values will not be restored.</dd>
 *     <dt>ACTIV/GOANY</dt>
 *       <dd>#mcuxClPkc_WaitForReady will be called before returning to caller.
 *       <br>The PKC calculation might be still on-going,
 *           call #mcuxClPkc_WaitForFinish before CPU accesses to the result.</dd>
 *   </dl></dd>
 * </dl>
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_ReduceModEven)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClMath_ReduceModEven(
    uint32_t iR_iX_iN_iT0,
    uint32_t iT1_iT2_iT3
    );
/** Helper macro for #mcuxClMath_ReduceModEven. */
#define MCUXCLMATH_REDUCEMODEVEN(iR, iX, iN, iT0, iT1, iT2, iT3)  \
    mcuxClMath_ReduceModEven(MCUXCLPKC_PACKARGS4(iR, iX, iN, iT0), MCUXCLPKC_PACKARGS4(0u, iT1, iT2, iT3))
/** Helper macro for #mcuxClMath_ReduceModEven with flow protection. */
#define MCUXCLMATH_FP_REDUCEMODEVEN(iR, iX, iN, iT0, iT1, iT2, iT3)  \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(MCUXCLMATH_REDUCEMODEVEN(iR, iX, iN, iT0, iT1, iT2, iT3))


/**
 * @brief Calculates modular exponentiation.
 *
 * This function calculates modular exponentiation with left-to-right binary
 * square-and-multiply algorithm.
 *
 * @param[in] pExp           pointer to exponent
 * @param[in] expByteLength  byte length of exponent
 * @param[in] iR_iX_iN_iT    indices of PKC operands
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p pExp </dt>
 *       <dd>the exponent is a big-endian octet string and shall be non-zero.</dd>
 *     <dt>@p iR_iX_iN_iT </dt>
 *       <dd><code>iT</code> (bits 0~7): index of temp operand (PKC operand).
 *       <br>Its size shall be at least (lenN + MCUXCLPKC_WORDSIZE).
 *       <br><code>iN</code> (bits 8~15): index of modulus (PKC operand), size = operandSize.
 *       <br>NDash of modulus shall be stored in the PKC word before modulus.
 *       <br><code>iX</code> (bits 16~23): index of base number (PKC operand), size = operandSize.
 *       <dd><code>iR</code> (bits 24~31): index of result (PKC operand).
 *       <br>Its size shall be at least (lenN + MCUXCLPKC_WORDSIZE).</dd>
 *   </dl></dd>
 * </dl>
 *
 * <dl>
 *   <dt>PKC properties</dt>
 *   <dd><dl>
 *     <dt>PS1 lengths</dt>
 *       <dd>PS1 OPLEN = MCLEN defines operandSize.</dd>
 *     <dt>PS2 lengths</dt>
 *       <dd>Unused.</dd>
 *     <dt>ACTIV/GOANY</dt>
 *       <dd>The PKC calculation might be still on-going,
 *           call #mcuxClPkc_WaitForFinish before CPU accesses to the result.</dd>
 *   </dl></dd>
 * </dl>
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_ModExp_SqrMultL2R)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClMath_ModExp_SqrMultL2R(
    const uint8_t *pExp,
    uint32_t expByteLength,
    uint32_t iR_iX_iN_iT
    );
/** Helper macro for #mcuxClMath_ModExp_SqrMultL2R. */
#define MCUXCLMATH_MODEXP_SQRMULTL2R(pExp, byteLenExp, iR, iX, iN, iT)  \
    mcuxClMath_ModExp_SqrMultL2R(pExp, byteLenExp, MCUXCLPKC_PACKARGS4(iR, iX, iN, iT))
/** Helper macro for #mcuxClMath_ModExp_SqrMultL2R with flow protection. */
#define MCUXCLMATH_FP_MODEXP_SQRMULTL2R(pExp, byteLenExp, iR, iX, iN, iT)  \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(MCUXCLMATH_MODEXP_SQRMULTL2R(pExp, byteLenExp, iR, iX, iN, iT))


/**
 * @brief Securely calculates modular exponentiation.
 *
 * This function calculates modular exponentiation in a secure manner.
 * It randomizes the computation by Euclidean splitting: exponent = b * q + r,
 * where b is a 64-bit odd random number (with both MSbit and LSbit set), and
 * r = exponent % b. The exponentiation is calculated by two steps:
 * (1) m0 = m^q mod n; and (2) result = m0^b * m^r mod n.
 * In addition, base operands are re-randomized, by adding random multiples of the
 * modulus to them before performing modular multiplications.
 *
 * @param[in] pSession        handle for the current CL session.
 * @param[in] pExp            pointer to exponent
 * @param[in] pExpTemp        pointer to temporary buffer
 * @param[in] expByteLength   byte length of exponent
 * @param[in] iT3_iX_iT2_iT1  indices of PKC operands
 * @param[in] iN_iTE_iT0_iR   indices of PKC operands
 * @param[in] secOption       option to disable the operand re-randomization
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p session:</dt>
 *       <dd>The session pointed to by pSession has to be initialized prior to a call to this function.</dd>
 *     <dt>@p pExp</dt>
 *       <dd>the exponent is a big-endian octet string and shall be non-zero.</dd>
 *     <dt>@p pExpTemp </dt>
 *       <dd>the temporary buffer can be in either CPU or PKC workarea.
 *       <br>It shall be CPU word aligned, and its length shall be a multiple of CPU word and greater than @p expByteLength.
 *       <br>It can share the space with exponent (i.e., pExpTemp = pExp), but the exponent will be overwritten.</dd>
 *     <dt>@p iT3_iX_iT2_iT1</dt>
 *       <dd><code>iT1</code> (bits 0~7): index of temp1 (PKC operand).
 *       <br>Its size shall be at least max(MCUXCLPKC_ROUNDUP_SIZE(@p expByteLength + 1), lenN + MCUXCLPKC_WORDSIZE, 2 * MCUXCLPKC_WORDSIZE).
 *       <br><code>iT2</code> (bits 8~15): index of temp2 (PKC operand).
 *       <br>Its size shall be at least max(lenN + MCUXCLPKC_WORDSIZE, 2 * MCUXCLPKC_WORDSIZE).
 *       <br><code>iX</code> (bits 16~23): index of base number (PKC operand), size = operandSize + MCUXCLPKC_WORDSIZE (= lenN + MCUXCLPKC_WORDSIZE).
 *       <br>It will be overwritten.
 *       <br><code>iT3</code> (bits 24~31): index of temp3 (PKC operand).
 *       <br>Its size shall be at least max(lenN + MCUXCLPKC_WORDSIZE, 2 * MCUXCLPKC_WORDSIZE).</dd>
 *     <dt>@p iN_iTE_iT0_iR</dt>
 *       <dd><code>iR</code> (bits 0~7): index of result (PKC operand).
 *       <br>The size shall be at least max(MCUXCLPKC_ROUNDUP_SIZE(@p expByteLength + 1), lenN + MCUXCLPKC_WORDSIZE).
 *       <br><code>iT0</code> (bits 8~15): index of temp0 (PKC operand).
 *       <br>The size shall be at least max(MCUXCLPKC_ROUNDUP_SIZE(@p expByteLength + 1), lenN + MCUXCLPKC_WORDSIZE).
 *       <br><code>iTE</code> (bits 16~23): index of temp4 (PKC operand).
 *       <br>The size shall be at least (6 * MCUXCLPKC_WORDSIZE).
 *       <br><code>iN</code> (bits 24~31): index of modulus (PKC operand), size = operandSize (= lenN).
 *       <br>The upper 32 bits of N shall be null, which can be obtained for instance by applying 32-bit modulus blinding,
 *           or by artificially increasing PS1 lengths and all buffer sizes by 1 PKC word.
 *       <br>NDash of modulus shall be stored in the PKC word before modulus.</dd>
 *   </dl></dd>
 * </dl>
 *
 * <dl>
 *   <dt>PKC properties</dt>
 *   <dd><dl>
 *     <dt>PS1 lengths</dt>
 *       <dd>PS1 OPLEN = MCLEN defines operandSize = MCUXCLPKC_ROUNDUP_SIZE(lenN), where lenN is the length of modulus n.</dd>
 *       <dd>As the upper 32 bits of N should be null, operandSize >= lenN + 4 bytes.</dd>
 *     <dt>PS2 lengths</dt>
 *       <dd>PS2 OPLEN and MCLEN will be modified, and original values will not be restored.</dd>
 *     <dt>ACTIV/GOANY</dt>
 *       <dd>#mcuxClPkc_WaitForReady will be called before returning to caller.</dd>
 *       <dd>The PKC calculation might be still on-going,
 *           call #mcuxClPkc_WaitForFinish before CPU accesses to the result.</dd>
 *   </dl></dd>
 * </dl>
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 * @retval #MCUXCLMATH_STATUS_OK     function executed successfully
 * @retval #MCUXCLMATH_STATUS_ERROR  error occurred during operation
 *
 * @attention This function uses PRNG which has to be initialized prior to calling the function.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_SecModExp)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClMath_Status_t) mcuxClMath_SecModExp(
    mcuxClSession_Handle_t session,
    const uint8_t *pExp,
    uint32_t *pExpTemp,
    uint32_t expByteLength,
    uint32_t iT3_iX_iT2_iT1,
    uint32_t iN_iTE_iT0_iR,
    uint32_t secOption
    );
/** Helper macro for #mcuxClMath_SecModExp. */
#define MCUXCLMATH_SECMODEXP(session, pExp, pExpTemp, byteLenExp, iR, iX, iN, iTE, iT0, iT1, iT2, iT3)  \
    mcuxClMath_SecModExp(session, pExp, pExpTemp, byteLenExp, MCUXCLPKC_PACKARGS4(iT3, iX, iT2, iT1), MCUXCLPKC_PACKARGS4(iN, iTE, iT0, iR), 0u)
/** Helper macro for #mcuxClMath_SecModExp with disabled operand re-randomization.
 * TODO CLNS-7824: analyze how to use the SecModExp in RsaKg MillerRabinTest, and remove secOption to always re-randomize */
#define MCUXCLMATH_SECMODEXP_WITHOUT_RERANDOMIZATION(session, pExp, pExpTemp, byteLenExp, iR, iX, iN, iTE, iT0, iT1, iT2, iT3)  \
    mcuxClMath_SecModExp(session, pExp, pExpTemp, byteLenExp, MCUXCLPKC_PACKARGS4(iT3, iX, iT2, iT1), MCUXCLPKC_PACKARGS4(iN, iTE, iT0, iR), MCUXCLMATH_SECMODEXP_OPTION_DIS_RERAND)


/**
 * @brief Calculates exact division with odd divisor.
 *
 * This function calculates exact division R = X/Y, where divisor Y is odd and
 * dividend X shall be exactly a multiple of Y. If X is not a multiple of Y,
 * result will be incorrect.
 *
 * @param[in] iR_iX_iY_iT     indices of PKC operands
 * @param[in] xPkcByteLength  length of X
 * @param[in] yPkcByteLength  length of Y
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p iR_iX_iY_iT</dt>
 *       <dd><code>iT</code> (bits 0~7): index of temp (PKC operand).
 *       <br>Its size shall be at least (3 * MCUXCLPKC_WORDSIZE).
 *       <br>The offset (UPTRT[iT]) shall be exactly a multiple of MCUXCLPKC_WORDSIZE.
 *       <br><code>iY</code> (bits 8~15): index of divisor Y (PKC operand), size = yPkcByteLength.
 *       <br>The most significant PKC word of Y shall be nonzero.
 *       <br><code>iX</code> (bits 16~23): index of dividend X (PKC operand), size = xPkcByteLength.
 *       <br>X will be destroyed by this function.
 *       <br>CAUTION: if xPkcByteLength = MCUXCLPKC_WORDSIZE,
 *           this function will access to (read) one extra PKC word of X, i.e.,
 *           X[MCUXCLPKC_WORDSIZE ~ 2*MCUXCLPKC_WORDSIZE - 1]. The value of this
 *           PKC word will not affect correctness of the result, but caller shall
 *           ensure that this PKC word is accessible by PKC.
 *       <br><code>iR</code> (bits 24~31): index of result R (PKC operand),
 *           size = (xPkcByteLength - yPkcByteLength + MCUXCLPKC_WORDSIZE).</dd>
 *     <dt>@p xPkcByteLength</dt>
 *       <dd>It shall be a multiple of MCUXCLPKC_WORDSIZE.</dd>
 *     <dt>@p yPkcByteLength</dt>
 *       <dd>It shall be a multiple of MCUXCLPKC_WORDSIZE.</dd>
 *   </dl></dd>
 * </dl>
 *
 * <dl>
 *   <dt>PKC properties</dt>
 *   <dd><dl>
 *     <dt>PS1 lengths</dt>
 *       <dd>Unused (modified and restored in the function).</dd>
 *     <dt>PS2 lengths</dt>
 *       <dd>PS2 OPLEN and MCLEN will be modified, and original values will not be restored.</dd>
 *     <dt>ACTIV/GOANY</dt>
 *       <dd>#mcuxClPkc_WaitForReady will be called before returning to caller.
 *       <br>The PKC calculation might be still on-going,
 *           call #mcuxClPkc_WaitForFinish before CPU accesses to the result.</dd>
 *   </dl></dd>
 * </dl>
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_ExactDivideOdd)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClMath_ExactDivideOdd(uint32_t iR_iX_iY_iT, uint32_t xPkcByteLength, uint32_t yPkcByteLength);
/** Helper macro for #mcuxClMath_ExactDivideOdd. */
#define MCUXCLMATH_EXACTDIVIDEODD(iR, iX, iN, iT, xPkcByteLen, yPkcByteLen)  \
    mcuxClMath_ExactDivideOdd(MCUXCLPKC_PACKARGS4(iR, iX, iN, iT), xPkcByteLen, yPkcByteLen)
/** Helper macro for #mcuxClMath_ExactDivideOdd with flow protection. */
#define MCUXCLMATH_FP_EXACTDIVIDEODD(iR, iX, iN, iT, xPkcByteLen, yPkcByteLen)  \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(MCUXCLMATH_EXACTDIVIDEODD(iR, iX, iN, iT, xPkcByteLen, yPkcByteLen))


/**
 * @brief Calculates exact division (supporting even divisor).
 *
 * This function calculates exact division R = X/Y, where dividend X shall be
 * exactly a multiple of divisor Y. If X is not a multiple of Y, result will be
 * incorrect.
 *
 * This function trims trailing zero bits of Y and gets Y' = Y >> trailingZeros(Y),
 * and X' = X >> ((trailingZeros(Y) / 8*MCUXCLPKC_WORDSIZE) * 8*MCUXCLPKC_WORDSIZE).
 * It relies on mcuxClMath_ExactDivideOdd to calculate R' = X'/Y', and then calculates
 * R = R' >> (trailingZeros(Y) % (8*MCUXCLPKC_WORDSIZE)).
 *
 * @param[in] iR_iX_iY_iT     Pointer table indices of parameters
 * @param[in] xPkcByteLength  length of X
 * @param[in] yPkcByteLength  length of Y
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p iR_iX_iY_iT</dt>
 *       <dd><code>iT</code> (bits 0~7): index of temp (PKC operand).
 *       <br>Its size shall be at least (3 * MCUXCLPKC_WORDSIZE).
 *       <br><code>iY</code> (bits 8~15): index of divisor Y (PKC operand), size = yPkcByteLength.
 *       <br>The most significant PKC word of Y shall be nonzero.
 *       <br>The offset (UPTRT[iY]) shall be exactly a multiple of MCUXCLPKC_WORDSIZE.
 *       <br><code>iX</code> (bits 16~23): index of dividend X (PKC operand), size = xPkcByteLength.
 *       <br>X will be destroyed by this function.
 *       <br>CAUTION: if the length of trimmed X' is MCUXCLPKC_WORDSIZE,
 *           this function will access to (read) one extra PKC word of X, i.e.,
 *           X[xPkcByteLength ~ xPkcByteLength + MCUXCLPKC_WORDSIZE - 1].
 *           The value of this PKC word will not affect correctness of the result,
 *           but caller shall ensure that this PKC word is accessible by PKC.
 *           If caller cannot guarantee the length of trimmed X' greater than
 *           MCUXCLPKC_WORDSIZE, X shall be stored in buffer of the size,
 *           xPkcByteLength + MCUXCLPKC_WORDSIZE.
 *       <br><code>iR</code> (bits 24~31): index of result R (PKC operand).
 *           Its buffer size shall be at least (xPkcByteLength - yPkcByteLength + 2*MCUXCLPKC_WORDSIZE).
 *           The result fits in size = (xPkcByteLength - yPkcByteLength + MCUXCLPKC_WORDSIZE).</dd>
 *     <dt>@p xPkcByteLength</dt>
 *       <dd>It shall be a multiple of MCUXCLPKC_WORDSIZE.</dd>
 *     <dt>@p yPkcByteLength</dt>
 *       <dd>It shall be a multiple of MCUXCLPKC_WORDSIZE.</dd>
 *   </dl></dd>
 * </dl>
 *
 * <dl>
 *   <dt>PKC properties</dt>
 *   <dd><dl>
 *     <dt>PS1 lengths</dt>
 *       <dd>Unused (modified and restored in the function).</dd>
 *     <dt>PS2 lengths</dt>
 *       <dd>PS2 OPLEN and MCLEN will be modified, and original values will not be restored.</dd>
 *     <dt>ACTIV/GOANY</dt>
 *       <dd>#mcuxClPkc_WaitForReady will be called before returning to caller.
 *       <br>The PKC calculation might be still on-going,
 *           call #mcuxClPkc_WaitForFinish before CPU accesses to the result.</dd>
 *   </dl></dd>
 * </dl>
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMath_ExactDivide)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClMath_ExactDivide(uint32_t iR_iX_iY_iT, uint32_t xPkcByteLength, uint32_t yPkcByteLength);
/** Helper macro for #mcuxClMath_ExactDivide. */
#define MCUXCLMATH_EXACTDIVIDE(iR, iX, iN, iT, xPkcByteLen, yPkcByteLen)  \
    mcuxClMath_ExactDivide(MCUXCLPKC_PACKARGS4(iR, iX, iN, iT), xPkcByteLen, yPkcByteLen)

/** Helper macro for #mcuxClMath_ExactDivide with flow protection. */
#define MCUXCLMATH_FP_EXACTDIVIDE(iR, iX, iN, iT, xPkcByteLen, yPkcByteLen)  \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(MCUXCLMATH_EXACTDIVIDE(iR, iX, iN, iT, xPkcByteLen, yPkcByteLen))


/**
 * @}
 */ /* mcuxClMath_Functions */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLMATH_FUNCTIONS_H_ */
