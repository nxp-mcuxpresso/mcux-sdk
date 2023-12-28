/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "clock_config.h"
#include "fsl_clock.h"
#include "fsl_rgpio.h"
#if defined(BOARD_USE_PCA6416A) && BOARD_USE_PCA6416A
#include "fsl_pca6416a.h"
#endif
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define PFD_VALID_MASK (0x40404040U)
#ifndef BIT
#define BIT(n) (1U << (n))
#endif
#define MHZ(X) ((X)*1000000UL)

/* SoC variable type */
#define MPU_SOC_IMX8ULP   0xA1 /* dummy ID, full feature, iMX8ULP Dual core 7D/7C */
#define MPU_SOC_IMX8ULPD5 0xA2 /* dummy ID, iMX8ULP Dual core 5D/5C, EPDC disabled */
#define MPU_SOC_IMX8ULPS5 0xA3 /* dummy ID, iMX8ULP Single core 5D/5C, EPDC disabled */
#define MPU_SOC_IMX8ULPD3 0xA4 /* dummy ID, iMX8ULP Dual core 3D/3C, EPDC + GPU disabled */
#define MPU_SOC_IMX8ULPS3 0xA5 /* dummy ID, iMX8ULP Single core 3D/3C, EPDC + GPU disabled */
#define MPU_SOC_IMX8ULPSC 0xA6 /* dummy ID, iMX8ULP SC part, 900 MHz + EPDC disabled */

/*! @brief The board name */
#define BOARD_NAME        "MIMX8ULP-EVK"
#define MANUFACTURER_NAME "NXP"

/* SOC infomation*/
#define IMX8ULP_SOC_REV_A0 0xA000
#define IMX8ULP_SOC_REV_A1 0xA100
#define IMX8ULP_SOC_ID     0x084D

/* The UART to use for debug messages. */
#define BOARD_DEBUG_UART_TYPE     kSerialPort_Uart
#define BOARD_DEBUG_UART_BAUDRATE 115200u
#define BOARD_DEBUG_UART_BASEADDR LPUART1_BASE
#define BOARD_DEBUG_UART_INSTANCE 1U
#define BOARD_DEBUG_UART_CLK_FREQ CLOCK_GetLpuartClkFreq(BOARD_DEBUG_UART_INSTANCE)
#define BOARD_DEBUG_UART_IP_NAME  kCLOCK_Lpuart1
#define BOARD_DEBUG_UART_CLKSRC   kCLOCK_Pcc1BusIpSrcSysOscDiv2
#define BOARD_DEBUG_UART_RESET    kRESET_Lpuart1
#define BOARD_UART_IRQ            LPUART1_IRQn
#define BOARD_UART_IRQ_HANDLER    LPUART1_IRQHandler

/* Board accelerator sensor configuration */
#define BOARD_ACCEL_I2C_BASEADDR   LPI2C0
#define BOARD_ACCEL_I2C_CLOCK_FREQ CLOCK_GetLpi2cClkFreq(0)

#define BOARD_CODEC_I2C_BASEADDR   LPI2C0
#define BOARD_CODEC_I2C_CLOCK_FREQ CLOCK_GetLpi2cClkFreq(0)
#define BOARD_CODEC_I2C_INSTANCE   0U

/* Board mipi to hdmi bridge ic(IT6161) */
#define BOARD_DISPLAY_I2C_BASEADDR   LPI2C0
#define BOARD_DISPLAY_I2C_CLOCK_FREQ CLOCK_GetLpi2cClkFreq(0)

