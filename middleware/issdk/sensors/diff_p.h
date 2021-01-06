/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**
 * @file diff_p.h
 * @brief The diff_p.h contains the DIFF_P Pressure sensor register definitions, access macros, and
 * its bit mask.
 */
#ifndef DIFF_P_H_
#define DIFF_P_H_

/**
 **
 **  DIFF_P Sensor Internal Registers
 */
enum {
	DIFF_P_INT_STATUS_0           = 0x00,
	DIFF_P_INT_STATUS_1           = 0x01,
	DIFF_P_OUT_P_LSB              = 0x02,
	DIFF_P_OUT_P_MSB              = 0x03,
	DIFF_P_OUT_T                  = 0x04,
	DIFF_P_P_MIN_LSB              = 0x05,
	DIFF_P_P_MIN_MSB              = 0x06,
	DIFF_P_T_MIN                  = 0x07,
	DIFF_P_P_MAX_LSB              = 0x08,
	DIFF_P_P_MAX_MSB              = 0x09,
	DIFF_P_T_MAX                  = 0x0A,
	DIFF_P_INT_MASK0              = 0x0B,
	DIFF_P_INT_MASK1              = 0x0C,
    /* Reserved:                    0x0D - 0x11 */
	DIFF_P_STATUS                 = 0x12,
	DIFF_P_WHO_AM_I               = 0x13,
	DIFF_P_OFF_P_LSB              = 0x14,
	DIFF_P_OFF_P_MSB              = 0x15,
	DIFF_P_OFF_CAL_P_LSB          = 0x16,
	DIFF_P_OFF_CAL_P_MSB          = 0x17,
	DIFF_P_OFF_T                  = 0x18,
	DIFF_P_P_TGT0_LSB             = 0x19,
	DIFF_P_P_TGT0_MSB             = 0x1A,
	DIFF_P_P_TGT1_LSB             = 0x1B,
	DIFF_P_P_TGT1_MSB             = 0x1C,
	DIFF_P_P_TGT2_LSB             = 0x1D,
	DIFF_P_P_TGT2_MSB             = 0x1E,
	DIFF_P_T_TGT                  = 0x1F,
	DIFF_P_CTRL_REG1              = 0x20,
	DIFF_P_CTRL_REG2              = 0x21,
	DIFF_P_CTRL_REG3              = 0x22,
	DIFF_P_INT_ROUTE0             = 0x23,
	DIFF_P_INT_ROUTE1             = 0x24,
    /* Reserved:                    0x25 - 0x5F */
	DIFF_P_I2C_ADDRESS            = 0x61,
	DIFF_P_WHO_AM_I_              = 0x62,
	DIFF_P_PROD_REV               = 0x63,
	DIFF_P_OFF_MOP_LSB            = 0x64,
	DIFF_P_OFF_MOP_MSB            = 0x65,
	DIFF_P_SERIALNUMBER_BYTE7     = 0x66,
	DIFF_P_SERIALNUMBER_BYTE6     = 0x67,
	DIFF_P_SERIALNUMBER_BYTE5     = 0x68,
	DIFF_P_SERIALNUMBER_BYTE4     = 0x69,
	DIFF_P_SERIALNUMBER_BYTE3     = 0x6A,
	DIFF_P_SERIALNUMBER_BYTE2     = 0x6B,
	DIFF_P_SERIALNUMBER_BYTE1     = 0x6C,
	DIFF_P_SERIALNUMBER_BYTE0     = 0x6D,
    /* Reserved:                    0x6E - 0x7F */
};

#define DIFF_P_NPS3000VV_WHOAMI_VALUE    (0xD0)  /* DIFF_P Who_Am_I Value of Part Number NPS3000VV. */
#define DIFF_P_NPS3001DV_WHOAMI_VALUE    (0xD1)  /* DIFF_P Who_Am_I Value of Part Number NPS3001DV. */
#define DIFF_P_NPS3002VV_WHOAMI_VALUE    (0xD2)  /* DIFF_P Who_Am_I Value of Part Number NPS3000VV. */
#define DIFF_P_NPS3005DV_WHOAMI_VALUE    (0xD3)  /* DIFF_P Who_Am_I Value of Part Number NPS3000VV. */


/*--------------------------------
** Register: INT_STATUS_0
** Enum: DIFF_P_INT_STATUS_0
** --
** Offset : 0x00 - Sensor Status Information Register 1.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                   pdu : 1; /*  Pressure data underflow. Pressure exceeded lower limit of operating        */
                                           /*  range..                                                                    */

        uint8_t                   pdo : 1; /*  Pressure data overflow. Pressure exceeded upper limit of operating range.  */

        uint8_t _reserved_            : 1;
        uint8_t                 verra : 1; /*  Analog voltage brown-out error status bit. This bit is only set when       */
                                           /*  BRWNOUT_EN bit in CTRL_REG2 is set to 1 enabling brownout detection.       */

        uint8_t                   tdr : 1; /*  Temperature new Data Ready. TDR is set to logic 1 whenever a Temperature   */
                                           /*  data acquisition is completed.                                             */

        uint8_t                   pdr : 1; /*  Pressure new Data Ready. PDR is set to logic 1 whenever a new Pressure     */
                                           /*  data acquisition is completed..                                            */

        uint8_t                   tow : 1; /*  Temperature Data Overwrite. TOW is set to logic 1 whenever a new           */
                                           /*  Temperature acquisition is completed before the TDR flag is cleared.       */

        uint8_t                   pow : 1; /*  Pressure Data Overwrite. POW is set to logic 1 whenever a new Pressure     */
                                           /*  acquisition is completed before the PDR flag has been cleared.             */

    } b;
    uint8_t w;
} DIFF_P_INT_STATUS_0_t;


/*
** INT_STATUS_0 - Bit field mask definitions
*/
#define DIFF_P_INT_STATUS_0_PDU_MASK     ((uint8_t) 0x01)
#define DIFF_P_INT_STATUS_0_PDU_SHIFT    ((uint8_t)    0)

#define DIFF_P_INT_STATUS_0_PDO_MASK     ((uint8_t) 0x02)
#define DIFF_P_INT_STATUS_0_PDO_SHIFT    ((uint8_t)    1)

#define DIFF_P_INT_STATUS_0_VERRA_MASK   ((uint8_t) 0x08)
#define DIFF_P_INT_STATUS_0_VERRA_SHIFT  ((uint8_t)    3)

#define DIFF_P_INT_STATUS_0_TDR_MASK     ((uint8_t) 0x10)
#define DIFF_P_INT_STATUS_0_TDR_SHIFT    ((uint8_t)    4)

#define DIFF_P_INT_STATUS_0_PDR_MASK     ((uint8_t) 0x20)
#define DIFF_P_INT_STATUS_0_PDR_SHIFT    ((uint8_t)    5)

#define DIFF_P_INT_STATUS_0_TOW_MASK     ((uint8_t) 0x40)
#define DIFF_P_INT_STATUS_0_TOW_SHIFT    ((uint8_t)    6)

#define DIFF_P_INT_STATUS_0_POW_MASK     ((uint8_t) 0x80)
#define DIFF_P_INT_STATUS_0_POW_SHIFT    ((uint8_t)    7)


