/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file orientaion_application_baremetal_agm01.c
 * @brief The orientaion_application_baremetal_agm01.c file implements the ISSDK
 *        baremetal orientation application for FRDM-STBC-AGM01 using sensor
 *        fusion core functional interfaces and host i/o interface.
 */
/**
 * Orient Packet Structure: 44 Bytes
 *  ------------------------------------------------------------------------------------------------------------------------------------------------------------
 * | TimeStamp | 9 Axis Sensor data | Quaternion data | Euler angles data | FitError% data | Co-ordinates data | BoardInfo data | BuildInfo data | SysTick data |                                                                       |
 *  ------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

/* KSDK Headers */
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_port.h"
#include "fsl_i2c.h"
#include "fsl_pit.h"

/* CMSIS Headers */
#include "Driver_USART.h"
#include "fsl_i2c_cmsis.h"
#include "fsl_uart_cmsis.h"

/* ISSDK Headers */
#include "fxas21002.h"
#include "fxos8700.h"
#include "register_io_i2c.h"
#include "host_io_uart.h"
#include "gpio_driver.h"
#include "auto_detection_service.h"
#include "systick_utils.h"

/* Sensor Fusion Headers */
#include "sensor_fusion.h"
#include "control.h"
#include "status.h"
#include "drivers.h"
#include "driver_pit.h"

/*******************************************************************************
 * Macro Definitions
 ******************************************************************************/
#define TIMESTAMP_DATA_SIZE      (4)                             /* Orientation Packet: TimeStamp field size */
#define NINEAXISSENSOR_DATA_SIZE (18)                            /* Orientation Packet: 9 Axis Sensor Data, Accel, Mag, Gyro field size */ 
#define QUATERNION_SIZE          (8)                             /* Orientation Packet: Quaternion field size */
#define EULERANGLE_DATA_SIZE     (6)                             /* Orientation Packet: Roll,Pitch,Compass Euler angles packet field size */
#define FITERROR_DATA_SIZE       (2)                             /* Orientation Packet: FitError% field size */
#define COORDINATES_SIZE         (1)                             /* Orientation Packet: coordinates field size */
#define BOARDINFO_SIZE           (1)                             /* Orientation Packet: BoardInfo field size */
#define BUILDNAME_SIZE           (2)                             /* Orientation Packet: BuildInfo field size */
#define SYSTICKINFO_SIZE         (2)                             /* Orientation Packet: SysTick field size */
/*! @brief Unique Name for this application which should match the target GUI pkg name. */
#define APPLICATION_NAME "9 Axis Orientation Sensor Demo"                /* Orientation Application Name */
/*! @brief Version to distinguish between instances the same application based on target Shield and updates. */
#define APPLICATION_VERSION "2.5"

/* Orientation Streaming Packet Payload Size */
#define STREAMING_PAYLOAD_LEN \
    (TIMESTAMP_DATA_SIZE + NINEAXISSENSOR_DATA_SIZE + QUATERNION_SIZE + EULERANGLE_DATA_SIZE + FITERROR_DATA_SIZE + COORDINATES_SIZE + BOARDINFO_SIZE + BUILDNAME_SIZE + SYSTICKINFO_SIZE)

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
SensorFusionGlobals     sfg;                                     /* Sensor Fusion Global Structure Instance */
ControlSubsystem        gOrientationControlSubsystem;            /* Control Subsystem Structure Instance for orientation streaming */
StatusSubsystem         statusSubsystem;                         /* Sensor Fusion algorithm execution status indicators (LED) */
char boardString[ADS_MAX_STRING_LENGTH] = {0}, shieldString[ADS_MAX_STRING_LENGTH] = {0},
     embAppName[ADS_MAX_STRING_LENGTH] = {0};
volatile bool           gStreamingEnabled;                       /* Variable indicating streaming mode. */
uint8_t                 gPrimaryStreamID;                        /* The auto assigned Stream ID to be used to stream complete data. */

uint8_t                 orientOutputBuffer[STREAMING_HEADER_LEN + STREAMING_PAYLOAD_LEN];


struct PhysicalSensor 	sensors[2];                              /* This implementation uses two physical sensors */
//EventGroupHandle_t event_group = NULL;
registerDeviceInfo_t i2cBusInfo = {
    .deviceInstance     = I2C_S_DEVICE_INDEX,
    .functionParam      = NULL,
    .idleFunction       = NULL
};

