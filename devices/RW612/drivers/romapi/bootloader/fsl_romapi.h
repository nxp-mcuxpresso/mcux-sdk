/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_ROMAPI_H_
#define _FSL_ROMAPI_H_
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#include <stdint.h>
#include <fsl_device_registers.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief ROMAPI driver version 2.0.0. */
#define FSL_ROMAPI_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

#define ROM_API_TREE_ADDR_A0           0x13024100U
#define ROM_API_TREE_ADDR_A1           0x13030000U

static inline uint32_t get_romapi_addr(void) {
    uint32_t chip_rev_nr = SOCCTRL->CHIP_INFO & 0x0fu;
    return (chip_rev_nr == 0u) ? ROM_API_TREE_ADDR_A0 : ROM_API_TREE_ADDR_A1;
}

#define ROM_API_TREE_ADDR  (get_romapi_addr())


// FOR A0. This needs to be adjusted for A1
//! @brief Boot parameters of the user application
//!  WORD    OFFSET      FIELD                              DESCRIPTION
//!          [31:24]     TAG                                Must be '0xEB'
//!          [23:20]     Boot mode                          0:Master boot mode; 1: ISP boot
//!          [19:16]     Boot interface                     0:USART 1:I2C 2:SPI 3:USB HID 4:QSPI 5:USB DFU
//!          [15:12]     Boot instance(Channel)             0 or 1; For SD or MMC,this is to select the instance
//!                                                         For FLEXSPI boot, this select the Channel A or Channel B
//!          [11:08]     Redundant boot image index         Redundant boot image index for FlexSPI NOR flash
//!          [07:00]     Reserved
//!
//!  TAG[31:24]	    BOOT MODE[23:20]    INTERFACE[19:16]    INSTANCE[15:12]     RBII    Reserved[07:00]     COMBINATION     BOOT ACTION
//!  0xEB  	        0                   0	                X	                X       X	                0xEB00XXXX	    MASTR BOOT: USART
//!	                0	                1	                X	                X       X	                0xEB01XXXX	    MASTR BOOT: I2C
//!	                0	                2	                X	                X       X	                0xEB02XXXX	    MASTR BOOT: SPI
//!	                0	                3	                X	                X       X	                0xEB03XXXX	    MASTR BOOT: USB HID
//!	                0	                4	                X	                0       X	                0xEB0400XX	    MASTR BOOT: FlexSPI Channel A:boot image index 0
//!	                0	                4	                X	                1       X	                0xEB0401XX	    MASTR BOOT: FlexSPI Channel A:boot image index 1
//!	                0                   4	                X	                0       X	                0xEB0410XX	    MASTR BOOT: FlexSPI Channel B:boot image index 0
//!	                0	                4	                X	                1       X	                0xEB0411XX	    MASTR BOOT: FlexSPI Channel B:boot image index 1
//!	                0	                5	                X	                X       X	                0xEB05XXXX	    MASTR BOOT: USB DFU
//!	                1	                0	                X	                X       X	                0xEB10XXXX	    ISP BOOT: USART
//!	                1	                1	                X	                X       X	                0xEB11XXXX	    ISP BOOT: I2C
//!	                1	                2	                X	                X       X	                0xEB12XXXX	    ISP BOOT: SPI
//!

typedef struct _user_app_boot_invoke_option
{
    union
    {
        struct
        {
            uint32_t reserved           : 8;
            uint32_t boot_image_index   : 4;
            uint32_t instance           : 4;
            uint32_t boot_interface     : 4;
            uint32_t mode               : 4;
            uint32_t tag                : 8;
        } B;
        uint32_t U;
    } option;
} user_app_boot_invoke_option_t;

/*!
 * @brief Run the Bootloader API  to force into the ISP mode base on the user arg
 *
 * @param arg Indicates API prototype fields definition. Refer to the above user_app_boot_invoke_option_t structure
 */
void bootloader_user_entry(void *arg);

/*!
 * @brief Get Bootloader version
 *
 * @retval Bootloader version.
 */
uint32_t bootloader_version(void);

/*!
 * @brief Get Bootloader Copyright
 *
 * @retval Pointer to Bootloader copyright header
 */
const char * bootloader_copyright(void);

#endif /* _FSL_ROMAPI_H_ */
