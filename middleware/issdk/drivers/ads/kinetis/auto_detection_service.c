/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file auto_detection_service.c
 * @brief The auto detection service file implements auto detection sequence
 *        for discovery of FRDM Board and Sensor Shield Board.
 */

#include <stdio.h>
#include <stdint.h>

#include "diff_p.h"
#include "mma9553.h"
#include "mpl3115.h"
#include "mag3110.h"
#include "mma845x.h"
#include "mma865x.h"
#include "fxls8962.h"
#include "fxpq3115.h"
#include "fxos8700.h"
#include "mma8491q.h"
#include "fxas21002.h"
#include "fxlc95000.h"
#include "fxls8471q.h"

#include "issdk_hal.h"
#include "gpio_driver.h"
#include "systick_utils.h"
#include "register_io_spi.h"
#include "register_io_i2c.h"
#include "auto_detection_shield.h"
#include "auto_detection_service.h"

#include "fsl_flash.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*!
* @brief These variables are specific to SPI access to the FXLS8471 for ADS.
*/
#define FXLS8471Q_SPI_CMD_LEN (2)
#define FXLS8471Q_SS_ACTIVE_VALUE SPI_SS_ACTIVE_LOW

/*!
* @brief These variables are specific to SPI access to the FXLS8962 for ADS.
*/
#define FXLS8962_SPI_CMD_LEN (2)
#define FXLS8962_SS_ACTIVE_VALUE SPI_SS_ACTIVE_LOW

/*!
* @brief These variables are specific to SPI access to the DIFF_P for ADS.
*/
#define DIFF_P_SPI_CMD_LEN (1)
#define DIFF_P_SS_ACTIVE_VALUE SPI_SS_ACTIVE_LOW

/*!
* @brief These variables are specific to MMA8491Q which does not have a Who Am I register.
*/
#define MMA8491Q_WHO_AM_I (MMA8491Q_STATUS)
#define MMA8491Q_WHO_AM_I_VALUE                                                                                       \
    (MMA8491Q_STATUS_RESERVED_ZERO | MMA8491Q_STATUS_XDR_DRDY | MMA8491Q_STATUS_YDR_DRDY | MMA8491Q_STATUS_ZDR_DRDY | \
     MMA8491Q_STATUS_ZYXDR_DRDY)

#define ADS_QUERY_NUM (sizeof(ADS_SensorQueryList) / sizeof(sensorAccess_t))
#define ADS_NUM_BOARDS (sizeof(gADS_QueryMap) / ADS_QUERY_NUM)
#define SPI_MAX_MSG_SIZE (64)

/*******************************************************************************
* Constants
******************************************************************************/
/*! @brief The Read Version Info Command for FXLC95000. */
const uint8_t ReadVersionInfo_MMA9553[4] = {0x00, 0x00, 0x00, 0x0C};

/*!
* @brief This constant data structure contains the expected valid MCU SDID combinations.
*/
const mcuSDID_t ADS_ValidSDIDValues[] = {
    {0, 5, 1, 2, 2, ADS_RD_KL25_AGMP01}, // RD-KL25-AGMP01
    {0, 5, 1, 2, 6, ADS_FRDM_KL25Z},     // FRDM-KL25Z
    {0, 7, 1, 2, 5, ADS_FRDM_KL27Z},     // FRDM-KL27Z
    {2, 2, 0, 1, 5, ADS_FRDM_K22F},      // FRDM-K22F
    {6, 2, 0, 4, 8, ADS_FRDM_K64F},      // FRDM-K64F Note: SubFamily reads 2 instead of expected 4 (known errata)
    {1, 5, 2, 0, 10, ADS_FRDM_KE15Z},    // FRDM-KE15Z
    {0, 1, 5, 4, 4, ADS_FRDM_KW41Z},     // FRDM-KW41Z
    //{0, 4, 5, 0, 8, ADS_FRDM_K32W042},    FRDM-K32W042
};

/*!
* @brief This constant data structure contains the expected valid comm/sensor/who_am_i combinations.
*/
const sensorAccess_t ADS_SensorQueryList[] = {
    {ADS_SPI_DEV, FXLS8471, FXLS8471Q_WHO_AM_I, FXLS8471Q_WHO_AM_I_WHOAMI_VALUE, 0xFF},
    {ADS_SPI_DEV, FXLS8962, FXLS8962_WHO_AM_I, FXLS8962_WHOAMI_VALUE, 0xFF},
    {ADS_SPI_DEV, DIFF_P, DIFF_P_WHO_AM_I, DIFF_P_NPS3000VV_WHOAMI_VALUE, 0xFC},
    {ADS_I2C_EXT, FXLS8962_I2C_ADDR, FXLS8962_WHO_AM_I, FXLS8962_WHOAMI_VALUE, 0xFF},
    {ADS_I2C_EXT, FXAS21002_I2C_ADDR, FXAS21002_WHO_AM_I, FXAS21002_WHO_AM_I_WHOAMI_PROD_VALUE, 0xFF},
    {ADS_I2C_EXT, FXLC95000, ADS_NO_WHO_AM_I, ADS_NO_WHO_AM_I, 0xFF},
    {ADS_I2C_EXT, FXOS8700_I2C_ADDR, FXOS8700_WHO_AM_I, FXOS8700_WHO_AM_I_PROD_VALUE, 0xFF},
    {ADS_I2C_EXT, FXPQ3115_I2C_ADDR, FXPQ3115_WHO_AM_I, FXPQ3115_WHOAMI_VALUE, 0xFF},
    {ADS_I2C_EXT, MAG3110_I2C_ADDR, MAG3110_WHO_AM_I, MAG3110_WHOAMI_VALUE, 0xFF},
    {ADS_I2C_EXT, MMA8491_I2C_ADDR, MMA8491Q_WHO_AM_I, MMA8491Q_WHO_AM_I_VALUE, 0xF0},
    {ADS_I2C_EXT, MMA8652_I2C_ADDR, MMA865x_WHO_AM_I, MMA8652_WHOAMI_VALUE, 0xFF},
    {ADS_I2C_EXT, MMA9553, ADS_NO_WHO_AM_I, ADS_NO_WHO_AM_I, 0xFF},
    {ADS_I2C_EXT, DIFF_P_I2C_ADDR, DIFF_P_WHO_AM_I, DIFF_P_NPS3000VV_WHOAMI_VALUE, 0xFC},
    {ADS_I2C_EXT, MPL3115_I2C_ADDR, MPL3115_WHO_AM_I, MPL3115_WHOAMI_VALUE, 0xFF},
    {ADS_I2C_INT, MMA8451_I2C_ADDR, MMA845x_WHO_AM_I, MMA8451_WHO_AM_I_WHOAMI_VALUE, 0xFF},
};