/*******************************************************************************
 * Local Function Prototype Definitions
 ******************************************************************************/
/* Utility Function to add field bytes to orientation buffer */
static void updateOrientBuf(uint8_t *pDest,
                            uint16_t *pIndex,
                            uint8_t *pSrc,
                            uint16_t iBytesToCopy);
/* Initialize the orientation application control subsystem */
static int8_t initOrientaionAppControlPort (ControlSubsystem *pComm);
/* Function to create orient packets for serial streaming over Host I/O */
static void encodeOrientPacketStream (SensorFusionGlobals * sfg, uint8_t *sUARTOutputBuffer);
/* Utility function for reading common algorithm parameters */
void readAlgoParams( SV_ptr data,
                 Quaternion *fq,
                 int16_t *iPhi,
                 int16_t *iThe,
                 int16_t *iRho,
                 int16_t iOmega[],
                 uint16_t *isystick);

/*******************************************************************************
 * Code
 ******************************************************************************/
/* Handler for Device Info and Streaming Control Commands. */
bool process_host_command(
    uint8_t tag, uint8_t *hostCommand, uint8_t *hostResponse, size_t *hostMsgSize, size_t respBufferSize)
{
    bool success = false;

    /* If it is Host requesting Device Info, send Board Name and Shield Name. */
    if (tag == HOST_PRO_INT_DEV_TAG)
    { /* Byte 1     : Payload - Length of APPLICATION_NAME (b)
       * Bytes=b    : Payload Application Name
       * Byte b+1   : Payload - Length of BOARD_NAME (s)
       * Bytes=s    : Payload Board Name
       * Byte b+s+2 : Payload - Length of SHIELD_NAME (v)
       * Bytes=v    : Payload Shield Name */

        size_t appNameLen = strlen(embAppName);
        size_t boardNameLen = strlen(boardString);
        size_t shieldNameLen = strlen(shieldString);

        if (respBufferSize >= boardNameLen + shieldNameLen + appNameLen + 3)
        { /* We have sufficient buffer. */
            *hostMsgSize = 0;
        }
        else
        {
            return false;
        }

        hostResponse[*hostMsgSize] = appNameLen;
        *hostMsgSize += 1;

        memcpy(hostResponse + *hostMsgSize, embAppName, appNameLen);
        *hostMsgSize += appNameLen;

        hostResponse[*hostMsgSize] = boardNameLen;
        *hostMsgSize += 1;

        memcpy(hostResponse + *hostMsgSize, boardString, boardNameLen);
        *hostMsgSize += boardNameLen;

        hostResponse[*hostMsgSize] = shieldNameLen;
        *hostMsgSize += 1;

        memcpy(hostResponse + *hostMsgSize, shieldString, shieldNameLen);
        *hostMsgSize += shieldNameLen;

        return true;
    }

    /* If it is Host sending Streaming Commands, take necessary actions. */
    if ((tag == (HOST_PRO_INT_CMD_TAG | HOST_PRO_CMD_W_CFG_TAG)) &&
        (*hostMsgSize == HOST_MSG_CMD_ACT_OFFSET - HOST_MSG_LEN_LSB_OFFSET))
    {                           /* Byte 1 : Payload - Operation Code (Start/Stop Operation Code)
                                 * Byte 2 : Payload - Stream ID (Target Stream for carrying out operation) */
        switch (hostCommand[0]) /* Execute desired operation (Start/Stop) on the requested Stream. */
        {
            case HOST_CMD_START:
                if (hostCommand[1] == gPrimaryStreamID && gStreamingEnabled == false)
                {
                    gStreamingEnabled = true;
                    success = true;
                }
                break;
            case HOST_CMD_STOP:
                if (hostCommand[1] == gPrimaryStreamID && gStreamingEnabled == true)
                {
                    gStreamingEnabled = false;
                    success = true;
                    LED_GREEN_ON();
                }
                break;
            default:
                break;
        }
        *hostMsgSize = 0; /* Zero payload in response. */
    }

    return success;
}

/*!
 * @brief updateOrientBuf utility function
 */
void updateOrientBuf(uint8_t *pDest, uint16_t *pIndex, uint8_t *pSrc, uint16_t iBytesToCopy)
{
    uint16_t counter;

    for (counter = 0; counter < iBytesToCopy; counter++)
    {
        pDest[(*pIndex)++] = pSrc[counter];
    }

    return;
}

