/*
 * Copyright 2021-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_LSM_H_
#define _FSL_LSM_H_

#include "fsl_common.h"

#ifndef LSM_SUPPORT_TILT
#define LSM_SUPPORT_TILT (1)
#endif
#ifndef LSM_SUPPORT_PEDOMETER
#define LSM_SUPPORT_PEDOMETER (1)
#endif

#define LSM6DSO_SLAVE_ADDRESS_WHEN_SA0_PIN_IS_LOW  (0x6AU)
#define LSM6DSO_SLAVE_ADDRESS_WHEN_SA0_PIN_IS_HIGH (0x6BU)

#define LSM6DSO_ACCEL_RESOLUTION_BITS 14

#define LSM_FUNC_CFG_ACCESS_REG (0x01U)

typedef enum
{
    LSM_USER_BANK          = 0,
    LSM_SENSOR_HUB_BANK    = 1,
    LSM_EMBEDDED_FUNC_BANK = 2,
} lsm_reg_access_t;

typedef enum
{
    LSM_INT_ACTIVE_HIGH    = 0,
    LSM_INT_ACTIVE_LOW     = 1,
} lsm_int_active_level_e;


typedef struct
{
    uint8_t not_used_01 : 6;
    uint8_t reg_access : 2; /* shub_reg_access + func_cfg_access */
} lsm_func_cfg_access_t;

#define LSM_WHO_AM_I_REG          (0X0FU)
#define LSM_WHO_AM_I_REG_WHO_AM_I (0x6CU) /* Device Id */
/*
 * EMB_FUNC_EN_A_REG Embedded functions enable register
 * TILT_EN=1 to enable the tilt detect function
 * PEDO_EN=1 to enable the pedometer function
 */
#define LSM_EMB_FUNC_EN_A_REG                      (0x04U)
#define LSM_EMB_FUNC_EN_A_REG_SIGN_MOTION_EN_SHIFT (0x05U)
#define LSM_EMB_FUNC_EN_A_REG_SIGN_MOTION_EN(N)    ((N) << LSM_EMB_FUNC_EN_A_REG_SIGN_MOTION_EN_SHIFT)

#define LSM_EMB_FUNC_EN_A_REG_TILT_EN_SHIFT (0x04U)
#define LSM_EMB_FUNC_EN_A_REG_TILT_EN(N)    ((N) << LSM_EMB_FUNC_EN_A_REG_TILT_EN_SHIFT)

#define LSM_EMB_FUNC_EN_A_REG_PEDO_EN_SHIFT (0x03U)
#define LSM_EMB_FUNC_EN_A_REG_PEDO_EN(N)    ((N) << LSM_EMB_FUNC_EN_A_REG_PEDO_EN_SHIFT)

/*
 * EMB_FUNC_INT1 INT1 pin control register
 * INT1_TILT=1, route the interrupt signal to INT1 pin
 */
#define LSM_EMB_FUNC_INT1_REG                          (0x0AU)
#define LSM_EMB_FUNC_INT1_REG_INT1_FSM_LC_SHIFT        (0x07U)
#define LSM_EMB_FUNC_INT1_REG_INT1_FSM_LC(N)           ((N) << LSM_EMB_FUNC_INT1_REG_INT1_FSM_LC_SHIFT)
#define LSM_EMB_FUNC_INT1_REG_INT1_SIG_MOT_SHIFT       (0x05U)
#define LSM_EMB_FUNC_INT1_REG_INT1_SIG_MOT(N)          ((N) << LSM_EMB_FUNC_INT1_REG_INT1_SIG_MOT_SHIFT)
#define LSM_EMB_FUNC_INT1_REG_INT1_TILT_SHIFT          (0x04U)
#define LSM_EMB_FUNC_INT1_REG_INT1_TILT(N)             ((N) << LSM_EMB_FUNC_INT1_REG_INT1_TILT_SHIFT)
#define LSM_EMB_FUNC_INT1_REG_INT1_STEP_DETECTOR_SHIFT (0x03U)
#define LSM_EMB_FUNC_INT1_REG_INT1_STEP_DETECTOR(N)    ((N) << LSM_EMB_FUNC_INT1_REG_INT1_STEP_DETECTOR_SHIFT)