/*!
* @brief These are the expected query signatures for the shield boards.
*/
const ADS_Status_t gADS_QueryMap[][ADS_QUERY_NUM] = {
    {
        // FRDM-STBC-AGM01
        ADS_FAIL, // FXLS8471
        ADS_FAIL, // FXLS8962
        ADS_FAIL, // DIFF-P
        ADS_FAIL, // FXLS8962
        ADS_OK,   // FXAS21002
        ADS_FAIL, // FXLC95000
        ADS_OK,   // FXOS8700
        ADS_FAIL, // FXPQ3115
        ADS_FAIL, // MAG3110
        ADS_FAIL, // MMA8491
        ADS_FAIL, // MMA865x
        ADS_FAIL, // MMA9553
        ADS_FAIL, // DIFF-P
        ADS_FAIL, // MPL3115
        ADS_NULL, // MMA845x
    },
    {
        //  FRDM-STBC-SA9500
        ADS_FAIL, // FXLS8471
        ADS_FAIL, // FXLS8962
        ADS_FAIL, // DIFF-P
        ADS_FAIL, // FXLS8962
        ADS_FAIL, // FXAS21002
        ADS_OK,   // FXLC95000
        ADS_FAIL, // FXOS8700
        ADS_FAIL, // FXPQ3115
        ADS_FAIL, // MAG3110
        ADS_FAIL, // MMA8491
        ADS_FAIL, // MMA865x
        ADS_FAIL, // MMA9553
        ADS_FAIL, // DIFF-P
        ADS_FAIL, // MPL3115
        ADS_NULL, // MMA845x
    },
    {
        //  FRDMSTBC-A8471
        ADS_OK,   // FXLS8471
        ADS_FAIL, // FXLS8962
        ADS_FAIL, // DIFF-P
        ADS_FAIL, // FXLS8962
        ADS_FAIL, // FXAS21002
        ADS_FAIL, // FXLC95000
        ADS_FAIL, // FXOS8700
        ADS_FAIL, // FXPQ3115
        ADS_FAIL, // MAG3110
        ADS_FAIL, // MMA8491
        ADS_FAIL, // MMA865x
        ADS_FAIL, // MMA9553
        ADS_FAIL, // DIFF-P
        ADS_FAIL, // MPL3115
        ADS_NULL, // MMA845x
    },
    {
        //  FRDMSTBC-A8491
        ADS_FAIL, // FXLS8471
        ADS_FAIL, // FXLS8962
        ADS_FAIL, // DIFF-P
        ADS_FAIL, // FXLS8962
        ADS_FAIL, // FXAS21002
        ADS_FAIL, // FXLC95000
        ADS_FAIL, // FXOS8700
        ADS_FAIL, // FXPQ3115
        ADS_FAIL, // MAG3110
        ADS_OK,   // MMA8491
        ADS_FAIL, // MMA865x
        ADS_FAIL, // MMA9553
        ADS_FAIL, // DIFF-P
        ADS_FAIL, // MPL3115
        ADS_NULL, // MMA845x
    },
    {
        //  FRDMSTBC-P3115
        ADS_FAIL, // FXLS8471
        ADS_FAIL, // FXLS8962
        ADS_FAIL, // DIFF-P
        ADS_FAIL, // FXLS8962
        ADS_FAIL, // FXAS21002
        ADS_FAIL, // FXLC95000
        ADS_FAIL, // FXOS8700
        ADS_FAIL, // FXPQ3115
        ADS_FAIL, // MAG3110
        ADS_FAIL, // MMA8491
        ADS_FAIL, // MMA865x
        ADS_FAIL, // MMA9553
        ADS_FAIL, // DIFF-P
        ADS_OK,   // MPL3115
        ADS_NULL, // MMA845x
    },
    {
        //  FRDMSTBC-DIFF-P SPI
        ADS_FAIL, // FXLS8471
        ADS_FAIL, // FXLS8962
        ADS_OK,   // DIFF-P
        ADS_FAIL, // FXLS8962
        ADS_FAIL, // FXAS21002
        ADS_FAIL, // FXLC95000
        ADS_FAIL, // FXOS8700
        ADS_FAIL, // FXPQ3115
        ADS_FAIL, // MAG3110
        ADS_FAIL, // MMA8491
        ADS_FAIL, // MMA865x
        ADS_FAIL, // MMA9553
        ADS_FAIL, // DIFF-P
        ADS_FAIL, // MPL3115
        ADS_NULL, // MMA845x
    },
    {
        //  FRDMSTBC-DIFF-P I2C
        ADS_FAIL, // FXLS8471
        ADS_FAIL, // FXLS8962
        ADS_FAIL, // DIFF-P
        ADS_FAIL, // FXLS8962
        ADS_FAIL, // FXAS21002
        ADS_FAIL, // FXLC95000
        ADS_FAIL, // FXOS8700
        ADS_FAIL, // FXPQ3115
        ADS_FAIL, // MAG3110
        ADS_FAIL, // MMA8491
        ADS_FAIL, // MMA865x
        ADS_FAIL, // MMA9553
        ADS_OK,   // DIFF-P
        ADS_FAIL, // MPL3115
        ADS_NULL, // MMA845x
    },
    {
        //  FRDMSTBC-B3115
        ADS_FAIL, // FXLS8471
        ADS_FAIL, // FXLS8962
        ADS_FAIL, // DIFF-P
        ADS_FAIL, // FXLS8962
        ADS_FAIL, // FXAS21002
        ADS_FAIL, // FXLC95000
        ADS_FAIL, // FXOS8700
        ADS_OK,   // FXPQ3115
        ADS_FAIL, // MAG3110
        ADS_FAIL, // MMA8491
        ADS_FAIL, // MMA865x
        ADS_FAIL, // MMA9553
        ADS_FAIL, // DIFF-P
        ADS_FAIL, // MPL3115
        ADS_NULL, // MMA845x
    },
    {
        //  FRDM-FXS-MULT2-B
        ADS_OK,   // FXLS8471
        ADS_FAIL, // FXLS8962
        ADS_FAIL, // DIFF-P
        ADS_FAIL, // FXLS8962
        ADS_OK,   // FXAS21002
        ADS_FAIL, // FXLC95000
        ADS_OK,   // FXOS8700
        ADS_FAIL, // FXPQ3115
        ADS_OK,   // MAG3110
        ADS_FAIL, // MMA8491
        ADS_OK,   // MMA865x
        ADS_OK,   // MMA9553
        ADS_FAIL, // DIFF-P
        ADS_OK,   // MPL3115
        ADS_NULL, // MMA845x
    },
    {
        //  FRDM-STBC-AGMP03 over SPI
        ADS_FAIL, // FXLS8471
        ADS_OK,   // FXLS8962
        ADS_FAIL, // DIFF-P
        ADS_FAIL, // FXLS8962
        ADS_FAIL, // FXAS21002
        ADS_FAIL, // FXLC95000
        ADS_FAIL, // FXOS8700
        ADS_FAIL, // FXPQ3115
        ADS_OK,   // MAG3110
        ADS_FAIL, // MMA8491
        ADS_FAIL, // MMA865x
        ADS_FAIL, // MMA9553
        ADS_FAIL, // DIFF-P
        ADS_OK,   // MPL3115
        ADS_NULL, // MMA845x
    },
    {
        //  FRDM-STBC-AGMP03 over I2C
        ADS_FAIL, // FXLS8471
        ADS_FAIL, // FXLS8962
        ADS_FAIL, // DIFF-P
        ADS_OK,   // FXLS8962
        ADS_OK,   // FXAS21002
        ADS_FAIL, // FXLC95000
        ADS_FAIL, // FXOS8700
        ADS_FAIL, // FXPQ3115
        ADS_OK,   // MAG3110
        ADS_FAIL, // MMA8491
        ADS_FAIL, // MMA865x
        ADS_FAIL, // MMA9553
        ADS_FAIL, // DIFF-P
        ADS_OK,   // MPL3115
        ADS_NULL, // MMA845x
    },
    {
        //  FRDM-STBC-AGM04
        ADS_FAIL, // FXLS8471
        ADS_FAIL, // FXLS8962
        ADS_FAIL, // DIFF-P
        ADS_FAIL, // FXLS8962
        ADS_OK,   // FXAS21002
        ADS_FAIL, // FXLC95000
        ADS_FAIL, // FXOS8700
        ADS_FAIL, // FXPQ3115
        ADS_OK,   // MAG3110
        ADS_FAIL, // MMA8491
        ADS_OK,   // MMA865x
        ADS_FAIL, // MMA9553
        ADS_FAIL, // DIFF-P
        ADS_FAIL, // MPL3115
        ADS_NULL, // MMA845x
    },
    {
        //   ON BOARD SENSORS (MMA8451)
        ADS_FAIL, // FXLS8471
        ADS_FAIL, // FXLS8962
        ADS_FAIL, // DIFF-P
        ADS_FAIL, // FXLS8962
        ADS_FAIL, // FXAS21002
        ADS_FAIL, // FXLC95000
        ADS_FAIL, // FXOS8700
        ADS_FAIL, // FXPQ3115
        ADS_FAIL, // MAG3110
        ADS_FAIL, // MMA8491
        ADS_FAIL, // MMA865x
        ADS_FAIL, // MMA9553
        ADS_FAIL, // DIFF-P
        ADS_FAIL, // MPL3115
        ADS_OK,   // MMA845x
    },
    {
        //  RD-KL25-AGMP01
        ADS_FAIL, // FXLS8471
        ADS_FAIL, // FXLS8962
        ADS_FAIL, // DIFF-P
        ADS_FAIL, // FXLS8962
        ADS_OK,   // FXAS21002
        ADS_FAIL, // FXLC95000
        ADS_OK,   // FXOS8700
        ADS_FAIL, // FXPQ3115
        ADS_FAIL, // MAG3110
        ADS_FAIL, // MMA8491
        ADS_FAIL, // MMA865x
        ADS_FAIL, // MMA9553
        ADS_FAIL, // DIFF-P
        ADS_OK,   // MPL3115
        ADS_NULL, // MMA845x
    },
};

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
/*!
* @brief This global contains the results from the sensor query.
*/
ADS_Status_t gADS_QueryResults[ADS_QUERY_NUM];