/*
** INT_STATUS_0 - Bit field value definitions
*/
#define DIFF_P_INT_STATUS_0_PDU_UNDERFLOW         ((uint8_t) 0x01)  /*  Underflow occurred.                               */
#define DIFF_P_INT_STATUS_0_PDU_NO_UNDERFLOW      ((uint8_t) 0x00)  /*  No Underflow occurred.                            */
#define DIFF_P_INT_STATUS_0_PDO_OVERFLOW          ((uint8_t) 0x02)  /*  Overflow occurred.                                */
#define DIFF_P_INT_STATUS_0_PDO_NO_OVERFLOW       ((uint8_t) 0x00)  /*  No overflow occurred.                             */
#define DIFF_P_INT_STATUS_0_VERRA_BRWNOUT         ((uint8_t) 0x08)  /*  Analog voltage brownout occurred.                 */
#define DIFF_P_INT_STATUS_0_VERRA_NO_BRWNOUT      ((uint8_t) 0x00)  /*  No brownout occurred.                             */
#define DIFF_P_INT_STATUS_0_TDR_DRDY              ((uint8_t) 0x10)  /*  A new Temperature data is ready.                  */
#define DIFF_P_INT_STATUS_0_PDR_DRDY              ((uint8_t) 0x20)  /*  A new set of Pressure data is ready.              */
#define DIFF_P_INT_STATUS_0_TOW_OWR               ((uint8_t) 0x40)  /*  Previous Temperature data was overwritten by new  */
                                                                    /*  Temperature data before it was read.              */
#define DIFF_P_INT_STATUS_0_POW_OWR               ((uint8_t) 0x80)  /*  Previous Pressure data was overwritten by new     */
                                                                    /*  Pressure data before it was read.                 */
/*------------------------------*/



/*--------------------------------
** Register: INT_STATUS_1
** Enum: DIFF_P_INT_STATUS_1
** --
** Offset : 0x01 - Sensor Status Information Register 2.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 1;
        uint8_t                p_wchg : 1; /*  Window threshold interrupt.                                                */

        uint8_t                p_tgt2 : 1; /*  Pressure target value 2.                                                   */

        uint8_t                p_tgt1 : 1; /*  Pressure target value 1.                                                   */

        uint8_t                p_tgt0 : 1; /*  Pressure target value 0.                                                   */

        uint8_t                 t_tgt : 1; /*  Temperature target value.                                                  */

        uint8_t                   tdu : 1; /*  Temperature data underflow. Temperature exceeded lower limit of operating  */
                                           /*  range.                                                                     */

        uint8_t                   tdo : 1; /*  Temperature data overflow. Temperature exceeded upper limit of operating   */
                                           /*  range.                                                                     */

    } b;
    uint8_t w;
} DIFF_P_INT_STATUS_1_t;


/*
** INT_STATUS_1 - Bit field mask definitions
*/
#define DIFF_P_INT_STATUS_1_P_WCHG_MASK   ((uint8_t) 0x02)
#define DIFF_P_INT_STATUS_1_P_WCHG_SHIFT  ((uint8_t)    1)

#define DIFF_P_INT_STATUS_1_P_TGT2_MASK   ((uint8_t) 0x04)
#define DIFF_P_INT_STATUS_1_P_TGT2_SHIFT  ((uint8_t)    2)

#define DIFF_P_INT_STATUS_1_P_TGT1_MASK   ((uint8_t) 0x08)
#define DIFF_P_INT_STATUS_1_P_TGT1_SHIFT  ((uint8_t)    3)

#define DIFF_P_INT_STATUS_1_P_TGT0_MASK   ((uint8_t) 0x10)
#define DIFF_P_INT_STATUS_1_P_TGT0_SHIFT  ((uint8_t)    4)

#define DIFF_P_INT_STATUS_1_T_TGT_MASK    ((uint8_t) 0x20)
#define DIFF_P_INT_STATUS_1_T_TGT_SHIFT   ((uint8_t)    5)

#define DIFF_P_INT_STATUS_1_TDU_MASK      ((uint8_t) 0x40)
#define DIFF_P_INT_STATUS_1_TDU_SHIFT     ((uint8_t)    6)

#define DIFF_P_INT_STATUS_1_TDO_MASK      ((uint8_t) 0x80)
#define DIFF_P_INT_STATUS_1_TDO_SHIFT     ((uint8_t)    7)


/*
** INT_STATUS_1 - Bit field value definitions
*/
#define DIFF_P_INT_STATUS_1_P_WCHG_TH_CROSSED     ((uint8_t) 0x02)  /*  pressure has crossed the window threshold defined */
                                                                    /*  by P_TGT1 and P_TGT2.                             */
#define DIFF_P_INT_STATUS_1_P_TGT2_REACHED        ((uint8_t) 0x04)  /*  Temperature target reached.                       */
#define DIFF_P_INT_STATUS_1_P_TGT1_REACHED        ((uint8_t) 0x08)  /*  Temperature target reached.                       */
#define DIFF_P_INT_STATUS_1_P_TGT0_REACHED        ((uint8_t) 0x10)  /*  Temperature target reached.                       */
#define DIFF_P_INT_STATUS_1_T_TGT_REACHED         ((uint8_t) 0x20)  /*  Temperature target reached.                       */
#define DIFF_P_INT_STATUS_1_TDU_UNDERFLOW         ((uint8_t) 0x40)  /*  Underflow occurred.                               */
#define DIFF_P_INT_STATUS_1_TDU_NO_UNDERFLOW      ((uint8_t) 0x00)  /*  No Underflow occurred.                            */
#define DIFF_P_INT_STATUS_1_TDO_OVERFLOW          ((uint8_t) 0x80)  /*  Overflow occurred.                                */
#define DIFF_P_INT_STATUS_1_TDO_NO_OVERFLOW       ((uint8_t) 0x00)  /*  No overflow occurred.                             */
/*------------------------------*/



/*--------------------------------
** Register: OUT_P_LSB
** Enum: DIFF_P_OUT_P_LSB
** --
** Offset : 0x02 - 8 LSBs of 16 bit Pressure Data LSB.
** ------------------------------*/
typedef uint8_t DIFF_P_OUT_P_LSB_t;


/*--------------------------------
** Register: OUT_P_MSB
** Enum: DIFF_P_OUT_P_MSB
** --
** Offset : 0x03 - 8 MSBs of 16 bit Pressure Data MSB.
** ------------------------------*/
typedef uint8_t DIFF_P_OUT_P_MSB_t;


/*--------------------------------
** Register: OUT_T
** Enum: DIFF_P_OUT_T
** --
** Offset : 0x04 - Temperature Data.
** ------------------------------*/
typedef uint8_t DIFF_P_OUT_T_t;



/*--------------------------------
** Register: P_MIN_LSB
** Enum: DIFF_P_P_MIN_LSB
** --
** Offset : 0x05 - 8 LSBs of 16 bit Minimum Pressure Data LSB.
** ------------------------------*/
typedef uint8_t DIFF_P_P_MIN_LSB_t;


/*--------------------------------
** Register: P_MIN_MSB
** Enum: DIFF_P_P_MIN_MSB
** --
** Offset : 0x06 - 8 MSBs of 16 bit Minimum Pressure Data MSB.
** ------------------------------*/
typedef uint8_t DIFF_P_P_MIN_MSB_t;


/*--------------------------------
** Register: T_MIN
** Enum: DIFF_P_T_MIN
** --
** Offset : 0x07 - Minimum Temperature Data.
** ------------------------------*/
typedef uint8_t DIFF_P_T_MIN_t;



/*--------------------------------
** Register: P_MAX_LSB
** Enum: DIFF_P_P_MAX_LSB
** --
** Offset : 0x08 - 8 LSBs of 16 bit Maximum Pressure Data LSB.
** ------------------------------*/
typedef uint8_t DIFF_P_P_MAX_LSB_t;


