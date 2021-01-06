/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** 
 * @file fxas21002.h
 * @brief The fxas21002.h contains the fxas21002 sensor register definitions and its bit mask.
*/

#ifndef FXAS21002_H_
#define FXAS21002_H_

/**
 **  FXAS21002 I2C Address
 */
#define   FXAS21002_I2C_ADDRESS     0x20

/**
 **
 ** @brief The FXAS21002 Sensor Register  Map.
 */
enum {
     FXAS21002_STATUS             = 0x00,
     FXAS21002_OUT_X_MSB          = 0x01,
     FXAS21002_OUT_X_LSB          = 0x02,
     FXAS21002_OUT_Y_MSB          = 0x03,
     FXAS21002_OUT_Y_LSB          = 0x04,
     FXAS21002_OUT_Z_MSB          = 0x05,
     FXAS21002_OUT_Z_LSB          = 0x06,
     FXAS21002_DR_STATUS          = 0x07,
     FXAS21002_F_STATUS           = 0x08,
     FXAS21002_F_SETUP            = 0x09,
     FXAS21002_F_EVENT            = 0x0A,
     FXAS21002_INT_SRC_FLAG       = 0x0B,
     FXAS21002_WHO_AM_I           = 0x0C,
     FXAS21002_CTRL_REG0          = 0x0D,
     FXAS21002_RT_CFG             = 0x0E,
     FXAS21002_RT_SRC             = 0x0F,
     FXAS21002_RT_THS             = 0x10,
     FXAS21002_RT_COUNT           = 0x11,
     FXAS21002_TEMP               = 0x12,
     FXAS21002_CTRL_REG1          = 0x13,
     FXAS21002_CTRL_REG2          = 0x14,
     FXAS21002_CTRL_REG3          = 0x15,
};


/*--------------------------------
** Register: STATUS
** Enum: FXAS21002_STATUS
** --
** Offset : 0x00 - Alias for DR_STATUS or F_STATUS.
** ------------------------------*/
typedef uint8_t FXAS21002_STATUS_t;



/*--------------------------------
** Register: OUT_X_MSB
** Enum: FXAS21002_OUT_X_MSB
** --
** Offset : 0x01 - 8 MSBs of 16 bit X-axis data sample
** ------------------------------*/
typedef uint8_t FXAS21002_OUT_X_MSB_t;


/*--------------------------------
** Register: OUT_X_LSB
** Enum: FXAS21002_OUT_X_LSB
** --
** Offset : 0x02 - 8 LSBs of 16 bit X-axis data sample
** ------------------------------*/
typedef uint8_t FXAS21002_OUT_X_LSB_t;



/*--------------------------------
** Register: OUT_Y_MSB
** Enum: FXAS21002_OUT_Y_MSB
** --
** Offset : 0x03 - 8 MSBs of 16 bit Y-axis data sample
** ------------------------------*/
typedef uint8_t FXAS21002_OUT_Y_MSB_t;


/*--------------------------------
** Register: OUT_Y_LSB
** Enum: FXAS21002_OUT_Y_LSB
** --
** Offset : 0x04 - 8 LSBs of 16 bit Y-axis data sample
** ------------------------------*/
typedef uint8_t FXAS21002_OUT_Y_LSB_t;



/*--------------------------------
** Register: OUT_Z_MSB
** Enum: FXAS21002_OUT_Z_MSB
** --
** Offset : 0x05 - 8 MSBs of 16 bit Z-axis data sample
** ------------------------------*/
typedef uint8_t FXAS21002_OUT_Z_MSB_t;


/*--------------------------------
** Register: OUT_Z_LSB
** Enum: FXAS21002_OUT_Z_LSB
** --
** Offset : 0x06 - 8 LSBs of 16 bit Z-axis data sample
** ------------------------------*/
typedef uint8_t FXAS21002_OUT_Z_LSB_t;



/*--------------------------------
** Register: DR_STATUS
** Enum: FXAS21002_DR_STATUS
** --
** Offset : 0x07 - Data-ready status information (FIFO disabled by setting F_SETUP :: F_MODE = 0)
** ------------------------------*/
typedef union {
    struct {
        uint8_t                   xdr : 1; /*  X-axis new data available.                                                 */

        uint8_t                   ydr : 1; /*  Y-axis new data available.                                                 */

        uint8_t                   zdr : 1; /*  Z-axis new data available.                                                 */

        uint8_t                 zyxdr : 1; /*  X-, Y-, and Z-axis data available.                                         */

        uint8_t                   xow : 1; /*  X-axis data overwrite.                                                     */

        uint8_t                   yow : 1; /*  Y-axis data overwrite.                                                     */

        uint8_t                   zow : 1; /*  Z-axis data overwrite.                                                     */

        uint8_t                 zyxow : 1; /*  X-, Y-, Z-axis data overwrite.                                             */

    } b;
    uint8_t w;
} FXAS21002_DR_STATUS_t;


/*
** DR_STATUS - Bit field mask definitions 
*/
#define FXAS21002_DR_STATUS_XDR_MASK     ((uint8_t) 0x01)
#define FXAS21002_DR_STATUS_XDR_SHIFT    ((uint8_t)    0)

#define FXAS21002_DR_STATUS_YDR_MASK     ((uint8_t) 0x02)
#define FXAS21002_DR_STATUS_YDR_SHIFT    ((uint8_t)    1)

