/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdlib.h>
#include "fsl_debug_console.h"
#include "fsl_kpp.h"

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_KPP_ACTIVE_COLUMROWS  (0xF0)
#define EXAMPLE_KPP_MATRX_NUM         (4)
#define EXAMPLE_KPP_COLROW_START_INDX (4)
#define EXAMPLE_KPP                   KPP
#define EXAMPLE_KPP_KEYPRESS_LONG_NUM (0xFFF)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*******************************************************************************
 * Variables
 ******************************************************************************/
char *keyMap[EXAMPLE_KPP_MATRX_NUM][EXAMPLE_KPP_MATRX_NUM] = {
    /* COL0    COL1    COL2    COL3   */
    {"SW1", "SW2", "SW3", "SW4"},     /* ROW0 */
    {"SW5", "SW6", "SW7", "SW8"},     /* ROW1 */
    {"SW9", "SW10", "SW11", "SW12"},  /* ROW2 */
    {"SW13", "SW14", "SW15", "SW16"}, /* ROW3 */
};
kpp_config_t kppConfig;
uint8_t read_keys[KPP_KEYPAD_COLUMNNUM_MAX] = {0};
extern char *keyMap[EXAMPLE_KPP_MATRX_NUM][EXAMPLE_KPP_MATRX_NUM];
volatile bool g_keypress   = false;
volatile bool g_keyrelease = false;
/*******************************************************************************
 * Code
 ******************************************************************************/
void KPP_IRQHandler(void)
{
    uint16_t status = KPP_GetStatusFlag(EXAMPLE_KPP);
    if (status & kKPP_keyDepressInterrupt)
    {
        /* Disable interrupts. */
        KPP_DisableInterrupts(EXAMPLE_KPP, kKPP_keyDepressInterrupt);
        /* Scanning. */
        KPP_keyPressScanning(EXAMPLE_KPP, &read_keys[0], CLOCK_GetFreq(kCLOCK_CpuClk));
        /* Clear status. */
        KPP_ClearStatusFlag(EXAMPLE_KPP, kKPP_keyDepressInterrupt);
        KPP_SetSynchronizeChain(EXAMPLE_KPP, kKPP_ClearKeyDepressSyncChain);
        /* Enable interrupts. */
        KPP_EnableInterrupts(EXAMPLE_KPP, kKPP_keyDepressInterrupt);
        g_keypress = true;
    }
    else if (status & kKPP_keyReleaseInterrupt)
    {
        /* Disable interrupts. */
        KPP_DisableInterrupts(EXAMPLE_KPP, kKPP_keyReleaseInterrupt);
        /* Clear status. */
        KPP_ClearStatusFlag(EXAMPLE_KPP, kKPP_keyReleaseInterrupt);
        KPP_SetSynchronizeChain(EXAMPLE_KPP, kKPP_SetKeyReleasesSyncChain);
        g_keyrelease = true;
    }
    SDK_ISR_EXIT_BARRIER;
}

int main(void)
{
    kpp_config_t kppConfig;
    uint8_t rowOld = 0xFF;
    uint8_t colOld = 0xFF;
    uint32_t index = 0;

    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\n KPP Driver Example Start.\r\n");

    kppConfig.activeColumn = kppConfig.activeRow = EXAMPLE_KPP_ACTIVE_COLUMROWS;
    kppConfig.interrupt                          = (kKPP_keyDepressInterrupt | kKPP_keyReleaseInterrupt);

    KPP_Init(EXAMPLE_KPP, &kppConfig);

    while (1)
    {
        if (g_keypress)
        {
            /* Scanning and print the triggered key log out.*/
            for (uint32_t col = 0; col < EXAMPLE_KPP_MATRX_NUM; col++)
            {
                if ((read_keys[col + EXAMPLE_KPP_COLROW_START_INDX] & EXAMPLE_KPP_ACTIVE_COLUMROWS) != 0x00)
                {
                    for (uint8_t row = 0; row < EXAMPLE_KPP_MATRX_NUM; row++)
                    {
                        if ((read_keys[col + EXAMPLE_KPP_COLROW_START_INDX] &
                             (1 << (row + EXAMPLE_KPP_COLROW_START_INDX))) != 0)
                        {
                            if (((rowOld != row) || (colOld != col)) && g_keypress)
                            {
                                rowOld = row;
                                colOld = col;
                                PRINTF("\r\n Key %s was pressed.\r\n", keyMap[rowOld][colOld]);
                            }
                            else
                            {
                                index++;
                                if (index > EXAMPLE_KPP_KEYPRESS_LONG_NUM)
                                {
                                    index = 0;
                                    PRINTF("\r\n This was a long press.\r\n");
                                }
                            }
                        }
                    }
                }
            }
            KPP_EnableInterrupts(EXAMPLE_KPP, kKPP_keyReleaseInterrupt);
            g_keypress = false;
        }
        else if (g_keyrelease)
        {
            rowOld       = 0xFF;
            colOld       = 0xFF;
            index        = 0;
            g_keyrelease = false;
        }
    }
}
