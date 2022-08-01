/*
* Copyright 2020 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**
 * @file dbap.h
 * @brief The fxps7250.h contains the FXPS7250 pressure sensor register definitions, access macros, and
 * its bit mask.
 */
#ifndef FXPS7250_H_
#define FXPS7250_H_

#define FXPS7250D4_WHOAMI_VALUE (0xC4)

/**
 **
 **  FXPS7250 Sensor Internal Registers
 */
enum {
	FXPS7250_COUNT                = 0x00,
	FXPS7250_DEVSTAT	          = 0x01,
	FXPS7250_DEVSTAT1             = 0x02,
	FXPS7250_DEVSTAT2             = 0x03,
	FXPS7250_DEVSTAT3             = 0x04,
	/* Reserved:                    0x05 - 0x0D	*/
	FXPS7250_TEMPERATURE          = 0x0E,
	/* Reserved:                    0x0F - 0x0F	*/
	FXPS7250_DEVLOCK_WR           = 0x10,
	/* Reserved:                    0x11 - 0x13	*/
	FXPS7250_UF_REGION_W          = 0x14,
	FXPS7250_UF_REGION_R          = 0x15,
	FXPS7250_COMMTYPE             = 0x16,
	/* Reserved:                    0x17 - 0x19	*/
	FXPS7250_SOURCEID_0           = 0x1A,
	FXPS7250_SOURCEID_1           = 0x1B,
    /* Reserved:                    0x1C - 0x21	*/
	FXPS7250_TIMING_CFG           = 0x22,
	/* Reserved:                    0x22 - 0x3C	*/
	FXPS7250_SPI_CFG              = 0x3D,
	FXPS7250_WHO_AM_I             = 0x3E,
	FXPS7250_I2C_ADDRESS          = 0x3F,
	FXPS7250_DSP_CFG_U1           = 0x40,
	FXPS7250_DSP_CFG_U2           = 0x41,
	FXPS7250_DSP_CFG_U3           = 0x42,
	FXPS7250_DSP_CFG_U4           = 0x43,
	FXPS7250_DSP_CFG_U5           = 0x44,
	FXPS7250_INT_CFG              = 0x45,
	FXPS7250_P_INT_HI_L           = 0x46,
	FXPS7250_P_INT_HI_H           = 0x47,
	FXPS7250_P_INT_LO_L           = 0x48,
	FXPS7250_P_INT_LO_H           = 0x49,
	/* Reserved:                    0x4A - 0x4B	*/
	FXPS7250_P_CAL_ZERO_L         = 0x4C,
	FXPS7250_P_CAL_ZERO_H         = 0x4D,
	/* Reserved:                    0x4E - 0x5E	*/
	FXPS7250_DSP_STAT             = 0x60,
	FXPS7250_DEVSTAT_COPY         = 0x61,
	FXPS7250_SNSDATA0_L           = 0x62,
	FXPS7250_SNSDATA0_H           = 0x63,
	FXPS7250_SNSDATA1_L           = 0x64,
	FXPS7250_SNSDATA1_H           = 0x65,
	FXPS7250_SNSDATA0_TIME0       = 0x66,
	FXPS7250_SNSDATA0_TIME1       = 0x67,
	FXPS7250_SNSDATA0_TIME2       = 0x68,
	FXPS7250_SNSDATA0_TIME3       = 0x69,
	FXPS7250_SNSDATA0_TIME4       = 0x6A,
	FXPS7250_SNSDATA0_TIME5       = 0x6B,
	FXPS7250_P_MAX_L              = 0x6C,
	FXPS7250_P_MAX_H              = 0x6D,
	FXPS7250_P_MIN_L              = 0x6E,
	FXPS7250_P_MIN_H              = 0x6F,
	/* Reserved:                    0x70 - 0x77 */
	FXPS7250_FRT0                 = 0x78,
	FXPS7250_FRT1                 = 0x79,
	FXPS7250_FRT2                 = 0x7A,
	FXPS7250_FRT3                 = 0x7B,
	FXPS7250_FRT4                 = 0x7C,
	FXPS7250_FRT5                 = 0x7D,
	/* Reserved:					0x7E - 0x9F */
	FXPS7250_DSP_CFG_F            = 0xA0,
	/* Reserved:					0xA1 - 0xAE */
	FXPS7250_CRC_F_A              = 0xAF,
	/* Reserved:					0xB0 - 0xBE */
	FXPS7250_CRC_F_B              = 0xBF,
	FXPS7250_ICTYPEID             = 0xC0,
	FXPS7250_ICREVID              = 0xC1,
	FXPS7250_ICMFGID              = 0xC2,
	/* Reserved:					0xC3 - 0xC3 */
	FXPS7250_PN0                  = 0xC4,
	FXPS7250_PN1                  = 0xC5,
	FXPS7250_SN0                  = 0xC6,
	FXPS7250_SN1                  = 0xC7,
	FXPS7250_SN2                  = 0xC8,
	FXPS7250_SN3                  = 0xC9,
	FXPS7250_SN4                  = 0xCA,
	FXPS7250_ASICWFR              = 0xCB,
	FXPS7250_ASICWFR_X            = 0xCC,
	FXPS7250_ASICWFR_Y            = 0xCD,
	/* Reserved:					0xCE - 0xCE */
	FXPS7250_CRC_F_C              = 0xCF,
	FXPS7250_ASICWLOT_L           = 0xD0,
	FXPS7250_ASICWLOT_H           = 0xD1,
	/* Reserved:					0xD2 - 0xDE */
	FXPS7250_CRC_F_D              = 0xDF,
	FXPS7250_USERDATA_0           = 0xE0,
	FXPS7250_USERDATA_1           = 0xE1,
	FXPS7250_USERDATA_2           = 0xE2,
	FXPS7250_USERDATA_3           = 0xE3,
	FXPS7250_USERDATA_4           = 0xE4,
	FXPS7250_USERDATA_5           = 0xE5,
	FXPS7250_USERDATA_6           = 0xE6,
	FXPS7250_USERDATA_7           = 0xE7,
	FXPS7250_USERDATA_8           = 0xE8,
	FXPS7250_USERDATA_9           = 0xE9,
	FXPS7250_USERDATA_A           = 0xEA,
	FXPS7250_USERDATA_B           = 0xEB,
	FXPS7250_USERDATA_C           = 0xEC,
	FXPS7250_USERDATA_D           = 0xED,
	FXPS7250_USERDATA_E           = 0xEE,
	FXPS7250_CRC_UF0              = 0xEF,
	FXPS7250_USERDATA_10          = 0xF0,
	FXPS7250_USERDATA_11          = 0xF1,
	FXPS7250_USERDATA_12          = 0xF2,
	FXPS7250_USERDATA_13          = 0xF3,
	FXPS7250_USERDATA_14          = 0xF4,
	FXPS7250_USERDATA_15          = 0xF5,
	FXPS7250_USERDATA_16          = 0xF6,
	FXPS7250_USERDATA_17          = 0xF7,
	FXPS7250_USERDATA_18          = 0xF8,
	FXPS7250_USERDATA_19          = 0xF9,
	FXPS7250_USERDATA_1A          = 0xFA,
	FXPS7250_USERDATA_1B          = 0xFB,
	FXPS7250_USERDATA_1C          = 0xFC,
	FXPS7250_USERDATA_1D          = 0xFD,
	FXPS7250_USERDATA_1E          = 0xFE,
	FXPS7250_CRC_UF1              = 0xFF,
};

/*--------------------------------
** Register: COUNT
** Enum: FXPS7250_COUNT
** --
** Offset : 0x00 - Rolling counter register.
** ------------------------------*/
typedef uint8_t FXPS7250_COUNT_t;

/*--------------------------------
** Register: DEVSTAT
** Enum: FXPS7250_DEVSTAT
** --
** Offset : 0x01 - Device Status Register.
** ------------------------------*/
typedef union {
    struct {
        uint8_t 			  devinit : 1;
        uint8_t 			   devres : 1;
        uint8_t              testmode : 1;
        uint8_t            supply_err : 1;
        uint8_t           memtemp_err : 1;
        uint8_t              comm_err : 1;
        uint8_t _reserved_			  : 1;
        uint8_t               dsp_err : 1;
    } b;
    uint8_t w;
} FXPS7250_DEVSTAT_t;

/*
** DEVSTAT - Bit field mask definitions
*/
#define FXPS7250_DEVSTAT_DEVINIT_MASK   	((uint8_t) 0x01)
#define FXPS7250_DEVSTAT_DEVINIT_SHIFT  	((uint8_t)    0)

#define FXPS7250_DEVSTAT_DEVRES_MASK   		((uint8_t) 0x02)
#define FXPS7250_DEVSTAT_DEVRES_SHIFT  		((uint8_t)    1)

