/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_PORT_H_
#define _FSL_PORT_H_

#include "fsl_common.h"

/*!
 * @addtogroup port
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! Version 2.0.2. */
#define FSL_PORT_DRIVER_VERSION (MAKE_VERSION(2, 0, 2))
/*@}*/

#define PORT_MODULEPS_BITWIDTH_OFFSET  (5U) /*　The bit width offset in the module enum type . */
#define PORT_MODULEPS_BITWIDTH_MASK    (0x7U) /* The bit width mask */
#define PORT_PINSEL_REG_OFFSET (0x20000U) /* The offset to identify the modules in different pin selection register. */
#define PORT_FILTER_REG_OFFSET (0x1000000U) /* The offset to identify the filter part in different filter register. */\

/*! @brief Module or peripheral for port pin selection */
typedef enum _port_module_t {
    kPORT_NMI = SIM_SOPT0_NMIE_SHIFT,  /*!< NMI port pin select. */
    kPORT_RESET = SIM_SOPT0_RSTPE_SHIFT, /*!< RESET pin select. */
    kPORT_SWDE = SIM_SOPT0_SWDE_SHIFT,    /*!< Single wire debug port pin. */
    kPORT_IRQ = (SIM_PINSEL0_IRQPS_SHIFT | (3 << PORT_MODULEPS_BITWIDTH_OFFSET)), /*!< IRQ port pin select. */
    kPORT_RTC = (SIM_PINSEL0_RTCPS_SHIFT | (1 << PORT_MODULEPS_BITWIDTH_OFFSET)), /*!< RTC port pin select. */
    kPORT_I2C0 = (SIM_PINSEL0_I2C0PS_SHIFT | (1 << PORT_MODULEPS_BITWIDTH_OFFSET)),     /*!< I2C0 Port pin select. */
    kPORT_SPI0 = (SIM_PINSEL0_SPI0PS_SHIFT | (1 << PORT_MODULEPS_BITWIDTH_OFFSET)),     /*!< SPI0 port pin select. */
    kPORT_UART0 = (SIM_PINSEL0_UART0PS_SHIFT | (1 << PORT_MODULEPS_BITWIDTH_OFFSET)),   /*!< UART0 port pin select. */
    kPORT_FTM0CH0 = (SIM_PINSEL0_FTM0PS0_SHIFT | (1 << PORT_MODULEPS_BITWIDTH_OFFSET)), /*!< FTM0_CH0 port pin select. */
    kPORT_FTM0CH1 = (SIM_PINSEL0_FTM0PS1_SHIFT | (1 << PORT_MODULEPS_BITWIDTH_OFFSET)), /*!< FTM0_CH1 port pin select. */
    kPORT_FTM1CH0 = (SIM_PINSEL0_FTM1PS0_SHIFT | (1 << PORT_MODULEPS_BITWIDTH_OFFSET)), /*!< FTM1_CH0 port pin select. */
    kPORT_FTM1CH1 = (SIM_PINSEL0_FTM1PS1_SHIFT | (1 << PORT_MODULEPS_BITWIDTH_OFFSET)),  /*!< FTM1_CH1 port pin select. */
    kPORT_FTM0CLK = (SIM_PINSEL0_FTM0CLKPS_SHIFT | (2 << PORT_MODULEPS_BITWIDTH_OFFSET)), /*!< FTM0 Clock pin select. */
    kPORT_FTM1CLK = (SIM_PINSEL0_FTM1CLKPS_SHIFT | (2 << PORT_MODULEPS_BITWIDTH_OFFSET)), /*!< FTM1 Clock pin select. */
    kPORT_FTM2CLK = (SIM_PINSEL0_FTM2CLKPS_SHIFT | (2 << PORT_MODULEPS_BITWIDTH_OFFSET)), /*!< FTM2 Clock pin select. */
    kPORT_PWTCLK = (SIM_PINSEL0_PWTCLKPS_SHIFT | (2 << PORT_MODULEPS_BITWIDTH_OFFSET)), /*!< PWT Clock pin select. */
    kPORT_FTM2CH0 = (SIM_PINSEL1_FTM2PS0_SHIFT | (2 << PORT_MODULEPS_BITWIDTH_OFFSET) | PORT_PINSEL_REG_OFFSET), /*!< FTM2_CH0 port pin select. */
    kPORT_FTM2CH1 = (SIM_PINSEL1_FTM2PS1_SHIFT | (2 << PORT_MODULEPS_BITWIDTH_OFFSET) | PORT_PINSEL_REG_OFFSET), /*!< FTM2_CH1 port pin select. */
    kPORT_FTM2CH2 = (SIM_PINSEL1_FTM2PS2_SHIFT | (2 << PORT_MODULEPS_BITWIDTH_OFFSET) | PORT_PINSEL_REG_OFFSET), /*!< FTM2_CH2 port pin select. */
    kPORT_FTM2CH3 = (SIM_PINSEL1_FTM2PS3_SHIFT | (2 << PORT_MODULEPS_BITWIDTH_OFFSET) | PORT_PINSEL_REG_OFFSET), /*!< FTM2_CH3 port pin select. */
    kPORT_FTM2CH4 = (SIM_PINSEL1_FTM2PS4_SHIFT | (1 << PORT_MODULEPS_BITWIDTH_OFFSET) | PORT_PINSEL_REG_OFFSET), /*!< FTM2_CH4 port pin select. */
    kPORT_FTM2CH5 = (SIM_PINSEL1_FTM2PS5_SHIFT | (1 << PORT_MODULEPS_BITWIDTH_OFFSET) | PORT_PINSEL_REG_OFFSET), /*!< FTM2_CH5 port pin select. */
    kPORT_I2C1 = (SIM_PINSEL1_I2C1PS_SHIFT | (1 << PORT_MODULEPS_BITWIDTH_OFFSET) | PORT_PINSEL_REG_OFFSET), /*!< I2C1 port pin select. */
    kPORT_SPI1 = (SIM_PINSEL1_SPI1PS_SHIFT | (1 << PORT_MODULEPS_BITWIDTH_OFFSET) | PORT_PINSEL_REG_OFFSET), /*!< SPI1 port pin select. */
    kPORT_UART1 = (SIM_PINSEL1_UART1PS_SHIFT | (1 << PORT_MODULEPS_BITWIDTH_OFFSET) | PORT_PINSEL_REG_OFFSET), /*!< UART1 port pin select. */
    kPORT_UART2 = (SIM_PINSEL1_UART2PS_SHIFT | (1 << PORT_MODULEPS_BITWIDTH_OFFSET) | PORT_PINSEL_REG_OFFSET), /*!< UART2 port pin select. */
    kPORT_PWTIN0 = (SIM_PINSEL1_PWTIN0PS_SHIFT | (1 << PORT_MODULEPS_BITWIDTH_OFFSET) | PORT_PINSEL_REG_OFFSET), /*!< PWT_IN0 port pin select. */
    kPORT_PWTIN1 = (SIM_PINSEL1_PWTIN1PS_SHIFT | (1 << PORT_MODULEPS_BITWIDTH_OFFSET) | PORT_PINSEL_REG_OFFSET), /*!< PWT_IN1 port pin select. */
} port_module_t;

