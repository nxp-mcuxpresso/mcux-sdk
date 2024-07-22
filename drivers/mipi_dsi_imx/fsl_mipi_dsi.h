/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_MIPI_DSI_H_
#define FSL_MIPI_DSI_H_

#include "fsl_common.h"

/*!
 * @addtogroup mipi_dsi
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
#define FSL_MIPI_DSI_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*! @} */

/*! @brief Error codes for the MIPI DSI driver. */
enum
{
    kStatus_DSI_Busy = MAKE_STATUS(kStatusGroup_MIPI_DSI, 0), /*!< DSI is busy. */
    kStatus_DSI_EccMultiBitError = MAKE_STATUS(kStatusGroup_MIPI_DSI, 1), /*!< Multibit ECC error detected in rx packet. */
    kStatus_DSI_CrcError        = MAKE_STATUS(kStatusGroup_MIPI_DSI, 2), /*!< CRC error detected in rx packet. */
    kStatus_DSI_PacketSizeError = MAKE_STATUS(kStatusGroup_MIPI_DSI, 3), /*!< Rx packet size error. */
    kStatus_DSI_EotMissingError = MAKE_STATUS(kStatusGroup_MIPI_DSI, 4), /*!< Received transmission does not end with an EoT packet. */
    kStatus_DSI_ErrorReportReceived = MAKE_STATUS(kStatusGroup_MIPI_DSI, 5), /*!< Error report package received. */
    kStatus_DSI_NotSupported        = MAKE_STATUS(kStatusGroup_MIPI_DSI, 6), /*!< The transfer type not supported. */
    kStatus_DSI_PhyError            = MAKE_STATUS(kStatusGroup_MIPI_DSI, 7), /*!< Physical layer error. */
};

/* Interrupt related definitions */
/*! @brief Status and interrupt mask of acknowledge error sent by device caused by host, belongs to interrupt group1.
 * INT_ST0 bit0-bit15 */
enum
{
    kDSI_ErrorReportSot     = (1UL << 0U), /*!< SoT error detected in device's acknowledge error report. */
    kDSI_ErrorReportSotSync = (1UL << 1U), /*!< SoT Sync error detected in device's acknowledge error report. */
    kDSI_ErrorReportEotSync = (1UL << 2U), /*!< EoT Sync error detected in device's acknowledge error report. */
    kDSI_ErrorReportEscEntryCmd =
        (1UL << 3U), /*!< Escape Mode Entry Command error detected in device's acknowledge error report. */
    kDSI_ErrorReportLpSync =
        (1UL << 4U), /*!< Low-power Transmit Sync error detected in device's acknowledge error report. */
    kDSI_ErrorReportPeriphTo =
        (1UL << 5U), /*!< Peripheral Timeout error detected in device's acknowledge error report. */
    kDSI_ErrorReportFalseControl =
        (1UL << 6U), /*!< False Control error detected in device's acknowledge error report. */
    kDSI_ErrorReportDeviceSpecific1 =
        (1UL << 7U), /*!< The deice specific error detected in device's acknowledge error report. */
    kDSI_ErrorReportEccOneBit = (1UL << 8U), /*!< Single-bit ECC error detected in device's acknowledge error report. */
    kDSI_ErrorReportEccMultiBit =
        (1UL << 9U),                         /*!< Muiti-bit ECC error detected in device's acknowledge error report. */
    kDSI_ErrorReportChecksum = (1UL << 10U), /*!< Checksum error detected in device's acknowledge error report. */
    kDSI_ErrorReportDataTypeUnrecognized =
        (1UL << 11U), /*!< DSI data type not recognized error detected in device's acknowledge error report. */
    kDSI_ErrorReportVcIdInvalid =
        (1UL << 12U), /*!< Virtual channel ID invalid error detected in device's acknowledge error report. */
    kDSI_ErrorReportTxLengthInvalid =
        (1UL << 13U), /*!< Invalid transmission length error detected in device's acknowledge error report. */
    kDSI_ErrorReportDeviceSpecific2 =
        (1UL << 14U), /*!< The deice specific error detected in device's acknowledge error report. */
    kDSI_ErrorReportProtocolViolation =
        (1UL << 15U), /*!< Protocol violation error detected in device's acknowledge error report. */

    kDSI_ErrorReportAll =
        kDSI_ErrorReportSot | kDSI_ErrorReportSotSync | kDSI_ErrorReportEotSync | kDSI_ErrorReportEscEntryCmd |
        kDSI_ErrorReportLpSync | kDSI_ErrorReportPeriphTo | kDSI_ErrorReportFalseControl |
        kDSI_ErrorReportDeviceSpecific1 | kDSI_ErrorReportEccOneBit | kDSI_ErrorReportEccMultiBit |
        kDSI_ErrorReportChecksum | kDSI_ErrorReportDataTypeUnrecognized | kDSI_ErrorReportVcIdInvalid |
        kDSI_ErrorReportTxLengthInvalid | kDSI_ErrorReportDeviceSpecific2 | kDSI_ErrorReportProtocolViolation,
};

