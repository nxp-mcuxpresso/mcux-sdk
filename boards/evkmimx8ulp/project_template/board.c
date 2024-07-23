/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifdef SDK_OS_FREE_RTOS
#include "FreeRTOS.h"
#include "task.h"
#endif
#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "board.h"
#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
#include "fsl_lpi2c.h"
#endif /* SDK_I2C_BASED_COMPONENT_USED */
#include "fsl_lpuart.h"
#include "fsl_flexspi.h"
#include "fsl_upower.h"
#include "fsl_sentinel.h"
#include "fsl_reset.h"
#include "fsl_cache.h"
#if defined(BOARD_USE_TPM) && BOARD_USE_TPM
#include "fsl_tpm.h"
#endif /* BOARD_USE_TPM */
#if defined(BOARD_USE_PCA6416A) && BOARD_USE_PCA6416A
#include "fsl_pca6416a.h"
#endif /* BOARD_USE_PCA6416A */
#include "fsl_trdc.h"
#include "fsl_mu.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
bool dram_auto_lp_true = false;
uint32_t dram_ctl_143;
struct dram_cfg *dram_timing_cfg;
uint32_t dram_class;
/*******************************************************************************
 * Variables
 ******************************************************************************/
static uint32_t mrc_start_addr[2] = {0x4000000, 0x40000000};
static uint32_t mrc_end_addr[2]   = {0xC000000, 0x50000000};

/* Boot Type Name(enum BOOT_TYPE) */
static const char *s_bootTypeNames[] = {"Single Boot Type", "Dual Boot Type", "Low Power Boot Type"};

/* TRDC */
static bool releasedTrdc =
    false; /* set a flag to check whether released TRDC(whether change owner of TRDC from sentinel to m33) */
/* These apis from uboot source code[drivers/misc/sentinel/fuse.c] */
struct fsb_map_entry
{
    int32_t fuse_bank;
    uint32_t fuse_words;
    bool redundancy;
};

/* Register context for LPAV FSB FUSE */
const struct fsb_map_entry fsb_mapping_table[] = {
    {3, 8},  {4, 8},  {-1, 48}, /* Reserve 48 words */
    {5, 8},  {6, 8},  {8, 4, true}, {24, 4, true}, {26, 4, true}, {27, 4, true}, {28, 8}, {29, 8}, {30, 8}, {31, 8},
    {37, 8}, {38, 8}, {39, 8},      {40, 8},       {41, 8},       {42, 8},       {43, 8}, {44, 8}, {45, 8}, {46, 8},
};

/* Register context for LPAV CGC2 */
static uint32_t cgc2[][2] = {
    {0x2da60014, 0x08004000}, {0x2da60020, 0x0},        {0x2da6003c, 0x18004180}, {0x2da60040, 0x48200000},
    {0x2da60108, 0x00808080}, {0x2da60208, 0x00808080}, {0x2da60900, 0x0},        {0x2da60904, 0x0},
    {0x2da60908, 0x0},        {0x2da60910, 0x0},        {0x2da60a00, 0x0},
};

/* Register context for LPAV PLL4 */
static uint32_t pll4[][2] = {
    {0x2da60604, 0x80},       {0x2da60608, 0x80808081}, {0x2da6060c, 0x808080C0}, {0x2da60610, 0x00160000},
    {0x2da60618, 0x00000001}, {0x2da6061c, 0x0},        {0x2da60620, 0x0},        {0x2da60624, 0x00001300},
    {0x2da60600, 0x03000001}, {0x2da68614, 0xD8DE5ECC},
};

/* Register context for LPAV PCC5 part 1 */
static uint32_t pcc5_0[][2] = {
    {0x2da70000, 0xC0000000}, {0x2da70004, 0x80000000}, {0x2da70008, 0x80000000}, {0x2da7000c, 0x80000000},
    {0x2da70010, 0x80000000}, {0x2da70014, 0x80000000}, {0x2da70018, 0x80000000}, {0x2da7001c, 0x80000000},
    {0x2da70020, 0x80000000}, {0x2da70024, 0x80000000}, {0x2da70028, 0x80000000}, {0x2da7002c, 0x80000000},
    {0x2da70030, 0x80000000}, {0x2da70034, 0x80000000}, {0x2da70038, 0x80000000}, {0x2da7003c, 0x80000000},
    {0x2da70040, 0x80000000}, {0x2da70044, 0x80000000}, {0x2da70048, 0x80000000}, {0x2da7004c, 0x80000000},
    {0x2da70050, 0x80000000}, {0x2da70054, 0x80000000}, {0x2da70058, 0x80000000}, {0x2da7005c, 0x80000000},
    {0x2da70060, 0x80000000}, {0x2da70064, 0x80000000}, {0x2da70068, 0x80000000}, {0x2da7006c, 0x80000000},
    {0x2da70070, 0x80000000}, {0x2da70074, 0x80000000}, {0x2da70078, 0x80000000}, {0x2da7007c, 0x80000000},
    {0x2da70080, 0x80000000}

};

/* Register context for LPAV PCC5 part 2 */
static uint32_t pcc5_1[][2] = {
    {0x2da70084, 0x80000000}, {0x2da70088, 0x80000000}, {0x2da7008c, 0x80000000}, {0x2da700a0, 0x80000000},
    {0x2da700a4, 0x80000000}, {0x2da700a8, 0x80000000}, {0x2da700ac, 0x80000000}, {0x2da700b0, 0x90000000},
    {0x2da700b4, 0x80000000}, {0x2da700bc, 0x80000000}, {0x2da700c0, 0x81000005}, {0x2da700c8, 0x90400000},
    {0x2da700cc, 0x80000000}, {0x2da700d0, 0x90000000}, {0x2da700f0, 0x92000000}, {0x2da700f4, 0x92000000},
    {0x2da700f8, 0x97000005}, {0x2da70108, 0xD0000000}, {0x2da7010c, 0x80000000}, {0x2da70110, 0x80000000},
    {0x2da70114, 0xC0000000},
};

/* Register context for LPAV SIM */
static uint32_t lpav_sim[][2] = {
    {0x2da50000, 0x0}, {0x2da50004, 0x0}, {0x2da50008, 0x02112002}, {0x2da5001c, 0x0},
    {0x2da50020, 0x0}, {0x2da50024, 0x0}, {0x2da50034, 0xFFFFFFFF},
};

/* DDR PHY register index for frequency diff */
static uint32_t freq_specific_reg_array[PHY_DIFF_NUM] = {
    90,  92,  93,  96,  97,  100, 101, 102, 103, 104, 114,  346,  348,  349,  352, 353, 356,
    357, 358, 359, 360, 370, 602, 604, 605, 608, 609, 612,  613,  614,  615,  616, 626, 858,
    860, 861, 864, 865, 868, 869, 870, 871, 872, 882, 1063, 1319, 1566, 1624, 1625};

/*******************************************************************************
 * Code
 ******************************************************************************/
/* Initialize debug console. */
void BOARD_InitDebugConsole(void)
{
    uint32_t uartClkSrcFreq;

    CLOCK_SetIpSrc(BOARD_DEBUG_UART_IP_NAME, BOARD_DEBUG_UART_CLKSRC);
    uartClkSrcFreq = BOARD_DEBUG_UART_CLK_FREQ;
    RESET_PeripheralReset(BOARD_DEBUG_UART_RESET);

    DbgConsole_Init(BOARD_DEBUG_UART_INSTANCE, BOARD_DEBUG_UART_BAUDRATE, BOARD_DEBUG_UART_TYPE, uartClkSrcFreq);
}

/*
 * check fusion whether available
 * return:
 *     true: fusion is not available
 *     false: fusion is available
 */
bool BOARD_IsFusionAvailable(void)
{
    return (!(SIM_SEC->SYSCTRL0 & SIM_SEC_SYSCTRL0_FUSION_DSP_RST_MASK));
}

void BOARD_DumpRegs(uint32_t start_reg_addr, uint32_t end_reg_addr)
{
#if BOARD_ENABLE_DUMP_REGS
    uint32_t i = 0U;

    for (i = start_reg_addr; i <= end_reg_addr; i += 4)
    {
        PRINTF("Reg 0x%x: Val = 0x%x\r\n", i, *(uint32_t *)i);
    }
#endif // BOARD_ENABLE_DUMP_REGS
}

void BOARD_DumpRTDRegs(void)
{
    PRINTF("DUMP SIM_SEM_RTD:r\n");
    PRINTF("* GPR0                                      = 0x%x\r\n", *((volatile uint32_t *)(0x2802b000)));
    PRINTF("* GPR1                                      = 0x%x\r\n", *((volatile uint32_t *)(0x2802b004)));
    PRINTF("* DGO_CTRL0                                 = 0x%x\r\n", *((volatile uint32_t *)(0x2802b008)));
    PRINTF("* DGO_CTRL1                                 = 0x%x\r\n", *((volatile uint32_t *)(0x2802b00c)));
    PRINTF("* DGO_GP0                                   = 0x%x\r\n", *((volatile uint32_t *)(0x2802b010)));
    PRINTF("* DGO_GP1                                   = 0x%x\r\n", *((volatile uint32_t *)(0x2802b014)));
    PRINTF("* DGO_GP2                                   = 0x%x\r\n", *((volatile uint32_t *)(0x2802b018)));
    PRINTF("* DGO_GP3                                   = 0x%x\r\n", *((volatile uint32_t *)(0x2802b01c)));
    PRINTF("* DGO_GP4                                   = 0x%x\r\n", *((volatile uint32_t *)(0x2802b020)));
    PRINTF("* DGO_GP5                                   = 0x%x\r\n", *((volatile uint32_t *)(0x2802b024)));
    PRINTF("* DGO_GP6                                   = 0x%x\r\n", *((volatile uint32_t *)(0x2802b028)));
    PRINTF("* DGO_GP7                                   = 0x%x\r\n", *((volatile uint32_t *)(0x2802b02c)));
    PRINTF("* DGO_GP8                                   = 0x%x\r\n", *((volatile uint32_t *)(0x2802b030)));
    PRINTF("* DGO_GP9                                   = 0x%x\r\n", *((volatile uint32_t *)(0x2802b034)));
    PRINTF("* DGO_GP10                                  = 0x%x\r\n", *((volatile uint32_t *)(0x2802b038)));
    PRINTF("* DGO_GP11                                  = 0x%x\r\n", *((volatile uint32_t *)(0x2802b03c)));
    PRINTF("* DGO_GP12                                  = 0x%x\r\n", *((volatile uint32_t *)(0x2802b040)));
    PRINTF("* SYSCTRL0                                  = 0x%x\r\n", *((volatile uint32_t *)(0x2802b044)));
    PRINTF("* SSRAM_ACCESS_DISABLE                      = 0x%x\r\n", *((volatile uint32_t *)(0x2802b048)));
    PRINTF("* LPAV_MASTER_ALLOC_CTRL                    = 0x%x\r\n", *((volatile uint32_t *)(0x2802b04c)));
    PRINTF("* LPAV_SLAVE_ALLOC_CTRL                     = 0x%x\r\n", *((volatile uint32_t *)(0x2802b050)));
    PRINTF("* LPAV_DMA2_CH_ALLOC_CTRL                   = 0x%x\r\n", *((volatile uint32_t *)(0x2802b054)));
    PRINTF("* LPAV_DMA2_REQ_ALLOC_CTRL                  = 0x%x\r\n", *((volatile uint32_t *)(0x2802b058)));
    PRINTF("* M33_CFGSSTCALIB                           = 0x%x\r\n", *((volatile uint32_t *)(0x2802b05c)));
    PRINTF("* FUSION_GPR0                               = 0x%x\r\n", *((volatile uint32_t *)(0x2802b060)));
    PRINTF("* FUSION_GPR1                               = 0x%x\r\n", *((volatile uint32_t *)(0x2802b064)));
    PRINTF("* FUSION_GPR2                               = 0x%x\r\n", *((volatile uint32_t *)(0x2802b068)));
    PRINTF("* RTD_INTERRUPT_MASK0                       = 0x%x\r\n", *((volatile uint32_t *)(0x2802b06c)));
    PRINTF("* APD_INTERRUPT_MASK0                       = 0x%x\r\n", *((volatile uint32_t *)(0x2802b070)));
    PRINTF("* AVD_INTERRUPT_MASK0                       = 0x%x\r\n", *((volatile uint32_t *)(0x2802b074)));
    PRINTF("* WRITE_ASSIST_CTR                          = 0x%x\r\n", *((volatile uint32_t *)(0x2802b078)));

    PRINTF("DUMP CGC0:r\n");
    PRINTF("* CGC0.CM33CLK                              = 0x%x\r\n", *((volatile uint32_t *)(0x2802f010)));
    PRINTF("* CGC0.FUSIONCLK                            = 0x%x\r\n", *((volatile uint32_t *)(0x2802f01c)));
    PRINTF("* CGC0.CLKOUTCFG                            = 0x%x\r\n", *((volatile uint32_t *)(0x2802f020)));
    PRINTF("* CGC0.SOSCCSR                              = 0x%x\r\n", *((volatile uint32_t *)(0x2802f104)));
    PRINTF("* CGC0.SOSCDIV                              = 0x%x\r\n", *((volatile uint32_t *)(0x2802f108)));
    PRINTF("* CGC0.FROCSR                               = 0x%x\r\n", *((volatile uint32_t *)(0x2802f200)));
    PRINTF("* CGC0.LPOSCCSR                             = 0x%x\r\n", *((volatile uint32_t *)(0x2802f304)));
    PRINTF("* CGC0.PLL0CSR                              = 0x%x\r\n", *((volatile uint32_t *)(0x2802f500)));
    PRINTF("* CGC0.PLL0DIV_VCO                          = 0x%x\r\n", *((volatile uint32_t *)(0x2802f504)));
    PRINTF("* CGC0.PLL0DIV_PFD_0                        = 0x%x\r\n", *((volatile uint32_t *)(0x2802f508)));
    PRINTF("* CGC0.PLL0CFG                              = 0x%x\r\n", *((volatile uint32_t *)(0x2802f510)));
    PRINTF("* CGC0.PLL0PFDCFG                           = 0x%x\r\n", *((volatile uint32_t *)(0x2802f514)));
    PRINTF("* CGC0.PLL1CSR                              = 0x%x\r\n", *((volatile uint32_t *)(0x2802f600)));

    PRINTF("DUMP CMC0:r\n");
    PRINTF("* CMC0.CKCTRL                               = 0x%x\r\n", *((volatile uint32_t *)(0x28025010)));
    PRINTF("* CMC0.PMPROT                               = 0x%x\r\n", *((volatile uint32_t *)(0x28025018)));
    PRINTF("* CMC0.PMCTRL                               = 0x%x\r\n", *((volatile uint32_t *)(0x28025020)));
    PRINTF("* CMC0.SRS                                  = 0x%x\r\n", *((volatile uint32_t *)(0x28025080)));
    PRINTF("* CMC0.SSRS                                 = 0x%x\r\n", *((volatile uint32_t *)(0x28025088)));
    PRINTF("* CMC0.SRIE                                 = 0x%x\r\n", *((volatile uint32_t *)(0x2802508c)));
    PRINTF("* CMC0.SRIF                                 = 0x%x\r\n", *((volatile uint32_t *)(0x28025090)));
    PRINTF("* CMC0.MR0                                  = 0x%x\r\n", *((volatile uint32_t *)(0x280250a0)));
    PRINTF("* CMC0.CORECTL                              = 0x%x\r\n", *((volatile uint32_t *)(0x28025110)));
    PRINTF("* CMC0.DBGCTL                               = 0x%x\r\n", *((volatile uint32_t *)(0x28025120)));

    PRINTF("DUMP WUU0:r\n");
    PRINTF("* WUU0_VERID                                = 0x%x\r\n", *((volatile uint32_t *)(0x28028000)));
    PRINTF("* WUU0_PARAM                                = 0x%x\r\n", *((volatile uint32_t *)(0x28028004)));
    PRINTF("* WUU0_PE1                                  = 0x%x\r\n", *((volatile uint32_t *)(0x28028008)));
    PRINTF("* WUU0_PE2                                  = 0x%x\r\n", *((volatile uint32_t *)(0x2802800c)));
    PRINTF("* WUU0_ME                                   = 0x%x\r\n", *((volatile uint32_t *)(0x28028018)));
    PRINTF("* WUU0_DE                                   = 0x%x\r\n", *((volatile uint32_t *)(0x2802801c)));
    PRINTF("* WUU0_PF                                   = 0x%x\r\n", *((volatile uint32_t *)(0x28028020)));
    PRINTF("* WUU0_MF                                   = 0x%x\r\n", *((volatile uint32_t *)(0x28028028)));
    PRINTF("* WUU0_FILT                                 = 0x%x\r\n", *((volatile uint32_t *)(0x28028030)));
    PRINTF("* WUU0_PDC1                                 = 0x%x\r\n", *((volatile uint32_t *)(0x28028038)));
    PRINTF("* WUU0_PDC2                                 = 0x%x\r\n", *((volatile uint32_t *)(0x2802803c)));
    PRINTF("* WUU0_FDC                                  = 0x%x\r\n", *((volatile uint32_t *)(0x28028048)));
    PRINTF("* WUU0_PMC                                  = 0x%x\r\n", *((volatile uint32_t *)(0x28028050)));
    PRINTF("* WUU0_FMC                                  = 0x%x\r\n", *((volatile uint32_t *)(0x28028058)));
}

