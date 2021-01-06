/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef MAG3110_H_
#define MAG3110_H_

/**
 **
 **  MAG3110 Sensor Internal Registers
 */
enum {
    MAG3110_DR_STATUS              = 0x00,
    MAG3110_OUT_X_MSB              = 0x01,
    MAG3110_OUT_X_LSB              = 0x02,
    MAG3110_OUT_Y_MSB              = 0x03,
    MAG3110_OUT_Y_LSB              = 0x04,
    MAG3110_OUT_Z_MSB              = 0x05,
    MAG3110_OUT_Z_LSB              = 0x06,
    MAG3110_WHO_AM_I               = 0x07,
    MAG3110_SYSMOD                 = 0x08,
    MAG3110_OFF_X_MSB              = 0x09,
    MAG3110_OFF_X_LSB              = 0x0A,
    MAG3110_OFF_Y_MSB              = 0x0B,
    MAG3110_OFF_Y_LSB              = 0x0C,
    MAG3110_OFF_Z_MSB              = 0x0D,
    MAG3110_OFF_Z_LSB              = 0x0E,
    MAG3110_DIE_TEMP               = 0x0F,
    MAG3110_CTRL_REG1              = 0x10,
    MAG3110_CTRL_REG2              = 0x11,
};

#define MAG3110_I2C_ADDRESS     (0x0E)  /* MAG3110 I2C Slave Address. */
#define MAG3110_WHOAMI_VALUE    (0xC4)  /* MAG3110 Who_Am_I Value. */



/*--------------------------------
** Register: DR_STATUS
** Enum: MAG3110_DR_STATUS
** --
** Offset : 0x00 - Data-ready status information
** ------------------------------*/
typedef union {
    struct {
        uint8_t                   xdr : 1; /*  - X-Axis new Data Available.                                               */

        uint8_t                   ydr : 1; /*  - Y-Axis new data available.                                               */

        uint8_t                   zdr : 1; /*  - Z-Axis new data available.                                               */

        uint8_t                 zyxdr : 1; /*  - X or Y or Z-Axis new data available.                                     */

        uint8_t                   xow : 1; /*  - X-Axis data overwrite.                                                   */

        uint8_t                   yow : 1; /*  - Y-Axis data overwrite.                                                   */

        uint8_t                   zow : 1; /*  - Z-Axis data overwrite.                                                   */

        uint8_t                 zyxow : 1; /*  - X, Y, Z-Axis data overwrite.                                             */

    } b;
    uint8_t w;
} MAG3110_DR_STATUS_t;


/*
** DR_STATUS - Bit field mask definitions 
*/
#define MAG3110_DR_STATUS_XDR_MASK     ((uint8_t) 0x01)
#define MAG3110_DR_STATUS_XDR_SHIFT    ((uint8_t)    0)

#define MAG3110_DR_STATUS_YDR_MASK     ((uint8_t) 0x02)
#define MAG3110_DR_STATUS_YDR_SHIFT    ((uint8_t)    1)

#define MAG3110_DR_STATUS_ZDR_MASK     ((uint8_t) 0x04)
#define MAG3110_DR_STATUS_ZDR_SHIFT    ((uint8_t)    2)

#define MAG3110_DR_STATUS_ZYXDR_MASK   ((uint8_t) 0x08)
#define MAG3110_DR_STATUS_ZYXDR_SHIFT  ((uint8_t)    3)

#define MAG3110_DR_STATUS_XOW_MASK     ((uint8_t) 0x10)
#define MAG3110_DR_STATUS_XOW_SHIFT    ((uint8_t)    4)

#define MAG3110_DR_STATUS_YOW_MASK     ((uint8_t) 0x20)
#define MAG3110_DR_STATUS_YOW_SHIFT    ((uint8_t)    5)

#define MAG3110_DR_STATUS_ZOW_MASK     ((uint8_t) 0x40)
#define MAG3110_DR_STATUS_ZOW_SHIFT    ((uint8_t)    6)

#define MAG3110_DR_STATUS_ZYXOW_MASK   ((uint8_t) 0x80)
#define MAG3110_DR_STATUS_ZYXOW_SHIFT  ((uint8_t)    7)


/*
** DR_STATUS - Bit field value definitions  
*/
#define MAG3110_DR_STATUS_XDR_DRDY              ((uint8_t) 0x01)  /*  - Set to 1 whenever new X-axis data acquisition is  */
                                                                  /*  completed. XDR is cleared any time OUT_X_MSB        */
                                                                  /*  register is read.                                   */
