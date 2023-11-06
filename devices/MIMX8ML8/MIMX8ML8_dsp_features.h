/*
** ###################################################################
**     Version:             rev. 5.0, 2021-03-01
**     Build:               b230301
**
**     Abstract:
**         Chip specific module features.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2023 NXP
**     All rights reserved.
**
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2019-10-11)
**         Initial version.
**     - rev. 2.0 (2020-02-21)
**         Rev.B Header.
**     - rev. 3.0 (2020-06-22)
**         Rev.C Header.
**     - rev. 4.0 (2020-11-16)
**         Rev.D Header.
**     - rev. 5.0 (2021-03-01)
**         Rev.D Header Final.
**
** ###################################################################
*/

#ifndef _MIMX8ML8_dsp_FEATURES_H_
#define _MIMX8ML8_dsp_FEATURES_H_

/* SOC module features */

/* @brief AIPSTZ availability on the SoC. */
#define FSL_FEATURE_SOC_AIPSTZ_COUNT (5)
/* @brief APBH availability on the SoC. */
#define FSL_FEATURE_SOC_APBH_COUNT (1)
/* @brief ASRC availability on the SoC. */
#define FSL_FEATURE_SOC_ASRC_COUNT (1)
/* @brief BCH availability on the SoC. */
#define FSL_FEATURE_SOC_BCH_COUNT (1)
/* @brief CCM availability on the SoC. */
#define FSL_FEATURE_SOC_CCM_COUNT (1)
/* @brief CCM_ANALOG availability on the SoC. */
#define FSL_FEATURE_SOC_CCM_ANALOG_COUNT (1)
/* @brief DDRC availability on the SoC. */
#define FSL_FEATURE_SOC_DDRC_COUNT (1)
/* @brief ECSPI availability on the SoC. */
#define FSL_FEATURE_SOC_ECSPI_COUNT (3)
/* @brief EDMA availability on the SoC. */
#define FSL_FEATURE_SOC_EDMA_COUNT (1)
/* @brief ENET availability on the SoC. */
#define FSL_FEATURE_SOC_ENET_COUNT (1)
/* @brief ENET_QOS availability on the SoC. */
#define FSL_FEATURE_SOC_ENET_QOS_COUNT (1)
/* @brief FLEXCAN availability on the SoC. */
#define FSL_FEATURE_SOC_FLEXCAN_COUNT (2)
/* @brief FLEXSPI availability on the SoC. */
#define FSL_FEATURE_SOC_FLEXSPI_COUNT (1)
/* @brief GPC availability on the SoC. */
#define FSL_FEATURE_SOC_GPC_COUNT (1)
/* @brief GPC_PGC availability on the SoC. */
#define FSL_FEATURE_SOC_GPC_PGC_COUNT (1)
/* @brief GPMI availability on the SoC. */
#define FSL_FEATURE_SOC_GPMI_COUNT (1)
/* @brief GPT availability on the SoC. */
#define FSL_FEATURE_SOC_GPT_COUNT (6)
/* @brief I2S availability on the SoC. */
#define FSL_FEATURE_SOC_I2S_COUNT (6)
/* @brief IGPIO availability on the SoC. */
#define FSL_FEATURE_SOC_IGPIO_COUNT (5)
/* @brief II2C availability on the SoC. */
#define FSL_FEATURE_SOC_II2C_COUNT (6)
/* @brief IOMUXC availability on the SoC. */
#define FSL_FEATURE_SOC_IOMUXC_COUNT (1)
/* @brief IOMUXC_GPR availability on the SoC. */
#define FSL_FEATURE_SOC_IOMUXC_GPR_COUNT (1)
/* @brief IPWM availability on the SoC. */
#define FSL_FEATURE_SOC_IPWM_COUNT (4)
/* @brief IRQSTEER availability on the SoC. */
#define FSL_FEATURE_SOC_IRQSTEER_COUNT (2)
/* @brief ISI availability on the SoC. */
#define FSL_FEATURE_SOC_ISI_COUNT (1)
/* @brief IUART availability on the SoC. */
#define FSL_FEATURE_SOC_IUART_COUNT (4)
/* @brief LCDIF availability on the SoC. */
#define FSL_FEATURE_SOC_LCDIF_COUNT (3)
/* @brief MU availability on the SoC. */
#define FSL_FEATURE_SOC_MU_COUNT (1)
/* @brief NPU availability on the SoC. */
#define FSL_FEATURE_SOC_NPU_COUNT (1)
/* @brief OCOTP availability on the SoC. */
#define FSL_FEATURE_SOC_OCOTP_COUNT (1)
/* @brief PDM availability on the SoC. */
#define FSL_FEATURE_SOC_PDM_COUNT (1)
/* @brief RDC availability on the SoC. */
#define FSL_FEATURE_SOC_RDC_COUNT (1)
/* @brief RDC_SEMAPHORE availability on the SoC. */
#define FSL_FEATURE_SOC_RDC_SEMAPHORE_COUNT (2)
/* @brief SDMA availability on the SoC. */
#define FSL_FEATURE_SOC_SDMA_COUNT (3)
/* @brief SEMA4 availability on the SoC. */
#define FSL_FEATURE_SOC_SEMA4_COUNT (1)
/* @brief SNVS availability on the SoC. */
#define FSL_FEATURE_SOC_SNVS_COUNT (1)
/* @brief SPBA availability on the SoC. */
#define FSL_FEATURE_SOC_SPBA_COUNT (2)
/* @brief SRC availability on the SoC. */
#define FSL_FEATURE_SOC_SRC_COUNT (1)
/* @brief USB availability on the SoC. */
#define FSL_FEATURE_SOC_USB_COUNT (2)
/* @brief USDHC availability on the SoC. */
#define FSL_FEATURE_SOC_USDHC_COUNT (3)
/* @brief WDOG availability on the SoC. */
#define FSL_FEATURE_SOC_WDOG_COUNT (3)
/* @brief XTALOSC availability on the SoC. */
#define FSL_FEATURE_SOC_XTALOSC_COUNT (1)

