/*
 * Copyright 2017-2018 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "fsl_gpio.h"
#include "fsl_lpi2c.h"
#include "svc/misc/misc_api.h"
#include "fsl_irqsteer.h"
#include "fsl_video_common.h"
#include "fsl_display.h"
#include "dpu_example.h"
#include "fsl_irqsteer.h"
#include "fsl_dpu_irqsteer.h"
#include "fsl_debug_console.h"
#if DPU_EXAMPLE_DI == DPU_DI_MIPI
#if !APP_DISPLAY_EXTERNAL_CONVERTOR
#include "fsl_mipi_dsi.h"
#include "fsl_rm67191.h"
#else
#include "fsl_adv7535.h"
#endif
#elif DPU_EXAMPLE_DI == DPU_DI_LVDS
#include "fsl_ldb.h"
#include "fsl_it6263.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if (DPU_EXAMPLE_DI == DPU_DI_LVDS) && (!APP_DISPLAY_EXTERNAL_CONVERTOR)
#error LDB only support external convertor
#endif

#if (DPU_EXAMPLE_DI == DPU_DI_MIPI)

#if (APP_MIPI_DSI_BASE == DI_MIPI_DSI_LVDS_0__MIPI_DSI_HOST_BASE)
#define BOARD_Display_I2C_Init    BOARD_Display0_I2C_Init
#define BOARD_Display_I2C_Send    BOARD_Display0_I2C_Send
#define BOARD_Display_I2C_Receive BOARD_Display0_I2C_Receive
#define MIPI_DSI_RSRC             SC_R_MIPI_0
#else /* (APP_MIPI_DSI_BASE == DI_MIPI_DSI_LVDS_0__MIPI_DSI_HOST_BASE) */
#define BOARD_Display_I2C_Init    BOARD_Display1_I2C_Init
#define BOARD_Display_I2C_Send    BOARD_Display1_I2C_Send
#define BOARD_Display_I2C_Receive BOARD_Display1_I2C_Receive
#define MIPI_DSI_RSRC             SC_R_MIPI_1
#endif /* (APP_MIPI_DSI_BASE == DI_MIPI_DSI_LVDS_0__MIPI_DSI_HOST_BASE) */

#elif (DPU_EXAMPLE_DI == DPU_DI_LVDS)

#if (APP_LDB_BASE == MIPI_DSI_LVDS_COMBO0_CSR_BASE)
#define BOARD_Display_I2C_Init    BOARD_Display0_I2C_Init
#define BOARD_Display_I2C_Send    BOARD_Display0_I2C_Send
#define BOARD_Display_I2C_Receive BOARD_Display0_I2C_Receive
#define LDB_RSRC                  SC_R_LVDS_0
#define MIPI_DSI_RSRC             SC_R_MIPI_0
#else /* (APP_LDB_BASE == MIPI_DSI_LVDS_COMBO0_CSR_BASE) */
#define BOARD_Display_I2C_Init    BOARD_Display1_I2C_Init
#define BOARD_Display_I2C_Send    BOARD_Display1_I2C_Send
#define BOARD_Display_I2C_Receive BOARD_Display1_I2C_Receive
#define LDB_RSRC                  SC_R_LVDS_1
#define MIPI_DSI_RSRC             SC_R_MIPI_1
#endif /* (APP_LDB_BASE == MIPI_DSI_LVDS_COMBO0_CSR_BASE) */

#endif /*DPU_EXAMPLE_DI */

#define DC_RSRC SC_R_DC_0

#if (0 == APP_DPU_DISPLAY_INDEX)
#define DC_PLL_RSRC      SC_R_DC_0_PLL_0
#define DC_DISPLAY_CLOCK SC_PM_CLK_MISC0
#else /* (0 == APP_DPU_DISPLAY_INDEX) */
#define DC_PLL_RSRC      SC_R_DC_0_PLL_1
#define DC_DISPLAY_CLOCK SC_PM_CLK_MISC1
#endif /* (0 == APP_DPU_DISPLAY_INDEX) */

#if (!APP_DISPLAY_EXTERNAL_CONVERTOR) || (DPU_EXAMPLE_DI == DPU_DI_LVDS)
#define IOEXP_I2C      ADMA__LPI2C1
#define IOEXP_I2C_RSRC SC_R_I2C_1

#define SWITCH_I2C_ADDR 0x71

#if (APP_MIPI_DSI_BASE == DI_MIPI_DSI_LVDS_0__MIPI_DSI_HOST_BASE) || (APP_LDB_BASE == MIPI_DSI_LVDS_COMBO0_CSR_BASE)
#define IOEXP_I2C_ADDR     0x1A
#define IOEXP_MIPI_DSI_PIN 6
#else
#define IOEXP_I2C_ADDR     0x1D
#define IOEXP_MIPI_DSI_PIN 7
#endif /* (APP_MIPI_DSI_BASE == DI_MIPI_DSI_LVDS_0__MIPI_DSI_HOST_BASE) */

