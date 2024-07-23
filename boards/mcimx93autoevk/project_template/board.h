/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "clock_config.h"
#if defined(BOARD_USE_PCAL6524) && BOARD_USE_PCAL6524
#include "fsl_pcal6524.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* The UART to use for debug messages. */
#define BOARD_DEBUG_UART_INSTANCE   2U
#define BOARD_DEBUG_UART_BAUDRATE   115200U
#define BOARD_DEBUG_UART_TYPE       kSerialPort_Uart
#define BOARD_DEBUG_UART_CLOCK_ROOT kCLOCK_Root_Lpuart2
#define BOARD_DEBUG_UART_CLOCK_GATE kCLOCK_Lpuart2
#define BOARD_DEBUG_UART_CLK_FREQ   CLOCK_GetIpFreq(BOARD_DEBUG_UART_CLOCK_ROOT)

#define VDEV0_VRING_BASE (0xA4000000U)
#define VDEV1_VRING_BASE (0xA4010000U)

#define LED_INIT()
#define LED_TOGGLE()

#define BOARD_CODEC_I2C_BASEADDR LPI2C1
#define BOARD_CODEC_I2C_INSTANCE 1U

/* PCAL6524 */
#define BOARD_PCAL6524_I2C            LPI2C2
#define BOARD_PCAL6524_I2C_CLOCK_ROOT kCLOCK_Root_Lpi2c2
#define BOARD_PCAL6524_I2C_CLOCK_GATE kCLOCK_Lpi2c2
#define BOARD_PCAL6524_I2C_CLOCK_FREQ CLOCK_GetIpFreq(BOARD_PCAL6524_I2C_CLOCK_ROOT)

/* PCAL6524 IO Expander A */
#define BOARD_PCAL6524_A_I2C_ADDR     (0x22U)
#define BOARD_PCAL6524_A_EXT1_PWREN   (8U + 5U)
#define BOARD_PCAL6524_A_ENET1_NRST   (8U + 7U)
#define BOARD_PCAL6524_A_ENET2_NRST   (16U + 0U)

/* PCAL6524 IO Expander B */
#define BOARD_PCAL6524_B_I2C_ADDR     (0x20U)
#define BOARD_PCAL6524_B_CAN_MQS_SEL  (2U)
#define BOARD_PCAL6524_B_EXP_SEL      (3U)
#define BOARD_PCAL6524_B_CAN1_SW_WAKE (8U + 0U)
#define BOARD_PCAL6524_B_CAN2_SW_WAKE (8U + 1U)
#define BOARD_PCAL6524_B_CAN1_STBY_B  (8U + 2U)
#define BOARD_PCAL6524_B_CAN2_STBY_B  (8U + 3U)
#define BOARD_PCAL6524_B_CAN1_EN      (8U + 4U)
#define BOARD_PCAL6524_B_CAN2_EN      (8U + 5U)

/* SEMA42 */
#define APP_SEMA42       SEMA42_1
#define APP_SEMA42_GATE  (0x3U)
#define M33_DOMAIN_ID    (0x8U)
#define APP_CORTEX_M_DID M33_DOMAIN_ID

#define BIT(n)         (1U << (n))
#define W32(addr, val) *((volatile uint32_t *)(addr)) = (val)
#define R32(addr)      *((volatile uint32_t *)(addr))

#define SETBIT32(addr, set)           W32(addr, R32(addr) | set)
#define CLRBIT32(addr, clear)         W32(addr, R32(addr) & ~clear)
#define CLRSETBIT32(addr, clear, set) W32(addr, (R32(addr) & ~clear) | set)

/*  SRC GPR1 as M33 active status flag, A55 will read the value before enter suspend mode */
#define M33_ACTIVE_FLAG (SRC_GENERAL_REG_BASE + 0x54)
#define M33_ACTIVE      (0x5555U)
#define M33_INACTIVE    (0x0U)

/*
 * SRC GPR2 bit 0 as A55 DDR status flag, bit 1 as M33 DDR status flag.
 * A55 will set GPR2 bit1 when it will enter suspend, and clear it before wakeup.
 */
#define DDR_RETENTION_BASE     (SRC_GENERAL_REG_BASE + 0x58)
#define DDR_RETENTION_A55_FLAG BIT(0)
#define DDR_RETENTION_M33_FLAG BIT(1)

#define DRAM_APB_CLK (0x44452680U)

/* DDR configure addres saved by A55 atf */
#define SAVED_DRAM_DATA_BASE_ADDR (0x2051C000)

/* DDR */
#define DDRPHY_BASE_ADDR               (0x4E100000U)
#define DDR_PHY_BASE                   DDRPHY_BASE_ADDR
#define IP2APB_DDRPHY_IPS_BASE_ADDR(X) (DDR_PHY_BASE + (X * 0x2000000))
#define DDR_DEBUG_26                   (0xF64U)
#define DDR_SDRAM_CFG_ADDR             (0x4E300110)

/* Default DDR DSR_2 Idel check time permanently */
#define DDRC_DDRDSR_2_Check_Idel_time (0x0U)

/* DDR PHY Addr remap table number */
#define DDRPHY_NB_ADDR_REMAP (0x6FU)

#define DDRC_STOP_ACK_SET_MASK  (0x0U)
#define DDRC_STOP_ACK_POLL_MASK (0x1U)