/* CACHE module features */

/* @brief L1 ICACHE line size in byte. */
#define FSL_FEATURE_L1ICACHE_LINESIZE_BYTE (32)
/* @brief L1 DCACHE line size in byte. */
#define FSL_FEATURE_L1DCACHE_LINESIZE_BYTE (32)

/* CCM module features */

/* @brief Is affected by errata with ID 50235 (Incorrect clock setting for CAN affects by LPUART clock gate). */
#define FSL_FEATURE_CCM_HAS_ERRATA_50235 (0)

/* ECSPI module features */

/* @brief ECSPI Tx FIFO Size. */
#define FSL_FEATURE_ECSPI_TX_FIFO_SIZEn(x) (64)

/* EDMA module features */

/* @brief Number of DMA channels (related to number of registers TCD, DCHPRI, bit fields ERQ[ERQn], EEI[EEIn], INT[INTn], ERR[ERRn], HRS[HRSn] and bit field widths ES[ERRCHN], CEEI[CEEI], SEEI[SEEI], CERQ[CERQ], SERQ[SERQ], CDNE[CDNE], SSRT[SSRT], CERR[CERR], CINT[CINT], TCDn_CITER_ELINKYES[LINKCH], TCDn_CSR[MAJORLINKCH], TCDn_BITER_ELINKYES[LINKCH]). (Valid only for eDMA modules.) */
#define FSL_FEATURE_EDMA_MODULE_CHANNEL (32)
/* @brief Total number of DMA channels on all modules. */
#define FSL_FEATURE_EDMA_DMAMUX_CHANNELS (32)
/* @brief Number of DMA channel groups (register bit fields CR[ERGA], CR[GRPnPRI], ES[GPE], DCHPRIn[GRPPRI]). (Valid only for eDMA modules.) */
#define FSL_FEATURE_EDMA_CHANNEL_GROUP_COUNT (1)
/* @brief Has DMA_Error interrupt vector. */
#define FSL_FEATURE_EDMA_HAS_ERROR_IRQ (1)
/* @brief Number of DMA channels with asynchronous request capability (register EARS). (Valid only for eDMA modules.) */
#define FSL_FEATURE_EDMA_ASYNCHRO_REQUEST_CHANNEL_COUNT (32)
/* @brief If channel clock controlled independently */
#define FSL_FEATURE_EDMA_CHANNEL_HAS_OWN_CLOCK_GATE (1)
/* @brief Number of channel for each EDMA instance, (only defined for soc with different channel numbers for difference instance) */
#define FSL_FEATURE_EDMA_INSTANCE_CHANNELn(x) (32)
/* @brief Has no register bit fields MP_CSR[EBW]. */
#define FSL_FEATURE_EDMA_HAS_NO_MP_CSR_EBW (1)
/* @brief If dma has channel mux */
#define FSL_FEATURE_EDMA_HAS_CHANNEL_MUX (0)
/* @brief If dma has common clock gate */
#define FSL_FEATURE_EDMA_HAS_COMMON_CLOCK_GATE (0)
/* @brief If dma channel IRQ support parameter */
#define FSL_FEATURE_EDMA_MODULE_CHANNEL_IRQ_ENTRY_SUPPORT_PARAMETER (0)
/* @brief If 8 bytes transfer supported. */
#define FSL_FEATURE_EDMA_SUPPORT_8_BYTES_TRANSFER (1)
/* @brief If 16 bytes transfer supported. */
#define FSL_FEATURE_EDMA_SUPPORT_16_BYTES_TRANSFER (1)
/* @brief If 64 bytes transfer supported. */
#define FSL_FEATURE_EDMA_SUPPORT_64_BYTES_TRANSFER (1)
/* @brief Has no register bit fields CH_SBR[ATTR]. */
#define FSL_FEATURE_EDMA_HAS_NO_CH_SBR_ATTR (1)