#define FXPS7250_DEVSTAT_TESTMODE_MASK   	((uint8_t) 0x04)
#define FXPS7250_DEVSTAT_TESTMODE_SHIFT  	((uint8_t)    2)

#define FXPS7250_DEVSTAT_SUPPLY_ERR_MASK   	((uint8_t) 0x08)
#define FXPS7250_DEVSTAT_SUPPLY_ERR_SHIFT  	((uint8_t)    3)

#define FXPS7250_DEVSTAT_MEMTEMP_ERR_MASK   ((uint8_t) 0x10)
#define FXPS7250_DEVSTAT_MEMTEMP_ERR_SHIFT  ((uint8_t)    4)

#define FXPS7250_DEVSTAT_COMM_ERR_MASK      ((uint8_t) 0x20)
#define FXPS7250_DEVSTAT_COMM_ERR_SHIFT     ((uint8_t)    5)

#define FXPS7250_DEVSTAT_DSP_ERR_MASK      	((uint8_t) 0x80)
#define FXPS7250_DEVSTAT_DSP_ERR_SHIFT     	((uint8_t)    7)


/*
** DEVSTAT - Bit field value definitions
*/
#define FXPS7250_DEVSTAT_DEVINIT_INIT     			((uint8_t) 0x01)  /*  Indicates if the device is initializing.				*/
#define FXPS7250_DEVSTAT_DEVINIT_NORMAL     		((uint8_t) 0x00)  /*  Device is operating normally.							*/
#define FXPS7250_DEVSTAT_DEVRES_RESET        		((uint8_t) 0x02)  /*  Indicates if the device has reset.                   	*/
#define FXPS7250_DEVSTAT_DEVRES_NOT_RESET        	((uint8_t) 0x00)  /*  Device is operating normally.                   		*/
#define FXPS7250_DEVSTAT_TESTMODE_ISACTIVE	        ((uint8_t) 0x04)  /*  Indicates if the device is in test mode.			   	*/
#define FXPS7250_DEVSTAT_TESTMODE_INACTIVE	        ((uint8_t) 0x00)  /*  Test mode is not active.								*/
#define FXPS7250_DEVSTAT_SUPPLY_ERR					((uint8_t) 0x08)  /*  Indicates if an error is flagged in DEVSTAT1.        	*/
#define FXPS7250_DEVSTAT_NOT_SUPPLY_ERR				((uint8_t) 0x00)  /*  No error is flagged in DEVSTAT1.						*/
#define FXPS7250_DEVSTAT_MEMTEMP_ERR				((uint8_t) 0x10)  /*  Indicates if an error is flagged in DEVSTAT2.        	*/
#define FXPS7250_DEVSTAT_NOT_MEMTEMP_ERR			((uint8_t) 0x00)  /*  No error is flagged in DEVSTAT2.        				*/
#define FXPS7250_DEVSTAT_COMM_ERR	         		((uint8_t) 0x20)  /*  Indicates if an error is flagged in DEVSTAT3.        	*/
#define FXPS7250_DEVSTAT_NOT_COMM_ERR	         	((uint8_t) 0x00)  /*  No error is flagged in DEVSTAT3.        				*/
#define FXPS7250_DEVSTAT_DSP_ERR		     		((uint8_t) 0x80)  /*  Indicates if an error is flagged in the pressure DSP.	*/
#define FXPS7250_DEVSTAT_NOT_DSP_ERR		     	((uint8_t) 0x00)  /*  No error is flagged in the pressure DSP.				*/

/*--------------------------------
** Register: DEVSTAT1
** Enum: FXPS7250_DEVSTAT1
** --
** Offset : 0x02 - Device Status Register.
** ------------------------------*/
typedef union {
    struct {
        uint8_t 			 cont_err : 1;
        uint8_t 		  intregf_err : 1;
        uint8_t            intreg_err : 1;
        uint8_t           intrega_err : 1;
        uint8_t _reserved1_			  : 1;
        uint8_t             vccov_err : 1;
        uint8_t _reserved2_			  : 1;
        uint8_t             vccuv_err : 1;

    } b;
    uint8_t w;
} FXPS7250_DEVSTAT1_t;


/*
** DEVSTAT - Bit field mask definitions
*/
#define FXPS7250_DEVSTAT1_CONT_ERR_MASK   	((uint8_t) 0x01)
#define FXPS7250_DEVSTAT1_CONT_ERR_SHIFT  	((uint8_t)    0)

#define FXPS7250_DEVSTAT1_INTREGF_ERR_MASK  ((uint8_t) 0x02)
#define FXPS7250_DEVSTAT1_INTREGF_ERR_SHIFT ((uint8_t)    1)

#define FXPS7250_DEVSTAT1_INTREG_ERR_MASK   ((uint8_t) 0x04)
#define FXPS7250_DEVSTAT1_INTREG_ERR_SHIFT  ((uint8_t)    2)

#define FXPS7250_DEVSTAT1_INTREGA_ERR_MASK  ((uint8_t) 0x08)
#define FXPS7250_DEVSTAT1_INTREGA_ERR_SHIFT ((uint8_t)    3)

#define FXPS7250_DEVSTAT1_VCCOV_ERR_MASK    ((uint8_t) 0x20)
#define FXPS7250_DEVSTAT1_VCCOV_ERR_SHIFT   ((uint8_t)    5)

#define FXPS7250_DEVSTAT1_VCCUV_ERR_MASK  	((uint8_t) 0x80)
#define FXPS7250_DEVSTAT1_VCCUV_ERR_SHIFT  	((uint8_t)    7)


/*
** DEVSTAT - Bit field value definitions
*/
#define FXPS7250_DEVSTAT1_CONT_ERR     				((uint8_t) 0x01)  /*  Indicates if an error is flagged by the continuity monitor.				*/
#define FXPS7250_DEVSTAT1_NO_CONT_ERR     			((uint8_t) 0x00)  /*  No error is flagged by the continuity monitor.							*/
#define FXPS7250_DEVSTAT1_INTREGF_ERR        		((uint8_t) 0x02)  /*  Indicates if the OTP regulator voltage is out of range.					*/
#define FXPS7250_DEVSTAT1_NO_INTREGF_ERR        	((uint8_t) 0x00)  /*  The OTP regulator voltage is in range.									*/
#define FXPS7250_DEVSTAT1_INTREG_ERR			    ((uint8_t) 0x04)  /*  Indicates if the digital regulator voltage is out of range.				*/
#define FXPS7250_DEVSTAT1_NO_INTREG_ERR			    ((uint8_t) 0x00)  /*  The digital regulator voltage is in range.								*/
#define FXPS7250_DEVSTAT1_INTREGA_ERR				((uint8_t) 0x08)  /*  Indicates if the analog regulator voltage is out of range.				*/
#define FXPS7250_DEVSTAT1_NO_INTREGA_ERR			((uint8_t) 0x00)  /*  The analog regulator voltage is out of range.								*/
#define FXPS7250_DEVSTAT1_VCCOV_ERR	         		((uint8_t) 0x20)  /*  Indicates if the Vcc voltage goes above the recommended maximum level.	*/
#define FXPS7250_DEVSTAT1_NO_VCCOV_ERR	         	((uint8_t) 0x00)  /*  The Vcc voltage is below the recommended maximum level.					*/
#define FXPS7250_DEVSTAT1_VCCUV_ERR		     		((uint8_t) 0x80)  /*  Indicates if the Vcc voltage goes below the recommended minimum level.	*/
#define FXPS7250_DEVSTAT1_NO_VCCUV_ERR		     	((uint8_t) 0x00)  /*  The Vcc voltage is above the recommended minimum level.					*/

/*--------------------------------
** Register: DEVSTAT2
** Enum: FXPS7250_DEVSTAT2
** --
** Offset : 0x03 - Device Status Register.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved1_			  : 2;
        uint8_t             temp0_err : 1;
        uint8_t _reserved2_			  : 1;
        uint8_t 		   u_w_active : 1;
        uint8_t              u_rw_err : 1;
        uint8_t 			u_otp_err : 1;
        uint8_t             f_otp_err : 1;

    } b;
    uint8_t w;
} FXPS7250_DEVSTAT2_t;


/*
** DEVSTAT - Bit field mask definitions
*/
#define FXPS7250_DEVSTAT2_TEMP0_ERR_MASK   	((uint8_t) 0x04)
#define FXPS7250_DEVSTAT2_TEMP0_ERR_SHIFT  	((uint8_t)    2)

#define FXPS7250_DEVSTAT2_U_W_ACTIVE_MASK  	((uint8_t) 0x10)
#define FXPS7250_DEVSTAT2_U_W_ACTIVE_SHIFT 	((uint8_t)    4)

#define FXPS7250_DEVSTAT2_U_RW_ERR_MASK   	((uint8_t) 0x20)
#define FXPS7250_DEVSTAT2_U_RW_ERR_SHIFT  	((uint8_t)    5)

