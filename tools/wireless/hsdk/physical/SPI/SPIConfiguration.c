/*
 * \file SPIConfiguration.c
 * This is a source file for the SPIConfiguration module.
 *
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "SPIConfiguration.h"


SPIConfigurationData *defaultSettingsSPI(void)
{
    SPIConfigurationData *config = (SPIConfigurationData *) calloc (1, sizeof(SPIConfigurationData));
    if (config == NULL) {
        logMessage(HSDK_ERROR, "[SPIConfiguration]defaultSettingsSPI", "Memory allocation failed", HSDKThreadId());
        return NULL;
    }

    config->lengthFieldSize = 2;  // Thread, FlexIP, BLE; set to 1 for MAC
    config->transferMode = SPI_MODE_0;
    config->bitsPerWord = 8;
    config->maxSpeedHz = 1000000;  // 1MHz

    return config;
}

void freeSettingsSPI(SPIConfigurationData *config)
{
    if (config != NULL) {
        free(config);
    }
}

void setLengthFieldSize(SPIConfigurationData *config, uint8_t lengthFieldSize)
{
    config->lengthFieldSize = lengthFieldSize;
}

void setSpeedHzSPI(SPIConfigurationData *config, uint32_t maxSpeedHz)
{
    config->maxSpeedHz = maxSpeedHz;
}


/*! *********************************************************************************
* \brief  Initialize the SPI device with the configuration attributes.
*
* \param[in] SPI device file descriptor
* \param[in] configuration structure holding the attributes
*
* \return 0 in case of success, -1 otherwise
********************************************************************************** */
int initPortSPI(File portHandle, SPIConfigurationData *config)
{
    int ret = 0;

    /*
     * SPI mode
     */
    ret = ioctl(portHandle, SPI_IOC_WR_MODE, &config->transferMode);
    if (ret == -1)
        perror("can't set spi mode");

    ret = ioctl(portHandle, SPI_IOC_RD_MODE, &config->transferMode);
    if (ret == -1)
        perror("can't get spi mode");

    /*
     * bits per word
     */
    ret = ioctl(portHandle, SPI_IOC_WR_BITS_PER_WORD, &config->bitsPerWord);
    if (ret == -1)
        perror("can't set bits per word");

    ret = ioctl(portHandle, SPI_IOC_RD_BITS_PER_WORD, &config->bitsPerWord);
    if (ret == -1)
        perror("can't get bits per word");

    /*
     * max speed in Hz
     */
    ret = ioctl(portHandle, SPI_IOC_WR_MAX_SPEED_HZ, &config->maxSpeedHz);
    if (ret == -1)
        perror("can't set max speed hz");

    ret = ioctl(portHandle, SPI_IOC_RD_MAX_SPEED_HZ, &config->maxSpeedHz);
    if (ret == -1)
        perror("can't get max speed hz");

#ifdef DEBUG
    printf("spi mode: %d\n", config->transferMode);
    printf("bits per word: %d\n", config->bitsPerWord);
    printf("max speed: %d Hz (%d KHz)\n", config->maxSpeedHz, config->maxSpeedHz / 1000);
#endif

    return 0;
}