#define FXAS21002_DR_STATUS_ZDR_MASK     ((uint8_t) 0x04)
#define FXAS21002_DR_STATUS_ZDR_SHIFT    ((uint8_t)    2)

#define FXAS21002_DR_STATUS_ZYXDR_MASK   ((uint8_t) 0x08)
#define FXAS21002_DR_STATUS_ZYXDR_SHIFT  ((uint8_t)    3)

#define FXAS21002_DR_STATUS_XOW_MASK     ((uint8_t) 0x10)
#define FXAS21002_DR_STATUS_XOW_SHIFT    ((uint8_t)    4)

#define FXAS21002_DR_STATUS_YOW_MASK     ((uint8_t) 0x20)
#define FXAS21002_DR_STATUS_YOW_SHIFT    ((uint8_t)    5)

#define FXAS21002_DR_STATUS_ZOW_MASK     ((uint8_t) 0x40)
#define FXAS21002_DR_STATUS_ZOW_SHIFT    ((uint8_t)    6)

#define FXAS21002_DR_STATUS_ZYXOW_MASK   ((uint8_t) 0x80)
#define FXAS21002_DR_STATUS_ZYXOW_SHIFT  ((uint8_t)    7)


/*
** DR_STATUS - Bit field value definitions  
*/
#define FXAS21002_DR_STATUS_XDR_DRDY              ((uint8_t) 0x01)  /*  Set to 1 whenever a new X-axis data acquisition   */
                                                                    /*  is completed. Cleared anytime the OUT_X_MSB       */
                                                                    /*  register is read.                                 */
#define FXAS21002_DR_STATUS_YDR_DRDY              ((uint8_t) 0x02)  /*  Set to 1 whenever a new Y-axis data acquisition   */
                                                                    /*  is completed. Cleared anytime the OUT_Y_MSB       */
                                                                    /*  register is read.                                 */
#define FXAS21002_DR_STATUS_ZDR_DRDY              ((uint8_t) 0x04)  /*  Set to 1 whenever a new Z-axis data acquisition   */
                                                                    /*  is completed. Cleared anytime the OUT_Z_MSB       */
                                                                    /*  register is read.                                 */
#define FXAS21002_DR_STATUS_ZYXDR_DRDY            ((uint8_t) 0x08)  /*  Cleared when the high-bytes of the acceleration   */
                                                                    /*  data (OUT_X_MSB, OUT_Y_MSB, OUT_Z_MSB) are read.  */
#define FXAS21002_DR_STATUS_XOW_OWR               ((uint8_t) 0x10)  /*  Asserted whenever a new X-axis acquisition is     */
                                                                    /*  completed before the retrieval of the previous    */
                                                                    /*  data.                                             */
#define FXAS21002_DR_STATUS_YOW_OWR               ((uint8_t) 0x20)  /*  Asserted whenever a new Y-axis acquisition is     */
                                                                    /*  completed before the retrieval of the previous    */
                                                                    /*  data.                                             */
#define FXAS21002_DR_STATUS_ZOW_OWR               ((uint8_t) 0x40)  /*  Asserted whenever a new Z-axis acquisition is     */
                                                                    /*  completed before the retrieval of the previous    */
                                                                    /*  data.                                             */
#define FXAS21002_DR_STATUS_ZYXOW_OWR             ((uint8_t) 0x80)  /*  Asserted whenever new X-, Y-, and Z-axis data is  */
                                                                    /*  acquired before completing the retrieval of the   */
                                                                    /*  previous set.                                     */
/*------------------------------*/



/*--------------------------------
** Register: F_STATUS
** Enum: FXAS21002_F_STATUS
** --
** Offset : 0x08 - FIFO status information (FIFO enabled by setting F_SETUP :: F_MODE > 0)
** ------------------------------*/
typedef union {
    struct {
        uint8_t                 f_cnt : 6; /*  FIFO sample counter; indicates the number of samples currently stored in   */
                                           /*  the FIFO.                                                                  */

        uint8_t                f_wmkf : 1; /*  FIFO sample count greater than or equal to the watermark count (F_SETUP :: */
                                           /*  F_WMRK) has been detected.                                                 */

        uint8_t                 f_ovf : 1; /*  FIFO overflow event, such as when F_CNT = 32 and a new sample arrives,     */
                                           /*  asserts the F_OVF flag.                                                    */

    } b;
    uint8_t w;
} FXAS21002_F_STATUS_t;


/*
** F_STATUS - Bit field mask definitions 
*/
#define FXAS21002_F_STATUS_F_CNT_MASK    ((uint8_t) 0x3F)
#define FXAS21002_F_STATUS_F_CNT_SHIFT   ((uint8_t)    0)

#define FXAS21002_F_STATUS_F_WMKF_MASK   ((uint8_t) 0x40)
#define FXAS21002_F_STATUS_F_WMKF_SHIFT  ((uint8_t)    6)

#define FXAS21002_F_STATUS_F_OVF_MASK    ((uint8_t) 0x80)
#define FXAS21002_F_STATUS_F_OVF_SHIFT   ((uint8_t)    7)


/*
** F_STATUS - Bit field value definitions  
*/
#define FXAS21002_F_STATUS_F_WMKF_DETECT         ((uint8_t) 0x40)  /*  FIFO Watermark event has been detected.            */
#define FXAS21002_F_STATUS_F_OVF_DETECT          ((uint8_t) 0x80)  /*  FIFO Overflow event has been detected.             */
/*------------------------------*/