/* ENET module features */

/* @brief Support Interrupt Coalesce */
#define FSL_FEATURE_ENET_HAS_INTERRUPT_COALESCE (1)
/* @brief Queue Size. */
#define FSL_FEATURE_ENET_QUEUE (3)
/* @brief Has AVB Support. */
#define FSL_FEATURE_ENET_HAS_AVB (1)
/* @brief Has Timer Pulse Width control. */
#define FSL_FEATURE_ENET_HAS_TIMER_PWCONTROL (0)
/* @brief Has Extend MDIO Support. */
#define FSL_FEATURE_ENET_HAS_EXTEND_MDIO (1)
/* @brief Has Additional 1588 Timer Channel Interrupt. */
#define FSL_FEATURE_ENET_HAS_ADD_1588_TIMER_CHN_INT (1)
/* @brief Support Interrupt Coalesce for each instance */
#define FSL_FEATURE_ENET_INSTANCE_HAS_INTERRUPT_COALESCEn(x) (1)
/* @brief Queue Size for each instance. */
#define FSL_FEATURE_ENET_INSTANCE_QUEUEn(x) (3)
/* @brief Has AVB Support for each instance. */
#define FSL_FEATURE_ENET_INSTANCE_HAS_AVBn(x) (1)
/* @brief Has Timer Pulse Width control for each instance. */
#define FSL_FEATURE_ENET_INSTANCE_HAS_TIMER_PWCONTROLn(x) (0)
/* @brief Has Extend MDIO Support for each instance. */
#define FSL_FEATURE_ENET_INSTANCE_HAS_EXTEND_MDIOn(x) (1)
/* @brief Has Additional 1588 Timer Channel Interrupt for each instance. */
#define FSL_FEATURE_ENET_INSTANCE_HAS_ADD_1588_TIMER_CHN_INTn(x) (1)
/* @brief Has threshold for the number of frames in the receive FIFO (register bit field RSEM[STAT_SECTION_EMPTY]). */
#define FSL_FEATURE_ENET_HAS_RECEIVE_STATUS_THRESHOLD (1)
/* @brief Has trasfer clock delay (register bit field ECR[TXC_DLY]). */
#define FSL_FEATURE_ENET_HAS_RGMII_TXC_DELAY (1)
/* @brief Has receive clock delay (register bit field ECR[RXC_DLY]). */
#define FSL_FEATURE_ENET_HAS_RGMII_RXC_DELAY (1)
/* @brief PTP Timestamp CAPTURE bit always returns 0 when the capture is not over. */
#define FSL_FEATURE_ENET_TIMESTAMP_CAPTURE_BIT_INVALID (0)
/* @brief ENET Has Extra Clock Gate.(RW610). */
#define FSL_FEATURE_ENET_HAS_EXTRA_CLOCK_GATE (0)

