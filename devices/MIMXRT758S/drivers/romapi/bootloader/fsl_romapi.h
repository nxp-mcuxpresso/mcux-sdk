/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_ROMAPI_H_
#define FSL_ROMAPI_H_
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

#define ROM_API_TREE_ADDR (0x1303FC00U)

/*!
 * @addtogroup runbootloader
 * @{
 */
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* clang-format off */
/*   API prototype fields definition.
| 31 : 24   |    23 : 20        |     19 : 16        |  15 : 12             | 11 : 8   |  7 ： 6  |  5 ： 4  |  3 ： 0  |
|     Tag   |   Boot mode       | boot interface     |  Instance            | Reserved | Recovery | Recovery | Reserved |
|           |                   |                    |  Used For Boot mode 0|          | boot     | boot     |          |
|           |0: Prime boot mode | ISP boot mode      |                      |          |interface |interface |          |
|           |1: ISP mode        | 0 - UART           |                      |          |configure1|configure0|          |
|           |                   | 1 - I2C            |                      |          |          |          |          |
|           |                   | 2 - SPI            |                      |          |          |          |          |
|           |                   | 3 - USB_HID(USB0)  |                      |          |          |          |          |
|           |                   | 8 - eUSB(USB1)     |                      |          |          |          |          |
|           |                   | F - Auto detection |                      |          |          |          |          |
|           |                   | Prime boot mode    |                      |          |          |          |          |
|           |                   | 4 - XSPI NOR       |                      |          |          |          |          |
|           |                   | 5 - LPSPI NOR      |                      |          |          |          |          |
|           |                   | 6 - DFU            |                      |          |          |          |          |
|           |                   | 7 - eMMC           |                      |          |          |          |          |

*/
/* clang-format on */

typedef struct _user_app_boot_invoke_option
{
    union
    {
        struct
        {
            uint32_t reserved0 : 4;
            uint32_t recovery_boot_cfg0 : 2;
            uint32_t recovery_boot_cfg1 : 2;
            uint32_t reserved1 : 4;
            uint32_t instance : 4;
            uint32_t boot_interface : 4;
            uint32_t mode : 4;
            uint32_t tag : 8;
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
const char *bootloader_copyright(void);

#endif /* FSL_ROMAPI_H_ */