#define FXPS7250_DEVSTAT2_U_OTP_ERR_MASK  	((uint8_t) 0x40)
#define FXPS7250_DEVSTAT2_U_OTP_ERR_SHIFT 	((uint8_t)    6)

#define FXPS7250_DEVSTAT2_F_OTP_ERR_MASK    ((uint8_t) 0x80)
#define FXPS7250_DEVSTAT2_F_OTP_ERR_SHIFT   ((uint8_t)    7)


/*
** DEVSTAT - Bit field value definitions
*/
#define FXPS7250_DEVSTAT2_TEMP0_ERR    				((uint8_t) 0x02)  /*  Indicates if temperature is outside of the recommended range.		*/
#define FXPS7250_DEVSTAT2_TEMP0_OK    				((uint8_t) 0x00)  /*  Indicates if temperature is inside of the recommended range.		*/
#define FXPS7250_DEVSTAT2_U_W_ACTIVE        		((uint8_t) 0x10)  /*  Indicates if a user initiated OTP write is in progress.			*/
#define FXPS7250_DEVSTAT2_U_W_INACTIVE        		((uint8_t) 0x00)  /*  Indicates if a user initiated OTP write is in progress.			*/
#define FXPS7250_DEVSTAT2_U_RW_ERR					((uint8_t) 0x20)  /*  Indicates if there is an error present in any user writable		*/
                                                                      /*  registers.														*/
#define FXPS7250_DEVSTAT2_NO_U_RW_ERR				((uint8_t) 0x00)  /*  Indicates if there are no errors present in any user writable		*/
																      /*  registers.														*/
#define FXPS7250_DEVSTAT2_U_OTP_ERR					((uint8_t) 0x40)  /*  Indicates if a fault is detected in the user OTP array.			*/
#define FXPS7250_DEVSTAT2_NO_U_OTP_ERR				((uint8_t) 0x00)  /*  Indicates if no faults are detected in the user OTP array.		*/
#define FXPS7250_DEVSTAT2_F_OTP_ERR	         		((uint8_t) 0x80)  /*  Indicates if a fault is detected in the factory OTP array.		*/
#define FXPS7250_DEVSTAT2_NO_F_OTP_ERR	         	((uint8_t) 0x00)  /*  Indicates if no faults are detected in the factory OTP array.		*/

/*--------------------------------
** Register: DEVSTAT3
** Enum: FXPS7250_DEVSTAT3
** --
** Offset : 0x04 - Device Status Register.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_			  : 6;
        uint8_t 		 osctrain_err : 1;
        uint8_t              miso_err : 1;

    } b;
    uint8_t w;
} FXPS7250_DEVSTAT3_t;


/*
** DEVSTAT - Bit field mask definitions
*/

#define FXPS7250_DEVSTAT3_OSCTRAIN_ERR_MASK 	((uint8_t) 0x40)
#define FXPS7250_DEVSTAT3_OSCTRAIN_ERR_SHIFT	((uint8_t)    6)

#define FXPS7250_DEVSTAT3_MISO_ERR_MASK    		((uint8_t) 0x80)
#define FXPS7250_DEVSTAT3_MISO_ERR_SHIFT   		((uint8_t)    7)


/*
** DEVSTAT - Bit field value definitions
*/

#define FXPS7250_DEVSTAT3_OSCTRAIN_ERR			((uint8_t) 0x40)  /*  Indicates if an error is detected in the oscillator settings		*/
															      /*  or communication timing.					  						*/
#define FXPS7250_DEVSTAT3_NO_OSCTRAIN_ERR		((uint8_t) 0x00)  /*  Indicates if no error is detected in the oscillator settings		*/
															      /*  or communication timing.					  						*/
#define FXPS7250_DEVSTAT3_MISO_ERR	         	((uint8_t) 0x80)  /*  Indicates if a data mismatch has occurred in the MISO data set.	*/
#define FXPS7250_DEVSTAT3_NO_MISO_ERR	        ((uint8_t) 0x00)  /*  Indicates if no data mismatch has occurred in the MISO data set.	*/

/*--------------------------------
** Register: TEMP
** Enum: FXPS7250_TEMP
** --
** Offset : 0x0E - Temperature Data Registers.
** ------------------------------*/
typedef uint8_t FXPS7250_TEMP_t;



/*--------------------------------
** Register: DEVLOCK_WR
** Enum: FXPS7250_DEVLOCK_WR
** --
** Offset : 0x10 - Lock Register Writes Register.
** ------------------------------*/
typedef union {
    struct {
        uint8_t 			    reset : 2;
        uint8_t _reserved1_			  : 1;
        uint8_t 		  sup_err_dis : 1;
        uint8_t _reserved2_           : 3;
        uint8_t               endinit : 1;

    } b;
    uint8_t w;
} FXPS7250_DEVLOCK_WR_t;


/*
** DEVLOCK_WR - Bit field mask definitions
*/
#define FXPS7250_DEVLOCK_WR_RESET_MASK   	((uint8_t) 0x01)
#define FXPS7250_DEVLOCK_WR_RESET_SHIFT  	((uint8_t)    0)

#define FXPS7250_DEVLOCK_WR_SUP_ERR_MASK   	((uint8_t) 0x08)
#define FXPS7250_DEVLOCK_WR_SUP_ERR_SHIFT  	((uint8_t)    3)

#define FXPS7250_DEVLOCK_WR_ENDINIT_MASK  	((uint8_t) 0x80)
#define FXPS7250_DEVLOCK_WR_ENDINIT_SHIFT 	((uint8_t)    7)


/*
** DEVLOCK_WR - Bit field value definitions
*/
#define FXPS7250_DEVLOCK_WR_RESET00	        		((uint8_t) 0x00)  /*  First element in the reset sequence.								*/
#define FXPS7250_DEVLOCK_WR_RESET01	        		((uint8_t) 0x01)  /*  Final element in the reset sequence.								*/
#define FXPS7250_DEVLOCK_WR_RESET10					((uint8_t) 0x02)  /*  No Effect.														*/
#define FXPS7250_DEVLOCK_WR_RESET11					((uint8_t) 0x03)  /*  Second element in the reset sequence.								*/
#define FXPS7250_DEVLOCK_WR_SUP_BLOCKED				((uint8_t) 0x08)  /*  Indicates if supply error reporting is blocked by the user.		*/
#define FXPS7250_DEVLOCK_WR_SUP_ALLOWED				((uint8_t) 0x00)  /*  Indicates if supply error reporting is allowed by the user.		*/
#define FXPS7250_DEVLOCK_WR_ENDINIT_FINISHED	    ((uint8_t) 0x80)  /*  Indicates if the device has finished initializing.				*/
#define FXPS7250_DEVLOCK_WR_ENDINIT_RUNNING	        ((uint8_t) 0x00)  /*  Indicates if the device is still initializing.					*/

/*--------------------------------
** Register: UF_REGION_W
** Enum: FXPS7250_UF_REGION_W
** --
** Offset : 0x14 - Used to load OTP registers for reading.
** ------------------------------*/
typedef union {
    struct {
        uint8_t empty				  : 4;
        uint8_t 		  region_load : 4;
    } b;
    uint8_t w;
} FXPS7250_UF_REGION_W_t;


/*
** UF_REGION_W - Bit field mask definitions
*/
#define FXPS7250_UF_REGION_W_REGION_LOAD_MASK   	((uint8_t) 0xA0)
#define FXPS7250_UF_REGION_W_REGION_LOAD_SHIFT  	((uint8_t)    4)

/*
** UF_REGION_W - Bit field value definitions
*/
#define FXPS7250_UF_REGION_W_REGION_LOAD_A0_AF		((uint8_t) 0xA0)  /*  Loads addresses A0 through AF 									*/
#define FXPS7250_UF_REGION_W_REGION_LOAD_B0_BF		((uint8_t) 0xB0)  /*  Loads addresses B0 through BF 									*/
#define FXPS7250_UF_REGION_W_REGION_LOAD_C0_CF		((uint8_t) 0xC0)  /*  Loads addresses C0 through CF 									*/
#define FXPS7250_UF_REGION_W_REGION_LOAD_D0_DF		((uint8_t) 0xD0)  /*  Loads addresses D0 through DF 									*/
#define FXPS7250_UF_REGION_W_REGION_LOAD_E0_EF		((uint8_t) 0xE0)  /*  Loads addresses E0 through EF 									*/
#define FXPS7250_UF_REGION_W_REGION_LOAD_F0_FF		((uint8_t) 0xF0)  /*  Loads addresses F0 through FF 									*/


/*--------------------------------
** Register: UF_REGION_R
** Enum: FXPS7250_UF_REGION_R
** --
** Offset : 0x15 - Used to read OTP registers. Should be loaded by UF_REGION_W first.
** ------------------------------*/
typedef union {
    struct {
        uint8_t empty				  : 4;
        uint8_t 	    region_active : 4;
    } b;
    uint8_t w;
} FXPS7250_UF_REGION_R_t;