/* ENET_QOS module features */

/* No feature definitions */

/* FLEXCAN module features */

/* @brief Message buffer size */
#define FSL_FEATURE_FLEXCAN_HAS_MESSAGE_BUFFER_MAX_NUMBERn(x) (64)
/* @brief Has doze mode support (register bit field MCR[DOZE]). */
#define FSL_FEATURE_FLEXCAN_HAS_DOZE_MODE_SUPPORT (1)
/* @brief Insatnce has doze mode support (register bit field MCR[DOZE]). */
#define FSL_FEATURE_FLEXCAN_INSTANCE_HAS_DOZE_MODE_SUPPORTn(x) (1)
/* @brief Has a glitch filter on the receive pin (register bit field MCR[WAKSRC]). */
#define FSL_FEATURE_FLEXCAN_HAS_GLITCH_FILTER (1)
/* @brief Has extended interrupt mask and flag register (register IMASK2, IFLAG2). */
#define FSL_FEATURE_FLEXCAN_HAS_EXTENDED_FLAG_REGISTER (1)
/* @brief Instance has extended bit timing register (register CBT). */
#define FSL_FEATURE_FLEXCAN_INSTANCE_HAS_EXTENDED_TIMING_REGISTERn(x) (1)
/* @brief Has a receive FIFO DMA feature (register bit field MCR[DMA]). */
#define FSL_FEATURE_FLEXCAN_HAS_RX_FIFO_DMA (1)
/* @brief Instance has a receive FIFO DMA feature (register bit field MCR[DMA]). */
#define FSL_FEATURE_FLEXCAN_INSTANCE_HAS_RX_FIFO_DMAn(x) (1)
/* @brief Remove CAN Engine Clock Source Selection from unsupported part. */
#define FSL_FEATURE_FLEXCAN_SUPPORT_ENGINE_CLK_SEL_REMOVE (0)
/* @brief Instance remove CAN Engine Clock Source Selection from unsupported part. */
#define FSL_FEATURE_FLEXCAN_INSTANCE_SUPPORT_ENGINE_CLK_SEL_REMOVEn(x) (0)
/* @brief Is affected by errata with ID 5641 (Module does not transmit a message that is enabled to be transmitted at a specific moment during the arbitration process). */
#define FSL_FEATURE_FLEXCAN_HAS_ERRATA_5641 (0)
/* @brief Is affected by errata with ID 5829 (FlexCAN: FlexCAN does not transmit a message that is enabled to be transmitted in a specific moment during the arbitration process). */
#define FSL_FEATURE_FLEXCAN_HAS_ERRATA_5829 (0)
/* @brief Is affected by errata with ID 6032 (FlexCAN: A frame with wrong ID or payload is transmitted into the CAN bus when the Message Buffer under transmission is either aborted or deactivated while the CAN bus is in the Bus Idle state). */
#define FSL_FEATURE_FLEXCAN_HAS_ERRATA_6032 (0)
/* @brief Is affected by errata with ID 9595 (FlexCAN: Corrupt frame possible if the Freeze Mode or the Low-Power Mode are entered during a Bus-Off state). */
#define FSL_FEATURE_FLEXCAN_HAS_ERRATA_9595 (0)
/* @brief Has CAN with Flexible Data rate (CAN FD) protocol. */
#define FSL_FEATURE_FLEXCAN_HAS_FLEXIBLE_DATA_RATE (1)
/* @brief CAN instance support Flexible Data rate (CAN FD) protocol. */
#define FSL_FEATURE_FLEXCAN_INSTANCE_HAS_FLEXIBLE_DATA_RATEn(x) (1)
/* @brief Has memory error control (register MECR). */
#define FSL_FEATURE_FLEXCAN_HAS_MEMORY_ERROR_CONTROL (1)
/* @brief Init memory base 1 */
#define FSL_FEATURE_FLEXCAN_INIT_MEMORY_BASE_1 (0x80)
/* @brief Init memory size 1 */
#define FSL_FEATURE_FLEXCAN_INIT_MEMORY_SIZE_1 (0xA60)
/* @brief Init memory base 2 */
#define FSL_FEATURE_FLEXCAN_INIT_MEMORY_BASE_2 (0xF28)
/* @brief Init memory size 2 */
#define FSL_FEATURE_FLEXCAN_INIT_MEMORY_SIZE_2 (0xD8)
/* @brief Has enhanced bit timing register (register EPRS, ENCBT, EDCBT and ETDC). */
#define FSL_FEATURE_FLEXCAN_HAS_ENHANCED_BIT_TIMING_REG (0)
/* @brief Has Pretended Networking mode support. */
#define FSL_FEATURE_FLEXCAN_HAS_PN_MODE (0)
/* @brief Does not support Supervisor Mode (bitfield MCR[SUPV]. */
#define FSL_FEATURE_FLEXCAN_HAS_NO_SUPV_SUPPORT (0)