#define PCA9557_REG_INTPUT_PORT        (0x00)
#define PCA9557_REG_OUTPUT_PORT        (0x01)
#define PCA9557_REG_POLARITY_INVERSION (0x02)
#define PCA9557_REG_CONFIGURATION      (0x03)

#endif /* APP_DISPLAY_EXTERNAL_CONVERTOR */

#if (DPU_EXAMPLE_DI == DPU_DI_MIPI)
/* Pixel Link address */
typedef struct _dpu_mipi_pl_addr
{
    IRIS_MVPL_Type *dpu;
    uint8_t dpuDisplayIndex;
    MIPI_DSI_HOST_Type *dsi;
    uint8_t plAddr;
} dpu_mipi_pl_addr_t;

#elif (DPU_EXAMPLE_DI == DPU_DI_LVDS)
/* Pixel Link address */
typedef struct _dpu_ldb_pl_addr
{
    IRIS_MVPL_Type *dpu;
    uint8_t dpuDisplayIndex;
    LDB_Type *ldb;
    uint8_t plAddr;
} dpu_ldb_pl_addr_t;

#endif /* DPU_EXAMPLE_DI */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
extern void DPU_IRQHandler(void);
#if (DPU_EXAMPLE_DI == DPU_DI_MIPI)

#if !APP_DISPLAY_EXTERNAL_CONVERTOR
static void RM67191_PullResetPin(bool pullUp);
status_t RM67191_DSI_Transfer(dsi_transfer_t *xfer);
#endif

#elif (DPU_EXAMPLE_DI == DPU_DI_LVDS)
static void IT6263_PullResetPin(bool pullUp);
#endif /* DPU_EXAMPLE_DI */

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if (DPU_EXAMPLE_DI == DPU_DI_MIPI)

#if !APP_DISPLAY_EXTERNAL_CONVERTOR

static mipi_dsi_device_t dsiDevice = {
    .virtualChannel = 0,
    .xferFunc       = RM67191_DSI_Transfer,
};

static const rm67191_resource_t rm67191Resource = {
    .dsiDevice    = &dsiDevice,
    .pullResetPin = RM67191_PullResetPin,
};

static display_handle_t rm67191Handle = {
    .resource = &rm67191Resource,
    .ops      = &rm67191_ops,
};
#endif

#elif (DPU_EXAMPLE_DI == DPU_DI_LVDS)

static it6263_resource_t it6263Resource = {
    .i2cAddr        = 0x98,
    .pullResetPin   = IT6263_PullResetPin,
    .i2cSendFunc    = BOARD_Display_I2C_Send,
    .i2cReceiveFunc = BOARD_Display_I2C_Receive,
};

static display_handle_t it6263Handle = {
    .resource = &it6263Resource,
    .ops      = &it6263_ops,
};
#endif /* DPU_EXAMPLE_DI  */

/*******************************************************************************
 * Codes
 ******************************************************************************/
#if (!APP_DISPLAY_EXTERNAL_CONVERTOR) || (DPU_EXAMPLE_DI == DPU_DI_LVDS)
static status_t PCA9557_ModifyReg(
    LPI2C_Type *base, const uint8_t dev_addr, const uint8_t reg_offset, uint8_t mask, uint8_t value)
{
    status_t status = kStatus_Fail;

    uint8_t data[2];

    data[0] = reg_offset;

    /* Read the register value back. */
    while (1)
    {
        status = LPI2C_MasterStart(base, dev_addr, kLPI2C_Write);

        if (kStatus_Success != status)
        {
            (void)LPI2C_MasterStop(base);
        }
        else
        {
            break;
        }
    }

    (void)LPI2C_MasterSend(base, data, 1);

    (void)LPI2C_MasterStart(base, dev_addr, kLPI2C_Read);

    (void)LPI2C_MasterReceive(base, &data[1], 1);

    (void)LPI2C_MasterStop(base);

    /* Modify the register value. */
    data[1] &= ~mask;
    data[1] |= (value & mask);

    /* Write the register value. */
    while (1)
    {
        status = LPI2C_MasterStart(base, dev_addr, kLPI2C_Write);

        if (kStatus_Success != status)
        {
            (void)LPI2C_MasterStop(base);
        }
        else
        {
            break;
        }
    }

    (void)LPI2C_MasterSend(base, data, 2);

    return LPI2C_MasterStop(base);
}

static status_t PCA9646_Write(LPI2C_Type *base, const uint8_t dev_addr, uint8_t value)
{
    status_t status = kStatus_Fail;

    /* Write the register value. */
    while (1)
    {
        status = LPI2C_MasterStart(base, dev_addr, kLPI2C_Write);

        if (kStatus_Success != status)
        {
            (void)LPI2C_MasterStop(base);
        }
        else
        {
            break;
        }
    }

    (void)LPI2C_MasterSend(base, &value, 1);

    return LPI2C_MasterStop(base);
}

