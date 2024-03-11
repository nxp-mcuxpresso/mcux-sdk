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
 * @file  mcuxClGlikey.c
 * @brief Implementation of the driver interface for the Glikey IP.
 * @defgroup mcuxClGlikey mcuxClGlikey
 * @brief Glikey driver
 */

#include <mcuxClGlikey.h>
#include <internal/mcuxClGlikey_SfrAccess.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <platform_specific_headers.h>



/**********************************************
 * MACROS
 **********************************************/
/**
 * @defgroup mcuxClGlikey_Macros mcuxClGlikey_Macros
 * @brief Macros for use with the Glikey driver
 * @ingroup mcuxClGlikey
 * @{
 */

/* [Design]
    The Glikey driver will use macros to access the fields of the Glikey SFR instead of unions/structures.
 */

#define MCUXCLGLIKEY_SFR_LOCK_LOCKED    0x05u
#define MCUXCLGLIKEY_SFR_LOCK_UNLOCKED  0x0Au

/**
 * @}
 */


/**********************************************
 * Helper
 **********************************************/

static inline void mcuxClGlikey_Internal_Set_WR_0(mcuxClGlikey_BaseAddress_t *base, uint32_t value)
{
    uint32_t ctrl0 = MCUXCLGLIKEY_SFR_READ(base, CTRL_0);
    //clear WR_0
    ctrl0 = ctrl0 & (~MCUXCLGLIKEY_SFR_FIELD_MASK(CTRL_0, WR_EN_0));
    MCUXCLGLIKEY_SFR_WRITE(base, CTRL_0, ctrl0 | MCUXCLGLIKEY_SFR_FIELD_FORMAT(CTRL_0, WR_EN_0, value));
}

static inline void mcuxClGlikey_Internal_Set_WR_1(mcuxClGlikey_BaseAddress_t *base, uint32_t value)
{
    uint32_t ctrl1 = MCUXCLGLIKEY_SFR_READ(base, CTRL_1);
    //clear WR_1
    ctrl1 = ctrl1 & (~MCUXCLGLIKEY_SFR_FIELD_MASK(CTRL_1, WR_EN_1));
    MCUXCLGLIKEY_SFR_WRITE(base, CTRL_1, ctrl1 | MCUXCLGLIKEY_SFR_FIELD_FORMAT(CTRL_1, WR_EN_1, value));
}

static inline mcuxClGlikey_GlikeyStatus_t mcuxClGlikey_Internal_GetStatus(mcuxClGlikey_BaseAddress_t *base)
{
    return MCUXCLGLIKEY_SFR_READ(base, STATUS);
}

static uint32_t mcuxClGlikey_Internal_Check_Glikey_Lock(mcuxClGlikey_BaseAddress_t *base)
{
    uint32_t sfrLock = MCUXCLGLIKEY_SFR_BITREAD(base, CTRL_1, SFR_LOCK);
    if(MCUXCLGLIKEY_SFR_LOCK_UNLOCKED != sfrLock) //locked
    {
        return MCUXCLGLIKEY_STATUS_LOCKED;
    }

    return MCUXCLGLIKEY_STATUS_NOT_LOCKED;
}


/**********************************************
 * Public API
 **********************************************/


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClGlikey_GetStatus)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t)
mcuxClGlikey_GetStatus(mcuxClGlikey_BaseAddress_t *base,
                      mcuxClGlikey_GlikeyStatus_t *result)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClGlikey_GetStatus);

    *result = mcuxClGlikey_Internal_GetStatus(base);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_GetStatus, MCUXCLGLIKEY_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClGlikey_SyncReset)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t)
mcuxClGlikey_SyncReset(mcuxClGlikey_BaseAddress_t *base)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClGlikey_SyncReset);

    if(MCUXCLGLIKEY_STATUS_NOT_LOCKED != mcuxClGlikey_Internal_Check_Glikey_Lock(base))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_SyncReset, MCUXCLGLIKEY_STATUS_LOCKED_ERROR);
    }

    //set CTRL_0.SFT_RST = 1
    MCUXCLGLIKEY_SFR_BITSET(base, CTRL_0, SFT_RST);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_SyncReset, MCUXCLGLIKEY_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClGlikey_SetIntEnable)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t)