/*--------------------------------
** Register: P_MAX_MSB
** Enum: DIFF_P_P_MAX_MSB
** --
** Offset : 0x09 - 8 MSBs of 16 bit Maximum Pressure Data MSB.
** ------------------------------*/
typedef uint8_t DIFF_P_P_MAX_MSB_t;


/*--------------------------------
** Register: T_MAX
** Enum: DIFF_P_T_MAX
** --
** Offset : 0x0A - Maximum Temperature Data.
** ------------------------------*/
typedef uint8_t DIFF_P_T_MAX_t;



/*--------------------------------
** Register: INT_MASK0
** Enum: DIFF_P_INT_MASK0
** --
** Offset : 0x0B - Interrupt Mask Register 1.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                   pdu : 1; /*  Interrupt Mask for PDU interrupt.                                          */

        uint8_t                   pdo : 1; /*  Interrupt Mask for PDO interrupt.                                          */

        uint8_t _reserved_            : 1;
        uint8_t                 verra : 1; /*  Interrupt Mask for VERRA interrupt.                                        */

        uint8_t                   tdr : 1; /*  Interrupt Mask for TDR interrupt.                                          */

        uint8_t                   pdr : 1; /*  Interrupt Mask for PDR interrupt.                                          */

        uint8_t                   tow : 1; /*  Interrupt Mask for TOW interrupt.                                          */

        uint8_t                   pow : 1; /*  Interrupt Mask for POW interrupt.                                          */

    } b;
    uint8_t w;
} DIFF_P_INT_MASK0_t;


/*
** INT_MASK0 - Bit field mask definitions
*/
#define DIFF_P_INT_MASK0_PDU_MASK     ((uint8_t) 0x01)
#define DIFF_P_INT_MASK0_PDU_SHIFT    ((uint8_t)    0)

#define DIFF_P_INT_MASK0_PDO_MASK     ((uint8_t) 0x02)
#define DIFF_P_INT_MASK0_PDO_SHIFT    ((uint8_t)    1)

#define DIFF_P_INT_MASK0_VERRA_MASK   ((uint8_t) 0x08)
#define DIFF_P_INT_MASK0_VERRA_SHIFT  ((uint8_t)    3)

#define DIFF_P_INT_MASK0_TDR_MASK     ((uint8_t) 0x10)
#define DIFF_P_INT_MASK0_TDR_SHIFT    ((uint8_t)    4)

#define DIFF_P_INT_MASK0_PDR_MASK     ((uint8_t) 0x20)
#define DIFF_P_INT_MASK0_PDR_SHIFT    ((uint8_t)    5)

#define DIFF_P_INT_MASK0_TOW_MASK     ((uint8_t) 0x40)
#define DIFF_P_INT_MASK0_TOW_SHIFT    ((uint8_t)    6)

#define DIFF_P_INT_MASK0_POW_MASK     ((uint8_t) 0x80)
#define DIFF_P_INT_MASK0_POW_SHIFT    ((uint8_t)    7)


/*
** INT_MASK0 - Bit field value definitions
*/
#define DIFF_P_INT_MASK0_PDU_INT_EN            ((uint8_t) 0x01)  /*  Interrupt Enabled.                                   */
#define DIFF_P_INT_MASK0_PDO_INT_EN            ((uint8_t) 0x02)  /*  Interrupt Enabled.                                   */
#define DIFF_P_INT_MASK0_VERRA_INT_EN          ((uint8_t) 0x08)  /*  Interrupt Enabled.                                   */
#define DIFF_P_INT_MASK0_TDR_INT_EN            ((uint8_t) 0x10)  /*  Interrupt Enabled.                                   */
#define DIFF_P_INT_MASK0_PDR_INT_EN            ((uint8_t) 0x20)  /*  Interrupt Enabled.                                   */
#define DIFF_P_INT_MASK0_TOW_INT_EN            ((uint8_t) 0x40)  /*  Interrupt Enabled.                                   */
#define DIFF_P_INT_MASK0_POW_INT_EN            ((uint8_t) 0x80)  /*  Interrupt Enabled.                                   */
/*------------------------------*/



/*--------------------------------
** Register: INT_MASK1
** Enum: DIFF_P_INT_MASK1
** --
** Offset : 0x0C - Interrupt Mask Register 2.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 1;
        uint8_t                p_wchg : 1; /*  Interrupt Mask for P_WCHG interrupt.                                       */

        uint8_t                p_tgt2 : 1; /*  Interrupt Mask for P_TGT2 interrupt.                                       */

        uint8_t                p_tgt1 : 1; /*  Interrupt Mask for P_TGT1 interrupt.                                       */

        uint8_t                p_tgt0 : 1; /*  Interrupt Mask for P_TGT0 interrupt.                                       */

        uint8_t                 t_tgt : 1; /*  Interrupt Mask for T_TGT interrupt.                                        */

        uint8_t                   tdu : 1; /*  Interrupt Mask for TDU interrupt.                                          */

        uint8_t                   tdo : 1; /*  Interrupt Mask for TDO interrupt.                                          */

    } b;
    uint8_t w;
} DIFF_P_INT_MASK1_t;


/*
** INT_MASK1 - Bit field mask definitions
*/
#define DIFF_P_INT_MASK1_P_WCHG_MASK   ((uint8_t) 0x02)
#define DIFF_P_INT_MASK1_P_WCHG_SHIFT  ((uint8_t)    1)

#define DIFF_P_INT_MASK1_P_TGT2_MASK   ((uint8_t) 0x04)
#define DIFF_P_INT_MASK1_P_TGT2_SHIFT  ((uint8_t)    2)

#define DIFF_P_INT_MASK1_P_TGT1_MASK   ((uint8_t) 0x08)
#define DIFF_P_INT_MASK1_P_TGT1_SHIFT  ((uint8_t)    3)

#define DIFF_P_INT_MASK1_P_TGT0_MASK   ((uint8_t) 0x10)
#define DIFF_P_INT_MASK1_P_TGT0_SHIFT  ((uint8_t)    4)

#define DIFF_P_INT_MASK1_T_TGT_MASK    ((uint8_t) 0x20)
#define DIFF_P_INT_MASK1_T_TGT_SHIFT   ((uint8_t)    5)

#define DIFF_P_INT_MASK1_TDU_MASK      ((uint8_t) 0x40)
#define DIFF_P_INT_MASK1_TDU_SHIFT     ((uint8_t)    6)

#define DIFF_P_INT_MASK1_TDO_MASK      ((uint8_t) 0x80)
#define DIFF_P_INT_MASK1_TDO_SHIFT     ((uint8_t)    7)


/*
** INT_MASK1 - Bit field value definitions
*/
#define DIFF_P_INT_MASK1_P_WCHG_INT_EN         ((uint8_t) 0x02)  /*  Interrupt Enabled.                                   */
#define DIFF_P_INT_MASK1_P_TGT2_INT_EN         ((uint8_t) 0x04)  /*  Interrupt Enabled.                                   */
#define DIFF_P_INT_MASK1_P_TGT1_INT_EN         ((uint8_t) 0x08)  /*  Interrupt Enabled.                                   */
#define DIFF_P_INT_MASK1_P_TGT0_INT_EN         ((uint8_t) 0x10)  /*  Interrupt Enabled.                                   */
#define DIFF_P_INT_MASK1_T_TGT_INT_EN          ((uint8_t) 0x20)  /*  Interrupt Enabled.                                   */
#define DIFF_P_INT_MASK1_TDU_INT_EN            ((uint8_t) 0x40)  /*  Interrupt Enabled.                                   */
#define DIFF_P_INT_MASK1_TDO_INT_EN            ((uint8_t) 0x80)  /*  Interrupt Enabled.                                   */
/*------------------------------*/



