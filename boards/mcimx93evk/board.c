/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "fsl_cache.h"
#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
#include "fsl_lpi2c.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
struct dram_timing_info *timing_info;

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if defined(BOARD_USE_DDR_RETENTION) && BOARD_USE_DDR_RETENTION
static const uint16_t BOARD_DDRPHY_Addr_Remap_table[DDRPHY_NB_ADDR_REMAP] = {
    0x000, // 0x00
    0x001, // 0x01
    0x002, // 0x02
    0x003, // 0x03
    0x004, // 0x04
    0x005, // 0x05
    0x006, // 0x06
    0x007, // 0x07
    0x008, // 0x08
    0x009, // 0x09
    0x00a, // 0x0a
    0x00b, // 0x0b
    0x100, // 0x0c
    0x101, // 0x0d
    0x102, // 0x0e
    0x103, // 0x0f
    0x104, // 0x10
    0x105, // 0x11
    0x106, // 0x12
    0x107, // 0x13
    0x108, // 0x14
    0x109, // 0x15
    0x10a, // 0x16
    0x10b, // 0x17
    0x200, // 0x18
    0x201, // 0x19
    0x202, // 0x1a
    0x203, // 0x1b
    0x204, // 0x1c
    0x205, // 0x1d
    0x206, // 0x1e
    0x207, // 0x1f
    0x208, // 0x20
    0x209, // 0x21
    0x20a, // 0x22
    0x20b, // 0x23
    0x300, // 0x24
    0x301, // 0x25
    0x302, // 0x26
    0x303, // 0x27
    0x304, // 0x28
    0x305, // 0x29
    0x306, // 0x2a
    0x307, // 0x2b
    0x308, // 0x2c
    0x309, // 0x2d
    0x30a, // 0x2e
    0x30b, // 0x2f
    0x010, // 0x30
    0x011, // 0x31
    0x012, // 0x32
    0x013, // 0x33
    0x014, // 0x34
    0x015, // 0x35
    0x016, // 0x36
    0x017, // 0x37
    0x018, // 0x38
    0x019, // 0x39
    0x110, // 0x3a
    0x111, // 0x3b
    0x112, // 0x3c
    0x113, // 0x3d
    0x114, // 0x3e
    0x115, // 0x3f
    0x116, // 0x40
    0x117, // 0x41
    0x118, // 0x42
    0x119, // 0x43
    0x210, // 0x44
    0x211, // 0x45
    0x212, // 0x46
    0x213, // 0x47
    0x214, // 0x48
    0x215, // 0x49
    0x216, // 0x4a
    0x217, // 0x4b
    0x218, // 0x4c
    0x219, // 0x4d
    0x310, // 0x4e
    0x311, // 0x4f
    0x312, // 0x50
    0x313, // 0x51
    0x314, // 0x52
    0x315, // 0x53
    0x316, // 0x54
    0x317, // 0x55
    0x318, // 0x56
    0x319, // 0x57
    0x020, // 0x58
    0x120, // 0x59
    0x220, // 0x5a
    0x320, // 0x5b
    0x040, // 0x5c
    0x140, // 0x5d
    0x240, // 0x5e
    0x340, // 0x5f
    0x050, // 0x60
    0x051, // 0x61
    0x052, // 0x62
    0x053, // 0x63
    0x054, // 0x64
    0x055, // 0x65
    0x056, // 0x66
    0x057, // 0x67
    0x070, // 0x68
    0x090, // 0x69
    0x190, // 0x6a
    0x290, // 0x6b
    0x390, // 0x6c
    0x0c0, // 0x6d
    0x0d0, // 0x6e
};
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

