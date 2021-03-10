/*
 * Copyright  2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef TFA2_DEV_H_
#define TFA2_DEV_H_

#ifdef __KERNEL__

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/ctype.h>
#include <asm/unaligned.h>

#else

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "stddef.h"
#include "config.h"

#if !defined(kmalloc) || !defined(kfree)
#define kmalloc(ptr, flags)       malloc(ptr)
#define kfree(ptr)                free(ptr)
#define GFP_KERNEL                0
#define msleep_interruptible(val) usleep(1000 * val)
#endif

#define le16_to_cpu(a)   (a)

typedef enum log_level
{
    LOG_NONE,
    LOG_ERR,
    LOG_WARN,
    LOG_INFO,
    LOG_DEBUG,
} log_level_t;

/*
    map kernel dev_* logging functions to user space
    - dev pointer is used point to idx
*/
#define dev_err(I, ...)  tfaprintf(LOG_ERR, I, __VA_ARGS__)
#define dev_warn(I, ...) tfaprintf(LOG_WARN, I, __VA_ARGS__)
#define dev_info(I, ...) tfaprintf(LOG_INFO, I, __VA_ARGS__)
#define dev_dbg(I, ...)  tfaprintf(LOG_DEBUG, I, __VA_ARGS__)

/*
    map kernel pr_* logging functions to user space
    - no dev pointer available, make it NULL
*/
#define pr_err(...)      dev_err(NULL, __VA_ARGS__)
#define pr_warn(...)     dev_warn(NULL, __VA_ARGS__)
#define pr_info(...)     dev_info(NULL, __VA_ARGS__)
#define pr_debug(...)    dev_dbg(NULL, __VA_ARGS__)

struct i2c_client
{
    int addr;  /*!< I2C slave addres */
    void *hal; /*!< Device HAL plugin handle */
    int dev;   /*!< used for user mode print, store idx */
};

#endif

#include "tfa9xxx_parameters.h"
#include "tfa_haptic_fw_defs.h"

/*
 * these are the locally defined bitfields
 */
