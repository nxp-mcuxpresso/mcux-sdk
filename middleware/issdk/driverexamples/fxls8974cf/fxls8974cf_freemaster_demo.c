/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file fxls8974cf_freemaster_demo.c
 * @brief The fxls8974cf_freemaster_demo.c file implements FreeMASTER demo using the ISSDK
 *        FXLS8974CF sensor driver example demonstration with interrupt mode.
 */

//-----------------------------------------------------------------------
// SDK Includes
//-----------------------------------------------------------------------
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "math.h"
#ifndef CPU_LPC55S16JBD100
#include "fsl_uart.h"
#else
#include "fsl_usart.h"
#endif
#include "fsl_common.h"
#include "freemaster.h"
#include "freemaster_serial_uart.h"
//-----------------------------------------------------------------------
// CMSIS Includes
//-----------------------------------------------------------------------
#include "Driver_I2C.h"

//-----------------------------------------------------------------------
// ISSDK Includes
//-----------------------------------------------------------------------
#include "issdk_hal.h"
#include "gpio_driver.h"
#include "fxls8974_drv.h"
#include "systick_utils.h"

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
#define FXLS8974_NUM_REGISTERS (FXLS8974_SELF_TEST_CONFIG2 + 1)
#define FF_A_FFMT_THS          (0x08)       /* FreeFall Threshold Value. */
#define A_FFMT_COUNT           (0x18)       /* Freefall/motion debounce count value. */
#define PL_COUNT               (0x15)       /* Pulse debounce count value. */
#define ASLP_COUNTER           (0x07)       /* Auto Sleep after ~5s. */
#define ACCEL_2G_SENS          (0.000976)   /* Sensitivity factor for 2G FS */
#define ACCEL_4G_SENS          (0.001953)   /* Sensitivity factor for 4G FS */
#define ACCEL_8G_SENS          (0.003906)   /* Sensitivity factor for 8G FS */
#define ACCEL_16G_SENS         (0.007813)   /* Sensitivity factor for 16G FS */
#define N                      (100U)       /* Number of samples used to measure offset/noise */
#define RAW_ACCEL_DATA_SIZE    (6U)         /* Accel Data Size */
#define MAX8BITSTORAGE         (255U)
#define FXLS8974_DATA_SIZE 6
//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
/*! @brief Defines the register write list to configure FXLS8974 in Interrupt mode. */
const registerwritelist_t cFxls8974ConfigNormal[] = {
    /*! Set Full-scale range as 4G. */
    {FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_FSR_4G, FXLS8974_SENS_CONFIG1_FSR_MASK},
    /*! Clear SENS_CONFIG2 */
    {FXLS8974_SENS_CONFIG2, 0x00, 0x00},
    /*! Disable Self-Test. */
    {FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_ST_AXIS_SEL_DISABLED, FXLS8974_SENS_CONFIG1_ST_AXIS_SEL_MASK},
    /*! Set Wake Mode ODR Rate as 12.5Hz. */
    {FXLS8974_SENS_CONFIG3, FXLS8974_SENS_CONFIG3_WAKE_ODR_12_5HZ, FXLS8974_SENS_CONFIG3_WAKE_ODR_MASK},
    /*! Enable Interrupts for Data Ready Events. */
    {FXLS8974_INT_EN, FXLS8974_INT_EN_DRDY_EN_EN, FXLS8974_INT_EN_DRDY_EN_MASK},
    /*! Enable Temperature sensor. */
    {FXLS8974_SENS_CONFIG2,FXLS8974_SENS_CONFIG2_ANIC_TEMP_EN,FXLS8974_SENS_CONFIG2_ANIC_TEMP_MASK},
    /*! Set Self-Test ODR to 100 Hz. */
    {0x38,0x05,0x00},
    {0x2F,0x38,0x00},
    {0x30,0xD8,0x00},
    {0x33,0xC0,0x00},
    {0x34,0xFF,0x00},
    {0x35,0x40,0x00},
    __END_WRITE_DATA__};

/*! @brief Register settings for Self-Test in X Axis (Positive polarity). */
const registerwritelist_t cFxls8974STXP[] = {
    /* Set Self Test Axis. */
    {FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_FSR_16G, FXLS8974_SENS_CONFIG1_FSR_MASK},
    {FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_ST_AXIS_SEL_EN_X, FXLS8974_SENS_CONFIG1_ST_AXIS_SEL_MASK},
    {FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_ST_POL_POSITIVE,  FXLS8974_SENS_CONFIG1_ST_POL_MASK},
    __END_WRITE_DATA__};

/*! @brief Register settings for Self-Test in X Axis (Negative polarity). */
const registerwritelist_t cFxls8974STXN[] = {
    /* Set Self Test Axis. */
    {FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_FSR_16G, FXLS8974_SENS_CONFIG1_FSR_MASK},
    {FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_ST_AXIS_SEL_EN_X, FXLS8974_SENS_CONFIG1_ST_AXIS_SEL_MASK},
    {FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_ST_POL_NEGATIVE, FXLS8974_SENS_CONFIG1_ST_POL_MASK},
    __END_WRITE_DATA__};

