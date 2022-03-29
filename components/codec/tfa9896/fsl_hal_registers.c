/*
 * Copyright 2019 NXP
 * All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "fsl_tfa9896.h"
#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define TFA_SWAP_UINT16_BYTE_SEQUENCE(x) (__REV16(x))

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
status_t TFA9896_ReadRegister(tfa9896_handle_t *handle, uint8_t subaddress, unsigned short *value)
{
    assert(handle->config != NULL);
    assert(handle->config->slaveAddress != 0U);

    uint16_t readValue = 0U;
#if defined(DEMO_VERBOSE)
    int i;
#endif

    if (CODEC_I2C_Receive(handle->i2cHandle, handle->config->slaveAddress, subaddress, 1U, (uint8_t *)&readValue, 2U) !=
        kStatus_HAL_I2cSuccess)
    {
        return kStatus_TFA9896_I2C_Fatal;
    }

    *value = TFA_SWAP_UINT16_BYTE_SEQUENCE(readValue);
#if defined(DEMO_VERBOSE)
    TFA9896_Printf("R(0x%02x):", subaddress);
    for (i = 0; i < transfer.dataSize; i++)
    {
        TFA9896_Printf("[0x%02x]", (unsigned char)((unsigned char *)transfer.data + i));
    }
    TFA9896_Printf("\r\n");
#endif

    return kStatus_TFA9896_Ok;
}

int tfa_read_reg(tfa9896_handle_t *handle, const uint16_t bf)
{
    status_t err = kStatus_TFA9896_Ok;
    uint16_t regvalue;

    /* bitfield enum - 8..15 : address */
    uint8_t address = (bf >> 8) & 0xff;

    err = TFA9896_ReadRegister(handle, address, &regvalue);
    if (err)
    {
        return -err;
    }

    return regvalue;
}

status_t TFA9896_WriteRegister(tfa9896_handle_t *handle, uint8_t subaddress, uint16_t value)
{
    assert(handle->config != NULL);
    assert(handle->config->slaveAddress != 0U);

#if defined(DEMO_VERBOSE)
    int i;
#endif

    uint16_t writeValue = TFA_SWAP_UINT16_BYTE_SEQUENCE(value);

    if (kStatus_HAL_I2cSuccess !=
        CODEC_I2C_Send(handle->i2cHandle, handle->config->slaveAddress, subaddress, 1U, (uint8_t *)&writeValue, 2U))
    {
        return kStatus_TFA9896_I2C_Fatal;
    }

#if defined(DEMO_VERBOSE)
    TFA9896_Printf("W(0x%02x):", subaddress);
    for (i = 0; i < transfer.dataSize; i++)
    {
        TFA9896_Printf("[0x%02x]", (unsigned char)((unsigned char *)transfer.data + i));
    }
    TFA9896_Printf("\r\n");
#endif

    return kStatus_TFA9896_Ok;
}

uint16_t TFA9896_GetBits(tfa9896_handle_t *handle, const uint16_t bf)
{
    uint16_t regvalue, msk;
    status_t err = kStatus_TFA9896_Ok;
    uint16_t value;
    uint8_t len     = bf & 0x0f;
    uint8_t pos     = (bf >> 4) & 0x0f;
    uint8_t address = (bf >> 8) & 0xff;
    err             = TFA9896_ReadRegister(handle, address, &regvalue);
    if (err != kStatus_TFA9896_Ok)
    {
        return 0U;
    }
    msk = ((1 << (len + 1)) - 1) << pos;
    regvalue &= msk;
    value = regvalue >> pos;

    return value;
}

uint16_t TFA9896_isFactory(tfa9896_handle_t *handle)
{
    return (TFA9896_GetBits(handle, TFA1_BF_MTPEX) == 1);
}

status_t TFA9896_SetBits(tfa9896_handle_t *handle, const uint16_t bf, const uint16_t value)
{
    status_t err = kStatus_TFA9896_Ok;
    uint16_t regvalue, msk, oldvalue;
    uint8_t len     = (bf & 0x0f) + 1;
    uint8_t pos     = (bf >> 4) & 0x0f;
    uint8_t address = (bf >> 8) & 0xff;
    err             = TFA9896_ReadRegister(handle, address, &regvalue);
    oldvalue        = regvalue;
    msk             = ((1 << len) - 1) << pos;
    regvalue &= ~msk;
    regvalue |= value << pos;

    if (oldvalue != regvalue)
    {
        err = TFA9896_WriteRegister(handle, (bf >> 8) & 0xff, regvalue);
    }

    return err;
}

status_t TFA9896_ReadData(tfa9896_handle_t *handle, unsigned char subaddress, int num_bytes, unsigned char data[])
{
    status_t err = kStatus_TFA9896_Ok;
#if defined(DEMO_VERBOSE)
    int i;
#endif

    err =
        CODEC_I2C_Receive(handle->i2cHandle, handle->config->slaveAddress, subaddress, 1U, (uint8_t *)data, num_bytes);

#if defined(DEMO_VERBOSE)
    TFA9896_Printf("R(0x%02x):", subaddress);
    for (i = 0; i < transfer.dataSize; i++)
        TFA9896_Printf("[0x%02x]", (unsigned char)((unsigned char *)transfer.data + i));
    TFA9896_Printf("\r\n");
#endif

    return err;
}

status_t TFA9896_WriteData(tfa9896_handle_t *handle,
                           unsigned char subaddress,
                           int num_bytes,
                           const unsigned char data[])
{
    status_t err = kStatus_TFA9896_Ok;
#if defined(DEMO_VERBOSE)
    int i;
#endif

    err = CODEC_I2C_Send(handle->i2cHandle, handle->config->slaveAddress, subaddress, 1U, (uint8_t *)data, num_bytes);

#if defined(DEMO_VERBOSE)
    TFA9896_Printf("W(0x%02x):", subaddress);
    for (i = 0; i < transfer.dataSize; i++)
    {
        TFA9896_Printf("[0x%02x]", (unsigned char)((unsigned char *)transfer.data + i));
    }
    TFA9896_Printf("\r\n");
#endif

    return err;
}

/* read the return code for the RPC call */
status_t checkRpcStatus(tfa9896_handle_t *handle, int *pRpcStatus)
{
    status_t error         = kStatus_TFA9896_Ok;
    unsigned short cf_ctrl = 0x0002; /* the value to sent to the CF_CONTROLS register: cf_req=00000000, cf_int=0,
                                        cf_aif=0, cf_dmem=XMEM=01, cf_rst_dsp=0 */
    unsigned short cf_mad = 0x0000;  /* memory address to be accessed (0 : Status, 1 : ID, 2 : parameters) */
    unsigned char mem[3];            /* will be filled with the status read from DSP memory */
    if (pRpcStatus == 0)
        return kStatus_TFA9896_Bad_Parameter;
#ifdef OPTIMIZED_RPC
    {
        /* minimize the number of I2C transactions by making use of the autoincrement in I2C */
        unsigned char buffer[4];
        /* first the data for CF_CONTROLS */
        buffer[0] = (unsigned char)((cf_ctrl >> 8) & 0xFF);
        buffer[1] = (unsigned char)(cf_ctrl & 0xFF);
        /* write the contents of CF_MAD which is the subaddress following CF_CONTROLS */
        buffer[2] = (unsigned char)((cf_mad >> 8) & 0xFF);
        buffer[3] = (unsigned char)(cf_mad & 0xFF);
        error     = TFA9896_WriteData(handle, 0x70, sizeof(buffer), buffer);
    }
#else
    /* 1) write DMEM=XMEM to the DSP XMEM */
    if (error == kStatus_TFA9896_Ok)
    {
        error = TFA9896_WriteRegister(handle, 0x70, cf_ctrl);
    }
    if (error == kStatus_TFA9896_Ok)
    {
        /* write the address in XMEM where to read */
        TFA9896_WriteRegister(handle, 0x71, cf_mad);
    }
#endif
    if (error == kStatus_TFA9896_Ok)
    {
        /* read 1 word (24 bit) from XMEM */
        error = TFA9896_ReadData(handle, 0x72, 3 /*sizeof(mem) */, mem);
    }
    if (error == kStatus_TFA9896_Ok)
    {
        *pRpcStatus = (mem[0] << 16) | (mem[1] << 8) | mem[2];
    }
    return error;
}

