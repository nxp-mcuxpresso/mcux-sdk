/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_XSPI_H_
#define FSL_XSPI_H_

#include "fsl_common.h"

/*!
 * @addtogroup xspi
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
#define FSL_XSPI_DRIVER_VERSION (MAKE_VERSION(2, 2, 1))
/*@{*/

/*! @brief Formula to form XSPI instructions in LUT table. */
#define XSPI_LUT_SEQ(cmd0, pad0, op0, cmd1, pad1, op1)                                            \
    (XSPI_LUT_INSTR0(cmd0) | XSPI_LUT_PAD0(pad0) | XSPI_LUT_OPRND0(op0) | XSPI_LUT_INSTR1(cmd1) | \
     XSPI_LUT_PAD1(pad1) | XSPI_LUT_OPRND1(op1))

/*! @brief Status structure of XSPI.*/
enum
{
    kStatus_XSPI_Busy                     = MAKE_STATUS(kStatusGroup_XSPI, 0),  /*!< XSPI is Busy */
    kStatus_XSPI_IpCommandUsageError      = MAKE_STATUS(kStatusGroup_XSPI, 1),  /*!< XSPI Ip Command Usage Error*/
    kStatus_XSPI_IpCommandtriggerError    = MAKE_STATUS(kStatusGroup_XSPI, 2),  /*!< XSPI Ip Command Trigger Error*/
    kStatus_XSPI_IllegalInstructionError  = MAKE_STATUS(kStatusGroup_XSPI, 3),  /*!< XSPI Illegal Instruction Error*/
    kStatus_XSPI_SequenceExecutionTimeout = MAKE_STATUS(kStatusGroup_XSPI, 4),  /*!< XSPI Sequence Execution Timeout*/
    kStatus_XSPI_FradCheckError           = MAKE_STATUS(kStatusGroup_XSPI, 5),  /*!< XSPI Frad Check Error*/
    kStatus_XSPI_TgQueueWritingError      = MAKE_STATUS(kStatusGroup_XSPI, 6),  /*!< XSPI Tg Queue Writing Error*/
    kStatus_XSPI_IpsBusTransError         = MAKE_STATUS(kStatusGroup_XSPI, 7),  /*!< XSPI Ip Bus Transfer Error*/
    kStatus_XSPI_AhbReadAccessAsserted    = MAKE_STATUS(kStatusGroup_XSPI, 8),  /*!< AHB read access is asserted. */
    kStatus_XSPI_AhbWriteAccessAsserted   = MAKE_STATUS(kStatusGroup_XSPI, 9),  /*!< AHB write access is asserted. */
    kStatus_XSPI_IPAccessAsserted         = MAKE_STATUS(kStatusGroup_XSPI, 10), /*!< IP access is asserted. */
    kStatus_XSPI_AhbSubBufferFactorError  = MAKE_STATUS(kStatusGroup_XSPI, 11), /*!< Wrong sub buffer factor input. */
    kStatus_XSPI_RegWriteLocked           = MAKE_STATUS(kStatusGroup_XSPI, 12), /*!< Fail to write register
                                                                                  due to write operation is locked. */
    kStatus_XSPI_WaterMarkIllegal = MAKE_STATUS(kStatusGroup_XSPI, 13),         /*!< The watermark value to
                                                                                set is not in multiple of 4 bytes. */
    kStatus_XSPI_PageProgramWaitFlagAsserted = MAKE_STATUS(kStatusGroup_XSPI, 14), /*!< The page program
                                                                                    wait flag already asserted. */
    kStatus_XSPI_IpAccessAddrSettingInvalid = MAKE_STATUS(kStatusGroup_XSPI, 15),  /*!< The input address for
                                                                                 Ip access is invalid. */
    kStatus_XSPI_RxBufferEntriesCountError = MAKE_STATUS(kStatusGroup_XSPI, 16),   /*!< The count of entries
                                                                               of RX buffer is incorrect. */
    kStatus_XSPI_IpAccessIPCRInvalid = MAKE_STATUS(kStatusGroup_XSPI, 17),         /*!< Access attributes to write
                                                                                        IPCR are not correct. */
};

/*! @brief CMD definition of XSPI, use to form LUT instruction, xspi_lut_instr_t. */
typedef enum _xspi_lut_instr
{
    kXSPI_Command_STOP      = 0x00U,   /*!< Stop execution, de-assert CS. */
    kXSPI_Command_SDR       = 0x01U,   /*!< Transmit Command code to Flash, using SDR mode. */
    kXSPI_Command_RADDR_SDR = 0x02U,   /*!< Transmit Row Address to Flash, using SDR mode. */
    kXSPI_Command_DUMMY_SDR = 0x03U,   /*!< Leave data lines un-driven by xSPI controller, using SDR mode. */
    kXSPI_Command_MODE_SDR  = 0x04U,   /*!< Transmit 8-bit Mode bits to Flash, using SDR mode. */
    kXSPI_Command_MODE2_SDR = 0x05U,   /*!< Transmit 2-bit Mode bits to Flash, using SDR mode. */
    kXSPI_Command_MODE4_SDR = 0x06U,   /*!< Transmit 4-bit Mode bits to Flash, using SDR mode. */
    kXSPI_Command_READ_SDR  = 0x07U,   /*!< Receive Read Data from Flash, using SDR mode. */
    kXSPI_Command_WRITE_SDR = 0x08U,   /*!< Transmit Programming Data to Flash, using SDR mode. */
    kXSPI_Command_JMP_ON_CS = 0x09U,   /*!< Stop execution, de-assert CS and save operand[7:0] as the
                                         instruction start pointer for next sequence*/
    kXSPI_Command_RADDR_DDR   = 0x0AU, /*!< Transmit Row Address to Flash, using DDR mode. */
    kXSPI_Command_MODE_DDR    = 0x0BU, /*!< Transmit 8-bit Mode bits to Flash, using DDR mode. */
    kXSPI_Command_MODE2_DDR   = 0x0CU, /*!< Transmit 2-bit Mode bits to Flash, using DDR mode. */
    kXSPI_Command_MODE4_DDR   = 0x0DU, /*!< Transmit 4-bit Mode bits to Flash, using DDR mode. */
    kXSPI_Command_READ_DDR    = 0x0EU, /*!< Receive Read Data from Flash, using DDR mode. */
    kXSPI_Command_WRITE_DDR   = 0x0FU, /*!< Transmit Programming Data to Flash, using DDR mode. */
    kXSPI_Command_LEARN_DDR   = 0x10U, /*!< Receive Read Data or Preamble bit from Flash, DDR mode. */
    kXSPI_Command_DDR         = 0x11U, /*!< Transmit Command code to Flash, using DDR mode. */
    kXSPI_Command_CADDR_SDR   = 0x12U, /*!< Transmit Column Address to Flash, using SDR mode. */
    kXSPI_Command_CADDR_DDR   = 0x13U, /*!< Transmit Column Address to Flash, using DDR mode. */
    kXSPI_Command_JUMP_TO_SEQ = 0x14U, /*!< Jump the LUT sequence pointed to by the operand. */
} xspi_lut_instr_t;

/*! @brief pad definition of XSPI, use to form LUT instruction. */
typedef enum _xspi_pad
{
    kXSPI_1PAD = 0x00U, /*!< Transmit command/address and transmit/receive data only through DATA0/DATA1. */
    kXSPI_2PAD = 0x01U, /*!< Transmit command/address and transmit/receive data only through DATA[1:0]. */
    kXSPI_4PAD = 0x02U, /*!< Transmit command/address and transmit/receive data only through DATA[3:0]. */
    kXSPI_8PAD = 0x03U, /*!< Transmit command/address and transmit/receive data only through DATA[7:0]. */
} xspi_pad_t;

/*! @brief XSPI interrupt status flags.*/
typedef enum _xspi_flags
{
    kXSPI_DataLearningFailedFlag = XSPI_FR_DLPFF_MASK,          /*!< Data learning failed. */
    kXSPI_DllAbortFlag           = XSPI_FR_DLLABRT_MASK,        /*!< DLL Abort. */
    kXSPI_DllUnlockFlag          = XSPI_FR_DLLUNLCK_MASK,       /*!< This field is set whenever DLL unlock event occurs,
                                                                  irrespective of flash memory access.*/
    kXSPI_TxBufferFillFlag = XSPI_FR_TBFF_MASK,                 /*!< If the field remains cleared,
                                                                  the TX buffer can be considered as full.*/
    kXSPI_TxBufferUnderrunFlag = XSPI_FR_TBUF_MASK,             /*!< This field is set if the module tries to pull data
                                                                  when the TX buffer is empty*/
    kXSPI_RxBufferOverflowFlag = XSPI_FR_RBOF_MASK,             /*!< This field is set when no more data can be pushed
                                                                  into the RX buffer from the serial flash memory device.*/
    kXSPI_RxBufferDrainFlag              = XSPI_FR_RBDF_MASK,   /*!< This field is set if SR[RXWE] is asserted.*/
    kXSPI_AhbAbortErrorFlag              = XSPI_FR_AAEF_MASK,   /*!< This flag can be set when AHB transaction error*/
    kXSPI_AhbIllegalTransactionErrorFlag = XSPI_FR_AITEF_MASK,
    kXSPI_AhbIllegalBurstSizeErrorFlag   = XSPI_FR_AIBSEF_MASK, /*!< The total burst size is more than prefetch size. */
    kXSPI_AhbBufferOverflowFlag          = XSPI_FR_ABOF_MASK,   /*!< The size of the AHB access exceed the size of
                                                                    the AHB buffer.  */
    kXSPI_AhbPerformanceMonitorOverflowFlag = XSPI_FR_PERFOVF_MASK, /*!< AHB performance hit or
                                                                        miss counter overflow. */
    kXSPI_AhbReadAddressErrorFlag = XSPI_FR_RDADDR_MASK,            /*!< The master send an AHB read address to that
                                                                buffer is not within the address range of any
                                                                sub-buffers or the address within multiple sub-buffers. */
    kXSPI_IllegalInstructionErrorFlag = XSPI_FR_ILLINE_MASK,   /*!< This field is set when an illegal instruction is
                                                                 encountered by the controller in any of the sequences.*/
    kXSPI_IpCmdtriggerErrorFlag = XSPI_FR_IPIEF_MASK,          /*!< Write access to Rx buffer control reg when
                                                               IP-triggered command is executing. */
    kXSPI_PageProgramWaitFlag = XSPI_FR_PPWF_MASK,             /*!< Indicates assertion of the page-program wait flag
                                                             after writing to flash memory. */
#if defined(XSPI_FR_IPEDERR_MASK)
    kXSPI_IPEDRxDecryptionErrorFlag    = XSPI_FR_IPEDERR_MASK, /*!< only support XSPI0 XSPI1*/
#endif /* defined(XSPI_FR_IPEDERR_MASK) */
    kXSPI_IpCommandExecutionDoneFlag   = XSPI_FR_TFF_MASK, /*!< Indicates XSPI has completed a running IP command. */
    kXSPI_SequenceExecutionTimeoutFlag = XSPI_INT_EN_TO_ERR_MASK, /*!< Sequence execution timeout. */
    kXSPI_FradMatchErrorFlag = XSPI_INT_EN_FRADMTCH_MASK,   /*Transaction address does not lie within address range of
                                                              any FRAD descriptor.*/
    kXSPI_Frad0AccessErrorFlag = XSPI_INT_EN_FRAD0ACC_MASK, /*<! FRAD 0 access error. */
    kXSPI_Frad1AccessErrorFlag = XSPI_INT_EN_FRAD1ACC_MASK, /*<! FRAD 1 access error. */
    kXSPI_Frad2AccessErrorFlag = XSPI_INT_EN_FRAD0ACC_MASK, /*<! FRAD 2 access error. */
    kXSPI_Frad3AccessErrorFlag = XSPI_INT_EN_FRAD1ACC_MASK, /*<! FRAD 3 access error. */
    kXSPI_Frad4AccessErrorFlag = XSPI_INT_EN_FRAD0ACC_MASK, /*<! FRAD 4 access error. */
    kXSPI_Frad5AccessErrorFlag = XSPI_INT_EN_FRAD1ACC_MASK, /*<! FRAD 5 access error. */
    kXSPI_Frad6AccessErrorFlag = XSPI_INT_EN_FRAD0ACC_MASK, /*<! FRAD 6 access error. */
    kXSPI_Frad7AccessErrorFlag = XSPI_INT_EN_FRAD1ACC_MASK, /*<! FRAD 7 access error. */
    kXSPI_FradnAccErrorFlag    = XSPI_INT_EN_FRAD0ACC_MASK | XSPI_INT_EN_FRAD1ACC_MASK | XSPI_INT_EN_FRAD2ACC_MASK |
                              XSPI_INT_EN_FRAD3ACC_MASK | XSPI_INT_EN_FRAD4ACC_MASK | XSPI_INT_EN_FRAD5ACC_MASK |
                              XSPI_INT_EN_FRAD6ACC_MASK | XSPI_INT_EN_FRAD7ACC_MASK, /*!< ORed value of all frad
                                                                                     error flag,. */
    kXSPI_IpsErrorFlag       = XSPI_INT_EN_IPS_ERR_MASK,
    kXSPI_Tg0SfarErrorFlag   = XSPI_INT_EN_TG0SFAR_MASK,
    kXSPI_Tg1SfarErrorFlag   = XSPI_INT_EN_TG1SFAR_MASK,
    kXSPI_TgnIpcrErrorFlag   = XSPI_INT_EN_TG0IPCR_MASK | XSPI_INT_EN_TG1IPCR_MASK,
    kXSPI_LockRegErrorFlag   = XSPI_INT_EN_LCK_ERR_IE_MASK,
    kXSPI_ArbLockTimeoutFlag = XSPI_INT_EN_ARB_TO_IE_MASK,
    kXSPI_ArbWinEventFlag    = XSPI_INT_EN_ARB_WIN_IE_MASK,
} xspi_flags_t;

