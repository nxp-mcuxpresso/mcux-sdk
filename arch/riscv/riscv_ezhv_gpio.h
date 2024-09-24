/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef RISCV_EZHV_GPIO_H_
#define RISCV_EZHV_GPIO_H_

#include "riscv_asm.h"
#include "riscv_xzmsg.h"

/*!
 * @ingroup RISCV_CoreCustomExtXzezhv
 * @defgroup RISCV_CoreCustomExtXzezhvGpio EZH-V GPIO
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @name GPIO CSR registers
 * @{
 */
#define CSR_EZ_GPIO_D (2101U)
#define CSR_EZ_GPIO_I (2102U)
#define CSR_EZ_GPIO_O (2103U)
/*!
 * @}
 */

/*!@brief LIST of EZHV GPIO pins */
typedef enum _ezhv_gpio_pin
{
    kEZHV_GPIO_Pin0 = 0U,    /*!< EZH_GPIO0 */
    kEZHV_GPIO_Pin1 = 1U,    /*!< EZH_GPIO1 */
    kEZHV_GPIO_Pin2 = 2U,    /*!< EZH_GPIO2 */
    kEZHV_GPIO_Pin3 = 3U,    /*!< EZH_GPIO3 */
    kEZHV_GPIO_Pin4 = 4U,    /*!< EZH_GPIO4 */
    kEZHV_GPIO_Pin5 = 5U,    /*!< EZH_GPIO5 */
    kEZHV_GPIO_Pin6 = 6U,    /*!< EZH_GPIO6 */
    kEZHV_GPIO_Pin7 = 7U,    /*!< EZH_GPIO7 */
    kEZHV_GPIO_Pin8 = 8U,    /*!< EZH_GPIO8 */
    kEZHV_GPIO_Pin9 = 9U,    /*!< EZH_GPIO9 */
    kEZHV_GPIO_Pin10 = 10U,  /*!< EZH_GPIO10 */
    kEZHV_GPIO_Pin11 = 11U,  /*!< EZH_GPIO11 */
    kEZHV_GPIO_Pin12 = 12U,  /*!< EZH_GPIO12 */
    kEZHV_GPIO_Pin13 = 13U,  /*!< EZH_GPIO13 */
    kEZHV_GPIO_Pin14 = 14U,  /*!< EZH_GPIO14 */
    kEZHV_GPIO_Pin15 = 15U,  /*!< EZH_GPIO15 */
    kEZHV_GPIO_Pin16 = 16U,  /*!< EZH_GPIO16 */
    kEZHV_GPIO_Pin17 = 17U,  /*!< EZH_GPIO17 */
    kEZHV_GPIO_Pin18 = 18U,  /*!< EZH_GPIO18 */
    kEZHV_GPIO_Pin19 = 19U,  /*!< EZH_GPIO19 */
    kEZHV_GPIO_Pin20 = 20U,  /*!< EZH_GPIO20 */
    kEZHV_GPIO_Pin21 = 21U,  /*!< EZH_GPIO21 */
    kEZHV_GPIO_Pin22 = 22U,  /*!< EZH_GPIO22 */
    kEZHV_GPIO_Pin23 = 23U,  /*!< EZH_GPIO23 */
    kEZHV_GPIO_Pin24 = 24U,  /*!< EZH_GPIO24 */
    kEZHV_GPIO_Pin25 = 25U,  /*!< EZH_GPIO25 */
    kEZHV_GPIO_Pin26 = 26U,  /*!< EZH_GPIO26 */
    kEZHV_GPIO_Pin27 = 27U,  /*!< EZH_GPIO27 */
    kEZHV_GPIO_Pin28 = 28U,  /*!< EZH_GPIO28 */
    kEZHV_GPIO_Pin29 = 29U,  /*!< EZH_GPIO29 */
    kEZHV_GPIO_Pin30 = 30U,  /*!< EZH_GPIO30 */
} ezhv_gpio_pin_t;

/*! @brief GPIO direction definition */
typedef enum _ezhv_gpio_pin_direction
{
    kEZHV_GPIO_DigitalInput  = 1U, /*!< Set current pin as digital input*/
    kEZHV_GPIO_DigitalOutput = 0U, /*!< Set current pin as digital output*/
} ezhv_gpio_pin_direction_t;

/*! @brief definition for GPIO level */
typedef enum _ezhv_gpio_pin_level
{
    kEZHV_GPIO_High = 1U,
    kEZHV_GPIO_Low  = 0U,
} ezhv_gpio_pin_level_t;

/*!
 * @brief The GPIO pin configuration structure.
 *
 * Every pin can only be configured as either output pin or input pin at a time.
 * If configured as a input pin, then leave the outputConfig unused.
 */
typedef struct _ezhv_gpio_pin_config
{
    ezhv_gpio_pin_direction_t pinDirection; /*!< GPIO direction, input or output */
    /* Output configurations, please ignore if configured as a input one */
    ezhv_gpio_pin_level_t outputLogic; /*!< Set default output logic, no use in input */
} ezhv_gpio_pin_config_t;


/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Set ezhv PIO direction register
 *
 * @param pin  which pin to set direction, refer to enum::ezhv_gpio_pin_t
 * @param dir  pin direction, refer to enum::ezhv_gpio_pin_direction_t
 */
static inline void EZHV_SetGpioDirection(ezhv_gpio_pin_t pin,  ezhv_gpio_pin_direction_t dir)
{
    if (kEZHV_GPIO_DigitalOutput == dir)
    {
        csr_clear(CSR_EZ_GPIO_D, (1UL << pin));
    }
    else
    {
        csr_set(CSR_EZ_GPIO_D, (1UL << pin));
    }
}