/*--------------------------------
** Register: F_SETUP
** Enum: FXAS21002_F_SETUP
** --
** Offset : 0x09 - FIFO configuration
** ------------------------------*/
typedef union {
    struct {
        uint8_t                f_wmrk : 6; /*  FIFO operating mode selection.                                             */

        uint8_t                f_mode : 2; /*  FIFO sample count watermark setting.                                       */

    } b;
    uint8_t w;
} FXAS21002_F_SETUP_t;


/*
** F_SETUP - Bit field mask definitions 
*/
#define FXAS21002_F_SETUP_F_WMRK_MASK   ((uint8_t) 0x3F)
#define FXAS21002_F_SETUP_F_WMRK_SHIFT  ((uint8_t)    0)

#define FXAS21002_F_SETUP_F_MODE_MASK   ((uint8_t) 0xC0)
#define FXAS21002_F_SETUP_F_MODE_SHIFT  ((uint8_t)    6)


/*
** F_SETUP - Bit field value definitions  
*/
#define FXAS21002_F_SETUP_F_MODE_FIFO_OFF       ((uint8_t) 0x00)  /*  FIFO is disabled.                                   */
#define FXAS21002_F_SETUP_F_MODE_CIR_MODE       ((uint8_t) 0x40)  /*  FIFO is in Circular Buffer mode.                    */
#define FXAS21002_F_SETUP_F_MODE_STOP_MODE      ((uint8_t) 0x80)  /*  FIFO is in Stop mode.                               */
/*------------------------------*/



/*--------------------------------
** Register: F_EVENT
** Enum: FXAS21002_F_EVENT
** --
** Offset : 0x0A - FIFO event status
** ------------------------------*/
typedef union {
    struct {
        uint8_t               fe_time : 5; /*  Number of ODR periods elapsed since F_EVENT was set.                       */

        uint8_t               f_event : 1; /*  FIFO Event: Indicates if either F_WMKF or F_OVF flags are set (logical     */
                                           /*  OR).                                                                       */

    } b;
    uint8_t w;
} FXAS21002_F_EVENT_t;


/*
** F_EVENT - Bit field mask definitions 
*/
#define FXAS21002_F_EVENT_FE_TIME_MASK   ((uint8_t) 0x1F)
#define FXAS21002_F_EVENT_FE_TIME_SHIFT  ((uint8_t)    0)

#define FXAS21002_F_EVENT_F_EVENT_MASK   ((uint8_t) 0x20)
#define FXAS21002_F_EVENT_F_EVENT_SHIFT  ((uint8_t)    5)


/*
** F_EVENT - Bit field value definitions  
*/
#define FXAS21002_F_EVENT_F_EVENT_DETECTED      ((uint8_t) 0x20)  /*  FIFO event was detected                             */
/*------------------------------*/



/*--------------------------------
** Register: INT_SRC_FLAG
** Enum: FXAS21002_INT_SRC_FLAG
** --
** Offset : 0x0B - Interrupt source status
** ------------------------------*/
typedef union {
    struct {
        uint8_t              src_drdy : 1; /*  Data ready event source flag.                                              */

        uint8_t                src_rt : 1; /*  Rate threshold event source flag.                                          */

        uint8_t              src_fifo : 1; /*  FIFO event source flag.                                                    */

        uint8_t               bootend : 1; /*  Boot sequence complete event flag.                                         */

    } b;
    uint8_t w;
} FXAS21002_INT_SRC_FLAG_t;


/*
** INT_SRC_FLAG - Bit field mask definitions 
*/
#define FXAS21002_INT_SRC_FLAG_SRC_DRDY_MASK   ((uint8_t) 0x01)
#define FXAS21002_INT_SRC_FLAG_SRC_DRDY_SHIFT  ((uint8_t)    0)

#define FXAS21002_INT_SRC_FLAG_SRC_RT_MASK     ((uint8_t) 0x02)
#define FXAS21002_INT_SRC_FLAG_SRC_RT_SHIFT    ((uint8_t)    1)

#define FXAS21002_INT_SRC_FLAG_SRC_FIFO_MASK   ((uint8_t) 0x04)
#define FXAS21002_INT_SRC_FLAG_SRC_FIFO_SHIFT  ((uint8_t)    2)

#define FXAS21002_INT_SRC_FLAG_BOOTEND_MASK    ((uint8_t) 0x08)
#define FXAS21002_INT_SRC_FLAG_BOOTEND_SHIFT   ((uint8_t)    3)


/*
** INT_SRC_FLAG - Bit field value definitions  
*/
#define FXAS21002_INT_SRC_FLAG_SRC_DRDY_READY        ((uint8_t) 0x01)  /*  Asserted whenever a data-ready event triggers  */
                                                                       /*  the interrupt.                                 */
#define FXAS21002_INT_SRC_FLAG_SRC_RT_THRESH         ((uint8_t) 0x02)  /*  Indicates that the rate threshold event flag   */
                                                                       /*  triggered the interrupt.                       */
#define FXAS21002_INT_SRC_FLAG_SRC_FIFO_EVENT        ((uint8_t) 0x04)  /*  F_OVF or F_WMKF are set, provided the FIFO     */
                                                                       /*  interrupt is enabled.                          */