#define dwc_ddrphy_apb_wr(addr, data) W32(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + BOARD_DDRPHY_Addr_Remap(addr), data)
#define dwc_ddrphy_apb_rd(addr)       R32(IP2APB_DDRPHY_IPS_BASE_ADDR(0) + BOARD_DDRPHY_Addr_Remap(addr))

struct dram_cfg_param
{
    uint32_t reg;
    uint32_t val;
};

struct dram_fsp_cfg
{
    struct dram_cfg_param ddrc_cfg[20];
    struct dram_cfg_param mr_cfg[10];
    unsigned int bypass;
};

/*
 * ATF init DDR setting and save DDR register to SAVED_DRAM_DATA_BASE_ADDR.
 * Acore run in 64 bit system, Mcore run in 32 bit system. So, add reserved area in dram_timing_info to protect the data
 * from being matched correctly data match.
 */
struct dram_timing_info
{
    /* umctl2 config */
    struct dram_cfg_param *ddrc_cfg;
    const uint32_t reserved_ddrc_cfg;
    unsigned int ddrc_cfg_num;
    const uint32_t reserved_ddrc_cfg_num;
    /* fsp config */
    struct dram_fsp_cfg *fsp_cfg;
    const uint32_t reserved_fsp_cfg;
    unsigned int fsp_cfg_num;
    const uint32_t reserved_fsp_cfg_num;
    /* ddrphy config */
    struct dram_cfg_param *ddrphy_cfg;
    const uint32_t reserved_ddrphy_cfg;
    unsigned int ddrphy_cfg_num;
    const uint32_t reserved_ddrphy_cfg_num;
    /* ddr fsp train info */
    struct dram_fsp_msg *fsp_msg;
    const uint32_t reserved_fsp_msg;
    unsigned int fsp_msg_num;
    const uint32_t reserved_fsp_msg_num;
    /* ddr phy trained CSR */
    struct dram_cfg_param *ddrphy_trained_csr;
    const uint32_t reserved_ddrphy_trained_csr;
    unsigned int ddrphy_trained_csr_num;
    const uint32_t reserved_ddrphy_trained_csr_num;
    /* ddr phy PIE */
    struct dram_cfg_param *ddrphy_pie;
    const uint32_t reserved_ddrphy_pie;
    unsigned int ddrphy_pie_num;
    const uint32_t reserved_ddrphy_pie_num;
    /* initialized fsp table */
    unsigned int fsp_table[4];
};

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
extern struct dram_timing_info *timing_info;
/*******************************************************************************
 * API
 ******************************************************************************/

void BOARD_InitDebugConsole(void);
#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
status_t BOARD_LPI2C_Send(LPI2C_Type *base,
                          uint8_t deviceAddress,
                          uint32_t subAddress,
                          uint8_t subaddressSize,
                          uint8_t *txBuff,
                          uint8_t txBuffSize,
                          uint32_t flags);
status_t BOARD_LPI2C_Receive(LPI2C_Type *base,
                             uint8_t deviceAddress,
                             uint32_t subAddress,
                             uint8_t subaddressSize,
                             uint8_t *rxBuff,
                             uint8_t rxBuffSize,
                             uint32_t flags);
#if defined(BOARD_USE_PCAL6524) && BOARD_USE_PCAL6524
void BOARD_PCAL6524_I2C_Init(void);
status_t BOARD_PCAL6524_I2C_Send(uint8_t deviceAddress,
                                 uint32_t subAddress,
                                 uint8_t subAddressSize,
                                 const uint8_t *txBuff,
                                 uint8_t txBuffSize,
                                 uint32_t flags);
status_t BOARD_PCAL6524_I2C_Receive(uint8_t deviceAddress,
                                    uint32_t subAddress,
                                    uint8_t subAddressSize,
                                    uint8_t *rxBuff,
                                    uint8_t rxBuffSize,
                                    uint32_t flags);

void BOARD_InitPCAL6524_A(pcal6524_handle_t *handle);
void BOARD_InitPCAL6524_B(pcal6524_handle_t *handle);
#endif /* BOARD_USE_PCAL6524 */

#endif

/* Mcore suspend setting */
#define OSCPLL_LPM_START 3U
#define OSCPLL_LPM_END   12U
/* SysTick Control and Status Register(SYST_CSR) of cortex-M33 */
#define SYSTICK_CTRL_REG (*((volatile uint32_t *)0xe000e010))
/*
 * SYST_CSR[0] ENABLE(Enable counter):
 * 0: Counter Disabled
 * 1: Counter Enabled
 * SYST_CSR[1] TICKINT(Enables SysTick exception request):
 * 0: Counting down to zero does not assert the SysTick exception request.
 * 1: Counting down to zero asserts the SysTick exception request.
 * More info from
 * https://developer.arm.com/documentation/100235/0004/the-cortex-m33-peripherals/system-timer--systick/systick-control-and-status-register
 */
#define SYSTICK_CLOSE 0U
void BOARD_McoreSUSPEND(void);

void BOARD_ConfigMPU(void);

#if defined(BOARD_USE_DDR_RETENTION) && BOARD_USE_DDR_RETENTION
/* DDR enter retention state */
void BOARD_DRAMEnterRetention(void);

/* DDR exit retention state */
void BOARD_DRAMExitRetention(void);
#endif

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* _BOARD_H_ */