/*
 * PAGE_RW_REG Enable read and write mode of advanced features dedicated page
 * Set EMB_FUNC_LIR=1 to enable Latch mode, in latch mode, can use the EMB_FUNC_STATUS' IS_TILT bit to reset the
 * interrupt signal
 */
#define LSM_PAGE_RW_REG                    (0x17U)
#define LSM_PAGE_RW_REG_EMB_FUNC_LIR_SHIFT (0x07U)
#define LSM_PAGE_RW_REG_EMB_FUNC_LIR(N)    ((N) << LSM_PAGE_RW_REG_EMB_FUNC_LIR_SHIFT)
#define LSM_PAGE_RW_REG_PAGE_WRITE_SHIFT   (0x06U)
#define LSM_PAGE_RW_REG_PAGE_WRITE(N)      ((N) << LSM_PAGE_RW_REG_PAGE_WRITE_SHIFT)
#define LSM_PAGE_RW_REG_PAGE_READ_SHIFT    (0x05U)
#define LSM_PAGE_RW_REG_PAGE_READ(N)       ((N) << LSM_PAGE_RW_REG_PAGE_READ_SHIFT)

/*
 * MD1_CFG_REG Functions routeing on INT1 register
 * The EMB_FUNC_INT1_REG based on this reg, need to set INT1_EMB_FUNC=1 first
 */
#define LSM_MD1_CFG_REG (0x5EU)

#define LSM_MD1_CFG_REG_INT1_SLEEP_CHANGE_SHIFT (0x07U)
#define LSM_MD1_CFG_REG_INT1_SLEEP_CHANGE(N)    ((N) << LSM_MD1_CFG_REG_INT1_SLEEP_CHANGE_SHIFT)
#define LSM_MD1_CFG_REG_INT1_SINGLE_TAP_SHIFT   (0x06U)
#define LSM_MD1_CFG_REG_INT1_SINGLE_TAP(N)      ((N) << LSM_MD1_CFG_REG_INT1_SINGLE_TAP_SHIFT)
#define LSM_MD1_CFG_REG_INT1_WU_SHIFT           (0x05U)
#define LSM_MD1_CFG_REG_INT1_WU(N)              ((N) << LSM_MD1_CFG_REG_INT1_WU_SHIFT)
#define LSM_MD1_CFG_REG_INT1_FF_SHIFT           (0x04U)
#define LSM_MD1_CFG_REG_INT1_FF(N)              ((N) << LSM_MD1_CFG_REG_INT1_FF_SHIFT)
#define LSM_MD1_CFG_REG_INT1_DOUBLE_TAP_SHIFT   (0x03U)
#define LSM_MD1_CFG_REG_INT1_DOUBLE_TAP(N)      ((N) << LSM_MD1_CFG_REG_INT1_DOUBLE_TAP_SHIFT)
#define LSM_MD1_CFG_REG_INT1_6D_SHIFT           (0x02U)
#define LSM_MD1_CFG_REG_INT1_6D(N)              ((N) << LSM_MD1_CFG_REG_INT1_6D_SHIFT)
#define LSM_MD1_CFG_REG_INT1_EMB_FUNC_SHIFT     (0x01U)
#define LSM_MD1_CFG_REG_INT1_EMB_FUNC(N)        ((N) << LSM_MD1_CFG_REG_INT1_EMB_FUNC_SHIFT)
#define LSM_MD1_CFG_REG_INT1_SHUB_SHIFT         (0x00U)
#define LSM_MD1_CFG_REG_INT1_SHUB(N)            ((N) << LSM_MD1_CFG_REG_INT1_SHUB_SHIFT)

/*
 * Set 0x20 to CTRL1_XL_REG to set the ODR with 26HZ in high performance mode
 * Set 0xc to CTRL1_XL_REG set the full scale with 4g
 */