typedef enum tfa9xxx_core_bf
{
    TFA9XXX_BF_AMPE       = 0x0030, /*!< Enable Amplifier                                   */
    TFA9XXX_BF_AMPC       = 0x0060, /*!< CoolFlux control over amplifier                    */
    TFA9XXX_BF_ACKCMD     = 0x9380, /*!< Firmware event acknowledge rpc command             */
    TFA9XXX_BF_ACS        = 0x1090, /*!< Cold Start                                         */
    TFA9XXX_BF_CFE        = 0x0020, /*!< Enable CoolFlux DSP                                */
    TFA9XXX_BF_CFINT      = 0x9040, /*!< Coolflux Interrupt - auto clear                    */
    TFA9XXX_BF_CFSM       = 0x5130, /*!< Coolflux firmware soft mute control                */
    TFA9XXX_BF_VDDS       = 0x1000, /*!< POR                                                */
    TFA9XXX_BF_OTDS       = 0x1020, /*!< OTP alarm                                          */
    TFA9XXX_BF_OVDS       = 0x1030, /*!< OVP alarm                                          */
    TFA9XXX_BF_UVDS       = 0x1040, /*!< UVP alarm                                          */
    TFA9XXX_BF_CLKS       = 0x1060, /*!< Clocks stable                                      */
    TFA9XXX_BF_MTPB       = 0x1070, /*!< MTP busy                                           */
    TFA9XXX_BF_NOCLK      = 0x1080, /*!< Lost clock                                         */
    TFA9XXX_BF_WDS        = 0x10a0, /*!< Watchdog                                           */
    TFA9XXX_BF_SPKS       = 0x1170, /*!< Speaker status                                     */
    TFA9XXX_BF_TDMERR     = 0x11a0, /*!< TDM error                                          */
    TFA9XXX_BF_TDMLUTER   = 0x11b0, /*!< TDM lookup table error                             */
    TFA9XXX_BF_DMEM       = 0x9011, /*!< Target memory for CFMA using I2C interface         */
    TFA9XXX_BF_I2CR       = 0x0010, /*!< I2C Reset - Auto clear                             */
    TFA9XXX_BF_ICLVDDS    = 0x4400, /*!< Clear POR                                          */
    TFA9XXX_BF_IPOVDDS    = 0x4c00, /*!< Polarity POR                                       */
    TFA9XXX_BF_ISTVDDS    = 0x4000, /*!< Status POR                                         */
    TFA9XXX_BF_VOL        = 0x5187, /*!< CF firmware volume control                         */
    TFA9XXX_BF_MANSCONF   = 0x0120, /*!< Device I2C settings configured                     */
    TFA9XXX_BF_MANCOLD    = 0x130,  /*!< Execute cold start                                , */
    TFA9XXX_BF_MANSTATE   = 0x1433, /*!< Device Manager status                              */
    TFA9XXX_BF_OPENMTP    = 0x01e0, /*!< Control for FAIM protection                        */
    TFA9XXX_BF_PWDN       = 0x0000, /*!< Powerdown control                                  */
    TFA9XXX_BF_REQCMD     = 0x9080, /*!< Firmware event request rpc command                 */
    TFA9XXX_BF_ACKCAL     = 0x93e0, /*!< Firmware event acknowledge calibration completed   */
    TFA9XXX_BF_REV        = 0x030f, /*!< Revision info                                      */
    TFA9XXX_BF_MANAOOSC   = 0x460,  /*!< Internal OSC1M off at PWDN                        , */
    TFA9XXX_BF_RST        = 0x9000, /*!< Reset for Coolflux DSP                             */
    TFA9XXX_BF_SBSL       = 0x0050, /*!< Coolflux configured                                */
    TFA9XXX_BF_LPM1MODE   = 0x5ac1, /*!< Low power mode control                              */
    TFA9XXX_BF_MTPK       = 0xa107, /*!< KEY2 to access KEY2 protected registers, customer key */
    TFA9XXX_BF_TROS       = 0xb190, /*!< Select temp Speaker calibration                    */
    TFA9XXX_BF_EXTTS      = 0xb108, /*!< External temperature (C)                           */
    TFA9XXX_BF_SWPROFIL   = 0xe00f, /*!< Software profile data                              */
    TFA9XXX_BF_SWVSTEP    = 0xe10f, /*!< Software vstep information                         */
    TFA9XXX_BF_MTPADDR    = 0xa302, /*!< MTP address for read/writing mtp in manual single word mode, */
    TFA9XXX_BF_KEY1LOCKED = 0xa200, /*!< Indicates KEY1 is locked                           */
    TFA9XXX_BF_KEY2LOCKED = 0xa210, /*!< Indicates KEY2 is locked */
    TFA9XXX_BF_MANCMTPI   = 0xa330, /*!< Start copying single word from MTP to I2C mtp register - auto clear  */
    TFA9XXX_BF_MANCIMTP   = 0xa340, /*!< Start copying single word from I2C mtp register to mtp - auto clear  */
    TFA9XXX_BF_CMTPI      = 0xa350, /*!< Start copying all the data from mtp to I2C mtp registers - auto clear */
    // forbidden TFA9XXX_BF_CIMTP = 0xa360,    /*!< Start copying data from I2C mtp registers to mtp - auto clear */
    TFA9XXX_BF_MTPRDMSB = 0xa50f, /*!< MSB word of MTP manual read data                   */
    TFA9XXX_BF_MTPRDLSB = 0xa60f, /*!< LSB word of MTP manual read data                   */
    TFA9XXX_BF_MTPWRMSB = 0xa70f, /*!< MSB word of MTP manual write data                   */
    TFA9XXX_BF_MTPWRLSB = 0xa80f, /*!< LSB word of MTP manual write data                   */
    TFA9XXX_BF_CUSTINFO =
        0xf078, /*!< TODO fix dev specific  Reserved space for allowing customer to store speaker information */
    TFA9XXX_BF_MTPOTC = 0xf000, /*!< Calibration schedule                               */
    TFA9XXX_BF_MTPEX  = 0xf010, /*!< Calibration Ron executed                           */
    TFA9XXX_BF_R25C   = 0xf50f, /*!< Ron resistance of speaker coil                     */
} tfa9xxx_core_bf_t;

/* TODO haptic profile names */
#define HB_LRA_MAIN       "lra_main.hap"
#define HB_LRA_DATA       "lra_data.hap"
#define HB_LRA_RECALC     "lra_recalculation.hap"
#define HB_RECALC_PROFILE "lra_recalculation.hap"

/* return true if in TFA range */
#define IS_I2C_TFA(slave) ((0x30 < slave) || (slave > 0x37))