/*! @brief Port type */
typedef enum _port_type_t {
    kPORT_PTA = 0U, /*!< PORT PTA. */
    kPORT_PTB = 1U, /*!< PORT PTB. */
    kPORT_PTC = 2U, /*!< PORT PTC. */
    kPORT_PTD = 3U, /*!< PORT PTD. */
    kPORT_PTE = 4U, /*!< PORT PTE. */
    kPORT_PTF = 5U, /*!< PORT PTF. */
    kPORT_PTG = 6U, /*!< PORT PTG. */
    kPORT_PTH = 7U, /*!< PORT PTH. */
    kPORT_PTI = 8U  /*!< PORT PTI. */
} port_type_t;

/*! @brief Pin number, Notice this index enum has been deprecated and it will be removed in the next release. */
typedef enum _port_pin_index_t {
    kPORT_PinIdx0 = 0U, /*!< PORT PIN index 0. */
    kPORT_PinIdx1 = 1U, /*!< PORT PIN index 1. */
    kPORT_PinIdx2 = 2U, /*!< PORT PIN index 2. */
    kPORT_PinIdx3 = 3U, /*!< PORT PIN index 3. */
    kPORT_PinIdx4 = 4U, /*!< PORT PIN index 4. */
    kPORT_PinIdx5 = 5U, /*!< PORT PIN index 5. */
    kPORT_PinIdx6 = 6U, /*!< PORT PIN index 6. */
    kPORT_PinIdx7 = 7U  /*!< PORT PIN index 7. */
} port_pin_index_t;

