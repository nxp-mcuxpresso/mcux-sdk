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
 * @file  mcuxClOsccaPkc.c
 * @brief mcuxClOsccaPkc: implementation of PKC functions
 */

#include <platform_specific_headers.h>
#include <stdint.h>
#include <mcuxClOsccaPkc.h>
#include <mcuxClMemory.h>
#include <internal/mcuxClOsccaPkc_Macros.h>
#include <internal/mcuxClOsccaPkc_Operations.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslSecureCounter.h>
#include <mcuxClOscca_FunctionIdentifiers.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaPkc_Init) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaPkc_Init(
        mcuxClOsccaPkc_State_t   *state
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaPkc_Init);
#define PKC_CTRL_DEFAULT_SETUP ( /* Reset and Clear Errors are excluded */ \
        ( (uint32_t)0U << MCUXCLOSCCAPKC_SFR_BITPOS(CTRL, STOP)) |    \
        ( (uint32_t)0U << MCUXCLOSCCAPKC_SFR_BITPOS(CTRL, GF2CONV)) | \
        ( (uint32_t)0U << MCUXCLOSCCAPKC_SFR_BITPOS(CTRL, REDMUL))    \
        )
#define PKC_CFG_DEFAULT_SETUP (  \
        ( 1U << MCUXCLOSCCAPKC_SFR_BITPOS(CFG, IDLEOP) ) | \
        ( 1U << MCUXCLOSCCAPKC_SFR_BITPOS(CFG, CLKRND) ) | \
        ( 1U << MCUXCLOSCCAPKC_SFR_BITPOS(CFG, REDMULNOISE) ) | \
        ( 0U << MCUXCLOSCCAPKC_SFR_BITPOS(CFG, RNDDLY) )            /* no delay */ \
        )

    /* clear STOP bit */
    MCUXCLOSCCAPKC_SFR_BITCLEAR(CTRL, STOP);
    while( 0U != MCUXCLOSCCAPKC_SFR_BITREAD(CTRL, STOP) )
    {
        /* wait */
    }

    /* read current state */
    if(state != NULL)
    {
        state->cfg    = MCUXCLOSCCAPKC_SFR_READ(CFG);
        state->ctrl   = MCUXCLOSCCAPKC_SFR_READ(CTRL);
    }

    /* set reset bit */
    MCUXCLOSCCAPKC_SFR_BITSET(CTRL, RESET);
    while( 0U == MCUXCLOSCCAPKC_SFR_BITREAD(CTRL, RESET) )
    {
        /* wait */
    }

    /* clear the error */
    MCUXCLOSCCAPKC_SFR_WRITE(ACCESS_ERR_CLR, 1U);
    /* configure Pkc */
    /* MISRA Ex. 22, while(0) is allowed */
    MCUXCLOSCCAPKC_SFR_WRITE(CTRL,
        ( (uint32_t)1U << MCUXCLOSCCAPKC_SFR_BITPOS(CTRL, RESET) ) |
        ( (uint32_t)1U << MCUXCLOSCCAPKC_SFR_BITPOS(CTRL, CACHE_EN) ) |
        ( (uint32_t)1U << MCUXCLOSCCAPKC_SFR_BITPOS(CTRL, CLRCACHE) ) |
        PKC_CTRL_DEFAULT_SETUP );

    MCUXCLOSCCAPKC_SFR_WRITE(CFG, PKC_CFG_DEFAULT_SETUP);

    /* clear reset bit */
    MCUXCLOSCCAPKC_SFR_BITCLEAR(CTRL, RESET);
    while( 0U != MCUXCLOSCCAPKC_SFR_BITREAD(CTRL, RESET) )
    {
        /* wait */
    }

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaPkc_Init);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaPkc_Reset) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(void)   mcuxClOsccaPkc_Reset(
        mcuxClOsccaPkc_State_t   *state    /**< pointer to state as returned by mcuxClOsccaPkc_Init */
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaPkc_Reset);
    /* clear STOP bit */
    MCUXCLOSCCAPKC_SFR_BITCLEAR(CTRL, STOP);
    while( 0U != MCUXCLOSCCAPKC_SFR_BITREAD(CTRL, STOP) )
    {
        /* wait */
    }

    /* sets reset bit and clear status implicitly */
    MCUXCLOSCCAPKC_SFR_BITSET(CTRL, RESET);
    while( 0U == MCUXCLOSCCAPKC_SFR_BITREAD(CTRL, RESET) )
    {
        /* wait */
    }

    /* clears all mode, ptr and len registers */
    MCUXCLOSCCAPKC_SFR_WRITE(MODE1,  0u);
    MCUXCLOSCCAPKC_SFR_WRITE(MODE2,  0u);
    MCUXCLOSCCAPKC_SFR_WRITE(XYPTR1, 0u);
    MCUXCLOSCCAPKC_SFR_WRITE(XYPTR2, 0u);
    MCUXCLOSCCAPKC_SFR_WRITE(ZRPTR1, 0u);
    MCUXCLOSCCAPKC_SFR_WRITE(ZRPTR2, 0u);
    MCUXCLOSCCAPKC_SFR_WRITE(LEN1,   0u);
    MCUXCLOSCCAPKC_SFR_WRITE(LEN2,   0u);
    MCUXCLOSCCAPKC_SFR_WRITE(UPTRT,  0u);
    MCUXCLOSCCAPKC_SFR_WRITE(ULEN,   0u);

    /* restores old CFG and CTRL states (including reset) */
    if(NULL != state)
    {
        MCUXCLOSCCAPKC_SFR_WRITE(CFG, state->cfg);
        MCUXCLOSCCAPKC_SFR_WRITE(CTRL, state->ctrl);
    }

    /* clear reset bit, because of possible STOP bit */
    MCUXCLOSCCAPKC_SFR_BITCLEAR(CTRL, RESET);
    while( 0U != MCUXCLOSCCAPKC_SFR_BITREAD(CTRL, RESET) )
    {
        /* wait */
    }
    /* update SC and return */
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaPkc_Reset);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaPkc_GetWordSize) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) mcuxClOsccaPkc_GetWordSize(void)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaPkc_GetWordSize);
    uint32_t redmul;

    redmul = MCUXCLOSCCAPKC_GETREDMUL();
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaPkc_GetWordSize, (uint32_t)(redmul > 0U ? (uint32_t)2U << redmul : (uint32_t)16U));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaPkc_SetWordSize) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaPkc_SetWordSize(uint32_t redmul)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaPkc_SetWordSize);
    MCUXCLOSCCAPKC_SETWORDSIZE(redmul);
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaPkc_SetWordSize);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaPkc_WaitforFinish) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaPkc_WaitforFinish(void)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaPkc_WaitforFinish);
    MCUXCLOSCCAPKC_WAITFORFINISH();
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaPkc_WaitforFinish);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaPkc_SetFupTable) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaPkc_SetFupTable(void *pUPTRT)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaPkc_SetFupTable);
    MCUXCLOSCCAPKC_WAITFORGOANY();
    /* MISRA Ex.2 - Rule 11.6 */
    MCUXCLOSCCAPKC_SETUPTRT(pUPTRT);
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaPkc_SetFupTable);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaPkc_Op) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaPkc_Op(uint32_t mode, uint32_t iRiXiYiZ)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaPkc_Op);
    uint32_t iR, iX, iY, iZ;
    uint32_t mode0, mode1;
    uint16_t pR, pX, pY, pZ;
    uint16_t *pUPTR = (uint16_t*)MCUXCLOSCCAPKC_GETUPTRT();

    iR = (iRiXiYiZ >> 24U) & 0xFFU;
    iX = (iRiXiYiZ >> 16U) & 0xFFU;
    iY = (iRiXiYiZ >> 8U) & 0xFFU;
    iZ = (iRiXiYiZ) & 0xFFU;

    mode0 = (mode >> 8U) & 0xFFU;
    mode1 = (mode) & 0xFFU;

    pR = pUPTR[iR];
    pX = pUPTR[iX];
    pY = pUPTR[iY];
    if (MCUXCLOSCCAPKC_FUP_OP_ZFIX == (mode0 & MCUXCLOSCCAPKC_FUP_OP_ZFIX))
    {
        pZ = (uint16_t)iZ;
    }
    else
    {
        pZ = pUPTR[iZ];
    }

    MCUXCLOSCCAPKC_WAITFORGOANY();

    if (MCUXCLOSCCAPKC_FUP_PS2 == (mode0 & MCUXCLOSCCAPKC_FUP_PS2))
    {
        //Fill PS2 registers
        MCUXCLOSCCAPKC_OPERANDS2(pX, pY, pZ, pR);
        MCUXCLOSCCAPKC_MODE2(mode1);

        if (MCUXCLOSCCAPKC_FUP_MC == (mode0 & MCUXCLOSCCAPKC_FUP_MC))
        {
            //Start layer MC
            MCUXCLOSCCAPKC_PS2_L1_START();
        }
        else
        {
            //Start layer OP
            MCUXCLOSCCAPKC_PS2_L0_START();
        }
    }
    else
    {
        //Fill PS1 registers
        MCUXCLOSCCAPKC_OPERANDS1(pX, pY, pZ, pR);
        MCUXCLOSCCAPKC_MODE1(mode1);

        if (MCUXCLOSCCAPKC_FUP_MC == (mode0 & MCUXCLOSCCAPKC_FUP_MC))
        {
            //Start layer MC
            MCUXCLOSCCAPKC_PS1_L1_START();
        }
        else
        {
            //Start layer OP
            MCUXCLOSCCAPKC_PS1_L0_START();
        }
    }

    /* update SC and return */
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaPkc_Op);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaPkc_GeneratePointerTable) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaPkc_GeneratePointerTable(uint16_t *pOperandsBase,
                    uint8_t *pBufferBase,
                    uint32_t bufferSize,
                    uint32_t bufferNums)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaPkc_GeneratePointerTable);
    uint32_t i;

    for (i = 0U; i < bufferNums; i++)
    {
        pOperandsBase[i] =
        MCUXCLOSCCAPKC_PTRTOPKCOFFSET(pBufferBase + i * bufferSize);
    }

    /* update SC and return */
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaPkc_GeneratePointerTable);
}

