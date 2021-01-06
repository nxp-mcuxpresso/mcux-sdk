/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_lpadc.h"
#include "fsl_lpi2c.h"
#include "fsl_lpit.h"
#include "fsl_pf1550.h"
#include "fsl_pf1550_charger.h"
#include "fsl_iomuxc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_PF1550_INTB_GPIO         GPIOB
#define DEMO_PF1550_INTB_PORT         PORTB
#define DEMO_PF1550_INTB_PIN          (11U)
#define DEMO_PF1550_INTB_HANDLER      PCTLB_IRQHandler
#define DEMO_PF1550_PORT_IRQ          PCTLB_IRQn
#define DEMO_PF1550_EWM_OUT_B_GPIO    GPIOA
#define DEMO_PF1550_EWM_OUT_B_PIN     (22U)
#define DEMO_BATT_ADC_EN_GPIO         GPIOA
#define DEMO_BATT_ADC_EN_PIN          (12U)
#define DEMO_LPADC_BASE               ADC0
#define DEMO_PF1550_LPI2C             LPI2C3
#define DEMO_PF1550_LPI2C_CLKSRC_FREQ CLOCK_GetIpFreq(kCLOCK_Lpi2c3)
#define DEMO_PF1550_LPI2C_BAUDRATE    (100000U)
#define LPIT_SOURCECLOCK              CLOCK_GetIpFreq(kCLOCK_Lpit0)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static status_t I2C_SendFunc(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
static status_t I2C_ReceiveFunc(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);

/*******************************************************************************
 * Variables
 ******************************************************************************/
static pf1550_handle_t pf1550Handle;
static lpi2c_master_handle_t lpi2cHandle;
static volatile bool pf1550IntFlag;
static volatile bool lpi2cIntFlag;
static volatile bool lpitIntFlag;
static uint8_t buffer[256U];

/*******************************************************************************
 * Code
 ******************************************************************************/

/*! @brief PF1550 INTB Pad ISR function */
void DEMO_PF1550_INTB_HANDLER(void)
{
    /* Disable level-triggered PF1550 INTB Pad Interrupt here.
       The interrupt will be enabled once current events have
       been solved in the main loop. */
    PORT_SetPinInterruptConfig(DEMO_PF1550_INTB_PORT, DEMO_PF1550_INTB_PIN, kPORT_InterruptOrDMADisabled);
    /* Inform main loop PF1550 INTB Pad Interrupt is asserted. */
    pf1550IntFlag = true;
    __DSB();
}

static void lpi2c_master_callback(LPI2C_Type *base, lpi2c_master_handle_t *handle, status_t status, void *userData)
{
    /* Signal transfer success when received success status. */
    if (status == kStatus_Success)
    {
        lpi2cIntFlag = true;
    }
}

void LPIT0_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    LPIT_ClearStatusFlags(LPIT0, kLPIT_Channel0TimerFlag);
    lpitIntFlag = true;
    SDK_ISR_EXIT_BARRIER;
}

static uint32_t DEMO_GetDemoToRun(void)
{
    uint8_t demoSel;

    PRINTF("\r\n-------------- PF1550 on board PMIC driver example --------------\r\n");
    PRINTF("\r\nPlease select the PMIC example you want to run:\r\n");
    PRINTF("[1]. Setting Regulator Output Voltage\r\n");
    PRINTF("[2]. Dumping Regulator Output Voltage\r\n");
    PRINTF("[3]. Dumping Selected Register Content\r\n");
    PRINTF("[4]. Charge Li-on Battery\r\n");

    while (1)
    {
        demoSel = GETCHAR();
        if ((demoSel >= '1') && (demoSel <= '4'))
        {
            break;
        }
    }

    return demoSel;
}

