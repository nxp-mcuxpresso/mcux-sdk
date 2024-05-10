/*
** ###################################################################
**     Version:             rev. 0.1, 2021-03-09
**     Build:               b240102
**
**     Abstract:
**         Chip specific module features.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2024 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 0.1 (2021-03-09)
**         Initial version.
**
** ###################################################################
*/

#ifndef _MIMXRT1189_cm7_FEATURES_H_
#define _MIMXRT1189_cm7_FEATURES_H_

/* SOC module features */

/* @brief ACMP availability on the SoC. */
#define FSL_FEATURE_SOC_ACMP_COUNT (4)
/* @brief AOI availability on the SoC. */
#define FSL_FEATURE_SOC_AOI_COUNT (4)
/* @brief ASRC availability on the SoC. */
#define FSL_FEATURE_SOC_ASRC_COUNT (1)
/* @brief AXBS availability on the SoC. */
#define FSL_FEATURE_SOC_AXBS_COUNT (1)
/* @brief BBNSM availability on the SoC. */
#define FSL_FEATURE_SOC_BBNSM_COUNT (1)
/* @brief CCM availability on the SoC. */
#define FSL_FEATURE_SOC_CCM_COUNT (1)
/* @brief DAC12 availability on the SoC. */
#define FSL_FEATURE_SOC_DAC12_COUNT (1)
/* @brief DCDC availability on the SoC. */
#define FSL_FEATURE_SOC_DCDC_COUNT (1)
/* @brief EDMA availability on the SoC. */
#define FSL_FEATURE_SOC_EDMA_COUNT (2)
/* @brief EIM availability on the SoC. */
#define FSL_FEATURE_SOC_EIM_COUNT (1)
/* @brief EQDC availability on the SoC. */
#define FSL_FEATURE_SOC_EQDC_COUNT (4)
/* @brief EWM availability on the SoC. */
#define FSL_FEATURE_SOC_EWM_COUNT (1)
/* @brief FLEXCAN availability on the SoC. */
#define FSL_FEATURE_SOC_FLEXCAN_COUNT (3)
/* @brief FLEXIO availability on the SoC. */
#define FSL_FEATURE_SOC_FLEXIO_COUNT (2)
/* @brief FLEXSPI availability on the SoC. */
#define FSL_FEATURE_SOC_FLEXSPI_COUNT (2)
/* @brief GPC availability on the SoC. */
#define FSL_FEATURE_SOC_GPC_COUNT (3)
/* @brief GPT availability on the SoC. */
#define FSL_FEATURE_SOC_GPT_COUNT (2)
/* @brief I3C availability on the SoC. */
#define FSL_FEATURE_SOC_I3C_COUNT (2)
/* @brief I2S availability on the SoC. */
#define FSL_FEATURE_SOC_I2S_COUNT (4)
/* @brief IEE availability on the SoC. */
#define FSL_FEATURE_SOC_IEE_COUNT (1)
/* @brief IOMUXC availability on the SoC. */
#define FSL_FEATURE_SOC_IOMUXC_COUNT (1)
/* @brief KPP availability on the SoC. */
#define FSL_FEATURE_SOC_KPP_COUNT (1)
/* @brief LPADC availability on the SoC. */
#define FSL_FEATURE_SOC_LPADC_COUNT (2)
/* @brief LPI2C availability on the SoC. */
#define FSL_FEATURE_SOC_LPI2C_COUNT (6)
/* @brief LPIT availability on the SoC. */
#define FSL_FEATURE_SOC_LPIT_COUNT (3)
/* @brief LPSPI availability on the SoC. */
#define FSL_FEATURE_SOC_LPSPI_COUNT (6)
/* @brief LPTMR availability on the SoC. */
#define FSL_FEATURE_SOC_LPTMR_COUNT (3)
/* @brief LPUART availability on the SoC. */
#define FSL_FEATURE_SOC_LPUART_COUNT (12)
/* @brief MU availability on the SoC. */
#define FSL_FEATURE_SOC_MU_COUNT (2)
/* @brief OCOTP availability on the SoC. */
#define FSL_FEATURE_SOC_OCOTP_COUNT (1)
/* @brief OTFAD availability on the SoC. */
#define FSL_FEATURE_SOC_OTFAD_COUNT (2)
/* @brief PDM availability on the SoC. */
#define FSL_FEATURE_SOC_PDM_COUNT (1)
/* @brief PWM availability on the SoC. */
#define FSL_FEATURE_SOC_PWM_COUNT (4)
/* @brief RGPIO availability on the SoC. */
#define FSL_FEATURE_SOC_RGPIO_COUNT (6)
/* @brief ROMC availability on the SoC. */
#define FSL_FEATURE_SOC_ROMC_COUNT (1)
/* @brief SEMA42 availability on the SoC. */
#define FSL_FEATURE_SOC_SEMA42_COUNT (2)
/* @brief SEMC availability on the SoC. */
#define FSL_FEATURE_SOC_SEMC_COUNT (1)
/* @brief SFA availability on the SoC. */
#define FSL_FEATURE_SOC_SFA_COUNT (1)
/* @brief SINC availability on the SoC. */
#define FSL_FEATURE_SOC_SINC_COUNT (3)
/* @brief SPDIF availability on the SoC. */
#define FSL_FEATURE_SOC_SPDIF_COUNT (1)
/* @brief SYSPM availability on the SoC. */
#define FSL_FEATURE_SOC_SYSPM_COUNT (2)
/* @brief TMR availability on the SoC. */
#define FSL_FEATURE_SOC_TMR_COUNT (8)
/* @brief TPM availability on the SoC. */
#define FSL_FEATURE_SOC_TPM_COUNT (6)
/* @brief TSTMR availability on the SoC. */
#define FSL_FEATURE_SOC_TSTMR_COUNT (2)
/* @brief USBHS availability on the SoC. */
#define FSL_FEATURE_SOC_USBHS_COUNT (2)
/* @brief USBHSDCD availability on the SoC. */
#define FSL_FEATURE_SOC_USBHSDCD_COUNT (2)
/* @brief USBNC availability on the SoC. */
#define FSL_FEATURE_SOC_USBNC_COUNT (2)
/* @brief USBPHY availability on the SoC. */
#define FSL_FEATURE_SOC_USBPHY_COUNT (2)
/* @brief USDHC availability on the SoC. */
#define FSL_FEATURE_SOC_USDHC_COUNT (2)
/* @brief VREF availability on the SoC. */
#define FSL_FEATURE_SOC_VREF_COUNT (1)
/* @brief XBAR_DSC availability on the SoC. */
#define FSL_FEATURE_SOC_XBAR_DSC_COUNT (3)
/* @brief ROM API Availability */
#define FSL_FEATURE_BOOT_ROM_HAS_ROMAPI (1)

/* LPADC module features */

