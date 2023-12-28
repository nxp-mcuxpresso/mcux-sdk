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
 * @file  mcuxClPkc_Functions.h
 * @brief APIs of mcuxClPkc component
 */


#ifndef MCUXCLPKC_FUNCTIONS_H_
#define MCUXCLPKC_FUNCTIONS_H_


#include <mcuxClCore_Platform.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClSession.h>
#include <mcuxClPkc_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup mcuxClPkc_Functions mcuxClPkc_Functions
 * @brief Defines all functions of @ref mcuxClPkc
 * @ingroup mcuxClPkc
 * @{
 */


/**********************************************************/
/* PKC initialization and deinitialization                */
/**********************************************************/
/**
 * @addtogroup mcuxClPkc_Functions_Init
 * mcuxClPkc functions of PKC initialization and deinitialization
 * @{
 */

/**
 * @brief Structure of PKC state backup.
 */
typedef struct
{
    uint16_t ctrl;  ///< backup of PKC CTRL bits
    uint16_t cfg;   ///< backup of PKC CFG bits
} mcuxClPkc_State_t;


/**
* @brief Function type for PKC initialization engine
*
* Generic function pointer to PKC initialization function
*
* @param[out]  pState   pointer to PKC state backup structure. If it's not a NULL pointer, PKC state before initialization will be stored in this structure.
*/
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClPkc_PkcInitializeEngine_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(void) (* mcuxClPkc_PkcInitializeEngine_t)(mcuxClPkc_State_t *pState));

/**
* @brief Function type for PKC deinitialization engine
*
* Generic function pointer to PKC deinitialization function
*
* @param[in]  pState   pointer to PKC state backup structure. If it's not a NULL pointer, PKC state will be restored from this structure.
*/
MCUX_CSSL_FP_FUNCTION_POINTER(mcuxClPkc_PkcDeInitializeEngine_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(void) (* mcuxClPkc_PkcDeInitializeEngine_t)(const mcuxClPkc_State_t *pState));

/**
 * @brief initialize PKC hardware
 *
 * This function initializes PKC hardware, and optionally backups the original PKC configuration (except STOP bit).
 *
 * @param[out] pState  pointer to PKC state backup structure. If it's not a NULL pointer, PKC state before initialization will be stored in this structure.
 *
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_Initialize, mcuxClPkc_PkcInitializeEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClPkc_Initialize(
    mcuxClPkc_State_t *pState
    );
/** Helper macro to call #mcuxClPkc_Initialize with flow protection. */
#define MCUXCLPKC_FP_INITIALIZE(pState)  \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClPkc_Initialize(pState))

/**
 * @brief deinitialize PKC hardware
 *
 * This function deinitializes PKC hardware, and optionally restores PKC configuration (except STOP bit).
 *
 * @param[in] pState  pointer to PKC state backup structure. If it's not a NULL pointer, PKC state will be restored from this structure.
 *
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_Deinitialize, mcuxClPkc_PkcDeInitializeEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClPkc_Deinitialize(
    const mcuxClPkc_State_t *pState
    );
/** Helper macro to call #mcuxClPkc_Deinitialize with flow protection. */
#define MCUXCLPKC_FP_DEINITIALIZE(pState)  \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClPkc_Deinitialize(pState))


/**
 * @}
 */ /* mcuxClPkc_Functions_Init */


/**********************************************************/
/* UPTR table                                             */
/**********************************************************/
/**
 * @addtogroup mcuxClPkc_Functions_UPTRT
 * mcuxClPkc functions of PKC UPTR table setup
 * @{
 */

/**
 * @brief Initialize UPTR table.
 *
 * This function initializes elements in UPTR table.
 * UPTR table contains the address (16-bit offset in PKC workarea) of each buffer (PKC operand).
 * Each element of the table will be initialized with a 16-bit offset, associated with a buffer allocated in sequence in PKC workarea.
 * When calling this function, there shall be no on-going and pending PKC calculations using the specified UPTR table elements.
 *
 * @param[out] pUPTRT      pointer to the first element to be initialized in UPTR table.
 * @param[in] pBaseBuffer  address of the buffer in PKC workarea, with which the first element will be associated.
 * @param[in] bufferLength byte length of each buffer in PKC workarea.
 * @param[in] noOfBuffer   number of elements to be initialized.
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>@p pUPTRT</dt>
 *       <dd>this pointer shall be 2-byte aligned.
 *     <dt>@p pBaseBuffer</dt>
 *       <dd>this address shall be MCUXCLPKC_WORDSIZE aligned.
 *     <dt>@p bufferLength</dt>
 *       <dd>this length shall be a multiple of MCUXCLPKC_WORDSIZE.
 *   </dl></dd>
 * </dl>
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_GenerateUPTRT)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClPkc_GenerateUPTRT(
    uint16_t *pUPTRT,
    const uint8_t *pBaseBuffer,
    uint16_t bufferLength,
    uint8_t noOfBuffer
    );
/** Helper macro to call #mcuxClPkc_GenerateUPTRT with flow protection. */
#define MCUXCLPKC_FP_GENERATEUPTRT(pUPTRT, pBaseBuffer, bufferSize, noOfBuffer)  \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClPkc_GenerateUPTRT(pUPTRT, pBaseBuffer, bufferSize, noOfBuffer))