#define FXAS21002_INT_SRC_FLAG_BOOTEND_BOOT_DONE     ((uint8_t) 0x08)  /*  Boot sequence is complete.                     */
/*------------------------------*/



/*--------------------------------
** Register: WHO_AM_I
** Enum: FXAS21002_WHO_AM_I
** --
** Offset : 0x0C - The WHO_AM_I register contains the device idenifier.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                whoami; /*  The WHO_AM_I register contains the device identifier which is factory          */
                                       /*  programmed.                                                                    */

    } b;
    uint8_t w;
} FXAS21002_WHO_AM_I_t;


/*
** WHO_AM_I - Bit field mask definitions 
*/
#define FXAS21002_WHO_AM_I_WHOAMI_MASK   ((uint8_t) 0xFF)
#define FXAS21002_WHO_AM_I_WHOAMI_SHIFT  ((uint8_t)    0)


/*
** WHO_AM_I - Bit field value definitions  
*/
#define FXAS21002_WHO_AM_I_WHOAMI_OLD_VALUE     ((uint8_t) 0xd1)  /*  FXAS21000                       */
#define FXAS21002_WHO_AM_I_WHOAMI_PRE_VALUE     ((uint8_t) 0xd6)  /*  Engineering Samples             */
#define FXAS21002_WHO_AM_I_WHOAMI_PROD_VALUE    ((uint8_t) 0xd7)  /*  FXAS21002 Rev 2.1 (production)  */
/*------------------------------*/



/*--------------------------------
** Register: CTRL_REG0
** --
** Offset : 0x0D - Used for general control and configuration.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                    fs : 2; /*  Full-scale range selection.                                                */

        uint8_t                hpf_en : 1; /*  High-pass filter enable. The high-pass filter is initialized on operating  */
                                           /*  mode and ODR change. When enabled, the HPF is applied to the angular rate  */
                                           /*  data supplied to the output registers/FIFO and the embedded rate threshold */
                                           /*  algorithm.                                                                 */

        uint8_t                   sel : 2; /*  High-pass filter cutoff frequency selection.                               */

        uint8_t                  spiw : 1; /*  SPI interface mode selection.                                              */

        uint8_t                    bw : 2; /*  Bandwidth selects the cut-off frequency of the digital low-pass filter.    */

    } b;
    uint8_t w;
} FXAS21002_CTRL_REG0_t;


/*
** CTRL_REG0 - Bit field mask definitions 
*/
#define FXAS21002_CTRL_REG0_FS_MASK       ((uint8_t) 0x03)
#define FXAS21002_CTRL_REG0_FS_SHIFT      ((uint8_t)    0)

#define FXAS21002_CTRL_REG0_HPF_EN_MASK   ((uint8_t) 0x04)
#define FXAS21002_CTRL_REG0_HPF_EN_SHIFT  ((uint8_t)    2)

#define FXAS21002_CTRL_REG0_SEL_MASK      ((uint8_t) 0x18)
#define FXAS21002_CTRL_REG0_SEL_SHIFT     ((uint8_t)    3)

#define FXAS21002_CTRL_REG0_SPIW_MASK     ((uint8_t) 0x20)
#define FXAS21002_CTRL_REG0_SPIW_SHIFT    ((uint8_t)    5)

#define FXAS21002_CTRL_REG0_BW_MASK       ((uint8_t) 0xC0)
#define FXAS21002_CTRL_REG0_BW_SHIFT      ((uint8_t)    6)


/*
** CTRL_REG0 - Bit field value definitions  
*/
#define FXAS21002_CTRL_REG0_FS_DPS2000            ((uint8_t) 0x00)  /*  2000 degrees per second (4000 dps if CTRL_REG3 :  */
                                                                    /*  FS_DOUBLE = 1).                                   */
#define FXAS21002_CTRL_REG0_FS_DPS1000            ((uint8_t) 0x01)  /*  1000 degrees per second (2000 dps if CTRL_REG3 :  */
                                                                    /*  FS_DOUBLE = 1).                                   */
#define FXAS21002_CTRL_REG0_FS_DPS500             ((uint8_t) 0x02)  /*  500 degrees per second (1000 dps if CTRL_REG3 :   */
                                                                    /*  FS_DOUBLE = 1).                                   */
#define FXAS21002_CTRL_REG0_FS_DPS250             ((uint8_t) 0x03)  /*  250 degrees per second (500 dps if CTRL_REG3 :    */
                                                                    /*  FS_DOUBLE = 1).                                   */
#define FXAS21002_CTRL_REG0_HPF_EN_ENABLE         ((uint8_t) 0x04) 
#define FXAS21002_CTRL_REG0_HPF_EN_DISABLE        ((uint8_t) 0x00) 
#define FXAS21002_CTRL_REG0_SPIW_4WIRE            ((uint8_t) 0x00)  /*  SPI 4-wire mode (default).                        */
#define FXAS21002_CTRL_REG0_SPIW_3WIRE            ((uint8_t) 0x20)  /*  SPI 3-wire mode (MOSI pin is used for SPI input   */
                                                                    /*  and output signals).                              */
/*------------------------------*/