/* check that num_byte matches the memory type selected */
status_t check_size(tfa9896_DMEM_t which_mem, int num_bytes)
{
    status_t error  = kStatus_TFA9896_Ok;
    int modulo_size = 1;
    switch (which_mem)
    {
        case DMEM_PMEM:
            /* 32 bit PMEM */
            modulo_size = 4;
            break;
        case DMEM_XMEM:
        case DMEM_YMEM:
        case DMEM_IOMEM:
            /* 24 bit MEM */
            modulo_size = 3;
            break;
        default:
            error = kStatus_TFA9896_Bad_Parameter;
    }
    if (error == kStatus_TFA9896_Ok)
    {
        if ((num_bytes % modulo_size) != 0)
        {
            error = kStatus_TFA9896_Bad_Parameter;
        }
    }
    return error;
}

status_t writeParameter(tfa9896_handle_t *handle,
                        unsigned char module_id,
                        unsigned char param_id,
                        int num_bytes,
                        const unsigned char data[])
{
    status_t error;
    unsigned short cf_ctrl = 0x0002; /* the value to be sent to the CF_CONTROLS register: cf_req=00000000, cf_int=0,
                                        cf_aif=0, cf_dmem=XMEM=01, cf_rst_dsp=0 */
    unsigned short cf_mad = 0x0001;  /* memory address to be accessed (0 : Status, 1 : ID, 2 : parameters) */
    error                 = check_size(DMEM_XMEM, num_bytes);
    if (error == kStatus_TFA9896_Ok)
    {
        if ((num_bytes <= 0) || (num_bytes > MAX_PARAM_SIZE))
        {
            return kStatus_TFA9896_Bad_Parameter;
        }
    }
#ifdef OPTIMIZED_RPC
    {
        /* minimize the number of I2C transactions by making use of the autoincrement in I2C */
        unsigned char buffer[7];
        /* first the data for CF_CONTROLS */
        buffer[0] = (unsigned char)((cf_ctrl >> 8) & 0xFF);
        buffer[1] = (unsigned char)(cf_ctrl & 0xFF);
        /* write the contents of CF_MAD which is the subaddress following CF_CONTROLS */
        buffer[2] = (unsigned char)((cf_mad >> 8) & 0xFF);
        buffer[3] = (unsigned char)(cf_mad & 0xFF);
        /* write the module and RPC id into CF_MEM, which follows CF_MAD */
        buffer[4] = 0;
        buffer[5] = module_id + 128;
        buffer[6] = param_id;
        /* TFA9896_Printf("calling TFA9896_WriteData\n");*/
        error = TFA9896_WriteData(handle, 0x70, sizeof(buffer), buffer);
    }
#else
    if (error == kStatus_TFA9896_Ok)
    {
        error = TFA9896_WriteRegister(handle, 0x70, cf_ctrl);
    }
    if (error == kStatus_TFA9896_Ok)
    {
        TFA9896_WriteRegister(handle, 0x71, cf_mad);
    }
    if (error == kStatus_TFA9896_Ok)
    {
        unsigned char id[3];
        id[0] = 0;
        id[1] = module_id + 128;
        id[2] = param_id;
        error = TFA9896_WriteData(handle, 0x72, 3, id);
    }
#endif /* OPTIMIZED_RPC */
    if (error == kStatus_TFA9896_Ok)
    {
        int offset          = 0;
        int chunk_size      = ROUND_DOWN(NXP_I2C_MAX_SIZE, 3 /* XMEM word size */);
        int remaining_bytes = num_bytes;
        /* due to autoincrement in cf_ctrl, next write will happen at the next address */
        while ((error == kStatus_TFA9896_Ok) && (remaining_bytes > 0))
        {
            if (remaining_bytes < chunk_size)
            {
                chunk_size = remaining_bytes;
            }
            /* else chunk_size remains at initialize value above*/
            error = TFA9896_WriteData(handle, 0x72, chunk_size, data + offset);
            if (error != kStatus_TFA9896_Ok)
            {
                break;
            }
            remaining_bytes -= chunk_size;
            offset += chunk_size;
        }
    }
    return error;
}

status_t executeParam(tfa9896_handle_t *handle)
{
    status_t error;
    unsigned short cf_ctrl = 0x0002; /* the value to be sent to the CF_CONTROLS register: cf_req=00000000, cf_int=0,
                                        cf_aif=0, cf_dmem=XMEM=01, cf_rst_dsp=0 */
    cf_ctrl |= (1 << 8) | (1 << 4);  /* set the cf_req1 and cf_int bit */
    error = TFA9896_WriteRegister(handle, 0x70, (uint16_t)cf_ctrl);
    return error;
}

status_t waitResult(tfa9896_handle_t *handle)
{
    status_t error;
    unsigned short cf_status; /* the contents of the CF_STATUS register */
    int tries = 0;
    do
    {
        error = TFA9896_ReadRegister(handle, 0x73, &cf_status);
        tries++;
    } while ((error == kStatus_TFA9896_Ok) && ((cf_status & 0x0100) == 0) &&
             (tries < TFA9896_API_WAITRESULT_NTRIES)); /* don't wait forever, DSP is pretty quick to respond (< 1ms) */
    if (tries >= TFA9896_API_WAITRESULT_NTRIES)
    {
        /* something wrong with communication with DSP */
        error = kStatus_TFA9896_DSP_not_running;
    }
    return error;
}

status_t TFA9896_DspSetParam(tfa9896_handle_t *handle,
                             unsigned char module_id,
                             unsigned char param_id,
                             int num_bytes,
                             const unsigned char data[])
{
    status_t error;
    int rpcStatus = STATUS_OK;
    /* 1) write the id and data to the DSP XMEM */
    error = writeParameter(handle, module_id, param_id, num_bytes, data);
    /* 2) wake up the DSP and let it process the data */
    if (error == kStatus_TFA9896_Ok)
    {
        error = executeParam(handle);
    }
    /* check the result when addressed an IC uniquely */
    if (handle->config->slaveAddress != 0x1C)
    {
        /* 3) wait for the ack */
        if (error == kStatus_TFA9896_Ok)
        {
            error = waitResult(handle);
        }
        /* 4) check the RPC return value */
        if (error == kStatus_TFA9896_Ok)
        {
            error = checkRpcStatus(handle, &rpcStatus);
            TFA9896_Printf("rpcStatus:%d\n", rpcStatus);
        }
        if (error == kStatus_TFA9896_Ok)
        {
            if (rpcStatus != STATUS_OK)
            {
                /* DSP RPC call returned an error */
                error = (status_t)(rpcStatus + kStatus_TFA9896_RpcBase);
            }
        }
    }
    return error;
}