enum tfa9xxx_Status_ID
{
    tfa9xxx_no_dsp_response      = -1, /* No response from DSP */
    tfa9xxx_I2C_Req_Done         = 0,  /* Request executed correctly and result, if any, is available for download */
    tfa9xxx_I2C_Req_Busy         = 1,  /* Request is being processed, just wait for result */
    tfa9xxx_I2C_Req_Invalid_M_ID = 2,  /* Provided M-ID does not fit in valid rang [0..2] */
    tfa9xxx_I2C_Req_Invalid_P_ID = 3,  /* Provided P-ID is not valid in the given M-ID context */
    tfa9xxx_I2C_Req_Invalid_CC   = 4,  /* Invalid channel configuration bits (SC|DS|DP|DC) combination */
    tfa9xxx_I2C_Req_Invalid_Seq =
        5, /* Invalid sequence of commands, in case the DSP expects some commands in a specific order */
    tfa9xxx_I2C_Req_Invalid_Param = 6, /* Generic error */
    tfa9xxx_I2C_Req_Buffer_Overflow =
        7, /* I2C buffer has overflowed: host has sent too many parameters, memory integrity is not guaranteed */
    tfa9xxx_I2C_Req_Calib_Busy   = 8, /* Calibration not finished */
    tfa9xxx_I2C_Req_Calib_Failed = 9  /* Calibration failed */
};

/**
 * Device states and modifier flags to allow a device/type independent fine
 * grained control of the internal state.
 * Values below 0x10 are referred to as base states which can be or-ed with
 * state modifiers, from 0x10 and higher.
 *
 */
enum tfa_state
{
    TFA_STATE_NONE,             /**< not requested, unknown or invalid */
    TFA_STATE_POWERDOWN,        /**< PLL in powerdown, Algo is up/warm */
    TFA_STATE_POWERUP,          /**< PLL to powerup, Algo can be up/warm */
    TFA_STATE_OPERATING,        /**< Amp and Algo running */
    TFA_STATE_RESET,            /**< I2C reset and ACS set */
    TFA_STATE_INIT_CF,          /**< coolflux HW access possible (~initcf) */
    TFA_STATE_OSC,              /**< internal oscillator */
    TFA_STATE_CLOCK,            /**< always return with clock, use OSC if no external clock  */
    TFA_STATE_POWERDOWN_HAPTIC, /**< PLL in powerdown, skip mute sequence */
    /* --sticky state modifiers-- */
    TFA_STATE_MUTE   = 0x10, /**< Algo & Amp mute */
    TFA_STATE_UNMUTE = 0x20  /**< Algo & Amp unmute */
};

/**
 * HB1.5 roles depend on what is expected to be connected or
 * only audio. This is derived from the container profiles
 */
#define TFA_HB_ROLE_MASK (7) /* use this mask to get lra or ls role */
enum tfa_hb_role
{
    tfa_hb_undetermined = -1, /**< not initialized */
    tfa_hb_none         = 0,  /**< no haptic boost */
    tfa_hb_lra,               /**< LRA expected */
    tfa_hb_ls,                /**< loudspeaker expected */
    tfa_hb_ready = (1 << 3)   /**< ready flag when config is loaded */
};

/*
 * haptic sequencer definition
 */
struct tfa2_sequence
{
    int32_t length;
    int32_t *object;
    int32_t *duration;
    int32_t *level;
    int32_t *freq;
    int total_duration;
    int object_table1_cache_save[FW_XMEM_NR_OBJECTS1][FW_XMEM_OBJECTSIZE];
    int object_table2_cache_save[FW_XMEM_NR_OBJECTS2][FW_XMEM_OBJECTSIZE];
};

struct haptic_data
{
    int index;     /* selected object */
    int frequency; /* frequency, valid if non-0 */
    int amplitude; /* level, strength of signal 0-100% */
    int duration;  /* time in milliseconds */

    int recalc_play_object; /* run boot obj in recalculation */
    int use_bck;
    int object_table1_cache[FW_XMEM_NR_OBJECTS1][FW_XMEM_OBJECTSIZE];
    int object_table2_cache[FW_XMEM_NR_OBJECTS2][FW_XMEM_OBJECTSIZE];
    int delay_attack; /* delay in milliseconds  between object trigger and object execution */

    int seq_max; /* total nr of sequencer virtual objects */
    struct tfa2_sequence seq;
};