#define MAG3110_DR_STATUS_YDR_DRDY              ((uint8_t) 0x02)  /*  - Set to 1 whenever new Y-axis data acquisition is  */
                                                                  /*  completed. YDR is cleared any time OUT_Y_MSB        */
                                                                  /*  register is read.                                   */
#define MAG3110_DR_STATUS_ZDR_DRDY              ((uint8_t) 0x04)  /*  - Set to 1 whenever new Z-axis data acquisition is  */
                                                                  /*  completed. ZDR is cleared any time OUT_Z_MSB        */
                                                                  /*  register is read.                                   */
#define MAG3110_DR_STATUS_ZYXDR_DRDY            ((uint8_t) 0x08)  /*  - Signals that new acquisition for any of the       */
                                                                  /*  enabled channels is available. ZYXDR is cleared     */
                                                                  /*  when the high-bytes of the data (OUT_X_MSB,         */
                                                                  /*  OUT_Y_MSB, OUT_Z_MSB) of all the enabled channels   */
                                                                  /*  are read.                                           */
#define MAG3110_DR_STATUS_XOW_OWR               ((uint8_t) 0x10)  /*  - Set to 1 whenever new X-axis acquisition is       */
                                                                  /*  completed before the retrieval of the previous      */
                                                                  /*  data. When this occurs the previous data is         */
                                                                  /*  overwritten. XOW is cleared any time OUT_X_MSB      */
                                                                  /*  register is read.                                   */
#define MAG3110_DR_STATUS_YOW_OWR               ((uint8_t) 0x20)  /*  - Set to 1 whenever new Y-axis acquisition is       */
                                                                  /*  completed before the retrieval of the previous      */
                                                                  /*  data. When this occurs the previous data is         */
                                                                  /*  overwritten. YOW is cleared any time OUT_Y_MSB      */
                                                                  /*  register is read.                                   */
#define MAG3110_DR_STATUS_ZOW_OWR               ((uint8_t) 0x40)  /*  - Set to 1 whenever new Z-axis acquisition is       */
                                                                  /*  completed before the retrieval of the previous      */
                                                                  /*  data. When this occurs the previous data is         */
                                                                  /*  overwritten. ZOW is cleared any time OUT_Z_MSB      */
                                                                  /*  register is read.                                   */
#define MAG3110_DR_STATUS_ZYXOW_OWR             ((uint8_t) 0x80)  /*  - Set to 1 whenever new data is acquired before     */
                                                                  /*  completing the retrieval of the previous set. This  */
                                                                  /*  event occurs when the content of at least one data  */
                                                                  /*  register (i.e. OUT_X, OUT_Y, OUT_Z) has been        */
                                                                  /*  overwritten. ZYXOW is cleared when the highbytes of */
                                                                  /*  the data (OUT_X_MSB, OUT_Y_MSB, OUT_Z_MSB) of all   */
                                                                  /*  active channels are read.                           */
/*------------------------------*/




/*--------------------------------
** Register: OUT_X_MSB
** Enum: MAG3110_OUT_X_MSB
** --
** Offset : 0x01 - Bits 8-15 of 16-bit real-time Magnetic Field Strength sample expressed as signed 2's complement numbers.
** ------------------------------*/
typedef uint8_t MAG3110_OUT_X_MSB_t;


/*--------------------------------
** Register: OUT_X_LSB
** Enum: MAG3110_OUT_X_LSB
** --
** Offset : 0x02 - Bits 0-7 of 16-bit real-time Magnetic Field Strength sample expressed as signed 2's complement numbers.
** ------------------------------*/
typedef uint8_t MAG3110_OUT_X_LSB_t;


/*--------------------------------
** Register: OUT_Y_MSB
** Enum: MAG3110_OUT_Y_MSB
** --
** Offset : 0x03 - Bits 8-15 of 16-bit real-time Magnetic Field Strength sample expressed as signed 2's complement numbers.
** ------------------------------*/
typedef uint8_t MAG3110_OUT_Y_MSB_t;


/*--------------------------------
** Register: OUT_Y_LSB
** Enum: MAG3110_OUT_Y_LSB
** --
** Offset : 0x04 - Bits 0-7 of 16-bit real-time Magnetic Field Strength sample expressed as signed 2's complement numbers.
** ------------------------------*/
typedef uint8_t MAG3110_OUT_Y_LSB_t;