/*! @brief Status and interrupt mask of error in phy layer, belongs to interrupt group1. INT_ST0 bit16-bit20 */
enum
{
    kDSI_PhyErrorEscEntry      = (1UL << 16U), /*!< Escape entry error from Lane 0. */
    kDSI_PhyErrorLpSync        = (1UL << 17U), /*!< Low-power data transmission synchronization error from Lane 0. */
    kDSI_PhyErrorControl       = (1UL << 18U), /*!< Control error from Lane 0. */
    kDSI_PhyErrorLp0Connection = (1UL << 19U), /*!< LP0 connection error from Lane 0. */
    kDSI_PhyErrorLp1Connection = (1UL << 20U), /*!< LP1 connection error from Lane 0. */

    kDSI_PhyErrorAll = kDSI_PhyErrorEscEntry | kDSI_PhyErrorLpSync | kDSI_PhyErrorControl | kDSI_PhyErrorLp0Connection |
                       kDSI_PhyErrorLp1Connection,
};

/*! @brief Timeout error interrupt and status, belongs to interrupt group2. INT_ST1 bit0-bit6 */
enum
{
    kDSI_TimeoutErrorHtx = (1UL << 0U), /*!< High Speed forward TX timeout detected. */
    kDSI_TimeoutErrorLrx = (1UL << 1U), /*!< Reverse Low power data receive timeout detected. */
};

/*! @brief Host receive packet error status, belongs to interrupt group2. INT_ST1 bit0-bit6 */
enum
{
    kDSI_RxErrorEccOneBit   = (1UL << 2U), /*!< ECC single bit error detected. */
    kDSI_RxErrorEccMultiBit = (1UL << 3U), /*!< ECC multi bit error detected. */
    kDSI_RxErrorCrc         = (1UL << 4U), /*!< CRC error detected. */
    kDSI_RxErrorPacketSize  = (1UL << 5U), /*!< Packet size error detected. */
    kDSI_RxErrorEotMissing  = (1UL << 6U), /*!< Host receives a transmission that does not end with an EoT packet. */

    kDSI_RxErrorAll = kDSI_RxErrorEccOneBit | kDSI_RxErrorEccMultiBit | kDSI_RxErrorCrc | kDSI_RxErrorPacketSize |
                      kDSI_RxErrorEotMissing,
};

/*! @brief Host receive error status, belongs to interrupt group2. INT_ST1 bit7-bit12 bit19? */
enum
{
    kDSI_DpiPayloadFifoOverflow =
        (1UL << 7U), /*!< During a DPI pixel line storage, the payload FIFO overflow occurs. */
    kDSI_GenericCommandFifoOverflow = (1UL << 8U),   /*!< System writes a command through the Generic interface
      while FIFO is full causing overflow. */
    kDSI_GenericPayloadFifoOverflow = (1UL << 9U),   /*!< System writes a payload data through the Generic interface
      while FIFO is full causing payload FIFO overflow. */
    kDSI_GenericPayloadFifoUnderflow = (1UL << 10U), /*!< System writes the packet header before the packet payload
     is completed loaded into the payload FIFO during a packet build causing payload FIFO underflow. */
    kDSI_GenericReadFifoUnderflow =
        (1UL << 11U), /*!< System requests data before it is fully received causing underflow. */
    kDSI_GenericReadFifoOverflow = (1UL << 12U), /*!< The Read FIFO size is not correctly dimensioned for the max
 rx packet size causing generic read FIFO overflow. */
};

/* General configuration. */
/*! @brief _dsi_dpi_package_flag Flags for DPI package composition. */
enum
{
    kDSI_DpiEnableEotpTxHs = (1U << 0U), /*!< Enables the EoTp transmission in high-speed. */
    kDSI_DpiEnableEotpRx   = (1U << 1U), /*!< Enables the EoTp reception. */
    kDSI_DpiEnableBta      = (1U << 2U), /*!< Enables the Bus Turn-Around (BTA) request. */
    kDSI_DpiEnableEcc      = (1U << 3U), /*!< Enables the ECC reception, error correction, and reporting. */
    kDSI_DpiEnableCrc      = (1U << 4U), /*!< Enables the CRC reception and error reporting. */
    kDSI_DpiEnableEotpTxLp = (1U << 5U), /*!< Enables the EoTp transmission in low-power. */

    kDSI_DpiEnableAll = kDSI_DpiEnableEotpTxHs | kDSI_DpiEnableEotpRx | kDSI_DpiEnableBta | kDSI_DpiEnableEcc |
                        kDSI_DpiEnableCrc | kDSI_DpiEnableEotpTxLp,
};

/*! @brief MIPI DSI operation mode. */
typedef enum _dsi_operation_mode
{
    kDSI_VideoMode   = 0U, /*!< Video mode. */
    kDSI_CommandMode = 1U, /*!< Command mode. */
} dsi_operation_mode_t;

