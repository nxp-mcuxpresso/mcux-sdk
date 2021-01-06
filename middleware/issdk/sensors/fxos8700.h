/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** 
 * @file fxos8700.h
 * @brief The fxos8700.h file contains the register definitions for FXOS8700 sensor driver.
 */

#ifndef FXOS8700_H_
#define FXOS8700_H_
/**
 * @brief FXOS8700 internal register addresses explained in the FXOS8700 data sheet.
 */
enum {
    FXOS8700_STATUS           = 0x00, /*!< Alias for ::FXOS8700_DR_STATUS or ::FXOS8700_F_STATUS. */
    FXOS8700_OUT_X_MSB        = 0x01, /*!< 14-bit X-axis measurement data bits 13:6. */
    FXOS8700_OUT_X_LSB        = 0x02, /*!< 14-bit X-axis measurement data bits 5:0. */
    FXOS8700_OUT_Y_MSB        = 0x03, /*!< 14-bit Y-axis measurement data bits 13:6. */
    FXOS8700_OUT_Y_LSB        = 0x04, /*!< 14-bit Y-axis measurement data bits 5:0. */
    FXOS8700_OUT_Z_MSB        = 0x05, /*!< 14-bit Z-axis measurement data bits 13:6. */
    FXOS8700_OUT_Z_LSB        = 0x06, /*!< 14-bit Z-axis measurement data bits 5:0. */
    FXOS8700_F_SETUP          = 0x09, /*!< FIFO setup. */
    FXOS8700_TRIG_CFG         = 0x0A, /*!< FIFO event trigger configuration register. */
    FXOS8700_SYSMOD           = 0x0B, /*!< Current system mode. */
    FXOS8700_INT_SOURCE       = 0x0C, /*!< Interrupt status. */
    FXOS8700_WHO_AM_I         = 0x0D, /*!< Device ID. */
    FXOS8700_XYZ_DATA_CFG     = 0x0E, /*!< Acceleration dynamic range and filter enable settings. */
    FXOS8700_HP_FILTER_CUTOFF = 0x0F, /*!< Pulse detection highpass and lowpass filter enabling bits. */
    FXOS8700_PL_STATUS        = 0x10, /*!< Landscape/portrait orientation status. */
    FXOS8700_PL_CFG           = 0x11, /*!< Landscape/portrait configuration. */
    FXOS8700_PL_COUNT         = 0x12, /*!< Landscape/portrait debounce counter. */
    FXOS8700_PL_BF_ZCOMP      = 0x13, /*!< Back/front trip angle threshold. */
    FXOS8700_PL_THS_REG       = 0x14, /*!< Portrait to landscape trip threshold angle and hysteresis settings. */
    FXOS8700_A_FFMT_CFG       = 0x15, /*!< Freefall/motion function configuration. */
    FXOS8700_A_FFMT_SRC       = 0x16, /*!< Freefall/motion event source register. */
    FXOS8700_A_FFMT_THS       = 0x17, /*!< Freefall/motion threshold register. */
    FXOS8700_A_FFMT_COUNT     = 0x18, /*!< Freefall/motion debounce counter. */
    FXOS8700_TRANSIENT_CFG    = 0x1D, /*!< Transient function configuration. */
    FXOS8700_TRANSIENT_SRC    = 0x1E, /*!< Transient event status register. */
    FXOS8700_TRANSIENT_THS    = 0x1F, /*!< Transient event threshold. */
    FXOS8700_TRANSIENT_COUNT  = 0x20, /*!< Transient debounce counter. */
    FXOS8700_PULSE_CFG        = 0x21, /*!< Pulse function configuration. */
    FXOS8700_PULSE_SRC        = 0x22, /*!< Pulse function source register. */
    FXOS8700_PULSE_THSX       = 0x23, /*!< X-axis pulse threshold. */
    FXOS8700_PULSE_THSY       = 0x24, /*!< Y-axis pulse threshold. */
    FXOS8700_PULSE_THSZ       = 0x25, /*!< Z-axis pulse threshold. */
    FXOS8700_PULSE_TMLT       = 0x26, /*!< Time limit for pulse detection. */
    FXOS8700_PULSE_LTCY       = 0x27, /*!< Latency time for second pulse detection. */
    FXOS8700_PULSE_WIND       = 0x28, /*!< Window time for second pulse detection. */
    FXOS8700_ASLP_COUNT       = 0x29, /*!< The counter setting for auto-sleep period. */
    FXOS8700_CTRL_REG1        = 0x2A, /*!< System ODR, accelerometer OSR (Output sample rate), operating mode. */
    FXOS8700_CTRL_REG2        = 0x2B, /*!< Self-test, reset, accelerometer OSR, and sleep mode settings. */
    FXOS8700_CTRL_REG3        = 0x2C, /*!< Sleep mode interrupt wake enable, interrupt polarity, push-pull/open drain configuration. */
    FXOS8700_CTRL_REG4        = 0x2D, /*!< Interrupt enable register. */
    FXOS8700_CTRL_REG5        = 0x2E, /*!< Interrupt pin (INT1/INT2) map. */
    FXOS8700_OFF_X            = 0x2F, /*!< X-axis accelerometer offset adjust. */
    FXOS8700_OFF_Y            = 0x30, /*!< Y-axis accelerometer offset adjust. */
    FXOS8700_OFF_Z            = 0x31, /*!< Z-axis accelerometer offset adjust. */
    FXOS8700_M_DR_STATUS      = 0x32, /*!< The magnetometer data ready status. */
    FXOS8700_M_OUT_X_MSB      = 0x33, /*!< MSB of the 16-bit magnetometer data for X-axis. */
    FXOS8700_M_OUT_X_LSB      = 0x34, /*!< LSB of the 16-bit magnetometer data for X-axis. */
    FXOS8700_M_OUT_Y_MSB      = 0x35, /*!< MSB of the 16-bit magnetometer data for Y-axis. */
    FXOS8700_M_OUT_Y_LSB      = 0x36, /*!< LSB of the 16-bit magnetometer data for Y-axis. */
    FXOS8700_M_OUT_Z_MSB      = 0x37, /*!< MSB of the 16-bit magnetometer data for Z-axis. */
    FXOS8700_M_OUT_Z_LSB      = 0x38, /*!< LSB of the 16-bit magnetometer data for Z-axis. */
    FXOS8700_CMP_X_MSB        = 0x39, /*!< Bits [13:8] of integrated X-axis acceleration data. */
    FXOS8700_CMP_X_LSB        = 0x3A, /*!< Bits [7:0] of integrated X-axis acceleration data. */
    FXOS8700_CMP_Y_MSB        = 0x3B, /*!< Bits [13:8] of integrated Y-axis acceleration data. */
    FXOS8700_CMP_Y_LSB        = 0x3C, /*!< Bits [7:0] of integrated Y-axis acceleration data. */
    FXOS8700_CMP_Z_MSB        = 0x3D, /*!< Bits [13:8] of integrated Z-axis acceleration data. */
    FXOS8700_CMP_Z_LSB        = 0x3E, /*!< Bits [7:0] of integrated Z-axis acceleration data. */
    FXOS8700_M_OFF_X_MSB      = 0x3F, /*!< MSB of magnetometer X-axis offset. */
    FXOS8700_M_OFF_X_LSB      = 0x40, /*!< LSB of magnetometer X-axis offset. */
    FXOS8700_M_OFF_Y_MSB      = 0x41, /*!< MSB of magnetometer Y-axis offset. */
    FXOS8700_M_OFF_Y_LSB      = 0x42, /*!< LSB of magnetometer Y-axis offset. */
    FXOS8700_M_OFF_Z_MSB      = 0x43, /*!< MSB of magnetometer Z-axis offset. */
    FXOS8700_M_OFF_Z_LSB      = 0x44, /*!< LSB of magnetometer Z-axis offset. */
    FXOS8700_MAX_X_MSB        = 0x45, /*!< Magnetometer X-axis maximum value MSB. */
    FXOS8700_MAX_X_LSB        = 0x46, /*!< Magnetometer X-axis maximum value LSB. */
    FXOS8700_MAX_Y_MSB        = 0x47, /*!< Magnetometer Y-axis maximum value MSB. */
    FXOS8700_MAX_Y_LSB        = 0x48, /*!< Magnetometer Y-axis maximum value LSB. */
    FXOS8700_MAX_Z_MSB        = 0x49, /*!< Magnetometer Z-axis maximum value MSB. */
    FXOS8700_MAX_Z_LSB        = 0x4A, /*!< Magnetometer Z-axis maximum value LSB. */
    FXOS8700_MIN_X_MSB        = 0x4B, /*!< Magnetometer X-axis minimum value MSB. */
    FXOS8700_MIN_X_LSB        = 0x4C, /*!< Magnetometer X-axis minimum value LSB. */
    FXOS8700_MIN_Y_MSB        = 0x4D, /*!< Magnetometer Y-axis minimum value MSB. */
    FXOS8700_MIN_Y_LSB        = 0x4E, /*!< Magnetometer Y-axis minimum value LSB. */
    FXOS8700_MIN_Z_MSB        = 0x4F, /*!< Magnetometer Z-axis minimum value MSB. */
    FXOS8700_MIN_Z_LSB        = 0x50, /*!< Magnetometer Z-axis minimum value LSB. */
    FXOS8700_TEMP             = 0x51, /*!< Device temperature with a valid range of -128 to 127 degrees C. */
    FXOS8700_M_THS_CFG        = 0x52, /*!< Magnetic threshold detection function configuration. */
    FXOS8700_M_THS_SRC        = 0x53, /*!< Magnetic threshold event source register. */
    FXOS8700_M_THS_X_MSB      = 0x54, /*!< X-axis magnetic threshold MSB. */
    FXOS8700_M_THS_X_LSB      = 0x55, /*!< X-axis magnetic threshold LSB. */
    FXOS8700_M_THS_Y_MSB      = 0x56, /*!< Y-axis magnetic threshold MSB. */
    FXOS8700_M_THS_Y_LSB      = 0x57, /*!< Y-axis magnetic threshold LSB. */
    FXOS8700_M_THS_Z_MSB      = 0x58, /*!< Z-axis magnetic threshold MSB. */
    FXOS8700_M_THS_Z_LSB      = 0x59, /*!< Z-axis magnetic threshold LSB. */
    FXOS8700_M_THS_COUNT      = 0x5A, /*!< Magnetic threshold debounce counter. */
    FXOS8700_M_CTRL_REG1      = 0x5B, /*!< Control for magnetometer sensor functions. */
    FXOS8700_M_CTRL_REG2      = 0x5C, /*!< Control for magnetometer sensor functions. */
    FXOS8700_M_CTRL_REG3      = 0x5D, /*!< Control for magnetometer sensor functions. */
    FXOS8700_M_INT_SRC        = 0x5E, /*!< Magnetometer interrupt source. */
    FXOS8700_A_VECM_CFG       = 0x5F, /*!< Acceleration vector magnitude configuration register. */
    FXOS8700_A_VECM_THS_MSB   = 0x60, /*!< Acceleration vector magnitude threshold MSB. */
    FXOS8700_A_VECM_THS_LSB   = 0x61, /*!< Acceleration vector magnitude threshold LSB. */
    FXOS8700_A_VECM_CNT       = 0x62, /*!< Acceleration vector magnitude debounce count. */
    FXOS8700_A_VECM_INITX_MSB = 0x63, /*!< Acceleration vector magnitude X-axis reference value MSB. */
    FXOS8700_A_VECM_INITX_LSB = 0x64, /*!< Acceleration vector magnitude X-axis reference value LSB. */
    FXOS8700_A_VECM_INITY_MSB = 0x65, /*!< Acceleration vector magnitude Y-axis reference value MSB. */
    FXOS8700_A_VECM_INITY_LSB = 0x66, /*!< Acceleration vector magnitude Y-axis reference value LSB. */
    FXOS8700_A_VECM_INITZ_MSB = 0x67, /*!< Acceleration vector magnitude Z-axis reference value MSB. */
    FXOS8700_A_VECM_INITZ_LSB = 0x68, /*!< Acceleration vector magnitude Z-axis reference value LSB. */
    FXOS8700_M_VECM_CFG       = 0x69, /*!< Magnetic vector magnitude configuration register. */
    FXOS8700_M_VECM_THS_MSB   = 0x6A, /*!< Magnetic vector magnitude threshold MSB. */
    FXOS8700_M_VECM_THS_LSB   = 0x6B, /*!< Magnetic vector magnitude threshold LSB. */
    FXOS8700_M_VECM_CNT       = 0x6C, /*!< Magnetic vector magnitude debounce count. */
    FXOS8700_M_VECM_INITX_MSB = 0x6D, /*!< Magnetic vector magnitude X-axis reference value MSB. */
    FXOS8700_M_VECM_INITX_LSB = 0x6E, /*!< Magnetic vector magnitude X-axis reference value LSB. */
    FXOS8700_M_VECM_INITY_MSB = 0x6F, /*!< Magnetic vector magnitude Y-axis reference value MSB. */
    FXOS8700_M_VECM_INITY_LSB = 0x70, /*!< Magnetic vector magnitude Y-axis reference value LSB. */
    FXOS8700_M_VECM_INITZ_MSB = 0x71, /*!< Magnetic vector magnitude Z-axis reference value MSB. */
    FXOS8700_M_VECM_INITZ_LSB = 0x72, /*!< Magnetic vector magnitude Z-axis reference value LSB. */
    FXOS8700_A_FFMT_THS_X_MSB = 0x73, /*!< X-axis FFMT threshold MSB. */
    FXOS8700_A_FFMT_THS_X_LSB = 0x74, /*!< X-axis FFMT threshold LSB. */
    FXOS8700_A_FFMT_THS_Y_MSB = 0x75, /*!< Y-axis FFMT threshold MSB. */
    FXOS8700_A_FFMT_THS_Y_LSB = 0x76, /*!< Y-axis FFMT threshold LSB. */
    FXOS8700_A_FFMT_THS_Z_MSB = 0x77, /*!< Z-axis FFMT threshold MSB. */
    FXOS8700_A_FFMT_THS_Z_LSB = 0x78, /*!< Z-axis FFMT threshold LSB. */
};

#define FXOS8700_DEVICE_ADDR_SA_00           (0x1E) 
  
#define FXOS8700_DEVICE_ADDR_SA_01           (0x1D) 
  
#define FXOS8700_DEVICE_ADDR_SA_10           (0x1C) 
  
#define FXOS8700_DEVICE_ADDR_SA_11           (0x1F) 
  

#define FXOS8700_WHO_AM_I_PROD_VALUE (0xC7) 
  
  
/**
 * The following are the macro definitions to address each bit and its value in the hardware registers.
 */

/*--------------------------------
** Register: DR_STATUS
** Enum: FXOS8700_DR_STATUS
** --
** Offset : 0x00 - Alias for ::FXOS8700_DR_STATUS or ::FXOS8700_F_STATUS.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                   xdr : 1;
        uint8_t                   ydr : 1;
        uint8_t                   zdr : 1;
        uint8_t                 zyxdr : 1;
        uint8_t                   xow : 1;
        uint8_t                   yow : 1;
        uint8_t                   zow : 1;
        uint8_t                 zyxow : 1;
    } b;
    uint8_t w;
} FXOS8700_DR_STATUS_t;


/*
** DR_STATUS - Bit field mask definitions 
*/
#define FXOS8700_DR_STATUS_XDR_MASK     ((uint8_t) 0x01)
#define FXOS8700_DR_STATUS_XDR_SHIFT    ((uint8_t)    0)

#define FXOS8700_DR_STATUS_YDR_MASK     ((uint8_t) 0x02)
#define FXOS8700_DR_STATUS_YDR_SHIFT    ((uint8_t)    1)

#define FXOS8700_DR_STATUS_ZDR_MASK     ((uint8_t) 0x04)
#define FXOS8700_DR_STATUS_ZDR_SHIFT    ((uint8_t)    2)

#define FXOS8700_DR_STATUS_ZYXDR_MASK   ((uint8_t) 0x08)
#define FXOS8700_DR_STATUS_ZYXDR_SHIFT  ((uint8_t)    3)

#define FXOS8700_DR_STATUS_XOW_MASK     ((uint8_t) 0x10)
#define FXOS8700_DR_STATUS_XOW_SHIFT    ((uint8_t)    4)

#define FXOS8700_DR_STATUS_YOW_MASK     ((uint8_t) 0x20)
#define FXOS8700_DR_STATUS_YOW_SHIFT    ((uint8_t)    5)

#define FXOS8700_DR_STATUS_ZOW_MASK     ((uint8_t) 0x40)
#define FXOS8700_DR_STATUS_ZOW_SHIFT    ((uint8_t)    6)

#define FXOS8700_DR_STATUS_ZYXOW_MASK   ((uint8_t) 0x80)
#define FXOS8700_DR_STATUS_ZYXOW_SHIFT  ((uint8_t)    7)


/*
** DR_STATUS - Bit field value definitions  
*/
#define FXOS8700_DR_STATUS_XDR_DRDY              ((uint8_t) 0x01)  /*  xdr is set to 1 whenever a new X-axis data         */
                                                                   /*  acquisition is completed. xdr is cleared anytime   */
                                                                   /*  the OUT_X_MSB register is read.                    */
#define FXOS8700_DR_STATUS_YDR_DRDY              ((uint8_t) 0x02)  /*  ydr is set to 1 whenever a new Y-axis data         */
                                                                   /*  acquisition is completed. xdr is cleared anytime   */
                                                                   /*  the OUT_Y_MSB register is read.                    */
#define FXOS8700_DR_STATUS_ZDR_DRDY              ((uint8_t) 0x04)  /*  zdr is set to 1 whenever a new Z-axis data         */
                                                                   /*  acquisition is completed. xdr is cleared anytime   */
                                                                   /*  the OUT_Z_MSB register is read.                    */
#define FXOS8700_DR_STATUS_ZYXDR_DRDY            ((uint8_t) 0x08)  /*  zyxdr signals that a new acquisition for any of    */
                                                                   /*  the enabled channels is available. zyxdr is        */
                                                                   /*  cleared when the high-bytes of the acceleration    */
                                                                   /*  data (OUT_X_MSB, OUT_Y_MSB, OUT_Z_MSB) are read.   */
#define FXOS8700_DR_STATUS_XOW_OWR               ((uint8_t) 0x10) 
#define FXOS8700_DR_STATUS_YOW_OWR               ((uint8_t) 0x20) 
#define FXOS8700_DR_STATUS_ZOW_OWR               ((uint8_t) 0x40) 
#define FXOS8700_DR_STATUS_ZYXOW_OWR             ((uint8_t) 0x80) 
/*------------------------------*/



/*--------------------------------
** Register: F_STATUS
** Enum: FXOS8700_F_STATUS
** --
** Offset : 0x00 - Fifo Status register
** ------------------------------*/
typedef union {
    struct {
        uint8_t                 f_cnt : 6; /*  These bits indicate the number of acceleration samples currently stored in */
                                           /*  the FIFO buffer. Count 0b00_0000 indicates that the FIFO is empty          */

        uint8_t           f_wmrk_flag : 1;
        uint8_t                 f_ovf : 1;
    } b;
    uint8_t w;
} FXOS8700_F_STATUS_t;


/*
** F_STATUS - Bit field mask definitions 
*/
#define FXOS8700_F_STATUS_F_CNT_MASK         ((uint8_t) 0x3F)
#define FXOS8700_F_STATUS_F_CNT_SHIFT        ((uint8_t)    0)

#define FXOS8700_F_STATUS_F_WMRK_FLAG_MASK   ((uint8_t) 0x40)
#define FXOS8700_F_STATUS_F_WMRK_FLAG_SHIFT  ((uint8_t)    6)

