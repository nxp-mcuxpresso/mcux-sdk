/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __NVM_ADAPTER_H__
#define __NVM_ADAPTER_H__

#include "NVM_Interface.h"

#if (defined(__CC_ARM) || defined(__ARMCC_VERSION))

#define NVM_ADAPTER_TABLE(table) const table __attribute__((section("NVM_ADAPTER_TABLE"), used))

#elif defined(__GNUC__)

#define __section_define(x)      __attribute__((section("" #x), used))
#define NVM_ADAPTER_TABLE(table) const __section_define(.NVM_ADAPTER_TABLE) table

#elif (defined(__IAR_SYSTEMS_ICC__))

#pragma section = "NVM_ADAPTER_TABLE"

#define NVM_ADAPTER_TABLE(table) const table @ "NVM_ADAPTER_TABLE"

#else
#error unsupported tool-chain for NVM adapter!
#endif

typedef int (*nvm_adapter_table_init)(void);
typedef int (*nvm_adapter_table_load)(void);
typedef int (*nvm_adapter_table_commit)(void);

typedef struct _nvm_adapter_table
{
    NVM_DataEntry_t *table;
    uint32_t tableCount;
    nvm_adapter_table_init init;
    nvm_adapter_table_load load;
    nvm_adapter_table_commit commit;
} nvm_adapter_table_t;

int NVM_AdapterInit(void);
int NVM_AdapterLoad(void);

#endif /* __NVM_ADAPTER_H__ */