/*! @brief Register settings for Self-Test in Y Axis (Positive polarity). */
const registerwritelist_t cFxls8974STYP[] = {
    /* Set Self Test Axis. */
    {FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_FSR_16G, FXLS8974_SENS_CONFIG1_FSR_MASK},
    {FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_ST_AXIS_SEL_EN_Y, FXLS8974_SENS_CONFIG1_ST_AXIS_SEL_MASK},
    {FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_ST_POL_POSITIVE,FXLS8974_SENS_CONFIG1_ST_POL_MASK},
    __END_WRITE_DATA__};

/*! @brief Register settings for Self-Test in Y Axis (Negative polarity). */
const registerwritelist_t cFxls8974STYN[] = {
    /* Set Self Test Axis. */
    {FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_FSR_16G, FXLS8974_SENS_CONFIG1_FSR_MASK},
    {FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_ST_AXIS_SEL_EN_Y, FXLS8974_SENS_CONFIG1_ST_AXIS_SEL_MASK},
    {FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_ST_POL_NEGATIVE, FXLS8974_SENS_CONFIG1_ST_POL_MASK},
    __END_WRITE_DATA__};

/*! @brief Register settings for Self-Test in Z Axis (Positive polarity). */
const registerwritelist_t cFxls8974STZP[] = {
    /* Set Self Test Axis. */
    {FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_FSR_16G, FXLS8974_SENS_CONFIG1_FSR_MASK},
    {FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_ST_AXIS_SEL_EN_Z, FXLS8974_SENS_CONFIG1_ST_AXIS_SEL_MASK},
    {FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_ST_POL_POSITIVE, FXLS8974_SENS_CONFIG1_ST_POL_MASK},
    __END_WRITE_DATA__};

/*! @brief Register settings for Self-Test in Z Axis (Negative polarity). */
const registerwritelist_t cFxls8974STZN[] = {
    /* Set Self Test Axis. */
    {FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_FSR_16G, FXLS8974_SENS_CONFIG1_FSR_MASK},
    {FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_ST_AXIS_SEL_EN_Z, FXLS8974_SENS_CONFIG1_ST_AXIS_SEL_MASK},
    {FXLS8974_SENS_CONFIG1, FXLS8974_SENS_CONFIG1_ST_POL_NEGATIVE,  FXLS8974_SENS_CONFIG1_ST_POL_MASK},
    __END_WRITE_DATA__};

/*! @brief Address of Raw Accel Data in Normal Mode. */
const registerreadlist_t cFxls8974OutputNormal[] = {{.readFrom = FXLS8974_OUT_X_LSB, .numBytes = FXLS8974_DATA_SIZE},
    __END_READ_DATA__};
	
const registerreadlist_t cFXLS8974_whoami[] = {
        {.readFrom = FXLS8974_WHO_AM_I, .numBytes = 1}, __END_READ_DATA__};

/*! @brief Prepare the register read for INT Status Register. */
const registerreadlist_t cFXLS8974_int_src[] = {
        {.readFrom = FXLS8974_INT_STATUS, .numBytes = 1}, __END_READ_DATA__};

/*! @brief Prepare the register read for FullScale range Register. */
const registerreadlist_t cFXLS8974_fs_src[] = {
        {.readFrom = FXLS8974_SENS_CONFIG1, .numBytes = 1}, __END_READ_DATA__};

/*! @brief FXLS8974 register list to read all registers */
const registerreadlist_t FXLS8974_ALL_REG_READ[] = {{.readFrom = FXLS8974_INT_STATUS, .numBytes = FXLS8974_NUM_REGISTERS},
                                                      __END_READ_DATA__};

//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
/*! @brief This structure defines the fxls8974 all registers metadata.*/
typedef struct
{
    uint8_t offset;
    uint8_t value;
    uint8_t trigger;
    uint8_t read_offset;
    uint8_t read_value;
    uint8_t read_trigger;
    uint8_t readall_value[FXLS8974_NUM_REGISTERS];
    uint8_t readall_size;
    uint8_t readall_trigger;
    uint8_t toggle;
    uint8_t trigger_accel_offnoise;
    uint8_t trigger_selftest;
    uint8_t fs_value;
    uint8_t mods_value;
    uint8_t odr_value;
    uint8_t reg_addr[FXLS8974_NUM_REGISTERS];
    uint8_t dataready_cntr;
    float accel[3];
    int16_t accelraw[3];
    uint8_t sdcd;
    int8_t temp;
    int16_t selftest[3];
    uint32_t timestamp;
} fxls8974_allregs_t;
//-----------------------------------------------------------------------
/*! @brief This structure defines the fxls8974 offset and noise calculation parameters. */
typedef struct
{
  	float offx;
  	float offy;
  	float offz;
  	float rmsx;
  	float rmsy;
  	float rmsz;
  	uint8_t complete_accel_offnoise;
} fxls8974_offset_noise_t;