#define FXOS8700_F_STATUS_F_OVF_MASK         ((uint8_t) 0x80)
#define FXOS8700_F_STATUS_F_OVF_SHIFT        ((uint8_t)    7)


/*
** F_STATUS - Bit field value definitions  
*/
#define FXOS8700_F_STATUS_F_WMRK_FLAG_NOEVT     ((uint8_t) 0x00)  /*  No FIFO watermark event detected                    */
#define FXOS8700_F_STATUS_F_WMRK_FLAG_EVTDET    ((uint8_t) 0x40) 
#define FXOS8700_F_STATUS_F_OVF_NOOVFL          ((uint8_t) 0x00)  /*  No FIFO overflow events detected                    */
#define FXOS8700_F_STATUS_F_OVF_OVFLDET         ((uint8_t) 0x80)  /*  FIFO overflow event detected                        */
/*------------------------------*/



/*--------------------------------
** Register: OUT_X_MSB
** Enum: FXOS8700_OUT_X_MSB
** --
** Offset : 0x01 - MSB of Accelerometer X value
** ------------------------------*/
typedef union {
    struct {
        uint8_t                    xd; /*  - 14-bit X-axis measurement data bits 13:6.                                    */

    } b;
    uint8_t w;
} FXOS8700_OUT_X_MSB_t;


/*
** OUT_X_MSB - Bit field mask definitions 
*/
#define FXOS8700_OUT_X_MSB_XD_MASK   ((uint8_t) 0xFF)
#define FXOS8700_OUT_X_MSB_XD_SHIFT  ((uint8_t)    0)


/*------------------------------*/



/*--------------------------------
** Register: OUT_X_LSB
** Enum: FXOS8700_OUT_X_LSB
** --
** Offset : 0x02 - LSB of Accelerometer X value
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 2;
        uint8_t                    xd : 6; /*  - 14-bit X-axis measurement data bits 5:0.                                 */

    } b;
    uint8_t w;
} FXOS8700_OUT_X_LSB_t;


/*
** OUT_X_LSB - Bit field mask definitions 
*/
#define FXOS8700_OUT_X_LSB_XD_MASK   ((uint8_t) 0xFC)
#define FXOS8700_OUT_X_LSB_XD_SHIFT  ((uint8_t)    2)


/*------------------------------*/



/*--------------------------------
** Register: OUT_Y_MSB
** Enum: FXOS8700_OUT_Y_MSB
** --
** Offset : 0x03 - 14-bit Y-axis measurement data bits 13:6.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                    yd; /*  - 14-bit Y-axis measurement data bits 13:6.                                    */

    } b;
    uint8_t w;
} FXOS8700_OUT_Y_MSB_t;


/*
** OUT_Y_MSB - Bit field mask definitions 
*/
#define FXOS8700_OUT_Y_MSB_YD_MASK   ((uint8_t) 0xFF)
#define FXOS8700_OUT_Y_MSB_YD_SHIFT  ((uint8_t)    0)


/*------------------------------*/



/*--------------------------------
** Register: OUT_Y_LSB
** Enum: FXOS8700_OUT_Y_LSB
** --
** Offset : 0x04 - 14-bit Y-axis measurement data bits 5:0.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 2;
        uint8_t                    yd : 6; /*  - 14-bit Y-axis measurement data bits 5:0.                                 */

    } b;
    uint8_t w;
} FXOS8700_OUT_Y_LSB_t;


/*
** OUT_Y_LSB - Bit field mask definitions 
*/
#define FXOS8700_OUT_Y_LSB_YD_MASK   ((uint8_t) 0xFC)
#define FXOS8700_OUT_Y_LSB_YD_SHIFT  ((uint8_t)    2)


/*------------------------------*/



/*--------------------------------
** Register: OUT_Z_MSB
** Enum: FXOS8700_OUT_Z_MSB
** --
** Offset : 0x05 - 14-bit Z-axis measurement data bits 13:6.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                    zd; /*  - 14-bit Z-axis measurement data bits 13:6.                                    */

    } b;
    uint8_t w;
} FXOS8700_OUT_Z_MSB_t;


/*
** OUT_Z_MSB - Bit field mask definitions 
*/
#define FXOS8700_OUT_Z_MSB_ZD_MASK   ((uint8_t) 0xFF)
#define FXOS8700_OUT_Z_MSB_ZD_SHIFT  ((uint8_t)    0)


/*------------------------------*/



/*--------------------------------
** Register: OUT_Z_LSB
** Enum: FXOS8700_OUT_Z_LSB
** --
** Offset : 0x06 - 14-bit Z-axis measurement data bits 5:0.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 2;
        uint8_t                    zd : 6; /*  - 14-bit Z-axis measurement data bits 5:0.                                 */

    } b;
    uint8_t w;
} FXOS8700_OUT_Z_LSB_t;


/*
** OUT_Z_LSB - Bit field mask definitions 
*/
#define FXOS8700_OUT_Z_LSB_ZD_MASK   ((uint8_t) 0xFC)
#define FXOS8700_OUT_Z_LSB_ZD_SHIFT  ((uint8_t)    2)


/*------------------------------*/



/*--------------------------------
** Register: F_SETUP
** Enum: FXOS8700_F_SETUP
** --
** Offset : 0x09 - FIFO setup.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                f_wmrk : 6; /*  FIFO sample count watermark                                                */

        uint8_t                f_mode : 2; /*  - FIFO Buffer operating mode                                               */

    } b;
    uint8_t w;
} FXOS8700_F_SETUP_t;


/*
** F_SETUP - Bit field mask definitions 
*/
#define FXOS8700_F_SETUP_F_WMRK_MASK   ((uint8_t) 0x3F)
#define FXOS8700_F_SETUP_F_WMRK_SHIFT  ((uint8_t)    0)

#define FXOS8700_F_SETUP_F_MODE_MASK   ((uint8_t) 0xC0)
#define FXOS8700_F_SETUP_F_MODE_SHIFT  ((uint8_t)    6)


/*
** F_SETUP - Bit field value definitions  
*/
#define FXOS8700_F_SETUP_F_MODE_FIFO_DISABLE   ((uint8_t) 0x00)  /*  FIFO is disabled                                     */
#define FXOS8700_F_SETUP_F_MODE_FIFO_CIRC      ((uint8_t) 0x40)  /*  FIFO contains the most recent samples when           */
                                                                 /*  overflowed (circular buffer). Oldest sample is       */
                                                                 /*  discarded to be replaced by new sample               */
#define FXOS8700_F_SETUP_F_MODE_FIFO_STOP_OVF  ((uint8_t) 0x80)  /*  FIFO stops accepting new samples when overflowed     */
#define FXOS8700_F_SETUP_F_MODE_FIFO_TRIGGER   ((uint8_t) 0xc0)  /*  FIFO trigger mode                                    */
/*------------------------------*/



/*--------------------------------
** Register: TRIG_CFG
** Enum: FXOS8700_TRIG_CFG
** --
** Offset : 0x0A - FIFO event trigger configuration register.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 1;
        uint8_t           trig_a_vecm : 1;
        uint8_t           trig_a_ffmt : 1;
        uint8_t            trig_pulse : 1;
        uint8_t           trig_lndprt : 1;
        uint8_t            trig_trans : 1;
    } b;
    uint8_t w;
} FXOS8700_TRIG_CFG_t;


/*
** TRIG_CFG - Bit field mask definitions 
*/
#define FXOS8700_TRIG_CFG_TRIG_A_VECM_MASK   ((uint8_t) 0x02)
#define FXOS8700_TRIG_CFG_TRIG_A_VECM_SHIFT  ((uint8_t)    1)

#define FXOS8700_TRIG_CFG_TRIG_A_FFMT_MASK   ((uint8_t) 0x04)
#define FXOS8700_TRIG_CFG_TRIG_A_FFMT_SHIFT  ((uint8_t)    2)

#define FXOS8700_TRIG_CFG_TRIG_PULSE_MASK    ((uint8_t) 0x08)
#define FXOS8700_TRIG_CFG_TRIG_PULSE_SHIFT   ((uint8_t)    3)

#define FXOS8700_TRIG_CFG_TRIG_LNDPRT_MASK   ((uint8_t) 0x10)
#define FXOS8700_TRIG_CFG_TRIG_LNDPRT_SHIFT  ((uint8_t)    4)

#define FXOS8700_TRIG_CFG_TRIG_TRANS_MASK    ((uint8_t) 0x20)
#define FXOS8700_TRIG_CFG_TRIG_TRANS_SHIFT   ((uint8_t)    5)


/*
** TRIG_CFG - Bit field value definitions  
*/
#define FXOS8700_TRIG_CFG_TRIG_A_VECM_EN        ((uint8_t) 0x02)  /*  Acceleration vector-magnitude FIFO trigger enable   */
#define FXOS8700_TRIG_CFG_TRIG_A_VECM_DIS       ((uint8_t) 0x00)  /*  Acceleration vector-magnitude FIFO trigger disable  */
#define FXOS8700_TRIG_CFG_TRIG_A_FFMT_EN        ((uint8_t) 0x04)  /*  Freefall/motion interrupt FIFO trigger enable       */
#define FXOS8700_TRIG_CFG_TRIG_A_FFMT_DIS       ((uint8_t) 0x00)  /*  Freefall/motion interrupt FIFO trigger disable      */
#define FXOS8700_TRIG_CFG_TRIG_PULSE_EN         ((uint8_t) 0x08)  /*  Pluse interrupt FIFO trigger enable                 */
#define FXOS8700_TRIG_CFG_TRIG_PULSE_DIS        ((uint8_t) 0x00)  /*  Pluse FIFO trigger enable                           */
#define FXOS8700_TRIG_CFG_TRIG_LNDPRT_EN        ((uint8_t) 0x10)  /*  Landscape/portrait orientation interrupt FIFO       */
                                                                  /*  trigger enable                                      */
#define FXOS8700_TRIG_CFG_TRIG_LNDPRT_DIS       ((uint8_t) 0x00)  /*  Landscape/portrait orientation interrupt FIFO       */
                                                                  /*  trigger disable                                     */
#define FXOS8700_TRIG_CFG_TRIG_TRANS_EN         ((uint8_t) 0x20)  /*  Transient interrupt FIFO trigger enable             */
#define FXOS8700_TRIG_CFG_TRIG_TRANS_DIS        ((uint8_t) 0x00)  /*  Transient interrupt FIFO trigger disable            */
/*------------------------------*/



/*--------------------------------
** Register: SYSMOD
** Enum: FXOS8700_SYSMOD
** --
** Offset : 0x0B - Current system mode.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                sysmod : 2;
        uint8_t                   fgt : 5;
        uint8_t                 fgerr : 1;
    } b;
    uint8_t w;
} FXOS8700_SYSMOD_t;


/*
** SYSMOD - Bit field mask definitions 
*/
#define FXOS8700_SYSMOD_SYSMOD_MASK   ((uint8_t) 0x03)
#define FXOS8700_SYSMOD_SYSMOD_SHIFT  ((uint8_t)    0)

#define FXOS8700_SYSMOD_FGT_MASK      ((uint8_t) 0x7C)
#define FXOS8700_SYSMOD_FGT_SHIFT     ((uint8_t)    2)

#define FXOS8700_SYSMOD_FGERR_MASK    ((uint8_t) 0x80)
#define FXOS8700_SYSMOD_FGERR_SHIFT   ((uint8_t)    7)


/*
** SYSMOD - Bit field value definitions  
*/
#define FXOS8700_SYSMOD_SYSMOD_STANDBY        ((uint8_t) 0x00)  /*  Standby mode                                          */
#define FXOS8700_SYSMOD_SYSMOD_WAKE           ((uint8_t) 0x01)  /*  Wake mode                                             */
#define FXOS8700_SYSMOD_SYSMOD_SLEEP          ((uint8_t) 0x02)  /*  Sleep mode                                            */
/*------------------------------*/




/*--------------------------------
** Register: INT_SOURCE
** Enum: FXOS8700_INT_SOURCE
** --
** Offset : 0x0C - Interrupt status.
** ------------------------------*/
typedef union {
    struct {
        uint8_t              src_drdy : 1;
        uint8_t            src_a_vecm : 1;
        uint8_t              src_ffmt : 1;
        uint8_t             src_pulse : 1;
        uint8_t            src_lndprt : 1;
        uint8_t             src_trans : 1;
        uint8_t              src_fifo : 1;
        uint8_t              src_aslp : 1;
    } b;
    uint8_t w;
} FXOS8700_INT_SOURCE_t;


/*
** INT_SOURCE - Bit field mask definitions 
*/
#define FXOS8700_INT_SOURCE_SRC_DRDY_MASK     ((uint8_t) 0x01)
#define FXOS8700_INT_SOURCE_SRC_DRDY_SHIFT    ((uint8_t)    0)

#define FXOS8700_INT_SOURCE_SRC_A_VECM_MASK   ((uint8_t) 0x02)
#define FXOS8700_INT_SOURCE_SRC_A_VECM_SHIFT  ((uint8_t)    1)

#define FXOS8700_INT_SOURCE_SRC_FFMT_MASK     ((uint8_t) 0x04)
#define FXOS8700_INT_SOURCE_SRC_FFMT_SHIFT    ((uint8_t)    2)

#define FXOS8700_INT_SOURCE_SRC_PULSE_MASK    ((uint8_t) 0x08)
#define FXOS8700_INT_SOURCE_SRC_PULSE_SHIFT   ((uint8_t)    3)

#define FXOS8700_INT_SOURCE_SRC_LNDPRT_MASK   ((uint8_t) 0x10)
#define FXOS8700_INT_SOURCE_SRC_LNDPRT_SHIFT  ((uint8_t)    4)

#define FXOS8700_INT_SOURCE_SRC_TRANS_MASK    ((uint8_t) 0x20)
#define FXOS8700_INT_SOURCE_SRC_TRANS_SHIFT   ((uint8_t)    5)

#define FXOS8700_INT_SOURCE_SRC_FIFO_MASK     ((uint8_t) 0x40)
#define FXOS8700_INT_SOURCE_SRC_FIFO_SHIFT    ((uint8_t)    6)

#define FXOS8700_INT_SOURCE_SRC_ASLP_MASK     ((uint8_t) 0x80)
#define FXOS8700_INT_SOURCE_SRC_ASLP_SHIFT    ((uint8_t)    7)


/*------------------------------*/



/*--------------------------------
** Register: WHO_AM_I
** Enum: FXOS8700_WHO_AM_I
** --
** Offset : 0x0D - Device ID.
** ------------------------------*/
typedef uint8_t FXOS8700_WHO_AM_I_t;



/*--------------------------------
** Register: XYZ_DATA_CFG
** Enum: FXOS8700_XYZ_DATA_CFG
** --
** Offset : 0x0E - Acceleration dynamic range and filter enable settings.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                    fs : 2;
        uint8_t _reserved_            : 2;
        uint8_t               hpf_out : 1; /*  - Enable high-pass filter on acceleration output data                      */

    } b;
    uint8_t w;
} FXOS8700_XYZ_DATA_CFG_t;


/*
** XYZ_DATA_CFG - Bit field mask definitions 
*/
#define FXOS8700_XYZ_DATA_CFG_FS_MASK        ((uint8_t) 0x03)
#define FXOS8700_XYZ_DATA_CFG_FS_SHIFT       ((uint8_t)    0)

#define FXOS8700_XYZ_DATA_CFG_HPF_OUT_MASK   ((uint8_t) 0x10)
#define FXOS8700_XYZ_DATA_CFG_HPF_OUT_SHIFT  ((uint8_t)    4)


/*
** XYZ_DATA_CFG - Bit field value definitions  
*/
#define FXOS8700_XYZ_DATA_CFG_HPF_OUT_EN            ((uint8_t) 0x10)  /*  Enable high-pass filter on acceleration output  */
                                                                      /*  data                                            */
#define FXOS8700_XYZ_DATA_CFG_HPF_OUT_DISABLE       ((uint8_t) 0x00)  /*  High-pass filter is disabled                    */
#define FXOS8700_XYZ_DATA_CFG_FS_2G_0P244           ((uint8_t) 0x00)  /*  0.244 mg/LSB                                    */
#define FXOS8700_XYZ_DATA_CFG_FS_4G_0P488           ((uint8_t) 0x01)  /*  0.488 mg/LSB                                    */
#define FXOS8700_XYZ_DATA_CFG_FS_8G_0P976           ((uint8_t) 0x02)  /*  0.976 mg/LSB                                    */
/*------------------------------*/



/*--------------------------------
** Register: HP_FILTER_CUTOFF
** Enum: FXOS8700_HP_FILTER_CUTOFF
** --
** Offset : 0x0F - Pulse detection highpass and lowpass filter enabling bits.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                   sel : 2;
        uint8_t _reserved_            : 2;
        uint8_t          pulse_lpf_en : 1;
        uint8_t         pulse_hpf_byp : 1;
    } b;
    uint8_t w;
} FXOS8700_HP_FILTER_CUTOFF_t;


/*
** HP_FILTER_CUTOFF - Bit field mask definitions 
*/
#define FXOS8700_HP_FILTER_CUTOFF_SEL_MASK             ((uint8_t) 0x03)
#define FXOS8700_HP_FILTER_CUTOFF_SEL_SHIFT            ((uint8_t)    0)

#define FXOS8700_HP_FILTER_CUTOFF_PULSE_LPF_EN_MASK    ((uint8_t) 0x10)
#define FXOS8700_HP_FILTER_CUTOFF_PULSE_LPF_EN_SHIFT   ((uint8_t)    4)

#define FXOS8700_HP_FILTER_CUTOFF_PULSE_HPF_BYP_MASK   ((uint8_t) 0x20)
#define FXOS8700_HP_FILTER_CUTOFF_PULSE_HPF_BYP_SHIFT  ((uint8_t)    5)


/*
** HP_FILTER_CUTOFF - Bit field value definitions  
*/
#define FXOS8700_HP_FILTER_CUTOFF_PULSE_HPF_BYP_EN      ((uint8_t) 0x00)  /*  HPF enabled for pulse processing            */
#define FXOS8700_HP_FILTER_CUTOFF_PULSE_HPF_BYP_BYPASS  ((uint8_t) 0x20)  /*  HPF bypassed for pulse processing           */
#define FXOS8700_HP_FILTER_CUTOFF_PULSE_LPF_EN_EN       ((uint8_t) 0x10)  /*  LPF enabled for pulse processing            */
#define FXOS8700_HP_FILTER_CUTOFF_PULSE_LPF_EN_DISABLE  ((uint8_t) 0x00)  /*  LPF bypassed for pulse processing           */
#define FXOS8700_HP_FILTER_CUTOFF_SEL_EN                ((uint8_t) 0x01)  /*  HPF cutoff frequency selection Enabled      */
#define FXOS8700_HP_FILTER_CUTOFF_SEL_DISABLE           ((uint8_t) 0x00)  /*  HPF cutoff frequency selection Disabled     */
/*------------------------------*/



/*--------------------------------
** Register: PL_STATUS
** Enum: FXOS8700_PL_STATUS
** --
** Offset : 0x10 - Landscape/portrait orientation status.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                 bafro : 1;
        uint8_t                  lapo : 2;
        uint8_t _reserved_            : 3;
        uint8_t                    lo : 1;
        uint8_t                 newlp : 1;
    } b;
    uint8_t w;
} FXOS8700_PL_STATUS_t;


/*
** PL_STATUS - Bit field mask definitions 
*/
#define FXOS8700_PL_STATUS_BAFRO_MASK   ((uint8_t) 0x01)
#define FXOS8700_PL_STATUS_BAFRO_SHIFT  ((uint8_t)    0)