/*! @brief Pin selection */
typedef enum _port_pin_select_t {
    kPORT_NMI_OTHERS = 0U,           /*!< PTB4/FTM2_CH4 etc function as PTB4/FTM2_CH4 etc */
    kPORT_NMI_NMIE = 1U,             /*!< PTB4/FTM2_CH4 etc function as NMI. */
    kPORT_RST_OTHERS = 0U,           /*!< PTA5/IRQ etc function as PTA5/IRQ etc. */
    kPORT_RST_RSTPE = 1U,            /*!< PTA5/IRQ etc function as REST. */
    kPORT_SWDE_OTHERS = 0U,          /*!< PTA4/ACMP0 etc function as PTA4/ACMP0 etc. */
    kPORT_SWDE_SWDE = 1U,            /*!< PTA4/ACMP0 etc function as SWD. */
    kPORT_IRQ_PTA5 = 0U,             /*!< IRQ is mapped to PTA5. */
    kPORT_IRQ_PTI0 = 1U,             /*!< IRQ is mapped to PTI0. */ 
    kPORT_IRQ_PTI1 = 2U,             /*!< IRQ is mapped to PTI1. */ 
    kPORT_IRQ_PTI2 = 3U,             /*!< IRQ is mapped to PTI2. */ 
    kPORT_IRQ_PTI3 = 4U,             /*!< IRQ is mapped to PTI3. */ 
    kPORT_IRQ_PTI4 = 5U,             /*!< IRQ is mapped to PTI4. */ 
    kPORT_IRQ_PTI5 = 6U,             /*!< IRQ is mapped to PTI5. */ 
    kPORT_IRQ_PTI6 = 7U,             /*!< IRQ is mapped to PTI6. */ 
    kPORT_RTCO_PTC4 = 0U,            /*!< RTCO is mapped to PTC4. */
    kPORT_RTCO_PTC5 = 1U,            /*!< RTCO is mapped to RTC5. */
    kPORT_I2C0_SCLPTA3_SDAPTA2 = 0U, /*!< I2C0_SCL and I2C0_SDA are mapped on PTA3 and PTA2, respectively. */
    kPORT_I2C0_SCLPTB7_SDAPTB6 = 1U, /*!< I2C0_SCL and I2C0_SDA are mapped on PTB7 and PTB6, respectively. */
    kPORT_SPI0_SCKPTB2_MOSIPTB3_MISOPTB4_PCSPTB5 = 0U, /*!< SPI0_SCK/MOSI/MISO/PCS0 are mapped on PTB2/PTB3/PTB4/PTB5.*/
    kPORT_SPI0_SCKPTE0_MOSIPTE1_MISOPTE2_PCSPTE3 =
        1U,                         /*!< SPI0_SCK/MOSI/MISO/PCS0 are mapped on PTE0/PTE1/PTE2/PTE3. */
    kPORT_UART0_RXPTB0_TXPTB1 = 0U, /*!< UART0_RX and UART0_TX are mapped on PTB0 and PTB1. */
    kPORT_UART0_RXPTA2_TXPTA3 = 1U, /*!< UART0_RX and UART0_TX are mapped on PTA2 and PTA3. */
    kPORT_FTM0_CH0_PTA0 = 0U,       /*!< FTM0_CH0 channels are mapped on PTA0. */
    kPORT_FTM0_CH0_PTB2 = 1U,       /*!< FTM0_CH0 channels are mapped on PTB2. */
    kPORT_FTM0_CH1_PTA1 = 0U,       /*!< FTM0_CH1 channels are mapped on PTA1. */
    kPORT_FTM0_CH1_PTB3 = 1U,       /*!< FTM0_CH1 channels are mapped on PTB3. */
    kPORT_FTM0CLK_TCLK0 = 0U,       /*!< FTM0 CLK using the TCLK0 pin. */
    kPORT_FTM0CLK_TCLK1 = 1U,       /*!< FTM0 CLK using the TCLK1 pin. */
    kPORT_FTM0CLK_TCLK2 = 2U,       /*!< FTM0 CLK using the TCLK2 pin. */
    kPORT_FTM1CLK_TCLK0 = 0U,       /*!< FTM1 CLK using the TCLK0 pin. */
    kPORT_FTM1CLK_TCLK1 = 1U,       /*!< FTM1 CLK using the TCLK1 pin. */
    kPORT_FTM1CLK_TCLK2 = 2U,       /*!< FTM1 CLK using the TCLK2 pin. */
    kPORT_FTM2CLK_TCLK0 = 0U,       /*!< FTM2 CLK using the TCLK0 pin. */
    kPORT_FTM2CLK_TCLK1 = 1U,       /*!< FTM2 CLK using the TCLK1 pin. */
    kPORT_FTM2CLK_TCLK2 = 2U,       /*!< FTM2 CLK using the TCLK2 pin. */
    kPORT_PWTCLK_TCLK0 = 0U,        /*!< PWT CLK using the TCLK0 pin. */
    kPORT_PWTCLK_TCLK1 = 1U,        /*!< PWT CLK using the TCLK1 pin. */
    kPORT_PWTCLK_TCLK2 = 2U,        /*!< PWT CLK using the TCLK2 pin. */
    kPORT_FTM1_CH0_PTC4 = 0U,       /*!< FTM1_CH0 channels are mapped on PTC4. */
    kPORT_FTM1_CH0_PTH2 = 1U,       /*!< FTM1_CH0 channels are mapped on PTH2. */
    kPORT_FTM1_CH1_PTC5 = 0U,       /*!< FTM1_CH1 channels are mapped on PTC5. */
    kPORT_FTM1_CH1_PTE7 = 1U,       /*!< FTM1_CH1 channels are mapped on PTE7. */
    kPORT_FTM2_CH0_PTC0 = 0U,       /*!< FTM2_CH0 channels are mapped on PTC0. */
    kPORT_FTM2_CH0_PTH0 = 1U,       /*!< FTM2_CH0 channels are mapped on PTH0. */
    kPORT_FTM2_CH0_PTF0 = 2U,       /*!< FTM2_CH0 channels are mapped on PTF0. */
    kPORT_FTM2_CH1_PTC1 = 0U,       /*!< FTM2_CH1 channels are mapped on PTC1. */
    kPORT_FTM2_CH1_PTH1 = 1U,       /*!< FTM2_CH1 channels are mapped on PTH1. */
    kPORT_FTM2_CH1_PTF1 = 2U,       /*!< FTM2_CH1 channels are mapped on PTF1. */
    kPORT_FTM2_CH2_PTC2 = 0U,       /*!< FTM2_CH2 channels are mapped on PTC2. */
    kPORT_FTM2_CH2_PTD0 = 1U,       /*!< FTM2_CH2 channels are mapped on PTD0. */
    kPORT_FTM2_CH2_PTG4 = 2U,       /*!< FTM2_CH2 channels are mapped on PTG4. */
    kPORT_FTM2_CH3_PTC3 = 0U,       /*!< FTM2_CH3 channels are mapped on PTC3. */
    kPORT_FTM2_CH3_PTD1 = 1U,       /*!< FTM2_CH3 channels are mapped on PTD1. */
    kPORT_FTM2_CH3_PTG5 = 2U,       /*!< FTM2_CH3 channels are mapped on PTG5. */
    kPORT_FTM2_CH4_PTB4 = 0U,       /*!< FTM2_CH4 channels are mapped on PTB4. */
    kPORT_FTM2_CH4_PTG6 = 1U,       /*!< FTM2_CH4 channels are mapped on PTG6. */
    kPORT_FTM2_CH5_PTB5 = 0U,       /*!< FTM2_CH5 channels are mapped on PTB5. */
    kPORT_FTM2_CH5_PTG7 = 1U,       /*!< FTM2_CH5 channels are mapped on PTG7. */
    kPORT_I2C1_SCLPTE1_SDAPTE0 = 0U, /*!< I2C1_SCL and I2C1_SDA are mapped on PTE1 and PTE0, respectively. */
    kPORT_I2C1_SCLPTH4_SDAPTH3 = 1U, /*!< I2C1_SCL and I2C1_SDA are mapped on PTH4 and PTH3, respectively. */
    kPORT_SPI1_SCKPTD0_MOSIPTD1_MISOPTD2_PCSPTD3 = 0U, /*!< SPI1_SCK/MOSI/MISO/PCS0 are mapped on PTD0/PTD1/PTD2/PTD3.*/
    kPORT_SPI1_SCKPTG4_MOSIPTG5_MISOPTG6_PCSPTG7 =
        1U,                         /*!< SPI1_SCK/MOSI/MISO/PCS0 are mapped on PTG4/PTG5/PTG6/PTG7. */
    kPORT_UART1_RXPTC7_TXPTC6 = 0U, /*!< UART1_RX and UART1_TX are mapped on PTC7 and PTC6. */
    kPORT_UART1_RXPTF3_TXPTF2 = 1U,  /*!< UART1_RX and UART1_TX are mapped on PTF3 and PTF2. */
    kPORT_UART2_RXPTD7_TXPTD6 = 0U, /*!< UART2_RX and UART2_TX are mapped on PTD7 and PTD6. */
    kPORT_UART2_RXPTI1_TXPTI0 = 1U,  /*!< UART2_RX and UART2_TX are mapped on PTI1 and PTI0. */
    kPORT_PWTIN0_PTD5 = 0U,         /*!< PWTIN0 is mapped to PTD5. */
    kPORT_PWTIN0_PTE2 = 1U,         /*!< PWTIN0 is mapped to PTE2. */
    kPORT_PWTIN1_PTB0 = 0U,         /*!< PWTIN0 is mapped to PTB0. */
    kPORT_PWTIN1_PTH7 = 1U,         /*!< PWTIN0 is mapped to PTH7. */
    kPORT_MSCAN_TXPTC7_RXPTC6 = 0U, /*!< CAN_TX, RXis mapped to PTC7, PTC6. */
    kPORT_MSCAN_TXPTE7_RXPTH2 = 1U  /*!< CAN_TX, RXis mapped to PTE7, PTH2. */
} port_pin_select_t;