/**
 * @brief Randomize UPTR table
 *
 * This function randomly permutes offsets stored in UPTR table.
 * It randomizes the buffer allocation (physical address in PKC workarea).
 * When calling this function, there shall be no on-going and pending PKC calculations using the specified UPTR table elements.
 *
 * @param[in] pSession    handle for the current CL session.
 * @param[in,out] pUPTRT  pointer to the first element to be randomized in UPTR table.
 * @param[in] noOfBuffer  number of elements to be randomized.
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>pSession:</dt>
 *       <dd>The session pointed to by pSession has to be initialized prior to a call to this function.
 *     <dt>@p pUPTRT</dt>
 *       <dd>this pointer shall be 2-byte aligned.
 *   </dl></dd>
 * </dl>
 *
 * @attention Only the buffer allocation will be randomized, existing operands stored in each buffer will not be moved accordingly.
 * @attention This function uses PRNG. Caller needs to check if PRNG is ready.
 *
 * @return A flow-protected status code (see @ref mcuxCsslFlowProtection).
 * @retval #MCUXCLPKC_STATUS_OK   if UPTR table is randomized successfully.
 * @retval #MCUXCLPKC_STATUS_NOK  if the operation failed.
 *
 * @attention This function uses PRNG which has to be initialized prior to calling the function.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_RandomizeUPTRT)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPkc_Status_t) mcuxClPkc_RandomizeUPTRT(
    mcuxClSession_Handle_t pSession,
    uint16_t *pUPTRT,
    uint8_t noOfBuffer
    );

/**
 * @brief Randomize UPTR table and operands in PKC workarea.
 *
 * This function randomly permutes offsets stored in UPTR table, together with operands stored in each buffer in PKC workarea.
 * It randomizes the buffer allocation (physical address in PKC workarea) and moves operands stored accordingly.
 * When calling this function, there shall be no on-going and pending PKC calculations using the specified UPTR table elements.
 *
 * @param[in] pSession      handle for the current CL session.
 * @param[in,out] pUPTRT    pointer to the first element to be randomized in UPTR table.
 * @param[in] bufferLength  byte length of each buffer in PKC workarea.
 * @param[in] noOfBuffer    number of elements to be randomized.
 *
 * <dl>
 *   <dt>Parameter properties</dt>
 *   <dd><dl>
 *     <dt>pSession:</dt>
 *       <dd>The session pointed to by pSession has to be initialized prior to a call to this function.
 *     <dt>@p pUPTRT</dt>
 *       <dd>this pointer shall be 2-byte aligned.
 *       <br>All offsets (pUPTRT[0~(noOfBuffer-1)]) shall be exactly a multiple of MCUXCLPKC_WORDSIZE.</dd>
 *     <dt>@p bufferLength</dt>
 *       <dd>this length shall be a multiple of MCUXCLPKC_WORDSIZE.
 *   </dl></dd>
 * </dl>
 *
 * @attention This function uses PRNG. Caller needs to check if PRNG is ready.
 *
 * @return A flow-protected status code (see @ref mcuxCsslFlowProtection).
 * @retval #MCUXCLPKC_STATUS_OK   if UPTR table is randomized successfully.
 * @retval #MCUXCLPKC_STATUS_NOK  if the operation failed.
 *
 * @attention This function uses PRNG which has to be initialized prior to calling the function.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_ReRandomizeUPTRT)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClPkc_Status_t) mcuxClPkc_ReRandomizeUPTRT(
    mcuxClSession_Handle_t pSession,
    uint16_t *pUPTRT,
    uint16_t bufferLength,
    uint8_t noOfBuffer
    );

/**
 * @}
 */ /* mcuxClPkc_Functions_UPTRT */


/**********************************************************/
/* PKC calculation                                        */
/**********************************************************/
/**
 * @addtogroup mcuxClPkc_Functions_Calculation
 * mcuxClPkc functions of PKC calculation
 * @{
 */

