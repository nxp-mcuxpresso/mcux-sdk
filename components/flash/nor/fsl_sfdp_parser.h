/*
 * Copyright 2024 NXP
 *
 * All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_SFDP_H
#define _FSL_SFDP_H

#include "fsl_common.h"

/*!
 * The SFDP strandard defines the structure of the SFDP database within the memory device and methods used to read its
 * data.
 * The SFDP defined header with Parameter ID FF00h and the related Basic Parameter Table is mandatory.
 * This header and table provide basic information for a SPI protocol memory.
 *
 */

/*!
 *
 * In the JESD216D revision are optional special function parameter tables for the JEDEC x4(Quad) eXtended Serial
 * Peripheral Interface(x4 xSPI).
 * New in the JESD216E revision is a description of the Replay Protected Monotonic Counter(RPMC) functionality
 * and also descriptions of the Secure Read and Secure write Packet transfer transactions.
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define SFDP_READ_INST  (0x5A)
#define SFDP_FETCH_INST (0x5B)

#define SFDP_REVISION(major, minor) (((uint16_t)(major) << 8UL) | ((uint16_t)(minor)))

/*!
 * @brief The enumeration of SFDP revision.
 */
typedef enum _sfdp_revsion
{
    kSFDP_JESD216F = SFDP_REVISION(0x01U, 0x0AU), /*!< Version F. */
    kSFDP_JESD216E = SFDP_REVISION(0x01U, 0x09U), /*!< Version E. */
    kSFDP_JESD216D = SFDP_REVISION(0x01U, 0x08U), /*!< Version D. */
    kSFDP_JESD216C = SFDP_REVISION(0x01U, 0x07U), /*!< Version C. */
    kSFDP_JESD216B = SFDP_REVISION(0x01U, 0x06U), /*!< Version B. */
    kSFDP_JESD216A = SFDP_REVISION(0x01U, 0x05U), /*!< Version A. */
    kSFDP_JESD216  = SFDP_REVISION(0x01U, 0x00U), /*!< The version pre A. */
} sfdp_revsion_t;

/*!
 * @brief The enumeration of return type of sfdp parser functions.
 */
typedef enum _sfdp_ret_type
{
    kSFDP_RET_Invalid,              /*!< Invalid input. */
    kSFDP_RET_HardwareIssue,        /*!< Fail due to spi hardare interface. */
    kSFDP_RET_NotImplemented,       /*!< The feature not implemented. */
    kSFDP_RET_ReadCMDNotSupported,  /*!< Read command not supported. */
    kSFDP_RET_EraseCMDNotSupported, /*!< Erase command not supported. */
    kSFDP_RET_RegBitNotSupported,   /*!< Register bit field not supported. */
    kSFDP_RET_OPICMDNotSupported,   /*!< OPI command not supported. */
    kSFDP_RET_Success,              /*!< Success. */
} sfdp_ret_type_t;

/*!
 * @brief The enumeration of sfdp access protocol
 *
 */
typedef enum _sfdp_access_protocol
{
    kSFDP_AccessProtocol240 = 0xF0, /*!< The access protocol 240 */
    kSFDP_AccessProtocol241 = 0xF1, /*!< The access protocol 241 */
    kSFDP_AccessProtocol242 = 0xF2, /*!< The access protocol 242 */
    kSFDP_AccessProtocol243 = 0xF3, /*!< The access protocol 243 */
    kSFDP_AccessProtocol244 = 0xF4, /*!< The access protocol 244 */
    kSFDP_AccessProtocol245 = 0xF5, /*!< The access protocol 245 */
    kSFDP_AccessProtocol246 = 0xF6, /*!< The access protocol 246 */
    kSFDP_AccessProtocol247 = 0xF7, /*!< The access protocol 247 */
    kSFDP_AccessProtocol250 = 0xFA, /*!< The access protocol 250 */
    kSFDP_AccessProtocol251 = 0xFB, /*!< The access protocol 251 */
    kSFDP_AccessProtocol252 = 0xFC, /*!< The access protocol 252 */
    kSFDP_AccessProtocol253 = 0xFD, /*!< The access protocol 253 */
    kSFDP_AccessProtocol254 = 0xFE, /*!< The access protocol 254 */
    kSFDP_AccessProtocol255 = 0xFF, /*!< The access protocol 255 */
} sfdp_access_protocol_t;

/*!
 * @brief The structure of sfdp header, including SFDP signature, revision, number of parameter header, and access
 * protocol.
 */
typedef struct _sfdp_header
{
    uint32_t signature; /*!< "SFDP" in little endian, 0x50444653h */
    uint8_t minorRev;   /*!< SFDP Minor Revision */
    uint8_t majorRev;   /*!< SFDP Major Revision */
    uint8_t nph;        /*!< Number of parameter header, 0-based, 0 indicates 1 parameter header. */
    uint8_t access;     /*!< SFDP access protocol, up to and including JESD216B this field was 0xFF. */
} sfdp_header_t;

/*!
 * @brief The structure of sfdp parameter header, including parameter ID, minor revision, major revision, length, and
 * parameter table pointer.
 *
 */
typedef struct _sfdp_param_header
{
    uint8_t idLsb;       /*!< Parameter ID LSB */
    uint8_t minorRev;    /*!< Parameter minor revision. */
    uint8_t majorRev;    /*!< Parameter major revision. */
    uint8_t len;         /*!< Parameter length in double words. */
    uint32_t ptp : 24U;  /*!< Parameter table pointer(byte address). */
    uint32_t idMsb : 8U; /*!< Parameter ID MSB. */
} sfdp_param_header_t;

#define SFDP_DW1_BLOCK_SECTOR_ERASE_SIZES_MASK  (0x3UL)
#define SFDP_DW1_BLOCK_SECTOR_ERASE_SIZES_SHIFT (0UL)

/*!
 * @brief The enumeration of octal dtr cmd type.
 */
typedef enum _sfdp_octal_dtr_cmd_type
{
    kSFDP_OctalDTRCmdExtensionSameAsCmd    = 0U, /*!< The command extension is same as the command. */
    kSFDP_OctalDTRCmdExtensionInvertCmd    = 1U, /*!< The command extension is the inverse of the command. */
    kSFDP_OctalDTRCmdExtensionReserved     = 2U, /*!< Reserved. */
    kSFDP_OctalDTRCmdExtensionCmdForm16Bit = 3U, /*!< The command and command extension forms a 16 bit command word. */
} sfdp_octal_dtr_cmd_type_t;

/*!
 * @brief The structure of basic flash param table, dw10 to dw16 is added from JESD216A, dw17 to dw20 is added from
 * JESD216C, dw21 to dw23 is added from JESD216F.
 */
typedef struct _sfdp_basic_flash_param_table
{
    uint32_t dw1;  /*!< Uniform 4KB Sectors, write buffer size, volatile status register, fast read support,
                       number of address bytes, DTR(DDR) support.  */
    uint32_t dw2;  /*!< Memory density. */
    uint32_t dw3;  /*!< Fast Read(1s-4s-4s and 1s-1s-4s): wait states, mode bit clocks and instruction. */
    uint32_t dw4;  /*!< Fast Read(1s-1s-2s and 1s-2s-2s): wait states, mode bit clocks and instruction. */
    uint32_t dw5;  /*!< Fast Read(2s-2s-2s and 4s-4s-4s) support. */
    uint32_t dw6;  /*!< Fast Read(2s-2s-2s): wait states, mode bit clocks and instruction. */
    uint32_t dw7;  /*!< Fast Read(4s-4s-4s): wait states, mode bit clocks and instruction. */
    uint32_t dw8;  /*!< Erase type 1 and 2 size and instruction. */
    uint32_t dw9;  /*!< Erase type 3 and 4 size and instruction. */
    uint32_t dw10; /*!< Added in kSFDP_JESD216A, erase type typical erase times and multiplier used to derive
                    max erase times. */
    uint32_t dw11; /*!< Added in kSFDP_JESD216A, chip erase typical time, byte program and page program
                    typical times, page size. */
    uint32_t dw12; /*!< Added in kSFDP_JESD216A, erase,program suspend, resume support, intervals, latency.*/
    uint32_t dw13; /*!< Added in kSFDP_JESD216A, Progam/Erase suspend/resume instructions. */
    uint32_t dw14; /*!< Added in kSFDP_JESD216A, deep power down and status register polling device busy. */
    uint32_t dw15; /*!< Added in kSFDP_JESD216A, hold and WP disable function, Quad Enable requirements, 4s-4s-4s mode
                    enable/disable sequences, 0-4-4 entry/exit methods and support. */
    uint32_t dw16; /*!< Added in kSFDP_JESD216A, 32-bit address entry/exit methods and support, soft reset and rescure
                    sequences, volatile and nonvolatile status register support. */
    uint32_t dw17; /*!< Added in kSFDP_JESD216C, fast read(1s-8s-8s)(1s-1s-8s): wait states,
                        mode bit clocks, instruction */
    uint32_t dw18; /*!< Added in kSFDP_JESD216C, octal commands, byte order, data strobe, JEDEC SPI protocol reset. */
    uint32_t dw19; /*!< Added in kSFDP_JESD216C, octal enable requirements, 8d-8d-8d mode enable/disable sequences,
                    0-8-8 entry/exit methods and support. */
    uint32_t dw20; /*!< Added in kSFDP_JESD216C, maximum operating speeds. */
    uint32_t dw21; /*!< Added in kSFDP_JESD216F, fast read(1s-1d-1d),(1s-2d-2d),(1s-4d-4d), and (4s-4d-4d) support. */
    uint32_t dw22; /*!< Added in kSFDP_JESD216F, fast read(1s-1d-1d) and (1s-2d-2d) wait states, mode bit clocks, and
                    instruction. */
    uint32_t dw23; /*!< Added in kSFDP_JESD216F, fast read(1s-4d-4d) and (4s-4d-4d) wait states, mode bit clocks and
                    instruction. */
} sfdp_basic_flash_param_table_t;

/*!
 * @brief The structure of sector map parameter table.
 *
 * @details The Sector Map Parameter Table identifies the location and size of sectors within the main data array of the
 * flash memory device and identifies which Erase Types are supported by each sector.
 *
 * @note Added in kSFDP_JESD216B
 */