/************************** External Device Control Structures and Enumerations Start *******************************/
/*! @brief The enumeration of Idle signal drive IOFA[3] and IOFA[2]
 */
enum _xspi_external_signal
{
    XSPI_SignalIOFA2 = XSPI_MCR_ISD2FA_MASK, /*!< Idle signal drive IOFA[2]. */
    XSPI_SignalIOFA3 = XSPI_MCR_ISD3FA_MASK  /*!< Idle signal drive IOFA[3]. */
};

/*!
 * @brief The structure of external device's status register information(location, priority).
 * @note Only useful when AHB write to flash device is enabled, and use hardware to clear ppw flag.
 */
typedef struct _xspi_device_status_reg_info
{
    uint8_t wipLocation;        /*!< WIP bit field's location. */
    bool upperHalfWordSelected; /*!< Specify which half word(upper or lower) is selected. */
    bool value1Expired;         /*!< Specify the value to be check o selected wip location to
                                    determine if the page progame wait period is expired,
                                    true means expected value is 1, false means expected value
                                    is 0. */
} xspi_device_status_reg_info_t;

/*! @brief Dll Mode enumerations. */
typedef enum _xspi_dll_mode
{
    kXSPI_AutoUpdateMode, /*!< Dll mode : Auto update mode. */
    kXSPI_BypassMode,     /*!< Dll mode : Bypass mode. */
} xspi_dll_mode_t;

/*!
 * @brief The union of user custommed DLL parameters, in case of #kXSPI_BypassMode bypassModePara is used, in case of
 * #kXSPI_AutoUpdateMode autoUpdateModoPara is used.
 */
typedef union _xspi_dll_para
{
    struct
    {
        uint16_t delayElementCoarseValue : 4U; /*!< Delay element coarse adjustment value, range from 0 to 15. */
        uint16_t delayElementFineValue : 3U;   /*!< Delay element fine adjustment value, range from 0 to 7.  */
        uint16_t offsetDelayElementCount : 4U; /*!< Specify the number of offset delay elements,
                                                   range from 0 to 15. */
        uint16_t enableHighFreq : 1U;          /*!< If set as true, high frequency used for delay chain operations,
                                                  otherwise low frequency is used. */
        uint16_t bypassModeReserved : 4U;      /*!< Reserved. */
    } bypassModePara;
    struct
    {
        uint16_t referenceCounter : 4U;              /*!< Specify count of interval for DLL phase detection, range from
                                                     0 to 15. */
        uint16_t resolution : 4U;                    /*!< Specify minimum resolution for the DLL phase detctor,
                                                     range from 0 to 15. */
        uint16_t offsetDelayElementCount : 4U;       /*!< Specify the number of offset delay elements,
                                                         range from 0 to 15. */
        uint16_t tDiv16OffsetDelayElementCount : 3U; /*!< Specify the number of T/16 offset elements in the incoming
                                                     DQS, range from 0 to 15. */
        uint16_t enableHighFreq : 1U; /*!< If set as true, high frequency used for delay chain operations,
                                         otherwise low frequency is used. */
    } autoUpdateModoPara;
} xspi_dll_para_t;

/*!
 * @brief The structure of Delay-lock-loop configuration.
 */
typedef struct _xspi_dll_config
{
    xspi_dll_mode_t dllMode;       /*!< Dll mode auto update mode or bypass mode */
    bool useRefValue;              /*!< Specify to use reference value or not, if the reference code do not
                                     satisfy the specific usecase, it is application's responsibility to
                                     set custom parameters
                                     - \b true: following inputs are ignored, use the reference values
                                                 provided by NXP as instead;
                                     - \b false: following inputs take effect. */

    xspi_dll_para_t dllCustomPara; /*!< User custommed parameter to configure DLL, different DLL mode
                                     corresponding to different parameters, please refer to the union
                                     @ref xspi_dll_para_t. */
    uint8_t dllCustomDelayTapNum;  /*!< User custommed number of delay elements for each delay tap. */
    bool enableCdl8;               /*!< Enable course delay line 8. */
} xspi_dll_config_t;

/*!
 * @brief The enumeration of sample clock source which is used to sample data from external devices.
 *
 * @note If external device support Data strobe signal, the sample clock
 *   should selected as kXSPI_SampleClkFromExternalDQS.
 */
typedef enum _xspi_sample_clk_source
{
    kXSPI_SampleClkFromNonInvertedFullySpeedDummyPadLoopback = 0x1U, /*!< Sample clock from non inverted
                                                                     fully speed dummy pad loopback. */
    kXSPI_SampleClkFromInvertedFullySpeedDummyPadLoopback = 0x5U,    /*!< Sample clock from inverted
                                                                     fully speed dummy pad loopback. */
    kXSPI_SampleClkFromHalfSpeedDummyPadLoopback = 0x9U,             /*!< Sample clock from half
                                                                     fully speed dummy pad loopback. */
    kXSPI_SampleClkFromDqsPadLoopback = 0x2U,                        /*!< Sample clock from Dqs pad loopback. */
    kXSPI_SampleClkFromExternalDQS    = 0x3U,                        /*!< Sample clock from external DQS signal. */
} xspi_sample_clk_source_t;

/*!
 * @brief The selection of data learning pad.
 */
typedef enum _xspi_data_learning_pad_select
{
    kXSPI_OnlyIO1    = 1U, /*!< IO1 selected as pad to use for pattern matching IO. */
    kXSPI_BothIO1IO3 = 3U, /*!< IO1 and IO3 selected as pad to use for pattern matching IO. */
} xspi_data_learning_pad_select_t;

/*!
 * @brief The configuration of data learning.
 *
 * @note Data learning feature only supported in the DQS sampling method(kXSPI_SampleClkFromExternalDQS).
 */
typedef struct _xspi_data_learning_config
{
    uint32_t pattern;                            /*!< Pre-defiend pattern to match. */
    bool deviceSupported;                        /*!< Specify if external device support data learning feature. */
    xspi_data_learning_pad_select_t padSelected; /*!< Used to select pad which use for pattern matching IO. */
} xspi_data_learning_config_t;

/*!
 * @brief Sample clock configuration, which used to sample data from external device.
 */
typedef struct _xspi_sample_clk_config
{
    xspi_sample_clk_source_t sampleClkSource; /*!< Specify the sample clock source. */
    bool enableDQSLatency;                    /*!< Enable DQS latency or not. */
    xspi_dll_config_t dllConfig; /*!< Specify the DLL configuration, to improve data accuracy, please adjust
                                     DLL settings based on specific use.  */
} xspi_sample_clk_config_t;

/*!
 * @brief External device's address mode.
 */
typedef enum _xspi_device_addr_mode
{
    kXSPI_DeviceByteAddressable  = 0U, /*!< Byte addressable. */
    kXSPI_Device2ByteAddressable = 1U, /*!< Two bytes addressable. */
    kXSPI_Device4ByteAddressable = 2U, /*!< Four bytes addressable. */
} xspi_device_addr_mode_t;

/*!
 * @brief The enumeration of external device's interface type, hyper bus or SPI(including strandard and extended).
 *
 * @note Different interface result different settings.
 */
typedef enum _xspi_device_interface_type
{
    kXSPI_StrandardExtendedSPI = 0U, /*!< External device follow SPI protocol, DQS_OUT_EN must be 0 */
    kXSPI_HyperBus             = 1U, /*!< External device follow hyper Bus protocol,  DQS_OUT_EN must be 1 */
} xspi_device_interface_type_t;

/*!
 * @brief The enumeration of hyper bus X16 mode
 */
typedef enum _xspi_hyper_bus_x16_mode
{
    kXSPI_x16ModeDisable            = 0U, /*!< X16 mode is disabled. */
    kXSPI_x16ModeEnabledOnlyData    = 2U, /*!< X16 mode is enabled only for data. */
    kXSPI_x16ModeEnabledAddrCmdData = 3U, /*!< X16 mode is enabled for address, command, and data. */
} xspi_hyper_bus_x16_mode_t;

/*!
 * @brief The union of external device's settings, if external device following hyper bus protocol #hyperBusSettings
 * take effects, if external device following SPI protocol #strandardExtendedSPISettings take effects.
 */
typedef union _xspi_device_interface_settings
{
    struct
    {
        uint32_t pageSize; /*!< The size of page to program, the unit is byte. */
    } strandardExtendedSPISettings;

    struct
    {
        xspi_hyper_bus_x16_mode_t x16Mode; /*!< Specify hyper bus X16 mode. */
        bool enableVariableLatency;        /*!< If enabled, the count of latency is depends on hyper bus device. */
        bool forceBit10To1;                /*!< Force bit 10 to logic one or not. */
    } hyperBusSettings;
} xspi_device_interface_settings_t;

/*!
 * @brief Enumeration defining the alignment modes of XSPI DDR data with respect to the internal reference clock.
 */
typedef enum _xspi_ddr_data_aligned_clk
{
    kXSPI_DDRDataAlignedWithInternalRefClk = 0U, /*!< DDR data aligned with internal reference clock. */
    kXSPI_DDRDataAlignedWith2xInternalRefClk,    /*!< DDR data aligned with 2X internal reference clock. */
} xspi_ddr_data_aligned_clk_t;

/*!
 * @brief The structure of device DDR configuration.
 */
typedef struct _xspi_device_ddr_config
{
    bool enableDdr;                                /*!< Used to enable/disable DDR mode. */
    xspi_ddr_data_aligned_clk_t ddrDataAlignedClk; /*!< Specify the DDR data aligned clock. */
    bool enableByteSwapInOctalMode;                /*!< Swap byte order in octal mode. */
} xspi_device_ddr_config_t;

/*! @brief External device configuration items. */
typedef struct _xspi_device_config
{
    uint32_t xspiRootClk; /*!< XSPI serial root clock. */
    bool enableCknPad;    /*!< Enable/disable clock on differential CKN pad for flash memory A.*/

    xspi_device_interface_type_t deviceInterface;       /*!< Type of external device's interface:
                                                        hyperBus or Strandard/Extended SPI. */
    xspi_device_interface_settings_t interfaceSettings; /*!< Settings of specified interface. */

    uint8_t CSHoldTime;                                 /*!< CS line hold time. */
    uint8_t CSSetupTime;                                /*!< CS line setup time. */

    xspi_sample_clk_config_t sampleClkConfig;           /*!< Configuration of sample clock. */

    xspi_device_ddr_config_t *ptrDeviceDdrConfig;    /*!< Set as NULL to set device as SDR mode, to change to DDR mode,
                                                   this member should be populated. */

    xspi_device_addr_mode_t addrMode;                /*!< Address mode of external device. */
    uint8_t columnAddrWidth;                         /*!< Width of column address. */
    bool enableCASInterleaving;                      /*!< Usually enabled in dual-die device. */
    uint32_t deviceSize[XSPI_SFAD_COUNT2];           /*!< Size of external device, the unit is KB. */

    xspi_device_status_reg_info_t *ptrDeviceRegInfo; /*!< Pointer to the structure to store external device's WIP
                                                        register information, should set as NULL if AHB page write
                                                        is not used or if AHB page write is used but use software
                                                        policy to clear flag. */
} xspi_device_config_t;
/************************** External Device Control Structures and Enumerations End *******************************/

/**************************** IP Access Control Structures and Enumerations Start *********************************/
/*! @brief Command type. */
typedef enum _xspi_command_type
{
    kXSPI_Command, /*!< XSPI operation: Only command, both TX and Rx buffer are ignored. */
    kXSPI_Config,  /*!< XSPI operation: Configure device mode, the TX fifo size is fixed in LUT. */
    kXSPI_Read,    /*!< XSPI operation: Read, only Rx Buffer is effective. */
    kXSPI_Write,   /*!< XSPI operation: Read, only Tx Buffer is effective. */
} xspi_command_type_t;

