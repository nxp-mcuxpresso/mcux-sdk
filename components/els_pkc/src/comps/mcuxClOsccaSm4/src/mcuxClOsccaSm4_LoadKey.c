/*--------------------------------------------------------------------------*/
/* Copyright 2014-2019, 2021-2024 NXP                                       */
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
/* Security Classification:  Company Confidential                           */
/*--------------------------------------------------------------------------*/

/**
 *
 * @file: mcuxClOsccaSm4_LoadKey.c
 * @brief: Implementation of OSCCA SM4 Load Key functionality.
 *
 */

#include <mcuxClMemory.h>
#include <mcuxClOscca_Memory.h>
#include <internal/mcuxClOsccaSm4_Internal.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>

#ifdef MCUXCL_FEATURE_HW_SAFO_SM4
#include <mcuxClOsccaSafo.h>
#endif

#ifdef MCUXCL_FEATURE_HW_SAFO_SM4
#else
/**
* \brief The constant parameter CK.
*/
static const uint32_t
gmcuxClOsccaSm4_CK[] = {
    0x00070e15U, 0x1c232a31U, 0x383f464dU, 0x545b6269U,
    0x70777e85U, 0x8c939aa1U, 0xa8afb6bdU, 0xc4cbd2d9U,
    0xe0e7eef5U, 0xfc030a11U, 0x181f262dU, 0x343b4249U,
    0x50575e65U, 0x6c737a81U, 0x888f969dU, 0xa4abb2b9U,
    0xc0c7ced5U, 0xdce3eaf1U, 0xf8ff060dU, 0x141b2229U,
    0x30373e45U, 0x4c535a61U, 0x686f767dU, 0x848b9299U,
    0xa0a7aeb5U, 0xbcc3cad1U, 0xd8dfe6edU, 0xf4fb0209U,
    0x10171e25U, 0x2c333a41U, 0x484f565dU, 0x646b7279U
};

/**
 * \brief The system parameter FK.
 */
static const uint32_t
gmcuxClOsccaSm4_FK[] = {
    0xA3B1BAC6U,
    0x56AA3350U,
    0x677D9197U,
    0xB27022DCU
};

/**
 * \brief The Linear substitution function for the key expansion algorithm
 *
 * \returns 32-bit output word
 *
 * \param [IN] B 32-bit input word to be transformed
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm4_Lprime)
static inline MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) mcuxClOsccaSm4_Lprime(uint32_t B)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm4_Lprime);
    uint32_t Lprime = (B ^ MCUXCLOSCCASM4_ROTATE_LEFT_UINT32(B, 13U)^ MCUXCLOSCCASM4_ROTATE_LEFT_UINT32(B, 23U));
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm4_Lprime, Lprime);
}

/**
 * \brief The Mixer-substitution function for the key expansion algorithm
 *
 * \returns 32-bit output word
 *
 * \param [IN] X 32-bit input word to be transformed
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm4_Tprime)
static inline MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) mcuxClOsccaSm4_Tprime(uint32_t X)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm4_Tprime, MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm4_Lprime),
                                                      MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm4_Tau));
    MCUX_CSSL_FP_FUNCTION_CALL(Tprime_Tau, mcuxClOsccaSm4_Tau(X));
    MCUX_CSSL_FP_FUNCTION_CALL(Tprime_L, mcuxClOsccaSm4_Lprime(Tprime_Tau));
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm4_Tprime, Tprime_L);
}
#endif

#ifdef MCUXCL_FEATURE_HW_SAFO_SM4
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm4_ScheduleKey)
static MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm4_ScheduleKey(
    uint32_t *pRoundKeys, uint8_t const *pMKey, uint32_t direction)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm4_ScheduleKey);

    /* For SGI implementation, just copy master key to round key */
    MCUXCLMEMORY_FP_MEMORY_COPY((uint8_t *)pRoundKeys, pMKey, MCUXCLOSCCASM4_BLOCK_SIZE);

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaSm4_ScheduleKey,
                                   MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy));
}

#else

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm4_ScheduleKey)
static MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm4_ScheduleKey(
    uint32_t *pRoundKeys, uint8_t const *pMKey, uint32_t direction)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm4_ScheduleKey);

    uint32_t pKey[4];
    MCUXCLMEMORY_FP_MEMORY_COPY((uint8_t *)pKey, pMKey, MCUXCLOSCCASM4_BLOCK_SIZE);
    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOscca_switch_endianness(pKey, MCUXCLOSCCASM4_BLOCK_SIZE));

    /* The actual derivation process pt. I */
    uint32_t K[4] =
    {
        pKey[3] ^ gmcuxClOsccaSm4_FK[0],
        pKey[2] ^ gmcuxClOsccaSm4_FK[1],
        pKey[1] ^ gmcuxClOsccaSm4_FK[2],
        pKey[0] ^ gmcuxClOsccaSm4_FK[3]
    };

    /* The actual derivation process pt. II */
    for(uint8_t i = 0U; i < MCUXCLOSCCASM4_RK_WORDS; ++i)
    {
        MCUX_CSSL_FP_FUNCTION_CALL(Tprime_output, mcuxClOsccaSm4_Tprime(K[(i + 1U) % 4U] ^ K[(i + 2U) % 4U] ^ K[(i + 3U) % 4U] ^ gmcuxClOsccaSm4_CK[i]));
        K[(i + 4U) % 4U] = K[i % 4U] ^ Tprime_output;
        if (MCUXCLOSCCASM4_ENCRYPT == direction)
        {
            pRoundKeys[i] = K[(i + 4U) % 4U];
        }
        else
        {
            pRoundKeys[MCUXCLOSCCASM4_RK_WORDS - 1U - i] =  K[(i + 4U) % 4U];
        }
    }

    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaSm4_ScheduleKey,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy),
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOscca_switch_endianness),
        MCUXCLOSCCASM4_RK_WORDS * MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm4_Tprime));
}
#endif

/**
 * \brief The Load Key internal (core) functionality
 *
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm4_ScheduleSM4Key)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClOsccaSm4_Status_t) mcuxClOsccaSm4_ScheduleSM4Key(
    uint32_t *pRoundKeys, uint8_t const *pMKey, uint32_t direction)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm4_ScheduleSM4Key);

    MCUX_CSSL_FP_FUNCTION_CALL_VOID(mcuxClOsccaSm4_ScheduleKey(pRoundKeys, pMKey, direction));

    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaSm4_ScheduleSM4Key, MCUXCLOSCCASM4_STATUS_LOADKEY_OK,
        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaSm4_ScheduleKey));
}