typedef struct _sfdp_sector_map_param_table
{
    uint32_t dw1; /*!< 1st DWORD. */
    uint32_t dw2; /*!< 2nd DWORD. */
} sfdp_sector_map_param_table_t;

/*!
 * @brief The structure of replay protected monotonic counters parameter header and table.
 *
 * @details  The widely supported RPMC functionality has been adopted by JEDEC to control multiple nonvolatile monotonic
 * counters integrated into a serial flash device. RPMC allows cryptographically secure host access to the
 * (typically four) monotonic counters using packets that include a signature. The signature is generated using an
 * HMAC-SHA256 process that guarantees the authenticity of the transferred packet. The details of RPMC functionality
 * are described in a separate JEDEC standard.
 *
 * @note Added in kSFDP_JESD216E
 */
typedef struct _sfdp_rpmc_param_table
{
    struct
    {
        uint32_t flashHardening : 1U;     /*!< 0: Supported, 1: Not supported. */
        uint32_t counterSize : 1U;        /*!< 0: monotonic counter size is 32 bits, 1: Reserved. */
        uint32_t busyPollingMethod : 1U;  /*!< 0: Use OP2 Extended status, 1: Use Read status. */
        uint32_t reserved1 : 1U;          /*!< Reserved. */
        uint32_t numCounter : 4U;         /*!< Number of supported counters minus one. */
        uint32_t rpmcPacketWriteCmd : 8U; /*!< RPMC packet WRITE command opcode. */
        uint32_t rpmcPacketReadCmd : 8U;  /*!< RPMC packet READ command opcode. */
        uint32_t updateRate : 4U;         /*!< Rate of update = 5 * (2^(updateRate)) seconds. */
        uint32_t reserved2 : 4U;          /*!< Reserved. */
    } dw1;
    struct
    {
        uint32_t readCounterPollingDelayValue : 5U;       /*!< Read counter polling delay value. */
        uint32_t readCounterPollingDelayUnit : 2U;        /*!< Read counter polling delay unit,
                                                              0: 1us, 1: 16us, 2: 128us, 3: 1ms. */
        uint32_t reserved1 : 1U;                          /*!< Reserved. */

        uint32_t writeCounterPollingShortDelayValue : 5U; /*!< Write counter polling short delay value. */
        uint32_t writeCounterPollingShortDelayUnit : 2U;  /*!< Write counter polling short delay unit,
                                                         0: 1us, 1: 16us, 2: 128us, 3: 1ms. */
        uint32_t reserved2 : 1U;                          /*!< Reserved */

        uint32_t writeCounterPollingLongDelayValue : 5U;  /*!< Write counter polling short delay value. */
        uint32_t writeCounterPollingLongDelayUnit : 2U;   /*!< Write counter polling short delay unit
                                                         0: 1ms, 1: 16ms, 2: 128ms, 3: 1s. */
        uint32_t reserved3 : 1U;                          /*!< Reserved. */

        uint32_t reserved4 : 8U;                          /*!< Reserved. */
    } dw2;
} sfdp_rpmc_param_table_t;

/*!
 * @brief The structure of 4-byte address instruction parameter table.
 *
 * @details Legacy SPI memory devices were limited to 128-Mbits (16-Mbytes) of address space by commands that provided
 * only three bytes (24-bits) of address. Recent SPI memories that exceed 128-Mbits density provide various options
 * for providing 4-bytes (32-bits) of address. One option is the use of commands that always provide 4-bytes of
 * address. These commands in some cases have the same function as legacy 3-byte address commands but use a different
 * instruction to indicate that 4-bytes of address follow the instruction. The 4-byte address instruction special
 * function table indicates which 4-byte address command instructions are supported by the SPI memory. The table also
 * provides the 4-byte address instructions for the four Erase Types defined in 8 th DWORD of the Basic Flash Parameter
 * Table. If a 4-byte address instruction is not supported for an Erase Type, the instruction for that type is shown in
 * the table as FFh.
 * @note Added in kSFDP_JESD216B.
 */
typedef struct _sfdp_4_byte_addr_instruction_param_table
{
    uint32_t dw1; /*!< 1st dword. */
    uint32_t dw2; /*!< 2nd dword. */
} sfdp_4_byte_addr_instruction_param_table_t;

/*!
 * @brief The structure of eXtended serial peripheral interface(xSPI) profile 1.0 parameter table.
 * @note Added in kSFDP_JESD216C
 */
typedef struct _sfdp_xSPI_profile1_param_table
{
    uint32_t dw1; /*!< 1st dword. */
    uint32_t dw2; /*!< 2nd dword. */
    uint32_t dw3; /*!< 3rd dword. */
    uint32_t dw4; /*!< 4th dword. */
    uint32_t dw5; /*!< 5th dword. */
    uint32_t dw6; /*!< 6th dword. */
} sfdp_xSPI_profile1_param_table_t;

/*!
 * @brief The structure of eXtended serial peripheral interface(xSPI) profile 2.0 parameter table.
 * @note Added in kSFDP_JESD216C
 */
typedef struct _sfdp_xSPI_profile2_param_table
{
    uint32_t dw1; /*!< 1st dword. */
    uint32_t dw2; /*!< 2nd dword. */
    uint32_t dw3; /*!< 3rd dword. */
} sfdp_xSPI_profile2_param_table_t;

/*!
 * @brief The status, control, and configuration register map for SPI memory devices.
 * @note Added in kSFDP_JESD216C
 */
typedef struct _sfdp_sccr_param_table
{
    uint32_t dw1;  /*!< Volatile register address offset. */
    uint32_t dw2;  /*!< Non-volatile register address offset. */
    uint32_t dw3;  /*!< Generic addressable Read/Write status/control register command for volatile registers. */
    uint32_t dw4;  /*!< Generic addressable Read/Write status/control register command for volatile registers. */
    uint32_t dw5;  /*!< WIP(write in process). */
    uint32_t dw6;  /*!< WEL(write enable latch). */
    uint32_t dw7;  /*!< Program Error. */
    uint32_t dw8;  /*!< Erase Error. */
    uint32_t dw9;  /*!< Variable dummy cycle settings on volatile register. */
    uint32_t dw10; /*!< Variable dummy cycle settings on non-volatile register. */
    uint32_t dw11; /*!< Variable dummy cycle settings 1. */
    uint32_t dw12; /*!< Variable dummy cycle settings 2. */
    uint32_t dw13; /*!< Variable dummy cycle settings 3. */
    uint32_t dw14; /*!< QPI mode enable volatile. */
    uint32_t dw15; /*!< OPI mode enable non volatile. */
    uint32_t dw16; /*!< Octal mode enable volatile. */
    uint32_t dw17; /*!< Octal mode enable non-volatile. */
    uint32_t dw18; /*!< STR or DTR mode select volatile. */
    uint32_t dw19; /*!< STR or DTR mode select non-volatile. */
    uint32_t dw20; /*!< STR Octal Mode enable volatile. */
    uint32_t dw21; /*!< STR Octal Mode enable non-volatile. */
    uint32_t dw22; /*!< DTR Octal Mode enable volatile. */
    uint32_t dw23; /*!< DTR Octal Mode enable non-volatile. */
    uint32_t dw24; /*!< DPD Status */
    uint32_t dw25; /*!< UDPD status. */
    uint32_t dw26; /*!< Output driver strength volatile. */
    uint32_t dw27; /*!< Output driver strength non-volatile. */
    uint32_t dw28; /*!< Output driver strength control bits patterns. */
} sfdp_sccr_param_table_t;

/*!
 * @brief Status, control and configuration register map for xSPI profile 2.0 memory devices.
 *
 * @details The purpose of the SCCR Map is to provide a host controller with a minimum amount of information to be able
 * to boot a system and load necessary code for the system to run. It is to be expected that the code loaded from the
 * memory device will contain the necessary information required to achieve optimum performance from the device.
 */
typedef struct _sfdp_sccr_profile2_param_table
{
    uint32_t dw1;  /*!< Volatile register address offset. */
    uint32_t dw2;  /*!< Non-volatile register address offset. */
    uint32_t dw3;  /*!< Generic addressable Read/Write Status/Control register commands. */
    uint32_t dw4;  /*!< Program Error. */
    uint32_t dw5;  /*!< Erase Error. */
    uint32_t dw6;  /*!< Variable dummy cycle settings - volatile register. */
    uint32_t dw7;  /*!< Variable dummy cycle settings - non-volatile register. */
    uint32_t dw8;  /*!< Variable dummy cycle settings 1 - bit patterns. */
    uint32_t dw9;  /*!< Variable dummy cycle settings 2 - bit patterns. */
    uint32_t dw10; /*!< Variable dummy cycle settings 3 - bit patterns. */
    uint32_t dw11; /*!< Output driver strength - volatile. */
    uint32_t dw12; /*!< Output driver strength - non-volatile. */
    uint32_t dw13; /*!< Output driver strength control bit patterns. */
} sfdp_sccr_profile2_param_table_t;

/*!
 * @brief The structure of status, control and configuration register map offsets for multi-chip spi memory devices.
 * @details For multi-chip devices, each chip (die) will follow the same Status, Control and Configuration Register Map
 * as described in 6.10. Direct commands are not an option in this case, register bits may only be accessed by a
 * command specifying an address and a register value.
 * @note Added in kSFDP_JESD216C
 */
typedef struct _sfdp_sccr_multi_dies_addr_offset_param_table
{
    uint32_t dw1; /*!< Volatile register address offset for Die1. */
    uint32_t dw2; /*!< Non-Volatile register address offset for Die1. */
    uint32_t dw3; /*!< Volatile register address offset for Die2. */
    uint32_t dw4; /*!< Non-Volatile register address offset for Die2. */
    uint32_t dw5; /*!< Volatile register address offset for Die3. */
    uint32_t dw6; /*!< Non-Volatile register address offset for Die3. */
} sfdp_sccr_multi_dies_addr_offset_param_table_t;

/*!
 * @brief The structure of command sequence to octal parameter table.
 * @note Added in kSFDP_JESD216C
 */