/* TRDC */
bool BOARD_GetReleaseFlagOfTrdc(void)
{
    return releasedTrdc;
}

void BOARD_SetReleaseFlagOfTrdc(bool flag)
{
    if (releasedTrdc != flag)
        releasedTrdc = flag;
}

static uint32_t BOARD_MapFsbFuseIndex(uint32_t bank, uint32_t word, bool *redundancy)
{
    int32_t size = ARRAY_SIZE(fsb_mapping_table);
    int32_t i, word_pos = 0;

    /* map the fuse from ocotp fuse map to FSB*/
    for (i = 0; i < size; i++)
    {
        if (fsb_mapping_table[i].fuse_bank != -1 && fsb_mapping_table[i].fuse_bank == bank &&
            fsb_mapping_table[i].fuse_words > word)
        {
            break;
        }

        word_pos += fsb_mapping_table[i].fuse_words;
    }

    if (i == size)
        return -1; /* Failed to find */

    if (fsb_mapping_table[i].redundancy)
    {
        *redundancy = true;
        return (word >> 1) + word_pos;
    }

    *redundancy = false;
    return word + word_pos;
}

/*
 * return:
 *     0: success
 *     -1: error
 */
int32_t BOARD_FuseRead(uint32_t bank, uint32_t word, uint32_t *val)
{
    int32_t word_index = -1;
    bool redundancy    = false;
    int32_t ret        = -1;

    if (bank >= FUSE_BANKS || word >= FUSE_WORDS_PER_BANKS || !val)
    {
        return ret;
    }

    word_index = BOARD_MapFsbFuseIndex(bank, word, &redundancy);
    if (word_index >= 0)
    {
        *val = *(uint32_t *)(FSB_BASE_ADDR + FSB_OTP_SHADOW + (word_index << 2));
        if (redundancy)
        {
            *val = (*val >> ((word % 2) * 16)) & 0xFFFF;
        }
        ret = 0;
    }
    return ret;
}

static uint32_t BOARD_GetMpuSpeedGradeHz(void)
{
    int ret;
    uint32_t val;
    uint32_t speed = MHZ(800);

    ret = BOARD_FuseRead(3, 1, &val);
    if (!ret)
    {
        val >>= 14;
        val &= 0x3;

        switch (val)
        {
            case 0x1:
                speed = MHZ(900); /* 900Mhz*/
                break;
            default:
                speed = MHZ(800); /* 800Mhz*/
        }
    }
    return speed;
}

uint32_t BOARD_GetSocVariantType(void)
{
    static uint32_t soc_type = 0;
    uint32_t val;
    int ret;

    if (soc_type == 0)
    {
        soc_type = MPU_SOC_IMX8ULP;
        ret      = BOARD_FuseRead(3, 2, &val);
        if (!ret)
        {
            bool epdc_disable  = !!(val & BIT(23));
            bool core1_disable = !!(val & BIT(15));
            bool gpu_disable   = false;
            bool a35_900mhz    = (BOARD_GetMpuSpeedGradeHz() == MHZ(900));

            if ((val & (BIT(18) | BIT(19))) == (BIT(18) | BIT(19)))
                gpu_disable = true;

            if (epdc_disable && gpu_disable)
                soc_type = core1_disable ? (soc_type + 4) : (soc_type + 3);
            else if (epdc_disable && a35_900mhz)
                soc_type = MPU_SOC_IMX8ULPSC;
            else if (epdc_disable)
                soc_type = core1_disable ? (soc_type + 2) : (soc_type + 1);
        }
    }

    return soc_type;
}

bool BOARD_IsIpDisabled(ip_type_e type)
{
    uint32_t soc_type;
    bool result = false;

    soc_type = BOARD_GetSocVariantType();
    switch (type)
    {
        case IP_EPDC:
            if (soc_type != MPU_SOC_IMX8ULP)
            {
                result = true; /* epdc is disabled */
            }
            break;
        case IP_GPU:
            if (soc_type == MPU_SOC_IMX8ULPD3 && soc_type == MPU_SOC_IMX8ULPS3)
            {
                result = true; /* gpu is disabled */
            }
            break;
        case IP_MPU1:
            if (soc_type == MPU_SOC_IMX8ULPS5 || soc_type == MPU_SOC_IMX8ULPS3)
            {
                result = true; /* a35_1 is disabled */
            }
            break;
        default:
            PRINTF("Not support the type 0x%x\r\n", type);
            break;
    }

    return result;
}

/*
 * RDC will be enabled defaultly when DBD_EN is fused.
 * return:
 *     true: RDC is enabled
 *     false: RDC is not enabled
 */
bool BOARD_IsRdcEnabled(void)
{
    static bool rdc_en                = true; /* Default assume DBD_EN is set */
    int32_t ret                       = -1;
    static bool read_dbd_en_from_fuse = false;
    uint32_t val                      = 0;

    /* Read DBD_EN fuse */
    if (read_dbd_en_from_fuse == false)
    {
        ret = BOARD_FuseRead(8, 1, &val);
        if (!ret)
        {
            rdc_en                = !!(val & 0x200); /* Only A1 sillicon uses DBD_EN */
            read_dbd_en_from_fuse = true;
        }
    }
    return rdc_en;
}

void BOARD_ReleaseTRDC(void)
{
    uint32_t status;
    if ((releasedTrdc == false) && (BOARD_IsRdcEnabled() == true))
    {
        /* Release TRDC(transfer owner of TRDC from s400 to m33) */
        status = SENTINEL_ReleaseRDC(TRDC_TYPE);
        if (status == BASELINE_SUCCESS_IND)
        {
            releasedTrdc = true;
        }
    }
}