char ADS_ShieldList[][ADS_MAX_STRING_LENGTH] = {
    "FRDM-STBC-AGM01",  "FRDM-STBC-SA9500", "FRDMSTBC-A8471",   "FRDMSTBC-A8491",
    "FRDMSTBC-P3115",   "FRDMSTBI-DP300x",  "FRDMSTBI-DP300x",  "FRDMSTBI-B3115",
    "FRDM-FXS-MULT2-B", "FRDM-STBC-AGMP03", "FRDM-STBC-AGMP03",	"FRDM-STBC-AGM04",
    "OnBoard",          "OnBoard",
};

/*!
* @brief These values hold the ARM CMSIS Driver interface pointers.
*/
ARM_DRIVER_SPI *SPIdrv = &SPI_S_DRIVER;
ARM_DRIVER_I2C *I2CextDrv = &I2C_S1_DRIVER;
ARM_DRIVER_I2C *I2CintDrv = &I2C_BB_DRIVER;
GENERIC_DRIVER_GPIO *pGPIODriver = &Driver_GPIO_KSDK;

spiSlaveSpecificParams_t spiParams_8471;
spiSlaveSpecificParams_t spiParams_8962;
spiSlaveSpecificParams_t spiParams_diff_p;
uint8_t spiRead_CmdBuffer[SPI_MAX_MSG_SIZE] = {0};
uint8_t spiRead_DataBuffer[SPI_MAX_MSG_SIZE] = {0};
uint8_t spiWrite_CmdDataBuffer[SPI_MAX_MSG_SIZE] = {0};