typedef struct _sfdp_command_seq_to_octal_param_table
{
    uint32_t dw1; /*!< 1st dword. */
    uint32_t dw2; /*!< 2nd dword. */
    uint32_t dw3; /*!< 3rd dword. */
    uint32_t dw4; /*!< 4th dword. */
    uint32_t dw5; /*!< 5th dword. */
    uint32_t dw6; /*!< 6th dword. */
    uint32_t dw7; /*!< 7th dword. */
    uint32_t dw8; /*!< 8th dword. */
} sfdp_command_seq_to_octal_param_table_t;

/*!
 * @brief The structure of x4 Quad IO with DS parameter table.
 * @note Added in kSFDP_JESD216D
 */
typedef struct _sfdp_x4_quad_with_DS_param_table
{
    uint32_t dw1; /*!< Command codes used in 4s-4d-4d protocol mode. */
    uint32_t dw2; /*!< Command codes used in 4s-4d-4d protocol mode. */
    uint32_t dw3; /*!< Memory commands supported in 4s-4d-4d protocal mode. */
    uint32_t dw4; /*!< Dummy cycles used for various frequencies. */
    uint32_t dw5; /*!< Dummy cycles used for various frequencies. */
} sfdp_x4_quad_with_DS_param_table_t;

/*!
 * @brief The structure of command sequences to change to Quad DTR(DDR).
 * @note Added in kSFDP_JESD216D
 */
typedef struct _sfdp_command_seq_to_quad_param_table
{
    uint32_t dw1; /*!< 1st dword. */
    uint32_t dw2; /*!< 2nd dword. */
    uint32_t dw3; /*!< 3rd dword. */
    uint32_t dw4; /*!< 4th dword. */
    uint32_t dw5; /*!< 5th dword. */
    uint32_t dw6; /*!< 6th dword. */
    uint32_t dw7; /*!< 7th dword. */
    uint32_t dw8; /*!< 8th dword. */
} sfdp_command_seq_to_quad_param_table_t;

/*!
 * @brief The structure of secure packet read/write parameter table.
 * @note Added in kSFDP_JESD216E.
 */
typedef struct _sfdp_secure_packet_read_write_param_table
{
    uint32_t dw1; /*!< 1st dword. */
    uint32_t dw2; /*!< 2nd dword. */
    uint32_t dw3; /*!< 3rd dword. */
    uint32_t dw4; /*!< 4th dword. */
} sfdp_secure_packet_read_write_param_table;

/*!
 * @brief The enumeration of address mode of serial flash devices.
 */
typedef enum _sfdp_addr_mode
{
    kSFDP_AddrMode_3ByteOnly = 0x0U, /*!< Serial flash device only support 3-byte mode. */
    kSFDP_AddrMode_3Or4Byte  = 0x1U, /*!< Default to 3-byte mode, enters 4-byte mode on command. */
    kSFDP_AddrMode_4ByteOnly = 0x2U, /*!< Defult to 4-byte mode. */
    kSFDP_AddrMode_Reserved  = 0x3U, /*!< Reserved. */
} sfdp_addr_mode_t;

/*!
 * @brief The enumeration of flash data pad number.
 */
typedef enum _sfdp_flash_pad_num
{
    kSFDP_Flash1Pad = 0U, /*!< Data pad number is 1. */
    kSFDP_Flash2Pad = 1U, /*!< Data pad number is 2. */
    kSFDP_Flash4Pad = 2U, /*!< Data pad number is 4. */
    kSFDP_Flash8Pad = 3U, /*!< Data pad number is 8. */
} sfdp_flash_pad_num_t;

#define SFDP_ENCODE_PROTOCOL_TYPE(instrPad, instrDDR, addrPad, addrDDR, dataPad, dataDDR, key) \
    (((uint16_t)(key) << 14U) | ((uint16_t)(dataPad) << 0U) | ((uint16_t)(dataDDR) << 2U) |    \
     ((uint8_t)(addrPad) << 3U) | ((uint16_t)(addrDDR) << 5U) | ((uint8_t)(instrPad) << 6U) |  \
     ((uint16_t)(instrDDR) << 8U))

#define SFDP_DECODE_PROTOCOL_TYPE(protocol)                                    \
    do                                                                         \
    {                                                                          \
        instrPad = (sfdp_flash_pad_num_t)(((uint16_t)protocol & 0xC0U) >> 6U); \
        instrDDR = (((uint16_t)protocol & 0x100U) >> 8U);                      \
        addrPad  = (sfdp_flash_pad_num_t)(((uint16_t)protocol & 0x18U) >> 3U); \
        addrDDR  = (((uint16_t)protocol & 0x20U) >> 5U);                       \
        dataPad  = (sfdp_flash_pad_num_t)((uint16_t)protocol & 0x3);           \
        dataDDR  = (((uint16_t)protocol & 0x4U) >> 2U);                        \
    } while (0)

/*!
 * @brief The enumeration of protocol types.
 *
 * @details Command mode nomenclature used to indicate the number of active pins used for the instruction (A),
 * address (B), and data (C), and the data rate used for each. Data rates(n) can be single (S) and dual (D).
 * At the present time, the only valid Read SFDP command modes are: (1S-1S-1S), (2S-2S-2S), (4S-4S-4S), (4S-4D-4D),
 * and (8D-8D-8D). (4S-4D-4D), and (8D-8D-8D) modes also use a Data Strobe (DS) as part of the communication protocol.
 */
typedef enum _sfdp_protocol_type
{
    kSFDP_Protocol_1s1s1s = SFDP_ENCODE_PROTOCOL_TYPE(
        kSFDP_Flash1Pad, 0U, kSFDP_Flash1Pad, 0U, kSFDP_Flash1Pad, 0U, 0U), /*!< The protocol is 1s-1s-1s. */
    kSFDP_Protocol_1s1d1d = SFDP_ENCODE_PROTOCOL_TYPE(
        kSFDP_Flash1Pad, 0U, kSFDP_Flash1Pad, 1U, kSFDP_Flash1Pad, 1U, 0U), /*!< The protocol is 1s-1d-1d. */

    kSFDP_Protocol_1s1s2s = SFDP_ENCODE_PROTOCOL_TYPE(
        kSFDP_Flash1Pad, 0U, kSFDP_Flash1Pad, 0U, kSFDP_Flash2Pad, 0U, 1U), /*!< The protocol is 1s-1s-2s. */
    kSFDP_Protocol_1s2s2s = SFDP_ENCODE_PROTOCOL_TYPE(
        kSFDP_Flash1Pad, 0U, kSFDP_Flash2Pad, 0U, kSFDP_Flash2Pad, 0U, 1U), /*!< The protocol is 1s-2s-2s. */
    kSFDP_Protocol_1s2d2d = SFDP_ENCODE_PROTOCOL_TYPE(
        kSFDP_Flash1Pad, 0U, kSFDP_Flash2Pad, 1U, kSFDP_Flash2Pad, 1U, 1U), /*!< The protocol is 1s-2d-2d. */
    kSFDP_Protocol_2s2s2s = SFDP_ENCODE_PROTOCOL_TYPE(
        kSFDP_Flash2Pad, 0U, kSFDP_Flash2Pad, 0U, kSFDP_Flash2Pad, 0U, 1U), /*!< The protocol is 2s-2s-2s. */

    kSFDP_Protocol_1s1s4s = SFDP_ENCODE_PROTOCOL_TYPE(
        kSFDP_Flash1Pad, 0U, kSFDP_Flash1Pad, 0U, kSFDP_Flash4Pad, 0U, 2U), /*!< The protocol is 1s-1s-4s. */
    kSFDP_Protocol_1s4s4s = SFDP_ENCODE_PROTOCOL_TYPE(
        kSFDP_Flash1Pad, 0U, kSFDP_Flash4Pad, 0U, kSFDP_Flash4Pad, 0U, 2U), /*!< The protocol is 1s-4s-4s. */
    kSFDP_Protocol_1s4d4d = SFDP_ENCODE_PROTOCOL_TYPE(
        kSFDP_Flash1Pad, 0U, kSFDP_Flash4Pad, 1U, kSFDP_Flash4Pad, 1U, 2U), /*!< The protocol is 1s-4d-4d. */
    kSFDP_Protocol_4s4s4s = SFDP_ENCODE_PROTOCOL_TYPE(
        kSFDP_Flash4Pad, 0U, kSFDP_Flash4Pad, 0U, kSFDP_Flash4Pad, 0U, 2U), /*!< The protocol is 4s-4s-4s. */
    kSFDP_Protocol_4s4d4d = SFDP_ENCODE_PROTOCOL_TYPE(
        kSFDP_Flash4Pad, 0U, kSFDP_Flash4Pad, 1U, kSFDP_Flash4Pad, 1U, 2U), /*!< The protocol is 4s-4d-4d. */

    kSFDP_Protocol_1s1s8s = SFDP_ENCODE_PROTOCOL_TYPE(
        kSFDP_Flash1Pad, 0U, kSFDP_Flash1Pad, 0U, kSFDP_Flash8Pad, 0U, 3U), /*!< The protocol is 1s-1s-8s. */
    kSFDP_Protocol_1s8s8s = SFDP_ENCODE_PROTOCOL_TYPE(
        kSFDP_Flash1Pad, 0U, kSFDP_Flash8Pad, 0U, kSFDP_Flash8Pad, 0U, 3U), /*!< The protocol is 1s-8s-8s. */
    kSFDP_Protocol_1s8d8d = SFDP_ENCODE_PROTOCOL_TYPE(
        kSFDP_Flash1Pad, 0U, kSFDP_Flash8Pad, 1U, kSFDP_Flash8Pad, 1U, 3U), /*!< The protocol is 1s-8d-8d. */
    kSFDP_Protocol_8s8s8s = SFDP_ENCODE_PROTOCOL_TYPE(
        kSFDP_Flash8Pad, 0U, kSFDP_Flash8Pad, 0U, kSFDP_Flash8Pad, 0U, 3U), /*!< The protocol is 8s-8s-8s. */
    kSFDP_Protocol_8d8d8d = SFDP_ENCODE_PROTOCOL_TYPE(
        kSFDP_Flash8Pad, 1U, kSFDP_Flash8Pad, 1U, kSFDP_Flash8Pad, 1U, 3U), /*!< The protocol is 8d-8d-8d. */
} sfdp_protocol_type_t;

