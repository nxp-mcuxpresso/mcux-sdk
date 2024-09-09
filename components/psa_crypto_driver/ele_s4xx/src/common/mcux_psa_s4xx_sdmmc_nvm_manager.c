/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <string.h>

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"

#include "ff.h"
#include "diskio.h"
#include "fsl_sd_disk.h"
#include "sdmmc_config.h"

#include "ele_nvm_manager.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

static int create_dir(char *dir_path)
{
    FRESULT error;

    error = f_mkdir(_T(dir_path));
    if (error) {
        /* The directory may already exist, that is not an error */
        if (error != FR_EXIST) {
            return -1;
        }
    }
    return 0;
}

/* Create the filepath of chunk associated with blob_id_msb, blob_id_lsb and blob_ext */
static int get_chunk_file_path(
    char *path, uint8_t path_buf_sz, char *nvm_storage_dname,
    uint32_t blob_id_msb, uint32_t blob_id_lsb, uint32_t blob_ext,
    bool create_path)
{
    uint8_t path_len = 0;
    int err = -1;
    char *path_current = path;
    char *path_end = NULL;

    /* 1 extra byte in path_len is for accommodating null termination char
     * \0 in path string.Since fatfs is not enabled with Long file system
     * names (LFS) due to space limitation, we are only using blob_id_lsb as filename
     * and rest of the unique values like blob_id_msb and lsb are used in the file path.
     * Chunk file path will be named <blob_ext> and the path will be
     * <nvm_storage_dname>/blob_ext/blob_id_msb/blob_id_lsb
     */
    path_len = strlen(nvm_storage_dname) + 1 +  /* 1 additional byte for / after every name */
               sizeof(blob_id_msb) * 2 + 1 +
               sizeof(blob_id_lsb) * 2 + 1 +
               sizeof(blob_ext) * 2 + 1;
    if (path_buf_sz < path_len) {
        PRINTF("Insufficient size of path buffer \r\n");
        return -1;
    }

    path_end = path + path_len;	/* For keeping track of free space when appending to the path string */

    /* If path needs to be created, we need to check and add the required directories */
    if (create_path) {
	path_current += snprintf(path, path_len, "%s/%lx", nvm_storage_dname, blob_ext);
        err = create_dir(path);
        if (err) {
            return -1;
        }

        path_current += snprintf(path_current, path_end - path_current, "/%lx", blob_id_msb);
        err = create_dir(path);
        if (err) {
            return -1;
        }

	path_current += snprintf(path_current, path_end - path_current, "/%lx", blob_id_lsb);
    } else {
        snprintf(path, path_len - 1, "%s/%lx/%lx/%lx",
                 nvm_storage_dname,
                 blob_ext, blob_id_msb, blob_id_lsb);
    }

    return 0;
}

/* Create and write to a file identified by passed blob_id */
status_t sd_file_write(uint32_t blob_id_msb,
                       uint32_t blob_id_lsb,
                       uint32_t blob_ext,
                       uint32_t *chunk,
                       size_t chunk_sz)
{
    FRESULT error;
    static FIL g_fileObject; /* File object */
    char path[64];
    UINT bytesWritten;

    /* Get the filepath of chunk associated with blob ID and blob_ext. */
    if (get_chunk_file_path((char *) path, sizeof(path), "/ele_nvm",
                            blob_id_msb, blob_id_lsb, blob_ext, true)) {
        return kStatus_Fail;
    }

    error = f_open(&g_fileObject, path, (FA_WRITE | FA_READ | FA_CREATE_ALWAYS));
    if (error) {
        if (error != FR_EXIST) {
            return kStatus_Fail;
        }
    }

    error = f_write(&g_fileObject, chunk, chunk_sz, &bytesWritten);
    if ((error) || (bytesWritten != chunk_sz)) {
        return kStatus_Fail;
    }

    if (f_close(&g_fileObject)) {
        return kStatus_Fail;
    }

    return kStatus_Success;
}

uint32_t *sd_file_read(uint32_t blob_id_msb,
                       uint32_t blob_id_lsb,
                       uint32_t blob_id_ext,
                       uint32_t *chunk,
                       size_t *sz)
{
    FRESULT error;
    static FIL g_fileObject; /* File object */
    char path[64];
    uint32_t file_sz;
    uint32_t *buffer = NULL;
    UINT bytesRead;

    if (get_chunk_file_path((char *) path, sizeof(path), "/ele_nvm",
                            blob_id_msb, blob_id_lsb, blob_id_ext, false)) {
        return NULL;
    }

    error = f_open(&g_fileObject, path, (FA_READ));
    if (error) {
        if (error != FR_EXIST) {
            return NULL;
        }
    }


    /* Get the size of file associated with chunk */
    file_sz = f_size(&g_fileObject);

    /* If buffer for chunk is not passed, allocate based on sie of file */
    if (!chunk) {
        buffer = malloc(file_sz);
        *sz    = file_sz;
        chunk  = buffer;
    }

    if (!buffer || *sz < file_sz) {
        return NULL;
    }

    memset(chunk, 0U, *sz);
    /* Read the chunk data into buffer */
    error = f_read(&g_fileObject, chunk, *sz, &bytesRead);
    if ((error) || (bytesRead != *sz)) {
        free(buffer);
        return NULL;
    }

    if (f_close(&g_fileObject)) {
        free(buffer);
        return NULL;
    }

    return chunk;
}

/* Initialize the FAT FS for SD */
int sd_ele_fs_initialize(void)
{
    FRESULT error;

    error = f_mkdir(_T("/ele_nvm"));
    if (error) {
        if (error != FR_EXIST) {
            return -1;
        }
    }

    return kStatus_Success;
}