/*!
 * @brief The enumeration of SFP MDAD mask type.
 */
typedef enum _xspi_mdad_mask_type
{
    kXSPI_MdadMaskTypeAnd = 0U, /*!< Target master is mask & reference. */
    kXSPI_MdadMaskTypeOr,       /*!< Target master is mask | reference. */
} xspi_mdad_mask_type_t;

/*!
 * @brief The enumeration of MDAD error reasons.
 */
typedef enum _xspi_mdad_error_reason
{
    kXSPI_ErrorOnlyDataSize = 1U, /*!< Error reason: Only Data size without required attributes. */
    kXSPI_ErrorOnlySeqId,         /*!< Error reason: Only sequence ID without required attributes. */
    kXSPI_ErrorBothDataSizeSeqId, /*!< Error reason: Both Data size and sequence ID without required attributes. */
} xspi_mdad_error_reason_t;

/*! @brief Exclusive access lock. */
typedef enum _xspi_exclusive_access_lock_mode
{
    kXSPI_ExclusiveAccessLockDisabled = 0x0U,       /*!< Write permissions available for all masters
                                                      based on their MDxACP evaluation.*/
    kXSPI_ExclusiveAccessLockEnabled = 0x2U,        /*!< Write permissions revoked for all domains, Any write
                                                    transaction coming to this flash address will result in an error..*/
    kXSPI_ExclusiveAccessLockExceptMasterId = 0x3U, /*!< Write permissions are revoked for all masters except the master
                                                       ID specified by FRADn_WORD2[EALO] fields.*/
} xspi_exclusive_access_lock_mode_t;

/*! @brief XSPI defines the secure attribute selection criteria for entry into descriptor queue...*/
typedef enum _xspi_secure_attribute
{
    kXSPI_AttributeMasterNonsecureOnly = 0x1U,       /*!< Allow the bus attribute for this master to
                                                          non-secure only*/
    kXSPI_AttributeMasterSecureOnly          = 0x2U, /*!< Allow the bus attribute for this master to secure only*/
    kXSPI_AttributeMasterNonsecureSecureBoth = 0x3U, /*!< Allow the bus master's attribute: Both secure and
                                                          non-secure*/
} xspi_secure_attribute_t;

/*! @brief MDAD configuration. */
typedef struct _xspi_mdad_config
{
    bool assignIsValid;                      /*!< Specify if the MDAD configuration for the target group is valid */

    bool enableDescriptorLock;               /*!< This field provides a means to make the MDAD descriptor read-only.
                                               Once written '1' this field will remain '1' until hard reset*/
    uint8_t maskType;                        /*!< 0b - ANDed mask 1b - ORed mask*/
    uint8_t mask;                            /*!< Defines the 6-bit mask value for the ID-Match comparison*/
    uint8_t masterIdReference;               /*!< Specifies the reference value of the Master-ID for MID-comparison*/
    xspi_secure_attribute_t secureAttribute; /*!< Defines the secure attribute selection criteria for entry into
                                             descriptor queue*/
} xspi_mdad_config_t;

#define XSPI_TARGET_GROUP_COUNT (2U)

/*!
 * @brief The structure of SFP MDAD configurations for all target groups.
 */
typedef struct _xspi_sfp_mdad_config
{
    xspi_mdad_config_t tgMdad[XSPI_TARGET_GROUP_COUNT]; /*!< Specify MDAD configurations for each target group. */
} xspi_sfp_mdad_config_t;

/*! @brief Descriptor lock. */
typedef enum _xspi_descriptor_lock
{
    kXSPI_DescriptorLockDisabled              = 0x0U, /*!< Descriptor registers can be written by any master*/
    kXSPI_DescriptorLockEnabledTillHardReset  = 0x1U, /*!< FRAD descriptor is read-only till next hard reset.*/
    kXSPI_DescriptorLockEnabledExceptMasterId = 0x2U, /*!< Descriptors are read-only. MDnACP fields can be programmed
                                                        only by the master with ID matching the MID.*/
    kXSPI_DescriptorLockEnabled = 0x3U,               /*!< Descriptor registers are read-only.*/
} xspi_descriptor_lock_t;

/*! @brief FRAD configuration. */
typedef struct _xspi_frad_config_t
{
    uint32_t startAddress;   /*!< Specifies the specific flash memory region starting address*/
    uint32_t endAddress;     /*!< Specifies the specific flash memory region end address*/
    uint8_t tg0MasterAccess; /*!< This field define the access restrictions for respective Master Domain
                               corresponding to this FRAD region. Access permissions are decided  based on secure
                               an privilege attributes of current transaction. Read access is not restricted.*/
    uint8_t tg1MasterAccess;
    bool assignIsValid;      /*!< This field indicates whether the FRAD Descriptor for a specific flash region
                               is valid.*/
    xspi_descriptor_lock_t descriptorLock; /*!< This field enables masking of accidental write on FRAD registers.
                                           Lock is enabled/disabled by Secure/ Privileged master.*/
    xspi_exclusive_access_lock_mode_t exclusiveAccessLock; /*!< This field provides exclusive write lock over a
                                                      FRAD region based on MDnACP.*/
} xspi_frad_config_t;

#define XSPI_SFP_FRAD_COUNT (8U)
/*!
 * @brief The structure of SFP FRAD configurations.
 */
typedef struct _xspi_sfp_frad_config
{
    xspi_frad_config_t fradConfig[XSPI_SFP_FRAD_COUNT]; /*!< Specify FRAD configuration for each item. */
} xspi_sfp_frad_config_t;

/*!
 * @brief The structure of latest FRAD transaction information.
 */
typedef struct _xspi_frad_transaction_info
{
    uint32_t startAddr;     /*!< Latest IP access start address. */
    uint8_t masterId;       /*!< Latest IP access master Id. */
    bool isSecureAccess;    /*!< Latest IP access is secure access or not. */
    bool isPrivilegeAccess; /*!< Latest IP access is privilege access or not. */
    bool isCompError;       /*!< Indicates the error status of the flash region specific comparision check for
                            the latest transaction.  */
    bool isCompValid;       /*!< Indicates availability of the result or status of a flash region-specific
                            comparison check. */
} xspi_frad_transaction_info_t;

/*!
 * @brief Configurations of IP access(including IP read and write).
 */
typedef struct _xspi_ip_access_config
{
    xspi_sfp_mdad_config_t *ptrSfpMdadConfig; /*!< Pointer to the variable in type of @ref xspi_sfp_mdad_config_t to
                                          set SFP MDAD feature, set as NULL to disable SFP MDAD feature.  */
    xspi_sfp_frad_config_t *ptrSfpFradConfig; /*!< Pointer to the variable in type of @ref xspi_sfp_frad_config_t to
                                          set SFP FRAD feature, set as NULL to disable SFP FRAD */
    uint32_t sfpArbitrationLockTimeoutValue;  /*!< Specify the time in IPS clock cycles before an unreleased
                                              arbitration triggers a timeout error. */
    uint32_t ipAccessTimeoutValue;            /*!< Specify the maximum time in IPS clock cycles for XSPI to wait fro an
                                          ongoing write or read command to complete before terminating the command. */
} xspi_ip_access_config_t;

#define XSPI_IP_RX_BUFFER_SIZE (512U)

/*! @brief The enumeration of target group. */
typedef enum _xspi_target_group
{
    kXSPI_TargetGroup0 = 0x0U, /*!< Target groupe queue 0*/
    kXSPI_TargetGroup1 = 0x1U, /*!< Target groupe queue 1*/
} xspi_target_group_t;

/*!
 * @brief The status of latest target group address write operation.
 */
typedef struct _xspi_tg_add_write_status
{
    uint8_t managerId;    /*!< Manager Id of TG address write operation. */
    bool secureWrite;     /*!< TG address write operation is secure write. */
    bool privilegedWrite; /*!< TG address write operation is privileged. */
} xspi_tg_add_write_status_t;

/*! @brief Transfer structure used for XSPI functional interface. */
typedef struct _xspi_transfer
{
    uint32_t deviceAddress;          /*!< Operation device address. */
    xspi_command_type_t cmdType;     /*!< Execution command type. */
    uint8_t seqIndex;                /*!< Sequence ID for command. */
    uint32_t *data;                  /*!< Data buffer. */
    size_t dataSize;                 /*!< Data size in bytes. */
    xspi_target_group_t targetGroup; /*!< Target group. include targetGroup[0] targetGroup[1]*/
    bool lockArbitration;
} xspi_transfer_t;

/* Forward declaration of the handle typedef. */
typedef struct _xspi_handle xspi_handle_t;

/*! @brief XSPI transfer callback function. */
typedef void (*xspi_transfer_callback_t)(XSPI_Type *base, xspi_handle_t *handle, status_t status, void *userData);

/*! @brief Transfer handle structure for XSPI. */
struct _xspi_handle
{
    uint32_t state;                              /*!< Internal state for XSPI transfer */
    uint8_t *data;                               /*!< Data buffer. */
    size_t dataSize;                             /*!< Remaining Data size in bytes. */
    size_t transferTotalSize;                    /*!< Total Data size in bytes. */
    xspi_transfer_callback_t completionCallback; /*!< Callback for users while transfer finish or error occurred */
    void *userData;                              /*!< XSPI callback function parameter.*/
};
/**************************** IP Access Control Structures and Enumerations End *********************************/

/**************************** AHB Access Control Structures and Enumerations Start *********************************/
/*! @brief Subbuffer division factor. */
typedef enum _xspi_subbuffer_division_factor
{
    kXSPI_Division0  = 0x0U, /*!< division factor 0*/
    kXSPI_Division2  = 0x1U, /*!< division factor 2 subbuffer size/2*/
    kXSPI_Division4  = 0x2U, /*!< division factor 4 subbuffer size/4*/
    kXSPI_Division8  = 0x3U, /*!< division factor 8 subbuffer size/8*/
    kXSPI_Division16 = 0x4U, /*!< division factor 16 subbuffer size/16*/
} xspi_subbuffer_division_factor_t;

/*!
 * @brief The structure of sub-buffer configurations.
 */
typedef struct _xspi_ahbBuffer_sub_buffer_config
{
    xspi_subbuffer_division_factor_t divFactor; /*!< Specify the divide factor for current sub-buffer. */
    uint32_t startAddr;                         /*!< Specify the start address of current sub-buffer. */
    uint32_t endAddr;                           /*!< Specify the end address of current sub-buffer. */
    bool enableAhbMonitor;                      /*!< Enable/disable AHB performance monitor for current sub-buffer. */
} xspi_ahbBuffer_sub_buffer_config_t;

/*!
 * @brief Structure of AHB buffer configurations.
 *
 * @note When an AHB read access comes it is assigned to a buffer based on its master ID. Then
 * it further assigned to a sub-buffer based on which sub-buffer address range this transaction lies into.
 *
 * @note When sub-buffer division is hit, in case of a buffer miss the controller will fetch the data equal to the size
 * of that sub-buffer.
 *
 * @note If sub-buffer division is enabled for a buffer the hit/miss check is done at sub-buffer level. And if prefetch
 * is enable, the prefetch takes place for individual sub-buffers.
 */
typedef struct _xspi_ahbBuffer_config
{
    uint8_t masterId; /*!< Specify the ID of the AHB master to be associated with buffer. */
    union
    {
        bool enablePriority;  /*!< High Priority Enable, it can be written '1' only when OTFAD is disabled,
                                the AHB prefetch feature must be enabled if priority mechanism is enabled.
                                 */
        bool enableAllMaster; /*!< When set, buffer3 acts as an all-master buffer.buff[i] routed to buffer3*/
    } enaPri;

    uint16_t bufferSize;                                     /* Specify the AHB buffer size and transfer size(8 byte as unit),
                                                              * in range of 512, 256, 128, 64, 32, 16, 8, 4, 2, 0.
                                                              */
    xspi_ahbBuffer_sub_buffer_config_t *ptrSubBuffer0Config; /*!< Pointer to sub buffer0's configuration. */
    xspi_ahbBuffer_sub_buffer_config_t *ptrSubBuffer1Config; /*!< Pointer to sub buffer1's configuration. */
    xspi_ahbBuffer_sub_buffer_config_t *ptrSubBuffer2Config; /*!< Pointer to sub buffer2's configuration. */
    xspi_ahbBuffer_sub_buffer_config_t *ptrSubBuffer3Config; /*!< Pointer to sub buffer3's configuration. */
} xspi_ahbBuffer_config_t;

/*!
 * @brief The enumeration of sub buffer status, empty, full, or partially full.
 */
typedef enum _xspi_ahb_sub_buffer_status
{
    kXSPI_AhbSubBufferEmpty = 0U,    /*!< Current sub buffer is empty. */
    kXSPI_AhbSubBufferFull,          /*!< Current sub buffer is full. */
    kXSPI_AhbSubBufferPartiallyFull, /*!< Current sub buffer contains some entries. */
} xspi_ahb_sub_buffer_status_t;