#define LSM_CTRL1_XL_REG                  (0x10U)
#define LSM_CTRL1_XL_REG_ODR_XL_SHIFT     (0x04U)
#define LSM_CTRL1_XL_REG_ODR_XL_MASK      (LSM_CTRL1_XL_REG_ODR_XL(0x0FU))
#define LSM_CTRL1_XL_REG_ODR_XL(N)        ((N) << LSM_CTRL1_XL_REG_ODR_XL_SHIFT)
#define LSM_CTRL1_XL_REG_FS_XL_SHIFT      (0x02U)
#define LSM_CTRL1_XL_REG_FS_XL_MASK       (LSM_CTRL1_XL_REG_FS_XL(0x03U))
#define LSM_CTRL1_XL_REG_FS_XL(N)         ((N) << LSM_CTRL1_XL_REG_FS_XL_SHIFT)
#define LSM_CTRL1_XL_REG_LPF2_XL_EN_SHIFT (0x01U)
#define LSM_CTRL1_XL_REG_LPF2_XL_EN_MASK  (LSM_CTRL1_XL_REG_LPF2_XL_EN(0x01U))
#define LSM_CTRL1_XL_REG_LPF2_XL_EN(N)    ((N) << LSM_CTRL1_XL_REG_LPF2_XL_EN_SHIFT)

#define LSM_PAGE_SEL_REG                (0x02U)
#define LSM_PAGE_SEL_REG_PAGE_SEL_SHIFT (0x04U)
#define LSM_PAGE_SEL_REG_PAGE_SEL_MASK  (LSM_PAGE_SEL_REG_PAGE_SEL(0x0FU))
#define LSM_PAGE_SEL_REG_PAGE_SEL(N)    ((N) << LSM_PAGE_SEL_REG_PAGE_SEL_SHIFT)

#define LSM_PAGE_ADDR_REG  (0x08U)
#define LSM_PAGE_VALUE_REG (0x09U)

#define LSM_EMB_FUNC_EN_B_REG                     (0x05U)
#define LSM_EMB_FUNC_EN_B_REG_PEDO_ADV_EN_SHIFT   (0x04U)
#define LSM_EMB_FUNC_EN_B_REG_PEDO_ADV_EN_MASK    (LSM_EMB_FUNC_EN_B_REG_PEDO_ADV_EN(0x01U))
#define LSM_EMB_FUNC_EN_B_REG_PEDO_ADV_EN(N)      ((N) << LSM_EMB_FUNC_EN_B_REG_PEDO_ADV_EN_SHIFT)
#define LSM_EMB_FUNC_EN_B_REG_FIFO_COMPR_EN_SHIFT (0x03U)
#define LSM_EMB_FUNC_EN_B_REG_FIFO_COMPR_EN_MASK  (LSM_EMB_FUNC_EN_B_REG_FIFO_COMPR_EN(0x01U))
#define LSM_EMB_FUNC_EN_B_REG_FIFO_COMPR_EN(N)    ((N) << LSM_EMB_FUNC_EN_B_REG_FIFO_COMPR_EN_SHIFT)
#define LSM_EMB_FUNC_EN_B_REG_FSM_EN_SHIFT        (0x00U)
#define LSM_EMB_FUNC_EN_B_REG_FSM_EN_MASK         (LSM_EMB_FUNC_EN_B_REG_FSM_EN(0x01U))
#define LSM_EMB_FUNC_EN_B_REG_FSM_EN(N)           ((N) << LSM_EMB_FUNC_EN_B_REG_FSM_EN_SHIFT)

/*
 * EMB_FUNC_STATUS Embedded function status Register
 * The IS_TILT=1 means there is the interrupt signal
 * IS_STEP_DET=1 means the step interrupt is detected
 */
#define LSM_EMB_FUNC_STATUS_REG (0x12U)

typedef struct
{
    uint8_t not_used_01 : 3;
    uint8_t is_step_det : 1;
    uint8_t is_tilt : 1;
    uint8_t is_sigmot : 1;
    uint8_t not_used_02 : 1;
    uint8_t is_fsm_lc : 1;
} lsm_emb_func_status_t;

