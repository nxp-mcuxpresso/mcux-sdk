/*
 * \file GetKinetisDevices.c
 * Source file that retrieves the system paths of connected Kinetis-W devices.
 *
 * Copyright 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>

#include "UARTDiscovery.h"

int main(int argc, char **argv)
{
    uint32_t i = 0, size = 0;

    InitializeDeviceManager();
    DeviceState *devices = GetAllDevices(&size);

    for (i = 0; i < size; i++) {
        if (devices[i].isKinetisWDevice) {
            printf("NXP Kinetis-W device on %s.\n", devices[i].deviceName);
        }
    }

    free(devices);

    return 0;
}
