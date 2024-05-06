/*
 * \file UARTConfiguration.c
 * This is a source file for the UARTConfiguration module.
 *
 * Copyright 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define _DEFAULT_SOURCE

#include "UARTConfiguration.h"
#include <stdlib.h>


void setDefaultLineConfig(UARTLineConfig *config)
{
    config->baudrate = BR115200;
    config->byteSize = EIGHTBITS;
    config->stopBits = ONE_STOPBIT;
    config->parity = NO_PARITY;
    config->handleDSRControl = 0;
    config->handleDTRControl = ENABLEDTR;
    config->handleRTSControl = ENABLERTS;
    config->inX = 0;
    config->outCtsFlow = 1;
    config->outDsrFlow = 1;
    config->outX = 0;
    config->XonLim = 0x800;
    config->XoffLim = 0x200;
    config->dsrSensitivity = 0;
    config->abortOnError = 0;
}

void setDefaultTimeConfig(UARTTimeConfig *config)
{
    config->readTime = -1;
    config->readTimeMultiplier = 0;
    config->readTotalTime = 0;
    config->writeTime = 5000;
    config->writeTimeMultiplier = 0;
}

UARTConfigurationData *defaultConfigurationData(void)
{
    UARTConfigurationData *config = (UARTConfigurationData *) calloc (1, sizeof(UARTConfigurationData));
    if (config == NULL)
        return NULL;
    config->lineConfig = (UARTLineConfig *) calloc (1, sizeof(UARTLineConfig));
    setDefaultLineConfig(config->lineConfig);

    config->timeConfig = (UARTTimeConfig *) calloc (1, sizeof(UARTTimeConfig));
    setDefaultTimeConfig(config->timeConfig);

    return config;
}

void freeConfigurationData(UARTConfigurationData *config)
{
    free(config->lineConfig);
    free(config->timeConfig);
    free(config);
}

void setBaudrate(UARTConfigurationData *config, Baudrate br)
{
    config->lineConfig->baudrate = br;
}

void setParity(UARTConfigurationData *config, ParityType pt)
{
    config->lineConfig->parity = pt;
}

void disableFlowControl(UARTConfigurationData *config)
{
    config->lineConfig->handleDTRControl = DISABLEDTR;
    config->lineConfig->handleRTSControl = DISABLERTS;
    config->lineConfig->outCtsFlow = 0;
	config->lineConfig->outDsrFlow = 0;
}

#ifdef _WIN32

#include <Windows.h>

/*! *********************************************************************************
* \brief  Initialize the COMPORT with the baudrate and sets the communication timeouts.
*
* \param[in] device pointer to the UARTHandle structure
* \param[in] baudRate int for configuring the baudrate
*
* \return 0 in case of initialization failure, 1 otherwise
********************************************************************************** */
int InitPort(File portHandle, UARTConfigurationData *config)
{
    BOOL bRet;
    DCB dcbPortSettings;
    COMMTIMEOUTS ctTimeouts;

    bRet = SetCommMask(portHandle, EV_RXCHAR);
    if (bRet == FALSE) {
        return FALSE;
    }

    memset(&dcbPortSettings, 0, sizeof(dcbPortSettings));
    dcbPortSettings.DCBlength = sizeof(dcbPortSettings);


    switch (config->lineConfig->baudrate) {
        case BR110:
            dcbPortSettings.BaudRate = 110;
            break;
        case BR300:
            dcbPortSettings.BaudRate = 300;
            break;
        case BR600:
            dcbPortSettings.BaudRate = 600;
            break;
        case BR1200:
            dcbPortSettings.BaudRate = 1200;
            break;
        case BR2400:
            dcbPortSettings.BaudRate = 2400;
            break;
        case BR4800:
            dcbPortSettings.BaudRate = 4800;
            break;
        case BR9600:
            dcbPortSettings.BaudRate = 9600;
            break;
        case BR19200:
            dcbPortSettings.BaudRate = 19200;
            break;
        case BR38400:
            dcbPortSettings.BaudRate = 38400;
            break;
        case BR57600:
            dcbPortSettings.BaudRate = 57600;
            break;
        case BR115200:
            dcbPortSettings.BaudRate = 115200;
            break;
        case BR921600:
            dcbPortSettings.BaudRate = 921600;
            break;
		case BR1000000:
			dcbPortSettings.BaudRate = 1000000;
			break;
        default:
            return FALSE;
    }

    switch (config->lineConfig->byteSize) {
        case FIVEBITS:
            dcbPortSettings.ByteSize = 5;
            break;
        case SIXBITS:
            dcbPortSettings.ByteSize = 6;
            break;
        case SEVENBITS:
            dcbPortSettings.ByteSize = 7;
            break;
        case EIGHTBITS:
            dcbPortSettings.ByteSize = 8;
            break;
        default:
            return FALSE;
    }

    switch (config->lineConfig->stopBits) {
        case ONE_STOPBIT:
            dcbPortSettings.StopBits = ONESTOPBIT;
            break;
        case ONE_HALF_STOPBITS:
            dcbPortSettings.StopBits = ONE5STOPBITS;
            break;
        case TWO_STOPBITS:
            dcbPortSettings.StopBits = TWOSTOPBITS;
            break;
        default:
            return FALSE;
    }

    switch (config->lineConfig->parity) {
        case NO_PARITY:
            dcbPortSettings.fParity = FALSE;
            dcbPortSettings.Parity = NOPARITY;
            break;

        case ODD_PARITY:
            dcbPortSettings.fParity = TRUE;
            dcbPortSettings.Parity = ODDPARITY;
            break;

        case EVEN_PARITY:
            dcbPortSettings.fParity = TRUE;
            dcbPortSettings.Parity = EVENPARITY;
            break;

        case MARK_PARITY:
            dcbPortSettings.fParity = TRUE;
            dcbPortSettings.Parity = MARKPARITY;
            break;

        case SPACE_PARITY:
            dcbPortSettings.fParity = TRUE;
            dcbPortSettings.Parity = SPACEPARITY;
            break;

        default:
            return FALSE;
    }

    switch (config->lineConfig->handleRTSControl) {
        case DISABLERTS:
            dcbPortSettings.fRtsControl = RTS_CONTROL_DISABLE;
            break;
        case ENABLERTS:
            dcbPortSettings.fRtsControl = RTS_CONTROL_ENABLE;
            break;
        case RTSHANDSHAKE:
            dcbPortSettings.fRtsControl = RTS_CONTROL_HANDSHAKE;
            break;
        case RTSTOGGLE:
            dcbPortSettings.fRtsControl = RTS_CONTROL_TOGGLE;
            break;
        default:
            return FALSE;
    }

    switch (config->lineConfig->handleDTRControl) {
        case DISABLEDTR:
            dcbPortSettings.fDtrControl = DTR_CONTROL_DISABLE;
            break;

        case ENABLEDTR:
            dcbPortSettings.fDtrControl = DTR_CONTROL_ENABLE;
            break;

        case DTRHANDSHAKE:
            dcbPortSettings.fDtrControl = DTR_CONTROL_HANDSHAKE;
            break;

        default:
            return FALSE;
    }

    dcbPortSettings.fBinary = TRUE;

    dcbPortSettings.fOutxCtsFlow = config->lineConfig->outCtsFlow;
    dcbPortSettings.fOutxDsrFlow = config->lineConfig->outDsrFlow;
    dcbPortSettings.fTXContinueOnXoff = TRUE;

    dcbPortSettings.fOutX = config->lineConfig->outX;
    dcbPortSettings.fInX = config->lineConfig->inX;
    dcbPortSettings.fDsrSensitivity = config->lineConfig->dsrSensitivity;
    dcbPortSettings.fAbortOnError = config->lineConfig->abortOnError;

    dcbPortSettings.XonLim = config->lineConfig->XonLim;
    dcbPortSettings.XoffLim = config->lineConfig->XoffLim;
    dcbPortSettings.XonChar = 0x11;
    dcbPortSettings.XoffChar = 0x13;
    dcbPortSettings.ErrorChar = 0x00;
    dcbPortSettings.EofChar = 0x00;
    dcbPortSettings.EvtChar = 0x00;

    bRet = SetCommState(portHandle, &dcbPortSettings);

    if (bRet == FALSE) {
        return FALSE;
    }

    ctTimeouts.ReadIntervalTimeout = config->timeConfig->readTime;
    ctTimeouts.ReadTotalTimeoutMultiplier = config->timeConfig->readTimeMultiplier;
    ctTimeouts.ReadTotalTimeoutConstant = config->timeConfig->readTotalTime;
    ctTimeouts.WriteTotalTimeoutMultiplier = config->timeConfig->writeTimeMultiplier;
    ctTimeouts.WriteTotalTimeoutConstant = config->timeConfig->writeTime;

    bRet = SetCommTimeouts(portHandle, &ctTimeouts);

    if (bRet == FALSE) {
        return FALSE;
    }

    return TRUE;
}