/* @brief FIFO availability on the SoC. */
#define FSL_FEATURE_LPADC_FIFO_COUNT (2)
/* @brief Does not support two simultanious single ended conversions (bitfield TCTRL[FIFO_SEL_B]). */
#define FSL_FEATURE_LPADC_HAS_NO_TCTRL_FIFO_SEL_B (0)
/* @brief Has subsequent trigger priority (bitfield CFG[TPRICTRL]). */
#define FSL_FEATURE_LPADC_HAS_CFG_SUBSEQUENT_PRIORITY (1)
/* @brief Has differential mode (bitfield CMDLn[DIFF]). */
#define FSL_FEATURE_LPADC_HAS_CMDL_DIFF (0)
/* @brief Has channel scale (bitfield CMDLn[CSCALE]). */
#define FSL_FEATURE_LPADC_HAS_CMDL_CSCALE (1)
/* @brief Has conversion type select (bitfield CMDLn[CTYPE]). */
#define FSL_FEATURE_LPADC_HAS_CMDL_CTYPE (1)
/* @brief Has conversion resolution select  (bitfield CMDLn[MODE]). */
#define FSL_FEATURE_LPADC_HAS_CMDL_MODE (1)
/* @brief Has Wait for trigger assertion before execution (bitfield CMDHn[WAIT_TRIG]). */
#define FSL_FEATURE_LPADC_HAS_CMDH_WAIT_TRIG (1)
/* @brief Has offset calibration (bitfield CTRL[CALOFS]). */
#define FSL_FEATURE_LPADC_HAS_CTRL_CALOFS (1)
/* @brief Has gain calibration (bitfield CTRL[CAL_REQ]). */
#define FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ (1)
/* @brief Has calibration average (bitfield CTRL[CAL_AVGS]). */
#define FSL_FEATURE_LPADC_HAS_CTRL_CAL_AVGS (1)
/* @brief Has internal clock (bitfield CFG[ADCKEN]). */
#define FSL_FEATURE_LPADC_HAS_CFG_ADCKEN (0)
/* @brief Enable support for low voltage reference on option 1 reference (bitfield CFG[VREF1RNG]). */
#define FSL_FEATURE_LPADC_HAS_CFG_VREF1RNG (0)
/* @brief Has calibration (bitfield CFG[CALOFS]). */
#define FSL_FEATURE_LPADC_HAS_CFG_CALOFS (0)
/* @brief Has offset trim (register OFSTRIM). */
#define FSL_FEATURE_LPADC_HAS_OFSTRIM (0)
/* @brief Has power select (bitfield CFG[PWRSEL]). */
#define FSL_FEATURE_LPADC_HAS_CFG_PWRSEL (0)
/* @brief Has alternate channel B scale (bitfield CMDLn[ALTB_CSCALE]). */
#define FSL_FEATURE_LPADC_HAS_CMDL_ALTB_CSCALE (1)
/* @brief Has alternate channel B select enable (bitfield CMDLn[ALTBEN]). */
#define FSL_FEATURE_LPADC_HAS_CMDL_ALTBEN (1)
/* @brief Has alternate channel input (bitfield CMDLn[ALTB_ADCH]). */
#define FSL_FEATURE_LPADC_HAS_CMDL_ALTB_ADCH (1)
/* @brief Has offset calibration mode (bitfield CTRL[CALOFSMODE]). */
#define FSL_FEATURE_LPADC_HAS_CTRL_CALOFSMODE (1)
/* @brief Conversion averaged bitfiled width. */
#define FSL_FEATURE_LPADC_CONVERSIONS_AVERAGED_BITFIELD_WIDTH (4)
/* @brief Enable hardware trigger command selection */
#define FSL_FEATURE_LPADC_HAS_TCTRL_CMD_SEL (0)
/* @brief Has Trigger status register. */
#define FSL_FEATURE_LPADC_HAS_TSTAT (1)
/* @brief Has B side channels. */
#define FSL_FEATURE_LPADC_HAS_B_SIDE_CHANNELS (1)
/* @brief Indicate whether the LPADC STAT register has trigger exception interrupt function (bitfield STAT[TEXC_INT]). */
#define FSL_FEATURE_LPADC_HAS_STAT_TEXC_INT (1)
/* @brief Indicate whether the LPADC STAT register has trigger completion interrupt function (bitfield STAT[TCOMP_INT]). */
#define FSL_FEATURE_LPADC_HAS_STAT_TCOMP_INT (1)
/* @brief Indicate whether the LPADC STAT register has calibration ready function (bitfield STAT[CAL_RDY]). */
#define FSL_FEATURE_LPADC_HAS_STAT_CAL_RDY (1)
/* @brief Indicate whether the LPADC STAT register has ADC active function (bitfield STAT[ADC_ACTIVE]). */
#define FSL_FEATURE_LPADC_HAS_STAT_ADC_ACTIVE (1)
/* @brief Indicate whether the LPADC IE register has trigger exception interrupt enable function (bitfield IE[TEXC_IE]). */
#define FSL_FEATURE_LPADC_HAS_IE_TEXC_IE (1)
/* @brief Indicate whether the LPADC IE register has trigger completion interrupt enable function (bitfield IE[TCOMP_IE]). */
#define FSL_FEATURE_LPADC_HAS_IE_TCOMP_IE (1)
/* @brief Indicate whether the LPADC CFG register has trigger resume/restart enable function (bitfield CFG[TRES]). */
#define FSL_FEATURE_LPADC_HAS_CFG_TRES (1)
/* @brief Indicate whether the LPADC CFG register has trigger command resume/restart enable function (bitfield CFG[TCMDRES]). */
#define FSL_FEATURE_LPADC_HAS_CFG_TCMDRES (1)
/* @brief Indicate whether the LPADC CFG register has high priority trigger exception disable function (bitfield CFG[HPT_EXDI]). */
#define FSL_FEATURE_LPADC_HAS_CFG_HPT_EXDI (1)
/* @brief Indicate LPADC CFG register TPRICTRL bitfield width. */
#define FSL_FEATURE_LPADC_CFG_TPRICTRL_BITFIELD_WIDTH (2)
/* @brief Has compare function enable (bitfield CMDHn[CMPEN]). */
#define FSL_FEATURE_LPADC_HAS_CMDH_CMPEN (1)

/* AOI module features */

/* @brief Maximum value of input mux. */
#define FSL_FEATURE_AOI_MODULE_INPUTS (4)
/* @brief Number of events related to number of registers AOIx_BFCRT01n/AOIx_BFCRT23n. */
#define FSL_FEATURE_AOI_EVENT_COUNT (4)

/* ASRC module features */

/* @brief Register name is ASRPM or ASRPMn */
#define FSL_FEATURE_ASRC_PARAMETER_REGISTER_NAME_ASRPM (1)

/* FLEXCAN module features */

/* @brief Message buffer size */
#define FSL_FEATURE_FLEXCAN_HAS_MESSAGE_BUFFER_MAX_NUMBERn(x) (96)
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
#define FSL_FEATURE_FLEXCAN_INIT_MEMORY_BASE_2 (0xC20)
/* @brief Init memory size 2 */
#define FSL_FEATURE_FLEXCAN_INIT_MEMORY_SIZE_2 (0x25E0)
/* @brief Has enhanced bit timing register (register EPRS, ENCBT, EDCBT and ETDC). */
#define FSL_FEATURE_FLEXCAN_HAS_ENHANCED_BIT_TIMING_REG (1)
/* @brief Has Pretended Networking mode support. */
#define FSL_FEATURE_FLEXCAN_HAS_PN_MODE (0)
/* @brief Has Enhanced Rx FIFO. */
#define FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO (1)
/* @brief Enhanced Rx FIFO size (Indicates how many CAN FD messages can be stored). */
#define FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO_SIZE (20)
/* @brief The number of enhanced Rx FIFO filter element registers. */
#define FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO_FILTER_MAX_NUMBER (128)
/* @brief Does not support Supervisor Mode (bitfield MCR[SUPV]. */
#define FSL_FEATURE_FLEXCAN_HAS_NO_SUPV_SUPPORT (0)
/* @brief Has more than 64 MBs. */
#define FSL_FEATURE_FLEXCAN_HAS_MORE_THAN_64_MB (1)

/* ACMP module features */

/* @brief Has CMP_C3. */
#define FSL_FEATURE_ACMP_HAS_C3_REG (1)
/* @brief Has C0 LINKEN Bit */
#define FSL_FEATURE_ACMP_HAS_C0_LINKEN_BIT (1)
/* @brief Has C0 OFFSET Bit */
#define FSL_FEATURE_ACMP_HAS_C0_OFFSET_BIT (0)
/* @brief Has C1 INPSEL Bit */
#define FSL_FEATURE_ACMP_HAS_C1_INPSEL_BIT (0)
/* @brief Has C1 INNSEL Bit */
#define FSL_FEATURE_ACMP_HAS_C1_INNSEL_BIT (0)
/* @brief Has C1 DACOE Bit */
#define FSL_FEATURE_ACMP_HAS_C1_DACOE_BIT (0)
/* @brief Has C1 DMODE Bit */
#define FSL_FEATURE_ACMP_HAS_C1_DMODE_BIT (1)
/* @brief Has C2 RRE Bit */
#define FSL_FEATURE_ACMP_HAS_C2_RRE_BIT (0)
/* @brief Has C0 HYSTCTR Bit */
#define FSL_FEATURE_ACMP_HAS_C0_HYSTCTR_BIT (0)

/* DAC12 module features */

/* @brief Has no ITRM register. */
#define FSL_FEATURE_DAC12_HAS_NO_ITRM_REGISTER (1)
/* @brief Has hardware trigger. */
#define FSL_FEATURE_DAC12_HAS_HW_TRIGGER (1)

/* DCDC module features */

