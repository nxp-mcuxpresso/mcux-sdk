/*
 * Copyright 2020-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file mma865x_freemaster_demo.c
 * @brief The mma865x_freemaster_demo.c file implements FreeMASTER demo using the ISSDK
 *        MMA865x sensor driver example demonstration with interrupt mode.
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
#include "mma865x_drv.h"

/*******************************************************************************
 * Macro Definitions
 ******************************************************************************/

#define MMA865x_NUM_REGISTERS (MMA865x_OFF_Z + 1)
#define FF_A_FFMT_THS          (0x08)       /* FreeFall Threshold Value. */
#define A_FFMT_COUNT           (0x18)       /* Freefall/motion debounce count value. */
#define PL_COUNT               (0x15)       /* Pulse debounce count value. */
#define ASLP_COUNTER           (0x07)       /* Auto Sleep after ~5s. */
#define ACCEL_2G_SENS          (0.000976)   /* Sensitivity factor for 2G FS */
#define ACCEL_4G_SENS          (0.001953)   /* Sensitivity factor for 4G FS */
#define ACCEL_8G_SENS          (0.003906)   /* Sensitivity factor for 8G FS */
#define N                      (500U)       /* Number of samples used to measure offset/noise */
#define RAW_ACCEL_DATA_SIZE    (6U)         /* Accel Data Size */
#define MAX8BITSTORAGE         (255U)

/*******************************************************************************
 * Constants
 ******************************************************************************/
/*! @brief Prepare the register write list to configure MMA865x in non-FIFO and ISR mode. */
const registerwritelist_t Mma865x_Config[] =
{   /*! Clear F_SETUP. */
	{MMA865x_F_SETUP, 0x00, 0},
    /*! Configure the MMA865x to set FS Range as 2g. */
	{MMA865x_XYZ_DATA_CFG, MMA865x_XYZ_DATA_CFG_FS_2G, MMA865x_XYZ_DATA_CFG_FS_MASK},
	/*! Configure the MMA865x to set ODR to 100Hz. */
	{MMA865x_CTRL_REG1, MMA865x_CTRL_REG1_DR_100HZ, MMA865x_CTRL_REG1_DR_MASK},
	/*! Configure the MMA865x to set High Resolution mode. */
	{MMA865x_CTRL_REG2, MMA865x_CTRL_REG2_MODS_HR, MMA865x_CTRL_REG2_MODS_MASK},
	/*! Configure the MMA865x to set interrupt polarity as Active High. */
	{MMA865x_CTRL_REG3, MMA865x_CTRL_REG3_IPOL_ACTIVE_HIGH, MMA865x_CTRL_REG3_IPOL_MASK},
	/*! Configure the MMA865x to set interrupt polarity as Active High. */
	{MMA865x_PL_CFG, MMA865x_PL_CFG_PL_EN_EN|MMA865x_PL_CFG_DBCNTM_CLEAR, 0},
	/*! Configure the MMA865x to set interrupt polarity as Active High. */
	{MMA865x_PL_COUNT, 0xFF, 0},
	/*! Configure the MMA865x to set interrupt polarity as Active High. */
	{MMA865x_FF_MT_CFG, MMA865x_FF_MT_CFG_OAE_FREEFALL|MMA865x_FF_MT_CFG_ZEFE_EN|MMA865x_FF_MT_CFG_YEFE_EN|MMA865x_FF_MT_CFG_XEFE_EN, 0},
	/*! Configure the MMA865x to set interrupt polarity as Active High. */
	{MMA865x_FF_MT_COUNT, 0x01, 0},
	/*! Configure the MMA865x to set interrupt polarity as Active High. */
	{MMA865x_FF_MT_THS, MMA865x_FF_MT_THS_DBCNTM_INC_CLR|0x02, 0},
	/*! Configure the MMA865x to set interrupt polarity as Active High. */
	{MMA865x_TRANSIENT_CFG,MMA865x_TRANSIENT_CFG_ZTEFE_EN|MMA865x_TRANSIENT_CFG_YTEFE_EN|MMA865x_TRANSIENT_CFG_XTEFE_EN, 0},
	{MMA865x_TRANSIENT_THS, MMA865x_TRANSIENT_THS_DBCNTM_INC_CLR|0x10, 0},
	{MMA865x_TRANSIENT_COUNT, 0x0C, 0},
	/*! Configure the MMA865x to set interrupt polarity as Active High. */
	{MMA865x_PULSE_CFG, MMA865x_PULSE_CFG_XSPEFE_EN|MMA865x_PULSE_CFG_YSPEFE_EN|MMA865x_PULSE_CFG_ZSPEFE_EN, 0},
	{MMA865x_PULSE_THSX, 0x37, 0},
	/*! Configure the MMA865x to set interrupt polarity as Active High. */
	{MMA865x_PULSE_THSY, 0x37, 0},
	/*! Configure the MMA865x to set interrupt polarity as Active High. */
	{MMA865x_PULSE_THSZ, 0x52, 0},
	/*! Configure the MMA865x to set interrupt polarity as Active High. */
	{MMA865x_PULSE_TMLT, 0x30, 0},
	/*! Configure the MMA865x to set interrupt polarity as Active High. */
	{MMA865x_PULSE_LTCY, 0x3C, 0},
	/*! Configure the MMA865x to enable Interrupts for Data Ready. */
	{MMA865x_CTRL_REG4, MMA865x_CTRL_REG4_INT_EN_DRDY_EN|MMA865x_CTRL_REG4_INT_EN_LNDPRT_EN|MMA865x_CTRL_REG4_INT_EN_FF_MT_EN|MMA865x_CTRL_REG4_INT_EN_TRANS_EN|MMA865x_CTRL_REG4_INT_EN_PULSE_EN, 0},
	/*! Configure the MMA865x to route Data Ready Interrupts to INT1. */
	{MMA865x_CTRL_REG5, MMA865x_CTRL_REG5_INT_CFG_DRDY_INT1, 0},
	__END_WRITE_DATA__};