enum tfa9xxx_DAI
{
    Tfa9xxx_DAI_NONE      = 0x0,  /**< Unknown  */
    Tfa9xxx_DAI_I2S       = 0x01, /**< I2S only */
    Tfa9xxx_DAI_TDM       = 0x02, /**< TDM, I2S */
    Tfa9xxx_DAI_PDM       = 0x04, /**< PDM  */
    Tfa9xxx_DAI_SOUNDWIRE = 0x08, /**< SOUNDWIRE  */
};

/**
 * This is the main tfa device context structure, it will carry all information
 * that is needed to handle a single I2C device instance.
 * All functions dealing with the device will need access to the fields herein.
 */
struct tfa2_device
{
    struct i2c_client *i2c;
    int dev_idx; /**< device container index */
    int in_use;
    int buffer_size;                 /**< lowest level max buffer size */
                                     //	int has_msg; 			/**< support direct dsp messaging */
    short slave_address;             /**< I2C slave address (not shifted) */
    uint16_t rev;                    /**< full revid of this device */
    int need_hw_init;                /**< hardware parameters not initialized */
    int need_cf_init;                /**< CoolFlux not configured/patched */
    int need_sb_config;              /**< SB firmware parameters not configured */
    enum tfa_hb_role need_hb_config; /**< HB firmware parameters needed */
                                     //	unsigned char tfa_family; /**< tfa1/tfa2 */
                                     //	enum featureSupport supportDrc;
                                     //	enum featureSupport supportFramework;
                                     //	enum featureSupport support_saam;
    int sw_feature_bits[2];          /**< cached copy of sw feature bits */
    int hw_feature_bits;             /**< cached copy of hw feature bits */
    int profile;                     /**< active profile */
    int vstep;                       /**< active vstep */
                                     //	unsigned char spkr_count;
                                     //	unsigned char spkr_select;
                                     //	unsigned char support_tcoef;/**< legacy tfa9887, will be removed */
    enum tfa9xxx_DAI daimap;         /**< supported audio interface types */
                                     //	int mohm; /**< speaker calibration value in milli ohms -1 is error */
                                     //	struct tfa2_device_ops dev_ops;
    uint16_t interrupt_enable[3];
    uint16_t interrupt_status[3];
    //	int ext_dsp; /**< respond to external DSP: -1:none, 0:no_dsp, 1:cold, 2:warm */
    int bus;                     /* logical bus, i2c bus is  in i2c_client */
    int tfadsp_event;            /**< enum tfadsp_event_en is for external registry */
    int verbose;                 /**< verbosity level for debug print output */
    enum tfa_state state;        /**< last known state or-ed with optional state_modifier */
    struct nxpTfaContainer *cnt; /**< the loaded container file */
    //	struct nxpTfaVolumeStepRegisterInfo *p_regInfo; /**< remember vstep for partial updates */
    int partial_enable;       /**< enable partial updates */
    void *data;               /**< typically pointing to Linux driver structure owning this device */
    int convert_dsp32;        /**< convert 24 bit DSP messages to 32 bit */
                              //	int sync_iv_delay; /**< synchronize I/V delay at cold start */
    int is_probus_device;     /**< probus device: device without internal DSP */
    int is_extern_dsp_device; /**< externel (non Coolflux) DSP device */
                              //	int needs_reset; /**< add the reset trigger for SetAlgoParams and SetMBDrc commands */
                              //	struct kmem_cache *cachep;	/**< Memory allocator handle */
                              //	struct tfa_hal_dev *hal;  /* Device HAL plugin handle >>>> moved to i2c_client */
    int reg_time;             /* worst case register read time in usec, for adding extra clock read delay */
    /* function pointer for per-device overloading */
    int (*tfa_init)(struct tfa2_device *tfa); /**< init for POR fixes like loading optimal settings */
    uint16_t bf_clks;                         /**<     TFA9XXX_BF_CLKS   Clocks stable for overload   */
    uint16_t bf_manstate;                     /**< TFA9XXX_BF_MANSTATE Device Manager status for overload */
    uint16_t bf_manaoosc;                     /**< TFA9XXX_BF_MANAOOSC overload */
    uint16_t bf_noclk;                        /**< TFA9XXX_BF_NOCLK overload */
    uint16_t bf_mtpb;                         /**< TFA9XXX_BF_MTPB overload */
    uint16_t bf_swprofil;                     /**< TFA9XXX_BF_SWPROFIL overload */
    uint16_t bf_swvstep;                      /**< TFA9XXX_BF_SWVSTEP overload */
    uint16_t bf_openmtp;                      /**< TFA9XXX_BF_OPENMTP overload */
    uint16_t bf_lpm1mode;                     /**<  TFA9XXX_BF_LPM1MODE overload */
    uint16_t bf_r25c;                         /**<  TFA9XXX_BF_R25C overload */
    uint16_t status_mask[4];                  /**< status masks for tfa2_dev_status() */
    uint16_t status_err[4];                   /**< error status for tfa2_dev_status() */
    struct haptic_data hap_data;              /**< haptic specific data */
    int (*dsp_init)(struct tfa2_device *tfa, const char *cmd_buf, size_t cmd_len);
    int (*dsp_execute)(struct tfa2_device *tfa, const char *cmd_buf, size_t cmd_len, char *res_buf, size_t res_len);
};