static status_t BOARD_InitExpansionIO(void)
{
    sc_ipc_t ipc;
    sc_err_t err = SC_ERR_NONE;
    lpi2c_master_config_t masterConfig;
    sc_pm_clock_rate_t i2cClkFreq = SC_24MHZ;

    ipc = BOARD_GetRpcHandle();

    /*
     * Initialize the I2C.
     */
    /* open the lpi2c power and clock */
    err = sc_pm_set_resource_power_mode(ipc, IOEXP_I2C_RSRC, SC_PM_PW_MODE_ON);
    if (err != SC_ERR_NONE)
        return kStatus_Fail;

    err = sc_pm_clock_enable(ipc, IOEXP_I2C_RSRC, SC_PM_CLK_PER, true, false);
    if (err != SC_ERR_NONE)
        return kStatus_Fail;

    err = sc_pm_set_clock_rate(ipc, IOEXP_I2C_RSRC, SC_PM_CLK_PER, &i2cClkFreq);
    if (err != SC_ERR_NONE)
        return kStatus_Fail;

    /* lpi2c init */
    LPI2C_MasterGetDefaultConfig(&masterConfig);
    masterConfig.baudRate_Hz = 400000;

    LPI2C_MasterInit(IOEXP_I2C, &masterConfig, i2cClkFreq);

    /*Configure Expansion Pin*/
    /* PCA9646 channel 3 is output to PCA9557. */
    PCA9646_Write(IOEXP_I2C, SWITCH_I2C_ADDR, (1 << 3));

    /* Set DSI pin enable and standby pin as output */
    return PCA9557_ModifyReg(IOEXP_I2C, IOEXP_I2C_ADDR, PCA9557_REG_CONFIGURATION, (1 << IOEXP_MIPI_DSI_PIN), 0);
}

#if (DPU_EXAMPLE_DI == DPU_DI_MIPI)
static void RM67191_PullResetPin(bool pullUp)
{
    if (pullUp)
    {
        PCA9557_ModifyReg(IOEXP_I2C, IOEXP_I2C_ADDR, PCA9557_REG_OUTPUT_PORT, (1 << IOEXP_MIPI_DSI_PIN), 0xFF);
    }
    else
    {
        PCA9557_ModifyReg(IOEXP_I2C, IOEXP_I2C_ADDR, PCA9557_REG_OUTPUT_PORT, (1 << IOEXP_MIPI_DSI_PIN), 0x00);
    }
}

status_t RM67191_DSI_Transfer(dsi_transfer_t *xfer)
{
    return DSI_TransferBlocking(APP_MIPI_DSI, xfer);
}

#elif (DPU_EXAMPLE_DI == DPU_DI_LVDS)
static void IT6263_PullResetPin(bool pullUp)
{
    if (pullUp)
    {
        PCA9557_ModifyReg(IOEXP_I2C, IOEXP_I2C_ADDR, PCA9557_REG_OUTPUT_PORT, (1 << IOEXP_MIPI_DSI_PIN), 0xFF);
    }
    else
    {
        PCA9557_ModifyReg(IOEXP_I2C, IOEXP_I2C_ADDR, PCA9557_REG_OUTPUT_PORT, (1 << IOEXP_MIPI_DSI_PIN), 0x00);
    }
}
#endif /* DPU_EXAMPLE_DI */
#endif /* APP_DISPLAY_EXTERNAL_CONVERTOR */

/*
 * The DPU output interrupts are:
 *
 * INT_OUT [0] - common
 * INT_OUT [1] - display 0 A
 * INT_OUT [2] - display 0 B (a duplicate to be sent to Coretex-M core)
 * INT_OUT [3] - display 1 A
 * INT_OUT [4] - display 1 B
 * INT_OUT [5] - Reserved
 * INT_OUT [6] - Reserved
 * INT_OUT [7] - BLIT
 *
 * Here use display 0 B and display 1 B.
 */
#if (0 == APP_DPU_DISPLAY_INDEX)
void DISPLAY0_INT_OUT2_IRQHandler(void)
{
    DPU_IRQHandler();
    __DSB();
}
#else
void DISPLAY0_INT_OUT4_IRQHandler(void)
{
    DPU_IRQHandler();
    __DSB();
}
#endif

void DISPLAY0_INT_OUT7_IRQHandler(void)
{
    DPU_IRQHandler();
    __DSB();
}

