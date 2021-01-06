/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_RGPIO_H_
#define _FSL_RGPIO_H_

#include "fsl_common.h"

/*!
 * @addtogroup rgpio
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief RGPIO driver version 2.0.3. */
#define FSL_RGPIO_DRIVER_VERSION (MAKE_VERSION(2, 0, 3))
/*@}*/

/*! @brief RGPIO direction definition */
typedef enum _rgpio_pin_direction
{
    kRGPIO_DigitalInput  = 0U, /*!< Set current pin as digital input*/
    kRGPIO_DigitalOutput = 1U, /*!< Set current pin as digital output*/
} rgpio_pin_direction_t;

#if defined(FSL_FEATURE_RGPIO_HAS_ATTRIBUTE_CHECKER) && FSL_FEATURE_RGPIO_HAS_ATTRIBUTE_CHECKER
/*! @brief RGPIO checker attribute */
typedef enum _rgpio_checker_attribute
{
    kRGPIO_UsernonsecureRWUsersecureRWPrivilegedsecureRW =
        0x00U, /*!< User nonsecure:Read+Write; User Secure:Read+Write; Privileged Secure:Read+Write */
    kRGPIO_UsernonsecureRUsersecureRWPrivilegedsecureRW =
        0x01U, /*!< User nonsecure:Read;       User Secure:Read+Write; Privileged Secure:Read+Write */
    kRGPIO_UsernonsecureNUsersecureRWPrivilegedsecureRW =
        0x02U, /*!< User nonsecure:None;       User Secure:Read+Write; Privileged Secure:Read+Write */
    kRGPIO_UsernonsecureRUsersecureRPrivilegedsecureRW =
        0x03U, /*!< User nonsecure:Read;       User Secure:Read;       Privileged Secure:Read+Write */
    kRGPIO_UsernonsecureNUsersecureRPrivilegedsecureRW =
        0x04U, /*!< User nonsecure:None;       User Secure:Read;       Privileged Secure:Read+Write */
    kRGPIO_UsernonsecureNUsersecureNPrivilegedsecureRW =
        0x05U, /*!< User nonsecure:None;       User Secure:None;       Privileged Secure:Read+Write */
    kRGPIO_UsernonsecureNUsersecureNPrivilegedsecureR =
        0x06U, /*!< User nonsecure:None;       User Secure:None;       Privileged Secure:Read */
    kRGPIO_UsernonsecureNUsersecureNPrivilegedsecureN =
        0x07U, /*!< User nonsecure:None;       User Secure:None;       Privileged Secure:None */
    kRGPIO_IgnoreAttributeCheck = 0x80U, /*!< Ignores the attribute check */
} rgpio_checker_attribute_t;
#endif

/*!
 * @brief The RGPIO pin configuration structure.
 *
 * Each pin can only be configured as either an output pin or an input pin at a time.
 * If configured as an input pin, leave the outputConfig unused.
 * Note that in some use cases, the corresponding port property should be configured in advance
 *        with the PORT_SetPinConfig().
 */
typedef struct _rgpio_pin_config
{
    rgpio_pin_direction_t pinDirection; /*!< RGPIO direction, input or output */
    /* Output configurations; ignore if configured as an input pin */
    uint8_t outputLogic; /*!< Set a default output logic, which has no use in input */
} rgpio_pin_config_t;