void BOARD_SetTrdcGlobalConfig(void)
{
    uint32_t i = 0, j = 0, m = 0, n = 0;
    trdc_mbc_memory_block_config_t mbcBlockConfig;
    trdc_mrc_region_descriptor_config_t mrcRegionConfig;
    trdc_slave_memory_hardware_config_t mbcHwConfig;

    BOARD_ReleaseTRDC();
    if (releasedTrdc == true)
    {
        /* Ungate TRDC MRC, MBC and DAC PCC */
        TRDC_Init(TRDC);

        /* 1. Get the hardware configuration of the TRDC module */
        trdc_hardware_config_t hwConfig;
        TRDC_GetHardwareConfig(TRDC, &hwConfig);

        /* 2. Set control policies for MRC and MBC access control configuration registers */
        trdc_memory_access_control_config_t memAccessConfig;
        (void)memset(&memAccessConfig, 0, sizeof(memAccessConfig));
#if 0
        /* Disable all access modes for MBC and MRC access control configuration register 1-7. */
        for (i = 0U; i < hwConfig.mbcNumber; i++)
        {
            for (j = 1U; j < 8U; j++)
            {
                TRDC_MbcSetMemoryAccessConfig(TRDC, &memAccessConfig, i, j);
            }
        }

        for (i = 0U; i < hwConfig.mrcNumber; i++)
        {
            for (j = 1U; j < 8U; j++)
            {
                TRDC_MrcSetMemoryAccessConfig(TRDC, &memAccessConfig, i, j);
            }
        }
#endif

#if 1
        /* Enable all access modes for MRC access control configuration register 0. */
        memAccessConfig.nonsecureUsrX  = 1U;
        memAccessConfig.nonsecureUsrW  = 1U;
        memAccessConfig.nonsecureUsrR  = 1U;
        memAccessConfig.nonsecurePrivX = 1U;
        memAccessConfig.nonsecurePrivW = 1U;
        memAccessConfig.nonsecurePrivR = 1U;
        memAccessConfig.secureUsrX     = 1U;
        memAccessConfig.secureUsrW     = 1U;
        memAccessConfig.secureUsrR     = 1U;
        memAccessConfig.securePrivX    = 1U;
        memAccessConfig.securePrivW    = 1U;
        memAccessConfig.securePrivR    = 1U;

        for (i = 0U; i < hwConfig.mrcNumber; i++)
        {
            TRDC_MrcSetMemoryAccessConfig(TRDC, &memAccessConfig, i, TRDC_MRC_ACCESS_CONTROL_POLICY_ALL_INDEX);
        }

        for (i = 0U; i < hwConfig.mbcNumber && i < TRDC_MBC_INDEX_NUM; i++)
        {
            if ((i == TRDC_MBC3_INDEX) &&
                (BOARD_IsFusionAvailable() == false)) /* skip T-MBC3 if Fusion is not available */
            {
                continue;
            }
            TRDC_MbcSetMemoryAccessConfig(TRDC, &memAccessConfig, i, TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX);
        }

        /* 3. Set the configuration for all MRC regions */
        (void)memset(&mrcRegionConfig, 0, sizeof(mrcRegionConfig));
        mrcRegionConfig.memoryAccessControlSelect = TRDC_MRC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mrcRegionConfig.valid                     = true;
        mrcRegionConfig.nseEnable                 = false; /* secure state can access the region */

        for (i = 0; i < hwConfig.mrcNumber; i++)
        {
            mrcRegionConfig.mrcIdx = i;
            for (j = 0; j < hwConfig.domainNumber; j++)
            {
                mrcRegionConfig.domainIdx = j;
                /* Get region number for current MRC instance */
                n = TRDC_GetMrcRegionNumber(TRDC, i);

                /*__IO uint32_t MRC_DOM0_RGD_W[8][2]; n do not more than 8 (coverity check)*/
                if (n > 8)
                {
                    return;
                }

                for (m = 0U; m < n; m++)
                {
                    mrcRegionConfig.regionIdx = m;
                    mrcRegionConfig.startAddr = mrc_start_addr[i] + (mrc_end_addr[i] - mrc_start_addr[i]) / n * m;
                    mrcRegionConfig.endAddr = mrc_start_addr[i] + (mrc_end_addr[i] - mrc_start_addr[i]) / n * (m + 1U);

                    TRDC_MrcSetRegionDescriptorConfig(TRDC, &mrcRegionConfig);
                }
            }
        }

        /* 4. Set the configuration for all MBC slave memory blocks */
        (void)memset(&mbcBlockConfig, 0, sizeof(mbcBlockConfig));
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable                 = false; /* secure state can access the region */

        for (i = 0U; i < hwConfig.mbcNumber && i < TRDC_MBC_INDEX_NUM; i++)
        {
            if ((i == TRDC_MBC3_INDEX) &&
                (BOARD_IsFusionAvailable() == false)) /* skip T-MBC3 if Fusion is not available */
            {
                continue;
            }
            mbcBlockConfig.mbcIdx = i;
            for (j = 0U; j < hwConfig.domainNumber; j++)
            {
                mbcBlockConfig.domainIdx = j;
                for (m = 0U; m < 4; m++)
                {
                    TRDC_GetMbcHardwareConfig(TRDC, &mbcHwConfig, i, m);
                    if (mbcHwConfig.blockNum == 0U)
                    {
                        break;
                    }
                    mbcBlockConfig.slaveMemoryIdx = m;
                    for (n = 0U; n < mbcHwConfig.blockNum; n++)
                    {
                        mbcBlockConfig.memoryBlockIdx = n;

                        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
                    }
                }
            }
        }
#endif

        /* for DMA1, USB0, USB1, ENET, UDSHC0, USDHC1, UDSHC2, CAMM Master(default domain id is 1), default TRDC
         * configuration */
        /* non secure state can access Pbridge1(MBC2_MEM1) for DMA1, USB0, USB1, ENET, UDSHC0, USDHC1, UDSHC2, CAMM
         * Master
         */
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable = true;    /* non secure state can access the block for DMA1, USB0, USB1, ENET, UDSHC0,
                                               USDHC1, UDSHC2, CAMM Master */
        mbcBlockConfig.mbcIdx         = 2U; /* MBC2 */
        mbcBlockConfig.domainIdx      = 1U; /* MBC2_DOM1 */
        mbcBlockConfig.slaveMemoryIdx = 1U; /* MBC2_DOM1_MEM1 */
        TRDC_GetMbcHardwareConfig(TRDC, &mbcHwConfig, mbcBlockConfig.mbcIdx, mbcBlockConfig.slaveMemoryIdx);
        for (n = 0U; n < mbcHwConfig.blockNum; n++)
        {
            mbcBlockConfig.memoryBlockIdx = n; /* MBC2_DOM1_MEM1_BLK_CFG_Wx */
            TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        }

        /* non secure state can access SSRAM(MBC0_MEM2) for DMA1, USB0, USB1, ENET, UDSHC0, USDHC1, UDSHC2, CAMM Master
         */
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable = true;    /* non secure state can access the block for DMA1, USB0, USB1, ENET, UDSHC0,
                                               USDHC1, UDSHC2, CAMM Master */
        mbcBlockConfig.mbcIdx         = 0U; /* MBC0 */
        mbcBlockConfig.domainIdx      = 1U; /* MBC0_DOM1 */
        mbcBlockConfig.slaveMemoryIdx = 2U; /* MBC0_DOM1_MEM2 */
        TRDC_GetMbcHardwareConfig(TRDC, &mbcHwConfig, mbcBlockConfig.mbcIdx, mbcBlockConfig.slaveMemoryIdx);
        for (n = 0U; n < mbcHwConfig.blockNum; n++)
        {
            mbcBlockConfig.memoryBlockIdx = n; /* MBC0_DOM1_MEM2_BLK_CFG_Wx */
            TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        }

        /* Special configurations for cortex-A35 */
        /* non secure state can access 0x1fff8000(it is used for resource table of rpmsg) for cortex-A35 */
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable                 = true; /* non secure state can access the block for cortex-A35 */
        mbcBlockConfig.mbcIdx                    = 0U;   /* MBC0 */
        mbcBlockConfig.domainIdx                 = 7U;   /* MBC0_DOM7 */
        mbcBlockConfig.slaveMemoryIdx            = 2U;   /* MBC0_DOM7_MEM2 */
        mbcBlockConfig.memoryBlockIdx            = 31U;  /* MBC0_DOM7_MEM2_BLK_CFG_W31 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);

        /* non secure state can access CGC0: PBrigge0 slot 47 and PCC0 slot 48 for cortex-A35 */
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable                 = true; /* non secure state can access the block for cortex-A35 */
        mbcBlockConfig.mbcIdx                    = 2U;   /* MBC2 */
        mbcBlockConfig.domainIdx                 = 7U;   /* MBC2_DOM7 */
        mbcBlockConfig.slaveMemoryIdx            = 0U;   /* MBC2_DOM7_MEM0 */
        mbcBlockConfig.memoryBlockIdx            = 47U;  /* MBC2_DOM7_MEM0_BLK_CFG_W47 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        mbcBlockConfig.memoryBlockIdx = 48U;             /* MBC2_DOM7_MEM0_BLK_CFG_W48 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);

        /* non secure state can access CGC0 (Pbridge0, slot 47) for HIFI4 DSP */
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable                 = true; /* non secure state can access the block for HIFI4 DSP */
        mbcBlockConfig.mbcIdx                    = 2U;   /* MBC2 */
        mbcBlockConfig.domainIdx                 = 2U;   /* MBC2_DOM2 */
        mbcBlockConfig.slaveMemoryIdx            = 0U;   /* MBC2_DOM2_MEM0 */
        mbcBlockConfig.memoryBlockIdx            = 47U;  /* MBC2_DOM2_MEM0_BLK_CFG_W47 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);

        /* non secure state can access PCC1(PBridge1 slot 17) and ADC1(PBridge1 slot 34) for cortex-A35 */
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable                 = true; /* non secure state can access the block for cortex-A35 */
        mbcBlockConfig.mbcIdx                    = 2U;   /* MBC2 */
        mbcBlockConfig.domainIdx                 = 7U;   /* MBC2_DOM7 */
        mbcBlockConfig.slaveMemoryIdx            = 1U;   /* MBC2_DOM7_MEM1 */
        mbcBlockConfig.memoryBlockIdx            = 17U;  /* MBC2_DOM7_MEM1_BLK_CFG_W17 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        mbcBlockConfig.memoryBlockIdx = 34U;             /* MBC2_DOM7_MEM1_BLK_CFG_W34 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);

        /* non secure state can access iomuxc0(PBridge1 slot 33) for cortex-A35 */
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable                 = true; /* non secure state can access the block for cortex-A35 */
        mbcBlockConfig.mbcIdx                    = 2U;   /* MBC2 */
        mbcBlockConfig.domainIdx                 = 7U;   /* MBC2_DOM7 */
        mbcBlockConfig.slaveMemoryIdx            = 1U;   /* MBC2_DOM7_MEM1 */
        mbcBlockConfig.memoryBlockIdx            = 33U;  /* MBC2_DOM7_MEM1_BLK_CFG_W33 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);

        /* non secure state can access flexspi0(PBridge0 slot 57 of T-MBC2, also need setup T-MRC0) for cortex-A35 */
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable                 = true; /* non secure state can access the block for cortex-A35 */
        mbcBlockConfig.mbcIdx                    = 2U;   /* MBC2 */
        mbcBlockConfig.domainIdx                 = 7U;   /* MBC2_DOM7 */
        mbcBlockConfig.slaveMemoryIdx            = 0U;   /* MBC2_DOM7_MEM0 */
        mbcBlockConfig.memoryBlockIdx            = 57U;  /* MBC2_DOM7_MEM0_BLK_CFG_W57 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        mrcRegionConfig.memoryAccessControlSelect = TRDC_MRC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mrcRegionConfig.valid                     = true;
        mrcRegionConfig.nseEnable                 = true; /* non secure state can access the region for cortex-A35 */
        mrcRegionConfig.mrcIdx                    = TRDC_MRC0_INDEX;
        mrcRegionConfig.domainIdx                 = 7U;
        /* Get region number for current MRC instance */
        TRDC_GetHardwareConfig(TRDC, &hwConfig);
        for (i = 0; i < hwConfig.mrcNumber; i++)
        {
            if (i == mrcRegionConfig.mrcIdx)
            {
                n = TRDC_GetMrcRegionNumber(TRDC, mrcRegionConfig.mrcIdx);

                /*__IO uint32_t MRC_DOM0_RGD_W[8][2]; n do not more than 8 (coverity check)*/
                if (n > 8)
                {
                    return;
                }

                for (m = 0U; m < n; m++)
                {
                    mrcRegionConfig.regionIdx = m;
                    mrcRegionConfig.startAddr = mrc_start_addr[i] + (mrc_end_addr[i] - mrc_start_addr[i]) / n * m;
                    mrcRegionConfig.endAddr = mrc_start_addr[i] + (mrc_end_addr[i] - mrc_start_addr[i]) / n * (m + 1U);

                    TRDC_MrcSetRegionDescriptorConfig(TRDC, &mrcRegionConfig);
                }
            }
        }

        /* non secure state can access tpm0(PBridge1 slot 21) for cortex-A35 */
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable                 = true; /* non secure state can access the block for cortex-A35 */
        mbcBlockConfig.mbcIdx                    = 2U;   /* MBC2 */
        mbcBlockConfig.domainIdx                 = 7U;   /* MBC2_DOM7 */
        mbcBlockConfig.slaveMemoryIdx            = 1U;   /* MBC2_DOM7_MEM1 */
        mbcBlockConfig.memoryBlockIdx            = 21U;  /* MBC2_DOM7_MEM1_BLK_CFG_W21 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);

        /* non secure state can access lpi2c0(PBridge1 slot 24, T-MBC2) for cortex-A35 */
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable                 = true; /* non secure state can access the block for cortex-A35 */
        mbcBlockConfig.mbcIdx                    = 2U;   /* MBC2 */
        mbcBlockConfig.domainIdx                 = 7U;   /* MBC2_DOM7 */
        mbcBlockConfig.slaveMemoryIdx            = 1U;   /* MBC2_DOM7_MEM1 */
        mbcBlockConfig.memoryBlockIdx            = 24U;  /* MBC2_DOM7_MEM1_BLK_CFG_W24 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);

        /* non secure state can access FSB(Sentinel slot 1, T-MBC2) and S400 MUAP A-side(Sentinel slot 2, T-MBC2) for
         * cortex-A35 */
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable                 = true; /* non secure state can access the block for cortex-A35 */
        mbcBlockConfig.mbcIdx                    = 2U;   /* MBC2 */
        mbcBlockConfig.domainIdx                 = 7U;   /* MBC2_DOM7 */
        mbcBlockConfig.slaveMemoryIdx            = 3U;   /* MBC2_DOM7_MEM3, slave memoty is sentinel */
        mbcBlockConfig.memoryBlockIdx            = 1U;   /* MBC2_DOM7_MEM3_BLK_CFG_W1 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        mbcBlockConfig.memoryBlockIdx = 2U;              /* MBC2_DOM7_MEM3_BLK_CFG_W2 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);

        /* non secure state can access RTD_SIM_SEC(PBridge0 slot 43, T-MBC2) for cortex-A35 */
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable                 = true; /* non secure state can access the block for cortex-A35 */
        mbcBlockConfig.mbcIdx                    = 2U;   /* MBC2 */
        mbcBlockConfig.domainIdx                 = 7U;   /* MBC2_DOM7 */
        mbcBlockConfig.slaveMemoryIdx            = 0U;   /* MBC2_DOM7_MEM0, slave memoty is PBridge0 */
        mbcBlockConfig.memoryBlockIdx            = 43U;  /* MBC2_DOM7_MEM0_BLK_CFG_W43 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);

        /* non secure state can access SEMA42[0](PBridge0 slot 55, T-MBC2) for cortex-A35 */
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable                 = true; /* non secure state can access the block for cortex-A35 */
        mbcBlockConfig.mbcIdx                    = 2U;   /* MBC2 */
        mbcBlockConfig.domainIdx                 = 7U;   /* MBC2_DOM7 */
        mbcBlockConfig.slaveMemoryIdx            = 0U;   /* MBC2_DOM7_MEM0, slave memoty is PBridge0 */
        mbcBlockConfig.memoryBlockIdx            = 55U;  /* MBC2_DOM7_MEM0_BLK_CFG_W55 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);

        /* non secure state can access flexspi0(PBridge0 slot 57 of T-MBC2, also need setup T-MRC0) for eDMA0 */
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable                 = true; /* non secure state can access the block for eDMA0 */
        mbcBlockConfig.mbcIdx                    = 2U;   /* MBC2 */
        mbcBlockConfig.domainIdx                 = TRDC_DMA0_DOMAIN_ID; /* MBC2_DOM0 */
        mbcBlockConfig.slaveMemoryIdx            = 0U;                  /* MBC2_DOM0_MEM0 */
        mbcBlockConfig.memoryBlockIdx            = 57U;                 /* MBC2_DOM0_MEM0_BLK_CFG_W57 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        mrcRegionConfig.memoryAccessControlSelect = TRDC_MRC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mrcRegionConfig.valid                     = true;
        mrcRegionConfig.nseEnable                 = true; /* non secure state can access the region for eDMA0 */
        mrcRegionConfig.mrcIdx                    = TRDC_MRC0_INDEX;
        mrcRegionConfig.domainIdx                 = TRDC_DMA0_DOMAIN_ID;
        /* Get region number for current MRC instance */
        TRDC_GetHardwareConfig(TRDC, &hwConfig);
        for (i = 0; i < hwConfig.mrcNumber; i++)
        {
            if (i == mrcRegionConfig.mrcIdx)
            {
                n = TRDC_GetMrcRegionNumber(TRDC, mrcRegionConfig.mrcIdx);

                /*__IO uint32_t MRC_DOM0_RGD_W[8][2]; n do not more than 8 (coverity check)*/
                if (n > 8)
                {
                    return;
                }

                for (m = 0U; m < n; m++)
                {
                    mrcRegionConfig.regionIdx = m;
                    mrcRegionConfig.startAddr = mrc_start_addr[i] + (mrc_end_addr[i] - mrc_start_addr[i]) / n * m;
                    mrcRegionConfig.endAddr = mrc_start_addr[i] + (mrc_end_addr[i] - mrc_start_addr[i]) / n * (m + 1U);

                    TRDC_MrcSetRegionDescriptorConfig(TRDC, &mrcRegionConfig);
                }
            }
        }

        /* non secure state can access flexspi1(PBridge1 slot 18 of T-MBC2, also need setup T-MRC1) for eDMA0 */
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable                 = true; /* non secure state can access the block for eDMA0 */
        mbcBlockConfig.mbcIdx                    = 2U;   /* MBC2 */
        mbcBlockConfig.domainIdx                 = TRDC_DMA0_DOMAIN_ID; /* MBC2_DOM0 */
        mbcBlockConfig.slaveMemoryIdx            = 1U;                  /* MBC2_DOM0_MEM1 */
        mbcBlockConfig.memoryBlockIdx            = 18U;                 /* MBC2_DOM0_MEM1_BLK_CFG_W18 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        mrcRegionConfig.memoryAccessControlSelect = TRDC_MRC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mrcRegionConfig.valid                     = true;
        mrcRegionConfig.nseEnable                 = true; /* non secure state can access the region for eDMA0 */
        mrcRegionConfig.mrcIdx                    = TRDC_MRC1_INDEX;
        mrcRegionConfig.domainIdx                 = TRDC_DMA0_DOMAIN_ID;
        /* Get region number for current MRC instance */
        TRDC_GetHardwareConfig(TRDC, &hwConfig);
        for (i = 0; i < hwConfig.mrcNumber; i++)
        {
            if (i == mrcRegionConfig.mrcIdx)
            {
                n = TRDC_GetMrcRegionNumber(TRDC, mrcRegionConfig.mrcIdx);

                /*__IO uint32_t MRC_DOM0_RGD_W[8][2]; n do not more than 8 (coverity check)*/
                if (n > 8)
                {
                    return;
                }

                for (m = 0U; m < n; m++)
                {
                    mrcRegionConfig.regionIdx = m;
                    mrcRegionConfig.startAddr = mrc_start_addr[i] + (mrc_end_addr[i] - mrc_start_addr[i]) / n * m;
                    mrcRegionConfig.endAddr = mrc_start_addr[i] + (mrc_end_addr[i] - mrc_start_addr[i]) / n * (m + 1U);

                    TRDC_MrcSetRegionDescriptorConfig(TRDC, &mrcRegionConfig);
                }
            }
        }

        /* non secure state can access flexspi1(PBridge1 slot 18 of T-MBC2, also need setup T-MRC1) for DCNANO */
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable                 = true; /* non secure state can access the block for DCNANO */
        mbcBlockConfig.mbcIdx                    = 2U;   /* MBC2 */
        mbcBlockConfig.domainIdx                 = TRDC_DCNANO_DOMAIN_ID; /* MBC2_DOM3 */
        mbcBlockConfig.slaveMemoryIdx            = 1U;                    /* MBC2_DOM0_MEM1 */
        mbcBlockConfig.memoryBlockIdx            = 18U;                   /* MBC2_DOM0_MEM1_BLK_CFG_W18 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        mrcRegionConfig.memoryAccessControlSelect = TRDC_MRC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mrcRegionConfig.valid                     = true;
        mrcRegionConfig.nseEnable                 = true; /* non secure state can access the region for DCNANO */
        mrcRegionConfig.mrcIdx                    = 1;
        mrcRegionConfig.domainIdx                 = TRDC_DCNANO_DOMAIN_ID;
        /* Get region number for current MRC instance */
        TRDC_GetHardwareConfig(TRDC, &hwConfig);
        for (i = 0; i < hwConfig.mrcNumber; i++)
        {
            if (i == TRDC_MRC1_INDEX)
            {
                n = TRDC_GetMrcRegionNumber(TRDC, mrcRegionConfig.mrcIdx);

                /*__IO uint32_t MRC_DOM0_RGD_W[8][2]; n do not more than 8 (coverity check)*/
                if (n > 8)
                {
                    return;
                }

                for (m = 0U; m < n; m++)
                {
                    mrcRegionConfig.regionIdx = m;
                    mrcRegionConfig.startAddr = mrc_start_addr[i] + (mrc_end_addr[i] - mrc_start_addr[i]) / n * m;
                    mrcRegionConfig.endAddr = mrc_start_addr[i] + (mrc_end_addr[i] - mrc_start_addr[i]) / n * (m + 1U);

                    TRDC_MrcSetRegionDescriptorConfig(TRDC, &mrcRegionConfig);
                }
            }
        }

        /* non secure state can access sai0(PBridge1 slot 28, T-MBC2) for eDMA0 */
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable                 = true; /* non secure state can access the block for eDMA0 */
        mbcBlockConfig.mbcIdx                    = 2U;   /* MBC2 */
        mbcBlockConfig.domainIdx                 = TRDC_DMA0_DOMAIN_ID; /* MBC2_DOM0 */
        mbcBlockConfig.slaveMemoryIdx            = 1U;                  /* MBC2_DOM0_MEM1 */
        mbcBlockConfig.memoryBlockIdx            = 28U;                 /* MBC2_DOM0_MEM1_BLK_CFG_W28 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);

        /* non secure state can access lpi2c0(PBridge1 slot 24, T-MBC2) for eDMA0 */
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable                 = true; /* non secure state can access the block for eDMA0 */
        mbcBlockConfig.mbcIdx                    = 2U;   /* MBC2 */
        mbcBlockConfig.domainIdx                 = TRDC_DMA0_DOMAIN_ID; /* MBC2_DOM0 */
        mbcBlockConfig.slaveMemoryIdx            = 1U;                  /* MBC2_DOM0_MEM1 */
        mbcBlockConfig.memoryBlockIdx            = 24U;                 /* MBC2_DOM0_MEM1_BLK_CFG_W24 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);

        /* non secure state can access lpspi1(PBridge0 slot 63, T-MBC2) for eDMA0 */
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable                 = true; /* non secure state can access the block for eDMA0 */
        mbcBlockConfig.mbcIdx                    = 2U;   /* MBC2 */
        mbcBlockConfig.domainIdx                 = TRDC_DMA0_DOMAIN_ID; /* MBC2_DOM0 */
        mbcBlockConfig.slaveMemoryIdx            = 0U;                  /* MBC2_DOM0_MEM0 */
        mbcBlockConfig.memoryBlockIdx            = 63U;                 /* MBC2_DOM0_MEM0_BLK_CFG_W63 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);

        /* non secure state can access flexio0(PBridge0 slot 60, T-MBC2) for eDMA0 */
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable                 = true; /* non secure state can access the block for eDMA0 */
        mbcBlockConfig.mbcIdx                    = 2U;   /* MBC2 */
        mbcBlockConfig.domainIdx                 = TRDC_DMA0_DOMAIN_ID; /* MBC2_DOM0 */
        mbcBlockConfig.slaveMemoryIdx            = 0U;                  /* MBC2_DOM0_MEM0 */
        mbcBlockConfig.memoryBlockIdx            = 60U;                 /* MBC2_DOM0_MEM0_BLK_CFG_W60 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);

        /* non secure state can access lpuart1(PBridge1 slot 27, T-MBC2) for eDMA0 */
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable                 = true; /* non secure state can access the block for eDMA0 */
        mbcBlockConfig.mbcIdx                    = 2U;   /* MBC2 */
        mbcBlockConfig.domainIdx                 = TRDC_DMA0_DOMAIN_ID; /* MBC2_DOM0 */
        mbcBlockConfig.slaveMemoryIdx            = 1U;                  /* MBC2_DOM0_MEM1 */
        mbcBlockConfig.memoryBlockIdx            = 27U;                 /* MBC2_DOM0_MEM1_BLK_CFG_W27 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);

        /* non secure state can access flexcan0(PBridge1 slot 40~43, T-MBC2) for eDMA0 */
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable                 = true; /* non secure state can access the block for eDMA0 */
        mbcBlockConfig.mbcIdx                    = 2U;   /* MBC2 */
        mbcBlockConfig.domainIdx                 = TRDC_DMA0_DOMAIN_ID; /* MBC2_DOM0 */
        mbcBlockConfig.slaveMemoryIdx            = 1U;                  /* MBC2_DOM0_MEM1 */
        mbcBlockConfig.memoryBlockIdx            = 40U;                 /* MBC2_DOM0_MEM1_BLK_CFG_W40 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        mbcBlockConfig.memoryBlockIdx = 41U;                            /* MBC2_DOM0_MEM1_BLK_CFG_W41 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        mbcBlockConfig.memoryBlockIdx = 42U;                            /* MBC2_DOM0_MEM1_BLK_CFG_W42 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        mbcBlockConfig.memoryBlockIdx = 43U;                            /* MBC2_DOM0_MEM1_BLK_CFG_W43 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);

        /* non secure state can access ssram(T-MBC0) for eDMA0 */
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable                 = true; /* non secure state can access the block for eDMA0 */
        mbcBlockConfig.mbcIdx                    = 0U;   /* MBC0 */
        mbcBlockConfig.domainIdx                 = TRDC_DMA0_DOMAIN_ID; /* MBC0_DOM0 */
        mbcBlockConfig.slaveMemoryIdx            = 2U;                  /* MBC0_DOM0_MEM2 */
        /* 0x20000000 ~ 0x20007FFF (SSRAM P0), slot number 0 */
        mbcBlockConfig.memoryBlockIdx = 0U; /* MBC0_DOM0_MEM2_BLK_CFG_W0 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        /* 0x20008000 ~ 0x2000FFFF (SSRAM P1), slot number 1 */
        mbcBlockConfig.memoryBlockIdx = 1U; /* MBC0_DOM0_MEM2_BLK_CFG_W1 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        /* 0x20010000 ~ 0x20017FFF (SSRAM P2), slot number 2 */
        mbcBlockConfig.memoryBlockIdx = 2U; /* MBC0_DOM0_MEM2_BLK_CFG_W2 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        /* 0x20018000 ~ 0x2001FFFF (SSRAM P2), slot number 3 */
        mbcBlockConfig.memoryBlockIdx = 3U; /* MBC0_DOM0_MEM2_BLK_CFG_W3 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        /* 0x20020000 ~ 0x20027FFF (SSRAM P3), slot number 4 */
        mbcBlockConfig.memoryBlockIdx = 4U; /* MBC0_DOM0_MEM2_BLK_CFG_W4 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        /* 0x20028000 ~ 0x2002FFFF (SSRAM P3), slot number 5 */
        mbcBlockConfig.memoryBlockIdx = 5U; /* MBC0_DOM0_MEM2_BLK_CFG_W5 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        /* 0x20030000 ~ 0x20037FFF (SSRAM P4), slot number 6 */
        mbcBlockConfig.memoryBlockIdx = 6U; /* MBC0_DOM0_MEM2_BLK_CFG_W6 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        /* 0x20038000 ~ 0x2003FFFF (SSRAM P4), slot number 7 */
        mbcBlockConfig.memoryBlockIdx = 7U; /* MBC0_DOM0_MEM2_BLK_CFG_W7 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        /* 0x20040000 ~ 0x20047FFF (SSRAM P5), slot number 8 */
        mbcBlockConfig.memoryBlockIdx = 8U; /* MBC0_DOM0_MEM2_BLK_CFG_W8 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        /* 0x20048000 ~ 0x2004FFFF (SSRAM P5), slot number 9 */
        mbcBlockConfig.memoryBlockIdx = 9U; /* MBC0_DOM0_MEM2_BLK_CFG_W9 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        /* 0x20050000 ~ 0x20057FFF (SSRAM P5), slot number 10 */
        mbcBlockConfig.memoryBlockIdx = 10U; /* MBC0_DOM0_MEM2_BLK_CFG_W10 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        /* 0x20058000 ~ 0x2005FFFF (SSRAM P5), slot number 11 */
        mbcBlockConfig.memoryBlockIdx = 11U; /* MBC0_DOM0_MEM2_BLK_CFG_W11 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        /* 0x20060000 ~ 0x20067FFF (SSRAM P6), slot number 12 */
        mbcBlockConfig.memoryBlockIdx = 12U; /* MBC0_DOM0_MEM2_BLK_CFG_W12 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        /* 0x20068000 ~ 0x2006FFFF (SSRAM P6), slot number 13 */
        mbcBlockConfig.memoryBlockIdx = 13U; /* MBC0_DOM0_MEM2_BLK_CFG_W13 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        /* 0x20070000 ~ 0x20077FFF (SSRAM P6), slot number 14 */
        mbcBlockConfig.memoryBlockIdx = 14U; /* MBC0_DOM0_MEM2_BLK_CFG_W14 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        /* 0x20078000 ~ 0x2007FFFF (SSRAM P6), slot number 15 */
        mbcBlockConfig.memoryBlockIdx = 15U; /* MBC0_DOM0_MEM2_BLK_CFG_W15 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);

        /* 0x0ffc0000 ~ 0x0ffc7fff (SSRAM P7), slot number 24 */
        mbcBlockConfig.memoryBlockIdx = 24U; /* MBC0_DOM0_MEM2_BLK_CFG_W24 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        /* 0x0ffc8000 ~ 0x0ffcffff (SSRAM P7), slot number 25 */
        mbcBlockConfig.memoryBlockIdx = 25U; /* MBC0_DOM0_MEM2_BLK_CFG_W25 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        /* 0x0ffd0000 ~ 0x0ffd7fff (SSRAM P7), slot number 26 */
        mbcBlockConfig.memoryBlockIdx = 26U; /* MBC0_DOM0_MEM2_BLK_CFG_W26 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        /* 0x0ffd8000 ~ 0x0ffdffff (SSRAM P7), slot number 27 */
        mbcBlockConfig.memoryBlockIdx = 27U; /* MBC0_DOM0_MEM2_BLK_CFG_W27 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        /* 0x0ffe0000 ~ 0x0ffe7fff (SSRAM P7), slot number 28 */
        mbcBlockConfig.memoryBlockIdx = 28U; /* MBC0_DOM0_MEM2_BLK_CFG_W28 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        /* 0x0ffe8000 ~ 0x0ffeffff (SSRAM P7), slot number 29 */
        mbcBlockConfig.memoryBlockIdx = 29U; /* MBC0_DOM0_MEM2_BLK_CFG_W29 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        /* 0x0fff0000 ~ 0x0fff7fff (SSRAM P7), slot number 30 */
        mbcBlockConfig.memoryBlockIdx = 30U; /* MBC0_DOM0_MEM2_BLK_CFG_W30 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        /* 0x0fff8000 ~ 0x0fffffff (SSRAM P7), slot number 31 */
        mbcBlockConfig.memoryBlockIdx = 31U; /* MBC0_DOM0_MEM2_BLK_CFG_W31 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);

        if (BOARD_IsFusionAvailable() == true)
        {
            /* non secure state can access MICFIL(T-MBC3) for eDMA0 */
            mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
            mbcBlockConfig.nseEnable                 = true; /* non secure state can access the block for eDMA0 */
            mbcBlockConfig.mbcIdx                    = 3U;   /* MBC3 */
            mbcBlockConfig.domainIdx                 = TRDC_DMA0_DOMAIN_ID; /* MBC3_DOM0 */
            mbcBlockConfig.slaveMemoryIdx            = 0U;                  /* MBC3_DOM0_MEM0 */
            mbcBlockConfig.memoryBlockIdx            = 17U;                 /* MBC3_DOM0_MEM0_BLK_CFG_W17 */
            TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        }

        TRDC_SetMbcGlobalValid(TRDC);
        TRDC_SetMrcGlobalValid(TRDC);

#if 0
        /* 5. Assign domain ID for m33  */
        trdc_processor_domain_assignment_t domainAssignment;

        TRDC_GetDefaultProcessorDomainAssignment(&domainAssignment);
        domainAssignment.domainId = TRDC_M33_DOMAIN_ID;

        TRDC_SetProcessorDomainAssignment(TRDC, &domainAssignment);
#endif

        /* 6. Assign domain ID for DMA0(T-MDAC2),Powerquad(T-MDAC0) */
        trdc_non_processor_domain_assignment_t nonProcessorDomainAssignment;
        TRDC_GetDefaultNonProcessorDomainAssignment(&nonProcessorDomainAssignment);
        nonProcessorDomainAssignment.privilegeAttr = kTRDC_ForcePrivilege;
        nonProcessorDomainAssignment.secureAttr    = kTRDC_ForceNonSecure;
        nonProcessorDomainAssignment.domainId      = TRDC_DMA0_DOMAIN_ID;
        TRDC_SetNonProcessorDomainAssignment(TRDC, TRDC_DMA0_MASTER_ID, &nonProcessorDomainAssignment);
        nonProcessorDomainAssignment.domainId = TRDC_POWERQUAD_DOMAIN_ID;
        TRDC_SetNonProcessorDomainAssignment(TRDC, TRDC_POWERQUAD_MASTER_ID, &nonProcessorDomainAssignment);

        TRDC_SetDacGlobalValid(TRDC);

        /* dump TRDC registers */
        BOARD_DumpRegs(0x28032020, 0x2803203c);
        BOARD_DumpRegs(0x28032fa8, 0x28032fb4);
    }
}