/*--------------------------------
** Register: STATUS
** Enum: DIFF_P_STATUS
** --
** Offset : 0x12 - Calibration and I2C reprogram status.
** ------------------------------*/
typedef union {
    struct {
        uint8_t            rst_status : 1; /*  This bit is set whenever the part comes out of POR.                        */

        uint8_t               osr_err : 1; /*  OSR Error. Bit is set on illegal combination of OSR and ODR..              */

        uint8_t             stat_cplt : 1; /*  Completion Status. STAT_CPLT notifies the user when the calibration        */
                                           /*  routine has successfully completed.                                        */

        uint8_t               stat_ep : 1; /*  Existing Pressure Status. STAT_EP is set to logic 1 when the calibration   */
                                           /*  routine detects an existing pressure condition in the system.              */

        uint8_t        i2c_rpg_status : 1; /*  I2C Address Reprograming status bit. Bit is set to logic 1 at the          */
                                           /*  beginning of the reprograming cycle.                                       */

        uint8_t               i2c_rpg : 1; /*  Completion Status of I2C Address Reprograming. This notifies the user that */
                                           /*  the I2C reprograming has been completed successfully.                      */

        uint8_t           i2c_rpg_cnt : 1; /*  I2C Reprograming count status bit.                                         */

        uint8_t           active_mode : 1; /*  Active mode status bit.                                                    */

    } b;
    uint8_t w;
} DIFF_P_STATUS_t;


/*
** STATUS - Bit field mask definitions
*/
#define DIFF_P_STATUS_RST_STATUS_MASK       ((uint8_t) 0x01)
#define DIFF_P_STATUS_RST_STATUS_SHIFT      ((uint8_t)    0)

#define DIFF_P_STATUS_OSR_ERR_MASK          ((uint8_t) 0x02)
#define DIFF_P_STATUS_OSR_ERR_SHIFT         ((uint8_t)    1)

#define DIFF_P_STATUS_STAT_CPLT_MASK        ((uint8_t) 0x04)
#define DIFF_P_STATUS_STAT_CPLT_SHIFT       ((uint8_t)    2)

#define DIFF_P_STATUS_STAT_EP_MASK          ((uint8_t) 0x08)
#define DIFF_P_STATUS_STAT_EP_SHIFT         ((uint8_t)    3)

#define DIFF_P_STATUS_I2C_RPG_STATUS_MASK   ((uint8_t) 0x10)
#define DIFF_P_STATUS_I2C_RPG_STATUS_SHIFT  ((uint8_t)    4)

#define DIFF_P_STATUS_I2C_RPG_MASK          ((uint8_t) 0x20)
#define DIFF_P_STATUS_I2C_RPG_SHIFT         ((uint8_t)    5)

#define DIFF_P_STATUS_I2C_RPG_CNT_MASK      ((uint8_t) 0x40)
#define DIFF_P_STATUS_I2C_RPG_CNT_SHIFT     ((uint8_t)    6)

#define DIFF_P_STATUS_ACTIVE_MODE_MASK      ((uint8_t) 0x80)
#define DIFF_P_STATUS_ACTIVE_MODE_SHIFT     ((uint8_t)    7)


/*
** STATUS - Bit field value definitions
*/
#define DIFF_P_STATUS_RST_STATUS_RST        ((uint8_t) 0x01)  /*  Part has come out of POR, brownout or soft reset.       */
#define DIFF_P_STATUS_RST_STATUS_NO_RST     ((uint8_t) 0x00)  /*  No POR, brownout or soft reset has occurred.            */
#define DIFF_P_STATUS_OSR_ERR_ERR           ((uint8_t) 0x02)  /*  Illegal ODR/OSR combination.                            */
#define DIFF_P_STATUS_OSR_ERR_NO_ERR        ((uint8_t) 0x00)  /*  No Error.                                               */
#define DIFF_P_STATUS_STAT_CPLT_SUCCESS     ((uint8_t) 0x04)  /*  Calibration routine was successful.                     */
#define DIFF_P_STATUS_STAT_CPLT_NO_SUCCESS  ((uint8_t) 0x00)  /*  Calibration routine was not successful.                 */
#define DIFF_P_STATUS_STAT_EP_DETECTED      ((uint8_t) 0x08)  /*  Existing pressure has been detected.                    */
#define DIFF_P_STATUS_STAT_EP_NOTDETECTED   ((uint8_t) 0x00)  /*  No existing pressure detected.                          */
#define DIFF_P_STATUS_I2C_RPG_STATUS_RPG_INIT ((uint8_t) 0x10)  /*  Reprograming cycle initiated.                         */
#define DIFF_P_STATUS_I2C_RPG_STATUS_RPG_CPLT ((uint8_t) 0x00)  /*  Reprograming cycle completed.                         */
#define DIFF_P_STATUS_I2C_RPG_RPG_SUCCESS   ((uint8_t) 0x20)  /*  I2C Reprograming successful.                            */
#define DIFF_P_STATUS_I2C_RPG_NO_RPG        ((uint8_t) 0x00)  /*  No Reprograming has taken place.                        */
#define DIFF_P_STATUS_I2C_RPG_CNT_CANT_RPG  ((uint8_t) 0x40)  /*  I2C address cannot be reprogrammed.                     */
#define DIFF_P_STATUS_I2C_RPG_CNT_CAN_RPG   ((uint8_t) 0x00)  /*  I2C address can be reprogrammed.                        */
#define DIFF_P_STATUS_ACTIVE_MODE_ACTIVE    ((uint8_t) 0x80)  /*  Sensor is in active mode.                               */
#define DIFF_P_STATUS_ACTIVE_MODE_STANDBY   ((uint8_t) 0x00)  /*  Sensor is in standby mode.                              */
/*------------------------------*/



/*--------------------------------
** Register: WHO_AM_I
** Enum: DIFF_P_WHO_AM_I
** --
** Offset : 0x13 - This register contains the device identifier.
** ------------------------------*/
typedef uint8_t DIFF_P_WHO_AM_I_t;



/*--------------------------------
** Register: OFF_P_LSB
** Enum: DIFF_P_OFF_P_LSB
** --
** Offset : 0x14 - 8 LSBs of 16 bit Pressure Data Offset LSB.
** ------------------------------*/
typedef uint8_t DIFF_P_OFF_P_LSB_t;


/*--------------------------------
** Register: OFF_P_MSB
** Enum: DIFF_P_OFF_P_MSB
** --
** Offset : 0x15 - 8 MSBs of 16 bit Pressure Data Offset MSB.
** ------------------------------*/
typedef uint8_t DIFF_P_OFF_P_MSB_t;


/*--------------------------------
** Register: OFF_CAL_P_LSB
** Enum: DIFF_P_OFF_CAL_P_LSB
** --
** Offset : 0x16 - 8 LSBs of 16 bit Existing Pressure Offset LSB.
** ------------------------------*/
typedef uint8_t DIFF_P_OFF_CAL_P_LSB_t;


/*--------------------------------
** Register: OFF_CAL_P_MSB
** Enum: DIFF_P_OFF_CAL_P_MSB
** --
** Offset : 0x17 - 8 MSBs of 16 bit Existing Pressure Offset MSB.
** ------------------------------*/
typedef uint8_t DIFF_P_OFF_CAL_P_MSB_t;