/* IGPIO module features */

/* @brief Has data register set DR_SET. */
#define FSL_FEATURE_IGPIO_HAS_DR_SET (0)
/* @brief Has data register clear DR_CLEAR. */
#define FSL_FEATURE_IGPIO_HAS_DR_CLEAR (0)
/* @brief Has data register toggle DR_TOGGLE. */
#define FSL_FEATURE_IGPIO_HAS_DR_TOGGLE (0)

/* SAI module features */

/* @brief SAI has FIFO in this soc (register bit fields TCR1[TFW]. */
#define FSL_FEATURE_SAI_HAS_FIFO (1)
/* @brief Receive/transmit FIFO size in item count (register bit fields TCSR[FRDE], TCSR[FRIE], TCSR[FRF], TCR1[TFW], RCSR[FRDE], RCSR[FRIE], RCSR[FRF], RCR1[RFW], registers TFRn, RFRn). */
#define FSL_FEATURE_SAI_FIFO_COUNTn(x) (128)
/* @brief Receive/transmit channel number (register bit fields TCR3[TCE], RCR3[RCE], registers TDRn and RDRn). */
#define FSL_FEATURE_SAI_CHANNEL_COUNTn(x) (8)
/* @brief Maximum words per frame (register bit fields TCR3[WDFL], TCR4[FRSZ], TMR[TWM], RCR3[WDFL], RCR4[FRSZ], RMR[RWM]). */
#define FSL_FEATURE_SAI_MAX_WORDS_PER_FRAME (32)
/* @brief Has support of combining multiple data channel FIFOs into single channel FIFO (register bit fields TCR3[CFR], TCR4[FCOMB], TFR0[WCP], TFR1[WCP], RCR3[CFR], RCR4[FCOMB], RFR0[RCP], RFR1[RCP]). */
#define FSL_FEATURE_SAI_HAS_FIFO_COMBINE_MODE (1)
/* @brief Has packing of 8-bit and 16-bit data into each 32-bit FIFO word (register bit fields TCR4[FPACK], RCR4[FPACK]). */
#define FSL_FEATURE_SAI_HAS_FIFO_PACKING (1)
/* @brief Configures when the SAI will continue transmitting after a FIFO error has been detected (register bit fields TCR4[FCONT], RCR4[FCONT]). */
#define FSL_FEATURE_SAI_HAS_FIFO_FUNCTION_AFTER_ERROR (1)
/* @brief Configures if the frame sync is generated internally, a frame sync is only generated when the FIFO warning flag is clear or continuously (register bit fields TCR4[ONDEM], RCR4[ONDEM]). */
#define FSL_FEATURE_SAI_HAS_ON_DEMAND_MODE (1)
/* @brief Simplified bit clock source and asynchronous/synchronous mode selection (register bit fields TCR2[CLKMODE], RCR2[CLKMODE]), in comparison with the exclusively implemented TCR2[SYNC,BCS,BCI,MSEL], RCR2[SYNC,BCS,BCI,MSEL]. */
#define FSL_FEATURE_SAI_HAS_CLOCKING_MODE (0)
/* @brief Has register for configuration of the MCLK divide ratio (register bit fields MDR[FRACT], MDR[DIVIDE]). */
#define FSL_FEATURE_SAI_HAS_MCLKDIV_REGISTER (0)
/* @brief Has register of MCR. */
#define FSL_FEATURE_SAI_HAS_MCR (1)
/* @brief Has bit field MICS of the MCR register. */
#define FSL_FEATURE_SAI_HAS_NO_MCR_MICS (1)
/* @brief Has register of MDR */
#define FSL_FEATURE_SAI_HAS_MDR (0)
/* @brief Has support the BCLK bypass mode when BCLK = MCLK. */
#define FSL_FEATURE_SAI_HAS_BCLK_BYPASS (1)
/* @brief Has DIV bit fields of MCR register (register bit fields MCR[DIV]. */
#define FSL_FEATURE_SAI_HAS_MCR_MCLK_POST_DIV (1)
/* @brief Support Channel Mode (register bit fields TCR4[CHMOD]). */
#define FSL_FEATURE_SAI_HAS_CHANNEL_MODE (1)
/* @brief SAI5 AND SAI6 SHARE ONE IRQNUMBER. */
#define FSL_FEATURE_SAI_SAI5_SAI6_SHARE_IRQ (1)