#define FXOS8700_PL_STATUS_LAPO_MASK    ((uint8_t) 0x06)
#define FXOS8700_PL_STATUS_LAPO_SHIFT   ((uint8_t)    1)

#define FXOS8700_PL_STATUS_LO_MASK      ((uint8_t) 0x40)
#define FXOS8700_PL_STATUS_LO_SHIFT     ((uint8_t)    6)

#define FXOS8700_PL_STATUS_NEWLP_MASK   ((uint8_t) 0x80)
#define FXOS8700_PL_STATUS_NEWLP_SHIFT  ((uint8_t)    7)


/*------------------------------*/



/*--------------------------------
** Register: PL_CFG
** Enum: FXOS8700_PL_CFG
** --
** Offset : 0x11 - Landscape/portrait configuration.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 6;
        uint8_t                 pl_en : 1;
        uint8_t                dbcntm : 1;
    } b;
    uint8_t w;
} FXOS8700_PL_CFG_t;


/*
** PL_CFG - Bit field mask definitions 
*/
#define FXOS8700_PL_CFG_PL_EN_MASK    ((uint8_t) 0x40)
#define FXOS8700_PL_CFG_PL_EN_SHIFT   ((uint8_t)    6)

#define FXOS8700_PL_CFG_DBCNTM_MASK   ((uint8_t) 0x80)
#define FXOS8700_PL_CFG_DBCNTM_SHIFT  ((uint8_t)    7)


/*
** PL_CFG - Bit field value definitions  
*/
#define FXOS8700_PL_CFG_DBCNTM_DECREMENT_MODE ((uint8_t) 0x00)  /*  Decrements debounce whenever condition of interest is */
                                                                /*  no longer valid                                       */
#define FXOS8700_PL_CFG_DBCNTM_CLEAR_MODE     ((uint8_t) 0x80)  /*  Clears counter whenever condition of interest is no   */
                                                                /*  longer valid                                          */
#define FXOS8700_PL_CFG_PL_EN_DISABLE         ((uint8_t) 0x00)  /*  Portrait/Landscape detection is disabled.             */
#define FXOS8700_PL_CFG_PL_EN_ENABLE          ((uint8_t) 0x40)  /*  Portrait/Landscape detection is enabled.              */
/*------------------------------*/



/*--------------------------------
** Register: PL_COUNT
** Enum: FXOS8700_PL_COUNT
** --
** Offset : 0x12 - Landscape/portrait debounce counter.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                 dbnce;
    } b;
    uint8_t w;
} FXOS8700_PL_COUNT_t;


/*
** PL_COUNT - Bit field mask definitions 
*/
#define FXOS8700_PL_COUNT_DBNCE_MASK   ((uint8_t) 0xFF)
#define FXOS8700_PL_COUNT_DBNCE_SHIFT  ((uint8_t)    0)


/*------------------------------*/



/*--------------------------------
** Register: PL_BF_ZCOMP
** Enum: FXOS8700_PL_BF_ZCOMP
** --
** Offset : 0x13 - Back/front trip angle threshold.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                 zlock : 3;
        uint8_t _reserved_            : 3;
        uint8_t                  bkfr : 2;
    } b;
    uint8_t w;
} FXOS8700_PL_BF_ZCOMP_t;


/*
** PL_BF_ZCOMP - Bit field mask definitions 
*/
#define FXOS8700_PL_BF_ZCOMP_ZLOCK_MASK   ((uint8_t) 0x07)
#define FXOS8700_PL_BF_ZCOMP_ZLOCK_SHIFT  ((uint8_t)    0)

#define FXOS8700_PL_BF_ZCOMP_BKFR_MASK    ((uint8_t) 0xC0)
#define FXOS8700_PL_BF_ZCOMP_BKFR_SHIFT   ((uint8_t)    6)


/*
** PL_BF_ZCOMP - Bit field value definitions  
*/
#define FXOS8700_PL_BF_ZCOMP_BKFR_BF_LT80_GT280__FB_LT260_GT100 ((uint8_t) 0x00) 
#define FXOS8700_PL_BF_ZCOMP_BKFR_BF_LT75_GT285__FB_LT255_GT105 ((uint8_t) 0x40) 
#define FXOS8700_PL_BF_ZCOMP_BKFR_BF_LT70_GT290__FB_LT250_GT110 ((uint8_t) 0x80) 
#define FXOS8700_PL_BF_ZCOMP_BKFR_BF_LT65_GT295__FB_LT245_GT115 ((uint8_t) 0xc0) 
#define FXOS8700_PL_BF_ZCOMP_ZLOCK_13P6MIN_14P5MAX ((uint8_t) 0x00) 
#define FXOS8700_PL_BF_ZCOMP_ZLOCK_17P1MIN_18P2MAX ((uint8_t) 0x01) 
#define FXOS8700_PL_BF_ZCOMP_ZLOCK_20P7MIN_22P0MAX ((uint8_t) 0x02) 
#define FXOS8700_PL_BF_ZCOMP_ZLOCK_24P4MIN_25P9MAX ((uint8_t) 0x04) 
#define FXOS8700_PL_BF_ZCOMP_ZLOCK_28P1MIN_30P0MAX ((uint8_t) 0x04) 
#define FXOS8700_PL_BF_ZCOMP_ZLOCK_32P0MIN_34P2MAX ((uint8_t) 0x05) 
#define FXOS8700_PL_BF_ZCOMP_ZLOCK_36P1MIN_38P7MAX ((uint8_t) 0x06) 
#define FXOS8700_PL_BF_ZCOMP_ZLOCK_40P4MIN_43P4MAX ((uint8_t) 0x07) 
/*------------------------------*/



/*--------------------------------
** Register: PL_THS_REG
** Enum: FXOS8700_PL_THS_REG
** --
** Offset : 0x14 - Portrait to landscape trip threshold angle and hysteresis settings.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                   hys : 3;
        uint8_t                pl_ths : 5;
    } b;
    uint8_t w;
} FXOS8700_PL_THS_REG_t;


/*
** PL_THS_REG - Bit field mask definitions 
*/
#define FXOS8700_PL_THS_REG_HYS_MASK      ((uint8_t) 0x07)
#define FXOS8700_PL_THS_REG_HYS_SHIFT     ((uint8_t)    0)

#define FXOS8700_PL_THS_REG_PL_THS_MASK   ((uint8_t) 0xF8)
#define FXOS8700_PL_THS_REG_PL_THS_SHIFT  ((uint8_t)    3)


/*
** PL_THS_REG - Bit field value definitions  
*/
#define FXOS8700_PL_THS_REG_PL_THS_15DEG          ((uint8_t) 0x38) 
#define FXOS8700_PL_THS_REG_PL_THS_20DEG          ((uint8_t) 0x48) 
#define FXOS8700_PL_THS_REG_PL_THS_30DEG          ((uint8_t) 0x60) 
#define FXOS8700_PL_THS_REG_PL_THS_35DEG          ((uint8_t) 0x68) 
#define FXOS8700_PL_THS_REG_PL_THS_40DEG          ((uint8_t) 0x78) 
#define FXOS8700_PL_THS_REG_PL_THS_45DEG          ((uint8_t) 0x80) 
#define FXOS8700_PL_THS_REG_PL_THS_55DEG          ((uint8_t) 0x98) 
#define FXOS8700_PL_THS_REG_PL_THS_60DEG          ((uint8_t) 0xa0) 
#define FXOS8700_PL_THS_REG_PL_THS_70DEG          ((uint8_t) 0xb8) 
#define FXOS8700_PL_THS_REG_PL_THS_75DEG          ((uint8_t) 0xc8) 
#define FXOS8700_PL_THS_REG_HYS_LP45_PL45         ((uint8_t) 0x00) 
#define FXOS8700_PL_THS_REG_HYS_LP49_PL41         ((uint8_t) 0x01) 
#define FXOS8700_PL_THS_REG_HYS_LP52_PL38         ((uint8_t) 0x02) 
#define FXOS8700_PL_THS_REG_HYS_LP56_PL34         ((uint8_t) 0x03) 
#define FXOS8700_PL_THS_REG_HYS_LP59_PL31         ((uint8_t) 0x04) 
#define FXOS8700_PL_THS_REG_HYS_LP62_PL28         ((uint8_t) 0x05) 
#define FXOS8700_PL_THS_REG_HYS_LP66_PL24         ((uint8_t) 0x06) 
#define FXOS8700_PL_THS_REG_HYS_LP69_PL21         ((uint8_t) 0x07) 
/*------------------------------*/



/*--------------------------------
** Register: A_FFMT_CFG
** Enum: FXOS8700_A_FFMT_CFG
** --
** Offset : 0x15 - Freefall/motion function configuration.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 3;
        uint8_t                  xefe : 1;
        uint8_t                  yefe : 1;
        uint8_t                  zefe : 1;
        uint8_t                   oae : 1;
        uint8_t                   ele : 1;
    } b;
    uint8_t w;
} FXOS8700_A_FFMT_CFG_t;


/*
** A_FFMT_CFG - Bit field mask definitions 
*/
#define FXOS8700_A_FFMT_CFG_XEFE_MASK   ((uint8_t) 0x08)
#define FXOS8700_A_FFMT_CFG_XEFE_SHIFT  ((uint8_t)    3)

#define FXOS8700_A_FFMT_CFG_YEFE_MASK   ((uint8_t) 0x10)
#define FXOS8700_A_FFMT_CFG_YEFE_SHIFT  ((uint8_t)    4)

#define FXOS8700_A_FFMT_CFG_ZEFE_MASK   ((uint8_t) 0x20)
#define FXOS8700_A_FFMT_CFG_ZEFE_SHIFT  ((uint8_t)    5)

#define FXOS8700_A_FFMT_CFG_OAE_MASK    ((uint8_t) 0x40)
#define FXOS8700_A_FFMT_CFG_OAE_SHIFT   ((uint8_t)    6)

#define FXOS8700_A_FFMT_CFG_ELE_MASK    ((uint8_t) 0x80)
#define FXOS8700_A_FFMT_CFG_ELE_SHIFT   ((uint8_t)    7)


/*
** A_FFMT_CFG - Bit field value definitions  
*/
#define FXOS8700_A_FFMT_CFG_ELE_EN                ((uint8_t) 0x80)  /*  Event flag latch enabled                          */
#define FXOS8700_A_FFMT_CFG_ELE_DIS               ((uint8_t) 0x00)  /*  Event flag latch disabled                         */
#define FXOS8700_A_FFMT_CFG_OAE_FREEFALL          ((uint8_t) 0x00)  /*  Freefall flag                                     */
#define FXOS8700_A_FFMT_CFG_OAE_MOTION            ((uint8_t) 0x40)  /*  Motion flag                                       */
#define FXOS8700_A_FFMT_CFG_ZEFE_DIS              ((uint8_t) 0x00)  /*  Event detection disabled                          */
#define FXOS8700_A_FFMT_CFG_ZEFE_RAISE_EVENT      ((uint8_t) 0x20)  /*  Raise event flag on measured Z-axis acceleration  */
                                                                    /*  above/below threshold                             */
#define FXOS8700_A_FFMT_CFG_YEFE_DIS              ((uint8_t) 0x00)  /*  Event detection disabled                          */
#define FXOS8700_A_FFMT_CFG_YEFE_RAISE_EVENT      ((uint8_t) 0x10)  /*  Raise event flag on measured Y-axis acceleration  */
                                                                    /*  above/below threshold                             */
#define FXOS8700_A_FFMT_CFG_XEFE_DIS              ((uint8_t) 0x00)  /*  Event detection disabled                          */
#define FXOS8700_A_FFMT_CFG_XEFE_RAISE_EVENT      ((uint8_t) 0x08)  /*  Raise event flag on measured X-axis acceleration  */
                                                                    /*  above/below threshold                             */
/*------------------------------*/



/*--------------------------------
** Register: A_FFMT_SRC
** Enum: FXOS8700_A_FFMT_SRC
** --
** Offset : 0x16 - Freefall/motion event source register.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                   xhp : 1;
        uint8_t                   xhe : 1;
        uint8_t                   yhp : 1;
        uint8_t                   yhe : 1;
        uint8_t                   zhp : 1;
        uint8_t                   zhe : 1;
        uint8_t _reserved_            : 1;
        uint8_t                    ea : 1;
    } b;
    uint8_t w;
} FXOS8700_A_FFMT_SRC_t;


/*
** A_FFMT_SRC - Bit field mask definitions 
*/
#define FXOS8700_A_FFMT_SRC_XHP_MASK   ((uint8_t) 0x01)
#define FXOS8700_A_FFMT_SRC_XHP_SHIFT  ((uint8_t)    0)

#define FXOS8700_A_FFMT_SRC_XHE_MASK   ((uint8_t) 0x02)
#define FXOS8700_A_FFMT_SRC_XHE_SHIFT  ((uint8_t)    1)

#define FXOS8700_A_FFMT_SRC_YHP_MASK   ((uint8_t) 0x04)
#define FXOS8700_A_FFMT_SRC_YHP_SHIFT  ((uint8_t)    2)

#define FXOS8700_A_FFMT_SRC_YHE_MASK   ((uint8_t) 0x08)
#define FXOS8700_A_FFMT_SRC_YHE_SHIFT  ((uint8_t)    3)

#define FXOS8700_A_FFMT_SRC_ZHP_MASK   ((uint8_t) 0x10)
#define FXOS8700_A_FFMT_SRC_ZHP_SHIFT  ((uint8_t)    4)

#define FXOS8700_A_FFMT_SRC_ZHE_MASK   ((uint8_t) 0x20)
#define FXOS8700_A_FFMT_SRC_ZHE_SHIFT  ((uint8_t)    5)

#define FXOS8700_A_FFMT_SRC_EA_MASK    ((uint8_t) 0x80)
#define FXOS8700_A_FFMT_SRC_EA_SHIFT   ((uint8_t)    7)


/*------------------------------*/



/*--------------------------------
** Register: A_FFMT_THS
** Enum: FXOS8700_A_FFMT_THS
** --
** Offset : 0x17 - Freefall/motion threshold register.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                   ths : 7;
        uint8_t                dbcntm : 1;
    } b;
    uint8_t w;
} FXOS8700_A_FFMT_THS_t;


/*
** A_FFMT_THS - Bit field mask definitions 
*/
#define FXOS8700_A_FFMT_THS_THS_MASK      ((uint8_t) 0x7F)
#define FXOS8700_A_FFMT_THS_THS_SHIFT     ((uint8_t)    0)

#define FXOS8700_A_FFMT_THS_DBCNTM_MASK   ((uint8_t) 0x80)
#define FXOS8700_A_FFMT_THS_DBCNTM_SHIFT  ((uint8_t)    7)


/*------------------------------*/



/*--------------------------------
** Register: A_FFMT_COUNT
** Enum: FXOS8700_A_FFMT_COUNT
** --
** Offset : 0x18 - Freefall/motion debounce counter.
** ------------------------------*/
typedef uint8_t FXOS8700_A_FFMT_COUNT_t;




/*--------------------------------
** Register: TRANSIENT_CFG
** Enum: FXOS8700_TRANSIENT_CFG
** --
** Offset : 0x1D - Transient function configuration.
** ------------------------------*/
typedef union {
    struct {
        uint8_t               hpf_byp : 1;
        uint8_t                 xtefe : 1;
        uint8_t                 ytefe : 1;
        uint8_t                 ztefe : 1;
        uint8_t                  tele : 1;
    } b;
    uint8_t w;
} FXOS8700_TRANSIENT_CFG_t;


/*
** TRANSIENT_CFG - Bit field mask definitions 
*/
#define FXOS8700_TRANSIENT_CFG_HPF_BYP_MASK   ((uint8_t) 0x01)
#define FXOS8700_TRANSIENT_CFG_HPF_BYP_SHIFT  ((uint8_t)    0)

#define FXOS8700_TRANSIENT_CFG_XTEFE_MASK     ((uint8_t) 0x02)
#define FXOS8700_TRANSIENT_CFG_XTEFE_SHIFT    ((uint8_t)    1)

#define FXOS8700_TRANSIENT_CFG_YTEFE_MASK     ((uint8_t) 0x04)
#define FXOS8700_TRANSIENT_CFG_YTEFE_SHIFT    ((uint8_t)    2)

#define FXOS8700_TRANSIENT_CFG_ZTEFE_MASK     ((uint8_t) 0x08)
#define FXOS8700_TRANSIENT_CFG_ZTEFE_SHIFT    ((uint8_t)    3)

#define FXOS8700_TRANSIENT_CFG_TELE_MASK      ((uint8_t) 0x10)
#define FXOS8700_TRANSIENT_CFG_TELE_SHIFT     ((uint8_t)    4)


/*
** TRANSIENT_CFG - Bit field value definitions  
*/
#define FXOS8700_TRANSIENT_CFG_TELE_EN               ((uint8_t) 0x10)  /*  Event flag latch enabled: the transient        */
                                                                       /*  interrupt event flag is latched and a read of  */
                                                                       /*  the TRANSIENT_SRC register is required to      */
                                                                       /*  clear the event flag                           */
#define FXOS8700_TRANSIENT_CFG_TELE_DIS              ((uint8_t) 0x00)  /*  Event flag latch disabled: the transient       */
                                                                       /*  interrupt flag reflects the real-time status   */
                                                                       /*  of the function                                */
#define FXOS8700_TRANSIENT_CFG_ZTEFE_EN              ((uint8_t) 0x08)  /*  Z-axis event detection enabled. Raise event    */
                                                                       /*  flag on Z-axis acceleration value greater than */
                                                                       /*  threshold                                      */
#define FXOS8700_TRANSIENT_CFG_ZTEFE_DIS             ((uint8_t) 0x00)  /*  Z-axis event detection disabled                */
#define FXOS8700_TRANSIENT_CFG_YTEFE_EN              ((uint8_t) 0x04)  /*  Y-axis event detection enabled. Raise event    */
                                                                       /*  flag on Y-axis acceleration value greater than */
                                                                       /*  threshold                                      */
#define FXOS8700_TRANSIENT_CFG_YTEFE_DIS             ((uint8_t) 0x00)  /*  Y-axis event detection disabled                */
#define FXOS8700_TRANSIENT_CFG_XTEFE_EN              ((uint8_t) 0x02)  /*  X-axis event detection enabled. Raise event    */
                                                                       /*  flag on X-axis acceleration value greater than */
                                                                       /*  threshold                                      */
#define FXOS8700_TRANSIENT_CFG_XTEFE_DIS             ((uint8_t) 0x00)  /*  X-axis event detection disabled                */
#define FXOS8700_TRANSIENT_CFG_HPF_BYP_EN            ((uint8_t) 0x01)  /*  High-pass filter is not applied to             */
                                                                       /*  accelerometer data input to the transient      */
                                                                       /*  function                                       */
#define FXOS8700_TRANSIENT_CFG_HPF_BYP_DIS           ((uint8_t) 0x00)  /*  High-pass filter is applied to accelerometer   */
                                                                       /*  data input to the transient function           */
/*------------------------------*/



/*--------------------------------
** Register: TRANSIENT_SRC
** Enum: FXOS8700_TRANSIENT_SRC
** --
** Offset : 0x1E - Transient event status register.
** ------------------------------*/
typedef union {
    struct {
        uint8_t            trans_xpol : 1;
        uint8_t              tran_xef : 1;
        uint8_t             tran_ypol : 1;
        uint8_t              tran_yef : 1;
        uint8_t             tran_zpol : 1;
        uint8_t              tran_zef : 1;
        uint8_t               tran_ea : 1;
    } b;
    uint8_t w;
} FXOS8700_TRANSIENT_SRC_t;


/*
** TRANSIENT_SRC - Bit field mask definitions 
*/
#define FXOS8700_TRANSIENT_SRC_TRANS_XPOL_MASK   ((uint8_t) 0x01)
#define FXOS8700_TRANSIENT_SRC_TRANS_XPOL_SHIFT  ((uint8_t)    0)