#pragma pack(push, 1)
struct tfa_patch_header
{
    /* Generic Header */
    uint16_t id;        /* PA */
    char version[2];    /* 1_ */
    char subversion[2]; /* 00 */
    uint16_t size;
    uint32_t crc;
    char customer[8];
    char application[8];
    char type[8];

    /* Patch Header */
    uint8_t rev;       /* 0x94 */
    uint16_t address;  /* 0xffff */
    uint16_t dev_type; /* 0x9914 */
    uint8_t msb_rev;   /* 0x1a */
};
#pragma pack(pop)

#define PATCH_HEADER_SIZE sizeof(struct tfa_patch_header)

/**
 *  @brief convert 24 bit BE DSP messages to a 32 bit signed LE integer
 *
 *  The input is sign extended to 32-bit from 24-bit.
 *
 *  @param data32 output 32 bit signed LE integer buffer
 *  @param data24 input 24 bit BE buffer
 *  @param length_bytes24 bytes in 24 bit BE buffer
 *  @return total nr of bytes in the result
 */
int tfa2_24_to_32(int32_t *data32, uint8_t *data24, int length_bytes24);

/**
 *   @brief  truncate 32 bit  integer buffer  to 24 bit BE
 *
 *   The input is truncated by chopping the highest byte.
 *  @param data24 output 24 bit BE buffer
 *  @param data32 input 32 bit signed LE integer buffer
 *  @param length_words32 number of words in 32bit  buffer
 *  @return total nr of bytes in the result
 */
int tfa2_32_to_24(uint8_t *data24, int32_t *data32, int length_words32);

int tfa2_dev_set_state(struct tfa2_device *tfa, enum tfa_state state);

/* generic tfa i2c level driver functions from tfa_haptic.c */
int tfa2_dev_get_revid(struct tfa2_device *tfa);

int tfa2_check_patch(const uint8_t *data, const int length, const uint16_t revid);
/*
 * cold start the calibration profile
 */
int tfa2_calibrate_profile_start(struct tfa2_device *tfa);
int tfa2_sb_calibrate(struct tfa2_device *tfa);
int tfa2_get_calibration_impedance(struct tfa2_device *tfa);

int tfa2_process_patch_file(struct i2c_client *client, int length, const uint8_t *bytes);

enum tfa2_cf_mem
{
    TFA2_CF_MEM_PMEM  = 0,
    TFA2_CF_MEM_XMEM  = 1,
    TFA2_CF_MEM_YMEM  = 2,
    TFA2_CF_MEM_IOMEM = 3,
};

int tfa2_i2c_dsp_init(struct tfa2_device *tfa, const char *cmd_buf, size_t cmd_len);
int tfa2_i2c_dsp_execute(struct tfa2_device *tfa, const char *cmd_buf, size_t cmd_len, char *res_buf, size_t res_len);
int tfa2_i2c_write_cf_mem32(
    struct i2c_client *client, uint16_t address, int32_t *input, int size, enum tfa2_cf_mem type);
int tfa2_i2c_read_cf_mem32(struct i2c_client *client, uint16_t address, int *data, int size, enum tfa2_cf_mem type);
int tfa2_i2c_write_cf_mem32_dsp_reset(
    struct i2c_client *client, uint16_t address, int32_t *input, int size, enum tfa2_cf_mem type);
int tfa2_i2c_read_cf_mem32_dsp_reset(
    struct i2c_client *client, uint16_t address, int *data, int size, enum tfa2_cf_mem type);
int tfa2_i2c_write_cf_mem24(
    struct i2c_client *client, uint16_t address, uint8_t *input, int size, enum tfa2_cf_mem type);
