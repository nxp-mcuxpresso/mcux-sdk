/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "nvm_adapter.h"

#if gNvStorageIncluded_d
#if (defined(__CC_ARM) || defined(__ARMCC_VERSION))

extern uint32_t Load$$ER_NVM_ADAPTER_TABLE$$Base[];
extern uint32_t Load$$ER_NVM_ADAPTER_TABLE$$Limit[];

#define gNVM_ADAPTER_TABLE_startAddr_c ((nvm_adapter_table_t *)Load$$ER_NVM_ADAPTER_TABLE$$Base)
#define gNVM_ADAPTER_TABLE_endAddr_c   ((nvm_adapter_table_t *)Load$$ER_NVM_ADAPTER_TABLE$$Limit)

#elif defined(__GNUC__)
extern uint32_t __start_NVM_ADAPTER_TABLE[];
extern uint32_t __stop_NVM_ADAPTER_TABLE[];
#define gNVM_ADAPTER_TABLE_startAddr_c ((nvm_adapter_table_t *)(void *)__start_NVM_ADAPTER_TABLE)
#define gNVM_ADAPTER_TABLE_endAddr_c   ((nvm_adapter_table_t *)(void *)__stop_NVM_ADAPTER_TABLE)
#elif (defined(__IAR_SYSTEMS_ICC__))
#define gNVM_ADAPTER_TABLE_startAddr_c ((nvm_adapter_table_t *)__section_begin("NVM_ADAPTER_TABLE"))
#define gNVM_ADAPTER_TABLE_endAddr_c   ((nvm_adapter_table_t *)__section_end("NVM_ADAPTER_TABLE"))
#else
#define gNVM_ADAPTER_TABLE_startAddr_c ((nvm_adapter_table_t *)0)
#define gNVM_ADAPTER_TABLE_endAddr_c   ((nvm_adapter_table_t *)0)
#warning Module information will not be stored!
#endif

int NVM_AdapterInit(void)
{
    static uint8_t initialized = 0;
    nvm_adapter_table_t *start;
    uint32_t startAddress = (uint32_t)gNVM_ADAPTER_TABLE_startAddr_c;
    uint32_t endAddress   = (uint32_t)gNVM_ADAPTER_TABLE_endAddr_c;
    int err               = 0;

    if (0U == initialized)
    {
        initialized = 1;
        start       = (nvm_adapter_table_t *)startAddress;

        while ((uint32_t)start < endAddress)
        {
            if (NULL != start->init)
            {
                err = start->init();
                if (0 != err)
                {
                    break;
                }
            }
            start++;
        }
        if (0 == err)
        {
            if (gNVM_OK_c != NvModuleInit())
            {
                err = -1;
            }
        }
    }
    else
    {
        err = -1;
    }
    return err;
}

int NVM_AdapterLoad(void)
{
    nvm_adapter_table_t *start;
    uint32_t startAddress = (uint32_t)gNVM_ADAPTER_TABLE_startAddr_c;
    uint32_t endAddress   = (uint32_t)gNVM_ADAPTER_TABLE_endAddr_c;
    int err               = 0;

    NVM_AdapterInit();

    start = (nvm_adapter_table_t *)startAddress;

    while ((uint32_t)start < endAddress)
    {
        if (NULL != start->load)
        {
            err = start->load();
            if (0 != err)
            {
                break;
            }
        }
        start++;
    }

    start = (nvm_adapter_table_t *)startAddress;

    while ((uint32_t)start < endAddress)
    {
        if (NULL != start->commit)
        {
            err = start->commit();
            if (0 != err)
            {
                break;
            }
        }
        start++;
    }
    return err;
}

#endif
