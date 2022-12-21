/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file register_io_spi.c
 * @brief The register_io_spi.c file contains definitions for low-level interface functions
 * for reading and writing sensor registers using CMSIS APIs.
 */

/* Standard C Includes */
#include <string.h>

/* ISSDK Includes */
#include "issdk_hal.h"
#include "gpio_driver.h"
#include "register_io_spi.h"

/*******************************************************************************
 * Types
 ******************************************************************************/
#define SPI_COUNT (sizeof(spiBases) / sizeof(void *))

/*******************************************************************************
 * Variables
 ******************************************************************************/
GENERIC_DRIVER_GPIO *pDspiGpioDriver = &Driver_GPIO_KSDK;
SPI_Type *const spiBases[] = SPI_BASE_PTRS;
volatile bool b_SPI_CompletionFlag[SPI_COUNT] = {false};
volatile uint32_t g_SPI_ErrorEvent[SPI_COUNT] = {ARM_SPI_EVENT_TRANSFER_COMPLETE};

/*******************************************************************************
 * Code
 ******************************************************************************/
#if defined(SPI0)
/* The SPI0 Signal Event Handler function. */
void SPI0_SignalEvent_t(uint32_t event)
{
    if (event != ARM_SPI_EVENT_TRANSFER_COMPLETE)
    {
        g_SPI_ErrorEvent[0] = event;
    }
    b_SPI_CompletionFlag[0] = true;
}
#endif

#if defined(SPI1)
/* The SPI1 Signal Event Handler function. */
void SPI1_SignalEvent_t(uint32_t event)
{
    if (event != ARM_SPI_EVENT_TRANSFER_COMPLETE)
    {
        g_SPI_ErrorEvent[1] = event;
    }
    b_SPI_CompletionFlag[1] = true;
}
#endif

#if defined(SPI2)
/* The SPI2 Signal Event Handler function. */
void SPI2_SignalEvent_t(uint32_t event)
{
    if (event != ARM_SPI_EVENT_TRANSFER_COMPLETE)
    {
        g_SPI_ErrorEvent[2] = event;
    }
    b_SPI_CompletionFlag[2] = true;
}
#endif

#if defined(SPI3)
/* The SPI3 Signal Event Handler function. */
void SPI3_SignalEvent_t(uint32_t event)
{
    if (event != ARM_SPI_EVENT_TRANSFER_COMPLETE)
    {
        g_SPI_ErrorEvent[3] = event;
    }
    b_SPI_CompletionFlag[3] = true;
}
#endif

#if defined(SPI4)
/* The SPI4 Signal Event Handler function. */
void SPI4_SignalEvent_t(uint32_t event)
{
    if (event != ARM_SPI_EVENT_TRANSFER_COMPLETE)
    {
        g_SPI_ErrorEvent[4] = event;
    }
    b_SPI_CompletionFlag[4] = true;
}
#endif

#if defined(SPI5)
/* The SPI5 Signal Event Handler function. */
void SPI5_SignalEvent_t(uint32_t event)
{
    if (event != ARM_SPI_EVENT_TRANSFER_COMPLETE)
    {
        g_SPI_ErrorEvent[5] = event;
    }
    b_SPI_CompletionFlag[5] = true;
}
#endif

#if defined(SPI6)
/* The SPI6 Signal Event Handler function. */
void SPI6_SignalEvent_t(uint32_t event)
{
    if (event != ARM_SPI_EVENT_TRANSFER_COMPLETE)
    {
        g_SPI_ErrorEvent[6] = event;
    }
    b_SPI_CompletionFlag[6] = true;
}
#endif

#ifndef CPU_LPC55S06JBD64
#if defined(SPI7)
/* The SPI7 Signal Event Handler function. */
void SPI7_SignalEvent_t(uint32_t event)
{
    if (event != ARM_SPI_EVENT_TRANSFER_COMPLETE)
    {
        g_SPI_ErrorEvent[7] = event;
    }
    b_SPI_CompletionFlag[7] = true;
}
#endif
#if defined(SPI8)
/* The SPI7 Signal Event Handler function. */
void SPI8_SignalEvent_t(uint32_t event)
{
    if (event != ARM_SPI_EVENT_TRANSFER_COMPLETE)
    {
        g_SPI_ErrorEvent[8] = event;
    }
    b_SPI_CompletionFlag[8] = true;
}
#endif
#endif