void SOC_InitDpuInterrupt()
{
    sc_ipc_t ipc;

    ipc = SystemGetScfwIpcHandle();
    sc_pm_set_resource_power_mode(ipc, SC_R_IRQSTR_M4_0, SC_PM_PW_MODE_ON);

    IRQSTEER_Init(IRQSTEER);

#if (0 == APP_DPU_DISPLAY_INDEX)
    IRQSTEER_EnableInterrupt(IRQSTEER, DISPLAY0_INT_OUT2_IRQn);
    DPU_IRQSTEER_EnableInterrupt(DPU0_IRQSTEER, ExtDst0ShadowLoad_DPU_IRQn);
    DPU_IRQSTEER_EnableInterrupt(DPU0_IRQSTEER, ExtDst4ShadowLoad_DPU_IRQn);
    DPU_IRQSTEER_EnableInterrupt(DPU0_IRQSTEER, Display0ShadowLoad_DPU_IRQn);
    DPU_IRQSTEER_EnableInterrupt(DPU0_IRQSTEER, Sig0ShadowLoad_DPU_IRQn);
#else
    IRQSTEER_EnableInterrupt(IRQSTEER, DISPLAY0_INT_OUT4_IRQn);
    DPU_IRQSTEER_EnableInterrupt(DPU0_IRQSTEER, ExtDst1ShadowLoad_DPU_IRQn);
    DPU_IRQSTEER_EnableInterrupt(DPU0_IRQSTEER, ExtDst5ShadowLoad_DPU_IRQn);
    DPU_IRQSTEER_EnableInterrupt(DPU0_IRQSTEER, Display1ShadowLoad_DPU_IRQn);
    DPU_IRQSTEER_EnableInterrupt(DPU0_IRQSTEER, Sig1ShadowLoad_DPU_IRQn);
#endif

    /* Blit engine. */
    IRQSTEER_EnableInterrupt(IRQSTEER, DISPLAY0_INT_OUT7_IRQn);
    DPU_IRQSTEER_EnableInterrupt(DPU0_IRQSTEER, Store9ShadowLoad_DPU_IRQn);
    DPU_IRQSTEER_EnableInterrupt(DPU0_IRQSTEER, Store9SeqComplete_DPU_IRQn);
    DPU_IRQSTEER_EnableInterrupt(DPU0_IRQSTEER, Store9FrameComplete_DPU_IRQn);
}