/*!
 * @brief The result of AHB buffer performance monitor, including buffer miss count and buffer hit count.
 */
typedef struct _xspi_ahbBuffer_perf_monitor_result
{
    uint16_t bufferMissCount; /*!< Count of AHB read buffer miss events. */
    uint16_t bufferHitCount;  /*!< Count of AHB read buffer hit events. */
} xspi_ahbBuffer_perf_monitor_result_t;

/*!
 * @brief The enumeration of XSPI page program waiting flag  clear policy.
 */
typedef enum _xspi_ppw_flag_clear_policy
{
    kXSPI_SoftwareClearPPWFlag = 0U, /*!< Application should clear the flag manually, after check the WIP of external
                                        flag is cleared. */
    kXSPI_HardwareClearPPWFlag,      /*!< The flag is cleared by hardware automatically, the variable in type of
                                         @ref xspi_device_status_reg_info_t should be defined. */
} xspi_ppw_flag_clear_policy_t;

/*!
 * @brief The configuration of AHB write access.
 */
typedef struct _xspi_ahb_write_config
{
    bool blockSequenceWrite;             /*!< Enable/disable sequence write operation after page program start. */
    bool blockRead;                      /*!< Enable/disable read operation after page program start,
                                             can be false for RWW extern device. */
    xspi_ppw_flag_clear_policy_t policy; /*!< Specify the policy to clear ppw flag, hardware or software. */
    uint32_t pageWaitTimeoutValue; /*!< Specify, in AHB clock cycles, how long XSPI waits before triggering a read of
                                   the device status register, only useful in hardare policy. */
    uint8_t AWRSeqIndex;           /*!< Specify the sequence index for AHB write. */
    uint8_t ARDSRSeqIndex;         /*!< Specify the sequence index for AHB read status, only useful if
                                   either sequence write or read is blocked. */
} xspi_ahb_write_config_t;

/*! @brief XSPI AHB Split Size These bits are used to control the split size when split function is enabled
 * BFGENCR[SPLITEN] is '1'.*/
typedef enum _xspi_ahb_split_size
{
    kXSPI_AhbSplitSize8b       = 0x0U, /*!< Enable AHB transaction split and split size is 8 bytes. */
    kXSPI_AhbSplitSize16b      = 0x1U, /*!< Enable AHB transaction split and split size is 16 bytes. */
    kXSPI_AhbSplitSize32b      = 0x2U, /*!< Enable AHB transaction split and split size is 32 bytes. */
    kXSPI_AhbSplitSize64b      = 0x3U, /*!< Enable AHB transaction split and split size is 64 bytes. */
    kXSPI_AhbSplitSizeDisabled = 0xFU, /*!< Disable AHB Transaction Split feature. */
} xspi_ahb_split_size_t;

/*! @brief XSPI AHB access towards flash is broken if this AHB alignment boundary is crossed.
 This field is only supported XSPI0 XSPI1.*/
typedef enum _xspi_ahb_alignment
{
    kXSPI_AhbAlignmentNoLimit   = 0x0U, /*!< no limit*/
    kXSPI_AhbAlignment256BLimit = 0x1U, /*!< 256B limit*/
    kXSPI_AhbAlignment512BLimit = 0x2U, /*!< 512B limit*/
    kXSPI_AhbAlignment1KBLimit  = 0x3U, /*!< 1KB limit*/
} xspi_ahb_alignment_t;

/*!
 * @brief The structure of AHB access configurations, including AHB buffer settings, AHB Read Seq ID, AHB write
 * settings.
 */
typedef struct _xspi_ahb_access_config
{
    xspi_ahbBuffer_config_t buffer[4];  /*!< AHB buffer size. */
    uint8_t ARDSeqIndex;                /*!< Specify the sequence index for AHB read data. */

    bool enableAHBPrefetch;             /*!< Enable/disable AHB read prefetch feature, when enabled, XSPI
                                           will fetch more data than current AHB burst. */
    bool enableAHBBufferWriteFlush;     /*!< Set true to enable flush of AHB buffer, due to either AHB write or IP
                                        access to avoid stable data in AHB buffer. */
    xspi_ahb_split_size_t ahbSplitSize; /*!< Specify ahb split size, set as kXSPI_AhbSplitSizeDisabled if do not
                                       want to use this feature. */
    xspi_ahb_alignment_t ahbAlignment;  /*!< AHB access towards flash is broken if this AHB alignment boundary is
                                           crossed, only support XSPI0 XSPI1 */

    xspi_ahb_write_config_t *ptrAhbWriteConfig; /*!< Set as NULL if AHB write feature is not used. */
    struct
    {
        uint32_t highPayload; /*!< High 32bit error payload. */
        uint32_t lowPayload;  /*!< Low 32bit error payload. */
    } ahbErrorPayload;
} xspi_ahb_access_config_t;

/*!
 * @brief The structure of information when AHB read error occur.
 */
typedef struct _xspi_ahb_read_error_info
{
    uint32_t errorAddr;  /*!< AHB read error address. */
    uint8_t errMasterId; /*!< AHB read error master Id. */
} xspi_ahb_read_error_info_t;

/*!
 * @brief The enumeration of AHB request suspend state.
 */
typedef enum _xspi_ahb_request_suspend_state
{
    kXSPI_AhbRequestNoSuspended = 0U, /*!< None of AHB request is suspended. */
    kXSPI_AhbRequestSuspended,        /*!< The AHB request is suspended. */
    kXSPI_AhbRequestNotApplicable,    /*!< The AHB request is not applicable. */
    kXSPI_AhbReqestResumed,           /*!< The AHB request is resumed. */
} xspi_ahb_request_suspend_state_t;

/*!
 * @brief The structure of information when AHB reqest is suspended.
 */
typedef struct _xspi_ahb_request_suspend_info
{
    xspi_ahb_request_suspend_state_t state; /*!< Current AHB request state. */
    uint8_t subBufferId;                    /*!< Suspended AHB request's sub buffer Id. */
    uint8_t ahbBufferId;                    /*!< Suspended AHB request's buffer Id. */
    uint16_t dataLeft;                      /*!< How many data left to transfer. */
    uint32_t address;                       /*!< Current address of suspended AHB request. */
} xspi_ahb_request_suspend_info_t;

/*!
 * @brief The enumeration of OTFAD prefetch address boundary.
 */
typedef enum _xspi_otfad_prefetch_boundary
{
    kXSPI_OTFADPrefetchNoBoundary = 0U, /*!< No prefetch address boundary. */
    kXSPI_OTFADPrefetchBoundary1K = 1U, /*!< Prefetch address boundary is 1K. */
} xspi_otfad_prefetch_boundary_t;
/**************************** AHB Access Control Structures and Enumerations End *********************************/

/**************************** XSPI Controller Structures and Enumerations Start *********************************/

/*! @brief Byte ordering endianness. */
typedef enum _xspi_byte_order
{
    kXSPI_64BitBE = 0x0U, /*!< 64 bit big endian*/
    kXSPI_32BitLE = 0x1U, /*!< 32 bit little endian*/
    kXSPI_32BitBE = 0x2U, /*!< 32 bit big endian*/
    kXSPI_64BitLE = 0x3U, /*!< 64 bit little endian*/
} xspi_byte_order_t;

/*! @brief XSPI configuration structure. */
typedef struct _xspi_config
{
    xspi_byte_order_t byteOrder;                  /*!< Byte ordering endianness*/
    bool enableDoze;                              /*!< Enable/disable doze mode support. */
    xspi_ahb_access_config_t *ptrAhbAccessConfig; /*!< Pointer to AHB access configuration,
                                                  can be NULL is AHB access is not used. */
    xspi_ip_access_config_t *ptrIpAccessConfig;   /*!< Pointer to IP access configuration,
                                                  can be NULL is IP access is not used. */
} xspi_config_t;
/**************************** XSPI Controller Structures and Enumerations End *********************************/

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /*_cplusplus. */

/*!
 * @name Initialization And Deinitialization Functional Interfaces
 * @{
 */

/*!
 * @brief Get the instance number for XSPI.
 *
 * @param base XSPI base pointer.
 */
uint32_t XSPI_GetInstance(XSPI_Type *base);

/*!
 * @brief Check and clear IP command execution errors.
 *
 * @param base XSPI base pointer.
 * @param status interrupt status.
 */
status_t XSPI_CheckAndClearError(XSPI_Type *base, uint32_t status);

/*!
 * @brief Initializes the XSPI module and internal state.
 *
 * This function configures the XSPI with the
 * input configure parameters. Users should call this function before any XSPI operations.
 *
 * @param base XSPI peripheral base address.
 * @param ptrConfig XSPI configure structure.
 */
void XSPI_Init(XSPI_Type *base, const xspi_config_t *ptrConfig);

/*!
 * @brief Gets default settings for XSPI.
 *
 * @warning The parameter \b devconfig will be removed in next release.
 *
 * @param base XSPI peripheral base address.
 * @param ptrConfig XSPI configuration structure.
 */
void XSPI_GetDefaultConfig(xspi_config_t *ptrConfig);

/*!
 * @brief Deinitialize the XSPI module.
 *
 * Clears the XSPI state and  XSPI module registers.
 * @param base XSPI peripheral base address.
 * @param devconfig Flash configuration parameters.
 */
void XSPI_Deinit(XSPI_Type *base);

/*! @brief Updates the LUT table.
 *
 * @param base XSPI peripheral base address.
 * @param index From which index start to update. It could be any index of the LUT table, which
 * also allows user to update command content inside a command. Each command consists of up to
 * 10 instructions and occupy 5*32-bit memory.
 * @param cmd Command sequence array.
 * @param count Number of instruction-operand pairs
 */
void XSPI_UpdateLUT(XSPI_Type *base, uint8_t index, const uint32_t *cmd, uint8_t count);

/*!
 * @brief Set OTFAD prefetch boundary.
 *
 * @param base XSPI peripheral base address.
 * @param boundary Prefetch boundary to set, in type of @ref xspi_otfad_prefetch_boundary_t.
 */
static inline void XSPI_SetOTFADPrefetchBoundary(XSPI_Type *base, xspi_otfad_prefetch_boundary_t boundary)
{
    base->SPTRCLR = (base->SPTRCLR & (~XSPI_SPTRCLR_OTFAD_BNDRY_MASK)) | XSPI_SPTRCLR_OTFAD_BNDRY(boundary);
}
/* @} */

/*!
 * @name XSPI Controller Low-Level Inferfaces
 */

static inline void XSPI_UpdateByteOrder(XSPI_Type *base, xspi_byte_order_t byteOrder)
{
    base->MCR = ((base->MCR) & (~XSPI_MCR_END_CFG_MASK)) | XSPI_MCR_END_CFG(byteOrder);
}

/*!
 * @brief Enable or disable the XSPI module.
 *
 * @param base XSPI peripheral base address.
 * @param enable true means enable XSPI, false means disable.
 */
static inline void XSPI_EnableModule(XSPI_Type *base, bool enable)
{
    if (enable)
    {
        base->MCR &= ~XSPI_MCR_MDIS_MASK;
    }
    else
    {
        base->MCR |= XSPI_MCR_MDIS_MASK;
    }
}

/*!
 * @brief Check if the XSPI module is enabled.
 *
 * @param base XSPI peripheral base address.
 *
 * @retval true XSPI module is enabled.
 * @retval false XSPI module is disabled.
 */
static inline bool XSPI_CheckModuleEnabled(XSPI_Type *base)
{
    return ((base->MCR & XSPI_MCR_MDIS_MASK) == 0UL);
}

/*!
 * @brief Reset Serial flash memory domain and AHB domain at the same time.
 *
 * @note Resetting only the Serial flash memory domain and AHB domain may cause undesirable side effects.
 *
 * @param base XSPI peripheral base address.
 */
void XSPI_ResetSfmAndAhbDomain(XSPI_Type *base);

/*!
 * @brief Reset IPS target group queue.
 *
 * @param base XSPI peripheral base address.
 */
static inline void XSPI_ResetTgQueue(XSPI_Type *base)
{
    base->MCR |= XSPI_MCR_IPS_TG_RST_MASK;
}

/*!
 * @brief Software reset  flash memory domain, AHB domain, and Target group at the same time.
 *
 * @param base XSPI peripheral base address.
 */
static inline void XSPI_SoftwareReset(XSPI_Type *base)
{
    XSPI_ResetTgQueue(base);
    XSPI_ResetSfmAndAhbDomain(base);
}

/*!
 * @brief Check if write access to registers(MGC, MRC, MTO, SFP_ARB_TIMEOUT, SFP_LUT_ENn, LUTn, BFGENCR) is locked.
 *
 * @param base XSPI peripheral base address.
 *
 * @retval false Write access to listed registers is not locked.
 * @retval true Write access to listed registers is locked.
 */
