/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_SDIOSLV_SDU_H_
#define _FSL_SDIOSLV_SDU_H_

#include "fsl_common.h"
#include "cis_table.h"

/*!
 * @addtogroup sdioslv_sdu_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define SDU_INT_CPU_NUM   kSDIOSLV_INT_CPUNum3
#define SDU_USED_FUN_NUM  1
#define SDU_USED_PORT_NUM 32

/*! @brief Maximum functions supported by SDU */
#define SDU_MAX_FUNCTION_NUM 7

/*! @brief Maximum data ports supported by SDU per function */
#define SDU_MAX_PORT_NUM 32

#define sdu_fbr_fnN_base(FN)    (SDU_FN0_CARD_BASE + 0x10 + (0x10 * FN))
#define sdu_fbr_fnN_fn_code(FN) (sdu_fbr_fnN_base(FN) + 0x0)

#define sdu_fbr_fnN_fn_code_code_HI 3
#define sdu_fbr_fnN_fn_code_code_LO 0


/*! @brief MACRO used to access register of SDU */
#define SDU_REGS8(x) (*((volatile uint8_t *)x))
/*! @brief MACRO used to read SDU register */
#define SDU_READ_REGS8(reg, val) ((val) = SDU_REGS8(reg))
/*! @brief MACRO used to write SDU register */
#define SDU_WRITE_REGS8(reg, val) (SDU_REGS8(reg) = (val))
/*! @brief MACRO used to set bits of SDU register */
#define SDU_REGS8_SETBITS(reg, val) (SDU_REGS8(reg) |= (uint8_t)(val))
/*! @brief MACRO used to clear bits of SDU register */
#define SDU_REGS8_CLRBITS(reg, val) (SDU_REGS8(reg) = (uint8_t)(SDU_REGS8(reg) & ~(val)))

/*! @brief Address of scratch register (group 2, offset 0) within function */
#define SDU_SCRATCH2_OFFSET0_ADDR 0xE8

/*! @brief SDU SDIO configuration base (SDU_FN0_CARD_BASE defined in device) */
#define SDU_SDIO_CFG_BASE SDU_FN0_CARD_BASE

/*! @brief Address offset of CCR between two functions */
#define SDIO_CCR_FUNC_OFFSET 0x00000100

/*! @brief SDIO I/O Enable */
#define SDIO_IO_ENABLE (SDU_SDIO_CFG_BASE + 0x02)

/*! @brief SDIO Bus Speed Select */
#define SDIO_FUNC0_BSS              (SDU_SDIO_CFG_BASE + 0x13)
#define SDIO_FUNC0_BSS_SUPPORT_MASK 0x1
#define SDIO_FUNC0_BSS_MODE_BIT     0x1
#define SDIO_FUNC0_BSS_MODE_MASK    0xE

/*! @brief Interrupt mask register for function 0 */
#define SDIO_CCR_FUNC0_CARD_INT_MSK (SDU_SDIO_CFG_BASE + 0x91)

/*! @brief Bit Def. Host Transfer Status (HostTransferStatus) */
#define SDIO_CCR_HOST_DnLdReStart (1 << 0)
#define SDIO_CCR_HOST_UpLdReStart (1 << 1)
#define SDIO_CCR_HOST_DnLdCRC_err (1 << 2)

/*! @brief Bit Def. Card To Host Interrupt Event (CardToHostEvent) */
#define SDIO_CCR_CS_DnLdRdy    (1 << 0)
#define SDIO_CCR_CS_UpLdRdy    (1 << 1)
#define SDIO_CCR_CS_ReadCISRdy (1 << 2)
#define SDIO_CCR_CS_CmdUpLdRdy (1 << 6)
#define SDIO_CCR_CS_CmdDnLdRdy (1 << 7)

/*! @brief Bit Def. Card Interrupt Mask (CardIntMask) */
#define SDIO_CCR_CIM_DnLdOvr    (1 << 0)
#define SDIO_CCR_CIM_UpLdOvr    (1 << 1)
#define SDIO_CCR_CIM_Abort      (1 << 2)
#define SDIO_CCR_CIM_PwrDn      (1 << 3)
#define SDIO_CCR_CIM_PwrUp      (1 << 4)
#define SDIO_CCR_CIM_CmdUpLdOvr (1 << 10)
#define SDIO_CCR_CIM_CmdDnLdOvr (1 << 11)

#define SDIO_CCR_CIM_MASK 0x0C07