/*--------------------------------
** Register: OUT_Z_MSB
** Enum: MAG3110_OUT_Z_MSB
** --
** Offset : 0x05 - Bits 8-15 of 16-bit real-time Magnetic Field Strength sample expressed as signed 2's complement numbers.
** ------------------------------*/
typedef uint8_t MAG3110_OUT_Z_MSB_t;


/*--------------------------------
** Register: OUT_Z_LSB
** Enum: MAG3110_OUT_Z_LSB
** --
** Offset : 0x06 - Bits 0-7 of 16-bit real-time Magnetic Field Strength sample expressed as signed 2's complement numbers.
** ------------------------------*/
 
typedef uint8_t MAG3110_OUT_Z_LSB_t;



/*--------------------------------
** Register: WHO_AM_I
** Enum: MAG3110_WHO_AM_I
** --
** Offset : 0x07 - Device identification register containing Fixed Device ID Number.
** ------------------------------*/
typedef uint8_t MAG3110_WHO_AM_I_t;




/*--------------------------------
** Register: SYSMOD
** Enum: MAG3110_SYSMOD
** --
** Offset : 0x08 - The read-only system mode register indicating the current device operating mode.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                sysmod : 2; /*  - System mode data bits 0-1. (Bits 7-2 will always read 0.)                */

    } b;
    uint8_t w;
} MAG3110_SYSMOD_t;


/*
** SYSMOD - Bit field mask definitions 
*/
#define MAG3110_SYSMOD_SYSMOD_MASK   ((uint8_t) 0x03)
#define MAG3110_SYSMOD_SYSMOD_SHIFT  ((uint8_t)    0)


/*
** SYSMOD - Bit field value definitions  
*/
#define MAG3110_SYSMOD_SYSMOD_STANDBY        ((uint8_t) 0x00)  /*  - STANDBY Mode.                                        */
#define MAG3110_SYSMOD_SYSMOD_ACTIVE_RAW     ((uint8_t) 0x01)  /*  - ACTIVE Mode, RAW Data.                               */
#define MAG3110_SYSMOD_SYSMOD_ACTIVE         ((uint8_t) 0x02)  /*  - ACTIVE Mode, non-RAW user-corrected Data.            */
/*------------------------------*/




/*--------------------------------
** Register: OFF_X_MSB
** Enum: MAG3110_OFF_X_MSB
** --
** Offset : 0x09 - Bits 7-14 of X-Axis user defined offsets in 2's complement format which are used when CTRL_REG2[RAW] = 0.
** ------------------------------*/
typedef uint8_t MAG3110_OFF_X_MSB_t;



/*--------------------------------
** Register: OFF_X_LSB
** Enum: MAG3110_OFF_X_LSB
** --
** Offset : 0x0A - Bits 0-6 of X-Axis user defined offsets in 2's complement format which are used when CTRL_REG2[RAW] = 0.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 1;
        uint8_t             off_x_lsb : 7; /*  - OFF_X_LSB register bits 1-7. (Bit 0 will always be 0.)                   */

    } b;
    uint8_t w;
} MAG3110_OFF_X_LSB_t;


/*
** OFF_X_LSB - Bit field mask definitions 
*/
#define MAG3110_OFF_X_LSB_OFF_X_LSB_MASK   ((uint8_t) 0xFE)
#define MAG3110_OFF_X_LSB_OFF_X_LSB_SHIFT  ((uint8_t)    1)


/*------------------------------*/



/*--------------------------------
** Register: OFF_Y_MSB
** Enum: MAG3110_OFF_Y_MSB
** --
** Offset : 0x0B - Bits 7-14 of Y-Axis user defined offsets in 2's complement format which are used when CTRL_REG2[RAW] = 0.
** ------------------------------*/
typedef uint8_t MAG3110_OFF_Y_MSB_t;



/*--------------------------------
** Register: OFF_Y_LSB
** Enum: MAG3110_OFF_Y_LSB
** --
** Offset : 0x0C - Bits 0-6 of Y-Axis user defined offsets in 2's complement format which are used when CTRL_REG2[RAW] = 0.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 1;
        uint8_t             off_y_lsb : 7; /*  - OFF_Y_LSB register bits 1-7. (Bit 0 will always be 0.)                   */

    } b;
    uint8_t w;
} MAG3110_OFF_Y_LSB_t;


/*
** OFF_Y_LSB - Bit field mask definitions 
*/
#define MAG3110_OFF_Y_LSB_OFF_Y_LSB_MASK   ((uint8_t) 0xFE)
#define MAG3110_OFF_Y_LSB_OFF_Y_LSB_SHIFT  ((uint8_t)    1)