/*! @brief The PORT pins for input glitch filter configure */
typedef enum _port_filter_pin_t {
    kPORT_FilterPTA = PORT_IOFLT0_FLTA_SHIFT,     /*!< Filter for input from PTA. */
    kPORT_FilterPTB = PORT_IOFLT0_FLTB_SHIFT,     /*!< Filter for input from PTB. */
    kPORT_FilterPTC = PORT_IOFLT0_FLTC_SHIFT,     /*!< Filter for input from PTC. */
    kPORT_FilterPTD = PORT_IOFLT0_FLTD_SHIFT,     /*!< Filter for input from PTD. */
    kPORT_FilterPTE = PORT_IOFLT0_FLTE_SHIFT,     /*!< Filter for input from PTE. */
    kPORT_FilterPTF = PORT_IOFLT0_FLTF_SHIFT,     /*!< Filter for input from PTF. */
    kPORT_FilterPTG = PORT_IOFLT0_FLTG_SHIFT,     /*!< Filter for input from PTG. */
    kPORT_FilterPTH = PORT_IOFLT0_FLTH_SHIFT,     /*!< Filter for input from PTH. */
    kPORT_FilterRST = PORT_IOFLT0_FLTRST_SHIFT,   /*!< Filter for input from RESET/IRQ. */
    kPORT_FilterKBI0 = PORT_IOFLT0_FLTKBI0_SHIFT, /*!< Filter for input from KBI0. */
    kPORT_FilterKBI1 = PORT_IOFLT0_FLTKBI1_SHIFT, /*!< Filter for input from KBI1. */
    kPORT_FilterNMI = PORT_IOFLT0_FLTNMI_SHIFT,   /*!< Filter for input from NMI. */
    KPORT_Filter0MAX = PORT_IOFLT0_FLTNMI_SHIFT + 1U,                      /*!< The max shift for Filter0 */
    kPORT_FilterPTI = PORT_IOFLT1_FLTI_SHIFT + PORT_FILTER_REG_OFFSET,     /*!< Filter for input from PTI. */
    kPORT_FilterIRQ = PORT_IOFLT1_FLTIRQ_SHIFT + PORT_FILTER_REG_OFFSET,   /*!< Filter for input from IRQ. */
    kPORT_FilterFTM0 = PORT_IOFLT1_FLTFTM0_SHIFT + PORT_FILTER_REG_OFFSET, /*!< Filter for input from FTM0. */
    kPORT_FilterFTM1 = PORT_IOFLT1_FLTFTM1_SHIFT + PORT_FILTER_REG_OFFSET, /*!< Filter for input form FTM1. */
    kPORT_FilterPWT = PORT_IOFLT1_FLTPWT_SHIFT + PORT_FILTER_REG_OFFSET,   /*!< Filter for input from PWT. */
    kPORT_FilterI2C0 = PORT_IOFLT1_FLTI2C0_SHIFT + PORT_FILTER_REG_OFFSET, /*!< Filter for input form I2C0. */ 
    kPORT_FilterI2C1 = PORT_IOFLT1_FLTI2C1_SHIFT + PORT_FILTER_REG_OFFSET  /*!< Filter for input from I2C1. */
} port_filter_pin_t;