void tfa9896_convert_data2bytes(int num_data, const int data[], unsigned char bytes[])
{
    int i; /* index for data */
    int k; /* index for bytes */
    int d;
    /* note: cannot just take the lowest 3 bytes from the 32 bit
     * integer, because also need to take care of clipping any
     * value > 2&23 */
    for (i = 0, k = 0; i < num_data; ++i, k += 3)
    {
        if (data[i] >= 0)
        {
            d = MIN(data[i], (1 << 23) - 1);
        }
        else
        {
            /* 2's complement */
            d = (1 << 24) - MIN(-data[i], 1 << 23);
        }
        bytes[k]     = (d >> 16) & 0xFF; /* MSB */
        bytes[k + 1] = (d >> 8) & 0xFF;
        bytes[k + 2] = (d)&0xFF; /* LSB */
    }
}

void tfa9896_convert_bytes2data(int num_bytes, const unsigned char bytes[], int data[])
{
    int i; /* index for data */
    int k; /* index for bytes */
    int d;
    int num_data = num_bytes / 3;

    for (i = 0, k = 0; i < num_data; ++i, k += 3)
    {
        d = (bytes[k] << 16) | (bytes[k + 1] << 8) | (bytes[k + 2]);
        if (bytes[k] & 0x80) /* sign bit was set */
        {
            d = -((1 << 24) - d);
        }

        data[i] = d;
    }
}

status_t TFA9896_DspBiquad_Disable(tfa9896_handle_t *handle, int biquad_index)
{
    int coeff_buffer[6];
    unsigned char bytes[6 * 3];
    status_t error = kStatus_TFA9896_Ok;
    /* set in correct order and format for the DSP */
    coeff_buffer[0] = (int)-8388608; /* -1.0f */
    coeff_buffer[1] = 0;
    coeff_buffer[2] = 0;
    coeff_buffer[3] = 0;
    coeff_buffer[4] = 0;
    coeff_buffer[5] = 0;
    /* convert float to fixed point and then bytes suitable for transmaission over I2C */
    tfa9896_convert_data2bytes(6, coeff_buffer, bytes);
    error = TFA9896_DspSetParam(handle, 2, (unsigned char)biquad_index, (unsigned char)6 * 3, bytes);

    return error;
}

#ifdef TFA9896_DEBUG_DATA
void printArray(char *ptr, size_t size)
{
    char *const end = ptr + size;
    while (ptr < end)
    {
        TFA9896_Printf("[%x]-", *ptr++);
    }
}
#endif

status_t TFA9896_Write_FilterBank(tfa9896_handle_t *handle, tfa9896FilterM_t *filter)
{
    unsigned char biquad_index;
    status_t error = kStatus_TFA9896_Ok;
    for (biquad_index = 0; biquad_index < 10; biquad_index++)
    {
        if (filter[biquad_index].enabled)
        {
            TFA9896_Printf("TFA9896_Write_FilterBank inside if block\n");
            error = TFA9896_DspSetParam(handle, 2, biquad_index + 1, sizeof(filter[biquad_index].biquad.bytes),
                                        filter[biquad_index].biquad.bytes);
        }
        else
        {
            TFA9896_Printf("TFA9896_Write_FilterBank inside else block\n");
            error = TFA9896_DspBiquad_Disable(handle, biquad_index + 1);
        }
    }
    return error;
}

unsigned char vsfwdelay_table[] = {
    0, 0, 2, /*Index 0 - Current/Volt Fractional Delay for 8KHz  */
    0, 0, 0, /*Index 1 - Current/Volt Fractional Delay for 11KHz */
    0, 0, 0, /*Index 2 - Current/Volt Fractional Delay for 12KHz */
    0, 0, 2, /*Index 3 - Current/Volt Fractional Delay for 16KHz */
    0, 0, 2, /*Index 4 - Current/Volt Fractional Delay for 22KHz */
    0, 0, 2, /*Index 5 - Current/Volt Fractional Delay for 24KHz */
    0, 0, 2, /*Index 6 - Current/Volt Fractional Delay for 32KHz */
    0, 0, 2, /*Index 7 - Current/Volt Fractional Delay for 44KHz */
    0, 0, 3  /*Index 8 - Current/Volt Fractional Delay for 48KHz */
};
unsigned char cvfracdelay_table[] = {
    0, 0, 51, /*Index 0 - Current/Volt Fractional Delay for 8KHz  */
    0, 0, 0,  /*Index 1 - Current/Volt Fractional Delay for 11KHz */
    0, 0, 0,  /*Index 2 - Current/Volt Fractional Delay for 12KHz */
    0, 0, 38, /*Index 3 - Current/Volt Fractional Delay for 16KHz */
    0, 0, 34, /*Index 4 - Current/Volt Fractional Delay for 22KHz */
    0, 0, 33, /*Index 5 - Current/Volt Fractional Delay for 24KHz */
    0, 0, 11, /*Index 6 - Current/Volt Fractional Delay for 32KHz */
    0, 0, 2,  /*Index 7 - Current/Volt Fractional Delay for 44KHz */
    0, 0, 62  /*Index 8 - Current/Volt Fractional Delay for 48KHz */
};

status_t tfa_dsp_write_cvfracdelay_table(tfa9896_handle_t *handle)
{
    TFA9896_Printf("Bytes  cvfracdelay_table_96 to be written:%d\n", sizeof(cvfracdelay_table));
    return TFA9896_DspSetParam(handle, MODULE_FRAMEWORK, 0x06, sizeof(cvfracdelay_table), cvfracdelay_table);
}

status_t tfa_dsp_write_vsfwdelay_table(tfa9896_handle_t *handle)
{
    TFA9896_Printf("Bytes  vsfwdelay_table_96 to be written:%d\n", sizeof(vsfwdelay_table));
    return TFA9896_DspSetParam(handle, MODULE_FRAMEWORK, 0x03, sizeof(vsfwdelay_table), vsfwdelay_table);
}

status_t TFA9896_DSPWriteTables(tfa9896_handle_t *handle)
{
    status_t error = kStatus_TFA9896_Ok;

    error = tfa_dsp_write_vsfwdelay_table(handle);
    if (error == kStatus_TFA9896_Ok)
    {
        error = tfa_dsp_write_cvfracdelay_table(handle);
        assert(error == kStatus_TFA9896_Ok);
    }

    TFA9896_SetBits(handle, TFA1_BF_RST, 1);
    assert(error == kStatus_TFA9896_Ok);
    TFA9896_SetBits(handle, TFA1_BF_RST, 0);
    assert(error == kStatus_TFA9896_Ok);
    return error;
}

status_t TFA9896_ProcessPatchFile(tfa9896_handle_t *handle, int length, const unsigned char *bytes)
{
    unsigned short size;
    int index;

    status_t err = kStatus_TFA9896_Ok;
#if defined(DEMO_VERBOSE)
    int i;
#endif

    /* expect following format in patchBytes:
     * 2 bytes length of I2C transaction in little endian, then the bytes, excluding the slave address which is added
     * from the handle This repeats for the whole file
     */
    index = 0;

    while (index < length)
    {
        /* extract little endian length */
        size = bytes[index] + bytes[index + 1] * 256;
        index += 2;
        if ((index + size) > length)
        {
            /* too big, outside the buffer, error in the input data */
            return kStatus_TFA9896_Bad_Parameter;
        }
        if ((size + 1) > MAX_I2C_LENGTH)
        {
            /* too big, must fit buffer */
            return kStatus_TFA9896_Bad_Parameter;
        }

#ifdef TFA9896_PRINT_DEBUG
        /* TFA9896_Printf("Bytes to be written_patch:%d (index = %d bytes[index] = %d bytes[index+1] = %d\r\n",size,
         index, bytes[index], bytes[index+1]);*/
#endif

        err = CODEC_I2C_Send(handle->i2cHandle, handle->config->slaveAddress, 0U, 0U, (void *)(bytes + index), size);

        if (err != kStatus_Success)
        {
#ifdef TFA9896_PRINT_DEBUG
            TFA9896_Printf("I2C write error at %d\r\n", size);
#endif
            err = kStatus_TFA9896_I2C_Fatal;
            break;
        }
#if defined(DEMO_VERBOSE)
        for (i = 0; i < transfer.dataSize; i++)
            TFA9896_Printf("[%02x]-", (unsigned char)((unsigned char *)transfer.data + i));
        TFA9896_Printf("\r\n");
#endif
        index += size;
    }

    return err;
}

