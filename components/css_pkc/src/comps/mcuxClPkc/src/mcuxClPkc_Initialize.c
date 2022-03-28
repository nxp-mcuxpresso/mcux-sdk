/*--------------------------------------------------------------------------*/
/* Copyright 2020 NXP                                                       */
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
 * @file  mcuxClPkc_Initialize.c
 * @brief PKC initialize and deinitialize functions
 */


#include <platform_specific_headers.h>
#include <stdint.h>
#include <stddef.h>

#include <mcuxCsslFlowProtection.h>
#include <mcuxClPkc_Types.h>
#include <mcuxClPkc_Functions.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_Initialize)
mcuxClPkc_Status_Protected_t mcuxClPkc_Initialize(mcuxClPkc_State_t *pState)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_Initialize);

    /* Clear STOP bit if it has been set. */
    uint32_t pkc_ctrl = PKC->CTRL;
    if (0u != (pkc_ctrl & PKC_CTRL_STOP_Msk))
    {
        PKC->CTRL = pkc_ctrl & (~ PKC_CTRL_STOP_Msk);

        /* Poll the STOP bit until it is cleared. */
        do
        {
            pkc_ctrl = PKC->CTRL;
        } while(0u != (pkc_ctrl & PKC_CTRL_STOP_Msk));
    }

    /* Backup PKC settings except STOP bit. */
    if (NULL != pState)
    {
        pState->ctrl = (uint16_t) pkc_ctrl;
        pState->cfg = (uint16_t) PKC->CFG;
    }

    /* Wait any on-going calculation and then set RESET bit, if RESET bit is not set. */
    if (0u == (pkc_ctrl & PKC_CTRL_RESET_Msk))
    {
        while (0u != PKC->STATUS_b.ACTIV)
        {}

        /* Set PKC RESET bit. */
        PKC->CTRL = PKC_CTRL_RESET_Msk;

        /* Poll the RESET bit until it is set. */
        while (0u == PKC->CTRL_b.RESET)
        {}
    }

    /* Configure PKC. */
    PKC->CFG =   PKC_CFG_IDLEOP_Msk
               | PKC_CFG_CLKRND_Msk
               | PKC_CFG_REDMULNOISE_Msk
               | (uint32_t) PKC_CFG_RNDDLY_NODLY;

    /* Configure PKC and clear RESET bit. */
    PKC->CTRL =   PKC_CTRL_CLRCACHE_Msk
                | PKC_CTRL_CACHE_EN_Msk
                | (uint32_t) PKC_CTRL_REDMUL_FULLSZ;

    /* Poll the RESET bit until it is cleared. */
    while (0u != PKC->CTRL_b.RESET)
    {}

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPkc_Initialize, MCUXCLPKC_STATUS_OK);
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_Deinitialize)
mcuxClPkc_Status_Protected_t mcuxClPkc_Deinitialize(const mcuxClPkc_State_t *pState)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_Deinitialize);

    /* Clear STOP bit if it has been set. */
    uint32_t pkc_ctrl = PKC->CTRL;
    if (0u != (pkc_ctrl & PKC_CTRL_STOP_Msk))
    {
        PKC->CTRL = pkc_ctrl & (~ PKC_CTRL_STOP_Msk);

        /* Poll the STOP bit until it is cleared. */
        do
        {
            pkc_ctrl = PKC->CTRL;
        } while(0u != (pkc_ctrl & PKC_CTRL_STOP_Msk));
    }

    /* Wait any on-going calculation and then set RESET bit, if RESET bit is not set. */
    if (0u == (pkc_ctrl & PKC_CTRL_RESET_Msk))
    {
        while (0u != PKC->STATUS_b.ACTIV)
        {}

        /* Set PKC RESET bit. */
        PKC->CTRL = PKC_CTRL_RESET_Msk;

        /* Poll the RESET bit until it is set. */
        while (0u == PKC->CTRL_b.RESET)
        {}
    }

    /* Clear SFRs. */
    PKC->MODE1  = 0u;
    PKC->XYPTR1 = 0u;
    PKC->ZRPTR1 = 0u;
    PKC->LEN1   = 0u;
    PKC->MODE2  = 0u;
    PKC->XYPTR2 = 0u;
    PKC->ZRPTR2 = 0u;
    PKC->LEN2   = 0u;
    PKC->UPTR   = 0u;
    PKC->UPTRT  = 0u;
    PKC->ULEN   = 0u;

    /* Restore configuration if provided, except STOP bit. */
    if (NULL != pState)
    {
        PKC->CFG  = pState->cfg;
        PKC->CTRL = pState->ctrl;
    }

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClPkc_Deinitialize, MCUXCLPKC_STATUS_OK);
}