/*! @brief The Filter selection for input pins */
typedef enum _port_filter_select_t {
    kPORT_BUSCLK_OR_NOFILTER = 0U, /*!< Filter section BUSCLK for PTA~PTH,= or no filter for REST/KBI0/KBI1/NMI/IRQ/FTM0/FTM1/PWT/I2C0/I2C1. */
    kPORT_FILTERDIV1 = 1U,      /*!< Filter Division Set 1. */
    kPORT_FILTERDIV2 = 2U,      /*!< Filter Division Set 2. */
    kPORT_FILTERDIV3_OR_BUSCLK = 3U /*!< Filter Division Set 3 for NMI/KBI1/KNI0/IRQ/PTA~PTH/PWT/FTM0/FTM1/IRQ/PTI or BUSCLK for I2C0/I2C1/ */
} port_filter_select_t;

/*! @brief Port pin for high driver enable/disable control. */
typedef enum _port_highdrive_pin_t {
    kPORT_HighDrive_PTB4 = PORT_HDRVE_PTB4_MASK, /*!< PTB4. */
    kPORT_HighDrive_PTB5 = PORT_HDRVE_PTB5_MASK, /*!< PTB5. */
    kPORT_HighDrive_PTD0 = PORT_HDRVE_PTD0_MASK, /*!< PTD0. */
    kPORT_HighDrive_PTD1 = PORT_HDRVE_PTD1_MASK, /*!< PTD1. */
    kPORT_HighDrive_PTE0 = PORT_HDRVE_PTE0_MASK, /*!< PTE0. */
    kPORT_HighDrive_PTE1 = PORT_HDRVE_PTE1_MASK, /*!< PTE1. */
    kPORT_HighDrive_PTH0 = PORT_HDRVE_PTH0_MASK, /*!< PTH0. */
    kPORT_HighDrive_PTH1 = PORT_HDRVE_PTH1_MASK  /*!< PTH1. */
} port_highdrive_pin_t;