/*! @brief Prepare the register read for WHOAMI Register. */
const registerreadlist_t cMMA865x_whoami[] = {
        {.readFrom = MMA865x_WHO_AM_I, .numBytes = 1}, __END_READ_DATA__};

/*! @brief Prepare the register read for INT Status Register. */
const registerreadlist_t cMMA865x_int_src[] = {
        {.readFrom = MMA865x_INT_SOURCE, .numBytes = 1}, __END_READ_DATA__};

/*! @brief Prepare the register read for FullScale range Register. */
const registerreadlist_t cMMA865x_fs_src[] = {
        {.readFrom = MMA865x_XYZ_DATA_CFG, .numBytes = 1}, __END_READ_DATA__};

/*! @brief Prepare the register read for FFMT Register. */
const registerreadlist_t cMMA865x_ffmt_src[] = {
        {.readFrom = MMA865x_FF_MT_SRC , .numBytes = 1}, __END_READ_DATA__};

/*! @brief Prepare the register read for PL Status Register. */
const registerreadlist_t cMMA865x_pl_status[] = {
		{.readFrom = MMA865x_PL_STATUS, .numBytes = 1}, __END_READ_DATA__};

/*! @brief MMA865x register list to read all registers */
const registerreadlist_t MMA865x_ALL_REG_READ[] = {{.readFrom = MMA865x_STATUS, .numBytes = MMA865x_NUM_REGISTERS},
                                                      __END_READ_DATA__};

/*! @brief This structure defines the mma865x all registers metadata.*/
typedef struct
{
    uint8_t offset;
    uint8_t value;
    uint8_t trigger;
    uint8_t read_offset;
    uint8_t read_value;
    uint8_t read_trigger;
    uint8_t readall_value[MMA865x_NUM_REGISTERS];
    uint8_t readall_size;
    uint8_t readall_trigger;
    uint8_t toggle;
    uint8_t trigger_accel_offnoise;
    uint8_t fs_value;
    uint8_t mods_value;
    uint16_t freefall_cntr;
    uint16_t tapdetect_cntr;
    uint16_t orient_cntr;
    uint16_t vecmchange_cntr;
    uint8_t reg_addr[MMA865x_NUM_REGISTERS];
    uint8_t dataready_cntr;
    float accel[3];
    float mag[3];
} mma865x_allregs_t;

/*! @brief This structure defines offset and noise calculation parameters. */
typedef struct
{
  	float offx;
  	float offy;
  	float offz;
  	float rmsx;
  	float rmsy;
  	float rmsz;
  	uint8_t complete_accel_offnoise;
} mma865x_offset_noise_t;

/*! @brief Defines MMA8652 host operation types. */
typedef enum mma8652_operation_type
{
	MMA865x_REG_WRITE   = 1U,
	MMA865x_REG_READ    = 2U,
	MMA865x_ALLREG_READ = 3U,
	MMA865x_ACCEL_CONFIG_END

} mma865x_operation_type_t;