/* EMB_FUNC_STATUS_MAINPAGE Embedded function status Register */
#define LSM_EMB_FUNC_STATUS_MAINPAGE_REG (0x35U)

#define LSM_EMB_FUNC_STATUS_MAINPAGE_REG_IS_FSM_LC_SHIFT   (0x07U)
#define LSM_EMB_FUNC_STATUS_MAINPAGE_REG_IS_FSM_LC_MASK    (LSM_EMB_FUNC_STATUS_MAINPAGE_REG_IS_FSM_LC(0x01U))
#define LSM_EMB_FUNC_STATUS_MAINPAGE_REG_IS_FSM_LC(N)      ((N) << LSM_EMB_FUNC_STATUS_MAINPAGE_REG_IS_FSM_LC_SHIFT)
#define LSM_EMB_FUNC_STATUS_MAINPAGE_REG_IS_SIGMOT_SHIFT   (0x05U)
#define LSM_EMB_FUNC_STATUS_MAINPAGE_REG_IS_SIGMOT_MASK    (LSM_EMB_FUNC_STATUS_MAINPAGE_REG_IS_SIGMOT(0x01U))
#define LSM_EMB_FUNC_STATUS_MAINPAGE_REG_IS_SIGMOT(N)      ((N) << LSM_EMB_FUNC_STATUS_MAINPAGE_REG_IS_SIGMOT_SHIFT)
#define LSM_EMB_FUNC_STATUS_MAINPAGE_REG_IS_TILT_SHIFT     (0x04U)
#define LSM_EMB_FUNC_STATUS_MAINPAGE_REG_IS_TILT_MASK      (LSM_EMB_FUNC_STATUS_MAINPAGE_REG_IS_TILT(0x01U))
#define LSM_EMB_FUNC_STATUS_MAINPAGE_REG_IS_TILT(N)        ((N) << LSM_EMB_FUNC_STATUS_MAINPAGE_REG_IS_TILT_SHIFT)
#define LSM_EMB_FUNC_STATUS_MAINPAGE_REG_IS_STEP_DET_SHIFT (0x03U)
#define LSM_EMB_FUNC_STATUS_MAINPAGE_REG_IS_STEP_DET_MASK  (LSM_EMB_FUNC_STATUS_MAINPAGE_REG_IS_STEP_DET(0x01U))
#define LSM_EMB_FUNC_STATUS_MAINPAGE_REG_IS_STEP_DET(N)    ((N) << LSM_EMB_FUNC_STATUS_MAINPAGE_REG_IS_STEP_DET_SHIFT)

/*
 * EMB_FUNC_INIT_A Embedded functions initialization register
 * Set TILT_INIT=1 to init the TILT algorithm
 * Set STEP_DET_INIT=1 to init pedometer step detect algorithm
 */
#define LSM_EMB_FUNC_INIT_A_REG (0x66U)

#define LSM_EMB_FUNC_INIT_A_REG_SIG_MOT_INIT_SHIFT  (0x05U)
#define LSM_EMB_FUNC_INIT_A_REG_SIG_MOT_INIT_MASK   (LSM_EMB_FUNC_INIT_A_REG_SIG_MOT_INIT(0x01U))
#define LSM_EMB_FUNC_INIT_A_REG_SIG_MOT_INIT(N)     ((N) << LSM_EMB_FUNC_INIT_A_REG_SIG_MOT_INIT_SHIFT)
#define LSM_EMB_FUNC_INIT_A_REG_TILT_INIT_SHIFT     (0x04U)
#define LSM_EMB_FUNC_INIT_A_REG_TILT_INIT_MASK      (LSM_EMB_FUNC_INIT_A_REG_TILT_INIT(0x01U))
#define LSM_EMB_FUNC_INIT_A_REG_TILT_INIT(N)        ((N) << LSM_EMB_FUNC_INIT_A_REG_TILT_INIT_SHIFT)
#define LSM_EMB_FUNC_INIT_A_REG_STEP_DET_INIT_SHIFT (0x03U)
#define LSM_EMB_FUNC_INIT_A_REG_STEP_DET_INIT_MASK  (LSM_EMB_FUNC_INIT_A_REG_STEP_DET_INIT(0x01U))
#define LSM_EMB_FUNC_INIT_A_REG_STEP_DET_INIT(N)    ((N) << LSM_EMB_FUNC_INIT_A_REG_STEP_DET_INIT_SHIFT)
#define LSM_STEP_COUNTER_L_REG                      (0x62U)
#define LSM_STEP_COUNTER_H_REG                      (0x63U)
/*
 * EMB_FUNC_SRC_REG Embedded function source register
 * If the accelerometer power down or reset, set PEDO_RST_STEP=1 to reset the step
 */