/*--------------------------------
** Register: RT_CFG
** Enum: FXAS21002_RT_CFG
** --
** Offset : 0x0E - Used to enable the Rate Threshold interrupt generation.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                 xtefe : 1; /*  Event flag enable on X rate.                                               */

        uint8_t                 ytefe : 1; /*  Event flag enable on Y rate.                                               */

        uint8_t                 ztefe : 1; /*  Event flag enable on Z rate.                                               */

        uint8_t                   ele : 1; /*  Event latch enable.                                                        */

    } b;
    uint8_t w;
} FXAS21002_RT_CFG_t;


/*
** RT_CFG - Bit field mask definitions 
*/
#define FXAS21002_RT_CFG_XTEFE_MASK   ((uint8_t) 0x01)
#define FXAS21002_RT_CFG_XTEFE_SHIFT  ((uint8_t)    0)

#define FXAS21002_RT_CFG_YTEFE_MASK   ((uint8_t) 0x02)
#define FXAS21002_RT_CFG_YTEFE_SHIFT  ((uint8_t)    1)

#define FXAS21002_RT_CFG_ZTEFE_MASK   ((uint8_t) 0x04)
#define FXAS21002_RT_CFG_ZTEFE_SHIFT  ((uint8_t)    2)

#define FXAS21002_RT_CFG_ELE_MASK     ((uint8_t) 0x08)
#define FXAS21002_RT_CFG_ELE_SHIFT    ((uint8_t)    3)


/*
** RT_CFG - Bit field value definitions  
*/
#define FXAS21002_RT_CFG_XTEFE_ENABLE          ((uint8_t) 0x01)  /*  X event detection enabled.                           */
#define FXAS21002_RT_CFG_XTEFE_DISABLE         ((uint8_t) 0x00)  /*  X event detection disabled.                          */
#define FXAS21002_RT_CFG_YTEFE_ENABLE          ((uint8_t) 0x02)  /*  Y event detection enabled.                           */
#define FXAS21002_RT_CFG_YTEFE_DISABLE         ((uint8_t) 0x00)  /*  Y event detection disabled.                          */
#define FXAS21002_RT_CFG_ZTEFE_ENABLE          ((uint8_t) 0x04)  /*  Z event detection enabled.                           */
#define FXAS21002_RT_CFG_ZTEFE_DISABLE         ((uint8_t) 0x00)  /*  Z event detection disabled.                          */
#define FXAS21002_RT_CFG_ELE_ENABLE            ((uint8_t) 0x08)  /*  Event flag latch enabled.                            */
#define FXAS21002_RT_CFG_ELE_DISABLE           ((uint8_t) 0x00)  /*  Event flag latch disabled.                           */
/*------------------------------*/



/*--------------------------------
** Register: RT_SRC
** Enum: FXAS21002_RT_SRC
** --
** Offset : 0x0F - Indicates the source of the Rate Threshold event. It also clears the RT_SRC flag in the INT_SOURCE_FLAG register.
** ------------------------------*/
typedef union {
    struct {
        uint8_t              x_rt_pol : 1; /*  Polarity of X event.                                                       */

        uint8_t                   xrt : 1; /*  X rate Event.                                                              */

        uint8_t              y_rt_pol : 1; /*  Polarity of Y event.                                                       */

        uint8_t                   yrt : 1; /*  Y rate event.                                                              */

        uint8_t              z_rt_pol : 1; /*  Polarity of Z event.                                                       */

        uint8_t                   zrt : 1; /*  Z rate event.                                                              */

        uint8_t                    ea : 1; /*  Event active flag.                                                         */

    } b;
    uint8_t w;
} FXAS21002_RT_SRC_t;


/*
** RT_SRC - Bit field mask definitions 
*/
#define FXAS21002_RT_SRC_X_RT_POL_MASK   ((uint8_t) 0x01)
#define FXAS21002_RT_SRC_X_RT_POL_SHIFT  ((uint8_t)    0)

#define FXAS21002_RT_SRC_XRT_MASK        ((uint8_t) 0x02)
#define FXAS21002_RT_SRC_XRT_SHIFT       ((uint8_t)    1)

#define FXAS21002_RT_SRC_Y_RT_POL_MASK   ((uint8_t) 0x04)
#define FXAS21002_RT_SRC_Y_RT_POL_SHIFT  ((uint8_t)    2)

#define FXAS21002_RT_SRC_YRT_MASK        ((uint8_t) 0x08)
#define FXAS21002_RT_SRC_YRT_SHIFT       ((uint8_t)    3)

#define FXAS21002_RT_SRC_Z_RT_POL_MASK   ((uint8_t) 0x10)
#define FXAS21002_RT_SRC_Z_RT_POL_SHIFT  ((uint8_t)    4)

#define FXAS21002_RT_SRC_ZRT_MASK        ((uint8_t) 0x20)
#define FXAS21002_RT_SRC_ZRT_SHIFT       ((uint8_t)    5)

#define FXAS21002_RT_SRC_EA_MASK         ((uint8_t) 0x40)
#define FXAS21002_RT_SRC_EA_SHIFT        ((uint8_t)    6)