/*
 * be careful, this function will corrupt the buffer behind operand iT
 * because of the MAC_Const
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaPkc_ComputeNDash) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaPkc_ComputeNDash(uint32_t iNiTiXiX)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaPkc_ComputeNDash, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_GetWordSize),
                                                           MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear));
    uint32_t NdashWordSizeByte;
    uint32_t NdashWordSizeBit;
    uint16_t *pUPTRT;
    uint8_t *pN, *pTmp, *pNDash;
    uint32_t iN, iT;

    iN = (iNiTiXiX >> 24U) & 0xffU;
    iT = (iNiTiXiX >> 16U) & 0xffU;

    MCUX_CSSL_FP_FUNCTION_CALL(NdashByte,mcuxClOsccaPkc_GetWordSize());
    NdashWordSizeByte = NdashByte;
    NdashWordSizeBit = NdashWordSizeByte*8U;

    pUPTRT = MCUXCLOSCCAPKC_GETUPTRT();
    pN = MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pUPTRT[iN]);
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_ARRAY_OUT_OF_BOUNDS("pN is allocated such that pNDash is in front of it, as required by the PKC")
    pNDash = pN - NdashWordSizeByte;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_ARRAY_OUT_OF_BOUNDS()
    pTmp = MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pUPTRT[iT]);

    MCUXCLMEMORY_FP_MEMORY_CLEAR(pNDash, NdashWordSizeByte);

    *pNDash = 1U;

    MCUXCLOSCCAPKC_WAITFORFINISH();
    MCUXCLOSCCAPKC_PS2_SETLENGTH(0u, NdashWordSizeByte);

    /* R = (-X)^(-1)  (mod 2^i)  ==>  R*X + 1 = 0 (mod 2^i) */
    /* (RX + 1)^2 = 0 (mod 2^(2i))                          */
    /* (RX + 2)R * X + 1 = 0 (mod 2^(2i))                   */

    MCUXCLOSCCAPKC_OPERANDX2(pNDash);

    uint32_t i = 1U;
    while(NdashWordSizeBit > i)
    {
        /* T := R * X + 2 */
        MCUXCLOSCCAPKC_WAITFORGOANY();
        MCUXCLOSCCAPKC_OPERANDY2(pN);
        MCUXCLOSCCAPKC_OPERANDZ2(0x0002U);
        MCUXCLOSCCAPKC_OPERANDR2(pTmp);
        MCUXCLOSCCAPKC_MODE2(0x12U);    /* 0x12 MAC_CONST, R := X[0] * Y + CONST */    /* lenT = lenY + 2FW (= 3 FW here) */
        MCUXCLOSCCAPKC_PS2_L0_START();

        /* T := R * T = (RX + 2) * R */
        MCUXCLOSCCAPKC_WAITFORGOANY();
        MCUXCLOSCCAPKC_OPERANDY2(pTmp);
        MCUXCLOSCCAPKC_MODE2(0x00U);    /* 0x00 MUL, R := X[0] * Y */
        MCUXCLOSCCAPKC_PS2_L0_START();

        /* R := T */
        MCUXCLOSCCAPKC_WAITFORGOANY();
        MCUXCLOSCCAPKC_OPERANDZ2(0x0000U);
        MCUXCLOSCCAPKC_OPERANDR2(pNDash);
        MCUXCLOSCCAPKC_MODE2(0x1eU);    /* 0x1e OR_CONST, R := Y OR CONST||CONST||...||CONST */
        MCUXCLOSCCAPKC_PS2_L0_START();

        i <<= 1;
    }

    /* update SC and return */
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaPkc_ComputeNDash);
}