status_t TFA9896_DspWritePreset(tfa9896_handle_t *handle, int length, const unsigned char *pPresetBytes)
{
    status_t error = kStatus_TFA9896_Ok;
    if (pPresetBytes != 0)
    {
        TFA9896_Printf("Bytes to be written_preset_end:%d\n", length);
        /* by design: keep the data opaque and no interpreting/calculation */
        error = TFA9896_DspSetParam(handle, MODULE_SPEAKERBOOST, SB_PARAM_SET_PRESET, length, pPresetBytes);
        TFA9896_Printf("Bytes  written_preset_end:%d\n", length);
    }
    else
    {
        error = kStatus_TFA9896_Bad_Parameter;
    }
    return error;
}

status_t TFA9896_DspWriteConfig(tfa9896_handle_t *handle, int length, const unsigned char *pConfigBytes)
{
    status_t error = kStatus_TFA9896_Ok;
    TFA9896_Printf("Bytes to be written_config:%d\n", length);
    error = TFA9896_DspSetParam(handle, MODULE_SPEAKERBOOST, SB_PARAM_SET_CONFIG, length, pConfigBytes);
    TFA9896_Printf("Bytes to written_config_end:%d\n", length);
    return error;
}

status_t TFA9896_DspWriteSpeakerParameters(tfa9896_handle_t *handle, int length, const unsigned char *pSpeakerBytes)
{
    status_t error;
    if (pSpeakerBytes != 0)
    {
        TFA9896_Printf("Bytes to be written_speaker:%d\n", length);
        /* by design: keep the data opaque and no interpreting/calculation */
        error = TFA9896_DspSetParam(handle, MODULE_SPEAKERBOOST, SB_PARAM_SET_LSMODEL, length, pSpeakerBytes);

        TFA9896_Printf("Bytes to written_speaker_end:%d\n", length);
    }
    else
    {
        error = kStatus_TFA9896_Bad_Parameter;
    }

    return error;
}

uint16_t tfa_get_bf_value(const uint16_t bf, const uint16_t reg_value)
{
    uint16_t msk, value;

    /*
     * bitfield enum:
     * - 0..3  : len
     * - 4..7  : pos
     * - 8..15 : address
     */
    uint8_t len = bf & 0x0f;
    uint8_t pos = (bf >> 4) & 0x0f;

    msk   = ((1 << (len + 1)) - 1) << pos;
    value = (reg_value & msk) >> pos;

    return value;
}

#ifdef TFA9890_DEVICE
static uint16_t tfa9890_dsp_system_stable(tfa9896_handle_t *handle, int *ready)
{
    char error;
    unsigned short status, mtp0;
    int result;
    uint8_t tries;
    /************************/
    result = tfa_read_reg(handle, TFA1_BF_AREFS);
    if (result < 0)
    {
        error = -result;
        goto errorExit;
    }
    status = (unsigned short)result;

    /* if AMPS is set then we were already configured and running
     *   no need to check further
     */
    *ready = (tfa_get_bf_value(TFA1_BF_AMPS, status) == 1);
    if (*ready) /* if  ready go back */
    {
        return 0; /* will be kStatus_TFA9896_Ok */
    }

    /* check AREFS and CLKS: not ready if either is clear */
    *ready = !((tfa_get_bf_value(TFA1_BF_AREFS, status) == 0) || (tfa_get_bf_value(TFA1_BF_CLKS, status) == 0));
    if (!*ready) /* if not ready go back */
    {
        return 0; /* will be kStatus_TFA9896_Ok */
    }

    /* check MTPB
     *   mtpbusy will be active when the subsys copies MTP to I2C
     *   2 times retry avoids catching this short mtpbusy active period
     */
    for (tries = 2; tries > 0; tries--)
    {
        result = TFA9896_GetBits(handle, TFA1_BF_MTPB);
        if (result < 0)
        {
            error = -result;
            goto errorExit;
        }
        status = (unsigned short)result;

        /* check the contents of the STATUS register */
        *ready = (status == 0);
        if (*ready) /* if ready go on */
        {
            break;
        }
    }
    if (tries == 0) /* ready will be 0 if retries exausted */
    {
        return 0;
    }
    /* check the contents of  MTP register for non-zero,
     *  this indicates that the subsys is ready  */

    error = TFA9896_ReadRegister(handle, 0x84, &mtp0);
    if (error)
    {
        goto errorExit;
    }

    *ready = (mtp0 != 0); /* The MTP register written? */

    return error;

errorExit:
    *ready = 0;
    return error;
}
#endif

status_t setOtc(tfa9896_handle_t *handle, int otcOn)
{
    unsigned short mtp;
    status_t err;
    unsigned short status;
    int mtpChanged = 0;
    int i;

    TFA9896_Printf("Inside setOtc\n");
    err = TFA9896_ReadRegister(handle, 0x80, &mtp);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    TFA9896_Printf("mtp:%d--mtp & 0x01:%d--otcOn:%d\n", mtp, (mtp & 0x01), otcOn);
    /* set reset MTPEX bit if needed */
    if ((mtp & 0x01) != otcOn)
    {
        TFA9896_Printf("writing into 0x5A and setting OTC\n");
        /* need to change the OTC bit, set MTPEX=0 in any case */
        err = TFA9896_WriteRegister(handle, 0x0B, (uint16_t)0x5A);
        if (err != kStatus_TFA9896_Ok)
        {
            return err;
        }
        err = TFA9896_WriteRegister(handle, 0x80, (uint16_t)otcOn);
        if (err != kStatus_TFA9896_Ok)
        {
            return err;
        }
        err = TFA9896_WriteRegister(handle, 0x62, 1 << 11);
        if (err != kStatus_TFA9896_Ok)
        {
            return err;
        }
        mtpChanged = 1;
    }
    do
    {
        for (i = 0; i < 0xfff; i++)
            ;
        err = TFA9896_ReadRegister(handle, 0x00, &status);
        if (err != kStatus_TFA9896_Ok)
        {
            return err;
        }

    } while ((status & 0x100) == 0x100);
    assert((status & 0x100) == 0);
    if (mtpChanged)
    {
        TFA9896_Printf("writing 0x01 into 0x70\n");
        err = TFA9896_WriteRegister(handle, 0x70, (uint16_t)0x1);
        if (err != kStatus_TFA9896_Ok)
        {
            return err;
        }
    }

    return kStatus_TFA9896_Ok;
}

status_t TFA9896_SetConfigured(tfa9896_handle_t *handle)
{
    status_t error;
    unsigned short value;
    /* read the SystemControl register, modify the bit and write again */
    error = TFA9896_ReadRegister(handle, 0x09, &value);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }
    value |= 0x20;
    error = TFA9896_WriteRegister(handle, 0x09, value);
    return error;
}