#define FXOS8700_TRANSIENT_SRC_TRAN_XEF_MASK     ((uint8_t) 0x02)
#define FXOS8700_TRANSIENT_SRC_TRAN_XEF_SHIFT    ((uint8_t)    1)

#define FXOS8700_TRANSIENT_SRC_TRAN_YPOL_MASK    ((uint8_t) 0x04)
#define FXOS8700_TRANSIENT_SRC_TRAN_YPOL_SHIFT   ((uint8_t)    2)

#define FXOS8700_TRANSIENT_SRC_TRAN_YEF_MASK     ((uint8_t) 0x08)
#define FXOS8700_TRANSIENT_SRC_TRAN_YEF_SHIFT    ((uint8_t)    3)

#define FXOS8700_TRANSIENT_SRC_TRAN_ZPOL_MASK    ((uint8_t) 0x10)
#define FXOS8700_TRANSIENT_SRC_TRAN_ZPOL_SHIFT   ((uint8_t)    4)

#define FXOS8700_TRANSIENT_SRC_TRAN_ZEF_MASK     ((uint8_t) 0x20)
#define FXOS8700_TRANSIENT_SRC_TRAN_ZEF_SHIFT    ((uint8_t)    5)

#define FXOS8700_TRANSIENT_SRC_TRAN_EA_MASK      ((uint8_t) 0x40)
#define FXOS8700_TRANSIENT_SRC_TRAN_EA_SHIFT     ((uint8_t)    6)


/*------------------------------*/



/*--------------------------------
** Register: TRANSIENT_THS
** Enum: FXOS8700_TRANSIENT_THS
** --
** Offset : 0x1F - Transient event threshold.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                tr_ths : 7;
        uint8_t             tr_dbcntm : 1;
    } b;
    uint8_t w;
} FXOS8700_TRANSIENT_THS_t;


/*
** TRANSIENT_THS - Bit field mask definitions 
*/
#define FXOS8700_TRANSIENT_THS_TR_THS_MASK      ((uint8_t) 0x7F)
#define FXOS8700_TRANSIENT_THS_TR_THS_SHIFT     ((uint8_t)    0)

#define FXOS8700_TRANSIENT_THS_TR_DBCNTM_MASK   ((uint8_t) 0x80)
#define FXOS8700_TRANSIENT_THS_TR_DBCNTM_SHIFT  ((uint8_t)    7)


/*
** TRANSIENT_THS - Bit field value definitions  
*/
#define FXOS8700_TRANSIENT_THS_TR_THS_DECREMENTS     ((uint8_t) 0x00)  /*  Decrements debounce counter when the transient */
                                                                       /*  event condition is not true during the current */
                                                                       /*  ODR period                                     */
#define FXOS8700_TRANSIENT_THS_TR_THS_CLEAR          ((uint8_t) 0x01)  /*  Clears debounce counter when the transient     */
                                                                       /*  event condition is not true during the current */
                                                                       /*  ODR period                                     */
/*------------------------------*/



/*--------------------------------
** Register: TRANSIENT_COUNT
** Enum: FXOS8700_TRANSIENT_COUNT
** --
** Offset : 0x20 - Transient debounce counter.
** ------------------------------*/
typedef uint8_t FXOS8700_TRANSIENT_COUNT_t;





/*--------------------------------
** Register: PULSE_CFG
** Enum: FXOS8700_PULSE_CFG
** --
** Offset : 0x21 - Pulse function configuration.
** ------------------------------*/
typedef union {
    struct {
        uint8_t            pls_xspefe : 1;
        uint8_t            pls_xdpefe : 1;
        uint8_t            pls_yspefe : 1;
        uint8_t            pls_ydpefe : 1;
        uint8_t            pls_zspefe : 1;
        uint8_t            pls_zdpefe : 1;
        uint8_t               pls_ele : 1;
        uint8_t               pls_dpa : 1;
    } b;
    uint8_t w;
} FXOS8700_PULSE_CFG_t;


/*
** PULSE_CFG - Bit field mask definitions 
*/
#define FXOS8700_PULSE_CFG_PLS_XSPEFE_MASK   ((uint8_t) 0x01)
#define FXOS8700_PULSE_CFG_PLS_XSPEFE_SHIFT  ((uint8_t)    0)

#define FXOS8700_PULSE_CFG_PLS_XDPEFE_MASK   ((uint8_t) 0x02)
#define FXOS8700_PULSE_CFG_PLS_XDPEFE_SHIFT  ((uint8_t)    1)

#define FXOS8700_PULSE_CFG_PLS_YSPEFE_MASK   ((uint8_t) 0x04)
#define FXOS8700_PULSE_CFG_PLS_YSPEFE_SHIFT  ((uint8_t)    2)

#define FXOS8700_PULSE_CFG_PLS_YDPEFE_MASK   ((uint8_t) 0x08)
#define FXOS8700_PULSE_CFG_PLS_YDPEFE_SHIFT  ((uint8_t)    3)

#define FXOS8700_PULSE_CFG_PLS_ZSPEFE_MASK   ((uint8_t) 0x10)
#define FXOS8700_PULSE_CFG_PLS_ZSPEFE_SHIFT  ((uint8_t)    4)

#define FXOS8700_PULSE_CFG_PLS_ZDPEFE_MASK   ((uint8_t) 0x20)
#define FXOS8700_PULSE_CFG_PLS_ZDPEFE_SHIFT  ((uint8_t)    5)

#define FXOS8700_PULSE_CFG_PLS_ELE_MASK      ((uint8_t) 0x40)
#define FXOS8700_PULSE_CFG_PLS_ELE_SHIFT     ((uint8_t)    6)

#define FXOS8700_PULSE_CFG_PLS_DPA_MASK      ((uint8_t) 0x80)
#define FXOS8700_PULSE_CFG_PLS_DPA_SHIFT     ((uint8_t)    7)


/*
** PULSE_CFG - Bit field value definitions  
*/
#define FXOS8700_PULSE_CFG_PLS_DPA_DIS           ((uint8_t) 0x00)  /*  Setting the pls_dpa bit momentarily suspends the   */
                                                                   /*  double-tap detection if the start of a pulse is    */
                                                                   /*  detected during the time period specified by the   */
                                                                   /*  PULSE_LTCY register and the pulse ends before the  */
                                                                   /*  end of the time period specified by the PULSE_LTCY */
                                                                   /*  register                                           */
#define FXOS8700_PULSE_CFG_PLS_DPA_EN            ((uint8_t) 0x80)  /*  Double-pulse detection is not aborted if the start */
                                                                   /*  of a pulse is detected during the time period      */
                                                                   /*  specified by the PULSE_LTCY register               */
#define FXOS8700_PULSE_CFG_PLS_ELE_DIS           ((uint8_t) 0x00)  /*  Event flag latch disabled                          */
#define FXOS8700_PULSE_CFG_PLS_ELE_EN            ((uint8_t) 0x40)  /*  Event flag latch enabled                           */
#define FXOS8700_PULSE_CFG_PLS_ZDPEFE_DIS        ((uint8_t) 0x00)  /*  Event flag latch disabled                          */
#define FXOS8700_PULSE_CFG_PLS_ZDPEFE_EN         ((uint8_t) 0x20)  /*  Raise event flag on detection of double-pulse      */
                                                                   /*  event on Z-axis                                    */
#define FXOS8700_PULSE_CFG_PLS_ZSPEFE_DIS        ((uint8_t) 0x00)  /*  Event flag latch disabled                          */
#define FXOS8700_PULSE_CFG_PLS_ZSPEFE_EN         ((uint8_t) 0x10)  /*  Raise event flag on detection of single-pulse      */
                                                                   /*  event on Z-axis                                    */
#define FXOS8700_PULSE_CFG_PLS_YDPEFE_DIS        ((uint8_t) 0x00)  /*  Event flag latch disabled                          */
#define FXOS8700_PULSE_CFG_PLS_YDPEFE_EN         ((uint8_t) 0x08)  /*  Raise event flag on detection of double-pulse      */
                                                                   /*  event on Y-axis                                    */
#define FXOS8700_PULSE_CFG_PLS_YSPEFE_DIS        ((uint8_t) 0x00)  /*  Event flag latch disabled                          */
#define FXOS8700_PULSE_CFG_PLS_YSPEFE_EN         ((uint8_t) 0x04)  /*  Raise event flag on detection of single-pulse      */
                                                                   /*  event on Y-axis                                    */
#define FXOS8700_PULSE_CFG_PLS_XDPEFE_DIS        ((uint8_t) 0x00)  /*  Event flag latch disabled                          */
#define FXOS8700_PULSE_CFG_PLS_XDPEFE_EN         ((uint8_t) 0x02)  /*  Raise event flag on detection of double-pulse      */
                                                                   /*  event on X-axis                                    */
#define FXOS8700_PULSE_CFG_PLS_XSPEFE_DIS        ((uint8_t) 0x00)  /*  Event flag latch disabled                          */
#define FXOS8700_PULSE_CFG_PLS_XSPEFE_EN         ((uint8_t) 0x01)  /*  Raise event flag on detection of single-pulse      */
                                                                   /*  event on X-axis                                    */
/*------------------------------*/



/*--------------------------------
** Register: PULSE_SRC
** Enum: FXOS8700_PULSE_SRC
** --
** Offset : 0x22 - Pulse function source register.
** ------------------------------*/
typedef union {
    struct {
        uint8_t          pls_src_polx : 1;
        uint8_t          pls_src_poly : 1;
        uint8_t          pls_src_polz : 1;
        uint8_t           pls_src_dpe : 1;
        uint8_t           pls_src_axx : 1;
        uint8_t           pls_src_axy : 1;
        uint8_t           pls_src_axz : 1;
        uint8_t            pls_src_ea : 1;
    } b;
    uint8_t w;
} FXOS8700_PULSE_SRC_t;


/*
** PULSE_SRC - Bit field mask definitions 
*/
#define FXOS8700_PULSE_SRC_PLS_SRC_POLX_MASK   ((uint8_t) 0x01)
#define FXOS8700_PULSE_SRC_PLS_SRC_POLX_SHIFT  ((uint8_t)    0)

#define FXOS8700_PULSE_SRC_PLS_SRC_POLY_MASK   ((uint8_t) 0x02)
#define FXOS8700_PULSE_SRC_PLS_SRC_POLY_SHIFT  ((uint8_t)    1)

#define FXOS8700_PULSE_SRC_PLS_SRC_POLZ_MASK   ((uint8_t) 0x04)
#define FXOS8700_PULSE_SRC_PLS_SRC_POLZ_SHIFT  ((uint8_t)    2)

#define FXOS8700_PULSE_SRC_PLS_SRC_DPE_MASK    ((uint8_t) 0x08)
#define FXOS8700_PULSE_SRC_PLS_SRC_DPE_SHIFT   ((uint8_t)    3)

#define FXOS8700_PULSE_SRC_PLS_SRC_AXX_MASK    ((uint8_t) 0x10)
#define FXOS8700_PULSE_SRC_PLS_SRC_AXX_SHIFT   ((uint8_t)    4)

#define FXOS8700_PULSE_SRC_PLS_SRC_AXY_MASK    ((uint8_t) 0x20)
#define FXOS8700_PULSE_SRC_PLS_SRC_AXY_SHIFT   ((uint8_t)    5)

#define FXOS8700_PULSE_SRC_PLS_SRC_AXZ_MASK    ((uint8_t) 0x40)
#define FXOS8700_PULSE_SRC_PLS_SRC_AXZ_SHIFT   ((uint8_t)    6)

#define FXOS8700_PULSE_SRC_PLS_SRC_EA_MASK     ((uint8_t) 0x80)
#define FXOS8700_PULSE_SRC_PLS_SRC_EA_SHIFT    ((uint8_t)    7)


/*------------------------------*/



/*--------------------------------
** Register: PULSE_THSX
** Enum: FXOS8700_PULSE_THSX
** --
** Offset : 0x23 - X-axis pulse threshold.
** ------------------------------*/
typedef union {
    struct {
        uint8_t              pls_thsx : 7;
    } b;
    uint8_t w;
} FXOS8700_PULSE_THSX_t;


/*
** PULSE_THSX - Bit field mask definitions 
*/
#define FXOS8700_PULSE_THSX_PLS_THSX_MASK   ((uint8_t) 0x7F)
#define FXOS8700_PULSE_THSX_PLS_THSX_SHIFT  ((uint8_t)    0)


/*------------------------------*/



/*--------------------------------
** Register: PULSE_THSY
** Enum: FXOS8700_PULSE_THSY
** --
** Offset : 0x24 - Y-axis pulse threshold.
** ------------------------------*/
typedef union {
    struct {
        uint8_t              pls_thsy : 7;
    } b;
    uint8_t w;
} FXOS8700_PULSE_THSY_t;


/*
** PULSE_THSY - Bit field mask definitions 
*/
#define FXOS8700_PULSE_THSY_PLS_THSY_MASK   ((uint8_t) 0x7F)
#define FXOS8700_PULSE_THSY_PLS_THSY_SHIFT  ((uint8_t)    0)


/*------------------------------*/



/*--------------------------------
** Register: PULSE_THSZ
** Enum: FXOS8700_PULSE_THSZ
** --
** Offset : 0x25 - Z-axis pulse threshold.
** ------------------------------*/
typedef union {
    struct {
        uint8_t              pls_thsz : 7;
    } b;
    uint8_t w;
} FXOS8700_PULSE_THSZ_t;


/*
** PULSE_THSZ - Bit field mask definitions 
*/
#define FXOS8700_PULSE_THSZ_PLS_THSZ_MASK   ((uint8_t) 0x7F)
#define FXOS8700_PULSE_THSZ_PLS_THSZ_SHIFT  ((uint8_t)    0)


/*------------------------------*/



/*--------------------------------
** Register: PULSE_TMLT
** Enum: FXOS8700_PULSE_TMLT
** --
** Offset : 0x26 - Time limit for pulse detection.
** ------------------------------*/
typedef uint8_t FXOS8700_PULSE_TMLT_t;



/*--------------------------------
** Register: PULSE_LTCY
** Enum: FXOS8700_PULSE_LTCY
** --
** Offset : 0x27 - Latency time for second pulse detection.
** ------------------------------*/
typedef uint8_t FXOS8700_PULSE_LTCY_t;


/*--------------------------------
** Register: PULSE_WIND
** Enum: FXOS8700_PULSE_WIND
** --
** Offset : 0x28 - Window time for second pulse detection.
** ------------------------------*/
typedef uint8_t FXOS8700_PULSE_WIND_t;



/*--------------------------------
** Register: ASLP_COUNT
** Enum: FXOS8700_ASLP_COUNT
** --
** Offset : 0x29 - The counter setting for auto-sleep period.
** ------------------------------*/
typedef uint8_t FXOS8700_ASLP_COUNT_t;



/*--------------------------------
** Register: CTRL_REG1
** Enum: FXOS8700_CTRL_REG1
** --
** Offset : 0x2A - System ODR, accelerometer OSR (Output sample rate), operating mode.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                active : 1;
        uint8_t                f_read : 1;
        uint8_t                lnoise : 1;
        uint8_t                    dr : 3;
        uint8_t             aslp_rate : 2;
    } b;
    uint8_t w;
} FXOS8700_CTRL_REG1_t;


/*
** CTRL_REG1 - Bit field mask definitions 
*/
#define FXOS8700_CTRL_REG1_ACTIVE_MASK      ((uint8_t) 0x01)
#define FXOS8700_CTRL_REG1_ACTIVE_SHIFT     ((uint8_t)    0)

#define FXOS8700_CTRL_REG1_F_READ_MASK      ((uint8_t) 0x02)
#define FXOS8700_CTRL_REG1_F_READ_SHIFT     ((uint8_t)    1)

#define FXOS8700_CTRL_REG1_LNOISE_MASK      ((uint8_t) 0x04)
#define FXOS8700_CTRL_REG1_LNOISE_SHIFT     ((uint8_t)    2)

#define FXOS8700_CTRL_REG1_DR_MASK          ((uint8_t) 0x38)
#define FXOS8700_CTRL_REG1_DR_SHIFT         ((uint8_t)    3)

#define FXOS8700_CTRL_REG1_ASLP_RATE_MASK   ((uint8_t) 0xC0)
#define FXOS8700_CTRL_REG1_ASLP_RATE_SHIFT  ((uint8_t)    6)


/*
** CTRL_REG1 - Bit field value definitions  
*/
#define FXOS8700_CTRL_REG1_ASLP_RATE_50_HZ       ((uint8_t) 0x00) 
#define FXOS8700_CTRL_REG1_ASLP_RATE_12P5_HZ     ((uint8_t) 0x40) 
#define FXOS8700_CTRL_REG1_ASLP_RATE_6P25_HZ     ((uint8_t) 0x80) 
#define FXOS8700_CTRL_REG1_ASLP_RATE_1P56_HZ     ((uint8_t) 0xc0) 
#define FXOS8700_CTRL_REG1_DR_SINGLE_800_HZ      ((uint8_t) 0x00) 
#define FXOS8700_CTRL_REG1_DR_SINGLE_400_HZ      ((uint8_t) 0x08) 
#define FXOS8700_CTRL_REG1_DR_SINGLE_200_HZ      ((uint8_t) 0x10) 
#define FXOS8700_CTRL_REG1_DR_SINGLE_100_HZ      ((uint8_t) 0x18) 
#define FXOS8700_CTRL_REG1_DR_SINGLE_50_HZ       ((uint8_t) 0x20) 
#define FXOS8700_CTRL_REG1_DR_SINGLE_12P5_HZ     ((uint8_t) 0x28) 
#define FXOS8700_CTRL_REG1_DR_SINGLE_6P25_HZ     ((uint8_t) 0x30) 
#define FXOS8700_CTRL_REG1_DR_SINGLE_1P5625_HZ   ((uint8_t) 0x38) 
#define FXOS8700_CTRL_REG1_DR_HYBRID_400_HZ      ((uint8_t) 0x00) 
#define FXOS8700_CTRL_REG1_DR_HYBRID_200_HZ      ((uint8_t) 0x08) 
#define FXOS8700_CTRL_REG1_DR_HYBRID_100_HZ      ((uint8_t) 0x10) 
#define FXOS8700_CTRL_REG1_DR_HYBRID_50_HZ       ((uint8_t) 0x18) 
#define FXOS8700_CTRL_REG1_DR_HYBRID_25_HZ       ((uint8_t) 0x20) 
#define FXOS8700_CTRL_REG1_DR_HYBRID_6P25_HZ     ((uint8_t) 0x28) 
#define FXOS8700_CTRL_REG1_DR_HYBRID_3P125_HZ    ((uint8_t) 0x30) 
#define FXOS8700_CTRL_REG1_DR_HYBRID_0P7813_HZ   ((uint8_t) 0x38) 
#define FXOS8700_CTRL_REG1_LNOISE_NORMAL         ((uint8_t) 0x00)  /*  Normal mode                                        */
#define FXOS8700_CTRL_REG1_LNOISE_REDUCED_NOISE  ((uint8_t) 0x04)  /*  Reduced noise mode; Note that the FSR setting is   */
                                                                   /*  restricted to Â±2 g or Â±4 g mode. This feature    */
                                                                   /*  cannot be used in Â±8 g mode                       */
#define FXOS8700_CTRL_REG1_F_READ_NORMAL         ((uint8_t) 0x00)  /*  Normal mode                                        */
#define FXOS8700_CTRL_REG1_F_READ_FAST           ((uint8_t) 0x02)  /*  Fast-read mode                                     */
#define FXOS8700_CTRL_REG1_ACTIVE_ACTIVE_MODE    ((uint8_t) 0x01)  /*  Active mode                                        */
#define FXOS8700_CTRL_REG1_ACTIVE_STANDBY_MODE   ((uint8_t) 0x00)  /*  Standby mode                                       */
/*------------------------------*/