/*
** UF_REGION_R - Bit field mask definitions
*/
#define FXPS7250_UF_REGION_R_REGION_ACTIVE_MASK   	((uint8_t) 0xA0)
#define FXPS7250_UF_REGION_R_REGION_ACTIVE_SHIFT  	((uint8_t)    4)


/*
** UF_R_REGION_R - Bit field value definitions
*/
#define FXPS7250_UF_REGION_W_REGION_ACTIVE_00		((uint8_t) 0x00)  /*  Load of addresses is in progress.									*/
#define FXPS7250_UF_REGION_W_REGION_ACTIVE_A0_AF	((uint8_t) 0xA0)  /*  Reads addresses A0 through AF. Must be loaded first.				*/
#define FXPS7250_UF_REGION_W_REGION_ACTIVE_B0_BF	((uint8_t) 0xB0)  /*  Reads addresses B0 through BF. Must be loaded first.				*/
#define FXPS7250_UF_REGION_W_REGION_ACTIVE_C0_CF	((uint8_t) 0xC0)  /*  Reads addresses C0 through CF. Must be loaded first.				*/
#define FXPS7250_UF_REGION_W_REGION_ACTIVE_D0_DF	((uint8_t) 0xD0)  /*  Reads addresses D0 through DF. Must be loaded first.				*/
#define FXPS7250_UF_REGION_W_REGION_ACTIVE_E0_EF	((uint8_t) 0xE0)  /*  Reads addresses E0 through EF. Must be loaded first.				*/
#define FXPS7250_UF_REGION_W_REGION_ACTIVE_F0_FF	((uint8_t) 0xF0)  /*  Reads addresses F0 through FF. Must be loaded first.				*/


/*--------------------------------
** Register: COMMTYPE
** Enum: FXPS7250_COMTYPE
** --
** Offset : 0x16 - 3 bit register that determines the communication protocol.
** ------------------------------*/
typedef union {
    struct {
        uint8_t 			 commtype : 3;
        uint8_t _reserved_            : 5;
    } b;
    uint8_t w;
} FXPS7250_COMMTYPE_t;


/*
** COMMTYPE - Bit field mask definitions
*/
#define FXPS7250_COMMTYPE_COMMTYPE_MASK   						((uint8_t) 0x00)
#define FXPS7250_COMMTYPE_COMMTYPE_SHIFT  						((uint8_t)    0)


/*
** COMMTYPE - Bit field value definitions
*/
#define FXPS7250_COMMTYPE_32BIT_SPI_NO_SELFTEST_DEBUG0		((uint8_t) 0x00)  /*  32-bit SPI communication protocol with no internal test, in debug mode	*/
#define FXPS7250_COMMTYPE_32BIT_SPI_SELFTEST				((uint8_t) 0x01)  /*  32-bit SPI communication protocol with internal test on startup			*/
#define FXPS7250_COMMTYPE_32BIT_SPI_NO_SELFTEST_DEBUG1		((uint8_t) 0x02)  /*  32-bit SPI communication protocol with no internal test, in debug mode	*/
#define FXPS7250_COMMTYPE_32BIT_SPI_NO_SELFTEST_DEBUG2		((uint8_t) 0x04)  /*  32-bit SPI communication protocol with no internal test, in debug mode	*/
#define FXPS7250_COMMTYPE_I2C_PIN3_INT0						((uint8_t) 0x06)  /*  I2C communication protocol, with PIN 3 working as an interrupt			*/
#define FXPS7250_COMMTYPE_I2C_PIN3_INT1						((uint8_t) 0x07)  /*  I2C communication protocol, with PIN 3 working as an interrupt			*/

/*--------------------------------
** Register: SOURCEID_0
** Enum: FXPS7250_SOURCEID_0
** --
** Offset : 0x1A - Contains Source ID information used in SPI mode.
** ------------------------------*/
typedef union {
    struct {
        uint8_t 		   sourceid_0 : 4;
        uint8_t _reserved_			  : 3;
        uint8_t 			  sid0_en : 1;
    } b;
    uint8_t w;
} FXPS7250_SOURCEID_0_t;


/*
** SOURCEID_0 - Bit field mask definitions
*/
#define FXPS7250_SOURCEID_0_SOURCEID_0_MASK   		((uint8_t) 0x01)
#define FXPS7250_SOURCEID_0_SOURCEID_0_SHIFT  		((uint8_t)    0)

#define FXPS7250_SOURCEID_0_SID0_EN_MASK			((uint8_t) 0x80)
#define FXPS7250_SOURCEID_0_SID0_EN_SHIFT			((uint8_t)    7)


/*
** SOURCEID_0 - Bit field value definitions
*/
#define FXPS7250_SOURCEID_0_SOURCEID_0				((uint8_t) 0x01)  /*  The stream of data to be sent if sid0_en is true						*/
#define FXPS7250_SOURCEID_0_SID0_EN					((uint8_t) 0x80)  /*  Enables reading of data or an error response for those source-id bits	*/

/*--------------------------------
** Register: SOURCEID_1
** Enum: FXPS7250_SOURCEID_1
** --
** Offset : 0x1B - Contains Source ID information used in SPI mode.
** ------------------------------*/
typedef union {
    struct {
        uint8_t 		   sourceid_1 : 4;
        uint8_t _reserved_			  : 3;
        uint8_t 			  sid1_en : 1;
    } b;
    uint8_t w;
} FXPS7250_SOURCEID_1_t;


/*
** SOURCEID_1 - Bit field mask definitions
*/
#define FXPS7250_SOURCEID_1_SOURCEID_1_MASK   		((uint8_t) 0x01)
#define FXPS7250_SOURCEID_1_SOURCEID_1_SHIFT  		((uint8_t)    0)

#define FXPS7250_SOURCEID_1_SID1_EN_MASK			((uint8_t) 0x80)
#define FXPS7250_SOURCEID_1_SID1_EN_SHIFT			((uint8_t)    7)


/*
** SOURCEID_1 - Bit field value definitions
*/
#define FXPS7250_SOURCEID_1_SOURCEID_10				((uint8_t) 0x01)  /*  Stream of data that is sent if sid1_en is true						*/
#define FXPS7250_SOURCEID_1_SID1_EN					((uint8_t) 0x80)  /*  Enables reading of data or an error response for those source-id bits	*/


/*--------------------------------
** Register: TIMING_CFG
** Enum: FXPS7250_TIMING_CFG
** --
** Offset : 0x22 - Contains user specified configurations for protocol timing.
** ------------------------------*/
typedef union {
    struct {
        uint8_t 		  	ck_cal_en : 1;
        uint8_t _reserved1_			  : 2;
        uint8_t 		   ck_cal_rst : 1;
        uint8_t 		 osctrain_sel : 1;
        uint8_t _reserved2_			  : 3;
    } b;
    uint8_t w;
} FXPS7250_TIMING_CFG_t;


/*
** TIMING_CFG - Bit field mask definitions
*/
#define FXPS7250_TIMING_CFG_CK_CAL_EN_MASK   		((uint8_t) 0x01)
#define FXPS7250_TIMING_CFG_CK_CAL_EN_SHIFT  		((uint8_t)    0)

#define FXPS7250_TIMING_CFG_CK_CAL_RST_MASK			((uint8_t) 0x08)
#define FXPS7250_TIMING_CFG_CK_CAL_RST_SHIFT 		((uint8_t)    3)

#define FXPS7250_TIMING_CFG_OSCTRAIN_SEL_MASK		((uint8_t) 0x10)
#define FXPS7250_TIMING_CFG_OSCTRAIN_SEL_SHIFT		((uint8_t)    4)

/*
** TIMING_CFG - Bit field value definitions
*/
#define FXPS7250_TIMING_CFG_CK_CAL_EN				((uint8_t) 0x01)  /*  Enables clock oscillator training over SPI or I2C				*/
#define FXPS7250_TIMING_CFG_CK_CAL_EN_DIS			((uint8_t) 0x00)  /*  Clock oscillator training is disabled							*/
#define FXPS7250_TIMING_CFG_CK_CAL_RST				((uint8_t) 0x08)  /*  Resets the oscillator training to default 					*/
#define FXPS7250_TIMING_CFG_CK_CAL_KEEP				((uint8_t) 0x00)  /*  Training value is maintained at last trained value 			*/
#define FXPS7250_TIMING_CFG_OSCTRAIN_SEL			((uint8_t) 0x10)  /*  Sets the protocol to SPI if FXPS7250_COMMTYPE_COMMTYPE=0x00 or 	*/
																  /*  FXPS7250_COMMTYPE_COMMTYPE=0x01. Otherwise has no effect.			*/
#define FXPS7250_TIMING_CFG_OSCTRAIN_DISABLE		((uint8_t) 0x00)  /*  Disables oscillator training.									*/