/*
** RT_SRC - Bit field value definitions  
*/
#define FXAS21002_RT_SRC_X_RT_POL_POS          ((uint8_t) 0x00)  /*  Rate Event was Positive.                             */
#define FXAS21002_RT_SRC_X_RT_POL_NEG          ((uint8_t) 0x01)  /*  Rate Event was Negative.                             */
#define FXAS21002_RT_SRC_XRT_LOWER             ((uint8_t) 0x00)  /*  Rate lower than RT_THS value.                        */
#define FXAS21002_RT_SRC_XRT_GREATER           ((uint8_t) 0x02)  /*  Rate greater than RT_THS value. Event has occured.   */
#define FXAS21002_RT_SRC_Y_RT_POL_POS          ((uint8_t) 0x00)  /*  Rate Event was Positive.                             */
#define FXAS21002_RT_SRC_Y_RT_POL_NEG          ((uint8_t) 0x04)  /*  Rate Event was Negative.                             */
#define FXAS21002_RT_SRC_YRT_LOWER             ((uint8_t) 0x00)  /*  Rate lower than RT_THS value.                        */
#define FXAS21002_RT_SRC_YRT_GREATER           ((uint8_t) 0x08)  /*  Rate greater than RT_THS value. Event has occured.   */
#define FXAS21002_RT_SRC_Z_RT_POL_POS          ((uint8_t) 0x00)  /*  Rate Event was Positive.                             */
#define FXAS21002_RT_SRC_Z_RT_POL_NEG          ((uint8_t) 0x10)  /*  Rate Event was Negative.                             */
#define FXAS21002_RT_SRC_ZRT_LOWER             ((uint8_t) 0x00)  /*  Rate lower than RT_THS value.                        */
#define FXAS21002_RT_SRC_ZRT_GREATER           ((uint8_t) 0x20)  /*  Rate greater than RT_THS value. Event has occured.   */
#define FXAS21002_RT_SRC_EA_NOEVENT            ((uint8_t) 0x00)  /*  No event flags have been asserted.                   */
#define FXAS21002_RT_SRC_EA_EVENT              ((uint8_t) 0x40)  /*  One or more event flags have been asserted.          */
/*------------------------------*/



/*--------------------------------
** Register: RT_THS
** Enum: FXAS21002_RT_THS
** --
** Offset : 0x10 - The RT_THS register sets the threshold limit for the detection of the rate and the debounce counter mode.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                   ths : 7; /*  Unsigned 7-bit rate threshold value; The contents should only be modified  */
                                           /*  when the device is in Standby mode; The internal state of the Rate         */
                                           /*  Threshold function is reset when a transition from Standby to Active or    */
                                           /*  Ready to Active modes occurs.                                              */

        uint8_t                dbcntm : 1; /*  Debounce counter mode selection.                                           */

    } b;
    uint8_t w;
} FXAS21002_RT_THS_t;


/*
** RT_THS - Bit field mask definitions 
*/
#define FXAS21002_RT_THS_THS_MASK      ((uint8_t) 0x7F)
#define FXAS21002_RT_THS_THS_SHIFT     ((uint8_t)    0)

#define FXAS21002_RT_THS_DBCNTM_MASK   ((uint8_t) 0x80)
#define FXAS21002_RT_THS_DBCNTM_SHIFT  ((uint8_t)    7)


/*
** RT_THS - Bit field value definitions  
*/
#define FXAS21002_RT_THS_DBCNTM_CLEAR          ((uint8_t) 0x80)  /*  Clear counter when angular rate is below the         */
                                                                 /*  threshold value.                                     */
#define FXAS21002_RT_THS_DBCNTM_DECREMENT      ((uint8_t) 0x00)  /*  Decrement counter on every ODR cycle that the        */
                                                                 /*  angular rate is below the threshold value.           */
/*------------------------------*/



/*--------------------------------
** Register: RT_COUNT
** Enum: FXAS21002_RT_COUNT
** --
** Offset : 0x11 - Sets the number of debounce counts.
** ------------------------------*/
typedef uint8_t FXAS21002_RT_COUNT_t;



/*--------------------------------
** Register: TEMP
** Enum: FXAS21002_TEMP
** --
** Offset : 0x12 - The TEMP register contains an 8-bit 2's complement temperature value with a range of –128 °C to +127 °C and a scaling of 1 °C/LSB.
** ------------------------------*/
typedef uint8_t FXAS21002_TEMP_t;



/*--------------------------------
** Register: CTRL_REG1
** Enum: FXAS21002_CTRL_REG1
** --
** Offset : 0x13 - The CTRL_REG1 register is used to configure the device ODR, set the operating mode, soft-reset the device, and exercise the Self-Test function.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                  mode : 2; /*  Operational Mode.                                                          */

        uint8_t                    dr : 3; /*  Output Data Rate selection.                                                */

        uint8_t                    st : 1; /*  Self-Test Enable.                                                          */

        uint8_t                   rst : 1; /*  Software Reset.                                                            */

    } b;
    uint8_t w;
} FXAS21002_CTRL_REG1_t;


/*
** CTRL_REG1 - Bit field mask definitions 
*/
#define FXAS21002_CTRL_REG1_MODE_MASK   ((uint8_t) 0x03)
#define FXAS21002_CTRL_REG1_MODE_SHIFT  ((uint8_t)    0)

#define FXAS21002_CTRL_REG1_DR_MASK     ((uint8_t) 0x1C)
#define FXAS21002_CTRL_REG1_DR_SHIFT    ((uint8_t)    2)

#define FXAS21002_CTRL_REG1_ST_MASK     ((uint8_t) 0x20)
#define FXAS21002_CTRL_REG1_ST_SHIFT    ((uint8_t)    5)

#define FXAS21002_CTRL_REG1_RST_MASK    ((uint8_t) 0x40)
#define FXAS21002_CTRL_REG1_RST_SHIFT   ((uint8_t)    6)