/*!
 * @brief appendZerosOrientBuf utility function
 */
void appendZerosOrientBuf(uint8_t *pDest, uint16_t *pIndex, uint16_t numZeros) {
    int16_t scratch16 = 0;
    uint16_t i;
    for (i=0; i<numZeros; i++) {
        sBufAppendItem(pDest, pIndex, (uint8_t *) &scratch16, 2);
    }
}

/*!
 * @brief Utility function for reading common algorithm parameters
 */
void readAlgoParams(
    SV_ptr data, Quaternion *fq, int16_t *iPhi, int16_t *iThe, int16_t *iRho, int16_t iOmega[], uint16_t *isystick)
{
    *fq = data->fq;
    iOmega[CHX] = (int16_t)(data->fOmega[CHX] * 20.0F);
    iOmega[CHY] = (int16_t)(data->fOmega[CHY] * 20.0F);
    iOmega[CHZ] = (int16_t)(data->fOmega[CHZ] * 20.0F);
    *iPhi = (int16_t)(10.0F * data->fPhi);
    *iThe = (int16_t)(10.0F * data->fThe);
    *iRho = (int16_t)(10.0F * data->fRho);
    *isystick = (uint16_t)(data->systick / 20);
}

/*!
 * @brief Initialize the orientation application control subsystem
 */
static int8_t initOrientaionAppControlPort(ControlSubsystem *pComm /* pointer to the control subystem structure */
                                           )
{
    if (pComm)
    {
        pComm->DefaultQuaternionPacketType = Q3; /* default to simplest algorithm */
        pComm->QuaternionPacketType = Q3;        /* default to simplest algorithm */
        pComm->AngularVelocityPacketOn = true;   /* transmit angular velocity packet */
        pComm->DebugPacketOn = true;             /* transmit debug packet */
        pComm->RPCPacketOn = true;               /* transmit roll, pitch, compass packet */
        pComm->AltPacketOn = true;               /* Altitude packet */
        pComm->AccelCalPacketOn = 0;
        pComm->write = NULL;
        pComm->stream = encodeOrientPacketStream; /* Function to create orient packets for serial stream */
        memset(orientOutputBuffer, 0, sizeof(orientOutputBuffer));
        return (0);
    }
    else
    {
        return (1);
    }
}

/*!
 * @brief Function to create orient packets for serial streaming over Host I/O
 */