/*--------------------------------
** Register: OFF_T
** Enum: DIFF_P_OFF_T
** --
** Offset : 0x18 - Temperature Data Offset.
** ------------------------------*/
typedef uint8_t DIFF_P_OFF_T_t;



/*--------------------------------
** Register: P_TGT0_LSB
** Enum: DIFF_P_P_TGT0_LSB
** --
** Offset : 0x19 - 8 LSBs of 16 bit Pressure Data Offset LSB.
** ------------------------------*/
typedef uint8_t DIFF_P_P_TGT0_LSB_t;


/*--------------------------------
** Register: P_TGT0_MSB
** Enum: DIFF_P_P_TGT0_MSB
** --
** Offset : 0x1A - 8 MSBs of 16 bit Pressure Data Offset MSB.
** ------------------------------*/
typedef uint8_t DIFF_P_P_TGT0_MSB_t;


/*--------------------------------
** Register: P_TGT1_LSB
** Enum: DIFF_P_P_TGT1_LSB
** --
** Offset : 0x1B - 8 LSBs of 16 bit Pressure Data Offset LSB.
** ------------------------------*/
typedef uint8_t DIFF_P_P_TGT1_LSB_t;


/*--------------------------------
** Register: P_TGT1_MSB
** Enum: DIFF_P_P_TGT1_MSB
** --
** Offset : 0x1C - 8 MSBs of 16 bit Pressure Data Offset MSB.
** ------------------------------*/
typedef uint8_t DIFF_P_P_TGT1_MSB_t;


/*--------------------------------
** Register: P_TGT2_LSB
** Enum: DIFF_P_P_TGT2_LSB
** --
** Offset : 0x1D - 8 LSBs of 16 bit Pressure Data Offset LSB.
** ------------------------------*/
typedef uint8_t DIFF_P_P_TGT2_LSB_t;


/*--------------------------------
** Register: P_TGT2_MSB
** Enum: DIFF_P_P_TGT2_MSB
** --
** Offset : 0x1E - 8 MSBs of 16 bit Pressure Data Offset MSB.
** ------------------------------*/
typedef uint8_t DIFF_P_P_TGT2_MSB_t;


/*--------------------------------
** Register: T_TGT
** Enum: DIFF_P_T_TGT
** --
** Offset : 0x1F - Temperature Target Value.
** ------------------------------*/
typedef uint8_t DIFF_P_T_TGT_t;



/*--------------------------------
** Register: CTRL_REG1
** Enum: DIFF_P_CTRL_REG1
** --
** Offset : 0x20 - Control Register 1.
** ------------------------------*/
typedef union {
    struct {
/* osr >= 21 will select OSR8192 */
        uint8_t                  sbyb : 1; /*  This bit sets the mode to ACTIVE.                                          */

        uint8_t                   ost : 1; /*  One Shot Mode. The OST bit, when set, will initiate a measurement          */
                                           /*  immediately and take the samples indicated by the OSR[4:0] bits.           */

        uint8_t                   rst : 1; /*  Software Reset. This bit is used to activate the software reset.           */

        uint8_t                   osr : 5; /*  Interrupt Mask for P_TGT1 interrupt.                                       */

    } b;
    uint8_t w;
} DIFF_P_CTRL_REG1_t;


/*
** CTRL_REG1 - Bit field mask definitions
*/
#define DIFF_P_CTRL_REG1_SBYB_MASK   ((uint8_t) 0x01)
#define DIFF_P_CTRL_REG1_SBYB_SHIFT  ((uint8_t)    0)

#define DIFF_P_CTRL_REG1_OST_MASK    ((uint8_t) 0x02)
#define DIFF_P_CTRL_REG1_OST_SHIFT   ((uint8_t)    1)

#define DIFF_P_CTRL_REG1_RST_MASK    ((uint8_t) 0x04)
#define DIFF_P_CTRL_REG1_RST_SHIFT   ((uint8_t)    2)

#define DIFF_P_CTRL_REG1_OSR_MASK    ((uint8_t) 0xF8)
#define DIFF_P_CTRL_REG1_OSR_SHIFT   ((uint8_t)    3)


/*
** CTRL_REG1 - Bit field value definitions
*/
#define DIFF_P_CTRL_REG1_SBYB_ACTIVE           ((uint8_t) 0x01)  /*  Part is ACTIVE.                                      */
#define DIFF_P_CTRL_REG1_SBYB_STANDBY          ((uint8_t) 0x00)  /*  Part is in STANDBY mode.                             */
#define DIFF_P_CTRL_REG1_OST_ONESHOT           ((uint8_t) 0x02)  /*  One Shot Mode.                                       */
#define DIFF_P_CTRL_REG1_OST_NORMAL            ((uint8_t) 0x00)  /*  Normal operating mode.                               */
#define DIFF_P_CTRL_REG1_RST_RESET             ((uint8_t) 0x04)  /*  Device will be reset.                                */
#define DIFF_P_CTRL_REG1_RST_NORMAL            ((uint8_t) 0x00)  /*  Normal operating mode.                               */
#define DIFF_P_CTRL_REG1_OSR_OSR1              ((uint8_t) 0x00)  /*  Oversampling Rate#1.                                 */
#define DIFF_P_CTRL_REG1_OSR_OSR2              ((uint8_t) 0x08)  /*  Oversampling Rate#2.                                 */
#define DIFF_P_CTRL_REG1_OSR_OSR4              ((uint8_t) 0x10)  /*  Oversampling Rate#4.                                 */
#define DIFF_P_CTRL_REG1_OSR_OSR8              ((uint8_t) 0x18)  /*  Oversampling Rate#8.                                 */
#define DIFF_P_CTRL_REG1_OSR_OSR16             ((uint8_t) 0x20)  /*  Oversampling Rate#16.                                */
#define DIFF_P_CTRL_REG1_OSR_OSR32             ((uint8_t) 0x28)  /*  Oversampling Rate#32.                                */
#define DIFF_P_CTRL_REG1_OSR_OSR64             ((uint8_t) 0x30)  /*  Oversampling Rate#64.                                */
#define DIFF_P_CTRL_REG1_OSR_OSR128            ((uint8_t) 0x38)  /*  Oversampling Rate#128.                               */
#define DIFF_P_CTRL_REG1_OSR_OSR256            ((uint8_t) 0x40)  /*  Oversampling Rate#256.                               */
#define DIFF_P_CTRL_REG1_OSR_OSR512            ((uint8_t) 0x48)  /*  Oversampling Rate#512.                               */
#define DIFF_P_CTRL_REG1_OSR_OSR768            ((uint8_t) 0x50)  /*  Oversampling Rate#768.                               */
#define DIFF_P_CTRL_REG1_OSR_OSR1024           ((uint8_t) 0x58)  /*  Oversampling Rate#1024.                              */
#define DIFF_P_CTRL_REG1_OSR_OSR1280           ((uint8_t) 0x60)  /*  Oversampling Rate#1280.                              */
#define DIFF_P_CTRL_REG1_OSR_OSR1536           ((uint8_t) 0x68)  /*  Oversampling Rate#1536.                              */
#define DIFF_P_CTRL_REG1_OSR_OSR2048           ((uint8_t) 0x70)  /*  Oversampling Rate#2048.                              */
#define DIFF_P_CTRL_REG1_OSR_OSR2560           ((uint8_t) 0x78)  /*  Oversampling Rate#2560.                              */
#define DIFF_P_CTRL_REG1_OSR_OSR3072           ((uint8_t) 0x80)  /*  Oversampling Rate#3072.                              */
#define DIFF_P_CTRL_REG1_OSR_OSR4096           ((uint8_t) 0x88)  /*  Oversampling Rate#4096.                              */
#define DIFF_P_CTRL_REG1_OSR_OSR5120           ((uint8_t) 0x90)  /*  Oversampling Rate#5120.                              */
#define DIFF_P_CTRL_REG1_OSR_OSR6144           ((uint8_t) 0x98)  /*  Oversampling Rate#6144.                              */
#define DIFF_P_CTRL_REG1_OSR_OSR7168           ((uint8_t) 0xa0)  /*  Oversampling Rate#7168.                              */
#define DIFF_P_CTRL_REG1_OSR_OSR8192           ((uint8_t) 0xa8)  /*  Oversampling Rate#8192.                              */
/*------------------------------*/



