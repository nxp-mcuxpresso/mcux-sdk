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
 * @file  mcuxClPkc_Functions.h
 * @brief APIs of mcuxClPkc component
 */


#ifndef MCUXCLPKC_FUNCTIONS_H_
#define MCUXCLPKC_FUNCTIONS_H_


#include <stdint.h>
#include <stdbool.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClPkc_Types.h>


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
 * @brief initialize PKC hardware
 *
 * This function initializes PKC hardware, and optionally backup the original PKC configuration (except STOP bit).
 *
 * @param[out] pState  pointer to PKC state backup structure. If it's not a NULL pointer, PKC state before initialization will be stored in this structure.
 *
 * @return A flow-protected status code (see @ref mcuxCsslFlowProtection).
 * @retval #MCUXCLPKC_STATUS_OK  this function always returns OK.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_Initialize)
mcuxClPkc_Status_Protected_t mcuxClPkc_Initialize(
    mcuxClPkc_State_t *pState
    );
/** Helper macro to call #mcuxClPkc_Initialize with flow protection. */
#define MCUXCLPKC_FP_INITIALIZE(pState)  \
    do{ \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClPkc_Initialize(pState));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while (false)

/**
 * @brief deinitialize PKC hardware
 *
 * This function deinitializes PKC hardware, and optionally restore PKC configuration (except STOP bit).
 *
 * @param[in] pState  pointer to PKC state backup structure. If it's not a NULL pointer, PKC state will be restored from this structure.
 *
 * @return A flow-protected status code (see @ref mcuxCsslFlowProtection).
 * @retval #MCUXCLPKC_STATUS_OK  this function always returns OK.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_Deinitialize)
mcuxClPkc_Status_Protected_t mcuxClPkc_Deinitialize(
    const mcuxClPkc_State_t *pState
    );
/** Helper macro to call #mcuxClPkc_Deinitialize with flow protection. */
#define MCUXCLPKC_FP_DEINITIALIZE(pState)  \
    do{ \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClPkc_Deinitialize(pState));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while (false)

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
 *
 * @param[out] pUPTRT      pointer to the first element to be initialized in UPTR table.
 * @param[in] pBaseBuffer  address of the buffer in PKC workarea, with which the first element will be associated.
 * @param[in] bufferSize   byte length of each buffer in PKC workarea.
 * @param[in] noOfBuffer   number of elements to be initialized.
 *
 * @return A flow-protected status code (see @ref mcuxCsslFlowProtection).
 * @retval #MCUXCLPKC_STATUS_OK  this function always returns OK.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_GenerateUPTRT)
mcuxClPkc_Status_Protected_t mcuxClPkc_GenerateUPTRT(
    uint16_t *pUPTRT,
    const uint8_t *pBaseBuffer,
    uint16_t bufferSize,
    uint8_t noOfBuffer
    );
/** Helper macro to call #mcuxClPkc_GenerateUPTRT with flow protection. */
#define MCUXCLPKC_FP_GENERATEUPTRT(pUPTRT, pBaseBuffer, bufferSize, noOfBuffer)  \
    do{ \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClPkc_GenerateUPTRT(pUPTRT, pBaseBuffer, bufferSize, noOfBuffer));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while (false)