/* Setup TRDC configuration before executing rom code of A35(A35 rom will access FSB, S400 MUAP A-Side, SIM0-S with
 * secure state, so m33 help a35 to configure TRDC) */
void BOARD_SetTrdcAfterApdReset(void)
{
    trdc_mbc_memory_block_config_t mbcBlockConfig;

    BOARD_ReleaseTRDC();
    if (releasedTrdc == true)
    {
        /* secure state can access FSB(Sentinel slot 1, T-MBC2) and S400 MUAP A-side(Sentinel slot 2, T-MBC2) for
         * cortex-A35
         */
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable                 = false; /* secure state can access the block for cortex-A35 */
        mbcBlockConfig.mbcIdx                    = 2U;    /* MBC2 */
        mbcBlockConfig.domainIdx                 = 7U;    /* MBC2_DOM7 */
        mbcBlockConfig.slaveMemoryIdx            = 3U;    /* MBC2_DOM7_MEM3, slave memoty is sentinel */
        mbcBlockConfig.memoryBlockIdx            = 1U;    /* MBC2_DOM7_MEM3_BLK_CFG_W1 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        mbcBlockConfig.memoryBlockIdx = 2U;               /* MBC2_DOM7_MEM3_BLK_CFG_W2 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);

        /* secure state can access RTD_SIM_SEC(PBridge0 slot 43, T-MBC2) for cortex-A35 */
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable                 = false; /* secure state can access the block for cortex-A35 */
        mbcBlockConfig.mbcIdx                    = 2U;    /* MBC2 */
        mbcBlockConfig.domainIdx                 = 7U;    /* MBC2_DOM7 */
        mbcBlockConfig.slaveMemoryIdx            = 0U;    /* MBC2_DOM7_MEM0, slave memoty is PBridge0 */
        mbcBlockConfig.memoryBlockIdx            = 43U;   /* MBC2_DOM7_MEM0_BLK_CFG_W43 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);

        /* secure state can access CGC0: PBrigge0 slot 47 and PCC0 slot 48 for cortex-A35 */
        mbcBlockConfig.memoryAccessControlSelect = TRDC_MBC_ACCESS_CONTROL_POLICY_ALL_INDEX;
        mbcBlockConfig.nseEnable                 = false; /* secure state can access the block for cortex-A35 */
        mbcBlockConfig.mbcIdx                    = 2U;    /* MBC2 */
        mbcBlockConfig.domainIdx                 = 7U;    /* MBC2_DOM7 */
        mbcBlockConfig.slaveMemoryIdx            = 0U;    /* MBC2_DOM7_MEM0 */
        mbcBlockConfig.memoryBlockIdx            = 47U;   /* MBC2_DOM7_MEM0_BLK_CFG_W47 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
        mbcBlockConfig.memoryBlockIdx = 48U;              /* MBC2_DOM7_MEM0_BLK_CFG_W48 */
        TRDC_MbcSetMemoryBlockConfig(TRDC, &mbcBlockConfig);
    }
}