/*--------------------------------
** Register: SPI_CFG
** Enum: FXPS7250_SPI_CFG
** --
** Offset : 0x3D - SPI Configuration Control Register.
** ------------------------------*/
typedef union {
    struct {
        uint8_t 		   spicrcseed : 4;
        uint8_t           spi_crc_len : 2;
        uint8_t           	 datasize : 1;
        uint8_t _reserved_			  : 1;


    } b;
    uint8_t w;
} FXPS7250_SPI_CFG_t;


/*
** SPI_CFG - Bit field mask definitions
*/
#define FXPS7250_SPI_CFG_SPICRCSEED_MASK    ((uint8_t) 0x01)
#define FXPS7250_SPI_CFG_SPICRCSEED_SHIFT   ((uint8_t)    0)

#define FXPS7250_SPI_CFG_SPI_CRC_LEN_MASK   ((uint8_t) 0x10)
#define FXPS7250_SPI_CFG_SPI_CRC_LEN_SHIFT  ((uint8_t)    4)

#define FXPS7250_SPI_CFG_DATASIZE_MASK   	((uint8_t) 0x40)
#define FXPS7250_SPI_CFG_DATASIZE_SHIFT  	((uint8_t)    6)


/*
** SPI_CFG - Bit field value definitions
*/
#define FXPS7250_SPI_CFG_SPICRCSEED	       	((uint8_t) 0x01)  	/*  CRCSeed is non-zero. For use with CRC_LEN.			*/
#define FXPS7250_SPI_CFG_SPICRCSEED_ZERO   	((uint8_t) 0x00)  	/*  CRCSeed is zero. For use with CRC_LEN.				*/
#define FXPS7250_SPI_CFG_SPI_CRC_LEN_00	   	((uint8_t) 0x00)    /*  Sets the length of the CRC Seed to 8, 4, or 3 bits 	*/
															/*  based on whether the CRC Seed is 0 or non-zero.		*/
#define FXPS7250_SPI_CFG_SPI_CRC_LEN_01	   	((uint8_t) 0x10)    /*  Sets the length of the CRC Seed to 8, 4, or 3 bits 	*/
															/*  based on whether the CRC Seed is 0 or non-zero.		*/
#define FXPS7250_SPI_CFG_SPI_CRC_LEN_10	   	((uint8_t) 0x20)    /*  Sets the length of the CRC Seed to 8, 4, or 3 bits 	*/
															/*  based on whether the CRC Seed is 0 or non-zero.		*/
#define FXPS7250_SPI_CFG_SPI_CRC_LEN_11	   	((uint8_t) 0x30)    /*  Sets the length of the CRC Seed to 8, 4, or 3 bits 	*/
															/*  based on whether the CRC Seed is 0 or non-zero.		*/
#define FXPS7250_SPI_CFG_DATASIZE_16		((uint8_t) 0x40)    /*  Sets SPI datafield size to 16 bits.					*/
#define FXPS7250_SPI_CFG_DATASIZE_12		((uint8_t) 0x00)    /*  Sets SPI datafield size to 12 bits.					*/


/*--------------------------------
** Register: WHO_AM_I
** Enum: FXPS7250_WHO_AM_I
** --
** Offset : 0x3E - Device Identification Register.
** ------------------------------*/
//typedef union {
//    struct {
//        uint8_t            WHO_AM_I : 8; /*  The device identification register.									*/
//    } b;
//    uint8_t w;
//} FXPS7250_WHO_AM_I_t;
typedef uint8_t FXPS7250_WHO_AM_I_t;


/*
** WHO_AM_I - Bit field mask definitions
*/
#define FXPS7250_WHO_AM_I_MASK      			((uint8_t) 0x01)
#define FXPS7250_WHO_AM_I_SHIFT     			((uint8_t)    0)


/*
** WHO_AM_I - Bit field value definitions
*/
#define FXPS7250_WHO_AM_I_1     				((uint8_t) 0x01)  /*  Non-zero value in the register returns the value in the register.	*/
#define FXPS7250_WHO_AM_I_DEFAULT	        	((uint8_t) 0x00)  /*  A zero value WHO_AM_I register returns the default value: C4h.	*/


/*--------------------------------
** Register: I2C_ADDRESS
** Enum: FXPS7250_I2C_ADDRESS
** --
** Offset : 0x3F - This register contains the I2C identifier.
** ------------------------------*/
typedef uint8_t FXPS7250_I2C_ADDRESS_t;


/*--------------------------------
** Register: DSP_CFG_U1
** Enum: FXPS7250_DSP_CFG_U1
** --
** Offset : 0x40 - User Configuration #1 Register.
** ------------------------------*/
typedef union {
    struct {
        uint8_t          user_range : 2; /*  User Range Selection Bits.												*/
        uint8_t _reserved_ 			: 2; /*  Reserved.																*/
        uint8_t            		lpf : 4; /*  Low Pass Filter Selection Bits.										*/
    } b;
    uint8_t w;
} FXPS7250_DSP_CFG_U1_t;


/*
** DSP_CFG_U1 - Bit field mask definitions
*/
#define FXPS7250_DSP_CFG_U1_USER_RANGE_MASK     ((uint8_t) 0x00)
#define FXPS7250_DSP_CFG_U1_USER_RANGE_SHIFT    ((uint8_t)    0)

#define FXPS7250_DSP_CFG_U1_LPF_MASK      		((uint8_t) 0x10)
#define FXPS7250_DSP_CFG_U1_LPF_SHIFT     		((uint8_t)    5)

/*
** DSP_CFG_U1 - Bit field value definitions
*/
#define FXPS7250_DSP_CFG_U1_LPF_370HZ_2POLE     	((uint8_t) 0x00)  /*  Default Low Pass Filter at 370hz and 2-pole.						*/
#define FXPS7250_DSP_CFG_U1_LPF_400HZ_3POLE       	((uint8_t) 0x10)  /*  Alternate Low Pass Filter at 400hz and 3-pole.					*/
#define FXPS7250_DSP_CFG_U1_LPF_800HZ_4POLE       	((uint8_t) 0x20)  /*  Alternate Low Pass Filter at 800hz and 4-pole.					*/
#define FXPS7250_DSP_CFG_U1_LPF_1000HZ_4POLE       	((uint8_t) 0x40)  /*  Alternate Low Pass Filter at 1000hz and 4-pole.					*/


/*--------------------------------
** Register: DSP_CFG_U4
** Enum: FXPS7250_DSP_CFG_U4
** --
** Offset : 0x43 - User Configuration #4 Register.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved0_			: 2; /*  Reserved.																*/
        uint8_t            	int_out : 1; /*  Interrupt Pin Configuration.											*/
        uint8_t _reserved_ 			: 5; /*  Reserved.																*/
    } b;
    uint8_t w;
} FXPS7250_DSP_CFG_U4_t;


/*
** DSP_CFG_U4 - Bit field mask definitions
*/
#define FXPS7250_DSP_CFG_U4_INT_OUT_MASK     					((uint8_t) 0x04)
#define FXPS7250_DSP_CFG_U4_INT_OUT_SHIFT    					((uint8_t)    2)

/*
** DSP_CFG_U4 - Bit field value definitions
*/
#define FXPS7250_DSP_CFG_U4_INT_OUT_ACTIVE_HIGH_PULL_DOWN     	((uint8_t) 0x00)  /*  Open Drain, Active High with Pull-down Current.					*/
#define FXPS7250_DSP_CFG_U4_INT_OUT_ACTIVE_LOW_PULL_UP			((uint8_t) 0x04)  /*  Open Drain, Active Low with Pull-up Current.						*/


/*--------------------------------
** Register: DSP_CFG_U5
** Enum: FXPS7250_DSP_CFG_U5
** --
** Offset : 0x44 - User Configuration #5 Register.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved_			: 4; /*  Reserved.																*/
        uint8_t            	st_ctrl : 4; /*  Self-test Control Bits.												*/
    } b;
    uint8_t w;
} FXPS7250_DSP_CFG_U5_t;


/*
** DSP_CFG_U5 - Bit field mask definitions
*/
#define FXPS7250_DSP_CFG_U5_ST_CTRL_MASK     					((uint8_t) 0x10)
#define FXPS7250_DSP_CFG_U5_ST_CTRL_SHIFT    					((uint8_t)    4)