#define SFDP_4_BYTE_ADDR_INST_TABLE                                                                              \
    {                                                                                                            \
        0x13U, 0x0CU, 0x0EU, 0x3CU, 0xBCU, 0xBEU, 0xFFU, 0x34U, 0xECU, 0xEEU, 0xFFU, 0xFFU, 0x84U, 0x8EU, 0xFDU, \
            0xFFU, 0xFFU                                                                                         \
    }

/*!
 * @brief The structure of write status command information, including instruction.
 *
 */
typedef struct _sfdp_write_status_cmd_info
{
    uint8_t instruction; /*!< The instruction to write status register. */
} sfdp_write_status_cmd_info_t;

/*!
 * @brief The structure of register bit information.
 *
 */
struct _sfdp_reg_bit_info
{
    uint8_t readInstr;          /*!< Read instrution. */
    uint8_t writeInstr;         /*!< Write instruction. */
    uint8_t dummyCycles;        /*!< Default dummy cycles. */
    bool polarity;              /*!< false: positive, value = 1 means write is in progress,
                                  true: Inverted, value = 0 means write is in progress. */
    uint8_t location;           /*!< Shift of bit field. */
    bool addrFollowCmd;         /*!< If required the address followed command. */
    bool upperHalfWordSelected; /*!< Upper half word or lower half word. */
};

typedef struct _sfdp_reg_bit_info sfdp_wip_bit_info_t;
typedef struct _sfdp_reg_bit_info sfdp_wel_bit_info_t;
typedef struct _sfdp_reg_bit_info sfdp_program_error_bit_info_t;
typedef struct _sfdp_reg_bit_info sfdp_erase_error_bit_info_t;

/*!
 * @brief The structure of variable dummy cycle bit field information.
 *
 */
typedef struct _sfdp_variable_dummy_cycle
{
    uint8_t writeInstr;         /*!< Write instruction. */
    uint8_t readInstr;          /*!< Read instruction. */
    uint8_t dummyCycles;        /*!< Number of dummy cycle used for command. */
    uint8_t location;           /*!< Shift of bit field. */
    bool upperHalfWordSelected; /*!< Upper half word or lower half word. */
    bool addrFollowCmd;         /*!<  If required the address followed command. */
    uint8_t bitFieldWidth;      /*!< Bit field width. */
} sfdp_variable_dummy_cycle_t;

/*!
 * @brief The enumeration of 4-byte address mode enter methods.
 *
 */
typedef enum _sfdp_4_byte_addr_enter_method
{
    kSFDP_4ByteAddrEnterMethod0 = 1U << 0U, /*!< Issue instruction 0xB7h */
    kSFDP_4ByteAddrEnterMethod1 = 1U << 1U, /*!< Issue write enable 0x06h then issue instruction 0xB7h */
    kSFDP_4ByteAddrEnterMethod2 = 1U << 2U, /*!< Read with 0xCB, write instruction is C5h with 1 byte of data. */
    kSFDP_4ByteAddrEnterMethod3 = 1U << 3U, /*!< When MSB is set to "1", 4-byte address mode is active, read with
                                                instruction 0x16h, write instruction is 0x17h with 1 byte of data. */
    kSFDP_4ByteAddrEnterMethod4 = 1U << 4U, /*!< A 16-bit nonvolatile configuration register control 3-byte/4-byte
                                                address mode, read instruction is 0xB5h, Bit[0] controls address mode
                                                [0=3 Byte, 1=4 Byte], write configuration register instruction is
                                                0xB1h, data length is 2 bytes. */
    kSFDP_4ByteAddrEnterMethod5 = 1U << 5U, /*!< Supports dedicated 4-byte address instruction set. */
    kSFDP_4ByteAddrEnterMethod6 = 1U << 6U, /*!< Always operates in 4-byte address mode. */
} sfdp_4_byte_addr_enter_method_t;

/*!
 * @brief The enumeration of 4 byte address mode exit methods.
 *
 */
typedef enum _sfdp_4_byte_addr_exit_method
{
    kSFDP_4ByteAddrExitMethod0 = 1U << 0U, /*!< Issue instruction 0xE9h to exit 4-byte address mode. */
    kSFDP_4ByteAddrExitMethod1 = 1U << 1U, /*!< Issue write enable instruction 0x06, then issue instruction
                                                0xE9h to exit 4-byte address mode. */
    kSFDP_4ByteAddrExitMethod2 = 1U << 2U, /*!< 8-bit volatile extended address register used to defined A[31:24] bits,
                                               read with instruction 0xC8h, write instruction is C5h, data length is 1
                                               byte, return to lowest memory segment by setting A[31:24] to 0x0 and use
                                               3-bte addressing. */
    kSFDP_4ByteAddrExitMethod3 = 1U << 3U, /*!< 8-bit volatile bank register used to define A[30:24] bit, MSB is used
                                               to enable/disable 4-byte address mode, when MSB is cleared to 0, 3-byte
                                               address mode is active and A30:A24 are used to select the active 128Mbit
                                               memory segment, read with instruction 0x16h, write instruction is 0x17h,
                                               data length is 1byte. */
    kSFDP_4ByteAddrExitMethod4 = 1U << 4U, /*!< A 16-bit nonvolatile configuration register control 3-byte/4-byte
                                               address mode, read instruction is 0xB5h, Bit[0] controls address mode
                                               [0=3 Byte, 1=4 Byte], write configuration register instruction is
                                               0xB1h, data length is 2 bytes. */
    kSFDP_4ByteAddrExitMethod5 = 1U << 5U, /*!< Hardware reset. */
    kSFDP_4ByteAddrExitMethod6 = 1U << 6U, /*!< Software reset. */
    kSFDP_4ByteAddrExitMethod7 = 1U << 7U, /*!< Power cycle. */
} sfdp_4_byte_addr_exit_method_t;

/*!
 * @brief The enumeration of policy used to get supported protocol, please refer to @ref sfdp_protocol_type_t.
 */
typedef enum _sfdp_cmd_policy
{
    kSFDP_CmdPolicy_HighestThroughput = 0U, /*!< Use this policy to select the supported read command that result in
                                           highest throughput. */
    kSFDP_CmdPolicy_DdrIO            = 1U,  /*!< Both input and output are in DTR(DDR) mode. */
    kSFDP_CmdPolicy_DdrOutput        = 2U,  /*!< Only output is in DTR(DDR) mode. */
    kSFDP_CmdPolicy_LowestThroughput = 3U,  /*!< Use this policy to select the supported read command that result in
                                           lowest throughput. */

    kSFDP_CmdPolicy_SdrIO     = 4U,         /*!< Both input and output are in STR(SDR) mode. */
    kSFDP_CmdPolicy_SdrOutput = 5U,         /*!< Only output is in STR(SDR) mode. */
} sfdp_cmd_policy_t;
#define SFDP_CMD_POLICY_COUNT (6U)

/*!
 * @brief The structure of read command information, including instruction, dummy cycle, and mode clocks.
 */
typedef struct _sfdp_read_cmd_info
{
    uint8_t instruction; /*!< The read instruction. */
    uint8_t dummyCycle;  /*!< The default dummy cycle of read instruction. */
    uint8_t modeClocks;  /*!< Mode bit clocks. */
} sfdp_read_cmd_info_t;

/*!
 * @brief The structure of chip erase command information, including instruction and typical time to erase whole chip.
 *
 */
typedef struct _sfdp_chip_erase_cmd_info
{
    uint8_t instruction;  /* Instruction to erase whole chip. */
    uint32_t typicalTime; /* Typical time to erase whole chip, the unit is ms. */
} sfdp_chip_erase_cmd_info_t;

/*!
 * @brief The structure of erase command information, including size, instruction and typical time to erase
 * specific size.
 */
typedef struct _sfdp_erase_cmd_info
{
    uint32_t eraseSize;   /*!< Size of memory to erase, the unit is byte. */
    uint8_t instruction;  /*!< Instruction to erase specific size of memory. */
    uint32_t typicalTime; /*!< Typical time to erase specific size of memory, the unit is ms. */
} sfdp_erase_cmd_info_t;

/*!
 * @brief The enumeration of erase command type.
 */
typedef enum _sfdp_erase_cmd_type
{
    kSFDP_EraseCmdType1 = 0U, /*!< Erase command type 1. */
    kSFDP_EraseCmdType2 = 1U, /*!< Erase command type 2. */
    kSFDP_EraseCmdType3 = 2U, /*!< Erase command type 3. */
    kSFDP_EraseCmdType4 = 3U, /*!< Erase command type 4. */
} sfdp_erase_cmd_type_t;

/*!
 * @brief The structure of page program command information, including instruction and typical time to program the
 * specific page.
 *
 */
typedef struct _sfdp_page_program_cmd_info
{
    uint8_t instruction;  /*!< The instruction of page program. */
    uint32_t typicalTime; /*!< Typical time to program page, the unit is us. */
} sfdp_page_program_cmd_info_t;

/*!
 * @brief The structure of read status command information, including instruction, address size a
 *
 */
typedef struct _sfdp_read_status_cmd_info
{
    uint8_t instruction; /*!< The read status instruction. */
    uint8_t addrSize;    /*!< Number of address size for generic addressable read/write
                           status/control register instruction. */
    uint8_t dummyCycle;  /*!< Number of dummy cycle. */
} sfdp_read_status_cmd_info_t;

typedef status_t (*SFDP_SpiReadFunc)(uint32_t address, uint32_t *outputBuffer, uint32_t sizeInBytes);

/*!
 * @brief The enumeration of cmd supported in xspi 1.0 and xspi 2.0 profile.
 *
 */
typedef enum _sfdp_xspi_profile_opi_cmd
{
    kSFDP_OPICmd_ReadSfdp = 0U,        /*!< Read SFDP command. */
    kSFDP_OPICmd_Erase4K,              /*!< Erase 4K command. */
    kSFDP_OPICmd_EraseChip,            /*!< Erase chip command. */
    kSFDP_OPICmd_WriteStatusConfigReg, /*!< Write status configuration register command. */
    kSFDP_OPICmd_ReadConfigReg,        /*!< Read configuration register command. */
    kSFDP_OPICmd_ReadStatusReg,        /*!< Read status register command. */
    kSFDP_OPICmd_WriteStatusReg,       /*!< Write status register command. */
} sfdp_xspi_profile_opi_cmd_t;
#define SFDP_XSPI_PROFILE_OPI_CMD_COUNT (7U)