/*!
 * @brief Set the output level of the one GPIO pin to logic 1 or 0
 *
 * @param pin       which pin to write, refer to enum::ezhv_gpio_pin_t
 * @param output    pin output logic level.
 *                  -0: corresponding pin output low-logic level.
 *                  -1: corresponding pin input high-logic level.
 */
static inline void EZHV_GpioPinWrite(ezhv_gpio_pin_t pin,  ezhv_gpio_pin_level_t output)
{
    if (kEZHV_GPIO_High == output)
    {
        csr_set(CSR_EZ_GPIO_O, (1UL << pin));
    }
    else
    {
        csr_clear(CSR_EZ_GPIO_O, (1UL << pin));
    }
}

/*!
 * @brief Reads the current input value of the ezhv GPIO PIN
 *
 * @param pin       which pin to write, refer to enum::ezhv_gpio_pin_t
 *
 * @return the level of ezh gpio pin
 */
static inline ezhv_gpio_pin_level_t EZHV_GpioPinRead(ezhv_gpio_pin_t pin)
{
    return (ezhv_gpio_pin_level_t)((csr_read(CSR_EZ_GPIO_I) >> pin) & 0x1);
}


/*!
 * @brief Sets the output level of the multiple ezhv PIO pins to logic 1, CSR#CSR_EZ_GPIO_O, ez_gpio_o
 *
 * @param value    bits in gpio output register to set
 */
static inline void EZHV_PortWrite(uint32_t value)
{
    csr_write(CSR_EZ_GPIO_O, value);
}

/*!
 * @brief Sets the output level of the multiple ezhv PIO pins to logic 1, CSR#CSR_EZ_GPIO_O, ez_gpio_o
 *
 * @param mask Bits in gpio output register to set
 */
static inline void EZHV_PortSet(uint32_t mask)
{
    csr_set(CSR_EZ_GPIO_O, mask);
}

/*!
 * @brief Clear the output level of the multiple ezhv PIO pins to logic 1, CSR#CSR_EZ_GPIO_O, ez_gpio_o
 *
 * @param mask Bits in gpio output register to clear
 */
static inline void EZHV_PortClear(uint32_t mask)
{
    csr_clear(CSR_EZ_GPIO_O, mask);
}

/*!
 * @brief Read the EZHV PIO port   CSR#CSR_EZ_GPIO_I, ez_gpio_i
 *
 * @return the ezhv gpio input register values
 */
static inline uint32_t EZHV_PortRead(void)
{
    return (uint32_t)csr_read(CSR_EZ_GPIO_I);
}

/*!
 * @brief Set all EZHV pin Direction  CSR#CSR_EZ_GPIO_D, ez_gpio_d
 *
 * @param dirVal  each bit defines a gpio direction, 1:input, 0: output,
 *        for example, 0x0: all as output pins, 0x7fff_ffff: all as input pins
 */
static inline void EZHV_PortDirSet(uint32_t dirVal)
{
    csr_write(CSR_EZ_GPIO_D, dirVal);
}

/*!
 * @brief Read the EZHV PIO direction register CSR#CSR_EZ_GPIO_D, ez_gpio_d
 *
 * @return the direction setting of all PIOs
 */
static inline uint32_t EZHV_PortDirRead(void)
{
    return (uint32_t)csr_read(CSR_EZ_GPIO_D);
}

/*!
 * @brief Initialize a EZHV GPIO pin
 *
 * @param pin    ezhv gpio pin index
 * @param config     pin configuration pointer
 */
static inline void EZHV_InitGpioPin(ezhv_gpio_pin_t pin, ezhv_gpio_pin_config_t *config)
{
    if (kEZHV_GPIO_DigitalOutput == config->pinDirection)
    {
        EZHV_SetGpioDirection(pin, kEZHV_GPIO_DigitalOutput);
        EZHV_GpioPinWrite(pin, config->outputLogic);
    }
    else
    {
        EZHV_SetGpioDirection(pin, kEZHV_GPIO_DigitalInput);
    }
}

/*!
 * @brief Toggle given EZH_PIO
 *
 * @param pin Refer to ezhv_gpio_pin_t
 *
 */
static inline void EZHV_PinToggle(ezhv_gpio_pin_t pin)
{
    static const xzmsg_snd_type arr[4] = {kXZMSG_UpdateGpio7ToGpio0, kXZMSG_UpdateGpio15ToGpio8,
                       kXZMSG_UpdateGpio23ToGpio16, kXZMSG_UpdateGpio31ToGpio24};
    uint32_t idx = pin / XZMSG_GPIO_BYTE_WISE;
    uint32_t val = pin % XZMSG_GPIO_BYTE_WISE;
    XZMSG_Send(XZMSG_GPIO_TOGGLE_EN(1UL << val), arr[idx]);
}

/*!
 * @brief Update EZH-V ezhv_gpio_out[31:0]
 *
 * @param gpioVal which pins to toggle, to clear, to set
 * @param gpioMsg refer to xzmsg_snd_type
 */
static inline void EZHV_UpdateGpio(uint32_t gpioVal, xzmsg_snd_type gpioMsg)
{
    XZMSG_Send(gpioVal, gpioMsg);
}

#define EZHV_READ_GPIO_IMM(n)    XZMSG_Rcvrdi(n)

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* RISCV_EZHV_GPIO_H_ */