/* ISI module features */

/* No feature definitions */

/* MEMORY module features */

/* @brief Memory map has offset between subsystems. */
#define FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET (1)

/* MU module features */

/* @brief MU side for current core */
#define FSL_FEATURE_MU_SIDE_B (1)
/* @brief MU Has register CCR */
#define FSL_FEATURE_MU_HAS_CCR (0)
/* @brief MU Has register SR[RS], BSR[ARS] */
#define FSL_FEATURE_MU_HAS_SR_RS (1)
/* @brief MU Has register CR[RDIE], CR[RAIE], SR[RDIP], SR[RAIP] */
#define FSL_FEATURE_MU_HAS_RESET_INT (0)
/* @brief MU Has register SR[MURIP] */
#define FSL_FEATURE_MU_HAS_SR_MURIP (0)
/* @brief MU Has register SR[HRIP] */
#define FSL_FEATURE_MU_HAS_SR_HRIP (0)
/* @brief MU does not support enable clock of the other core, CR[CLKE] or CCR[CLKE]. */
#define FSL_FEATURE_MU_NO_CLKE (1)
/* @brief MU does not support NMI, CR[NMI]. */
#define FSL_FEATURE_MU_NO_NMI (1)
/* @brief MU does not support hold the other core reset. CR[RSTH] or CCR[RSTH]. */
#define FSL_FEATURE_MU_NO_RSTH (1)
/* @brief MU does not supports MU reset, CR[MUR]. */
#define FSL_FEATURE_MU_NO_MUR (1)
/* @brief MU does not supports hardware reset, CR[HR] or CCR[HR]. */
#define FSL_FEATURE_MU_NO_HR (1)
/* @brief MU supports mask the hardware reset. CR[HRM] or CCR[HRM]. */
#define FSL_FEATURE_MU_HAS_HRM (1)
/* @brief MU does not support check the other core power mode. SR[PM] or BSR[APM]. */
#define FSL_FEATURE_MU_NO_PM (0)
/* @brief MU supports reset assert interrupt. CR[RAIE] or BCR[RAIE]. */
#define FSL_FEATURE_MU_HAS_RESET_ASSERT_INT (0)
/* @brief MU supports reset de-assert interrupt. CR[RDIE] or BCR[RDIE]. */
#define FSL_FEATURE_MU_HAS_RESET_DEASSERT_INT (0)