/*! @brief MIPI DSI controller configuration. */
typedef struct _dsi_config
{
    dsi_operation_mode_t mode;   /*!< DSI operation mode. MODE_CFG[cmd_video_mode] */
    uint8_t packageFlags;        /*!< OR'ed value of @ref _dsi_dpi_package_flag that controls DPI package composition.
                                    PCKHDL_CFG */
    bool enableNoncontinuousClk; /*!< Enables the automatic mechanism to stop providing clock in the clock lane when
                                    time allows. LPCLK_CTRL[auto_clklane_ctrl] */
    uint16_t HsRxDeviceReady_ByteClk; /*!< The min time the display device takes to process high-speed read from master
     before it can continue doing other stuff. The timer starts when D-PHY enters stop state and measured in lane byte
     clock. HS_RD_TO_CNT[hs_rd_to_cnt] */
    uint16_t lpRxDeviceReady_ByteClk; /*!< The min time the display device takes to process low-power read from master
     before it can continue doing other stuff. The timer starts when D-PHY enters stop state and measured in lane byte
     clock. LP_RD_TO_CNT[lp_rd_to_cnt] */
    uint16_t HsTxDeviceReady_ByteClk; /*!< The min time the display device takes to process high-speed write from master
     before it can continue doing other stuff. The timer starts when D-PHY enters stop state and measured in lane byte
     clock. HS_WR_TO_CNT[hs_wr_to_cnt] */
    uint16_t lpTxDeviceReady_ByteClk; /*!< The min time the display device takes to process low-power write from master
     before it can continue doing other stuff. The timer starts when D-PHY enters stop state and measured in lane byte
     clock. LP_WR_TO_CNT[lp_wr_to_cnt] */
} dsi_config_t;

/* DPI related definitions */
/*! @brief MIPI DPI interface color coding. */
typedef enum _dsi_dpi_color_coding
{
    kDSI_DpiRGB16Bit       = 0U, /*!< 16-bit configuration 1. RGB565: XXXXXXXX_RRRRRGGG_GGGBBBBB. */
    kDSI_DpiRGB16BitLoose0 = 1U, /*!< 16-bit configuration 2. RGB565: XXXRRRRR_XXGGGGGG_XXXBBBBB. */
    kDSI_DpiRGB16BitLoose1 = 2U, /*!< 16-bit configuration 3. RGB565: XXRRRRRX_XXGGGGGG_XXBBBBBX. */
    kDSI_DpiRGB18Bit       = 3U, /*!< 18-bit configuration 1. RGB666: XXXXXXRR_RRRRGGGG_GGBBBBBB. */
    kDSI_DpiRGB18BitLoose  = 4U, /*!< 18-bit configuration 2. RGB666: XXRRRRRR_XXGGGGGG_XXBBBBBB. */
    kDSI_DpiRGB24Bit       = 5U, /*!< 24-bit configuration. RGB888: RRRRRRRR_GGGGGGGG_BBBBBBBB. */
    kDSI_DpiYCbCr20Bit     = 6U, /*!< 20-bit configuration. YCbCr422 loosely packed.
       CyCle1: YYYYYYYY_YYXXCbCbCbCb_CbCbCbCbCbCbXX, Cycle2: YYYYYYYY_YYXXCrCrCrCr_CrCrCrCrCrCrXX. */
    kDSI_DpiYCbCr24Bit = 7U,     /*!< 24-bit configuration. YCbCr422:
       CyCle1: YYYYYYYY_YYYYCbCbCbCb_CbCbCbCbCbCbCbCb, Cycle2: YYYYYYYY_YYYYCrCrCrCr_CrCrCrCrCrCrCrCr. */
    kDSI_DpiYCbCr16Bit = 8U,     /*!< 16-bit configuration. YCbCr422 loosely packed.
       CyCle1: YYYYYYYY_YYXXCbCbCbCb_CbCbCbCbCbCbXX, Cycle2: YYYYYYYY_XXXXCrCrCrCr_CrCrCrCrXXXX. */
    kDSI_DpiRGB30Bit = 9U,       /*!< 30-bit configuration. RGB10.10.10: XXRRRRRR_RRRRGGGG_GGGGGGBB_BBBBBBBB. */
    kDSI_DpiRGB36Bit = 10U,      /*!< 36-bit configuration. RGB12.12.12.
      CyCle1: XXXXXXRR_RRRRRRRR_RRGGGGGG, Cycle2: XXXXXXGG_GGGGBBBB_BBBBBBBB. */
    kDSI_DpiYCbCr12Bit = 11U,    /*!< 12-bit configuration. YCbCr420:
      CyCle1: Y1Y1Y1Y1Y1Y1Y1Y1_Y0Y0Y0Y0Y0Y0Y0Y0_CbCbCbCbCbCbCbCb, Cycle2:
      Y1Y1Y1Y1Y1Y1Y1Y1_Y0Y0Y0Y0Y0Y0Y0Y0_CrCrCrCrCrCrCrCr. */
    kDSI_DpiDcs24Bit = 12U,      /*!< 24-bit configuration with no specific coding. */
} dsi_dpi_color_coding_t;