/*! @brief This structure defines variables to compute self-test output change (STOC) and self-test offset (STOF). */
typedef struct
{
	int16_t x_stoc;
	int16_t y_stoc;
	int16_t z_stoc;
	int16_t x_stof;
	int16_t y_stof;
	int16_t z_stof;
  	uint8_t complete_selftest;
} fxls8974_selftest_t;

/*! @brief This structure defines the fxls8974 raw data buffer.*/
typedef struct
{
    int16_t xdata; /*!< The x accel data */
    int16_t ydata; /*!< The y accel data */
    int16_t zdata; /*!< The z accel data */
} sensor_data;


typedef union rawdata
{
	uint8_t byte_data[sizeof(sensor_data)];
	sensor_data dat;
}RAW_DATA;

/*! @brief This structure defines the fxls8974 host operation type.*/
typedef enum fxls8974_operation_type
{
	FXLS8974_REG_WRITE   = 1U,
	FXLS8974_REG_READ    = 2U,
    FXLS8974_ALLREG_READ = 3U,
	FXLS8974_ACCEL_CONFIG_END

} fxls8974_operation_type_t;

/*******************************************************************************
 * Globals
 ******************************************************************************/

fxls8974_acceldata_t rawData;
fxls8974_allregs_t      registers;
fxls8974_offset_noise_t offnoise_data;
fxls8974_selftest_t selftest;
uint8_t prev_toggle = 1;
volatile bool bFxls8974IntFlag = false;

static FMSTR_U8 recBuffer[1024*10];
FMSTR_REC_BUFF  recBuffCfg;
FMSTR_REC_VAR   recVar;
FMSTR_REC_CFG   recCfg;

int32_t status, gSystick;
static unsigned char pipe3_rxb[512];
static unsigned char pipe3_txb[0x1000];

uint8_t axis=0;
/* variables to store self-test values (Positive(P) + / Negative(N) -) */
int16_t XSTP[2]={0,0},YSTP[2]={0,0},ZSTP[2]={0,0},XSTN[2]={0,0},YSTN[2]={0,0},ZSTN[2]={0,0};


/*******************************************************************************
 * Local functions
 ******************************************************************************/
 /*! @brief           Function to initialize target communication to FreeMASTER host.
 *  @details         This function initializes FreeMASTER UART communication.
 *  @param[in]       void.
 *  @return          void.
 */
static void init_freemaster_uart(void);
/*! @brief           ISR for FXLS8974 interrupt source event.
 *  @details         This function implements ISR for FXLS8974 INT source.
 *  @param[in]       void *.
 *  @return          void.
 */
void fxls8974_isr_callback(void *pUserData);
/*! @brief           Function to apply FXLS8974 register write operation.
 *  @details         This function apply FXLS8974 register write based on write trigger from host.
 *  @param[in]       fxls8974_i2c_sensorhandle_t fxls8974Driver, FXLS8974 sensor I2C handle.
 *  @param[in]       uint8_t offset, the address of the register to start writing from.
 *  @param[in]       uint8_t value, value to write on register offset.
 *  @return          returns the status of the operation.
 */
int32_t apply_register_write(fxls8974_i2c_sensorhandle_t fxls8974Driver, uint8_t offset, uint8_t value);
/*! @brief           Function to apply FXLS8974 register read operation.
 *  @details         This function apply FXLS8974 register read based on read trigger from host.
 *  @param[in]       fxls8974_i2c_sensorhandle_t fxls8974Driver, FXLS8974 sensor I2C handle.
 *  @param[in]       uint8_t offset, the address of the register to read from.
 *  @param[in/out]   uint8_t *value, pointer to output buffer.
 *  @return          returns the status of the operation.
 */
int32_t apply_register_read(fxls8974_i2c_sensorhandle_t fxls8974Driver, uint8_t offset, uint8_t *value);
/*! @brief           Function to apply FXLS8974 register read-all operation.
 *  @details         This function apply FXLS8974 all-registers read based on read-all trigger from host.
 *  @param[in]       fxls8974_i2c_sensorhandle_t fxls8974Driver, FXLS8974 sensor I2C handle.
 *  @return          returns the status of the operation.
 */
int32_t apply_register_readall(fxls8974_i2c_sensorhandle_t fxls8974Driver);
/*! @brief           Function to update dropdown selection.
 *  @details         This function updates the dropdown selection values in real-time based on read/write/read-all triggers.
 *  @param[in/out]   fxls8974_allregs_t *registers, pointer to FXLS8974 all-registers metadata.
 *  @param[in]       uint8_t caller, called from which operation type.
 *  @return          returns the status of the operation.
 */
int32_t update_dropdown_selection(fxls8974_allregs_t *registers, uint8_t caller);
/*! @brief           Function to initialize offset noise measurement.
 *  @details         This function initializes offset noise measurement metadata.
 *  @param[in/out]   fxls8974_offset_noise_t *offnoiseptr, pointer to FXLS8974 offset noise metadata.
 *  @return          void.
 */