static inline bool XSPI_CheckGlobalConfigLocked(XSPI_Type *base)
{
    return (bool)((base->MGC & XSPI_MGC_GCLCK_MASK) != 0UL);
}
/* @} */

/*!
 * @name External Device Control Low-Level Interfaces
 * @{
 */

/*!
 * @brief Set Hyper bus X16 mode.
 *
 * @param base XSPI peripheral base address.
 * @param x16Mode Specify X16 mode.
 */
void XSPI_SetHyperBusX16Mode(XSPI_Type *base, xspi_hyper_bus_x16_mode_t x16Mode);

/*!
 * @brief Update address mode to access external device.
 * 
 * @param base XSPI peripheral base address.
 * @param addrMode Specify the address mode to update.
 *
 * @retval kStatus_XSPI_AhbReadAccessAsserted Fail to update address mode due to AHB read access asserted.
 * @retval kStatus_XSPI_IPAccessAsserted Fail to update address mode due to a IP access already asserted.
 * @retval kStatus_XSPI_AhbWriteAccessAsserted Fail to update address mode due to AHB write access asserted.
 * @retval kStatus_Success  Successfully to update address mode.
 */
status_t XSPI_UpdateDeviceAddrMode(XSPI_Type *base, xspi_device_addr_mode_t addrMode);

/*!
 * @brief Enable/disable variable latency for XSPI.
 *
 * @note Only useful for hyper bus device.
 * @note It is application responsibility to enable variable latency for external hyper bus
 * device(by change device's register).
 *
 * @param base XSPI peripheral base address.
 * @param enable Specify operation:
            - \b true Enable variable latency;
            - \b false Disable variable latency.
 */
static inline void XSPI_EnableVariableLatency(XSPI_Type *base, bool enable)
{
    if (enable)
    {
        base->MCR |= XSPI_MCR_VAR_LAT_EN_MASK;
    }
    else
    {
        base->MCR &= ~XSPI_MCR_VAR_LAT_EN_MASK;
    }
}

/*!
 * @brief Enable/disable Doze mode for XSPI controller.
 *
 * @note Once doze mode is enabled, the XSPI controller will enter disable mode when system in low power modes.
 *
 * @param base XSPI peripheral base address
 * @param enable Specify operation:
 *          - \b true Enable Doze mode;
 *          - \b false Disable Doze mode.
 */
static inline void XSPI_EnableDozeMode(XSPI_Type *base, bool enable)
{
    if (enable)
    {
        base->MCR |= XSPI_MCR_DOZE_MASK;
    }
    else
    {
        base->MCR &= ~XSPI_MCR_DOZE_MASK;
    }
}

/*!
 * @brief Specify the logic level of the XSPI IOFA[3] and IOFA[2] output in the inactive state.
 *
 * @param base XSPI peripheral base address
 * @param signalMask Should be the OR'ed value of _xspi_external_signal.
 * @param outputLogic Output logic of selected signals,
 *          - \b false Output logic 0;
 *          - \b true Output logic 1.
 */
static inline void XSPI_SetSignalOutputValue(XSPI_Type *base, uint32_t signalMask, bool outputLogic)
{
    bool moduleEnabled = false;

    if (XSPI_CheckModuleEnabled(base))
    {
        moduleEnabled = true;
        XSPI_EnableModule(base, false);
    }

    if (outputLogic)
    {
        /* Output logic High for input mask of signals. */
        base->MCR |= signalMask;
    }
    else
    {
        /* Output logic Low for input mask of signals. */
        base->MCR &= ~signalMask;
    }

    if (moduleEnabled)
    {
        XSPI_EnableModule(base, true);
    }
}

/*!
 * @brief Enable/disable inverted serial clock output for XSPI controller.
 *
 * @note It is application responsibility to enable CLKn for external device(by change device's register).
 *
 * @param[in] base XSPI peripheral base address
 * @param[in] enable Enable/disable inverted serial clock output:
 *           - \b true Enable inverted serial clock output;
 *           - \b false Disable inverted serial clock output.
 */
static inline void XSPI_EnableInvertedSerialClockOutput(XSPI_Type *base, bool enable)
{
    bool moduleEnabled = false;

    if (XSPI_CheckModuleEnabled(base))
    {
        moduleEnabled = true;
        XSPI_EnableModule(base, false);
    }

    if (enable)
    {
        base->MCR |= XSPI_MCR_CKN_FA_EN_MASK;
    }
    else
    {
        base->MCR &= ~XSPI_MCR_CKN_FA_EN_MASK;
    }

    if (moduleEnabled)
    {
        XSPI_EnableModule(base, true);
    }
}

/*!
 * @brief Update DLL configuration.
 * 
 * @param[in] base XSPI peripheral base address.
 * @param[in] ptrDllConfig Pointer to the DLL configuration.
 * @param[in] enableDDR DDR mode is enabled or not.
 * @param[in] enableX16Mode X16 mode is enabled or not.
 * @param[in] xspiRootClk The frequency of xspi root clock, the unit is Hz.
 */
void XSPI_UpdateDllValue( XSPI_Type *base, xspi_dll_config_t *ptrDllConfig,
                        bool enableDDR, bool enableX16Mode, uint32_t xspiRootClk);

/*!
 * @brief Set Data learning configurations.
 * 
 * @param[in] base XSPI peripheral base address.
 * @param[in] ptrDataLearningConfig Pointer to data learning configuration.
 * 
 * @retval kStatus_XSPI_AhbReadAccessAsserted Fail to set data learning configuration due to AHB read access asserted.
 * @retval kStatus_XSPI_IPAccessAsserted Fail to set data learning configuration due to a IP access already asserted.
 * @retval kStatus_XSPI_AhbWriteAccessAsserted Fail to set data learning configuration due to AHB write access asserted.
 * @retval kStatus_Success  Successfully to set Data learning configurations.
 */
status_t XSPI_SetDataLearningConfig(XSPI_Type *base, xspi_data_learning_config_t *ptrDataLearningConfig);

/*!
 * @brief Check if data learning failure has detected.
 *
 * @param[in] base XSPI peripheral base address.
 *
 * @retval true Data learning has failed.
 * @retval false Data learning not fail.
 */
static inline bool XSPI_CheckDataLearningFailure(XSPI_Type *base)
{
    return (bool)((base->DLSR_F[0] & XSPI_DLSR_F_DLPFF_MASK) == XSPI_DLSR_F_DLPFF_MASK);
}

/*!
 * @brief Get data learning positive and negative edge match signature.
 *
 * @param[in] base XSPI peripheral base address.
 * @param[out] posEdgeMatch Pointer to the memory to store positive edge match signature.
 * @param[out] negEdgeMatch Pointer to the memory to store negative edge match signature.
 */
static inline void XSPI_GetDataLearningEdgeMatchSignature(XSPI_Type *base, uint8_t *posEdgeMatch, uint8_t *negEdgeMatch)
{
    uint32_t tmp32 = base->DLSR_F[0];

    *negEdgeMatch = (uint8_t)((tmp32 & XSPI_DLSR_F_NEG_EDGE_MASK) >> XSPI_DLSR_F_NEG_EDGE_SHIFT);
    *posEdgeMatch = (uint8_t)((tmp32 & XSPI_DLSR_F_POS_EDGE_MASK) >> XSPI_DLSR_F_POS_EDGE_SHIFT);
}
/* @} */

/*!
 * @name External Device Control Functional Interfaces
 */

/*!
 * @brief Set device configuration.
 * 
 * @param[in] base XSPI peripheral base address.
 * @param[in] devConfig Pointer to device configuration.
 *
 * @retval kStatus_XSPI_AhbReadAccessAsserted Fail to set device configuration due to AHB read access asserted.
 * @retval kStatus_XSPI_IPAccessAsserted Fail to set device configuration due to a IP access already asserted.
 * @retval kStatus_XSPI_AhbWriteAccessAsserted Fail to set device configuration due to AHB write access asserted.
 * @retval kStatus_Success  Successfully to set device configurations.
 */
status_t XSPI_SetDeviceConfig(XSPI_Type *base, xspi_device_config_t *devConfig);

/* @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enables the XSPI interrupts.
 *
 * @param base XSPI peripheral base address.
 * @param mask XSPI interrupt source.
 */

static inline void XSPI_EnableInterrupts(XSPI_Type *base, uint32_t mask)
{
    base->RSER |= mask;
}

/*!
 * @brief Disable the XSPI interrupts.
 *
 * @param base XSPI peripheral base address.
 * @param mask XSPI interrupt source.
 */
static inline void XSPI_DisableInterrupts(XSPI_Type *base, uint32_t mask)
{
    base->RSER &= ~mask;
}

/* @} */

/*! @name DMA control */
/*@{*/

/*!
 * @brief Enables or disables XSPI IP Tx FIFO DMA requests.
 *
 * @param[in] base XSPI peripheral base address.
 * @param[in] enable Enable flag for transmit DMA request. Pass true for enable, false for disable.
 */
static inline void XSPI_EnableTxDMA(XSPI_Type *base, bool enable)
{
    if (enable)
    {
        base->RSER |= XSPI_RSER_TBFDE_MASK;
    }
    else
    {
        base->RSER &= ~XSPI_RSER_TBFDE_MASK;
    }
}

/*!
 * @brief Enables or disables XSPI IP Rx FIFO DMA requests.
 *
 * @param[in] base XSPI peripheral base address.
 * @param[in] enable Enable flag for receive DMA request. Pass true for enable, false for disable.
 */
static inline void XSPI_EnableRxDMA(XSPI_Type *base, bool enable)
{
    if (enable)
    {
        base->RSER |= XSPI_RSER_RBDDE_MASK;
    }
    else
    {
        base->RSER &= ~XSPI_RSER_RBDDE_MASK;
    }
}

/*!
 * @brief Gets XSPI IP tx fifo address for DMA transfer.
 *
 * @param[in] base XSPI peripheral base address.
 *
 * @return The tx fifo address.
 */
static inline uint32_t XSPI_GetTxFifoAddress(XSPI_Type *base)
{
    return (uint32_t)&base->TBDR;
}

/*!
 * @brief Gets XSPI IP rx fifo address for DMA transfer.
 *
 * @param[in] base XSPI peripheral base address.
 *
 * @return The rx fifo address.
 */
static inline uint32_t XSPI_GetRxFifoAddress(XSPI_Type *base)
{
    return (uint32_t)&base->RBDR[0];
}

/*@}*/

/*!
 * @name Status
 * @{
 */
/*!
 * @brief Get the XSPI interrupt status flags.
 *
 * @param[in] base XSPI peripheral base address.
 *
 * @return interrupt status flag, use status flag to AND #xspi_flags_t could get the related status.
 */
static inline uint32_t XSPI_GetInterruptStatusFlags(XSPI_Type *base)
{
    return base->ERRSTAT;
}

/*! @brief Return whether the bus is idle.
 *
 * @param[in] base XSPI peripheral base address.
 *
 * @retval true Bus is idle.
 * @retval false Bus is busy.
 */
static inline bool XSPI_GetBusIdleStatus(XSPI_Type *base)
{
    return (bool)(XSPI_SR_BUSY_MASK != (base->SR & XSPI_SR_BUSY_MASK));
}

/*!
 * @brief Check if AHB read access has been requested or is ongoing.
 *
 * @param[in] base XSPI peripheral base address.
 *
 * @retval true AHB read access is requested or is ongoing.
 * @retval false AHB read access is not requested and is not ongoing.
 */
static inline bool XSPI_CheckAhbReadAccessAsserted(XSPI_Type *base)
{
    return (bool)((base->SR & XSPI_SR_AHB_ACC_MASK) != 0UL);
}

/*!
 * @brief Check if AHB write access has been requested or is ongoing.
 *
 * @param[in] base XSPI peripheral base address.
 *
 * @retval true AHB read access is requested or is ongoing.
 * @retval false AHB read access is not requested and is not ongoing.
 */
static inline bool XSPI_CheckAhbWriteAccessAsserted(XSPI_Type *base)
{
    return (bool)((base->SR & XSPI_SR_AWRACC_MASK) != 0UL);
}

/*@}*/

/*!
 * @name IPS Access Control Low-Level Interfaces
 * @{
 */

/*! @brief Clear the XSPI IP TX/RX buffer logic.
 *
 * @param[in] base XSPI peripheral base address.
 * @param[in] txFifo Pass true to reset TX FIFO.
 * @param[in] rxFifo Pass true to reset RX FIFO.
 */
static inline void XSPI_ResetTxRxBuffer(XSPI_Type *base, bool txFifo, bool rxFifo)
{
    if (txFifo)
    {
        base->MCR |= XSPI_MCR_CLR_TXF_MASK;
    }
    if (rxFifo)
    {
        base->MCR |= XSPI_MCR_CLR_RXF_MASK;
    }
}

/*!
 * @brief Clear TX buffer.
 *
 * @param[in] base XSPI peripheral base address.
 */