/*--------------------------------
** Register: CTRL_REG2
** Enum: FXOS8700_CTRL_REG2
** --
** Offset : 0x2B - Self-test, reset, accelerometer OSR, and sleep mode settings.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                  mods : 2;
        uint8_t                  slpe : 1;
        uint8_t                 smods : 2;
        uint8_t _reserved_            : 1;
        uint8_t                   rst : 1;
        uint8_t                    st : 1;
    } b;
    uint8_t w;
} FXOS8700_CTRL_REG2_t;


/*
** CTRL_REG2 - Bit field mask definitions 
*/
#define FXOS8700_CTRL_REG2_MODS_MASK    ((uint8_t) 0x03)
#define FXOS8700_CTRL_REG2_MODS_SHIFT   ((uint8_t)    0)

#define FXOS8700_CTRL_REG2_SLPE_MASK    ((uint8_t) 0x04)
#define FXOS8700_CTRL_REG2_SLPE_SHIFT   ((uint8_t)    2)

#define FXOS8700_CTRL_REG2_SMODS_MASK   ((uint8_t) 0x18)
#define FXOS8700_CTRL_REG2_SMODS_SHIFT  ((uint8_t)    3)

#define FXOS8700_CTRL_REG2_RST_MASK     ((uint8_t) 0x40)
#define FXOS8700_CTRL_REG2_RST_SHIFT    ((uint8_t)    6)

#define FXOS8700_CTRL_REG2_ST_MASK      ((uint8_t) 0x80)
#define FXOS8700_CTRL_REG2_ST_SHIFT     ((uint8_t)    7)


/*
** CTRL_REG2 - Bit field value definitions  
*/
#define FXOS8700_CTRL_REG2_ST_DIS                ((uint8_t) 0x00)  /*  Self-test disabled                                 */
#define FXOS8700_CTRL_REG2_ST_EN                 ((uint8_t) 0x80)  /*  Self-test enabled                                  */
#define FXOS8700_CTRL_REG2_RST_EN                ((uint8_t) 0x40)  /*  Device reset enabled                               */
#define FXOS8700_CTRL_REG2_RST_DIS               ((uint8_t) 0x00)  /*  Device reset disabled                              */
#define FXOS8700_CTRL_REG2_SMODS_NORMAL          ((uint8_t) 0x00) 
#define FXOS8700_CTRL_REG2_SMODS_LOW_NOISE_LOW_POWER ((uint8_t) 0x08) 
#define FXOS8700_CTRL_REG2_SMODS_HIGH_RES        ((uint8_t) 0x10) 
#define FXOS8700_CTRL_REG2_SMODS_LOW_POWER       ((uint8_t) 0x18) 
#define FXOS8700_CTRL_REG2_SLPE_EN               ((uint8_t) 0x04) 
#define FXOS8700_CTRL_REG2_SLPE_DISABLE          ((uint8_t) 0x00) 
#define FXOS8700_CTRL_REG2_MODS_NORMAL           ((uint8_t) 0x00) 
#define FXOS8700_CTRL_REG2_MODS_LOW_NOISE_LOW_POWER ((uint8_t) 0x01) 
#define FXOS8700_CTRL_REG2_MODS_HIGH_RES         ((uint8_t) 0x02) 
#define FXOS8700_CTRL_REG2_MODS_LOW_POWER        ((uint8_t) 0x03) 
/*------------------------------*/



/*--------------------------------
** Register: CTRL_REG3
** Enum: FXOS8700_CTRL_REG3
** --
** Offset : 0x2C - Sleep mode interrupt wake enable, interrupt polarity, push-pull/open drain configuration.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                 pp_od : 1;
        uint8_t                  ipol : 1;
        uint8_t           wake_a_vecm : 1;
        uint8_t             wake_ffmt : 1;
        uint8_t            wake_pulse : 1;
        uint8_t           wake_lndprt : 1;
        uint8_t            wake_trans : 1;
        uint8_t             fifo_gate : 1;
    } b;
    uint8_t w;
} FXOS8700_CTRL_REG3_t;


/*
** CTRL_REG3 - Bit field mask definitions 
*/
#define FXOS8700_CTRL_REG3_PP_OD_MASK         ((uint8_t) 0x01)
#define FXOS8700_CTRL_REG3_PP_OD_SHIFT        ((uint8_t)    0)

#define FXOS8700_CTRL_REG3_IPOL_MASK          ((uint8_t) 0x02)
#define FXOS8700_CTRL_REG3_IPOL_SHIFT         ((uint8_t)    1)

#define FXOS8700_CTRL_REG3_WAKE_A_VECM_MASK   ((uint8_t) 0x04)
#define FXOS8700_CTRL_REG3_WAKE_A_VECM_SHIFT  ((uint8_t)    2)

#define FXOS8700_CTRL_REG3_WAKE_FFMT_MASK     ((uint8_t) 0x08)
#define FXOS8700_CTRL_REG3_WAKE_FFMT_SHIFT    ((uint8_t)    3)

#define FXOS8700_CTRL_REG3_WAKE_PULSE_MASK    ((uint8_t) 0x10)
#define FXOS8700_CTRL_REG3_WAKE_PULSE_SHIFT   ((uint8_t)    4)

#define FXOS8700_CTRL_REG3_WAKE_LNDPRT_MASK   ((uint8_t) 0x20)
#define FXOS8700_CTRL_REG3_WAKE_LNDPRT_SHIFT  ((uint8_t)    5)

#define FXOS8700_CTRL_REG3_WAKE_TRANS_MASK    ((uint8_t) 0x40)
#define FXOS8700_CTRL_REG3_WAKE_TRANS_SHIFT   ((uint8_t)    6)

#define FXOS8700_CTRL_REG3_FIFO_GATE_MASK     ((uint8_t) 0x80)
#define FXOS8700_CTRL_REG3_FIFO_GATE_SHIFT    ((uint8_t)    7)


/*
** CTRL_REG3 - Bit field value definitions  
*/
#define FXOS8700_CTRL_REG3_FIFO_GATE_BYPASSED    ((uint8_t) 0x00)  /*  FIFO gate is bypassed                              */
#define FXOS8700_CTRL_REG3_FIFO_GATE_BLOCKED     ((uint8_t) 0x80)  /*  The FIFO input buffer is blocked from accepting    */
                                                                   /*  new samples when transitioning from wake-to-sleep  */
                                                                   /*  mode or from sleep-to-wake mode until the FIFO is  */
                                                                   /*  flushed                                            */
#define FXOS8700_CTRL_REG3_WAKE_TRANS_DIS        ((uint8_t) 0x00)  /*  Transient function is disabled in sleep mode       */
#define FXOS8700_CTRL_REG3_WAKE_TRANS_EN         ((uint8_t) 0x40)  /*  Transient function is enabled in sleep mode and    */
                                                                   /*  can generate an interrupt to wake the system       */
#define FXOS8700_CTRL_REG3_WAKE_LNDPRT_DIS       ((uint8_t) 0x00)  /*  Orientation function is disabled sleep mode        */
#define FXOS8700_CTRL_REG3_WAKE_LNDPRT_EN        ((uint8_t) 0x20)  /*  Orientation function is enabled in sleep mode and  */
                                                                   /*  can generate an interrupt to wake the system       */
#define FXOS8700_CTRL_REG3_WAKE_PULSE_DIS        ((uint8_t) 0x00)  /*  Pulse function is disabled in sleep mode           */
#define FXOS8700_CTRL_REG3_WAKE_PULSE_EN         ((uint8_t) 0x10)  /*  Pulse function is enabled in sleep mode and can    */
                                                                   /*  generate an interrupt to wake the system           */
#define FXOS8700_CTRL_REG3_WAKE_FFMT_DIS         ((uint8_t) 0x00)  /*  Freefall/motion function is disabled in sleep mode */
#define FXOS8700_CTRL_REG3_WAKE_FFMT_EN          ((uint8_t) 0x08)  /*  Freefall/motion function is enabled in sleep mode  */
                                                                   /*  and can generate an interrupt to wake the system   */
#define FXOS8700_CTRL_REG3_WAKE_A_VECM_DIS       ((uint8_t) 0x00)  /*  Acceleration vector-magnitude function is disabled */
                                                                   /*  in sleep mode                                      */
#define FXOS8700_CTRL_REG3_WAKE_A_VECM_EN        ((uint8_t) 0x04)  /*  Acceleration vector-magnitude function is enabled  */
                                                                   /*  in sleep mode and can generate an interrupt to     */
                                                                   /*  wake the system                                    */
#define FXOS8700_CTRL_REG3_IPOL_ACTIVE_LOW       ((uint8_t) 0x00)  /*  Active Low                                         */
#define FXOS8700_CTRL_REG3_IPOL_ACTIVE_HIGH      ((uint8_t) 0x02)  /*  Active High                                        */
#define FXOS8700_CTRL_REG3_PP_OD_PUSH_PULL       ((uint8_t) 0x00)  /*  Push-pull                                          */
#define FXOS8700_CTRL_REG3_PP_OD_OPEN_DRAIN      ((uint8_t) 0x01)  /*  Open Drain                                         */
/*------------------------------*/



/*--------------------------------
** Register: CTRL_REG4
** Enum: FXOS8700_CTRL_REG4
** --
** Offset : 0x2D - Interrupt enable register.
** ------------------------------*/
typedef union {
    struct {
        uint8_t           int_en_drdy : 1;
        uint8_t         int_en_a_vecm : 1;
        uint8_t           int_en_ffmt : 1;
        uint8_t          int_en_pulse : 1;
        uint8_t         int_en_lndprt : 1;
        uint8_t          int_en_trans : 1;
        uint8_t           int_en_fifo : 1;
        uint8_t           int_en_aslp : 1;
    } b;
    uint8_t w;
} FXOS8700_CTRL_REG4_t;


/*
** CTRL_REG4 - Bit field mask definitions 
*/
#define FXOS8700_CTRL_REG4_INT_EN_DRDY_MASK     ((uint8_t) 0x01)
#define FXOS8700_CTRL_REG4_INT_EN_DRDY_SHIFT    ((uint8_t)    0)

#define FXOS8700_CTRL_REG4_INT_EN_A_VECM_MASK   ((uint8_t) 0x02)
#define FXOS8700_CTRL_REG4_INT_EN_A_VECM_SHIFT  ((uint8_t)    1)

#define FXOS8700_CTRL_REG4_INT_EN_FFMT_MASK     ((uint8_t) 0x04)
#define FXOS8700_CTRL_REG4_INT_EN_FFMT_SHIFT    ((uint8_t)    2)

#define FXOS8700_CTRL_REG4_INT_EN_PULSE_MASK    ((uint8_t) 0x08)
#define FXOS8700_CTRL_REG4_INT_EN_PULSE_SHIFT   ((uint8_t)    3)

#define FXOS8700_CTRL_REG4_INT_EN_LNDPRT_MASK   ((uint8_t) 0x10)
#define FXOS8700_CTRL_REG4_INT_EN_LNDPRT_SHIFT  ((uint8_t)    4)

#define FXOS8700_CTRL_REG4_INT_EN_TRANS_MASK    ((uint8_t) 0x20)
#define FXOS8700_CTRL_REG4_INT_EN_TRANS_SHIFT   ((uint8_t)    5)

#define FXOS8700_CTRL_REG4_INT_EN_FIFO_MASK     ((uint8_t) 0x40)
#define FXOS8700_CTRL_REG4_INT_EN_FIFO_SHIFT    ((uint8_t)    6)

#define FXOS8700_CTRL_REG4_INT_EN_ASLP_MASK     ((uint8_t) 0x80)
#define FXOS8700_CTRL_REG4_INT_EN_ASLP_SHIFT    ((uint8_t)    7)


/*
** CTRL_REG4 - Bit field value definitions  
*/
#define FXOS8700_CTRL_REG4_INT_EN_ASLP_DIS       ((uint8_t) 0x00)  /*  Auto-sleep/wake interrupt disabled                 */
#define FXOS8700_CTRL_REG4_INT_EN_ASLP_EN        ((uint8_t) 0x80)  /*  Auto-sleep/wake interrupt Enabled                  */
#define FXOS8700_CTRL_REG4_INT_EN_FIFO_DIS       ((uint8_t) 0x00)  /*  FIFO interrupt disabled                            */
#define FXOS8700_CTRL_REG4_INT_EN_FIFO_EN        ((uint8_t) 0x40)  /*  FIFO interrupt enabled                             */
#define FXOS8700_CTRL_REG4_INT_EN_TRANS_DIS      ((uint8_t) 0x00)  /*  Transient interrupt disabled                       */
#define FXOS8700_CTRL_REG4_INT_EN_TRANS_EN       ((uint8_t) 0x20)  /*  Transient interrupt enabled                        */
#define FXOS8700_CTRL_REG4_INT_EN_LNDPRT_DIS     ((uint8_t) 0x00)  /*  Orientation (landscape/portrait) interrupt         */
                                                                   /*  disabled                                           */
#define FXOS8700_CTRL_REG4_INT_EN_LNDPRT_EN      ((uint8_t) 0x10)  /*  Orientation (landscape/portrait) interrupt enabled */
#define FXOS8700_CTRL_REG4_INT_EN_PULSE_DIS      ((uint8_t) 0x00)  /*  Pulse detection interrupt disabled                 */
#define FXOS8700_CTRL_REG4_INT_EN_PULSE_EN       ((uint8_t) 0x08)  /*  Pulse detection interrupt enabled                  */
#define FXOS8700_CTRL_REG4_INT_EN_FFMT_DIS       ((uint8_t) 0x00)  /*  Freefall/motion interrupt disabled                 */
#define FXOS8700_CTRL_REG4_INT_EN_FFMT_EN        ((uint8_t) 0x04)  /*  Freefall/motion interrupt enabled                  */
#define FXOS8700_CTRL_REG4_INT_EN_A_VECM_DIS     ((uint8_t) 0x00)  /*  Acceleration vector-magnitude interrupt disabled   */
#define FXOS8700_CTRL_REG4_INT_EN_A_VECM_EN      ((uint8_t) 0x02)  /*  Acceleration vector-magnitude interrupt disabled   */
#define FXOS8700_CTRL_REG4_INT_EN_DRDY_DIS       ((uint8_t) 0x00)  /*  Data-ready interrupt disabled                      */
#define FXOS8700_CTRL_REG4_INT_EN_DRDY_EN        ((uint8_t) 0x01)  /*  Data-ready interrupt Enabled                       */
/*------------------------------*/



/*--------------------------------
** Register: CTRL_REG5
** Enum: FXOS8700_CTRL_REG5
** --
** Offset : 0x2E - Interrupt pin (INT1/INT2) map.
** ------------------------------*/
typedef union {
    struct {
        uint8_t          int_cfg_drdy : 1;
        uint8_t        int_cfg_a_vecm : 1;
        uint8_t          int_cfg_ffmt : 1;
        uint8_t         int_cfg_pulse : 1;
        uint8_t        int_cfg_lndprt : 1;
        uint8_t         int_cfg_trans : 1;
        uint8_t          int_cfg_fifo : 1;
        uint8_t          int_cfg_aslp : 1;
    } b;
    uint8_t w;
} FXOS8700_CTRL_REG5_t;


/*
** CTRL_REG5 - Bit field mask definitions 
*/
#define FXOS8700_CTRL_REG5_INT_CFG_DRDY_MASK     ((uint8_t) 0x01)
#define FXOS8700_CTRL_REG5_INT_CFG_DRDY_SHIFT    ((uint8_t)    0)

#define FXOS8700_CTRL_REG5_INT_CFG_A_VECM_MASK   ((uint8_t) 0x02)
#define FXOS8700_CTRL_REG5_INT_CFG_A_VECM_SHIFT  ((uint8_t)    1)

#define FXOS8700_CTRL_REG5_INT_CFG_FFMT_MASK     ((uint8_t) 0x04)
#define FXOS8700_CTRL_REG5_INT_CFG_FFMT_SHIFT    ((uint8_t)    2)

#define FXOS8700_CTRL_REG5_INT_CFG_PULSE_MASK    ((uint8_t) 0x08)
#define FXOS8700_CTRL_REG5_INT_CFG_PULSE_SHIFT   ((uint8_t)    3)

#define FXOS8700_CTRL_REG5_INT_CFG_LNDPRT_MASK   ((uint8_t) 0x10)
#define FXOS8700_CTRL_REG5_INT_CFG_LNDPRT_SHIFT  ((uint8_t)    4)

#define FXOS8700_CTRL_REG5_INT_CFG_TRANS_MASK    ((uint8_t) 0x20)
#define FXOS8700_CTRL_REG5_INT_CFG_TRANS_SHIFT   ((uint8_t)    5)

#define FXOS8700_CTRL_REG5_INT_CFG_FIFO_MASK     ((uint8_t) 0x40)
#define FXOS8700_CTRL_REG5_INT_CFG_FIFO_SHIFT    ((uint8_t)    6)

#define FXOS8700_CTRL_REG5_INT_CFG_ASLP_MASK     ((uint8_t) 0x80)
#define FXOS8700_CTRL_REG5_INT_CFG_ASLP_SHIFT    ((uint8_t)    7)


/*
** CTRL_REG5 - Bit field value definitions  
*/
#define FXOS8700_CTRL_REG5_INT_CFG_ASLP_INT2     ((uint8_t) 0x00)  /*  Interrupt is routed to INT2 pin                    */
#define FXOS8700_CTRL_REG5_INT_CFG_ASLP_INT1     ((uint8_t) 0x80)  /*  Interrupt is routed to INT1 pin                    */
#define FXOS8700_CTRL_REG5_INT_CFG_FIFO_INT2     ((uint8_t) 0x00)  /*  Interrupt is routed to INT2 pin                    */
#define FXOS8700_CTRL_REG5_INT_CFG_FIFO_INT1     ((uint8_t) 0x40)  /*  Interrupt is routed to INT1 pin                    */
#define FXOS8700_CTRL_REG5_INT_CFG_TRANS_INT2    ((uint8_t) 0x00)  /*  Interrupt is routed to INT2 pin                    */
#define FXOS8700_CTRL_REG5_INT_CFG_TRANS_INT1    ((uint8_t) 0x20)  /*  Interrupt is routed to INT1 pin                    */
#define FXOS8700_CTRL_REG5_INT_CFG_LNDPRT_INT2   ((uint8_t) 0x00)  /*  Interrupt is routed to INT2 pin                    */
#define FXOS8700_CTRL_REG5_INT_CFG_LNDPRT_INT1   ((uint8_t) 0x10)  /*  Interrupt is routed to INT1 pin                    */
#define FXOS8700_CTRL_REG5_INT_CFG_PULSE_INT2    ((uint8_t) 0x00)  /*  Interrupt is routed to INT2 pin                    */
#define FXOS8700_CTRL_REG5_INT_CFG_PULSE_INT1    ((uint8_t) 0x08)  /*  Interrupt is routed to INT1 pin                    */
#define FXOS8700_CTRL_REG5_INT_CFG_FFMT_INT2     ((uint8_t) 0x00)  /*  Interrupt is routed to INT2 pin                    */
#define FXOS8700_CTRL_REG5_INT_CFG_FFMT_INT1     ((uint8_t) 0x04)  /*  Interrupt is routed to INT1 pin                    */
#define FXOS8700_CTRL_REG5_INT_CFG_A_VECM_INT2   ((uint8_t) 0x00)  /*  Interrupt is routed to INT2 pin                    */
#define FXOS8700_CTRL_REG5_INT_CFG_A_VECM_INT1   ((uint8_t) 0x02)  /*  Interrupt is routed to INT1 pin                    */
#define FXOS8700_CTRL_REG5_INT_CFG_DRDY_INT2     ((uint8_t) 0x00)  /*  Interrupt is routed to INT2 pin                    */
#define FXOS8700_CTRL_REG5_INT_CFG_DRDY_INT1     ((uint8_t) 0x01)  /*  Interrupt is routed to INT1 pin                    */
/*------------------------------*/