/*
 * Count leading zeros of non-zero value.
 * If the value is 0, the result is undefined.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaPkc_CountLeadingZerosWord)
static inline MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) mcuxClOsccaPkc_CountLeadingZerosWord(uint32_t value)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaPkc_CountLeadingZerosWord);
#ifdef __CLZ
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaPkc_CountLeadingZerosWord, __CLZ(value));
#else
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaPkc_CountLeadingZerosWord, (uint32_t)__builtin_clz(value));
#endif
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaPkc_LeadingZeros) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) mcuxClOsccaPkc_LeadingZeros(uint8_t *pNum, uint32_t numLen)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaPkc_LeadingZeros);
    uint32_t zeros = 0U;
    uint32_t temp;
    uint32_t numLenByWord = numLen / (sizeof(uint32_t)) ;
    /* MISRA Ex.24 - Rule 11.3 */
    uint32_t *pBigNum = (uint32_t *)pNum;
    uint32_t loopTimes = 0U;

    while(numLenByWord > 0U)
    {
        temp = pBigNum[numLenByWord - 1U];
        if (0U == temp)
        {
            zeros += sizeof(uint32_t) * 8U;
        }
        else
        {
            loopTimes++;
            MCUX_CSSL_FP_FUNCTION_CALL(zeroWords, mcuxClOsccaPkc_CountLeadingZerosWord(temp));
            zeros += zeroWords;
            break;
        }
        numLenByWord--;
    }

    /* update SC and return */
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaPkc_LeadingZeros, zeros, loopTimes * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_CountLeadingZerosWord));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaPkc_MultipleShiftRotate_Index) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaPkc_MultipleShiftRotate_Index(uint32_t iModuluss, uint32_t iModulus,
                        uint32_t leadingZeroBits, _Bool shiftLeft)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaPkc_MultipleShiftRotate_Index, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_GetWordSize));
    uint32_t pkcWordSizeByte;
    uint32_t pkcWordSizeBit;
    uint32_t shiftBits;
    uint32_t shiftTimes = 0u;

    MCUX_CSSL_FP_FUNCTION_CALL(NdashByte,mcuxClOsccaPkc_GetWordSize());
    pkcWordSizeByte = NdashByte;
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("pkcWordSizeByte * 8U cannot overflow.")
    pkcWordSizeBit = pkcWordSizeByte * 8U;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()

    MCUXCLOSCCAPKC_FXIOP1_OR_YC(iModuluss, iModulus, 0);
    while(leadingZeroBits > 0U)
    {
        if (leadingZeroBits >= pkcWordSizeBit)
        {
            shiftBits = pkcWordSizeBit - 1U;
        }
        else
        {
            shiftBits = leadingZeroBits;
        }

        if (shiftLeft)
        {
            MCUXCLOSCCAPKC_FXIOP1_SHL_YC(iModuluss, iModuluss, shiftBits);
        }
        else
        {
            MCUXCLOSCCAPKC_FXIOP1_SHR_YC(iModuluss, iModuluss, shiftBits);
        }
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("leadingZeroBits cannot be less than shiftBits.")
        leadingZeroBits -= shiftBits;
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
        MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("The size of shiftTimes is big enough, it cannot overflow.")
        shiftTimes++;
        MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
    }
    /* update SC and return */
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaPkc_MultipleShiftRotate_Index, ((shiftTimes + 1u) * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op)));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaPkc_ComputeQSquared) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaPkc_ComputeQSquared(uint32_t iQiMiTiX, uint16_t iMs)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaPkc_ComputeQSquared);
    uint32_t j = 0U;
    bool msb_found = false;
    uint32_t opByteLen;
    uint32_t exponent, expBitLen;
    uint32_t iQ, iM, iT, iX;

    iQ = (iQiMiTiX >> 24U) & 0xffU;
    iM = (iQiMiTiX >> 16U) & 0xffU;
    iT = (iQiMiTiX >> 8U) & 0xffU;
    iX = (iQiMiTiX) & 0xffU;

    opByteLen = MCUXCLOSCCAPKC_PS1_GETOPLEN();

    /* 1 in MR */
    MCUXCLOSCCAPKC_FXIOP1_NEG(iT, iM);
    /* 2 in MR */
    MCUXCLOSCCAPKC_FXIMC1_MADD(iX, iT, iT, iMs);

    MCUXCLOSCCAPKC_FXIOP1_OR_YC(iQ, iX, 0);

    exponent = opByteLen * 8U;
    expBitLen = sizeof(exponent) * 8U - 1U;
    j = expBitLen;
    uint32_t loopTimes = 0U;
    do
    {
        if (((exponent & ((uint32_t)1U << j)) == 0U) && (msb_found == false))
        {
            continue;
        }
        else if (msb_found == false)
        {
            /* ignore the msb, because we have get 2 by MADD */
            msb_found = true;
        }
        else
        {
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("The size of loopTimes is big enough, it cannot overflow.")
            loopTimes++;
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
            /* square */
            MCUXCLOSCCAPKC_FXIMC1_MMUL(iT, iQ, iQ, iM);
            if (0U != (exponent & ((uint32_t)1U << j)))
            {
                /* mutliply */
                MCUXCLOSCCAPKC_FXIMC1_MMUL(iQ, iT, iX, iM);
            }
            else
            {
                MCUXCLOSCCAPKC_FXIOP1_OR_YC(iQ, iT, 0U);
            }

        }
    }while ((j--) != 0U);

    /* update SC and return */
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaPkc_ComputeQSquared, ((3U + loopTimes * 2U) * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op)));
}