/*
** DSP_CFG_U5 - Bit field value definitions
*/
#define FXPS7250_DSP_CFG_U5_STL_CTRL_NORMAL_SIGNAL		     	((uint8_t) 0x00)  /*  SNS_DATAx_X Contains: 16-bit Absolute Pressure.					*/
#define FXPS7250_DSP_CFG_U5_STL_CTRL_P_CELL_MODE_VERIFICATION	((uint8_t) 0x10)  /*  SNS_DATAx_X Contains: 16-bit Absolute Pressure.					*/
#define FXPS7250_DSP_CFG_U5_STL_CTRL_INHIBIT_SNS_DATA_X_WRITE0	((uint8_t) 0x40)  /*  SNS_DATAx_X Contains: 0x0000.										*/
#define FXPS7250_DSP_CFG_U5_STL_CTRL_INHIBIT_SNS_DATA_X_WRITE1	((uint8_t) 0x50)  /*  SNS_DATAx_X Contains: 0xAAAA.										*/
#define FXPS7250_DSP_CFG_U5_STL_CTRL_INHIBIT_SNS_DATA_X_WRITE2	((uint8_t) 0x60)  /*  SNS_DATAx_X Contains: 0x5555.										*/
#define FXPS7250_DSP_CFG_U5_STL_CTRL_INHIBIT_SNS_DATA_X_WRITE3	((uint8_t) 0x70)  /*  SNS_DATAx_X Contains: 0xFFFF.										*/
#define FXPS7250_DSP_CFG_U5_STL_CTRL_DIGITAL_SELF_TEST0			((uint8_t) 0xC0)  /*  SNS_DATAx_X Contains: Digital Self Test Output.					*/
#define FXPS7250_DSP_CFG_U5_STL_CTRL_DIGITAL_SELF_TEST1			((uint8_t) 0xD0)  /*  SNS_DATAx_X Contains: Digital Self Test Output.					*/
#define FXPS7250_DSP_CFG_U5_STL_CTRL_DIGITAL_SELF_TEST2			((uint8_t) 0xE0)  /*  SNS_DATAx_X Contains: Digital Self Test Output.					*/
#define FXPS7250_DSP_CFG_U5_STL_CTRL_DIGITAL_SELF_TEST3			((uint8_t) 0xF0)  /*  SNS_DATAx_X Contains: Digital Self Test Output.					*/


/*--------------------------------
** Register: INT_CFG
** Enum: FXPS7250_INT_CFG
** --
** Offset : 0x45 - Interrupt Configuration Register.
** ------------------------------*/
typedef union {
    struct {
        uint8_t _reserved0_			: 3; /*  Reserved.																*/
        uint8_t        int_polarity : 1; /*  Interrupt Polarity Bit.												*/
        uint8_t        		 int_ps : 2; /*  Programmable Pulse Stretch Time for Interrupt Output.					*/
        uint8_t _reserved1_			: 1; /*  Reserved.																*/
    } b;
    uint8_t w;
} FXPS7250_INT_CFG_t;


/*
** INT_CFG - Bit field mask definitions
*/
#define FXPS7250_INT_CFG_INT_POLARITY_MASK     					((uint8_t) 0x08)
#define FXPS7250_INT_CFG_INT_POLARITY_SHIFT    					((uint8_t)    3)

#define FXPS7250_INT_CFG_INT_PS_MASK     						((uint8_t) 0x10)
#define FXPS7250_INT_CFG_INT_PS_SHIFT    						((uint8_t)    4)

/*
** INT_CFG - Bit field value definitions
*/
#define FXPS7250_INT_CFG_INT_POLARITY_OUTSIDE_RANGE		     	((uint8_t) 0x00)  /*  Interrupt activates if values are outside of the range.			*/
#define FXPS7250_INT_CFG_INT_POLARITY_INSIDE_RANGE				((uint8_t) 0x08)  /*  Interrupt activates if values are inside of the range.			*/
#define FXPS7250_INT_CFG_INT_PS_00								((uint8_t) 0x00)  /*  Pulse Stretch of 0ms.												*/
#define FXPS7250_INT_CFG_INT_PS_01								((uint8_t) 0x10)  /*  Pulse Stretch of 16,000ms - 16,512ms.								*/
#define FXPS7250_INT_CFG_INT_PS_10								((uint8_t) 0x20)  /*  Pulse Stretch of 64,000ms - 60,512ms.								*/
#define FXPS7250_INT_CFG_INT_PS_11								((uint8_t) 0x30)  /*  Pulse Stretch of 256,000ms - 256,512ms.							*/


/*--------------------------------
** Register: PIN_INT_HI_L
** Enum: FXPS7250_PIN_INT_HI_L
** --
** Offset : 0x46 - 8 LSBs of 16-bit High Interrupt Window Comparator Threshold Registers.
** ------------------------------*/
typedef uint8_t FXPS7250_PIN_INT_HI_L_t;


/*--------------------------------
** Register: PIN_INT_HI_M
** Enum: FXPS7250_PIN_INT_HI_M
** --
** Offset : 0x47 - 8 MSBs of 16-bit High Interrupt Window Comparator Threshold Registers.
** ------------------------------*/
typedef uint8_t FXPS7250_PIN_INT_HI_M_t;


/*--------------------------------
** Register: PIN_INT_LO_L
** Enum: FXPS7250_PIN_INT_LO_L
** --
** Offset : 0x48 - 8 LSBs of 16-bit Low Interrupt Window Comparator Threshold Registers.
** ------------------------------*/
typedef uint8_t FXPS7250_PIN_INT_LO_L_t;


/*--------------------------------
** Register: PIN_INT_LO_H
** Enum: FXPS7250_PIN_INT_LO_H
** --
** Offset : 0x49 - 8 MSBs of 16-bit Low Interrupt Window Comparator Threshold Registers.
** ------------------------------*/
typedef uint8_t FXPS7250_PIN_INT_LO_H_t;


/*--------------------------------
** Register: P_CAL_ZERO_L
** Enum: FXPS7250_P_CAL_ZERO_L
** --
** Offset : 0x4C - 8 LSBs of 16-bit Pressure Calibration Registers.
** ------------------------------*/
typedef uint8_t FXPS7250_P_CAL_ZERO_L_t;


/*--------------------------------
** Register: P_CAL_ZERO_H
** Enum: FXPS7250_P_CAL_ZERO_H
** --
** Offset : 0x4D - 8 MSBs of 16-bit Pressure Calibration Registers.
** ------------------------------*/
typedef uint8_t FXPS7250_P_TGT2_LSB_t;


/*--------------------------------
** Register: DSP_STAT
** Enum: FXPS7250_DSP_STAT
** --
** Offset : 0x60 - DSP Specific Status Register.
** ------------------------------*/
typedef union {
    struct {
        uint8_t         	 st_error : 1; /*  Self-Test Error Flag.                                          					*/
        uint8_t            	 cm_error : 1; /*  Common Mode Error Status bit.													*/
        uint8_t         	st_active : 1; /*  Self-Test Active Bit.															*/
        uint8_t    		   st_incmplt : 1; /*  Self-Test Incomplete Bit. Set after device reset and cleared when an ST is run.	*/
        uint8_t	_reserved0_			  : 1; /*  Reserved.																		*/
        uint8_t 			 pabs_low : 1; /*  Status Bit for low overage limit of absolute pressure. 							*/
        uint8_t 			pabs_high : 1; /*  Status Bit for high overage limit of absolute pressure. 							*/
        uint8_t _reserved1_			  : 1; /*  Reserved. 																		*/
    } b;
    uint8_t w;
} FXPS7250_DSP_STAT_t;


/*
** DSP_STAT - Bit field mask definitions
*/
#define FXPS7250_DSP_STAT_ST_ERROR_MASK   		((uint8_t) 0x01)
#define FXPS7250_DSP_STAT_ST_ERROR_SHIFT  		((uint8_t)    0)

#define FXPS7250_DSP_STAT_CM_ERROR_MASK    		((uint8_t) 0x02)
#define FXPS7250_DSP_STAT_CM_ERROR_SHIFT   		((uint8_t)    1)

#define FXPS7250_DSP_STAT_ST_ACTIVE_MASK    	((uint8_t) 0x04)
#define FXPS7250_DSP_STAT_ST_ACTIVE_SHIFT   	((uint8_t)    2)

#define FXPS7250_DSP_STAT_ST_INCMPLT_MASK    	((uint8_t) 0x08)
#define FXPS7250_DSP_STAT_ST_INCMPLT_SHIFT   	((uint8_t)    3)

#define FXPS7250_DSP_STAT_PABS_LOW_MASK    		((uint8_t) 0x20)
#define FXPS7250_DSP_STAT_PABS_LOW_SHIFT   		((uint8_t)    5)

#define FXPS7250_DSP_STAT_PABS_HIGH_MASK    	((uint8_t) 0x40)
#define FXPS7250_DSP_STAT_PABS_HIGH_SHIFT   	((uint8_t)    6)