/*! @brief _dsi_dpi_polarity_flag Flags for DPI signal polarity. */
enum
{
    kDSI_DpiDataEnableActiveHigh = 0U,         /*!< Data enable pin active high. */
    kDSI_DpiVsyncActiveHigh      = 0U,         /*!< VSYNC active high. */
    kDSI_DpiHsyncActiveHigh      = 0U,         /*!< HSYNC active high. */
    kDSI_DpiShutDownActiveHigh   = 0U,         /*!< Shutdown pin active high. */
    kDSI_DpiColorModeActiveHigh  = 0U,         /*!< Color mode pin active high. */
    kDSI_DpiDataEnableActiveLow  = (1U << 0U), /*!< Data enable pin active low. */
    kDSI_DpiVsyncActiveLow       = (1U << 1U), /*!< VSYNC active low. */
    kDSI_DpiHsyncActiveLow       = (1U << 2U), /*!< HSYNC active low. */
    kDSI_DpiShutDownActiveLow    = (1U << 3U), /*!< Shutdown pin active low. */
    kDSI_DpiColorModeActiveLow   = (1U << 4U), /*!< Color mode pin active low. */
};

/*! @brief DSI video mode. */
typedef enum _dsi_video_mode
{
    kDSI_DpiNonBurstWithSyncPulse = 0U, /*!< Non-Burst mode with Sync Pulses. */
    kDSI_DpiNonBurstWithSyncEvent = 1U, /*!< Non-Burst mode with Sync Events. */
    kDSI_DpiBurst                 = 2U, /*!< Burst mode. */
} dsi_video_mode_t;

typedef enum _dsi_video_pattern
{
    kDSI_PatternDisable    = 0U, /*!< Color bar pattern mode disabled. */
    kDSI_PatternVertical   = 1U, /*!< Color bar pattern mode displayed vertically. */
    kDSI_PatternHorizontal = 2U, /*!< Color bar pattern mode displayed horizontally. */
} dsi_video_pattern_t;

/*! @brief MIPI DSI controller DPI interface configuration. */
typedef struct _dsi_dpi_config
{
    uint8_t virtualChannel;             /*!< Virtual channel. DPI_VCID[dpi_vcid] */
    dsi_dpi_color_coding_t colorCoding; /*!< DPI color coding. DPI_COLOR_CODING */
    uint8_t polarityFlags; /*!< OR'ed value of @ref _dsi_dpi_polarity_flag that controls signal polarity. DPI_CFG_POL */
    bool enablelpSwitch; /*!< Enable return to low-power inside the VSA/VBP/VFP/VACT/HBP/HFP period when timing allows.
                            VID_MODE_CFG[bit8-13] */
    bool enableAck;      /*!< Enable the request for an acknowledge response at the end of a frame.
                            VID_MODE_CFG[frame_bta_ack_en] */
    dsi_video_mode_t videoMode;  /*!< Video mode. VID_MODE_CFG[vid_mode_type] */
    dsi_video_pattern_t pattern; /*! Color bar pattern. VID_MODE_CFG[vpg_orientation][vpg_en][vpg_mode=0] */
    uint16_t pixelPayloadSize;   /*!< The number of pixels in a single video packet. For 18-bit not loosely packed data
       types,   this number must be a multiple of 4, for YCbCr data types, it must be a multiple of 2. Recommended to set
       to the line size (in pixels). VID_PKT_SIZE */
    uint16_t vsw;                /*!< Number of lines in vertical sync width. VID_VSA_LINES */
    uint16_t vbp;                /*!< Number of lines in vertical back porch. VID_VBP_LINES */
    uint16_t vfp;                /*!< Number of lines in vertical front porch. VID_VFP_LINES */
    uint16_t panelHeight;        /*!< Number of lines in vertical active area. VID_VACTIVE_LINES */
    uint16_t hsw;                /*!< Horizontal sync width, in dpi pixel clock. VID_HSA_TIME */
    uint16_t hbp;                /*!< Horizontal back porch, in dpi pixel clock. VID_HBP_TIME */
    uint16_t hfp; /*!< Horizontal front porch, in dpi pixel clock. VID_HLINE_TIME = (hsw+hbp+hfp+width) */
} dsi_dpi_config_t;

/* command mode */
/*! @brief MIPI DSI command mode configuration. */
typedef struct _dsi_command_config
{
    uint32_t escClkFreq_Hz; /*!< Escape clock frequencey in Hz. */
    uint16_t lpRxTo_Ns;     /*!< Timeout value that triggers a low-power reception timeout contention detection.
                               TO_CNT_CFG[lprx_to_cnt] */
    uint16_t hsTxTo_Ns;     /*!< Timeout value that triggers a high-speed transmission timeout contention detection.
        In non-burst mode, the time should be larger than 1.1 times of one frame data transmission time, in burst mode it
        should be one line.     TO_CNT_CFG[hstx_to_cnt] */
    uint16_t btaTo_Ns;      /*!< The time period for which MIPI DSI host keeps the link still after completing a Bus
                               Turnaround. BTA_TO_CNT[bta_to_cnt] */
} dsi_command_config_t;