#define BOARD_FLEXSPI_PSRAM FLEXSPI1
/* NOR FLASH */
#define BOARD_NOR_FLASH_READ_MAXIMUM_FREQ (40000000U) /* READ NOR FLASH MAXIMUM FREQUENCY is 40 MHz */
/* For NOR FLASH that connected to flexspi0 controller */
#define BOARD_FLEXSPI_NOR_FLASH_PORT       kFLEXSPI_PortA1
#define BOARD_FLEXSPI_CONNECT_TO_NOR_FLASH FLEXSPI0
/* For NOR FLASH GD25LX256E */
#ifndef SPINOR_OP_DISABLE_4_BYTE_ADDR_MODE_GIGADEVICE
#define SPINOR_OP_DISABLE_4_BYTE_ADDR_MODE_GIGADEVICE \
    (0xE9) /* Disable 4-Byte Address Mode (from GigaDevice GD25LX256E) */
#endif

#define BOARD_SW8_GPIO        GPIOB
#define BOARD_SW8_GPIO_PIN    12U
#define BOARD_SW8_IRQ         GPIOB_INT0_IRQn
#define BOARD_SW8_IRQ_HANDLER GPIOB_INT0_IRQHandler
#define BOARD_SW8_NAME        "SW8"

#define BOARD_SW7_GPIO        GPIOB
#define BOARD_SW7_GPIO_PIN    13U
#define BOARD_SW7_IRQ         GPIOB_INT0_IRQn
#define BOARD_SW7_IRQ_HANDLER GPIOB_INT0_IRQHandler
#define BOARD_SW7_NAME        "SW7"

#define LED_INIT()
#define LED_ON()
#define LED_TOGGLE()

#define VDEV0_VRING_BASE (0xAFF00000U)
#define VDEV1_VRING_BASE (0xAFF10000U)

/* MIPI panel. */
/* RST pin. */
#define BOARD_MIPI_RST_GPIO GPIOC
#define BOARD_MIPI_RST_PIN  23
/* Backlight pin. */
#define BOARD_MIPI_BL_GPIO GPIOA
#define BOARD_MIPI_BL_PIN  3
/* TE pin. */
#define BOARD_MIPI_TE_GPIO GPIOE
#define BOARD_MIPI_TE_PIN  17

#define BOARD_IS_XIP_FLEXSPI0()                                                                                 \
    ((((uint32_t)BOARD_InitDebugConsole >= 0x04000000U) && ((uint32_t)BOARD_InitDebugConsole < 0x0C000000U)) || \
     (((uint32_t)BOARD_InitDebugConsole >= 0x14000000U) && ((uint32_t)BOARD_InitDebugConsole < 0x1C000000U)))

/* PCA6416A (U27) */
#define BOARD_PCA6416A_I2C            LPI2C0
#define BOARD_PCA6416A_I2C_ADDR       (0x20U)
#define BOARD_PCA6416A_I2C_CLOCK_FREQ (CLOCK_GetLpi2cClkFreq(0))

#define BOARD_PCA6416A_CPU_POWER_MODE0 0U
#define BOARD_PCA6416A_CPU_POWER_MODE1 1U
#define BOARD_PCA6416A_CPU_POWER_MODE2 2U
#define BOARD_PCA6416A_CAN0_STDBY      4U
#define BOARD_PCA6416A_TOUCH_RESET     5U
#define BOARD_PCA6416A_CAMERA_RESET    7U
#define BOARD_PCA6416A_CAMERA_PWDN     (8U + 0U)
#define BOARD_PCA6416A_MIPI_SWITCH     (8U + 1U)
#define BOARD_PCA6416A_EPDC_SWITCH     (8U + 2U)
#define BOARD_PCA6416A_BATT_ADC_ENABLE (8U + 3U)
#define BOARD_PCA6416A_CHG_OK          (8U + 4U)
#define BOARD_PCA6416A_AC_OK           (8U + 5U)

#define TPM0_CH2 (2UL)
/* 500 Hz */
#define TPM0_CH2_PWM_FREQ (500UL)
#define FULL_DUTY_CYCLE   (100UL)

/* IT6161(U10) */
#define BOARD_IT6161_I2C            LPI2C0
#define BOARD_IT6161_I2C_ADDR       (0x6CU)
#define BOARD_IT6161_I2C_CLOCK_FREQ (CLOCK_GetLpi2cClkFreq(0))

