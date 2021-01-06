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
#define DMA_ITRIG_INMUX_ID 0x00U
#define DMA_INMUX 0x4000U
#define SCT0_INMUX_ID 0x4020U
#define PMUX_SHIFT 16U

/*! @brief INPUTMUX connections type */
typedef enum _inputmux_connection_t
{
    /*!< DMA ITRIG INMUX. */
    kINPUTMUX_AdcASeqaIrqToDma = 0U + (DMA_ITRIG_INMUX_ID << PMUX_SHIFT),
    kINPUTMUX_AdcBSeqbIrqToDma = 1U + (DMA_ITRIG_INMUX_ID << PMUX_SHIFT),
    kINPUTMUX_SctDma0ToDma = 2U + (DMA_ITRIG_INMUX_ID << PMUX_SHIFT),
    kINPUTMUX_SctDma1ToDma = 3U + (DMA_ITRIG_INMUX_ID << PMUX_SHIFT),
    kINPUTMUX_AcmpOToDma = 4U + (DMA_ITRIG_INMUX_ID << PMUX_SHIFT),
    kINPUTMUX_PinInt0ToDma = 5U + (DMA_ITRIG_INMUX_ID << PMUX_SHIFT),
    kINPUTMUX_PinInt1ToDma = 6U + (DMA_ITRIG_INMUX_ID << PMUX_SHIFT),
    kINPUTMUX_DmaTriggerMux0ToDma = 7U + (DMA_ITRIG_INMUX_ID << PMUX_SHIFT),
    kINPUTMUX_DmaTriggerMux1ToDma = 8U + (DMA_ITRIG_INMUX_ID << PMUX_SHIFT),

    /*!< DMA INMUX. */
    kINPUTMUX_DmaOut0ToDmaTriggerMux = 0U + (DMA_INMUX << PMUX_SHIFT),
    kINPUTMUX_DmaOut1ToDmaTriggerMux = 1U + (DMA_INMUX << PMUX_SHIFT),
    kINPUTMUX_DmaOut2ToDmaTriggerMux = 2U + (DMA_INMUX << PMUX_SHIFT),
    kINPUTMUX_DmaOut3ToDmaTriggerMux = 3U + (DMA_INMUX << PMUX_SHIFT),
    kINPUTMUX_DmaOut4ToDmaTriggerMux = 4U + (DMA_INMUX << PMUX_SHIFT),
    kINPUTMUX_DmaOut5ToDmaTriggerMux = 5U + (DMA_INMUX << PMUX_SHIFT),
    kINPUTMUX_DmaOut6ToDmaTriggerMux = 6U + (DMA_INMUX << PMUX_SHIFT),
    kINPUTMUX_DmaOut7ToDmaTriggerMux = 7U + (DMA_INMUX << PMUX_SHIFT),
    kINPUTMUX_DmaOut8ToDmaTriggerMux = 8U + (DMA_INMUX << PMUX_SHIFT),
    kINPUTMUX_DmaOut9ToDmaTriggerMux = 9U + (DMA_INMUX << PMUX_SHIFT),
    kINPUTMUX_DmaOut10ToDmaTriggerMux = 10U + (DMA_INMUX << PMUX_SHIFT),
    kINPUTMUX_DmaOut11ToDmaTriggerMux = 11U + (DMA_INMUX << PMUX_SHIFT),
    kINPUTMUX_DmaOut12ToDmaTriggerMux = 12U + (DMA_INMUX << PMUX_SHIFT),
    kINPUTMUX_DmaOut13ToDmaTriggerMux = 13U + (DMA_INMUX << PMUX_SHIFT),
    kINPUTMUX_DmaOut14ToDmaTriggerMux = 14U + (DMA_INMUX << PMUX_SHIFT),
    kINPUTMUX_DmaOut15ToDmaTriggerMux = 15U + (DMA_INMUX << PMUX_SHIFT),
    kINPUTMUX_DmaOut16ToDmaTriggerMux = 16U + (DMA_INMUX << PMUX_SHIFT),
    kINPUTMUX_DmaOut17ToDmaTriggerMux = 17U + (DMA_INMUX << PMUX_SHIFT),
    
    /*!< SCT INMUX. */
    kINPUTMUX_SctPin0ToSct0 = 0U + (SCT0_INMUX_ID << PMUX_SHIFT),
    kINPUTMUX_SctPin1ToSct0 = 1U + (SCT0_INMUX_ID << PMUX_SHIFT),
    kINPUTMUX_SctPin2ToSct0 = 2U + (SCT0_INMUX_ID << PMUX_SHIFT),
    kINPUTMUX_SctPin3ToSct0 = 3U + (SCT0_INMUX_ID << PMUX_SHIFT),
    kINPUTMUX_AdcThcmpIrqToSct0 = 4U + (SCT0_INMUX_ID << PMUX_SHIFT),
    kINPUTMUX_AcmpOToSct0 = 5U + (SCT0_INMUX_ID << PMUX_SHIFT),
    kINPUTMUX_ArmTxevToSct0 = 6U + (SCT0_INMUX_ID << PMUX_SHIFT),
    kINPUTMUX_DebugHaltedToSct0 =7U + (SCT0_INMUX_ID << PMUX_SHIFT),
    
} inputmux_connection_t;

/*@}*/

#endif /* _FSL_INPUTMUX_CONNECTIONS_ */