/*******************************************************************************
* FXLS8471 SPI Specific Functions
*****************************************************************************/
void ADS_FXLS8471Q_SPI_ReadPreprocess(void *pCmdOut, uint32_t offset, uint32_t size)
{
    spiCmdParams_t *pSlaveCmd = pCmdOut;

    uint8_t *pWBuff = spiRead_CmdBuffer;
    uint8_t *pRBuff = spiRead_DataBuffer;

    /* Formatting for Read command of FXLS8471Q SENSOR. */
    *(pWBuff) = offset & 0x7F; /* offset is the internal register address of the sensor at which write is performed. */
    *(pWBuff + 1) = offset & 0x80;

    // Create the slave read command.
    pSlaveCmd->size = size + FXLS8471Q_SPI_CMD_LEN;
    pSlaveCmd->pWriteBuffer = pWBuff;
    pSlaveCmd->pReadBuffer = pRBuff;
}

void ADS_FXLS8471Q_SPI_WritePreprocess(void *pCmdOut, uint32_t offset, uint32_t size, void *pWritebuffer)
{
    spiCmdParams_t *pSlaveCmd = pCmdOut;

    uint8_t *pWBuff = spiWrite_CmdDataBuffer;
    uint8_t *pRBuff = spiWrite_CmdDataBuffer + size + FXLS8471Q_SPI_CMD_LEN;

    /* Formatting for Write command of FXLS8471Q SENSOR. */
    *(pWBuff) = offset | 0x80; /* offset is the internal register address of the sensor at which write is performed. */
    *(pWBuff + 1) = offset & 0x80;

    /* Copy the slave write command */
    memcpy(pWBuff + FXLS8471Q_SPI_CMD_LEN, pWritebuffer, size);

    /* Create the slave command. */
    pSlaveCmd->size = size + FXLS8471Q_SPI_CMD_LEN;
    pSlaveCmd->pWriteBuffer = pWBuff;
    pSlaveCmd->pReadBuffer = pRBuff;
}

void ADS_InitSPI_FXLS8471()
{
    spiParams_8471.pReadPreprocessFN = ADS_FXLS8471Q_SPI_ReadPreprocess;
    spiParams_8471.pWritePreprocessFN = ADS_FXLS8471Q_SPI_WritePreprocess;
    spiParams_8471.pTargetSlavePinID = &FXLS8471_SPI_CS;
    spiParams_8471.spiCmdLen = FXLS8471Q_SPI_CMD_LEN;
    spiParams_8471.ssActiveValue = FXLS8471Q_SS_ACTIVE_VALUE;

    /* Initialize the Slave Select Pin. */
    pGPIODriver->pin_init(&FXLS8471_SPI_CS, GPIO_DIRECTION_OUT, NULL, NULL, NULL);
    if (spiParams_8471.ssActiveValue == SPI_SS_ACTIVE_LOW)
    {
        pGPIODriver->set_pin(&FXLS8471_SPI_CS);
    }
    else
    {
        pGPIODriver->clr_pin(&FXLS8471_SPI_CS);
    }
};

ADS_Status_t ADS_FXLS8471Query(uint8_t whoAmiAddr, uint8_t whoAmi)
{
    int32_t status;
    uint8_t reg;
    registerDeviceInfo_t deviceInfo = {
        .deviceInstance = SPI_S_DEVICE_INDEX, .functionParam = NULL, .idleFunction = NULL};

    /*!  Read and store the device's WHO_AM_I.*/
    status = Register_SPI_Read(SPIdrv, &deviceInfo, &spiParams_8471, whoAmiAddr, 1, &reg);
    if ((ARM_DRIVER_OK != status) || (whoAmi != reg))
    {
        return ADS_FAIL;
    }

    return ADS_OK;
}

/*******************************************************************************
* FXLS8962 SPI Specific Functions
*****************************************************************************/
void ADS_FXLS8962_SPI_ReadPreprocess(void *pCmdOut, uint32_t offset, uint32_t size)
{
    spiCmdParams_t *pSlaveCmd = pCmdOut;

    uint8_t *pWBuff = spiRead_CmdBuffer;
    uint8_t *pRBuff = spiRead_DataBuffer;

    /* Formatting for Read command of FXLS8962 SENSOR. */
    *(pWBuff) = offset | 0x80; /* offset is the internal register address of the sensor at which write is performed. */
    *(pWBuff + 1) = 0x00;

    /* Create the slave read command. */
    pSlaveCmd->size = size + FXLS8962_SPI_CMD_LEN;
    pSlaveCmd->pWriteBuffer = pWBuff;
    pSlaveCmd->pReadBuffer = pRBuff;
}

void ADS_FXLS8962_SPI_WritePreprocess(void *pCmdOut, uint32_t offset, uint32_t size, void *pWritebuffer)
{
    spiCmdParams_t *pSlaveCmd = pCmdOut;

    uint8_t *pWBuff = spiWrite_CmdDataBuffer;
    uint8_t *pRBuff = spiWrite_CmdDataBuffer + size + FXLS8962_SPI_CMD_LEN;

    /* Formatting for Write command of FXLS8962 SENSOR. */
    *(pWBuff) = offset & 0x7F; /* offset is the internal register address of the sensor at which write is performed. */
    *(pWBuff + 1) = 0x00;

    /* Copy the slave write command */
    memcpy(pWBuff + FXLS8962_SPI_CMD_LEN, pWritebuffer, size);

    /* Create the slave command. */
    pSlaveCmd->size = size + FXLS8962_SPI_CMD_LEN;
    pSlaveCmd->pWriteBuffer = pWBuff;
    pSlaveCmd->pReadBuffer = pRBuff;
}

