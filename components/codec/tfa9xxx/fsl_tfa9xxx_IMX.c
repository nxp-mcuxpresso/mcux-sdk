/*
 * Copyright  2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * fsl_tfa9xxx_IMX.c
 *
 *   IMX platform specific integration of tfa2_core code.
 */

#include "fsl_tfa9xxx.h"
#include "stdarg.h"
#include "fsl_codec_i2c.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Message buffer used to communicate with TFA DSP. */
static uint8_t s_TFA_DSP_Message_Buffer[TFADSP_COMMAND_BUFFER_MAX_SIZE];

/* i2c_client used by the driver */
static struct i2c_client s_myclient[4] = {{0x34U, NULL, 0U}, {0x35U, NULL, 1U}, {0x36U, NULL, 2U}, {0x37U, NULL, 3U}};

typedef status_t (*tfa9xxx_codec_i2c_callback_t)(
    void *handle, uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint8_t *buff, uint8_t buffSize);
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void SysTick_DelayTicks(uint32_t n);

/*******************************************************************************
 * Code
 ******************************************************************************/

void tfa2_i2c_trace(const char *str, unsigned addr, const char *buf, size_t buf_len)
{
    const char *p = buf;

    TFA9XXX_Printf("%s [%d]: 0x%02x ", str, buf_len, addr);

    if (buf && buf_len)
    {
        do
        {
            /* Print buffer item. For all items, aside last, terminate it with space */
            TFA9XXX_Printf("0x%02x%c", (unsigned char)*p, ((buf_len - 1) ? ' ' : '\n'));
            p++;
            buf_len--;
        } while (buf_len);
    }
    else
    {
        TFA9XXX_Printf("\n");
    }
}

static status_t TFA9XXX_I2C_Transfer(tfa9xxx_codec_i2c_callback_t codec_i2c_callback,
                                     void *handle,
                                     uint8_t deviceAddress,
                                     uint32_t subAddress,
                                     uint8_t subaddressSize,
                                     uint8_t *buff,
                                     int buffSize)
{
    status_t retval = kStatus_Success;
    assert(buffSize >= 0);

    uint8_t *transferAddress = buff;
    uint32_t remainSize      = buffSize;
    uint8_t transferSize;
    while (remainSize > 0)
    {
        transferSize = (remainSize > BOARD_I2C_TRANSFER_SIZE_MAX) ? BOARD_I2C_TRANSFER_SIZE_MAX : remainSize;
        retval = codec_i2c_callback(handle, deviceAddress, subAddress, subaddressSize, transferAddress, transferSize);
        if (retval != kStatus_Success)
        {
            return retval;
        }
        transferAddress += transferSize;
        remainSize = buffSize - (transferAddress - buff);
    }

    return retval;
}

/* platform i2c */
/*!
 * @brief Low level I2C write read function for TFA driver, should be implemented using platform specific I2C APIs
 *
 * @param client I2C client. For IMX codec implementation, client->hal will point to the tfa9xxx_handle_t->i2cHandle.
 * @param wrlen Length of the data to write
 * @param wrdata Buffer of write data
 * @param rdlen Length of the data to read
 * @param rddata Buffer of read data
 * @return int Returns kStatus_Success if success, or negative value of error code in enum _lpi2c_status
 */
int tfa2_i2c_write_read_raw(struct i2c_client *client, int wrlen, uint8_t *wrdata, int rdlen, uint8_t *rddata)
{
    uint16_t retval = kStatus_Success;

    if (rdlen == 0 || rddata == NULL)
    {
        retval = TFA9XXX_I2C_Transfer(CODEC_I2C_Send, client->hal, client->addr, *wrdata, 1U, wrdata + 1U, wrlen - 1U);
    }
    else
    {
        retval = TFA9XXX_I2C_Transfer(CODEC_I2C_Send, client->hal, client->addr, 0, 0, wrdata, wrlen);
        if (retval != kStatus_Success)
        {
            return -retval;
        }
        retval = TFA9XXX_I2C_Transfer(CODEC_I2C_Receive, client->hal, client->addr, 0, 0, rddata, rdlen);
        if (retval != kStatus_Success)
        {
            return -retval;
        }
    }

    return retval;
}

/*!
 * @brief Low level I2C write function, wrapper for the tfa2_i2c_write_read_raw
 *
 * @param client I2C client
 * @param len Length of the data to write
 * @param data Pointer to the write data buffer
 * @return int Returns kStatus_Success if success, or negative value of error code in enum _lpi2c_status
 */
int tfa2_i2c_write_raw(struct i2c_client *client, int len, const uint8_t *data)
{
    return tfa2_i2c_write_read_raw(client, len, (uint8_t *)data, 0, NULL);
}

/*****************************************************************************/
/*!
 * @brief Get the pointer of the I2C client structure for given slave address.
 *
 * Depending on how ADS1 and ADS2 pins on TFA are connected physically, TFA supports 4 options of slave address: 0x34,
 * 0x35, 0x36 or 0x37. The provided slave address will also be double checked with the container file.
 *
 * @param cnt Pointer of the container array.
 * @param slaveAddress Device slave address.
 * @return void* Returns the pointer of the I2C client structure, NULL if slaveAddress is not valid.
 */