/*******************************************************************************
 * Globals
 ******************************************************************************/

mma865x_acceldata_t rawData;
mma865x_allregs_t      registers;
mma865x_offset_noise_t offnoise_data;
uint8_t prev_toggle = 1;
volatile bool bMma8652IntFlag = false;

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
/*! @brief           ISR for MMA8652 data ready event.
 *  @details         This function implements ISR for MMA8652 DRDY event.
 *  @param[in]       void *.
 *  @return          void.
 */
void mma8652_isr_callback(void *pUserData);
/*! @brief           Function to apply MMA8652 register write operation.
 *  @details         This function apply MMA8652 register write based on write trigger from host.
 *  @param[in]       mma865x_i2c_sensorhandle_t MMA8652drv, MMA8652 sensor I2C handle.
 *  @param[in]       uint8_t offset, the address of the register to start writing from.
 *  @param[in]       uint8_t value, value to write on register offset.
 *  @return          returns the status of the operation.
 */
int32_t apply_register_write(mma865x_i2c_sensorhandle_t MMA8652drv, uint8_t offset, uint8_t value);
/*! @brief           Function to apply MMA8652 register read operation.
 *  @details         This function apply MMA8652 register read based on read trigger from host.
 *  @param[in]       mma865x_i2c_sensorhandle_t MMA8652drv, MMA8652 sensor I2C handle.
 *  @param[in]       uint8_t offset, the address of the register to read from.
 *  @param[in/out]   uint8_t *value, pointer to output buffer.
 *  @return          returns the status of the operation.
 */
int32_t apply_register_read(mma865x_i2c_sensorhandle_t MMA8652drv, uint8_t offset, uint8_t *value);
/*! @brief           Function to apply MMA8652 register read-all operation.
 *  @details         This function apply MMA8652 all-registers read based on read-all trigger from host.
 *  @param[in]       mma865x_i2c_sensorhandle_t MMA8652drv, MMA8652 sensor I2C handle.
 *  @return          returns the status of the operation.
 */
int32_t apply_register_readall(mma865x_i2c_sensorhandle_t MMA8652drv);
/*! @brief           Function to update dropdown selection.
 *  @details         This function updates the dropdown selection values in real-time based on read/write/read-all triggers.
 *  @param[in/out]   mma865x_allregs_t *registers, pointer to MMA8652 all-registers metadata.
 *  @param[in]       uint8_t caller, called from which operation type.
 *  @return          returns the status of the operation.
 */
int32_t update_dropdown_selection(mma865x_allregs_t *registers, uint8_t caller);
/*! @brief           Function to initialize offset noise measurement.
 *  @details         This function initializes offset noise measurement metadata.
 *  @param[in/out]   mma865x_allregs_t *offnoiseptr, pointer to MMA8652 offset noise metadata.
 *  @return          void.
 */
void offset_noise_init(mma865x_offset_noise_t *offnoiseptr);
/*! @brief           Function to measure accelerometer offset noise.
 *  @details         This function measures accelerometer offset noise.
 *  @param[in]       mma865x_acceldata_t *rawData, pointer to MMA8652 rawdata metadata.
 *  @param[in/out]   mma865x_offset_noise_t *offnoiseptr, pointer to MMA8652 offset noise metadata.
 *  @param[in]       float sens, MMA8652 sensitivity based on FS configuration.
 *  @return          void.
 */
void accel_off_noise(mma865x_acceldata_t* rawData, mma865x_offset_noise_t *offnoiseptr, float sens);
void FRM_Recorder_Init();

/*******************************************************************************
 * Code
 ******************************************************************************/
 
/* This is the Sensor Data Ready ISR implementation.*/
void mma8652_isr_callback(void *pUserData)
{ /*! @brief Set flag to indicate Sensor has signalled data ready. */
    bMma8652IntFlag = true;
}

/* Create TSA table and add output variables. */
/*!
 * @brief Target Side Addressable (TSA) table created for this application.
 */