#define LSM_EMB_FUNC_SRC_REG                           (0x64U)
#define LSM_EMB_FUNC_SRC_REG_PEDO_RST_STEP_SHIFT       (0x07U)
#define LSM_EMB_FUNC_SRC_REG_PEDO_RST_STEP_MASK        (LSM_EMB_FUNC_SRC_REG_PEDO_RST_STEP(0x01U))
#define LSM_EMB_FUNC_SRC_REG_PEDO_RST_STEP(N)          ((N) << LSM_EMB_FUNC_SRC_REG_PEDO_RST_STEP_SHIFT)
#define LSM_EMB_FUNC_SRC_REG_STEP_DETECTED_SHIFT       (0x05U)
#define LSM_EMB_FUNC_SRC_REG_STEP_DETECTED_MASK        (LSM_EMB_FUNC_SRC_REG_STEP_DETECTED(0x01U))
#define LSM_EMB_FUNC_SRC_REG_STEP_DETECTED(N)          ((N) << LSM_EMB_FUNC_SRC_REG_STEP_DETECTED_SHIFT)
#define LSM_EMB_FUNC_SRC_REG_STEP_COUNT_DELTA_IA_SHIFT (0x04U)
#define LSM_EMB_FUNC_SRC_REG_STEP_COUNT_DELTA_IA_MASK  (LSM_EMB_FUNC_SRC_REG_STEP_COUNT_DELTA_IA(0x01U))
#define LSM_EMB_FUNC_SRC_REG_STEP_COUNT_DELTA_IA(N)    ((N) << LSM_EMB_FUNC_SRC_REG_STEP_COUNT_DELTA_IA_SHIFT)
#define LSM_EMB_FUNC_SRC_REG_STEP_OVERFLOW_SHIFT       (0x03U)
#define LSM_EMB_FUNC_SRC_REG_STEP_OVERFLOW_MASK        (LSM_EMB_FUNC_SRC_REG_STEP_OVERFLOW(0x01U))
#define LSM_EMB_FUNC_SRC_REG_STEP_OVERFLOW(N)          ((N) << LSM_EMB_FUNC_SRC_REG_STEP_OVERFLOW_SHIFT)
#define LSM_EMB_FUNC_SRC_REG_STEPCOUNTER_BIT_SET_SHIFT (0x02U)
#define LSM_EMB_FUNC_SRC_REG_STEPCOUNTER_BIT_SET_MASK  (LSM_EMB_FUNC_SRC_REG_STEPCOUNTER_BIT_SET(0x01U))
#define LSM_EMB_FUNC_SRC_REG_STEPCOUNTER_BIT_SET(N)    ((N) << LSM_EMB_FUNC_SRC_REG_STEPCOUNTER_BIT_SET_SHIFT)

/* PEDO_DEB_STEPS_CONF_REG Pedometer debounce configuration register */
#define LSM_PEDO_DEB_STEPS_CONF_REG (0x84U)

