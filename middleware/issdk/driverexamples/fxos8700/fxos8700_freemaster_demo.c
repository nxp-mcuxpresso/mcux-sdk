/*
 * Copyright 2019-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file fxos8700_freemaster_demo.c
 * @brief The fxos8700_freemaster.c file implements FreeMASTER demo using the ISSDK
 *        FXOS8700 sensor driver example demonstration with interrupt mode.
 */

/*  SDK Includes */
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "math.h"
#include "fsl_uart.h"
#include "fsl_common.h"
#include "freemaster.h"
#include "freemaster_serial_uart.h"

/* CMSIS Includes */
#include "Driver_I2C.h"

/* ISSDK Includes */
#include "issdk_hal.h"
#include "gpio_driver.h"
#include "fxos8700_drv.h"

/*******************************************************************************
 * Macro Definitions
 ******************************************************************************/

#define FXOS8700_NUM_REGISTERS (FXOS8700_A_FFMT_THS_Z_LSB + 1)
#define FF_A_FFMT_THS          (0x08)       /* FreeFall Threshold Value. */
#define A_FFMT_COUNT           (0x18)       /* Freefall/motion debounce count value. */
#define PL_COUNT               (0x15)       /* Pulse debounce count value. */
#define ASLP_COUNTER           (0x07)       /* Auto Sleep after ~5s. */
#define ACCEL_2G_SENS          (0.000244)   /* Sensitivity factor for 2G FS */
#define ACCEL_4G_SENS          (0.000488)   /* Sensitivity factor for 4G FS */
#define ACCEL_8G_SENS          (0.000976)   /* Sensitivity factor for 8G FS */
#define N                      (500U)       /* Number of samples used to measure offset/noise */
#define RAW_ACCELMAG_DATA_SIZE (12U)        /* Accel + Mag Data Size */
#define MAX8BITSTORAGE         (255U)

/*******************************************************************************
 * Constants
 ******************************************************************************/
/*!
 * @brief Defines the register write list to configure FXOS8700 in Hybrid mode.
 */
const registerwritelist_t fxos8700_Config_Hybrid[] = {
        /*! Clear F_SETUP. */
		{FXOS8700_F_SETUP, 0x00, 0x00},
        /*! Set FS 2G Mode. */
		{FXOS8700_XYZ_DATA_CFG, FXOS8700_XYZ_DATA_CFG_FS_2G_0P244, FXOS8700_XYZ_DATA_CFG_FS_MASK},
        /*! Configure the FXOS8700 to 100Hz sampling rate. */
        {FXOS8700_CTRL_REG1, FXOS8700_CTRL_REG1_DR_HYBRID_100_HZ, FXOS8700_CTRL_REG1_DR_MASK},
        /*! Configure the FXOS8700 to Set High Resolution Mode. */
        {FXOS8700_CTRL_REG2, FXOS8700_CTRL_REG2_MODS_HIGH_RES, FXOS8700_CTRL_REG2_MODS_MASK},		
        {FXOS8700_CTRL_REG3, FXOS8700_CTRL_REG3_IPOL_ACTIVE_HIGH | FXOS8700_CTRL_REG3_PP_OD_PUSH_PULL,
		                     FXOS8700_CTRL_REG3_IPOL_MASK | FXOS8700_CTRL_REG3_PP_OD_MASK}, /*! Active High, Push-Pull */
        {FXOS8700_CTRL_REG4, FXOS8700_CTRL_REG4_INT_EN_DRDY_EN,FXOS8700_CTRL_REG4_INT_EN_DRDY_MASK}, /*! Data Ready Event. */
        {FXOS8700_CTRL_REG5, FXOS8700_CTRL_REG5_INT_CFG_DRDY_INT2, FXOS8700_CTRL_REG5_INT_CFG_DRDY_MASK}, /*! INT2 Pin  */
        {FXOS8700_M_CTRL_REG1, FXOS8700_M_CTRL_REG1_M_ACAL_DISABLE | FXOS8700_M_CTRL_REG1_M_HMS_HYBRID_MODE | FXOS8700_M_CTRL_REG1_M_OS_OSR0,
                               FXOS8700_M_CTRL_REG1_M_ACAL_MASK | FXOS8700_M_CTRL_REG1_M_HMS_MASK | FXOS8700_M_CTRL_REG1_M_OS_MASK}, /*! Enable the Hybrid Mode. */
        {FXOS8700_M_CTRL_REG2, FXOS8700_M_CTRL_REG2_M_AUTOINC_HYBRID_MODE, FXOS8700_M_CTRL_REG2_M_AUTOINC_MASK}, /*! Enable the Data read with Hybrid Mode. */
        {FXOS8700_CTRL_REG5,0x7E,0x00},
        {FXOS8700_CTRL_REG4,255,0x00},

		/*! Landscape-Portrait registers configurations */
        {FXOS8700_PL_CFG,FXOS8700_PL_CFG_DBCNTM_CLEAR_MODE  ,FXOS8700_PL_CFG_DBCNTM_MASK},
        {FXOS8700_PL_CFG,FXOS8700_PL_CFG_PL_EN_ENABLE   ,FXOS8700_PL_CFG_PL_EN_MASK },
		/*! PL count set to (64 * 2.5ms) = 160ms */
        {FXOS8700_PL_COUNT, 0x40, 0x00},
		/*! Z-lock angle threshold set to ~28deg */
        {FXOS8700_PL_BF_ZCOMP,4 ,FXOS8700_PL_BF_ZCOMP_ZLOCK_MASK},
		/*! Back/front trip angle threshold set to ~44deg */
        {FXOS8700_PL_BF_ZCOMP,2 ,FXOS8700_PL_BF_ZCOMP_BKFR_MASK},
		/*! PL_THS set to 0x10=> 45deg threshold angle, HYS set to 0b100=> LtoP trip angle 59deg and PtoL trip angle 31deg*/
        {FXOS8700_PL_THS_REG,132,0x00},

        /*! Freefall detection registers configurations */
		/*! Configure FreeFall debounce counter to 60msec */
	    {FXOS8700_A_FFMT_COUNT, A_FFMT_COUNT, 0}, /* Debounce Counter */
		/*! Configure FreeFall detection threshold to 0.5g */
	    {FXOS8700_A_FFMT_THS, FF_A_FFMT_THS | FXOS8700_A_FFMT_THS_DBCNTM_MASK,
	     FXOS8700_A_FFMT_THS_THS_MASK | FXOS8700_A_FFMT_THS_DBCNTM_MASK}, /* Threshold */
		 /*! Configure sensor to detect freefall, raise event on X, Y, Z axes */
	    {FXOS8700_A_FFMT_CFG,
	     FXOS8700_A_FFMT_CFG_OAE_FREEFALL | FXOS8700_A_FFMT_CFG_ZEFE_RAISE_EVENT |
	         FXOS8700_A_FFMT_CFG_YEFE_RAISE_EVENT | FXOS8700_A_FFMT_CFG_XEFE_RAISE_EVENT,
	     FXOS8700_A_FFMT_CFG_OAE_MASK | FXOS8700_A_FFMT_CFG_ZEFE_MASK |
	         FXOS8700_A_FFMT_CFG_YEFE_MASK | FXOS8700_A_FFMT_CFG_XEFE_MASK},
	    {FXOS8700_CTRL_REG4, FXOS8700_CTRL_REG4_INT_EN_FFMT_EN, FXOS8700_CTRL_REG4_INT_EN_FFMT_MASK},

        /*! Pulse detection registers configurations */
		/*! Configure to raise event flag on detection of single-pulse event (spefe) on X, Y & Z axes*/
        {FXOS8700_PULSE_CFG,21,0x00},
		/*! Configure Pulse Time Limit to 50msec */
        {FXOS8700_PULSE_TMLT,80,0x00},
		/*! Configure pulse latency to 300msec */
        {FXOS8700_PULSE_LTCY,240,0x00},
		/*! Configure Pulse detection threshold for X, Y, Z axes */
        {FXOS8700_PULSE_THSX,55,0x00},
        {FXOS8700_PULSE_THSY,55,0x00},
        {FXOS8700_PULSE_THSZ,82,0x00},

        /*! VECM change detection configurations */
        { FXOS8700_A_VECM_CNT,15,0x00},
		/*! Configure VECM to enable VECM ELE (0x40) and VECM EN (0x08)*/
        { FXOS8700_A_VECM_CFG,72,0x00},
		/*! Set VECM THS to ~0.5g; THS = 0x788=>1928 (=0.47g in 2g mode) */
        { FXOS8700_A_VECM_THS_LSB,88,0x00},
        { FXOS8700_A_VECM_THS_MSB,1, FXOS8700_A_VECM_THS_MSB_A_VBECM_DBCNTM_MASK  },
        { FXOS8700_A_VECM_THS_MSB,27, FXOS8700_A_VECM_THS_MSB_A_VBECM_THS_MASK  },

        __END_WRITE_DATA__};