/*! @brief Bit Def. Card Interrupt Status (CardIntStatus) */
#define SDIO_CCR_CIC_DnLdOvr    (1 << 0)
#define SDIO_CCR_CIC_UpLdOvr    (1 << 1)
#define SDIO_CCR_CIC_Abort      (1 << 2)
#define SDIO_CCR_CIC_PwrDn      (1 << 3)
#define SDIO_CCR_CIC_PwrUp      (1 << 4)
#define SDIO_CCR_CIC_CmdUpLdOvr (1 << 10)
#define SDIO_CCR_CIC_CmdDnLdOvr (1 << 11)
#define SDIO_CCR_CIC_ALL \
    (SDIO_CCR_CIC_DnLdOvr | SDIO_CCR_CIC_UpLdOvr | SDIO_CCR_CIC_CmdUpLdOvr | SDIO_CCR_CIC_CmdDnLdOvr)

#define SDIO_CCR_CIC_MASK 0x0C1F

/*! @brief Bit Def. Default setting ISR bit clear after read (CardIntMode) */
#define CARD_INT_MODE_MSK 0x00000C03

/*! @brief Bit Def. Command port configuration register (CmdPortConfig) */
#define CMD_TX_LEN_BIT_OFFSET (0)
#define CMD_RD_LEN_BIT_OFFSET (2)

/*! @brief Bit Def. Config2 register (Config2) */
#define CONFIG2_ASYNC_INT           (1 << 3)
#define CONFIG2_CMD53_NEW_MODE      (1 << 8)
#define CONFIG2_DNLD_RDY_AUTO_RESET (1 << 10)
#define CONFIG2_UPLD_RDY_AUTO_RESET (1 << 11)
#define CONFIG2_TX_LEN_BIT_OFFSET   (12)
#define CONFIG2_RD_LEN_BIT_OFFSET   (14)

#define CONFIG2_DEFAULT_SETTING \
    (CONFIG2_ASYNC_INT | CONFIG2_CMD53_NEW_MODE | CONFIG2_DNLD_RDY_AUTO_RESET | CONFIG2_UPLD_RDY_AUTO_RESET)


/*! @name Driver version */
/*@{*/
/*! @brief Driver version 1.0.0. */
#define FSL_SDIOSLV_SDU_DRIVER_VERSION (MAKE_VERSION(1U, 0U, 0U))
/*@}*/

/*! @brief SDIO status */
enum _sdioslv_status
{
    kStatus_SDIOSLV_CmdPending       = MAKE_STATUS(kStatusGroup_SDIOSLV, 0U), /*!< previous command is under working. */
    kStatus_SDIOSLV_SendFull         = MAKE_STATUS(kStatusGroup_SDIOSLV, 1U), /*!< all data slots are occupied. */
    kStatus_SDIOSLV_FuncEnabled      = MAKE_STATUS(kStatusGroup_SDIOSLV, 2U), /*!< function enabled */
    kStatus_SDIOSLV_FuncDisabled     = MAKE_STATUS(kStatusGroup_SDIOSLV, 3U), /*!< function disabled */
    kStatus_SDIOSLV_FuncSuspended    = MAKE_STATUS(kStatusGroup_SDIOSLV, 4U), /*!< function suspended */
    kStatus_SDIOSLV_FuncResumed      = MAKE_STATUS(kStatusGroup_SDIOSLV, 5U), /*!< function resumed */
    kStatus_SDIOSLV_FuncSendComplete = MAKE_STATUS(kStatusGroup_SDIOSLV, 6U), /*!< function send complete */
    kStatus_SDIOSLV_FuncReadComplete = MAKE_STATUS(kStatusGroup_SDIOSLV, 7U), /*!< function read complete */
    kStatus_SDIOSLV_FuncRequestBuffer = MAKE_STATUS(kStatusGroup_SDIOSLV, 8U), /*!< function request read buffer */
};

/*! @brief SDIO card function number */
typedef enum _sdioslv_int_cpu_num
{
    kSDIOSLV_INT_CPUNum1 = 1, /*!< sdio interrupt to CPU1 */
    kSDIOSLV_INT_CPUNum2 = 2, /*!< sdio interrupt to CPU2 */
    kSDIOSLV_INT_CPUNum3 = 4, /*!< sdio interrupt to CPU3 */
} sdioslv_int_cpu_num_t;

