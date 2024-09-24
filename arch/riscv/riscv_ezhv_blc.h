/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef RISCV_EZHV_BLC_H_
#define RISCV_EZHV_BLC_H_

#include "riscv_asm.h"

/*!
 * @ingroup RISCV_CoreCustomExtXzezhv
 * @defgroup RISCV_CoreCustomExtXzezhvBlc EZH-V BLC
 * @brief Boolean Logic Combiner
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @name BLC CSR registers
 * @{
 */
#define CSR_EZ_BLC_CFG  (2088U)
#define CSR_EZ_BLC_SEL  (2089U)
#define CSR_EZ_BLC_PATT (2090U)
/*!
 * @}
 */

/* BLC Macros */
#define EZHV_BLC_EN_OFFSET           (24U)
#define EZHV_BLC_OR_EN_OFFSET        (24U)
#define EZHV_BLC_CFG_WIDTH           (3U)
#define EZHV_BLC_SEL_WIDTH           (3U)
#define EZHV_BLC_EN_MASK(eIdx)       (1U << ((eIdx)+EZHV_BLC_EN_OFFSET))
#define EZHV_BLC_CFG0_MASK           (0x07U)
#define EZHV_BLC_CFGx_MASK(eIdx)     (EZHV_BLC_CFG0_MASK << ((eIdx)*EZHV_BLC_CFG_WIDTH))
#define EZHV_BLC_CFGx(eIdx, eCfg)    ((eCfg) << ((eIdx)*EZHV_BLC_CFG_WIDTH))
#define EZHV_BLC_OR_EN_MASK(eIdx)    (1U << ((eIdx)+EZHV_BLC_OR_EN_OFFSET))
#define EZHV_BLC_SEL0_MASK           (0x07U)
#define EZHV_BLC_SELx_MASK(eIdx)     (EZHV_BLC_SEL0_MASK << ((eIdx)*EZHV_BLC_SEL_WIDTH))
#define EZHV_BLC_SELx(eIdx, eSel)    ((eSel) << ((eIdx)*EZHV_BLC_SEL_WIDTH))
#define EZHV_BLC_PATT_EN_MASK        (1U << 0)
#define EZHV_BLC_PATT_CSEL_OFFSET    (1U)
#define EZHV_BLC_PATT_CSEL_MASK      (0x7U << EZHV_BLC_PATT_CSEL_OFFSET)
#define EZHV_BLC_PATT_DSEL_OFFSET    (4U)
#define EZHV_BLC_PATT_DSEL_MASK      (0x7U << EZHV_BLC_PATT_DSEL_OFFSET)
#define EZHV_BLC_PATT_VAL_OFFSET     (8U)
#define EZHV_BLC_PATT_VAL_MASK       (0xFFU << EZHV_BLC_PATT_VAL_OFFSET)
#define EZHV_BLC_PATT_VBASE_OFFSET   (16U)
#define EZHV_BLC_PATT_VBASE_MASK     (0xFFFFU << EZHV_BLC_PATT_VBASE_OFFSET)

/*!@brief LIST of BLC Slices */
typedef enum _ezhv_blc_idx
{
    kBLC_IDX_0 = 0,     /*!< Bit Slice 0 */
    kBLC_IDX_1 = 1,     /*!< Bit Slice 1 */
    kBLC_IDX_2 = 2,     /*!< Bit Slice 2 */
    kBLC_IDX_3 = 3,     /*!< Bit Slice 3 */
    kBLC_IDX_4 = 4,     /*!< Bit Slice 4 */
    kBLC_IDX_5 = 5,     /*!< Bit Slice 5 */
    kBLC_IDX_6 = 6,     /*!< Bit Slice 6 */
    kBLC_IDX_7 = 7,     /*!< Bit Slice 7 */
    kBLC_SLICE_NUM = 8, /*!< number of BLC slices */
} ezhv_blc_idx_t;

/*!@brief List of BLC Slice's CFG MUX inputs */
typedef enum _ez_blc_mux_cfg
{
    kBLC_CFG_LOGIC_HIGH     = 0, /*!< 000 - Logic 1 always */
    kBLC_CFG_RISING_EDGE    = 1, /*!< 001 - Rising edge detect */
    kBLC_CFG_FALLING_EDGE   = 2, /*!< 010 - Falling edge detect */
    kBLC_CFG_BOTH_EDGE      = 3, /*!< 011 - Edge detect */
    kBLC_CFG_TRANSPARENT    = 4, /*!< 100 - Transparent (pass-through, non-sticky) */
    kBLC_CFG_NOT            = 5, /*!< 101 - NOT */
    kBLC_CFG_LOGIC_LOW      = 6, /*!< 110 - Logic 0 always */
    kBLC_CFG_TRANSIENT_EDGE = 7, /*!< 111 - Transient edge (non-sticky) */
    kBLC_CFG_NUM            = 8,
} ezhv_blc_cfg_t;