/* @brief Has CTRL register (register CTRL0/1). */
#define FSL_FEATURE_DCDC_HAS_CTRL_REG (1)
/* @brief DCDC VDD output count. */
#define FSL_FEATURE_DCDC_VDD_OUTPUT_COUNT (2)
/* @brief Has no current alert function (register bit field REG0[CURRENT_ALERT_RESET]). */
#define FSL_FEATURE_DCDC_HAS_NO_CURRENT_ALERT_FUNC (1)
/* @brief Has switching converter differential mode (register bit field REG1[LOOPCTRL_EN_DF_HYST]). */
#define FSL_FEATURE_DCDC_HAS_SWITCHING_CONVERTER_DIFFERENTIAL_MODE (1)
/* @brief Has register bit field REG0[REG_DCDC_IN_DET]. */
#define FSL_FEATURE_DCDC_HAS_REG0_DCDC_IN_DET (1)
/* @brief Has no register bit field REG0[EN_LP_OVERLOAD_SNS]. */
#define FSL_FEATURE_DCDC_HAS_NO_REG0_EN_LP_OVERLOAD_SNS (1)
/* @brief Has register bit field REG3[REG_FBK_SEL]). */
#define FSL_FEATURE_DCDC_HAS_REG3_FBK_SEL (1)

/* EDMA module features */

/* @brief Number of DMA channels (related to number of registers TCD, DCHPRI, bit fields ERQ[ERQn], EEI[EEIn], INT[INTn], ERR[ERRn], HRS[HRSn] and bit field widths ES[ERRCHN], CEEI[CEEI], SEEI[SEEI], CERQ[CERQ], SERQ[SERQ], CDNE[CDNE], SSRT[SSRT], CERR[CERR], CINT[CINT], TCDn_CITER_ELINKYES[LINKCH], TCDn_CSR[MAJORLINKCH], TCDn_BITER_ELINKYES[LINKCH]). (Valid only for eDMA modules.) */
#define FSL_FEATURE_EDMA_MODULE_CHANNEL (64)
/* @brief If 8 bytes transfer supported. */
#define FSL_FEATURE_EDMA_SUPPORT_8_BYTES_TRANSFER (1)
/* @brief Number of channel for each EDMA instance, (only defined for soc with different channel numbers for difference instance) */
#define FSL_FEATURE_EDMA_INSTANCE_CHANNELn(x) \
    (((x) == DMA4) ? (64) : \
    (((x) == DMA3) ? (32) : (-1)))
/* @brief If 16 bytes transfer supported. */
#define FSL_FEATURE_EDMA_SUPPORT_16_BYTES_TRANSFER (1)
/* @brief Number of DMA channel groups (register bit fields CR[ERGA], CR[GRPnPRI], ES[GPE], DCHPRIn[GRPPRI]). (Valid only for eDMA modules.) */
#define FSL_FEATURE_EDMA_CHANNEL_GROUP_COUNT (1)
/* @brief Has register bit fields MP_CSR[GMRC]. */
#define FSL_FEATURE_EDMA_HAS_GLOBAL_MASTER_ID_REPLICATION (1)
/* @brief If 64 bytes transfer supported. */
#define FSL_FEATURE_EDMA_SUPPORT_64_BYTES_TRANSFER (1)
/* @brief Has DMA_Error interrupt vector. */
#define FSL_FEATURE_EDMA_HAS_ERROR_IRQ (1)
/* @brief Has register bit fields CR[CLM]. */
#define FSL_FEATURE_EDMA_HAS_CONTINUOUS_LINK_MODE (0)
/* @brief If 128 bytes transfer supported. */
#define FSL_FEATURE_EDMA_SUPPORT_128_BYTES_TRANSFER (1)
/* @brief Has register access permission. */
#define FSL_FEATURE_HAVE_DMA_CONTROL_REGISTER_ACCESS_PERMISSION (0)
/* @brief NBYTES must be multiple of 8 when using scatter gather. */
#define FSL_FEATURE_EDMA_HAS_ERRATA_51327 (1)
/* @brief If 128 bytes transfer supported. */
#define FSL_FEATURE_EDMA_INSTANCE_SUPPORT_128_BYTES_TRANSFERn(x) \
    (((x) == DMA4) ? (1) : \
    (((x) == DMA3) ? (0) : (-1)))
/* @brief If channel clock controlled independently */
#define FSL_FEATURE_EDMA_CHANNEL_HAS_OWN_CLOCK_GATE (1)
/* @brief NBYTES must be multiple of 8 when using scatter gather. */
#define FSL_FEATURE_EDMA_INSTANCE_HAS_ERRATA_51327n(x) \
    (((x) == DMA4) ? (1) : \
    (((x) == DMA3) ? (0) : (-1)))
/* @brief Has register CH_CSR. */
#define FSL_FEATURE_EDMA_HAS_CHANNEL_CONFIG (1)
/* @brief Has channel mux */
#define FSL_FEATURE_EDMA_HAS_CHANNEL_MUX (1)
/* @brief Has no register bit fields MP_CSR[EBW]. */
#define FSL_FEATURE_EDMA_HAS_NO_MP_CSR_EBW (1)
/* @brief Instance has channel mux */
#define FSL_FEATURE_EDMA_INSTANCE_HAS_CHANNEL_MUXn(x) (1)
/* @brief If dma has common clock gate */
#define FSL_FEATURE_EDMA_HAS_COMMON_CLOCK_GATE (0)
/* @brief Has register CH_SBR. */
#define FSL_FEATURE_EDMA_HAS_SBR (1)
/* @brief If dma channel IRQ support parameter */
#define FSL_FEATURE_EDMA_MODULE_CHANNEL_IRQ_ENTRY_SUPPORT_PARAMETER (0)
/* @brief Has no register bit fields CH_SBR[ATTR]. */
#define FSL_FEATURE_EDMA_HAS_NO_CH_SBR_ATTR (0)
/* @brief Has register bit field CH_CSR[SWAP]. */
#define FSL_FEATURE_EDMA_HAS_CHANNEL_SWAP_SIZE (1)
/* @brief Instance has register bit field CH_CSR[SWAP]. */
#define FSL_FEATURE_EDMA_INSTANCE_HAS_CHANNEL_SWAP_SIZEn(x) \
    (((x) == DMA4) ? (1) : \
    (((x) == DMA3) ? (0) : (-1)))
/* @brief Has register bit field CH_SBR[INSTR]. */
#define FSL_FEATURE_EDMA_HAS_CHANNEL_ACCESS_TYPE (1)
/* @brief Instance has register bit field CH_SBR[INSTR]. */
#define FSL_FEATURE_EDMA_INSTANCE_HAS_CHANNEL_ACCESS_TYPEn(x) \
    (((x) == DMA4) ? (1) : \
    (((x) == DMA3) ? (0) : (-1)))
/* @brief Has register bit fields CH_MATTR[WCACHE], CH_MATTR[RCACHE]. */
#define FSL_FEATURE_EDMA_HAS_CHANNEL_MEMORY_ATTRIBUTE (1)
/* @brief Instance has register CH_MATTR. */
#define FSL_FEATURE_EDMA_INSTANCE_HAS_CHANNEL_MEMORY_ATTRIBUTEn(x) \
    (((x) == DMA4) ? (1) : \
    (((x) == DMA3) ? (0) : (-1)))
/* @brief Has register bit field CH_CSR[SIGNEXT]. */
#define FSL_FEATURE_EDMA_HAS_CHANNEL_SIGN_EXTENSION (1)
/* @brief Instance Has register bit field CH_CSR[SIGNEXT]. */
#define FSL_FEATURE_EDMA_INSTANCE_HAS_CHANNEL_SIGN_EXTENSIONn(x) \
    (((x) == DMA4) ? (1) : \
    (((x) == DMA3) ? (0) : (-1)))
/* @brief Has register bit field TCD_CSR[BWC]. */
#define FSL_FEATURE_EDMA_HAS_BANDWIDTH (1)
/* @brief Instance has register bit field TCD_CSR[BWC]. */
#define FSL_FEATURE_EDMA_INSTANCE_HAS_BANDWIDTHn(x) \
    (((x) == DMA4) ? (0) : \
    (((x) == DMA3) ? (1) : (-1)))
/* @brief Has register bit fields TCD_CSR[TMC]. */
#define FSL_FEATURE_EDMA_HAS_TRANSFER_MODE (1)
/* @brief Instance has register bit fields TCD_CSR[TMC]. */
#define FSL_FEATURE_EDMA_INSTANCE_HAS_TRANSFER_MODEn(x) \
    (((x) == DMA4) ? (1) : \
    (((x) == DMA3) ? (0) : (-1)))
