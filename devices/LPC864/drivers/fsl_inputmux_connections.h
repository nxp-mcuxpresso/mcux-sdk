/*
 * Copyright  2017 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_INPUTMUX_CONNECTIONS_
#define _FSL_INPUTMUX_CONNECTIONS_

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.inputmux_connections"
#endif

/*!
 * @addtogroup inputmux_driver
 * @{
 */

/*!
 * @name Input multiplexing connections
 * @{
 */

/*! @brief Periphinmux IDs */
#define DMA_OTRIG_PMUX_ID 0x00U
#define DMA_TRIG0_PMUX_ID 0x40U
#define PMUX_SHIFT        20U

/*! @brief INPUTMUX connections type */
typedef enum _inputmux_connection_t
{
    /*!< DMA OTRIG. */
    kINPUTMUX_DmaChannel0TrigoutToTriginChannels  = 0U + (DMA_OTRIG_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_DmaChannel1TrigoutToTriginChannels  = 1U + (DMA_OTRIG_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_DmaChannel2TrigoutToTriginChannels  = 2U + (DMA_OTRIG_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_DmaChannel3TrigoutToTriginChannels  = 3U + (DMA_OTRIG_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_DmaChannel4TrigoutToTriginChannels  = 4U + (DMA_OTRIG_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_DmaChannel5TrigoutToTriginChannels  = 5U + (DMA_OTRIG_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_DmaChannel6TrigoutToTriginChannels  = 6U + (DMA_OTRIG_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_DmaChannel7TrigoutToTriginChannels  = 7U + (DMA_OTRIG_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_DmaChannel8TrigoutToTriginChannels  = 8U + (DMA_OTRIG_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_DmaChannel9TrigoutToTriginChannels  = 9U + (DMA_OTRIG_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_DmaChannel10TrigoutToTriginChannels = 10U + (DMA_OTRIG_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_DmaChannel11TrigoutToTriginChannels = 11U + (DMA_OTRIG_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_DmaChannel12TrigoutToTriginChannels = 12U + (DMA_OTRIG_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_DmaChannel13TrigoutToTriginChannels = 13U + (DMA_OTRIG_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_DmaChannel14TrigoutToTriginChannels = 14U + (DMA_OTRIG_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_DmaChannel15TrigoutToTriginChannels = 15U + (DMA_OTRIG_PMUX_ID << PMUX_SHIFT),

    /*!< DMA ITRIG. */
    kINPUTMUX_GpioInt4ToDma     = 0U + (DMA_TRIG0_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_GpioInt5ToDma     = 1U + (DMA_TRIG0_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_GpioInt6ToDma     = 2U + (DMA_TRIG0_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_GpioInt7ToDma     = 3U + (DMA_TRIG0_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_Adc0SeqaIrqToDma  = 4U + (DMA_TRIG0_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_Adc0SeqbIrqToDma  = 5U + (DMA_TRIG0_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_Comp0OutToDma     = 6U + (DMA_TRIG0_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_Ftm0InitTrigToDma = 7U + (DMA_TRIG0_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_Ftm1InitTrigToDma = 8U + (DMA_TRIG0_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_Ftm0Ch0ToCh5ToDma = 9U + (DMA_TRIG0_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_Ftm1Ch0ToCh3ToDma = 10U + (DMA_TRIG0_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_SdmaTrigoutAToDma = 11U + (DMA_TRIG0_PMUX_ID << PMUX_SHIFT),
    kINPUTMUX_SdmaTrigoutBToDma = 12U + (DMA_TRIG0_PMUX_ID << PMUX_SHIFT),
} inputmux_connection_t;

/*@}*/

/*@}*/

#endif /* _FSL_INPUTMUX_CONNECTIONS_ */