/*
** DSP_STAT - Bit field value definitions
*/
#define FXPS7250_DSP_STAT_ST_ERROR_CLR          	((uint8_t) 0x00)  /*  No Self-Test Error has been flagged.									*/
#define FXPS7250_DSP_STAT_ST_ERROR_FLAGGED      	((uint8_t) 0x01)  /*  A Self-Test Error has been flagged.									*/
#define FXPS7250_DSP_STAT_CM_ERROR_CLR       		((uint8_t) 0x00)  /*  No Common Mode Error has been flagged.								*/
#define FXPS7250_DSP_STAT_CM_ERROR_FLAGGED     		((uint8_t) 0x02)  /*  A Common Mode Error has been flagged.									*/
#define FXPS7250_DSP_STAT_ST_ACTIVE_INACTIVE    	((uint8_t) 0x00)  /*  No Self-Test Mode is currently active.								*/
#define FXPS7250_DSP_STAT_ST_ACTIVE_ACTIVE      	((uint8_t) 0x04)  /*  A Self-Test Mode is currently active.									*/
#define FXPS7250_DSP_STAT_ST_INCMPLT_FALSE    		((uint8_t) 0x00)  /*  An analog or digital Self-Test has been run since the last reset.		*/
#define FXPS7250_DSP_STAT_ST_INCMPLT_TRUE    		((uint8_t) 0x08)  /*  An analog or digital Self-Test has not been run since the last reset.	*/
#define FXPS7250_DSP_STAT_PABS_LOW_IN_RANGE			((uint8_t) 0x00)  /*  Absolute Pressure is below the out-of-range lower limit 				*/
#define FXPS7250_DSP_STAT_PABS_LOW_NOT_IN_RANGE		((uint8_t) 0x20)  /*  Absolute Pressure is above the out-of-range lower limit 				*/
#define FXPS7250_DSP_STAT_PABS_HIGH_IN_RANGE		((uint8_t) 0x00)  /*  Absolute Pressure is below the out-of-range higher limit 				*/
#define FXPS7250_DSP_STAT_PABS_HIGH_NOT_IN_RANGE	((uint8_t) 0x40)  /*  Absolute Pressure is above the out-of-range higher limit 				*/

/*--------------------------------
** Register: DEVSTAT_COPY
** Enum: FXPS7250_DEVSTAT_COPY
** --
** Offset : 0x61 - Device Status Copy Register.
** ------------------------------*/
typedef union {
    struct {
        uint8_t 			  devinit : 1;
        uint8_t 			   devres : 1;
        uint8_t              testmode : 1;
        uint8_t            supply_err : 1;
        uint8_t           memtemp_err : 1;
        uint8_t              comm_err : 1;
        uint8_t _reserved_			  : 1;
        uint8_t               dsp_err : 1;

    } b;
    uint8_t w;
} FXPS7250_DEVSTAT_COPY_t;


/*
** DEVSTAT - Bit field mask definitions
*/
#define FXPS7250_DEVSTAT_DEVINIT_MASK   	((uint8_t) 0x01)
#define FXPS7250_DEVSTAT_DEVINIT_SHIFT  	((uint8_t)    0)

#define FXPS7250_DEVSTAT_DEVRES_MASK   		((uint8_t) 0x02)
#define FXPS7250_DEVSTAT_DEVRES_SHIFT  		((uint8_t)    1)

#define FXPS7250_DEVSTAT_TESTMODE_MASK   	((uint8_t) 0x04)
#define FXPS7250_DEVSTAT_TESTMODE_SHIFT  	((uint8_t)    2)

#define FXPS7250_DEVSTAT_SUPPLY_ERR_MASK   	((uint8_t) 0x08)
#define FXPS7250_DEVSTAT_SUPPLY_ERR_SHIFT  	((uint8_t)    3)

#define FXPS7250_DEVSTAT_MEMTEMP_ERR_MASK   ((uint8_t) 0x10)
#define FXPS7250_DEVSTAT_MEMTEMP_ERR_SHIFT  ((uint8_t)    4)

#define FXPS7250_DEVSTAT_COMM_ERR_MASK      ((uint8_t) 0x20)
#define FXPS7250_DEVSTAT_COMM_ERR_SHIFT     ((uint8_t)    5)

#define FXPS7250_DEVSTAT_DSP_ERR_MASK      	((uint8_t) 0x80)
#define FXPS7250_DEVSTAT_DSP_ERR_SHIFT     	((uint8_t)    7)


/*
** DEVSTAT - Bit field value definitions
*/
#define FXPS7250_DEVSTAT_DEVINIT_INIT     			((uint8_t) 0x01)  /*  Indicates if the device is initializing.				*/
#define FXPS7250_DEVSTAT_DEVINIT_NOT_INIT     		((uint8_t) 0x00)  /*  Device is operating normally.							*/
#define FXPS7250_DEVSTAT_DEVRES_RESET        		((uint8_t) 0x02)  /*  Indicates if the device has reset.                   	*/
#define FXPS7250_DEVSTAT_DEVRES_NOT_RESET        	((uint8_t) 0x00)  /*  Device is operating normally.                   		*/
#define FXPS7250_DEVSTAT_TESTMODE_ISACTIVE	        ((uint8_t) 0x04)  /*  Indicates if the device is in test mode.			   	*/
#define FXPS7250_DEVSTAT_TESTMODE_INACTIVE	        ((uint8_t) 0x00)  /*  Test mode is not active.								*/
#define FXPS7250_DEVSTAT_SUPPLY_ERR					((uint8_t) 0x08)  /*  Indicates if an error is flagged in DEVSTAT1.        	*/
#define FXPS7250_DEVSTAT_NOT_SUPPLY_ERR				((uint8_t) 0x00)  /*  No error is flagged in DEVSTAT1.						*/
#define FXPS7250_DEVSTAT_MEMTEMP_ERR				((uint8_t) 0x10)  /*  Indicates if an error is flagged in DEVSTAT2.        	*/
#define FXPS7250_DEVSTAT_NOT_MEMTEMP_ERR			((uint8_t) 0x00)  /*  No error is flagged in DEVSTAT2.        				*/
#define FXPS7250_DEVSTAT_COMM_ERR	         		((uint8_t) 0x20)  /*  Indicates if an error is flagged in DEVSTAT3.        	*/
#define FXPS7250_DEVSTAT_NOT_COMM_ERR	         	((uint8_t) 0x00)  /*  No error is flagged in DEVSTAT3.        				*/
#define FXPS7250_DEVSTAT_DSP_ERR		     		((uint8_t) 0x80)  /*  Indicates if an error is flagged in the pressure DSP.	*/
#define FXPS7250_DEVSTAT_NOT_DSP_ERR		     	((uint8_t) 0x00)  /*  No error is flagged in the pressure DSP.				*/

/*--------------------------------
** Register: SNSDATA0_L
** Enum: FXPS7250_SNSDATA0_L
** --
** Offset : 0x62 - 8 LSBs of 16-bit Sensor Data #0 Registers.
** ------------------------------*/
typedef uint8_t FXPS7250_SNSDATA0_L_t;


/*--------------------------------
** Register: SNSDATA0_H
** Enum: FXPS7250_SNSDATA0_H
** --
** Offset : 0x63 - 8 MSBs of 16-bit Sensor Data #0 Registers.
** ------------------------------*/
typedef uint8_t FXPS7250_SNSDATA0_H_t;

/*--------------------------------
** Register: SNSDATA1_L
** Enum: FXPS7250_SNSDATA1_L
** --
** Offset : 0x64 - 8 LSBs of 16-bit Sensor Data #1 Registers.
** ------------------------------*/
typedef uint8_t FXPS7250_SNSDATA1_L_t;


/*--------------------------------
** Register: SNSDATA1_H
** Enum: FXPS7250_SNSDATA1_H
** --
** Offset : 0x65 - 8 MSBs of 16-bit Sensor Data #1 Registers.
** ------------------------------*/
typedef uint8_t FXPS7250_SNSDATA1_H_t;

/*--------------------------------
** Register: SNSDATA0_TIME0
** Enum: FXPS7250_SNSDATA0_TIME0
** --
** Offset : 0x66 - First 8 bits of 48-bit Sensor Data Time Stamp Register.
** ------------------------------*/
typedef uint8_t FXPS7250_SNSDATA_TIME0_t;

/*--------------------------------
** Register: SNSDATA0_TIME1
** Enum: FXPS7250_SNSDATA0_TIME1
** --
** Offset : 0x67 - Second 8 bits of 48-bit Sensor Data 0 Time Stamp Register.
** ------------------------------*/
typedef uint8_t FXPS7250_SNSDATA_TIME1_t;

/*--------------------------------
** Register: SNSDATA0_TIME2
** Enum: FXPS7250_SNSDATA0_TIME2
** --
** Offset : 0x68 - Third 8 bits of 48-bit Sensor Data Time Stamp Register.
** ------------------------------*/
typedef uint8_t FXPS7250_SNSDATA_TIME2_t;

/*--------------------------------
** Register: SNSDATA0_TIME3
** Enum: FXPS7250_SNSDATA0_TIME3
** --
** Offset : 0x69 - Fourth 8 bits of 48-bit Sensor Data Time Stamp Register.
** ------------------------------*/
typedef uint8_t FXPS7250_SNSDATA_TIME3_t;