/*
** CTRL_REG1 - Bit field value definitions  
*/
#define FXAS21002_CTRL_REG1_MODE_STANDBY          ((uint8_t) 0x00)  /*  Standby Mode. Register setting allowed. Lowest    */
                                                                    /*  power.                                            */
#define FXAS21002_CTRL_REG1_MODE_READY            ((uint8_t) 0x01)  /*  Ready Mode. The device is ready to measure        */
                                                                    /*  angular rate but no data acquisitions are being   */
                                                                    /*  made. Register reads only. Reduced power.         */
#define FXAS21002_CTRL_REG1_MODE_ACTIVE           ((uint8_t) 0x02)  /*  Active Mode. The device is fully functional.      */
                                                                    /*  Register reads only. Maximum power.               */
#define FXAS21002_CTRL_REG1_DR_800HZ              ((uint8_t) 0x00) 
#define FXAS21002_CTRL_REG1_DR_400HZ              ((uint8_t) 0x04) 
#define FXAS21002_CTRL_REG1_DR_200HZ              ((uint8_t) 0x08) 
#define FXAS21002_CTRL_REG1_DR_100HZ              ((uint8_t) 0x0c) 
#define FXAS21002_CTRL_REG1_DR_50HZ               ((uint8_t) 0x10) 
#define FXAS21002_CTRL_REG1_DR_25HZ               ((uint8_t) 0x14) 
#define FXAS21002_CTRL_REG1_DR_12_5HZ             ((uint8_t) 0x18) 
#define FXAS21002_CTRL_REG1_ST_ENABLE             ((uint8_t) 0x20) 
#define FXAS21002_CTRL_REG1_ST_DISABLE            ((uint8_t) 0x00) 
#define FXAS21002_CTRL_REG1_RST_TRIGGER           ((uint8_t) 0x40) 
#define FXAS21002_CTRL_REG1_RST_NOTTRIGGERED      ((uint8_t) 0x00) 
/*------------------------------*/



/*--------------------------------
** Register: CTRL_REG2
** Enum: FXAS21002_CTRL_REG2
** --
** Offset : 0x14 - This register enables and assigns the output pin(s) and logic polarities for the various interrupt sources available on the device.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                 pp_od : 1; /*  INT1 and INT2 pin output driver configuration.                             */

        uint8_t                  ipol : 1; /*  Interrupt logic polarity.                                                  */

        uint8_t           int_en_drdy : 1; /*  Data ready interrupt enable.                                               */

        uint8_t          int_cfg_drdy : 1; /*  Data-ready interrupt pin routing.                                          */

        uint8_t             int_en_rt : 1; /*  Rate threshold interrupt enable.                                           */

        uint8_t            int_cfg_rt : 1; /*  Rate threshold interrupt pin routing.                                      */

        uint8_t           int_en_fifo : 1; /*  FIFO Interrupt Enable.                                                     */

        uint8_t          int_cfg_fifo : 1; /*  FIFO interrupt pin routing.                                                */

    } b;
    uint8_t w;
} FXAS21002_CTRL_REG2_t;


/*
** CTRL_REG2 - Bit field mask definitions 
*/
#define FXAS21002_CTRL_REG2_PP_OD_MASK          ((uint8_t) 0x01)
#define FXAS21002_CTRL_REG2_PP_OD_SHIFT         ((uint8_t)    0)

#define FXAS21002_CTRL_REG2_IPOL_MASK           ((uint8_t) 0x02)
#define FXAS21002_CTRL_REG2_IPOL_SHIFT          ((uint8_t)    1)

#define FXAS21002_CTRL_REG2_INT_EN_DRDY_MASK    ((uint8_t) 0x04)
#define FXAS21002_CTRL_REG2_INT_EN_DRDY_SHIFT   ((uint8_t)    2)

#define FXAS21002_CTRL_REG2_INT_CFG_DRDY_MASK   ((uint8_t) 0x08)
#define FXAS21002_CTRL_REG2_INT_CFG_DRDY_SHIFT  ((uint8_t)    3)

#define FXAS21002_CTRL_REG2_INT_EN_RT_MASK      ((uint8_t) 0x10)
#define FXAS21002_CTRL_REG2_INT_EN_RT_SHIFT     ((uint8_t)    4)

#define FXAS21002_CTRL_REG2_INT_CFG_RT_MASK     ((uint8_t) 0x20)
#define FXAS21002_CTRL_REG2_INT_CFG_RT_SHIFT    ((uint8_t)    5)

#define FXAS21002_CTRL_REG2_INT_EN_FIFO_MASK    ((uint8_t) 0x40)
#define FXAS21002_CTRL_REG2_INT_EN_FIFO_SHIFT   ((uint8_t)    6)

#define FXAS21002_CTRL_REG2_INT_CFG_FIFO_MASK   ((uint8_t) 0x80)
#define FXAS21002_CTRL_REG2_INT_CFG_FIFO_SHIFT  ((uint8_t)    7)