#define TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX (0)
#define TRDC_MRC_ACCESS_CONTROL_POLICY_ALL_INDEX (0)
#define TRDC_M33_DOMAIN_ID                       (6)
#define TRDC_POWERQUAD_DOMAIN_ID                 (0)
#define TRDC_POWERQUAD_MASTER_ID                 (4)
#define TRDC_DMA0_DOMAIN_ID                      (0)
#define TRDC_DMA0_MASTER_ID                      (2)
#define TRDC_MDAC2_INDEX                         (2) /* T-MADC2 */
#define TRDC_MDAC0_INDEX                         (0) /* T-MADC0 */
#define TRDC_MRC0_INDEX                          (0) /* T-MRC0 */
#define TRDC_MRC1_INDEX                          (1) /* T-MRC1 */
#define TRDC_DCNANO_DOMAIN_ID                    (3)

#define TRDC_MBC3_INDEX    (3) /* T-MBC3(controll access of DSP Domain) */
#define TRDC_MBC_INDEX_NUM (4)

/* FSB */
#define FUSE_BANKS           (64)
#define FUSE_WORDS_PER_BANKS (8)
#define FSB_OTP_SHADOW       (0x800)
#define FSB_BASE_ADDR        (0x27010000)

/* handshake with uboot */
/* Define the timeout ms to do handshake with uboot with mu flag */
#define BOARD_HANDSHAKE_WITH_UBOOT_TIMEOUT_MS (10000U)

/*
 * Get a proper sequence to recovery RCR of MU0_MUA from uboot(a35)
 * at the same time, imply that io and pwm of mipi is ready for uboot
 */
#define BOARD_MU0_MUB_F0_INIT_SRTM_COMMUNICATION_FLG (0x1UL)
/* 1 ms */
#define BOARD_WAIT_MU0_MUB_F0_FLG_FROM_UBOOT_MS (0x1U)

#define BOARD_FLEXSPI_DLL_LOCK_RETRY (10)

#define LPI_WAKEUP_EN_SHIFT (8U)

#define DENALI_CTL_137 (0x224U)
#define DENALI_CTL_143 (0x23CU)
#define DENALI_CTL_144 (0x240U)
#define DENALI_CTL_146 (0x248U)
#define DENALI_CTL_147 (0x24CU)
#define DENALI_CTL_148 (0x250U)
#define DENALI_CTL_153 (0x264U)
#define DENALI_CTL_266 (0x428U)

#define DENALI_PHY_1559 (0x585CU)
#define DENALI_PHY_1590 (0x58D8U)

#define DENALI_PI_52  (0x20D0U)
#define DENALI_PI_26  (0x2068U)
#define DENALI_PI_33  (0x2084U)
#define DENALI_PI_65  (0x2104U)
#define DENALI_PI_77  (0x2134U)
#define DENALI_PI_134 (0x2218U)
#define DENALI_PI_132 (0x2210U)
#define DENALI_PI_137 (0x2224U)

/* Set RTD_SEC_SIM_GPR1 as ddr state flag between AD and RTD,  ddr active: 0, ddr in self refresh: 1 */
#define DDR_IN_SELFREFRESH_BASE (0x2802B004u)

#define W32(addr, val) *((volatile uint32_t *)(addr)) = (val)
#define R32(addr)      *((volatile uint32_t *)(addr))

#define SETBIT32(addr, set)   W32(addr, R32(addr) | set)
#define CLRBIT32(addr, clear) W32(addr, R32(addr) & ~clear)

#define LPDDR3_TYPE                          (0x7U)
#define LPDDR4_TYPE                          (0xBU)
#define SAVED_DRAM_DATA_BASE_ADDR_FROM_TFA   (0x20055000)
#define SAVED_DRAM_TIMING_INFO_SIZE_FROM_TFA (0x58)