FMSTR_TSA_TABLE_BEGIN(main_table)
	FMSTR_TSA_STRUCT(mma865x_acceldata_t)

	FMSTR_TSA_STRUCT(mma865x_allregs_t)
    FMSTR_TSA_MEMBER(mma865x_allregs_t, offset, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(mma865x_allregs_t, value, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(mma865x_allregs_t, trigger, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(mma865x_allregs_t, read_offset, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(mma865x_allregs_t, read_value, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(mma865x_allregs_t, read_trigger, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(mma865x_allregs_t, readall_value, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(mma865x_allregs_t, readall_size, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(mma865x_allregs_t, readall_trigger, FMSTR_TSA_UINT8)
	FMSTR_TSA_MEMBER(mma865x_allregs_t, trigger_accel_offnoise, FMSTR_TSA_UINT8)
	FMSTR_TSA_MEMBER(mma865x_allregs_t, fs_value, FMSTR_TSA_UINT8)
	FMSTR_TSA_MEMBER(mma865x_allregs_t, mods_value, FMSTR_TSA_UINT8)
	FMSTR_TSA_MEMBER(mma865x_allregs_t, toggle, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(mma865x_allregs_t, freefall_cntr, FMSTR_TSA_UINT16)
    FMSTR_TSA_MEMBER(mma865x_allregs_t, tapdetect_cntr, FMSTR_TSA_UINT16)
    FMSTR_TSA_MEMBER(mma865x_allregs_t, orient_cntr, FMSTR_TSA_UINT16)
	FMSTR_TSA_MEMBER(mma865x_allregs_t, vecmchange_cntr, FMSTR_TSA_UINT16)
    FMSTR_TSA_MEMBER(mma865x_allregs_t, reg_addr, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(mma865x_allregs_t, accel, FMSTR_TSA_FLOAT)
    FMSTR_TSA_MEMBER(mma865x_allregs_t, dataready_cntr, FMSTR_TSA_UINT8)

	FMSTR_TSA_STRUCT(mma865x_offset_noise_t)
	FMSTR_TSA_MEMBER(mma865x_offset_noise_t, offx, FMSTR_TSA_FLOAT)
	FMSTR_TSA_MEMBER(mma865x_offset_noise_t, offy, FMSTR_TSA_FLOAT)
	FMSTR_TSA_MEMBER(mma865x_offset_noise_t, offz, FMSTR_TSA_FLOAT)
	FMSTR_TSA_MEMBER(mma865x_offset_noise_t, rmsx, FMSTR_TSA_FLOAT)
	FMSTR_TSA_MEMBER(mma865x_offset_noise_t, rmsy, FMSTR_TSA_FLOAT)
	FMSTR_TSA_MEMBER(mma865x_offset_noise_t, rmsz, FMSTR_TSA_FLOAT)
	FMSTR_TSA_MEMBER(mma865x_offset_noise_t, complete_accel_offnoise, FMSTR_TSA_UINT8)

    FMSTR_TSA_RO_VAR(rawData, FMSTR_TSA_USERTYPE(mma865x_accelmagdata_t))

    FMSTR_TSA_RW_VAR(registers, FMSTR_TSA_USERTYPE(mma865x_allregs_t))

    FMSTR_TSA_RO_VAR(offnoise_data, FMSTR_TSA_USERTYPE(mma865x_offset_noise_t))

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
    recBuffCfg.name = "MMA865x 3-Axis Accelerometer Data";

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
    mma865x_i2c_sensorhandle_t MMA8652drv;

    /*! Initialize the MCU hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /*! Initialize MMA8652_INT1 pin used by FRDM board */
    pGpioDriver->pin_init(&MMA8652_INT1, GPIO_DIRECTION_IN, NULL, &mma8652_isr_callback, NULL);

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

    /*! Initialize the MMA865x sensor driver. */
    status = MMA865x_I2C_Initialize(&MMA8652drv, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, MMA8652_I2C_ADDR, MMA8652_WHOAMI_VALUE);
    if (SENSOR_ERROR_NONE != status)
    {
        return status;
    }

    /*!  Set the task to be executed while waiting for I2C transactions to complete. */
    MMA865x_I2C_SetIdleTask(&MMA8652drv, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);

    /*! Configure the mma865x sensor driver. */
    status = MMA865x_I2C_Configure(&MMA8652drv, Mma865x_Config);
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
    registers.dataready_cntr = 0;

    for(int i = 0; i < MMA865x_NUM_REGISTERS; i++)
    {
    	registers.readall_value[i] = 0;
    }

    for (;;) /* Forever loop */
    {

        /*! Calling Recorder#0 in execution loop for generic high-speed variables sampling. */
        FMSTR_Recorder(0);

    	/*! FreeMASTER host communication polling mode */
		FMSTR_Poll();
		
        /*! Check for any write register trigger from Host */
		if (registers.trigger == 1)
		{
		    /*! Apply Register Write */
			status = apply_register_write(MMA8652drv, registers.offset, registers.value);
		    if (SENSOR_ERROR_NONE != status)
		    {
                return status;
		    }
		    registers.trigger = 0;
            /*! Update drop down menu selection based on updated register write */
		    update_dropdown_selection(&registers, MMA865x_REG_WRITE);
		}

        /*! Check for any read register trigger from Host */
		if (registers.read_trigger == 1)
		{
		    /*! Apply Register Write */
			status = apply_register_read(MMA8652drv, registers.read_offset, &(registers.read_value));
		    if (SENSOR_ERROR_NONE != status)
		    {
                return status;
		    }
		    registers.read_trigger = 0;
            /*! Update drop down menu selection based on updated register read */
		    update_dropdown_selection(&registers, MMA865x_REG_READ);
		}

        /*! Check for any read all register trigger from Host */
		if (registers.readall_trigger == 1)
		{
		    /*! Apply Register Write */
			status = apply_register_readall(MMA8652drv);
		    if (SENSOR_ERROR_NONE != status)
		    {
                return status;
		    }
		    registers.readall_trigger = 0;
		    registers.readall_size = MMA865x_NUM_REGISTERS;
            /*! Update drop down menu selection based on updated all register read */
		    update_dropdown_selection(&registers, MMA865x_ALLREG_READ);
		}

        /*! Wait for data ready from the MMA865x. */
        if (false == bMma8652IntFlag)
        {
            SMC_SetPowerModeWait(SMC); /* Power save, wait if nothing to do. */
            continue;
        }
        else
        { /*! Clear the data ready flag, it will be set again by the ISR. */
            bMma8652IntFlag = false;
            //pGpioDriver->toggle_pin(&GREEN_LED);
        }

        /*! Calling Recorder#1 for sampling sensor data when we get sensor data ready interrupt based on ODR. */
        FMSTR_Recorder(1);

        /*! Read all MMA865x registers */
        status = MMA865x_I2C_ReadData(&MMA8652drv, MMA865x_ALL_REG_READ, registers.reg_addr);
        if (0 == (registers.reg_addr[0] & MMA865x_STATUS_ZYXDR_MASK))
        { /* Loop, if new sample is not available. */
            continue;
        }

        /*! Convert the raw sensor data to signed 16-bit container for display to the debug port. */
        rawData.accel[0] = ((int16_t)registers.reg_addr[1] << 8) | registers.reg_addr[2];
        rawData.accel[0] /= 16;
        rawData.accel[1] = ((int16_t)registers.reg_addr[3] << 8) | registers.reg_addr[4];
        rawData.accel[1] /= 16;
        rawData.accel[2] = ((int16_t)registers.reg_addr[5] << 8) | registers.reg_addr[6];
        rawData.accel[2] /= 16;

        status = MMA865x_I2C_ReadData(&MMA8652drv, cMMA865x_whoami, (uint8_t *)&registers.reg_addr[13]);

        /*! Check the FS and apply sensitivity */
        status = MMA865x_I2C_ReadData(&MMA8652drv, cMMA865x_fs_src, &regdata);
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

        /*! Call offset and noise calculation function for MMA8652 */
        if (registers.trigger_accel_offnoise == 1)
        {
        	accel_off_noise(&(rawData), &(offnoise_data), sensitivity);
            if (offnoise_data.complete_accel_offnoise == 1)
            {
            	registers.trigger_accel_offnoise = 0;
            	//offnoise_data.complete_accel_offnoise = 0;
            }
        }

       status = MMA865x_I2C_ReadData(&MMA8652drv, cMMA865x_int_src, &regdata);

        /*! The following condition checks for multiple interrupts occurring at the same time */
        if((regdata & MMA865x_INT_SOURCE_SRC_FF_MT_MASK) == 0x04)
        {
            ffmt_incr++;
            if (ffmt_incr == 1)
            {
                registers.freefall_cntr++;
            }
        }
        /*! Check for single-tap detection interrupt */
        else if((regdata & MMA865x_INT_SOURCE_SRC_PULSE_MASK) == 0x08)
        {
            pulse_incr++;
            if (pulse_incr == 1)
            {
                registers.tapdetect_cntr++;
            }
        }
        /*! Check for Vector Magnitude change interrupt */
        else if((regdata & MMA865x_INT_SOURCE_SRC_FF_MT_MASK) == 0x04)
        {
            vecm_incr++;
            if (vecm_incr == 1)
            {
                registers.vecmchange_cntr++;
            }
        }
        /*! Check for Vector Magnitude change interrupt */
        else if((regdata & MMA865x_INT_SOURCE_SRC_LNDPRT_MASK) == 0x10)
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
        status = MMA865x_I2C_ReadData(&MMA8652drv, cMMA865x_int_src, &regdata);
        status = MMA865x_I2C_ReadData(&MMA8652drv, cMMA865x_ffmt_src, &regdata);
        status = MMA865x_I2C_ReadData(&MMA8652drv, cMMA865x_pl_status, &regdata);

    }
}


/*!
 * @brief Service register write trigger from Host
 */
int32_t apply_register_write(mma865x_i2c_sensorhandle_t MMA8652drv, uint8_t offset, uint8_t value)
{
    int32_t status;

	if (offset > MMA865x_NUM_REGISTERS)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	registerwritelist_t mma865x_register_write[] = {
	     /*! Set register offset with provided value */
	     {offset, value, 0},
	      __END_WRITE_DATA__};

    status = MMA865x_I2C_Configure(&MMA8652drv, mma865x_register_write);
    if (SENSOR_ERROR_NONE != status)
    {
        return SENSOR_ERROR_WRITE;
    }

    return SENSOR_ERROR_NONE;
}

/*!
 * @brief Service register read trigger from Host
 */
int32_t apply_register_read(mma865x_i2c_sensorhandle_t MMA8652drv, uint8_t read_offset, uint8_t *read_value)
{
    int32_t status;

	if (read_offset > MMA865x_NUM_REGISTERS)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	registerreadlist_t mma865x_register_read[] = {
		     /*! Set register offset with provided value */
	        {.readFrom = read_offset, .numBytes = 1}, __END_READ_DATA__};

    status = MMA865x_I2C_ReadData(&MMA8652drv, mma865x_register_read, read_value);
    if (SENSOR_ERROR_NONE != status)
    {
        return SENSOR_ERROR_WRITE;
    }

    return SENSOR_ERROR_NONE;
}

/*!
 * @brief Service register read all trigger from Host
 */
int32_t apply_register_readall(mma865x_i2c_sensorhandle_t MMA8652drv)
{
    int32_t status;

	for (int reg_offset = MMA865x_STATUS; reg_offset <= MMA865x_OFF_Z; reg_offset++)
	{
		registerreadlist_t mma865x_register_readall[] = {
				 /*! Set register offset with provided value */
				{.readFrom = reg_offset, .numBytes = 1}, __END_READ_DATA__};

		status = MMA865x_I2C_ReadData(&MMA8652drv, mma865x_register_readall, &(registers.readall_value[reg_offset]));
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
int32_t update_dropdown_selection( mma865x_allregs_t *registers, uint8_t caller)
{

    int32_t status = SENSOR_ERROR_NONE;

	switch (caller)
	{
		case MMA865x_REG_WRITE:

            /*! Update drop down option based on updated read value */
		    if(MMA865x_XYZ_DATA_CFG == registers->offset) //FS Selection
		    {
			    registers->fs_value = registers->value;
		    }
		    else if (MMA865x_CTRL_REG2 == registers->offset)
		    {
			    registers->mods_value = registers->value;
		    }
			break;
		case MMA865x_REG_READ: //Called from Register Read

            /*! Update drop down option based on updated read value */
		    if(MMA865x_XYZ_DATA_CFG == registers->read_offset) //FS Selection
		    {
			    registers->fs_value = registers->read_value;
		    }
		    else if (MMA865x_CTRL_REG2 == registers->offset)
		    {
			    registers->mods_value = registers->read_value;
		    }
			break;
		case MMA865x_ALLREG_READ: //Called from Register ReadAll

            /*! Update drop down option based on updated read values */
			registers->fs_value = registers->reg_addr[MMA865x_XYZ_DATA_CFG];
			registers->mods_value = registers->reg_addr[MMA865x_CTRL_REG2];
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
void offset_noise_init(mma865x_offset_noise_t *offnoiseptr)
{
	offnoiseptr->offx = 0.0;
	offnoiseptr->offy = 0.0;
	offnoiseptr->offz = 0.0;
	offnoiseptr->rmsx = 0.0;
	offnoiseptr->rmsy = 0.0;
	offnoiseptr->rmsz = 0.0;
	offnoiseptr->complete_accel_offnoise = 0;
}


/* Calculate Offset & Noise for ACCELEROMETER */
void accel_off_noise(mma865x_acceldata_t* rawData, mma865x_offset_noise_t *offnoiseptr, float sens)
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