/*******************************************************************************
* API
******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*! @name Configuration */
/*@{*/

/*!
 * @brief Selects pin for modules.
 *
 * This API is used to select the port pin for the module with multiple port pin
 * selection. For example the FTM Channel 0 can be mapped to ether PTA0 or PTB2.
 * Select FTM channel 0 map to PTA0 port pin as:
 * @code
 * PORT_SetPinSelect(kPORT_FTM0CH0, kPORT_FTM0_CH0_PTA0);
 * @endcode
 *  
 * @Note： This API doesn't support to select specified ALT for a given port pin. 
 * The ALT feature is automatically selected by hardware according to the 
 * ALT priority:
 *     Low -----> high: 
 *     Alt1, Alt2, …
 * when peripheral modules has been enabled.
 *
 * If you want to select a specified ALT for a given port pin, please add two more
 * steps after calling PORT_SetPinSelect:
 * 1. Enable module or the port control in the module for the ALT you want to select.
 *   For I2C ALT feature:all port enable is controlled by the module enable, so 
 *   set IICEN in I2CX_C1 to enable the port pins for I2C feature.
 *   For KBI ALT feature:each port pin is controlled independently by each bit in KBIx_PE.
 *   set related bit in this register to enable the KBI feature in the port pin.          
 * 2. Make sure there is no module enabled with higher priority than the ALT module feature
 *  you want to select. 
 *
 * @param module   Modules for pin selection.
 *        For NMI/RST module are write-once attribute after reset.
 * @param pin   Port pin selection for modules.
 *
 */
