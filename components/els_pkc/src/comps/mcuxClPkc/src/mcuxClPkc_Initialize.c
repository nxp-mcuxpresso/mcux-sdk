/*--------------------------------------------------------------------------*/
/* Copyright 2014-2023 NXP                                                  */
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
#include <mcuxClCore_Platform.h>
#include <mcuxCsslAnalysis.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClPkc_Types.h>
#include <mcuxClPkc_Functions.h>
#include <internal/mcuxClPkc_Macros.h>




/**
 * [Design]
 * This function initializes PKC hardware in the following steps:
 * (1) if PKC is in STOP, clear STOP bit according to PKC specification;
 * (2) backup PKC state (except STOP bit) if required (pState != NULL);
 * (3) if PKC is not in RESET, wait any on-going calculation;
 * (4) initialize and set PKC according to PKC specification.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_Initialize, mcuxClPkc_PkcInitializeEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClPkc_Initialize(mcuxClPkc_State_t *pState)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_Initialize);

    /* Clear STOP bit if it has been set. */
    uint32_t pkc_ctrl = MCUXCLPKC_SFR_READ(CTRL);
    if (0u != (pkc_ctrl & MCUXCLPKC_SFR_BITMSK(CTRL, STOP)))
    {
        MCUXCLPKC_SFR_WRITE(CTRL, pkc_ctrl & (~ MCUXCLPKC_SFR_BITMSK(CTRL, STOP)));

        /* Poll the STOP bit until it is cleared. */
        do
        {
            pkc_ctrl = MCUXCLPKC_SFR_READ(CTRL);
        } while(0u != (pkc_ctrl & MCUXCLPKC_SFR_BITMSK(CTRL, STOP)));
    }

    /* Backup PKC settings except STOP bit. */
    if (NULL != pState)
    {
        pState->ctrl = (uint16_t) pkc_ctrl;
        pState->cfg = (uint16_t) MCUXCLPKC_SFR_READ(CFG);
    }

    /* Wait any on-going calculation and then set RESET bit, if RESET bit is not set. */
    if (0u == (pkc_ctrl & MCUXCLPKC_SFR_BITMSK(CTRL, RESET)))
    {
        MCUXCLPKC_WAITFORFINISH();

        /* Set PKC RESET bit. */
        MCUXCLPKC_SFR_WRITE(CTRL, MCUXCLPKC_SFR_BITMSK(CTRL, RESET));

        /* Poll the RESET bit until it is set. */
        while (0u == (MCUXCLPKC_SFR_BITREAD(CTRL, RESET)))
        {}
    }

    /* Configure PKC. */
    const uint32_t pkcCfg =   MCUXCLPKC_SFR_BITMSK(CFG, IDLEOP)
                            | MCUXCLPKC_SFR_BITMSK(CFG, CLKRND)
                            | MCUXCLPKC_SFR_BITMSK(CFG, REDMULNOISE)
                            | MCUXCLPKC_SFR_CFG_RNDDLY_NODLY;

    MCUXCLPKC_SFR_WRITE(CFG, pkcCfg);


    /* Configure PKC and clear RESET bit. */
    MCUXCLPKC_SFR_WRITE(CTRL,   MCUXCLPKC_SFR_BITMSK(CTRL, CLRCACHE)
                             | MCUXCLPKC_SFR_BITMSK(CTRL, CACHE_EN)
                             | MCUXCLPKC_SFR_CTRL_REDMUL_FULLSZ );

    /* Poll the RESET bit until it is cleared. */
    while (0u != (MCUXCLPKC_SFR_BITREAD(CTRL, RESET)))
    {}

    /* Poll the PW_READY bit until it is set, on supported platforms. */
    MCUXCLPKC_PKC_WAIT_PW_READY();

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClPkc_Initialize);
}


/**
 * [Design]
 * This function deinitializes PKC hardware in the following steps:
 * (1) if PKC is in STOP, clear STOP bit according to PKC specification;
 * (2) if PKC is not in RESET, wait any on-going calculation, and then set PKC RESET bit;
 * (3) clear PKC SFRs;
 * (4) restore PKC state (except STOP bit) if it is provided (pState != NULL).
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_Deinitialize, mcuxClPkc_PkcDeInitializeEngine_t)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClPkc_Deinitialize(const mcuxClPkc_State_t *pState)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_Deinitialize);

    /* Clear STOP bit if it has been set. */
    uint32_t pkc_ctrl = MCUXCLPKC_SFR_READ(CTRL);
    if (0u != (pkc_ctrl & MCUXCLPKC_SFR_BITMSK(CTRL, STOP)))
    {
        MCUXCLPKC_SFR_WRITE(CTRL, pkc_ctrl & (~ MCUXCLPKC_SFR_BITMSK(CTRL, STOP)));

        /* Poll the STOP bit until it is cleared. */
        do
        {
            pkc_ctrl = MCUXCLPKC_SFR_READ(CTRL);
        } while(0u != (pkc_ctrl & MCUXCLPKC_SFR_BITMSK(CTRL, STOP)));
    }

    /* Wait any on-going calculation and then set RESET bit, if RESET bit is not set. */
    if (0u == (pkc_ctrl & MCUXCLPKC_SFR_BITMSK(CTRL, RESET)))
    {
        MCUXCLPKC_WAITFORFINISH();

        /* Set PKC RESET bit. */
        MCUXCLPKC_SFR_WRITE(CTRL, MCUXCLPKC_SFR_BITMSK(CTRL, RESET));

        /* Poll the RESET bit until it is set. */
        while (0u == (MCUXCLPKC_SFR_BITREAD(CTRL, RESET)))
        {}
    }

    /* Clear SFRs. */
    MCUXCLPKC_SFR_WRITE(MODE1,  0u);
    MCUXCLPKC_SFR_WRITE(XYPTR1, 0u);
    MCUXCLPKC_SFR_WRITE(ZRPTR1, 0u);
    MCUXCLPKC_SFR_WRITE(LEN1,   0u);
    MCUXCLPKC_SFR_WRITE(MODE2,  0u);
    MCUXCLPKC_SFR_WRITE(XYPTR2, 0u);
    MCUXCLPKC_SFR_WRITE(ZRPTR2, 0u);
    MCUXCLPKC_SFR_WRITE(LEN2,   0u);
    MCUXCLPKC_SFR_WRITE(UPTR,   0u);
    MCUXCLPKC_SFR_WRITE(UPTRT,  0u);
    MCUXCLPKC_SFR_WRITE(ULEN,   0u);

    /* Restore configuration if provided, except STOP bit. */
    if (NULL != pState)
    {
        MCUXCLPKC_SFR_WRITE(CFG,  (uint32_t) pState->cfg);
        MCUXCLPKC_SFR_WRITE(CTRL, (uint32_t) pState->ctrl);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClPkc_Deinitialize);
}