int tfa2_i2c_read_cf_mem24(struct i2c_client *client, uint16_t address, uint8_t *data, int size, enum tfa2_cf_mem type);

int tfa2_i2c_write_bf(struct i2c_client *client, uint16_t bitfield, uint16_t value);
int tfa2_i2c_write_bf_volatile(struct i2c_client *client, uint16_t bitfield, uint16_t value);
int tfa2_i2c_read_bf(struct i2c_client *client, uint16_t bitfield);

/* i2c abstraction provided by driver */
int tfa2_i2c_write_raw(struct i2c_client *client, int len, const uint8_t *data);
int tfa2_i2c_write_read_raw(struct i2c_client *client, int wrlen, uint8_t *wrdata, int rdlen, uint8_t *rddata);

int tfa2_i2c_set_bf_value(const uint16_t bf, const uint16_t bf_value, uint16_t *p_reg_value);
uint16_t tfa2_i2c_get_bf_value(const uint16_t bf, const uint16_t reg_value);

/*** MTP support ***/
enum tfa_mtp
{
    TFA_MTP_OTC,
    TFA_MTP_EX,
    TFA_MTP_R25C,
    TFA_MTP_F0,
    TFA_MTP_OPEN
};
int tfa2_i2c_hap_key2(struct i2c_client *i2c, int lock);

int tfa2_i2c_read_reg(struct i2c_client *client, uint8_t reg);
int tfa2_i2c_write_reg(struct i2c_client *client, uint8_t reg, uint16_t val);
// i2c
int tfa2_dev_mtp_get(struct tfa2_device *tfa, enum tfa_mtp item);
int tfa2_dev_mtp_set(struct tfa2_device *tfa, enum tfa_mtp item, uint16_t value);
int tfa2_i2c_get_revid(struct i2c_client *i2c);
// dsp msg for tfa i2c
int tfa2_i2c_rpc_write(struct i2c_client *i2c, int length, const char *buffer);
// TODO new if
// tfa dev
int tfa2_dev_start(struct tfa2_device *tfa, int next_profile, int vstep);
int tfa2_dev_start_hw(struct tfa2_device *tfa, int profile);
int tfa2_dev_stop(struct tfa2_device *tfa); // TODO
int tfa2_dev_probe(struct tfa2_device *tfa);
int tfa2_set_query_info(struct tfa2_device *tfa);
// device specific ops init
int tfa2_dev_specific(struct tfa2_device *tfa);
int tfa2_dev_clock_stable_wait(struct tfa2_device *tfa);
int tfa2_dev_is_fw_cold(struct tfa2_device *tfa);

int tfa2_get_noclk(struct tfa2_device *tfa);

int tfa2_dev_set_volume(struct tfa2_device *tfa, uint8_t volume);
int tfa2_dev_get_volume(struct tfa2_device *tfa);

// from tfa_service.h
/**
 * Load the default HW settings in the device
 * @param tfa the device struct pointer
 */
int tfa2_dev_init(struct tfa2_device *tfa);
int tfa2_dev_mute(struct tfa2_device *tfa, int state);

// low level, from tfa_init
int tfa2_dev_dsp_system_stable(struct tfa2_device *tfa, int *ready);
int tfa2_dev_faim_protect(struct tfa2_device *tfa, int state);
int tfa2_dev_set_swprofile(struct tfa2_device *tfa, uint16_t new_value);
int tfa2_dev_get_swprofile(struct tfa2_device *tfa);
int tfa2_dev_set_swvstep(struct tfa2_device *tfa, uint16_t new_value);
int tfa2_dev_get_swvstep(struct tfa2_device *tfa);
/* mtp */
int tfa2_dev_mtp_readpair(struct tfa2_device *tfa, uint16_t mtp_address, uint16_t mtp_data[2]);
int tfa2_dev_mtp_read(struct tfa2_device *tfa, uint16_t mtp_address);
int tfa2_dev_mtp_write(struct tfa2_device *tfa, uint16_t mtp_address, uint16_t mtp_value);
void tfa2_i2c_unlock(struct i2c_client *client);

/*
 * poll for the bf until value or loopcount exhaust return timeout
 */
int tfa2_i2c_bf_poll(struct i2c_client *client, uint16_t bf, uint16_t value, int loop);

/*
 * the dsp init function
 */
int tfa2_dsp_init(struct tfa2_device *tfa, const char *cmd_buf, size_t cmd_len);

