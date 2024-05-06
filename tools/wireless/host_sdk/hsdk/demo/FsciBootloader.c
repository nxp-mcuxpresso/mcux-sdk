/*
 * \file FsciBootloader.c
 * Source file that implements the host side of the FSCI bootloader.
 *
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "Framer.h"
#include "FSCIFrame.h"
#include "hsdkError.h"
#include "hsdkOSCommon.h"
#include "PhysicalDevice.h"
#ifdef __linux__spi__
#include "SPIConfiguration.h"
#endif
#include "UARTConfiguration.h"
#include "utils.h"

#define TRUE 1
#define FALSE 0

#define LENGTH_FIELD_SIZE 2
#define CRC_FIELD_SIZE 1
#define SECTOR_SIZE 2048  // sector size KW41Z
#define SPI_SPEED 2000000
#define UART_BAUDRATE BR115200
#define DEFAULT_CHUNK_LEN SECTOR_SIZE
#define DEFAULT_WAIT_TIME 3000  // milliseconds
#define KW_NVM_SECTOR_START ((0x0006F800 / SECTOR_SIZE) - 1)
#define KW_NVM_SECTOR_END   ((0x0007F7FF / SECTOR_SIZE) - 1)

static int fsci_cpu_reset(Framer *framer);
static int fsci_enter_bootloader(Framer *framer);
static int fsci_firmware_cancel_process(Framer *framer);
static int fsci_firmware_start_image(Framer *framer, uint32_t size);
static int fsci_firmware_push_image_chunk(Framer *framer, uint8_t *data, uint32_t size);
static int fsci_firmware_commit_image(Framer *framer, uint8_t *bitmask, uint16_t crc);

static void read_image(char *imagePath, uint8_t **fileData, uint32_t *file_size);
static void flash_image(Framer *framer, uint8_t *fileData, uint32_t file_size, uint8_t erase_nvm);
static uint8_t *bitmask_computation(uint8_t erase_nvm);
static uint16_t crc_computation(uint8_t *file, uint32_t file_size);
static void Usage();

// global variable to store the RX confirm status
static uint8_t confirm_status_success = FALSE;
// global variable to store the information about external memory
static uint8_t external_memory_suport = FALSE;
// global synchronization variable
static Event rx_notification;
// global variable to store a possible error status of FSCIFirmware_CommitImageConfirm
static uint8_t error_commit_image_confirm = 0;
// global to store number of bytes sent
static uint32_t bytes_sent = 0;
// global to store the number of sent packets
static uint32_t seq_no = 0;
// global to store CRC check state
static uint8_t disable_crc = FALSE;
// store the chunk size for the fsci_firmware_push_image_chunk
static uint32_t chunk_len = 0;

/*
 * Executes on every RX packet.
 */
void callback(void *callee, void *response)
{
    FSCIFrame *frame = (FSCIFrame *)response;
    if ((frame->opGroup == 0xA4) && (frame->opCode == 0x2C)) {
        // confirm from FSCIEnterBootloaderRequest
        if (frame->data[0] == 0x00) {
            confirm_status_success = TRUE;
        } else {
            confirm_status_success = FALSE;
        }
        HSDKSignalEvent(rx_notification);
    } else if ((frame->opGroup == 0xA4) && (frame->opCode == 0x29)) {
        // confirm from FSCIFirmware_StartImage_Confirm
        if (frame->data[0] == 0x00) {
            confirm_status_success = TRUE;
        } else {
            confirm_status_success = FALSE;
        }
        if (frame->data[2] == 0x01) {
            external_memory_suport = TRUE;
        } else {
            external_memory_suport = FALSE;
        }
        HSDKSignalEvent(rx_notification);
    } else if ((frame->opGroup == 0xA4) && (frame->opCode == 0x2A)) {
        // confirm from FSCIFirmware_PushImageChunk_Confirm
        if (frame->data[0] == 0x00) {
            confirm_status_success = TRUE;
            bytes_sent += chunk_len;
            seq_no += 1;
        } else {
            confirm_status_success = FALSE;
        }
        HSDKSignalEvent(rx_notification);
    } else if ((frame->opGroup == 0xA4) && (frame->opCode == 0x2B)) {
        // confirm from FSCIFirmware_CommitImageConfirm
        if (frame->data[0] == 0x00) {
            confirm_status_success = TRUE;
        } else {
            confirm_status_success = FALSE;
            error_commit_image_confirm = frame->data[0];
        }
        HSDKSignalEvent(rx_notification);
    }
    DestroyFSCIFrame(frame);
}