#if (DPU_EXAMPLE_DI == DPU_DI_MIPI)
status_t SOC_SetDpuMipiDsiPixelLink(sc_ipc_t ipc, IRIS_MVPL_Type *dpu, uint8_t displayIndex, MIPI_DSI_HOST_Type *dsi)
{
    /*
     * Pixel link setting.
     *
     * DPU 0 display0 is connected to MIPI DSI 0 using address 0.
     * DPU 0 display1 is connected to MIPI DSI 1 using address 0.
     *
     * SC_R_DC_0    SC_C_PXL_LINK_MST1_ADDR   Master 1 pixel link address
     * SC_R_DC_0    SC_C_PXL_LINK_MST1_ENB    Master 1 pixel link enable
     * SC_R_DC_0    SC_C_PXL_LINK_MST1_VLD    Master 1 pixel link valid
     * SC_R_DC_0    SC_C_PXL_LINK_MST2_ADDR   Master 2 pixel link address
     * SC_R_DC_0    SC_C_PXL_LINK_MST2_ENB    Master 2 pixel link enable
     * SC_R_DC_0    SC_C_PXL_LINK_MST2_VLD    Master 2 pixel link valid
     * SC_R_DC_0    SC_C_SYNC_CTRL0           PL sync ctrl 0
     * SC_R_DC_0    SC_C_SYNC_CTRL1           PL sync ctrl 1
     */
    uint8_t pixelLinkAddr = 0;
    uint32_t i;
    sc_err_t err = SC_ERR_NONE;

    const dpu_mipi_pl_addr_t dpuMipiPlAddrs[] = {
        {
            .dpu             = DC__IRIS_MVPL,
            .dpuDisplayIndex = 0,
            .dsi             = DI_MIPI_DSI_LVDS_0__MIPI_DSI_HOST,
            .plAddr          = 0,
        },
        {
            .dpu             = DC__IRIS_MVPL,
            .dpuDisplayIndex = 1,
            .dsi             = DI_MIPI_DSI_LVDS_1__MIPI_DSI_HOST,
            .plAddr          = 0,
        },
    };

    const sc_ctrl_t pixelLinkCtrl[][4] = {
        {
            SC_C_PXL_LINK_MST1_ADDR,
            SC_C_PXL_LINK_MST1_ENB,
            SC_C_PXL_LINK_MST1_VLD,
            SC_C_SYNC_CTRL0,
        },
        {
            SC_C_PXL_LINK_MST2_ADDR,
            SC_C_PXL_LINK_MST2_ENB,
            SC_C_PXL_LINK_MST2_VLD,
            SC_C_SYNC_CTRL1,
        },
    };

    /* Get the pixel link address. */
    for (i = 0; i < ARRAY_SIZE(dpuMipiPlAddrs); i++)
    {
        if ((dpu == dpuMipiPlAddrs[i].dpu) && (displayIndex == dpuMipiPlAddrs[i].dpuDisplayIndex) &&
            (dsi == dpuMipiPlAddrs[i].dsi))
        {
            pixelLinkAddr = dpuMipiPlAddrs[i].plAddr;
            break;
        }
    }

    if (ARRAY_SIZE(dpuMipiPlAddrs) <= i)
    {
        PRINTF("ERROR: This DPU to MIPI DSI path is not supported.\r\n");
        return kStatus_Fail;
    }

    /* Set address. */
    err = sc_misc_set_control(ipc, DC_RSRC, pixelLinkCtrl[displayIndex][0], pixelLinkAddr);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    /* Pull down sync control. */
    err = sc_misc_set_control(ipc, DC_RSRC, pixelLinkCtrl[displayIndex][3], 0);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    /* Enable pixel link. */
    err = sc_misc_set_control(ipc, DC_RSRC, pixelLinkCtrl[displayIndex][1], 1);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    /* Delay at least 3 pixel clock. */
    for (volatile uint32_t i = 0; i < 0x100000; i++)
    {
    }

    /* Valid pixel link. */
    err = sc_misc_set_control(ipc, DC_RSRC, pixelLinkCtrl[displayIndex][2], 1);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    /* Pull up sync control. */
    err = sc_misc_set_control(ipc, DC_RSRC, pixelLinkCtrl[displayIndex][3], 1);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    return kStatus_Success;
}
#elif (DPU_EXAMPLE_DI == DPU_DI_LVDS)
status_t SOC_SetDpuLdbPixelLink(sc_ipc_t ipc, IRIS_MVPL_Type *dpu, uint8_t displayIndex, LDB_Type *ldb)
{
    /*
     * Pixel link setting.
     *
     * DPU 0 display1 is connected to LDB 0 using address 0.
     * DPU 1 display1 is connected to LDB 1 using address 0.
     *
     * SC_R_DC_0    SC_C_PXL_LINK_MST1_ADDR   Master 1 pixel link address
     * SC_R_DC_0    SC_C_PXL_LINK_MST1_ENB    Master 1 pixel link enable
     * SC_R_DC_0    SC_C_PXL_LINK_MST1_VLD    Master 1 pixel link valid
     * SC_R_DC_0    SC_C_PXL_LINK_MST2_ADDR   Master 2 pixel link address
     * SC_R_DC_0    SC_C_PXL_LINK_MST2_ENB    Master 2 pixel link enable
     * SC_R_DC_0    SC_C_PXL_LINK_MST2_VLD    Master 2 pixel link valid
     * SC_R_DC_0    SC_C_SYNC_CTRL0           PL sync ctrl 0
     * SC_R_DC_0    SC_C_SYNC_CTRL1           PL sync ctrl 1
     */
    uint8_t pixelLinkAddr = 0;
    uint32_t i;
    sc_err_t err = SC_ERR_NONE;

    const dpu_ldb_pl_addr_t dpuLdbPlAddrs[] = {
        {
            .dpu             = DC__IRIS_MVPL,
            .dpuDisplayIndex = 0,
            .ldb             = MIPI_DSI_LVDS_COMBO0_CSR,
            .plAddr          = 0,
        },
        {
            .dpu             = DC__IRIS_MVPL,
            .dpuDisplayIndex = 1,
            .ldb             = MIPI_DSI_LVDS_COMBO1_CSR,
            .plAddr          = 0,
        },
    };

    const sc_ctrl_t pixelLinkCtrl[][4] = {
        {
            SC_C_PXL_LINK_MST1_ADDR,
            SC_C_PXL_LINK_MST1_ENB,
            SC_C_PXL_LINK_MST1_VLD,
            SC_C_SYNC_CTRL0,
        },
        {
            SC_C_PXL_LINK_MST2_ADDR,
            SC_C_PXL_LINK_MST2_ENB,
            SC_C_PXL_LINK_MST2_VLD,
            SC_C_SYNC_CTRL1,
        },
    };

    /* Get the pixel link address. */
    for (i = 0; i < ARRAY_SIZE(dpuLdbPlAddrs); i++)
    {
        if ((dpu == dpuLdbPlAddrs[i].dpu) && (displayIndex == dpuLdbPlAddrs[i].dpuDisplayIndex) &&
            (ldb == dpuLdbPlAddrs[i].ldb))
        {
            pixelLinkAddr = dpuLdbPlAddrs[i].plAddr;
            break;
        }
    }

    if (ARRAY_SIZE(dpuLdbPlAddrs) <= i)
    {
        PRINTF("ERROR: This DPU to LDB path is not supported.\r\n");
        return kStatus_Fail;
    }

    /* 8QX uses combo PHY, configure to LVDS here. */
    err = sc_misc_set_control(ipc, MIPI_DSI_RSRC, SC_C_MODE, 1);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    err = sc_misc_set_control(ipc, MIPI_DSI_RSRC, SC_C_DUAL_MODE, 0);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    err = sc_misc_set_control(ipc, MIPI_DSI_RSRC, SC_C_PXL_LINK_SEL, 0);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    /* Set address. */
    err = sc_misc_set_control(ipc, DC_RSRC, pixelLinkCtrl[displayIndex][0], pixelLinkAddr);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    /* Pull down sync control. */
    err = sc_misc_set_control(ipc, DC_RSRC, pixelLinkCtrl[displayIndex][3], 0);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    /* Enable pixel link. */
    err = sc_misc_set_control(ipc, DC_RSRC, pixelLinkCtrl[displayIndex][1], 1);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    /* Delay at least 3 pixel clock. */
    for (volatile uint32_t i = 0; i < 0x100000; i++)
    {
    }

    /* Valid pixel link. */
    err = sc_misc_set_control(ipc, DC_RSRC, pixelLinkCtrl[displayIndex][2], 1);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    /* Pull up sync control. */
    err = sc_misc_set_control(ipc, DC_RSRC, pixelLinkCtrl[displayIndex][3], 1);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    return kStatus_Success;
}