/*! @brief SDIO card function number */
typedef enum _sdioslv_func_num
{
    kSDIOSLV_FunctionNum1 = 1, /*!< sdio function1 */
    kSDIOSLV_FunctionNum2 = 2, /*!< sdio function2 */
    kSDIOSLV_FunctionNum3 = 3, /*!< sdio function3 */
    kSDIOSLV_FunctionNum4 = 4, /*!< sdio function4 */
    kSDIOSLV_FunctionNum5 = 5, /*!< sdio function5 */
    kSDIOSLV_FunctionNum6 = 6, /*!< sdio function6 */
    kSDIOSLV_FunctionNum7 = 7, /*!< sdio function7 */
} sdioslv_func_t;

/*! @brief SDIO port number (per function) */
typedef enum _sdioslv_port_num
{
    kSDIOSLV_DataPortNum0  = 0,  /*!< sdio dataport0 */
    kSDIOSLV_DataPortNum1  = 1,  /*!< sdio dataport1 */
    kSDIOSLV_DataPortNum2  = 2,  /*!< sdio dataport2 */
    kSDIOSLV_DataPortNum3  = 3,  /*!< sdio dataport3 */
    kSDIOSLV_DataPortNum4  = 4,  /*!< sdio dataport4 */
    kSDIOSLV_DataPortNum5  = 5,  /*!< sdio dataport5 */
    kSDIOSLV_DataPortNum6  = 6,  /*!< sdio dataport6 */
    kSDIOSLV_DataPortNum7  = 7,  /*!< sdio dataport7 */
    kSDIOSLV_DataPortNum8  = 8,  /*!< sdio dataport8 */
    kSDIOSLV_DataPortNum9  = 9,  /*!< sdio dataport9 */
    kSDIOSLV_DataPortNum10 = 10, /*!< sdio dataport10 */
    kSDIOSLV_DataPortNum11 = 11, /*!< sdio dataport11 */
    kSDIOSLV_DataPortNum12 = 12, /*!< sdio dataport12 */
    kSDIOSLV_DataPortNum13 = 13, /*!< sdio dataport13 */
    kSDIOSLV_DataPortNum14 = 14, /*!< sdio dataport14 */
    kSDIOSLV_DataPortNum15 = 15, /*!< sdio dataport15 */
    kSDIOSLV_DataPortNum16 = 16, /*!< sdio dataport16 */
    kSDIOSLV_DataPortNum17 = 17, /*!< sdio dataport17 */
    kSDIOSLV_DataPortNum18 = 18, /*!< sdio dataport18 */
    kSDIOSLV_DataPortNum19 = 19, /*!< sdio dataport19 */
    kSDIOSLV_DataPortNum20 = 20, /*!< sdio dataport20 */
    kSDIOSLV_DataPortNum21 = 21, /*!< sdio dataport21 */
    kSDIOSLV_DataPortNum22 = 22, /*!< sdio dataport22 */
    kSDIOSLV_DataPortNum23 = 23, /*!< sdio dataport23 */
    kSDIOSLV_DataPortNum24 = 24, /*!< sdio dataport24 */
    kSDIOSLV_DataPortNum25 = 25, /*!< sdio dataport25 */
    kSDIOSLV_DataPortNum26 = 26, /*!< sdio dataport26 */
    kSDIOSLV_DataPortNum27 = 27, /*!< sdio dataport27 */
    kSDIOSLV_DataPortNum28 = 28, /*!< sdio dataport28 */
    kSDIOSLV_DataPortNum29 = 29, /*!< sdio dataport29 */
    kSDIOSLV_DataPortNum30 = 30, /*!< sdio dataport30 */
    kSDIOSLV_DataPortNum31 = 31, /*!< sdio dataport31 */
    kSDIOSLV_CmdPortNum0   = 32, /*!< sdio cmdport0 */
} sdioslv_port_t;

/*! @brief SDIO Bus Speed */
typedef enum _sdioslv_bus_speed
{
    kSDIOSLV_SDR12_MODE  = 0, /*!< SDR12 mode  => 25Mhz */
    kSDIOSLV_SDR25_MODE  = 1, /*!< SDR25 mode  => 50Mhz */
    kSDIOSLV_SDR50_MODE  = 2, /*!< SDR50 mode  => 100Mhz */
    kSDIOSLV_SDR104_MODE = 3, /*!< SDR104 mode => 208Mhz */
} sdioslv_bus_speed_t;

