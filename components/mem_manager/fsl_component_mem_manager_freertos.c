/*! *********************************************************************************
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * \file
 *
 * This is the source file for the Memory Manager.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 ********************************************************************************** */

/*! *********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */

#include "fsl_common.h"
#include "fsl_component_mem_manager.h"
#include "FreeRTOS.h"
#include "portable.h"

/*! *********************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
********************************************************************************** */

mem_status_t MEM_Init(void)
{
    return kStatus_MemSuccess;
}

void *MEM_BufferAllocWithId(uint32_t numBytes, uint8_t poolId)
{
    (void)poolId;
    return pvPortMalloc((size_t)numBytes);
}

void *MEM_CallocAlt(size_t len, size_t val)
{
    return pvPortCalloc(len, val);
}

mem_status_t MEM_BufferFree(void *buffer)
{
    vPortFree(buffer);

    return kStatus_MemSuccess;
}

uint32_t MEM_GetFreeHeapSizeByAreaId(uint8_t area_id)
{
    (void)area_id;
    return (uint32_t)xPortGetFreeHeapSize();
}

uint32_t MEM_GetFreeHeapSize(void)
{
    return MEM_GetFreeHeapSizeByAreaId(0U);
}

mem_status_t MEM_RegisterExtendedArea(memAreaCfg_t *area_desc, uint8_t *p_area_id, uint16_t flags)
{
    /* NOT IMPLEMENTED */
    (void)area_desc;
    (void)p_area_id;
    (void)flags;
    return kStatus_MemUnknownError;
}

mem_status_t MEM_UnRegisterExtendedArea(uint8_t area_id)
{
    /* NOT IMPLEMENTED */
    (void)area_id;
    return kStatus_MemUnknownError;
}

mem_status_t MEM_BufferFreeAllWithId(uint8_t poolId)
{
    /* NOT IMPLEMENTED */
    (void)poolId;
    return kStatus_MemFreeError;
}

uint32_t MEM_GetHeapUpperLimitByAreaId(uint8_t area_id)
{
    /* NOT IMPLEMENTED */
    (void)area_id;
    return 0U;
}

uint32_t MEM_GetHeapUpperLimit(void)
{
    return MEM_GetHeapUpperLimitByAreaId(0u);
}

uint32_t MEM_GetFreeHeapSizeLowWaterMarkByAreaId(uint8_t area_id)
{
    /* NOT IMPLEMENTED */
    (void)area_id;
    return 0U;
}

uint32_t MEM_GetFreeHeapSizeLowWaterMark(void)
{
    return MEM_GetFreeHeapSizeLowWaterMarkByAreaId(0u);
}

uint32_t MEM_ResetFreeHeapSizeLowWaterMarkByAreaId(uint8_t area_id)
{
    /* NOT IMPLEMENTED */
    (void)area_id;
    return 0U;
}

uint32_t MEM_ResetFreeHeapSizeLowWaterMark(void)
{
    return MEM_ResetFreeHeapSizeLowWaterMarkByAreaId(0u);
}

uint16_t MEM_BufferGetSize(void *buffer)
{
    /* NOT IMPLEMENTED */
    (void)buffer;
    return 0U;
}

void *MEM_BufferRealloc(void *buffer, uint32_t new_size)
{
    /* NOT IMPLEMENTED */
    (void)buffer;
    (void)new_size;
    return NULL;
}

__attribute__((weak)) void MEM_ReinitRamBank(uint32_t startAddress, uint32_t endAddress)
{
    /* To be implemented by the platform */
    (void)startAddress;
    (void)endAddress;
}
