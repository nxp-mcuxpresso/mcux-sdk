/*
 * Copyright (c) 2016, NXP Semiconductor, Inc.
 * Copyright 2021, 2023 NXP
 * All rights reserved.
 *
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 *  that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _loader_v3_h
#define _loader_v3_h

#include <stdint.h>

//! @addtogroup sbloader
//! @{

//! Defines the number of bytes in a cipher block (chunk). This is dictated by
//! the encryption algorithm.
#define SB3_BYTES_PER_CHUNK 16

typedef uint8_t chunk_v3_t[SB3_BYTES_PER_CHUNK];

typedef struct _ldr_buf ldr_buf_t;

struct _ldr_buf
{
    chunk_v3_t data;
    uint32_t fillPosition;
};

// Provides forward reference to the loader context definition.
typedef struct _ldr_Context_v3 ldr_Context_v3_t;

//! Function pointer definition for all loader action functions.
typedef status_t (*pLdrFnc_v3_t)(ldr_Context_v3_t *content);

//! sb3 section definitions

//! section type
typedef enum _sectionType
{
    kSectionNone       = 0, // end or invalid
    kSectionDataRange  = 1,
    kSectionDiffUpdate = 2,
    kSectionDDRConfig  = 3,
    kSectionRegister   = 4,
} section_type_t;

#define SB3_DATA_RANGE_HEADER_FLAGS_ERASE_MASK (0x1U) // bit 0
#define SB3_DATA_RANGE_HEADER_FLAGS_LOAD_MASK  (0x2U) // bit 1

#define SB3_DATA_RANGE_HEADER_TAG       (0x55aaaa55U)
#define SB3_DATA_ALIGNMENT_SIZE_IN_BYTE (16U)
#define SB3_LOAD_KEY_BLOB_OTP_MASK      (0xf000)

//! section data range structure
typedef struct range_header
{
    uint32_t tag;
    uint32_t startAddress;
    uint32_t length;
    uint32_t cmd;
} sb3_data_range_header_t;

typedef struct range_header_expansion
{
    uint32_t memoryId;
    uint32_t pad0;
    uint32_t pad1;
    uint32_t pad2;
} sb3_data_range_expansion_t;

typedef struct copy_memory_expansion
{
    uint32_t destAddr;
    uint32_t memoryIdFrom;
    uint32_t memoryIdTo;
    uint32_t pad;
} sb3_copy_memory_expansion_t;

typedef struct copy
{
    sb3_data_range_header_t header;
    sb3_copy_memory_expansion_t expansion;
} sb3_copy_memory_t;

typedef struct load_keyblob
{
    uint32_t tag;
    uint16_t offset;
    uint16_t keyWrapId;
    uint32_t length;
    uint32_t cmd;
} sb3_load_keyblob_t;

typedef struct fill_memory_expansion
{
    uint32_t pattern; // word to be used as pattern
    uint32_t pad0;
    uint32_t pad1;
    uint32_t pad2;
} sb3_fill_memory_expansion_t;

typedef struct fill_memory
{
    sb3_data_range_header_t header;
    sb3_fill_memory_expansion_t arg;
} sb3_fill_memory_t;

typedef struct config_memory
{
    uint32_t tag;
    uint32_t memoryId;
    uint32_t address; // address of config blob
    uint32_t cmd;
} sb3_config_memory_t;

enum
{
    kFwVerChk_Id_none      = 0,
    kFwVerChk_Id_nonsecure = 1,
    kFwVerChk_Id_secure    = 2,
};

typedef struct fw_ver_check
{
    uint32_t tag;
    uint32_t version;
    uint32_t id;
    uint32_t cmd;
} sb3_fw_ver_check_t;

//! sb3 DATA section header format
typedef struct section_header
{
    uint32_t sectionUid;
    uint32_t sectionType;
    uint32_t length;
    uint32_t _pad;
} sb3_section_header_t;

// loader command enum

typedef enum _loader_command_sb3
{
    kSB3_CmdInvalid         = 0,
    kSB3_CmdErase           = 1,
    kSB3_CmdLoad            = 2,
    kSB3_CmdExecute         = 3,
    kSB3_CmdCall            = 4,
    kSB3_CmdProgramFuse     = 5,
    kSB3_CmdProgramIFR      = 6,
    kSB3_CmdLoadCmac        = 7,
    kSB3_CmdCopy            = 8,
    kSB3_CmdLoadHashLocking = 9,
    kSB3_CmdLoadKeyBlob     = 10,
    kSB3_CmdConfigMem       = 11,
    kSB3_CmdFillMem         = 12,
    kSB3_CmdFwVerCheck      = 13,
} sb3_cmd_t;

//! The all of the allowed command
#define SBLOADER_V3_CMD_SET_ALL                                                                                      \
    ((1u << kSB3_CmdErase) | (1u << kSB3_CmdLoad) | (1u << kSB3_CmdExecute) | (1u << kSB3_CmdCall) |                 \
     (1u << kSB3_CmdProgramFuse) | (1u << kSB3_CmdProgramIFR) | (1u << kSB3_CmdCopy) | (1u << kSB3_CmdLoadKeyBlob) | \
     (1u << kSB3_CmdConfigMem) | (1u << kSB3_CmdFillMem) | (1u << kSB3_CmdFwVerCheck))
//! The allowed command set in ISP mode
#define SBLOADER_V3_CMD_SET_IN_ISP_MODE                                                                            \
    ((1u << kSB3_CmdErase) | (1u << kSB3_CmdLoad) | (1u << kSB3_CmdExecute) | (1u << kSB3_CmdProgramFuse) |        \
     (1u << kSB3_CmdProgramIFR) | (1u << kSB3_CmdCopy) | (1u << kSB3_CmdLoadKeyBlob) | (1u << kSB3_CmdConfigMem) | \
     (1u << kSB3_CmdFillMem) | (1u << kSB3_CmdFwVerCheck))
//! The allowed command set in recovery mode
#define SBLOADER_V3_CMD_SET_IN_REC_MODE                                                                            \
    ((1u << kSB3_CmdErase) | (1u << kSB3_CmdLoad) | (1u << kSB3_CmdExecute) | (1u << kSB3_CmdProgramFuse) |        \
     (1u << kSB3_CmdProgramIFR) | (1u << kSB3_CmdCopy) | (1u << kSB3_CmdLoadKeyBlob) | (1u << kSB3_CmdConfigMem) | \
     (1u << kSB3_CmdFillMem) | (1u << kSB3_CmdFwVerCheck))
//! The allowed command set in secure ATE mode
#define SBLOADER_V3_CMD_SET_IN_SEC_ATE_MODE                                                                        \
    ((1u << kSB3_CmdErase) | (1u << kSB3_CmdLoad) | (1u << kSB3_CmdExecute) | (1u << kSB3_CmdProgramFuse) |        \
     (1u << kSB3_CmdProgramIFR) | (1u << kSB3_CmdCopy) | (1u << kSB3_CmdLoadKeyBlob) | (1u << kSB3_CmdConfigMem) | \
     (1u << kSB3_CmdFillMem) | (1u << kSB3_CmdFwVerCheck))

#define SB3_DATA_BUFFER_SIZE_IN_BYTE (MAX(128, NBOOT_KEY_BLOB_SIZE_IN_BYTE_MAX))

//! Loader context definition.
struct _ldr_Context_v3
{
    pLdrFnc_v3_t Action;        //!< pointer to loader action function
    uint32_t block_size;        //!< size of each block in bytes
    uint32_t block_data_size;   //!< data size in bytes (NBOOT_SB3_CHUNK_SIZE_IN_BYTES)
    uint32_t block_data_total;  //!< data max size in bytes (block_size * data_size
    uint32_t block_buffer_size; //!< block0 and block size
    uint32_t block_buffer_position;
    uint8_t block_buffer[MAX(NBOOT_SB3_MANIFEST_MAX_SIZE_IN_BYTES,
                             NBOOT_SB3_BLOCK_MAX_SIZE_IN_BYTES)]; //! will be used for both block0 and blockx
    uint32_t processedBlocks;

    uint8_t data_block_offset; //! data block offset in a block.
    bool in_data_block;        //!< in progress of handling a data block within a block
    uint8_t *data_block;
    uint32_t data_block_position;

    bool in_data_section; //!< in progress of handling a data section within a data block
    uint32_t data_section_handled;
    sb3_section_header_t data_section_header;

    bool in_data_range; //!< in progress of handling a data range within a data section
    uint32_t data_range_handled;
    uint32_t data_range_gap;
    sb3_data_range_header_t data_range_header;
    bool has_data_range_expansion;
    sb3_data_range_expansion_t data_range_expansion;

    uint32_t commandSet; //!< support command set during sb file handling

    uint32_t data_position;
    uint8_t data_buffer[SB3_DATA_BUFFER_SIZE_IN_BYTE]; //!< temporary data buffer

    uint32_t fuse_cmd_position;
    uint8_t fuse_cmd_buffer[32 * 4]; //!< used for fuse command

    // options from ROM API
    kb_options_t fromAPI;

    bool do_firmware_load; //!< special handling for firmware loading ourside normal memory regions
};

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

#if defined(__cplusplus)
}
#endif // __cplusplus

//! @}

#endif