/*--------------------------------
** Register: CTRL_REG2
** Enum: DIFF_P_CTRL_REG2
** --
** Offset : 0x21 - Control Register 2.
** ------------------------------*/
typedef union {
    struct {
/* odr >= 12 will select ODR0P781 */
        uint8_t                   odr : 4; /*  Output Data Rate. Sets the output data rate.                               */

        uint8_t _reserved_            : 1;
        uint8_t                f_read : 1; /*  Fast Read Mode. Selects the auto-increment address methodology.            */

        uint8_t            brwnout_en : 1; /*  Enables or disables internal brown out circuit..                           */

        uint8_t               ctrl_ac : 1; /*  This bit controls when the Calibration Algorithm is to be run..            */

    } b;
    uint8_t w;
} DIFF_P_CTRL_REG2_t;


/*
** CTRL_REG2 - Bit field mask definitions
*/
#define DIFF_P_CTRL_REG2_ODR_MASK          ((uint8_t) 0x0F)
#define DIFF_P_CTRL_REG2_ODR_SHIFT         ((uint8_t)    0)

#define DIFF_P_CTRL_REG2_F_READ_MASK       ((uint8_t) 0x20)
#define DIFF_P_CTRL_REG2_F_READ_SHIFT      ((uint8_t)    5)

#define DIFF_P_CTRL_REG2_BRWNOUT_EN_MASK   ((uint8_t) 0x40)
#define DIFF_P_CTRL_REG2_BRWNOUT_EN_SHIFT  ((uint8_t)    6)

#define DIFF_P_CTRL_REG2_CTRL_AC_MASK      ((uint8_t) 0x80)
#define DIFF_P_CTRL_REG2_CTRL_AC_SHIFT     ((uint8_t)    7)


/*
** CTRL_REG2 - Bit field value definitions
*/
#define DIFF_P_CTRL_REG2_ODR_ODR3200           ((uint8_t) 0x00)  /*  Output Data Rate#3200.                               */
#define DIFF_P_CTRL_REG2_ODR_ODR1600           ((uint8_t) 0x01)  /*  Output Data Rate#1600.                               */
#define DIFF_P_CTRL_REG2_ODR_ODR800            ((uint8_t) 0x02)  /*  Output Data Rate#800.                                */
#define DIFF_P_CTRL_REG2_ODR_ODR400            ((uint8_t) 0x03)  /*  Output Data Rate#400.                                */
#define DIFF_P_CTRL_REG2_ODR_ODR200            ((uint8_t) 0x04)  /*  Output Data Rate#200.                                */
#define DIFF_P_CTRL_REG2_ODR_ODR100            ((uint8_t) 0x05)  /*  Output Data Rate#100.                                */
#define DIFF_P_CTRL_REG2_ODR_ODR50             ((uint8_t) 0x06)  /*  Output Data Rate#50.                                 */
#define DIFF_P_CTRL_REG2_ODR_ODR25             ((uint8_t) 0x07)  /*  Output Data Rate#25.                                 */
#define DIFF_P_CTRL_REG2_ODR_ODR12P5           ((uint8_t) 0x08)  /*  Output Data Rate#12.5.                               */
#define DIFF_P_CTRL_REG2_ODR_ODR6P25           ((uint8_t) 0x09)  /*  Output Data Rate#6.25.                               */
#define DIFF_P_CTRL_REG2_ODR_ODR3P125          ((uint8_t) 0x0a)  /*  Output Data Rate#3.125.                              */
#define DIFF_P_CTRL_REG2_ODR_ODR1P563          ((uint8_t) 0x0b)  /*  Output Data Rate#1.563.                              */
#define DIFF_P_CTRL_REG2_ODR_ODR0P781          ((uint8_t) 0x0c)  /*  Output Data Rate#0.781.                              */
#define DIFF_P_CTRL_REG2_F_READ_NORMAL         ((uint8_t) 0x20)  /*  Loops between all register addresses.                */
#define DIFF_P_CTRL_REG2_F_READ_FASTREAD       ((uint8_t) 0x00)  /*  Loops between register address 0x00 and 0x04.        */
#define DIFF_P_CTRL_REG2_BRWNOUT_EN_ENABLED    ((uint8_t) 0x40)  /*  Internal brown out circuit is enabled.               */
#define DIFF_P_CTRL_REG2_BRWNOUT_EN_DISABLED   ((uint8_t) 0x00)  /*  Internal brown out circuit is disabled.              */
#define DIFF_P_CTRL_REG2_CTRL_AC_CALRUN        ((uint8_t) 0x80)  /*  Run Calibration Algorithm.                           */
#define DIFF_P_CTRL_REG2_CTRL_AC_NOCALRUN      ((uint8_t) 0x00)  /*  Calibration Algorithm not run.                       */
/*------------------------------*/



/*--------------------------------
** Register: CTRL_REG3
** Enum: DIFF_P_CTRL_REG3
** --
** Offset : 0x22 - Control Register 3.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                pp_od2 : 1; /*  This bit configures the interrupt pin to Push-Pull or in Open Drain        */
                                           /*  mode.Push-Pull/Open Drain selection on interrupt pad INT2.                 */

        uint8_t                 ipol2 : 1; /*  The IPOL bit selects the polarity of the interrupt signal on pin INT2.     */

        uint8_t _reserved_            : 2;
        uint8_t                pp_od1 : 1; /*  This bit configures the interrupt pin to Push-Pull or in Open Drain        */
                                           /*  mode.Push-Pull/Open Drain selection on interrupt pad INT1.                 */

        uint8_t                 ipol1 : 1; /*  The IPOL bit selects the polarity of the interrupt signal on pin INT1.     */

    } b;
    uint8_t w;
} DIFF_P_CTRL_REG3_t;


/*
** CTRL_REG3 - Bit field mask definitions
*/
#define DIFF_P_CTRL_REG3_PP_OD2_MASK   ((uint8_t) 0x01)
#define DIFF_P_CTRL_REG3_PP_OD2_SHIFT  ((uint8_t)    0)

#define DIFF_P_CTRL_REG3_IPOL2_MASK    ((uint8_t) 0x02)
#define DIFF_P_CTRL_REG3_IPOL2_SHIFT   ((uint8_t)    1)

#define DIFF_P_CTRL_REG3_PP_OD1_MASK   ((uint8_t) 0x10)
#define DIFF_P_CTRL_REG3_PP_OD1_SHIFT  ((uint8_t)    4)

#define DIFF_P_CTRL_REG3_IPOL1_MASK    ((uint8_t) 0x20)
#define DIFF_P_CTRL_REG3_IPOL1_SHIFT   ((uint8_t)    5)


