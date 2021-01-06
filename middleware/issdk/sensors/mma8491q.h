/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef MMA8491Q_H_
#define MMA8491Q_H_

/**
 **
 **  MMA8491Q Sensor Internal Registers
 */
enum
{
    MMA8491Q_STATUS = 0x00,
    MMA8491Q_OUT_X_MSB = 0x01,
    MMA8491Q_OUT_X_LSB = 0x02,
    MMA8491Q_OUT_Y_MSB = 0x03,
    MMA8491Q_OUT_Y_LSB = 0x04,
    MMA8491Q_OUT_Z_MSB = 0x05,
    MMA8491Q_OUT_Z_LSB = 0x06,
};

#define MMA8491Q_I2C_ADDRESS (0x55) /* MMA8491Q I2C Slave Address. */

#define MMA8491Q_T_RST_MIN (1U)    /* Approx time between falling edge of EN and next rising edge of EN. */
#define MMA8491Q_T_ON_TYPICAL (1U) /* Approx time taken for Data to become available after rising edge of EN. */

/*--------------------------------
** Register: STATUS
** Enum: MMA8491Q_STATUS
** --
** Offset : 0x00 - Data-ready status information
** ------------------------------*/
typedef union
{
    struct
    {
        uint8_t xdr : 1; /*  - X-Axis new Data Available.                                               */

        uint8_t ydr : 1; /*  - Y-Axis new data available.                                               */

        uint8_t zdr : 1; /*  - Z-Axis new data available.                                               */

        uint8_t zyxdr : 1; /*  - X or Y or Z-Axis new data available.                                     */

        uint8_t reserved : 4; /*  - Reserved bits (Will always be set to zero).                              */

    } b;
    uint8_t w;
} MMA8491Q_STATUS_t;

/*
** STATUS - Bit field mask definitions
*/
#define MMA8491Q_STATUS_XDR_MASK ((uint8_t)0x01)
#define MMA8491Q_STATUS_XDR_SHIFT ((uint8_t)0)

#define MMA8491Q_STATUS_YDR_MASK ((uint8_t)0x02)
#define MMA8491Q_STATUS_YDR_SHIFT ((uint8_t)1)

#define MMA8491Q_STATUS_ZDR_MASK ((uint8_t)0x04)
#define MMA8491Q_STATUS_ZDR_SHIFT ((uint8_t)2)

#define MMA8491Q_STATUS_ZYXDR_MASK ((uint8_t)0x08)
#define MMA8491Q_STATUS_ZYXDR_SHIFT ((uint8_t)3)

#define MMA8491Q_STATUS_RESERVED_MASK ((uint8_t)0xF0)
#define MMA8491Q_STATUS_RESERVED_SHIFT ((uint8_t)4)

/*
** STATUS - Bit field value definitions
*/
#define MMA8491Q_STATUS_XDR_DRDY ((uint8_t)0x01)      /*  - Set to 1 whenever new X-axis data acquisition is    */
                                                      /*  completed. XDR is cleared any time OUT_X_MSB register */
                                                      /*  is read.                                              */
#define MMA8491Q_STATUS_YDR_DRDY ((uint8_t)0x02)      /*  - Set to 1 whenever new Y-axis data acquisition is    */
                                                      /*  completed. YDR is cleared any time OUT_Y_MSB register */
                                                      /*  is read.                                              */
#define MMA8491Q_STATUS_ZDR_DRDY ((uint8_t)0x04)      /*  - Set to 1 whenever new Z-axis data acquisition is    */
                                                      /*  completed. ZDR is cleared any time OUT_Z_MSB register */
                                                      /*  is read.                                              */
#define MMA8491Q_STATUS_ZYXDR_DRDY ((uint8_t)0x08)    /*  - Signals that new acquisition for any of the enabled */
                                                      /*  channels is available. ZYXDR is cleared when the      */
                                                      /*  high-bytes of the acceleration data (OUT_X_MSB,       */
                                                      /*  OUT_Y_MSB, OUT_Z_MSB) of all channels are read.       */