void PORT_SetPinSelect(port_module_t module, port_pin_select_t pin);

/*!
 * @brief Selects the glitch filter for input pins.
 *
 * @param base   PORT peripheral base pointer.
 * @param port   PORT pin, see "port_filter_pin_t".
 * @param filter  Filter select, see "port_filter_select_t".
 */
void PORT_SetFilterSelect(PORT_Type *base, port_filter_pin_t port, port_filter_select_t filter);

/*!
 * @brief Sets the width threshold for glitch filter division set 1.
 *`
 * @param base   PORT peripheral base pointer.
 * @param threshold PORT glitch filter width threshold, take refer to reference manual for detail information.
 *        0  -   LPOCLK
 *        1  -   LPOCLK/2
 *        2  -   LPOCLK/4
 *        3  -   LPOCLK/8
 *        4  -   LPOCLK/16
 *        5  -   LPOCLK/32
 *        6  -   LPOCLK/64
 *        7  -   LPOCLK/128
 */
static inline void PORT_SetFilterDIV1WidthThreshold(PORT_Type *base, uint8_t threshold)
{
    uint32_t fltReg;

    fltReg = base->IOFLT0 & ~PORT_IOFLT0_FLTDIV1_MASK;
    base->IOFLT0 = fltReg | PORT_IOFLT0_FLTDIV1(threshold);
}

/*!
 * @brief Sets the width threshold for glitch filter division set 2.
 *`
 * @param base   PORT peripheral base pointer.
 * @param threshold PORT glitch filter width threshold, take refer to reference manual for detail information.
 *        0  -   BUSCLK/32
 *        1  -   BUSCLK/64
 *        2  -   BUSCLK/128
 *        3  -   BUSCLK/256
 *        4  -   BUSCLK/512
 *        5  -   BUSCLK/1024
 *        6  -   BUSCLK/2048
 *        7  -   BUSCLK/4096
 */
static inline void PORT_SetFilterDIV2WidthThreshold(PORT_Type *base, uint8_t threshold)
{
    uint32_t fltReg;

    fltReg = base->IOFLT0 & ~PORT_IOFLT0_FLTDIV2_MASK;
    base->IOFLT0 = fltReg | PORT_IOFLT0_FLTDIV2(threshold);
}

/*!
 * @brief Sets the width threshold for glitch filter division set 3.
 *`
 * @param base   PORT peripheral base pointer.
 * @param threshold PORT glitch filter width threshold, take refer to reference manual for detail information.
 *        0  -   BUSCLK/2
 *        1  -   BUSCLK/4
 *        2  -   BUSCLK/8
 *        3  -   BUSCLK/16
 */
static inline void PORT_SetFilterDIV3WidthThreshold(PORT_Type *base, uint8_t threshold)
{
    uint32_t fltReg;

    fltReg = base->IOFLT0 & ~PORT_IOFLT0_FLTDIV3_MASK;
    base->IOFLT0 = fltReg | PORT_IOFLT0_FLTDIV3(threshold);
}

/*!
 * @brief Enables or disables the port pull up.
 *
 * @param base   PORT peripheral base pointer.
 * @param port   PORT type, such as PTA/PTB/PTC etc, see "port_type_t".
 * @param num    PORT pin number, such as 0, 1, 2...
 *               For PTI, only PTI0 ~ PTI6 pins are supported. so when set pull
 *               up feature for PTI, please don't set number 7. see reference manual for more details.
 * @param enable  Enable or disable the pull up feature switch.
 */
void PORT_SetPinPullUpEnable(PORT_Type *base, port_type_t port, uint8_t num, bool enable);

/*!
 * @brief Set High drive for port pins.
 *
 * @param base PORT peripheral base pointer.
 * @param pin PORT pin support high drive.
 * @param enable Enable or disable the high driver feature switch.
 */
static inline void PORT_SetHighDriveEnable(PORT_Type *base, port_highdrive_pin_t pin, bool enable)
{
    if (enable)
    {
        base->HDRVE |= (uint32_t)pin;
    }
    else
    {
        base->HDRVE &= ~(uint32_t)pin;
    }
}

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_PORT_H_ */