void offset_noise_init(fxls8974_offset_noise_t *offnoiseptr);
/*! @brief           Function to measure accelerometer offset noise.
 *  @details         This function measures accelerometer offset noise.
 *  @param[in]       fxls8974_acceldata_t *rawData, pointer to FXLS8974 rawdata metadata.
 *  @param[in/out]   fxls8974_offset_noise_t *offnoiseptr, pointer to FXLS8974 offset noise metadata.
 *  @param[in]       float sens, FXLS8974 sensitivity based on FS configuration.
 *  @return          void.
 */
void accel_off_noise(fxls8974_acceldata_t* rawData, fxls8974_offset_noise_t *offnoiseptr, float sens);
/*! @brief           Function to initialize FXLS8974 self test metadata.
 *  @details         This function initializes FXLS8974 self test metadata.
 *  @param[in/out]   fxls8974_selftest_t *selftest, pointer to FXLS8974 selftest metadata.
 *  @return          void.
 */
void selftest_init(fxls8974_selftest_t *selftest);
/*! @brief           Function to perform FXLS8974 self test.
 *  @details         This function performs FXLS8974 self test.
 *  @param[in]       fxls8974_i2c_sensorhandle_t fxls8974Driver, FXLS8974 sensor I2C handle.
 *  @param[in/out]   fxls8974_selftest_t *selftest, pointer to FXLS8974 selftest metadata.
 *  @return          returns the status of the operation..
 */
int32_t perform_selftest(fxls8974_i2c_sensorhandle_t fxls8974Driver, fxls8974_selftest_t *selftest);
void FRM_Recorder_Init();

/*******************************************************************************
 * Code
 ******************************************************************************/
void fxls8974_isr_callback(void *pUserData)
{ /*! @brief Set flag to indicate Sensor has signalled data ready. */
    bFxls8974IntFlag = true;
}

/* Create TSA table and add output variables. */
/*!
 * @brief Target Side Addressable (TSA) table created for this application.
 */