/*!
 * @brief Defines the register read list to read the Data Ready Status.
 */
const registerreadlist_t cFXOS8700_whoami[] = {
        {.readFrom = FXOS8700_WHO_AM_I, .numBytes = 1}, __END_READ_DATA__};
/*!
 * @brief Defines the register read list to read the Interrupt Source.
 */
const registerreadlist_t cFXOS8700_int_src[] = {
        {.readFrom = FXOS8700_INT_SOURCE, .numBytes = 1}, __END_READ_DATA__};
/*!
 * @brief Defines the register read list to read the FullScale range.
 */
const registerreadlist_t cFXOS8700_fs_src[] = {
        {.readFrom = FXOS8700_XYZ_DATA_CFG, .numBytes = 1}, __END_READ_DATA__};

/*!
 * @brief Defines the register read list to read all-registers.
 */
const registerreadlist_t FXOS8700_ALL_REG_READ[] = {{.readFrom = FXOS8700_STATUS, .numBytes = FXOS8700_NUM_REGISTERS},
                                                      __END_READ_DATA__};
/*!
 * @brief Defines the register read list to read FFMT Source.
 */
const registerreadlist_t cFXOS8700_ffmt_src[] = {
        {.readFrom = FXOS8700_A_FFMT_SRC , .numBytes = 1}, __END_READ_DATA__};
/*!
 * @brief Defines the register read list to read the PL Status.
 */
const registerreadlist_t cFXOS8700_pl_status[] = {
        {.readFrom = FXOS8700_PL_STATUS, .numBytes = 1}, __END_READ_DATA__};

/*!
 * @brief This structure defines the fxos8700 all registers metadata.
 */
typedef struct
{
    uint8_t offset;
    uint8_t value;
    uint8_t trigger;
    uint8_t read_offset;
    uint8_t read_value;
    uint8_t read_trigger;
    uint8_t readall_value[FXOS8700_NUM_REGISTERS];
    uint8_t readall_size;
    uint8_t readall_trigger;
    uint8_t toggle;
    uint8_t trigger_accel_offnoise;
    uint8_t trigger_mag_offnoise;
    uint8_t fs_value;
    uint8_t mods_value;
    uint16_t freefall_cntr;
    uint16_t tapdetect_cntr;
    uint16_t orient_cntr;
    uint16_t vecmchange_cntr;
    uint8_t reg_addr[FXOS8700_NUM_REGISTERS];
    uint8_t dataready_cntr;
    float accel[3];
    float mag[3];
} fxos8700_allregs_t;

/*!
 * @brief This structure defines the fxos8700 offset and noise calculation parameters.
 */