/*!@brief List of BLC Slice's Sel Mux inputs */
typedef enum _ez_blc_in_sel
{
    kBLC_SEL_INPUT_0 = 0,      /*!< select input 0 */
    kBLC_SEL_INPUT_1 = 1,      /*!< select input 1 */
    kBLC_SEL_INPUT_2 = 2,      /*!< select input 2 */
    kBLC_SEL_INPUT_3 = 3,      /*!< select input 3 */
    kBLC_SEL_INPUT_4 = 4,      /*!< select input 4 */
    kBLC_SEL_INPUT_5 = 5,      /*!< select input 5 */
    kBLC_SEL_INPUT_6 = 6,      /*!< select input 6 */
    kBLC_SEL_INPUT_7 = 7,      /*!< select input 7 */
    kBLC_SEL_NUM     = 8,      /*!< sel num */
} ezhv_blc_sel_t;

/*!
 * @brief Select input data signal to capture for pattern match.
 *        the data signal is one bit, input from BLC_IN signals
 */
typedef ezhv_blc_sel_t ezhv_blc_dsel_t;

/*!@brief Select input signal for capture enable/clock.
 * the clock signal is one bit, input from BLC_IN signals
 * */
typedef ezhv_blc_sel_t ezhv_blc_csel_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief set BLC cfg register CSR_EZ_BLC_CFG
 *
 * @param mask    bits to set
 */
static inline void EZHV_SetBlcCfg(uint32_t mask)
{
    csr_set(CSR_EZ_BLC_CFG, mask);
}

/*!
 * @brief clear BLC cfg register CSR_EZ_BLC_CFG
 *
 * @param mask    bits to clear
 */
static inline void EZHV_ClrBlcCfg(uint32_t mask)
{
    csr_clear(CSR_EZ_BLC_CFG, mask);
}

/*!
 * @brief write BLC cfg Register CSR_EZ_BLC_CFG
 *
 * @param regVal    the register value to write
 */
static inline void EZHV_WriteBlcCfg(uint32_t regVal)
{
    csr_write(CSR_EZ_BLC_CFG, regVal);
}

/*!
 * @brief read the value of Blc Cfg register CSR_EZ_BLC_CFG
 *
 * @return the register value of ez_blc_cfg
 */
static inline uint32_t EZHV_ReadBlcCfg(void)
{
    return (uint32_t)csr_read(CSR_EZ_BLC_CFG);
}

/*!
 * @brief set BLC sel register CSR_EZ_BLC_SEL
 *
 * @param mask    bits to set
 */
static inline void EZHV_SetBlcSel(uint32_t mask)
{
    csr_set(CSR_EZ_BLC_SEL, mask);
}

/*!
 * @brief clear given bits of BLC Sel register CSR_EZ_BLC_SEL
 *
 * @param mask    bits to clear
 */
static inline void EZHV_ClrBlcSel(uint32_t mask)
{
    csr_clear(CSR_EZ_BLC_SEL, mask);
}

/*!
 * @brief write BLC Sel register CSR_EZ_BLC_SEL
 *
 * @param regVal value to over write
 */
static inline void EZHV_WriteBlcSel(uint32_t regVal)
{
    csr_write(CSR_EZ_BLC_SEL, regVal);
}

/*!
 * @brief read the value of BLC SEL register CSR_EZ_BLC_SEL
 *
 * @return the register value of ez_blc_sel
 */
static inline uint32_t EZHV_ReadBlcSel(void)
{
    return (uint32_t)csr_read(CSR_EZ_BLC_SEL);
}

/*!
 * @brief Set BLC patt register CSR_EZ_BLC_PATT
 *
 * @param mask     bits to set
 */
static inline void EZHV_SetBlcPatt(uint32_t mask)
{
    csr_set(CSR_EZ_BLC_PATT, mask);
}

/*!
 * @brief clear BLC patt register CSR_EZ_BLC_PATT
 *
 * @param mask    bits to clear
 */
static inline void EZHV_ClrBlcPatt(uint32_t mask)
{
    csr_clear(CSR_EZ_BLC_PATT, mask);
}


/*!
 * @brief API to write BLC patt register CSR_EZ_BLC_PATT
 *
 * @param value    the value to be written into CSR_EZ_BLC_PATT
 */