void ADS_InitSPI_FXLS8962()
{ /*! Initialize the sensor handle. */
    spiParams_8962.pReadPreprocessFN = ADS_FXLS8962_SPI_ReadPreprocess;
    spiParams_8962.pWritePreprocessFN = ADS_FXLS8962_SPI_WritePreprocess;
    spiParams_8962.pTargetSlavePinID = &FXLS8962_CS;
    spiParams_8962.spiCmdLen = FXLS8962_SPI_CMD_LEN;
    spiParams_8962.ssActiveValue = FXLS8962_SS_ACTIVE_VALUE;

    /* Initialize the Slave Select Pin. */
    pGPIODriver->pin_init(&FXLS8962_CS, GPIO_DIRECTION_OUT, NULL, NULL, NULL);
    if (spiParams_8962.ssActiveValue == SPI_SS_ACTIVE_LOW)
    {
        pGPIODriver->set_pin(&FXLS8962_CS);
    }
    else
    {
        pGPIODriver->clr_pin(&FXLS8962_CS);
    }
};

ADS_Status_t ADS_FXLS8962Query(uint8_t whoAmiAddr, uint8_t whoAmi)
{
    int32_t status;
    uint8_t reg;
    registerDeviceInfo_t deviceInfo = {
        .deviceInstance = SPI_S_DEVICE_INDEX, .functionParam = NULL, .idleFunction = NULL};

    /*!  Read and store the device's WHO_AM_I.*/
    status = Register_SPI_Read(SPIdrv, &deviceInfo, &spiParams_8962, whoAmiAddr, 1, &reg);
    if ((ARM_DRIVER_OK != status) || (whoAmi != reg))
    {
        return ADS_FAIL;
    }

    return ADS_OK;
}

/*******************************************************************************
* DIFF-P SPI Specific Functions
*****************************************************************************/
void ADS_DIFF_P_SPI_ReadPreprocess(void *pCmdOut, uint32_t offset, uint32_t size)
{
    spiCmdParams_t *pSlaveCmd = pCmdOut;

    uint8_t *pWBuff = spiRead_CmdBuffer;
    uint8_t *pRBuff = spiRead_DataBuffer;

    /* Formatting for Read command of DIFF-P SENSOR. */
    *(pWBuff) = offset & 0x7F; /* offset is the internal register address of the sensor at which write is performed. */

    // Create the slave read command.
    pSlaveCmd->size = size + DIFF_P_SPI_CMD_LEN;
    pSlaveCmd->pWriteBuffer = pWBuff;
    pSlaveCmd->pReadBuffer = pRBuff;
}

void ADS_DIFF_P_SPI_WritePreprocess(void *pCmdOut, uint32_t offset, uint32_t size, void *pWritebuffer)
{
    spiCmdParams_t *pSlaveCmd = pCmdOut;

    uint8_t *pWBuff = spiWrite_CmdDataBuffer;
    uint8_t *pRBuff = spiWrite_CmdDataBuffer + size + DIFF_P_SPI_CMD_LEN;

    /* Formatting for Write command of DIFF-P SENSOR. */
    *(pWBuff) = offset | 0x80; /* offset is the internal register address of the sensor at which write is performed. */

    /* Copy the slave write command */
    memcpy(pWBuff + DIFF_P_SPI_CMD_LEN, pWritebuffer, size);

    /* Create the slave command. */
    pSlaveCmd->size = size + DIFF_P_SPI_CMD_LEN;
    pSlaveCmd->pWriteBuffer = pWBuff;
    pSlaveCmd->pReadBuffer = pRBuff;
}

void ADS_InitSPI_DIFF_P()
{
    spiParams_diff_p.pReadPreprocessFN = ADS_DIFF_P_SPI_ReadPreprocess;
    spiParams_diff_p.pWritePreprocessFN = ADS_DIFF_P_SPI_WritePreprocess;
    spiParams_diff_p.pTargetSlavePinID = &DIFF_P_SPI_CS;
    spiParams_diff_p.spiCmdLen = DIFF_P_SPI_CMD_LEN;
    spiParams_diff_p.ssActiveValue = DIFF_P_SS_ACTIVE_VALUE;

    /* Initialize the Slave Select Pin. */
    pGPIODriver->pin_init(&DIFF_P_SPI_CS, GPIO_DIRECTION_OUT, NULL, NULL, NULL);
    if (spiParams_diff_p.ssActiveValue == SPI_SS_ACTIVE_LOW)
    {
        pGPIODriver->set_pin(&DIFF_P_SPI_CS);
    }
    else
    {
        pGPIODriver->clr_pin(&DIFF_P_SPI_CS);
    }
};

ADS_Status_t ADS_DIFF_PQuery(uint8_t whoAmiAddr, uint8_t whoAmi)
{
    int32_t status;
    uint8_t reg;
    registerDeviceInfo_t deviceInfo = {
        .deviceInstance = SPI_S_DEVICE_INDEX, .functionParam = NULL, .idleFunction = NULL};

    /*!  Read and store the device's WHO_AM_I.*/
    status = Register_SPI_Read(SPIdrv, &deviceInfo, &spiParams_diff_p, whoAmiAddr, 1, &reg);
    if ((ARM_DRIVER_OK != status) || (whoAmi != reg))
    {
        return ADS_FAIL;
    }

    return ADS_OK;
}

/*******************************************************************************
* FXLC95000 Specific Functions
*****************************************************************************/
ADS_Status_t ADS_FXLC95000Query()
{
    int32_t status;
    uint16_t partNumber = 0;

    registerDeviceInfo_t deviceInfo = {
        .deviceInstance = I2C_S1_DEVICE_INDEX, .functionParam = NULL, .idleFunction = NULL};

    /* ADS is required to confirm only the presence of FXLC95000 and not the contents of its FLASH.
     * As such we will not send command to Boot FXLC95000 to Flash.
     * We send the Get Device Info ROM CI command and validate response. */
    Register_I2C_BlockWrite(I2CextDrv, &deviceInfo, FXLC95000_I2C_ADDR, 0, GetDeviceInfoCmd, sizeof(GetDeviceInfoCmd));
    BOARD_DELAY_ms(1);

    /* Read the Device Info Result.
     * A valid response COCO indicates command acceptance and by nature Sensor Identity. */
    status = Register_I2C_Read(I2CextDrv, &deviceInfo, FXLC95000_I2C_ADDR, FXLC95000_PART_NUMBER_OFFSET,
                               FXLC95000_PART_NUMBER_SIZE, (uint8_t *)&partNumber);
    partNumber = (partNumber >> 8) | (partNumber << 8);
    if (ARM_DRIVER_OK != status || partNumber != FXLC95000_PART_NUMBER)
    {
        return ADS_FAIL;
    }
    return ADS_OK;
};