typedef struct
{
  	float offx;
  	float offy;
  	float offz;
  	float rmsx;
  	float rmsy;
  	float rmsz;
  	float mag_off[3];
  	float mag_rms[3];
  	uint8_t complete_accel_offnoise;
  	uint8_t complete_mag_offnoise;
} fxos8700_offset_noise_t;

/*!
 * @brief Defines host operation types.
 */
typedef enum fxos8700_operation_type
{
	FXOS8700_REG_WRITE   = 1U,
	FXOS8700_REG_READ    = 2U,
	FXOS8700_ALLREG_READ = 3U,
	FXOS8700_ACCEL_CONFIG_END

} fxos8700_operation_type_t;


/*******************************************************************************
 * Globals
 ******************************************************************************/

fxos8700_accelmagdata_t rawData;
fxos8700_allregs_t      registers;
fxos8700_offset_noise_t offnoise_data;
uint8_t prev_toggle = 1;
volatile bool bFxos8700DataReady = false;

static FMSTR_U8 recBuffer[1024*10];
FMSTR_REC_BUFF  recBuffCfg;
FMSTR_REC_VAR   recVar;
FMSTR_REC_CFG   recCfg;

/*******************************************************************************
 * Local functions
 ******************************************************************************/
/*! @brief           Function to initialize target communication to FreeMASTER host.
 *  @details         This function initializes FreeMASTER UART communication.
 *  @param[in]       void.
 *  @return          void.
 */
static void init_freemaster_uart(void);
/*! @brief           ISR for FXOS8700 data ready event.
 *  @details         This function implements ISR for FXOS8700 DRDY event.
 *  @param[in]       void *.
 *  @return          void.
 */
void fxos8700_isr_callback(void *pUserData);
/*! @brief           Function to apply FXOS8700 register write operation.
 *  @details         This function apply FXOS8700 register write based on write trigger from host.
 *  @param[in]       fxos8700_i2c_sensorhandle_t FXOS8700drv, FXOS8700 sensor I2C handle.
 *  @param[in]       uint8_t offset, the address of the register to start writing from.
 *  @param[in]       uint8_t value, value to write on register offset.
 *  @return          returns the status of the operation.
 */
int32_t apply_register_write(fxos8700_i2c_sensorhandle_t FXOS8700drv, uint8_t offset, uint8_t value);
/*! @brief           Function to apply FXOS8700 register read operation.
 *  @details         This function apply FXOS8700 register read based on read trigger from host.
 *  @param[in]       fxos8700_i2c_sensorhandle_t FXOS8700drv, FXOS8700 sensor I2C handle.
 *  @param[in]       uint8_t offset, the address of the register to read from.
 *  @param[in/out]   uint8_t *value, pointer to output buffer.
 *  @return          returns the status of the operation.
 */
int32_t apply_register_read(fxos8700_i2c_sensorhandle_t FXOS8700drv, uint8_t offset, uint8_t *value);
/*! @brief           Function to apply FXOS8700 register read-all operation.
 *  @details         This function apply FXOS8700 all-registers read based on read-all trigger from host.
 *  @param[in]       fxos8700_i2c_sensorhandle_t FXOS8700drv, FXOS8700 sensor I2C handle.
 *  @return          returns the status of the operation.
 */
int32_t apply_register_readall(fxos8700_i2c_sensorhandle_t FXOS8700drv);
/*! @brief           Function to update dropdown selection.
 *  @details         This function updates the dropdown selection values in real-time based on read/write/read-all triggers.
 *  @param[in/out]   fxos8700_allregs_t *registers, pointer to FXOS8700 all-registers metadata.
 *  @param[in]       uint8_t caller, called from which operation type.
 *  @return          returns the status of the operation.
 */
int32_t update_dropdown_selection( fxos8700_allregs_t *registers, uint8_t caller);
/*! @brief           Function to initialize offset noise measurement.
 *  @details         This function initializes offset noise measurement metadata.
 *  @param[in/out]   fxos8700_offset_noise_t *offnoiseptr, pointer to FXOS8700 offset noise metadata.
 *  @return          void.
 */
void offset_noise_init(fxos8700_offset_noise_t *offnoiseptr);
/*! @brief           Function to measure accelerometer offset noise.
 *  @details         This function measures accelerometer offset noise.
 *  @param[in]       fxos8700_accelmagdata_t *rawData, pointer to FXOS8700 rawdata metadata.
 *  @param[in/out]   fxos8700_offset_noise_t *offnoiseptr, pointer to FXOS8700 offset noise metadata.
 *  @param[in]       float sens, FXOS8700 sensitivity based on FS configuration.
 *  @return          void.
 */
void accel_off_noise(fxos8700_accelmagdata_t* rawData,fxos8700_offset_noise_t *offnoiseptr, float sens);
/*! @brief           Function to measure magnetometer offset noise.
 *  @details         This function measures magnetometer offset noise.
 *  @param[in]       fxos8700_accelmagdata_t *rawData, pointer to FXOS8700 rawdata metadata.
 *  @param[in/out]   fxos8700_offset_noise_t *offnoiseptr, pointer to FXOS8700 offset noise metadata.
 *  @return          void.
 */
void mag_off_noise(fxos8700_accelmagdata_t* rawData,fxos8700_offset_noise_t *offnoiseptr);
void FRM_Recorder_Init();

/*******************************************************************************
 * Code
 ******************************************************************************/
 
/*! This is the Sensor Data Ready ISR implementation.*/
void fxos8700_isr_callback(void *pUserData)
{ /*! @brief Set flag to indicate Sensor has signalled data ready. */
    bFxos8700DataReady = true;
}

/* Create TSA table and add output variables. */
/*!
 * @brief Target Side Addressable (TSA) table created for this application.
 */
