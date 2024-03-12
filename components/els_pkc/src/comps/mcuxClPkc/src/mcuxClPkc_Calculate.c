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
 * @file  mcuxClPkc_Calculate.c
 * @brief PKC L0(OP)/L1(MC)/L2(FUP) calculation functions
 */


#include <platform_specific_headers.h>
#include <mcuxClCore_Platform.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxCsslFlowProtection.h>

#include <mcuxClPkc_Types.h>
#include <mcuxClPkc_Functions.h>
#include <internal/mcuxClPkc_Macros.h>
#include <internal/mcuxClPkc_Operations.h>


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_Calc)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClPkc_Calc(uint16_t param_mode, uint32_t iR_iX_iY_iZ)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_Calc);

    const volatile uint16_t * pUPTRT = MCUXCLPKC_GETUPTRT();

    uint32_t iZ = 0xFFu & iR_iX_iY_iZ;
    uint32_t iY = 0xFFu & (iR_iX_iY_iZ >> 8);
    uint32_t iX = 0xFFu & (iR_iX_iY_iZ >> 16);
    uint32_t iR = 0xFFu & (iR_iX_iY_iZ >> 24);

    uint16_t offsetZ = pUPTRT[iZ];
    uint16_t offsetY = pUPTRT[iY];
    uint16_t offsetX = pUPTRT[iX];
    uint16_t offsetR = pUPTRT[iR];

    /* Pre-calculate pkc_ctrl according to:                  */
    /* L0-PS1: param_mode = 0x00xy => PKC_CTRL_GOD1_Pos = 2; */
    /* L0-PS2: param_mode = 0x40xy => PKC_CTRL_GOD2_Pos = 3; */
    /* L1-PS1: param_mode = 0x80xy => PKC_CTRL_GOM1_Pos = 4; */
    /* L1-PS2: param_mode = 0xC0xy => PKC_CTRL_GOM2_Pos = 5. */
#if (  (MCUXCLPKC_SFR_BITPOS(CTRL, GOD1) != 2) | (MCUXCLPKC_SFR_BITPOS(CTRL, GOD2) != 3) \
     | (MCUXCLPKC_SFR_BITPOS(CTRL, GOM1) != 4) | (MCUXCLPKC_SFR_BITPOS(CTRL, GOM2) != 5) )
#error update implementation according to the PKC spec
#endif
    uint32_t pkc_ctrl = MCUXCLPKC_SFR_READ(CTRL) | ((uint32_t) MCUXCLPKC_SFR_BITMSK(CTRL, GOD1) << (((uint32_t) param_mode >> 14u) & 0x3u));

    MCUXCLPKC_WAITFORREADY();

    if (0u == ((uint32_t) param_mode & ((uint32_t) MCUXCLPKC_PARAM_PS2 << 8)))
    {
        MCUXCLPKC_PS1_SETMODE(param_mode);  /* Only mode in least significant 8 bits */
        MCUXCLPKC_PS1_SETXY(offsetX, offsetY);
        MCUXCLPKC_PS1_SETZR(offsetZ, offsetR);
    }
    else
    {
        MCUXCLPKC_PS2_SETMODE(param_mode);  /* Only mode in least significant 8 bits */
        MCUXCLPKC_PS2_SETXY(offsetX, offsetY);
        MCUXCLPKC_PS2_SETZR(offsetZ, offsetR);
    }

    MCUXCLPKC_SFR_WRITE(CTRL, pkc_ctrl);
    MCUXCLPKC_PKC_BLOCK_CPU_WORKAROUND();

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClPkc_Calc);
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_CalcConst)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClPkc_CalcConst(uint16_t param_mode, uint32_t iR_iX_iY_C)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_CalcConst);

    const volatile uint16_t * pUPTRT = MCUXCLPKC_GETUPTRT();

    uint32_t C  = 0xFFu & iR_iX_iY_C;
    uint32_t iY = 0xFFu & (iR_iX_iY_C >> 8);
    uint32_t iX = 0xFFu & (iR_iX_iY_C >> 16);
    uint32_t iR = 0xFFu & (iR_iX_iY_C >> 24);

    uint16_t offsetY = pUPTRT[iY];
    uint16_t offsetX = pUPTRT[iX];
    uint16_t offsetR = pUPTRT[iR];

    uint32_t pkc_ctrl = MCUXCLPKC_SFR_READ(CTRL);

    MCUXCLPKC_WAITFORREADY();

    if (0u == ((uint32_t) param_mode & ((uint32_t) MCUXCLPKC_PARAM_PS2 << 8u)))
    {
        pkc_ctrl |= MCUXCLPKC_SFR_BITMSK(CTRL, GOD1);
        MCUXCLPKC_PS1_SETMODE(param_mode);  /* Only mode in least significant 8 bits */
        MCUXCLPKC_PS1_SETXY(offsetX, offsetY);
        MCUXCLPKC_PS1_SETZR(C, offsetR);
    }
    else
    {
        pkc_ctrl |= MCUXCLPKC_SFR_BITMSK(CTRL, GOD2);
        MCUXCLPKC_PS2_SETMODE(param_mode);  /* Only mode in least significant 8 bits */
        MCUXCLPKC_PS2_SETXY(offsetX, offsetY);
        MCUXCLPKC_PS2_SETZR(C, offsetR);
    }

    MCUXCLPKC_SFR_WRITE(CTRL, pkc_ctrl);
    MCUXCLPKC_PKC_BLOCK_CPU_WORKAROUND();

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClPkc_CalcConst);
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_CalcFup)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClPkc_CalcFup(mcuxClPkc_PtrFUPEntry_t pUPTR, uint8_t uLength)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_CalcFup);

    uint32_t pkc_ctrl = MCUXCLPKC_SFR_READ(CTRL) | MCUXCLPKC_SFR_BITMSK(CTRL, GOU) | MCUXCLPKC_SFR_BITMSK(CTRL, CLRCACHE);
    MCUXCLPKC_WAITFORREADY();

    MCUXCLPKC_SFR_WRITE(UPTR, (uint32_t) pUPTR);
    MCUXCLPKC_SFR_WRITE(ULEN, (uint32_t) uLength);

    /* Clear PKC UPTRT cache and start calculation of the FUP program. */
    MCUXCLPKC_SFR_WRITE(CTRL, pkc_ctrl);
    MCUXCLPKC_PKC_BLOCK_CPU_WORKAROUND();

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClPkc_CalcFup);
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_WaitForFinish)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClPkc_WaitForFinish(void)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_WaitForFinish);

    MCUXCLPKC_WAITFORFINISH();

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClPkc_WaitForFinish);
}


MCUX_CSSL_FP_FUNCTION_DEF(mcuxClPkc_WaitForReady)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClPkc_WaitForReady(void)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClPkc_WaitForReady);

    MCUXCLPKC_WAITFORREADY();

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClPkc_WaitForReady);
}