/* true: low power boot type; false: not low power boot type(such as: single boot type, dual boot type) */
bool BOARD_IsLowPowerBootType(void)
{
    /*
     * BOOTCFG[0](BT0_CFG0)
     * dgo_gp5[15:0] = cmc0_mr[15:0] | 0x0100, dgo[31:16] = cmc1_mr[15:0] | 0x0001
     * 0: No Low Power Boot
     * 1: Boot from M33 with A35 on demand
     */
    return SIM_SEC->DGO_GP5 & CMC_MR_BOOTCFG(1);
}

/* true: RTD hold LPAV, false: APD hold LPAV */
bool BOARD_IsLPAVOwnedByRTD(void)
{
    return !(SIM_SEC->SYSCTRL0 & SIM_SEC_SYSCTRL0_LPAV_MASTER_CTRL(1));
}

/* true: Single Boot type; false: not Single Boot type(such as: Low Power Boot type, Dual Boot type) */
bool BOARD_IsSingleBootType(void)
{
    /*
     * BOOTCFG[0](BT0_CFG0)
     * dgo_gp5[15:0] = cmc0_mr[15:0] | 0x0100, dgo[31:16] = cmc1_mr[15:0] | 0x0001
     * 0: No Single Boot
     * 1: Single Boot
     */
    return !(SIM_SEC->DGO_GP5 & CMC_MR_BOOTCFG(3));
}

const char *BOARD_GetBootTypeName(void)
{
    boot_type_e bootType = SINGLE_BOOT_TYPE;

    if (BOARD_IsSingleBootType())
    {
        bootType = SINGLE_BOOT_TYPE;
    }
    else if (BOARD_IsLowPowerBootType())
    {
        bootType = LOW_POWER_BOOT_TYPE;
    }
    else
    {
        bootType = DUAL_BOOT_TYPE;
    }

    return s_bootTypeNames[bootType];
}
/*
 * return the handshake result(fail or success):
 * true: succeeded to handshake with uboot; false: failed to handshake with uboot
 */
bool BOARD_HandshakeWithUboot(void)
{
#ifdef SDK_OS_FREE_RTOS
    TickType_t xTicksToWait = pdMS_TO_TICKS(BOARD_HANDSHAKE_WITH_UBOOT_TIMEOUT_MS);
    TickType_t currTick     = xTaskGetTickCount();
#else
    uint64_t timeout_time = BOARD_HANDSHAKE_WITH_UBOOT_TIMEOUT_MS * 1000; /* us */
    uint64_t curr_time    = 0U;
#endif
    bool state = false;

    /*
     * Wait MU0_MUA FSR F0 flag is set by uboot
     *
     * handshake procedure as follows:
     * a35(set flag F0 of MU0_MUB) --- ready to do MU communication(also indicates MIPI DSI panel ready) ---> m33
     * a35 <--------------- ACK ----------------------------------------------------------------------------> m33 (get
     * flag F0 of MU0_MUA,  and set flag F0 of MU0_MUA) a35(clear flag F0 of MU0_MUB)
     * -----------------------------------------------------------------------> m33 a35
     * <------------------------------------------------------------------------------------------------> m33 (get flag
     * F0 of MU0_MUA and clear flag F0 of MU0_MUA)
     *
     * (uboot will set MU0_MUB FCR F0 flag in board_init(), board/freescale/imx8ulp_evk/imx8ulp_evk.c,
     * after uboot set MU0_MUB FCR F0 flag, the flag will be shown in MU0_MUA FSR)
     */
    /* enable clock of MU0_MUA before accessing registers of MU0_MUA */
    MU_Init(MU0_MUA);
    while (true)
    {
        if (MU_GetFlags(MU0_MUA) & BOARD_MU0_MUB_F0_INIT_SRTM_COMMUNICATION_FLG)
        {
            /* Set FCR F0 flag of MU0_MUA to notify uboot to clear FCR F0 flag of MU0_MUB */
            MU_SetFlags(MU0_MUA, BOARD_MU0_MUB_F0_INIT_SRTM_COMMUNICATION_FLG);
            BOARD_SetTrdcGlobalConfig();
            break;
        }

#ifdef SDK_OS_FREE_RTOS
        vTaskDelay(pdMS_TO_TICKS(BOARD_WAIT_MU0_MUB_F0_FLG_FROM_UBOOT_MS));
        if (currTick + xTicksToWait < xTaskGetTickCount())
#else
        SDK_DelayAtLeastUs(BOARD_WAIT_MU0_MUB_F0_FLG_FROM_UBOOT_MS * 1000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
        curr_time += BOARD_WAIT_MU0_MUB_F0_FLG_FROM_UBOOT_MS * 1000;
        if (curr_time > timeout_time) /* when time out */
#endif
        {
            PRINTF("\r\n %s: %d handshake with uboot timeout\r\n", __func__, __LINE__);
            return state;
        }
    }

    /*
     * Wait uboot to clear the FCR F0 flag of MU0_MUB
     * Clear FCR F0 flag of MU0_MUA after uboot have cleared the FCR
     * F0 flag of MU0_MUB
     */

#ifdef SDK_OS_FREE_RTOS
    currTick = xTaskGetTickCount(); /* update currTick */
#else
    curr_time = 0UL;
#endif
    while (true)
    {
        if ((MU_GetFlags(MU0_MUA) & BOARD_MU0_MUB_F0_INIT_SRTM_COMMUNICATION_FLG) == 0)
        {
            MU_SetFlags(MU0_MUA, 0);
            state = true;
            break;
        }
#ifdef SDK_OS_FREE_RTOS
        vTaskDelay(pdMS_TO_TICKS(BOARD_WAIT_MU0_MUB_F0_FLG_FROM_UBOOT_MS));
        if (currTick + xTicksToWait < xTaskGetTickCount())
#else
        SDK_DelayAtLeastUs(BOARD_WAIT_MU0_MUB_F0_FLG_FROM_UBOOT_MS * 1000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
        curr_time += BOARD_WAIT_MU0_MUB_F0_FLG_FROM_UBOOT_MS * 1000;
        if (curr_time > timeout_time) /* when time out */
#endif
        {
            PRINTF("\r\n %s: %d handshake with uboot timeout\r\n", __func__, __LINE__);
            MU_SetFlags(MU0_MUA, 0); /* clear flag */
            break;
        }
    }
    return state;
}

void BOARD_ConfigMPU(void)
{
    uint8_t attr;

    /* Disable MPU */
    ARM_MPU_Disable();

    /* Attr0: device memory. */
    ARM_MPU_SetMemAttr(0U, ARM_MPU_ATTR(ARM_MPU_ATTR_DEVICE, ARM_MPU_ATTR_DEVICE));

    /* Attr1: non cacheable, normal memory */
    ARM_MPU_SetMemAttr(1U, ARM_MPU_ATTR(ARM_MPU_ATTR_NON_CACHEABLE, ARM_MPU_ATTR_NON_CACHEABLE));

    /* Attr2: transient, write through, read allocate, normal memory */
    attr = ARM_MPU_ATTR_MEMORY_(0U, 0U, 1U, 0U);
    ARM_MPU_SetMemAttr(2U, ARM_MPU_ATTR(attr, attr));

    /* Attr3: transient, write back, read/write allocate, normal memory */
    attr = ARM_MPU_ATTR_MEMORY_(0U, 1U, 1U, 1U);
    ARM_MPU_SetMemAttr(3U, ARM_MPU_ATTR(attr, attr));

    /* NOTE1: All SSRAM/TCRAMU/TCRAML is non-cacheable regardless of MPU setting. */
    /* NOTE2: [0x0, 0x1FFFFFFF] cannot support write back. */
    /* Region 0: [0x0, 0x1FFFFFFF](FlexSPI0 is also in the range), non-shareable, read/write, any privileged,
     * executable. Attr 2 (write through). */
    ARM_MPU_SetRegion(0U, ARM_MPU_RBAR(0U, ARM_MPU_SH_NON, 0U, 1U, 0U), ARM_MPU_RLAR(0x1FFFFFFFU, 2U));

    /* NOTE1: All SSRAM/TCRAMU/TCRAML is non-cacheable regardless of MPU setting. */
    /* Region 1: [0x20000000, 0x20037FFF](m_m33_suspend_ram, m_a35_suspend_ram, m_data, m_ncache, Non-Secure),
     * non-shareable, read/write, any privileged, executable. Attr 3 (write back). */
    ARM_MPU_SetRegion(1U, ARM_MPU_RBAR(0x20000000U, ARM_MPU_SH_NON, 0U, 1U, 0U), ARM_MPU_RLAR(0x20037FFFU, 3U));

    /* NOTE1: All SSRAM/TCRAMU/TCRAML is non-cacheable regardless of MPU setting. */
    /* Region 2: [0x27000000, 0x2FFFFFFF](pheripheral, Non-Secure), non-shareable, read/write, any privileged,
     * executable. Attr 0 (device). */
    ARM_MPU_SetRegion(2U, ARM_MPU_RBAR(0x27000000U, ARM_MPU_SH_NON, 0U, 1U, 0U), ARM_MPU_RLAR(0x2FFFFFFFU, 0U));

    /* NOTE1: All SSRAM/TCRAMU/TCRAML is non-cacheable regardless of MPU setting. */
    /* Region 3: [0x30000000, 0x30037FFF](m_m33_suspend_ram, m_a35_suspend_ram, m_data, m_ncache, Secure),
     * non-shareable, read/write, any privileged, executable. Attr 3 (write back). */
    ARM_MPU_SetRegion(3U, ARM_MPU_RBAR(0x30000000U, ARM_MPU_SH_NON, 0U, 1U, 0U), ARM_MPU_RLAR(0x30037FFFU, 3U));

    /* NOTE1: All SSRAM/TCRAMU/TCRAML is non-cacheable regardless of MPU setting. */
    /* Region 4: [0x37000000, 0x3FFFFFFF](pheripheral, Secure), non-shareable, read/write, any privileged,
     * executable. Attr 0 (device). */
    ARM_MPU_SetRegion(4U, ARM_MPU_RBAR(0x37000000U, ARM_MPU_SH_NON, 0U, 1U, 0U), ARM_MPU_RLAR(0x3FFFFFFFU, 0U));

    /* Region 5 (FlexSPI1,2): [0x40000000, 0x7FFFFFFF], non-shareable, read/write, any privileged, executable. Attr 3
     * (write back). */
    ARM_MPU_SetRegion(5U, ARM_MPU_RBAR(0x40000000, ARM_MPU_SH_NON, 0U, 1U, 0U), ARM_MPU_RLAR(0x7FFFFFFF, 3U));

    /* NOTE: DDR is used as shared memory for A/M core communication, set it to non-cacheable. */
    /* Region 6 (DDR): [0x80000000, 0xDFFFFFFF], outer shareable, read/write, any privileged, executable. Attr 1
     * (non-cacheable). */
    ARM_MPU_SetRegion(6U, ARM_MPU_RBAR(0x80000000, ARM_MPU_SH_OUTER, 0U, 1U, 0U), ARM_MPU_RLAR(0xDFFFFFFF, 1U));

    /* Enable MPU */
    ARM_MPU_Enable(MPU_CTRL_HFNMIENA_Msk | MPU_CTRL_PRIVDEFENA_Msk);

    CACHE64_EnableCache(CACHE64_CTRL0); /* enable code bus cache(I-Cache) */
    CACHE64_EnableCache(CACHE64_CTRL1); /* enable system bus cache(D-Cache) */
    /* flush pipeline */
    __DSB();
    __ISB();
}

static status_t flexspi_hyper_ram_write_mcr(FLEXSPI_Type *base, uint8_t regAddr, uint32_t *mrVal)
{
    flexspi_transfer_t flashXfer;
    status_t status;

    /* Write data */
    flashXfer.deviceAddress = regAddr;
    flashXfer.port          = kFLEXSPI_PortA1;
    flashXfer.cmdType       = kFLEXSPI_Write;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = 3;
    flashXfer.data          = mrVal;
    flashXfer.dataSize      = 1;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);

    return status;
}

static status_t flexspi_hyper_ram_get_mcr(FLEXSPI_Type *base, uint8_t regAddr, uint32_t *mrVal)
{
    flexspi_transfer_t flashXfer;
    status_t status;

    /* Read data */
    flashXfer.deviceAddress = regAddr;
    flashXfer.port          = kFLEXSPI_PortA1;
    flashXfer.cmdType       = kFLEXSPI_Read;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = 2;
    flashXfer.data          = mrVal;
    flashXfer.dataSize      = 2;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);

    return status;
}

static status_t flexspi_hyper_ram_reset(FLEXSPI_Type *base)
{
    flexspi_transfer_t flashXfer;
    status_t status;

    /* Write data */
    flashXfer.deviceAddress = 0x0U;
    flashXfer.port          = kFLEXSPI_PortA1;
    flashXfer.cmdType       = kFLEXSPI_Command;
    flashXfer.SeqNumber     = 1;
    flashXfer.seqIndex      = 4;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);

    if (status == kStatus_Success)
    {
        /* for loop of 50000 is about 1ms (@200 MHz CPU) */
        for (uint32_t i = 2000000U; i > 0; i--)
        {
            __NOP();
        }
    }
    return status;
}