/* @brief Has no register bit fields CH_SBR[SEC]. */
#define FSL_FEATURE_EDMA_HAS_NO_CH_SBR_SEC (0)

/* EQDC module features */

/* @brief Is affected by errata with ID 051383 (Quadrature decoder CTRL[DMAEN] bit can not be cleared by SW). */
#define FSL_FEATURE_EQDC_HAS_ERRATA_051383 (1)
/* @brief soc does not have compare interrupt. */
#define FSL_FEATURE_EQDC_HAS_NO_COMPARE_INTERRUPT (1)

/* EWM module features */

/* @brief Has clock select (register CLKCTRL). */
#define FSL_FEATURE_EWM_HAS_CLOCK_SELECT (1)
/* @brief Has clock prescaler (register CLKPRESCALER). */
#define FSL_FEATURE_EWM_HAS_PRESCALER (1)

/* FLEXIO module features */

/* @brief FLEXIO support reset from RSTCTL */
#define FSL_FEATURE_FLEXIO_HAS_RESET (0)
/* @brief Has Shifter Status Register (FLEXIO_SHIFTSTAT) */
#define FSL_FEATURE_FLEXIO_HAS_SHIFTER_STATUS (1)
/* @brief Has Pin Data Input Register (FLEXIO_PIN) */
#define FSL_FEATURE_FLEXIO_HAS_PIN_STATUS (1)
/* @brief Has Shifter Buffer N Nibble Byte Swapped Register (FLEXIO_SHIFTBUFNBSn) */
#define FSL_FEATURE_FLEXIO_HAS_SHFT_BUFFER_NIBBLE_BYTE_SWAP (1)
/* @brief Has Shifter Buffer N Half Word Swapped Register (FLEXIO_SHIFTBUFHWSn) */
#define FSL_FEATURE_FLEXIO_HAS_SHFT_BUFFER_HALF_WORD_SWAP (1)
/* @brief Has Shifter Buffer N Nibble Swapped Register (FLEXIO_SHIFTBUFNISn) */
#define FSL_FEATURE_FLEXIO_HAS_SHFT_BUFFER_NIBBLE_SWAP (1)
/* @brief Supports Shifter State Mode (FLEXIO_SHIFTCTLn[SMOD]) */
#define FSL_FEATURE_FLEXIO_HAS_STATE_MODE (1)
/* @brief Supports Shifter Logic Mode (FLEXIO_SHIFTCTLn[SMOD]) */
#define FSL_FEATURE_FLEXIO_HAS_LOGIC_MODE (1)
/* @brief Supports paralle width (FLEXIO_SHIFTCFGn[PWIDTH]) */
#define FSL_FEATURE_FLEXIO_HAS_PARALLEL_WIDTH (1)
/* @brief Reset value of the FLEXIO_VERID register */
#define FSL_FEATURE_FLEXIO_VERID_RESET_VALUE (0x2010003)
/* @brief Reset value of the FLEXIO_PARAM register */
#define FSL_FEATURE_FLEXIO_PARAM_RESET_VALUE (0x4200808)
/* @brief Flexio DMA request base channel */
#define FSL_FEATURE_FLEXIO_DMA_REQUEST_BASE_CHANNEL (0)
/* @brief Represent the bit width of the TIMDCE field (FLEXIO_TIMCFGLn[TIMDEC]) */
#define FSL_FEATURE_FLEXIO_TIMCFG_TIMDCE_FIELD_WIDTH (3)
/* @brief Has pin input output related registers */
#define FSL_FEATURE_FLEXIO_HAS_PIN_REGISTER (1)

/* FLEXSPI module features */

/* @brief FlexSPI AHB buffer count */
#define FSL_FEATURE_FLEXSPI_AHB_BUFFER_COUNTn(x) (8)
/* @brief FlexSPI has no data learn. */
#define FSL_FEATURE_FLEXSPI_HAS_NO_DATA_LEARN (1)
/* @brief There is AHBBUSERROREN bit in INTEN register. */
#define FSL_FEATURE_FLEXSPI_HAS_INTEN_AHBBUSERROREN (1)
/* @brief There is CLRAHBTX_RXBUF bit in AHBCR register. */
#define FSL_FEATURE_FLEXSPI_HAS_AHBCR_CLRAHBTX_RXBUF (1)
/* @brief FLEXSPI has no IP parallel mode. */
#define FSL_FEATURE_FLEXSPI_HAS_NO_IP_PARALLEL_MODE (0)
/* @brief FLEXSPI has no AHB parallel mode. */
#define FSL_FEATURE_FLEXSPI_HAS_NO_AHB_PARALLEL_MODE (0)
/* @brief FLEXSPI support address shift. */
#define FSL_FEATURE_FLEXSPI_SUPPORT_ADDRESS_SHIFT (0)
/* @brief FlexSPI has no MCR0 ARDFEN bit */
#define FSL_FEATURE_FLEXSPI_HAS_NO_MCR0_ARDFEN (0)
/* @brief FlexSPI has no MCR0 ATDFEN bit */
#define FSL_FEATURE_FLEXSPI_HAS_NO_MCR0_ATDFEN (0)
/* @brief FlexSPI has no MCR0 COMBINATIONEN bit */
#define FSL_FEATURE_FLEXSPI_HAS_NO_MCR0_COMBINATIONEN (0)
/* @brief FlexSPI has no FLSHCR4 WMENB bit */
#define FSL_FEATURE_FLEXSPI_HAS_NO_FLSHCR4_WMENB (0)
/* @brief FlexSPI has no STS0 DATALEARNPHASEB bit */
#define FSL_FEATURE_FLEXSPI_HAS_NO_STS0_DATALEARNPHASEB (1)
/* @brief FlexSPI has no MCR2 SCKBDIFFOPT bit */
#define FSL_FEATURE_FLEXSPI_HAS_NO_MCR2_SCKBDIFFOPT (0)

/* I3C module features */

/* @brief Has TERM bitfile in MERRWARN register. */
#define FSL_FEATURE_I3C_HAS_NO_MERRWARN_TERM (1)
/* @brief SOC has no reset driver. */
#define FSL_FEATURE_I3C_HAS_NO_RESET (1)
/* @brief Use fixed BAMATCH count, do not provide editable BAMATCH. */
#define FSL_FEATURE_I3C_HAS_NO_SCONFIG_BAMATCH (1)
/* @brief Register SCONFIG do not have IDRAND bitfield. */
#define FSL_FEATURE_I3C_HAS_NO_SCONFIG_IDRAND (1)
/* @brief Register SCONFIG has HDROK bitfield. */
#define FSL_FEATURE_I3C_HAS_HDROK (0)
/* @brief Has ERRATA_051617. */
#define FSL_FEATURE_I3C_HAS_ERRATA_051617 (0)
/* @brief SOC does not support slave IBI/MR/HJ */
#define FSL_FEATURE_I3C_HAS_NO_SLAVE_IBI_MR_HJ (0)
/* @brief Has ERRATA_052086. */
#define FSL_FEATURE_I3C_HAS_ERRATA_052086 (1)

/* IEE module features */

/* @brief SOC support ele provisioned. */
#define FSL_FEATURE_IEE_ELE_PROVISIONED_KEY (1)
/* @brief iee apc use GPR. */
#define FSL_FEATURE_IEE_APC_USE_GPR (0)

/* LPI2C module features */

/* @brief Has separate DMA RX and TX requests. */
#define FSL_FEATURE_LPI2C_HAS_SEPARATE_DMA_RX_TX_REQn(x) (1)
/* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
#define FSL_FEATURE_LPI2C_FIFO_SIZEn(x) (8)

/* LPIT module features */

/* @brief Number of channels (related to number of registers LDVALn, CVALn, TCTRLn, TFLGn). */
#define FSL_FEATURE_LPIT_TIMER_COUNT (4)
/* @brief Has lifetime timer (related to existence of registers LTMR64L and LTMR64H). */
#define FSL_FEATURE_LPIT_HAS_LIFETIME_TIMER (0)
/* @brief Has shared interrupt handler (has not individual interrupt handler for each channel). */
#define FSL_FEATURE_LPIT_HAS_SHARED_IRQ_HANDLER (1)