#define LSM_PEDO_CMD_REG                       (0x83U)
#define LSM_PEDO_CMD_REG_CARRY_COUNT_EN_SHIFT  (0x03U)
#define LSM_PEDO_CMD_REG_CARRY_COUNT_EN_MASK   (LSM_PEDO_CMD_REG_CARRY_COUNT_EN(0x01U))
#define LSM_PEDO_CMD_REG_CARRY_COUNT_EN(N)     ((N) << LSM_PEDO_CMD_REG_CARRY_COUNT_EN_SHIFT)
#define LSM_PEDO_CMD_REG_FP_REJECTION_EN_SHIFT (0x02U)
#define LSM_PEDO_CMD_REG_FP_REJECTION_EN_MASK  (LSM_PEDO_CMD_REG_FP_REJECTION_EN(0x01U))
#define LSM_PEDO_CMD_REG_FP_REJECTION_EN(N)    ((N) << LSM_PEDO_CMD_REG_FP_REJECTION_EN_SHIFT)
#define LSM_PEDO_CMD_REG_AD_DET_EN_SHIFT       (0x00U)
#define LSM_PEDO_CMD_REG_AD_DET_EN_MASK        (LSM_PEDO_CMD_REG_AD_DET_EN(0x01U))
#define LSM_PEDO_CMD_REG_AD_DET_EN(N)          ((N) << LSM_PEDO_CMD_REG_AD_DET_EN_SHIFT)

/* Set 0x8 to CTRL4_C_REG used to enable data available */
#define LSM_CTRL4_C_REG (0x13U)

/* Set 0x1 to CTRL3_C_REG to do software reset */
#define LSM_CTRL3_C_REG (0x12U)
typedef struct
{
    uint8_t sw_reset : 1; /* 0: normal mode; 1: reset device */
    uint8_t not_used : 1;
    uint8_t if_inc : 1; /* Register address automatically incremented; 0: disabled; 1: enabled(default) */
    uint8_t sim : 1; /* SPI serial interface mode selection; 0: 4-wire interface(default); 1: 3-wire interface */
    uint8_t pp_od : 1; /* push-pull/open-drain selection on INT1 and INT2 pins; 0: push-pull mode(default); 1: open-drain mode */
    uint8_t h_lactive : 1; /* interrupt activation level; 0: interrupt output pins active high(default); 1: interrupt output pins active low  */
    uint8_t bdu : 1; /* block data update; 0: continuous update(default); 1: output registers are not updated until MSB and LSB have been read */
    uint8_t boot : 1; /* Reboots memory content; 0: normal mode(default); 1: reboot memory content */
} lsm_ctrl3_c_t;

#define LSM_STATUS_REG_OR_STATUS_SPIAUX_REG (0x1EU)

#define LSM_STATUS_REG_OR_STATUS_SPIAUX_REG_TDA_OR_GYRO_SETTING_SHIFT (0x02U)
#define LSM_STATUS_REG_OR_STATUS_SPIAUX_REG_TDA_OR_GYRO_SETTING_MASK \
    (LSM_STATUS_REG_OR_STATUS_SPIAUX_REG_TDA_OR_GYRO_SETTING(0x01U))
#define LSM_STATUS_REG_OR_STATUS_SPIAUX_REG_TDA_OR_GYRO_SETTING(N) \
    ((N) << LSM_STATUS_REG_OR_STATUS_SPIAUX_REG_TDA_OR_GYRO_SETTING_SHIFT)
#define LSM_STATUS_REG_OR_STATUS_SPIAUX_REG_GDA_SHIFT  (0x01U)
#define LSM_STATUS_REG_OR_STATUS_SPIAUX_REG_GDA_MASK   (LSM_STATUS_REG_OR_STATUS_SPIAUX_REG_GDA(0x01U))
#define LSM_STATUS_REG_OR_STATUS_SPIAUX_REG_GDA(N)     ((N) << LSM_STATUS_REG_OR_STATUS_SPIAUX_REG_GDA_SHIFT)
#define LSM_STATUS_REG_OR_STATUS_SPIAUX_REG_XLDA_SHIFT (0x00U)
#define LSM_STATUS_REG_OR_STATUS_SPIAUX_REG_XLDA_MASK  (LSM_STATUS_REG_OR_STATUS_SPIAUX_REG_XLDA(0x01U))
#define LSM_STATUS_REG_OR_STATUS_SPIAUX_REG_XLDA(N)    ((N) << LSM_STATUS_REG_OR_STATUS_SPIAUX_REG_XLDA_SHIFT)