/* interrupt module features */

/* @brief Lowest interrupt request number. */
#define FSL_FEATURE_INTERRUPT_IRQ_MIN (-14)
/* @brief Highest interrupt request number. */
#define FSL_FEATURE_INTERRUPT_IRQ_MAX (105)

/* PDM module features */

/* @brief PDM FIFO offset */
#define FSL_FEATURE_PDM_FIFO_OFFSET (4)
/* @brief PDM Channel Number */
#define FSL_FEATURE_PDM_CHANNEL_NUM (8)
/* @brief PDM FIFO WIDTH Size */
#define FSL_FEATURE_PDM_FIFO_WIDTH (4)
/* @brief PDM FIFO DEPTH Size */
#define FSL_FEATURE_PDM_FIFO_DEPTH (32)
/* @brief PDM has RANGE_CTRL register */
#define FSL_FEATURE_PDM_HAS_RANGE_CTRL (1)
/* @brief PDM Has Low Frequency */
#define FSL_FEATURE_PDM_HAS_STATUS_LOW_FREQ (1)
/* @brief CLKDIV factor in Medium, High and Low Quality modes */
#define FSL_FEATURE_PDM_HIGH_QUALITY_CLKDIV_FACTOR (125)
/* @brief CLKDIV factor in Very Low Quality modes */
#define FSL_FEATURE_PDM_VERY_LOW_QUALITY_CLKDIV_FACTOR (19)
/* @brief PDM Has No VADEF Bitfield In PDM VAD0_STAT Register */
#define FSL_FEATURE_PDM_HAS_NO_VADEF (0)
/* @brief PDM Has no FIR_RDY Bitfield In PDM STAT Register */
#define FSL_FEATURE_PDM_HAS_NO_FIR_RDY (1)

/* RDC module features */

/* @brief Memory address need shift when configure the RDC. */
#define FSL_FEATURE_RDC_MEM_REGION_ADDR_SHIFT (1)

/* SDMA module features */

/* @brief SDMA module channel number. */
#define FSL_FEATURE_SDMA_MODULE_CHANNEL (32)
/* @brief SDMA module event number. */
#define FSL_FEATURE_SDMA_EVENT_NUM (48)
/* @brief SDMA ROM memory to memory script start address. */
#define FSL_FEATURE_SDMA_M2M_ADDR (644)
/* @brief SDMA ROM peripheral to memory script start address. */
#define FSL_FEATURE_SDMA_P2M_ADDR (685)
/* @brief SDMA ROM memory to peripheral script start address. */
#define FSL_FEATURE_SDMA_M2P_ADDR (749)
/* @brief SDMA ROM uart to memory script start address. */
#define FSL_FEATURE_SDMA_UART2M_ADDR (819)
/* @brief SDMA ROM peripheral on SPBA to memory script start address. */
#define FSL_FEATURE_SDMA_SHP2M_ADDR (893)
/* @brief SDMA ROM memory to peripheral on SPBA script start address. */
#define FSL_FEATURE_SDMA_M2SHP_ADDR (962)
/* @brief SDMA ROM UART on SPBA to memory script start address. */
#define FSL_FEATURE_SDMA_UARTSH2M_ADDR (1034)
/* @brief SDMA ROM SPDIF to memory script start address. */
#define FSL_FEATURE_SDMA_SPDIF2M_ADDR (1102)
/* @brief SDMA ROM memory to SPDIF script start address. */
#define FSL_FEATURE_SDMA_M2SPDIF_ADDR (1136)
/* @brief SDMA ROM memory to MULTI_FIFO_SAI_TX script start address. */
#define FSL_FEATURE_SDMA_MULTI_FIFO_SAI_TX_ADDR (6235)
/* @brief SDMA ROM memory to MULTI_FIFO_SAI_RX script start address. */
#define FSL_FEATURE_SDMA_MULTI_FIFO_SAI_RX_ADDR (6729)