/*--------------------------------
** Register: OFF_X
** Enum: FXOS8700_OFF_X
** --
** Offset : 0x2F - X-axis accelerometer offset adjust.
** ------------------------------*/
typedef uint8_t FXOS8700_OFF_X_t;


/*--------------------------------
** Register: OFF_Y
** Enum: FXOS8700_OFF_Y
** --
** Offset : 0x30 - Y-axis accelerometer offset adjust.
** ------------------------------*/
typedef uint8_t FXOS8700_OFF_Y_t;


/*--------------------------------
** Register: OFF_Z
** Enum: FXOS8700_OFF_Z
** --
** Offset : 0x31 - Z-axis accelerometer offset adjust.
** ------------------------------*/
typedef uint8_t FXOS8700_OFF_Z_t;



/*--------------------------------
** Register: M_DR_STATUS
** Enum: FXOS8700_M_DR_STATUS
** --
** Offset : 0x32 - The magnetometer data ready status.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                   xdr : 1;
        uint8_t                   ydr : 1;
        uint8_t                   zdr : 1;
        uint8_t                 zyxdr : 1;
        uint8_t                   xow : 1;
        uint8_t                   yow : 1;
        uint8_t                   zow : 1;
        uint8_t                 zyxow : 1;
    } b;
    uint8_t w;
} FXOS8700_M_DR_STATUS_t;


/*
** M_DR_STATUS - Bit field mask definitions 
*/
#define FXOS8700_M_DR_STATUS_XDR_MASK     ((uint8_t) 0x01)
#define FXOS8700_M_DR_STATUS_XDR_SHIFT    ((uint8_t)    0)

#define FXOS8700_M_DR_STATUS_YDR_MASK     ((uint8_t) 0x02)
#define FXOS8700_M_DR_STATUS_YDR_SHIFT    ((uint8_t)    1)

#define FXOS8700_M_DR_STATUS_ZDR_MASK     ((uint8_t) 0x04)
#define FXOS8700_M_DR_STATUS_ZDR_SHIFT    ((uint8_t)    2)

#define FXOS8700_M_DR_STATUS_ZYXDR_MASK   ((uint8_t) 0x08)
#define FXOS8700_M_DR_STATUS_ZYXDR_SHIFT  ((uint8_t)    3)

#define FXOS8700_M_DR_STATUS_XOW_MASK     ((uint8_t) 0x10)
#define FXOS8700_M_DR_STATUS_XOW_SHIFT    ((uint8_t)    4)

#define FXOS8700_M_DR_STATUS_YOW_MASK     ((uint8_t) 0x20)
#define FXOS8700_M_DR_STATUS_YOW_SHIFT    ((uint8_t)    5)

#define FXOS8700_M_DR_STATUS_ZOW_MASK     ((uint8_t) 0x40)
#define FXOS8700_M_DR_STATUS_ZOW_SHIFT    ((uint8_t)    6)

#define FXOS8700_M_DR_STATUS_ZYXOW_MASK   ((uint8_t) 0x80)
#define FXOS8700_M_DR_STATUS_ZYXOW_SHIFT  ((uint8_t)    7)


/*------------------------------*/



/*--------------------------------
** Register: M_OUT_X_MSB
** Enum: FXOS8700_M_OUT_X_MSB
** --
** Offset : 0x33 - MSB of the 16-bit magnetometer data for X-axis.
** ------------------------------*/
typedef uint8_t FXOS8700_M_OUT_X_MSB_t;


/*--------------------------------
** Register: M_OUT_X_LSB
** Enum: FXOS8700_M_OUT_X_LSB
** --
** Offset : 0x34 - LSB of the 16-bit magnetometer data for X-axis.
** ------------------------------*/
typedef uint8_t FXOS8700_M_OUT_X_LSB_t;


/*--------------------------------
** Register: M_OUT_Y_MSB
** Enum: FXOS8700_M_OUT_Y_MSB
** --
** Offset : 0x35 - MSB of the 16-bit magnetometer data for Y-axis.
** ------------------------------*/
typedef uint8_t FXOS8700_M_OUT_Y_MSB_t;


/*--------------------------------
** Register: M_OUT_Y_LSB
** Enum: FXOS8700_M_OUT_Y_LSB
** --
** Offset : 0x36 - LSB of the 16-bit magnetometer data for Y-axis.
** ------------------------------*/
typedef uint8_t FXOS8700_M_OUT_Y_LSB_t;


/*--------------------------------
** Register: M_OUT_Z_MSB
** Enum: FXOS8700_M_OUT_Z_MSB
** --
** Offset : 0x37 - MSB of the 16-bit magnetometer data for Z-axis.
** ------------------------------*/
typedef uint8_t FXOS8700_M_OUT_Z_MSB_t;


/*--------------------------------
** Register: M_OUT_Z_LSB
** Enum: FXOS8700_M_OUT_Z_LSB
** --
** Offset : 0x38 - LSB of the 16-bit magnetometer data for Z-axis.
** ------------------------------*/
typedef uint8_t FXOS8700_M_OUT_Z_LSB_t;



/*--------------------------------
** Register: CMP_X_MSB
** Enum: FXOS8700_CMP_X_MSB
** --
** Offset : 0x39 - Bits [13:8] of integrated X-axis acceleration data.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                 cmp_x : 6;
    } b;
    uint8_t w;
} FXOS8700_CMP_X_MSB_t;


/*
** CMP_X_MSB - Bit field mask definitions 
*/
#define FXOS8700_CMP_X_MSB_CMP_X_MASK   ((uint8_t) 0x3F)
#define FXOS8700_CMP_X_MSB_CMP_X_SHIFT  ((uint8_t)    0)


/*------------------------------*/



/*--------------------------------
** Register: CMP_X_LSB
** Enum: FXOS8700_CMP_X_LSB
** --
** Offset : 0x3A - Bits [7:0] of integrated X-axis acceleration data.
** ------------------------------*/
typedef uint8_t FXOS8700_CMP_X_LSB_t;


/*--------------------------------
** Register: CMP_Y_MSB
** Enum: FXOS8700_CMP_Y_MSB
** --
** Offset : 0x3B - Bits [13:8] of integrated Y-axis acceleration data.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                 cmp_y : 6;
    } b;
    uint8_t w;
} FXOS8700_CMP_Y_MSB_t;


/*
** CMP_Y_MSB - Bit field mask definitions 
*/
#define FXOS8700_CMP_Y_MSB_CMP_Y_MASK   ((uint8_t) 0x3F)
#define FXOS8700_CMP_Y_MSB_CMP_Y_SHIFT  ((uint8_t)    0)


/*------------------------------*/



/*--------------------------------
** Register: CMP_Y_LSB
** Enum: FXOS8700_CMP_Y_LSB
** --
** Offset : 0x3C - Bits [7:0] of integrated Y-axis acceleration data.
** ------------------------------*/
typedef uint8_t FXOS8700_CMP_Y_LSB_t;


/*--------------------------------
** Register: CMP_Z_MSB
** Enum: FXOS8700_CMP_Z_MSB
** --
** Offset : 0x3D - Bits [13:8] of integrated Z-axis acceleration data.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                 cmp_z : 6;
    } b;
    uint8_t w;
} FXOS8700_CMP_Z_MSB_t;


/*
** CMP_Z_MSB - Bit field mask definitions 
*/
#define FXOS8700_CMP_Z_MSB_CMP_Z_MASK   ((uint8_t) 0x3F)
#define FXOS8700_CMP_Z_MSB_CMP_Z_SHIFT  ((uint8_t)    0)


/*------------------------------*/



/*--------------------------------
** Register: CMP_Z_LSB
** Enum: FXOS8700_CMP_Z_LSB
** --
** Offset : 0x3E - Bits [7:0] of integrated Z-axis acceleration data.
** ------------------------------*/
typedef uint8_t FXOS8700_CMP_Z_LSB_t;


/*--------------------------------
** Register: M_OFF_X_MSB
** Enum: FXOS8700_M_OFF_X_MSB
** --
** Offset : 0x3F - MSB of magnetometer X-axis offset.
** ------------------------------*/
typedef uint8_t FXOS8700_M_OFF_X_MSB_t;


/*--------------------------------
** Register: M_OFF_X_LSB
** Enum: FXOS8700_M_OFF_X_LSB
** --
** Offset : 0x40 - LSB of magnetometer X-axis offset.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 1;
        uint8_t               m_off_x : 7;
    } b;
    uint8_t w;
} FXOS8700_M_OFF_X_LSB_t;


/*
** M_OFF_X_LSB - Bit field mask definitions 
*/
#define FXOS8700_M_OFF_X_LSB_M_OFF_X_MASK   ((uint8_t) 0xFE)
#define FXOS8700_M_OFF_X_LSB_M_OFF_X_SHIFT  ((uint8_t)    1)


/*------------------------------*/



/*--------------------------------
** Register: M_OFF_Y_MSB
** Enum: FXOS8700_M_OFF_Y_MSB
** --
** Offset : 0x41 - MSB of magnetometer Y-axis offset.
** ------------------------------*/
typedef uint8_t FXOS8700_M_OFF_Y_MSB_t;


/*--------------------------------
** Register: M_OFF_Y_LSB
** Enum: FXOS8700_M_OFF_Y_LSB
** --
** Offset : 0x42 - LSB of magnetometer Y-axis offset.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 1;
        uint8_t               m_off_y : 7;
    } b;
    uint8_t w;
} FXOS8700_M_OFF_Y_LSB_t;


/*
** M_OFF_Y_LSB - Bit field mask definitions 
*/
#define FXOS8700_M_OFF_Y_LSB_M_OFF_Y_MASK   ((uint8_t) 0xFE)
#define FXOS8700_M_OFF_Y_LSB_M_OFF_Y_SHIFT  ((uint8_t)    1)


/*------------------------------*/



/*--------------------------------
** Register: M_OFF_Z_MSB
** Enum: FXOS8700_M_OFF_Z_MSB
** --
** Offset : 0x43 - MSB of magnetometer Z-axis offset.
** ------------------------------*/
typedef uint8_t FXOS8700_M_OFF_Z_MSB_t;


/*--------------------------------
** Register: M_OFF_Z_LSB
** Enum: FXOS8700_M_OFF_Z_LSB
** --
** Offset : 0x44 - LSB of magnetometer Z-axis offset.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 1;
        uint8_t               m_off_z : 7;
    } b;
    uint8_t w;
} FXOS8700_M_OFF_Z_LSB_t;


/*
** M_OFF_Z_LSB - Bit field mask definitions 
*/
#define FXOS8700_M_OFF_Z_LSB_M_OFF_Z_MASK   ((uint8_t) 0xFE)
#define FXOS8700_M_OFF_Z_LSB_M_OFF_Z_SHIFT  ((uint8_t)    1)


/*------------------------------*/



/*--------------------------------
** Register: MAX_X_MSB
** Enum: FXOS8700_MAX_X_MSB
** --
** Offset : 0x45 - Magnetometer X-axis maximum value MSB.
** ------------------------------*/
typedef uint8_t FXOS8700_MAX_X_MSB_t;


/*--------------------------------
** Register: MAX_X_LSB
** Enum: FXOS8700_MAX_X_LSB
** --
** Offset : 0x46 - Magnetometer X-axis maximum value LSB.
** ------------------------------*/
typedef uint8_t FXOS8700_MAX_X_LSB_t;


/*--------------------------------
** Register: MAX_Y_MSB
** Enum: FXOS8700_MAX_Y_MSB
** --
** Offset : 0x47 - Magnetometer Y-axis maximum value MSB.
** ------------------------------*/
typedef uint8_t FXOS8700_MAX_Y_MSB_t;


/*--------------------------------
** Register: MAX_Y_LSB
** Enum: FXOS8700_MAX_Y_LSB
** --
** Offset : 0x48 - Magnetometer Y-axis maximum value LSB.
** ------------------------------*/
typedef uint8_t FXOS8700_MAX_Y_LSB_t;


/*--------------------------------
** Register: MAX_Z_MSB
** Enum: FXOS8700_MAX_Z_MSB
** --
** Offset : 0x49 - Magnetometer Z-axis maximum value MSB.
** ------------------------------*/
typedef uint8_t FXOS8700_MAX_Z_MSB_t;


/*--------------------------------
** Register: MAX_Z_LSB
** Enum: FXOS8700_MAX_Z_LSB
** --
** Offset : 0x4A - Magnetometer Z-axis maximum value LSB.
** ------------------------------*/
typedef uint8_t FXOS8700_MAX_Z_LSB_t;


/*--------------------------------
** Register: MIN_X_MSB
** Enum: FXOS8700_MIN_X_MSB
** --
** Offset : 0x4B - Magnetometer X-axis minimum value MSB.
** ------------------------------*/
typedef uint8_t FXOS8700_MIN_X_MSB_t;


/*--------------------------------
** Register: MIN_X_LSB
** Enum: FXOS8700_MIN_X_LSB
** --
** Offset : 0x4C - Magnetometer X-axis minimum value LSB.
** ------------------------------*/
typedef uint8_t FXOS8700_MIN_X_LSB_t;


/*--------------------------------
** Register: MIN_Y_MSB
** Enum: FXOS8700_MIN_Y_MSB
** --
** Offset : 0x4D - Magnetometer Y-axis minimum value MSB.
** ------------------------------*/
typedef uint8_t FXOS8700_MIN_Y_MSB_t;


/*--------------------------------
** Register: MIN_Y_LSB
** Enum: FXOS8700_MIN_Y_LSB
** --
** Offset : 0x4E - Magnetometer Y-axis minimum value LSB.
** ------------------------------*/
typedef uint8_t FXOS8700_MIN_Y_LSB_t;


/*--------------------------------
** Register: MIN_Z_MSB
** Enum: FXOS8700_MIN_Z_MSB
** --
** Offset : 0x4F - Magnetometer Z-axis minimum value MSB.
** ------------------------------*/
typedef uint8_t FXOS8700_MIN_Z_MSB_t;


/*--------------------------------
** Register: MIN_Z_LSB
** Enum: FXOS8700_MIN_Z_LSB
** --
** Offset : 0x50 - Magnetometer Z-axis minimum value LSB.
** ------------------------------*/
typedef uint8_t FXOS8700_MIN_Z_LSB_t;



/*--------------------------------
** Register: TEMP
** Enum: FXOS8700_TEMP
** --
** Offset : 0x51 - Device temperature with a valid range of -128 to 127 degrees C.
** ------------------------------*/
typedef union {
    struct {
        uint8_t       die_temperature;
    } b;
    uint8_t w;
} FXOS8700_TEMP_t;


/*
** TEMP - Bit field mask definitions 
*/
#define FXOS8700_TEMP_DIE_TEMPERATURE_MASK   ((uint8_t) 0xFF)
#define FXOS8700_TEMP_DIE_TEMPERATURE_SHIFT  ((uint8_t)    0)


/*------------------------------*/



/*--------------------------------
** Register: M_THS_CFG
** Enum: FXOS8700_M_THS_CFG
** --
** Offset : 0x52 - Magnetic threshold detection function configuration.
** ------------------------------*/
typedef union {
    struct {
        uint8_t         m_ths_int_cfg : 1;
        uint8_t          m_ths_int_en : 1;
        uint8_t         m_ths_wake_en : 1;
        uint8_t            m_ths_xefe : 1;
        uint8_t            m_ths_yefe : 1;
        uint8_t            m_ths_zefe : 1;
        uint8_t             m_ths_oae : 1;
        uint8_t             m_ths_ele : 1;
    } b;
    uint8_t w;
} FXOS8700_M_THS_CFG_t;


/*
** M_THS_CFG - Bit field mask definitions 
*/
#define FXOS8700_M_THS_CFG_M_THS_INT_CFG_MASK   ((uint8_t) 0x01)
#define FXOS8700_M_THS_CFG_M_THS_INT_CFG_SHIFT  ((uint8_t)    0)

#define FXOS8700_M_THS_CFG_M_THS_INT_EN_MASK    ((uint8_t) 0x02)
#define FXOS8700_M_THS_CFG_M_THS_INT_EN_SHIFT   ((uint8_t)    1)

#define FXOS8700_M_THS_CFG_M_THS_WAKE_EN_MASK   ((uint8_t) 0x04)
#define FXOS8700_M_THS_CFG_M_THS_WAKE_EN_SHIFT  ((uint8_t)    2)

#define FXOS8700_M_THS_CFG_M_THS_XEFE_MASK      ((uint8_t) 0x08)
#define FXOS8700_M_THS_CFG_M_THS_XEFE_SHIFT     ((uint8_t)    3)

#define FXOS8700_M_THS_CFG_M_THS_YEFE_MASK      ((uint8_t) 0x10)
#define FXOS8700_M_THS_CFG_M_THS_YEFE_SHIFT     ((uint8_t)    4)

#define FXOS8700_M_THS_CFG_M_THS_ZEFE_MASK      ((uint8_t) 0x20)
#define FXOS8700_M_THS_CFG_M_THS_ZEFE_SHIFT     ((uint8_t)    5)

#define FXOS8700_M_THS_CFG_M_THS_OAE_MASK       ((uint8_t) 0x40)
#define FXOS8700_M_THS_CFG_M_THS_OAE_SHIFT      ((uint8_t)    6)

#define FXOS8700_M_THS_CFG_M_THS_ELE_MASK       ((uint8_t) 0x80)
#define FXOS8700_M_THS_CFG_M_THS_ELE_SHIFT      ((uint8_t)    7)


/*------------------------------*/



/*--------------------------------
** Register: M_THS_SRC
** Enum: FXOS8700_M_THS_SRC
** --
** Offset : 0x53 - Magnetic threshold event source register.
** ------------------------------*/
typedef union {
    struct {
        uint8_t             m_ths_xhp : 1;
        uint8_t             m_ths_xhe : 1;
        uint8_t             m_ths_yhp : 1;
        uint8_t             m_ths_yhe : 1;
        uint8_t             m_ths_zhp : 1;
        uint8_t             m_ths_zhe : 1;
        uint8_t _reserved_            : 1;
        uint8_t              m_ths_ea : 1;
    } b;
    uint8_t w;
} FXOS8700_M_THS_SRC_t;


/*
** M_THS_SRC - Bit field mask definitions 
*/
#define FXOS8700_M_THS_SRC_M_THS_XHP_MASK   ((uint8_t) 0x01)
#define FXOS8700_M_THS_SRC_M_THS_XHP_SHIFT  ((uint8_t)    0)

#define FXOS8700_M_THS_SRC_M_THS_XHE_MASK   ((uint8_t) 0x02)
#define FXOS8700_M_THS_SRC_M_THS_XHE_SHIFT  ((uint8_t)    1)

#define FXOS8700_M_THS_SRC_M_THS_YHP_MASK   ((uint8_t) 0x04)
#define FXOS8700_M_THS_SRC_M_THS_YHP_SHIFT  ((uint8_t)    2)

#define FXOS8700_M_THS_SRC_M_THS_YHE_MASK   ((uint8_t) 0x08)
#define FXOS8700_M_THS_SRC_M_THS_YHE_SHIFT  ((uint8_t)    3)