#define LPDDR_CTRL_LP_CMD_MASK       (0x7F00U)
#define LPAV_LPDDR_CTRL_LP_CMD_SHIFT (8U)
#define LPAV_LPDDR_CTRL_LP_CMD(x) \
    (((uint32_t)(((uint32_t)(x)) << LPAV_LPDDR_CTRL_LP_CMD_SHIFT)) & LPDDR_CTRL_LP_CMD_MASK)
#define CTL_NUM      680
#define PI_NUM       298
#define PHY_NUM      1654
#define PHY_DIFF_NUM 49

#define LP_AUTO_ENTRY_EN (0x4U)
#define LP_AUTO_EXIT_EN  (0xFU)
#define AUTO_LP_NUM      (0x3)

/* For debugging  */
#define BOARD_ENABLE_DUMP_REGS                 (0)
#define LPI_SRPD_LONG_MCCLK_GATE_WAKEUP_F2_NUM (0xF)

extern struct dram_cfg *dram_timing_cfg;
extern uint32_t dram_class;
struct dram_cfg
{
    uint32_t ctl_cfg[CTL_NUM];
    uint32_t pi_cfg[PI_NUM];
    uint32_t phy_full[PHY_NUM];
    uint32_t phy_diff[PHY_DIFF_NUM];
    uint32_t auto_lp_cfg[AUTO_LP_NUM];
};

struct dram_cfg_param
{
    uint32_t reg;
    uint32_t val;
};

struct dram_timing_info
{
    /* ddr controller config */
    struct dram_cfg_param *ctl_cfg;
    unsigned int ctl_cfg_num;
    /* pi config */
    struct dram_cfg_param *pi_cfg;
    unsigned int pi_cfg_num;
    /* phy freq1 config */
    struct dram_cfg_param *phy_f1_cfg;
    unsigned int phy_f1_cfg_num;
    /* phy freq2 config */
    struct dram_cfg_param *phy_f2_cfg;
    unsigned int phy_f2_cfg_num;
    struct dram_cfg_param *auto_lp_cfg;
    unsigned int auto_lp_cfg_num;
    /* initialized drate table */
    unsigned int fsp_table[3];
};

/* boot type */
typedef enum
{
    SINGLE_BOOT_TYPE,
    DUAL_BOOT_TYPE,
    LOW_POWER_BOOT_TYPE,
} boot_type_e;

typedef enum
{
    IP_EPDC = 1,
    IP_GPU  = 2,
    IP_MPU1 = 3, /* MPU1 - Cortex-A35 core 1 */
} ip_type_e;
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/

void BOARD_InitDebugConsole(void);
bool BOARD_IsLowPowerBootType(void);
bool BOARD_IsSingleBootType(void);
bool BOARD_IsLPAVOwnedByRTD(void);
const char *BOARD_GetBootTypeName(void);

/* TRDC */
bool BOARD_GetReleaseFlagOfTrdc(void);
void BOARD_SetReleaseFlagOfTrdc(bool flag);
void BOARD_ReleaseTRDC(void);
void BOARD_SetTrdcGlobalConfig(void);
/* Setup TRDC configuration before executing rom code of A35(A35 rom will access FSB, S400 MUAP A-Side, SIM0-S with
 * secure state, so m33 help a35 to configure TRDC) */
void BOARD_SetTrdcAfterApdReset(void);

/*
 * return the handshake result(fail or success):
 * true: succeeded to handshake with uboot; false: failed to handshake with uboot
 */
bool BOARD_HandshakeWithUboot(void);

void BOARD_ConfigMPU(void);
status_t BOARD_InitPsRam(void);
void BOARD_FlexspiClockSafeConfig(void);
AT_QUICKACCESS_SECTION_CODE(
    void BOARD_SetFlexspiClock(FLEXSPI_Type *base, uint32_t src, uint8_t divValue, uint8_t fracValue));