/*! @brief Scratch register group */
typedef enum _sdioslv_scratch_group
{
    kSDIOSLV_ScratchGroup0 = 0, /*!< sdio scratch1 in FW18 0xnD4 n:1..7 16 bits */
    kSDIOSLV_ScratchGroup1 = 1, /*!< sdio scratch2 in FW18 0xnB0 n:1..7 16 bits */
    kSDIOSLV_ScratchGroup2 = 2, /*!< sdio scratch group 2 in SDU 0xnE8 n:1..7 32 bits */
    kSDIOSLV_ScratchGroup3 = 3, /*!< sdio scratch group 3 in SDU 0xnEC n:1..7 32 bits */
    kSDIOSLV_ScratchGroup4 = 4, /*!< sdio scratch group 4 in SDU 0xnF0 n:1..7 32 bits */
    kSDIOSLV_ScratchGroup5 = 5, /*!< sdio scratch group 5 in SDU 0xnF4 n:1..7 32 bits */
    kSDIOSLV_ScratchGroup6 = 6, /*!< sdio scratch group 6 in SDU 0xnF8 n:1..7 32 bits */
    kSDIOSLV_ScratchGroup7 = 7, /*!< sdio scratch group 7 in SDU 0xnFC n:1..7 32 bits */
} sdioslv_scratch_group_t;

/*! @brief Scratch register offset in a group */
typedef enum _sdioslv_scratch_offset
{
    kSDIOSLV_ScratchOffset0 = 0, /*!< sdio scratchoffset0 */
    kSDIOSLV_ScratchOffset1 = 1, /*!< sdio scratchoffset1 */
    kSDIOSLV_ScratchOffset3 = 3, /*!< sdio scratchoffset2 */
    kSDIOSLV_ScratchOffset4 = 4, /*!< sdio scratchoffset3 */
} sdioslv_scratch_offset_t;


/*! @brief SDU register map version 4 */
typedef struct _sdioslv_sdu_regmap
{
    uint32_t HostToCardEvent;   /*!< 0x100/200.../700 */
    uint32_t HostIntCause;      /*!< 0x104/204.../704 */
    uint32_t HostIntMask;       /*!< 0x108/208.../708 */
    uint32_t HostIntStatus;     /*!< 0x10C/20C.../70C */
    uint32_t RdBitMap;          /*!< 0x110/210.../710 */
    uint32_t WrBitMap;          /*!< 0x114/214.../714 */
    uint16_t RdLen[32];         /*!< 0x118/218.../718 */
    uint8_t HostTransferStatus; /*!< 0x158/258.../758 */
    uint8_t FunctionCardIntMsk; /*!< 0x159/259.../759 */
    uint8_t Card_Q_PTR_RANGE0;  /*!< 0x15A/25A.../75A */
    uint8_t Card_Q_PTR_RANGE1;  /*!< 0x15B/25B.../75B */
    uint16_t CardToHostEvent;   /*!< 0x15C/25C.../75C */
    uint8_t reserved2[2];
    uint32_t CardIntMask;        /*!< 0x160/260.../760 */
    uint32_t CardIntStatus;      /*!< 0x164/264.../764 */
    uint32_t CardIntMode;        /*!< 0x168/268.../768 */
    uint32_t SqReadBase;         /*!< 0x16C/26C.../76C */
    uint32_t SqWriteBase;        /*!< 0x170/270.../770 */
    uint8_t RdIdx;               /*!< 0x174/274.../774 */
    uint8_t WrIdx;               /*!< 0x175/275.../775 */
    uint8_t Reserved6[2];        /*!< 0x176/276.../776 */
    uint8_t Card_APU_SLP_RDY_EN; /*!< 0x178/278.../778 */
    uint8_t Reserved7[3];
    uint8_t Card_HOST_ERR_WKUP_EN; /*!< 0x17C/27C.../77C */
    uint8_t Reserved8[3];
    uint8_t HOST_ERR_CMD0; /*!< 0x180/280.../780 */
    uint8_t HOST_ERR_CMD1; /*!< 0x181/281.../781 */
    uint8_t HOST_ERR_CMD2; /*!< 0x182/282.../782 */
    uint8_t HOST_ERR_CMD3; /*!< 0x183/283.../783 */
    uint8_t HOST_ERR_CMD4; /*!< 0x184/284.../784 */
    uint8_t HOST_ERR_CMD5; /*!< 0x185/285.../785 */
    uint8_t Reserved9[2];
    uint32_t PktWrBitmapClr;     /*!< 0x188/288.../788 */
    uint32_t PktRdBitmapClr;     /*!< 0x18C/28C.../78C */
    uint32_t HostIntActMskEn;    /*!< 0x190/290.../790 */
    uint32_t HostIntActMskClr;   /*!< 0x194/294.../794 */
    uint32_t HostIntActMskStat;  /*!< 0x198/298.../798 */
    uint32_t CardIntActMskEn;    /*!< 0x19C/29C.../79C */
    uint32_t CardIntActMskClr;   /*!< 0x1A0/2A0.../7A0 */
    uint32_t CardIntActMskStat;  /*!< 0x1A4/2A4.../7A4 */
    uint32_t TestbusBitSelect;   /*!< 0x1A8/2A8.../7A8 */
    uint32_t TestbusBitSelect1;  /*!< 0x1AC/2AC.../7AC */
    uint16_t Scratch2;           /*!< 0x1B0/2B0.../7B0 */
    uint8_t Scratch[6];          /*!< 0x1B2/2B2.../7B2 */
    uint32_t CmdPortSqWriteBase; /*!< 0x1B8/2B8.../7B8 */
    uint32_t CmdPortSqReadBase;  /*!< 0x1BC/2BC.../7BC */
    uint16_t CmdPortRdLen;       /*!< 0x1C0/2C0.../7C0 */
    uint16_t Reserved10;         /*!< 0x1C2/2C2.../7C2 */
    uint32_t CmdPortConfig;      /*!< 0x1C4/2C4.../7C4 */
    uint8_t ChipRev;             /*!< 0x1C8/2C8.../7C8 */
    uint8_t reserved11;
    uint8_t SDUMinorIPRev;       /*!< 0x1CA/2CA.../7CA */
    uint8_t SDUMajorIPRev;       /*!< 0x1CB/2CB.../7CB */
    uint32_t Card_PKT_END_RADDR; /*!< 0x1CC/2CC.../7CC */
    uint32_t Card_PKT_END_WADDR; /*!< 0x1D0/2D0.../7D0 */
    uint16_t Scratch1;           /*!< 0x1D4/2D4.../7D4 */
    uint8_t Ocr2;                /*!< 0x1D6/2D6.../7D6 */
    uint8_t Config;              /*!< 0x1D7/2D7.../7D7 */
    uint32_t Config2;            /*!< 0x1D8/2D8.../7D8 */
    uint32_t Debug;              /*!< 0x1DC/2DC.../7DC */
    uint32_t DmaAddr;            /*!< 0x1E0/2E0.../7E0 */
    uint8_t IoPort[3];           /*!< 0x1E4/2E4.../7E4 */
} sdioslv_sdu_regmap_t;


/*! @brief SDIO CIS table callback. */
typedef void (*sdioslv_cis_table_callback_t)(const uint32_t SDU_BASE);

/*! @brief Data structure to configure SDIO handle for specific function. */
typedef struct sdio_slave_config
{
    uint8_t fun_num;               /*!< SDIO function number (1..7). */
    sdioslv_int_cpu_num_t cpu_num; /*!< Specify interrupt should be generated to which CPU */
    uint8_t used_port_num;         /*!< How many data ports are used inside this function */
    uint8_t cmd_tx_format;         /*!< Command Tx length format. 0: no tx_len, 1: 2 bytes, 2: 3 bytes */
    uint8_t cmd_rd_format;         /*!< Command Rx length format. 0: blk_num * blk_size, 1: CMD_PORT_RD_LEN */
    uint8_t data_tx_format;        /*!< Data Tx length format. 0: no tx_len, 1: 2 bytes, 2: 3 bytes */
    uint8_t data_rd_format;        /*!< Data Rx length format.
                                     0: blk_num * blk_size, 1: PORT_RD_LEN[15:0], 2: PORT1_RD_LEN[7:0] && PORT0_RD_LEN[15:0] */
    sdioslv_cis_table_callback_t cis_table_callback; /*!< Callback function for initializing the CIS table. */
} sdio_slave_config_t;


/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief SDIOSLV Init0.
 *
 * Call this API to Init SDIOSLV phase0.
 *
 * @param void None.
 * @retval void None.
 */
void SDIOSLV_Init0(void);

/*!
 * @brief SDIOSLV Init1.
 *
 * Call this API to Init SDIOSLV phase1.
 *
 * @param base FN FSR pointer.
 * @param config Configure for SDIO Slave.
 * @retval #kStatus_Success command is ready to be sent to host driver.
 * @retval #kStatus_InvalidArgument Invalid argument.
 */
status_t SDIOSLV_Init1(SDU_FN_CARD_Type *base, sdio_slave_config_t *config);


/* @} */

/*!
 * @name Cmd/Data Send/Refill
 * @{
 */

/*!
 * @brief SDIOSLV send command.
 *
 * Call this API to send command to host driver.
 * The callback is always invoked from theinterrupt context.
 *
 * @param regmap FN FSR pointer.
 * @param data_addr Data Address.
 * @param data_len Data Length.
 * @retval #kStatus_Success command is ready to be sent to host driver.
 * @retval #kStatus_InvalidArgument Invalid argument.
 */
status_t SDIOSLV_SendCmdNonBlocking(sdioslv_sdu_regmap_t *regmap, uint8_t *data_addr, uint16_t data_len);

/*!
 * @brief SDIOSLV provide command buffer.
 *
 * Call this API to provide receive command buffer to SDU driver.
 *
 * @param regmap FN FSR pointer.
 * @param data_addr Data Address.
 * @param data_len Data Length.
 * @retval #kStatus_Success buffer refill sucessfully.
 * @retval #kStatus_Fail fail to refill buffer.
 */
status_t SDIOSLV_RefillCmdBuffer(sdioslv_sdu_regmap_t *regmap, uint8_t *data_addr);

/*!
 * @brief SDIOSLV send data transfer.
 *
 * Call this API to send data to host driver.
 * The callback is always invoked from theinterrupt context.
 *
 * @param regmap FN FSR pointer.
 * @param port Data Port.
 * @param data_addr Data Address.
 * @param data_len Data Length.
 * @retval #kStatus_Success buffer is added to data slot with problem.
 * @retval #kStatus_InvalidArgument Invalid argument.
 * @retval #kStatus_SDIOSLV_SendFull all data slots are occupied, application
 */
status_t SDIOSLV_SendDataNonBlocking(sdioslv_sdu_regmap_t *regmap, sdioslv_port_t port, uint8_t *data_addr, uint16_t data_len);

/*!
 * @brief SDIOSLV provide receive data buffer.
 *
 * Call this API to provide receive data buffer to SDU driver.
 *
 * @param regmap FN FSR pointer.
 * @param port Data Port.
 * @param data_addr Data Address.
 * @param data_len Data Length.
 * @retval #kStatus_Success refill buffer sucessfully.
 * @retval #kStatus_Fail fail to refill buffer.
 */
status_t SDIOSLV_RefillDataBuffer(sdioslv_sdu_regmap_t *regmap, sdioslv_port_t port, uint8_t *data_addr);

/* @} */

/*!
 * @name Control and Status
 * @{
 */

/*!
 * @brief Get SDIO bus speed selection.
 *
 * Call this API to get current bus speed selected for SDIO.
 *
 * @param void None.
 * @retval sdioslv_bus_speed_t Bus speed selected for SDIO.
 */
sdioslv_bus_speed_t SDIOSLV_GetBusSpeed(void);

/*!
 * @brief Get SDIO the block size in FBR.
 *
 * For block mode, block size equals to block size in FBR.
 *
 * @param handle Created by SDIOSLV_CreateHanle().
 * @retval the block size in FBR.
 */
uint32_t SDIOSLV_GetBlockSize(uint8_t fn_num);

/* @} */

/*!
 * @name Scratch register read/write
 * @{
 */

/*!
 * @brief SDIOSLV read scratch register of SDU.
 *
 * Call this API to read scratch register of SDU (based on group and offset).
 *
 * @param fun_num Specify which function.
 * @param group Specify which group scratch register.
 * @param offset Specify offset of the scratch group.
 * @param value Value read from the register.
 * @retval #kStatus_Success read sucessfully.
 * @retval #kStatus_Fail fail to read.
 */
status_t SDIOSLV_ReadScratchRegister(sdioslv_func_t fun_num,
                                     sdioslv_scratch_group_t group,
                                     sdioslv_scratch_offset_t offset,
                                     uint8_t *value);

/*!
 * @brief SDIOSLV write value to scratch register of SDU.
 *
 * Call this API to write value to scratch register of SDU (based on group and offset).
 *
 * @param fun_num Specify which function.
 * @param group Specify which group scratch register.
 * @param offset Specify offset of the scratch group.
 * @param value Value write to the register.
 * @retval #kStatus_Success write sucessfully.
 * @retval #kStatus_Fail fail to write.
 */
status_t SDIOSLV_WriteScratchRegister(sdioslv_func_t fun_num,
                                      sdioslv_scratch_group_t group,
                                      sdioslv_scratch_offset_t offset,
                                      uint8_t value);

/* @} */

#if defined(__cplusplus)
}
#endif

/* @}*/

#endif /* _FSL_SDIOSLV_SDU_H_ */
