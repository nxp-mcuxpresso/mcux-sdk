/*
 * \file hsdkFile.c
 * This is a source file for the OS abstraction file handling module.
 *
 * Copyright 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "hsdkOSCommon.h"
#include "hsdkLogger.h"

#define DEBUG 0
#define USE_AIO 0


void printBuffer(const char *tag, uint8_t *buff, int size)
{
#if DEBUG
    int i;
    printf("%s: ", tag);

    for (i = 0; i < size; i++) {
        fprintf(stdout, "%02X ", buff[i]);
    }

    fprintf(stdout, "\n");
#endif
}


#ifdef _WIN32

typedef struct {
    OVERLAPPED ov;
    uint8_t *buffer;
} AsyncPiggyBacking;

#if USE_AIO
static VOID CALLBACK CompletionRoutine(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped)
{
    AsyncPiggyBacking *elem = (AsyncPiggyBacking *) lpOverlapped;
    printBuffer("AIO CompletionRoutine", elem->buffer, dwNumberOfBytesTransfered);
    free(elem->buffer);
    free(elem);
}
#endif

File HSDKOpenFile(char *filename)
{
    File f = CreateFile(filename,
                        GENERIC_READ | GENERIC_WRITE,
                        0,
                        NULL,
                        OPEN_EXISTING,
                        FILE_FLAG_OVERLAPPED,
                        NULL
                       );

    if (f == INVALID_HANDLE_VALUE) {
        logMessage(HSDK_ERROR, "[hsdkFile]HSDKOpenFile", "Failed to open file", HSDKThreadId());
    }

    return f;
}

int HSDKCloseFile(File f)
{
    BOOL b = FlushFileBuffers(f);

    if (!b) {
        logMessage(HSDK_ERROR, "[hsdkFile]HSDKCloseFile", "Failed to flush file buffers", HSDKThreadId());
    }

    b = CloseHandle(f);

    if (b) {
        return ERROR_SUCCESS;
    } else {
        DWORD err = GetLastError();
        logMessage(HSDK_ERROR, "[hsdkFile]HSDKCloseFile", "Failed to close event", HSDKThreadId());
        return (int)err;
    }
}

int HSDKWriteFile(File file, uint8_t *buffer, uint32_t count)
{
    printBuffer("TX", buffer, count);

#if USE_AIO
    DWORD err;
    AsyncPiggyBacking *elem = (AsyncPiggyBacking *) calloc(1, sizeof(AsyncPiggyBacking));

    if (elem == NULL) {
        err = GetLastError();
        return (int)err;
    }

    memset(&elem->ov, 0, sizeof(OVERLAPPED));
    elem->buffer = buffer;

    WriteFileEx(file, buffer, count, (LPOVERLAPPED)elem, CompletionRoutine);
    err = GetLastError();

    if (err != ERROR_SUCCESS && err != ERROR_IO_PENDING) {
        logMessage(HSDK_ERROR, "[hsdkFile]HSDKWriteFile", "Failed to write data", HSDKThreadId());
        return err;
    }

    return 0;
#else
    BOOL bRet;
    DWORD dwBytesRead, dwErr;
    OVERLAPPED ov;
    HANDLE hEvent;

    ZeroMemory(&ov, sizeof(ov));
    hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    ov.hEvent = hEvent;

    bRet = WriteFile(
               file,
               buffer,
               count,
               &dwBytesRead,
               &ov);

    if (bRet == FALSE) {
        dwErr = GetLastError();

        if (dwErr == ERROR_IO_PENDING) {
            if (ov.hEvent == NULL) {
                logMessage(HSDK_ERROR, "[hsdkFile]HSDKWriteFile", "Failed to write data, overlapped event is NULL", HSDKThreadId());
                return (int)dwErr;
            }

            WaitForSingleObject(ov.hEvent, INFINITE);
            GetOverlappedResult(ov.hEvent, &ov, &dwBytesRead, TRUE);
            CloseHandle(hEvent);
            return ERROR_SUCCESS;
        }

        logMessage(HSDK_ERROR, "[hsdkFile]HSDKWriteFile", "Failed to write data", HSDKThreadId());
        return (int)dwErr;
    } else {
        return ERROR_SUCCESS;
    }

#endif
}

int HSDKReadFile(File file, uint8_t *buffer, uint32_t *count)
{
    OVERLAPPED ov;
    ZeroMemory(&ov, sizeof(OVERLAPPED));
    ov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    memset(buffer, 0, *count);

    DWORD dwBytesRead = 0;
    BOOL ret;

    ret = ReadFile(file, buffer, *count, &dwBytesRead, &ov);
    printBuffer("RX", buffer, dwBytesRead);

    if (ret == FALSE) {
        DWORD dwErr = GetLastError();

        if (dwErr == ERROR_IO_PENDING) {
            WaitForSingleObject(ov.hEvent, INFINITE);
            GetOverlappedResult(file, &ov, &dwBytesRead, TRUE);
        } else {
            CloseHandle(ov.hEvent);
            logMessage(HSDK_ERROR, "[hsdkFile]HSDKReadFile", "Failed to read data", HSDKThreadId());
            *count = 0;
            return (int)dwErr;
        }
    }

    CloseHandle(ov.hEvent);
    *count = dwBytesRead;
    return ERROR_SUCCESS;
}

int HSDKIsDescriptorValid(File f)
{
    return f != INVALID_HANDLE_VALUE;
}

void HSDKInvalidateDescriptor(File *f)
{
    *f = INVALID_HANDLE_VALUE;
}


#elif __linux__ || __APPLE__

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>

#if USE_AIO
#include <aio.h>

static void AIOCompletionCallback(sigval_t sigval)
{
    int ret;
    struct aiocb *req;

    req = (struct aiocb *)sigval.sival_ptr;

    /* Did the request complete? */
    if (aio_error(req) == 0) {
        /* Request completed successfully, get the return status */
        ret = aio_return(req);
    }

    free((void *)(req->aio_buf));
    memset(req, 0, sizeof(struct aiocb));
    free(req);

    return;
}