uint16_t crc_computation(uint8_t *file, uint32_t file_size)
{
    uint16_t CRC16_XMODEM_TABLE[] = {
        0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
        0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
        0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
        0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
        0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
        0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
        0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
        0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
        0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
        0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
        0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
        0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
        0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
        0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
        0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
        0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
        0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
        0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
        0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
        0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
        0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
        0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
        0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
        0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
        0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
        0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
        0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
        0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
        0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
        0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
        0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
        0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0,
    };
    uint16_t crc = 0;
    uint32_t i;
    for (i = 0; i < file_size; ++i) {
        crc = ((crc << 8) & 0xff00) ^ CRC16_XMODEM_TABLE[((crc >> 8) & 0xff) ^ file[i]];
    }
    return crc & 0xffff;
}

uint8_t *bitmask_computation(uint8_t erase_nvm)
{
    uint8_t *buffer = (uint8_t *)calloc(32, sizeof(uint8_t));
    if (buffer == NULL) {
        printf("Memory allocation failed");
        printf("Unable to alloc 32 bytes for the bit mask");
        exit(EXIT_FAILURE);
    }

    if (erase_nvm) {
        int sector_start = (KW_NVM_SECTOR_START) / 8;
        int sector_end = (KW_NVM_SECTOR_END) / 8;

        int i;
        for (i = sector_start + 1; i < sector_end; ++i) {
            buffer[i] = 0xff;
        }

        int mod_sector_start = (KW_NVM_SECTOR_START) % 8;
        int mod_sector_end = (KW_NVM_SECTOR_END) % 8;
        switch (mod_sector_start) {
            case 1:
                buffer[sector_start] = 0x7f;
                break;
            case 2:
                buffer[sector_start] = 0x3f;
                break;
            case 3:
                buffer[sector_start] = 0x1f;
                break;
            case 4:
                buffer[sector_start] = 0x0f;
                break;
            case 5:
                buffer[sector_start] = 0x07;
                break;
            case 6:
                buffer[sector_start] = 0x03;
                break;
            case 7:
                buffer[sector_start] = 0x01;
                break;
        }

        switch (mod_sector_end) {
            case 0:
                buffer[sector_end] = 0x80;
                break;
            case 1:
                buffer[sector_end] = 0xc0;
                break;
            case 2:
                buffer[sector_end] = 0xe0;
                break;
            case 3:
                buffer[sector_end] = 0xf0;
                break;
            case 4:
                buffer[sector_end] = 0xf8;
                break;
            case 5:
                buffer[sector_end] = 0xfc;
                break;
            case 6:
                buffer[sector_end] = 0xfe;
                break;
            case 7:
                buffer[sector_end] = 0xff;
                break;
        }
    }

    return buffer;
}

void read_image(char *imagePath, uint8_t **fileData, uint32_t *file_size)
{
    // open file
    FILE *ptr = fopen(imagePath, "rb");
    if (!ptr) {
        printf("%s does not exist or is inaccessible.\n", imagePath);
    }

    // read the length of the file
    fseek(ptr, 0L, SEEK_END);
    *file_size = ftell(ptr);
    fseek(ptr, 0L, SEEK_SET);

    // read the contents
    *fileData = (uint8_t *)calloc(*file_size, sizeof(uint8_t));
    if (*fileData == NULL) {
        printf("Memory allocation failed");
        printf("Unable to alloc %d bytes for the image file", *file_size);
        exit(EXIT_FAILURE);
    }

    size_t res = fread(*fileData, *file_size, 1, ptr);
    if (res <= 0) {
        printf("Error reading from file.\n");
        printf("%zu\n", res);
    }

    // remove useless 0xFFs at the end
    uint32_t i = 0, last_ff_position = -1;
    for (i = (*file_size - 1); i >= 0; --i) {
        if ((*fileData)[i] == 0xFF) {
            last_ff_position = i;
        } else {
            break;
        }
    }
    if (last_ff_position != -1) {
        // fill last sector so it can be erased
        if ((last_ff_position % SECTOR_SIZE) != 0) {
            last_ff_position += SECTOR_SIZE - (last_ff_position % SECTOR_SIZE);
        }
        *file_size = last_ff_position;
        *fileData = (uint8_t *)realloc(*fileData, (*file_size) * sizeof(uint8_t));
        if (*fileData == NULL) {
            printf("Memory reallocation failed");
            printf("Unable to realloc %d bytes for the image file", *file_size);
            exit(EXIT_FAILURE);
        }
    }
}

