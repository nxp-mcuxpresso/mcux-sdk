/*--------------------------------------------------------------------------*/
/* Copyright 2022-2024 NXP                                                  */
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
 * @file  mcuxClGlikey.h
 * @brief Top-level include file for the Glikey driver
 *
 * This header exposes functions that implement the driver interface for the Glikey IP.
 *
 * @defgroup mcuxClGlikey mcuxClGlikey
 * @brief Glikey driver
 */

#ifndef MCUXCLGLIKEY_H_
#define MCUXCLGLIKEY_H_

#include <mcuxClConfig.h> // Exported features flags header

#include <stdint.h>
#include <stddef.h>

#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#ifdef __cplusplus
extern "C" {
#endif


/**********************************************
 * CONSTANTS
 **********************************************/
/**
 * @defgroup mcuxClGlikey_Constants mcuxClGlikey_Constants
 * @brief Constants for use with the Glikey driver
 * @ingroup mcuxClGlikey
 * @{
 */

/* [Design]
    Value: XX YZ UU VW
    - XX: F0: write to WR_EN1, 0F: do not write to WR_EN1
    - UU: F0: write to WR_EN0, 0F: do not write to WR_EN0
    - Y:  equal to <step> ^ W
    - Z:  value to write to WR_EN1 or equal to ~W
    - V:  equal to <step> ^ Z
    - W:  value to write to WR_EN0 or equal to ~Z
    Invariant: XXYZ ^ UUVW == 0xFFFF
*/
#define MCUXCLGLIKEY_CODEWORD_STEP1  ((uint32_t) 0xF0C10F3EU) ///< Codeword for transition from STEP1 --> STEP2
#define MCUXCLGLIKEY_CODEWORD_STEP2  ((uint32_t) 0x0F1DF0E2U) ///< Codeword for transition from STEP2 --> STEP3
#define MCUXCLGLIKEY_CODEWORD_STEP3  ((uint32_t) 0xF0B00F4FU) ///< Codeword for transition from STEP3 --> STEP4
#define MCUXCLGLIKEY_CODEWORD_STEP4  ((uint32_t) 0x0F4EF0B1U) ///< Codeword for transition from STEP4 --> STEP5
#define MCUXCLGLIKEY_CODEWORD_STEP5  ((uint32_t) 0xF0810F7EU) ///< Codeword for transition from STEP5 --> STEP6
#define MCUXCLGLIKEY_CODEWORD_STEP6  ((uint32_t) 0x0F5DF0A2U) ///< Codeword for transition from STEP6 --> STEP7
#define MCUXCLGLIKEY_CODEWORD_STEP7  ((uint32_t) 0xF0700F8FU) ///< Codeword for transition from STEP7 --> STEP8
#define MCUXCLGLIKEY_CODEWORD_STEP_EN  ((uint32_t) 0x0FFFF000U) ///< Codeword for transition from STEP 4/8 --> WR_EN

#define MCUXCLGLIKEY_STATUS_OK               0x0FF22E03u
#define MCUXCLGLIKEY_STATUS_NOT_LOCKED       0x0FF22E07u
#define MCUXCLGLIKEY_STATUS_LOCKED           0x0FF22E0Bu

#define MCUXCLGLIKEY_STATUS_VERSION_ERROR    0x0FF25334u
#define MCUXCLGLIKEY_STATUS_LOCKED_ERROR     0x0FF25338u

// Glikey state defines
#define MCUXCLGLIKEY_FSM_WR_DIS 0x0Bu
#define MCUXCLGLIKEY_FSM_INIT 0x16u
#define MCUXCLGLIKEY_FSM_STEP1 0x2Cu
#define MCUXCLGLIKEY_FSM_STEP2 0x58u
#define MCUXCLGLIKEY_FSM_STEP3 0xB0u
#define MCUXCLGLIKEY_FSM_STEP4 0x160u
#define MCUXCLGLIKEY_FSM_LOCKED 0xC01u
#define MCUXCLGLIKEY_FSM_WR_EN 0x1802u
#define MCUXCLGLIKEY_FSM_SSR_RESET 0x1005u
/**@}*/

/**
 * @}
 */



/**********************************************
 * TYPEDEFS
 **********************************************/
/**
 * @defgroup mcuxClGlikey_Types mcuxClGlikey_Types
 * @brief Types for use with the Glikey driver
 * @ingroup mcuxClGlikey
 * @{
 */

typedef uint32_t mcuxClGlikey_BaseAddress_t;
typedef uint32_t mcuxClGlikey_Status_t;
typedef uint32_t mcuxClGlikey_IntEnable_t;
typedef uint32_t mcuxClGlikey_GlikeyStatus_t;
/**
 * @}
 */

/**********************************************
 * FUNCTIONS
 **********************************************/
/**
 * @defgroup mcuxClGlikey_Types mcuxClGlikey_Types
 * @brief Types for use with the Glikey driver
 * @ingroup mcuxClGlikey
 * @{
 */


/**
 * @brief Retrieves the current status of Glikey.
 *
 * @param[in]   base    The base address of the Glikey instance
 * @param[out]  result  Pointer which will be filled with the Glikey status information
 *
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 *
 * @retval #MCUXCLGLIKEY_STATUS_OK               The operation was successful
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClGlikey_GetStatus)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t) mcuxClGlikey_GetStatus(
    mcuxClGlikey_BaseAddress_t *     base,
    mcuxClGlikey_GlikeyStatus_t *    result
    );
/**
 * @brief Perform a synchronous reset of Glikey.
 *
 * This function performs a synchronous reset of the Glikey. This results in:
 * - Glikey will return to the INIT state, unless it is in the GLOBAL_LOCK state [TODO: REVIEW NAMING]
 *
 * @param[in]   base    The base address of the Glikey instance
 *
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 *
 * @retval #MCUXCLGLIKEY_STATUS_OK               The operation was successful
 * @retval #MCUXCLGLIKEY_STATUS_LOCKED_ERROR     Glikey is locked and cannot be reset by software
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClGlikey_SyncReset)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t) mcuxClGlikey_SyncReset(
    mcuxClGlikey_BaseAddress_t *     base
    );

/**
 * @brief Set interrupt enable flag of Glikey.
 *
 * @param[in]   base    The base address of the Glikey instance
 * @param[in]   value   Value to set the interrupt enable flag to, see #[TODO: add reference to constants]
 *
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 *
 * @retval #MCUXCLGLIKEY_STATUS_OK               The operation was successful
 * @retval #MCUXCLGLIKEY_STATUS_LOCKED_ERROR     Glikey is locked and cannot be configured by software
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClGlikey_SetIntEnable)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t) mcuxClGlikey_SetIntEnable(
    mcuxClGlikey_BaseAddress_t *     base,
    mcuxClGlikey_IntEnable_t         value
    );

/**
 * @brief Get interrupt enable flag of Glikey.
 *
 * @param[in]   base    The base address of the Glikey instance
 * @param[out]  value   Pointer which will be filled with the interrupt enable status, see #[TODO: add reference to constants]
 *
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 *
 * @retval #MCUXCLGLIKEY_STATUS_OK               The operation was successful
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClGlikey_GetIntEnable)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t) mcuxClGlikey_GetIntEnable(
    mcuxClGlikey_BaseAddress_t *     base,
    mcuxClGlikey_IntEnable_t *       value
    );

/**
 * @brief Clear the interrupt status flag of Glikey.
 *
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 *
 * @retval #MCUXCLGLIKEY_STATUS_OK               The operation was successful
 * @retval #MCUXCLGLIKEY_STATUS_LOCKED_ERROR     Glikey is locked and cannot be configured by software
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClGlikey_ClearIntStatus)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t) mcuxClGlikey_ClearIntStatus(
    mcuxClGlikey_BaseAddress_t *     base
    );

/**
 * @brief Set the interrupt status flag of Glikey.
 *
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 *
 * @retval #MCUXCLGLIKEY_STATUS_OK               The operation was successful
 * @retval #MCUXCLGLIKEY_STATUS_LOCKED_ERROR     Glikey is locked and cannot be configured by software
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClGlikey_SetIntStatus)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t) mcuxClGlikey_SetIntStatus(
    mcuxClGlikey_BaseAddress_t *     base
    );

/**
 * @brief Lock Glikey SFR interface
 *
 * This operation locks the Glikey SFR interface if it is not locked yet.
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 *
 * @retval #MCUXCLGLIKEY_STATUS_OK               The operation was successful
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClGlikey_Lock)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t) mcuxClGlikey_Lock(
    mcuxClGlikey_BaseAddress_t *     base
    );

/**
 * @brief Check if Glikey is locked
 *
 * This operation returns the locking status of Glikey.
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 *
 * @retval #MCUXCLGLIKEY_STATUS_NOT_LOCKED       Glikey is not locked
 * @retval #MCUXCLGLIKEY_STATUS_LOCKED           Glikey is locked
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClGlikey_IsLocked)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t) mcuxClGlikey_IsLocked(
    mcuxClGlikey_BaseAddress_t *     base
    );

/**
 * @brief Check if Glikey index is locked
 *
 * This operation returns the locking status of Glikey index.
 * Using a wrong index (which is out of the bounds) leads to undefined program behavior.
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 *
 * @retval #MCUXCLGLIKEY_STATUS_NOT_LOCKED       The Glikey index is not locked
 * @retval #MCUXCLGLIKEY_STATUS_LOCKED           The Glikey index is locked
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClGlikey_IsIndexLocked)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t) mcuxClGlikey_IsIndexLocked(
    mcuxClGlikey_BaseAddress_t *     base,
    uint32_t                        index
    );

/**
 * @brief Start Glikey enable
 *
 * This operation is used to set a new index and start a the sequence to enable it. It needs to be
 * started from the INIT state. If the new index is already locked Glikey will go to LOCKED state,
 * otherwise it will go to STEP1 state.
 * If this operation is used when Glikey is in any state other than INIT Glikey will go to WR_DIS
 * state. It can only recover from this state through a reset (synchronous or asynchronous).
 * If the Glikey SFR lock is active this operation will return an error.
 * Using a wrong index (which is out of the bounds) leads to undefined program behavior.
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 *
 * @pre The FSM is in the INIT state.
 * 
 * @retval #MCUXCLGLIKEY_STATUS_OK               The operation was successful
 * @retval #MCUXCLGLIKEY_STATUS_LOCKED           The Glikey index is locked
 * @retval #MCUXCLGLIKEY_STATUS_LOCKED_ERROR     Glikey is locked and cannot be configured by software
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClGlikey_StartEnable)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t) mcuxClGlikey_StartEnable(
    mcuxClGlikey_BaseAddress_t *     base,
    uint32_t                        index
    );

/**
 * @brief Continue Glikey enable
 *
 * This operation is used to progress through the different states of the state machine, starting
 * from STEP1 until the state WR_EN is reached. Each next state of the state machine can only be
 * reached by providing the right codeword to this function. The transition from a state to itself is 
 * always possible. The possible transitions are:
 * - Step n -> Step n+1
 * - Step n -> Step n
 * - Step n_max -> WR_EN
 * - WR_EN -> WR_EN
 * If anything goes wrong the state machine will go to WR_DIS state and can only recover from it
 * through a reset (synchronous or asynchronous).
 * If the Glikey SFR lock is active this operation will return an error.
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 *
 * @retval #MCUXCLGLIKEY_STATUS_OK               The state transition was triggered successfully
 * @retval #MCUXCLGLIKEY_STATUS_LOCKED_ERROR     Glikey is locked and cannot be configured by software
 */
/* [Design]
    - Check if Glikey is locked
        if ( GLIKEY_LOCKED == GLIKEY_GET_SFR_LOCK(base) ) return MCUXCLGLIKEY_STATUS_LOCKED_ERROR
    - Decode the codeword and write to Glikey CTRL[]
        EnableSelect = (XX - 0xF)%2
        EnableValue  = (XXYZUUVW >> (EnableSelect << 4))&3
        Write GLIKEY_CTRL(base, EnableSelect, EnableValue)
    - Return MCUXCLGLIKEY_STATUS_OK
*/
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClGlikey_ContinueEnable)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t) mcuxClGlikey_ContinueEnable(
    mcuxClGlikey_BaseAddress_t *     base,
    uint32_t                        codeword
    );