/* PHY configuration */
/*! @brief MIPI DSI D-PHY configuration. */
typedef struct _dsi_dphy_config
{
    uint8_t numLanes;            /*!< Number of lanes. The value range is from 1-4, lane 0-3. PHY_IF_CFG[n_lanes] */
    uint8_t tStopState_ByteClk;  /*!< Minimum time that the PHY controller stays in stop state before a HS transmission.
                                    TODO in what unit? PHY_IF_CFG[phy_stop_wait_time] */
    uint16_t tClkHs2Lp_ByteClk;  /*!< Maximum time that the D-PHY clock lane takes to go from high-speed
      to low-power in lane byte clock. PHY_TMR_LPCLK_CFG[phy_clkhs2lp_time] */
    uint16_t tClkLp2Hs_ByteClk;  /*!< Maximum time that the D-PHY clock lane takes to go from low-power
      to high-speed in lane byte clock. PHY_TMR_LPCLK_CFG[phy_clklp2hs_time] */
    uint16_t tDataHs2Lp_ByteClk; /*!< Maximum time that the D-PHY data lane takes to go from high-speed
     to low-power in lane byte clock. PHY_TMR_CFG[phy_hs2lp_time] */
    uint16_t tDataLp2Hs_ByteClk; /*!< Maximum time that the D-PHY data lane takes to go from low-power
     to high-speed in lane byte clock. PHY_TMR_CFG[phy_lp2hs_time] */
    uint16_t maxRead_ByteClk;    /*!< Maximum time required to perform a read command in lane byte clock.
                                    PHY_TMR_RD_CFG[max_rd_time] */
} dsi_dphy_config_t;

/* Transfer related structure */
/*! @brief DSI TX data type. */
typedef enum _dsi_tx_data_type
{
    kDSI_TxDataVsyncStart                   = 0x01U, /*!< V Sync start. */
    kDSI_TxDataVsyncEnd                     = 0x11U, /*!< V Sync end. */
    kDSI_TxDataHsyncStart                   = 0x21U, /*!< H Sync start. */
    kDSI_TxDataHsyncEnd                     = 0x31U, /*!< H Sync end. */
    kDSI_TxDataEoTp                         = 0x08U, /*!< End of transmission packet. */
    kDSI_TxDataCmOff                        = 0x02U, /*!< Color mode off. */
    kDSI_TxDataCmOn                         = 0x12U, /*!< Color mode on. */
    kDSI_TxDataShutDownPeriph               = 0x22U, /*!< Shut down peripheral. */
    kDSI_TxDataTurnOnPeriph                 = 0x32U, /*!< Turn on peripheral. */
    kDSI_TxDataGenShortWrNoParam            = 0x03U, /*!< Generic Short WRITE, no parameters. */
    kDSI_TxDataGenShortWrOneParam           = 0x13U, /*!< Generic Short WRITE, one parameter. */
    kDSI_TxDataGenShortWrTwoParam           = 0x23U, /*!< Generic Short WRITE, two parameter. */
    kDSI_TxDataGenShortRdNoParam            = 0x04U, /*!< Generic Short READ, no parameters. */
    kDSI_TxDataGenShortRdOneParam           = 0x14U, /*!< Generic Short READ, one parameter. */
    kDSI_TxDataGenShortRdTwoParam           = 0x24U, /*!< Generic Short READ, two parameter. */
    kDSI_TxDataDcsShortWrNoParam            = 0x05U, /*!< DCS Short WRITE, no parameters. */
    kDSI_TxDataDcsShortWrOneParam           = 0x15U, /*!< DCS Short WRITE, one parameter. */
    kDSI_TxDataDcsShortRdNoParam            = 0x06U, /*!< DCS Short READ, no parameters. */
    kDSI_TxDataSetMaxReturnPktSize          = 0x37U, /*!< Set the Maximum Return Packet Size. */
    kDSI_TxDataNull                         = 0x09U, /*!< Null Packet, no data. */
    kDSI_TxDataBlanking                     = 0x19U, /*!< Blanking Packet, no data. */
    kDSI_TxDataGenLongWr                    = 0x29U, /*!< Generic long write. */
    kDSI_TxDataDcsLongWr                    = 0x39U, /*!< DCS Long Write/write_LUT Command Packet. */
    kDSI_TxDataLooselyPackedPixel20BitYCbCr = 0x0CU, /*!< Loosely Packed Pixel Stream, 20-bit YCbCr, 4:2:2 Format. */
    kDSI_TxDataPackedPixel24BitYCbCr        = 0x1CU, /*!< Packed Pixel Stream, 24-bit YCbCr, 4:2:2 Format. */
    kDSI_TxDataPackedPixel16BitYCbCr        = 0x2CU, /*!< Packed Pixel Stream, 16-bit YCbCr, 4:2:2 Format. */
    kDSI_TxDataPackedPixel30BitRGB          = 0x0DU, /*!< Packed Pixel Stream, 30-bit RGB, 10-10-10 Format. */
    kDSI_TxDataPackedPixel36BitRGB          = 0x1DU, /*!< Packed Pixel Stream, 36-bit RGB, 12-12-12 Format. */
    kDSI_TxDataPackedPixel12BitYCrCb        = 0x3DU, /*!< Packed Pixel Stream, 12-bit YCbCr, 4:2:0 Format. */
    kDSI_TxDataPackedPixel16BitRGB          = 0x0EU, /*!< Packed Pixel Stream, 16-bit RGB, 5-6-5 Format. */
    kDSI_TxDataPackedPixel18BitRGB          = 0x1EU, /*!< Packed Pixel Stream, 18-bit RGB, 6-6-6 Format. */
    kDSI_TxDataLooselyPackedPixel18BitRGB   = 0x2EU, /*!< Loosely Packed Pixel Stream, 18-bit RGB, 6-6-6 Format. */
    kDSI_TxDataPackedPixel24BitRGB          = 0x3EU, /*!< Packed Pixel Stream, 24-bit RGB, 8-8-8 Format. */
} dsi_tx_data_type_t;

