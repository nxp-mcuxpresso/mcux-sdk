/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file kw45b41zevk.c
 * @brief The kw45b41zevk.c file defines GPIO pins and CMSIS utilities for
 * kw45b41zevk board.
 */

#include "kw45b41zevk.h"

#define LPI2C_MASTER_CLOCK           (kCLOCK_Lpi2c1)
#define LPI2C_MASTER_CLOCK_FREQUENCY (CLOCK_GetIpFreq(LPI2C_MASTER_CLOCK))

#define LPSPI_MASTER_CLOCK            (kCLOCK_Lpspi0)
#define LPSPI_MASTER_CLOCK_FREQUENCY  (CLOCK_GetIpFreq(LPSPI_MASTER_CLOCK))

#define LPUART_MASTER_CLOCK           (kCLOCK_Lpuart1)
#define LPUART_MASTER_CLOCK_FREQUENCY (CLOCK_GetIpFreq(LPUART_MASTER_CLOCK))

/* Get frequency of lpi2c clock */
#define LPI2C_CLOCK_FREQUENCY (CLOCK_GetRootClockFreq(kCLOCK_Root_Lpi2c0102))
/* Get frequency of lpspi clock */
#define LPSPI_CLOCK_FREQUENCY (CLOCK_GetRootClockFreq(kCLOCK_Root_Lpspi0304))
/* Get frequency of lpspi clock */
#define LPUART_CLOCK_FREQUENCY (CLOCK_GetRootClockFreq(kCLOCK_Root_Lpuart0102))

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by
 * fsl_uart_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t LPUART1_GetFreq(void)
{
	/*Clock setting for LPUART*/
    CLOCK_SetIpSrc(LPUART_MASTER_CLOCK, kCLOCK_IpSrcFro6M);
    return LPUART_MASTER_CLOCK_FREQUENCY;
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by
 * fsl_i2c_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t LPI2C1_GetFreq(void)
{
	/*Clock setting for LPI2C*/
    CLOCK_SetIpSrc(LPI2C_MASTER_CLOCK, kCLOCK_IpSrcFro192M);
    CLOCK_SetIpSrcDiv(LPI2C_MASTER_CLOCK, kSCG_SysClkDivBy16);
    return LPI2C_MASTER_CLOCK_FREQUENCY;
}

/*! @brief       Determines the Clock Frequency feature.
 *  @details     The Clock Frequecny computation API required by
 * fsl_spi_cmsis.c.
 *  @param[in]   void
 *  @Constraints None
 *  @Reentrant   Yes
 *  @return      uint32_t Returns the clock frequency .
 */
uint32_t LPSPI0_GetFreq(void)
{
    /* Set clock source for LPSPI slave and get the clock source */
    CLOCK_SetIpSrc(LPSPI_MASTER_CLOCK, kCLOCK_IpSrcFro192M);
    CLOCK_SetIpSrcDiv(LPSPI_MASTER_CLOCK, kSCG_SysClkDivBy16);
    return LPSPI_MASTER_CLOCK_FREQUENCY;
}