/*!
 * @brief The enumeration of 0-4-4 mode entry method.
 *
 */
typedef enum _sfdp_044_mode_entry_method
{
    kSFDP_044ModeEntryMethod0 =
        1U << 0U, /*!< Mode Bits[7:0] = A5h, note that QE must be set prior to using this mode. */
    kSFDP_044ModeEntryMethod1 = 1U << 1U, /*!< Read volatile configuration register with instruction 85h, set bit 3(XIP)
                                            in the data read, and write the modified data using the instruction 81h. */
    kSFDP_044ModeEntryMethod2 = 1U << 2U, /*!< Mode Bit[7:0]= AXh */
} sfdp_044_mode_entry_method_t;

/*!
 * @brief The enumeration of 0-4-4 mode exit method.
 *
 */
typedef enum _sfdp_044_mode_exit_method
{
    kSFDP_044ModeExitMethod0 = 1U << 0U, /*!< Mode Bit[7:0] = 00h will terminate 0-4-4 mode
                                            at the end of the current read operation. */
    kSFDP_044ModeExitMethod1 = 1U << 1U, /*!< If 3-byte address active, input Fh in IO0-IO3 for 8 clocks,
                                            if 4-byte address active, input Fh on IO0-IO3 for 10 clocks. */
    kSFDP_044ModeExitMethod2 = 1U << 3U, /*!< Input Fh on IO0-IO3 for 8 clocks. */
    kSFDP_044ModeExitMethod3 = 1U << 4U, /*!< Mode Bit[7:0] != AXh. */
} sfdp_044_mode_exit_method_t;

/*!
 * @brief The enumeration of 0-8-8 mode entry method.
 *
 */
typedef enum _sfdp_088_mode_entry_method
{
    kSFDP_088ModeEntryNotSupported = 0U, /*!< Device does not support 0-8-8 mode. */
    kSFDP_088ModeEntryMethod1      = 1U, /*!< Read the 8-bit volatile configuration register with instruction 85h, set
                                             XIP bit[0] in the data read, and write the modified data using the instruction
                                             81h, then mode bits[7:0] = 01h. */
} sfdp_088_mode_entry_method_t;

/*!
 * @brief The enumeration of 0-8-8 mode exit method.
 *
 */
typedef enum _sfdp_088_mode_exit_method
{
    kSFDP_088ModeExitNotSupported = 0U,  /*!< Device does not support 0-8-8 mode. */
    kSFDP_088ModeExitMethod1 = 1U << 0U, /*!< Mode Bits[7:0] = 00h will terminate this mode at the end of the current
                                        read operation. */
    kSFDP_088ModeExitMethod2 = 1U << 1U, /*!< If 3-byte address active, input FFh on DQ0-DQ7 for 4 clocks, if 4-byte
                                        address active input Fh on DQ0-DQ7 for 5 clocks. */
} sfdp_088_mode_exit_method_t;

/*!
 * @brief The enumeration of 4s-4s-4s mode enable method from 1s-1s-1s mode.
 */
typedef enum _sfdp_4s4s4s_mode_enable_method
{
    kSFDP_4s4s4sModeEnableMethod0 = 1U << 0U, /*!< set QE per QER, then issue instruction 38h. */
    kSFDP_4s4s4sModeEnableMethod1 = 1U << 1U, /*!< Issue instruction 38h. */
    kSFDP_4s4s4sModeEnableMethod2 = 1U << 2U, /*!< Issue instruction 35h. */
    kSFDP_4s4s4sModeEnableMethod3 = 1U << 3U, /*!< Read configuration using instruction 65h followed by address 800003h,
                                                set bit 6, write configuration using instruction 71h followed by
                                                address 800003h. */
    kSFDP_4s4s4sModeEnableMethod4 = 1U << 4U, /*!< Read volatile enhanced configuration using instruction 65h, no
                                                address is required, set bit 7 to 1, write volatile enhanced
                                                configuration using instruction 61h, no address is required. */
} sfdp_4s4s4s_mode_enable_method_t;

/*!
 * @brief The enumeration of 4s-4s-4s mode disable method
 *
 */
typedef enum _sfdp_4s4s4s_mode_disable_method
{
    kSFDP_4s4s4sModeDisableMethod0 = 1U << 0U, /*!< Issue FFh instruction. */
    kSFDP_4s4s4sModeDisableMethod1 = 1U << 1U, /*!< Issue F5h instruction. */
    kSFDP_4s4s4sModeDisableMethod2 = 1U << 2U, /*!< Read configuration using instruction 65h followed by address
                                                800003h, clear bit 6, write configuration using instruction 71h followed
                                                by address 800003h. */
    kSFDP_4s4s4sModeDisableMethod3 = 1U << 3U, /*!< Issue software reset 66/99 sequence. */
    kSFDP_4s4s4sModeDisableMethod4 = 1U << 4U, /* Read volatile enhanced configuration using instruction 65h, no address
                                                is required, clear bit 7, write volatile enhanced configuration using
                                                instruction 61h, no address is required. */
} sfdp_4s4s4s_mode_disable_method_t;

/*!
 * @brief The enumeration of 8s-8s-8s mode enable method from 1s-1s-1s mode.
 *
 */
typedef enum _sfdp_8s8s8s_mode_enable_method
{
    kSFDP_8s8s8sModeEnableMethod0 = 1U << 1U, /*!< Issue instruction 06h, then issue instruction E8h. */
    kSFDP_8s8s8sModeEnableMethod1 = 1U << 2U, /*!< Issue instruction 06h, then issue instruction 72h(address = 0h,
                                               data=01h or 02h). */
} sfdp_8s8s8s_mode_enable_method_t;

/*!
 * @brief The enumeration of 8s-8s-8s mode disable method.
 *
 */
typedef enum _sfdp_8s8s8s_mode_disable_method
{
    kSFDP_8s8s8sModeDisableMethod0 = 1U << 0U, /*!< Issue instruction 06h, then issue FFh instruction. */
    kSFDP_8s8s8sModeDisableMethod1 = 1U << 3U, /*!< Issue the soft reset sequence. */
} sfdp_8s8s8s_mode_disable_method_t;

/*!
 * @brief The structure of erase/suspend resume command information, including suspend instruction, resume
 * instruction, erase maximum latency, resume to suspend interval.
 *
 */
typedef struct _sfdp_erase_suspend_resume_cmd_info
{
    uint8_t suspendInstr;     /*!< Suspend instruction. */
    uint8_t resumeInstr;      /*!< Resume instruction. */
    uint32_t eraseMaxLatency; /*!< Maximum time required by the flash device to suspend an in-progress erase, the unit
                                 is ns.  */
    uint32_t resumeToSuspendInterval; /*!< The interval between the resumed erase operation to another suspend, the unit
                                         is us. */
} sfdp_erase_suspend_resume_cmd_info_t;

/*!
 * @brief The structure of program suspend command information, including suspend instruction, resume instruction,
 * erase maximum latency, resume to suspend interval.
 *
 */
typedef struct _sfdp_program_suspend_cmd_info
{
    uint8_t suspendInstr;     /*!< Suspend instruction. */
    uint8_t resumeInstr;      /*!< Resume instruction. */
    uint32_t eraseMaxLatency; /*!< Maximum time required by the flash device to suspend an in-progress erase, the unit
                                 is ns.  */
    uint32_t resumeToSuspendInterval; /*!< The interval between the resumed erase operation to another suspend, the unit
                                         is us. */
} sfdp_program_suspend_cmd_info_t;

/*!
 * @brief The structure of deep power down command information, including enter/exit instruction, exit deep power down
 * delay.
 *
 */
typedef struct _sfdp_deep_power_down_cmd_info
{
    uint8_t enterDeepPowerDownInstr; /*!< Instruction of enter deep power down mode. */
    uint8_t exitDeepPowerDownInstr;  /*!< Instruction of exit deep power down mode. */
    uint32_t exitDeepPowerDownDelay; /*!< Maximum time required by the flash device to exit deep power down and be
                                        ready to accept any command, the unit is ns. */
} sfdp_deep_power_down_cmd_info_t;

/*!
 * @brief The enumeration of quad enable method, the quad enable bit used to enable 1s-1s-4s and 1s-4s-4s quad read
 * or quad program operations.
 *
 */
typedef enum _sfdp_quad_enable_method
{
    kSFDP_QuadEnableNotSupported = 0U, /*!< Device doest not have a QE bit, device detects 1s-1s-4s and 1s-4s-4s reads
                                       based on instruction. */
    kSFDP_QuadEnableMethod1 = 1U,      /*!< QE is bit 1 of status register 2, it is set via write status with two data
                                         bytes where bit 1 of the second byte is one, it is cleared via write status with two
                                         data bytes where bit 1 of the second byte is zero. */
    kSFDP_QuadEnableMethod2 = 2U, /*!< QE is bit 6 of status register 1, it is set via write status with one data byte
                                    where bit 6 is one, it is cleared via write status with one data byte where bit 6
                                    is zero. */
    kSFDP_QuadEnableMethod3 = 3U, /*!< QE is bit 7 of status register 2, it is set via write status register 2
                                instruction 3Eh with one data byte where bit 7 is one, it is cleared via write status
                                register 2 instruction 3Eh with one data byte where bit 7 is zero, the status register
                                2 is read using instruction 3Fh. */
    kSFDP_QuadEnableMethod4 = 4U, /*!< QE is bit 1 of status register 2, it is set via write status with two data bytes
                                where bit 1 of the second byte is one, it is cleared via write status with two data
                                bytes where bit 1 of the second byte is zero. */
    kSFDP_QuadEnableMethod5 = 5U, /*!< QE is bit 1 of status register 2, using 05h to read status register 1, using 35h
                                to read status register 2, it is set via write status instruction 01h with two data
                                bytes where bit 1 of the second byte is one, it is cleared via write status with two
                                data bytes where bit 1 of the second byte is zero. */
    kSFDP_QuadEnableMethod6 = 6U, /*!< QE is bit 1 of status register 2, using 05h to read status register 1, using 35h
                                to read status register 2, using 15h to read status register 3, it is set via write
                                status instruction 31h with two data bytes where bit 1 of the second byte is one, it is
                                cleared via write status with two data bytes where bit 1 of the second byte is zero. */
} sfdp_quad_enable_method_t;