#define FXOS8700_M_THS_SRC_M_THS_ZHP_MASK   ((uint8_t) 0x10)
#define FXOS8700_M_THS_SRC_M_THS_ZHP_SHIFT  ((uint8_t)    4)

#define FXOS8700_M_THS_SRC_M_THS_ZHE_MASK   ((uint8_t) 0x20)
#define FXOS8700_M_THS_SRC_M_THS_ZHE_SHIFT  ((uint8_t)    5)

#define FXOS8700_M_THS_SRC_M_THS_EA_MASK    ((uint8_t) 0x80)
#define FXOS8700_M_THS_SRC_M_THS_EA_SHIFT   ((uint8_t)    7)


/*------------------------------*/



/*--------------------------------
** Register: M_THS_X_MSB
** Enum: FXOS8700_M_THS_X_MSB
** --
** Offset : 0x54 - X-axis magnetic threshold MSB.
** ------------------------------*/
typedef union {
    struct {
        uint8_t               m_ths_x : 7;
    } b;
    uint8_t w;
} FXOS8700_M_THS_X_MSB_t;


/*
** M_THS_X_MSB - Bit field mask definitions 
*/
#define FXOS8700_M_THS_X_MSB_M_THS_X_MASK   ((uint8_t) 0x7F)
#define FXOS8700_M_THS_X_MSB_M_THS_X_SHIFT  ((uint8_t)    0)


/*------------------------------*/



/*--------------------------------
** Register: M_THS_X_LSB
** Enum: FXOS8700_M_THS_X_LSB
** --
** Offset : 0x55 - X-axis magnetic threshold LSB.
** ------------------------------*/
typedef uint8_t FXOS8700_M_THS_X_LSB_t;


/*--------------------------------
** Register: M_THS_Y_MSB
** Enum: FXOS8700_M_THS_Y_MSB
** --
** Offset : 0x56 - Y-axis magnetic threshold MSB.
** ------------------------------*/
typedef union {
    struct {
        uint8_t               m_ths_y : 7;
    } b;
    uint8_t w;
} FXOS8700_M_THS_Y_MSB_t;


/*
** M_THS_Y_MSB - Bit field mask definitions 
*/
#define FXOS8700_M_THS_Y_MSB_M_THS_Y_MASK   ((uint8_t) 0x7F)
#define FXOS8700_M_THS_Y_MSB_M_THS_Y_SHIFT  ((uint8_t)    0)


/*------------------------------*/



/*--------------------------------
** Register: M_THS_Y_LSB
** Enum: FXOS8700_M_THS_Y_LSB
** --
** Offset : 0x57 - Y-axis magnetic threshold LSB.
** ------------------------------*/
typedef uint8_t FXOS8700_M_THS_Y_LSB_t;


/*--------------------------------
** Register: M_THS_Z_MSB
** Enum: FXOS8700_M_THS_Z_MSB
** --
** Offset : 0x58 - Z-axis magnetic threshold MSB.
** ------------------------------*/
typedef union {
    struct {
        uint8_t               m_ths_z : 7;
    } b;
    uint8_t w;
} FXOS8700_M_THS_Z_MSB_t;


/*
** M_THS_Z_MSB - Bit field mask definitions 
*/
#define FXOS8700_M_THS_Z_MSB_M_THS_Z_MASK   ((uint8_t) 0x7F)
#define FXOS8700_M_THS_Z_MSB_M_THS_Z_SHIFT  ((uint8_t)    0)


/*------------------------------*/



/*--------------------------------
** Register: M_THS_Z_LSB
** Enum: FXOS8700_M_THS_Z_LSB
** --
** Offset : 0x59 - Z-axis magnetic threshold LSB.
** ------------------------------*/
typedef uint8_t FXOS8700_M_THS_Z_LSB_t;


/*--------------------------------
** Register: M_THS_COUNT
** Enum: FXOS8700_M_THS_COUNT
** --
** Offset : 0x5A - Magnetic threshold debounce counter.
** ------------------------------*/
typedef uint8_t FXOS8700_M_THS_COUNT_t;



/*--------------------------------
** Register: M_CTRL_REG1
** Enum: FXOS8700_M_CTRL_REG1
** --
** Offset : 0x5B - Control for magnetometer sensor functions.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                 m_hms : 2;
        uint8_t                  m_os : 3; /*  M-cell oversample ratio                                                    */

        uint8_t                 m_ost : 1; /*  One-shot triggered magnetic measurement mode:                              */

        uint8_t                 m_rst : 1;
        uint8_t                m_acal : 1;
    } b;
    uint8_t w;
} FXOS8700_M_CTRL_REG1_t;


/*
** M_CTRL_REG1 - Bit field mask definitions 
*/
#define FXOS8700_M_CTRL_REG1_M_HMS_MASK    ((uint8_t) 0x03)
#define FXOS8700_M_CTRL_REG1_M_HMS_SHIFT   ((uint8_t)    0)

#define FXOS8700_M_CTRL_REG1_M_OS_MASK     ((uint8_t) 0x1C)
#define FXOS8700_M_CTRL_REG1_M_OS_SHIFT    ((uint8_t)    2)

#define FXOS8700_M_CTRL_REG1_M_OST_MASK    ((uint8_t) 0x20)
#define FXOS8700_M_CTRL_REG1_M_OST_SHIFT   ((uint8_t)    5)

#define FXOS8700_M_CTRL_REG1_M_RST_MASK    ((uint8_t) 0x40)
#define FXOS8700_M_CTRL_REG1_M_RST_SHIFT   ((uint8_t)    6)

#define FXOS8700_M_CTRL_REG1_M_ACAL_MASK   ((uint8_t) 0x80)
#define FXOS8700_M_CTRL_REG1_M_ACAL_SHIFT  ((uint8_t)    7)


/*
** M_CTRL_REG1 - Bit field value definitions  
*/
#define FXOS8700_M_CTRL_REG1_M_ACAL_EN             ((uint8_t) 0x80)  /*  Auto-calibration feature enabled                 */
#define FXOS8700_M_CTRL_REG1_M_ACAL_DISABLE        ((uint8_t) 0x00)  /*  Auto-calibration feature disabled                */
#define FXOS8700_M_CTRL_REG1_M_RST_EN              ((uint8_t) 0x40)  /*  One-shot magnetic sensor reset enabled, hw       */
                                                                     /*  cleared when complete                            */
#define FXOS8700_M_CTRL_REG1_M_RST_DISABLE         ((uint8_t) 0x00)  /*  No magnetic sensor reset active                  */
#define FXOS8700_M_CTRL_REG1_M_OST_EN              ((uint8_t) 0x20)  /*  If device is in Active mode no action is taken.  */
                                                                     /*  If device is in Standby mode, take one set of    */
                                                                     /*  magnetic measurements, clear this bit, and       */
                                                                     /*  return to Standby mode.                          */
#define FXOS8700_M_CTRL_REG1_M_OST_DISABLE         ((uint8_t) 0x00)  /*  No action taken, or one-shot measurement         */
                                                                     /*  complete                                         */
#define FXOS8700_M_CTRL_REG1_M_OS_OSR0             ((uint8_t) 0x00)  /*  1.56=16, 6.25=4, 12.5=2, 50=2, 100=2, 200=2,     */
                                                                     /*  400=2, 800=2                                     */
#define FXOS8700_M_CTRL_REG1_M_OS_OSR1             ((uint8_t) 0x04)  /*  1.56=16, 6.25=4, 12.5=2, 50=2, 100=2, 200=2,     */
                                                                     /*  400=2, 800=2                                     */
#define FXOS8700_M_CTRL_REG1_M_OS_OSR2             ((uint8_t) 0x08)  /*  1.56=32, 6.25=8, 12.5=4, 50=2, 100=2, 200=2,     */
                                                                     /*  400=2, 800=2                                     */
#define FXOS8700_M_CTRL_REG1_M_OS_OSR3             ((uint8_t) 0x0c)  /*  1.56=64, 6.25=16, 12.5=8, 50=2, 100=2, 200=2,    */
                                                                     /*  400=2, 800=2                                     */
#define FXOS8700_M_CTRL_REG1_M_OS_OSR4             ((uint8_t) 0x10)  /*  1.56=128, 6.25=32, 12.5=16, 50=4, 100=2, 200=2,  */
                                                                     /*  400=2, 800=2                                     */
#define FXOS8700_M_CTRL_REG1_M_OS_OSR5             ((uint8_t) 0x14)  /*  1.56=256, 6.25=64, 12.5=32, 50=8, 100=4, 200=2,  */
                                                                     /*  400=2, 800=2                                     */
#define FXOS8700_M_CTRL_REG1_M_OS_OSR6             ((uint8_t) 0x18)  /*  1.56=512, 6.25=128, 12.5=64, 50=16, 100=8,       */
                                                                     /*  200=4, 400=2, 800=2                              */
#define FXOS8700_M_CTRL_REG1_M_OS_OSR7             ((uint8_t) 0x1c)  /*  1.56=1024, 6.25=256, 12.5=128, 50=32, 100=16,    */
                                                                     /*  200=8, 400=4, 800=2                              */
#define FXOS8700_M_CTRL_REG1_M_HMS_ACCEL_ONLY      ((uint8_t) 0x00)  /*  0b00 = Only accelerometer sensor is active       */
#define FXOS8700_M_CTRL_REG1_M_HMS_MAG_ONLY        ((uint8_t) 0x01)  /*  0b01 = Only magnetometer sensor is active        */
#define FXOS8700_M_CTRL_REG1_M_HMS_HYBRID_MODE     ((uint8_t) 0x03)  /*  0b11 = Hybrid mode, both accelerometer and       */
                                                                     /*  magnetometer sensors are active                  */
/*------------------------------*/



/*--------------------------------
** Register: M_CTRL_REG2
** Enum: FXOS8700_M_CTRL_REG2
** --
** Offset : 0x5C - Control for magnetometer sensor functions.
** ------------------------------*/
typedef union {
    struct {
        uint8_t             m_rst_cnt : 2;
        uint8_t          m_maxmin_rst : 1;
        uint8_t      m_maxmin_dis_ths : 1;
        uint8_t          m_maxmin_dis : 1;
        uint8_t             m_autoinc : 1;
    } b;
    uint8_t w;
} FXOS8700_M_CTRL_REG2_t;


/*
** M_CTRL_REG2 - Bit field mask definitions 
*/
#define FXOS8700_M_CTRL_REG2_M_RST_CNT_MASK          ((uint8_t) 0x03)
#define FXOS8700_M_CTRL_REG2_M_RST_CNT_SHIFT         ((uint8_t)    0)

#define FXOS8700_M_CTRL_REG2_M_MAXMIN_RST_MASK       ((uint8_t) 0x04)
#define FXOS8700_M_CTRL_REG2_M_MAXMIN_RST_SHIFT      ((uint8_t)    2)

#define FXOS8700_M_CTRL_REG2_M_MAXMIN_DIS_THS_MASK   ((uint8_t) 0x08)
#define FXOS8700_M_CTRL_REG2_M_MAXMIN_DIS_THS_SHIFT  ((uint8_t)    3)

#define FXOS8700_M_CTRL_REG2_M_MAXMIN_DIS_MASK       ((uint8_t) 0x10)
#define FXOS8700_M_CTRL_REG2_M_MAXMIN_DIS_SHIFT      ((uint8_t)    4)

#define FXOS8700_M_CTRL_REG2_M_AUTOINC_MASK          ((uint8_t) 0x20)
#define FXOS8700_M_CTRL_REG2_M_AUTOINC_SHIFT         ((uint8_t)    5)


/*
** M_CTRL_REG2 - Bit field value definitions  
*/
#define FXOS8700_M_CTRL_REG2_M_AUTOINC_HYBRID_MODE ((uint8_t) 0x20)  /*  With hyb_autoinc_mode = 1 and fast-read mode is  */
                                                                     /*  disabled (CTRL_REG1 [f_read] = 0), the register  */
                                                                     /*  address will automatically advance to register   */
                                                                     /*  x33 (M_OUT_X_MSB) after reading register x06     */
                                                                     /*  (OUT_Z_LSB) in burst-read mode.                  */
                                                                     /*  For hyb_autoinc_mode = 1 and fast read mode      */
                                                                     /*  enabled (CTRL_REG1[f_read = 1) the register      */
                                                                     /*  address will automatically advance to register   */
                                                                     /*  x33 (M_OUT_X_MSB) after reading register x05     */
                                                                     /*  (OUT_Z_MSB) during a burstread mode. Please      */
                                                                     /*  refer to the register map auto-increment address */
                                                                     /*  column for further information.                  */
#define FXOS8700_M_CTRL_REG2_M_AUTOINC_ACCEL_ONLY_MODE ((uint8_t) 0x00)  /*  hyb_autoinc_mode = 0                         */
#define FXOS8700_M_CTRL_REG2_M_MAXMIN_DIS_DIS      ((uint8_t) 0x00)  /*  Magnetic min/max detection function is enabled   */
#define FXOS8700_M_CTRL_REG2_M_MAXMIN_DIS_EN       ((uint8_t) 0x10)  /*  Magnetic min/max detection function is disabled  */
#define FXOS8700_M_CTRL_REG2_M_MAXMIN_DIS_THS_DIS  ((uint8_t) 0x00)  /*  No impact to magnetic min/max detection function */
                                                                     /*  on a magnetic threshold event                    */
#define FXOS8700_M_CTRL_REG2_M_MAXMIN_DIS_THS_EN   ((uint8_t) 0x08)  /*  Magnetic min/max detection function is disabled  */
                                                                     /*  when magnetic threshold event is triggered       */
#define FXOS8700_M_CTRL_REG2_M_MAXMIN_RST_NO_SEQUENCE ((uint8_t) 0x00)  /*  No reset sequence is active                   */
#define FXOS8700_M_CTRL_REG2_M_MAXMIN_RST_SET      ((uint8_t) 0x04)  /*  Setting this bit resets the MIN_X/Y/Z and        */
                                                                     /*  MAX_X/Y/Z registers to 0x7FFF and 0x8000         */
#define FXOS8700_M_CTRL_REG2_M_RST_CNT_EVERY1      ((uint8_t) 0x00)  /*  Automatic magnetic reset at the beginning of     */
                                                                     /*  each ODR cycle (default).                        */
#define FXOS8700_M_CTRL_REG2_M_RST_CNT_EVERY16     ((uint8_t) 0x01)  /*  Automatic magnetic reset every 16 ODR cycles     */
#define FXOS8700_M_CTRL_REG2_M_RST_CNT_EVERY512    ((uint8_t) 0x02)  /*  Automatic magnetic reset every 512 ODR cycles    */
#define FXOS8700_M_CTRL_REG2_M_RST_CNT_DISABLE     ((uint8_t) 0x03)  /*  Automatic magnetic reset is disabled. Magnetic   */
                                                                     /*  reset only occurs automatically on a transition  */
                                                                     /*  from Standby to Active mode, or can be triggered */
                                                                     /*  manually by setting M_CTRL_REG1[m_rst] = 1       */
/*------------------------------*/




/*--------------------------------
** Register: M_CTRL_REG3
** Enum: FXOS8700_M_CTRL_REG3
** --
** Offset : 0x5D - Control for magnetometer sensor functions.
** ------------------------------*/
typedef union {
    struct {
        uint8_t               m_st_xy : 2;
        uint8_t                m_st_z : 1;
        uint8_t      m_ths_xyz_update : 1;
        uint8_t             m_aslp_os : 3;
        uint8_t                 m_raw : 1;
    } b;
    uint8_t w;
} FXOS8700_M_CTRL_REG3_t;


/*
** M_CTRL_REG3 - Bit field mask definitions 
*/
#define FXOS8700_M_CTRL_REG3_M_ST_XY_MASK            ((uint8_t) 0x03)
#define FXOS8700_M_CTRL_REG3_M_ST_XY_SHIFT           ((uint8_t)    0)

#define FXOS8700_M_CTRL_REG3_M_ST_Z_MASK             ((uint8_t) 0x04)
#define FXOS8700_M_CTRL_REG3_M_ST_Z_SHIFT            ((uint8_t)    2)

#define FXOS8700_M_CTRL_REG3_M_THS_XYZ_UPDATE_MASK   ((uint8_t) 0x08)
#define FXOS8700_M_CTRL_REG3_M_THS_XYZ_UPDATE_SHIFT  ((uint8_t)    3)

#define FXOS8700_M_CTRL_REG3_M_ASLP_OS_MASK          ((uint8_t) 0x70)
#define FXOS8700_M_CTRL_REG3_M_ASLP_OS_SHIFT         ((uint8_t)    4)

#define FXOS8700_M_CTRL_REG3_M_RAW_MASK              ((uint8_t) 0x80)
#define FXOS8700_M_CTRL_REG3_M_RAW_SHIFT             ((uint8_t)    7)


/*
** M_CTRL_REG3 - Bit field value definitions  
*/
#define FXOS8700_M_CTRL_REG3_M_RAW_EN              ((uint8_t) 0x80)  /*  Values stored in the M_OFF_X/Y/Z registers are   */
                                                                     /*  applied to the magnetic sample data              */
#define FXOS8700_M_CTRL_REG3_M_RAW_DIS             ((uint8_t) 0x00)  /*  Values stored in M_OFF_X/Y/Z are not applied to  */
                                                                     /*  the magnetic sample data                         */
#define FXOS8700_M_CTRL_REG3_M_ASLP_OS_OSR_0       ((uint8_t) 0x00)  /*  OSR 0 look at table 203                          */
#define FXOS8700_M_CTRL_REG3_M_ASLP_OS_OSR_1       ((uint8_t) 0x10)  /*  OSR 1 look at table 203                          */
#define FXOS8700_M_CTRL_REG3_M_ASLP_OS_OSR_2       ((uint8_t) 0x20)  /*  OSR 2 look at table 203                          */
#define FXOS8700_M_CTRL_REG3_M_ASLP_OS_OSR_3       ((uint8_t) 0x30)  /*  OSR 3 look at table 203                          */
#define FXOS8700_M_CTRL_REG3_M_ASLP_OS_OSR_4       ((uint8_t) 0x40)  /*  OSR 4 look at table 203                          */
#define FXOS8700_M_CTRL_REG3_M_ASLP_OS_OSR_5       ((uint8_t) 0x50)  /*  OSR 5 look at table 203                          */
#define FXOS8700_M_CTRL_REG3_M_ASLP_OS_OSR_6       ((uint8_t) 0x60)  /*  OSR 6 look at table 203                          */
#define FXOS8700_M_CTRL_REG3_M_ASLP_OS_OSR_7       ((uint8_t) 0x70)  /*  OSR look at table 203                            */
#define FXOS8700_M_CTRL_REG3_M_THS_XYZ_UPDATE_EN   ((uint8_t) 0x08)  /*  Only the reference value for the axis that       */
                                                                     /*  triggered the detection event is updated         */
#define FXOS8700_M_CTRL_REG3_M_THS_XYZ_UPDATE_DIS  ((uint8_t) 0x00)  /*  X, Y and Z reference values are all updated when */
                                                                     /*  the function triggers on any of the X, Y, or Z   */
                                                                     /*  axes                                             */
/*------------------------------*/



/*--------------------------------
** Register: M_INT_SRC
** Enum: FXOS8700_M_INT_SRC
** --
** Offset : 0x5E - Magnetometer interrupt source.
** ------------------------------*/
typedef union {
    struct {
        uint8_t            src_m_drdy : 1;
        uint8_t            src_m_vecm : 1;
        uint8_t             src_m_ths : 1;
    } b;
    uint8_t w;
} FXOS8700_M_INT_SRC_t;


/*
** M_INT_SRC - Bit field mask definitions 
*/
#define FXOS8700_M_INT_SRC_SRC_M_DRDY_MASK   ((uint8_t) 0x01)
#define FXOS8700_M_INT_SRC_SRC_M_DRDY_SHIFT  ((uint8_t)    0)