/**
 * @brief Start a PKC calculation
 *
 * This function performs one specified PKC calculation, of which the operand(s) and result are specified by the indices of UPTR table.
 *
 * @param[in] param_mode   param (the higher 8 bits) indicates the type of the calculation (L0 or L1) and the parameter set (PS1 or PS2).
 *                         <br> mode (the lower 8 bits) indicates the calculation, either an L0 operation or L1 microcode.
 * @param[in] iR_iX_iY_iZ  indices of the operand(s) and the result in UPTR table.
 *
 *
 * @attention The PKC calculation might be still on-going when returning to caller, call #mcuxClPkc_WaitForFinish before CPU accesses to the result.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_Calc)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClPkc_Calc(
    uint16_t param_mode,
    uint32_t iR_iX_iY_iZ
    );

/**
 * @brief Start a PKC calculation with one constant parameter
 *
 * This function performs one specified PKC calculation, of which the operand(s) and result are specified by the indices of UPTR table,
 * and a 8-bit constant parameter is directly provided.
 * This function can also be used to perform an L0 operation without using Z operand, e.g., OP_MUL, R = X0 * Y.
 *
 * @param[in] param_mode  param (the higher 8 bits) indicates the type of the calculation (always L0) and the parameter set (PS1 or PS2).
                          <br> mode (the lower 8 bits) indicates the calculation, an L0 operation.
 * @param[in] iR_iX_iY_C  indices of the operand(s) and the result in UPTR table, and a direct 8-bit constant.
 *
 *
 * @attention The PKC calculation might be still on-going when returning to caller, call #mcuxClPkc_WaitForFinish before CPU accesses to the result.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_CalcConst)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClPkc_CalcConst(
    uint16_t param_mode,
    uint32_t iR_iX_iY_C
    );

/** @brief type of FUP program address. */
typedef const struct mcuxClPkc_FUPEntry * mcuxClPkc_PtrFUPEntry_t;

/**
 * @brief Start a PKC FUP program calculation
 *
 * This function triggers PKC to start the calculation of a FUP program.
 *
 * @param[in] pUPTR    2-byte aligned address of the FUP program.
 * @param[in] uLength  length (number of calculation) of the FUP program.
 *
 * @attention The PKC calculation might be still on-going when returning to caller, call #mcuxClPkc_WaitForFinish before CPU accesses to the result.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_CalcFup)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClPkc_CalcFup(
    mcuxClPkc_PtrFUPEntry_t pUPTR,
    uint8_t uLength
    );
/** Helper macro to call #mcuxClPkc_CalcFup with flow protection. */
#define MCUXCLPKC_FP_CALCFUP(pUPTR, ulen)  \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClPkc_CalcFup(pUPTR, ulen))

/** Helper macro to call #mcuxClPkc_CalcFup (skipping first skipLen calculation(s)) with flow protection. */
#define MCUXCLPKC_FP_CALCFUP_OFFSET(pUPTR, skipLen, ulen)  \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClPkc_CalcFup(&((mcuxClPkc_PtrFUPEntry_t) (pUPTR))[(skipLen)], ulen))

/**
 * @}
 */ /* mcuxClPkc_Functions_Calculation */


/**********************************************************/
/* PKC wait functions                                     */
/**********************************************************/
/**
 * @addtogroup mcuxClPkc_Functions_Wait
 * mcuxClPkc functions for waiting PKC computation
 * @{
 */

/**
 * @brief Wait until PKC finishes calculations
 *
 * This function waits until PKC finishes on-going and pending calculations (if there is any).
 * When returning to caller, PKC is in idle state, and result in PKC workarea is ready.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_WaitForFinish)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClPkc_WaitForFinish(void);
/** Helper macro to call #mcuxClPkc_WaitForFinish with flow protection. */
#define MCUXCLPKC_FP_WAITFORFINISH()  \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClPkc_WaitForFinish())

/**
 * @brief Wait until PKC is ready to accept new calculation
 *
 * This function waits until PKC is ready to accept next calculation (i.e., no pending calculation).
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_WaitForReady)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClPkc_WaitForReady(void);
/** Helper macro to call #mcuxClPkc_WaitForReady with flow protection. */
#define MCUXCLPKC_FP_WAITFORREADY()  \
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClPkc_WaitForReady())


/**
 * @}
 */ /* mcuxClPkc_Functions_Wait */

/**
 * @}
 */ /* mcuxClPkc_Functions */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLPKC_FUNCTIONS_H_ */