/*!
 * @brief The enumeration of software reset method.
 *
 */
typedef enum _sfdp_soft_reset_method
{
    kSFDP_SoftResetNotSupported = 0U,       /*!< No software reset instruction is supported. */
    kSFDP_SoftResetMethod1      = 1U << 0U, /*!< Drive Fh on all 4 data wires for 8 clocks. */
    kSFDP_SoftResetMethod2      = 1U << 1U, /*!< Drive Fh on all 4 data wires for 10 clocks if device is operating in
                                            4-byte address mode. */
    kSFDP_SoftResetMethod3 = 1U << 2U,      /*!< Drive Fh on all 4 data wires for 16 clocks. */
    kSFDP_SoftResetMethod4 = 1U << 3U,      /*!< Issue instruction F0h. */
    kSFDP_SoftResetMethod5 = 1U << 4U, /*!< Issue reset enable instruction 66h, then issue reset instruction 99h. */
    kSFDP_SoftResetMethod6 = 1U << 5U, /*!< Issue 0-4-4 mode is required prior to other reset sequence above if the
                                        device may be operating in this mode. */
} sfdp_soft_reset_method_t;

/*!
 * @brief The enumeration of octal enable method, the octal enable bit used to enable 1s-1s-8s and 1s-8s-8s octal read
 * or octal program operations.
 *
 */
typedef enum _sfdp_octal_enable_method
{
    kSFDP_OctalEnableNotSupported = 0U, /*!< Device does not have an octal enable bit. */
    kSFDP_OctalEnableMethod1 = 1U, /*!< Octal enable is bit 3 of status register, it is set via write status register2
                                    instruction 31h with one data byte where bit 3 is one, it is cleared via write
                                    register instruction 3Eh with one data byte where bit 3 is zero, the status
                                    register 2 is read using instruction 65h with address byte 02h and one dummy
                                    cycle. */
} sfdp_octal_enable_method_t;

/*!
 * @brief The structure of octal ddr or quad ddr entry sequence format.
 *
 */
typedef union _sfdp_entry_seq_format
{
    struct
    {
        uint8_t byte3;  /*!< 3rd byte of sequence. */
        uint8_t byte2;  /*!< 2nd byte of sequence. */
        uint8_t byte1;  /*!< 1st byte of sequence. */
        uint8_t length; /*!< length of sequence. */
        uint8_t byte7;  /*!< 7th byte of sequence. */
        uint8_t byte6;  /*!< 6th byte of sequence. */
        uint8_t byte5;  /*!< 5th byte of sequence. */
        uint8_t byte4;  /*!< 4th byte of sequence. */
    } seqStruct;        /*!< The sequence format in structure format. */
    uint64_t seqU64;    /*!< The sequence format in uint64 format. */
} sfdp_entry_seq_format_t;

/*!
 * @brief The structure of 8d-8d-8d(octal ddr) mode entry sequences.
 *
 */
typedef struct _sfdp_8d8d8d_entry_seq
{
    sfdp_entry_seq_format_t seq1; /*!< 1st sequence. */
    sfdp_entry_seq_format_t seq2; /*!< 2nd sequence. */
    sfdp_entry_seq_format_t seq3; /*!< 3rd sequence. */
    sfdp_entry_seq_format_t seq4; /*!< 4th sequence. */
} sfdp_8d8d8d_entry_seq_t;

/*!
 * @brief The macro used to get command in the sequence.
 *     - idx: range from 1 to 7
 *     - seq: The sequence data in type of #sfdp_entry_seq_format_t.
 */
#define SFDP_GET_SEQ_CMD(seq, idx) \
    (uint8_t)(((seq).seqU64 >> (8ULL * (((idx) / 4ULL) * 4ULL + (3ULL - (idx) % 4ULL)))) & 0xFFULL)

/*!
 * @brief The structure of 4s-4d-4d(quad ddr) entry sequence.
 *
 */
typedef struct _sfdp_4s4d4d_entry_seq
{
    sfdp_entry_seq_format_t seq1; /*!< 1st sequence. */
    sfdp_entry_seq_format_t seq2; /*!< 2nd sequence. */
    sfdp_entry_seq_format_t seq3; /*!< 3rd sequence. */
    sfdp_entry_seq_format_t seq4; /*!< 4th sequence. */
} sfdp_4s4d4d_entry_seq_t;

/*!
 * @brief The handle of sfdp, included all sfdp parameter table.
 *
 */
