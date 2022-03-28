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

/** @file  mcuxClCss_Internal.h
 *  @brief Provide macros for mcuxClCss internal use.
 * This header declares internal macros to deduplicate code and support for internal use only. */

#ifndef MCUXCLCSS_INTERNAL_H_
#define MCUXCLCSS_INTERNAL_H_

#include <platform_specific_headers.h>

/** Asserts the correctness of the supplied parameters*/
#define MCUXCLCSS_INPUT_PARAM_CHECK(x) if((x)) { return MCUXCLCSS_STATUS_SW_INVALID_PARAM; }
#define MCUXCLCSS_INPUT_PARAM_CHECK_PROTECTED(funcid, x) if((x)) { MCUX_CSSL_FP_FUNCTION_EXIT(funcid, MCUXCLCSS_STATUS_SW_INVALID_PARAM); }

#define MCUXCLCSS_REVERSEFETCH_ENABLE         ((uint32_t) 1U) ///< Reverse fetch enabled
#define MCUXCLCSS_REVERSEFETCH_DISABLE        ((uint32_t) 0U) ///< Reverse fetch disabled

#define CSS_CMD_BIG_ENDIAN ((uint8_t) 0x01U)    ///< CSS command option specifying big-endian byte order
#define CSS_CMD_LITTLE_ENDIAN ((uint8_t) 0x00U) ///< CSS command option specifying little-endian byte order

// Utility code of mcuxClCss implementation

/** Tests if the CSS is in BUSY state.
 * @retval @c true if the CSS is in BUSY state */
#define MCUXCLCSS_ISBUSY (1U == IP_CSS->CSS_STATUS_b.CSS_BUSY)

/** Sets the variable-size input buffer from which the input 0 of the CSS operation will be transferred via DMA. */
#define MCUXCLCSS_SETCSSINPUT0(pInput, inputSize)                          \
{                                                                         \
    IP_CSS->CSS_DMA_SRC0_b.ADDR_SRC0 = (uint32_t) ((uintptr_t) (pInput)); \
    IP_CSS->CSS_DMA_SRC0_LEN_b.SIZE_SRC0_LEN = (uint32_t) (inputSize);    \
}

/** Sets the fixed-size input buffer from which the input 0 of the CSS operation will be transferred via DMA. */
#define MCUXCLCSS_SETCSSINPUT0_FIXEDSIZE(pInput)                           \
{                                                                         \
    IP_CSS->CSS_DMA_SRC0_b.ADDR_SRC0 = (uint32_t) ((uintptr_t) (pInput)); \
}

/** Sets the variable-size input buffer from which the input 1 of the CSS operation will be transferred via DMA. */
#define MCUXCLCSS_SETCSSINPUT1(pInput, inputSize)                          \
{                                                                         \
    IP_CSS->CSS_DMA_SRC2_b.ADDR_SRC1 = (uint32_t) ((uintptr_t) (pInput)); \
    IP_CSS->CSS_DMA_SRC2_LEN_b.SIZE_SRC1_LEN = (uint32_t) (inputSize);    \
}

/** Sets the fixed-size input buffer from which the input 1 of the CSS operation will be transferred via DMA. */
#define MCUXCLCSS_SETCSSINPUT1_FIXEDSIZE(pInput)                           \
{                                                                         \
    IP_CSS->CSS_DMA_SRC1_b.ADDR_SRC1 = (uint32_t) ((uintptr_t) (pInput)); \
}

/** Sets the variable-size input buffer from which the input 2 of the CSS operation will be transferred via DMA. */
#define MCUXCLCSS_SETCSSINPUT2(pInput, inputSize)                          \
{                                                                         \
    IP_CSS->CSS_DMA_SRC2_b.ADDR_SRC2 = (uint32_t) ((uintptr_t) (pInput)); \
    IP_CSS->CSS_DMA_SRC2_LEN_b.SIZE_SRC2_LEN = (uint32_t) (inputSize);    \
}

/** Sets the fixed-size input buffer from which the input 2 of the CSS operation will be transferred via DMA. */
#define MCUXCLCSS_SETCSSINPUT2_FIXEDSIZE(pInput)                           \
{                                                                         \
    IP_CSS->CSS_DMA_SRC2_b.ADDR_SRC2 = (uint32_t) ((uintptr_t) (pInput)); \
}

/** Sets the variable-size output buffer to which the result of the CSS operation will be transferred via DMA. */
#define MCUXCLCSS_SETCSSOUTPUT(pOutput, outputSize)                         \
{                                                                          \
    IP_CSS->CSS_DMA_RES0_b.ADDR_RES0 = (uint32_t) ((uintptr_t) (pOutput)); \
    IP_CSS->CSS_DMA_RES0_LEN = (uint32_t) (outputSize);                    \
}

/** Sets the output buffer to which the result of the CSS operation will be transferred via DMA. */
#define MCUXCLCSS_SETCSSOUTPUT_FIXEDSIZE(pOutput)                           \
{                                                                          \
    IP_CSS->CSS_DMA_RES0_b.ADDR_RES0 = (uint32_t) ((uintptr_t) (pOutput)); \
}

/** Sets the CSS keystore index 0, for commands that access a single key. */
#define MCUXCLCSS_SETKEYSTOREINDEX0(index)          \
{                                                  \
    IP_CSS->CSS_KIDX0_b.KIDX0 = (uint8_t) (index); \
}

/** Sets the CSS keystore index 1, for commands that access 2 keys. */
#define MCUXCLCSS_SETKEYSTOREINDEX1(index)          \
{                                                  \
    IP_CSS->CSS_KIDX1_b.KIDX1 = (uint8_t) (index); \
}

#ifdef CSS_KIDX2_KIDX2_Pos
/** Sets the CSS keystore index 2, for commands that access 3 keys. */
#define MCUXCLCSS_SETKEYSTOREINDEX2(index)          \
{                                                  \
    IP_CSS->CSS_KIDX2_b.KIDX2 = (uint8_t) (index); \
}
#endif /* CSS_KIDX2_KIDX2_Pos */

/** Sets the CSS requested key properties, for commands that create a key. */
#define MCUXCLCSS_SETREQUESTEDKEYPROPERTIES(properties)       \
{                                                            \
    IP_CSS->CSS_KPROPIN_b.KPROPIN = (properties).word.value; \
}

/** Starts a CSS command. */
#define MCUXCLCSS_STARTCOMMAND(command, cmdcfg0, byteOrder)       \
{                                                                \
    IP_CSS->CSS_CMDCFG0_b.CMDCFG0 = (cmdcfg0);                   \
    uint32_t ctrl = 0U;                                          \
    ctrl |= ((uint32_t) (command)) << CSS_CTRL_CSS_CMD_Pos;      \
    ctrl |= 0x01U << CSS_CTRL_CSS_START_Pos;                     \
    ctrl |= 0x01U << CSS_CTRL_CSS_EN_Pos;                        \
    ctrl |= ((uint32_t) (byteOrder)) << CSS_CTRL_BYTE_ORDER_Pos; \
    IP_CSS->CSS_CTRL = ctrl;                                     \
}

#endif /* MCUXCLCSS_INTERNAL_H_ */