/* Control Slave Select based on inactive/active and active low/high. */
void register_spi_control(spiControlParams_t *ssControl)
{
    if (ssControl->cmdCode == ssControl->activeValue)
    {
        pDspiGpioDriver->set_pin(ssControl->pTargetSlavePinID);
    }
    else
    {
        pDspiGpioDriver->clr_pin(ssControl->pTargetSlavePinID);
    }
}

/*! The interface function to block write sensor registers. */
int32_t Register_SPI_BlockWrite(ARM_DRIVER_SPI *pCommDrv,
                                registerDeviceInfo_t *devInfo,
                                void *pWriteParams,
                                uint8_t offset,
                                const uint8_t *pBuffer,
                                uint8_t bytesToWrite)
{
    int32_t status;
    spiCmdParams_t slaveWriteCmd;
    spiSlaveSpecificParams_t *pSlaveParams = pWriteParams;

    spiControlParams_t ss_en_cmd = {
        .cmdCode = ARM_SPI_SS_ACTIVE,
        .activeValue = pSlaveParams->ssActiveValue,
        .pTargetSlavePinID = pSlaveParams->pTargetSlavePinID,
    };
    spiControlParams_t ss_dis_cmd = {
        .cmdCode = ARM_SPI_SS_INACTIVE,
        .activeValue = pSlaveParams->ssActiveValue,
        .pTargetSlavePinID = pSlaveParams->pTargetSlavePinID,
    };

    pSlaveParams->pWritePreprocessFN(&slaveWriteCmd, offset, bytesToWrite, (void *)pBuffer);
    b_SPI_CompletionFlag[devInfo->deviceInstance] = false;
    g_SPI_ErrorEvent[devInfo->deviceInstance] = ARM_SPI_EVENT_TRANSFER_COMPLETE;
    /*! Write and the value.*/
    register_spi_control(&ss_en_cmd);
    status = pCommDrv->Transfer(slaveWriteCmd.pWriteBuffer, slaveWriteCmd.pReadBuffer, slaveWriteCmd.size);
    if (ARM_DRIVER_OK == status)
    {
        /* Wait for completion */
        while (!b_SPI_CompletionFlag[devInfo->deviceInstance])
        {
            if (devInfo->idleFunction)
            {
                devInfo->idleFunction(devInfo->functionParam);
            }
            else
            {
                __NOP();
            }
        }
        if (g_SPI_ErrorEvent[devInfo->deviceInstance] != ARM_SPI_EVENT_TRANSFER_COMPLETE)
        {
            status = ARM_DRIVER_ERROR;
            pCommDrv->Control(ARM_SPI_ABORT_TRANSFER, 0);
        }
    }
    register_spi_control(&ss_dis_cmd);

    return status;
}