static inline void XSPI_ClearTxBuffer(XSPI_Type *base)
{
    base->MCR |= XSPI_MCR_CLR_TXF_MASK;

    for (uint8_t i = 0U; i < 10U; i++)
    {
        __NOP();
    }
}

/*!
 * @brief Update watermark for TX buffer.
 *
 * @param[in] base XSPI peripheral base address.
 * @param[in] waterMark The watermark to set, the unit is byte, should be the multiple of 4 byte.
 *
 * @retval  kStatus_XSPI_IPAccessAsserted Fail to update watermark for Tx buffer, due to IP access is asserted.
 * @retval kStatus_XSPI_WaterMarkIllegal Fail to update watermark for Tx buffer, due to input watermark is not the
 * multiple of 4 bytes.
 * @retval kStatus_Success Successful to update watermark.
 */
status_t XSPI_UpdateTxBufferWaterMark(XSPI_Type *base, uint32_t waterMark);

/*!
 * @brief Check if IP manager can write to TX buffer.
 *
 * @param[in] base XSPI peripheral base address.
 *
 * @retval true Tx buffer lock is open.
 * @retval false Tx buffer lock is not open.
 */
static inline bool XSPI_CheckTxBuffLockOpen(XSPI_Type *base)
{
    return (bool)((base->FSMSTAT & XSPI_FSMSTAT_STATE_MASK) == XSPI_FSMSTAT_STATE(1UL));
}

/*!
 * @brief Writes data into IPS TX Buffer.
 *
 * @param[in] base XSPI peripheral base address
 * @param[in] data The data bytes to send.
 */
static inline void XSPI_WriteTxBuffer(XSPI_Type *base, uint32_t data)
{
    base->TBDR = data;
}

/*!
 * @brief Clear RX buffer.
 *
 * @param[in] base XSPI peripheral base address.
 */
static inline void XSPI_ClearRxBuffer(XSPI_Type *base)
{
    base->MCR |= XSPI_MCR_CLR_RXF_MASK;

    for (uint8_t i = 0U; i < 10U; i++)
    {
        __NOP();
    }
}

/*!
 * @brief Receive data from IPX RX FIFO.
 *
 * @param[in] base XSPI peripheral base address
 * @param[in] fifoIndex Source fifo index.
 *
 * @return The data in the FIFO.
 */
static inline uint32_t XSPI_ReadRxBuffer(XSPI_Type *base, uint8_t fifoIndex)
{
    return base->RBDR[fifoIndex];
}

/*!
 * @brief Trigger a pop event for RX buffer pop event.
 *
 * @note Each pop event discard watermark + 1 enties from RX buffer.
 *
 * @param[in] base XSPI peripheral base address.
 */
static inline void XSPI_TriggerRxBufferPopEvent(XSPI_Type *base)
{
    base->FR = XSPI_FR_RBDF_MASK;
}

/*!
 * @brief Update watermark for RX buffer.
 *
 * @code
 * Set watermark as 4 bytes:
 * XSPI_UpdateRxBufferWaterMark(XSPI0, 4UL);
 * Set watermark as 8 bytes:
 * XSPI_UpdateRxBufferWaterMark(XSPI0, 8UL);
 * @endcode
 *
 *
 * @param[in] base XSPI peripheral base address.
 * @param[in] waterMark Specify the number of bytes in the RX buffer which causes XSPI to assert the watermark exceeded
 * flag, should be in multiple of 4 bytes.
 *
 * @retval kStatus_XSPI_IPAccessAsserted Fail to update watermark for Rx buffer, due to IP access is asserted.
 * @retval kStatus_XSPI_WaterMarkIllegal Fail to update watermark for Tx buffer, due to input watermark is not the
 * multiple of 4 bytes.
 * @retval kStatus_Success Successful to update watermark.
 */
status_t XSPI_UpdateRxBufferWaterMark(XSPI_Type *base, uint32_t waterMark);

/*!
 * @brief Check if RX buffer watermark is exceed.
 *
 * @param[in] base XSPI peripheral base address.
 *
 * @retval true The RX buffer watermark has been excceded.
 * @retval false The RX buffer watermark has not been exceeded.
 */
static inline bool XSPI_CheckRxBufferWaterMarkExceed(XSPI_Type *base)
{
    return (bool)((base->FR & XSPI_FR_RBDF_MASK) == XSPI_FR_RBDF_MASK);
}

/*!
 * @brief Get RX buffer aviailable bytes count.
 * 
 * @param[in] base XSPI peripheral base address.
 * 
 * @return The available counts if bytes in RX buffer.
 */
static inline uint32_t XSPI_GetRxBufferAvailableBytesCount(XSPI_Type *base)
{
    return ((base->RBSR & XSPI_RBSR_RDBFL_MASK) >> XSPI_RBSR_RDBFL_SHIFT) * 4UL;
}

/*!
 * @brief Get counts of bytes already removed from RX buffer.
 * 
 * @param[in] base XSPI peripheral base address.
 * 
 * @return Counts of removed bytes.
 */
static inline uint32_t XSPI_GetRxBufferRemovedBytesCount(XSPI_Type *base)
{
    return ((base->RBSR & XSPI_RBSR_RDCTR_MASK) >> XSPI_RBSR_RDCTR_SHIFT) * 4UL;
}

/*!
 * @brief Set exclusive access lock mode for the specific frad..
 * 
 * @param[in] base XSPI peripheral base address.
 * @param[in] ealMode Specify the exclusive access lock mode.
 * @param[in] fradId Specify the frad.
 */
void XSPI_SetSFPFradEALMode(XSPI_Type *base, xspi_exclusive_access_lock_mode_t ealMode, uint8_t fradId);

/*!
 * @brief Update SFP configurations, including MDAD configurations and FRAD configurations.
 *
 * @param[in] base XSPI peripheral base address.
 * @param[in] ptrMdadConfig Pointer to the SFP MDAD configuration.
 * @param[in] ptrFradConfig Pointer to the SFP FRAD configuration.
 */
void XSPI_UpdateSFPConfig(XSPI_Type *base,
                          xspi_sfp_mdad_config_t *ptrSfpMdadConfig,
                          xspi_sfp_frad_config_t *ptrSfpFradConfig);

/*!
 * @brief Check if SFP FRAD check is enabled for IP write access.
 *
 * @param[in] base XSPI peripheral base address.
 *
 * @retval false SFP FRAD check is disabled.
 * @retval true SFP FRAD check is enabled for IP write access.
 */
static inline bool XSPI_CheckSFPFradEnabled(XSPI_Type *base)
{
    return (bool)((base->MGC & XSPI_MGC_GVLDFRAD_MASK) != 0UL);
}

/*!
 * @brief Get MDAD check error reason for specific target group.
 * 
 * @param[in] base XSPI peripheral base address.
 * @param[in] tgId Specify the target group.
 *
 * @return The details of MDAD error reason, in type of @ref xspi_mdad_error_reason_t.
 */
xspi_mdad_error_reason_t XSPI_GetMdadErrorReason(XSPI_Type *base, xspi_target_group_t tgId);

/*!
 * @brief Get FARD latest transaction information.
 * 
 * @param[in] base XSPI peripheral base address.
 * @param[out] ptrInfo Pointer to the variable in type of @ref xspi_frad_transaction_info_t to store information.
 * @param[in] fradId Specify the frad Id.
 */
void XSPI_GetFradLastTransactionsInfo(XSPI_Type *base, xspi_frad_transaction_info_t *ptrInfo, uint8_t fradId);

/*!
 * @brief Update SFP arbitration lock timeout counter.
 *
 * @note The SFP arbitration lock time out counter starts when Page program wait flag asserted.
 *
 * @param[in] base XSPI peripheral base address.
 * @param[in] countValue The count value, specify the time in IPS clock cycles.
 *
 * @retval kStatus_XSPI_RegWriteLocked Write operation to related register is locked.
 * @retval kStatus_Success Success to update timeout counter.
 */
status_t XSPI_UpdateSFPArbitrationLockTimeoutCounter(XSPI_Type *base, uint32_t countValue);

/*!
 * @brief Clear address write status for specific target group.
 * 
 * @param[in] base XSPI peripheral base address.
 * @param[in] tgId Specify the target group to clear address write status.
 */
void XSPI_ClearTgAddrWriteStatus(XSPI_Type *base, xspi_target_group_t tgId);

/*!
 * @brief Get address write status for specific target group.
 * 
 * @param[in] base XSPI peripheral base address.
 * @param[in] tgId Specify the target group.
 * @param[out] ptrStatus Pointer to the variable in type of @ref xspi_tg_add_write_status_t
                        to store address write status.
 */
void XSPI_GetTgAddrWriteStatus(XSPI_Type *base, xspi_target_group_t tgId, xspi_tg_add_write_status_t *ptrStatus);

/*!
 * @brief Unlock Ip access arbitration.
 * 
 * @param[in] base XSPI peripheral base address.
 * @param[in] tgId Specify the target group.
 */
void XSPI_UnlockIpAccessArbitration(XSPI_Type *base, xspi_target_group_t tgId);

/*!
 * @brief Check if IP access is asserted.
 *
 * @param[in] base XSPI peripheral base address.
 *
 * @retval false The Access triggered by IP bus is not asserted.
 * @retval true The Access triggered by IP bus is asserted.
 */
static inline bool XSPI_CheckIPAccessAsserted(XSPI_Type *base)
{
    return (bool)((base->SR & XSPI_SR_IP_ACC_MASK) != 0UL);
}

/*!
 * @brief Clear Ip access sequence pointer.
 * 
 * @param[in] base XSPI peripheral base address.
 */
static inline void XSPI_ClearIPAccessSeqPointer(XSPI_Type *base)
{
    base->SPTRCLR |= XSPI_SPTRCLR_IPPTRC_MASK;
}

/*!
 * @brief Update the count of SFP access timeout counter.
 *
 * @note The counter starts when any IP access pass SFP check(if enabled), and request is granted by XSPI arbiter and
 * XSPI is IDLE.
 *
 * @note The counter does not start in case of IP access was granted by XSPI is not IDLE.
 *
 * @param base XSPI peripheral base address.
 * @param countValue The count value, specify the time in IPS clock cycles.
 *
 * @retval kStatus_XSPI_RegWriteLocked Write operation to related register is locked.
 * @retval kStatus_Success Success to update timeout counter.
 */
status_t XSPI_UpdateIPAccessTimeoutCounter(XSPI_Type *base, uint32_t countValue);

/*!
 * @brief Check if IP access is granted by XSPI arbitration.
 *
 * @param base XSPI peripheral base address.
 *
 * @retval true The IP access is granted arbitration.
 * @retval false No IP access is queued.
 */
static inline bool XSPI_CheckIPAccessGranted(XSPI_Type *base)
{
    return (bool)((base->FSMSTAT & XSPI_FSMSTAT_VLD_MASK) != 0UL);
}

/*!
 * @brief Check if IP write access is triggered.
 * 
 * @param[in] base XSPI peripheral base address.
 *
 * @retval true The IP write access is granted arbitration.
 * @retval false No IP write access is queued.
 */
static inline bool XSPI_CheckIpWriteTriggered(XSPI_Type *base)
{
    return (bool)((base->FSMSTAT & XSPI_FSMSTAT_STATE_MASK) == XSPI_FSMSTAT_STATE(2U));
}

/*!
 * @brief Check if IP read access is triggered.
 * 
 * @param[in] base XSPI peripheral base address.
 *
 * @retval true The IP read access is granted arbitration.
 * @retval false No IP read access is queued.
 */
static inline bool XSPI_CheckIpReadTriggered(XSPI_Type *base)
{
    return (bool)((base->FSMSTAT & XSPI_FSMSTAT_STATE_MASK) == XSPI_FSMSTAT_STATE(3U));
}

/*!
 * @brief Start IP access(including read and write).
 * 
 * @param[in] base XSPI peripheral base address.
 * @param[in] addr Address of external device to read/write.
 * @param[in] seqIndex Sequence Id of the pre-programed LUT.
 * @param[in] byteSize Size of data to read/write, the unit of byte.
 * @param[in] tgId Specify the target group used to write/read.
 * @param[in] lockArbitration Lock arbitration or not.
 *
 * @retval kStatus_XSPI_IpAccessAddrSettingInvalid Wrong Address input.
 * @retval kStatus_XSPI_IpAccessIPCRInvalid Wrong seqindex or bytesize input.
 * @retval kStatus_Success Success to start Ip access.
 */
status_t XSPI_StartIpAccess(XSPI_Type *base, uint32_t addr, uint8_t seqIndex,
                            size_t byteSize, xspi_target_group_t tgId, bool lockArbitration);

/* @} */

/*!
 * @name IPS Access Control Functional Interfaces
 * @{
 */