/* note: iR is R in MR, output iI is R's inverse in MR */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaPkc_ComputeModInv) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaPkc_ComputeModInv(uint32_t iRiIiNiT, uint32_t iT2)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaPkc_ComputeModInv);
    uint32_t i, j, loopTimes = 0U, loopTimes1 = 0U;
    bool msb_found = false;
    uint32_t iR, iI, iN, iT;
    uint16_t *pOperands;
    uint16_t *pExp;
    uint32_t operandSize = MCUXCLOSCCAPKC_PS1_GETOPLEN();


    iR = (iRiIiNiT >> 24U) & 0xffU;
    iI = (iRiIiNiT >> 16U) & 0xffU;
    iN = (iRiIiNiT >> 8U) & 0xffU;
    iT = iRiIiNiT & 0xffU;

    pOperands = MCUXCLOSCCAPKC_GETUPTRT();
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("Reinterpret pointer type to uint16_t* types.")
    pExp = (uint16_t *)MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[iT2]);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()

    /* the initial value is 1 in MR */
    MCUXCLOSCCAPKC_FXIOP1_NEG(iT, iN);

    MCUXCLOSCCAPKC_FXIOP1_SUB_YC(iT2, iN, 2U);
    MCUXCLOSCCAPKC_WAITFORFINISH();
    i = (operandSize >> 1U) - 1U;

    do
    {
        j = 15U;
        do
        {
            if ((0U == (pExp[i] & ((uint16_t)1U << j))) && (false == msb_found))
            {
                continue;
            }
            else
            {
                msb_found = true;
            }

            /* square */
            MCUXCLOSCCAPKC_FXIMC1_MMUL(iI, iT, iT, iN);
            MCUXCLOSCCAPKC_FXIOP1_OR_YC(iT, iI, 0);

            if(0U != (pExp[i] & ((uint16_t)1U << j)))
            {
                loopTimes1++;
                /* multiply */
                MCUXCLOSCCAPKC_FXIMC1_MMUL(iI, iR, iT, iN);
                MCUXCLOSCCAPKC_FXIOP1_OR_YC(iT, iI, 0);
            }
            else
            {
                // Do nothing, just balance to avoid misra violation.
            }
            MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("The size of loopTimes is big enough, it cannot overflow.")
            loopTimes++;
            MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
        }while ((j--) != 0U);
    }while ((i--) != 0U);

    /* update SC and return */
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaPkc_ComputeModInv,((loopTimes * 2U + loopTimes1 * 2U + 2U) * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op)));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaPkc_CalcMontInverse) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaPkc_CalcMontInverse(uint32_t iIiRiNiT, uint32_t R2)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaPkc_CalcMontInverse);
    uint32_t iN, iI, iT, iR;
    uint32_t exponent, shiftBits;
    uint32_t len = MCUXCLOSCCAPKC_PS1_GETOPLEN();
    MCUX_CSSL_FP_FUNCTION_CALL(pkcWordSize, mcuxClOsccaPkc_GetWordSize());
    uint16_t *pOperands = MCUXCLOSCCAPKC_GETUPTRT();

    iI = (iIiRiNiT >> 24U) & 0xFFU;
    iR = (iIiRiNiT >> 16U) & 0xFFU;
    iN = (iIiRiNiT >> 8U) & 0xFFU;
    iT = (iIiRiNiT) & 0xFFU;

    /* set PS1 Lens to (len + pkcWordSize, len + pkcWordSize) */
    MCUXCLOSCCAPKC_WAITFORGOANY();
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_OVERFLOW("len is PKC operand length, len + pkcWordSize cannot overflow.")
    MCUXCLOSCCAPKC_PS1_SETLENGTH(len + pkcWordSize, len + pkcWordSize);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_OVERFLOW()
    /* set T := 0, with extra pkcWordSize (len + pkcWordSize) */
    MCUXCLOSCCAPKC_FXIOP1_AND_YC(iT, iT, 0x00U);

    /* set R := T + 1 = 1 */
    MCUXCLOSCCAPKC_FXIOP1_ADD_YC(iR, iT, 0x01U);

    /* set the loop counter LC = 31, for almostMontgomeryInverse */
    MCUXCLOSCCAPKC_WAITFORGOANY();
    MCUXCLOSCCAPKC_PS1_SETLENGTH(31, len);

    if(pkcWordSize > 16u)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaPkc_CalcMontInverse);
    }
    if((pOperands[iT] + pkcWordSize) > ((uint16_t) - 1))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaPkc_CalcMontInverse);
    }
    pOperands[iT] = pOperands[iT] + (uint16_t)pkcWordSize;
    /* perform almostMontgomeryInverse using MC code */
    /* T (upper part) = almostMontgomeryInverse(X) = - X^(-1) * 2^exp */
    /* T (lower fWord) = exp */
    MCUXCLOSCCAPKC_FXIMC1_MONTINV(iT, iN, iI, iR);
    /* save the result of almostMontgomeryInverse to iI */
    MCUXCLOSCCAPKC_FXIOP1_OR_YC(iI, iT, 0x00U);
    MCUXCLOSCCAPKC_WAITFORFINISH();

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY("PKC operand buffers are 32 bit aligned.")
    exponent = *(volatile uint32_t *)MCUXCLOSCCAPKC_PKCOFFSETTOPTR((uint32_t)pOperands[iT] - pkcWordSize);
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY()

    /* recover the modulus */
    MCUXCLOSCCAPKC_FXIOP1_OR_YC(iN, iR, 0x00U); /* N = R = n, because N*R = n and N = gcd(i,n) = 1. */

    pOperands[iT] = pOperands[iT] - (uint16_t)pkcWordSize;
    MCUXCLOSCCAPKC_FXIOP1_XOR(iT, iT, iT);
    MCUXCLOSCCAPKC_PS1_SETLENGTH(len, len);
    if (exponent <= len * 8U)
    {
        shiftBits = len * 8U - exponent;
        *MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[iT] + (shiftBits >> 3U)) |= (1U << (shiftBits & 7U));
        MCUXCLOSCCAPKC_FXIMC1_MMUL(iR, iI, iT, iN);
        MCUXCLOSCCAPKC_FXIMC1_MSUB(iI, iN, iR, iN);
        MCUXCLOSCCAPKC_FXIMC1_MMUL(iR, iI, R2, iN);
    }
    else
    {
        if(2U * len * 8U < exponent)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaPkc_CalcMontInverse);
        }
        shiftBits = 2U * len * 8U - exponent;
        *MCUXCLOSCCAPKC_PKCOFFSETTOPTR(pOperands[iT] + (shiftBits >> 3U)) |= (1U << (shiftBits & 7U));
        MCUXCLOSCCAPKC_FXIMC1_MMUL(iR, iI, iT, iN);
        MCUXCLOSCCAPKC_FXIMC1_MSUB(iR, iN, iR, iN);
    }

    /* update SC and return */
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaPkc_CalcMontInverse, 8U * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op),
                                                                  MCUX_CSSL_FP_CONDITIONAL((exponent <= len * 8U), MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_Op)),
                                                                  MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaPkc_GetWordSize));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaPkc_StartFupProgram) /* No semicolon */
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaPkc_StartFupProgram(mcuxClOsccaPkc_PtrFUPEntry_t fupProgram,
                        uint32_t fupProgramSize)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaPkc_StartFupProgram);
    MCUXCLOSCCAPKC_WAITFORFINISH();
    uint32_t pkc_ctrl = MCUXCLOSCCAPKC_SFR_READ(CTRL) | MCUXCLOSCCAPKC_SFR_BITMSK(CTRL, GOU) | MCUXCLOSCCAPKC_SFR_BITMSK(CTRL, CLRCACHE);
    MCUXCLOSCCAPKC_SFR_WRITE(ULEN, fupProgramSize);
    /* MISRA Ex.2 - Rule 11.6 */
    MCUXCLOSCCAPKC_SFR_WRITE(UPTR, (uint32_t)fupProgram);
    /* Clear PKC UPTRT cache and start calculation of the FUP program. */
    MCUXCLOSCCAPKC_SFR_WRITE(CTRL, pkc_ctrl);

    /* update SC and return */
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaPkc_StartFupProgram);
}
