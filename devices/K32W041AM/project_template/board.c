/*
 * Copyright  2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "fsl_clock.h"
#include "board.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
#if (defined TCXO_32M_MODE_EN) && (TCXO_32M_MODE_EN != 0)
/* Table of load capacitance versus temperature for 32MHz crystal. Values below
   are for NDK NX2016SA 32MHz EXS00A-CS11213-6(IEC). Values are for temperatures
   from -40 to +130 in steps of 5 */
#if OLD_XTAL32M_CAL
int32_t CLOCK_ai32MXtalIecLoadPfVsTemp_x1000[HW_32M_LOAD_VS_TEMP_SIZE] =
{  537,   714,   837,   909,   935,   922,   873,   796, /* -40, -35, ... -5 */
   694,   574,   440,   297,   149,     0,  -147,  -290, /* 0, 5, ... 35 */
  -425,  -551,  -667,  -770,  -860,  -936,  -998, -1042, /* 40, 45, ... 75 */
 -1069, -1076, -1061, -1019,  -947,  -837,  -682,  -472, /* 80, 85, ... 115 */
  -196,   161,   618                                     /* 120, 125, 130 */
};
#else
int32_t CLOCK_ai32MXtalIecLoadPfVsTemp_x1000[HW_32M_LOAD_VS_TEMP_SIZE] =
{  506,   687,   818,   900,   938,   933,   892,   819, /* -40, -35, ... -5 */
   720,   599,   461,   313,   158,     0,  -156,  -307, /* 0, 5, ... 35 */
  -451,  -584,  -705,  -812,  -903,  -977, -1032, -1067, /* 40, 45, ... 75 */
 -1079, -1067, -1025,  -950,  -835,  -673,  -453,  -163, /* 80, 85, ... 115 */
   212,   691,  1296                                     /* 120, 125, 130 */
};
#endif
#endif

#if (defined TCXO_32k_MODE_EN) && (TCXO_32k_MODE_EN != 0)
/* Table of load capacitance versus temperature for 32kHz crystal. Values are
   for temperatures from -40 to +130 in steps of 5. *Note* values below are
   just for example */
#ifdef OLD_XTAL32K_CAL
int32_t CLOCK_ai32kXtalIecLoadPfVsTemp_x1000[HW_32k_LOAD_VS_TEMP_SIZE] =
{-1843, -1583, -1351, -1138,  -939,  -752,  -579,  -422, /* -40, -35, ... -5 */
  -285,  -170,   -81,   -22,     5,     0,   -38,  -107, /* 0, 5, ... 35 */
  -205,  -330,  -478,  -645,  -830, -1031, -1247, -1482, /* 40, 45, ... 75 */
 -1742, -2078, -2409, -2766, -3147, -3554, -3995, -4442, /* 80, 85, ... 115 */
 -4923, -5430, -5961};                                   /* 120, 125, 130 */
#else
int32_t CLOCK_ai32kXtalIecLoadPfVsTemp_x1000[HW_32k_LOAD_VS_TEMP_SIZE] =
{-1984, -1728, -1496, -1278, -1070,  -870,  -680,  -504, /* -40, -35, ... -5 */
  -347,  -214,  -109,   -37,     0,     0,   -37,  -111, /* 0, 5, ... 35 */
  -218,  -356,  -521,  -709,  -917, -1143, -1388, -1656, /* 40, 45, ... 75 */
 -1957, -2293, -2657, -3048, -3467, -3913, -4386, -4887, /* 80, 85, ... 115 */
 -5416, -5971, -6555};                                   /* 120, 125, 130 */
#endif

#endif
/*******************************************************************************
 * Local Prototypes
 ******************************************************************************/

/*****************************************************************************
 * Local functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Initialize debug console. */
status_t BOARD_InitDebugConsole(void)
{
    status_t result;

    uint32_t uartClkSrcFreq = BOARD_DEBUG_UART_CLK_FREQ;

    result =
        DbgConsole_Init(BOARD_DEBUG_UART_INSTANCE, BOARD_DEBUG_UART_BAUDRATE, BOARD_DEBUG_UART_TYPE, uartClkSrcFreq);

#ifndef RTL_SIMU_ON_ES2
    CLOCK_uDelay(500);
#endif

    return result;
}

/* Dummy functions, added to enable LowPower module to link */
void BOARD_DbgDiagEnable(void)
{
}
void BOARD_DbgLpIoSet(int pinid, int val)
{
    (void)(pinid);
    (void)(val);
}