/*------------------------------*/



/*--------------------------------
** Register: OFF_Z_MSB
** Enum: MAG3110_OFF_Z_MSB
** --
** Offset : 0x0D - Bits 7-14 of Z-Axis user defined offsets in 2's complement format which are used when CTRL_REG2[RAW] = 0.
** ------------------------------*/
typedef uint8_t MAG3110_OFF_Z_MSB_t;



/*--------------------------------
** Register: OFF_Z_LSB
** Enum: MAG3110_OFF_Z_LSB
** --
** Offset : 0x0E - Bits 0-6 of Z-Axis user defined offsets in 2's complement format which are used when CTRL_REG2[RAW] = 0.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 1;
        uint8_t             off_z_lsb : 7; /*  - OFF_Z_LSB register bits 1-7. (Bit 0 will always be 0.)                   */

    } b;
    uint8_t w;
} MAG3110_OFF_Z_LSB_t;


/*
** OFF_Z_LSB - Bit field mask definitions 
*/
#define MAG3110_OFF_Z_LSB_OFF_Z_LSB_MASK   ((uint8_t) 0xFE)
#define MAG3110_OFF_Z_LSB_OFF_Z_LSB_SHIFT  ((uint8_t)    1)


/*------------------------------*/




/*--------------------------------
** Register: DIE_TEMP
** Enum: MAG3110_DIE_TEMP
** --
** Offset : 0x0F - The die temperature in °C expressed as an 8-bit 2's complement number.
** ------------------------------*/
typedef uint8_t MAG3110_DIE_TEMP_t;




/*--------------------------------
** Register: CTRL_REG1
** Enum: MAG3110_CTRL_REG1
** --
** Offset : 0x10 - Control Register 1: Modes, Trigger, ODR, OSR.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                    ac : 1; /*  - Operating Mode.                                                          */

        uint8_t                    tm : 1; /*  - Trigger immediate measurement (if the ac bit is set to standby).         */

        uint8_t                    fr : 1; /*  - Fast Read selection Mode. 8-bit values are read from the MSB registers   */
                                           /*  (Auto-increment skips over the LSB register in burst-read mode).           */

        uint8_t                    os : 2; /*  - These bits configures the over sampling ratio for the measurement.       */

        uint8_t                    dr : 3; /*  - These bits configures the Output Data Rate.                              */

    } b;
    uint8_t w;
} MAG3110_CTRL_REG1_t;


/*
** CTRL_REG1 - Bit field mask definitions 
*/
#define MAG3110_CTRL_REG1_AC_MASK   ((uint8_t) 0x01)
#define MAG3110_CTRL_REG1_AC_SHIFT  ((uint8_t)    0)

#define MAG3110_CTRL_REG1_TM_MASK   ((uint8_t) 0x02)
#define MAG3110_CTRL_REG1_TM_SHIFT  ((uint8_t)    1)

#define MAG3110_CTRL_REG1_FR_MASK   ((uint8_t) 0x04)
#define MAG3110_CTRL_REG1_FR_SHIFT  ((uint8_t)    2)

#define MAG3110_CTRL_REG1_OS_MASK   ((uint8_t) 0x18)
#define MAG3110_CTRL_REG1_OS_SHIFT  ((uint8_t)    3)

#define MAG3110_CTRL_REG1_DR_MASK   ((uint8_t) 0xE0)
#define MAG3110_CTRL_REG1_DR_SHIFT  ((uint8_t)    5)