/*! @brief DSI RX data type. */
typedef enum _dsi_rx_data_type
{
    kDSI_RxDataAckAndErrorReport         = 0x02U, /*!< Acknowledge and Error Report */
    kDSI_RxDataEoTp                      = 0x08U, /*!< End of Transmission packet. */
    kDSI_RxDataGenShortRdResponseOneByte = 0x11U, /*!< Generic Short READ Response, 1 byte returned. */
    kDSI_RxDataGenShortRdResponseTwoByte = 0x12U, /*!< Generic Short READ Response, 2 byte returned. */
    kDSI_RxDataGenLongRdResponse         = 0x1AU, /*!< Generic Long READ Response. */
    kDSI_RxDataDcsLongRdResponse         = 0x1CU, /*!< DCS Long READ Response. */
    kDSI_RxDataDcsShortRdResponseOneByte = 0x21U, /*!< DCS Short READ Response, 1 byte returned. */
    kDSI_RxDataDcsShortRdResponseTwoByte = 0x22U, /*!< DCS Short READ Response, 2 byte returned. */
} dsi_rx_data_type_t;

/*! @brief _dsi_transfer_flags DSI transfer control flags. */
enum
{
    kDSI_TransferUseLowPower = (1U << 0U), /*!< Use low power or not. */
    kDSI_TransferPerformBTA  = (1U << 1U), /*!< Perform BTA or not at the end of a frame. */
};

/*! @brief Structure for the data transfer. */
typedef struct _dsi_transfer
{
    uint8_t virtualChannel;        /*!< Virtual channel. */
    dsi_tx_data_type_t txDataType; /*!< TX data type. */
    uint8_t flags;                 /*!< Flags to control the transfer, see _dsi_transfer_flags. */
    const uint8_t *txData;         /*!< The TX data buffer. */
    uint8_t *rxData;               /*!< The TX data buffer. */
    uint16_t txDataSize;           /*!< Size of the TX data. */
    uint16_t rxDataSize;           /*!< Size of the RX data. */
    bool sendDscCmd;               /*!< If set to true, the DCS command is specified by @ref dscCmd, otherwise
                                        the DCS command is included in the @ref txData. */
    uint8_t dscCmd;                /*!< The DCS command to send, only valid when @ref sendDscCmd is true. */
} dsi_transfer_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Gets the MIPI DSI host controller instance from peripheral base address.
 *
 * @param base MIPI DSI peripheral base address.
 * @return MIPI DSI instance.
 */
uint32_t DSI_GetInstance(MIPI_DSI_Type *base);

/*!
 * @name Controller initialization and de-initialization
 * @{
 */
/*!
 * @brief Initializes the MIPI DSI host with the user configuration.
 *
 * This function initializes the MIPI DSI host with the configuration, it should
 * be called before other MIPI DSI driver functions.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param config Pointer to the user configuration structure.
 */
void DSI_Init(MIPI_DSI_Type *base, dsi_config_t *config);

/*!
 * @brief Deinitializes an MIPI DSI host.
 *
 * This function should be called after all bother MIPI DSI driver functions.
 *
 * @param base MIPI DSI host peripheral base address.
 */
void DSI_Deinit(MIPI_DSI_Type *base);

/*!
 * @brief Gets the default configuration to initialize the MIPI DSI host.
 *
 * The default value is:
 * @code
 * config->mode = kDSI_CommandMode;
 * config->packageFlags = kDSI_DpiEnableAll;
 * config->enableNoncontinuousClk = true;
 * config->HsRxDeviceReady_ByteClk = 0U;
 * config->lpRxDeviceReady_ByteClk = 0U;
 * config->HsTxDeviceReady_ByteClk = 0U;
 * config->lpTxDeviceReady_ByteClk = 0U;
 * @endcode
 *
 * @param config Pointer to a user-defined configuration structure.
 */