#define FXOS8700_M_INT_SRC_SRC_M_VECM_MASK   ((uint8_t) 0x02)
#define FXOS8700_M_INT_SRC_SRC_M_VECM_SHIFT  ((uint8_t)    1)

#define FXOS8700_M_INT_SRC_SRC_M_THS_MASK    ((uint8_t) 0x04)
#define FXOS8700_M_INT_SRC_SRC_M_THS_SHIFT   ((uint8_t)    2)


/*------------------------------*/



/*--------------------------------
** Register: A_VECM_CFG
** Enum: FXOS8700_A_VECM_CFG
** --
** Offset : 0x5F - Acceleration vector magnitude configuration register.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 4;
        uint8_t           a_vecm_updm : 1;
        uint8_t          a_vecm_initm : 1;
        uint8_t            a_vecm_ele : 1;
        uint8_t             a_vecm_en : 1;
    } b;
    uint8_t w;
} FXOS8700_A_VECM_CFG_t;


/*
** A_VECM_CFG - Bit field mask definitions 
*/
#define FXOS8700_A_VECM_CFG_A_VECM_UPDM_MASK    ((uint8_t) 0x10)
#define FXOS8700_A_VECM_CFG_A_VECM_UPDM_SHIFT   ((uint8_t)    4)

#define FXOS8700_A_VECM_CFG_A_VECM_INITM_MASK   ((uint8_t) 0x20)
#define FXOS8700_A_VECM_CFG_A_VECM_INITM_SHIFT  ((uint8_t)    5)

#define FXOS8700_A_VECM_CFG_A_VECM_ELE_MASK     ((uint8_t) 0x40)
#define FXOS8700_A_VECM_CFG_A_VECM_ELE_SHIFT    ((uint8_t)    6)

#define FXOS8700_A_VECM_CFG_A_VECM_EN_MASK      ((uint8_t) 0x80)
#define FXOS8700_A_VECM_CFG_A_VECM_EN_SHIFT     ((uint8_t)    7)


/*------------------------------*/



/*--------------------------------
** Register: A_VECM_THS_MSB
** Enum: FXOS8700_A_VECM_THS_MSB
** --
** Offset : 0x60 - Acceleration vector magnitude threshold MSB.
** ------------------------------*/
typedef union {
    struct {
        uint8_t           a_vbecm_ths : 5;
        uint8_t _reserved_            : 2;
        uint8_t        a_vbecm_dbcntm : 1;
    } b;
    uint8_t w;
} FXOS8700_A_VECM_THS_MSB_t;


/*
** A_VECM_THS_MSB - Bit field mask definitions 
*/
#define FXOS8700_A_VECM_THS_MSB_A_VBECM_THS_MASK      ((uint8_t) 0x1F)
#define FXOS8700_A_VECM_THS_MSB_A_VBECM_THS_SHIFT     ((uint8_t)    0)

#define FXOS8700_A_VECM_THS_MSB_A_VBECM_DBCNTM_MASK   ((uint8_t) 0x80)
#define FXOS8700_A_VECM_THS_MSB_A_VBECM_DBCNTM_SHIFT  ((uint8_t)    7)


/*------------------------------*/



/*--------------------------------
** Register: A_VECM_THS_LSB
** Enum: FXOS8700_A_VECM_THS_LSB
** --
** Offset : 0x61 - Acceleration vector magnitude threshold LSB.
** ------------------------------*/
typedef uint8_t FXOS8700_A_VECM_THS_LSB_t;


/*--------------------------------
** Register: A_VECM_CNT
** Enum: FXOS8700_A_VECM_CNT
** --
** Offset : 0x62 - Acceleration vector magnitude debounce count.
** ------------------------------*/
typedef uint8_t FXOS8700_A_VECM_CNT_t;



/*--------------------------------
** Register: A_VECM_INITX_MSB
** Enum: FXOS8700_A_VECM_INITX_MSB
** --
** Offset : 0x63 - Acceleration vector magnitude X-axis reference value MSB.
** ------------------------------*/
typedef union {
    struct {
        uint8_t          a_vecm_initx : 6;
    } b;
    uint8_t w;
} FXOS8700_A_VECM_INITX_MSB_t;


/*
** A_VECM_INITX_MSB - Bit field mask definitions 
*/
#define FXOS8700_A_VECM_INITX_MSB_A_VECM_INITX_MASK   ((uint8_t) 0x3F)
#define FXOS8700_A_VECM_INITX_MSB_A_VECM_INITX_SHIFT  ((uint8_t)    0)


/*------------------------------*/



/*--------------------------------
** Register: A_VECM_INITX_LSB
** Enum: FXOS8700_A_VECM_INITX_LSB
** --
** Offset : 0x64 - Acceleration vector magnitude X-axis reference value LSB.
** ------------------------------*/
typedef uint8_t FXOS8700_A_VECM_INITX_LSB_t;


/*--------------------------------
** Register: A_VECM_INITY_MSB
** Enum: FXOS8700_A_VECM_INITY_MSB
** --
** Offset : 0x65 - Acceleration vector magnitude Y-axis reference value MSB.
** ------------------------------*/
typedef union {
    struct {
        uint8_t          a_vecm_inity : 6;
    } b;
    uint8_t w;
} FXOS8700_A_VECM_INITY_MSB_t;


/*
** A_VECM_INITY_MSB - Bit field mask definitions 
*/
#define FXOS8700_A_VECM_INITY_MSB_A_VECM_INITY_MASK   ((uint8_t) 0x3F)
#define FXOS8700_A_VECM_INITY_MSB_A_VECM_INITY_SHIFT  ((uint8_t)    0)


/*------------------------------*/



/*--------------------------------
** Register: A_VECM_INITY_LSB
** Enum: FXOS8700_A_VECM_INITY_LSB
** --
** Offset : 0x66 - Acceleration vector magnitude Y-axis reference value LSB.
** ------------------------------*/
typedef uint8_t FXOS8700_A_VECM_INITY_LSB_t;


/*--------------------------------
** Register: A_VECM_INITZ_MSB
** Enum: FXOS8700_A_VECM_INITZ_MSB
** --
** Offset : 0x67 - Acceleration vector magnitude Z-axis reference value MSB.
** ------------------------------*/
typedef union {
    struct {
        uint8_t          a_vecm_initz : 6;
    } b;
    uint8_t w;
} FXOS8700_A_VECM_INITZ_MSB_t;


/*
** A_VECM_INITZ_MSB - Bit field mask definitions 
*/
#define FXOS8700_A_VECM_INITZ_MSB_A_VECM_INITZ_MASK   ((uint8_t) 0x3F)
#define FXOS8700_A_VECM_INITZ_MSB_A_VECM_INITZ_SHIFT  ((uint8_t)    0)


/*------------------------------*/



/*--------------------------------
** Register: A_VECM_INITZ_LSB
** Enum: FXOS8700_A_VECM_INITZ_LSB
** --
** Offset : 0x68 - Acceleration vector magnitude Z-axis reference value LSB.
** ------------------------------*/
typedef uint8_t FXOS8700_A_VECM_INITZ_LSB_t;


/*--------------------------------
** Register: M_VECM_CFG
** Enum: FXOS8700_M_VECM_CFG
** --
** Offset : 0x69 - Magnetic vector magnitude configuration register.
** ------------------------------*/
typedef union {
    struct {
        uint8_t       m_vecm_init_cfg : 1;
        uint8_t         m_vecm_int_en : 1;
        uint8_t        m_vecm_wake_en : 1;
        uint8_t             a_vecm_en : 1;
        uint8_t           m_vecm_updm : 1;
        uint8_t          m_vecm_initm : 1;
        uint8_t            m_vecm_ele : 1;
        uint8_t              reserved : 1;
    } b;
    uint8_t w;
} FXOS8700_M_VECM_CFG_t;


/*
** M_VECM_CFG - Bit field mask definitions 
*/
#define FXOS8700_M_VECM_CFG_M_VECM_INIT_CFG_MASK   ((uint8_t) 0x01)
#define FXOS8700_M_VECM_CFG_M_VECM_INIT_CFG_SHIFT  ((uint8_t)    0)

#define FXOS8700_M_VECM_CFG_M_VECM_INT_EN_MASK     ((uint8_t) 0x02)
#define FXOS8700_M_VECM_CFG_M_VECM_INT_EN_SHIFT    ((uint8_t)    1)

#define FXOS8700_M_VECM_CFG_M_VECM_WAKE_EN_MASK    ((uint8_t) 0x04)
#define FXOS8700_M_VECM_CFG_M_VECM_WAKE_EN_SHIFT   ((uint8_t)    2)

#define FXOS8700_M_VECM_CFG_A_VECM_EN_MASK         ((uint8_t) 0x08)
#define FXOS8700_M_VECM_CFG_A_VECM_EN_SHIFT        ((uint8_t)    3)

#define FXOS8700_M_VECM_CFG_M_VECM_UPDM_MASK       ((uint8_t) 0x10)
#define FXOS8700_M_VECM_CFG_M_VECM_UPDM_SHIFT      ((uint8_t)    4)

#define FXOS8700_M_VECM_CFG_M_VECM_INITM_MASK      ((uint8_t) 0x20)
#define FXOS8700_M_VECM_CFG_M_VECM_INITM_SHIFT     ((uint8_t)    5)

#define FXOS8700_M_VECM_CFG_M_VECM_ELE_MASK        ((uint8_t) 0x40)
#define FXOS8700_M_VECM_CFG_M_VECM_ELE_SHIFT       ((uint8_t)    6)

#define FXOS8700_M_VECM_CFG_RESERVED_MASK          ((uint8_t) 0x80)
#define FXOS8700_M_VECM_CFG_RESERVED_SHIFT         ((uint8_t)    7)


/*
** M_VECM_CFG - Bit field value definitions  
*/
#define FXOS8700_M_VECM_CFG_M_VECM_ELE_DIS        ((uint8_t) 0x00)  /*  Event latch disabled                              */
#define FXOS8700_M_VECM_CFG_M_VECM_ELE_EN         ((uint8_t) 0x40)  /*  Event latch enabled                               */
#define FXOS8700_M_VECM_CFG_M_VECM_INITM_OUT      ((uint8_t) 0x00)  /*  The ASIC uses the current magnetic output data as */
                                                                    /*  the initial reference values at the time the      */
                                                                    /*  m_vecm_en bit is set                              */
#define FXOS8700_M_VECM_CFG_M_VECM_INITM_STORED   ((uint8_t) 0x20)  /*  The ASIC uses the data stored in the              */
                                                                    /*  M_VECM_X/Y/Z_INIT registers as the initial        */
                                                                    /*  reference values at the time the m_vecm_en bit is */
                                                                    /*  set                                               */
#define FXOS8700_M_VECM_CFG_M_VECM_UPDM_DIS       ((uint8_t) 0x00)  /*  The function updates the reference values with    */
                                                                    /*  the current X, Y, and Z magnetic data when the    */
                                                                    /*  event is triggered                                */
#define FXOS8700_M_VECM_CFG_M_VECM_UPDM_EN        ((uint8_t) 0x10)  /*  The function does not update the reference values */
                                                                    /*  when the event is triggered                       */
#define FXOS8700_M_VECM_CFG_A_VECM_EN_EN          ((uint8_t) 0x00)  /*  Function is disabled                              */
#define FXOS8700_M_VECM_CFG_A_VECM_EN_DIS         ((uint8_t) 0x08)  /*  Function is enabled                               */
#define FXOS8700_M_VECM_CFG_M_VECM_WAKE_EN_EN     ((uint8_t) 0x00)  /*  The system excludes the src_m_vecm event flag     */
                                                                    /*  when evaluating the auto-sleep function           */
#define FXOS8700_M_VECM_CFG_M_VECM_WAKE_EN_DIS    ((uint8_t) 0x04)  /*  The system includes the src_m_vecm event flag     */
                                                                    /*  when evaluating the auto-sleep function           */
#define FXOS8700_M_VECM_CFG_M_VECM_INT_EN_EN      ((uint8_t) 0x00)  /*  Magnetic vector-magnitude interrupt is disabled   */
#define FXOS8700_M_VECM_CFG_M_VECM_INT_EN_DIS     ((uint8_t) 0x02)  /*  Magnetic vector-magnitude interrupt is enabled    */
#define FXOS8700_M_VECM_CFG_M_VECM_INIT_CFG_INT2  ((uint8_t) 0x00)  /*  Magnetic vector-magnitude interrupt is output on  */
                                                                    /*  INT2 pin                                          */
#define FXOS8700_M_VECM_CFG_M_VECM_INIT_CFG_INT1  ((uint8_t) 0x01)  /*  Magnetic vector-magnitude interrupt is output on  */
                                                                    /*  INT1 pin.                                         */
#define FXOS8700_M_VECM_CFG_M_VECM_INIT_CFG_DIS   ((uint8_t) 0x01)  /*  Function is enabled                               */
/*------------------------------*/



/*--------------------------------
** Register: M_VECM_THS_MSB
** Enum: FXOS8700_M_VECM_THS_MSB
** --
** Offset : 0x6A - Magnetic vector magnitude threshold MSB.
** ------------------------------*/
typedef union {
    struct {
        uint8_t            m_vecm_ths : 7;
    } b;
    uint8_t w;
} FXOS8700_M_VECM_THS_MSB_t;


/*
** M_VECM_THS_MSB - Bit field mask definitions 
*/
#define FXOS8700_M_VECM_THS_MSB_M_VECM_THS_MASK   ((uint8_t) 0x7F)
#define FXOS8700_M_VECM_THS_MSB_M_VECM_THS_SHIFT  ((uint8_t)    0)


/*------------------------------*/



/*--------------------------------
** Register: M_VECM_THS_LSB
** Enum: FXOS8700_M_VECM_THS_LSB
** --
** Offset : 0x6B - Magnetic vector magnitude threshold LSB.
** ------------------------------*/
typedef uint8_t FXOS8700_M_VECM_THS_LSB_t;


/*--------------------------------
** Register: M_VECM_CNT
** Enum: FXOS8700_M_VECM_CNT
** --
** Offset : 0x6C - Magnetic vector magnitude debounce count.
** ------------------------------*/
typedef uint8_t FXOS8700_M_VECM_CNT_t;


/*--------------------------------
** Register: M_VECM_INITX_MSB
** Enum: FXOS8700_M_VECM_INITX_MSB
** --
** Offset : 0x6D - Magnetic vector magnitude X-axis reference value MSB.
** ------------------------------*/
typedef uint8_t FXOS8700_M_VECM_INITX_MSB_t;


/*--------------------------------
** Register: M_VECM_INITX_LSB
** Enum: FXOS8700_M_VECM_INITX_LSB
** --
** Offset : 0x6E - Magnetic vector magnitude X-axis reference value LSB.
** ------------------------------*/
typedef uint8_t FXOS8700_M_VECM_INITX_LSB_t;


/*--------------------------------
** Register: M_VECM_INITY_MSB
** Enum: FXOS8700_M_VECM_INITY_MSB
** --
** Offset : 0x6F - Magnetic vector magnitude Y-axis reference value MSB.
** ------------------------------*/
typedef uint8_t FXOS8700_M_VECM_INITY_MSB_t;


/*--------------------------------
** Register: M_VECM_INITY_LSB
** Enum: FXOS8700_M_VECM_INITY_LSB
** --
** Offset : 0x70 - Magnetic vector magnitude Y-axis reference value LSB.
** ------------------------------*/
typedef uint8_t FXOS8700_M_VECM_INITY_LSB_t;


/*--------------------------------
** Register: M_VECM_INITZ_MSB
** Enum: FXOS8700_M_VECM_INITZ_MSB
** --
** Offset : 0x71 - Magnetic vector magnitude Z-axis reference value MSB.
** ------------------------------*/
typedef uint8_t FXOS8700_M_VECM_INITZ_MSB_t;


/*--------------------------------
** Register: M_VECM_INITZ_LSB
** Enum: FXOS8700_M_VECM_INITZ_LSB
** --
** Offset : 0x72 - Magnetic vector magnitude Z-axis reference value LSB.
** ------------------------------*/
typedef uint8_t FXOS8700_M_VECM_INITZ_LSB_t;


/*--------------------------------
** Register: A_FFMT_THS_X_MSB
** Enum: FXOS8700_A_FFMT_THS_X_MSB
** --
** Offset : 0x73 - X-axis FFMT threshold MSB.
** ------------------------------*/
typedef uint8_t FXOS8700_A_FFMT_THS_X_MSB_t;



/*--------------------------------
** Register: A_FFMT_THS_X_LSB
** Enum: FXOS8700_A_FFMT_THS_X_LSB
** --
** Offset : 0x74 - X-axis FFMT threshold LSB.
** ------------------------------*/
typedef union {
    struct {
        uint8_t          a_ffmt_ths_x : 7;
    } b;
    uint8_t w;
} FXOS8700_A_FFMT_THS_X_LSB_t;


/*
** A_FFMT_THS_X_LSB - Bit field mask definitions 
*/
#define FXOS8700_A_FFMT_THS_X_LSB_A_FFMT_THS_X_MASK   ((uint8_t) 0x7F)
#define FXOS8700_A_FFMT_THS_X_LSB_A_FFMT_THS_X_SHIFT  ((uint8_t)    0)


/*------------------------------*/



/*--------------------------------
** Register: A_FFMT_THS_Y_MSB
** Enum: FXOS8700_A_FFMT_THS_Y_MSB
** --
** Offset : 0x75 - Y-axis FFMT threshold MSB.
** ------------------------------*/
typedef uint8_t FXOS8700_A_FFMT_THS_Y_MSB_t;


/*--------------------------------
** Register: A_FFMT_THS_Y_LSB
** Enum: FXOS8700_A_FFMT_THS_Y_LSB
** --
** Offset : 0x76 - Y-axis FFMT threshold LSB.
** ------------------------------*/
typedef union {
    struct {
        uint8_t          a_ffmt_ths_y : 7;
    } b;
    uint8_t w;
} FXOS8700_A_FFMT_THS_Y_LSB_t;


/*
** A_FFMT_THS_Y_LSB - Bit field mask definitions 
*/
#define FXOS8700_A_FFMT_THS_Y_LSB_A_FFMT_THS_Y_MASK   ((uint8_t) 0x7F)
#define FXOS8700_A_FFMT_THS_Y_LSB_A_FFMT_THS_Y_SHIFT  ((uint8_t)    0)


/*------------------------------*/



/*--------------------------------
** Register: A_FFMT_THS_Z_MSB
** Enum: FXOS8700_A_FFMT_THS_Z_MSB
** --
** Offset : 0x77 - Z-axis FFMT threshold MSB.
** ------------------------------*/
typedef uint8_t FXOS8700_A_FFMT_THS_Z_MSB_t;


/*--------------------------------
** Register: A_FFMT_THS_Z_LSB
** Enum: FXOS8700_A_FFMT_THS_Z_LSB
** --
** Offset : 0x78 - Z-axis FFMT threshold LSB.
** ------------------------------*/
typedef union {
    struct {
        uint8_t          a_ffmt_ths_z : 7;
    } b;
    uint8_t w;
} FXOS8700_A_FFMT_THS_Z_LSB_t;


/*
** A_FFMT_THS_Z_LSB - Bit field mask definitions 
*/
#define FXOS8700_A_FFMT_THS_Z_LSB_A_FFMT_THS_Z_MASK   ((uint8_t) 0x7F)
#define FXOS8700_A_FFMT_THS_Z_LSB_A_FFMT_THS_Z_SHIFT  ((uint8_t)    0)


/*------------------------------*/


#endif /* FXOS8700_H_ */

// STATUS :  0x00 