/*******************************************************************************
* MMA9553 Specific Functions
*****************************************************************************/
ADS_Status_t ADS_MMA9553Query()
{
    int32_t status;
    uint8_t cmdRespHdr[MMA9553_HDR_SIZE] = {0};

    registerDeviceInfo_t deviceInfo = {
        .deviceInstance = I2C_S1_DEVICE_INDEX, .functionParam = NULL, .idleFunction = NULL};

    /* We send the Read Version Info command and validate response. */
    Register_I2C_BlockWrite(I2CextDrv, &deviceInfo, MMA9553_I2C_ADDR, 0, ReadVersionInfo_MMA9553,
                            sizeof(ReadVersionInfo_MMA9553));
    BOARD_DELAY_ms(1);

    /* Read the Device Info Result.
     * A valid response COCO and length fields indicate command acceptance and by nature Sensor Identity. */
    status = Register_I2C_Read(I2CextDrv, &deviceInfo, MMA9553_I2C_ADDR, 0, sizeof(cmdRespHdr), cmdRespHdr);
    if (ARM_DRIVER_OK != status || (cmdRespHdr[1] & 0x80) != 0x80 || cmdRespHdr[2] != ReadVersionInfo_MMA9553[3] ||
        cmdRespHdr[3] != ReadVersionInfo_MMA9553[3])
    {
        return ADS_FAIL;
    }
    return ADS_OK;
};

/*******************************************************************************
 * Functions
 *****************************************************************************/
int ADS_InitI2CBuses()
{
    int32_t status;

    /*! Initialize the Internal I2C driver. */
    status = I2CintDrv->Initialize(I2C_BB_SIGNAL_EVENT);
    if (ARM_DRIVER_OK != status)
    {
        return ARM_DRIVER_ERROR;
    }

    /*! Set the Internal I2C Power mode. */
    status = I2CintDrv->PowerControl(ARM_POWER_FULL);
    if (ARM_DRIVER_OK != status)
    {
        return ARM_DRIVER_ERROR;
    }

    /*! Set the Internal I2C bus speed. */
    status = I2CintDrv->Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_FAST);
    if (ARM_DRIVER_OK != status)
    {
        return ARM_DRIVER_ERROR;
    }

    /*! Initialize the External I2C driver. */
    status = I2CextDrv->Initialize(I2C_S1_SIGNAL_EVENT);
    if (ARM_DRIVER_OK != status)
    {
        return ARM_DRIVER_ERROR;
    }

    /*! Set the External I2C Power mode. */
    status = I2CextDrv->PowerControl(ARM_POWER_FULL);
    if (ARM_DRIVER_OK != status)
    {
        return ARM_DRIVER_ERROR;
    }

    /*! Set the External I2C bus speed. */
    status = I2CextDrv->Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_FAST);
    if (ARM_DRIVER_OK != status)
    {
        return ARM_DRIVER_ERROR;
    }

    return status;
}

int ADS_InitSPIBus()
{
    int32_t status;

    /*! Initialize the SPI driver. */
    status = SPIdrv->Initialize(SPI_S_SIGNAL_EVENT);
    if (ARM_DRIVER_OK != status)
    {
        return ARM_DRIVER_ERROR;
    }

    /*! Set the SPI Power mode. */
    status = SPIdrv->PowerControl(ARM_POWER_FULL);
    if (ARM_DRIVER_OK != status)
    {
        return ARM_DRIVER_ERROR;
    }

    /*! Set the SPI Slave speed. */
    status = SPIdrv->Control(ARM_SPI_MODE_MASTER | ARM_SPI_CPOL0_CPHA0, SPI_S_BAUDRATE);
    if (ARM_DRIVER_OK != status)
    {
        return ARM_DRIVER_ERROR;
    }

    return status;
}

int ADS_DeInitI2CBuses()
{
    int32_t status;

    /*! De-Initialize the Internal I2C driver. */
    status = I2CintDrv->Uninitialize();
    if (ARM_DRIVER_OK != status)
    {
        return ARM_DRIVER_ERROR;
    }

    /*! De-Initialize the External I2C driver. */
    status = I2CextDrv->Uninitialize();
    if (ARM_DRIVER_OK != status)
    {
        return ARM_DRIVER_ERROR;
    }

    return status;
}

int ADS_DeInitSPIBus()
{
    int32_t status;

    /*! De-Initialize the SPI0 driver. */
    status = SPIdrv->Uninitialize();
    if (ARM_DRIVER_OK != status)
    {
        return ARM_DRIVER_ERROR;
    }

    return status;
}