status_t TFA9896_DspReadMem(tfa9896_handle_t *handle, unsigned short start_offset, int num_words, int *pValues)
{
    status_t error = kStatus_TFA9896_Ok;
    unsigned short cf_ctrl; /* the value to sent to the CF_CONTROLS register */
    unsigned char bytes[MAX_PARAM_SIZE /*MAX_I2C_LENGTH*/];
    int burst_size; /* number of words per burst size */
    int bytes_per_word = 3;
    int num_bytes;
    int *p;
    /* first set DMEM and AIF, leaving other bits intact */
    error = TFA9896_ReadRegister(handle, 0x70, &cf_ctrl);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }
    cf_ctrl &= ~0x000E;          /* clear AIF & DMEM */
    cf_ctrl |= (DMEM_XMEM << 1); /* set DMEM, leave AIF cleared for autoincrement */
    error = TFA9896_WriteRegister(handle, 0x70, cf_ctrl);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }
    error = TFA9896_WriteRegister(handle, 0x71, start_offset);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }
    num_bytes = num_words * bytes_per_word;
    p         = pValues;
    for (; num_bytes > 0;)
    {
        burst_size = ROUND_DOWN(MAX_I2C_LENGTH, bytes_per_word);
        if (num_bytes < burst_size)
        {
            burst_size = num_bytes;
        }
        assert(burst_size <= sizeof(bytes));
        error = TFA9896_ReadData(handle, 0x72, burst_size, bytes);
        if (error != kStatus_TFA9896_Ok)
        {
            return error;
        }
        tfa9896_convert_bytes2data(burst_size, bytes, p);
        num_bytes -= burst_size;
        p += burst_size / bytes_per_word;
    }
    return kStatus_TFA9896_Ok;
}

status_t TFA9896_DspExecuteRpc(tfa9896_handle_t *handle,
                               unsigned char module_id,
                               unsigned char param_id,
                               int num_inbytes,
                               unsigned char indata[],
                               int num_outbytes,
                               unsigned char outdata[])
{
    status_t error;
    int rpcStatus = STATUS_OK;
    int i;

    /* 1) write the id and data to the DSP XMEM */
    error = writeParameter(handle, module_id, param_id, num_inbytes, indata);

    /* 2) wake up the DSP and let it process the data */
    if (error == kStatus_TFA9896_Ok)
    {
        error = executeParam(handle);
    }

    /* 3) wait for the ack */
    if (error == kStatus_TFA9896_Ok)
    {
        error = waitResult(handle);
    }

    /* 4) check the RPC return value */
    if (error == kStatus_TFA9896_Ok)
    {
        error = checkRpcStatus(handle, &rpcStatus);
    }
    if (error == kStatus_TFA9896_Ok)
    {
        if (rpcStatus != STATUS_OK)
        {
            /* DSP RPC call returned an error */
            error = (status_t)(rpcStatus + kStatus_TFA9896_RpcBase);
        }
    }

    if (error == kStatus_TFA9896_Ok)
    {
        /* 5) read the resulting data */
        error = TFA9896_WriteRegister(handle, 0x71, 2 /*start_offset*/);
        if (error != kStatus_TFA9896_Ok)
        {
            return error;
        }
        /* read in chunks, limited by max I2C length */
        for (i = 0; i < num_outbytes;)
        {
            int burst_size = ROUND_DOWN(MAX_I2C_LENGTH, 3 /*bytes_per_word*/);
            if ((num_outbytes - i) < burst_size)
            {
                burst_size = num_outbytes - i;
            }
            error = TFA9896_ReadData(handle, 0x72, burst_size, outdata + i);
            if (error != kStatus_TFA9896_Ok)
            {
                return error;
            }
            i += burst_size;
        }
    }

    return error;
}

status_t TFA9896_CheckICROMversion(tfa9896_handle_t *handle, const unsigned char patchheader[])
{
    status_t error = kStatus_TFA9896_Ok;
    unsigned short checkrev;
    unsigned short checkaddress;
    int checkvalue;
    int value = 0;
    unsigned short status;
    checkrev = patchheader[0];
    if ((checkrev != 0xFF) && (checkrev != 0x96))
    {
        return kStatus_TFA9896_Not_Supported;
    }
    checkaddress = (patchheader[1] << 8) + patchheader[2];
    checkvalue   = (patchheader[3] << 16) + (patchheader[4] << 8) + patchheader[5];
    if (checkaddress != 0xFFFF)
    {
        /* before reading XMEM, check if we can access the DSP */
        error = TFA9896_ReadRegister(handle, 0x00, &status);
        if (error == kStatus_TFA9896_Ok)
        {
            if ((status & 0x8000) != 0x8000)
            {
                /* one of Vddd, PLL and clocks not ok */
                error = kStatus_TFA9896_DSP_not_running;
            }
        }
        /* read some address register that allows checking the correct ROM version */
        if (error == kStatus_TFA9896_Ok)
        {
            error = TFA9896_DspReadMem(handle, checkaddress, 1, &value);
        }
        if (error == kStatus_TFA9896_Ok)
        {
            if (value != checkvalue)
            {
                error = kStatus_TFA9896_Not_Supported;
            }
        }
    }
    return error;
}

int tfa_write_reg(tfa9896_handle_t *handle, const uint16_t bf, const uint16_t reg_value)
{
    status_t err;

    /* bitfield enum - 8..15 : address */
    uint8_t address = (bf >> 8) & 0xff;

    err = TFA9896_WriteRegister(handle, address, reg_value);
    if (err)
        return -err;

    return 0;
}

status_t TFA9896_DSP_System_Stable(tfa9896_handle_t *handle, int *ready)
{
#ifndef TFA9890_DEVICE
    status_t error = kStatus_TFA9896_Ok;
    unsigned short status;
    int value;

    /* check the contents of the STATUS register */
    value = tfa_read_reg(handle, TFA1_BF_AREFS);
    if (value < 0)
    {
        error  = -value;
        *ready = 0;
        /* an error here can be fatal */
        TFA9896_Printf("FATAL ERROR#######\n");
        return error;
    }
    status = (unsigned short)value;

    /* check AREFS and CLKS: not ready if either is clear */
    *ready = !((tfa_get_bf_value(TFA1_BF_AREFS, status) == 0) || (tfa_get_bf_value(TFA1_BF_CLKS, status) == 0) ||
               (tfa_get_bf_value(TFA1_BF_MTPB, status) == 1));

    return error;
#else
    return tfa9890_dsp_system_stable(handle, ready);
#endif
}

#ifdef TFA9896_DEBUG
static char *stateFlagsStr(int stateFlags)
{
    static char flags[10];

    flags[0] = (stateFlags & (0x1 << tfa9896_SpeakerBoost_ActivityLive)) ? 'A' : 'a';
    flags[1] = (stateFlags & (0x1 << tfa9896_SpeakerBoost_S_CtrlLive)) ? 'S' : 's';
    flags[2] = (stateFlags & (0x1 << tfa9896_SpeakerBoost_MutedLive)) ? 'M' : 'm';
    flags[3] = (stateFlags & (0x1 << tfa9896_SpeakerBoost_X_CtrlLive)) ? 'X' : 'x';
    flags[4] = (stateFlags & (0x1 << tfa9896_SpeakerBoost_T_CtrlLive)) ? 'T' : 't';
    flags[5] = (stateFlags & (0x1 << tfa9896_SpeakerBoost_NewModelLive)) ? 'L' : 'l';
    flags[6] = (stateFlags & (0x1 << tfa9896_SpeakerBoost_VolumeRdyLive)) ? 'V' : 'v';
    flags[7] = (stateFlags & (0x1 << tfa9896_SpeakerBoost_DamagedLive)) ? 'D' : 'd';
    flags[8] = (stateFlags & (0x1 << tfa9896_SpeakerBoost_SignalClippingLive)) ? 'C' : 'c';

    flags[9] = 0;
    return flags;
}
#endif