/* Initialize psram. */
status_t BOARD_InitPsRam(void)
{
    flexspi_device_config_t deviceconfig = {
        .flexspiRootClk       = 392000000, /* 392MHZ SPI serial clock, DDR serial clock 196M */
        .isSck2Enabled        = false,
        .flashSize            = 0x2000,    /* 64Mb/KByte */
        .CSIntervalUnit       = kFLEXSPI_CsIntervalUnit1SckCycle,
        .CSInterval           = 5,
        .CSHoldTime           = 3,
        .CSSetupTime          = 3,
        .dataValidTime        = 1,
        .columnspace          = 0,
        .enableWordAddress    = false,
        .AWRSeqIndex          = 1,
        .AWRSeqNumber         = 1,
        .ARDSeqIndex          = 0,
        .ARDSeqNumber         = 1,
        .AHBWriteWaitUnit     = kFLEXSPI_AhbWriteWaitUnit2AhbCycle,
        .AHBWriteWaitInterval = 0,
        .enableWriteMask      = true,
    };

    uint32_t customLUT[64] = {
        /* Read Data */
        [0] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_8PAD, 0x20, kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20),
        [1] = FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DUMMY_RWDS_DDR, kFLEXSPI_8PAD, 0x07, kFLEXSPI_Command_READ_DDR,
                              kFLEXSPI_8PAD, 0x04),

        /* Write Data */
        [4] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_8PAD, 0xA0, kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20),
        [5] = FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DUMMY_RWDS_DDR, kFLEXSPI_8PAD, 0x07, kFLEXSPI_Command_WRITE_DDR,
                              kFLEXSPI_8PAD, 0x04),

        /* Read Register */
        [8] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_8PAD, 0x40, kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20),
        [9] = FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DUMMY_RWDS_DDR, kFLEXSPI_8PAD, 0x07, kFLEXSPI_Command_READ_DDR,
                              kFLEXSPI_8PAD, 0x04),

        /* Write Register */
        [12] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_8PAD, 0xC0, kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x20),
        [13] = FLEXSPI_LUT_SEQ(kFLEXSPI_Command_WRITE_DDR, kFLEXSPI_8PAD, 0x08, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD,
                               0x00),

        /* reset */
        [16] =
            FLEXSPI_LUT_SEQ(kFLEXSPI_Command_SDR, kFLEXSPI_8PAD, 0xFF, kFLEXSPI_Command_DUMMY_SDR, kFLEXSPI_8PAD, 0x03),

    };

    uint32_t mr0mr1[1];
    uint32_t mr4mr8[1];
    uint32_t mr0Val[1];
    uint32_t mr4Val[1];
    uint32_t mr8Val[1];
    flexspi_config_t config;
    status_t status = kStatus_Success;

    UPOWER_PowerOnMemPart(0U, (uint32_t)kUPOWER_MP1_FLEXSPI1);

    /* 392MHz * 1U / 1U = 392MHz */
    CLOCK_SetIpSrcDiv(kCLOCK_Flexspi1, kCLOCK_Pcc1PlatIpSrcPll0Pfd3, 0U, 0U);
    RESET_PeripheralReset(kRESET_Flexspi1);

    /* Get FLEXSPI default settings and configure the flexspi. */
    FLEXSPI_GetDefaultConfig(&config);

    /* Init FLEXSPI. */
    config.rxSampleClock = kFLEXSPI_ReadSampleClkExternalInputFromDqsPad;
    /*Set AHB buffer size for reading data through AHB bus. */
    config.ahbConfig.enableAHBPrefetch    = true;
    config.ahbConfig.enableAHBBufferable  = true;
    config.ahbConfig.enableAHBCachable    = true;
    config.ahbConfig.enableReadAddressOpt = true;
    for (uint8_t i = 1; i < FSL_FEATURE_FLEXSPI_AHB_BUFFER_COUNT - 1; i++)
    {
        config.ahbConfig.buffer[i].bufferSize = 0;
    }
    /* FlexSPI1 has total 2KB RX buffer.
     * Set GPU/Display master to use AHB Rx Buffer0.
     */
    config.ahbConfig.buffer[0].masterIndex    = 2;    /* DMA0 */
    config.ahbConfig.buffer[0].bufferSize     = 1024; /* Allocate 1KB bytes for DMA0 */
    config.ahbConfig.buffer[0].enablePrefetch = true;
    config.ahbConfig.buffer[0].priority       = 7;    /* Set DMA0 to highest priority. */
    /* All other masters use last buffer with 1KB bytes. */
    config.ahbConfig.buffer[FSL_FEATURE_FLEXSPI_AHB_BUFFER_COUNT - 1].bufferSize = 1024;
    config.enableCombination                                                     = true;
    FLEXSPI_Init(BOARD_FLEXSPI_PSRAM, &config);

    /* Configure flash settings according to serial flash feature. */
    FLEXSPI_SetFlashConfig(BOARD_FLEXSPI_PSRAM, &deviceconfig, kFLEXSPI_PortA1);

    /* Update LUT table. */
    FLEXSPI_UpdateLUT(BOARD_FLEXSPI_PSRAM, 0, customLUT, ARRAY_SIZE(customLUT));

    /* Do software reset. */
    FLEXSPI_SoftwareReset(BOARD_FLEXSPI_PSRAM);

    /* Reset hyper ram. */
    status = flexspi_hyper_ram_reset(BOARD_FLEXSPI_PSRAM);
    if (status != kStatus_Success)
    {
        return status;
    }

    status = flexspi_hyper_ram_get_mcr(BOARD_FLEXSPI_PSRAM, 0x0, mr0mr1);
    if (status != kStatus_Success)
    {
        return status;
    }

    status = flexspi_hyper_ram_get_mcr(BOARD_FLEXSPI_PSRAM, 0x4, mr4mr8);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* Enable RBX, burst length set to 1K. - MR8 */
    mr8Val[0] = (mr4mr8[0] & 0xFF00U) >> 8U;
    mr8Val[0] = mr8Val[0] | 0x0F;
    status    = flexspi_hyper_ram_write_mcr(BOARD_FLEXSPI_PSRAM, 0x8, mr8Val);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* Set LC code to 0x04(LC=7, maximum frequency 200M) - MR0. */
    mr0Val[0] = mr0mr1[0] & 0x00FFU;
    mr0Val[0] = (mr0Val[0] & ~0x3CU) | (4U << 2U);
    status    = flexspi_hyper_ram_write_mcr(BOARD_FLEXSPI_PSRAM, 0x0, mr0Val);
    if (status != kStatus_Success)
    {
        return status;
    }

    /* Set WLC code to 0x01(WLC=7, maximum frequency 200M) - MR4. */
    mr4Val[0] = mr4mr8[0] & 0x00FFU;
    mr4Val[0] = (mr4Val[0] & ~0xE0U) | (1U << 5U);
    status    = flexspi_hyper_ram_write_mcr(BOARD_FLEXSPI_PSRAM, 0x4, mr4Val);
    if (status != kStatus_Success)
    {
        return status;
    }

    return status;
}

void BOARD_DeinitXip(FLEXSPI_Type *base)
{
    /* Wait until FLEXSPI is not busy */
    while (!((base->STS0 & FLEXSPI_STS0_ARBIDLE_MASK) && (base->STS0 & FLEXSPI_STS0_SEQIDLE_MASK)))
    {
    }
    /* Disable module during the reset procedure */
    base->MCR0 |= FLEXSPI_MCR0_MDIS_MASK;
}

void BOARD_InitXip(FLEXSPI_Type *base)
{
    uint32_t status;
    uint32_t lastStatus;
    uint32_t retry;

    /* Enable FLEXSPI module */
    base->MCR0 &= ~FLEXSPI_MCR0_MDIS_MASK;

    base->MCR0 |= FLEXSPI_MCR0_SWRESET_MASK;
    while (base->MCR0 & FLEXSPI_MCR0_SWRESET_MASK)
    {
    }

    /* Need to wait DLL locked if DLL enabled */
    if (0U != (base->DLLCR[0] & FLEXSPI_DLLCR_DLLEN_MASK))
    {
        lastStatus = base->STS2;
        retry      = BOARD_FLEXSPI_DLL_LOCK_RETRY;
        /* Wait slave delay line locked and slave reference delay line locked. */
        do
        {
            status = base->STS2;
            if ((status & (FLEXSPI_STS2_AREFLOCK_MASK | FLEXSPI_STS2_ASLVLOCK_MASK)) ==
                (FLEXSPI_STS2_AREFLOCK_MASK | FLEXSPI_STS2_ASLVLOCK_MASK))
            {
                /* Locked */
                retry = 100;
                break;
            }
            else if (status == lastStatus)
            {
                /* Same delay cell number in calibration */
                retry--;
            }
            else
            {
                retry      = BOARD_FLEXSPI_DLL_LOCK_RETRY;
                lastStatus = status;
            }
        } while (retry > 0);
        /* According to ERR011377, need to delay at least 100 NOPs to ensure the DLL is locked. */
        for (; retry > 0U; retry--)
        {
            __NOP();
        }
    }
}

/* BOARD_SetFlexspiClock run in RAM used to configure FlexSPI clock source and divider when XIP. */
void BOARD_SetFlexspiClock(FLEXSPI_Type *base, uint32_t src, uint8_t divValue, uint8_t fracValue)
{
    uint32_t pccReg;

    if (base == FLEXSPI0)
    {
        pccReg = PCC_REG(kCLOCK_Flexspi0);
        if ((PCC_PCS_VAL(pccReg) != src) || PCC_PCD_VAL(pccReg) != divValue || PCC_FRAC_VAL(pccReg) != fracValue)
        {
            if (BOARD_IS_XIP_FLEXSPI0())
            {
                BOARD_DeinitXip(base);
            }
            pccReg &= ~(PCC_CLKCFG_PCD_MASK | PCC_CLKCFG_FRAC_MASK | PCC_CLKCFG_PCS_MASK);
            pccReg |= PCC_CLKCFG_PCD(divValue) | PCC_CLKCFG_FRAC(fracValue) | PCC_CLKCFG_PCS(src);
            /*
             * If clock is already enabled, first disable it, then set the clock
             * source and re-enable it.
             */
            PCC_REG(kCLOCK_Flexspi0) = pccReg & ~PCC_CLKCFG_CGC_MASK;
            PCC_REG(kCLOCK_Flexspi0) = pccReg;
            if (BOARD_IS_XIP_FLEXSPI0())
            {
                BOARD_InitXip(base);
            }
        }
    }
    else if (base == FLEXSPI1)
    {
        pccReg = PCC_REG(kCLOCK_Flexspi1);
        if ((PCC_PCS_VAL(pccReg) != src) || PCC_PCD_VAL(pccReg) != divValue || PCC_FRAC_VAL(pccReg) != fracValue)
        {
            /* FLEXSPI1 not for CM33 XIP. */
            pccReg &= ~(PCC_CLKCFG_PCD_MASK | PCC_CLKCFG_FRAC_MASK | PCC_CLKCFG_PCS_MASK);
            pccReg |= PCC_CLKCFG_PCD(divValue) | PCC_CLKCFG_FRAC(fracValue) | PCC_CLKCFG_PCS(src);
            /*
             * If clock is already enabled, first disable it, then set the clock
             * source and re-enable it.
             */
            PCC_REG(kCLOCK_Flexspi1) = pccReg & ~PCC_CLKCFG_CGC_MASK;
            PCC_REG(kCLOCK_Flexspi1) = pccReg;
        }
    }
    else
    {
        assert(false);
    }
}

/* This function is used to change FlexSPI clock to a stable source before clock sources(Such as PLL and Main clock)
 * updating in case XIP(execute code on FLEXSPI memory.) */
void BOARD_FlexspiClockSafeConfig(void)
{
    int freq_divider = 1;

    /*
     * Move FLEXSPI clock source from main clock(old clock source for flexspi0) to FRO(192 MHz) / divider = xx MHz(new
     * clock source[FRO] for flexspi0) to avoid instruction/data fetch issue in XIP when updating PLL and main clock.
     * 6 - clock source of flexspi0 is FRO
     */
    BOARD_CalculateDivider(CLK_FRO_192MHZ, BOARD_NOR_FLASH_READ_MAXIMUM_FREQ, &freq_divider);
    BOARD_SetFlexspiClock(FLEXSPI0, 6U, freq_divider - 1, 0U); /* flexspi0's clock is FRO(192 MHz) / div */
}

#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
void BOARD_LPI2C_Init(LPI2C_Type *base, uint32_t clkSrc_Hz)
{
    lpi2c_master_config_t lpi2cConfig = {0};

    /*
     * lpi2cConfig.debugEnable = false;
     * lpi2cConfig.ignoreAck = false;
     * lpi2cConfig.pinConfig = kLPI2C_2PinOpenDrain;
     * lpi2cConfig.baudRate_Hz = 100000U;
     * lpi2cConfig.busIdleTimeout_ns = 0;
     * lpi2cConfig.pinLowTimeout_ns = 0;
     * lpi2cConfig.sdaGlitchFilterWidth_ns = 0;
     * lpi2cConfig.sclGlitchFilterWidth_ns = 0;
     */
    LPI2C_MasterGetDefaultConfig(&lpi2cConfig);
    LPI2C_MasterInit(base, &lpi2cConfig, clkSrc_Hz);
}

status_t BOARD_LPI2C_Send(LPI2C_Type *base,
                          uint8_t deviceAddress,
                          uint32_t subAddress,
                          uint8_t subAddressSize,
                          uint8_t *txBuff,
                          uint16_t txBuffSize,
                          uint32_t flags)
{
    lpi2c_master_transfer_t xfer;

    xfer.flags          = flags;
    xfer.slaveAddress   = deviceAddress;
    xfer.direction      = kLPI2C_Write;
    xfer.subaddress     = subAddress;
    xfer.subaddressSize = subAddressSize;
    xfer.data           = txBuff;
    xfer.dataSize       = txBuffSize;

    return LPI2C_MasterTransferBlocking(base, &xfer);
}

status_t BOARD_LPI2C_Receive(LPI2C_Type *base,
                             uint8_t deviceAddress,
                             uint32_t subAddress,
                             uint8_t subAddressSize,
                             uint8_t *rxBuff,
                             uint16_t rxBuffSize,
                             uint32_t flags)
{
    lpi2c_master_transfer_t xfer;

    xfer.flags          = flags;
    xfer.slaveAddress   = deviceAddress;
    xfer.direction      = kLPI2C_Read;
    xfer.subaddress     = subAddress;
    xfer.subaddressSize = subAddressSize;
    xfer.data           = rxBuff;
    xfer.dataSize       = rxBuffSize;

    return LPI2C_MasterTransferBlocking(base, &xfer);
}

void BOARD_Accel_I2C_Init(void)
{
    BOARD_LPI2C_Init(BOARD_ACCEL_I2C_BASEADDR, BOARD_ACCEL_I2C_CLOCK_FREQ);
}

status_t BOARD_Accel_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint32_t txBuff, uint32_t flags)
{
    uint8_t data = (uint8_t)txBuff;

    return BOARD_LPI2C_Send(BOARD_ACCEL_I2C_BASEADDR, deviceAddress, subAddress, subaddressSize, &data, 1, flags);
}

status_t BOARD_Accel_I2C_Receive(uint8_t deviceAddress,
                                 uint32_t subAddress,
                                 uint8_t subaddressSize,
                                 uint8_t *rxBuff,
                                 uint8_t rxBuffSize,
                                 uint32_t flags)
{
    return BOARD_LPI2C_Receive(BOARD_ACCEL_I2C_BASEADDR, deviceAddress, subAddress, subaddressSize, rxBuff, rxBuffSize,
                               flags);
}