#endif /* DPU_EXAMPLE_DI */

void APP_InitPixelLink(void)
{
    sc_ipc_t ipc;

    ipc = SystemGetScfwIpcHandle();

#if (DPU_EXAMPLE_DI == DPU_DI_MIPI)
    SOC_SetDpuMipiDsiPixelLink(ipc, APP_DPU, APP_DPU_DISPLAY_INDEX, APP_MIPI_DSI);
#elif (DPU_EXAMPLE_DI == DPU_DI_LVDS)
    SOC_SetDpuLdbPixelLink(ipc, APP_DPU, APP_DPU_DISPLAY_INDEX, APP_LDB);
#endif
}

void BOARD_PrepareDisplay(void)
{
    uint32_t dpuPllClkFreq_Hz;
    uint32_t dpuDisplayClkFreq_Hz;

    sc_ipc_t ipc;
    sc_err_t err = SC_ERR_NONE;

    ipc = SystemGetScfwIpcHandle();
    /*
     * DPU clock definition
     *
     * Resource            Clock              Description
     * SC_R_DC_0           SC_PM_CLK_MISC0    Display 0 clock
     * SC_R_DC_0           SC_PM_CLK_MISC1    Display 1 clock
     * SC_R_DC_0_PLL_0     SC_PM_CLK_PLL      User programmable PLL clock
     * SC_R_DC_0_PLL_1     SC_PM_CLK_PLL      User programmable PLL clock
     * SC_R_DC_0_VIDEO0    SC_PM_CLK_MISC     Bypass 0 clock
     * SC_R_DC_0_VIDEO1    SC_PM_CLK_MISC     Bypass 1 clock
     */
    err = sc_pm_set_resource_power_mode(ipc, DC_RSRC, SC_PM_PW_MODE_ON);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    err = sc_pm_set_resource_power_mode(ipc, DC_PLL_RSRC, SC_PM_PW_MODE_ON);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    /* DPU PLL. */
    dpuPllClkFreq_Hz = APP_PIXEL_CLOCK_HZ * 8;
    err              = sc_pm_set_clock_rate(ipc, DC_PLL_RSRC, SC_PM_CLK_PLL, &dpuPllClkFreq_Hz);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    err = sc_pm_clock_enable(ipc, DC_PLL_RSRC, SC_PM_CLK_PLL, true, false);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    /* DPU display clock set to the same as pixel clock. */
    dpuDisplayClkFreq_Hz = APP_PIXEL_CLOCK_HZ;
    err                  = sc_pm_set_clock_rate(ipc, DC_RSRC, DC_DISPLAY_CLOCK, &dpuDisplayClkFreq_Hz);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    err = sc_pm_clock_enable(ipc, DC_RSRC, DC_DISPLAY_CLOCK, true, false);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    /*
     * Assign the display kachuck signal to fetch unit, the relationship between
     * resource and fetch unit is:
     *
     * SC_R_DC_0_FRAC0 : fetchLayer0
     * SC_R_DC_0_VIDEO0 : fetchDecode0, fetchEco0
     * SC_R_DC_0_VIDEO1 : fetchDecode1, fetchEco1
     * SC_R_DC_0_WARP0 : fetchWarp2, fetchEco2
     *
     * The kachuck signal should be assigned according to application requirement,
     * for example, if fetchDecode0 is used by display 0 and fetchDecode1 is used by
     * display 1, then SC_R_DC_0_VIDEO0 kachucksel should be set to 0, and
     * SC_R_DC_0_VIDEO1 should be set to 1. In the driver example, only one display
     * stream is used, so set all resource to this display stream.
     */
    err = sc_misc_set_control(ipc, SC_R_DC_0_VIDEO0, SC_C_KACHUNK_SEL, APP_DPU_DISPLAY_INDEX);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    err = sc_misc_set_control(ipc, SC_R_DC_0_VIDEO1, SC_C_KACHUNK_SEL, APP_DPU_DISPLAY_INDEX);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    err = sc_misc_set_control(ipc, SC_R_DC_0_FRAC0, SC_C_KACHUNK_SEL, APP_DPU_DISPLAY_INDEX);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    err = sc_misc_set_control(ipc, SC_R_DC_0_WARP, SC_C_KACHUNK_SEL, APP_DPU_DISPLAY_INDEX);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

#if (DPU_EXAMPLE_DI == DPU_DI_MIPI)

    /* Power up MIPI DSI subsystem. */
    err = sc_pm_set_resource_power_mode(ipc, MIPI_DSI_RSRC, SC_PM_PW_MODE_ON);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    /*
     * MIPI clock setting.
     * MIPI DSI clock definition:
     * SC_PM_CLK_BYPASS    Bypass clock
     * SC_PM_CLK_MST_BUS   DSI tx escape clock
     * SC_PM_CLK_PER       DPI (pixel) clock
     * SC_PM_CLK_SLV_BUS   DSI rx escape clock
     * SC_R_MIPI           SC_PM_CLK_PHY      DPHY PLL ref
     */
    err = sc_pm_clock_enable(ipc, MIPI_DSI_RSRC, SC_PM_CLK_PHY, true, false);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    /* The DPI clock sources from the bypass clock, for simple, set them to the same rate. */
    mipiDsiDpiClkFreq_Hz = dpuDisplayClkFreq_Hz;
    err                  = sc_pm_set_clock_rate(ipc, MIPI_DSI_RSRC, SC_PM_CLK_BYPASS, &mipiDsiDpiClkFreq_Hz);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }
    err = sc_pm_clock_enable(ipc, MIPI_DSI_RSRC, SC_PM_CLK_BYPASS, true, false);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    err = sc_pm_set_clock_parent(ipc, MIPI_DSI_RSRC, SC_PM_CLK_PER, SC_PM_PARENT_BYPS);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    mipiDsiDpiClkFreq_Hz = dpuDisplayClkFreq_Hz;
    err                  = sc_pm_set_clock_rate(ipc, MIPI_DSI_RSRC, SC_PM_CLK_PER, &mipiDsiDpiClkFreq_Hz);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }
    /* DPI clock (pixel clock), max value is 300MHz. */
    err = sc_pm_clock_enable(ipc, MIPI_DSI_RSRC, SC_PM_CLK_PER, true, false);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    /* tx_esc clock, max value is 20MHz. */
    err = sc_pm_set_clock_parent(ipc, MIPI_DSI_RSRC, SC_PM_CLK_MST_BUS, SC_PM_PARENT_XTAL);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }
    mipiDsiTxEscClkFreq_Hz = 20000000;
    err                    = sc_pm_clock_enable(ipc, MIPI_DSI_RSRC, SC_PM_CLK_MST_BUS, true, false);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    /* rx_esc resample clock, max value is 60MHz. */
    err = sc_pm_set_clock_parent(ipc, MIPI_DSI_RSRC, SC_PM_CLK_SLV_BUS, SC_PM_PARENT_XTAL);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }
    mipiDsiRxEscClkFreq_Hz = 60000000;
    err                    = sc_pm_clock_enable(ipc, MIPI_DSI_RSRC, SC_PM_CLK_SLV_BUS, true, false);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    /* DPHY reference clock is enabled by default, 27HMz. */
    mipiDsiDphyRefClkFreq_Hz = 27000000U;

    /*
     * DPHY bit clock, max value 1.05GHz.
     *
     * If external convertor such as ADV7535 is used, the MIPI DSI works in
     * non-burst-with-sync-pulse mode, in this mode the DPHY clock should be
     * matched with the pixel clock. When ppb is 24, the DPHY bit clock
     * frequency is (pixel clock * 24 / data lane used).
     *
     * If external convertor is not used, the MIPI DSI works in burst mode,
     * in this mode, the DPHY clock should be quick enough to send out pixels
     * in time.
     */