AT_QUICKACCESS_SECTION_CODE(void BOARD_DeinitXip(FLEXSPI_Type *base));
AT_QUICKACCESS_SECTION_CODE(void BOARD_InitXip(FLEXSPI_Type *base));
#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
void BOARD_LPI2C_Init(LPI2C_Type *base, uint32_t clkSrc_Hz);
status_t BOARD_LPI2C_Send(LPI2C_Type *base,
                          uint8_t deviceAddress,
                          uint32_t subAddress,
                          uint8_t subaddressSize,
                          uint8_t *txBuff,
                          uint16_t txBuffSize,
                          uint32_t flags);
status_t BOARD_LPI2C_Receive(LPI2C_Type *base,
                             uint8_t deviceAddress,
                             uint32_t subAddress,
                             uint8_t subaddressSize,
                             uint8_t *rxBuff,
                             uint16_t rxBuffSize,
                             uint32_t flags);
void BOARD_Accel_I2C_Init(void);
status_t BOARD_Accel_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint32_t txBuff, uint32_t flags);
status_t BOARD_Accel_I2C_Receive(uint8_t deviceAddress,
                                 uint32_t subAddress,
                                 uint8_t subaddressSize,
                                 uint8_t *rxBuff,
                                 uint8_t rxBuffSize,
                                 uint32_t flags);
void BOARD_Codec_I2C_Init(void);
status_t BOARD_Codec_I2C_Send(uint8_t deviceAddress,
                              uint32_t subAddress,
                              uint8_t subAddressSize,
                              const uint8_t *txBuff,
                              uint8_t txBuffSize,
                              uint32_t flags);
status_t BOARD_Codec_I2C_Receive(uint8_t deviceAddress,
                                 uint32_t subAddress,
                                 uint8_t subAddressSize,
                                 uint8_t *rxBuff,
                                 uint8_t rxBuffSize,
                                 uint32_t flags);

void BOARD_Display_I2C_Init(void);
status_t BOARD_Display_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
status_t BOARD_Display_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);

#if defined(BOARD_USE_PCA6416A) && BOARD_USE_PCA6416A
void BOARD_PCA6416A_I2C_Init(void);
status_t BOARD_PCA6416A_I2C_Send(uint8_t deviceAddress,
                                 uint32_t subAddress,
                                 uint8_t subAddressSize,
                                 const uint8_t *txBuff,
                                 uint8_t txBuffSize,
                                 uint32_t flags);
status_t BOARD_PCA6416A_I2C_Receive(uint8_t deviceAddress,
                                    uint32_t subAddress,
                                    uint8_t subAddressSize,
                                    uint8_t *rxBuff,
                                    uint8_t rxBuffSize,
                                    uint32_t flags);

/* PCA6416A U27. */
extern pca6416a_handle_t g_pca6416aHandle;

void BOARD_InitPCA6416A(pca6416a_handle_t *handle);

/* MIPI DSI */
void BOARD_InitMipiDsiPins(void);
void BOARD_EnableMipiDsiBacklight(void);
#endif /* BOARD_USE_PCA6416A */

#endif /* SDK_I2C_BASED_COMPONENT_USED */

/* LPAV DDR */
void BOARD_LpavInit();
void BOARD_DdrSave(void);
void BOARD_LpavSave(void);
void BOARD_DramEnterRetention(void);
void BOARD_DramExitRetention(uint32_t dram_class, struct dram_cfg *dram_timing_cfg);
void BOARD_DDREnterSelfRefresh();
void BOARD_DDRExitSelfRefresh();

/* Use for debugging */
void BOARD_DumpRegs(uint32_t start_reg_addr, uint32_t end_reg_addr);
void BOARD_DumpRTDRegs(void);
bool BOARD_IsIpDisabled(ip_type_e type);
uint32_t BOARD_GetSocVariantType(void);
#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