/* Execute RPC protocol to read something from the DSP */
status_t TFA9896_DspGetParam(
    tfa9896_handle_t *handle, unsigned char module_id, unsigned char param_id, int num_bytes, unsigned char data[])
{
    status_t error;
    unsigned short cf_ctrl = 0x0002; /* the value to be sent to the CF_CONTROLS register: cf_req=00000000, cf_int=0,
                                        cf_aif=0, cf_dmem=XMEM=01, cf_rst_dsp=0 */
    unsigned short cf_mad = 0x0001;  /* memory address to be accessed (0 : Status, 1 : ID, 2 : parameters) */
    unsigned short cf_status;        /* the contents of the CF_STATUS register */
    int rpcStatus = STATUS_OK;

    if (handle->config->slaveAddress == 0x1C)
    {
        /* cannot read */
        return kStatus_TFA9896_Bad_Parameter;
    }
    error = check_size(DMEM_XMEM, num_bytes);

    if (error == kStatus_TFA9896_Ok)
    {
        if ((num_bytes <= 0) || (num_bytes > MAX_PARAM_SIZE))
        {
            return kStatus_TFA9896_Bad_Parameter;
        }
    }
#ifdef OPTIMIZED_RPC
    {
        /* minimize the number of I2C transactions by making use of the autoincrement in I2C */
        unsigned char buffer[7];
        /* first the data for CF_CONTROLS */
        buffer[0] = (unsigned char)((cf_ctrl >> 8) & 0xFF);
        buffer[1] = (unsigned char)(cf_ctrl & 0xFF);
        /* write the contents of CF_MAD which is the subaddress following CF_CONTROLS */
        buffer[2] = (unsigned char)((cf_mad >> 8) & 0xFF);
        buffer[3] = (unsigned char)(cf_mad & 0xFF);
        /* write the module and RPC id into CF_MEM, which follows CF_MAD */
        buffer[4] = 0;
        buffer[5] = module_id + 128;
        buffer[6] = param_id;
        error     = TFA9896_WriteData(handle, 0x70, sizeof(buffer), buffer);
    }
#else
    /* 1) write the id and data to the DSP XMEM */
    if (error == kStatus_TFA9896_Ok)
    {
        error = TFA9896_WriteRegister(handle, 0x70, cf_ctrl);
    }
    if (error == kStatus_TFA9896_Ok)
    {
        error = TFA9896_WriteRegister(handle, 0x71, cf_mad);
    }
    if (error == kStatus_TFA9896_Ok)
    {
        unsigned char id[3];
        id[0] = 0;
        id[1] = module_id + 128;
        id[2] = param_id;
        /* only try MEM once, if error, need to resend mad as well */
        error = TFA9896_WriteData(handle, 0x72, 3, id);
    }
#endif
    /* 2) wake up the DSP and let it process the data */
    if (error == kStatus_TFA9896_Ok)
    {
        cf_ctrl |= (1 << 8) | (1 << 4); /* set the cf_req1 and cf_int bit */

        error = TFA9896_WriteRegister(handle, 0x70, (uint16_t)cf_ctrl);
    }
    /* 3) wait for the ack */
    if (error == kStatus_TFA9896_Ok)
    {
        int tries = 0;
        do
        {
            error = TFA9896_ReadRegister(handle, 0x73, &cf_status);
            tries++;
        } while (
            (error == kStatus_TFA9896_Ok) && ((cf_status & 0x0100) == 0) &&
            (tries < TFA9896_API_WAITRESULT_NTRIES)); /* don't wait forever, DSP is pretty quick to respond (< 1ms) */
        if (tries >= TFA9896_API_WAITRESULT_NTRIES)
        {
            /* something wrong with communication with DSP */
            return kStatus_TFA9896_DSP_not_running;
        }
    }
    /* 4) check the RPC return value */
    if (error == kStatus_TFA9896_Ok)
    {
        error = checkRpcStatus(handle, &rpcStatus);
    }
    if (error == kStatus_TFA9896_Ok)
    {
        if (rpcStatus != STATUS_OK)
        {
            /* DSP RPC call returned an error */
            error = (status_t)(rpcStatus + kStatus_TFA9896_RpcBase);
        }
    }
    /* 5) read the resulting data */
    if (error == kStatus_TFA9896_Ok)
    {
        cf_mad = 0x0002; /* memory address to be accessed (0 : Status, 1 : ID, 2 : parameters) */
        error  = TFA9896_WriteRegister(handle, 0x71, (uint16_t)cf_mad);
    }
    if (error == kStatus_TFA9896_Ok)
    {
        int offset          = 0;
        int chunk_size      = ROUND_DOWN(NXP_I2C_MAX_SIZE, 3 /* XMEM word size */);
        int remaining_bytes = num_bytes;
        /* due to autoincrement in cf_ctrl, next write will happen at the next address */
        while ((error == kStatus_TFA9896_Ok) && (remaining_bytes > 0))
        {
            if (remaining_bytes < 252)
            {
                chunk_size = remaining_bytes;
            }
            /* else chunk_size remains at initialize value above*/
            error = TFA9896_ReadData(handle, 0x72, chunk_size, data + offset);
            remaining_bytes -= chunk_size;
            offset += chunk_size;
        }
    }
    return error;
}

#ifdef TFA9896_LIVEDATA_CAPTURE
status_t TFA9896_DspGetStateInfo(tfa9896_handle_t *handle, tfa9896_StateInfoLive_t *pInfo)
{
    status_t error = kStatus_TFA9896_Ok;
    int24 data[FW_STATE_MAX_SIZE]; /* allocate worst case */
    unsigned char bytes[FW_STATE_MAX_SIZE * 3];
    int stateSize =
        FW_STATE_SIZE; /* contains the actual amount of parameters transferred, depends on IC and ROM code version */
    int i;

    assert(pInfo != 0);

    /* init to default value to have sane values even when some features aren't supported */
    for (i = 0; i < FW_STATE_MAX_SIZE; i++)
    {
        data[i] = 0;
    }

    error = TFA9896_DspGetParam(handle, MODULE_FRAMEWORK, FW_PARAM_GET_STATE, 3 * stateSize, bytes);
    if (error != kStatus_TFA9896_Ok)
    {
        if (error == kStatus_TFA9896_RpcParamId)
        {
            /* old ROM code, ask SpeakerBoost and only do first portion */
            stateSize = 8;
            error     = TFA9896_DspGetParam(handle, MODULE_SPEAKERBOOST, SB_PARAM_GET_STATE, 3 * stateSize, bytes);
        }
        else
        {
            return error;
        }
    }
    tfa9896_convert_bytes2data(3 * stateSize, bytes, data);
    pInfo->agcGain    = (float)data[0] / (1 << (23 - SPKRBST_AGCGAIN_EXP)); /* /2^23*2^(SPKRBST_AGCGAIN_EXP) */
    pInfo->limGain    = (float)data[1] / (1 << (23 - SPKRBST_LIMGAIN_EXP)); /* /2^23*2^(SPKRBST_LIMGAIN_EXP) */
    pInfo->sMax       = (float)data[2] / (1 << (23 - SPKRBST_HEADROOM));    /* /2^23*2^(SPKRBST_HEADROOM)    */
    pInfo->T          = data[3] / (1 << (23 - SPKRBST_TEMPERATURE_EXP));    /* /2^23*2^(def.SPKRBST_TEMPERATURE_EXP) */
    pInfo->statusFlag = data[4];
    pInfo->X1         = (float)data[5] / (1 << (23 - SPKRBST_HEADROOM)); /* /2^23*2^(SPKRBST_HEADROOM)        */

    pInfo->X2          = 0;                                                      /* /2^23*2^(SPKRBST_HEADROOM)        */
    pInfo->Re          = (float)data[6] / (1 << (23 - SPKRBST_TEMPERATURE_EXP)); /* /2^23*2^(SPKRBST_TEMPERATURE_EXP) */
    pInfo->shortOnMips = data[7];
    return error;
}