/*--------------------------------
** Register: SNSDATA0_TIME4
** Enum: FXPS7250_SNSDATA0_TIME4
** --
** Offset : 0x6A - Fifth 8 bits of 48-bit Sensor Data Time Stamp Register.
** ------------------------------*/
typedef uint8_t FXPS7250_SNSDATA_TIME4_t;

/*--------------------------------
** Register: SNSDATA0_TIME5
** Enum: FXPS7250_SNSDATA0_TIME5
** --
** Offset : 0x6B - Sixth 8 bits of 48-bit Sensor Data Time Stamp Register.
** ------------------------------*/
typedef uint8_t FXPS7250_SNSDATA_TIME5_t;

/*--------------------------------
** Register: P_MAX_L
** Enum: FXPS7250_P_MAX_L
** --
** Offset : 0x6C - 8 LSBs of 16-bit Maximum Absolute Pressure Value Register.
** ------------------------------*/
typedef uint8_t FXPS7250_P_MAX_L_t;

/*--------------------------------
** Register: P_MAX_H
** Enum: FXPS7250_P_MAX_H
** --
** Offset : 0x6D - 8 MSBs of 16-bit Maximum Absolute Pressure Value Register.
** ------------------------------*/
typedef uint8_t FXPS7250_P_MAX_H_t;

/*--------------------------------
** Register: P_MIN_L
** Enum: FXPS7250_P_MIN_L
** --
** Offset : 0x6E - 8 LSBs of 16-bit Minimum Absolute Pressure Value Register.
** ------------------------------*/
typedef uint8_t FXPS7250_P_MIN_L_t;

/*--------------------------------
** Register: P_MIN_L
** Enum: FXPS7250_P_MIN_L
** --
** Offset : 0x6F - 8 MSBs of 16-bit Minimum Absolute Pressure Value Register.
** ------------------------------*/
typedef uint8_t FXPS7250_P_MIN_H_t;

/*--------------------------------
** Register: FRT0
** Enum: FXPS7250_FRT0
** --
** Offset : 0x78 - First 8 bits of 48-bit Free Running Timer Register.
** ------------------------------*/
typedef uint8_t FXPS7250_FRT0_t;

/*--------------------------------
** Register: FRT1
** Enum: FXPS7250_FRT1
** --
** Offset : 0x79 - Second 8 bits of 48-bit Free Running Timer Register.
** ------------------------------*/
typedef uint8_t FXPS7250_FRT1_t;

/*--------------------------------
** Register: FRT2
** Enum: FXPS7250_FRT2
** --
** Offset : 0x7A - Third 8 bits of 48-bit Free Running Timer Register.
** ------------------------------*/
typedef uint8_t FXPS7250_FRT2_t;

/*--------------------------------
** Register: FRT3
** Enum: FXPS7250_FRT3
** --
** Offset : 0x7B - Fourth 8 bits of 48-bit Free Running Timer Register.
** ------------------------------*/
typedef uint8_t FXPS7250_FRT3_t;

/*--------------------------------
** Register: FRT4
** Enum: FXPS7250_FRT4
** --
** Offset : 0x7C - Fifth 8 bits of 48-bit Free Running Timer Register.
** ------------------------------*/
typedef uint8_t FXPS7250_FRT4_t;

/*--------------------------------
** Register: FRT5
** Enum: FXPS7250_FRT5
** --
** Offset : 0x7D - Sixth 8 bits of 48-bit Free Running Timer Register.
** ------------------------------*/
typedef uint8_t FXPS7250_FRT5_t;

/*--------------------------------
** Register: ICTYPEID
** Enum: FXPS7250_ICTYPEID
** --
** Offset : 0xC0 - Contains IC type ID.
** ------------------------------*/
typedef uint8_t FXPS7250_ICTYPEID_t;

/*--------------------------------
** Register: ICREVID
** Enum: FXPS7250_ICREVID
** --
** Offset : 0xC1 - Contains IC revision ID.
** ------------------------------*/
typedef uint8_t FXPS7250_ICREVID_t;

/*--------------------------------
** Register: ICMFGID
** Enum: FXPS7250_ICMFGID
** --
** Offset : 0xC2 - Identifies NXP as the IC Manufacturer.
** ------------------------------*/
typedef uint8_t FXPS7250_ICMFGID_t;

/*--------------------------------
** Register: PN0
** Enum: FXPS7250_PN0
** --
** Offset : 0xC4 - Contains 8 MSB's out of 16-bits that represent the numeric portion of the device ID.
** ------------------------------*/
typedef uint8_t FXPS7250_PN0_t;

/*--------------------------------
** Register: PN1
** Enum: FXPS7250_PN1
** --
** Offset : 0xC5 - Contains 8 LSB's out of 16-bits that represent the numeric portion of the device ID.
** ------------------------------*/
typedef uint8_t FXPS7250_PN1_t;

/*--------------------------------
** Register: SN0
** Enum: FXPS7250_SN0
** --
** Offset : 0xC6 - Contains the first set of 8 bits out of 40-bits that represent the device serial number.
** ------------------------------*/
typedef uint8_t FXPS7250_SN0_t;

/*--------------------------------
** Register: SN1
** Enum: FXPS7250_SN1
** --
** Offset : 0xC7 - Contains the second set of 8 bits out of 40-bits that represent the device serial number.
** ------------------------------*/
typedef uint8_t FXPS7250_SN1_t;

/*--------------------------------
** Register: SN2
** Enum: FXPS7250_SN2
** --
** Offset : 0xC8 - Contains the third set of 8 bits out of 40-bits that represent the device serial number.
** ------------------------------*/
typedef uint8_t FXPS7250_SN2_t;

/*--------------------------------
** Register: SN3
** Enum: FXPS7250_SN3
** --
** Offset : 0xC9 - Contains the fourth set of 8 bits out of 40-bits that represent the device serial number.
** ------------------------------*/
typedef uint8_t FXPS7250_SN3_t;

/*--------------------------------
** Register: SN4
** Enum: FXPS7250_SN4
** --
** Offset : 0xCA - Contains the fifth set of 8 bits out of 40-bits that represent the device serial number.
** ------------------------------*/
typedef uint8_t FXPS7250_SN4_t;

/*--------------------------------
** Register: ASICWFR#
** Enum: FXPS7250_ASICWFR
** --
** Offset : 0xCB - Contains the device wafer ASIC number.
** ------------------------------*/
typedef uint8_t FXPS7250_ASICWFR_t;

/*--------------------------------
** Register: ASICWFR_X
** Enum: FXPS7250_ASICWFR_X
** --
** Offset : 0xCC - Contains the x coordinates for the device ASIC.
** ------------------------------*/
typedef uint8_t FXPS7250_ASICWFR_X_t;

/*--------------------------------
** Register: ASICWFR_Y
** Enum: FXPS7250_ASICWFR_Y
** --
** Offset : 0xCD - Contains the Y coordinates for the device ASIC.
** ------------------------------*/
typedef uint8_t FXPS7250_ASICWFR_Y_t;

/*--------------------------------
** Register: ASICWLOT_L
** Enum: FXPS7250_ASICWLOT_L
** --
** Offset : 0xD0 - Contains 8 LSB's of the device wafer ASIC lot number.
** ------------------------------*/
typedef uint8_t FXPS7250_ASICWLOT_L_t;

/*--------------------------------
** Register: ASICWLOT_H
** Enum: FXPS7250_ASICWLOT_H
** --
** Offset : 0xD1 - Contains 8 MSB's of the device wafer ASIC lot number.
** ------------------------------*/
typedef uint8_t FXPS7250_ASICWLOT_H_t;

/*--------------------------------
** Register: TRNS1WFR_X
** Enum: FXPS7250_TRNS1WFR_X
** --
** Offset : 0xD2 - Contains the x coordinates for the device wafer transducer.
** ------------------------------*/
typedef uint8_t FXPS7250_TRNS1WFR_X_t;

/*--------------------------------
** Register: TRNS1WFR_Y
** Enum: FXPS7250_TRNS1WFR_Y
** --
** Offset : 0xD3 - Contains the y coordinates for the device wafer transducer.
** ------------------------------*/
typedef uint8_t FXPS7250_TRNS1WFR_Y_t;

/*--------------------------------
** Register: TRNS1LOT_L
** Enum: FXPS7250_TRNS1LOT_L
** --
** Offset : 0xD4 - Contains 8 LSB's of the device transducer lot number.
** ------------------------------*/
typedef uint8_t FXPS7250_TRNS1LOT_L_t;

/*--------------------------------
** Register: TRNS1LOT_H
** Enum: FXPS7250_TRNS1LOT_H
** --
** Offset : 0xD5 - Contains 8 MSB's of the device transducer lot number.
** ------------------------------*/
typedef uint8_t FXPS7250_TRNS1LOT_H_t;

#endif  /* FXPS7250_H_ */