/* Initialize debug console. */
void BOARD_InitDebugConsole(void)
{
    /* clang-format off */
    const clock_root_config_t uartClkCfg = {
        .clockOff = false,
	.mux = 0, // 24MHz oscillator source
	.div = 1
    };
    /* clang-format on */

    CLOCK_SetRootClock(BOARD_DEBUG_UART_CLOCK_ROOT, &uartClkCfg);
    CLOCK_EnableClock(BOARD_DEBUG_UART_CLOCK_GATE);
    DbgConsole_Init(BOARD_DEBUG_UART_INSTANCE, BOARD_DEBUG_UART_BAUDRATE, BOARD_DEBUG_UART_TYPE,
                    BOARD_DEBUG_UART_CLK_FREQ);
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
                          uint8_t txBuffSize,
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
                             uint8_t rxBuffSize,
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

#if defined(BOARD_USE_ADP5585) && BOARD_USE_ADP5585
void BOARD_ADP5585_I2C_Init(void)
{
    BOARD_LPI2C_Init(BOARD_ADP5585_I2C, BOARD_ADP5585_I2C_CLOCK_FREQ);
}

status_t BOARD_ADP5585_I2C_Send(uint8_t deviceAddress,
                                uint32_t subAddress,
                                uint8_t subAddressSize,
                                const uint8_t *txBuff,
                                uint8_t txBuffSize,
                                uint32_t flags)
{
    return BOARD_LPI2C_Send(BOARD_ADP5585_I2C, deviceAddress, subAddress, subAddressSize, (uint8_t *)txBuff, txBuffSize,
                            flags);
}

status_t BOARD_ADP5585_I2C_Receive(uint8_t deviceAddress,
                                   uint32_t subAddress,
                                   uint8_t subAddressSize,
                                   uint8_t *rxBuff,
                                   uint8_t rxBuffSize,
                                   uint32_t flags)
{
    return BOARD_LPI2C_Receive(BOARD_ADP5585_I2C, deviceAddress, subAddress, subAddressSize, rxBuff, rxBuffSize, flags);
}

void BOARD_InitADP5585(adp5585_handle_t *handle)
{
    BOARD_ADP5585_I2C_Init();

    static const adp5585_config_t config = {
        .i2cAddr         = BOARD_ADP5585_I2C_ADDR,
        .I2C_SendFunc    = BOARD_ADP5585_I2C_Send,
        .I2C_ReceiveFunc = BOARD_ADP5585_I2C_Receive,
    };

    ADP5585_Init(handle, &config);
}

#endif /* BOARD_USE_ADP5585. */

#if defined(BOARD_USE_PCAL6524) && BOARD_USE_PCAL6524
void BOARD_PCAL6524_I2C_Init(void)
{
    BOARD_LPI2C_Init(BOARD_PCAL6524_I2C, BOARD_PCAL6524_I2C_CLOCK_FREQ);
}

status_t BOARD_PCAL6524_I2C_Send(uint8_t deviceAddress,
                                 uint32_t subAddress,
                                 uint8_t subAddressSize,
                                 const uint8_t *txBuff,
                                 uint8_t txBuffSize,
                                 uint32_t flags)
{
    return BOARD_LPI2C_Send(BOARD_PCAL6524_I2C, deviceAddress, subAddress, subAddressSize, (uint8_t *)txBuff,
                            txBuffSize, flags);
}

status_t BOARD_PCAL6524_I2C_Receive(uint8_t deviceAddress,
                                    uint32_t subAddress,
                                    uint8_t subAddressSize,
                                    uint8_t *rxBuff,
                                    uint8_t rxBuffSize,
                                    uint32_t flags)
{
    return BOARD_LPI2C_Receive(BOARD_PCAL6524_I2C, deviceAddress, subAddress, subAddressSize, rxBuff, rxBuffSize,
                               flags);
}

void BOARD_InitPCAL6524(pcal6524_handle_t *handle)
{
    BOARD_PCAL6524_I2C_Init();

    static const pcal6524_config_t config = {
        .i2cAddr         = BOARD_PCAL6524_I2C_ADDR,
        .I2C_SendFunc    = BOARD_PCAL6524_I2C_Send,
        .I2C_ReceiveFunc = BOARD_PCAL6524_I2C_Receive,
    };

    PCAL6524_Init(handle, &config);
}

#endif /* BOARD_USE_PCAL6524. */

#endif

void BOARD_McoreSUSPEND(void)
{
    uint32_t value = 0U;
    /* Config OSCPLL LPM setting for M33 SUSPEND */
    for (unsigned int i = OSCPLL_LPM_START; i <= OSCPLL_LPM_END; i++)
    {
        CCM_CTRL->OSCPLL[i].LPM0 |= CCM_OSCPLL_LPM0_LPM_SETTING_D2_MASK;
    }

    /* Config GPC_CTRL_CM33 to set Mcore as SUSPEND mode */
    GPC_CTRL_CM33->CM_MODE_CTRL |= GPC_CPU_CTRL_CM_MODE_CTRL_CPU_MODE_TARGET_MASK;

    /* Stop SysTick and enter WFI
     * System will goes into system sleep flow
     * The STBY LED on board will light with red color
     */
    /* Save old value of SYST_CSR */
    value            = SYSTICK_CTRL_REG;
    SYSTICK_CTRL_REG = SYSTICK_CLOSE;
    __WFI();
    /* Enable systick */
    SYSTICK_CTRL_REG = value;
}

void BOARD_ConfigMPU(void)
{
    uint8_t attr;

    /* Disable code cache(ICache) and system cache(DCache) */
    XCACHE_DisableCache(LPCAC_PC);
    XCACHE_DisableCache(LPCAC_PS);

    /* NOTE: All TCRAM is non-cacheable regardless of MPU setting. */

    /*
     * default cache policy(default memory access behavior) after enable mpu on cortex-m33(according to RM of
     * cortex-m33): 0x00000000-0x1FFFFFFF Normal memory, Non-shareable, Write-Through, not Write Allocate
     * 0x20000000-0x3FFFFFFF Normal memory, Non-shareable, Write-Back, Write Allocate
     * 0x40000000-0x5FFFFFFF Device, Shareable
     * 0x60000000-0x7FFFFFFF Normal memory, Non-shareable, Write-Back, Write Allocate
     * 0x80000000-0x9FFFFFFF Normal memory, Non-shareable, Write-Through, not Write Allocate
     * 0xA0000000-0xDFFFFFFF Device, Shareable
     * 0xE0000000-0xE003FFFF Device, Shareable
     * 0xE0040000-0xE0043FFF Device, Shareable
     * 0xE0044000-0xE00EFFFF Device, Shareable
     * 0xF0000000-0xFFFFFFFF Device, Shareable
     */
    /* Disable MPU */
    ARM_MPU_Disable();

    /* Attr0: Device-nGnRnE */
    ARM_MPU_SetMemAttr(0U, ARM_MPU_ATTR(ARM_MPU_ATTR_DEVICE, ARM_MPU_ATTR_DEVICE));

    /* Attr1: Normal memory, Outer non-cacheable, Inner non-cacheable */
    ARM_MPU_SetMemAttr(1U, ARM_MPU_ATTR(ARM_MPU_ATTR_NON_CACHEABLE, ARM_MPU_ATTR_NON_CACHEABLE));

    /* Attr2: Normal memory, Inner write-through transient, read allocate. Inner write-through transient, read allocate
     */
    attr = ARM_MPU_ATTR_MEMORY_(0U, 0U, 1U, 0U);
    ARM_MPU_SetMemAttr(2U, ARM_MPU_ATTR(attr, attr));

    /* Attr3: Normal memory, Outer write-back transient, read/write allocate. Inner write-back transient, read/write
     * allocate */
    attr = ARM_MPU_ATTR_MEMORY_(0U, 1U, 1U, 1U);
    ARM_MPU_SetMemAttr(3U, ARM_MPU_ATTR(attr, attr));

    /*
     * Change macro definitions as follows when choose cache policy as non-cacheable:
     * #define DDR_NONCACHEABLE (1U)
     * #define DDR_WRITE_THROUGH (0U)
     * #define DDR_WRITE_BACK (0U)
     *
     *
     * Change macro definitions as follows when choose cache policy as Write-Through:
     * #define DDR_NONCACHEABLE (0U)
     * #define DDR_WRITE_THROUGH (1U)
     * #define DDR_WRITE_BACK (0U)
     *
     *
     * Change macro definitions as follows when choose cache policy as Write-Back:
     * #define DDR_NONCACHEABLE (0U)
     * #define DDR_WRITE_THROUGH (0U)
     * #define DDR_WRITE_BACK (1U)
     */
#define DDR_NONCACHEABLE  (1U)
#define DDR_WRITE_THROUGH (0U)
#define DDR_WRITE_BACK    (0U)
#if DDR_NONCACHEABLE
    /* NOTE: DDR is used as shared memory for A/M core communication, set it to non-cacheable. */
    /* Region 0: [0x80000000, 0xDFFFFFFF](DRAM), outer shareable, read/write, any privileged, executable. Attr 1
     * (non-cacheable). */
    ARM_MPU_SetRegion(0U, ARM_MPU_RBAR(0x80000000, ARM_MPU_SH_OUTER, 0U, 1U, 0U), ARM_MPU_RLAR(0xDFFFFFFF, 1U));
#elif DDR_WRITE_THROUGH
    /* Region 0: [0x80000000, 0xDFFFFFFF](DRAM), outer shareable, read/write, any privileged, executable. Attr 2
     * (Normal memory, Inner write-through transient, read allocate. Inner write-through transient, read allocate). */
    ARM_MPU_SetRegion(0U, ARM_MPU_RBAR(0x80000000, ARM_MPU_SH_OUTER, 0U, 1U, 0U), ARM_MPU_RLAR(0xDFFFFFFF, 2U));
#elif DDR_WRITE_BACK
    /* Region 0: [0x80000000, 0xDFFFFFFF](DRAM), outer shareable, read/write, any privileged, executable. Attr 3
     * (Normal memory, Outer write-back transient, read/write allocate. Inner write-back transient, read/write
     * allocate). */
    ARM_MPU_SetRegion(0U, ARM_MPU_RBAR(0x80000000, ARM_MPU_SH_OUTER, 0U, 1U, 0U), ARM_MPU_RLAR(0xDFFFFFFF, 3U));
#endif

    /* Enable MPU(use default memory map when access the memory within region) */
    ARM_MPU_Enable(MPU_CTRL_HFNMIENA_Msk | MPU_CTRL_PRIVDEFENA_Msk);

    /* Enable ICache and DCache */
    XCACHE_EnableCache(LPCAC_PC);
    XCACHE_EnableCache(LPCAC_PS);
    /* flush pipeline */
    __DSB();
    __ISB();
}

#if defined(BOARD_USE_DDR_RETENTION) && BOARD_USE_DDR_RETENTION
static unsigned long BOARD_DDRPHY_Addr_Remap(uint32_t paddr_apb_from_ctlr)
{
    uint32_t paddr_apb_qual;
    uint32_t paddr_apb_unqual_dec_22_13;
    uint32_t paddr_apb_unqual_dec_19_13;
    uint32_t paddr_apb_unqual_dec_12_1;
    uint32_t paddr_apb_unqual;
    uint32_t paddr_apb_phy;

    paddr_apb_qual             = (paddr_apb_from_ctlr << 1);
    paddr_apb_unqual_dec_22_13 = ((paddr_apb_qual & 0x7fe000) >> 13);
    paddr_apb_unqual_dec_12_1  = ((paddr_apb_qual & 0x1ffe) >> 1);

    /* seacrching backward, so the last tested addr (0) is also the default value in case not found */
    paddr_apb_unqual_dec_19_13 = DDRPHY_NB_ADDR_REMAP - 1;
    while ((paddr_apb_unqual_dec_19_13 > 0) &&
           (BOARD_DDRPHY_Addr_Remap_table[paddr_apb_unqual_dec_19_13] != (uint16_t)paddr_apb_unqual_dec_22_13))
    {
        paddr_apb_unqual_dec_19_13--;
    }

    paddr_apb_unqual = ((paddr_apb_unqual_dec_19_13 << 13) | (paddr_apb_unqual_dec_12_1 << 1));
    paddr_apb_phy    = (paddr_apb_unqual << 1);
    return paddr_apb_phy;
}

int BOARD_Check_DDRC_Idle(int waitus, uint32_t flag)
{
    uint32_t ddrdsr2_val;
    int waitforever = 0;
    int waitedus    = 0;
    if (waitus == 0)
    {
        waitforever = 1;
    }

    do
    {
        ddrdsr2_val = DDR_CTRL->DDRDSR_2;
        if ((ddrdsr2_val & flag) == flag)
        {
            /* Memory controller is idle */
            break;
        }
        SDK_DelayAtLeastUs(1, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
        waitus--;
        waitedus++;
    } while (waitus | waitforever);

    if ((waitus == 0) & !waitforever)
    {
        return -1;
    }
    return waitedus;
}

static void BOARD_Ipg_Stop_Ack_Wait(uint32_t expect_value)
{
    uint32_t read_data;
    read_data = BLK_CTRL_DDRMIX->DDRC_STOP_CTRL;

    if (expect_value == 0x1)
    {
        while ((read_data & BIT(1)) == 0x0)
        {
            /* DDR Controller ipg_stop_ack is a 0 */
            read_data = BLK_CTRL_DDRMIX->DDRC_STOP_CTRL;
        }
        /* DDR Controller ipg_stop_ack is a 1 */
    }
    else if (expect_value == 0x0)
    {
        while ((read_data & BIT(1)) != 0x0)
        {
            /* DDR Controller ipg_stop_ack is a 1 */
            read_data = BLK_CTRL_DDRMIX->DDRC_STOP_CTRL;
        }
        /* DDR Controller ipg_stop_ack is a 0 */
    }
}

/* Check whether PHY initialization is complete */
void BOARD_Check_Dfi_Init_Complete(void)
{
    uint32_t ddr_phy_status = 0;

    do
    {
        ddr_phy_status = DDR_CTRL->DDRDSR_2;
        if (ddr_phy_status & DDRC_DDRDSR_2_PHY_INIT_CMPLT_MASK)
        {
            /* PHY initialization is complete */
            break;
        }
    } while (1);

    DDR_CTRL->DDRDSR_2 |= DDRC_DDRDSR_2_PHY_INIT_CMPLT_MASK;
}

void BOARD_DDRCEnterSelfRefresh(void)
{
    /* Set FRC_SR bit, put DDRC into self-refresh mode */
    DDR_CTRL->DDR_SDRAM_CFG_2 |= DDRC_DDR_SDRAM_CFG_2_FRC_SR_MASK;
}

void BOARD_DDRPHY_ClodRest(void)
{
    /*
     * dramphy_apb_n default 1 , assert -> 0, de_assert -> 1
     * dramphy_reset_n default 0 , assert -> 0, de_assert -> 1
     * dramphy_PwrOKIn default 0 , assert -> 1, de_assert -> 0
     */
    /* src_gen_dphy_apb_sw_rst_de_assert */
    SRC_DPHY_SLICE->SLICE_SW_CTRL &= ~SRC_MIX_SLICE_SLICE_SW_CTRL_RST_CTRL_SOFT_MASK;
    /* src_gen_dphy_sw_rst_de_assert */
    SRC_DPHY_SLICE->SINGLE_RESET_SW_CTRL &= ~SRC_MIX_SLICE_SINGLE_RESET_SW_CTRL_RST_CTRL_SOFT_1_MASK;
    /* src_gen_dphy_PwrOKIn_sw_rst_de_assert() */
    SRC_DPHY_SLICE->SINGLE_RESET_SW_CTRL |= SRC_MIX_SLICE_SINGLE_RESET_SW_CTRL_RST_CTRL_SOFT_0_MASK;
    SDK_DelayAtLeastUs(10, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

    /* src_gen_dphy_apb_sw_rst_assert */
    SRC_DPHY_SLICE->SLICE_SW_CTRL |= SRC_MIX_SLICE_SLICE_SW_CTRL_RST_CTRL_SOFT_MASK;
    /* src_gen_dphy_sw_rst_assert */
    SRC_DPHY_SLICE->SINGLE_RESET_SW_CTRL |= SRC_MIX_SLICE_SINGLE_RESET_SW_CTRL_RST_CTRL_SOFT_1_MASK;
    SDK_DelayAtLeastUs(10, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

    /* src_gen_dphy_PwrOKIn_sw_rst_assert */
    SRC_DPHY_SLICE->SINGLE_RESET_SW_CTRL &= ~SRC_MIX_SLICE_SINGLE_RESET_SW_CTRL_RST_CTRL_SOFT_0_MASK;
    SDK_DelayAtLeastUs(10, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

    /* src_gen_dphy_apb_sw_rst_de_assert */
    SRC_DPHY_SLICE->SLICE_SW_CTRL &= ~SRC_MIX_SLICE_SLICE_SW_CTRL_RST_CTRL_SOFT_MASK;
    /* src_gen_dphy_sw_rst_de_assert() */
    SRC_DPHY_SLICE->SINGLE_RESET_SW_CTRL &= ~SRC_MIX_SLICE_SINGLE_RESET_SW_CTRL_RST_CTRL_SOFT_1_MASK;
}

void BOARD_DRAM_PLL_Init(void)
{
    /* Powerup and Enable DRAM PLL block*/
    DRAMPLL->CTRL.SET |= PLL_CTRL_POWERUP_MASK;

    /* Wait lock */
    while (!(R32(DRAMPLL->PLL_STATUS) & PLL_PLL_STATUS_PLL_LOCK_MASK))
    {
        ;
    }

    /* Enable PLL output clock */
    DRAMPLL->CTRL.SET |= PLL_CTRL_CLKMUX_EN_MASK;
}

void BOARD_DDR_Disable_Bypass(void)
{
    /* Set DRAM APB to 133Mhz */
    const clock_root_config_t dramapbClkCfg = {.clockOff = false, .mux = 2, .div = 3};
    CLOCK_SetRootClock(kCLOCK_Root_DramApb, &dramapbClkCfg);

    /* wait for the new setting update done */
    while (R32(DRAM_APB_CLK + 0x20) & BIT(28))
    {
        ;
    }

    /* Switch from DRAM  clock root from CCM to PLL */
    CCM_CTRL->GPR_SHARED2.CLR |= CCM_GPR_SHARED2_DRAM_PLL_BYPASS_MASK;
}

/* Restore the dram PHY config */
void BOARD_DRAM_PHY_Restore(struct dram_timing_info *timing)
{
    struct dram_cfg_param *cfg = timing->ddrphy_cfg;
    uint32_t i;

    /* Restore the PHY init config */
    cfg = timing->ddrphy_cfg;
    for (i = 0U; i < timing->ddrphy_cfg_num; i++)
    {
        dwc_ddrphy_apb_wr(cfg->reg, cfg->val);
        cfg++;
    }

    dwc_ddrphy_apb_wr(0xd0000, 0x0);
    dwc_ddrphy_apb_wr(0xc0080, 0x3);

    /* Restore the DDR PHY CSRs */
    cfg = timing->ddrphy_trained_csr;
    for (i = 0U; i < timing->ddrphy_trained_csr_num; i++)
    {
        dwc_ddrphy_apb_wr(cfg->reg, cfg->val);
        cfg++;
    }

    dwc_ddrphy_apb_wr(0xc0080, 0x2);
    dwc_ddrphy_apb_wr(0xd0000, 0x1);

    /* Load the PIE image */
    cfg = timing->ddrphy_pie;
    for (i = 0U; i < timing->ddrphy_pie_num; i++)
    {
        dwc_ddrphy_apb_wr(cfg->reg, cfg->val);
        cfg++;
    }
}

void BOARD_DDRC_Restore(struct dram_timing_info *timing)
{
    struct dram_cfg_param *ddrc_cfg = timing->ddrc_cfg;
    uint32_t i;
    uint32_t waitus = 0;

    for (i = 0; i < timing->ddrc_cfg_num; i++)
    {
        /* skip the dram init as we resume from retention */
        if (ddrc_cfg->reg == DDR_SDRAM_CFG_ADDR)
        {
            W32(ddrc_cfg->reg, ddrc_cfg->val & ~BIT(4));
        }
        else
        {
            W32(ddrc_cfg->reg, ddrc_cfg->val);
        }
        ddrc_cfg++;
    }

    if (timing->fsp_cfg != NULL)
    {
        ddrc_cfg = timing->fsp_cfg[0].ddrc_cfg;
        while (ddrc_cfg->reg != 0)
        {
            W32(ddrc_cfg->reg, ddrc_cfg->val);
            ddrc_cfg++;
        }
    }

    /* Check whether PHY initialization is complete */
    BOARD_Check_Dfi_Init_Complete();

    /* Enable DDRC */
    DDR_CTRL->DDR_SDRAM_CFG |= DDRC_DDR_SDRAM_CFG_MEM_EN_MASK;

    /* Waiting for DDRC idel status all the times */
    waitus = BOARD_Check_DDRC_Idle(DDRC_DDRDSR_2_Check_Idel_time, DDRC_DDRDSR_2_IDLE_MASK);

    if (waitus == -1)
    {
        PRINTF("Check DDRC Idel status fail\r\n");
    }
}

void BOARD_DRAMEnterRetention(void)
{
    uint32_t waitus = 0;

    /* Waiting for DDRC idel status all the times */
    waitus = BOARD_Check_DDRC_Idle(DDRC_DDRDSR_2_Check_Idel_time, DDRC_DDRDSR_2_IDLE_MASK);

    if (waitus == -1)
    {
        PRINTF("Check DDRC Idel status fail\r\n");
    }

    /* Set MEM_HALT bit, halt any new transactions for DDR SDRAM */
    DDR_CTRL->DDR_SDRAM_CFG |= DDRC_DDR_SDRAM_CFG_MEM_HALT_MASK;

    /* Set DDR_SDRAM_CFG_3[SR_FAST_WK_EN], select fast wakeup method */
    DDR_CTRL->DDR_SDRAM_CFG_3 |= DDRC_DDR_SDRAM_CFG_3_SR_FAST_WK_EN_MASK;

    /*
     * Temporarily DDR_SDRAM_CFG_4 info unavailable on 93 RM.
     * Program DFI Frequency to max value, DDR_SDRAM_CFG_4[DFI_FREQ] to 2b'1111.
     */
    DDR_CTRL->DDR_SDRAM_CFG_4 |= 0x1f000;

    /* Clear DDR_ZQ_CNTL register */
    DDR_CTRL->DDR_ZQ_CNTL = 0x0;

    /* Set DEBUG_26[DIS_CTRLUPD_REQ */
    SETBIT32(DDR_CTRL_BASE + DDR_DEBUG_26, (0x1f << 12));

    /* Force the DDRC to enter self-refresh */
    BOARD_DDRCEnterSelfRefresh();

    /* Set BLK_CTRL_DDRMIX AUTO_CG_CTRL[HWFFC_ACG_FORCE_B], enable ipg_stop_reg while auto cg */
    BLK_CTRL_DDRMIX->AUTO_CG_CTRL |= DDRMIX_BLK_CTRL_AUTO_CG_CTRL_HWFFC_ACG_FORCE_B_MASK;
    /* Set DDR_SDRAM_CFG[SREN] bit, enable DDR self-refresh function during sleep */
    DDR_CTRL->DDR_SDRAM_CFG |= DDRC_DDR_SDRAM_CFG_SREN_MASK;
    /* Set DDR_SDRAM_CFG_3[DRAIN_FOR_SR], drain DDRC main command for self refresh */
    DDR_CTRL->DDR_SDRAM_CFG_3 |= DDRC_DDR_SDRAM_CFG_3_DRAIN_FOR_SR_MASK;

    /* Set stop and poll stop ack */
    BOARD_Ipg_Stop_Ack_Wait(DDRC_STOP_ACK_SET_MASK);
    BLK_CTRL_DDRMIX->DDRC_STOP_CTRL |= DDRMIX_BLK_CTRL_DDRC_STOP_CTRL_DDRC_STOP_MASK;

    BOARD_Ipg_Stop_Ack_Wait(DDRC_STOP_ACK_POLL_MASK);

    /* Clear DDR_INTERVAL(this disables refreshes) */
    DDR_CTRL->DDR_SDRAM_INTERVAL = 0x0;

    /* Set DDR_SDRAM_MD_CNTL[CKE_CNTL] to 0x00100000(this forces CKE to remain low) */
    DDR_CTRL->DDR_SDRAM_MD_CNTL = 0x00100000;

    /* Remove Stop request via DDRMIX register */
    BLK_CTRL_DDRMIX->DDRC_STOP_CTRL &= ~DDRMIX_BLK_CTRL_DDRC_STOP_CTRL_DDRC_STOP_MASK;

    BOARD_Check_Dfi_Init_Complete();

    /* Clear DDR_SDRAM_CFG[SREN] */
    DDR_CTRL->DDR_SDRAM_CFG &= ~DDRC_DDR_SDRAM_CFG_SREN_MASK;

    /* Clear DDR_SDRAM_CFG_3[SR_FAST_WK_EN] */
    DDR_CTRL->DDR_SDRAM_CFG_3 &= ~DDRC_DDR_SDRAM_CFG_3_SR_FAST_WK_EN_MASK;

    /* Set stop request and poll again via DDRMIX register */
    BOARD_Ipg_Stop_Ack_Wait(DDRC_STOP_ACK_SET_MASK);
    BLK_CTRL_DDRMIX->DDRC_STOP_CTRL |= DDRMIX_BLK_CTRL_DDRC_STOP_CTRL_DDRC_STOP_MASK;

    BOARD_Ipg_Stop_Ack_Wait(DDRC_STOP_ACK_POLL_MASK);

    /* Set STOP request again via DDRMIX register */
    BLK_CTRL_DDRMIX->DDRC_STOP_CTRL &= ~DDRMIX_BLK_CTRL_DDRC_STOP_CTRL_DDRC_STOP_MASK;

    /* Should check PhyInLP3 pub reg */
    dwc_ddrphy_apb_wr(0xd0000, 0x0);
    if (!(dwc_ddrphy_apb_rd(0x90028) & 0x1))
    {
        PRINTF("PhyInLP3 = 1\r\n");
    }
    dwc_ddrphy_apb_wr(0xd0000, 0x1);

    /* Clear PwrOkIn via DDRMIX regsiter */
    SRC_DPHY_SLICE->SINGLE_RESET_SW_CTRL |= SRC_MIX_SLICE_SINGLE_RESET_SW_CTRL_RST_CTRL_SOFT_0_MASK;
    /* Power off the DDRMIX */
    SDK_DelayAtLeastUs(10, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    SRC_DDR_SLICE->SLICE_SW_CTRL |= SRC_MIX_SLICE_SLICE_SW_CTRL_PDN_SOFT_MASK;
    SDK_DelayAtLeastUs(10, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
}

void BOARD_DRAMExitRetention(void)
{
    /* Power up the DDRMIX */
    SRC_DDR_SLICE->SLICE_SW_CTRL &= ~SRC_MIX_SLICE_SLICE_SW_CTRL_PDN_SOFT_MASK;

    /* additional step to make sure DDR exit retenton works */
    SRC_DDR_SLICE->SLICE_SW_CTRL |= SRC_MIX_SLICE_SLICE_SW_CTRL_RST_CTRL_SOFT_MASK;
    SDK_DelayAtLeastUs(10, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

    SRC_DDR_SLICE->SLICE_SW_CTRL &= ~SRC_MIX_SLICE_SLICE_SW_CTRL_RST_CTRL_SOFT_MASK;
    SDK_DelayAtLeastUs(10, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

    /* Cold reset the DDRPHY */
    BOARD_DDRPHY_ClodRest();

    /* Config the DRAM PLL to FSP0 */
    BOARD_DRAM_PLL_Init();
    BOARD_DDR_Disable_Bypass();

    /* Reload the DDRPHY config */
    BOARD_DRAM_PHY_Restore(timing_info);

    /* Reload the ddrc config */
    BOARD_DDRC_Restore(timing_info);
}
#endif