static inline void EZHV_WriteBlcPatt(uint32_t value)
{
    csr_write(CSR_EZ_BLC_PATT, value);
}

/*!
 * @brief read the value of BLC patt register CSR_EZ_BLC_PATT
 *
 * @return the register value of ez_blc_patt
 */
static inline uint32_t EZHV_ReadBlcPatt(void)
{
    return (uint32_t)csr_read(CSR_EZ_BLC_PATT);
}

/*!
 * @brief enable BLC slice N
 *
 * @param eIdx    given blc slice to enable, refer to enum::ezhv_blc_idx_t
 * @param eCfg    cfg for cfg mux, refer to enum::ezhv_blc_cfg_t
 * @param eSel    sel for input sel mux, refer to enum::ezhv_blc_sel_t
 */
static inline void EZHV_EnableBlc(ezhv_blc_idx_t eIdx, ezhv_blc_cfg_t eCfg, ezhv_blc_sel_t eSel)
{
    /* Disable before configure. */
    csr_clear(CSR_EZ_BLC_CFG, EZHV_BLC_CFGx_MASK(eIdx) | EZHV_BLC_EN_MASK(eIdx));

    /* To set the ez_blc_sel (CSR_EZ_BLC_SEL) register  */
    csr_clear(CSR_EZ_BLC_SEL, EZHV_BLC_SELx_MASK(eIdx));
    csr_set(CSR_EZ_BLC_SEL, EZHV_BLC_SELx(eIdx, eSel));

    /* To set the ez_blc_cfg (CSR_EZ_BLC_CFG) register */
    csr_set(CSR_EZ_BLC_CFG, EZHV_BLC_CFGx(eIdx, eCfg) | EZHV_BLC_EN_MASK(eIdx));
}

/*!
 * @brief disable BLC slice N
 *
 * @param eIdx    given slice to disable
 */
static inline void EZHV_DisableBlc(ezhv_blc_idx_t eIdx)
{
    EZHV_ClrBlcCfg(EZHV_BLC_EN_MASK(eIdx));
}

/*!
 * @brief enable BLC SliceN event, should be called after EZHV_EnableBlc()
 *
 * @param eIdx    given slice event to enable
 */
static inline void EZHV_EnableBlcEvent(ezhv_blc_idx_t eIdx)
{
    EZHV_SetBlcSel(EZHV_BLC_OR_EN_MASK(eIdx));
}

/*!
 * @brief disable the event of BLC slice eIdx
 *
 * @param eIdx    given blc slice event to disable
 */
static inline void EZHV_DisableBlcEvent(ezhv_blc_idx_t eIdx)
{
    EZHV_ClrBlcSel(EZHV_BLC_OR_EN_MASK(eIdx));
}

/*!
 * @brief enable BLC compare pattern feature, which should be called after EZHV_EnableBlc()
 *
 * @param dSel    select input signal to capture for pattern match
 * @param cSel    select input signal for capture enable/clock.
 * @param pattern    value used to be compared with
 */
static inline void EZHV_EnableBlcPatternMatch(ezhv_blc_dsel_t dSel, ezhv_blc_csel_t cSel, uint8_t pattern)
{
    /* Diable first before configure. */
    csr_clear(CSR_EZ_BLC_PATT, EZHV_BLC_PATT_VAL_MASK | EZHV_BLC_PATT_DSEL_MASK | EZHV_BLC_PATT_CSEL_MASK | EZHV_BLC_PATT_EN_MASK);

    /* {PATT | DSEL | CSEL | EN} */
    csr_set(CSR_EZ_BLC_PATT,
                        (pattern << EZHV_BLC_PATT_VAL_OFFSET) |
                        (dSel<<EZHV_BLC_PATT_DSEL_OFFSET)  |
                        (cSel<<EZHV_BLC_PATT_CSEL_OFFSET)  |
                        EZHV_BLC_PATT_EN_MASK);
}

/*!
 * @brief disable BLC compare pattern match function
 */
static inline void EZHV_DisableBlcPatternMatch(void)
{
    /* clear bit PATT EN bit */
    EZHV_ClrBlcPatt(EZHV_BLC_PATT_EN_MASK);
}

/*!
 * @brief write vbase address
 *
 * @param addr    VBASE address, used to set the upper 16
 *                bits of vector address when VIE=0
 */
static inline void EZHV_WriteBlcPtternVbase(uint32_t addr)
{
    csr_clear(CSR_EZ_BLC_PATT, EZHV_BLC_PATT_VBASE_MASK);
    csr_set(CSR_EZ_BLC_PATT, EZHV_BLC_PATT_VBASE_MASK & addr);
}

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif
