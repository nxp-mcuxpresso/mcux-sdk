/*
 * Copyright 2020-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_UPOWER_H_
#define _FSL_UPOWER_H_

#include "fsl_common.h"
#include "upower_soc_defs.h"
#include "upower_api.h"

/*!
 * @addtogroup upower
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief upower driver version (2.0.19.) */
#define FSL_UPOWER_DRIVER_VERSION (MAKE_VERSION(2, 0, 19))
/*@}*/

/*! @brief pmic rail id. */
#define PMIC_BUCK1 (0U)
#define PMIC_BUCK2 (1U)
#define PMIC_BUCK3 (2U)
#define PMIC_BUCK4 (3U)
#define PMIC_LDO1  (4U)
#define PMIC_LDO2  (5U)
#define PMIC_LDO3  (6U)
#define PMIC_LDO4  (7U)
#define PMIC_LSW1  (8U)
#define PMIC_LSW2  (9U)
#define PMIC_LSW3  (10U)
#define PMIC_LSW4  (11U)

/*! @brief pmic voltage. */
/* 1.1 V */
#define PMIC_VOLTAGE_1_1V (1100 * 1000)
/* 1.0 V */
#define PMIC_VOLTAGE_1_0V (1000 * 1000)
/* 0.9 V */
#define PMIC_VOLTAGE_0_9V (900 * 1000)

#define PMIC_I2C_ADDR           (0x32)
#define PMIC_WRITE_DATA_SIZE    (1)
#define PMIC_IC_WRITE_DATA_SIZE (1)
#define PMIC_READ_DATA_SIZE     (-1)
#define PMIC_IC_READ_DATA_SIZE  (1)

/*! @brief PCA9460 register */
#define PCA9460_BUCK23_DVS_CFG1_ADDR     (0x12)
#define PCA9460_BUCK23_DVS_CFG2_ADDR     (0x13)
#define PCA9460_BUCK2CTRL_ADDR     (0x14)
#define PCA9460_BUCK2OUT_DVS0_ADDR (0x15)
#define PCA9460_BUCK2OUT_DVS1_ADDR (0x16)
#define PCA9460_BUCK2OUT_DVS2_ADDR (0x17)
#define PCA9460_BUCK2OUT_DVS3_ADDR (0x18)
#define PCA9460_BUCK2OUT_DVS4_ADDR (0x19)
#define PCA9460_BUCK2OUT_DVS5_ADDR (0x1A)
#define PCA9460_BUCK2OUT_DVS6_ADDR (0x1B)
#define PCA9460_BUCK2OUT_DVS7_ADDR (0x1C)
#define PCA9460_BUCK2OUT_STDBY_ADDR (0x1D)
#define PCA9460_BUCK2OUT_MAX_LIMIT_ADDR (0x1F)
#define PCA9460_BUCK2OUT_MIN_LIMIT_ADDR (0x20)
#define PCA9460_BUCK3CTRL_ADDR     (0x21)
#define PCA9460_BUCK3OUT_DVS0_ADDR (0x22)
#define PCA9460_LDO1_CFG_ADDR      (0x30)
#define PCA9460_LDO1_OUT_ADDR      (0x31)

/*! Drive Mode: OD(Over Drive), ND(Nominal Drive), UD(Under Drive) */
typedef enum
{
    DRIVE_MODE_UD = 0,
    DRIVE_MODE_ND = 1,
    DRIVE_MODE_OD  = 2,
    DRIVE_MODE_NUM = 3,
} drive_mode_e;

/*! PCA9460 BUCK23_DVS_CFG2 register */
#define BUCK23_DVS_CFG2_B2_DVS_CTRL_BITS (2)
#define BUCK23_DVS_CFG2_B3_DVS_CTRL_BITS (2)
#define BUCK23_DVS_CFG2_RSVD_BITS (4)

/*! PCA9460 BUCK3CTRL register */
#define B3_RAMP_BITS   (2)
#define B3_LPMODE_BITS (2)
#define B3_AD_BITS     (1)
#define B3_FPWM_BITS   (1)
#define B3_ENMODE_BITS (2)

#define BUCK_OUTPUT_TABLE_SIZE    (128)
#define BUCK2_BUCK3_VOLTAGE_STEPS (0.0125)

/*! PCA9460 LDO1_CFG register */
#define L1_CSEL_BITS   (2)
#define L1_LLSEL_BITS  (2)
#define L1_LPMODE_BITS (2)
#define L1_ENMODE_BITS (2)

typedef union
{
    uint8_t val;
    struct
    {
        uint8_t RSVD : BUCK23_DVS_CFG2_RSVD_BITS;
        uint8_t B3_DVS_CTRL : BUCK23_DVS_CFG2_B3_DVS_CTRL_BITS;
        uint8_t B2_DVS_CTRL : BUCK23_DVS_CFG2_B2_DVS_CTRL_BITS;
    } reg;
} pca9460_buck23_dvs_cfg2_t;

typedef union
{
    uint8_t val;
    struct
    {
        uint8_t B3_ENMODE : B3_ENMODE_BITS;
        uint8_t B3_FPWM : B3_FPWM_BITS;
        uint8_t B3_AD : B3_AD_BITS;
        uint8_t B3_LPMODE : B3_LPMODE_BITS;
        uint8_t B3_RAMP : B3_RAMP_BITS;
    } reg;
} pca9460_buck3ctrl_t;

typedef union
{
    uint8_t val;
    struct
    {
        uint8_t L1_ENMODE : L1_ENMODE_BITS;
        uint8_t L1_LPMODE : L1_LPMODE_BITS;
        uint8_t L1_LLSEL : L1_LLSEL_BITS;
        uint8_t L1_CSEL : L1_CSEL_BITS;
    } reg;
} pca9460_ldo1_cfg_t;

/*! @brief upower power switch mask definition. */
typedef enum _upower_ps_mask
{
    kUPOWER_PS_M33       = (1U << 0U), /*!< RTD: CM33 core complex/platform/peripherals */
    kUPOWER_PS_FUSION    = (1U << 1U), /*!< RTD: Fusion core and peripherals */
    kUPOWER_PS_A35_0     = (1U << 2U), /*!< AD: A35[0] core complex */
    kUPOWER_PS_A35_1     = (1U << 3U), /*!< AD: A35[1] core complex */
    kUPOWER_PS_L2_CACHE  = (1U << 4U), /*!< AD: 256KB L2 cache */
    kUPOWER_PS_AD_NIC    = (1U << 5U), /*!< AD: A35 NIC_PER, NIC_AP */
    kUPOWER_PS_AD_PER    = (1U << 6U), /*!< AD: A35 peripherals and croessbar */
    kUPOWER_PS_GPU3D     = (1U << 7U), /*!< LPAV: 3DGPU */
    kUPOWER_PS_HIFI4     = (1U << 8U), /*!< LPAV: HiFi4 complex */
    kUPOWER_PS_DDRC      = (1U << 9U | 1U << 10U | 1U << 11U | 1U << 12U), /*!< LPAV: DDR controller */
    kUPOWER_PS_PXP_EPDC  = (1U << 13U),                                    /*!< LPAV: PXP, EPDC */
    kUPOWER_PS_MIPI_DSI  = (1U << 14U),                                    /*!< LPAV: MIPI DSI */
    kUPOWER_PS_MIPI_CSI  = (1U << 15U),                                    /*!< LPAV: MIPI CSI */
    kUPOWER_PS_AV_NIC    = (1U << 16U),                                    /*!< LPAV: NIC, System RAM2, DCNano */
    kUPOWER_PS_FUSION_AO = (1U << 17U),                                    /*!< RTD: Fusion "Always ON" */
    kUPOWER_PS_FUSES     = (1U << 18U),                                    /*!< RTD: Fuses */
} upower_ps_mask_t;

/*! @brief upower memory partitions 0 mask definition. */
typedef enum _upower_mp0_mask
{
    kUPOWER_MP0_A35_0       = (1U << 0U),  /*!< AD: A35 core0 */
    kUPOWER_MP0_A35_1       = (1U << 1U),  /*!< AD: A35 core1 */
    kUPOWER_MP0_A35_CORE_A  = (1U << 2U),  /*!< AD: A35 core0/1 */
    kUPOWER_MP0_A35_CORE_B  = (1U << 3U),  /*!< AD: A35 core0/1 */
    kUPOWER_MP0_A35_CORE_C  = (1U << 4U),  /*!< AD: A35 core0/1 */
    kUPOWER_MP0_CAAM        = (1U << 5U),  /*!< AD: CAAM */
    kUPOWER_MP0_DMA1        = (1U << 6U),  /*!< AD: DMA1 */
    kUPOWER_MP0_FLEXSPI2    = (1U << 7U),  /*!< AD: FlexSPI2 */
    kUPOWER_MP0_AD_SYSTEM_A = (1U << 8U),  /*!< AD: System */
    kUPOWER_MP0_AD_SYSTEM_B = (1U << 9U),  /*!< AD: System */
    kUPOWER_MP0_USB         = (1U << 10U), /*!< AD: USB */
    kUPOWER_MP0_USDHC0      = (1U << 11U), /*!< AD: uSDHC0 */
    kUPOWER_MP0_USDHC1      = (1U << 12U), /*!< AD: uSDHC1 */
    kUPOWER_MP0_USDHC2      = (1U << 13U), /*!< AD: uSDHC2 */
    kUPOWER_MP0_GIC         = (1U << 14U), /*!< AD: GIC */
    kUPOWER_MP0_ENET        = (1U << 15U), /*!< AD: ENET */
    kUPOWER_MP0_BRAINSHIFT  = (1U << 16U), /*!< AD: Brainshift */
    kUPOWER_MP0_DCNANO_A    = (1U << 17U), /*!< LPAV: DCNano */
    kUPOWER_MP0_DCNANO_B    = (1U << 18U), /*!< LPAV: DCNano */
    kUPOWER_MP0_EPDC_A      = (1U << 19U), /*!< LPAV: EPDC */
    kUPOWER_MP0_EPDC_B      = (1U << 20U), /*!< LPAV: EPDC */
    kUPOWER_MP0_DMA2        = (1U << 21U), /*!< LPAV: DMA2 */
    kUPOWER_MP0_GPU2D_A     = (1U << 22U), /*!< LPAV: GPU2D */
    kUPOWER_MP0_GPU2D_B     = (1U << 23U), /*!< LPAV: GPU2D */
    kUPOWER_MP0_GPU3D_A     = (1U << 24U), /*!< LPAV: GPU3D */
    kUPOWER_MP0_GPU3D_B     = (1U << 25U), /*!< LPAV: GPU3D */
    kUPOWER_MP0_HIFI4       = (1U << 26U), /*!< LPAV: Hi-Fi DSP */
    kUPOWER_MP0_ISI         = (1U << 27U), /*!< LPAV: ISI */
    kUPOWER_MP0_MIPI_CSI    = (1U << 28U), /*!< LPAV: MIPI CSI */
    kUPOWER_MP0_MIPI_DSI    = (1U << 29U), /*!< LPAV: MIPI DSI */
    kUPOWER_MP0_PXP         = (1U << 30U), /*!< LPAV: PXP */
    kUPOWER_MP0_AV_SYSTEM   = (1U << 31U), /*!< LPAV: System */
} upower_mp0_mask_t;

/*! @brief upower memory partitions 1 mask definition. */
typedef enum _upower_mp1_mask
{
    kUPOWER_MP1_CASPER     = (1U << 0U),  /*!< RTD: Casper */
    kUPOWER_MP1_DMA0       = (1U << 1U),  /*!< RTD: DMA0 */
    kUPOWER_MP1_FLEXCAN    = (1U << 2U),  /*!< RTD: FlexCAN (CAN-FD) */
    kUPOWER_MP1_FLEXSPI0   = (1U << 3U),  /*!< RTD: FlexSPI0 (OTFAD) */
    kUPOWER_MP1_FLEXSPI1   = (1U << 4U),  /*!< RTD: FlexSPI1 */
    kUPOWER_MP1_M33        = (1U << 5U),  /*!< RTD: M33 */
    kUPOWER_MP1_POWERQUAD  = (1U << 6U),  /*!< RTD: PowerQuad */
    kUPOWER_MP1_M33_ETF    = (1U << 7U),  /*!< RTD: M33-ETF */
    kUPOWER_MP1_SENTINEL_A = (1U << 8U),  /*!< RTD: Sentinel */
    kUPOWER_MP1_SENTINEL_B = (1U << 9U),  /*!< RTD: Sentinel */
    kUPOWER_MP1_UPOWER_A   = (1U << 10U), /*!< RTD: uPower */
    kUPOWER_MP1_UPOWER_B   = (1U << 11U), /*!< RTD: uPower */
    kUPOWER_MP1_RTD_SYSTEM = (1U << 12U), /*!< RTD: System */
    kUPOWER_MP1_SYSTEM0    = (1U << 13U), /*!< RTD: System[0] */
    kUPOWER_MP1_SYSTEM1    = (1U << 14U), /*!< RTD: System[1] */
    kUPOWER_MP1_SYSTEM2    = (1U << 15U), /*!< RTD: System[2] */
    kUPOWER_MP1_SYSTEM3    = (1U << 16U), /*!< RTD: System[3] */
    kUPOWER_MP1_SYSTEM4    = (1U << 17U), /*!< RTD: System[4] */
    kUPOWER_MP1_SYSTEM5    = (1U << 18U), /*!< RTD: System[5] */
    kUPOWER_MP1_SYSTEM6    = (1U << 19U), /*!< RTD: System[6] */
    kUPOWER_MP1_SYSTEM7    = (1U << 20U), /*!< RTD: System[7] */
    kUPOWER_MP1_SENTINEL_C = (1U << 21U), /*!< RTD: Sentinel */
} upower_mp1_mask_t;

typedef struct _upower_version
{
    uint32_t romMajor;
    uint32_t romMinor;
    uint32_t romFixes;
    uint32_t ramMajor;
    uint32_t ramMinor;
    uint32_t ramFixes;
} upower_version_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /*__cplusplus */

/*!
 * @brief Check status of current request to uPower.
 *
 * Will block till related callback function has been called
 *
 * @sg Indicate which Service Group that request point to
 * @sgfptr: pointer to the variable that will hold the function id of the last request completed
 * @errptr: pointer to the variable that will hold the error code
 * @retptr: pointer to the variable that will hold the value returned by the last request completed (invalid if the last
 * request completed didn't return any value)
 * @attempts: maximum number of polling attempts; if attempts > 0 and is reached with no service response received,
 * upwr_poll_req_status returns UPWR_REQ_BUSY and variables pointed by sgfptr, retptr and errptr are not updated; if
 * attempts = 0, upwr_poll_req_status waits "forever".
 */
void UPOWER_CheckReqWithArgs(upwr_sg_t sg, uint32_t *sgfptr, upwr_resp_t *errptr, int *retptr, uint32_t attempts);

/*!
 * @brief uPower specific IRQ handler.
 *
 */
void uPower_IRQHandler(void);

/*!
 * @brief Check status of current request to uPower.
 *
 * Will block till related callback function has been called
 *
 * @sg Indicate which Service Group that request point to
 */
void UPOWER_CheckReq(upwr_sg_t sg);

/*!
 * @brief Initialize MU interface for uPower access.
 *
 * @param pVersion Pointer to the structure to save uPower ROM and RAM versions
 */
void UPOWER_Init(upower_version_t *pVersion);

/*!
 * @brief Deinitialize MU interface for uPower access.
 */
void UPOWER_Deinit(void);

/*!
 * @brief Power on certain domain without reset.
 *
 * @param domain Target domain to power on.
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_PowerOnDomain(soc_domain_t domain);

/*!
 * @brief Reset and kick off certain domain.
 *
 * @param domain Target domain to boot.
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_BootDomain(soc_domain_t domain);

/*!
 * @brief Power on power switches.
 *
 * @param mask Bits to define which switch should be turned on. The value should be ORed by @ref upower_ps_mask_t.
 *             Bit value 1 means the switch is to be powered on; Value 0 means the switch keeps unchanged.
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_PowerOnSwitches(upower_ps_mask_t mask);

/*!
 * @brief Power off power switches.
 *
 * @param mask Bits to define which switch should be turned off. The value should be ORed by @ref upower_ps_mask_t.
 *             Bit value 1 means the switch is to be powered off; Value 0 means the switch keeps unchanged.
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_PowerOffSwitches(upower_ps_mask_t mask);

/*!
 * @brief Power on memory partitions array/periphery logic. If a memory is requested to turn on, but the
 * power switch that feeds that memory is not, the power switch will be turned on automatically.
 *
 * The parameter mask bits define which memory partition should be turned on. The value should be ORed by
 * upower_mp0_mask_t or upower_mp1_mask_t. Mask bit value 1 means the switch is to be powered on; Value 0
 * means the switch keeps unchanged.
 *
 * @param mask0 memory partition group 0 mask, see @ref upower_mp0_mask_t.
 * @param mask1 memory partition group 1 mask, see @ref upower_mp1_mask_t.
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_PowerOnMemPart(uint32_t mask0, uint32_t mask1);

/*!
 * @brief Power off memory partitions array/periphery logic.
 *
 * The parameter mask bits define which memory partition should be turned off. The value should be ORed by
 * upower_mp0_mask_t and upower_mp1_mask_t. Mask bit value 1 means the switch is to be powered off; Value 0
 * means the switch keeps unchanged.
 *
 * @param mask0 memory partition group 0 mask, see @ref upower_mp0_mask_t.
 * @param mask1 memory partition group 1 mask, see @ref upower_mp1_mask_t.
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_PowerOffMemPart(uint32_t mask0, uint32_t mask1);

/*!
 * @brief Power on memory partitions array logic and power off its periphery logic. If a memory array is
 * requested to turn on, but the power switch that feeds that memory is not, the power switch will be turned
 * on automatically.
 *
 * The parameter mask bits define which memory partition should be turned on. The value should be ORed by
 * upower_mp0_mask_t or upower_mp1_mask_t. Mask bit value 1 means the switch is to be powered on; Value 0
 * means the switch keeps unchanged.
 *
 * @param mask0 memory partition group 0 mask, see @ref upower_mp0_mask_t.
 * @param mask1 memory partition group 1 mask, see @ref upower_mp1_mask_t.
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_RetainMemPart(uint32_t mask0, uint32_t mask1);

/*!
 * @brief M33 call this API to inform uPower, M33 is using ddr.
 *
 * @param use_ddr not 0, true, means that RTD is using ddr. 0, false, means that, RTD is not using ddr.
 * @return 0 if ok, failure otherwise(-1 if service group is busy, -3 if called in an invalid API state).
 */
int UPOWER_SetRtdUseDdr(bool use_ddr);

/*!
 * @brief M33 call this API to Power On Application Domain when Application Domain is in Power Down/Deep Power Down
 * mode. After upower get the msg, upower write a flag to registers according to msg. Then upower will get a WUU1
 * interrupt request and upower change Power Down mode/Deep Power mode to Active mode when Application Domain is in
 * Power Down/Deep Power Down mode.
 *
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_PowerOnADInPDMode(void);

/*!
 * @brief set sg powermanagement parameters of upower.
 *
 * please see upower_soc_defs.h file for struct upwr_pwm_param_t
 *
 * @param pcfg_in user's selection for powermanagement parameter of upower
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_SetPwrMgmtParam(upwr_pwm_param_t *pcfg_in);

/*!
 * @brief Reduce Buck2 and Buck3 voltage in STANDBY mode.
 *
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_ReduceBuck23VoltInSTBY(void);

/*!
 * @brief Set DDR retention control bit.
 *
 * @param domain Target domain to power on.
 * @param enable true means set ddr retention, false means clear ddr retention.
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_SetDDRRetention(soc_domain_t domain, bool enable);

/*!
 * @brief Set LDO1 rail power.
 *
 * @param enable True means on, false means off.
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_SetLDO1Power(bool enable);

/*!
 * @brief Set Buck3 rail power.
 *
 * @param enable True means on, false means off.
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_SetBuck3Power(bool enable);

/*
 * @brief change PMIC voltage.
 *
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_ChngPmicVoltage(uint32_t rail, int voltage);

/*!
 * @brief Write PMIC registers by I2C.
 *
 * @param reg_addr means pmic ic target address.
 * @param reg_val means write data, specific data can be found in PCA9460.
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_SetPmicReg(uint32_t reg_addr, uint32_t reg_val);

/*!
 * @brief Read PMIC registers by I2C.
 *
 * @param reg_addr means pmic ic pca9460 target address.
 * @param reg_val means value of register.
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_ReadPmicReg(uint32_t reg_addr, uint8_t *reg_val);

/*!
 * @brief Init BUCK2 BUCK3 output voltage table.
 */
void UPOWER_InitBuck2Buck3Table(void);

/*!
 * @brief get PMIC voltage.
 *
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_GetPmicVoltage(uint32_t rail, int *voltage);

/*!
 * @brief Change Bias Configuration(biasing options: NBB, RBB, ARBB, AFBB; Bias Voltage) for RTD
 *
 * @param  drive_mode Drive Mode: UD, ND, OD.
 * @return 0 if ok, failure otherwise.
 */
int UPOWER_ChngRTDDomBias(drive_mode_e drive_mode);
#if defined(__cplusplus)
}
#endif /*__cplusplus */

/*! @} */

#endif /* _FSL_UPOWER_H_ */