void dump_state_infoLive(tfa9896_StateInfoLive_t *pState)
{
#ifdef TFA9896_DEBUG
    TFA9896_Printf(
        "state: flags %s, agcGain %2.1f\tlimGain %2.1f\tsMax %2.1f\tT %d\tX1 %2.1f\tX2 %2.1f\tRe %2.2f\tshortOnMips "
        "%d\n",
        stateFlagsStr(pState->statusFlag), pState->agcGain, pState->limGain, pState->sMax, pState->T, pState->X1,
        pState->X2, pState->Re, pState->shortOnMips);
#endif
}
#endif

status_t TFA9896_WaitCalibrateDone(tfa9896_handle_t *handle, int *calibrateDone)
{
    status_t err;
    int tries = 0;
    unsigned short mtp;
#define WAIT_TRIES 30000

    err = TFA9896_ReadRegister(handle, 0x80, &mtp);

    /* in case of calibrate once wait for MTPEX */
    if (mtp & 0x1)
    {
        while ((*calibrateDone == 0) && (tries < TFA9896_API_WAITRESULT_NTRIES))
        { /* TODO optimise with wait estimation */
            err            = TFA9896_ReadRegister(handle, 0x80, &mtp);
            *calibrateDone = (mtp & 0x2); /* check MTP bit1 (MTPEX) */
            tries++;
        }
    }
    else /* poll xmem for calibrate always */
    {
        while ((*calibrateDone == 0) && (tries < WAIT_TRIES))
        { /* TODO optimise with wait estimation*/
            err = TFA9896_DspReadMem(handle, 231, 1, calibrateDone);
            tries++;
        }
        if (tries == WAIT_TRIES)
        {
            TFA9896_Printf("calibrateDone 231 timedout\n");
        }
    }
    return err;
}

status_t TFA9896_DspGetCalibrationImpedance(tfa9896_handle_t *handle, float *pRe25)
{
    status_t error = kStatus_TFA9896_Ok;
    unsigned char bytes[3];
    int24 data[1];
    int calibrateDone;

    assert(pRe25 != 0);
    *pRe25 = 0.0f; /* default 0.0 */
    {
        error = TFA9896_DspReadMem(handle, 231, 1, &calibrateDone);
        if (error == kStatus_TFA9896_Ok)
        {
            if (!calibrateDone)
            {
                /* return the default */
                return error;
            }
            error = TFA9896_DspGetParam(handle, MODULE_SPEAKERBOOST, 0x85, 3, bytes);
        }
        if (error == kStatus_TFA9896_Ok)
        {
            tfa9896_convert_bytes2data(3, bytes, data);
            *pRe25 = ((float)data[0] / (1 << (23 - SPKRBST_TEMPERATURE_EXP)) * 1024) /
                     1000; /* /2^23*2^(def.SPKRBST_TEMPERATURE_EXP) */
        }
    }
    return error;
}

status_t TFA9896_DSP_Write_Mem_Word(tfa9896_handle_t *handle, unsigned short address, int value, int memtype)
{
    status_t error = kStatus_TFA9896_Ok;
    unsigned char bytes[3];

    TFA9896_SetBits(handle, TFA1_BF_DMEM, (uint16_t)memtype);
    error = -tfa_write_reg(handle, TFA1_BF_MADD, address);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }
    tfa9896_convert_data2bytes(1, &value, bytes);
    error = TFA9896_WriteData(handle, 0x720f >> 8, 3, bytes);

    return error;
}

/*************************/
#ifdef TFA9896_LIVEDATA_CAPTURE
status_t tfa9896GetSpeakerModel(tfa9896_handle_t *handle, int xmodel, tfa9896SPKRBST_SpkrModel_t *record)
{
    status_t error = kStatus_TFA9896_Ok;
    unsigned char bytes[3 * 141];
    int24 data[141];
    int i = 0;

    memset(bytes, 0, 423);

    /*PARAM_GET_LSMODELW*/
    error = TFA9896_DspGetParam(handle, 1, PARAM_GET_LSMODEL, 423, bytes);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }

    tfa9896_convert_bytes2data(sizeof(bytes), bytes, data);

    for (i = 0; i < 128; i++)
    {
        /*record->pFIR[i] = (double)data[i] / ((1 << 23) * 2);*/
        record->pFIR[i] = (double)data[i] / (1 << 22);
    }

    record->Shift_FIR     = data[i++];                        /* Exponent of HX data*/
    record->leakageFactor = (float)data[i++] / (1 << (23));   /* Excursion model integration leakage*/
    record->ReCorrection  = (float)data[i++] / (1 << (23));   /* Correction factor for Re*/
    record->xInitMargin = (float)data[i++] / (1 << (23 - 2)); /* (can change) Margin on excursion model during startup*/
    record->xDamageMargin =
        (float)data[i++] / (1 << (23 - 2));                /* Margin on excursion modelwhen damage has been detected*/
    record->xMargin  = (float)data[i++] / (1 << (23 - 2)); /* Margin on excursion model activated when LookaHead is 0*/
    record->Bl       = (float)data[i++] / (1 << (23 - 2)); /* Loudspeaker force factor*/
    record->fRes     = data[i++]; /* (can change) Estimated Speaker Resonance Compensation Filter cutoff frequency*/
    record->fResInit = data[i++]; /* Initial Speaker Resonance Compensation Filter cutoff frequency*/
    record->Qt       = (float)data[i++] / (1 << (23 - 6)); /* Speaker Resonance Compensation Filter Q-factor*/
    record->xMax     = (float)data[i++] / (1 << (23 - 7)); /* Maximum excursion of the speaker membrane*/
    record->tMax     = (float)data[i++] / (1 << (23 - 9)); /* Maximum Temperature of the speaker coil*/
    record->tCoefA   = (float)data[i++] / (1 << 23);       /* (can change) Temperature coefficient*/

    return error;
}

void dump_speaker_model(tfa9896SPKRBST_SpkrModel_t *pState, tfa9896_handle_t *handle)
{
    TFA9896_Printf("FRes:%d--SPKS:%d\n", pState->fRes, TFA9896_GetBits(handle, TFA1_BF_SPKS));
}
#endif

status_t TFA9896_PrintCalibration(tfa9896_handle_t *handle)
{
    status_t err = kStatus_TFA9896_Ok;
#ifdef TFA9896_DEBUG
    unsigned char bytes[6] = {0};
    int24 data[2];
    float mohm;

    err = TFA9896_DspGetParam(handle, MODULE_SPEAKERBOOST, SB_PARAM_GET_RE0, 3, bytes);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }

    tfa9896_convert_bytes2data(3, bytes, data);
    mohm = ((float)data[0] * 1024) / TFA1_FW_ReZ_SCALE;

    TFA9896_Printf(" Calibrated value :%1.2f mOhms :\n", (mohm * 1024) / 1000);
#endif

    return err;
}

status_t TFA9896_SetOneTimeCalibration(tfa9896_handle_t *handle)
{
    unsigned short mtp = 0;
    status_t err       = kStatus_TFA9896_Ok;
    int tries = 0, mtpBusy = 0;
    int i;
    /* Read MTP register*/
    TFA9896_Printf("totest\n");
    /* Set MTPOTC=1*/
    mtp |= 0x01;
    err = TFA9896_WriteRegister(handle, 0x40, (uint16_t)0x5A6B);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    err = TFA9896_WriteRegister(handle, 0x0B, (uint16_t)0x005A);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    err = TFA9896_WriteRegister(handle, 0x40, (uint16_t)0);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    /* Update contents of MTP register*/
    err = TFA9896_WriteRegister(handle, 0x80, mtp);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    err = TFA9896_SetBits(handle, TFA1_BF_CIMTP, 0x01);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    err = TFA9896_WriteRegister(handle, 0x40, (uint16_t)0x5A6B);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    err = TFA9896_WriteRegister(handle, 0x0B, (uint16_t)0);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    err = TFA9896_WriteRegister(handle, 0x40, (uint16_t)0);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    tries = 0;
    do
    {
        tries++;
        for (i = 0; i < 0xfff; i++)
            ;
        mtpBusy = TFA9896_GetBits(handle, TFA1_BF_MTPB);
    } while ((mtpBusy == 0x01) && (tries < TFA9896_API_WAITRESULT_NTRIES));

    if (tries == TFA9896_API_WAITRESULT_NTRIES)
    {
        TFA9896_Printf("MTP Busy timedout\n");
        err = kStatus_TFA9896_StateTimedOut;
    }

    return err;
}