/*! @} */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @addtogroup rgpio_driver
 * @{
 */

/*! @name RGPIO Configuration */
/*@{*/

/*!
 * @brief Initializes a RGPIO pin used by the board.
 *
 * To initialize the RGPIO, define a pin configuration, as either input or output, in the user file.
 * Then, call the RGPIO_PinInit() function.
 *
 * This is an example to define an input pin or an output pin configuration.
 * @code
 *  Define a digital input pin configuration,
 * rgpio_pin_config_t config =
 * {
 *   kRGPIO_DigitalInput,
 *   0,
 * }
 * Define a digital output pin configuration,
 * rgpio_pin_config_t config =
 * {
 *   kRGPIO_DigitalOutput,
 *   0,
 * }
 * @endcode
 *
 * @param base   RGPIO peripheral base pointer (RGPIOA, RGPIOB, RGPIOC, and so on.)
 * @param pin    RGPIO port pin number
 * @param config RGPIO pin configuration pointer
 */
void RGPIO_PinInit(RGPIO_Type *base, uint32_t pin, const rgpio_pin_config_t *config);

/*!
 * @brief Gets the RGPIO instance according to the RGPIO base
 *
 * @param base    RGPIO peripheral base pointer(PTA, PTB, PTC, etc.)
 * @retval RGPIO instance
 */
uint32_t RGPIO_GetInstance(RGPIO_Type *base);
/*@}*/

/*! @name RGPIO Output Operations */
/*@{*/

/*!
 * @brief Sets the output level of the multiple RGPIO pins to the logic 1 or 0.
 *
 * @param base    RGPIO peripheral base pointer (RGPIOA, RGPIOB, RGPIOC, and so on.)
 * @param pin     RGPIO pin number
 * @param output  RGPIO pin output logic level.
 *        - 0: corresponding pin output low-logic level.
 *        - 1: corresponding pin output high-logic level.
 */
static inline void RGPIO_PinWrite(RGPIO_Type *base, uint32_t pin, uint8_t output)
{
    if (output == 0U)
    {
        base->PCOR = 1UL << pin;
    }
    else
    {
        base->PSOR = 1UL << pin;
    }
}

/*!
 * @brief Sets the output level of the multiple RGPIO pins to the logic 1 or 0.
 * @deprecated Do not use this function.  It has been superceded by @ref RGPIO_PinWrite.
 */
static inline void RGPIO_WritePinOutput(RGPIO_Type *base, uint32_t pin, uint8_t output)
{
    RGPIO_PinWrite(base, pin, output);
}

/*!
 * @brief Sets the output level of the multiple RGPIO pins to the logic 1.
 *
 * @param base RGPIO peripheral base pointer (RGPIOA, RGPIOB, RGPIOC, and so on.)
 * @param mask RGPIO pin number macro
 */
static inline void RGPIO_PortSet(RGPIO_Type *base, uint32_t mask)
{
    base->PSOR = mask;
}

/*!
 * @brief Sets the output level of the multiple RGPIO pins to the logic 1.
 * @deprecated Do not use this function.  It has been superceded by @ref RGPIO_PortSet.
 */
static inline void RGPIO_SetPinsOutput(RGPIO_Type *base, uint32_t mask)
{
    RGPIO_PortSet(base, mask);
}

/*!
 * @brief Sets the output level of the multiple RGPIO pins to the logic 0.
 *
 * @param base RGPIO peripheral base pointer (RGPIOA, RGPIOB, RGPIOC, and so on.)
 * @param mask RGPIO pin number macro
 */
static inline void RGPIO_PortClear(RGPIO_Type *base, uint32_t mask)
{
    base->PCOR = mask;
}

/*!
 * @brief Sets the output level of the multiple RGPIO pins to the logic 0.
 * @deprecated Do not use this function.  It has been superceded by @ref RGPIO_PortClear.
 *
 * @param base RGPIO peripheral base pointer (RGPIOA, RGPIOB, RGPIOC, and so on.)
 * @param mask RGPIO pin number macro
 */
static inline void RGPIO_ClearPinsOutput(RGPIO_Type *base, uint32_t mask)
{
    RGPIO_PortClear(base, mask);
}

/*!
 * @brief Reverses the current output logic of the multiple RGPIO pins.
 *
 * @param base RGPIO peripheral base pointer (RGPIOA, RGPIOB, RGPIOC, and so on.)
 * @param mask RGPIO pin number macro
 */
static inline void RGPIO_PortToggle(RGPIO_Type *base, uint32_t mask)
{
    base->PTOR = mask;
}

/*!
 * @brief Reverses the current output logic of the multiple RGPIO pins.
 * @deprecated Do not use this function.  It has been superceded by @ref RGPIO_PortToggle.
 */
static inline void RGPIO_TogglePinsOutput(RGPIO_Type *base, uint32_t mask)
{
    RGPIO_PortToggle(base, mask);
}
/*@}*/

/*! @name RGPIO Input Operations */
/*@{*/

/*!
 * @brief Reads the current input value of the RGPIO port.
 *
 * @param base RGPIO peripheral base pointer (RGPIOA, RGPIOB, RGPIOC, and so on.)
 * @param pin     RGPIO pin number
 * @retval RGPIO port input value
 *        - 0: corresponding pin input low-logic level.
 *        - 1: corresponding pin input high-logic level.
 */
static inline uint32_t RGPIO_PinRead(RGPIO_Type *base, uint32_t pin)
{
    return (((base->PDIR) >> pin) & 0x01U);
}

/*!
 * @brief Reads the current input value of the RGPIO port.
 * @deprecated Do not use this function.  It has been superceded by @ref RGPIO_PinRead.
 */
static inline uint32_t RGPIO_ReadPinInput(RGPIO_Type *base, uint32_t pin)
{
    return RGPIO_PinRead(base, pin);
}

/*@}*/

#if defined(FSL_FEATURE_SOC_PORT_COUNT) && FSL_FEATURE_SOC_PORT_COUNT
/*! @name RGPIO Interrupt */
/*@{*/

/*!
 * @brief Reads the RGPIO port interrupt status flag.
 *
 * If a pin is configured to generate the DMA request, the corresponding flag
 * is cleared automatically at the completion of the requested DMA transfer.
 * Otherwise, the flag remains set until a logic one is written to that flag.
 * If configured for a level sensitive interrupt that remains asserted, the flag
 * is set again immediately.
 *
 * @param base RGPIO peripheral base pointer (RGPIOA, RGPIOB, RGPIOC, and so on.)
 * @retval The current RGPIO port interrupt status flag, for example, 0x00010001 means the
 *         pin 0 and 17 have the interrupt.
 */
uint32_t RGPIO_PortGetInterruptFlags(RGPIO_Type *base);

/*!
 * @brief Reads the RGPIO port interrupt status flag.
 * @deprecated Do not use this function.  It has been superceded by @ref RGPIO_PortGetInterruptFlags.
 */
static inline uint32_t RGPIO_GetPinsInterruptFlags(RGPIO_Type *base)
{
    return RGPIO_PortGetInterruptFlags(base);
}

/*!
 * @brief Clears multiple RGPIO pin interrupt status flags.
 *
 * @param base RGPIO peripheral base pointer (RGPIOA, RGPIOB, RGPIOC, and so on.)
 * @param mask RGPIO pin number macro
 */
void RGPIO_PortClearInterruptFlags(RGPIO_Type *base, uint32_t mask);

/*!
 * @brief Clears multiple RGPIO pin interrupt status flags.
 * @deprecated Do not use this function.  It has been superceded by @ref RGPIO_PortClearInterruptFlags.
 */
static inline void RGPIO_ClearPinsInterruptFlags(RGPIO_Type *base, uint32_t mask)
{
    RGPIO_PortClearInterruptFlags(base, mask);
}
#endif
#if defined(FSL_FEATURE_RGPIO_HAS_ATTRIBUTE_CHECKER) && FSL_FEATURE_RGPIO_HAS_ATTRIBUTE_CHECKER
/*!
 * @brief The RGPIO module supports a device-specific number of data ports, organized as 32-bit
 * words. Each 32-bit data port includes a GACR register, which defines the byte-level
 * attributes required for a successful access to the RGPIO programming model. The attribute controls for the 4 data
 * bytes in the GACR follow a standard little endian
 * data convention.
 *
 * @param base RGPIO peripheral base pointer (RGPIOA, RGPIOB, RGPIOC, and so on.)
 * @param mask RGPIO pin number macro
 */
void RGPIO_CheckAttributeBytes(RGPIO_Type *base, rgpio_checker_attribute_t attribute);
#endif

/*@}*/
/*! @} */

/*!
 * @addtogroup fgpio_driver
 * @{
 */

/*
 * Introduces the FGPIO feature.
 *
 * The FGPIO registers are aliased to the IOPORT interface.
 * Accesses via the IOPORT interface occur in parallel with any instruction fetches and
 * complete in a single cycle. This aliased Fast GPIO memory map is called FGPIO.
 */

#if defined(FSL_FEATURE_SOC_FGPIO_COUNT) && FSL_FEATURE_SOC_FGPIO_COUNT

/*! @name FGPIO Configuration */
/*@{*/

#if defined(FSL_FEATURE_PCC_HAS_FGPIO_CLOCK_GATE_CONTROL) && FSL_FEATURE_PCC_HAS_FGPIO_CLOCK_GATE_CONTROL
/*!
 * @brief Initializes the FGPIO peripheral.
 *
 * This function ungates the FGPIO clock.
 *
 * @param base   FGPIO peripheral base pointer (FGPIOA, FGPIOB, FGPIOC, and so on.)
 */
void FGPIO_PortInit(FGPIO_Type *base);

/*!
 * @brief Initializes the FGPIO peripheral.
 * @deprecated Do not use this function.  It has been superceded by @ref FGPIO_PortInit.
 */
static inline void FGPIO_Init(FGPIO_Type *base)
{
    FGPIO_PortInit(base);
}
#endif
/*!
 * @brief Initializes a FGPIO pin used by the board.
 *
 * To initialize the FGPIO driver, define a pin configuration, as either input or output, in the user file.
 * Then, call the FGPIO_PinInit() function.
 *
 * This is an example to define an input pin or an output pin configuration:
 * @code
 *  Define a digital input pin configuration,
 * rgpio_pin_config_t config =
 * {
 *   kRGPIO_DigitalInput,
 *   0,
 * }
 * Define a digital output pin configuration,
 * rgpio_pin_config_t config =
 * {
 *   kRGPIO_DigitalOutput,
 *   0,
 * }
 * @endcode
 *
 * @param base   FGPIO peripheral base pointer (FGPIOA, FGPIOB, FGPIOC, and so on.)
 * @param pin    FGPIO port pin number
 * @param config FGPIO pin configuration pointer
 */
void FGPIO_PinInit(FGPIO_Type *base, uint32_t pin, const rgpio_pin_config_t *config);

/*!
 * @brief Gets the FGPIO instance according to the RGPIO base
 *
 * @param base    FGPIO peripheral base pointer(PTA, PTB, PTC, etc.)
 * @retval FGPIO instance
 */
uint32_t FGPIO_GetInstance(FGPIO_Type *base);
/*@}*/

/*! @name FGPIO Output Operations */
/*@{*/

/*!
 * @brief Sets the output level of the multiple FGPIO pins to the logic 1 or 0.
 *
 * @param base    FGPIO peripheral base pointer (FGPIOA, FGPIOB, FGPIOC, and so on.)
 * @param pin     FGPIO pin number
 * @param output  FGPIOpin output logic level.
 *        - 0: corresponding pin output low-logic level.
 *        - 1: corresponding pin output high-logic level.
 */
static inline void FGPIO_PinWrite(FGPIO_Type *base, uint32_t pin, uint8_t output)
{
    if (output == 0U)
    {
        base->PCOR = 1UL << pin;
    }
    else
    {
        base->PSOR = 1UL << pin;
    }
}

/*!
 * @brief Sets the output level of the multiple FGPIO pins to the logic 1 or 0.
 * @deprecated Do not use this function.  It has been superceded by @ref FGPIO_PinWrite.
 */
static inline void FGPIO_WritePinOutput(FGPIO_Type *base, uint32_t pin, uint8_t output)
{
    FGPIO_PinWrite(base, pin, output);
}

/*!
 * @brief Sets the output level of the multiple FGPIO pins to the logic 1.
 *
 * @param base FGPIO peripheral base pointer (FGPIOA, FGPIOB, FGPIOC, and so on.)
 * @param mask FGPIO pin number macro
 */
static inline void FGPIO_PortSet(FGPIO_Type *base, uint32_t mask)
{
    base->PSOR = mask;
}

/*!
 * @brief Sets the output level of the multiple FGPIO pins to the logic 1.
 * @deprecated Do not use this function.  It has been superceded by @ref FGPIO_PortSet.
 */
static inline void FGPIO_SetPinsOutput(FGPIO_Type *base, uint32_t mask)
{
    FGPIO_PortSet(base, mask);
}

/*!
 * @brief Sets the output level of the multiple FGPIO pins to the logic 0.
 *
 * @param base FGPIO peripheral base pointer (FGPIOA, FGPIOB, FGPIOC, and so on.)
 * @param mask FGPIO pin number macro
 */
static inline void FGPIO_PortClear(FGPIO_Type *base, uint32_t mask)
{
    base->PCOR = mask;
}

/*!
 * @brief Sets the output level of the multiple FGPIO pins to the logic 0.
 * @deprecated Do not use this function.  It has been superceded by @ref FGPIO_PortClear.
 */
static inline void FGPIO_ClearPinsOutput(FGPIO_Type *base, uint32_t mask)
{
    FGPIO_PortClear(base, mask);
}

/*!
 * @brief Reverses the current output logic of the multiple FGPIO pins.
 *
 * @param base FGPIO peripheral base pointer (FGPIOA, FGPIOB, FGPIOC, and so on.)
 * @param mask FGPIO pin number macro
 */
static inline void FGPIO_PortToggle(FGPIO_Type *base, uint32_t mask)
{
    base->PTOR = mask;
}

/*!
 * @brief Reverses the current output logic of the multiple FGPIO pins.
 * @deprecated Do not use this function.  It has been superceded by @ref FGPIO_PortToggle.
 */
static inline void FGPIO_TogglePinsOutput(FGPIO_Type *base, uint32_t mask)
{
    FGPIO_PortToggle(base, mask);
}
/*@}*/

/*! @name FGPIO Input Operations */
/*@{*/

/*!
 * @brief Reads the current input value of the FGPIO port.
 *
 * @param base FGPIO peripheral base pointer (FGPIOA, FGPIOB, FGPIOC, and so on.)
 * @param pin  FGPIO pin number
 * @retval FGPIO port input value
 *        - 0: corresponding pin input low-logic level.
 *        - 1: corresponding pin input high-logic level.
 */
static inline uint32_t FGPIO_PinRead(FGPIO_Type *base, uint32_t pin)
{
    return (((base->PDIR) >> pin) & 0x01U);
}

/*!
 * @brief Reads the current input value of the FGPIO port.
 * @deprecated Do not use this function.  It has been superceded by @ref FGPIO_PinRead
 */
static inline uint32_t FGPIO_ReadPinInput(FGPIO_Type *base, uint32_t pin)
{
    return FGPIO_PinRead(base, pin);
}
/*@}*/

#if defined(FSL_FEATURE_SOC_PORT_COUNT) && FSL_FEATURE_SOC_PORT_COUNT
/*! @name FGPIO Interrupt */
/*@{*/

/*!
 * @brief Reads the FGPIO port interrupt status flag.
 *
 * If a pin is configured to generate the DMA request, the corresponding flag
 * is cleared automatically at the completion of the requested DMA transfer.
 * Otherwise, the flag remains set until a logic one is written to that flag.
 * If configured for a level-sensitive interrupt that remains asserted, the flag
 * is set again immediately.
 *
 * @param base FGPIO peripheral base pointer (FGPIOA, FGPIOB, FGPIOC, and so on.)
 * @retval The current FGPIO port interrupt status flags, for example, 0x00010001 means the
 *         pin 0 and 17 have the interrupt.
 */
uint32_t FGPIO_PortGetInterruptFlags(FGPIO_Type *base);

/*!
 * @brief Reads the FGPIO port interrupt status flag.
 * @deprecated Do not use this function.  It has been superceded by @ref FGPIO_PortGetInterruptFlags.
 */
static inline uint32_t FGPIO_GetPinsInterruptFlags(FGPIO_Type *base)
{
    return FGPIO_PortGetInterruptFlags(base);
}

/*!
 * @brief Clears the multiple FGPIO pin interrupt status flag.
 *
 * @param base FGPIO peripheral base pointer (FGPIOA, FGPIOB, FGPIOC, and so on.)
 * @param mask FGPIO pin number macro
 */
void FGPIO_PortClearInterruptFlags(FGPIO_Type *base, uint32_t mask);

/*!
 * @brief Clears the multiple FGPIO pin interrupt status flag.
 * @deprecated Do not use this function.  It has been superceded by @ref FGPIO_PortClearInterruptFlags.
 */
static inline void FGPIO_ClearPinsInterruptFlags(FGPIO_Type *base, uint32_t mask)
{
    FGPIO_PortClearInterruptFlags(base, mask);
}
#endif
#if defined(FSL_FEATURE_RGPIO_HAS_ATTRIBUTE_CHECKER) && FSL_FEATURE_RGPIO_HAS_ATTRIBUTE_CHECKER
/*!
 * @brief The FGPIO module supports a device-specific number of data ports, organized as 32-bit
 * words. Each 32-bit data port includes a GACR register, which defines the byte-level
 * attributes required for a successful access to the RGPIO programming model. The attribute controls for the 4 data
 * bytes in the GACR follow a standard little endian
 * data convention.
 *
 * @param base FGPIO peripheral base pointer (FGPIOA, FGPIOB, FGPIOC, and so on.)
 * @param mask FGPIO pin number macro
 */
void FGPIO_CheckAttributeBytes(FGPIO_Type *base, rgpio_checker_attribute_t attribute);
#endif

/*@}*/

#endif /* FSL_FEATURE_SOC_FGPIO_COUNT */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */

#endif /* _FSL_RGPIO_H_*/