/**
 * @brief Lock Glikey index
 *
 * This operation is used to lock a Glikey index. It can only be executed from the WR_EN state,
 * executing it from any other state will result in Glikey entering WR_DIS state. When this happens
 * Glikey requires a reset (synchronous or asynchronous) to go back to INIT state.
 * If the Glikey SFR lock is active this operation will return an error.
 * 
 * @pre The FSM is in the WR_EN state.
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 *
 * @retval #MCUXCLGLIKEY_STATUS_LOCKED           The Glikey index is now locked
 * @retval #MCUXCLGLIKEY_STATUS_LOCKED_ERROR     Glikey is locked and cannot be configured by software
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClGlikey_LockIndex)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t) mcuxClGlikey_LockIndex(
    mcuxClGlikey_BaseAddress_t *     base
    );

/**
 * @brief Reset Glikey index
 *
 * This operation is used to reset a Glikey index. It can only be executed from the INIT state,
 * executing it from any other state will result in Glikey entering WR_DIS state. When this happens
 * Glikey requires a reset (synchronous or asynchronous) to go back to INIT state.
 * If the Glikey SFR lock is active or the index is locked this operation will return an error.
 * Using a wrong index (which is out of the bounds) leads to undefined program behavior.
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 *
 * @retval #MCUXCLGLIKEY_STATUS_OK               The operation was successful
 * @retval #MCUXCLGLIKEY_STATUS_LOCKED           The Glikey index is locked
 * @retval #MCUXCLGLIKEY_STATUS_LOCKED_ERROR     Glikey is locked and cannot be configured by software
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClGlikey_ResetIndex)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t) mcuxClGlikey_ResetIndex(
    mcuxClGlikey_BaseAddress_t *     base,
    uint32_t                        index
    );



/**
 * @brief End Glikey operation  TODO: if we are in locked state we cannot exit(move to init) as curent index is locked
 *
 * This operation is used to end a Glikey operation. It can only be executed from the WR_EN, LOCKED,
 * RESET, and INIT states. Executing it from any other state will result in Glikey entering WR_DIS state.
 * When this happens Glikey requires a reset (synchronous or asynchronous) to go back to INIT state.
 * After this operation Glikey will go to INIT state or stay in LOCKED state when the index was locked.
 * If the Glikey SFR lock is active this operation will return an error.
 *
 * @return A code-flow protected error code (see @ref mcuxCsslFlowProtection)
 * 
 * @pre The FSM is in the WR_EN, LOCKED, RESET, or INIT state.
 *
 * @retval #MCUXCLGLIKEY_STATUS_OK               The operation was successful
 * @retval #MCUXCLGLIKEY_STATUS_LOCKED           The Glikey index is still locked
 * @retval #MCUXCLGLIKEY_STATUS_LOCKED_ERROR     Glikey is locked and cannot be configured by software
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClGlikey_EndOperation)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t) mcuxClGlikey_EndOperation(
    mcuxClGlikey_BaseAddress_t *     base
    );


/**
 * @}
 */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // MCUXCLGLIKEY_H_