void BOARD_Codec_I2C_Init(void)
{
    BOARD_LPI2C_Init(BOARD_CODEC_I2C_BASEADDR, BOARD_CODEC_I2C_CLOCK_FREQ);
}

status_t BOARD_Codec_I2C_Send(uint8_t deviceAddress,
                              uint32_t subAddress,
                              uint8_t subAddressSize,
                              const uint8_t *txBuff,
                              uint8_t txBuffSize,
                              uint32_t flags)
{
    return BOARD_LPI2C_Send(BOARD_CODEC_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, (uint8_t *)txBuff,
                            txBuffSize, flags);
}

status_t BOARD_Codec_I2C_Receive(uint8_t deviceAddress,
                                 uint32_t subAddress,
                                 uint8_t subAddressSize,
                                 uint8_t *rxBuff,
                                 uint8_t rxBuffSize,
                                 uint32_t flags)
{
    return BOARD_LPI2C_Receive(BOARD_CODEC_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, rxBuff, rxBuffSize,
                               flags);
}

void BOARD_Display_I2C_Init(void)
{
    BOARD_LPI2C_Init(BOARD_DISPLAY_I2C_BASEADDR, BOARD_DISPLAY_I2C_CLOCK_FREQ);
}

status_t BOARD_Display_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize)
{
    return BOARD_LPI2C_Send(BOARD_DISPLAY_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, (uint8_t *)txBuff,
                            txBuffSize, 0);
}

status_t BOARD_Display_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize)
{
    return BOARD_LPI2C_Receive(BOARD_CODEC_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, rxBuff, rxBuffSize,
                               0);
}

#if defined(BOARD_USE_PCA6416A) && BOARD_USE_PCA6416A
pca6416a_handle_t g_pca6416aHandle;

void BOARD_PCA6416A_I2C_Init(void)
{
    BOARD_LPI2C_Init(BOARD_PCA6416A_I2C, BOARD_PCA6416A_I2C_CLOCK_FREQ);
}

status_t BOARD_PCA6416A_I2C_Send(uint8_t deviceAddress,
                                 uint32_t subAddress,
                                 uint8_t subAddressSize,
                                 const uint8_t *txBuff,
                                 uint8_t txBuffSize,
                                 uint32_t flags)
{
    return BOARD_LPI2C_Send(BOARD_PCA6416A_I2C, deviceAddress, subAddress, subAddressSize, (uint8_t *)txBuff,
                            txBuffSize, flags);
}

status_t BOARD_PCA6416A_I2C_Receive(uint8_t deviceAddress,
                                    uint32_t subAddress,
                                    uint8_t subAddressSize,
                                    uint8_t *rxBuff,
                                    uint8_t rxBuffSize,
                                    uint32_t flags)
{
    return BOARD_LPI2C_Receive(BOARD_PCA6416A_I2C, deviceAddress, subAddress, subAddressSize, rxBuff, rxBuffSize,
                               flags);
}

void BOARD_InitPCA6416A(pca6416a_handle_t *handle)
{
    BOARD_PCA6416A_I2C_Init();

    static const pca6416a_config_t config = {
        .i2cAddr         = BOARD_PCA6416A_I2C_ADDR,
        .I2C_SendFunc    = BOARD_PCA6416A_I2C_Send,
        .I2C_ReceiveFunc = BOARD_PCA6416A_I2C_Receive,
    };

    PCA6416A_Init(handle, &config);
}

/* Set I2C0 PCA6416 IO9(PTH9_MIPI_SWITH) to high to select MIPI DSI panel path for uboot(running on a35) */
void BOARD_InitMipiDsiPins(void)
{
    BOARD_InitPCA6416A(&g_pca6416aHandle);
    PCA6416A_SetPins(&g_pca6416aHandle, (1U << BOARD_PCA6416A_MIPI_SWITCH));
    PCA6416A_SetDirection(&g_pca6416aHandle, (1U << BOARD_PCA6416A_MIPI_SWITCH), kPCA6416A_Output);
}
#endif /* BOARD_USE_PCA6416A. */

#if defined(BOARD_USE_TPM) && BOARD_USE_TPM
/* Set TPM0_CH2 to full duty cycle to enable backlight at highest brightness for uboot(running on a35) */
void BOARD_EnableMipiDsiBacklight(void)
{
    tpm_config_t tpmInfo;
    tpm_chnl_pwm_signal_param_t pwmChannelConfig = {
        .chnlNumber       = (tpm_chnl_t)TPM0_CH2,
        .level            = kTPM_HighTrue,
        .dutyCyclePercent = FULL_DUTY_CYCLE,
    };

    TPM_GetDefaultConfig(&tpmInfo);
    TPM_Init(TPM0, (void *)&tpmInfo);
    TPM_SetupPwm(TPM0, (void *)&pwmChannelConfig, 1, kTPM_EdgeAlignedPwm, CLOCK_GetTpmClkFreq(0U), TPM0_CH2_PWM_FREQ);
    TPM_StartTimer(TPM0, kTPM_SystemClock);
}
#endif /* BOARD_USE_TPM. */
#endif /* SDK_I2C_BASED_COMPONENT_USED */

/* Init LPAV domain clock, prepare for DDR retention exit */
void BOARD_LpavInit()
{
    int i;

    /* PLL4 */
    for (i = 0; i < 9; i++)
    {
        W32(pll4[i][0], pll4[i][1]);
    }

    /* wait for PLL4 lock */
    while (!(R32(pll4[8][0]) & BIT(24)))
    {
    }

    /* restore the PLL4 PFDs */
    W32(pll4[9][0], pll4[9][1] & ~(BIT(31) | BIT(23) | BIT(15) | BIT(7)));
    W32(pll4[9][0], pll4[9][1]);

    /* wait for the PFD is stable */
    while (!(R32(pll4[9][0]) & PFD_VALID_MASK))
    {
    }

    /* CGC2 restore */
    for (i = 0; i < ARRAY_SIZE(cgc2); i++)
    {
        W32(cgc2[i][0], cgc2[i][1]);
    }

    /* PCC5 restore */
    for (i = 0; i < ARRAY_SIZE(pcc5_0); i++)
    {
        if (pcc5_0[i][1] & PCC_CLKCFG_PR_MASK)
        {
            W32(pcc5_0[i][0], pcc5_0[i][1]);
        }
    }

    for (i = 0; i < ARRAY_SIZE(pcc5_1); i++)
    {
        if (pcc5_1[i][1] & PCC_CLKCFG_PR_MASK)
        {
            W32(pcc5_1[i][0], pcc5_1[i][1]);
        }
    }

    /* LPAV_SIM */
    for (i = 0; i < ARRAY_SIZE(lpav_sim); i++)
    {
        W32(lpav_sim[i][0], lpav_sim[i][1]);
    }

    /* Config the LPAV PLL4 and DDR clock for the desired LPDDR operating frequency. */
    PCC5->PCC_LPDDR4 |= PCC5_PCC_LPDDR4_CGC_MASK;

    /* Write PCC5.PCC_LPDDR4[SWRST] to 1b'1 to release LPDDR from reset. */
    PCC5->PCC_LPDDR4 |= PCC5_PCC_LPDDR4_SWRST_MASK;
}

/* Restore DDR controller registers */
static void ddrInit(uint32_t dram_class, struct dram_cfg *dram_timing_cfg)
{
    int i;

    /* restore the ddr ctl config */
    for (i = 0; i < CTL_NUM; i++)
    {
        W32(LPDDR_BASE + i * 4, dram_timing_cfg->ctl_cfg[i]);
    }

    /* load the PI registers */
    for (i = 0; i < PI_NUM; i++)
    {
        W32(LPDDR_BASE + 0x2000 + i * 4, dram_timing_cfg->pi_cfg[i]);
    }

    /* restore all PHY registers for all the fsp. */
    LPDDR->DENALI_PHY_1537 = LPDDR_DENALI_PHY_1537_PHY_FREQ_SEL_MULTICAST_EN_MASK;

    /* restore all the phy configs */
    for (i = 0; i < PHY_NUM; i++)
    {
        if (i >= 121 && i <= 255)
            continue;
        if (i >= 377 && i <= 511)
            continue;
        if (i >= 633 && i <= 767)
            continue;
        if (i >= 889 && i <= 1023)
            continue;
        if (i >= 1065 && i <= 1279)
            continue;
        if (i >= 1321 && i <= 1535)
            continue;
        W32(LPDDR_BASE + 0x4000 + i * 4, dram_timing_cfg->phy_full[i]);
    }

    if (dram_class == LPDDR4_TYPE)
    {
        /* restore only the diff. */
        LPDDR->DENALI_PHY_1537 = 0;
        for (i = 0; i < PHY_DIFF_NUM; i++)
            W32(LPDDR_BASE + 0x4000 + freq_specific_reg_array[i] * 4, dram_timing_cfg->phy_diff[i]);
    }

    /* Re-enable MULTICAST mode */
    LPDDR->DENALI_PHY_1537 = LPDDR_DENALI_PHY_1537_PHY_FREQ_SEL_MULTICAST_EN(1);
}

void BOARD_DdrSave(void)
{
    uint32_t i;
    struct dram_timing_info *Info;
    Info = (struct dram_timing_info *)(SAVED_DRAM_DATA_BASE_ADDR_FROM_TFA);

    /*
     * Save DDR Controller & PHY config.
     * Set PHY_FREQ_SEL_MULTICAST_EN=0 & PHY_FREQ_SEL_INDEX=1. Read and store all the PHY registers
     * for F2 into phy_f1_cfg, then read/store the diff between F1 & F2 into phy_f2_cfg.
     */

    /* save the ctl registers */
    for (i = 0; i < CTL_NUM; i++)
    {
        dram_timing_cfg->ctl_cfg[i] = R32(LPDDR_BASE + i * 4);
    }
    dram_timing_cfg->ctl_cfg[0] = dram_timing_cfg->ctl_cfg[0] & 0xFFFFFFFE;

    /* save th ePIl registers */
    for (i = 0; i < PI_NUM; i++)
    {
        dram_timing_cfg->pi_cfg[i] = R32(LPDDR_BASE + 0x2000 + i * 4);
    }

    /* Read and store all PHY registers. full array is a full copy for all the setpoint */
    if (dram_class == LPDDR4_TYPE)
    {
        W32(LPDDR_BASE + 0x5804U, 0x10000);
        for (i = 0; i < PHY_NUM; i++)
        {
            /* Make sure MULTICASE is enabled */
            if (i == 1537)
            {
                dram_timing_cfg->phy_full[i] = 0x100;
            }
            else
            {
                dram_timing_cfg->phy_full[i] = R32(LPDDR_BASE + 0x4000 + i * 4);
            }
        }
        /* set PHY_FREQ_SEL_MULTICAST_EN=0 & PHY_FREQ_SEL_INDEX=0. Read and store only the diff. */
        W32(LPDDR_BASE + 0x5804U, 0x0);
        /* save only the frequency based diff config to save memory */
        for (i = 0; i < PHY_DIFF_NUM; i++)
        {
            dram_timing_cfg->phy_diff[i] = R32(LPDDR_BASE + 0x4000 + freq_specific_reg_array[i] * 4);
        }
    }
    else
    {
        /* LPDDR3, only f1 need to save */
        for (i = 0; i < Info->phy_f1_cfg_num; i++)
        {
            Info->phy_f1_cfg[i].val = R32(Info->phy_f1_cfg[i].reg);
        }
    }
}

/* Store LPAV domain clock before DDR enter retention */
void BOARD_LpavSave(void)
{
    uint32_t i;
    uint32_t val;

    /* CGC2 save */
    for (i = 0; i < ARRAY_SIZE(cgc2); i++)
        cgc2[i][1] = R32(cgc2[i][0]);

    /* PLL4 */
    for (i = 0; i < ARRAY_SIZE(pll4); i++)
        pll4[i][1] = R32(pll4[i][0]);

    /*
     * PCC5 save
     * Note: Check PR bit when save/store PCC5
     * When some module is fused, the PCC with PR=0 can't be written.
     */

    for (i = 0; i < ARRAY_SIZE(pcc5_0); i++)
    {
        val          = R32(pcc5_0[i][0]);
        pcc5_0[i][1] = 0U;
        if (val & PCC_CLKCFG_PR_MASK)
        {
            pcc5_0[i][1] = val;
        }
    }

    for (i = 0; i < ARRAY_SIZE(pcc5_1); i++)
    {
        val          = R32(pcc5_1[i][0]);
        pcc5_1[i][1] = 0U;
        if (val & PCC_CLKCFG_PR_MASK)
        {
            pcc5_1[i][1] = val;
        }
    }

    /* LPAV SIM save */
    for (i = 0; i < ARRAY_SIZE(lpav_sim); i++)
        lpav_sim[i][1] = R32(lpav_sim[i][0]);
}

/* Disable low power auto self-refresh for DRAM */
void BOARD_DramLpAutoDisable(void)
{
    dram_timing_cfg = (struct dram_cfg *)(SAVED_DRAM_DATA_BASE_ADDR_FROM_TFA + SAVED_DRAM_TIMING_INFO_SIZE_FROM_TFA);
    dram_class      = (LPDDR->DENALI_CTL[0] >> 8) & 0xF;
    uint32_t lp_auto_en;

    /* LP AUTO ENTRY EN, Bits[27, 24], Set different bit to enable matching */
    lp_auto_en = (R32(LPDDR_BASE + DENALI_CTL_146) & (LP_AUTO_ENTRY_EN << 24));
    /* Save initial config */
    dram_ctl_143 = R32(LPDDR_BASE + DENALI_CTL_143);

    /* Set LPI_SRPD_LONG_MCCLK_GATE_WAKEUP_F2 to Maximum */
    SETBIT32(LPDDR_BASE + DENALI_CTL_143, LPI_SRPD_LONG_MCCLK_GATE_WAKEUP_F2_NUM << 24);

    if (lp_auto_en && !dram_auto_lp_true)
    {
        /* Save DDRC auto low-power mode parameter */
        dram_timing_cfg->auto_lp_cfg[0] = R32(LPDDR_BASE + DENALI_CTL_144);
        dram_timing_cfg->auto_lp_cfg[1] = R32(LPDDR_BASE + DENALI_CTL_147);
        dram_timing_cfg->auto_lp_cfg[2] = R32(LPDDR_BASE + DENALI_CTL_146);

        /*
         * Disable DDRC auto low-power mode interface, controls self-refresh long with memory and controller clock
         * gating. or self-refresh power-down long with mem-ory and controller clock gating.
         */
        CLRBIT32(LPDDR_BASE + DENALI_CTL_146, LP_AUTO_ENTRY_EN << 24);

        /* Read any location to get DRAM out of Self-refresh */
        R32(0x80000000);
        /* Roll check [LP_STATE_CS0] and [LP_STATE_CS1] whether DRAM is out of self-refresh */
        while ((R32(LPDDR_BASE + DENALI_CTL_146) & 0x004F4F00) != 0x00404000)
        {
            ;
        }
        /* Disable DDRC auto low-power exit */
        CLRBIT32(LPDDR_BASE + DENALI_CTL_147, LP_AUTO_EXIT_EN);

        /* update dram low power mode flag */
        dram_auto_lp_true = true;
    }
}