/*! The interface function to write a sensor register. */
int32_t Register_SPI_Write(ARM_DRIVER_SPI *pCommDrv,
                           registerDeviceInfo_t *devInfo,
                           void *pWriteParams,
                           uint8_t offset,
                           uint8_t value,
                           uint8_t mask)
{
    int32_t status;
    uint8_t regValue;
    spiCmdParams_t slaveReadCmd, slaveWriteCmd;
    spiSlaveSpecificParams_t *pSlaveParams = pWriteParams;

    spiControlParams_t ss_en_cmd = {
        .cmdCode = ARM_SPI_SS_ACTIVE,
        .activeValue = pSlaveParams->ssActiveValue,
        .pTargetSlavePinID = pSlaveParams->pTargetSlavePinID,
    };
    spiControlParams_t ss_dis_cmd = {
        .cmdCode = ARM_SPI_SS_INACTIVE,
        .activeValue = pSlaveParams->ssActiveValue,
        .pTargetSlavePinID = pSlaveParams->pTargetSlavePinID,
    };

    /*! Set the register based on the values in the register value pair configuration.*/
    if (mask)
    {
        /* Get the formatted SPI Read Command. */
        pSlaveParams->pReadPreprocessFN(&slaveReadCmd, offset, 1);
        b_SPI_CompletionFlag[devInfo->deviceInstance] = false;
        g_SPI_ErrorEvent[devInfo->deviceInstance] = ARM_SPI_EVENT_TRANSFER_COMPLETE;
        /*! Read the register value.*/
        register_spi_control(&ss_en_cmd);
        status = pCommDrv->Transfer(slaveReadCmd.pWriteBuffer, slaveReadCmd.pReadBuffer, slaveReadCmd.size);
        if (ARM_DRIVER_OK == status)
        {
            /* Wait for completion */
            while (!b_SPI_CompletionFlag[devInfo->deviceInstance])
            {
                if (devInfo->idleFunction)
                {
                    devInfo->idleFunction(devInfo->functionParam);
                }
                else
                {
                    __NOP();
                }
            }
            if (g_SPI_ErrorEvent[devInfo->deviceInstance] != ARM_SPI_EVENT_TRANSFER_COMPLETE)
            {
                status = ARM_DRIVER_ERROR;
                pCommDrv->Control(ARM_SPI_ABORT_TRANSFER, 0);
            }
        }
        register_spi_control(&ss_dis_cmd);

        /*! 'OR' in the requested values to the current contents of the register */
        regValue = *(slaveReadCmd.pReadBuffer + pSlaveParams->spiCmdLen);
        regValue = (regValue & ~mask) | value;
    }
    else
    {
        /*! Overwrite the register with specified value.*/
        regValue = value;
    }

    pSlaveParams->pWritePreprocessFN(&slaveWriteCmd, offset, 1, &regValue);
    b_SPI_CompletionFlag[devInfo->deviceInstance] = false;
    g_SPI_ErrorEvent[devInfo->deviceInstance] = ARM_SPI_EVENT_TRANSFER_COMPLETE;
    /*! Write and the value.*/
    register_spi_control(&ss_en_cmd);
    status = pCommDrv->Transfer(slaveWriteCmd.pWriteBuffer, slaveWriteCmd.pReadBuffer, slaveWriteCmd.size);
    if (ARM_DRIVER_OK == status)
    {
        /* Wait for completion */
        while (!b_SPI_CompletionFlag[devInfo->deviceInstance])
        {
            if (devInfo->idleFunction)
            {
                devInfo->idleFunction(devInfo->functionParam);
            }
            else
            {
                __NOP();
            }
        }
        if (g_SPI_ErrorEvent[devInfo->deviceInstance] != ARM_SPI_EVENT_TRANSFER_COMPLETE)
        {
            status = ARM_DRIVER_ERROR;
            pCommDrv->Control(ARM_SPI_ABORT_TRANSFER, 0);
        }
    }
    register_spi_control(&ss_dis_cmd);

    return status;
}

/*! The interface function to read a sensor register. */
int32_t Register_SPI_Read(ARM_DRIVER_SPI *pCommDrv,
                          registerDeviceInfo_t *devInfo,
                          void *pReadParams,
                          uint8_t offset,
                          uint8_t length,
                          uint8_t *pOutBuffer)
{
    int32_t status;
    spiCmdParams_t slaveReadCmd;
    spiSlaveSpecificParams_t *pSlaveParams = pReadParams;

    spiControlParams_t ss_en_cmd = {
        .cmdCode = ARM_SPI_SS_ACTIVE,
        .activeValue = pSlaveParams->ssActiveValue,
        .pTargetSlavePinID = pSlaveParams->pTargetSlavePinID,
    };
    spiControlParams_t ss_dis_cmd = {
        .cmdCode = ARM_SPI_SS_INACTIVE,
        .activeValue = pSlaveParams->ssActiveValue,
        .pTargetSlavePinID = pSlaveParams->pTargetSlavePinID,
    };

    pSlaveParams->pReadPreprocessFN(&slaveReadCmd, offset, length);
    b_SPI_CompletionFlag[devInfo->deviceInstance] = false;
    g_SPI_ErrorEvent[devInfo->deviceInstance] = ARM_SPI_EVENT_TRANSFER_COMPLETE;
    /*! Read the value.*/
    register_spi_control(&ss_en_cmd);
    status = pCommDrv->Transfer(slaveReadCmd.pWriteBuffer, slaveReadCmd.pReadBuffer, slaveReadCmd.size);
    if (ARM_DRIVER_OK == status)
    {
        /* Wait for completion */
        while (!b_SPI_CompletionFlag[devInfo->deviceInstance])
        {
            if (devInfo->idleFunction)
            {
                devInfo->idleFunction(devInfo->functionParam);
            }
            else
            {
                __NOP();
            }
        }
        if (g_SPI_ErrorEvent[devInfo->deviceInstance] != ARM_SPI_EVENT_TRANSFER_COMPLETE)
        {
            status = ARM_DRIVER_ERROR;
            pCommDrv->Control(ARM_SPI_ABORT_TRANSFER, 0);
        }
    }
    register_spi_control(&ss_dis_cmd);

    memcpy(pOutBuffer, slaveReadCmd.pReadBuffer + pSlaveParams->spiCmdLen, length);

    return status;
}