typedef struct _sfdp_handle
{
    sfdp_basic_flash_param_table_t bfp;                               /*!< Basic flash parameter table. */
    sfdp_sector_map_param_table_t sectorMapTable;                     /*!< Sector map parameter table. */
    sfdp_rpmc_param_table_t rpmcTable;                                /*!< Replay protected monotonic counters
                                                                      parameter table. */
    sfdp_4_byte_addr_instruction_param_table_t fourByteAddrInstTable; /*!< 4-byte address instruction
                                                                        parameter table. */
    sfdp_xSPI_profile1_param_table_t xSPIProfile1Table;               /*!< eXtended serial peripheral interface profile
                                                                          1.0 parameter table. */
    sfdp_xSPI_profile2_param_table_t xSPIProfile2Table;               /*!< eXtended serial peripheral interface profile
                                                                          2.0 parameter table. */
    sfdp_sccr_param_table_t SCCRegMapTable;                   /*!< Status, control, and Configuration register map
                                                              for SPI memory devices. */
    sfdp_sccr_profile2_param_table_t SCCRegMapMultiChipTable; /*!< Status, control and configuration register map
                                                          for xSPI profile 2.0 memory devices. */
    sfdp_sccr_multi_dies_addr_offset_param_table_t SCCRegMapxSPIProfile2Table; /*!< Status, control and configuration
                                                           register map offset for multi-chip SPI memory devices. */
    sfdp_command_seq_to_octal_param_table_t cmdSeq2OctalDDR;                   /*!< Command sequences to change to
                                                                               octal DTR(DDR) mode. */
    sfdp_command_seq_to_quad_param_table_t cmdSeq2QuadDDR;                     /*!< Command sequences to change to
                                                                                  Quad DTR(DDR) mode. */
    sfdp_x4_quad_with_DS_param_table_t x4QualIOWithDS;             /*!< x4 Quad IO with DS parameter table. */
    sfdp_secure_packet_read_write_param_table securePacketRWTable; /*!< Secure packet READ/WRITE parameter table. */

    SFDP_SpiReadFunc spiRead;                                      /*!< The function of read sfdp. */
    sfdp_revsion_t curJEDECVersion;                                /*!< JEDEC version of current serial flash device. */
    uint8_t nph;                                                   /* Counts of parameter tables. */
    uint8_t access;            /*!< Current serial flash device's access protocol. */
    sfdp_addr_mode_t addrMode; /*!< Current serial flash device's address mode. */
} sfdp_handle_t;

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @name Read SFDP Data Sets
 * @{
 */

/*!
 * @brief Read SFDP header, and check if SFDP signature is correct.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[in] spiRead The function to read sfdp header.
 *
 * @retval kSFDP_RET_HardwareIssue Fail to read SFDP header due to some hardware issue.
 * @retval kSFDP_RET_Invalid Fail to read SFDP header due to invalid SFDP signature.
 * @retval kSFDP_RET_Success Successfully to read sfdp header.
 */
sfdp_ret_type_t SFDP_ReadSFDPHeader(sfdp_handle_t *handle, SFDP_SpiReadFunc spiRead);

/*!
 * @brief Read SFDP parameter header.
 *
 * @param[out] ptrSfdpParamHeader Pointer to the variable in type of @ref sfdp_param_header_t
                                to store sfdp parameter header.
 * @param[in] nph Number of parameter header.
 * @param[in] spiRead Function to read sfdp parameter header.
 *
 * @retval kStatus_Success Successfully to read SFDP parameter header.
 * @retval kSFDP_RET_HardwareIssue Fail to read SFDP parameter header due to some hardware issues.
 */
sfdp_ret_type_t SFDP_ReadSFDPParameterHeader(sfdp_param_header_t *ptrSfdpParamHeader,
                                             uint8_t nph,
                                             SFDP_SpiReadFunc spiRead);

/*!
 * @brief Read all current serial flash device supported parameter tables.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 *
 * @retval kSFDP_RET_HardwareIssue Fail to read SFDP parameter header due to some hardware issues.
 * @retval kSFDP_RET_Success Successfully to read all supported parameter tables.
 */
sfdp_ret_type_t SFDP_ReadAllSupportedTable(sfdp_handle_t *handle);

/* @} */

/*!
 * @name Get Flash Basic Attributes
 * @{
 */

/*!
 * @brief Get Flash Density, the result in unit of KB.

 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 *
 * @return In unit of KB, 64 means 64KB(512 Kb)
 */
uint32_t SFDP_GetFlashDensity(sfdp_handle_t *handle);

/*!
 * @brief Get page size, the result in unit of Byte.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 *
 * @return The size of page.
 */
uint32_t SFDP_GetPageSize(sfdp_handle_t *handle);

/*!
 * @brief Get flash interface mode based on input policy, and number of data pad.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[in] cmdPolicy The policy used to select interface mode, in type of @ref sfdp_cmd_policy_t.
 * @param[in] flashPadNum The number of data pad, in type of @ref sfdp_flash_pad_num_t
 *
 * @return Calculated protocol type, in type of @ref sfdp_protocol_type_t.
 */
sfdp_protocol_type_t SFDP_GetFlashProtocolType(sfdp_handle_t *handle,
                                               sfdp_cmd_policy_t cmdPolicy,
                                               sfdp_flash_pad_num_t flashPadNum);

/*!
 * @brief Check if DTR(DDR) is supported.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 *
 * @retval true DTR clocking supported.
 * @retval false DTR NOT supported.
 */
static inline bool SFDP_CheckDTRSupported(sfdp_handle_t *handle)
{
    assert(handle != NULL);
    return (bool)((handle->bfp.dw1 & 0x80000UL) != 0UL);
}

/*!
 * @brief Get serial flash device's address mode.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 *
 * @return Serial flash device's address mode, in type of @ref sfdp_addr_mode_t.
 */
static inline sfdp_addr_mode_t SFDP_GetAddressBytes(sfdp_handle_t *handle)
{
    assert(handle != NULL);

    return (sfdp_addr_mode_t)((handle->bfp.dw1 & 0x60000UL) >> 17UL);
}

/*!
 * @brief Check if serial flash device support suspend operations.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 *
 * @retval false Suspend operation not supported.
 * @retval true Suspend operation supported.
 */
static inline bool SFDP_CheckSuspendSupported(sfdp_handle_t *handle)
{
    return (bool)((handle->bfp.dw12 & (1UL << 31UL)) == 0UL);
}

/*!
 * @brief Check if serial flash device support deep power down operations.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 *
 * @retval false Deep power down operation not supported.
 * @retval true Deep power down operation supported.
 */
static inline bool SFDP_CheckDeepPowerDownSupported(sfdp_handle_t *handle)
{
    return (bool)((handle->bfp.dw14 & (1UL << 31UL)) == 0UL);
}

/*!
 * @brief Get 4 byte address mode enter method, only workable when serial flash device support 4-byte
 * address mode.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @return 4-byte address mode enter method of serial flash device, please refer to
 * @ref sfdp_4_byte_addr_enter_method_t for details.
 */
static inline sfdp_4_byte_addr_enter_method_t SFDP_Get4ByteAddrModeEnterMethod(sfdp_handle_t *handle)
{
    return (sfdp_4_byte_addr_enter_method_t)(uint32_t)((handle->bfp.dw16 & 0xFF000000UL) >> 24UL);
}

/*!
 * @brief Get 4 byte address mode exit method, only workable when serial flash device support 4-byte
 * address mode.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @return 4-byte address mode exit method of serial flash device, please refer to
 * sfdp_4_byte_addr_exit_method_t for details.
 */
static inline sfdp_4_byte_addr_exit_method_t SFDP_Get4ByteAddrModeExitMethod(sfdp_handle_t *handle)
{
    return (sfdp_4_byte_addr_exit_method_t)(uint32_t)((handle->bfp.dw16 & 0xFFC000UL) >> 14UL);
}

/*!
 * @brief Get software reset method.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @return Serial flash device software reset method, please refer to @ref sfdp_soft_reset_method_t for details.
 */
static inline sfdp_soft_reset_method_t SFDP_GetSoftResetMethod(sfdp_handle_t *handle)
{
    return (sfdp_soft_reset_method_t)((handle->bfp.dw16 & 0x3F00UL) >> 8UL);
}

/* @} */

/*!
 * @name Get QPI Attributes
 * @{
 */

/*!
 * @brief Get supported method to enable 1s-1s-4s and 1s-4s-4s mode.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @return The serial flash device supported quad enable method, please refer to @ref sfdp_quad_enable_method_t for
 * details.
 */
static inline sfdp_quad_enable_method_t SFDP_GetQuadEnableMethod(sfdp_handle_t *handle)
{
    return (sfdp_quad_enable_method_t)((handle->bfp.dw15 & 0x700000UL) >> 20UL);
}

/*!
 * @brief Check if serial flash device support 0-4-4 mode.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 *
 * @retval false Current serial flash device do not support 0-4-4 mode.
 * @retval true Current serial flash device support 0-4-4 mode.
 */
static inline bool SFDP_Check044ModeSupported(sfdp_handle_t *handle)
{
    return ((handle->bfp.dw15 & 0x200UL) != 0UL);
}

/*!
 * @brief Get supported method to entry 0-4-4 mode.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @return The serial flash device supported method to enter 0-4-4 mode, please refer to
 * @ref sfdp_044_mode_entry_method_t for details.
 */
static inline sfdp_044_mode_entry_method_t SFDP_Get044ModeEntryMethod(sfdp_handle_t *handle)
{
    return (sfdp_044_mode_entry_method_t)((handle->bfp.dw15 & 0xF0000UL) >> 16UL);
}

/*!
 * @brief Get support method to exit 0-4-4 mode.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @return The serial flash device supported method to exit 0-4-4 mode, please refer to
 * @ref sfdp_044_mode_exit_method_t for details.
 */
static inline sfdp_044_mode_exit_method_t SFDP_Get044ModeExitMethod(sfdp_handle_t *handle)
{
    return (sfdp_044_mode_exit_method_t)((handle->bfp.dw15 & 0xFC00UL) >> 10U);
}

/*!
 * @brief Get supported method to enable 4s-4s-4s mode from 1s-1s-1s mode.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @return The serial flash device supported method to enable 4s-4s-4s mode, please refer to
 * @ref sfdp_4s4s4s_mode_enable_method_t for details.
 */
static inline sfdp_4s4s4s_mode_enable_method_t SFDP_Get4s4s4sModeEnableMethod(sfdp_handle_t *handle)
{
    return (sfdp_4s4s4s_mode_enable_method_t)((handle->bfp.dw15 & 0x1F0UL) >> 4U);
}

/*!
 * @brief Get supported method to disable 4s-4s-4s mode.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @return The serial flash device supported method to disable 4s-4s-4s mode, please refer to
 * @ref sfdp_4s4s4s_mode_disable_method_t for details.
 */
static inline sfdp_4s4s4s_mode_disable_method_t SFDP_Get4s4s4sModeDisableMethod(sfdp_handle_t *handle)
{
    if (SFDP_Get4s4s4sModeEnableMethod(handle) == kSFDP_4s4s4sModeEnableMethod4)
    {
        return kSFDP_4s4s4sModeDisableMethod4;
    }
    else
    {
        return (sfdp_4s4s4s_mode_disable_method_t)(handle->bfp.dw15 & 0xFUL);
    }
}

/*!
 * @brief Get sequence to entry 4s-4d-4d mode.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[out] ptrEntrySe The parameter to store sequences to enter 4s-4d-4d mode,
                        in type of @ref sfdp_4s4d4d_entry_seq_t.
 *
 * @retval kSFDP_RET_Success Successfully to get 4s-4d-4d entry sequence.
 * @retval kSFDP_RET_NotImplemented Current serial flash device does not support 4s-4d-4d entry sequence.
 */
sfdp_ret_type_t SFDP_Get4s4d4dEntrySeq(sfdp_handle_t *handle, sfdp_4s4d4d_entry_seq_t *ptrEntrySeq);

/*!
 * @brief Check if Data strobe supported in Quad SPI DTR(DDR) mode.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 *
 * @retval false Data strobe not supported in Quad SPI DTR mode.
 * @retval true  Data strobe supported in Quad SPI DTR mode.
 */
static inline bool SFDP_CheckDSSupportedForQpiDtrMode(sfdp_handle_t *handle)
{
    return (bool)((handle->bfp.dw18 & (1UL << 27UL)) != 0UL);
}

/*!
 * @brief Check if data strobe supported in Quad SPI STR(SDR) mode.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 *
 * @retval false Data strobe not supported in Quad SPI STR mode.
 * @retval true Data strobe supported in Quad SPI STR mode.
 */
static inline bool SFDP_CheckDSSupportedForQpiStrMode(sfdp_handle_t *handle)
{
    return (bool)((handle->bfp.dw18 & (1UL << 26UL)) != 0UL);
}

/* @} */

/*!
 * @name Get OPI Attributes
 * @{
 */

/*!
 * @brief Get octal DTR(DDR)(also called 8d-8d-8d) command type.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 *
 * @return The serial flash supported octal dtr cmd type, please refer to @ref sfdp_octal_dtr_cmd_type_t for details.
 */
static inline sfdp_octal_dtr_cmd_type_t SFDP_GetOctalDTRCmdType(sfdp_handle_t *handle)
{
    return (sfdp_octal_dtr_cmd_type_t)((handle->bfp.dw18 & 0x60000000UL) >> 29UL);
}

/*!
 * @brief Check if byte order is swapped in 8D-8D-8D mode.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 *
 * @retval true Byte order is swapped.
 * @retval false Byte order is not swapped.
 */
static inline bool SFDP_CheckByteSwapInOctalMode(sfdp_handle_t *handle)
{
    assert(handle->curJEDECVersion >= kSFDP_JESD216A);

    return (bool)((handle->bfp.dw18 & 0x80000000UL) != 0UL);
}

/*!
 * @brief Get command extension of input command.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[in] cmd The octal command used to calculate command extension.
 *
 * @return The command extension based on current serial flash device's command policy.
 */
uint8_t SFDP_GetOctalDTRCmdExtension(sfdp_handle_t *handle, uint8_t cmd);

/*!
 * @brief Check if current serial flash device support input OPI(octal spi) command.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param opiCmd The input octal spi command to check.
 *
 * @retval kSFDP_RET_OPICMDNotSupported The input opi command not supported.
 * @retval kSFDP_RET_Success The input opi command supported.
 */
sfdp_ret_type_t SFDP_CheckOPICmdSupported(sfdp_handle_t *handle, sfdp_xspi_profile_opi_cmd_t opiCmd);

/*!
 * @brief Used to enable 1s-1s-8s and 1s-8s-8s octal read or octal program operations.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @return The serial flash device supported octal enable method, please refer to @ref sfdp_octal_enable_method_t
 * for details.
 */
static inline sfdp_octal_enable_method_t SFDP_GetOctalEnableMethod(sfdp_handle_t *handle)
{
    return (sfdp_octal_enable_method_t)((handle->bfp.dw19 & 0x700000UL) >> 20UL);
}

/*!
 * @brief Check if current serial flash device support 0-8-8 mode.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @retval false Current serial flash device does not support 0-8-8 mode.
 * @retval true Current serial flash device supports 0-8-8 mode.
 */
static inline bool SFDP_Check088ModeSupported(sfdp_handle_t *handle)
{
    return (bool)((handle->bfp.dw19 & (1UL << 9UL)) != 0UL);
}

/*!
 * @brief Get 0-8-8 mode entry method.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 *
 * @return The serial flash device supported 0-8-8 mode entry method,
 * please refer to @ref sfdp_088_mode_entry_method_t.
 */
static inline sfdp_088_mode_entry_method_t SFDP_Get088ModeEntryMethod(sfdp_handle_t *handle)
{
    return (sfdp_088_mode_entry_method_t)((handle->bfp.dw19 & 0xF0000UL) >> 16UL);
}

/*!
 * @brief Get 0-8-8 mode exit method.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 *
 * @return The serial flash device supported 0-8-8 mode exit method,
 * please refer to @ref sfdp_088_mode_exit_method_t.
 */
static inline sfdp_088_mode_exit_method_t SFDP_Get088ModeExitMethod(sfdp_handle_t *handle)
{
    return (sfdp_088_mode_exit_method_t)((handle->bfp.dw19 & 0xFC00UL) >> 10UL);
}

/*!
 * @brief Get supported method to enter 8s-8s-8s mode from 1s-1s-1s mode.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @return The serial flash supported method to enter 8s-8s-8s mode,
 * please refer to @ref sfdp_8s8s8s_mode_enable_method_t for details.
 */
static inline sfdp_8s8s8s_mode_enable_method_t SFDP_Get8s8s8sModeEnableMethod(sfdp_handle_t *handle)
{
    return (sfdp_8s8s8s_mode_enable_method_t)((handle->bfp.dw19 & 0x1F0UL) >> 4UL);
}

/*!
 * @brief Get supported method to exit 8s-8s-8s mode.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @return The serial flash supported method to exit 8s-8s-8s mode, please refer to
 * @ref sfdp_8s8s8s_mode_disable_method_t for details.
 */
static inline sfdp_8s8s8s_mode_disable_method_t SFDP_Get8s8s8sModeDisableMethod(sfdp_handle_t *handle)
{
    return (sfdp_8s8s8s_mode_disable_method_t)(handle->bfp.dw19 & 0xFUL);
}

/*!
 * @brief Get 8d-8d-8d(octal DTR) mode entry sequences.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[out] ptrEntrySeq The variable to store sequences to enter 8d-8d-8d mode.
 *
 * @retval kSFDP_RET_Success Successfully to get sequences to enter 8d-8d-8d mode.
 * @retval kSFDP_RET_NotImplemented Current serial flash device do not support sequences to enter 8d-8d-8d mode.
 */
sfdp_ret_type_t SFDP_Get8d8d8dEntrySeq(sfdp_handle_t *handle, sfdp_8d8d8d_entry_seq_t *ptrEntrySeq);
/*! @} */

/*!
 * @name Get Device's Commands
 * @{
 */

/*!
 * @brief Get erase suspend/resume command information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[out] ptrEraseSuspendResumeCmdInfo The variable to store erase suspend/resume command information, please
 *                                          refer to @ref sfdp_erase_suspend_resume_cmd_info_t for details.
 */
void SFDP_GetEraseSuspendResumeCmdInfo(sfdp_handle_t *handle,
                                       sfdp_erase_suspend_resume_cmd_info_t *ptrEraseSuspendResumeCmdInfo);

/*!
 * @brief Get program suspend/resume command information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[out] ptrProgramSuspendResumeCmdInfo The variable to store program suspend/resume command information,
 * please refer to @ref sfdp_program_suspend_cmd_info_t for details.
 */
void SFDP_GetProgramSuspendResumeCmdInfo(sfdp_handle_t *handle,
                                         sfdp_program_suspend_cmd_info_t *ptrProgramSuspendResumeCmdInfo);

/*!
 * @brief Get deep power down command information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[out] ptrDeepPowerDownCmdInfo The variable to store deep power down command information, please refer to
 * @ref sfdp_deep_power_down_cmd_info_t for details.
 */
void SFDP_GetDeepPowerDownCmdInfo(sfdp_handle_t *handle, sfdp_deep_power_down_cmd_info_t *ptrDeepPowerDownCmdInfo);

/*!
 * @brief Get read command information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[in] protocolType The protocol type for current serial flash device.
 * @param[in] clkFreq The frequency of serial clock.
 * @param[out] ptrReadCmdInfo The variable of store read command information,
 *                          please refer to @ref sfdp_read_cmd_info_t for details.
 */
void SFDP_GetReadCmdInfo(sfdp_handle_t *handle,
                         sfdp_protocol_type_t protocolType,
                         uint32_t clkFreq,
                         sfdp_read_cmd_info_t *ptrReadCmdInfo);

/*!
 * @brief Get chip erase information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[out] ptrChipEraseCmdInfo The variable to store chip erase command information,
 *                                  please refer to @ref sfdp_chip_erase_cmd_info_t for details.
 */
void SFDP_GetChipEraseCmdInfo(sfdp_handle_t *handle, sfdp_chip_erase_cmd_info_t *ptrChipEraseCmdInfo);

/*!
 * @brief Get sector erase command information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[in] type Used to select erase command type, please refer to @ref sfdp_erase_cmd_type_t.
 * @param[out] ptrEraseCmdInfo The variable to store erase command information,
                                please refer to @ref sfdp_erase_cmd_info_t for details.
 *
 * @retval kSFDP_RET_EraseCMDNotSupported Selected type of erase command not supported.
 * @retval kSFDP_RET_Success Successfully to get selected erase command information.
 */
sfdp_ret_type_t SFDP_GetSectorEraseCmdInfo(sfdp_handle_t *handle,
                                           sfdp_erase_cmd_type_t type,
                                           sfdp_erase_cmd_info_t *ptrEraseCmdInfo);

/*!
 * @brief Get page program command information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[in] protocolType The protocol type for current serial flash device.
 * @param[out] ptrPageProgramCmdInfo The variable to store page program command information,
 *                                  please refer to @ref sfdp_page_program_cmd_info_t.
 */
void SFDP_GetPageProgramCmdInfo(sfdp_handle_t *handle,
                                sfdp_protocol_type_t protocolType,
                                sfdp_page_program_cmd_info_t *ptrPageProgramCmdInfo);

/*!
 * @brief Get read status command information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[in] protocolType The protocol type for current serial flash device.
 * @param[out] ptrReadStatusCmdInfo The variable to store read status command information,
 *                              please refer to @ref sfdp_read_status_cmd_info_t.
 */
void SFDP_GetReadStatusCmdInfo(sfdp_handle_t *handle,
                               sfdp_protocol_type_t protocolType,
                               sfdp_read_status_cmd_info_t *ptrReadStatusCmdInfo);

/*!
 * @brief Get write status command information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[out] ptrWriteStatusCmdInfo The variable to stor write status command information,
 *                                  please refer to @ref sfdp_write_status_cmd_info_t.
 */
void SFDP_GetWriteStatusCmdInfo(sfdp_handle_t *handle, sfdp_write_status_cmd_info_t *ptrWriteStatusCmdInfo);

/* @} */

/*!
 * @name Get Device register bit field information
 * @{
 */

/*!
 * @brief Get busy bit field information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[in] padNum Number of data pad.
 * @param[out] ptrBusyBitInfo The variable to store busy bit information.
 *
 * @retval kSFDP_RET_Success Successfully to get busy bit field information.
 */
sfdp_ret_type_t SFDP_GetBusyBitInfo(sfdp_handle_t *handle,
                                    sfdp_flash_pad_num_t padNum,
                                    sfdp_wip_bit_info_t *ptrBusyBitInfo);

/*!
 * @brief Get WEL(write enable) bit field information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[in] protocolType Current selected protocol type.
 * @param[out] ptrWelBitInfo The variable to store WEL bit information.
 *
 * @retval kSFDP_RET_Success Successfully to get WEL bit field information.
 */
sfdp_ret_type_t SFDP_GetWELBitInfo(sfdp_handle_t *handle,
                                   sfdp_protocol_type_t protocolType,
                                   sfdp_wel_bit_info_t *ptrWelBitInfo);

/*!
 * @brief Get program error bit field information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[in] protocolType Specify the protocol type to use.
 * @param[out] ptrProgramErrorBitInfo The variable to store program error bit information.
 *
 * @retval kSFDP_RET_NotImplemented Current serial flash do not implement the parameter table.
 * @retval kSFDP_RET_RegBitNotSupported Current serial flash do not support program error bit.
 * @retval kSFDP_RET_Success Successfully to get program error bit field information.
 */
sfdp_ret_type_t SFDP_GetProgramErrorBitInfo(sfdp_handle_t *handle,
                                            sfdp_protocol_type_t protocolType,
                                            sfdp_program_error_bit_info_t *ptrProgramErrorBitInfo);

/*!
 * @brief Get erase error bit field information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[in] protocolType Specify the protocol type to use.
 * @param[out] ptrEraseErrorBitInfo The variable to store erase error bit information.
 *
 * @retval kSFDP_RET_NotImplemented Current serial flash do not implement the parameter table.
 * @retval kSFDP_RET_RegBitNotSupported Current serial flash do not support erase error bit.
 * @retval kSFDP_RET_Success Successfully to get erase error bit field information.
 */
sfdp_ret_type_t SFDP_GetEraseErrorBitInfo(sfdp_handle_t *handle,
                                          sfdp_protocol_type_t protocolType,
                                          sfdp_erase_error_bit_info_t *ptrEraseErrorBitInfo);

/*!
 * @brief Get variable dummy cycle information.
 *
 * @param[in] handle The parameter in type of @ref sfdp_handle_t.
 * @param[in] protocolType Specify the protocol type to use.
 * @param[out] ptrVariableDCInfo The variable to updated dummy cycle value..
 *
 * @retval kSFDP_RET_NotImplemented Current serial flash do not implement the parameter table.
 * @retval kSFDP_RET_RegBitNotSupported Current serial flash do not support variable dummy cycle bit.
 * @retval kSFDP_RET_Success Successfully to get variable dummy cycle bit field information.
 */
sfdp_ret_type_t SFDP_GetVolatileVariableDummyCycleInfo(sfdp_handle_t *handle,
                                                       sfdp_protocol_type_t protocolType,
                                                       sfdp_variable_dummy_cycle_t *ptrVariableDCInfo);
/* @} */

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* __FSL_SFDP_H */