/*
 * the dsp execute funtion will execute and the RPC message in the cmd_buf and return the result
 */
int tfa2_dsp_execute(struct tfa2_device *tfa, const char *cmd_buf, size_t cmd_len, char *res_buf, size_t res_len);

/**
 * check the state of the DSP coolflux
 * @param tfa the device struct pointer
 * @return the value of CFE
 */
int tfa2_dev_cf_enabled(struct tfa2_device *tfa);

/**
 * start CoolFlux DSP subsystem
 *  this will load the patch witch will implicitly start the DSP
 *   if no patch is available the DSP is started immediately
 * @param tfa the device struct pointer
 */
int tfa2_dev_start_cf(struct tfa2_device *tfa);

/**
 * start DSP firmware
 * start the clocks and wait until the AMP is switching
 * on return the DSP sub system will be ready for loading
 * @param tfa the device struct pointer
 * @param profile the profile that should be loaded on startup
 */
int tfa2_dev_load_config(struct tfa2_device *tfa, int profile);

/**
 * start the maximus speakerboost algorithm
 * this implies a full system startup when the system was not already started
 * @param tfa the device struct pointer
 * @param profile the profile that should be loaded
 */
int tfa2_dev_start_speakerboost(struct tfa2_device *tfa, int profile);

/**
 * Get hw feature bits from container file
 * @param tfa the device struct pointer
 * @param hw_feature_register pointer to where hw features are stored
 */
void tfa2_dev_get_hw_features_from_cnt(struct tfa2_device *tfa, int *hw_feature_register);

/**
 * Get sw feature bits from container file
 * @param tfa the device struct pointer
 * @param sw_feature_register pointer to where sw features are stored
 */
void tfa2_dev_get_sw_features_from_cnt(struct tfa2_device *tfa, int sw_feature_register[2]);

/**
 * patch the ROM code of the DSP
 * @param tfa the device struct pointer
 * @param patchLength the number of bytes of patchBytes
 * @param patchBytes pointer to the bytes to patch
 */
int tfa2_dev_dsp_patch(struct tfa2_device *tfa, int patchLength, const uint8_t *patchBytes);

/*
 * update the struct for hw and fw init fields
 *  if no DSP need_sb_config can be skipped
 */
int tfa2_dev_update_config_init(struct tfa2_device *tfa);

/*
 * firmware RPC calls
 */

int tfa2dsp_fw_get_api_version(struct tfa2_device *tfa, uint8_t *buffer);
int tfa2dsp_fw_get_status_change(struct tfa2_device *tfa, uint8_t *buffer);
int tfa2dsp_fw_get_re25(struct tfa2_device *tfa, uint8_t *buffer);
int tfa2dsp_fw_get_tag(struct tfa2_device *tfa, uint8_t *buffer);

/*
 * set ISTVDDS
 * clear SBSL and ACS (need clock for ACS)
 */
int tfa2_dev_force_cold(struct tfa2_device *tfa);
int tfa2_process_patch_file(struct i2c_client *client, int length, const uint8_t *bytes);
int tfa2_check_patch(const uint8_t *data, const int length, const uint16_t revid);

void tfa2_set_exttemp(struct tfa2_device *tfa, short ext_temp);
short tfa2_get_exttemp(struct tfa2_device *tfa);

int tfa2_dev_mtp_busy(struct tfa2_device *tfa);
int tfa2_dev_mtp_to_i2c(struct tfa2_device *tfa);
int tfa2_dev_mtp_writepair(struct tfa2_device *tfa, uint16_t mtp_address, uint16_t mtp_data[2]);
int tfa2_dev_mtp_write(struct tfa2_device *tfa, uint16_t mtp_address, uint16_t mtp_value);

int tfa2_dev_status(struct tfa2_device *tfa);

/* called during cold start before powering up the device */
int tfa2_init_fix_powerup(struct tfa2_device *tfa);
/* called before powering down the device */
int tfa2_init_fix_powerdown(struct tfa2_device *tfa, int manstate);
/* device specifics for mtp access */
int tfa2_init_mtp_write_wrapper(struct tfa2_device *tfa,
                                uint16_t mtp_address,
                                uint16_t mtp_value,
                                int (*f)(struct tfa2_device *tfa, uint16_t mtp_address, uint16_t mtp_value));
/* called during warm profile switch */
int tfa2_init_fix_initcf(struct tfa2_device *tfa);

#endif /* TFA2_DEV_H_ */