#if APP_DISPLAY_EXTERNAL_CONVERTOR
    mipiDsiDphyBitClkFreq_Hz = mipiDsiDpiClkFreq_Hz * (24 / APP_MIPI_DSI_LANE_NUM);
#else
    mipiDsiDphyBitClkFreq_Hz = 891000000;
#endif

#elif (DPU_EXAMPLE_DI == DPU_DI_LVDS)

    /* Combo PHY, power up MIPI DSI subsystem. */
    err = sc_pm_set_resource_power_mode(ipc, MIPI_DSI_RSRC, SC_PM_PW_MODE_ON);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    /* Power up LVDS subsystem. */
    err = sc_pm_set_resource_power_mode(ipc, LDB_RSRC, SC_PM_PW_MODE_ON);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    /*
     * LVDS clock setting.
     * SC_PM_CLK_BYPASS    Bypass
     * SC_PM_CLK_PER       Pixel
     * SC_PM_CLK_PHY       Phy
     */
    displayPixelClkFreq_Hz = dpuDisplayClkFreq_Hz;

    err = sc_pm_set_clock_rate(ipc, LDB_RSRC, SC_PM_CLK_BYPASS, &displayPixelClkFreq_Hz);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    err = sc_pm_clock_enable(ipc, LDB_RSRC, SC_PM_CLK_BYPASS, true, false);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    err = sc_pm_set_clock_rate(ipc, LDB_RSRC, SC_PM_CLK_PER, &displayPixelClkFreq_Hz);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    err = sc_pm_clock_enable(ipc, LDB_RSRC, SC_PM_CLK_PER, true, false);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    err = sc_pm_set_clock_rate(ipc, LDB_RSRC, SC_PM_CLK_PHY, &displayPixelClkFreq_Hz);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

    err = sc_pm_clock_enable(ipc, LDB_RSRC, SC_PM_CLK_PHY, true, false);
    if (SC_ERR_NONE != err)
    {
        assert(false);
    }