/*
** CTRL_REG2 - Bit field value definitions  
*/
#define FXAS21002_CTRL_REG2_PP_OD_PUSHPULL        ((uint8_t) 0x00)  /*  Push-pull output driver.                          */
#define FXAS21002_CTRL_REG2_PP_OD_OPENDRAIN       ((uint8_t) 0x01)  /*  Open-drain output driver.                         */
#define FXAS21002_CTRL_REG2_IPOL_ACTIVE_LOW       ((uint8_t) 0x00) 
#define FXAS21002_CTRL_REG2_IPOL_ACTIVE_HIGH      ((uint8_t) 0x02) 
#define FXAS21002_CTRL_REG2_INT_EN_DRDY_ENABLE    ((uint8_t) 0x04) 
#define FXAS21002_CTRL_REG2_INT_EN_DRDY_DISABLE   ((uint8_t) 0x00) 
#define FXAS21002_CTRL_REG2_INT_CFG_DRDY_INT2     ((uint8_t) 0x00)  /*  Interrupt is routed to INT2 pin.                  */
#define FXAS21002_CTRL_REG2_INT_CFG_DRDY_INT1     ((uint8_t) 0x08)  /*  Interrupt is routed to INT1 pin.                  */
#define FXAS21002_CTRL_REG2_INT_EN_RT_ENABLE      ((uint8_t) 0x10) 
#define FXAS21002_CTRL_REG2_INT_EN_RT_DISABLE     ((uint8_t) 0x00) 
#define FXAS21002_CTRL_REG2_INT_CFG_RT_INT2       ((uint8_t) 0x00)  /*  Interrupt is routed to INT2 pin.                  */
#define FXAS21002_CTRL_REG2_INT_CFG_RT_INT1       ((uint8_t) 0x20)  /*  Interrupt is routed to INT1 pin.                  */
#define FXAS21002_CTRL_REG2_INT_EN_FIFO_ENABLE    ((uint8_t) 0x40) 
#define FXAS21002_CTRL_REG2_INT_EN_FIFO_DISABLE   ((uint8_t) 0x00) 
#define FXAS21002_CTRL_REG2_INT_CFG_FIFO_INT2     ((uint8_t) 0x00)  /*  Interrupt is routed to INT2 pin.                  */
#define FXAS21002_CTRL_REG2_INT_CFG_FIFO_INT1     ((uint8_t) 0x80)  /*  Interrupt is routed to INT1 pin.                  */
/*------------------------------*/



/*--------------------------------
** Register: CTRL_REG3
** Enum: FXAS21002_CTRL_REG3
** --
** Offset : 0x15 - Auto-increment address configuration, external power control, Full Scale Range (FSR) expansion
** ------------------------------*/
typedef union {
    struct {
        uint8_t             fs_double : 1; /*  Increases the dynamic range for each CTRL_REG0 : FS selection by a factor  */
                                           /*  of two.                                                                    */

        uint8_t _reserved_            : 1;
        uint8_t             extctrlen : 1; /*  External power mode control input.                                         */

        uint8_t             wraptoone : 1; /*  Auto-increment read address pointer roll-over behavior.                    */

    } b;
    uint8_t w;
} FXAS21002_CTRL_REG3_t;


/*
** CTRL_REG3 - Bit field mask definitions 
*/
#define FXAS21002_CTRL_REG3_FS_DOUBLE_MASK   ((uint8_t) 0x01)
#define FXAS21002_CTRL_REG3_FS_DOUBLE_SHIFT  ((uint8_t)    0)

#define FXAS21002_CTRL_REG3_EXTCTRLEN_MASK   ((uint8_t) 0x04)
#define FXAS21002_CTRL_REG3_EXTCTRLEN_SHIFT  ((uint8_t)    2)

#define FXAS21002_CTRL_REG3_WRAPTOONE_MASK   ((uint8_t) 0x08)
#define FXAS21002_CTRL_REG3_WRAPTOONE_SHIFT  ((uint8_t)    3)


/*
** CTRL_REG3 - Bit field value definitions  
*/
#define FXAS21002_CTRL_REG3_FS_DOUBLE_ENABLE      ((uint8_t) 0x01)  /*  Maximum full-scale range selections are doubled   */
                                                                    /*  (4000, 2000, 1000, 500 dps).                      */
#define FXAS21002_CTRL_REG3_FS_DOUBLE_DISABLE     ((uint8_t) 0x00)  /*  Maximum full-scale range selections are as per    */
                                                                    /*  selectable full-scale ranges (2000, 1000, 500,    */
                                                                    /*  250 dps).                                         */
#define FXAS21002_CTRL_REG3_EXTCTRLEN_INT2        ((uint8_t) 0x00)  /*  INT2 pin is used as an interrupt output           */
                                                                    /*  (default).                                        */
#define FXAS21002_CTRL_REG3_EXTCTRLEN_POWER_CONTROL ((uint8_t) 0x04)  /*  INT2 pin becomes an input pin that may be used  */
                                                                      /*  to control the power mode.                      */
#define FXAS21002_CTRL_REG3_WRAPTOONE_ROLL_STATUS ((uint8_t) 0x00)  /*  The auto-increment read address pointer rolls     */
                                                                    /*  over to address 0x00 (STATUS) after the Z-axis    */
                                                                    /*  LSB is read (default).                            */
#define FXAS21002_CTRL_REG3_WRAPTOONE_ROLL_DATA   ((uint8_t) 0x08)  /*  The auto-increment pointer rolls over to address  */
                                                                    /*  0x01 (X-axis MSB) in order to facilitate the      */
                                                                    /*  faster read out of the FIFO data in a single      */
                                                                    /*  burst read operation.                             */
/*------------------------------*/


#endif /* FXAS21002_H_ */ 