/* Enable low power auto self-refresh for DRAM */
void BOARD_DramLpAutoEnabble(void)
{
    /* restore ctl config */
    W32(LPDDR_BASE + DENALI_CTL_143, dram_ctl_143);

    if (dram_auto_lp_true)
    {
        /* Now, DRAM is active state, switch back to auto low-power self refresh mode */
        /* Roll check [LP_STATE_CS0] and [LP_STATE_CS1] whether DRAM is out of self-refresh */
        while ((R32(LPDDR_BASE + DENALI_CTL_146) & 0x004F4F00) != 0x00404000)
        {
            ;
        }
        /* Reconfigure DENALI_CTL_144 [LPI_WAKEUP_EN[5:0]] bit LPI_WAKEUP_EN[3] = 1b'1 */
        W32(LPDDR_BASE + DENALI_CTL_144, dram_timing_cfg->auto_lp_cfg[0]);
        W32(LPDDR_BASE + DENALI_CTL_147, dram_timing_cfg->auto_lp_cfg[1]);
        /* Re-enable DDRC auto low-power mode interface */
        W32(LPDDR_BASE + DENALI_CTL_146, dram_timing_cfg->auto_lp_cfg[2]);

        /* update dram low power mode flag */
        dram_auto_lp_true = false;
    }
}

/* Program DDR controller to let DRAM enter self-refresh */
void BOARD_DramEnterRetention(void)
{
    uint32_t val;

    /* Disable DRAM auto self-refresh if if it is enabled */
    BOARD_DramLpAutoDisable();

    /* Save lpav context */
    BOARD_LpavSave();

    /* Save DDR controller registers */
    BOARD_DdrSave();

    SETBIT32(LPDDR_BASE + DENALI_CTL_144, BIT(3) << LPI_WAKEUP_EN_SHIFT);

    /*
     * a. Config SIM_LPAV LPDDR_CTRL[LPDDR_AUTO_LP_MODE_DISABLE] to 1b'0(enable the logic to
     * to automatic handles low power entry/exit. This is the recommended option over handling
     * through software.
     * b. Config the SIM_LPAV LPDDR_CTRL[SOC_LP_CMD] to 6b'101001(encoding for self_refresh with
     * both DDR controller and DRAM clock gate. THis is mandatory since LPPDR logic will be power
     * gated).
     */
    SIM_LPAV->LPDDR_CTRL &= ~SIM_LPAV_LPDDR_CTRL_LPDDR_AUTO_LP_MODE_DISABLE_MASK;
    val = SIM_LPAV->LPDDR_CTRL;
    val &= -SIM_LPAV_LPDDR_CTRL_SOC_LP_CMD(0x3f);
    val |= SIM_LPAV_LPDDR_CTRL_SOC_LP_CMD(0x29);
    SIM_LPAV->LPDDR_CTRL = val;

    SIM_LPAV->LPDDR_CTRL2 = SIM_LPAV_LPDDR_CTRL2_LPDDR_EN_CLKGATE_MASK;

    /* Program Idle count to enter LP state */
    W32(LPDDR_BASE + DENALI_CTL_148, R32(LPDDR_BASE + DENALI_CTL_148) | 0x0F0F000F);

    /* Enable Mem clk gating */
    W32(LPDDR_BASE + DENALI_CTL_147, R32(LPDDR_BASE + DENALI_CTL_147) | 0x700);

    /* Enable Auto entry */
    W32(LPDDR_BASE + DENALI_CTL_146, R32(LPDDR_BASE + DENALI_CTL_146) | 0x0F000000);

    /* Wait for controller to enter SRPD with Mem and CTl clk gating */
    while ((R32(LPDDR_BASE + DENALI_CTL_146) & 0x7F00) != 0x4F00)
    {
    }
}

/* Program DDR controller to let DRAM exit from self-refresh */
void BOARD_DramExitRetention(uint32_t dram_class, struct dram_cfg *dram_timing_cfg)
{
    uint32_t val;
    int status;

    /* Reload the LPDDR CTL/PI/PHY register */
    ddrInit(dram_class, dram_timing_cfg);

    if (dram_class == LPDDR4_TYPE)
    {
        /* a. FIXME Set PHY_SET_DFI_INPUT_N parameters to 4'h1. LPDDR4 only */
        W32(LPDDR_BASE + DENALI_PHY_1559, 0x01010101);

        /* b. CTL PWRUP_SREFRESH_EXIT=1'b0 for disabling self refresh exit from controller. */
        /* c. PI_PWRUP_SELF_REF_EXIT=1, PI_MC_PWRUP_SELF_REF_EXIT=0 for enabling self refresh exit from PI */
        /* c. PI_INT_LVL_EN=0 to skip Initialization trainings. */
        /*
         * d. PI_WRLVL_EN_F0/1/2= PI_CALVL_EN_F0/1/2= PI_RDLVL_EN_F0/1/2= PI_RDLVL_GATE_EN_F0/1/2=
         * PI_WDQLVL_EN_F0/1/2=0x2. Enable non initialization trainings.
         */
        /* e. PI_PWRUP_SREFRESH_EXIT_CS=0xF */
        /* f. PI_DLL_RESET=0x1 */
        SETBIT32(LPDDR_BASE + DENALI_PI_137, 0x1);                       /* PI_DLL_RESET=1 */
        SETBIT32(LPDDR_BASE + DENALI_PI_132, 0x01000000);                /* PI_PWRUP_SELF_REF_EXIT = 1 */
        CLRBIT32(LPDDR_BASE + DENALI_PI_132, BIT(16));                   /* PI_MC_PWRUP_SELF_REF_EXIT = 0 */
        LPDDR->DENALI_PI_4 &= ~LPDDR_DENALI_PI_4_PI_INIT_LVL_EN_MASK;    /* PI_INT_LVL_EN = 0 */
        LPDDR->DENALI_PI_174 |= (LPDDR_DENALI_PI_174_PI_WRLVL_EN_F0(3) |
                                 LPDDR_DENALI_PI_174_PI_WRLVL_EN_F1(3)); /* PI_WRLVL_EN_F0 = 3, PI_WRLVL_EN_F1 = 3 */
        LPDDR->DENALI_PI_175 |= LPDDR_DENALI_PI_175_PI_WRLVL_EN_F2(3);   /* PI_WRLVL_EN_F2 = 3 */
        LPDDR->DENALI_PI_191 |= (LPDDR_DENALI_PI_191_PI_CALVL_EN_F0(3) |
                                 LPDDR_DENALI_PI_191_PI_CALVL_EN_F1(3)); /* PI_CALVL_EN_F0 = 3, PI_CALVL_EN_F1 = 3 */
        LPDDR->DENALI_PI_192 |= LPDDR_DENALI_PI_192_PI_CALVL_EN_F2_MASK; /* PI_CALVL_EN_F2 = 3 */
        LPDDR->DENALI_PI_212 |= LPDDR_DENALI_PI_212_PI_WDQLVL_EN_F0(3);  /* PI_WDQLVL_EN_F0 = 3 */
        LPDDR->DENALI_PI_214 |= LPDDR_DENALI_PI_214_PI_WDQLVL_EN_F1(3);  /* PI_WDQLVL_EN_F1 = 3 */
        LPDDR->DENALI_PI_217 |= LPDDR_DENALI_PI_217_PI_WDQLVL_EN_F2(3);  /* PI_WDQLVL_EN_F2 = 3 */
        LPDDR->DENALI_PI_181 |=
            (LPDDR_DENALI_PI_181_PI_RDLVL_EN_F0(3) |
             LPDDR_DENALI_PI_181_PI_RDLVL_GATE_EN_F0(3)); /* PI_EDLVL_EN_F0 = 3, PI_EDLVL_GATE_EN_F0 = 3 */
        LPDDR->DENALI_PI_182 |=
            (LPDDR_DENALI_PI_182_PI_RDLVL_EN_F1(3) | LPDDR_DENALI_PI_182_PI_RDLVL_GATE_EN_F1(3) |
             LPDDR_DENALI_PI_182_PI_RDLVL_EN_F2(3) |
             LPDDR_DENALI_PI_182_PI_RDLVL_GATE_EN_F2(
                 3)); /* PI_RDLVL_EN_F1 = 3, PI_RDLVL_GATE_EN_F1 = 3, PI_RDLVL_EN_F2 = 3, PI_RDLVL_GATE_EN_F2 = 3 */
        SETBIT32(LPDDR_BASE + DENALI_PI_134, 0x000F0000); /* PI_PWRUP_SREFRESH_EXIT_CS = 0xF */
    }
    else
    {
        SETBIT32(LPDDR_BASE + DENALI_PI_137, 0x1);                     /* PI_DLL_RESET=1 */
        SETBIT32(LPDDR_BASE + DENALI_PI_132, 0x01000000);              /* PI_PWRUP_SELF_REF_EXIT=1 */
        CLRBIT32(LPDDR_BASE + DENALI_PI_132, BIT(16));                 /* PI_MC_PWRUP_SELF_REF_EXIT=0 */
        LPDDR->DENALI_PI_4 &= ~LPDDR_DENALI_PI_4_PI_INIT_LVL_EN_MASK;  /* PI_INT_LVL_EN = 0 */
        LPDDR->DENALI_PI_174 |= LPDDR_DENALI_PI_174_PI_WRLVL_EN_F0(3); /* PI_WRLVL_EN_F0=3 */
        LPDDR->DENALI_PI_191 |= LPDDR_DENALI_PI_191_PI_CALVL_EN_F0(3); /* PI_CALVL_EN_F0=3 */
        LPDDR->DENALI_PI_181 |=
            (LPDDR_DENALI_PI_181_PI_RDLVL_EN_F0(3) |
             LPDDR_DENALI_PI_181_PI_RDLVL_GATE_EN_F0(3)); /* PI_RDLVL_EN_F0=3,PI_RDLVL_GATE_EN_F0=3 */
        SETBIT32(LPDDR_BASE + DENALI_PI_134, 0x000F0000); /* PI_PWRUP_SREFRESH_EXIT_CS=0xF */
    }

    W32(LPDDR_BASE + DENALI_CTL_144, 0x00002D00);

    /* Force in-order AXI read data */
    W32(LPDDR_BASE + DENALI_CTL_144, 0x1);

    /*
     * Disable special R/W group switches so that R/W group placement is always
     * at END of R/W group.
     */
    LPDDR->DENALI_CTL[249] = 0x0;

    /* Reduce time for IO pad calibration */
    W32(LPDDR_BASE + DENALI_PHY_1590, 0x01000000);

    LPDDR->DENALI_CTL[25] = LPDDR_DENALI_CTL_FREQ_CHANGE_TYPE_F1(1) | LPDDR_DENALI_CTL_FREQ_CHANGE_TYPE_F2(2);

    /* PD disable */
    W32(LPDDR_BASE + DENALI_CTL_153, 0x04040000);

    status = UPOWER_SetDDRRetention(RTD_DOMAIN, false);
    if (status != 0)
    {
        assert(false);
    }

    /* Disable automatic LP entry and PCPCS modes LP_AUTO_ENTRY_EN to 1b'0, PCPCS_PD_EN to 1b'0 */
    if (dram_class == LPDDR4_TYPE)
    {
        /* Write PI START parameter to 1'b1 */
        LPDDR->DENALI_PI_0 = LPDDR_DENALI_PI_0_PI_START_MASK | LPDDR_DENALI_PI_0_PI_DRAM_CLASS(0xb);

        /* Write CTL START parameter to 1'b1 */
        LPDDR->DENALI_CTL[0] = LPDDR_DENALI_CTL_START_MASK | LPDDR_DENALI_CTL_DRAM_CLASS(0xb);
    }
    else
    {
        /* Write PI START parameter to 1'b1 */
        LPDDR->DENALI_PI_0 = LPDDR_DENALI_PI_0_PI_START_MASK | LPDDR_DENALI_PI_0_PI_DRAM_CLASS(0x7);

        /* Write CTL START parameter to 1'b1 */
        LPDDR->DENALI_CTL[0] = LPDDR_DENALI_CTL_START_MASK | LPDDR_DENALI_CTL_DRAM_CLASS(0x7);
    }

    /* DENALI_CTL_266:  Wait for INT_STATUS_INIT=0x2 */
    do
    {
        val = (R32(LPDDR_BASE + DENALI_CTL_266) >> 8) & 0xFF;
    } while (val != 0x2);

    /* Run SW trainings by setting PI_CALVL_REQ,PI_WRLVL_REQ,PI_RDLVL_GATE_REQ,PI_RDLVL_REQ,PI_WDQLVL_REQ(NA for LPDDR3)
     * in same order. */
    if (dram_class == LPDDR4_TYPE)
    {
        SETBIT32(LPDDR_BASE + DENALI_PI_52, 0x10000); /* CALVL */
        SETBIT32(LPDDR_BASE + DENALI_PI_26, 0x100);   /* WRLVL */
        SETBIT32(LPDDR_BASE + DENALI_PI_33, 0x10000); /* RDGATE */
        SETBIT32(LPDDR_BASE + DENALI_PI_33, 0x100);   /* RDQLVL */
        SETBIT32(LPDDR_BASE + DENALI_PI_65, 0x10000); /* WDQLVL */

        /* Wait for trainings to get complete by polling PI_INT_STATUS */
        while ((R32(LPDDR_BASE + DENALI_PI_77) & 0x07E00000) != 0x07E00000)
        {
        }
    }
    else
    {
        SETBIT32(LPDDR_BASE + DENALI_PI_52, 0x10000); /* CALVL */
        SETBIT32(LPDDR_BASE + DENALI_PI_26, 0x100);   /* WRLVL */
        SETBIT32(LPDDR_BASE + DENALI_PI_33, 0x10000); /* RDGATE */
        SETBIT32(LPDDR_BASE + DENALI_PI_33, 0x100);   /* RDQLVL */
        while ((R32(LPDDR_BASE + DENALI_PI_77) & 0x05E00000) != 0x05E00000)
        {
        }
    }
    BOARD_DramLpAutoEnabble();
}

/* put ddr into self-refresh immediately */
void BOARD_DDREnterSelfRefresh()
{
    uint32_t val;
    val = R32(LPDDR_BASE + DENALI_CTL_137);
    val &= ~LPAV_LPDDR_CTRL_LP_CMD(0x7f);
    val |= LPAV_LPDDR_CTRL_LP_CMD(0x51);

    W32(LPDDR_BASE + DENALI_CTL_137, val);

    /* wait low power state transition */
    while ((R32(LPDDR_BASE + DENALI_CTL_146) & 0x400) == 0)
    {
        ;
    }
}

/* let ddr exit self-refresh immediately */
void BOARD_DDRExitSelfRefresh()
{
    uint32_t val;
    val = R32(LPDDR_BASE + DENALI_CTL_137);
    val &= ~LPAV_LPDDR_CTRL_LP_CMD(0x7f);
    val |= LPAV_LPDDR_CTRL_LP_CMD(0x2);

    W32(LPDDR_BASE + DENALI_CTL_137, val);
}