#elif __linux__ || __APPLE__

#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>

/*! *********************************************************************************
* \brief  Initialize the COMPORT with the baudrate and sets the communication timeouts.
*
* \param[in] device pointer to the UARTHandle structure
* \param[in] baudRate int for configuring the baudrate
*
* \return 0 in case of initialization failure, 1 otherwise
********************************************************************************** */
int InitPort(File portHandle, UARTConfigurationData *config)
{
    int rc = 0, argp = 0;
    struct termios newtio;

    memset(&newtio, 0, sizeof(struct termios));

    newtio.c_cflag = CLOCAL | CREAD;
    newtio.c_iflag = 0;
    newtio.c_oflag = 0;

    newtio.c_cc[VMIN] = 1;
    newtio.c_cc[VTIME] = (unsigned int) config->timeConfig->readTime;

    if (config->lineConfig->inX)
        newtio.c_iflag |= IXOFF;

    if (config->lineConfig->outX)
        newtio.c_iflag |= IXON;

    switch (config->lineConfig->baudrate) {
        case BR110:
            rc = cfsetspeed(&newtio, B110);
            break;
        case BR300:
            rc = cfsetspeed(&newtio, B300);
            break;
        case BR600:
            rc = cfsetspeed(&newtio, B600);
            break;
        case BR1200:
            rc = cfsetspeed(&newtio, B1200);
            break;
        case BR2400:
            rc = cfsetspeed(&newtio, B2400);
            break;
        case BR4800:
            rc = cfsetspeed(&newtio, B4800);
            break;
        case BR9600:
            rc = cfsetspeed(&newtio, B9600);
            break;
        case BR19200:
            rc = cfsetspeed(&newtio, B19200);
            break;
        case BR38400:
            rc = cfsetspeed(&newtio, B38400);
            break;
        case BR57600:
            rc = cfsetspeed(&newtio, B57600);
            break;
        case BR115200:
            rc = cfsetspeed(&newtio, B115200);
            break;
        case BR921600:
#define B921600 0010007 /* OS X does not have a define for this baudrate. */
            rc = cfsetspeed(&newtio, B921600);
            break;
        case BR1000000:
#define B1000000 0010010 /* OS X does not have a define for this baudrate. */
            rc = cfsetspeed(&newtio, B1000000);
            break;
    }

    if (rc == -1) {
        perror("InitPort cfsetspeed");
    }

    switch (config->lineConfig->byteSize) {
        case FIVEBITS:
            newtio.c_cflag |= CS5;
            break;
        case SIXBITS:
            newtio.c_cflag |= CS6;
            break;
        case SEVENBITS:
            newtio.c_cflag |= CS7;
            break;
        case EIGHTBITS:
            newtio.c_cflag |= CS8;
            break;
        default:
            return 0;
    }

    switch (config->lineConfig->parity) {
        case NO_PARITY:
            newtio.c_iflag |= IGNPAR;
            break;
        case ODD_PARITY:
            newtio.c_cflag |= PARENB | PARODD;
            break;
        case EVEN_PARITY:
            newtio.c_cflag |= PARENB;
            break;
        default:
            return 0;
    }

    switch (config->lineConfig->stopBits) {
        case ONE_STOPBIT:
            break;
        case TWO_STOPBITS:
            newtio.c_cflag |= CSTOPB;
            break;
        default:
            return 0;
    }

    rc = tcflush(portHandle, TCIFLUSH);
    if (rc == -1) {
        perror("InitPort tcflush");
    }

    rc = tcsetattr(portHandle, TCSANOW, &newtio);
    if (rc == -1) {
        perror("InitPort tcsetattr");
        return -1;
    }

    rc = ioctl(portHandle, TIOCMGET, &argp);
    if (rc == -1) {
        perror("InitPort ioctl(portHandle, TIOCMGET, &argp)");
        return -1;
    }

    switch (config->lineConfig->handleRTSControl) {
        case DISABLERTS:
            argp &= ~TIOCM_RTS;
            break;
        case ENABLERTS:
            argp |= TIOCM_RTS;
            break;
        default:
            return 0;
    }

    switch (config->lineConfig->handleDTRControl) {
        case DISABLEDTR:
            argp &= ~TIOCM_DTR;
            break;
        case ENABLEDTR:
            argp |= TIOCM_DTR;
            break;
        default:
            return 0;
    }

    rc = ioctl(portHandle, TIOCMSET, &argp);
    if (rc == -1) {
        perror("InitPort ioctl(portHandle, TIOCMSET, &argp)");
        return -1;
    }

    return 0;
}

#endif
