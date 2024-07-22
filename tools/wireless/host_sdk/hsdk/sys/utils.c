/*
 * \file utils.c
 * This is a source file for the helper functions module.
 *
 * Copyright 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "utils.h"

/************************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
************************************************************************************/
void Store(uint64_t value, uint8_t *dest, uint32_t size, endianness end);
uint64_t Read(uint8_t *src, uint32_t size, endianness end);

/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
* \brief    Store an integer into a 2 byte array based on the selected endianness.
*
* \param[in] value
* \param[in] dest
* \param[in] end
*
* \return none
********************************************************************************** */
void Store16(uint16_t value, uint8_t *dest, endianness end)
{
    Store(value, dest, sizeof(uint16_t), end);
}

/*! *********************************************************************************
* \brief    Store an integer into a 4 byte array based on the selected endianness.
*
* \param[in] value
* \param[in] dest
* \param[in] end
*
* \return none
********************************************************************************** */
void Store32(uint32_t value, uint8_t *dest, endianness end)
{
    Store(value, dest, sizeof(uint32_t), end);
}

/*! *********************************************************************************
* \brief    Store an integer into an 8 byte array based on the selected endianness.
*
* \param[in] value
* \param[in] dest
* \param[in] end
*
* \return none
********************************************************************************** */
void Store64(uint64_t value, uint8_t *dest, endianness end)
{
    Store(value, dest, sizeof(uint64_t), end);
}

/*! *********************************************************************************
* \brief    Read a 2 byte integer into an array
*
* \param[in] src
* \param[in] end
*
* \return an integer containing the stored bytes of the array
********************************************************************************** */
uint16_t Read16(uint8_t *src, endianness end)
{
    return (uint16_t)Read(src, sizeof(uint16_t), end);
}

/*! *********************************************************************************
* \brief    Read a 4 byte integer into an array
*
* \param[in] src
* \param[in] end
*
* \return an integer containing the stored bytes of the array
********************************************************************************** */
uint32_t Read32(uint8_t *src, endianness end)
{
    return (uint32_t)Read(src, sizeof(uint32_t), end);
}

/*! *********************************************************************************
* \brief    Read an 8 byte integer into an array
*
* \param[in] src
* \param[in] end
*
* \return an integer containing the stored bytes of the array
********************************************************************************** */
uint64_t Read64(uint8_t *src, endianness end)
{
    return Read(src, sizeof(uint64_t), end);
}

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
* \brief    Store an integer into a byte array
*
* \param[in] value  the integer value to store into a byte array
* \param[in] dest   pointer to a previously allocated byte array
* \param[in] size   the size of the integer
* \param[in] end    the endianness used
*
* \return none
********************************************************************************** */
void Store(uint64_t value, uint8_t *dest, uint32_t size, endianness end)
{
    uint32_t i;
    uint8_t tmp;

    if (!dest) {
        return;
    }

    for (i = 0; i < size; i++) {
        tmp = value & 0xFF;
        if (end == _LITTLE_ENDIAN) {
            dest[i] = tmp;
        } else {
            dest[size - i - 1] = tmp;
        }
        value = value >> 8;
    }
}

/*! *********************************************************************************
* \brief    Store a byte array into an integer
*
* \param[in] src    pointer to the byte array
* \param[in] size   the size of the byte array
* \param[in] end    the endianness used
*
* \return an integer containing the bytes in the specified order
********************************************************************************** */
uint64_t Read(uint8_t *src, uint32_t size, endianness end)
{
    uint32_t i;
    uint64_t tmp = 0, value = 0;

    if (!src) {
        return 0;
    }

    for (i = 0; i < size; i++) {
        if (end == _LITTLE_ENDIAN) {
            tmp = ((uint64_t)src[i]) << (i * 8);
        } else {
            tmp = ((uint64_t)src[size - i - 1]) << (i * 8);
        }
        value = value + tmp;
    }

    return value;
}


#define MAXLEN 80

#ifdef __linux__
#   define CONFIG_FILE "/usr/local/etc/hsdk/hsdk.conf"
#elif _WIN32
#   define CONFIG_FILE "C:\\Python27\\DLLs\\hsdk.conf"
#   define strtok_r strtok_s
#endif

static char *trim(char *s)
{
    /* Initialize start, end pointers */
    char *s1 = s, *s2 = &s[strlen (s) - 1];

    /* Trim and delimit right side */
    while ((isspace (*s2)) && (s2 >= s1)) {
        s2--;
    }

    *(s2 + 1) = '\0';

    /* Trim left side */
    while ((isspace (*s1)) && (s1 < s2)) {
        s1++;
    }

    /* Copy finished string */
    strcpy (s, s1);
    return s;
}

ConfigParams *ParseConfig(void)
{
    ConfigParams *params = (ConfigParams *)calloc(1, sizeof(ConfigParams));

    char *s, *saveptr, buff[256];
    FILE *fp = fopen(CONFIG_FILE, "r");
    if (fp == NULL) {
        return params;  // everything is zeroed out by calloc
    }

    while ((s = fgets(buff, sizeof buff, fp)) != NULL) {

        /* Skip blank lines and comments */
        if (buff[0] == '\n' || buff[0] == '#') {
            continue;
        }

        /* Parse name/value pair from line */
        char name[MAXLEN + 1], value[MAXLEN + 1];
        s = strtok_r(buff, "=", &saveptr);
        if (s == NULL) {
            continue;
        } else {
            strncpy(name, s, MAXLEN);
            name[MAXLEN] = '\0';
        }
        s = strtok_r(NULL, "=", &saveptr);
        if (s == NULL) {
            continue;
        } else {
            strncpy(value, s, MAXLEN);
            value[MAXLEN] = '\0';
        }

        /* Get rid of trailing and leading whitespace */
        trim(value);

        if (strcmp(name, "FsciTxAck") == 0) {
            params->fsciTxAck = atoi(value);
        } else if (strcmp(name, "NumberOfRetries") == 0) {
            params->numberOfRetries = atoi(value);
        } else if (strcmp(name, "TimeoutAckMs") == 0) {
            params->timeoutAckMs = atoi(value);
        } else if (strcmp(name, "FsciRxAck") == 0) {
            params->fsciRxAck = atoi(value);
        } else {
            printf("WARNING: %s/%s: Unknown name/value pair!\n", name, value);
        }
    }

    fclose(fp);

    return params;
}

/*! *********************************************************************************
* \brief  Returns a correct system path regarding the current OS. If the value given
*         is already the path, carry on.
*
* \param[in] uartPath   a system path or a name for the device
*
* \return the system path for the given value
********************************************************************************** */
char *UARTSystemPath(char *uartPath)
{
#ifdef _WIN32
    char *p;
    char path[128];
    /* Check for already formatted string. */
    p = strstr(uartPath, "\\\\.\\");
    if (p != NULL) {
        return _strdup(uartPath);
    }
    /* Format string for Windows. */
    p = strstr(uartPath, "COM");
    sprintf_s(path, 128, "\\\\.\\%s", p);
    return _strdup(path);
#endif
    return uartPath;
}