FMSTR_TSA_TABLE_BEGIN(main_table)
	FMSTR_TSA_STRUCT(fxos8700_accelmagdata_t)
    FMSTR_TSA_MEMBER(fxos8700_accelmagdata_t, mag, FMSTR_TSA_SINT16)

	FMSTR_TSA_STRUCT(fxos8700_allregs_t)
    FMSTR_TSA_MEMBER(fxos8700_allregs_t, offset, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(fxos8700_allregs_t, value, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(fxos8700_allregs_t, trigger, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(fxos8700_allregs_t, read_offset, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(fxos8700_allregs_t, read_value, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(fxos8700_allregs_t, read_trigger, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(fxos8700_allregs_t, readall_value, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(fxos8700_allregs_t, readall_size, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(fxos8700_allregs_t, readall_trigger, FMSTR_TSA_UINT8)
	FMSTR_TSA_MEMBER(fxos8700_allregs_t, trigger_accel_offnoise, FMSTR_TSA_UINT8)
	FMSTR_TSA_MEMBER(fxos8700_allregs_t, trigger_mag_offnoise, FMSTR_TSA_UINT8)
	FMSTR_TSA_MEMBER(fxos8700_allregs_t, fs_value, FMSTR_TSA_UINT8)
	FMSTR_TSA_MEMBER(fxos8700_allregs_t, mods_value, FMSTR_TSA_UINT8)
	FMSTR_TSA_MEMBER(fxos8700_allregs_t, toggle, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(fxos8700_allregs_t, freefall_cntr, FMSTR_TSA_UINT16)
    FMSTR_TSA_MEMBER(fxos8700_allregs_t, tapdetect_cntr, FMSTR_TSA_UINT16)
    FMSTR_TSA_MEMBER(fxos8700_allregs_t, orient_cntr, FMSTR_TSA_UINT16)
	FMSTR_TSA_MEMBER(fxos8700_allregs_t, vecmchange_cntr, FMSTR_TSA_UINT16)
    FMSTR_TSA_MEMBER(fxos8700_allregs_t, reg_addr, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(fxos8700_allregs_t, accel, FMSTR_TSA_FLOAT)
    FMSTR_TSA_MEMBER(fxos8700_allregs_t, dataready_cntr, FMSTR_TSA_UINT8)

	FMSTR_TSA_STRUCT(fxos8700_offset_noise_t)
	FMSTR_TSA_MEMBER(fxos8700_offset_noise_t, offx, FMSTR_TSA_FLOAT)
	FMSTR_TSA_MEMBER(fxos8700_offset_noise_t, offy, FMSTR_TSA_FLOAT)
	FMSTR_TSA_MEMBER(fxos8700_offset_noise_t, offz, FMSTR_TSA_FLOAT)
	FMSTR_TSA_MEMBER(fxos8700_offset_noise_t, rmsx, FMSTR_TSA_FLOAT)
	FMSTR_TSA_MEMBER(fxos8700_offset_noise_t, rmsy, FMSTR_TSA_FLOAT)
	FMSTR_TSA_MEMBER(fxos8700_offset_noise_t, rmsz, FMSTR_TSA_FLOAT)
	FMSTR_TSA_MEMBER(fxos8700_offset_noise_t, mag_rms, FMSTR_TSA_FLOAT)
	FMSTR_TSA_MEMBER(fxos8700_offset_noise_t, mag_off, FMSTR_TSA_FLOAT)
	FMSTR_TSA_MEMBER(fxos8700_offset_noise_t, complete_accel_offnoise, FMSTR_TSA_UINT8)
	FMSTR_TSA_MEMBER(fxos8700_offset_noise_t, complete_mag_offnoise, FMSTR_TSA_UINT8)

    FMSTR_TSA_RO_VAR(rawData, FMSTR_TSA_USERTYPE(fxos8700_accelmagdata_t))

    FMSTR_TSA_RW_VAR(registers, FMSTR_TSA_USERTYPE(fxos8700_allregs_t))

    FMSTR_TSA_RO_VAR(offnoise_data, FMSTR_TSA_USERTYPE(fxos8700_offset_noise_t))

FMSTR_TSA_TABLE_END()

FMSTR_TSA_TABLE_LIST_BEGIN()
    FMSTR_TSA_TABLE(main_table)
FMSTR_TSA_TABLE_LIST_END()

/*!
 * @brief FreeMASTER recorder initialization
 */
void FRM_Recorder_Init()
{
    /* Do local configuration of additional recorder */

    /* Setup the additional recorder raw buffer */
    recBuffCfg.addr = recBuffer;
    recBuffCfg.size = sizeof(recBuffer);
    recBuffCfg.basePeriod_ns = 0;    /* Unknown period */
    recBuffCfg.name = "FXOS8700 3-Axis Accelerometer Data";

    FMSTR_RecorderCreate(1, &recBuffCfg);
}

/*!
 * @brief Main function
 */

int main(void)
{
    int32_t status;
    uint16_t ffmt_incr   = 0;
    uint16_t pulse_incr  = 0;
    uint16_t orient_incr = 0;
    uint16_t vecm_incr   = 0;
    uint8_t regdata;
    float sensitivity = ACCEL_2G_SENS;

    ARM_DRIVER_I2C *I2Cdrv = &I2C_S_DRIVER; // Now using the shield.h value!!!
    GENERIC_DRIVER_GPIO *pGpioDriver = &Driver_GPIO_KSDK;
    fxos8700_i2c_sensorhandle_t FXOS8700drv;

    /*! Initialize the MCU hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /*! Initialize FXOS8700_INT2 pin used by FRDM board */
    pGpioDriver->pin_init(&FXOS8700_INT2, GPIO_DIRECTION_IN, NULL, &fxos8700_isr_callback, NULL);

    /*! Initialize RGB LED pin used by FRDM board */
    pGpioDriver->pin_init(&GREEN_LED, GPIO_DIRECTION_OUT, NULL, NULL, NULL);

    /*! FreeMASTER communication layer initialization */
    init_freemaster_uart();

    /*! Initialize the I2C driver. */
    status = I2Cdrv->Initialize(I2C_S_SIGNAL_EVENT);
    if (ARM_DRIVER_OK != status)
    {
        return status;
    }

    /*! Set the I2C Power mode. */
    status = I2Cdrv->PowerControl(ARM_POWER_FULL);
    if (ARM_DRIVER_OK != status)
    {
        return status;
    }

    /*! Set the I2C bus speed. */
    status = I2Cdrv->Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_FAST);
    if (ARM_DRIVER_OK != status)
    {
        return status;
    }

    /*! Initialize the FXOS8700 sensor driver. */
    status = FXOS8700_I2C_Initialize(&FXOS8700drv, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, FXOS8700_I2C_ADDR,
                                     FXOS8700_WHO_AM_I_PROD_VALUE);
    if (SENSOR_ERROR_NONE != status)
    {
        return status;
    }

    /*!  Set the task to be executed while waiting for I2C transactions to complete. */
    FXOS8700_I2C_SetIdleTask(&FXOS8700drv, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);

    /*! Configure the fxos8700 sensor driver. */
    status = FXOS8700_I2C_Configure(&FXOS8700drv, fxos8700_Config_Hybrid);
    if (SENSOR_ERROR_NONE != status)
    {
        return status;
    }

    /*! FreeMASTER Driver Initialization */
    FMSTR_Init();

    /*! FreeMASTER Recorder Initialization */
    FRM_Recorder_Init();

    /*! Initialize trigger flags */
    registers.toggle = 1;
    registers.trigger = 0;
    registers.read_trigger = 0;
    registers.read_value = 0;
    registers.readall_trigger = 0;
    registers.trigger_accel_offnoise=0;
    registers.trigger_mag_offnoise=0;
    registers.dataready_cntr = 0;

    /*! Initialize read all values */
    for(int i = 0; i < FXOS8700_NUM_REGISTERS; i++)
    {
    	registers.readall_value[i] = 0;
    }

    for (;;) /* Forever loop */
    {

        /*! Call Recorder#0 in execution loop for generic high-speed variables sampling. */
        FMSTR_Recorder(0);

    	/*! Call FreeMASTER host in polling mode */
		FMSTR_Poll();
		
        /*! Check for any write register trigger from Host */
		if (registers.trigger == 1)
		{
		    /*! Apply Register Write */
			status = apply_register_write(FXOS8700drv, registers.offset, registers.value);
		    if (SENSOR_ERROR_NONE != status)
		    {
                return status;
		    }
		    registers.trigger = 0;
            /*! Update drop down menu selection based on updated register write */
		    update_dropdown_selection(&registers, FXOS8700_REG_WRITE);
		}

        /*! Check for any read register trigger from Host */
		if (registers.read_trigger == 1)
		{
		    /*! Apply Register Write */
			status = apply_register_read(FXOS8700drv, registers.read_offset, &(registers.read_value));
		    if (SENSOR_ERROR_NONE != status)
		    {
                return status;
		    }
		    registers.read_trigger = 0;
            /*! Update drop down menu selection based on updated register read */
		    update_dropdown_selection(&registers, FXOS8700_REG_READ);
		}

        /*! Check for any read all register trigger from Host */
		if (registers.readall_trigger == 1)
		{
		    /*! Apply Register Write */
			status = apply_register_readall(FXOS8700drv);
		    if (SENSOR_ERROR_NONE != status)
		    {
                return status;
		    }
		    registers.readall_trigger = 0;
		    registers.readall_size = FXOS8700_NUM_REGISTERS;
            /*! Update drop down menu selection based on updated all-register read */
		    update_dropdown_selection(&registers, FXOS8700_ALLREG_READ);
		}

        /*! Wait for data ready interrupt from the FXOS8700. */
        if (false == bFxos8700DataReady)
        {
            SMC_SetPowerModeWait(SMC); /* Power save, wait if nothing to do. */
            continue;
        }
        else
        { /*! Clear the data ready flag, it will be set again by the ISR. */
            bFxos8700DataReady = false;
            //pGpioDriver->toggle_pin(&GREEN_LED);
        }

        /*! Calling Recorder#1 for sampling sensor data when we get sensor data ready interrupt based on ODR. */
        FMSTR_Recorder(1);

        /*! Read all FXOS8700 registers */
        status = FXOS8700_I2C_ReadData(&FXOS8700drv, FXOS8700_ALL_REG_READ, registers.reg_addr);
        if (0 == (registers.reg_addr[0] & FXOS8700_DR_STATUS_ZYXDR_MASK))
        { /* Loop, if new sample is not available. */
            continue;
        }

        /*! Convert the raw sensor data to signed 16-bit container for display to the debug port. */
        rawData.accel[0] = ((int16_t)registers.reg_addr[1] << 8) | registers.reg_addr[2];
        rawData.accel[0] /= 4;
        rawData.accel[1] = ((int16_t)registers.reg_addr[3] << 8) | registers.reg_addr[4];
        rawData.accel[1] /= 4;
        rawData.accel[2] = ((int16_t)registers.reg_addr[5] << 8) | registers.reg_addr[6];
        rawData.accel[2] /= 4;
        rawData.mag[0] = ((int16_t)registers.reg_addr[7] << 8) | registers.reg_addr[8];
        rawData.mag[1] = ((int16_t)registers.reg_addr[9] << 8) | registers.reg_addr[10];
        rawData.mag[2] = ((int16_t)registers.reg_addr[11] << 8) | registers.reg_addr[12];

        status = FXOS8700_I2C_ReadData(&FXOS8700drv, cFXOS8700_whoami, (uint8_t *)&registers.reg_addr[13]);

        /*! Check the FS and apply sensitivity */
        status = FXOS8700_I2C_ReadData(&FXOS8700drv, cFXOS8700_fs_src, &regdata);
        if (regdata == 1)
        {
            sensitivity = ACCEL_4G_SENS;
        }
        else if (regdata == 2)
        {
            sensitivity = ACCEL_8G_SENS;
        }
        else
        {
            sensitivity = ACCEL_2G_SENS;
        }

        /*! Convert raw values to Gs */
        registers.accel[0] = (float) (rawData.accel[0] * sensitivity);
        registers.accel[1] = (float) (rawData.accel[1] * sensitivity);
        registers.accel[2] = (float) (rawData.accel[2] * sensitivity);

        /*! Increment data ready counter and check for rollover */
        registers.dataready_cntr++;
        if(MAX8BITSTORAGE == registers.dataready_cntr)
        {
        	registers.dataready_cntr = 0;
        }

        if (prev_toggle != registers.toggle)
        {
        	pGpioDriver->toggle_pin(&GREEN_LED);
        	prev_toggle = registers.toggle;
        }

        /*! Call offset and noise calculation function for FXOS8700 accelerometer */
        if (registers.trigger_accel_offnoise == 1)
        {
        	accel_off_noise(&(rawData), &(offnoise_data), sensitivity);
            if (offnoise_data.complete_accel_offnoise == 1)
            {
            	registers.trigger_accel_offnoise = 0;
            	//offnoise_data.complete_accel_offnoise = 0;
            }
        }

        /*! Call offset and noise calculation function for FXOS8700 magnetometer */
	   if (registers.trigger_mag_offnoise == 1)
	   {
		   mag_off_noise(&(rawData), &(offnoise_data));
		   if (offnoise_data.complete_mag_offnoise == 1)
		   {
			registers.trigger_mag_offnoise = 0;
			PRINTF("\r\n Mag offset X = %f  Y = %f  Z = %f\r\n", offnoise_data.mag_off[0], offnoise_data.mag_off[1], offnoise_data.mag_off[2]);
		   }
	   }

       status = FXOS8700_I2C_ReadData(&FXOS8700drv, cFXOS8700_int_src, &regdata);

        /*! The following condition checks for multiple interrupts occurring at the same time */
        if((regdata & FXOS8700_INT_SOURCE_SRC_FFMT_MASK) == 0x04)
        {
            ffmt_incr++;
            if (ffmt_incr == 1)
            {
                registers.freefall_cntr++;
            }
        }
        /*! Check for single-tap detection interrupt */
        else if((regdata & FXOS8700_INT_SOURCE_SRC_PULSE_MASK) == 0x08)
        {
            pulse_incr++;
            if (pulse_incr == 1)
            {
                registers.tapdetect_cntr++;
            }
        }
        /*! Check for Vector Magnitude change interrupt */
        else if((regdata & FXOS8700_INT_SOURCE_SRC_A_VECM_MASK) == 0x02)
        {
            vecm_incr++;
            if (vecm_incr == 1)
            {
                registers.vecmchange_cntr++;
            }
        }
        /*! Check for Vector Magnitude change interrupt */
        else if((regdata & FXOS8700_INT_SOURCE_SRC_LNDPRT_MASK) == 0x10)
        {
            orient_incr++;
            if (orient_incr == 1)
            {
                registers.orient_cntr++;
            }
        }
        /* Else send other interrupts, clear counters */
        else
        {
        	/* Reset all event counters */
            ffmt_incr = 0;
            pulse_incr = 0;
            orient_incr = 0;
            vecm_incr = 0;
        }

        /*! Read FFMT interrupt source register to clear flags */
        status = FXOS8700_I2C_ReadData(&FXOS8700drv, cFXOS8700_int_src, &regdata);
        status = FXOS8700_I2C_ReadData(&FXOS8700drv, cFXOS8700_ffmt_src, &regdata);
        status = FXOS8700_I2C_ReadData(&FXOS8700drv, cFXOS8700_pl_status, &regdata);

    }
}


/*!
 * @brief Service register write trigger from Host
 */
int32_t apply_register_write(fxos8700_i2c_sensorhandle_t FXOS8700drv, uint8_t offset, uint8_t value)
{
    int32_t status;

	if (offset > FXOS8700_NUM_REGISTERS)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	registerwritelist_t register_write[] = {
	     /*! Set register offset with provided value */
	     {offset, value, 0},
	      __END_WRITE_DATA__};

    status = FXOS8700_I2C_Configure(&FXOS8700drv, register_write);
    if (SENSOR_ERROR_NONE != status)
    {
        return SENSOR_ERROR_WRITE;
    }

    return SENSOR_ERROR_NONE;
}

/*!
 * @brief Service register read trigger from Host
 */
int32_t apply_register_read(fxos8700_i2c_sensorhandle_t FXOS8700drv, uint8_t read_offset, uint8_t *read_value)
{
    int32_t status;

	if (read_offset > FXOS8700_NUM_REGISTERS)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	registerreadlist_t register_read[] = {
		     /*! Set register offset with provided value */
	        {.readFrom = read_offset, .numBytes = 1}, __END_READ_DATA__};

    status = FXOS8700_I2C_ReadData(&FXOS8700drv, register_read, read_value);
    if (SENSOR_ERROR_NONE != status)
    {
        return SENSOR_ERROR_WRITE;
    }

    return SENSOR_ERROR_NONE;
}

/*!
 * @brief Service register read all trigger from Host
 */
int32_t apply_register_readall(fxos8700_i2c_sensorhandle_t FXOS8700drv)
{
    int32_t status;

	for (int reg_offset = FXOS8700_STATUS; reg_offset <= FXOS8700_A_FFMT_THS_Z_LSB; reg_offset++)
	{
		registerreadlist_t register_readall[] = {
				 /*! Set register offset with provided value */
				{.readFrom = reg_offset, .numBytes = 1}, __END_READ_DATA__};

		status = FXOS8700_I2C_ReadData(&FXOS8700drv, register_readall, &(registers.readall_value[reg_offset]));
		if (SENSOR_ERROR_NONE != status)
		{
			return SENSOR_ERROR_READ;
		}
	}

    return SENSOR_ERROR_NONE;
}

/*!
 * @brief Update drop down selection values based on register write, read or readall.
 */
int32_t update_dropdown_selection( fxos8700_allregs_t *registers, uint8_t caller)
{

    int32_t status = SENSOR_ERROR_NONE;

	switch (caller)
	{
		case FXOS8700_REG_WRITE:

            /*! Update drop down option based on updated read value */
		    if(FXOS8700_XYZ_DATA_CFG == registers->offset) //FS Selection
		    {
			    registers->fs_value = registers->value;
		    }
		    else if (FXOS8700_CTRL_REG2 == registers->offset)
		    {
			    registers->mods_value = registers->value;
		    }
			break;
		case FXOS8700_REG_READ: //Called from Register Read

            /*! Update drop down option based on updated read value */
		    if(FXOS8700_XYZ_DATA_CFG == registers->read_offset) //FS Selection
		    {
			    registers->fs_value = registers->read_value;
		    }
		    else if (FXOS8700_CTRL_REG2 == registers->offset)
		    {
			    registers->mods_value = registers->read_value;
		    }
			break;
		case FXOS8700_ALLREG_READ: //Called from Register ReadAll

            /*! Update drop down option based on updated read values */
			registers->fs_value = registers->reg_addr[FXOS8700_XYZ_DATA_CFG];
			registers->mods_value = registers->reg_addr[FXOS8700_CTRL_REG2];
			break;
        default:
            status = SENSOR_ERROR_INVALID_PARAM;
            break;
	}

    return status;

}

/*******************************************************************************
 * OFFSET NOISE CALCULATION
 ******************************************************************************/

/*!
 * @brief Initialize Offset-Noise Variables
 */
void offset_noise_init(fxos8700_offset_noise_t *offnoiseptr)
{
	offnoiseptr->offx = 0.0;
	offnoiseptr->offy = 0.0;
	offnoiseptr->offz = 0.0;
	offnoiseptr->rmsx = 0.0;
	offnoiseptr->rmsy = 0.0;
	offnoiseptr->rmsz = 0.0;
	offnoiseptr->mag_off[0] = 0.0;
	offnoiseptr->mag_off[1] = 0.0;
	offnoiseptr->mag_off[2] = 0.0;
	offnoiseptr->mag_rms[0] = 0.0;
	offnoiseptr->mag_rms[1] = 0.0;
	offnoiseptr->mag_rms[2] = 0.0;
	offnoiseptr->complete_accel_offnoise = 0;
	offnoiseptr->complete_mag_offnoise = 0;
}


/* Calculate Offset & Noise for ACCELEROMETER */
void accel_off_noise(fxos8700_accelmagdata_t* rawData,fxos8700_offset_noise_t *offnoiseptr, float sens)
{
	uint16_t j;
	static uint16_t k=0;
	static uint16_t cntr=0;
	static float stdx=0;
	static float stdy=0;
	static float stdz=0;
	static float xx[N], yy[N], zz[N];
	static float xm[N], ym[N], zm[N];
	static float xsq[N], ysq[N], zsq[N];
	float am[3];
	static float sumx=0.0;
	static float sumy=0.0;
	static float sumz=0.0;

    /* Init offset noise variables */
    offset_noise_init(offnoiseptr);

	cntr++;

	/* Store Accel samples and calculate sum for configured N */
	if(cntr < N)
	{
		 am[0]=rawData->accel[0]*sens;
		 am[1]=rawData->accel[1]*sens;
		 am[2]=rawData->accel[2]*sens;
		 xx[k]=am[0];
		 yy[k]=am[1];
		 zz[k]=am[2];
		 sumx+=am[0];
		 sumy+=am[1];
		 sumz+=am[2];
		 k+=1;
		 offnoiseptr->complete_accel_offnoise = 0;
	}

	/* Measure offset and RMS */
	if(cntr == N)
	{
		/* Measure average */
		sumx=sumx/(N-1);
		sumy=sumy/(N-1);
		sumz=sumz/(N-1);

		/* Measure offset */
		offnoiseptr->offx=0-sumx;
		offnoiseptr->offy=0-sumy;
		offnoiseptr->offz=1-sumz;

		/* Measure standard deviation */
		for(j=0; j<N-1; j++)
		{
			xm[j]=xx[j]-sumx;
			ym[j]=yy[j]-sumy;
			zm[j]=zz[j]-sumz;

			xsq[j]=pow(xm[j],2);
			ysq[j]=pow(ym[j],2);
			zsq[j]=pow(zm[j],2);
			stdx+=xsq[j];
			stdy+=ysq[j];
			stdz+=zsq[j];
		}
		stdx=stdx/(N-2);
		stdy=stdy/(N-2);
		stdz=stdz/(N-2);

        /* Measure RMS */
		offnoiseptr->rmsx=pow(stdx,0.5);
		offnoiseptr->rmsy=pow(stdy,0.5);
		offnoiseptr->rmsz=pow(stdz,0.5);

		/* Set the completion flag */
		offnoiseptr->complete_accel_offnoise = 1;

		/* Reset local storage */
		cntr = k = 0;
		sumx = sumy = sumz = 0;
		stdx = stdy = stdz = 0;
	}
}

/* Calculate Offset & Noise for MAGNETOMETER */
void mag_off_noise(fxos8700_accelmagdata_t* rawData,fxos8700_offset_noise_t *offnoiseptr)
{
	//local variables

	uint16_t j;
	static uint16_t k;
	static uint16_t cntr=0;
	static float stdx=0;
	static float stdy=0;
	static float stdz=0;
	static float xx[N], yy[N], zz[N];
	static float xm[N], ym[N], zm[N];
	static float xsq[N], ysq[N], zsq[N];
	float mm[3];
	float Bx[2] = {0,0};
	float By[2] = {0,0};
	float Bz[2] = {0,0};
	float sens=0.1; //uT
	static float sumx=0.0;
	static float sumy=0.0;
	static float sumz=0.0;
	//float refx, refy, refz;

    /* Init offset noise variables */
    offset_noise_init(offnoiseptr);

	cntr++;
	 if(cntr < N)
	        {
		       /* if (cntr == 1)
		        {
		        	refx = rawData->mag[0]*sens;
		        	refy = rawData->mag[1]*sens;
		        	refz = rawData->mag[2]*sens;
		        }*/
		         mm[0]=rawData->mag[0]*sens;
		         mm[1]=rawData->mag[1]*sens;
		         mm[2]=rawData->mag[2]*sens;
	        	 xx[k]=mm[0];
	        	 yy[k]=mm[1];
	        	 zz[k]=mm[2];
	        	 Bx[0]=xx[0];
	        	 Bx[1]=xx[0];
	        	 By[0]=yy[0];
	        	 By[1]=yy[0];
	        	 Bz[0]=zz[0];
	        	 Bz[1]=zz[0];
	        	 sumx+=mm[0];
	        	 sumy+=mm[1];
	        	 sumz+=mm[2];
	        	 //Bx[0]=
	        	 k+=1;
	        	 offnoiseptr->complete_mag_offnoise = 0;
	        }
	        if(cntr == N)
	        {
	        	sumx=sumx/(N-1);
	            sumy=sumy/(N-1);
	            sumz=sumz/(N-1);
	        	for (j=0; j<N; j++)
	        	{
	        		/*if (!(xx[i]>=Bx[0]))
	        		{
	        			Bx[0]=xx[i];
	        		}
	        		if(!(xx[i] <= Bx[1]))
	        		{
	        			Bx[1]=xx[i];
	        		} */
	        		if(Bx[0] > xx[j]) Bx[0]=xx[j]; //minimum value
	        		if(Bx[1] < xx[j]) Bx[1]=xx[j]; //maximum value
	        		if(By[0] > yy[j]) By[0]=yy[j];
	        		if(By[1] < yy[j]) By[1]=yy[j];
	        		if(Bz[0] > zz[j]) Bz[0]=zz[j];
	        		if(Bz[1] < zz[j]) Bz[1]=zz[j];

	        	}
	            offnoiseptr->mag_off[0]=0.5*(Bx[0]+Bx[1]);
	            offnoiseptr->mag_off[1]=0.5*(By[0]+By[1]);
	            offnoiseptr->mag_off[2]=0.5*(Bz[0]+Bz[1]);
	            for(j=0; j<N-1; j++)
	            {
	            	xm[j]=xx[j]-sumx;
	                ym[j]=yy[j]-sumy;
	                zm[j]=zz[j]-sumz;
	                 			 //PRINTF("\r\n Before X = %f  Y = %f  Z = %f\r\n", xx[j], yy[j], zz[j]);
	                xsq[j]=pow(xm[j],2);
	                ysq[j]=pow(ym[j],2);
	                zsq[j]=pow(zm[j],2);
	                stdx+=xsq[j];
	                stdy+=ysq[j];
	                stdz+=zsq[j];
	            }
	                stdx=stdx/(N-2);
	                stdy=stdy/(N-2);
	                stdz=stdz/(N-2);
	                 		 //PRINTF("\r\n Accel StdX = %f  StdY = %f  StdZ = %f\r\n", stdx, stdy, stdz);
	                offnoiseptr->mag_rms[0]=pow(stdx,0.5);
	                offnoiseptr->mag_rms[1]=pow(stdy,0.5);
	                offnoiseptr->mag_rms[2]=pow(stdz,0.5);

	                offnoiseptr->complete_mag_offnoise = 1;
	                cntr = k = 0;
	                sumx = sumy = sumz = 0;
	                stdx = stdy = stdz = 0;
	                //refx = refy = refz = 0;
	        }

}


/*!
 * @brief UART Module initialization (UART is a the standard block included e.g. in K22F)
 */
static void init_freemaster_uart(void)
{
    uart_config_t config;

    /*
     * config.baudRate_Bps = 115200U;
     * config.parityMode = kUART_ParityDisabled;
     * config.stopBitCount = kUART_OneStopBit;
     * config.txFifoWatermark = 0;
     * config.rxFifoWatermark = 1;
     * config.enableTx = false;
     * config.enableRx = false;
     */
    UART_GetDefaultConfig(&config);
    config.baudRate_Bps = 115200U;
    config.enableTx = false;
    config.enableRx = false;

    UART_Init((UART_Type*)BOARD_DEBUG_UART_BASEADDR, &config, BOARD_DEBUG_UART_CLK_FREQ);

    /* Register communication module used by FreeMASTER driver. */
    FMSTR_SerialSetBaseAddress((UART_Type*)BOARD_DEBUG_UART_BASEADDR);

#if FMSTR_SHORT_INTR || FMSTR_LONG_INTR
    /* Enable UART interrupts. */
    EnableIRQ(BOARD_UART_IRQ);
    EnableGlobalIRQ(0);
#endif
}

#if FMSTR_SHORT_INTR || FMSTR_LONG_INTR
/*
*   Application interrupt handler of communication peripheral used in interrupt modes
*   of FreeMASTER communication.
*
*   NXP MCUXpresso SDK framework defines interrupt vector table as a part of "startup_XXXXXX.x"
*   assembler/C file. The table points to weakly defined symbols, which may be overwritten by the
*   application specific implementation. FreeMASTER overrides the original weak definition and
*   redirects the call to its own handler.
*
*/

void BOARD_UART_IRQ_HANDLER(void)
{
    /* Call FreeMASTER Interrupt routine handler */
    FMSTR_SerialIsr();
    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
        exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}
#endif