// Private function to detect Shield.
int ADS_DetectShield(char *pShieldString, size_t bufferLength)
{
    int32_t status;
    uint8_t reg;
    bool match;
    uint32_t boardFound = ADS_NO_SHIELD_DETECTED;
    registerDeviceInfo_t deviceInfo = {0};

    /* We init SPI bus to test for SPI Sensors. */
    ADS_InitSPIBus();

    // Execute the SPI queries based on the ADS_SensorQueryList.
    for (uint32_t i = 0; i < ADS_QUERY_NUM; i++)
    {
        if (ADS_SPI_DEV == ADS_SensorQueryList[i].channel)
        {
            gADS_QueryResults[i] = ADS_FAIL;
            if (FXLS8962 == ADS_SensorQueryList[i].slaveAddr)
            {
                ADS_InitSPI_FXLS8962();
                gADS_QueryResults[i] =
                    ADS_FXLS8962Query(ADS_SensorQueryList[i].whoAmIAddr, ADS_SensorQueryList[i].whoAmIValue);
                continue;
            }
            if (FXLS8471 == ADS_SensorQueryList[i].slaveAddr)
            {
                ADS_InitSPI_FXLS8471();
                gADS_QueryResults[i] =
                    ADS_FXLS8471Query(ADS_SensorQueryList[i].whoAmIAddr, ADS_SensorQueryList[i].whoAmIValue);
                continue;
            }
            if (DIFF_P == ADS_SensorQueryList[i].slaveAddr)
            {
                ADS_InitSPI_DIFF_P();
                gADS_QueryResults[i] =
                    ADS_DIFF_PQuery(ADS_SensorQueryList[i].whoAmIAddr, ADS_SensorQueryList[i].whoAmIValue);
                continue;
            }
        }
    }

    /* We now disable SPI bus and init I2C buses to test for I2C sensors. */
    ADS_DeInitSPIBus();
    ADS_InitI2CBuses();

    // Execute the Ext I2C queries based on the ADS_SensorQueryList.
    for (uint32_t i = 0; i < ADS_QUERY_NUM; i++)
    {
        if (ADS_I2C_EXT == ADS_SensorQueryList[i].channel)
        {
            gADS_QueryResults[i] = ADS_FAIL;
            deviceInfo.deviceInstance = I2C_S1_DEVICE_INDEX;
            if (FXLC95000 == ADS_SensorQueryList[i].slaveAddr)
            {
                gADS_QueryResults[i] = ADS_FXLC95000Query();
                continue;
            }
            if (MMA9553 == ADS_SensorQueryList[i].slaveAddr)
            {
                gADS_QueryResults[i] = ADS_MMA9553Query();
                continue;
            }
            if (MMA8491Q_I2C_ADDRESS == ADS_SensorQueryList[i].slaveAddr)
            { /* Set MMA8491Q EN Pin to enable I2C communication. */
                CLOCK_EnableClock(MMA8491_EN.clockName);
                pGPIODriver->pin_init(&MMA8491_EN, GPIO_DIRECTION_OUT, NULL, NULL, NULL);
                pGPIODriver->set_pin(&MMA8491_EN);
                BOARD_DELAY_ms(MMA8491Q_T_ON_TYPICAL); /* Wait for Bus to become active. */
                reg = MMA8491Q_STATUS_RESERVED_MASK;
            }
            status = Register_I2C_Read(I2CextDrv, &deviceInfo, ADS_SensorQueryList[i].slaveAddr,
                                       ADS_SensorQueryList[i].whoAmIAddr, 1, &reg);
            if ((ARM_DRIVER_OK != status) ||
                ((ADS_SensorQueryList[i].whoAmIValue & ADS_SensorQueryList[i].whoAmIMask) !=
                 (reg & ADS_SensorQueryList[i].whoAmIMask)))
            {
                gADS_QueryResults[i] = ADS_FAIL;
            }
            else
            {
                gADS_QueryResults[i] = ADS_OK;
            }
        }
    }

    // Execute the Int I2C queries based on the ADS_SensorQueryList.
    for (uint32_t i = 0; i < ADS_QUERY_NUM; i++)
    {
        if (ADS_I2C_INT == ADS_SensorQueryList[i].channel)
        {
            gADS_QueryResults[i] = ADS_FAIL;
            deviceInfo.deviceInstance = I2C_BB_DEVICE_INDEX;
            status = Register_I2C_Read(I2CintDrv, &deviceInfo, ADS_SensorQueryList[i].slaveAddr,
                                       ADS_SensorQueryList[i].whoAmIAddr, 1, &reg);
            if ((ARM_DRIVER_OK != status) || (ADS_SensorQueryList[i].whoAmIValue != reg))
            {
                gADS_QueryResults[i] = ADS_FAIL;
            }
            else
            {
                gADS_QueryResults[i] = ADS_OK;
            }
        }
    }

    /* I2C Sensor verified, disable I2C buses. */
    ADS_DeInitI2CBuses();

    // Analyze the responses and return the Sensor Shield or Reference name.
    for (uint32_t board = 0; board < ADS_NUM_BOARDS; board++)
    {
        match = true;
        for (uint32_t sensor = 0; sensor < ADS_QUERY_NUM; sensor++)
        {
            if (gADS_QueryMap[board][sensor] == ADS_NULL)
            {
                continue;
            }
            if (gADS_QueryMap[board][sensor] != gADS_QueryResults[sensor])
            {
                match = false;
                break;
            }
        }
        if (match)
        {
            boardFound = board;
            break;
        }
    }

    // If a board was found, then put the proper string into the response.
    if (boardFound != ADS_NO_SHIELD_DETECTED)
    {
        strncpy(pShieldString, ADS_ShieldList[boardFound], bufferLength);
        status = ARM_DRIVER_OK;
    }
    else
    {
        status = ARM_DRIVER_ERROR;
    }

    return status;
}