/**
 * @brief Randomize UPTR table
 *
 * This function randomly permutes offsets stored in UPTR table.
 * It randomizes the buffer allocation (physical address in PKC workarea).
 *
 * @param[in,out] pUPTRT  pointer to the first element to be randomized in UPTR table.
 * @param[in] noOfBuffer  number of elements to be randomized.
 *
 * @return A flow-protected status code (see @ref mcuxCsslFlowProtection).
 * @retval #MCUXCLPKC_STATUS_OK   if UPTR table is randomized successfully.
 * @retval #MCUXCLPKC_STATUS_NOK  if the operation failed.
 *
 * @attention Only the buffer allocation will be randomized, existing operands stored in each buffer will not be moved accordingly.
 * @attention This function uses PRNG. Caller needs to check if PRNG is ready.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_RandomizeUPTRT)
mcuxClPkc_Status_Protected_t mcuxClPkc_RandomizeUPTRT(
    uint16_t *pUPTRT,
    uint8_t noOfBuffer
    );

/**
 * @brief Randomize UPTR table and operands in PKC workarea.
 *
 * This function randomly permutes offsets stored in UPTR table, together with operands stored in each buffer in PKC workarea.
 * It randomizes the buffer allocation (physical address in PKC workarea) and moves operands stored accordingly.
 *
 * @param[in,out] pUPTRT  pointer to the first element to be randomized in UPTR table.
 * @param[in] bufferSize  byte length of each buffer in PKC workarea.
 * @param[in] noOfBuffer  number of elements to be randomized.
 *
 * @return A flow-protected status code (see @ref mcuxCsslFlowProtection).
 * @retval #MCUXCLPKC_STATUS_OK   if UPTR table is randomized successfully.
 * @retval #MCUXCLPKC_STATUS_NOK  if the operation failed.
 *
 * @attention This function uses PRNG. Caller needs to check if PRNG is ready.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_ReRandomizeUPTRT)
mcuxClPkc_Status_Protected_t mcuxClPkc_ReRandomizeUPTRT(
    uint16_t *pUPTRT,
    uint16_t bufferSize,
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
 * @return A flow-protected status code (see @ref mcuxCsslFlowProtection).
 * @retval #MCUXCLPKC_STATUS_OK  this function always returns OK.
 *
 * @attention The PKC calculation might be still on-going, call #mcuxClPkc_WaitForFinish before CPU accesses to the result.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_Calc)
mcuxClPkc_Status_Protected_t mcuxClPkc_Calc(
    uint16_t param_mode,
    uint32_t iR_iX_iY_iZ
    );

/**
 * @brief Start a PKC calculation with one constant parameter
 *
 * This function performs one specified PKC calculation, of which the operand(s) and result are specified by the indices of UPTR table,
 * and a 8-bit constant parameter is directly provided.
 *
 * @param[in] param_mode  param (the higher 8 bits) indicates the type of the calculation (always L0) and the parameter set (PS1 or PS2).
                          <br> mode (the lower 8 bits) indicates the calculation, an L0 operation.
 * @param[in] iR_iX_iY_C  indices of the operand(s) and the result in UPTR table, and a direct 8-bit constant.
 *
 * @return A flow-protected status code (see @ref mcuxCsslFlowProtection).
 * @retval #MCUXCLPKC_STATUS_OK  this function always returns OK.
 *
 * @attention The PKC calculation might be still on-going, call #mcuxClPkc_WaitForFinish before CPU accesses to the result.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_CalcConst)
mcuxClPkc_Status_Protected_t mcuxClPkc_CalcConst(
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
 * @param[in] pUPTR address of the FUP program.
 * @param[in] ulen  length (number of calculation) of the FUP program.
 *
 * @return A flow-protected status code (see @ref mcuxCsslFlowProtection).
 * @retval #MCUXCLPKC_STATUS_OK  this function always returns OK.
 *
 * @attention The PKC calculation might be still on-going, call #mcuxClPkc_WaitForFinish before CPU accesses to the result.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_CalcFup)
mcuxClPkc_Status_Protected_t mcuxClPkc_CalcFup(
    mcuxClPkc_PtrFUPEntry_t pUPTR,
    uint8_t ulen
    );
/** Helper macro to call #mcuxClPkc_CalcFup with flow protection. */
#define MCUXCLPKC_FP_CALCFUP(pUPTR, ulen)  \
    do{ \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClPkc_CalcFup(pUPTR, ulen));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while (false)
/** Helper macro to call #mcuxClPkc_CalcFup (skipping first skipLen calculation(s)) with flow protection. */
#define MCUXCLPKC_FP_CALCFUP_OFFSET(pUPTR, skipLen, ulen)  \
    do{ \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClPkc_CalcFup(&((mcuxClPkc_PtrFUPEntry_t) (pUPTR))[(skipLen)], ulen));  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while (false)

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
 *
 * @return A flow-protected status code (see @ref mcuxCsslFlowProtection).
 * @retval #MCUXCLPKC_STATUS_OK  this function always returns OK.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_WaitForFinish)
mcuxClPkc_Status_Protected_t mcuxClPkc_WaitForFinish(void);
/** Helper macro to call #mcuxClPkc_WaitForFinish with flow protection. */
#define MCUXCLPKC_FP_WAITFORFINISH()  \
    do{ \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClPkc_WaitForFinish());  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while (false)

/**
 * @brief Wait until PKC is ready to accept new calculation
 *
 * This function waits until PKC is ready to accept next calculation (i.e., no pending calculation).
 *
 * @return A flow-protected status code (see @ref mcuxCsslFlowProtection).
 * @retval #MCUXCLPKC_STATUS_OK  this function always returns OK.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClPkc_WaitForReady)
mcuxClPkc_Status_Protected_t mcuxClPkc_WaitForReady(void);
/** Helper macro to call #mcuxClPkc_WaitForReady with flow protection. */
#define MCUXCLPKC_FP_WAITFORREADY()  \
    do{ \
        MCUX_CSSL_FP_FUNCTION_CALL(retValTemp, mcuxClPkc_WaitForReady());  \
        (void) retValTemp;  /* Checking is unnecessary, because it always returns OK. */  \
    } while (false)

/**
 * @}
 */ /* mcuxClPkc_Functions_Wait */

/**
 * @}
 */ /* mcuxClPkc_Functions */


#endif /* MCUXCLPKC_FUNCTIONS_H_ */