static uint32_t DEMO_GetInputNumWithEcho(uint32_t length, bool allowZero)
{
    uint8_t ch;
    uint8_t digBuffer[10U] = {0U};
    uint8_t i, j;
    uint8_t digCount = 0U;
    uint32_t temp1 = 0U, temp2 = 0U;
    uint32_t result  = 0U;
    bool getFirstDig = false;

    assert(length <= (sizeof(digBuffer) / sizeof(digBuffer[0U])));

    /* Get user input and echo it back to terminal. */
    for (;;)
    {
        ch = GETCHAR();
        if ((('0' <= ch) && ('9' >= ch)) && (digCount < length))
        {
            if (false == getFirstDig)
            {
                if (allowZero || (('0' < ch) && ('9' >= ch)))
                {
                    getFirstDig = true;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                if ('0' == digBuffer[0U])
                {
                    continue;
                }
            }
            PUTCHAR(ch);
            digBuffer[digCount] = ch;
            digCount++;
        }
        else if ((0x7FU == ch) && (0U != digCount))
        {
            digBuffer[digCount] = 0x0U;
            digCount--;
            PUTCHAR(0x7FU);
        }
        else
        {
            if ('\r' == ch)
            {
                break;
            }
        }
    }

    /* Reconstruct user input number. */
    temp1 = digCount - 1;
    for (i = 0; i < digCount; i++)
    {
        temp2 = digBuffer[i] - '0';
        for (j = 0U; j < temp1; j++)
        {
            temp2 *= 10U;
        }
        temp1--;
        result += temp2;
    }

    return result;
}

static void DEMO_SetRegulatorOutput(void)
{
    uint8_t regulatorSel;
    uint32_t outputVoltage = 0;
    pf1550_module_t module = kPF1550_ModuleSwitch1;

    for (;;)
    {
        PRINTF("\f");
        PRINTF("\r\n-------------- Setting Regulator Output Voltage  --------------\r\n");
        PRINTF("Please select which regulator to set:\r\n");
        PRINTF("[a]. Buck Switch 1\r\n");
        PRINTF("[b]. Buck Switch 2\r\n");
        PRINTF("[c]. Buck Switch 3\r\n");
        PRINTF("[d]. LDO 1\r\n");
        PRINTF("[e]. LDO 2\r\n");
        PRINTF("[f]. LDO 3\r\n");
        PRINTF("[g]. Back to Home Page\r\n");

        for (;;)
        {
            regulatorSel = GETCHAR();
            if ((regulatorSel >= 'a') && (regulatorSel <= 'g'))
            {
                break;
            }
        }

        if ('g' != regulatorSel)
        {
            switch (regulatorSel)
            {
                case 'a':
                    if (PF1550_IsRegulatorSupportDvs(&pf1550Handle, kPF1550_ModuleSwitch1))
                    {
                        module = kPF1550_ModuleSwitch1;
                    }
                    else
                    {
                        PRINTF("\f");
                        PRINTF("%s does not support DVS!!!\r\n", "Switch1");
                        PRINTF("Press Any Key to Continue...\r\n");
                        GETCHAR();
                        PRINTF("\f");
                        continue;
                    }
                    break;

                case 'b':
                    if (PF1550_IsRegulatorSupportDvs(&pf1550Handle, kPF1550_ModuleSwitch2))
                    {
                        module = kPF1550_ModuleSwitch2;
                    }
                    else
                    {
                        PRINTF("\f");
                        PRINTF("%s does not support DVS!!!\r\n", "Switch2");
                        PRINTF("Press Any Key to Continue...\r\n");
                        GETCHAR();
                        PRINTF("\f");
                        continue;
                    }
                    break;

                case 'c':
                    PRINTF("\f");
                    PRINTF("%s does not support DVS!!!\r\n", "Switch3");
                    PRINTF("Press Any Key to Continue...\r\n");
                    GETCHAR();
                    PRINTF("\f");
                    continue;

                case 'd':
                    module = kPF1550_ModuleLdo1;
                    break;

                case 'e':
                    module = kPF1550_ModuleLdo2;
                    break;

                case 'f':
                    module = kPF1550_ModuleLdo3;
                    break;
            }

            PRINTF("\f");
            PRINTF("Please input the regulator output(mV):");
            outputVoltage = DEMO_GetInputNumWithEcho(4U, false);
            PRINTF("\r\n");

            PRINTF("User desired regulator output:%dmV\r\n", outputVoltage);
            PRINTF("Please confirm the desired output will not damage to the hardware!!!\r\n");
            PRINTF("Press any key to update regulator output...\r\n");
            GETCHAR();

            /* Convert user input unit to uV. */
            outputVoltage *= 1000U;
        }
        else
        {
            break;
        }

        PF1550_SetRegulatorOutputVoltage(&pf1550Handle, module, PF1550_GetOperatingStatus(&pf1550Handle),
                                         outputVoltage);
        outputVoltage =
            PF1550_GetRegulatorOutputVoltage(&pf1550Handle, module, PF1550_GetOperatingStatus(&pf1550Handle));

        /* Convert actual output unit to mV. */
        outputVoltage /= 1000U;
        PRINTF("Actual Regulator Output:%dmV\r\n", outputVoltage);
        PRINTF("Press Any Key to Continue...\r\n");
        GETCHAR();
        PRINTF("\f");
    }
}

static void DEMO_PrintRegulatorInfo(const char *regulatorName, pf1550_module_t module)
{
    pf1550_operating_status_t status;

    PRINTF("[Name:%s]", regulatorName);
    status = PF1550_GetOperatingStatus(&pf1550Handle);
    switch (status)
    {
        case kPF1550_OperatingStatusCoreOff:
            PRINTF("[Status:CoreOff]");
            break;

        case kPF1550_OperatingStatusShipMode:
            PRINTF("[Status:ShipMode]");
            break;

        case kPF1550_OperatingStatusRegsDisable:
            PRINTF("[Status:RegsDisable]");
            break;

        case kPF1550_OperatingStatusRun:
            PRINTF("[Status:Run]");
            break;

        case kPF1550_OperatingStatusStandby:
            PRINTF("[Status:Standby]");
            break;

        case kPF1550_OperatingStatusSleep:
            PRINTF("[Status:Sleep]");
            break;

        default:
            break;
    }

    PRINTF("[Enable:%s][Voltage:%dmV]\r\n", PF1550_IsRegulatorEnabled(&pf1550Handle, module, status) ? "Yes" : "No",
           PF1550_GetRegulatorOutputVoltage(&pf1550Handle, module, status) / 1000U);
}

static void DEMO_DumpRegulatorOutput(void)
{
    /* Scroll to a new page. */
    PRINTF("\f");
    PRINTF("\r\n-------------- Dumping PF1550 Regulator Output --------------\r\n");
    PRINTF("All the Regulator Output Parameters are listed here:\r\r\n\n");

    /* Print All Regulator Output Voltages. */
    DEMO_PrintRegulatorInfo("Switch1", kPF1550_ModuleSwitch1);
    DEMO_PrintRegulatorInfo("Switch2", kPF1550_ModuleSwitch2);
    DEMO_PrintRegulatorInfo("Switch3", kPF1550_ModuleSwitch3);
    DEMO_PrintRegulatorInfo(" LDO1  ", kPF1550_ModuleLdo1);
    DEMO_PrintRegulatorInfo(" LDO2  ", kPF1550_ModuleLdo2);
    DEMO_PrintRegulatorInfo(" LDO3  ", kPF1550_ModuleLdo3);
    DEMO_PrintRegulatorInfo(" Vsnvs ", kPF1550_ModuleVsnvs);
    PRINTF("\r\n");
}

static void DEMO_DumpRegisterContent(void)
{
    uint32_t address;
    uint8_t number;
    uint8_t i;

    for (;;)
    {
        /* Scroll to a new page. */
        PRINTF("\f");
        PRINTF("\r\n-------------- Dumping PF1550 Register Content --------------\r\n\r\n");
        PRINTF("Please select the first address to dump(0~255):");
        address = DEMO_GetInputNumWithEcho(3U, true);
        if (255U >= address)
        {
            break;
        }
    }
    PRINTF("\r\n");

    for (;;)
    {
        /* Scroll to a new page. */
        PRINTF("\f");
        PRINTF("Please select the number of registers to dump(1~256):");
        number = DEMO_GetInputNumWithEcho(3U, false);
        if ((256U > (address + number)) && (0U != number))
        {
            break;
        }
    }
    PRINTF("\r\n");

    /* Read register from PF1550 */
    PF1550_DumpReg(&pf1550Handle, address, buffer, number);

    PRINTF("\r\nDump Format: [Register Address] = Register Content:\r\n");
    for (i = 0; i < number; i++)
    {
        PRINTF("[0x%x] = 0x%x\r\n", address + i, buffer[i]);
    }
    PRINTF("\r\n");
}

static void DEMO_PrintChargerStatus(void)
{
    uint32_t status;

    status = PF1550_GetChargerStatus(&pf1550Handle);

    /* Vbus status check. */
    if (status & kPF1550_ChargerStatusVbusUvlo)
    {
        PRINTF("[VBUS]VBUS deattached!\r\n");
    }
    if (status & kPF1550_ChargerStatusVbusIn2Sys)
    {
        PRINTF("[VBUS]VBUS_IN2SYS_SNS!\r\n");
    }
    if (status & kPF1550_ChargerStatusVbusOvlo)
    {
        PRINTF("[VBUS]VBUS_OVLO_SNS!\r\n");
    }
    if (status & kPF1550_ChargerStatusVbusValid)
    {
        PRINTF("[VBUS]VBUS attached!\r\n");
    }
    if (status & kPF1550_ChargerStatusVbusDpm)
    {
        PRINTF("[VBUS]VBUS DPM triggered!\r\n");
    }
    if (status & kPF1550_ChargerStatusWdogTimeout)
    {
        PRINTF("[WDOG]WDOG expired!\r\n");
    }
    if (status & kPF1550_ChargerStatusThm)
    {
        PRINTF("[THM]Thermistor temperature is < Cool, or > Warm threshold!\r\n");
    }
    if (status & kPF1550_ChargerStatusTreg)
    {
        PRINTF("[THM]Junction temperature greater than threshold!\r\n");
    }
    if (status & kPF1550_ChargerStatusBattOc)
    {
        PRINTF("[BAT]VBATT to VSYS overcurrent fault!\r\n");
    }

    switch (status & kPF1550_ChargerStatusChargerMode)
    {
        case kPF1550_ChargerModePreChg:
            PRINTF("[CHG]Pre-Charge!\r\n");
            break;

        case kPF1550_ChargerModeFastChgCc:
            PRINTF("[CHG]Fast Charge CC!\r\n");
            break;

        case kPF1550_ChargerModeFastChgCv:
            PRINTF("[CHG]Fast Charge CV!\r\n");
            break;

        case kPF1550_ChargerModeEndOfChg:
            PRINTF("[CHG]End Of Charge!\r\n");
            break;

        case kPF1550_ChargerModeDone:
            PRINTF("[CHG]Done!\r\n");
            break;

        case kPF1550_ChargerModeTimerFault:
            PRINTF("[CHG]Timer Fault!\r\n");
            break;

        case kPF1550_ChargerModeThermSuspend:
            PRINTF("[CHG]Thermistor Suspend!\r\n");
            break;

        case kPF1550_ChargerModeOffOt:
            PRINTF("[CHG]Charger Off with junction temperature overflow!\r\n");
            break;

        case kPF1550_ChargerModeOffLinearOn:
            PRINTF("[CHG]Charger block is in Linear only mode, not charging!\r\n");
            break;

        default:
            break;
    }

    /* Vbus status check. */
    switch (status & kPF1550_ChargerStatusBattMode)
    {
        case kPF1550_BattModeNoValidVbus:
            PRINTF("[BAT]No valid VBUS input!\r\n");
            break;

        case kPF1550_BattModeVbattLessThanVpre:
            PRINTF("[BAT]VBATT < VPRECHG.LB!\r\n");
            break;

        case kPF1550_BattModeTimerFault:
            PRINTF("[BAT]Charger is in timer fault mode!\r\n");
            break;

        case kPF1550_BattModeVbattGreaterThanVpre:
            PRINTF("[BAT]VPRECHG.LB < VBATT!< VBATT!\r\n");
            break;

        case kPF1550_BattModeOv:
            PRINTF("[BAT]battery overvoltage!\r\n");
            break;

        case kPF1550_BattModeNoBatt:
            PRINTF("Battery not detected!\r\n");
            break;

        default:
            break;
    }
}

static void DEMO_Charger(void)
{
    /* Structure of initialize LPIT */
    lpit_config_t lpitConfig;
    lpit_chnl_params_t lpitChannelConfig;

    lpadc_config_t mLpadcConfigStruct;
    lpadc_conv_trigger_config_t mLpadcTriggerConfigStruct;
    lpadc_conv_command_config_t mLpadcCommandConfigStruct;
    lpadc_conv_result_t mLpadcResultConfigStruct;

    const pf1550_charger_attribute_t chargerAttribute = {
        .fastChargeCurrent_mA           = 1000U,
        .fastChargeVoltage_uV           = 4200000U,
        .preChargeTime_min              = 45U,
        .fastChargeTime_hr              = 6U,
        .endOfChargeTime_min            = 40U,
        .endOfChargeCurrentThreshold_mA = 50U,
        .restartVoltageThreshold_uV     = 150000U,
        .miniSystemVoltage_uV           = 3500000U,
    };
    const pf1550_batFET_attribute_t batFetAttribute = {
        .overcurrentThreshold_mA        = 2200U,
        .overcurrentProtectEnable       = true,
        .overcurrentProtectEnableNoVbus = true,
        .overvoltageFaultProtectEnable  = true,
        .watchDogFaultProtectEnable     = true,
        .thermalFaultProtectEnable      = true,
        .thermalShutdownProtectEnable   = true,
        .timerFaultProtectEnable        = true,
    };
    const pf1550_power_path_attribute_t powerPathAttribute = {
        .vbusCurrentLimit_mA     = 1000U,
        .vbusDpmVoltage_uV       = 4600000U,
        .vbusDpmStopThreshold_uV = 250000U,
        .vbusOvDebounce_us       = 100U,
        .vbus2vsysDebounce_us    = 100U,
        .vbus2vsysThreashold_uV  = 50000U,
        .usbPhyVoltage_uV        = 3300000U,
        .vsysWakeupDelay_ms      = 16U,
        .usbPhyDischargerEnbale  = false,
        .usbPhyLdoEnable         = false,
    };
    const pf1550_thermal_attribute_t thermalAttribute = {
        .mode                      = kPF1550_ThermalMode_2,
        .junctionThermalSetPoint_C = 80U,
        .thermalColdThreshold_C    = 0U,
        .thermalCoolThreshold_C    = 15U,
        .thermalWarmThreshold_C    = 45U,
        .thermalHotThreshold_C     = 55U,
        .thermalVoltageAdjust_uV   = 200000U,
        .thermalCurrentAdjust_pct  = 50U,
        .thermalFoldbackEnable     = true,
    };
    const pf1550_led_attribute_t ledAttribute = {
        .mode             = kPF1550_LedMode_1,
        .pwmDuty_pct      = 50U,
        .pwmFrequency_mHz = 1000U,
        .rampEnable       = false,
        .swCtrlEnable     = false,
    };
    uint32_t category;
    uint32_t status;

    PF1550_ServiceChargerWdog(&pf1550Handle);
    PF1550_SetChargerWdog(&pf1550Handle, 0U, false);
    PF1550_SetChargerOperation(&pf1550Handle, kPF1550_ChargerOperation_ChargerOffLinearOn);

    PF1550_SetChargerAttibute(&pf1550Handle, &chargerAttribute);
    PF1550_SetBatFETAttibute(&pf1550Handle, &batFetAttribute);
    PF1550_EnableBatFET(&pf1550Handle, true);
    PF1550_SetPowerPathAttibute(&pf1550Handle, &powerPathAttribute);
    PF1550_SetThermalAttibute(&pf1550Handle, &thermalAttribute);
    PF1550_SetLedAttibute(&pf1550Handle, &ledAttribute);
    PF1550_SetledOutput(&pf1550Handle, true);

    PF1550_ClearInterruptStatus(&pf1550Handle, kPF1550_IntCategoryCharger, 0xFF);
    PF1550_ClearInterruptStatus(&pf1550Handle, kPF1550_IntCategorySwitch, 0xFF);
    PF1550_ClearInterruptStatus(&pf1550Handle, kPF1550_IntCategoryLdo, 0xFF);
    PF1550_ClearInterruptStatus(&pf1550Handle, kPF1550_IntCategoryOnkey, 0xFF);
    PF1550_ClearInterruptStatus(&pf1550Handle, kPF1550_IntCategoryTemp, 0xFF);
    PF1550_ClearInterruptStatus(&pf1550Handle, kPF1550_IntCategoryMisc, 0xFF);
    pf1550IntFlag = false;

    PF1550_EnableInterrupts(&pf1550Handle, kPF1550_IntCategoryCharger,
                            kPF1550_IntSrcChargerBatt2SysOc | kPF1550_IntSrcChargerBatt | kPF1550_IntSrcChargerChg |
                                kPF1550_IntSrcChargerVbus | kPF1550_IntSrcChargerThm);
    PORT_ClearPinsInterruptFlags(DEMO_PF1550_INTB_PORT, 1U << DEMO_PF1550_INTB_PIN);
    PORT_SetPinInterruptConfig(DEMO_PF1550_INTB_PORT, DEMO_PF1550_INTB_PIN, kPORT_InterruptLogicZero);
    EnableIRQ(DEMO_PF1550_PORT_IRQ);
    PF1550_SetChargerOperation(&pf1550Handle, kPF1550_ChargerOperation_ChargerOnLinearOn);

    /*
     * lpitConfig.enableRunInDebug = false;
     * lpitConfig.enableRunInDoze = false;
     */
    LPIT_GetDefaultConfig(&lpitConfig);

    /* Init lpit module */
    LPIT_Init(LPIT0, &lpitConfig);

    lpitChannelConfig.chainChannel          = false;
    lpitChannelConfig.enableReloadOnTrigger = false;
    lpitChannelConfig.enableStartOnTrigger  = false;
    lpitChannelConfig.enableStopOnTimeout   = false;
    lpitChannelConfig.timerMode             = kLPIT_PeriodicCounter;
    /* Set default values for the trigger source */
    lpitChannelConfig.triggerSelect = kLPIT_Trigger_TimerChn0;
    lpitChannelConfig.triggerSource = kLPIT_TriggerSource_External;

    /* Init lpit channel 0 */
    LPIT_SetupChannel(LPIT0, kLPIT_Chnl_0, &lpitChannelConfig);

    /* Set timer period for channel 0 */
    LPIT_SetTimerPeriod(LPIT0, kLPIT_Chnl_0, USEC_TO_COUNT(1000000U, LPIT_SOURCECLOCK));

    /* Enable timer interrupts for channel 0 */
    LPIT_EnableInterrupts(LPIT0, kLPIT_Channel0TimerInterruptEnable);

    /* Enable at the NVIC */
    EnableIRQ(LPIT0_IRQn);

    PRINTF("\f");
    PRINTF("\r\n-------------- Charge Battery Pack --------------\r\n\r\n");

    /* Start channel 0 */
    LPIT_StartTimer(LPIT0, kLPIT_Chnl_0);

    for (;;)
    {
        if (pf1550IntFlag)
        {
            category = PF1550_GetInterruptCategory(&pf1550Handle);
            if (category & kPF1550_IntCategoryCharger)
            {
                /* Process Charger event here. */
                status = PF1550_GetInterruptStatus(&pf1550Handle, kPF1550_IntCategoryCharger);
                PRINTF("[PF1550 CHG INT]:0x%x\r\n", status);
                PF1550_ClearInterruptStatus(&pf1550Handle, kPF1550_IntCategoryCharger, status);
                PORT_ClearPinsInterruptFlags(DEMO_PF1550_INTB_PORT, 1U << DEMO_PF1550_INTB_PIN);
                DEMO_PrintChargerStatus();
            }

            pf1550IntFlag = false;
            PORT_SetPinInterruptConfig(DEMO_PF1550_INTB_PORT, DEMO_PF1550_INTB_PIN, kPORT_InterruptLogicZero);
        }
        if (lpitIntFlag)
        {
            lpitIntFlag = false;

            GPIO_PinWrite(DEMO_BATT_ADC_EN_GPIO, DEMO_BATT_ADC_EN_PIN, 1U);

            LPADC_GetDefaultConfig(&mLpadcConfigStruct);
            mLpadcConfigStruct.enableAnalogPreliminary = true;
            LPADC_Init(DEMO_LPADC_BASE, &mLpadcConfigStruct);

            /* Set conversion CMD configuration. */
            LPADC_GetDefaultConvCommandConfig(&mLpadcCommandConfigStruct);
            mLpadcCommandConfigStruct.channelNumber   = 10; /* Take channel8A as ADC input.  */
            mLpadcCommandConfigStruct.sampleScaleMode = kLPADC_SamplePartScale;
            LPADC_SetConvCommandConfig(DEMO_LPADC_BASE, 15U,
                                       &mLpadcCommandConfigStruct); /* Configurate the CMD15 buffer. */

            /* Set trigger configuration. */
            LPADC_GetDefaultConvTriggerConfig(&mLpadcTriggerConfigStruct);
            mLpadcTriggerConfigStruct.targetCommandId       = 15U; /* CMD15 is executed. */
            mLpadcTriggerConfigStruct.enableHardwareTrigger = false;
            LPADC_SetConvTriggerConfig(DEMO_LPADC_BASE, 0U, &mLpadcTriggerConfigStruct); /* Configurate the trigger0. */

            PRINTF("Current VBAT:");
            LPADC_DoSoftwareTrigger(DEMO_LPADC_BASE, 1U); /* 1U is trigger0 mask. */
            while (!LPADC_GetConvResult(DEMO_LPADC_BASE, &mLpadcResultConfigStruct))
            {
            }
            PRINTF("%dmV\r\n", ((((mLpadcResultConfigStruct.convValue) >> 3U) * 1800 * 64) / (4096 * 30)) * 2);

            LPADC_Deinit(DEMO_LPADC_BASE);

            GPIO_PinWrite(DEMO_BATT_ADC_EN_GPIO, DEMO_BATT_ADC_EN_PIN, 0U);
        }
    }
}

/*! @brief Main function */
int main(void)
{
    gpio_pin_config_t gpioPinConfig;
    lpi2c_master_config_t masterConfig;
    pf1550_config_t pf1550Config;
    pf1550_onkey_attribute_t pf1550OnkeyAttribute;
    uint32_t demoSelection;

    /* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    CLOCK_EnableClock(kCLOCK_PctlA);
    CLOCK_EnableClock(kCLOCK_PctlB);
    CLOCK_EnableClock(kCLOCK_Rgpio2p0);
    CLOCK_SetIpSrc(kCLOCK_Lpi2c3, kCLOCK_IpSrcSircAsync);
    CLOCK_SetIpSrc(kCLOCK_Lpit0, kCLOCK_IpSrcSircAsync);
    CLOCK_SetIpSrc(kCLOCK_Adc0, kCLOCK_IpSrcFircAsync);

    /* Init GPIO used by BATT_ADC_EN for Battery Measurement. */
    gpioPinConfig.pinDirection = kGPIO_DigitalOutput;
    gpioPinConfig.outputLogic  = 0x0U;
    GPIO_PinInit(DEMO_BATT_ADC_EN_GPIO, DEMO_BATT_ADC_EN_PIN, &gpioPinConfig);

    /* Init LPI2C used by PF1550. */
    /*
     * masterConfig.debugEnable = false;
     * masterConfig.ignoreAck = false;
     * masterConfig.pinConfig = kLPI2C_2PinOpenDrain;
     * masterConfig.baudRate_Hz = 100000U;
     * masterConfig.busIdleTimeout_ns = 0;
     * masterConfig.pinLowTimeout_ns = 0;
     * masterConfig.sdaGlitchFilterWidth_ns = 0;
     * masterConfig.sclGlitchFilterWidth_ns = 0;
     */
    LPI2C_MasterGetDefaultConfig(&masterConfig);
    masterConfig.baudRate_Hz = DEMO_PF1550_LPI2C_BAUDRATE;
    /* Initialize the LPI2C master peripheral */
    LPI2C_MasterInit(DEMO_PF1550_LPI2C, &masterConfig, DEMO_PF1550_LPI2C_CLKSRC_FREQ);
    /* Create the LPI2C handle for the non-blocking transfer */
    LPI2C_MasterTransferCreateHandle(DEMO_PF1550_LPI2C, &lpi2cHandle, lpi2c_master_callback, NULL);

    /* Init PF1550 Component. */
    PF1550_GetDefaultConfig(&pf1550Config);
    pf1550Config.I2C_SendFunc    = I2C_SendFunc;
    pf1550Config.I2C_ReceiveFunc = I2C_ReceiveFunc;
    PF1550_Init(&pf1550Handle, &pf1550Config);

    pf1550OnkeyAttribute.debounce                    = kPF1550_OnkeyDebounce_Falling31ms25Rising31ms25;
    pf1550OnkeyAttribute.enableTurnOffSystemViaOnkey = false;
    pf1550OnkeyAttribute.pushTime                    = kPF1550_OnkeyPushResetTime_16s;
    PF1550_SetOnKeyPadAttibute(&pf1550Handle, &pf1550OnkeyAttribute);

    /* Print the initial banner. */
    for (;;)
    {
        demoSelection = DEMO_GetDemoToRun();

        switch (demoSelection)
        {
            /* Setting Regulator Output Voltage: */
            case '1':
                DEMO_SetRegulatorOutput();
                break;

            /* Dumping all Regulator Output Voltage: */
            case '2':
                DEMO_DumpRegulatorOutput();
                PRINTF("Press Any Key to Home Page...");
                GETCHAR();
                break;

            /* Dumping Selected Register Content: */
            case '3':
                DEMO_DumpRegisterContent();
                PRINTF("Press Any Key to Home Page...");
                GETCHAR();
                break;

            /* Charger. */
            case '4':
                DEMO_Charger();
                PRINTF("Press Any Key to Home Page...");
                GETCHAR();
                break;

            default:
                break;
        }

        /* Scroll to a new page. */
        PRINTF("\f");
    }
}

static status_t I2C_SendFunc(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize)
{
    status_t reVal = kStatus_Fail;
    lpi2c_master_transfer_t masterXfer;

    /* Prepare transfer structure. */
    masterXfer.slaveAddress   = deviceAddress;
    masterXfer.direction      = kLPI2C_Write;
    masterXfer.subaddress     = subAddress;
    masterXfer.subaddressSize = subAddressSize;
    masterXfer.data           = (void *)txBuff;
    masterXfer.dataSize       = txBuffSize;
    masterXfer.flags          = kLPI2C_TransferDefaultFlag;

    lpi2cIntFlag = false;
    reVal        = LPI2C_MasterTransferNonBlocking(DEMO_PF1550_LPI2C, &lpi2cHandle, &masterXfer);
    if (kStatus_Success != reVal)
    {
        return reVal;
    }

    while (false == lpi2cIntFlag)
    {
    }

    return reVal;
}

static status_t I2C_ReceiveFunc(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize)
{
    status_t reVal = kStatus_Fail;
    lpi2c_master_transfer_t masterXfer;

    /* Prepare transfer structure. */
    masterXfer.slaveAddress   = deviceAddress;
    masterXfer.direction      = kLPI2C_Read;
    masterXfer.subaddress     = subAddress;
    masterXfer.subaddressSize = subAddressSize;
    masterXfer.data           = rxBuff;
    masterXfer.dataSize       = rxBuffSize;
    masterXfer.flags          = kLPI2C_TransferDefaultFlag;

    lpi2cIntFlag = false;
    reVal        = LPI2C_MasterTransferNonBlocking(DEMO_PF1550_LPI2C, &lpi2cHandle, &masterXfer);
    if (kStatus_Success != reVal)
    {
        return reVal;
    }

    while (false == lpi2cIntFlag)
    {
    }

    return reVal;
}