void flash_image(Framer *framer, uint8_t *fileData, uint32_t file_size, uint8_t erase_nvm)
{
    uint32_t size_data_to_send = 0;
    uint8_t *data_to_send = NULL;
    time_t start, stop;

    fsci_enter_bootloader(framer);

    fsci_firmware_cancel_process(framer);
    int rc = HSDKWaitEvent(rx_notification, DEFAULT_WAIT_TIME);
    if ((rc <= 0) || ((rc == 1) && (confirm_status_success == FALSE))) {
        printf("%s\n", "Cannot communicate with the board, please try again. Exiting..");
        exit(EXIT_FAILURE);
    }

    confirm_status_success = FALSE;

    fsci_firmware_start_image(framer, file_size);
    rc = HSDKWaitEvent(rx_notification, DEFAULT_WAIT_TIME);
    if ((rc <= 0) || ((rc == 1) && (confirm_status_success == FALSE))) {
        printf("%s\n", "Start Image Failed");
        exit(EXIT_FAILURE);
    }
    confirm_status_success = FALSE;

    // verify if board has external memory support
    if (external_memory_suport == FALSE) {
        printf("Failed. Board doesn't have external memory support.\n");
        exit(EXIT_FAILURE);
    }

    printf("Start writing image on board\n");
    data_to_send = (uint8_t *)calloc(chunk_len + 1, sizeof(uint8_t));  // +1 for sequence number
    if (data_to_send == NULL) {
        printf("Memory allocation failed\n");
        printf("Unable to alloc %d bytes for fsci_firmware_push_image_chunk", size_data_to_send);
        exit(EXIT_FAILURE);
    }

    time(&start);
    // start writing image
    while (bytes_sent < file_size) {
        if ((file_size - bytes_sent) >= chunk_len) {
            size_data_to_send = chunk_len + 1;
        } else {
            size_data_to_send = (file_size - bytes_sent) + 1;
        }
        data_to_send[0] = seq_no;
        memcpy(data_to_send + 1, fileData + bytes_sent, size_data_to_send);

        fsci_firmware_push_image_chunk(framer, data_to_send, size_data_to_send);
        HSDKWaitEvent(rx_notification, DEFAULT_WAIT_TIME);
        printf("\rProgress: %3.2f%s", ((100 * (double)bytes_sent) / (double)file_size), "%");

        fflush(stdout);
    }
    time(&stop);

    free(data_to_send);
    printf("\rProgress: 100%s                     ", "%");
    printf("\nAll chunks sent in %.0f seconds\n", difftime(stop, start));

    uint8_t *bitmask = bitmask_computation(erase_nvm);
    fsci_firmware_commit_image(framer, bitmask, crc_computation(fileData, file_size));
    free(bitmask);
    rc = HSDKWaitEvent(rx_notification, DEFAULT_WAIT_TIME);
    if (rc <= 0) {
        printf("%s\n", "Commit image Failed");
        exit(EXIT_FAILURE);
    } else if ((rc == 1) && (confirm_status_success == FALSE)) {
        if (error_commit_image_confirm == 0x04) {
            if (disable_crc == TRUE) {
                printf("[FAILED] Bootloader has gFsciUseCRC_c = TRUE;");
                printf("please enable the CRC check by removing -d\n");
            } else {
                printf("[FAILED] CRC validation failed.\n");
            }
        } else {
            printf("[FAILED] Something went wrong. Commit image return status is %d\n", error_commit_image_confirm);
        }
    } else if ((rc == 1) && (confirm_status_success == TRUE)) {
        printf("Commit image completed \n");
    }

    fsci_cpu_reset(framer);
}

int fsci_enter_bootloader(Framer *framer)
{
    FSCIFrame *temp_frame = CreateFSCIFrame(framer, 0xA3, 0xCF, NULL, 0, 0);
    int return_value = SendFrame(framer, temp_frame);
    sleep(1);
    free(temp_frame);
    return return_value;
}

int fsci_firmware_cancel_process(Framer *framer)
{
    FSCIFrame *temp_frame = CreateFSCIFrame(framer, 0xA3, 0x2C, NULL, 0, 0);
    int return_value = SendFrame(framer, temp_frame);
    free(temp_frame);
    return return_value;
}

int fsci_firmware_start_image(Framer *framer, uint32_t size)
{
    uint8_t *buffer = (uint8_t *)calloc(4, sizeof(uint8_t));
    if (buffer == NULL) {
        printf("Memory allocation failed");
        printf("Unable to alloc 4 bytes for fsci_firmware_start_image");
        exit(EXIT_FAILURE);
    }

    Store32(size, buffer, _LITTLE_ENDIAN);
    FSCIFrame *temp_frame = CreateFSCIFrame(framer, 0xA3, 0x29, buffer, 4, 0);
    free(buffer);
    int return_value = SendFrame(framer, temp_frame);
    free(temp_frame);
    return return_value;
}