void DSI_GetDefaultConfig(dsi_config_t *config);

/*!
 * @brief Calculates the D-PHY PLL dividers to generate the desired output frequency.
 *
 * The phy byte clock frequency(byte count per second) is generated by multiplying the refClkFreq_Hz,
 * the formula is as follows, m & n is configured by mediamix control block.
 *
 * desiredOutFreq_Hz = refClkFreq_Hz * (M + 2) / (N + 1).
 * M: 40 ~ 625
 * N: 0 ~ 15
 *
 * @param m Control of the feedback multiplication ratio.
 * @param n Control of the input frequency division ratio.
 * @param refClkFreq_Hz The D-PHY input reference clock frequency (REF_CLK).
 * @param desiredOutFreq_Hz Desired PLL output frequency.
 * @return The actually output frequency using the returned dividers. If can not
 * find suitable dividers, return 0.
 */
uint32_t DSI_DphyGetPllDivider(uint32_t *m, uint32_t *n, uint32_t refClkFreq_Hz, uint32_t desiredOutFreq_Hz);

/*!
 * @brief Power up the DSI
 *
 * @param base MIPI DSI host peripheral base address.
 * @retval kStatus_Success Data transfer finished with no error.
 * @retval kStatus_Timeout Transfer failed because of timeout.
 */
status_t DSI_PowerUp(MIPI_DSI_Type *base);

/*!
 * @brief Power down the DSI
 *
 * @param base MIPI DSI host peripheral base address.
 */
static inline void DSI_PowerDown(MIPI_DSI_Type *base)
{
    base->PWR_UP = 0UL;
}

/*! @} */

/*!
 * @name Interrupts and status
 * @{
 */
/*!
 * @brief Enable the interrupts.
 *
 * The interrupts to enable are passed in as OR'ed mask value of _dsi_interrupt.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param intGroup1 Interrupts to enable in group 1.
 * @param intGroup2 Interrupts to enable in group 2.
 */
static inline void DSI_EnableInterrupts(MIPI_DSI_Type *base, uint32_t intGroup1, uint32_t intGroup2)
{
    base->INT_MSK0 |= intGroup1;
    base->INT_MSK1 |= intGroup2;
}

/*!
 * @brief Disable the interrupts.
 *
 * The interrupts to disable are passed in as OR'ed mask value of _dsi_interrupt.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param intGroup1 Interrupts to disable in group 1.
 * @param intGroup2 Interrupts to disable in group 2.
 */
static inline void DSI_DisableInterrupts(MIPI_DSI_Type *base, uint32_t intGroup1, uint32_t intGroup2)
{
    base->INT_MSK0 &= ~intGroup1;
    base->INT_MSK1 &= ~intGroup2;
}

/*!
 * @brief Get and clear the interrupt status.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param intGroup1 Group 1 interrupt status.
 * @param intGroup2 Group 2 interrupt status.
 */
static inline void DSI_GetAndClearInterruptStatus(MIPI_DSI_Type *base, uint32_t *intGroup1, uint32_t *intGroup2)
{
    *intGroup2 = base->INT_ST0;
    *intGroup1 = base->INT_ST1;
}
/*! @} */

/*!
 * @name DPI
 * @{
 */
/*!
 * @brief Configure the DPI interface.
 *
 * This function sets the DPI interface configuration, it should be used in
 * video mode.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param config Pointer to the DPI interface configuration.
 * @param laneNum How may lanes in use.
 */
void DSI_SetDpiConfig(MIPI_DSI_Type *base, const dsi_dpi_config_t *config, uint8_t laneNum);
/*! @} */

/*!
 * @name Command mode
 * @{
 */
/*!
 * @brief Configures the command mode configuration.
 *
 * This function configures the timeout values for DSI command mode.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param config Pointer to the command mode configuration structure.
 * @param laneBitClkFreq_Hz Bit clock frequency in each lane.
 */
void DSI_SetCommandModeConfig(MIPI_DSI_Type *base, const dsi_command_config_t *config, uint32_t laneBitClkFreq_Hz);

/*!
 * @brief Enables the command mode.
 *
 * This function configures the timeout values for DSI command mode.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param enable true to enable command mode and disable video mode, vise versa.
 */
static inline void DSI_EnableCommandMode(MIPI_DSI_Type *base, bool enable)
{
    if (enable)
    {
        base->MODE_CFG = 1UL;
    }
    else
    {
        base->MODE_CFG = 0UL;
    }
}
/*! @} */

/*!
 * @name PHY
 * @{
 */