#endif
    SOC_InitDpuInterrupt();
}

void BOARD_InitLcdPanel(void)
{
#if (DPU_EXAMPLE_DI == DPU_DI_MIPI)

#if !APP_DISPLAY_EXTERNAL_CONVERTOR
    const display_config_t displayConfig = {
        .resolution   = FSL_VIDEO_RESOLUTION(APP_PANEL_WIDTH, APP_PANEL_HEIGHT),
        .hsw          = APP_HSW,
        .hfp          = APP_HFP,
        .hbp          = APP_HBP,
        .vsw          = APP_VSW,
        .vfp          = APP_VFP,
        .vbp          = APP_VBP,
        .controlFlags = 0,
        .dsiLanes     = APP_MIPI_DSI_LANE_NUM,
    };

    /* Init the resource for RM67191. */
    BOARD_InitExpansionIO();

    if (kStatus_Success != RM67191_Init(&rm67191Handle, &displayConfig))
    {
        PRINTF("Error: Failed to init the LCD panel\r\n");
    }

    return;
#else
    static adv7535_resource_t adv7535Resource;

    static display_handle_t handle = {
        .resource = &adv7535Resource,
        .ops      = &adv7535_ops,
    };

    const display_config_t displayConfig = {
        .resolution   = FSL_VIDEO_RESOLUTION(APP_PANEL_WIDTH, APP_PANEL_HEIGHT),
        .hsw          = APP_HSW,
        .hfp          = APP_HFP,
        .hbp          = APP_HBP,
        .vsw          = APP_VSW,
        .vfp          = APP_VFP,
        .vbp          = APP_VBP,
        .controlFlags = 0,
        .dsiLanes     = APP_MIPI_DSI_LANE_NUM,
    };

    /* Init the resource. */
    BOARD_Display_I2C_Init();
    adv7535Resource.i2cAddr        = 0x3D;
    adv7535Resource.i2cSendFunc    = BOARD_Display_I2C_Send;
    adv7535Resource.i2cReceiveFunc = BOARD_Display_I2C_Receive;

    ADV7535_Init(&handle, &displayConfig);
#endif

#elif (DPU_EXAMPLE_DI == DPU_DI_LVDS)
    display_config_t displayConfig = {
        .resolution    = FSL_VIDEO_RESOLUTION(APP_PANEL_WIDTH, APP_PANEL_HEIGHT),
        .hsw           = APP_HSW,
        .hfp           = APP_HFP,
        .hbp           = APP_HBP,
        .vsw           = APP_VSW,
        .vfp           = APP_VFP,
        .vbp           = APP_VBP,
        .controlFlags  = 0,
        .pixelClock_Hz = displayPixelClkFreq_Hz,
    };

    /* Init the resource for IT6263. */
    BOARD_Display_I2C_Init();
    BOARD_InitExpansionIO();

    if (kStatus_Success != IT6263_Init(&it6263Handle, &displayConfig))
    {
        PRINTF("Error: Failed to init the LCD panel\r\n");
    }

    IT6263_Start(&it6263Handle);

    return;
#endif /* DPU_EXAMPLE_DI */
}

#if (DPU_EXAMPLE_DI == DPU_DI_MIPI)
void SOC_ResetMipiDsi(MIPI_DSI_HOST_Type *base, mipi_dsi_part_t part, uint32_t reset)
{
    sc_ipc_t ipc;
    sc_err_t err = SC_ERR_NONE;

    sc_ctrl_t ctrls[] = {SC_C_DPI_RESET, SC_C_MIPI_RESET, SC_C_PHY_RESET};

    ipc = SystemGetScfwIpcHandle();

    err = sc_misc_set_control(ipc, MIPI_DSI_RSRC, ctrls[part], reset);

    if (SC_ERR_NONE != err)
    {
        assert(false);
    }
}
#endif /* DPU_EXAMPLE_DI */