/*!
 * @brief Set IP access configurations, including SFP configurations, sfp arbitration lock timeout value, Ip access
 * timeout value.
 * 
 * @param[in] base XSPI peripheral base address.
 * @param[in] ptrIpAccessConfig Pointer to the variable which contains Ip access configurations.
 *
 * @retval kStatus_XSPI_RegWriteLocked Write operation to related register is locked.
 * @retval kStatus_Success Success to update timeout counter.
 */
status_t XSPI_SetIpAccessConfig(XSPI_Type *base, xspi_ip_access_config_t *ptrIpAccessConfig);

/*!
 * @brief Sends a buffer of data bytes using blocking method.
 *
 * @note This function blocks via polling until all bytes have been sent.
 *
 * @param[in] base XSPI peripheral base address
 * @param[in] buffer Pointer to the buffer to send.
 * @param[in] size The number of data bytes to send
 *
 * @retval kStatus_Success write success without error
 * @retval kStatus_XSPI_SequenceExecutionTimeout sequence execution timeout
 * @retval kStatus_XSPI_IpCommandSequenceError IP command sequence error detected
 * @retval kStatus_XSPI_IpCommandGrantTimeout IP command grant timeout detected
 */
status_t XSPI_WriteBlocking(XSPI_Type *base, uint8_t *buffer, size_t size);

/*!
 * @brief Receives a buffer of data bytes using a blocking method.
 *
 * @note This function blocks via polling until all bytes have been sent.
 *
 * @param[in] base XSPI peripheral base address
 * @param[out] buffer Pointer to the buffer to store read data.
 * @param[in] size The number of data bytes to receive
 *
 * @retval kStatus_Success read success without error
 * @retval kStatus_XSPI_SequenceExecutionTimeout sequence execution timeout
 * @retval kStatus_XSPI_IpCommandSequenceError IP command sequence error detected
 * @retval kStatus_XSPI_IpCommandGrantTimeout IP command grant timeout detected
 */
status_t XSPI_ReadBlocking(XSPI_Type *base, uint8_t *buffer, size_t size);

/*!
 * @brief Execute command to transfer a buffer data bytes using a blocking method.
 *
 * @param[in] base XSPI peripheral base address
 * @param[in] xfer pointer to the transfer structure.
 *
 * @retval kStatus_Success command transfer success without error
 * @retval kStatus_XSPI_SequenceExecutionTimeout sequence execution timeout
 * @retval kStatus_XSPI_IpCommandSequenceError IP command sequence error detected
 * @retval kStatus_XSPI_IpCommandGrantTimeout IP command grant timeout detected
 */
status_t XSPI_TransferBlocking(XSPI_Type *base, xspi_transfer_t *xfer);

/*!
 * @brief Initialize the XSPI handle which is used in transactional functions.
 *
 * @param[in] base XSPI peripheral base address.
 * @param[in] handle pointer to xspi_handle_t structure to store the transfer state.
 * @param[in] callback pointer to user callback function.
 * @param[in] userData user parameter passed to the callback function.
 */
void XSPI_TransferCreateHandle(XSPI_Type *base,
                               xspi_handle_t *handle,
                               xspi_transfer_callback_t callback,
                               void *userData);

/*!
 * @brief Perform a interrupt non-blocking transfer on the XSPI bus.
 *
 * @note Calling the API returns immediately after transfer initiates. The user needs
 * to call XSPI_GetTransferCount to poll the transfer status to check whether
 * the transfer is finished. If the return status is not kStatus_XSPI_Busy, the transfer
 * is finished. For XSPI_Read, the dataSize should be multiple of rx watermark level, or
 * XSPI could not read data properly.
 *
 * @param[in] base XSPI peripheral base address.
 * @param[in] handle pointer to xspi_handle_t structure which stores the transfer state.
 * @param[in] xfer pointer to xspi_transfer_t structure.
 *
 * @retval kStatus_Success Successfully start the data transmission.
 * @retval kStatus_XSPI_Busy Previous transmission still not finished.
 */
status_t XSPI_TransferNonBlocking(XSPI_Type *base, xspi_handle_t *handle, xspi_transfer_t *xfer);

/*!
 * @brief Get the master transfer status during a interrupt non-blocking transfer.
 *
 * @param[in] base XSPI peripheral base address.
 * @param[in] handle pointer to xspi_handle_t structure which stores the transfer state.
 * @param[out] count Number of bytes transferred so far by the non-blocking transaction.
 *
 * @retval kStatus_InvalidArgument count is Invalid.
 * @retval kStatus_Success Successfully return the count.
 */
status_t XSPI_TransferGetCount(XSPI_Type *base, xspi_handle_t *handle, size_t *count);

/*!
 * @brief Abort an interrupt non-blocking transfer early.
 *
 * @note This API can be called at any time when an interrupt non-blocking transfer initiates
 * to abort the transfer early.
 *
 * @param[in] base XSPI peripheral base address.
 * @param[in] handle pointer to xspi_handle_t structure which stores the transfer state
 */
void XSPI_TransferAbort(XSPI_Type *base, xspi_handle_t *handle);

/*! @} */

/*!
 * @name AHB Access Control Low-Level Interfaces
 * @{
 */

/*!
 * @brief Blocks to clear AHB buffer and abort ongoing prefetch transaction(if prefetch is enabled.)
 *
 * @note The function return only after all AHB buffer pointers are cleared.
 *
 * @param[in] base XSPI peripheral base address.
 */
static inline void XSPI_ClearAhbBuffer(XSPI_Type *base)
{
    base->SPTRCLR |= XSPI_SPTRCLR_ABRT_CLR_MASK;
    while ((base->SPTRCLR & XSPI_SPTRCLR_ABRT_CLR_MASK) != 0UL)
    {
    }
}

/*!
 * @brief Enable/disable the clearing of AHB read prefetch buffers when the same flash address is written by an
 *   AHB or IP command.
 *
 * @param[in] base XSPI peripheral base address.
 * @param[in] enable Used to enable/disable write flush.
 *
 * @retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted.
 * @retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted.
 * @retval kStatus_Success Successfully to enable/disable AHB buffer write flush.
 */
status_t XSPI_EnableAhbBufferWriteFlush(XSPI_Type *base, bool enable);

/*!
 * @brief Set AHB buffer configurations.
 * 
 * @param[in] base XSPI peripheral base address.
 * @param[in] ptrBuffer0Config Pointer to the variable which contain buffer0 configurations.
 * @param[in] ptrBuffer1Config Pointer to the variable which contain buffer1 configurations. 
 * @param[in] ptrBuffer2Config Pointer to the variable which contain buffer2 configurations.
 * @param[in] ptrBuffer3Config Pointer to the variable which contain buffer3 configurations.
 * 
 * @retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted.
 * @retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted.
 * @retval kStatus_Success Success to set AHB buffer configurations.
 */
status_t XSPI_SetAhbBufferConfig(XSPI_Type *base,
                                 xspi_ahbBuffer_config_t *ptrBuffer0Config,
                                 xspi_ahbBuffer_config_t *ptrBuffer1Config,
                                 xspi_ahbBuffer_config_t *ptrBuffer2Config,
                                 xspi_ahbBuffer_config_t *ptrBuffer3Config);

/*!
 * @brief Set Buffer size for all 4 AHB buffers.
 *
 * @param[in] base XSPI peripheral base address.
 * @param[in] buf0Size Specify size of AHB buffer0, range of 512, 256, 128, 64, 32, 16, 8, 4, 2, 0.
 * @param[in] buf1Size Specify size of AHB buffer1, range of 512, 256, 128, 64, 32, 16, 8, 4, 2, 0.
 * @param[in] buf2Size Specify size of AHB buffer2, range of 512, 256, 128, 64, 32, 16, 8, 4, 2, 0.
 * @param[in] buf3Size Specify size of AHB buffer3, range of 512, 256, 128, 64, 32, 16, 8, 4, 2, 0.
 *
 * @retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted.
 * @retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted.
 * @retval kStatus_Success Success to set AHB buffer size.
 */
status_t XSPI_UpdateAhbBufferSize(XSPI_Type *base, uint16_t buf0Size,
                                 uint16_t buf1Size, uint16_t buf2Size, uint16_t buf3Size);

/*!
 * @brief Get status of AHB sub buffer.
 *
 * @note This function only useful when sub-division feature of the selected AHB buffer is enabled.
 *
 * @param[in] base XSPI peripheral base address.
 * @param[in] ahbBufferId The Id of AHB buffer, range from 0 to 3.
 * @param[in] subBufferId The Id of AHB buffer sub division, range from 0 to 3.
 *
 * @return Current status of selected AHB sub buffer, in type of @ref xspi_ahb_sub_buffer_status_t.
 */
xspi_ahb_sub_buffer_status_t XSPI_GetAhbSubBufferStatus(XSPI_Type *base, uint8_t ahbBufferId, uint8_t subBufferId);

/*!
 * @brief Start AHB buffer performance monitor.
 * 
 * @param[in] base XSPI peripheral base address.
 */
static inline void XSPI_StartAhbBufferPerfMonitor(XSPI_Type *base)
{
    base->AHB_PERF_CTRL |= XSPI_AHB_PERF_CTRL_CNTSTART_MASK;
}

/*!
 * @brief Enable AHB buffer performance monitor for selected AHB buffer's sub buffer.
 * 
 * @param[in] base XSPI peripheral base address.
 * @param[in] ahbBufferId Specify the selected AHB buffer.
 * @param[in] subBufferId Specify the selected sub-buffer.
 */
void XSPI_EnableAhbBufferPerfMonitor(XSPI_Type *base, uint8_t ahbBufferId, uint8_t subBufferId);

/*!
 * @brief Disable AHB buffer performance monitor for selected AHB buffer.
 * 
 * @param[in] base XSPI peripheral base address.
 * @param[in] ahbBufferId Specify the selected AHB buffer.
 */
static inline void XSPI_DisableAhbBufferPerfMonitor(XSPI_Type *base, uint8_t ahbBufferId)
{
    base->AHB_PERF_CTRL &= (uint32_t)(~(uint32_t)(XSPI_AHB_PERF_CTRL_BUF0_EN_MASK << (uint32_t)(ahbBufferId)));
}

/*!
 * @brief Stop AHB buffer performance monitor.
 * 
 * @param[in] base XSPI peripheral base address.
 */
static inline void XSPI_StopAhbBufferPerfMonitor(XSPI_Type *base)
{
    base->AHB_PERF_CTRL |= XSPI_AHB_PERF_CTRL_CNTSTP_MASK;
}

/*!
 * @brief Get AHB buffer performance monitor result.
 * 
 * @param[in] base XSPI peripheral base address.
 * @param[in] ahbBufferId Specify AHB buffer Id.
 * @param[out] ptrPerfMonitorResult Pointer to the variable to store selected AHB buffer's performance monitor result.
 */
static inline void XSPI_GetAhbBufferPerfMonitorResult(XSPI_Type *base,
                                                      uint8_t ahbBufferId,
                                                      xspi_ahbBuffer_perf_monitor_result_t *ptrPerfMonitorResult)
{
    uint32_t tmp32 = 0UL;

    tmp32                                 = (uint32_t)(base->AHB_PERF_BUF[ahbBufferId]);
    ptrPerfMonitorResult->bufferMissCount = (uint16_t)(tmp32 & 0xFFFFUL);
    ptrPerfMonitorResult->bufferHitCount  = (uint16_t)((tmp32 & 0xFFFF0000UL) >> 16UL);
}

/*!
 * @brief Check if AHB buffer performance monitor timeout counter is overflow.
 * 
 * @param base XSPI peripheral base address.
 *
 * @retval false AHB buffer performance monitor timeout counter is not overflow.
 * @retval true AHB buffer performance monitor timeout counter is overflow.
 */
static inline bool XSPI_CheckAhbBufferPerfMonitorTimeCounterOverflow(XSPI_Type *base)
{
    return (bool)((base->AHB_PERF_CTRL & XSPI_AHB_PERF_CTRL_TCNTO_MASK) != 0UL);
}

/*!
 * @brief Check if AHB buffer performance monitor buffer hit counter is overflow.
 * 
 * @param[in] base XSPI peripheral base address.
 * @param[in] ahbBufferId Specify the AHB buffer Id.
 *
 * @retval false Overflow not detected.
 * @retval true Overflow is detected.
 */
static inline bool XSPI_CheckAhbBufferPerfMonitorHitOverflow(XSPI_Type *base, uint8_t ahbBufferId)
{
    return (bool)((base->AHB_PERF_CTRL & (XSPI_AHB_PERF_CTRL_BUF0_HIT_OVF_MASK << (uint32_t)ahbBufferId)) != 0UL);
}

/*!
 * @brief Check if AHB buffer performance monitor buffer miss counter is overflow.
 * 
 * @param[in] base XSPI peripheral base address.
 * @param[in] ahbBufferId Specify the AHB buffer Id.
 *
 * @retval false Overflow not detected.
 * @retval true Overflow is detected.
 */