// Private function to detect the MCU.
int ADS_DetectFRDM(char *pBoardString, size_t bufferLength)
{
    int32_t status;

    //  Declare the SDID Query structure
    mcuSDID_t MCUInfo = {.mcuFamilyId = 0,
                         .mcuSubfamilyId = 0,
                         .mcuSeriesId = 0,
                         .mcuFamId = 0,
                         .mcuPinId = 0,
                         .board = ADS_NO_BOARD_DETECTED};

    if (pBoardString == NULL)
    {
        return ARM_DRIVER_ERROR_PARAMETER;
    }

//	Use the #define Macros in <device>_feature.h to conditionally compile the queries to SDID fields..
#ifdef SIM_SDID_FAMILYID
    MCUInfo.mcuFamilyId = ((SIM->SDID) & SIM_SDID_FAMILYID_MASK) >> SIM_SDID_FAMILYID_SHIFT;
#endif

#ifdef SIM_SDID_SUBFAMID
    MCUInfo.mcuSubfamilyId = ((SIM->SDID) & SIM_SDID_SUBFAMID_MASK) >> SIM_SDID_SUBFAMID_SHIFT;
#endif

#ifdef SIM_SDID_SERIESID
    MCUInfo.mcuSeriesId = ((SIM->SDID) & SIM_SDID_SERIESID_MASK) >> SIM_SDID_SERIESID_SHIFT;
#endif

#ifdef SIM_SDID_FAMID
    MCUInfo.mcuFamId = ((SIM->SDID) & SIM_SDID_FAMID_MASK) >> SIM_SDID_FAMID_SHIFT;
#endif

    MCUInfo.mcuPinId = ((SIM->SDID) & SIM_SDID_PINID_MASK) >> SIM_SDID_PINID_SHIFT;

    // Compare the values extracted to the static table and return detected board.
    for (uint32_t i = 0; i < (sizeof(ADS_ValidSDIDValues) / sizeof(mcuSDID_t)); i++)
    {
        if ((MCUInfo.mcuFamilyId == ADS_ValidSDIDValues[i].mcuFamilyId) &&
            (MCUInfo.mcuSubfamilyId == ADS_ValidSDIDValues[i].mcuSubfamilyId) &&
            (MCUInfo.mcuSeriesId == ADS_ValidSDIDValues[i].mcuSeriesId) &&
            (MCUInfo.mcuFamId == ADS_ValidSDIDValues[i].mcuFamId) &&
            (MCUInfo.mcuPinId == ADS_ValidSDIDValues[i].mcuPinId))
        {
            MCUInfo.board = ADS_ValidSDIDValues[i].board;
            break;
        }
    }

    status = ARM_DRIVER_OK;
    // Translate the result into the string.
    switch (MCUInfo.board)
    {
        case ADS_FRDM_KW41Z:
            strncpy(pBoardString, "FRDM-KW41Z", bufferLength);
            break;
        case ADS_FRDM_KE15Z:
            strncpy(pBoardString, "FRDM-KE15Z", bufferLength);
            break;
        case ADS_FRDM_KL25Z:
            strncpy(pBoardString, "FRDM-KL25Z", bufferLength);
            break;
        case ADS_FRDM_KL27Z:
            strncpy(pBoardString, "FRDM-KL27Z", bufferLength);
            break;
        case ADS_FRDM_K22F:
            strncpy(pBoardString, "FRDM-K22F", bufferLength);
            break;
        case ADS_FRDM_K64F:
            strncpy(pBoardString, "FRDM-K64F", bufferLength);
            break;
        case ADS_RD_KL25_AGMP01:
            strncpy(pBoardString, "RD-KL25-AGMP01", bufferLength);
            break;
        default:
            status = ARM_DRIVER_ERROR;
            break;
    }

    return status;
}

// Private function to compare flash contents.
ADS_FlashStatus_t ADS_FlashCompare(char *pResultString)
{
    ADSFlashRecord_t *pRecord = (ADSFlashRecord_t *)ADS_NVM_ADDR;
    uint32_t status;

    // Check that the ADS_COOKIE is as expected.
    if (pRecord->cookie != ADS_COOKIE_VALUE)
    {
        return ADS_NO_FLASH_RECORD; // Flash record is not valid.
    }
    else
    { // Compare the result string with the ADS stored results in Flash.
        status = strncmp((char *)pResultString, (char *)pRecord->ADSString, pRecord->length);
        if (status != 0)
        {
            return ADS_FLASH_RECORD_CHANGE;
        }
        else
        {
            return ADS_FLASH_RECORD_NO_CHANGE;
        }
    }
}

// Private function to update flash contents.
ADS_Status_t ADS_FlashUpdate(char *pResultString)
{
    status_t result;
    uint32_t pflashSectorSize = 0;
    ADS_Status_t retVal = ADS_FAIL;
    ADSFlashRecord_t flashRecord = {0};
    flash_config_t s_flashDriver;

    // Create the ADS Flash Record.
    flashRecord.cookie = ADS_COOKIE_VALUE;
    flashRecord.length = strlen((char const *)pResultString);
    memcpy(flashRecord.ADSString, pResultString, flashRecord.length);

    // Clean up Flash driver Structure.
    memset(&s_flashDriver, 0, sizeof(flash_config_t));

    // Setup flash driver structure for device and initialize variables.
    result = FLASH_Init(&s_flashDriver);
    if (kStatus_FLASH_Success == result)
    {
        // Get the Flash sector size.
        FLASH_GetProperty(&s_flashDriver, FLASH_SECTOR_SIZE_PROPERTY, &pflashSectorSize);

        // Erase the target sector.
        result = FLASH_Erase(&s_flashDriver, ADS_NVM_ADDR, pflashSectorSize, kFLASH_ApiEraseKey);
        if (kStatus_FLASH_Success == result)
        {
            // Write the ADS Record to the Flash.
            result = FLASH_Program(&s_flashDriver, ADS_NVM_ADDR, (uint8_t *)&flashRecord,
                                   sizeof(flashRecord)); // Note: Flash write needs to be 32-bit word aligned in length
            if (kStatus_FLASH_Success == result)
            {
                retVal = ADS_OK;
            }
        }
    }

    return retVal;
}

// API to register Application Name and trigger Board Shield detection.
void BOARD_RunADS(const char *appName, char *boardString, char *shieldString, size_t bufferLength)
{
    int32_t position, status = ADS_OK;
    char finalString[ADS_FLASH_STRING_LENGTH] = {0};

    status = ADS_DetectFRDM(boardString, bufferLength);
    if (ARM_DRIVER_ERROR == status)
    {
        strncpy(boardString, "NotDetected", bufferLength);
        status = ADS_FAIL;
    }

    status = ADS_DetectShield(shieldString, bufferLength);
    if (ARM_DRIVER_ERROR == status)
    {
        strncpy(shieldString, "NotDetected", bufferLength);
        status = ADS_FAIL;
    }

    // Build the string with App Name and Shield Name to write to flash.
    strncpy(finalString, appName, ADS_FLASH_STRING_LENGTH);
    position = strlen(appName);

    finalString[position++] = ':';

    strncpy(&finalString[position], shieldString, ADS_FLASH_STRING_LENGTH - position);
    position += strlen(shieldString);

    /* Fill the remaining string with 0. */
    memset(&finalString[position], 0, ADS_FLASH_STRING_LENGTH - position);

    status = ADS_FlashCompare(finalString);
    if (ADS_FLASH_RECORD_NO_CHANGE != status)
    {
        ADS_FlashUpdate(finalString);
        strcpy(finalString, shieldString);
        snprintf(shieldString, bufferLength, "Changed:%s", finalString);
    }
}