/* LPSPI module features */

/* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
#define FSL_FEATURE_LPSPI_FIFO_SIZEn(x) (16)
/* @brief Has separate DMA RX and TX requests. */
#define FSL_FEATURE_LPSPI_HAS_SEPARATE_DMA_RX_TX_REQn(x) (1)
/* @brief Has CCR1 (related to existence of registers CCR1). */
#define FSL_FEATURE_LPSPI_HAS_CCR1 (1)
/* @brief Has no PCSCFG bit in CFGR1 register. */
#define FSL_FEATURE_LPSPI_HAS_NO_PCSCFG (0)
/* @brief Has no WIDTH bits in TCR register. */
#define FSL_FEATURE_LPSPI_HAS_NO_MULTI_WIDTH (0)

/* LPTMR module features */

/* @brief Has shared interrupt handler with another LPTMR module. */
#define FSL_FEATURE_LPTMR_HAS_SHARED_IRQ_HANDLER (0)
/* @brief Whether LPTMR counter is 32 bits width. */
#define FSL_FEATURE_LPTMR_CNR_WIDTH_IS_32B (1)
/* @brief Has timer DMA request enable (register bit CSR[TDRE]). */
#define FSL_FEATURE_LPTMR_HAS_CSR_TDRE (1)
/* @brief Do not has prescaler clock source 1. */
#define FSL_FEATURE_LPTMR_HAS_NO_PRESCALER_CLOCK_SOURCE_1_SUPPORT (1)
/* @brief Do not has prescaler clock source 3. */
#define FSL_FEATURE_LPTMR_HAS_NO_PRESCALER_CLOCK_SOURCE_3_SUPPORT (1)

/* LPUART module features */

/* @brief Has receive FIFO overflow detection (bit field CFIFO[RXOFE]). */
#define FSL_FEATURE_LPUART_HAS_IRQ_EXTENDED_FUNCTIONS (0)
/* @brief Has low power features (can be enabled in wait mode via register bit C1[DOZEEN] or CTRL[DOZEEN] if the registers are 32-bit wide). */
#define FSL_FEATURE_LPUART_HAS_LOW_POWER_UART_SUPPORT (1)
/* @brief Has extended data register ED (or extra flags in the DATA register if the registers are 32-bit wide). */
#define FSL_FEATURE_LPUART_HAS_EXTENDED_DATA_REGISTER_FLAGS (1)
/* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
#define FSL_FEATURE_LPUART_HAS_FIFO (1)
/* @brief Has 32-bit register MODIR */
#define FSL_FEATURE_LPUART_HAS_MODIR (1)
/* @brief Hardware flow control (RTS, CTS) is supported. */
#define FSL_FEATURE_LPUART_HAS_MODEM_SUPPORT (1)
/* @brief Infrared (modulation) is supported. */
#define FSL_FEATURE_LPUART_HAS_IR_SUPPORT (1)
/* @brief 2 bits long stop bit is available. */
#define FSL_FEATURE_LPUART_HAS_STOP_BIT_CONFIG_SUPPORT (1)
/* @brief If 10-bit mode is supported. */
#define FSL_FEATURE_LPUART_HAS_10BIT_DATA_SUPPORT (1)
/* @brief If 7-bit mode is supported. */
#define FSL_FEATURE_LPUART_HAS_7BIT_DATA_SUPPORT (1)
/* @brief Baud rate fine adjustment is available. */
#define FSL_FEATURE_LPUART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT (0)
/* @brief Baud rate oversampling is available (has bit fields C4[OSR], C5[BOTHEDGE], C5[RESYNCDIS] or BAUD[OSR], BAUD[BOTHEDGE], BAUD[RESYNCDIS] if the registers are 32-bit wide). */
#define FSL_FEATURE_LPUART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORT (1)
/* @brief Baud rate oversampling is available. */
#define FSL_FEATURE_LPUART_HAS_RX_RESYNC_SUPPORT (1)
/* @brief Baud rate oversampling is available. */
#define FSL_FEATURE_LPUART_HAS_BOTH_EDGE_SAMPLING_SUPPORT (1)
/* @brief Peripheral type. */
#define FSL_FEATURE_LPUART_IS_SCI (1)
/* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
#define FSL_FEATURE_LPUART_FIFO_SIZEn(x) (16)
/* @brief Supports two match addresses to filter incoming frames. */
#define FSL_FEATURE_LPUART_HAS_ADDRESS_MATCHING (1)
/* @brief Has transmitter/receiver DMA enable bits C5[TDMAE]/C5[RDMAE] (or BAUD[TDMAE]/BAUD[RDMAE] if the registers are 32-bit wide). */
#define FSL_FEATURE_LPUART_HAS_DMA_ENABLE (1)
/* @brief Has transmitter/receiver DMA select bits C4[TDMAS]/C4[RDMAS], resp. C5[TDMAS]/C5[RDMAS] if IS_SCI = 0. */
#define FSL_FEATURE_LPUART_HAS_DMA_SELECT (0)
/* @brief Data character bit order selection is supported (bit field S2[MSBF] or STAT[MSBF] if the registers are 32-bit wide). */
#define FSL_FEATURE_LPUART_HAS_BIT_ORDER_SELECT (1)
/* @brief Has smart card (ISO7816 protocol) support and no improved smart card support. */
#define FSL_FEATURE_LPUART_HAS_SMART_CARD_SUPPORT (0)
/* @brief Has improved smart card (ISO7816 protocol) support. */
#define FSL_FEATURE_LPUART_HAS_IMPROVED_SMART_CARD_SUPPORT (0)
/* @brief Has local operation network (CEA709.1-B protocol) support. */
#define FSL_FEATURE_LPUART_HAS_LOCAL_OPERATION_NETWORK_SUPPORT (0)
/* @brief Has 32-bit registers (BAUD, STAT, CTRL, DATA, MATCH, MODIR) instead of 8-bit (BDH, BDL, C1, S1, D, etc.). */
#define FSL_FEATURE_LPUART_HAS_32BIT_REGISTERS (1)
/* @brief Lin break detect available (has bit BAUD[LBKDIE]). */
#define FSL_FEATURE_LPUART_HAS_LIN_BREAK_DETECT (1)
/* @brief UART stops in Wait mode available (has bit C1[UARTSWAI]). */
#define FSL_FEATURE_LPUART_HAS_WAIT_MODE_OPERATION (0)
/* @brief Has separate DMA RX and TX requests. */
#define FSL_FEATURE_LPUART_HAS_SEPARATE_DMA_RX_TX_REQn(x) (1)
/* @brief Has separate RX and TX interrupts. */
#define FSL_FEATURE_LPUART_HAS_SEPARATE_RX_TX_IRQ (0)
/* @brief Has LPAURT_PARAM. */
#define FSL_FEATURE_LPUART_HAS_PARAM (1)
/* @brief Has LPUART_VERID. */
#define FSL_FEATURE_LPUART_HAS_VERID (1)
/* @brief Has LPUART_GLOBAL. */
#define FSL_FEATURE_LPUART_HAS_GLOBAL (1)
/* @brief Has LPUART_PINCFG. */
#define FSL_FEATURE_LPUART_HAS_PINCFG (1)
/* @brief Belong to LPFLEXCOMM */
#define FSL_FEATURE_LPUART_IS_LPFLEXCOMM (0)
/* @brief Has register MODEM Control. */
#define FSL_FEATURE_LPUART_HAS_MCR (1)
/* @brief Has register Half Duplex Control. */
#define FSL_FEATURE_LPUART_HAS_HDCR (1)
/* @brief Has register Timeout. */
#define FSL_FEATURE_LPUART_HAS_TIMEOUT (1)

/* SYSPM module features */

/* @brief Temperature sensor parameter A (slope). */
#define FSL_FEATURE_SYSPM_HAS_PMCR_DCIFSH (0)
/* @brief Temperature sensor parameter B (offset). */
#define FSL_FEATURE_SYSPM_HAS_PMCR_RICTR (0)

/* MEMORY module features */

/* @brief Memory map has offset between subsystems. */
#define FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET (1)

/* MU module features */