int fsci_firmware_push_image_chunk(Framer *framer, uint8_t *data, uint32_t size)
{
    FSCIFrame *temp_frame = CreateFSCIFrame(framer, 0xA3, 0x2A, data, size, 0);
    int return_value = SendFrame(framer, temp_frame);
    free(temp_frame);
    return return_value;
}

int fsci_firmware_commit_image(Framer *framer, uint8_t *bitmask, uint16_t crc)
{
    uint8_t *buffer = (uint8_t *)calloc(34, sizeof(uint8_t));
    if (buffer == NULL) {
        printf("Memory allocation failed");
        printf("Unable to alloc 34 bytes for fsci_firmware_commit_image");
        exit(EXIT_FAILURE);
    }
    memcpy(buffer, bitmask, 32);
    Store16(crc, buffer + 32, _LITTLE_ENDIAN);
    FSCIFrame *temp_frame = CreateFSCIFrame(framer, 0xA3, 0x2B, buffer, 34, 0);
    int return_value = SendFrame(framer, temp_frame);
    free(temp_frame);
    free(buffer);
    return return_value;
}

int fsci_cpu_reset(Framer *framer)
{
    FSCIFrame *temp_frame = CreateFSCIFrame(framer, 0xA3, 0x08, NULL, 0, 0);
    int return_value = SendFrame(framer, temp_frame);
    free(temp_frame);
    return return_value;
}

void Usage()
{
    printf("Usage: # ./FsciBootloader serial_port binary_file [-e] [-d] [-s value]\n");
    printf("\tserial_port - Kinetis-W system device node.\n");
#ifndef __linux__spi__
    printf("\t\tWARNING: SPI device node support is disabled.\n");
#endif
    printf("\tbinary_file - The binary file to be written.\n");
    printf("\t-e - Erase the non-volatile memory.\n");
    printf("\t-d - Disable the CRC check on commit image.\n");
    printf("\t-s - Push chunks this large (in bytes). Defaults to 2048, Max 2048.\n");
}

int main(int argc, char **argv)
{
    uint8_t *fileData = NULL;
    uint32_t file_size = 0;
    uint8_t erase_nvm = FALSE;
    char *imagePath;
    char *serial_port;
    rx_notification = HSDKCreateEvent(0);
#ifdef __linux__spi__
    char *spi = "spi";
#endif
    PhysicalDevice *device = NULL;
    void *config = NULL;

    if (argc < 3) {
        Usage();
        exit(EXIT_FAILURE);
    }

    serial_port = argv[1];
    imagePath = argv[2];

    int opt;
    while ((opt = getopt(argc, argv, "eds:")) != -1) {
        switch (opt) {
            case 'e': erase_nvm = TRUE; break;
            case 'd': disable_crc = TRUE; break;
            case 's': chunk_len = atoi(optarg); break;
            default:
                Usage();
                exit(EXIT_FAILURE);
        }
    }

    if (chunk_len == 0) {
        chunk_len = DEFAULT_CHUNK_LEN;
    }

    if (chunk_len > SECTOR_SIZE) {
        printf("Chunk size %d is too large! Maximum allowed is 2048.\n", chunk_len);
        exit(EXIT_FAILURE);
    }

    // read image
    read_image(imagePath, &fileData, &file_size);

#ifdef __linux__spi__
    // verify if port is SPI
    if (strstr(serial_port, spi) != NULL) {
        config = defaultSettingsSPI();
        setSpeedHzSPI(config, SPI_SPEED);
        device = InitPhysicalDevice(SPI, config, serial_port, GLOBAL);
    } else
#endif
    {
        config = defaultConfigurationData();
        setBaudrate(config, UART_BAUDRATE);
        device = InitPhysicalDevice(UART, config, serial_port, GLOBAL);
    }

    // open device
    Framer *framer = InitializeFramer(device, FSCI, LENGTH_FIELD_SIZE, CRC_FIELD_SIZE, _LITTLE_ENDIAN);
    int rc = OpenPhysicalDevice(device);
    if (rc != HSDK_ERROR_SUCCESS) {
        printf("Error opening device \n");
        exit(EXIT_FAILURE);
    }
    AttachToFramer(framer, device, callback);

    // write image
    flash_image(framer, fileData, file_size, erase_nvm);

    // close
    DetachFromFramer(framer, device);
    DestroyFramer(framer);
    DestroyPhysicalDevice(device);
    free(config);
    HSDKDestroyEvent(rx_notification);

    return 0;
}