void encodeOrientPacketStream(SensorFusionGlobals *sfg, uint8_t *sUARTOutputBuffer)
{
    Quaternion      fq;                                          /* quaternion to be transmitted */
    static uint32_t iTimeStamp = 0;                              /* 1MHz time stamp */
    uint16_t        iIndex;                                      /* output buffer counter */
    int32_t         scratch32;                                   /* scratch int32_t */
    int16_t         scratch16;                                   /* scratch int16_t */
    int16_t         iPhi, iThe, iRho;                            /* integer angles to be transmitted */
    int16_t         iOmega[3];                                   /* scaled angular velocity vector */
    uint16_t        isystick;                                    /* algorithm systick time */
    uint8_t         tmpuint8_t;                                  /* scratch uint8_t */
    uint8_t         flags;                                       /* byte of flags */
    size_t          sUARTOutputBufLen = STREAMING_PAYLOAD_LEN;

    /* Update the 1 microsecond timestamp counter */
    iTimeStamp += 1000000 / FUSION_HZ;

    /* Start the index to store orientation packet payload into the transmit buffer */
    iIndex = STREAMING_HEADER_LEN;

    /* Add Time Stamp to Orientation Buffer */
    /*! Add 1 microsecond timestamp counter (4 bytes) value to Orientation Buffer */
    updateOrientBuf(sUARTOutputBuffer, &iIndex, (uint8_t *)&iTimeStamp, 4);

    /* Add Accel X, Y Z values to Orientation Buffer */
    /*! Add Accel X, Y Z (6 bytes) value to Orientation Buffer. Send non-zero data only if the accelerometer sensor is enabled */
    if (sfg->iFlags & F_USING_ACCEL)
    {
        /* Accelerometer data is used for the selected quaternion so transmit but clip at 4g */
        scratch32 = (sfg->Accel.iGc[CHX] * 8192) / sfg->Accel.iCountsPerg;
        if (scratch32 > 32767) scratch32 = 32767;
        if (scratch32 < -32768) scratch32 = -32768;
        scratch16 = (int16_t) (scratch32);
        updateOrientBuf(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);

        scratch32 = (sfg->Accel.iGc[CHY] * 8192) / sfg->Accel.iCountsPerg;
        if (scratch32 > 32767) scratch32 = 32767;
        if (scratch32 < -32768) scratch32 = -32768;
        scratch16 = (int16_t) (scratch32);
        updateOrientBuf(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);

        scratch32 = (sfg->Accel.iGc[CHZ] * 8192) / sfg->Accel.iCountsPerg;
        if (scratch32 > 32767) scratch32 = 32767;
        if (scratch32 < -32768) scratch32 = -32768;
        scratch16 = (int16_t) (scratch32);
        updateOrientBuf(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
     }
     else
     {
       /* Accelerometer structure is not defined so transmit zero */
        appendZerosOrientBuf(sUARTOutputBuffer, &iIndex, 3);
     }

    /* Add MAG X, Y Z values to Orientation Buffer */
    /*! Add MAG X, Y Z (6 bytes) value to Orientation Buffer. Send non-zero data only if the magnetometer sensor is enabled */
    if (sfg->iFlags & F_USING_MAG)
    {
        /* Magnetometer data is used for the selected quaternion so transmit */
        scratch16 = (int16_t) (sfg->Mag.iBc[CHX] * 10) / (sfg->Mag.iCountsPeruT);
        updateOrientBuf(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
        scratch16 = (int16_t) ((sfg->Mag.iBc[CHY] * 10) / sfg->Mag.iCountsPeruT);
        updateOrientBuf(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
        scratch16 = (int16_t) ((sfg->Mag.iBc[CHZ] * 10) / sfg->Mag.iCountsPeruT);
        updateOrientBuf(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
    }
    else
    {
        /* Magnetometer structure is not defined so transmit zero */
        appendZerosOrientBuf(sUARTOutputBuffer, &iIndex, 3);
    }

    /* Add Gyro X, Y Z values to Orientation Buffer */
    /*! Add Gyro X, Y Z (6 bytes) value to Orientation Buffer. Send non-zero data only if the gyro sensor is enabled */
    if (sfg->iFlags & F_USING_GYRO)
    {
      /* Gyro data is used for the selected quaternion so transmit */
        scratch16 = (int16_t) ((sfg->Gyro.iYs[CHX] * 20) / sfg->Gyro.iCountsPerDegPerSec);
        updateOrientBuf(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
        scratch16 = (int16_t) ((sfg->Gyro.iYs[CHY] * 20) / sfg->Gyro.iCountsPerDegPerSec);
        updateOrientBuf(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
        scratch16 = (int16_t) ((sfg->Gyro.iYs[CHZ] * 20) / sfg->Gyro.iCountsPerDegPerSec);
        updateOrientBuf(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
    }
    else
    {
        /* Gyro structure is not defined so transmit zero */
        appendZerosOrientBuf(sUARTOutputBuffer, &iIndex, 3);
    }

    /* Initialize default quaternion, flags byte, angular velocity and orientation */
    fq.q0 = 1.0F;
    fq.q1 = fq.q2 = fq.q3 = 0.0F;
    flags = 0x00;
    iOmega[CHX] = iOmega[CHY] = iOmega[CHZ] = 0;
    iPhi = iThe = iRho = 0;
    isystick = 0;

    /* set the quaternion, flags, angular velocity and Euler angles */
    if (sfg->iFlags & F_9DOF_GBY_KALMAN)
    {
        flags |= 0x08;
        readAlgoParams((SV_ptr)&sfg->SV_9DOF_GBY_KALMAN, &fq, &iPhi, &iThe, &iRho, iOmega, &isystick);
    }

    /* Add Quaternion data to Orientation Buffer */
    /*! Scale the quaternion and add to the Orientation Buffer  */
    scratch16 = (int16_t) (fq.q0 * 30000.0F);
    updateOrientBuf(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
    scratch16 = (int16_t) (fq.q1 * 30000.0F);
    updateOrientBuf(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
    scratch16 = (int16_t) (fq.q2 * 30000.0F);
    updateOrientBuf(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
    scratch16 = (int16_t) (fq.q3 * 30000.0F);
    updateOrientBuf(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);

    /* Add Euler angles data to Orientation Buffer */
    /*! Add the Roll, Pitch, Compass Euler angles packet to the Orientation Buffer */
    updateOrientBuf(sUARTOutputBuffer, &iIndex, (uint8_t *) &iPhi, 2);
    updateOrientBuf(sUARTOutputBuffer, &iIndex, (uint8_t *) &iThe, 2);
    updateOrientBuf(sUARTOutputBuffer, &iIndex, (uint8_t *) &iRho, 2);

    if (sfg->iFlags & F_USING_MAG)
    {   
         /* Add Fit error values to Orientation Buffer */
        if (sfg->MagCal.fFitErrorpc > 327.67F)
            scratch16 = 32767;
        else
            scratch16 = (int16_t) (sfg->MagCal.fFitErrorpc * 100.0F);
        updateOrientBuf(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);
    }

    /* Set the coordinate system bits in flags from default NED (00) */
#if THISCOORDSYSTEM == ANDROID
    /* Set the Android flag bits */
    flags |= 0x10;
#elif THISCOORDSYSTEM == WIN8
    /* set the Win8 flag bits */
    flags |= 0x20;
#endif // THISCOORDSYSTEM

    /*! Add the co-ordinate info byte to the Orientation Buffer */
    updateOrientBuf(sUARTOutputBuffer, &iIndex, &flags, 1);

    /*! Add the shield (bits 7-5) and Kinetis (bits 4-0) byte to the Orientation Buffer */
    tmpuint8_t = ((THIS_SHIELD & 0x07) << 5) | (THIS_BOARD & 0x1F);
    updateOrientBuf(sUARTOutputBuffer, &iIndex, &tmpuint8_t, 1);

    /*! Add Software version number to the Orientation Buffer */
    scratch16 = THISBUILD;
    updateOrientBuf(sUARTOutputBuffer, &iIndex, (uint8_t *) &scratch16, 2);

    /*! Add systick count to the Orientation Buffer */
    updateOrientBuf(sUARTOutputBuffer, &iIndex, (uint8_t *) &isystick, 2);

    /*! Send packet to host only if streaming has been enabled by Host. */
//    if (gStreamingEnabled)
    {
        /*! Add Host I/O ISO streaming header */
        Host_IO_Add_ISO_Header(gPrimaryStreamID, sUARTOutputBuffer, sUARTOutputBufLen);

        /*! Send Orientation streaming packet to Host using Host I/O */
        Host_IO_Send(sUARTOutputBuffer, STREAMING_HEADER_LEN + sUARTOutputBufLen, HOST_FORMAT_HDLC);
    }
    return;
}

/*!
 * @brief Main function
 */
int main(void)
{
    int32_t status;
    uint8_t secondaryStreamID1;             /* The auto assigned Stream ID not to be used to stream data. */
    ARM_DRIVER_I2C *I2Cdrv = &I2C_S_DRIVER; /* defined in the <shield>.h file */
    ARM_DRIVER_USART *pUartDriver = &HOST_S_DRIVER;
    uint16_t i = 0; /* general counter variable */

    /*! Initialize the MCU hardware. */
    BOARD_BootClockRUN();
    BOARD_SystickEnable();

    /* Create the Short Application Name String for ADS. */
    sprintf(embAppName, "%s:%s", APPLICATION_NAME, APPLICATION_VERSION);

    /* Run ADS. */
    BOARD_RunADS(embAppName, boardString, shieldString, ADS_MAX_STRING_LENGTH);

    /* Create the Full Application Name String for Device Info Response. */
    sprintf(embAppName, "%s:%s:%s", SHIELD_NAME, APPLICATION_NAME, APPLICATION_VERSION);

    /*! Initialize and set the KSDK driver for the I2C port */
    I2Cdrv->Initialize(I2C_S_SIGNAL_EVENT);
    I2Cdrv->PowerControl(ARM_POWER_FULL);
    I2Cdrv->Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_FAST);

    /*! Initialize the UART driver. */
    status = pUartDriver->Initialize(HOST_S_SIGNAL_EVENT);
    if (ARM_DRIVER_OK != status)
    {
        return -1;
    }
    /*! Set UART Power mode. */
    status = pUartDriver->PowerControl(ARM_POWER_FULL);
    if (ARM_DRIVER_OK != status)
    {
        return -1;
    }
    /*! Set UART Baud Rate. */
    status = pUartDriver->Control(ARM_USART_MODE_ASYNCHRONOUS, BOARD_DEBUG_UART_BAUDRATE);
    if (ARM_DRIVER_OK != status)
    {
        return -1;
    }

    /*! Initialize control sub-system for orientation packet streaming */
    initOrientaionAppControlPort(&gOrientationControlSubsystem);

    /*! Initialize sensor fusion status sub-system */
    initializeStatusSubsystem(&statusSubsystem);
    /*! Initialize sensor fusion global metadata */
    initSensorFusionGlobals(&sfg, &statusSubsystem, &gOrientationControlSubsystem);

    /*! Install the sensors to be used by sensor fusion */
    sfg.installSensor(&sfg, &sensors[0], FXOS8700_I2C_ADDR, 1, (void *)I2Cdrv, &i2cBusInfo, FXOS8700_Init,
                      FXOS8700_Read);
    sfg.installSensor(&sfg, &sensors[1], FXAS21002_I2C_ADDR, 1, (void *)I2Cdrv, &i2cBusInfo, FXAS21002_Init,
                      FXAS21002_Read);

    /*! Initialize streaming and assign Stream IDs. */
    gStreamingEnabled = false;
    /* Registering the FXOS8700 slave address with Host I/O for Register Read/Write. */
    gPrimaryStreamID =
        Host_IO_Init(pUartDriver, (void *)sensors[0].bus_driver, &sensors[0].deviceInfo, NULL, FXOS8700_I2C_ADDR);
    /* Confirm if a valid Stream ID has been allocated for this stream. */
    if (0 == gPrimaryStreamID)
    {
        return -1;
    }

    /* Registering the FXAS21002 slave address with Host I/O for Register Read/Write. */
    secondaryStreamID1 =
        Host_IO_Init(pUartDriver, (void *)sensors[1].bus_driver, &sensors[1].deviceInfo, NULL, FXAS21002_I2C_ADDR);
    /* Confirm if a valid Stream ID has been allocated for this stream. */
    if (0 == secondaryStreamID1)
    {
        return -1;
    }

    /*! Initialize sensor fusion engine */
    sfg.initializeFusionEngine(&sfg);

    /*! pitIsrFlag will be set true at FUSION_HZ periodic intervals */
    pit_init(1000000 / FUSION_HZ);

    sfg.setStatus(&sfg, NORMAL); // If we got this far, let's set status state to NORMAL
    LED_GREEN_ON();
    
    while (true)
    {
        /*! Check whether occur interupt */
        if (true == pitIsrFlag)
        {
            /*! Check for incoming commands form Host. */
            Host_IO_Receive(process_host_command, HOST_FORMAT_HDLC);
            
            if (false == gStreamingEnabled)
            {
                SMC_SetPowerModeWait(SMC); /* Power save, wait if nothing to do. */
                continue;
            }

            /*! Reads sensors, applies HAL and does averaging (if applicable) */
            sfg.readSensors(&sfg, 1);

            /*! Condition sensor data, magCal is run as part of this */
            sfg.conditionSensorReadings(&sfg);

            /*! Run fusion algorithms */
            sfg.runFusion(&sfg);

            /*! Apply debug perturbation */
            sfg.applyPerturbation(&sfg);

            /* Required to check incoming host command and send response before host times out */
            Host_IO_Receive(process_host_command, HOST_FORMAT_HDLC);

            sfg.loopcounter++;
            i = i + 1;
            if (i >= 4)
            {                           /* Some status codes include a "blink" feature.  This loop */
                i = 0;                  /* should cycle at least four times for that to operate correctly. */
                sfg.updateStatus(&sfg); /* This is where pending status updates are made visible */
            }

            /*! assume NORMAL status for next pass through the loop */
            sfg.queueStatus(&sfg, NORMAL);
            
            /* Required to check incoming host command and send response before host times out */
            Host_IO_Receive(process_host_command, HOST_FORMAT_HDLC);

            /*! Encode Orietantion Stream Packet and send packet to host*/
            sfg.pControlSubsystem->stream(&sfg, sUARTOutputBuffer);

            pitIsrFlag = false; // Reset the flag for the next cycle
        }
    }
}
/// \endcode