FMSTR_TSA_TABLE_BEGIN(main_table)
	FMSTR_TSA_STRUCT(fxls8974_acceldata_t)

	FMSTR_TSA_STRUCT(fxls8974_allregs_t)
    FMSTR_TSA_MEMBER(fxls8974_allregs_t, offset, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(fxls8974_allregs_t, value, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(fxls8974_allregs_t, trigger, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(fxls8974_allregs_t, read_offset, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(fxls8974_allregs_t, read_value, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(fxls8974_allregs_t, read_trigger, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(fxls8974_allregs_t, readall_value, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(fxls8974_allregs_t, readall_size, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(fxls8974_allregs_t, readall_trigger, FMSTR_TSA_UINT8)
	FMSTR_TSA_MEMBER(fxls8974_allregs_t, trigger_accel_offnoise, FMSTR_TSA_UINT8)
	FMSTR_TSA_MEMBER(fxls8974_allregs_t, trigger_selftest, FMSTR_TSA_UINT8)
	FMSTR_TSA_MEMBER(fxls8974_allregs_t, fs_value, FMSTR_TSA_UINT8)
	FMSTR_TSA_MEMBER(fxls8974_allregs_t, mods_value, FMSTR_TSA_UINT8)
	FMSTR_TSA_MEMBER(fxls8974_allregs_t, odr_value, FMSTR_TSA_UINT8)
	FMSTR_TSA_MEMBER(fxls8974_allregs_t, toggle, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(fxls8974_allregs_t, reg_addr, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(fxls8974_allregs_t, accel, FMSTR_TSA_FLOAT)
    FMSTR_TSA_MEMBER(fxls8974_allregs_t, accelraw, FMSTR_TSA_SINT16)
    FMSTR_TSA_MEMBER(fxls8974_allregs_t, sdcd, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(fxls8974_allregs_t, temp, FMSTR_TSA_SINT8)
    FMSTR_TSA_MEMBER(fxls8974_allregs_t, selftest, FMSTR_TSA_SINT16)
    FMSTR_TSA_MEMBER(fxls8974_allregs_t, dataready_cntr, FMSTR_TSA_UINT8)
    FMSTR_TSA_MEMBER(fxls8974_allregs_t, timestamp, FMSTR_TSA_UINT32)

	FMSTR_TSA_STRUCT(fxls8974_offset_noise_t)
	FMSTR_TSA_MEMBER(fxls8974_offset_noise_t, offx, FMSTR_TSA_FLOAT)
	FMSTR_TSA_MEMBER(fxls8974_offset_noise_t, offy, FMSTR_TSA_FLOAT)
	FMSTR_TSA_MEMBER(fxls8974_offset_noise_t, offz, FMSTR_TSA_FLOAT)
	FMSTR_TSA_MEMBER(fxls8974_offset_noise_t, rmsx, FMSTR_TSA_FLOAT)
	FMSTR_TSA_MEMBER(fxls8974_offset_noise_t, rmsy, FMSTR_TSA_FLOAT)
	FMSTR_TSA_MEMBER(fxls8974_offset_noise_t, rmsz, FMSTR_TSA_FLOAT)
	FMSTR_TSA_MEMBER(fxls8974_offset_noise_t, complete_accel_offnoise, FMSTR_TSA_UINT8)


	FMSTR_TSA_STRUCT(fxls8974_selftest_t)
    FMSTR_TSA_MEMBER(fxls8974_selftest_t, x_stoc, FMSTR_TSA_SINT16)
    FMSTR_TSA_MEMBER(fxls8974_selftest_t, y_stoc, FMSTR_TSA_SINT16)
    FMSTR_TSA_MEMBER(fxls8974_selftest_t, z_stoc, FMSTR_TSA_SINT16)
    FMSTR_TSA_MEMBER(fxls8974_selftest_t, x_stof, FMSTR_TSA_SINT16)
    FMSTR_TSA_MEMBER(fxls8974_selftest_t, y_stof, FMSTR_TSA_SINT16)
    FMSTR_TSA_MEMBER(fxls8974_selftest_t, z_stof, FMSTR_TSA_SINT16)
	FMSTR_TSA_MEMBER(fxls8974_selftest_t, complete_selftest, FMSTR_TSA_UINT8)

    FMSTR_TSA_RO_VAR(rawData, FMSTR_TSA_USERTYPE(fxls8974_acceldata_t))

    FMSTR_TSA_RW_VAR(registers, FMSTR_TSA_USERTYPE(fxls8974_allregs_t))

    FMSTR_TSA_RO_VAR(offnoise_data, FMSTR_TSA_USERTYPE(fxls8974_offset_noise_t))

    FMSTR_TSA_RO_VAR(selftest, FMSTR_TSA_USERTYPE(fxls8974_selftest_t))

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
    recBuffCfg.name = "FXLS8974 3-Axis Accelerometer Data";

    FMSTR_RecorderCreate(1, &recBuffCfg);
}

/*!
 * @brief Main function
 */

int main(void)
{
    int32_t status;
    uint8_t whoami = 0;
    uint8_t regdata;
    float sensitivity = ACCEL_4G_SENS;

    ARM_DRIVER_I2C *I2Cdrv = &I2C_S_DRIVER; // Now using the shield.h value!!!
    GENERIC_DRIVER_GPIO *pGpioDriver = &Driver_GPIO_KSDK;
    fxls8974_i2c_sensorhandle_t fxls8974Driver;

    /*! Initialize the MCU hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_SystickEnable();
    BOARD_InitDebugConsole();

    /*! Initialize FXLS8974_INT1 pin used by FRDM board */
    pGpioDriver->pin_init(&FXLS8974_INT1, GPIO_DIRECTION_IN, NULL, &fxls8974_isr_callback, NULL);

    /*! Initialize RGB LED pin used by FRDM board */
    pGpioDriver->pin_init(&GREEN_LED, GPIO_DIRECTION_OUT, NULL, NULL, NULL);

    /*! FreeMASTER communication layer initialization */
    init_freemaster_uart();

    /*! Initialize the I2C driver. */
    status = I2Cdrv->Initialize(I2C_S_SIGNAL_EVENT);
    if (ARM_DRIVER_OK != status)
    {
        return -1;
    }

    /*! Set the I2C Power mode. */
    status = I2Cdrv->PowerControl(ARM_POWER_FULL);
    if (ARM_DRIVER_OK != status)
    {
        return -1;
    }

    /*! Set the I2C bus speed. */
    status = I2Cdrv->Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_FAST);
    if (ARM_DRIVER_OK != status)
    {
        return -1;
    }

    /*! Initialize FXLS8974 sensor driver. */
    status = FXLS8974_I2C_Initialize(&fxls8974Driver, &I2C_S_DRIVER, I2C_S_DEVICE_INDEX, FXLS8974_I2C_ADDR,
                                     &whoami);
    if (SENSOR_ERROR_NONE != status)
    {
        return status;
    }

    /*!  Set the task to be executed while waiting for I2C transactions to complete. */
    FXLS8974_I2C_SetIdleTask(&fxls8974Driver, (registeridlefunction_t)SMC_SetPowerModeVlpr, SMC);

    /*! Configure the FXLS8974 sensor. */
    status = FXLS8974_I2C_Configure(&fxls8974Driver, cFxls8974ConfigNormal);
    if (SENSOR_ERROR_NONE != status)
    {
        return status;
    }

    /*! FreeMASTER Driver Initialization */
    FMSTR_Init();

    /*! FreeMASTER Recorder Initialization */
    FRM_Recorder_Init();

    /*! Open FreeMASTER Pipe and get a Pipe handle */
    FMSTR_HPIPE hpipe = FMSTR_PipeOpen(3, NULL, (FMSTR_ADDR)pipe3_rxb, sizeof(pipe3_rxb), (FMSTR_ADDR)pipe3_txb, sizeof(pipe3_txb),
                   FMSTR_PIPE_TYPE_ANSI_TERMINAL, "streaming");

    /*! Initialize trigger flags */
    registers.toggle = 1;
    registers.trigger = 0;
    registers.read_trigger = 0;
    registers.read_value = 0;
    registers.readall_trigger = 0;
    registers.trigger_accel_offnoise=0;
    registers.trigger_selftest=0;
    registers.dataready_cntr = 0;
    registers.selftest[0]=0;
    registers.selftest[1]=0;
    registers.selftest[2]=0;
    registers.timestamp = 0;

    for(int i = 0; i < FXLS8974_NUM_REGISTERS; i++)
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
			status = apply_register_write(fxls8974Driver, registers.offset, registers.value);
		    if (SENSOR_ERROR_NONE != status)
		    {
                return status;
		    }
		    registers.trigger = 0;
            /*! Update drop down menu selection based on updated register write */
		    update_dropdown_selection(&registers, FXLS8974_REG_WRITE);
		}

        /*! Check for any read register trigger from Host */
		if (registers.read_trigger == 1)
		{
		    /*! Apply Register Write */
			status = apply_register_read(fxls8974Driver, registers.read_offset, &(registers.read_value));
		    if (SENSOR_ERROR_NONE != status)
		    {
                return status;
		    }
		    registers.read_trigger = 0;
            /*! Update drop down menu selection based on updated register read */
		    update_dropdown_selection(&registers, FXLS8974_REG_READ);
		}

        /*! Check for any read all register trigger from Host */
		if (registers.readall_trigger == 1)
		{
		    /*! Apply Register Write */
			status = apply_register_readall(fxls8974Driver);
		    if (SENSOR_ERROR_NONE != status)
		    {
                return status;
		    }
		    registers.readall_trigger = 0;
		    registers.readall_size = FXLS8974_NUM_REGISTERS;
            /*! Update drop down menu selection based on updated all register read */
		    update_dropdown_selection(&registers, FXLS8974_ALLREG_READ);
		}

        /*! Wait for data ready interrupt from the FXLS8974. */
        if (false == bFxls8974IntFlag)
        { /* Loop, if new sample is not available. */
            SMC_SetPowerModeWait(SMC);
            continue;
        }
        else
        { /*! Clear the data ready flag, it will be set again by the ISR. */
            bFxls8974IntFlag = false;
            pGpioDriver->toggle_pin(&GREEN_LED);
        }

        /*! Calling Recorder#1 for sampling sensor data when we get sensor data ready interrupt based on ODR. */
        FMSTR_Recorder(1);

        /*! Read new raw sensor data from the FXLS8974. */
        status = FXLS8974_I2C_ReadData(&fxls8974Driver, FXLS8974_ALL_REG_READ, registers.reg_addr);
        if (ARM_DRIVER_OK != status)
        {
            return -1;
        }

        /* Update timestamp from Systick framework. */
        registers.timestamp +=BOARD_SystickElapsedTime_us(&gSystick);

        /*! Increment data ready counter and check for rollover */
        registers.dataready_cntr++;
        if(MAX8BITSTORAGE == registers.dataready_cntr)
        {
        	registers.dataready_cntr = 0;
        }

        registers.temp = registers.reg_addr[1]+25;
        registers.sdcd = (registers.reg_addr[0] & 0x10)>>4;

        /*! Convert the raw sensor data to signed 16-bit container for display to the debug port. */
        rawData.accel[0] = (int16_t)(((int16_t)(((int16_t)registers.reg_addr[3] << 8) | registers.reg_addr[2])));
        rawData.accel[1] = (int16_t)(((int16_t)(((int16_t)registers.reg_addr[5] << 8) | registers.reg_addr[4])));
        rawData.accel[2] = (int16_t)(((int16_t)(((int16_t)registers.reg_addr[7] << 8) | registers.reg_addr[6])));

        registers.accelraw[0] = rawData.accel[0];
        registers.accelraw[1] = rawData.accel[1];
        registers.accelraw[2] = rawData.accel[2];

        /*! Add data log into Pipe TX */
        FMSTR_PipePrintf(hpipe, "%d\t%d\t%d\t%d\t%d\n", registers.timestamp, registers.dataready_cntr, registers.accelraw[0], registers.accelraw[1], registers.accelraw[2]);

        status = FXLS8974_I2C_ReadData(&fxls8974Driver, cFXLS8974_whoami, (uint8_t *)&registers.reg_addr[13]);

        /*! Check the FS and apply sensitivity */
        status = FXLS8974_I2C_ReadData(&fxls8974Driver, cFXLS8974_fs_src, &regdata);
        if ((regdata & FXLS8974_SENS_CONFIG1_FSR_MASK) == 2)
        {
            sensitivity = ACCEL_4G_SENS;
        }
        else if ((regdata & FXLS8974_SENS_CONFIG1_FSR_MASK) == 4)
        {
            sensitivity = ACCEL_8G_SENS;
        }
        else if ((regdata & FXLS8974_SENS_CONFIG1_FSR_MASK) == 6)
        {
            sensitivity = ACCEL_16G_SENS;
        }
        else
        {
            sensitivity = ACCEL_2G_SENS;
        }

        /*! Convert raw values to Gs */
        registers.accel[0] = (float) (rawData.accel[0] * sensitivity);
        registers.accel[1] = (float) (rawData.accel[1] * sensitivity);
        registers.accel[2] = (float) (rawData.accel[2] * sensitivity);

        if (prev_toggle != registers.toggle)
        {
        	pGpioDriver->toggle_pin(&GREEN_LED);
        	prev_toggle = registers.toggle;
        }

        /*! Call offset and noise calculation function for FXLS8974 */
        if (registers.trigger_accel_offnoise == 1)
        {
        	accel_off_noise(&(rawData), &(offnoise_data), sensitivity);
            if (offnoise_data.complete_accel_offnoise == 1)
            {
            	registers.trigger_accel_offnoise = 0;
            }
        }

        /*! Call self-test function */
        if (registers.trigger_selftest == 1)
        {
        	perform_selftest(fxls8974Driver, &selftest);
            if (selftest.complete_selftest == 1)
            {
            	registers.trigger_selftest = 0;

                /*! Re-Configure the FXLS8974 sensor to default configuration */
                status = FXLS8974_I2C_Configure(&fxls8974Driver, cFxls8974ConfigNormal);
                if (SENSOR_ERROR_NONE != status)
                {
                    return status;
                }
            }
        }

    }
}


/*!
 * @brief Service register write trigger from Host
 */
int32_t apply_register_write(fxls8974_i2c_sensorhandle_t fxls8974Driver, uint8_t offset, uint8_t value)
{
    int32_t status;

	if (offset > FXLS8974_NUM_REGISTERS)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	registerwritelist_t fxls8974_register_write[] = {
	     /*! Set register offset with provided value */
	     {offset, value, 0},
	      __END_WRITE_DATA__};

    status = FXLS8974_I2C_Configure(&fxls8974Driver, fxls8974_register_write);
    if (SENSOR_ERROR_NONE != status)
    {
        return SENSOR_ERROR_WRITE;
    }

    return SENSOR_ERROR_NONE;
}

/*!
 * @brief Service register read trigger from Host
 */
int32_t apply_register_read(fxls8974_i2c_sensorhandle_t fxls8974Driver, uint8_t read_offset, uint8_t *read_value)
{
    int32_t status;

	if (read_offset > FXLS8974_NUM_REGISTERS)
	{
		return SENSOR_ERROR_INVALID_PARAM;
	}

	registerreadlist_t fxls8974_register_read[] = {
		     /*! Set register offset with provided value */
	        {.readFrom = read_offset, .numBytes = 1}, __END_READ_DATA__};

    status = FXLS8974_I2C_ReadData(&fxls8974Driver, fxls8974_register_read, read_value);
    if (SENSOR_ERROR_NONE != status)
    {
        return SENSOR_ERROR_WRITE;
    }

    return SENSOR_ERROR_NONE;
}

/*!
 * @brief Service register read all trigger from Host
 */
int32_t apply_register_readall(fxls8974_i2c_sensorhandle_t fxls8974Driver)
{
    int32_t status;

	for (int reg_offset = FXLS8974_INT_STATUS; reg_offset <= FXLS8974_SELF_TEST_CONFIG2; reg_offset++)
	{
		registerreadlist_t fxls8974_register_readall[] = {
				 /*! Set register offset with provided value */
				{.readFrom = reg_offset, .numBytes = 1}, __END_READ_DATA__};

		status = FXLS8974_I2C_ReadData(&fxls8974Driver, fxls8974_register_readall, &(registers.readall_value[reg_offset]));
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
int32_t update_dropdown_selection(fxls8974_allregs_t *registers, uint8_t caller)
{

    int32_t status = SENSOR_ERROR_NONE;

	switch (caller)
	{
		case FXLS8974_REG_WRITE:

            /*! Update drop down option based on updated read value */
		    if(FXLS8974_SENS_CONFIG1 == registers->offset) //FS Selection
		    {
			    registers->fs_value = registers->value;
		    }
		    else if (FXLS8974_SENS_CONFIG2 == registers->offset)
		    {
			    registers->mods_value = registers->value;
		    }
		    else if (FXLS8974_SENS_CONFIG3 == registers->offset)
		    {
			    registers->odr_value = registers->value;
		    }
			break;
		case FXLS8974_REG_READ: //Called from Register Read

            /*! Update drop down option based on updated read value */
		    if(FXLS8974_SENS_CONFIG1 == registers->read_offset) //FS Selection
		    {
			    registers->fs_value = registers->read_value;
		    }
		    else if (FXLS8974_SENS_CONFIG2 == registers->read_offset)
		    {
			    registers->mods_value = registers->read_value;
		    }
		    else if (FXLS8974_SENS_CONFIG3 == registers->read_offset)
		    {
			    registers->odr_value = registers->read_value;
		    }
			break;
		case FXLS8974_ALLREG_READ: //Called from Register ReadAll

            /*! Update drop down option based on updated read values */
			registers->fs_value   = registers->reg_addr[FXLS8974_SENS_CONFIG1];
			registers->mods_value = registers->reg_addr[FXLS8974_SENS_CONFIG2];
			registers->odr_value = registers->reg_addr[FXLS8974_SENS_CONFIG3];
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
void offset_noise_init(fxls8974_offset_noise_t *offnoiseptr)
{
	offnoiseptr->offx = 0.0;
	offnoiseptr->offy = 0.0;
	offnoiseptr->offz = 0.0;
	offnoiseptr->rmsx = 0.0;
	offnoiseptr->rmsy = 0.0;
	offnoiseptr->rmsz = 0.0;
	offnoiseptr->complete_accel_offnoise = 0;
}


/* Calculate Offset & Noise for FXLS8974 */
void accel_off_noise(fxls8974_acceldata_t* rawData, fxls8974_offset_noise_t *offnoiseptr, float sens)
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

			xsq[j]=(float)pow(xm[j],2);
			ysq[j]=(float)pow(ym[j],2);
			zsq[j]=(float)pow(zm[j],2);
			stdx+=xsq[j];
			stdy+=ysq[j];
			stdz+=zsq[j];
		}
		stdx=stdx/(N-2);
		stdy=stdy/(N-2);
		stdz=stdz/(N-2);

        /* Measure RMS */
		offnoiseptr->rmsx=(float)pow(stdx,0.5);
		offnoiseptr->rmsy=(float)pow(stdy,0.5);
		offnoiseptr->rmsz=(float)pow(stdz,0.5);

		/* Set the completion flag */
		offnoiseptr->complete_accel_offnoise = 1;

		/* Reset local storage */
		cntr = k = 0;
		sumx = sumy = sumz = 0;
		stdx = stdy = stdz = 0;
	}
}

/*!
 * @brief Initialize Offset-Noise Variables
 */
void selftest_init(fxls8974_selftest_t *selftest)
{
	selftest->x_stoc = 0;
	selftest->y_stoc = 0;
	selftest->z_stoc = 0;
	selftest->x_stof = 0;
	selftest->y_stof = 0;
	selftest->z_stof = 0;
	selftest->complete_selftest = 0;
}


int32_t perform_selftest(fxls8974_i2c_sensorhandle_t fxls8974Driver, fxls8974_selftest_t *selftest)
{
	int32_t status;

	axis=0;

    /* Initialize self-test parameters */
	selftest_init(selftest);

	while (axis<6)
	{

		switch(axis)
		{
			case 0:status = FXLS8974_I2C_Configure(&fxls8974Driver, cFxls8974STXP);break;
			case 1:status = FXLS8974_I2C_Configure(&fxls8974Driver, cFxls8974STXN);break;
			case 2:status = FXLS8974_I2C_Configure(&fxls8974Driver, cFxls8974STYP);break;
			case 3:status = FXLS8974_I2C_Configure(&fxls8974Driver, cFxls8974STYN);break;
			case 4:status = FXLS8974_I2C_Configure(&fxls8974Driver, cFxls8974STZP);break;
			case 5:status = FXLS8974_I2C_Configure(&fxls8974Driver, cFxls8974STZN);break;
			default:break;
		}

		if (ARM_DRIVER_OK != status)
		{
			return status;
		}

		int counter =0;
		for(counter=0;counter<1;counter++)
		{

			// In ISR Mode we do not need to check Data Ready Register.
			// The receipt of interrupt will indicate data is ready.
			RAW_DATA data_ = {0x00};
			while(false == bFxls8974IntFlag)
			{

			}

			/*! Set device to Standby mode. */
			Register_I2C_Write(&I2C_S_DRIVER,&(fxls8974Driver.deviceInfo),FXLS8974_I2C_ADDR, FXLS8974_SENS_CONFIG1,0x00,0x00,0x00);
			if (ARM_DRIVER_OK != status)
			{
				return SENSOR_ERROR_WRITE;
			}


			bFxls8974IntFlag = false;
			//pGpioDriver->toggle_pin(&RED_LED);

			/*! Read new raw sensor data from the FXLS8974. */
			status = FXLS8974_I2C_ReadData(&fxls8974Driver, cFxls8974OutputNormal, &data_.byte_data[0]);
			if (ARM_DRIVER_OK != status)
			{ /* Read did not work, so loop. */
				continue;
			}

			/* store the self-test values for each axis & for each polarity*/
			switch(axis)
			{
			case 0: XSTP[counter]= data_.dat.xdata;break;
			case 1: XSTN[counter]= data_.dat.xdata;break;
			case 2: YSTP[counter]= data_.dat.ydata;break;
			case 3: YSTN[counter]= data_.dat.ydata;break;
			case 4: ZSTP[counter]= data_.dat.zdata;break;
			case 5: ZSTN[counter]= data_.dat.zdata;break;
			default:break;
			}

		}

		BOARD_DELAY_ms(1000);
		axis++;
	}

		/* compute self-test output change*/
	    selftest->x_stoc=(XSTP[0]-XSTN[0])/2;
	    selftest->y_stoc=(YSTP[0]-YSTN[0])/2;
	    selftest->z_stoc=(ZSTP[0]-ZSTN[0])/2;

		/* compute self-test offset*/
	    selftest->x_stof=(XSTP[0]+XSTN[0])/2;
	    selftest->y_stof=(YSTP[0]+YSTN[0])/2;
	    selftest->z_stof=(ZSTP[0]+ZSTN[0])/2;

	    selftest->complete_selftest = 1;
	    return SENSOR_ERROR_NONE;
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