mcuxClGlikey_SetIntEnable(mcuxClGlikey_BaseAddress_t *base,
                         mcuxClGlikey_IntEnable_t value)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClGlikey_SetIntEnable);

    if(MCUXCLGLIKEY_STATUS_NOT_LOCKED != mcuxClGlikey_Internal_Check_Glikey_Lock(base))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_SetIntEnable, MCUXCLGLIKEY_STATUS_LOCKED_ERROR);
    }

    MCUXCLGLIKEY_SFR_WRITE(base, INTR_CTRL, MCUXCLGLIKEY_SFR_FIELD_FORMAT(INTR_CTRL, INT_EN, value));
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_SetIntEnable, MCUXCLGLIKEY_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClGlikey_GetIntEnable)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t)
mcuxClGlikey_GetIntEnable(mcuxClGlikey_BaseAddress_t *base,
                         mcuxClGlikey_IntEnable_t *value)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClGlikey_GetIntEnable);

    *value = MCUXCLGLIKEY_SFR_READ(base, INTR_CTRL) & MCUXCLGLIKEY_SFR_FIELD_MASK(INTR_CTRL, INT_EN);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_GetIntEnable, MCUXCLGLIKEY_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClGlikey_ClearIntStatus)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t)
mcuxClGlikey_ClearIntStatus(mcuxClGlikey_BaseAddress_t *base)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClGlikey_ClearIntStatus);

    if(MCUXCLGLIKEY_STATUS_NOT_LOCKED != mcuxClGlikey_Internal_Check_Glikey_Lock(base))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_ClearIntStatus, MCUXCLGLIKEY_STATUS_LOCKED_ERROR);
    }

   MCUXCLGLIKEY_SFR_BITSET(base, INTR_CTRL, INT_CLR);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_ClearIntStatus, MCUXCLGLIKEY_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClGlikey_SetIntStatus)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t)
mcuxClGlikey_SetIntStatus(mcuxClGlikey_BaseAddress_t *base)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClGlikey_SetIntStatus);

    if(MCUXCLGLIKEY_STATUS_NOT_LOCKED != mcuxClGlikey_Internal_Check_Glikey_Lock(base))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_SetIntStatus, MCUXCLGLIKEY_STATUS_LOCKED_ERROR);
    }

    MCUXCLGLIKEY_SFR_BITSET(base, INTR_CTRL, INT_SET);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_SetIntStatus, MCUXCLGLIKEY_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClGlikey_Lock)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t)