/*! @brief Define I2C access function. */
typedef status_t (*I2C_SendFunc_t)(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint32_t txBuff, uint32_t flags);
typedef status_t (*I2C_ReceiveFunc_t)(uint8_t deviceAddress,
                                      uint32_t subAddress,
                                      uint8_t subaddressSize,
                                      uint8_t *rxBuff,
                                      uint8_t rxBuffSize,
                                      uint32_t flags);

/*! @brief lsm6dso configure definition. This structure should be global.*/
typedef struct _lsm_handle
{
    /* Pointer to the user-defined I2C Send Data function. */
    I2C_SendFunc_t I2C_SendFunc;
    /* Pointer to the user-defined I2C Receive Data function. */
    I2C_ReceiveFunc_t I2C_ReceiveFunc;
    /* The I2C slave address . */
    uint8_t slaveAddress;
} lsm_handle_t;

/*! @brief lsm6dso configure structure.*/
typedef struct _lsm_config
{
    /* Pointer to the user-defined I2C Send Data function. */
    I2C_SendFunc_t I2C_SendFunc;
    /* Pointer to the user-defined I2C Receive Data function. */
    I2C_ReceiveFunc_t I2C_ReceiveFunc;
    /* The I2C slave address . */
    uint8_t slaveAddress;
    lsm_int_active_level_e int_active_level; /* interrupt output pins activation level */
} lsm_config_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initialize the lsm6dso driver instance.
 *
 * @param accel_device Device driver state structure that will be filled in by this function.
 *      It is the responsibility of the caller to provide storage for this structure, and
 *      to free that storage when the driver is no longer needed.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 */
status_t LSM_Init(lsm_handle_t *handle, const lsm_config_t *config);

/*!
 * @brief Get value of register.
 *
 * @param reg variable address of register
 * @param val pointer store return value of register.
 * @param enter_bank mem bank when enter.
 * @param exit_bank mem bank when exit.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 */
status_t LSM_GetVal(
    lsm_handle_t *handle, uint8_t reg, uint8_t *val, lsm_reg_access_t enter_bank, lsm_reg_access_t exit_bank);

/*!
 * @brief Set value of register.
 *
 * @param reg variable address of register
 * @param val value will be set to register.
 * @param enter_bank mem bank when enter.
 * @param exit_bank mem bank when exit.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 */
status_t LSM_SetVal(
    lsm_handle_t *handle, uint8_t reg, uint8_t val, lsm_reg_access_t enter_bank, lsm_reg_access_t exit_bank);

/*!
 * @brief Read the value of register in accelerometer.
 *
 * @param reg variable store address of register
 * @param val pointer store return value.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 */
status_t LSM_ReadReg(lsm_handle_t *handle, uint8_t reg, uint8_t *val);

/*!
 * @brief Write the value to register of accelerometer.
 *
 * @param handle Pointer to a valid accel_device instance structure.
 * @param reg variable store address of register
 * @param val pointer store value which is writen to accelerometer.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 */
status_t LSM_WriteReg(lsm_handle_t *handle, uint8_t reg, uint8_t *val);

/*!
 * @brief Get step count.
 *
 * @param stepCount pointer store step count.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 */
status_t LSM_GetPedometerCnt(lsm_handle_t *handle, uint16_t *stepCount);

/*!
 * @brief Set mem bank.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 */
status_t LSM_SetMemBank(lsm_handle_t *handle, lsm_reg_access_t bank);

/*!
 * @brief Get mem bank.
 *
 * @return kStatus_Success if success or kStatus_Fail if error.
 */
status_t LSM_GetMemBank(lsm_handle_t *handle, lsm_reg_access_t *bank);
#if defined(__cplusplus)
}
#endif

#endif /* _FSL_LSM_H_ */