static inline bool XSPI_CheckAhbBufferPerfMonitorMissOverflow(XSPI_Type *base, uint8_t ahbBufferId)
{
    return (bool)((base->AHB_PERF_CTRL & ((uint32_t)XSPI_AHB_PERF_CTRL_BUF0_MISS_OVF_MASK << (uint32_t)ahbBufferId)) != 0UL);
}

/*!
 * @brief Get AHB buffer performance monitor timeout value.
 *
 * @param[in] base XSPI peripheral base address.
 *
 * @return The value of time counter, in AHB clock cycles, since the performance monitor was running.
 */
static inline uint32_t XSPI_GetAhbBufferPerfMonitorTimeCounter(XSPI_Type *base)
{
    return base->AHB_PERF_TIME_CNT;
}

/*!
 * @brief Set AHB transaction(read/write) split size.
 *
 * @note For AHB write, if enable split feature(ahbSplitSize not set as kXSPI_AhbSplitSizeDisabled), XSPI will split one
 * single AHB write burst into smaller bursts on external device side.
 *
 * @note For AHB read, if enable split feature, HW will realign the prefetch size to split size and in that way split
 * a single read burst into smaller bursts.
 *
 * @param[in] base XSPI peripheral base address.
 * @param[in] ahbSplitSize Specify the AHB split size.
 *
 * @retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted
 * @retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted
 * @retval kStatus_XSPI_RegWriteLocked Fail due to write operation to related registers is locked.
 * @retval kStatus_Success Success to set AHB access split size.
 */
status_t XSPI_SetAhbAccessSplitSize(XSPI_Type *base, xspi_ahb_split_size_t ahbSplitSize);

/*!
 * @brief Set AHB transaction(read/write) boundary.
 *
 * @note For AHB write, XSPI keeps track of the start address and then compares it with the address of subsequent
 * transaction receive on the AHB bus, when the input alignment is reached, XSPI negates AHB HREADY to block new
 * accesses. This signal will be kept low until all the previous received write data is written to external memory and
 * chip select is de-asserted. After that it allows next AHB write data to be received by making HREADY high thus
 * ensuring that transaction is split at address boundary on external memory.
 *
 * @note For AHB read, XSPI checks the start address and end address to see if it is crossing the address boundary
 * specified by input alignment. If the transaction crosses the address boundary, then it reduces the transaction size
 * such that the data pre-fetch is stopped before the address boundary. Now if the AHB master is reading the data
 * sequentially it will get buffer hits up to the input alignment boundary. When it reaches the next address boundary
 * it will get a buffer miss and a new data pre-fetch will be launched towards the external memory device.
 *
 * @param[in] base XSPI peripheral base address.
 * @param[in] alignment Specify the AHB alignment, in type of @ref xspi_ahb_alignment_t.
 *
 * @retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted
 * @retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted
 * @retval kStatus_XSPI_RegWriteLocked Fail due to write operation to related registers is locked.
 * @retval kStatus_Success Success to set AHB access boundary.
 */
status_t XSPI_SetAhbAccessBoundary(XSPI_Type *base, xspi_ahb_alignment_t alignment);

/*!
 * @brief Set AHB read sequence Id.
 * 
 * @param[in] base XSPI peripheral base address.
 * @param[in] seqId Specify the sequence Id in LUT used for AHB read.
 *
 * @retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted
 * @retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted
 * @retval kStatus_XSPI_RegWriteLocked Fail due to write operation to related registers is locked.
 * @retval kStatus_Success Success to set AHB read sequence Id.
 */
status_t XSPI_SetAhbReadDataSeqId(XSPI_Type *base, uint8_t seqId);

/*!
 * @brief Set AHB write sequence Id.
 * 
 * @param[in] base XSPI peripheral base address.
 * @param[in] seqId Specify the sequence Id in LUT used for AHB write.
 *
 * @retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted
 * @retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted
 * @retval kStatus_XSPI_RegWriteLocked Fail due to write operation to related registers is locked.
 * @retval kStatus_Success Success to set AHB write sequence Id.
 */
status_t XSPI_SetAhbWriteDataSeqId(XSPI_Type *base, uint8_t seqId);

/*!
 * @brief Specify how long XSPI can hold HEADY low while waiting for response to an AHB transfer.
 *
 * @note If the specified time out value expired, an AHB illegal transaction error will be triggerred.
 *
 * @param[in] base XSPI peripheral base address.
 * @param[in] timeoutValue In multiples of 50000 AHB clock cycles, default value is 3,
 *                      it means waiting for 150000 AHB clock cycles.
 *
 * @retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted
 * @retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted
 * @retval kStatus_Success Success to set AHB HREADY timeout value.
 */
status_t XSPI_UpdateAhbHreadyTimeOutValue(XSPI_Type *base, uint16_t timeoutValue);

/*!
 * @brief Pre-define error payload which will be provided on the read data bus when the HEADY timeout counter expires.
 *
 * @note If the incoming AHB read request master is not mapped to any of the AHB buffer, the XSPI will keep the AHB
 * HREADY signal low and will provided this pre-defined error payload on the AHB read data bus when the HEADY timeout
 * counter expires.
 *
 * @param[in] base XSPI peripheral base address.
 * @param[in] highPayload High 32bits payload to set.
 * @param[in] lowPayload Low 32bits payload to set.

 * @retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted
 * @retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted
 * @retval kStatus_Success Success to set AHB HREADY timeout value.
 */
status_t XSPI_SetAhbErrorPayload(XSPI_Type *base, uint32_t highPayload, uint32_t lowPayload);

/*!
 * @brief Return AHB read error information.
 * 
 * @param[in] base XSPI peripheral base address.
 *
 * @return Latest AHB read error information, in type of xspi_ahb_read_error_info_t.
 */
xspi_ahb_read_error_info_t XSPI_ReturnAhbReadErrorInfo(XSPI_Type *base);

/*!
 * @brief Clear AHB access sequence pointer.
 * 
 * @param[in] base XSPI peripheral base address.
 */
static inline void XSPI_ClearAhbAccessSeqPointer(XSPI_Type *base)
{
    base->SPTRCLR |= XSPI_SPTRCLR_BFPTRC_MASK;
}

/*!
 * @brief Get Ahb request suspend information if priority mechanism is enabled.
 *
 * @param[in] base XSPI peripheral base address.
 * @param[out] ptrSuspendInfo Contain latest suspend info, the value may be 0xFF if the item is invalid in current
 * suspend state.
 */
void XSPI_GetAhbRequestSuspendInfo(XSPI_Type *base, xspi_ahb_request_suspend_info_t *ptrSuspendInfo);

/*!
 * @brief Enable/disable AHB Read Prefetch feature.
 * 
 * @param[in] base XSPI peripheral base address.
 * @param[in] enable Used to enable/disable AHB read prefetch:
 *               - \b false Disable AHB read prefetch;
 *               - \b true Enable AHB read prefetch.   
 */
static inline void XSPI_EnableAhbReadPrefetch(XSPI_Type *base, bool enable)
{
    if (enable)
    {
        base->SPTRCLR &= ~XSPI_SPTRCLR_PREFETCH_DIS_MASK;
    }
    else
    {
        base->SPTRCLR |= XSPI_SPTRCLR_PREFETCH_DIS_MASK;
    }
}

/*!
 * @brief Block access(write and read) after the AHB write operation.
 *
 * @note If external flash support RWW, read should not be blocked:
 * @code
 *  XSPI_BlockAccessAfterAhbWrite(XSPI0, true, false);
 * @endcode
 *
 * @note If either of access is blocked, the page program wait flag will be asserted after
 * an AHB write sequence completed. The assertion of flag will lock the arbitration and all
 * access to the external memory are blocked. And the internal "page wait time" counter
 * starts(Invoke XSPI_UpdatePageWaitTimeCounter to update counter value). After this counter
 * reaches the value, a read is triggered by the XSPI module to read external device's
 * status register(The seq id should be pre-defiend by XSPI_SetAhbReadStatusRegSeqId),
 * and the value is stored in the XSPI internal regsiter. And there are two
 * options(Invoke XSPI_SelectPPWFlagClearPolicy to select) to clear the asserted page program wait flag.
 *      1. Automatic cleared by XSPI hardware;
 *      2. Cleared by software.
 *
 * @note As soon as the page program wait flag is asserted, another counter(SFP arbitration
 * lock counter) also started, if the flag not cleared in desired counter value the
 * arbitration lock timeout error will be generated.
 *
 * @param[in] base XSPI peripheral base address.
 * @param[in] blockSequentWrite Block sequence write or not.
 * @param[in] blockRead Block read or not.
 *
 * @retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted
 * @retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted
 * @retval kStatus_Success Success to set related registers..
 */
status_t XSPI_BlockAccessAfterAhbWrite(XSPI_Type *base, bool blockSequentWrite, bool blockRead);

/*!
 * @brief Set Page program wait flag clear policy.
 * 
 * @note If set as hardware policy, the device's WIP information should be set by invoking XSPI_SetSFMStatusRegInfo()
 *
 * @param[in] base XSPI peripheral base address.
 * @param[in] policy Specify the policy to clear page program wait flag.
 *
 * @retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted
 * @retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted
 * @retval kStatus_XSPI_RegWriteLocked Fail due to write operation to related registers is locked.
 * @retval kStatus_Success Success to set PPW flag clear policy.
 */
status_t XSPI_SelectPPWFlagClearPolicy(XSPI_Type *base, xspi_ppw_flag_clear_policy_t policy);

/*!
 * @brief Update page wait timeout counter.
 *
 * @param[in] base XSPI peripheral base address.
 * @param[in] countValue The value of counter, in AHB clock cycles.
 *
 * @retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted
 * @retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted
 * @retval kStatus_XSPI_PageProgramWaitFlagAsserted Page program wait flag already asserted.
 * @retval kStatus_Success Successfully to update page wait timeout counter.
 */
status_t XSPI_UpdatePageWaitTimeCounter(XSPI_Type *base, uint32_t countValue);

/*!
 * @brief Set AHB read status register sequence Id
 *
 * @note The read status sequence only triggerred when the page wait time counter expired.
 *
 * @param[in] base XSPI peripheral base address.
 * @param[in] seqId Specify the sequence Id in LUT used for AHB read status register.
 *
 * @retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted
 * @retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted
 * @retval kStatus_XSPI_RegWriteLocked Fail due to write operation to related registers is locked.
 * @retval kStatus_Success Success to set AHB read status register sequence Id.
 */
status_t XSPI_SetAhbReadStatusRegSeqId(XSPI_Type *base, uint8_t seqId);

/*!
 * @brief Get external serial flash's status register value.
 *
 * @note This function is only useful after the Page program wait flag is asserted due to
 * either wait/read access is blocked after the AHB write operation.
 *
 * @param[in] base XSPI peripheral base address.
 *
 * @return The status regsiter value of external device.
 */
static inline uint16_t XSPI_GetSFMStatusRegValue(XSPI_Type *base)
{
    while ((base->PPW_RDSR & XSPI_PPW_RDSR_VALID_MASK) == 0UL)
    {
    }

    return (uint16_t)(base->PPW_RDSR & XSPI_PPW_RDSR_RDSR_MASK);
}

/*!
 * @brief Set Serial flash memory status register information
 * 
 * @param[in] base XSPI peripheral base address.
 * @param[in] ptrStatusRegInfo Pointer to the variable which contain status register information.
 *
 * @retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted
 * @retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted
 * @retval kStatus_XSPI_PageProgramWaitFlagAsserted Page program wait flag already asserted.
 * @retval kStatus_Success Successfully to set status register information.
 */
status_t XSPI_SetSFMStatusRegInfo(XSPI_Type *base, xspi_device_status_reg_info_t *ptrStatusRegInfo);

/*! @} */

/*!
 * @name AHB Access Control Functional Interfaces
 * @{
 */

/*!
 * @brief Set AHB access configuration.
 * 
 * @param[in] base XSPI peripheral base address.
 * @param[in] ptrAhbAccessConfig Pointer to the variable which contains AHB access configurations.
 *
 * @retval kStatus_XSPI_AhbReadAccessAsserted Fail due to an AHB read access already asserted
 * @retval kStatus_XSPI_AhbWriteAccessAsserted Fail due to an AHB write access already asserted
 * @retval kStatus_XSPI_RegWriteLocked Fail due to write operation to related registers is locked.
 * @retval kStatus_Success Success to set AHB read status register sequence Id.
 */
status_t XSPI_SetAhbAccessConfig(XSPI_Type *base, xspi_ahb_access_config_t *ptrAhbAccessConfig);

/*! @} */



/*! @}  */

#if defined(__cplusplus)
}
#endif /*_cplusplus. */
/*@}*/

#endif /* FSL_XSPI_H_ */