/* @brief MU side for current core */
#define FSL_FEATURE_MU_SIDE_B (1)
/* @brief MU supports reset assert interrupt. CIER0[RAIE] or CR[RAIE] or BCR[RAIE]. */
#define FSL_FEATURE_MU_HAS_RESET_ASSERT_INT (0)
/* @brief MU supports reset de-assert interrupt. CR[RDIE] or BCR[RDIE]. */
#define FSL_FEATURE_MU_HAS_RESET_DEASSERT_INT (0)
/* @brief MU does not support core status. Register CSSR0 or CSR0. */
#define FSL_FEATURE_MU_NO_CORE_STATUS (1)
/* @brief MU does not support NMI. Register bit CCR0[NMI]. */
#define FSL_FEATURE_MU_NO_NMI (1)
/* @brief MU does not support core event pending. Register bit SR[CEP]. */
#define FSL_FEATURE_MU_NO_CEP (1)
/* @brief MU supports Power-Down mode entry interrupt. CIER0[PDIE] */
#define FSL_FEATURE_MU_HAS_PD_INT (0)
/* @brief MU supports STOP mode entry interrupt. CIER0[STOPIE] */
#define FSL_FEATURE_MU_HAS_STOP_INT (0)
/* @brief MU supports WAIT mode entry interrupt. CIER0[WAITIE] */
#define FSL_FEATURE_MU_HAS_WAIT_INT (0)
/* @brief MU supports HALT mode entry interrupt. CIER0[HALTIE] */
#define FSL_FEATURE_MU_HAS_HALT_INT (0)
/* @brief MU supports RUN mode entry interrupt. CIER0[RUNIE] */
#define FSL_FEATURE_MU_HAS_RUN_INT (0)
/* @brief MU supports hardware reset interrupt. CSSR0[HRIP] or CSR0[HRIP]. */
#define FSL_FEATURE_MU_HAS_SR_HRIP (0)
/* @brief MU supports reset interrupt. Register bit SR[MURIP]. */
#define FSL_FEATURE_MU_HAS_SR_MURIP (1)
/* @brief MU does not support enable clock of the other core, CR[CLKE] or CCR[CLKE]. */
#define FSL_FEATURE_MU_NO_CLKE (1)
/* @brief MU has bit CCR0[RSTH]. */
#define FSL_FEATURE_MU_HAS_RSTH (0)
/* @brief MU has bit CCR0[RSTH] by instance. */
#define FSL_FEATURE_MU_HAS_RSTH_BY_INSTANCEn(x) (0)
/* @brief MU has bit CCR0[BOOT]. */
#define FSL_FEATURE_MU_HAS_BOOT (0)
/* @brief MU has bit CCR0[BOOT] by instance. */
#define FSL_FEATURE_MU_HAS_BOOT_BY_INSTANCEn(x) (0)
/* @brief MU supports MU reset, CR[MUR]. */
#define FSL_FEATURE_MU_HAS_MUR (1)
/* @brief MU supports hardware reset, CR[HR] or CCR0[HR]. */
#define FSL_FEATURE_MU_HAS_HR (0)
/* @brief MU supports hardware reset by instance */
#define FSL_FEATURE_MU_HAS_HR_BY_INSTANCEn(x) (0)

/* NETC module features */

/* @brief Accesses to 64b stats registers must be performed atomically. */
#define FSL_FEATURE_NETC_HAS_ERRATA_050679 (1)
/* @brief Egress time gate scheduling can get corrupted when functional level reset is applied or when time gating is disabled. */
#define FSL_FEATURE_NETC_HAS_ERRATA_051130 (1)
/* @brief Possible transmit MAC underrun at low 10M/100M speeds when the NETC switch is operating in cut-through forwarding mode. */
#define FSL_FEATURE_NETC_HAS_ERRATA_051202 (1)
/* @brief Tx/Rx disable (POR[RXDIS] and POR[TXDIS]) are enabled out of reset. */
#define FSL_FEATURE_NETC_HAS_ERRATA_051246 (1)
/* @brief Administrative gate control list can get configured inadvertently when an exception is detected and notified. */
#define FSL_FEATURE_NETC_HAS_ERRATA_051254 (1)
/* @brief One-step timestamp support for PTP/IEEE1588 does not function properly. */
#define FSL_FEATURE_NETC_HAS_ERRATA_051255 (1)
/* @brief During initial Initialization of NETC, all ENETCs and Switch PCI functions must be enabled for NETC to accept table management commands for any function. */
#define FSL_FEATURE_NETC_HAS_ERRATA_051260 (1)
/* @brief FLR or transmit disable may cause frame transfers to underrun in MAC resulting in bad frame transmission. */
#define FSL_FEATURE_NETC_HAS_ERRATA_051398 (1)
/* @brief The Ingress Stream Identification key construction check of payload may evaluate incorrectly. */
#define FSL_FEATURE_NETC_HAS_ERRATA_051524 (1)
/* @brief Time gate scheduling update command can erroneously respond with an error when AdminBaseTime specified is near the current time. */
#define FSL_FEATURE_NETC_HAS_ERRATA_051587 (1)
/* @brief Only mapping profile instance 0 can be used. */
#define FSL_FEATURE_NETC_HAS_ERRATA_051649 (1)
/* @brief The host that is reading MAC_MERGE_MMFAECR register should check status of PM1_RFCS. */
#define FSL_FEATURE_NETC_HAS_ERRATA_051707 (1)
/* @brief After one or more late collision or excessive collision events, counters PMa_TOCTn and PMa_TFRMn will be higher than expected. */
#define FSL_FEATURE_NETC_HAS_ERRATA_051710 (1)
/* @brief MAC statistic counters TEOCT and TOCT are inaccurate after Pause frames are transmitted with flexible preamble enabled and flexible preamble count set to less than 7. */
#define FSL_FEATURE_NETC_HAS_ERRATA_051711 (1)
/* @brief Number of Switch ports. */
#define FSL_FEATURE_NETC_SWITCH_MAX_PORT_NUMBER (5)
/* @brief Number of Switch Ethernet MAC ports. */
#define FSL_FEATURE_NETC_SWITCH_ETH_PORT_NUMBER (4)
/* @brief Switch Pseudo MAC port base address. */
#define FSL_FEATURE_NETC_SWITCH_PSEUDO_PORT_BASE (0x60A14000)
/* @brief Max number of ENETC SI Tx/Rx BD rings. */
#define FSL_FEATURE_NETC_SI_RING_NUM_MAX (10)
/* @brief NETC MSI-X table base address. */
#define FSL_FEATURE_NETC_MSIX_TABLE_BASE (0x60BC0000)
/* @brief No switch support. */
#define FSL_FEATURE_NETC_HAS_NO_SWITCH (0)

/* NVIC module features */

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
#define FSL_FEATURE_PDM_FIFO_DEPTH (8)
/* @brief PDM has RANGE_CTRL register */
#define FSL_FEATURE_PDM_HAS_RANGE_CTRL (1)
/* @brief PDM Has Low Frequency */
#define FSL_FEATURE_PDM_HAS_STATUS_LOW_FREQ (1)
/* @brief CLKDIV factor in Medium, High and Low Quality modes */
#define FSL_FEATURE_PDM_HIGH_QUALITY_CLKDIV_FACTOR (93)
/* @brief CLKDIV factor in Very Low Quality modes */
#define FSL_FEATURE_PDM_VERY_LOW_QUALITY_CLKDIV_FACTOR (43)
/* @brief PDM Has DC_OUT_CTRL. */
#define FSL_FEATURE_PDM_HAS_DC_OUT_CTRL (0)
/* @brief PDM Has Fixed DC CTRL VALUE. */
#define FSL_FEATURE_PDM_DC_CTRL_VALUE_FIXED (0)
/* @brief PDM Has no independent error IRQ. */
#define FSL_FEATURE_PDM_HAS_NO_INDEPENDENT_ERROR_IRQ (0)
/* @brief PDM has no minimum clkdiv. */
#define FSL_FEATURE_PDM_HAS_NO_MINIMUM_CLKDIV (0)
/* @brief PDM Has No VADEF Bitfield In PDM VAD0_STAT Register */
#define FSL_FEATURE_PDM_HAS_NO_VADEF (1)
/* @brief PDM Has no FIR_RDY Bitfield In PDM STAT Register */
#define FSL_FEATURE_PDM_HAS_NO_FIR_RDY (0)
/* @brief PDM Has no DOZEN Bitfield In PDM CTRL_1 Register */
#define FSL_FEATURE_PDM_HAS_NO_DOZEN (0)
/* @brief PDM Has DEC_BYPASS Bitfield In PDM CTRL_2 Register */
#define FSL_FEATURE_PDM_HAS_DECIMATION_FILTER_BYPASS (0)