void *TFA9XXX_GetI2CClient(nxpTfaContainer_t *cnt, uint8_t slaveAddress)
{
    if (slaveAddress < 0x34U || slaveAddress > 0x37U)
        return NULL;

    return &s_myclient[slaveAddress - 0x34U];
}

/*!
 * @brief Wait function for the TFA
 *
 * User needs to implement below in the upper layer:
 *
 * //global volatile counter used for sleep/wait
 * volatile uint32_t g_systickCounter;
 *
 * void SysTick_Handler(void)
 * {
 * 		if (g_systickCounter != 0U)
 * 		{
 * 			g_systickCounter--;
 * 		}
 * }
 *
 * void SysTick_DelayTicks(uint32_t n)
 * {
 * 		g_systickCounter = n;
 * 		while(g_systickCounter != 0U)
 * 		{
 * 		}
 * }
 *
 * void main(void)
 * {
 * 		...
 * 		//System Tick Configuration, generate 1ms interrupt
 * 		SysTick_Config(SystemCoreClock / 1000U);
 * 		...
 * 		//then initialize TFA
 * }
 *
 * @param val Time to wait in terms of milliseconds
 */
void TFA9XXX_WaitMS(uint32_t val)
{
    SysTick_DelayTicks(val);
}

/*!
 * @brief Convert the return check value from TFA driver to predefined error code.
 *
 * If passing in fsl_common.h/enum _generic_status, it will be returned directly without any conversion.
 *
 * @param rc Return check value from TFA driver.
 * @return status_t Returns error code from enum _tfa_error or enum _lpi2c_status.
 */
status_t TFA9XXX_ConvertErrorCode(int32_t rc)
{
    switch (rc)
    {
        case kStatus_Success:
        case kStatus_Fail:
        case kStatus_ReadOnly:
        case kStatus_OutOfRange:
        case kStatus_InvalidArgument:
        case kStatus_Timeout:
            return rc; /* if input is already the predefined error code, return rc directly */
        case -EINVAL:
            TFA9XXX_Printf("%s: error code: %s, description: %s\n", __FUNCTION__, "EINVAL", "Invalid argument");
            return kStatus_InvalidArgument;
        case -EPERM:
            TFA9XXX_Printf("%s: error code: %s, description: %s\n", __FUNCTION__, "EPERM", "Operation not permitted");
            return kStatus_Fail;
        case -ENODEV:
            TFA9XXX_Printf("%s: error code: %s, description: %s\n", __FUNCTION__, "ENODEV", "No such device");
            return kStatus_InvalidArgument;
        case -ENOMEM:
            TFA9XXX_Printf("%s: error code: %s, description: %s\n", __FUNCTION__, "ENOMEM", "Out of memory");
            return kStatus_Fail;
        case -ENXIO:
            TFA9XXX_Printf("%s: error code: %s, description: %s\n", __FUNCTION__, "ENXIO", "No such device or address");
            return kStatus_InvalidArgument;
        case -ETIME:
            TFA9XXX_Printf("%s: error code: %s, description: %s\n", __FUNCTION__, "ETIME", "Timer expired");
            return kStatus_Timeout;
        case -EIO:
            TFA9XXX_Printf("%s: error code: %s, description: %s\n", __FUNCTION__, "EIO", "I/O error");
            return kStatus_Fail;
        case -ERANGE:
            TFA9XXX_Printf("%s: error code: %s, description: %s\n", __FUNCTION__, "ERANGE",
                           "Math result not representable");
            return kStatus_OutOfRange;
        case -ETIMEDOUT:
            TFA9XXX_Printf("%s: error code: %s, description: %s\n", __FUNCTION__, "ETIMEDOUT", "Connection timed out");
            return kStatus_Timeout;
        case -ENOENT:
            TFA9XXX_Printf("%s: error code: %s, description: %s\n", __FUNCTION__, "ENOENT",
                           "No such file or directory");
            return kStatus_InvalidArgument;
        case -EFAULT:
            TFA9XXX_Printf("%s: error code: %s, description: %s\n", __FUNCTION__, "EFAULT", "Bad address");
            return kStatus_InvalidArgument;
        case -E2BIG:
            TFA9XXX_Printf("%s: error code: %s, description: %s\n", __FUNCTION__, "E2BIG", "Argument list too long");
            return kStatus_InvalidArgument;
        default:
            TFA9XXX_Printf("Error code unknown: %d\n", rc);
            return kStatus_Fail;
    }
}

uint8_t *TFA9XXX_GetDSPMessageBuffer(void)
{
    memset(s_TFA_DSP_Message_Buffer, 0, TFADSP_COMMAND_BUFFER_MAX_SIZE);
    return s_TFA_DSP_Message_Buffer;
}

void TFA9XXX_NOP(const char *format, ...)
{
}