#endif

File HSDKOpenFile(char *filename)
{
    int rc = open(filename, O_RDWR | O_NOCTTY);

    if (rc == -1) {
        perror(filename);
        logMessage(HSDK_ERROR, "[HSDKOpenFile] open", strerror(errno), HSDKThreadId());
    }

    return rc;
}

int HSDKCloseFile(File f)
{
    int rc = close(f);

    if (rc == -1) {
        perror("HSDKCloseFile close");
        logMessage(HSDK_ERROR, "[HSDKCloseFile] close", strerror(errno), HSDKThreadId());
    }

    return rc;
}

int HSDKWriteFile(File file, uint8_t *buffer, uint32_t count)
{
    int rc = 0;
    printBuffer("TX", buffer, count);

#if USE_AIO
    struct aiocb *writeControlBlock = (struct aiocb *) calloc(1, sizeof(struct aiocb));

    writeControlBlock->aio_fildes = file;
    writeControlBlock->aio_offset = 0;
    writeControlBlock->aio_buf = buffer;
    writeControlBlock->aio_nbytes = count;

    writeControlBlock->aio_sigevent.sigev_notify = SIGEV_THREAD;
    writeControlBlock->aio_sigevent.sigev_notify_function = AIOCompletionCallback;
    writeControlBlock->aio_sigevent.sigev_notify_attributes = NULL;
    writeControlBlock->aio_sigevent.sigev_value.sival_ptr = writeControlBlock;

    rc = aio_write(writeControlBlock);
#else
    rc = write(file, buffer, count);
#endif

    if (rc == -1) {
        perror("HSDKWriteFile write");
        logMessage(HSDK_ERROR, "[HSDKWriteFile] write", strerror(errno), HSDKThreadId());
    }

    return rc;
}

int HSDKReadFile(File file, uint8_t *buffer, uint32_t *count)
{
    int rc = read(file, buffer, *count);

    if (rc == -1) {
        logMessage(HSDK_ERROR, "[HSDKReadFile] read", strerror(errno), HSDKThreadId());
        *count = 0;
        return rc;
    } else {
        *count = rc;
        printBuffer("RX", buffer, rc);
        return 0;
    }
}

int HSDKIsDescriptorValid(File f)
{
    return f != -1;
}

void HSDKInvalidateDescriptor(File *f)
{
    *f = -1;
}

#endif