/*
** CTRL_REG3 - Bit field value definitions
*/
#define DIFF_P_CTRL_REG3_PP_OD2_OPENDRAIN      ((uint8_t) 0x01)  /*  Open drain.                                          */
#define DIFF_P_CTRL_REG3_PP_OD2_PUSHPULL       ((uint8_t) 0x00)  /*  Push-pull.                                           */
#define DIFF_P_CTRL_REG3_IPOL2_ACTIVE_HIGH     ((uint8_t) 0x02)  /*  Active High.                                         */
#define DIFF_P_CTRL_REG3_IPOL2_ACTIVE_LOW      ((uint8_t) 0x00)  /*  Active Low.                                          */
#define DIFF_P_CTRL_REG3_PP_OD1_OPENDRAIN      ((uint8_t) 0x10)  /*  Open drain.                                          */
#define DIFF_P_CTRL_REG3_PP_OD1_PUSHPULL       ((uint8_t) 0x00)  /*  Push-pull.                                           */
#define DIFF_P_CTRL_REG3_IPOL1_ACTIVE_HIGH     ((uint8_t) 0x20)  /*  Active High.                                         */
#define DIFF_P_CTRL_REG3_IPOL1_ACTIVE_LOW      ((uint8_t) 0x00)  /*  Active Low.                                          */
/*------------------------------*/



/*--------------------------------
** Register: INT_ROUTE0
** Enum: DIFF_P_INT_ROUTE0
** --
** Offset : 0x23 - Interrupt Route Register 0.
** ------------------------------*/
typedef union {
    struct {
        uint8_t                   pdu : 1; /*  Pressure data underflow.                                                   */

        uint8_t                   pdo : 1; /*  Pressure data overflow.                                                    */

        uint8_t _reserved_            : 1;
        uint8_t                 verra : 1; /*  Analog voltage brown-out error status bit.                                 */

        uint8_t                   tdr : 1; /*  Temperature new Data Ready.                                                */

        uint8_t                   pdr : 1; /*  Pressure new Data Ready.                                                   */

        uint8_t                   tow : 1; /*  Temperature Data Overwrite.                                                */

        uint8_t                   pow : 1; /*  Pressure Data Overwrite.                                                   */

    } b;
    uint8_t w;
} DIFF_P_INT_ROUTE0_t;


/*
** INT_ROUTE0 - Bit field mask definitions
*/
#define DIFF_P_INT_ROUTE0_PDU_MASK     ((uint8_t) 0x01)
#define DIFF_P_INT_ROUTE0_PDU_SHIFT    ((uint8_t)    0)

#define DIFF_P_INT_ROUTE0_PDO_MASK     ((uint8_t) 0x02)
#define DIFF_P_INT_ROUTE0_PDO_SHIFT    ((uint8_t)    1)

#define DIFF_P_INT_ROUTE0_VERRA_MASK   ((uint8_t) 0x08)
#define DIFF_P_INT_ROUTE0_VERRA_SHIFT  ((uint8_t)    3)

#define DIFF_P_INT_ROUTE0_TDR_MASK     ((uint8_t) 0x10)
#define DIFF_P_INT_ROUTE0_TDR_SHIFT    ((uint8_t)    4)

#define DIFF_P_INT_ROUTE0_PDR_MASK     ((uint8_t) 0x20)
#define DIFF_P_INT_ROUTE0_PDR_SHIFT    ((uint8_t)    5)

#define DIFF_P_INT_ROUTE0_TOW_MASK     ((uint8_t) 0x40)
#define DIFF_P_INT_ROUTE0_TOW_SHIFT    ((uint8_t)    6)

#define DIFF_P_INT_ROUTE0_POW_MASK     ((uint8_t) 0x80)
#define DIFF_P_INT_ROUTE0_POW_SHIFT    ((uint8_t)    7)


/*
** INT_ROUTE0 - Bit field value definitions
*/
#define DIFF_P_INT_ROUTE0_PDU_INT2              ((uint8_t) 0x01)  /*  Interrupt routed to INT2 pin.                       */
#define DIFF_P_INT_ROUTE0_PDU_INT1              ((uint8_t) 0x00)  /*  Interrupt routed to INT1 pin.                       */
#define DIFF_P_INT_ROUTE0_PDO_INT2              ((uint8_t) 0x02)  /*  Interrupt routed to INT2 pin.                       */
#define DIFF_P_INT_ROUTE0_PDO_INT1              ((uint8_t) 0x00)  /*  Interrupt routed to INT1 pin.                       */
#define DIFF_P_INT_ROUTE0_VERRA_INT2            ((uint8_t) 0x08)  /*  Interrupt routed to INT2 pin.                       */
#define DIFF_P_INT_ROUTE0_VERRA_INT1            ((uint8_t) 0x00)  /*  Interrupt routed to INT1 pin.                       */
#define DIFF_P_INT_ROUTE0_TDR_INT2              ((uint8_t) 0x10)  /*  Interrupt routed to INT2 pin.                       */
#define DIFF_P_INT_ROUTE0_TDR_INT1              ((uint8_t) 0x00)  /*  Interrupt routed to INT1 pin.                       */
#define DIFF_P_INT_ROUTE0_PDR_INT2              ((uint8_t) 0x20)  /*  Interrupt routed to INT2 pin.                       */
#define DIFF_P_INT_ROUTE0_PDR_INT1              ((uint8_t) 0x00)  /*  Interrupt routed to INT1 pin.                       */
#define DIFF_P_INT_ROUTE0_TOW_INT2              ((uint8_t) 0x40)  /*  Interrupt routed to INT2 pin.                       */
#define DIFF_P_INT_ROUTE0_TOW_INT1              ((uint8_t) 0x00)  /*  Interrupt routed to INT1 pin.                       */
#define DIFF_P_INT_ROUTE0_POW_INT2              ((uint8_t) 0x80)  /*  Interrupt routed to INT2 pin.                       */
#define DIFF_P_INT_ROUTE0_POW_INT1              ((uint8_t) 0x00)  /*  Interrupt routed to INT1 pin.                       */
/*------------------------------*/



/*--------------------------------
** Register: INT_ROUTE1
** Enum: DIFF_P_INT_ROUTE1
** --
** Offset : 0x24 - Interrupt Route Register 1.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_            : 1;
        uint8_t                p_wchg : 1; /*  Window threshold interrupt.                                                */

        uint8_t                p_tgt2 : 1; /*  Pressure target value 2.                                                   */

        uint8_t                p_tgt1 : 1; /*  Pressure target value 1.                                                   */

        uint8_t                p_tgt0 : 1; /*  Pressure target value 0.                                                   */

        uint8_t                 t_tgt : 1; /*  Temperature target value.                                                  */

        uint8_t                   tdu : 1; /*  Temperature data underflow.                                                */

        uint8_t                   tdo : 1; /*  Temperature data overflow.                                                 */

    } b;
    uint8_t w;
} DIFF_P_INT_ROUTE1_t;


/*
** INT_ROUTE1 - Bit field mask definitions
*/
#define DIFF_P_INT_ROUTE1_P_WCHG_MASK   ((uint8_t) 0x02)
#define DIFF_P_INT_ROUTE1_P_WCHG_SHIFT  ((uint8_t)    1)

#define DIFF_P_INT_ROUTE1_P_TGT2_MASK   ((uint8_t) 0x04)
#define DIFF_P_INT_ROUTE1_P_TGT2_SHIFT  ((uint8_t)    2)