/* SEMA4 module features */

/* @brief Gate counts */
#define FSL_FEATURE_SEMA4_GATE_COUNT (16)

/* SPBA module features */

/* @brief SPBA module start address. */
#define FSL_FEATURE_SPBA_STARTn(x) \
    (((x) == SPBA1) ? (0x30800000) : \
    (((x) == SPBA2) ? (0x30C00000) : (-1)))
/* @brief SPBA module end address. */
#define FSL_FEATURE_SPBA_ENDn(x) \
    (((x) == SPBA1) ? (0x308FFFFF) : \
    (((x) == SPBA2) ? (0x30CFFFFF) : (-1)))

/* SysTick module features */

/* @brief Systick has external reference clock. */
#define FSL_FEATURE_SYSTICK_HAS_EXT_REF (0)
/* @brief Systick external reference clock is core clock divided by this value. */
#define FSL_FEATURE_SYSTICK_EXT_REF_CORE_DIV (0)

/* IUART module features */

/* @brief UART Transmit/Receive FIFO Size */
#define FSL_FEATURE_IUART_FIFO_SIZEn(x) (32)
/* @brief UART RX MUXed input selected option */
#define FSL_FEATURE_IUART_RXDMUXSEL (1)

/* USDHC module features */

/* @brief Has external DMA support (VEND_SPEC[EXT_DMA_EN]) */
#define FSL_FEATURE_USDHC_HAS_EXT_DMA (1)
/* @brief Has HS400 mode (MIX_CTRL[HS400_MODE]) */
#define FSL_FEATURE_USDHC_HAS_HS400_MODE (1)
/* @brief Has SDR50 support (HOST_CTRL_CAP[SDR50_SUPPORT]) */
#define FSL_FEATURE_USDHC_HAS_SDR50_MODE (1)
/* @brief Has SDR104 support (HOST_CTRL_CAP[SDR104_SUPPORT]) */
#define FSL_FEATURE_USDHC_HAS_SDR104_MODE (1)
/* @brief USDHC has reset control */
#define FSL_FEATURE_USDHC_HAS_RESET (0)
/* @brief USDHC has no bitfield WTMK_LVL[WR_BRST_LEN] and WTMK_LVL[RD_BRST_LEN] */
#define FSL_FEATURE_USDHC_HAS_NO_RW_BURST_LEN (1)
/* @brief If USDHC instance support 8 bit width */
#define FSL_FEATURE_USDHC_INSTANCE_SUPPORT_8_BIT_WIDTHn(x) (1)
/* @brief If USDHC instance support HS400 mode */
#define FSL_FEATURE_USDHC_INSTANCE_SUPPORT_HS400_MODEn(x) (0)
/* @brief If USDHC instance support 1v8 signal */
#define FSL_FEATURE_USDHC_INSTANCE_SUPPORT_1V8_SIGNALn(x) (1)
/* @brief Has no retuning time counter (HOST_CTRL_CAP[TIME_COUNT_RETURNING]) */
#define FSL_FEATURE_USDHC_REGISTER_HOST_CTRL_CAP_HAS_NO_RETUNING_TIME_COUNTER (1)
/* @brief Has no VSELECT bit in VEND_SPEC register */
#define FSL_FEATURE_USDHC_HAS_NO_VOLTAGE_SELECT (1)

/* IRQSTEER module features */

/* @brief Number of IRQSTEER CHn_MASK registers */
#define FSL_FEATURE_IRQSTEER_CHn_MASK_COUNT (5)
/* @brief The start IRQ index of first IRQSTEER source IRQ */
#define FSL_FEATURE_IRQSTEER_IRQ_START_INDEX (0)

#endif /* _MIMX8ML8_dsp_FEATURES_H_ */