#define MMA8491Q_STATUS_RESERVED_ZERO ((uint8_t)0x00) /*  - Value of reserved field.                            */
                                                      /*------------------------------*/

/*--------------------------------
** Register: OUT_X_MSB
** Enum: MMA8491Q_OUT_X_MSB
** --
** Offset : 0x01 - Bits 8-15 of 14-bit X-Axis output sample data (expressed as 2's complement numbers).
** ------------------------------*/
typedef uint8_t MMA8491Q_OUT_X_MSB_t;

/*--------------------------------
** Register: OUT_X_LSB
** Enum: MMA8491Q_OUT_X_LSB
** --
** Offset : 0x02 - Bits 0-7 of 14-bit X-Axis output sample data (expressed as 2's complement numbers).
** ------------------------------*/
typedef union
{
    struct
    {
        uint8_t _reserved_ : 2;
        uint8_t out_x_lsb : 6; /*  - OUT_X_LSB register bits 2-7. (Bit 0 and 1 will always be 0).             */

    } b;
    uint8_t w;
} MMA8491Q_OUT_X_LSB_t;

/*
** OUT_X_LSB - Bit field mask definitions
*/
#define MMA8491Q_OUT_X_LSB_OUT_X_LSB_MASK ((uint8_t)0xFC)
#define MMA8491Q_OUT_X_LSB_OUT_X_LSB_SHIFT ((uint8_t)2)

/*------------------------------*/

/*--------------------------------
** Register: OUT_Y_MSB
** Enum: MMA8491Q_OUT_Y_MSB
** --
** Offset : 0x03 - Bits 8-15 of 14-bit Y-Axis output sample data (expressed as 2's complement numbers).
** ------------------------------*/
typedef uint8_t MMA8491Q_OUT_Y_MSB_t;

/*--------------------------------
** Register: OUT_Y_LSB
** Enum: MMA8491Q_OUT_Y_LSB
** --
** Offset : 0x04 - Bits 0-7 of 14-bit Y-Axis output sample data (expressed as 2's complement numbers).
** ------------------------------*/
typedef union
{
    struct
    {
        uint8_t _reserved_ : 2;
        uint8_t out_y_lsb : 6; /*  - OUT_Y_LSB register bits 2-7. (Bit 0 and 1 will always be 0).             */

    } b;
    uint8_t w;
} MMA8491Q_OUT_Y_LSB_t;

/*
** OUT_Y_LSB - Bit field mask definitions
*/
#define MMA8491Q_OUT_Y_LSB_OUT_Y_LSB_MASK ((uint8_t)0xFC)
#define MMA8491Q_OUT_Y_LSB_OUT_Y_LSB_SHIFT ((uint8_t)2)

/*------------------------------*/

/*--------------------------------
** Register: OUT_Z_MSB
** Enum: MMA8491Q_OUT_Z_MSB
** --
** Offset : 0x05 - Bits 8-15 of 14-bit Z-Axis output sample data (expressed as 2's complement numbers).
** ------------------------------*/
typedef uint8_t MMA8491Q_OUT_Z_MSB_t;

/*--------------------------------
** Register: OUT_Z_LSB
** Enum: MMA8491Q_OUT_Z_LSB
** --
** Offset : 0x06 - Bits 0-7 of 14-bit Z-Axis output sample data (expressed as 2's complement numbers).
** ------------------------------*/
typedef union
{
    struct
    {
        uint8_t _reserved_ : 2;
        uint8_t out_z_lsb : 6; /*  - OUT_Z_LSB register bits 2-7. (Bit 0 and 1 will always be 0).             */

    } b;
    uint8_t w;
} MMA8491Q_OUT_Z_LSB_t;

/*
** OUT_Z_LSB - Bit field mask definitions
*/
#define MMA8491Q_OUT_Z_LSB_OUT_Z_LSB_MASK ((uint8_t)0xFC)
#define MMA8491Q_OUT_Z_LSB_OUT_Z_LSB_SHIFT ((uint8_t)2)

/*------------------------------*/

#endif /* MMA8491Q_H_ */ 