status_t TFA9896_SetFactoryValues(tfa9896_handle_t *handle)
{
    unsigned short mtp = 0, ron, regRead, xor;
    status_t err       = kStatus_TFA9896_Ok;
    int tries = 0, mtpBusy = 0;
    int i;

    TFA9896_Printf("totest\n");
    /*********Hardcoding MTPEX and MTPOTC***************************/
    mtp |= 0x03;
    /*********Hardcoding Ron  in MTP to 8 ohm***************************/
    ron = 0x1F40;
    err = TFA9896_ReadRegister(handle, 0x8B, &regRead);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    xor = regRead ^ 0x005A;
    err = TFA9896_WriteRegister(handle, 0x40, (uint16_t)0x5A6B);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    err = TFA9896_WriteRegister(handle, 0x0B, (uint16_t)0x005A);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    err = TFA9896_WriteRegister(handle, 0x60, (uint16_t) xor);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    err = TFA9896_WriteRegister(handle, 0x40, (uint16_t)0);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    err = TFA9896_ReadRegister(handle, 0x32, &regRead);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    /*Update contents of MTP register*/
    err = TFA9896_WriteRegister(handle, 0x83, ron);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    err = TFA9896_WriteRegister(handle, 0x80, mtp);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    err = TFA9896_SetBits(handle, TFA1_BF_CIMTP, 0x01);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    err = TFA9896_WriteRegister(handle, 0x40, (uint16_t)0x5A6B);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    err = TFA9896_WriteRegister(handle, 0x0B, (uint16_t)0);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    err = TFA9896_WriteRegister(handle, 0x40, (uint16_t)0);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    tries = 0;
    do
    {
        tries++;
        for (i = 0; i < 0xfff; i++)
            ;
        mtpBusy = TFA9896_GetBits(handle, TFA1_BF_MTPB);
    } while ((mtpBusy == 0x01) && (tries < TFA9896_API_WAITRESULT_NTRIES));

    if (tries == TFA9896_API_WAITRESULT_NTRIES)
    {
        TFA9896_Printf("MTP Busy timedout\n");
        err = kStatus_TFA9896_StateTimedOut;
    }

    return err;
}

status_t TFA9896_ClearOneTimeCalibration(tfa9896_handle_t *handle)
{
    status_t err = kStatus_TFA9896_Ok;
    unsigned short mtp;
    int tries = 0, mtpBusy = 0;
    int i;

    /* Read MTP register */
    err = TFA9896_ReadRegister(handle, 0x80, &mtp);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    /* Set MTPEX=0 and MTPOTC=0 to clear current calibration status*/
    mtp &= ~(0x03);
    err = TFA9896_WriteRegister(handle, 0x40, (uint16_t)0x5A6B);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    err = TFA9896_WriteRegister(handle, 0x0B, (uint16_t)0x005A);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    err = TFA9896_WriteRegister(handle, 0x40, (uint16_t)0);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    /* Update contents of MTP register*/
    err = TFA9896_WriteRegister(handle, 0x80, mtp);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    err = TFA9896_SetBits(handle, TFA1_BF_CIMTP, 0x01);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }

    tries = 0;
    do
    {
        tries++;
        for (i = 0; i < 0xfff; i++)
            ;
        mtpBusy = TFA9896_GetBits(handle, TFA1_BF_MTPB);
    } while ((mtpBusy == 0x01) && (tries < TFA9896_API_WAITRESULT_NTRIES));

    if (tries == TFA9896_API_WAITRESULT_NTRIES)
    {
        TFA9896_Printf("MTP Busy timedout\n");
        err = kStatus_TFA9896_StateTimedOut;
    }

    return err;
}

status_t TFA9896_SetOVPBypass(tfa9896_handle_t *handle)
{
    status_t err;

    unsigned short value, xor;

    /* read the SystemControl register, modify the bit and write again */
    err = TFA9896_WriteRegister(handle, 0x40, 0x5A6B);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }

    err = TFA9896_ReadRegister(handle, 0x8B, &value);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }

    xor = value ^ 0x005A;
    err = TFA9896_WriteRegister(handle, 0x60, xor);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }

    err = TFA9896_ReadRegister(handle, 0x45, &value);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }
    TFA9896_Printf("before 0x45 regsiter is:%d\n", value);
    value |= (0x01 << 9);

    err = TFA9896_WriteRegister(handle, 0x45, value);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }

    err = TFA9896_ReadRegister(handle, 0x45, &value);
    if (err != kStatus_TFA9896_Ok)
    {
        return err;
    }

    TFA9896_Printf("after 0x45 regsiter is:%d\n", value);

    return err;
}

status_t TFA9896_SetMute(tfa9896_handle_t *handle, tfa9896_mute_t mute)
{
    status_t error;
    unsigned short audioctrl_value;
    unsigned short sysctrl_value;
    error = TFA9896_ReadRegister(handle, TFA9896_AUDIO_CTR, &audioctrl_value);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }
    error = TFA9896_ReadRegister(handle, TFA9896_SYS_CTRL, &sysctrl_value);

    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }
    switch (mute)
    {
        case Mute_Off:
            /* previous state can be digital or amplifier mute,
             * clear the cf_mute and set the enbl_amplifier bits
             *
             * To reduce PLOP at power on it is needed to switch the
             * amplifier on with the DCDC in follower mode (enbl_boost = 0 ?).
             * This workaround is also needed when toggling the powerdown bit!
             */
            audioctrl_value &= ~(TFA9896_AUDIO_CTR_CFSM_MSK);
            sysctrl_value |= TFA9896_SYS_CTRL_AMPE_MSK;
            sysctrl_value |= TFA9896_SYS_CTRL_DCA_MSK;
            break;
        case Mute_Digital:
            /* expect the amplifier to run */
            /* set the cf_mute bit */
            audioctrl_value |= TFA9896_AUDIO_CTR_CFSM_MSK;
            /* set the enbl_amplifier bit */
            sysctrl_value |= (TFA9896_SYS_CTRL_AMPE_MSK);
            /* clear active mode */
            sysctrl_value &= ~(TFA9896_SYS_CTRL_DCA_MSK);
            break;
        case Mute_Amplifier:
            /* clear the cf_mute bit */
            audioctrl_value &= ~TFA9896_AUDIO_CTR_CFSM_MSK;
            /* clear the enbl_amplifier bit and active mode */
            sysctrl_value &= ~(TFA9896_SYS_CTRL_AMPE_MSK | TFA9896_SYS_CTRL_DCA_MSK);
            break;
        default:
            error = kStatus_TFA9896_Bad_Parameter;
    }
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }
    error = TFA9896_WriteRegister(handle, TFA9896_AUDIO_CTR, audioctrl_value);
    if (error != kStatus_TFA9896_Ok)
    {
        return error;
    }
    error = TFA9896_WriteRegister(handle, TFA9896_SYS_CTRL, sysctrl_value);

    return error;
}