/* PWM module features */

/* @brief If (e)FlexPWM has module A channels (outputs). */
#define FSL_FEATURE_PWM_HAS_CHANNELA (1)
/* @brief If (e)FlexPWM has module B channels (outputs). */
#define FSL_FEATURE_PWM_HAS_CHANNELB (1)
/* @brief If (e)FlexPWM has module X channels (outputs). */
#define FSL_FEATURE_PWM_HAS_CHANNELX (1)
/* @brief If (e)FlexPWM has fractional feature. */
#define FSL_FEATURE_PWM_HAS_FRACTIONAL (1)
/* @brief If (e)FlexPWM has mux trigger source select bit field. */
#define FSL_FEATURE_PWM_HAS_MUX_TRIGGER_SOURCE_SEL (1)
/* @brief Number of submodules in each (e)FlexPWM module. */
#define FSL_FEATURE_PWM_SUBMODULE_COUNT (4)
/* @brief Number of fault channel in each (e)FlexPWM module. */
#define FSL_FEATURE_PWM_FAULT_CH_COUNT (1)
/* @brief (e)FlexPWM has no WAITEN Bitfield In CTRL2 Register. */
#define FSL_FEATURE_PWM_HAS_NO_WAITEN (1)
/* @brief If (e)FlexPWM has phase delay feature. */
#define FSL_FEATURE_PWM_HAS_PHASE_DELAY (1)
/* @brief If (e)FlexPWM has input filter capture feature. */
#define FSL_FEATURE_PWM_HAS_INPUT_FILTER_CAPTURE (1)
/* @brief If (e)FlexPWM has module capture functionality on A channels (inputs). */
#define FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELA (1)
/* @brief If (e)FlexPWM has module capture functionality on B channels (inputs). */
#define FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELB (1)
/* @brief If (e)FlexPWM has module capture functionality on X channels (inputs). */
#define FSL_FEATURE_PWM_HAS_CAPTURE_ON_CHANNELX (1)

/* RGPIO module features */

/* @brief Has GPIO attribute checker register  (GACR). */
#define FSL_FEATURE_RGPIO_HAS_ATTRIBUTE_CHECKER (0)
/* @brief GPIO registers width */
#define FSL_FEATURE_RGPIO_REGISTERS_WIDTHn(x) (32)
/* @brief There is ICR registers */
#define FSL_FEATURE_RGPIO_HAS_IRQ_CONFIG (1)
/* @brief There is PIDR register */
#define FSL_FEATURE_RGPIO_HAS_PORT_INPUT_DISABLE (1)

/* RTWDOG module features */

/* @brief Watchdog is available. */
#define FSL_FEATURE_RTWDOG_HAS_WATCHDOG (1)
/* @brief RTWDOG_CNT can be 32-bit written. */
#define FSL_FEATURE_RTWDOG_HAS_32BIT_ACCESS (1)

/* SAI module features */

/* @brief Receive/transmit FIFO size in item count (register bit fields TCSR[FRDE], TCSR[FRIE], TCSR[FRF], TCR1[TFW], RCSR[FRDE], RCSR[FRIE], RCSR[FRF], RCR1[RFW], registers TFRn, RFRn). */
#define FSL_FEATURE_SAI_FIFO_COUNTn(x) \
    (((x) == SAI1) ? (16) : \
    (((x) == SAI2) ? (32) : \
    (((x) == SAI3) ? (32) : \
    (((x) == SAI4) ? (32) : (-1)))))
/* @brief Receive/transmit channel number (register bit fields TCR3[TCE], RCR3[RCE], registers TDRn and RDRn). */
#define FSL_FEATURE_SAI_CHANNEL_COUNTn(x) \
    (((x) == SAI1) ? (2) : \
    (((x) == SAI2) ? (1) : \
    (((x) == SAI3) ? (1) : \
    (((x) == SAI4) ? (4) : (-1)))))
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
/* @brief Interrupt source number */
#define FSL_FEATURE_SAI_INT_SOURCE_NUM (1)
/* @brief Has register of MCR. */
#define FSL_FEATURE_SAI_HAS_MCR (0)
/* @brief Has bit field MICS of the MCR register. */
#define FSL_FEATURE_SAI_HAS_NO_MCR_MICS (1)
/* @brief Has register of MDR */
#define FSL_FEATURE_SAI_HAS_MDR (0)
/* @brief Has support the BCLK bypass mode when BCLK = MCLK. */
#define FSL_FEATURE_SAI_HAS_BCLK_BYPASS (1)
/* @brief Has DIV bit fields of MCR register (register bit fields MCR[DIV]). */
#define FSL_FEATURE_SAI_HAS_MCR_MCLK_POST_DIV (0)
/* @brief Support Channel Mode (register bit fields TCR4[CHMOD]). */
#define FSL_FEATURE_SAI_HAS_CHANNEL_MODE (1)
/* @brief SAI has FIFO in this soc (register bit fields TCR1[TFW]. */
#define FSL_FEATURE_SAI_HAS_FIFO (1)
/* @brief Support synchronous with another SAI. */
#define FSL_FEATURE_SAI_HAS_SYNC_WITH_ANOTHER_SAI (0)

/* SCB module features */

/* @brief L1 ICACHE line size in byte. */
#define FSL_FEATURE_L1ICACHE_LINESIZE_BYTE (32)
/* @brief L1 DCACHE line size in byte. */
#define FSL_FEATURE_L1DCACHE_LINESIZE_BYTE (32)

/* SEMA42 module features */

/* @brief Gate counts */
#define FSL_FEATURE_SEMA42_GATE_COUNT (64)

/* SEMC module features */

/* @brief Has WDH time in NOR controller (register bit field NORCR2[WDH]). */
#define FSL_FEATURE_SEMC_HAS_NOR_WDH_TIME (0)
/* @brief Has WDS time in NOR controller (register bit field NORCR2[WDS]). */
#define FSL_FEATURE_SEMC_HAS_NOR_WDS_TIME (0)
/* @brief Has LC time in NOR controller (register bit field NORCR2[LC]). */
#define FSL_FEATURE_SEMC_HAS_NOR_LC_TIME (1)
/* @brief Has RD time in NOR controller (register bit field NORCR2[RD]). */
#define FSL_FEATURE_SEMC_HAS_NOR_RD_TIME (1)
/* @brief Has WDH time in SRAM controller (register bit field SRAMCR2[WDH] or SRAMCR6[WDH]). */
#define FSL_FEATURE_SEMC_HAS_SRAM_WDH_TIME (1)
/* @brief Has WDS time in SRAM controller (register bit field SRAMCR2[WDS] or SRAMCR6[WDS]). */
#define FSL_FEATURE_SEMC_HAS_SRAM_WDS_TIME (1)
/* @brief Has LC time in SRAM controller (register bit field SRAMCR2[LC] or SRAMCR6[LC]). */
#define FSL_FEATURE_SEMC_HAS_SRAM_LC_TIME (1)
/* @brief Has RD time in SRAM controller (register bit field SRAMCR2[RD] or SRAMCR6[RD]). */
#define FSL_FEATURE_SEMC_HAS_SRAM_RD_TIME (1)
/* @brief SRAM count SEMC can support (register BRx). */
#define FSL_FEATURE_SEMC_SUPPORT_SRAM_COUNT (4)
/* @brief If SEMC support delay chain control (register DCCR). */
#define FSL_FEATURE_SEMC_HAS_DELAY_CHAIN_CONTROL (1)
/* @brief Has read hold time feature (register bit field SRAMCR2[RDH] or SRAMCR6[RDH]). */
#define FSL_FEATURE_SEMC_HAS_SRAM_RDH_TIME (1)
/* @brief Width of SDRAMCR0[PS] bitfields. */
#define FSL_FEATURE_SEMC_SUPPORT_SDRAM_PS_BITWIDTH (2)
/* @brief If SEMC has errata 050577. */
#define FSL_FEATURE_SEMC_ERRATA_050577 (0)
/* @brief If sdram support column address 8 bit (register bit field SRAMCR0[CLO8]). */
#define FSL_FEATURE_SEMC_SDRAM_SUPPORT_COLUMN_ADDRESS_8BIT (1)
/* @brief If SEMC has register DBICR2 (register DBICR2). */
#define FSL_FEATURE_SEMC_HAS_DBICR2 (1)
/* @brief SEMC supports hardware ECC on NAND flash interface. */
#define FSL_FEATURE_SEMC_HAS_NAND_HW_ECC (1)
/* @brief Has read hold time feature (register bit field SRAMCR0[SYNCEN] or SRAMCR4[SYNCEN]). */
#define FSL_FEATURE_SEMC_HAS_SRAM_SYNCEN (1)
/* @brief Has read hold time feature (register bit field SRAMCR0[WAITEN] or SRAMCR4[WAITEN]). */
#define FSL_FEATURE_SEMC_HAS_SRAM_WAITEN (1)
/* @brief Has read hold time feature (register bit field SRAMCR0[WAITSP] or SRAMCR4[WAITSP]). */
#define FSL_FEATURE_SEMC_HAS_SRAM_WAITSP (1)
/* @brief Has read hold time feature (register bit field SRAMCR0[ADVH] or SRAMCR4[ADVH]). */
#define FSL_FEATURE_SEMC_HAS_SRAM_ADVH (1)