#define DIFF_P_INT_ROUTE1_P_TGT1_MASK   ((uint8_t) 0x08)
#define DIFF_P_INT_ROUTE1_P_TGT1_SHIFT  ((uint8_t)    3)

#define DIFF_P_INT_ROUTE1_P_TGT0_MASK   ((uint8_t) 0x10)
#define DIFF_P_INT_ROUTE1_P_TGT0_SHIFT  ((uint8_t)    4)

#define DIFF_P_INT_ROUTE1_T_TGT_MASK    ((uint8_t) 0x20)
#define DIFF_P_INT_ROUTE1_T_TGT_SHIFT   ((uint8_t)    5)

#define DIFF_P_INT_ROUTE1_TDU_MASK      ((uint8_t) 0x40)
#define DIFF_P_INT_ROUTE1_TDU_SHIFT     ((uint8_t)    6)

#define DIFF_P_INT_ROUTE1_TDO_MASK      ((uint8_t) 0x80)
#define DIFF_P_INT_ROUTE1_TDO_SHIFT     ((uint8_t)    7)


/*
** INT_ROUTE1 - Bit field value definitions
*/
#define DIFF_P_INT_ROUTE1_P_WCHG_INT2           ((uint8_t) 0x02)  /*  Interrupt routed to INT2 pin.                       */
#define DIFF_P_INT_ROUTE1_P_WCHG_INT1           ((uint8_t) 0x00)  /*  Interrupt routed to INT1 pin.                       */
#define DIFF_P_INT_ROUTE1_P_TGT2_INT2           ((uint8_t) 0x04)  /*  Interrupt routed to INT2 pin.                       */
#define DIFF_P_INT_ROUTE1_P_TGT2_INT1           ((uint8_t) 0x00)  /*  Interrupt routed to INT1 pin.                       */
#define DIFF_P_INT_ROUTE1_P_TGT1_INT2           ((uint8_t) 0x08)  /*  Interrupt routed to INT2 pin.                       */
#define DIFF_P_INT_ROUTE1_P_TGT1_INT1           ((uint8_t) 0x00)  /*  Interrupt routed to INT1 pin.                       */
#define DIFF_P_INT_ROUTE1_P_TGT0_INT2           ((uint8_t) 0x10)  /*  Interrupt routed to INT2 pin.                       */
#define DIFF_P_INT_ROUTE1_P_TGT0_INT1           ((uint8_t) 0x00)  /*  Interrupt routed to INT1 pin.                       */
#define DIFF_P_INT_ROUTE1_T_TGT_INT2            ((uint8_t) 0x20)  /*  Interrupt routed to INT2 pin.                       */
#define DIFF_P_INT_ROUTE1_T_TGT_INT1            ((uint8_t) 0x00)  /*  Interrupt routed to INT1 pin.                       */
#define DIFF_P_INT_ROUTE1_TDU_INT2              ((uint8_t) 0x40)  /*  Interrupt routed to INT2 pin.                       */
#define DIFF_P_INT_ROUTE1_TDU_INT1              ((uint8_t) 0x00)  /*  Interrupt routed to INT1 pin.                       */
#define DIFF_P_INT_ROUTE1_TDO_INT2              ((uint8_t) 0x80)  /*  Interrupt routed to INT2 pin.                       */
#define DIFF_P_INT_ROUTE1_TDO_INT1              ((uint8_t) 0x00)  /*  Interrupt routed to INT1 pin.                       */
/*------------------------------*/



/*--------------------------------
** Register: I2C_ADDRESS
** Enum: DIFF_P_I2C_ADDRESS
** --
** Offset : 0x61 - This register configures the I2C address of the device.
** ------------------------------*/
typedef uint8_t DIFF_P_I2C_ADDRESS_t;


/*--------------------------------
** Register: PROD_REV
** Enum: DIFF_P_PROD_REV
** --
** Offset : 0x63 - This register keeps track of ASIC and MEMS die revisions.
** ------------------------------*/
typedef uint8_t DIFF_P_PROD_REV_t;



/*--------------------------------
** Register: OFF_MOP_LSB
** Enum: DIFF_P_OFF_MOP_LSB
** --
** Offset : 0x64 - 8 LSBs of 16 bit Maximum Offset Pressure LSB.
** ------------------------------*/
typedef uint8_t DIFF_P_OFF_MOP_LSB_t;


/*--------------------------------
** Register: OFF_MOP_MSB
** Enum: DIFF_P_OFF_MOP_MSB
** --
** Offset : 0x65 - 8 MSBs of 16 bit Maximum Offset Pressure MSB.
** ------------------------------*/
typedef uint8_t DIFF_P_OFF_MOP_MSB_t;



/*--------------------------------
** Register: SERIALNUMBER_BYTE7
** Enum: DIFF_P_SERIALNUMBER_BYTE7
** --
** Offset :0x66 - SerialNumber byte 7 stored in NVM memory and will be programmed at final test.
** ------------------------------*/
typedef uint8_t DIFF_P_SERIALNUMBER_BYTE7_t;


/*--------------------------------
** Register: SERIALNUMBER_BYTE6
** Enum: DIFF_P_SERIALNUMBER_BYTE6
** --
** Offset :0x67 - SerialNumber byte 6 stored in NVM memory and will be programmed at final test.
** ------------------------------*/
typedef uint8_t DIFF_P_SERIALNUMBER_BYTE6_t;


/*--------------------------------
** Register: SERIALNUMBER_BYTE5
** Enum: DIFF_P_SERIALNUMBER_BYTE5
** --
** Offset :0x68 - SerialNumber byte 5 stored in NVM memory and will be programmed at final test.
** ------------------------------*/
typedef uint8_t DIFF_P_SERIALNUMBER_BYTE5_t;


/*--------------------------------
** Register: SERIALNUMBER_BYTE4
** Enum: DIFF_P_SERIALNUMBER_BYTE4
** --
** Offset :0x69 - SerialNumber byte 4 stored in NVM memory and will be programmed at final test.
** ------------------------------*/
typedef uint8_t DIFF_P_SERIALNUMBER_BYTE4_t;


/*--------------------------------
** Register: SERIALNUMBER_BYTE3
** Enum: DIFF_P_SERIALNUMBER_BYTE3
** --
** Offset :0x6A - SerialNumber byte 3 stored in NVM memory and will be programmed at final test.
** ------------------------------*/
typedef uint8_t DIFF_P_SERIALNUMBER_BYTE3_t;


/*--------------------------------
** Register: SERIALNUMBER_BYTE2
** Enum: DIFF_P_SERIALNUMBER_BYTE2
** --
** Offset :0x6B - SerialNumber byte 2 stored in NVM memory and will be programmed at final test.
** ------------------------------*/
typedef uint8_t DIFF_P_SERIALNUMBER_BYTE2_t;


/*--------------------------------
** Register: SERIALNUMBER_BYTE1
** Enum: DIFF_P_SERIALNUMBER_BYTE1
** --
** Offset :0x6C - SerialNumber byte 1 stored in NVM memory and will be programmed at final test.
** ------------------------------*/
typedef uint8_t DIFF_P_SERIALNUMBER_BYTE1_t;


/*--------------------------------
** Register: SERIALNUMBER_BYTE0
** Enum: DIFF_P_SERIALNUMBER_BYTE0
** --
** Offset :0x6D - SerialNumber byte 0 stored in NVM memory and will be programmed at final test.
** ------------------------------*/
typedef uint8_t DIFF_P_SERIALNUMBER_BYTE0_t;


#endif  /* DIFF_P_H_ */