mcuxClGlikey_Lock(mcuxClGlikey_BaseAddress_t *base)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClGlikey_Lock);

    //Check if SFR_LOCK is locked
    if(MCUXCLGLIKEY_STATUS_NOT_LOCKED == mcuxClGlikey_Internal_Check_Glikey_Lock(base))  //Glikey is not locked -> lock
    {
        uint32_t ctrl1 = MCUXCLGLIKEY_SFR_READ(base, CTRL_1);
        //clear SFR_LOCK
        ctrl1 = ctrl1 & (~MCUXCLGLIKEY_SFR_FIELD_MASK(CTRL_1, SFR_LOCK));
        //Lock Glikey
        MCUXCLGLIKEY_SFR_WRITE(base, CTRL_1, ctrl1 | MCUXCLGLIKEY_SFR_FIELD_FORMAT(CTRL_1, SFR_LOCK, MCUXCLGLIKEY_SFR_LOCK_LOCKED) );
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_Lock, MCUXCLGLIKEY_STATUS_OK);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClGlikey_IsLocked)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t)
mcuxClGlikey_IsLocked(mcuxClGlikey_BaseAddress_t *base)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClGlikey_IsLocked);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_IsLocked, mcuxClGlikey_Internal_Check_Glikey_Lock(base));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClGlikey_IsIndexLocked)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t)
mcuxClGlikey_IsIndexLocked(mcuxClGlikey_BaseAddress_t *base,
                          uint32_t index)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClGlikey_IsIndexLocked);

    //set CTRL_1.READ_INDEX = index
    uint32_t ctr1Val = MCUXCLGLIKEY_SFR_READ(base, CTRL_1);
    //Clear READ_INDEX
    ctr1Val = ctr1Val & (~MCUXCLGLIKEY_SFR_FIELD_MASK(CTRL_1, READ_INDEX));
    //Set index value
    MCUXCLGLIKEY_SFR_WRITE(base, CTRL_1, ctr1Val | MCUXCLGLIKEY_SFR_FIELD_FORMAT(CTRL_1, READ_INDEX, index));

    // check if STATUS.LOCK_STATUS is 0
    if (0u == (mcuxClGlikey_Internal_GetStatus(base) & MCUXCLGLIKEY_SFR_FIELD_MASK(STATUS, LOCK_STATUS)))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_IsIndexLocked ,MCUXCLGLIKEY_STATUS_NOT_LOCKED);
    }
    else
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_IsIndexLocked, MCUXCLGLIKEY_STATUS_LOCKED);
    }
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClGlikey_StartEnable)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t)
mcuxClGlikey_StartEnable(mcuxClGlikey_BaseAddress_t *base,
                        uint32_t index)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClGlikey_StartEnable);

    if(MCUXCLGLIKEY_STATUS_NOT_LOCKED != mcuxClGlikey_Internal_Check_Glikey_Lock(base))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_StartEnable, MCUXCLGLIKEY_STATUS_LOCKED_ERROR);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(retCodeIsIndexLocked, mcuxClGlikey_IsIndexLocked(base, index));
    if(MCUXCLGLIKEY_STATUS_NOT_LOCKED != retCodeIsIndexLocked)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_StartEnable, retCodeIsIndexLocked,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClGlikey_IsIndexLocked));
    }

    uint32_t ctrl0 = MCUXCLGLIKEY_SFR_READ(base, CTRL_0);
    //Clear old index
    ctrl0 = ctrl0 & (~MCUXCLGLIKEY_SFR_FIELD_MASK(CTRL_0, WRITE_INDEX));
    //set index
    ctrl0 |= MCUXCLGLIKEY_SFR_FIELD_FORMAT(CTRL_0, WRITE_INDEX, index);
    //Set CTRL_0 with correct index and WR_EN_0 = 0x02
    MCUXCLGLIKEY_SFR_WRITE(base, CTRL_0, ctrl0);

    //Clear old wr_en_0
    ctrl0 = ctrl0 & (~MCUXCLGLIKEY_SFR_FIELD_MASK(CTRL_0, WR_EN_0));
    //Set CTRL_0 with correct index and WR_EN_0 = 0x01, to progress to STEP1
    MCUXCLGLIKEY_SFR_WRITE(base, CTRL_0, ctrl0 | ((mcuxClGlikey_BaseAddress_t)0x01u << MCUXCLGLIKEY_SFR_FIELD_SHIFT(CTRL_0, WR_EN_0)));

    //Set WR_EN_1 to 0x00 - needed? as this should be 0
    MCUXCLGLIKEY_SFR_BITCLEAR(base, CTRL_1, WR_EN_1);

    //TODO: is there something to check? Maybe if we are now in state1, should we check before if we where in Init?

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_StartEnable, MCUXCLGLIKEY_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClGlikey_IsIndexLocked));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClGlikey_ContinueEnable)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t)
mcuxClGlikey_ContinueEnable(mcuxClGlikey_BaseAddress_t *base,
                           uint32_t codeword)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClGlikey_ContinueEnable);

    //set correctly we_en0 and wr_en1 according to codeword
    MCUX_CSSL_FP_FUNCTION_CALL(retCodeIsLocked, mcuxClGlikey_IsLocked(base));
    if(MCUXCLGLIKEY_STATUS_NOT_LOCKED != retCodeIsLocked)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_ContinueEnable, MCUXCLGLIKEY_STATUS_LOCKED_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClGlikey_IsLocked));
    }

    //select CTRL0/CTRL1
    uint32_t enableSelect = codeword >> 24u;

    if(0xF0u == enableSelect)
    {
        mcuxClGlikey_Internal_Set_WR_1(base, codeword >> 16u);
    }
    else
    {
        mcuxClGlikey_Internal_Set_WR_0(base, codeword);
    }
    //Alternative could be to use  mcuxClGlikey_Internal_Set_WR_X(ctrl0Addr + enableSelect, codeword >> (16 * enableSelect))

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_ContinueEnable, MCUXCLGLIKEY_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClGlikey_IsLocked));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClGlikey_LockIndex)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t)
mcuxClGlikey_LockIndex(mcuxClGlikey_BaseAddress_t *base)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClGlikey_LockIndex);

    MCUX_CSSL_FP_FUNCTION_CALL(retCodeIsLocked, mcuxClGlikey_IsLocked(base));
    if(MCUXCLGLIKEY_STATUS_NOT_LOCKED != retCodeIsLocked)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_LockIndex, MCUXCLGLIKEY_STATUS_LOCKED_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClGlikey_IsLocked));
    }

    //set WR_EN0 = b11
    uint32_t ctrl0 = MCUXCLGLIKEY_SFR_READ(base, CTRL_0);
    MCUXCLGLIKEY_SFR_WRITE(base, CTRL_0, ctrl0 | MCUXCLGLIKEY_SFR_FIELD_FORMAT(CTRL_0, WR_EN_0, 0x3u));

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_LockIndex, MCUXCLGLIKEY_STATUS_LOCKED,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClGlikey_IsLocked));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClGlikey_ResetIndex)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t)
mcuxClGlikey_ResetIndex(mcuxClGlikey_BaseAddress_t *base,
                       uint32_t index)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClGlikey_ResetIndex);

    //Check if Glikey is locked
    MCUX_CSSL_FP_FUNCTION_CALL(retCodeIsLocked, mcuxClGlikey_IsLocked(base));
    if(MCUXCLGLIKEY_STATUS_NOT_LOCKED != retCodeIsLocked)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_ResetIndex,  MCUXCLGLIKEY_STATUS_LOCKED_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClGlikey_IsLocked));
    }

    //Check if index is locked
    MCUX_CSSL_FP_FUNCTION_CALL(retCodeIsIndexLocked, mcuxClGlikey_IsIndexLocked(base, index));
    if(MCUXCLGLIKEY_STATUS_NOT_LOCKED != retCodeIsIndexLocked)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_ResetIndex,  retCodeIsIndexLocked,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClGlikey_IsLocked),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClGlikey_IsIndexLocked));
    }

    // Write WRITE_INDEX = index and WR_EN_0 = 0b11
    uint32_t ctrl0 = MCUXCLGLIKEY_SFR_FIELD_FORMAT(CTRL_0, WRITE_INDEX, index);
    ctrl0 |=  MCUXCLGLIKEY_SFR_FIELD_FORMAT(CTRL_0, WR_EN_0, 0x03u);
    MCUXCLGLIKEY_SFR_WRITE(base, CTRL_0, ctrl0);

    // Write WR_EN_1 = 0b00
    uint32_t ctrl1 = MCUXCLGLIKEY_SFR_READ(base, CTRL_1);
    ctrl1 = ctrl1 & (~MCUXCLGLIKEY_SFR_FIELD_MASK(CTRL_1, WR_EN_1));
    MCUXCLGLIKEY_SFR_WRITE(base, CTRL_1, ctrl1);

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_ResetIndex,  MCUXCLGLIKEY_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClGlikey_IsLocked),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClGlikey_IsIndexLocked));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClGlikey_EndOperation)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClGlikey_Status_t)
mcuxClGlikey_EndOperation(mcuxClGlikey_BaseAddress_t *base)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClGlikey_EndOperation);

    //Check if Glikey is locked
    MCUX_CSSL_FP_FUNCTION_CALL(retCodeIsLocked, mcuxClGlikey_IsLocked(base));
    if(MCUXCLGLIKEY_STATUS_NOT_LOCKED != retCodeIsLocked)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_EndOperation, MCUXCLGLIKEY_STATUS_LOCKED_ERROR,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClGlikey_IsLocked));
    }

    /* Check state before transition */
    uint32_t prevState = MCUXCLGLIKEY_SFR_BITREAD(base, STATUS, FSM_STATE);  /* MISRA Ex. 9 to Rule 11.3 - Interaction with hardware */

    /* Do the transition: wr_en0 = 10; wr_en1 = 00 */
    mcuxClGlikey_Internal_Set_WR_0(base, 0x02u);
    mcuxClGlikey_Internal_Set_WR_1(base, 0x00u);

    if(MCUXCLGLIKEY_FSM_LOCKED == prevState)
    {
        // if still locked return locked - need to change index
        if (MCUXCLGLIKEY_FSM_LOCKED == MCUXCLGLIKEY_SFR_BITREAD(base, STATUS, FSM_STATE))
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_EndOperation, MCUXCLGLIKEY_STATUS_LOCKED,
                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClGlikey_IsLocked));
        }

        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_EndOperation, MCUXCLGLIKEY_STATUS_OK,
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClGlikey_IsLocked));
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClGlikey_EndOperation, MCUXCLGLIKEY_STATUS_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClGlikey_IsLocked));
}