/*!
 * @brief Gets the default D-PHY configuration.
 *
 * Gets the default D-PHY configuration, the timing parameters are set according
 * to D-PHY specification. User can use the configuration directly, or change
 * the parameters according device specific requirements.
 *
 * @param config Pointer to the D-PHY configuration.
 * @param phyByteClkFreq_Hz Byte clock frequency.
 * @param laneNum How may lanes in use.
 */
void DSI_GetDefaultDphyConfig(dsi_dphy_config_t *config, uint32_t phyByteClkFreq_Hz, uint8_t laneNum);

/*!
 * @brief Initializes the D-PHY
 *
 * This function configures the D-PHY timing and setups the D-PHY PLL based on
 * user configuration. The default configuration can be obtained by calling the
 * function @ref DSI_GetDefaultDphyConfig.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param config Pointer to the D-PHY configuration.
 */
void DSI_InitDphy(MIPI_DSI_Type *base, const dsi_dphy_config_t *config);
/*! @} */

/*!
 * @name Bus Operation
 * @{
 */
/*!
 * @brief Configures the APB packet to send.
 *
 * This function configures the next APB packet transfer feature. After configuration,
 * user can write the payload by calling DSI_WriteTxPayload then call DSI_WriteTxHeader
 * to start the tranasfer or just call DSI_WriteTxHeader alone if it is a short packet.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param flags The transfer control flags, see ref _dsi_transfer_flags.
 */
void DSI_SetPacketControl(MIPI_DSI_Type *base, uint8_t flags);

/*!
 * @brief Writes tx header to command FIFO. This will trigger the packet transfer.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param wordCount For long packet, this is the byte count of the payload.
 *                 For short packet, this is (data1 << 8) | data0.
 * @param virtualChannel Virtual channel.
 * @param dataType The packet data type, (DI).
 */
void DSI_WriteTxHeader(MIPI_DSI_Type *base, uint16_t wordCount, uint8_t virtualChannel, dsi_tx_data_type_t dataType);

/*!
 * @brief Fills the long APB packet payload.
 *
 * Write the long packet payload to TX FIFO.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param payload Pointer to the payload.
 * @param payloadSize Payload size in byte.
 */
void DSI_WriteTxPayload(MIPI_DSI_Type *base, const uint8_t *payload, uint16_t payloadSize);

/*!
 * @brief Writes payload data to generic payload FIFO.
 *
 * Write the long packet payload to TX FIFO. This function could be used in two ways
 *
 * 1. Include the DCS command in the 1st byte of @p payload. In this case, the DCS command
 *    is the first byte of @p payload. The parameter @p sendDcsCmd is set to false,
 *    the @p dcsCmd is not used. This function is the same as @ref DSI_WriteTxPayload
 *    when used in this way.
 *
 * 2. The DCS command in not in @p payload, but specified by parameter @p dcsCmd.
 *    In this case, the parameter @p sendDcsCmd is set to true, the @p dcsCmd is the DCS
 *    command to send. The @p payload is sent after @p dcsCmd.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param payload Pointer to the payload.
 * @param payloadSize Payload size in byte.
 * @param sendDcsCmd If set to true, the DCS command is specified by @p dcsCmd,
 *       otherwise the DCS command is included in the @p payload.
 * @param dcsCmd The DCS command to send, only used when @p sendDCSCmd is true.
 */
void DSI_WriteTxPayloadExt(
    MIPI_DSI_Type *base, const uint8_t *payload, uint16_t payloadSize, bool sendDcsCmd, uint8_t dcsCmd);

/*!
 * @brief Reads the long APB packet payload.
 *
 * Read the long packet payload from RX FIFO. This function reads directly from
 * RX FIFO status. Upper layer should make sure the whole rx packet has been received.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param payload Pointer to the payload buffer.
 * @param payloadSize Payload size in byte.
 */
void DSI_ReadRxData(MIPI_DSI_Type *base, uint8_t *payload, uint16_t payloadSize);
/*! @} */

/*!
 * @name Transactional
 * @{
 */
/*!
 * @brief APB data transfer using blocking method.
 *
 * Perform APB data transfer using blocking method. This function waits until all
 * data send or received, or timeout happens.
 *
 * @param base MIPI DSI host peripheral base address.
 * @param xfer Pointer to the transfer structure.
 * @retval kStatus_Success Data transfer finished with no error.
 * @retval kStatus_Timeout Transfer failed because of timeout.
 * @retval kStatus_DSI_RxDataError RX data error, user could use ref DSI_GetRxErrorStatus
 *        to check the error details.
 * @retval kStatus_DSI_PhyError PHY error detected during transfer.
 * @retval kStatus_DSI_ErrorReportReceived Error Report packet received, user could use
 *        ref DSI_GetAndClearHostStatus to check the error report status.
 * @retval kStatus_DSI_NotSupported Transfer format not supported.
 * @retval kStatus_DSI_Fail Transfer failed for other reasons.
 */
status_t DSI_TransferBlocking(MIPI_DSI_Type *base, dsi_transfer_t *xfer);
/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* FSL_MIPI_DSI_H_ */