/*
** CTRL_REG1 - Bit field value definitions  
*/
#define MAG3110_CTRL_REG1_AC_STANDBY            ((uint8_t) 0x00)  /*  - Standby Mode.                                     */
#define MAG3110_CTRL_REG1_AC_ACTIVE             ((uint8_t) 0x01)  /*  - Active Mode.                                      */
#define MAG3110_CTRL_REG1_TM_NORMAL             ((uint8_t) 0x00)  /*  - Normal operation based on AC condition.           */
#define MAG3110_CTRL_REG1_TM_TRIGGER            ((uint8_t) 0x02)  /*  - Trigger Measurement.                              */
#define MAG3110_CTRL_REG1_FR_FULL               ((uint8_t) 0x00)  /*  - The full 16-bit values are read.                  */
#define MAG3110_CTRL_REG1_FR_FAST               ((uint8_t) 0x04)  /*  - 8-bit values read from the MSB registers.         */
#define MAG3110_CTRL_REG1_OS_OSR_16             ((uint8_t) 0x00)  /*  - OSR = 16.                                         */
#define MAG3110_CTRL_REG1_OS_OSR_32             ((uint8_t) 0x08)  /*  - OSR = 32.                                         */
#define MAG3110_CTRL_REG1_OS_OSR_64             ((uint8_t) 0x10)  /*  - OSR = 64.                                         */
#define MAG3110_CTRL_REG1_OS_OSR_128            ((uint8_t) 0x18)  /*  - OSR = 128.                                        */
#define MAG3110_CTRL_REG1_DR_ODR_0              ((uint8_t) 0x00)  /*  - ADC Rate = 1280Hz; Output Rate = ADC/OS.          */
#define MAG3110_CTRL_REG1_DR_ODR_1              ((uint8_t) 0x20)  /*  - ADC Rate = 640Hz; Output Rate = ADC/OS.           */
#define MAG3110_CTRL_REG1_DR_ODR_2              ((uint8_t) 0x40)  /*  - ADC Rate = 320Hz; Output Rate = ADC/OS.           */
#define MAG3110_CTRL_REG1_DR_ODR_3              ((uint8_t) 0x60)  /*  - ADC Rate = 160Hz; Output Rate = ADC/OS.           */
#define MAG3110_CTRL_REG1_DR_ODR_4              ((uint8_t) 0x80)  /*  - ADC Rate = 80Hz; Output Rate = ADC/OS.            */
#define MAG3110_CTRL_REG1_DR_ODR_5              ((uint8_t) 0xa0)  /*  - ADC Rate = 80Hz; Output Rate = ADC/OS.            */
#define MAG3110_CTRL_REG1_DR_ODR_6              ((uint8_t) 0xc0)  /*  - ADC Rate = 80Hz; Output Rate = ADC/OS.            */
#define MAG3110_CTRL_REG1_DR_ODR_7              ((uint8_t) 0xe0)  /*  - ADC Rate = 80Hz; Output Rate = ADC/OS.            */
/*------------------------------*/




/*--------------------------------
** Register: CTRL_REG2
** Enum: MAG3110_CTRL_REG2
** --
** Offset : 0x11 - Control Register 2: Correction, Reset.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 4;
        uint8_t               mag_rst : 1; /*  - Magnetic Sensor Reset (One-Shot) Bit.                                    */

        uint8_t                   raw : 1; /*  - Data output correction Bit.                                              */

        uint8_t _reserved_1           : 1;
        uint8_t          auto_msrt_en : 1; /*  - Automatic Magnetic Sensor Reset Bit.                                     */

    } b;
    uint8_t w;
} MAG3110_CTRL_REG2_t;


/*
** CTRL_REG2 - Bit field mask definitions 
*/
#define MAG3110_CTRL_REG2_MAG_RST_MASK        ((uint8_t) 0x10)
#define MAG3110_CTRL_REG2_MAG_RST_SHIFT       ((uint8_t)    4)

#define MAG3110_CTRL_REG2_RAW_MASK            ((uint8_t) 0x20)
#define MAG3110_CTRL_REG2_RAW_SHIFT           ((uint8_t)    5)

#define MAG3110_CTRL_REG2_AUTO_MSRT_EN_MASK   ((uint8_t) 0x80)
#define MAG3110_CTRL_REG2_AUTO_MSRT_EN_SHIFT  ((uint8_t)    7)


/*
** CTRL_REG2 - Bit field value definitions  
*/
#define MAG3110_CTRL_REG2_MAG_RST_EN            ((uint8_t) 0x10)  /*  - Reset cycle initiate or Reset cycle busy/active.  */
#define MAG3110_CTRL_REG2_RAW_NORMAL            ((uint8_t) 0x00)  /*  - The data values are corrected by the user offset  */
                                                                  /*  register values.                                    */
#define MAG3110_CTRL_REG2_RAW_RAW               ((uint8_t) 0x20)  /*  - The data values are not corrected by the user     */
                                                                  /*  offset register values.                             */
#define MAG3110_CTRL_REG2_AUTO_MSRT_EN_DIS      ((uint8_t) 0x00)  /*  - Automatic magnetic sensor resets disabled.        */
#define MAG3110_CTRL_REG2_AUTO_MSRT_EN_EN       ((uint8_t) 0x80)  /*  - Automatic magnetic sensor resets enabled.         */
/*------------------------------*/



#endif  /* MAG3110_H_ */ 