/* SINC module features */

/* @brief SINC channel count. */
#define FSL_FEATURE_SINC_CHANNEL_COUNT (4)
/* @brief SINC CACFR register has bitfield ADMASEL. */
#define FSL_FEATURE_SINC_CACFR_HAS_ADMASEL (0)

/* SPDIF module features */

/* @brief SPDIF has no register SIC. */
#define FSL_FEATURE_SPDIF_HAS_NO_SIC_REGISTER (1)

/* TMPSNS module features */

/* @brief The basic settings for access to the temperature sensor through Analog IP (AI) Interface. */
#define FSL_FEATURE_TMPSNS_HAS_AI_INTERFACE (0)

/* TPM module features */

/* @brief Number of channels. */
#define FSL_FEATURE_TPM_CHANNEL_COUNTn(x) (4)
/* @brief Has counter reset by the selected input capture event (register bits C0SC[ICRST], C1SC[ICRST], ...). */
#define FSL_FEATURE_TPM_HAS_COUNTER_RESET_BY_CAPTURE_EVENT (0)
/* @brief Has TPM_PARAM. */
#define FSL_FEATURE_TPM_HAS_PARAM (1)
/* @brief Has TPM_VERID. */
#define FSL_FEATURE_TPM_HAS_VERID (1)
/* @brief Has TPM_GLOBAL. */
#define FSL_FEATURE_TPM_HAS_GLOBAL (1)
/* @brief Has TPM_TRIG. */
#define FSL_FEATURE_TPM_HAS_TRIG (1)
/* @brief Whether TRIG register has effect. */
#define FSL_FEATURE_TPM_TRIG_HAS_EFFECTn(x) (0)
/* @brief Has counter pause on trigger. */
#define FSL_FEATURE_TPM_HAS_PAUSE_COUNTER_ON_TRIGGER (1)
/* @brief Has external trigger selection. */
#define FSL_FEATURE_TPM_HAS_EXTERNAL_TRIGGER_SELECTION (1)
/* @brief Has TPM_COMBINE register. */
#define FSL_FEATURE_TPM_HAS_COMBINE (1)
/* @brief Whether COMBINE register has effect. */
#define FSL_FEATURE_TPM_COMBINE_HAS_EFFECTn(x) (1)
/* @brief Has TPM_POL. */
#define FSL_FEATURE_TPM_HAS_POL (1)
/* @brief Whether POL register has effect. */
#define FSL_FEATURE_TPM_POL_HAS_EFFECTn(x) (0)
/* @brief Has TPM_FILTER register. */
#define FSL_FEATURE_TPM_HAS_FILTER (1)
/* @brief Whether FILTER register has effect. */
#define FSL_FEATURE_TPM_FILTER_HAS_EFFECTn(x) (1)
/* @brief Has TPM_QDCTRL register. */
#define FSL_FEATURE_TPM_HAS_QDCTRL (1)
/* @brief Whether QDCTRL register has effect. */
#define FSL_FEATURE_TPM_QDCTRL_HAS_EFFECTn(x) (1)
/* @brief Has pause level select. */
#define FSL_FEATURE_TPM_HAS_PAUSE_LEVEL_SELECT (1)
/* @brief Whether 32 bits counter has effect. */
#define FSL_FEATURE_TPM_HAS_32BIT_COUNTERn(x) (1)

/* TRDC module features */

/* @brief Process master count. */
#define FSL_FEATURE_TRDC_PROCESSOR_MASTER_COUNT (2)
/* @brief TRDC instance has PID configuration or not. */
#define FSL_FEATURE_TRDC_INSTANCE_HAS_PID_CONFIGURATIONn(x) \
    (((x) == TRDC1) ? (1) : \
    (((x) == TRDC2) ? (0) : \
    (((x) == TRDC3) ? (0) : (-1))))
/* @brief TRDC domain number (reset value of HWCFG0[NDID]). */
#define FSL_FEATURE_TRDC_DOMAIN_COUNT (16)
/* @brief TRDC instance has MBC. */
#define FSL_FEATURE_TRDC_HAS_MBC (1)
/* @brief TRDC instance has MRC. */
#define FSL_FEATURE_TRDC_HAS_MRC (1)
/* @brief TRDC instance has TRDC_CR. */
#define FSL_FEATURE_TRDC_HAS_GENERAL_CONFIG (1)
/* @brief TRDC instance has MDA_Wx_y_DFMT. */
#define FSL_FEATURE_TRDC_HAS_DOMAIN_ASSIGNMENT (1)
/* @brief TRDC instance has TRDC_FDID. */
#define FSL_FEATURE_TRDC_HAS_DOMAIN_ERROR (1)
/* @brief TRDC instance has TRDC_FLW_CTL. */
#define FSL_FEATURE_TRDC_HAS_FLW (1)

/* TSTMR module features */

/* @brief TSTMR clock frequency is 24MHZ. */
#define FSL_FEATURE_TSTMR_CLOCK_FREQUENCY_24MHZ (1)

/* USBPHY module features */

/* @brief USBPHY contain DCD analog module */
#define FSL_FEATURE_USBPHY_HAS_DCD_ANALOG (0)
/* @brief USBPHY has register TRIM_OVERRIDE_EN */
#define FSL_FEATURE_USBPHY_HAS_TRIM_OVERRIDE_EN (1)
/* @brief USBPHY is 28FDSOI */
#define FSL_FEATURE_USBPHY_28FDSOI (1)

/* USBHS module features */

/* @brief EHCI module instance count */
#define FSL_FEATURE_USBHS_EHCI_COUNT (2)
/* @brief Number of endpoints supported */
#define FSL_FEATURE_USBHS_ENDPT_COUNT (8)
/* @brief If the USB controller support eUSB PHY */
#define FSL_FEATURE_USBHS_SUPPORT_EUSBn(x) (0)

/* USDHC module features */

/* @brief Has external DMA support (VEND_SPEC[EXT_DMA_EN]) */
#define FSL_FEATURE_USDHC_HAS_EXT_DMA (0)
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
#define FSL_FEATURE_USDHC_INSTANCE_SUPPORT_8_BIT_WIDTHn(x) \
    (((x) == USDHC1) ? (0) : \
    (((x) == USDHC2) ? (1) : (-1)))
/* @brief If USDHC instance support HS400 mode */
#define FSL_FEATURE_USDHC_INSTANCE_SUPPORT_HS400_MODEn(x) (1)
/* @brief If USDHC instance support 1v8 signal */
#define FSL_FEATURE_USDHC_INSTANCE_SUPPORT_1V8_SIGNALn(x) (1)
/* @brief Has no retuning time counter (HOST_CTRL_CAP[TIME_COUNT_RETURNING]) */
#define FSL_FEATURE_USDHC_REGISTER_HOST_CTRL_CAP_HAS_NO_RETUNING_TIME_COUNTER (1)
/* @brief Has no VSELECT bit in VEND_SPEC register */
#define FSL_FEATURE_USDHC_HAS_NO_VOLTAGE_SELECT (0)
/* @brief Has no VS18 bit in HOST_CTRL_CAP register */
#define FSL_FEATURE_USDHC_HAS_NO_VS18 (0)

#endif /* _MIMXRT1189_cm7_FEATURES_H_ */

