/*
 * Copyright (c) 2022 ITE.
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_IT6161_H_
#define _FSL_IT6161_H_

#include "fsl_video_common.h"
#include "fsl_video_i2c.h"
#include "fsl_display.h"
#include "fsl_common.h"
#include "mipi_rx.h"
#include "hdmi_tx.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define F_AUDIO_ON       (1U << 7U)
#define F_AUDIO_HBR      (1U << 6U)
#define F_AUDIO_DSD      (1U << 5U)
#define F_AUDIO_NLPCM    (1U << 4U)
#define F_AUDIO_LAYOUT_1 (1U << 3U)
#define F_AUDIO_LAYOUT_0 (0U << 3U)
// HBR - 1100
// DSD - 1010
// NLPCM - 1001
// LPCM - 1000
#define T_AUDIO_MASK  (0xF0)
#define T_AUDIO_OFF   (0U)
#define T_AUDIO_HBR   (F_AUDIO_ON | F_AUDIO_HBR)
#define T_AUDIO_DSD   (F_AUDIO_ON | F_AUDIO_DSD)
#define T_AUDIO_NLPCM (F_AUDIO_ON | F_AUDIO_NLPCM)
#define T_AUDIO_LPCM  (F_AUDIO_ON)

/* Video Data Type */
#define F_MODE_RGB444      (0x00U)
#define F_MODE_YUV422      (0x01U)
#define F_MODE_YUV444      (0x02U)
#define F_MODE_CLRMOD_MASK (0x03U)

#define F_VIDMODE_ITU709 (1U << 4U)
#define F_VIDMODE_ITU601 (0U)

#define F_VIDMODE_0_255  (0U)
#define F_VIDMODE_16_235 (1U << 5U)

#define F_VIDMODE_EN_UDFILT (1U << 6U)
#define F_VIDMODE_EN_DITHER (1U << 7U)

/* sample clock */
#define AUDFS_22p05KHz (0x04U)
#define AUDFS_44p1KHz  (0x00U)
#define AUDFS_88p2KHz  (0x08U)
#define AUDFS_176p4KHz (0x0CU)
#define AUDFS_24KHz    (0x06U)
#define AUDFS_48KHz    (0x02U)
#define AUDFS_96KHz    (0x0AU)
#define AUDFS_192KHz   (0x0EU)
#define AUDFS_768KHz   (0x09U)
#define AUDFS_32KHz    (0x03U)
#define AUDFS_OTHER    (0x01U)

#ifndef BIT
#define BIT(nr) ((0x01U) << (nr))
#endif

#define DEMO_HDMI_RESOLUSION (HDMI_480p60_16x9)
#define DEMO_HDMI_COLOR_MODE (HDMI_RGB444)

#define delay1ms(x) SDK_DelayAtLeastUs((x) * 1000, SystemCoreClock)

#define MIPIRX_LANE_NUM (4) /* 1~4 */

/* I2C Address */
#define HDMI_TX_ADDR               (0x4C)
#define HDMI_TX_CEC_ADDR           (0x4E)
#define HDMI_TX_CEC_I2C_SLAVE_ADDR (0x9C)
#define MIPI_RX_ADDR               (0x6C)

#define IT6161_I2C_ModifyReg(handle, addr, reg, mask, value)                                 \
    VIDEO_I2C_ModifyReg(addr, kVIDEO_RegAddr8Bit, (reg), kVIDEO_RegWidth8Bit, mask, (value), \
                        ((const it6161_resource_t *)((handle)->resource))->i2cReceiveFunc,   \
                        ((const it6161_resource_t *)((handle)->resource))->i2cSendFunc)

#define IT6161_I2C_WriteReg(handle, addr, reg, value)                                 \
    VIDEO_I2C_WriteReg(addr, kVIDEO_RegAddr8Bit, (reg), kVIDEO_RegWidth8Bit, (value), \
                       ((const it6161_resource_t *)((handle)->resource))->i2cSendFunc)

#define IT6161_I2C_WriteRegs(handle, addr, reg, value, len)                          \
    VIDEO_I2C_WriteReg(addr, kVIDEO_RegAddr8Bit, reg, (video_reg_width_t)len, value, \
                       ((const it6161_resource_t *)((handle)->resource))->i2cSendFunc)

#define IT6161_I2C_ReadRegs(handle, addr, reg, value, len)                            \
    VIDEO_I2C_ReadReg(addr, kVIDEO_RegAddr8Bit, reg, (video_reg_width_t)len, (value), \
                      ((const it6161_resource_t *)((handle)->resource))->i2cReceiveFunc)

#define HDMITX_ReadI2C_Byte(handle, RegAddr, pValue) IT6161_I2C_ReadRegs(handle, HDMI_TX_ADDR, RegAddr, pValue, 1)
#define HDMITX_WriteI2C_Byte(handle, RegAddr, value) IT6161_I2C_WriteReg(handle, HDMI_TX_ADDR, RegAddr, value)
#define HDMITX_ReadI2C_Bytes(handle, RegAddr, pValue, num) \
    IT6161_I2C_ReadRegs(handle, HDMI_TX_ADDR, RegAddr, pValue, num)
#define HDMITX_WriteI2C_Bytes(handle, RegAddr, pValue, num) \
    IT6161_I2C_WriteRegs(handle, HDMI_TX_ADDR, RegAddr, pValue, num)
#define HDMITX_SetI2C_Byte(handle, RegAddr, Mask, Value) \
    IT6161_I2C_ModifyReg(handle, HDMI_TX_ADDR, RegAddr, Mask, Value)

#define HDMITX_CEC_ReadI2C_Byte(handle, RegAddr, pValue) \
    IT6161_I2C_ReadRegs(handle, HDMI_TX_CEC_ADDR, RegAddr, pValue, 1)
#define HDMITX_CEC_WriteI2C_Byte(handle, RegAddr, value) IT6161_I2C_WriteReg(handle, HDMI_TX_CEC_ADDR, RegAddr, value)
#define HDMITX_CEC_ReadI2C_Bytes(handle, RegAddr, pValue, num) \
    IT6161_I2C_ReadRegs(handle, HDMI_TX_CEC_ADDR, RegAddr, pValue, num)
#define HDMITX_CEC_WriteI2C_Bytes(handle, RegAddr, pValue, num) \
    IT6161_I2C_WriteRegs(handle, HDMI_TX_CEC_ADDR, RegAddr, pValue, num)
#define HDMITX_CEC_SetI2C_Byte(handle, RegAddr, Mask, Value) \
    IT6161_I2C_ModifyReg(handle, HDMI_TX_CEC_ADDR, RegAddr, Mask, Value)

#define MIPIRX_ReadI2C_Byte(handle, RegAddr, pValue) IT6161_I2C_ReadRegs(handle, MIPI_RX_ADDR, RegAddr, pValue, 1)
#define MIPIRX_WriteI2C_Byte(handle, RegAddr, value) IT6161_I2C_WriteReg(handle, MIPI_RX_ADDR, RegAddr, value)
#define MIPIRX_ReadI2C_Bytes(handle, RegAddr, pValue, num) \
    IT6161_I2C_ReadRegs(handle, MIPI_RX_ADDR, RegAddr, pValue, num)
#define MIPIRX_SetI2C_Byte(handle, RegAddr, Mask, Value) \
    IT6161_I2C_ModifyReg(handle, MIPI_RX_ADDR, RegAddr, Mask, Value)

/*!
 * @brief IT6161 resource.
 *
 * The I2C instance should be initialized before calling @ref IT6161_Init.
 */

/* ported from linu kernel: include/drm/drm_modes.h(struct drm_display_mode) */
typedef struct display_mode
{
    uint16_t hdisplay;    /* horizontal display size */
    uint16_t hsync_start; /* horizontal sync start */
    uint16_t hsync_end;   /* horizontal sync end */
    uint16_t htotal;      /* horizontal total size */
    uint16_t vdisplay;    /* vertical display size */
    uint16_t vsync_start; /* vertical sync start */
    uint16_t vsync_end;   /* vertical sync end */
    uint16_t vtotal;      /* vertical total size */
} display_mode_t;

typedef struct it6161_hdmi_tx_cfg
{
    uint8_t hdmitx_bypass_mode;
    uint8_t tx_clk_stable;
    uint8_t tx_vid_stable;
    uint8_t de_generation_enable;
    uint8_t vertical_sync_polarity;
    uint8_t horizontal_sync_polarity;
    uint8_t de_only_in;
    uint32_t rclk;
    uint32_t pclk;
    uint8_t input_color_space;
    uint8_t output_color_space;
    uint8_t support_audio;
    uint8_t input_audio_type;
    uint8_t input_audio_interface;
    uint32_t input_audio_sample_freq;
    uint8_t output_channel;
    uint8_t hdmi_mode;
    uint8_t bAudioChannelEnable;
    bool pclk_div2; /* Input Data Format Register 0x70, Reg_PCLKDiv2, 0: IO latch clock = TxCLK, 1: IO latch clock = 1/2 * TxCLK */
    display_mode_t mode;
} it6161_hdmi_tx_cfg_t;

typedef struct it6161_mipi_rx_cfg
{
    uint8_t lanes;
    uint8_t mipirx_lane_swap;
    uint8_t mipirx_dpdn_swap;
    uint8_t inverse_mclk;
    uint8_t inverse_pclk;
    uint8_t enable_standby_mode;
    uint8_t enable_standby_to_reset;
    uint8_t enable_iddq_mode;
    uint8_t pd_ref_clk; /* when PDREFCLK=TRUE, 0:div2, 1:div4, 2:div8, 3:div16 */
    uint8_t pd_ref_cnt;
    uint8_t hs_settle_num;
    uint8_t hs_trailing_skip_stage;
    uint8_t enable_sync_bit_error_tolerance;
    uint8_t enable_multi_lane_deskew;
    uint8_t force_continuous_clock_mode;
    uint8_t ppi_debug_selection;
    uint8_t ignore_null_packet;
    uint8_t ignore_blank_packet;
    uint8_t enable_dummy_ecc_error;
    uint8_t sel_eotp;
    uint8_t lm_debug_selection;
    uint8_t auto_sync_falling;
    uint8_t interlaced_mode;
    uint8_t user_define_timming;
    uint8_t prec_update;
    uint8_t mrec_update;
    uint8_t v_timing_resync_selction; /* 0:Div2, 1:Div4, 2:Div8, 3:Div16, 4:Div32 */
    uint8_t enable_v_timing_resync_enhance_mode;
    uint8_t enable_frame_resync;
    uint16_t pps_fifo_read_start_point;
    uint8_t enable_h_timing_resync;
    uint8_t enable_v_timing_resync;
    uint8_t enable_fifo_auto_reset;
    uint8_t enable_overflow_auto_reset;
    uint8_t enable_mclk_horizontal_average;
    uint8_t allowable_mclk_horizontal_shift_value;
    uint8_t allowable_pclk_horizontal_shift_value;
    uint8_t enable_external_pclk;
    uint8_t bypass_through_mode;
    uint8_t enable_ttl_tx_crc;
    uint8_t crc_frame_number;
    uint32_t rclk;
    uint32_t pclk;
} it6161_mipi_rx_cfg_t;

enum it6161_active_level
{
    LOW_LVL,
    HIGH_LVL,
};

enum hdmi_packet_type
{
    HDMI_PACKET_TYPE_NULL                 = 0x00,
    HDMI_PACKET_TYPE_AUDIO_CLOCK_REGEN    = 0x01,
    HDMI_PACKET_TYPE_AUDIO_SAMPLE         = 0x02,
    HDMI_PACKET_TYPE_GENERAL_CONTROL      = 0x03,
    HDMI_PACKET_TYPE_ACP                  = 0x04,
    HDMI_PACKET_TYPE_ISRC1                = 0x05,
    HDMI_PACKET_TYPE_ISRC2                = 0x06,
    HDMI_PACKET_TYPE_ONE_BIT_AUDIO_SAMPLE = 0x07,
    HDMI_PACKET_TYPE_DST_AUDIO            = 0x08,
    HDMI_PACKET_TYPE_HBR_AUDIO_STREAM     = 0x09,
    HDMI_PACKET_TYPE_GAMUT_METADATA       = 0x0a,
    /* + enum hdmi_infoframe_type */
};

enum hdmi_infoframe_type
{
    HDMI_INFOFRAME_TYPE_VENDOR = 0x81,
    HDMI_INFOFRAME_TYPE_AVI    = 0x82,
    HDMI_INFOFRAME_TYPE_SPD    = 0x83,
    HDMI_INFOFRAME_TYPE_AUDIO  = 0x84,
    HDMI_INFOFRAME_TYPE_DRM    = 0x87,
};

#define HDMI_IEEE_OUI              0x000c03
#define HDMI_FORUM_IEEE_OUI        0xc45dd8
#define HDMI_INFOFRAME_HEADER_SIZE 4U
#define HDMI_AVI_INFOFRAME_SIZE    13U
#define HDMI_SPD_INFOFRAME_SIZE    25
#define HDMI_AUDIO_INFOFRAME_SIZE  10U
#define HDMI_DRM_INFOFRAME_SIZE    26
#define HDMI_VENDOR_INFOFRAME_SIZE 4

#define HDMI_INFOFRAME_SIZE(type) (HDMI_INFOFRAME_HEADER_SIZE + HDMI_##type##_INFOFRAME_SIZE)

struct hdmi_any_infoframe
{
    enum hdmi_infoframe_type type;
    uint8_t version;
    uint8_t length;
};

enum hdmi_colorspace
{
    HDMI_COLORSPACE_RGB,
    HDMI_COLORSPACE_YUV422,
    HDMI_COLORSPACE_YUV444,
    HDMI_COLORSPACE_YUV420,
    HDMI_COLORSPACE_RESERVED4,
    HDMI_COLORSPACE_RESERVED5,
    HDMI_COLORSPACE_RESERVED6,
    HDMI_COLORSPACE_IDO_DEFINED,
};

enum hdmi_scan_mode
{
    HDMI_SCAN_MODE_NONE,
    HDMI_SCAN_MODE_OVERSCAN,
    HDMI_SCAN_MODE_UNDERSCAN,
    HDMI_SCAN_MODE_RESERVED,
};

enum hdmi_colorimetry
{
    HDMI_COLORIMETRY_NONE,
    HDMI_COLORIMETRY_ITU_601,
    HDMI_COLORIMETRY_ITU_709,
    HDMI_COLORIMETRY_EXTENDED,
};

enum hdmi_picture_aspect
{
    HDMI_PICTURE_ASPECT_NONE,
    HDMI_PICTURE_ASPECT_4_3,
    HDMI_PICTURE_ASPECT_16_9,
    HDMI_PICTURE_ASPECT_64_27,
    HDMI_PICTURE_ASPECT_256_135,
    HDMI_PICTURE_ASPECT_RESERVED,
};

enum hdmi_active_aspect
{
    HDMI_ACTIVE_ASPECT_16_9_TOP     = 2,
    HDMI_ACTIVE_ASPECT_14_9_TOP     = 3,
    HDMI_ACTIVE_ASPECT_16_9_CENTER  = 4,
    HDMI_ACTIVE_ASPECT_PICTURE      = 8,
    HDMI_ACTIVE_ASPECT_4_3          = 9,
    HDMI_ACTIVE_ASPECT_16_9         = 10,
    HDMI_ACTIVE_ASPECT_14_9         = 11,
    HDMI_ACTIVE_ASPECT_4_3_SP_14_9  = 13,
    HDMI_ACTIVE_ASPECT_16_9_SP_14_9 = 14,
    HDMI_ACTIVE_ASPECT_16_9_SP_4_3  = 15,
};

enum hdmi_extended_colorimetry
{
    HDMI_EXTENDED_COLORIMETRY_XV_YCC_601,
    HDMI_EXTENDED_COLORIMETRY_XV_YCC_709,
    HDMI_EXTENDED_COLORIMETRY_S_YCC_601,
    HDMI_EXTENDED_COLORIMETRY_OPYCC_601,
    HDMI_EXTENDED_COLORIMETRY_OPRGB,

    /* The following EC values are only defined in CEA-861-F. */
    HDMI_EXTENDED_COLORIMETRY_BT2020_CONST_LUM,
    HDMI_EXTENDED_COLORIMETRY_BT2020,
    HDMI_EXTENDED_COLORIMETRY_RESERVED,
};

enum hdmi_quantization_range
{
    HDMI_QUANTIZATION_RANGE_DEFAULT,
    HDMI_QUANTIZATION_RANGE_LIMITED,
    HDMI_QUANTIZATION_RANGE_FULL,
    HDMI_QUANTIZATION_RANGE_RESERVED,
};

/* non-uniform picture scaling */
enum hdmi_nups
{
    HDMI_NUPS_UNKNOWN,
    HDMI_NUPS_HORIZONTAL,
    HDMI_NUPS_VERTICAL,
    HDMI_NUPS_BOTH,
};

enum hdmi_ycc_quantization_range
{
    HDMI_YCC_QUANTIZATION_RANGE_LIMITED,
    HDMI_YCC_QUANTIZATION_RANGE_FULL,
};

enum hdmi_content_type
{
    HDMI_CONTENT_TYPE_GRAPHICS,
    HDMI_CONTENT_TYPE_PHOTO,
    HDMI_CONTENT_TYPE_CINEMA,
    HDMI_CONTENT_TYPE_GAME,
};

enum hdmi_metadata_type
{
    HDMI_STATIC_METADATA_TYPE1 = 1,
};

enum hdmi_eotf
{
    HDMI_EOTF_TRADITIONAL_GAMMA_SDR,
    HDMI_EOTF_TRADITIONAL_GAMMA_HDR,
    HDMI_EOTF_SMPTE_ST2084,
    HDMI_EOTF_BT_2100_HLG,
};

enum hdmi_audio_coding_type
{
    HDMI_AUDIO_CODING_TYPE_STREAM,
    HDMI_AUDIO_CODING_TYPE_PCM,
    HDMI_AUDIO_CODING_TYPE_AC3,
    HDMI_AUDIO_CODING_TYPE_MPEG1,
    HDMI_AUDIO_CODING_TYPE_MP3,
    HDMI_AUDIO_CODING_TYPE_MPEG2,
    HDMI_AUDIO_CODING_TYPE_AAC_LC,
    HDMI_AUDIO_CODING_TYPE_DTS,
    HDMI_AUDIO_CODING_TYPE_ATRAC,
    HDMI_AUDIO_CODING_TYPE_DSD,
    HDMI_AUDIO_CODING_TYPE_EAC3,
    HDMI_AUDIO_CODING_TYPE_DTS_HD,
    HDMI_AUDIO_CODING_TYPE_MLP,
    HDMI_AUDIO_CODING_TYPE_DST,
    HDMI_AUDIO_CODING_TYPE_WMA_PRO,
    HDMI_AUDIO_CODING_TYPE_CXT,
};

enum hdmi_audio_sample_size
{
    HDMI_AUDIO_SAMPLE_SIZE_STREAM,
    HDMI_AUDIO_SAMPLE_SIZE_16,
    HDMI_AUDIO_SAMPLE_SIZE_20,
    HDMI_AUDIO_SAMPLE_SIZE_24,
};

enum hdmi_audio_sample_frequency
{
    HDMI_AUDIO_SAMPLE_FREQUENCY_STREAM,
    HDMI_AUDIO_SAMPLE_FREQUENCY_32000,
    HDMI_AUDIO_SAMPLE_FREQUENCY_44100,
    HDMI_AUDIO_SAMPLE_FREQUENCY_48000,
    HDMI_AUDIO_SAMPLE_FREQUENCY_88200,
    HDMI_AUDIO_SAMPLE_FREQUENCY_96000,
    HDMI_AUDIO_SAMPLE_FREQUENCY_176400,
    HDMI_AUDIO_SAMPLE_FREQUENCY_192000,
};

enum hdmi_audio_coding_type_ext
{
    /* Refer to Audio Coding Type (CT) field in Data Byte 1 */
    HDMI_AUDIO_CODING_TYPE_EXT_CT,

    /*
     * The next three CXT values are defined in CEA-861-E only.
     * They do not exist in older versions, and in CEA-861-F they are
     * defined as 'Not in use'.
     */
    HDMI_AUDIO_CODING_TYPE_EXT_HE_AAC,
    HDMI_AUDIO_CODING_TYPE_EXT_HE_AAC_V2,
    HDMI_AUDIO_CODING_TYPE_EXT_MPEG_SURROUND,

    /* The following CXT values are only defined in CEA-861-F. */
    HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_HE_AAC,
    HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_HE_AAC_V2,
    HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_AAC_LC,
    HDMI_AUDIO_CODING_TYPE_EXT_DRA,
    HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_HE_AAC_SURROUND,
    HDMI_AUDIO_CODING_TYPE_EXT_MPEG4_AAC_LC_SURROUND = 10,
};

struct hdmi_avi_infoframe
{
    enum hdmi_infoframe_type type;
    uint8_t version;
    uint8_t length;
    enum hdmi_colorspace colorspace;
    enum hdmi_scan_mode scan_mode;
    enum hdmi_colorimetry colorimetry;
    enum hdmi_picture_aspect picture_aspect;
    enum hdmi_active_aspect active_aspect;
    bool itc;
    enum hdmi_extended_colorimetry extended_colorimetry;
    enum hdmi_quantization_range quantization_range;
    enum hdmi_nups nups;
    uint8_t video_code;
    enum hdmi_ycc_quantization_range ycc_quantization_range;
    enum hdmi_content_type content_type;
    uint8_t pixel_repeat;
    uint32_t top_bar;
    uint32_t bottom_bar;
    uint32_t left_bar;
    uint32_t right_bar;
};

struct hdmi_audio_infoframe
{
    enum hdmi_infoframe_type type;
    uint8_t version;
    uint8_t length;
    uint8_t channels;
    enum hdmi_audio_coding_type coding_type;
    enum hdmi_audio_sample_frequency sample_frequency;
    enum hdmi_audio_sample_size sample_size;
    enum hdmi_audio_coding_type_ext coding_type_ext;
    uint8_t channel_allocation;
    uint8_t level_shift_value;
    bool downmix_inhibit;
};

typedef struct it6161_cfg
{
    it6161_mipi_rx_cfg_t mipi_rx;
    it6161_hdmi_tx_cfg_t hdmi_tx;
    display_mode_t mode;
    struct hdmi_avi_infoframe source_avi_infoframe;
} it6161_cfg_t;

typedef struct _it6161_resource
{
    video_i2c_send_func_t i2cSendFunc;       /* I2C send function. */
    video_i2c_receive_func_t i2cReceiveFunc; /* I2C receive function. */
    void (*pullResetPin)(bool pullUp);       /* Function to pull reset pin high or low. */
    uint8_t i2cAddr;                         /* I2C address, 0x4C or 0x6C. */
} it6161_resource_t;

extern it6161_cfg_t it6161;
extern const display_operations_t it6161_ops;

/* default configurations */
/* define EN_MIPIRX_BYPASS_MODE to 0x01 when want to debug input signals(MIPI_DSI) */
#if 0
#define EN_MIPIRX_BYPASS_MODE (0x01U)
#else
#define EN_MIPIRX_BYPASS_MODE (0x00U)
#endif

#if (EN_MIPIRX_BYPASS_MODE == 0x01U)
#define EN_HDMITX_BYPASS_MODE (0x01U)
#else
#define EN_HDMITX_BYPASS_MODE (0x00U)
#endif

#if (EN_MIPIRX_BYPASS_MODE == 0x01U)
#define PREC_UPDATE (0x01U)
#define MREC_UPDATE (0x01U)
#else
#define PREC_UPDATE (0x00U)
#define MREC_UPDATE (0x00U)
#endif

#ifndef HDMI_TX_SUPPORT_AUDIO
#define HDMI_TX_SUPPORT_AUDIO (false)
#endif
#ifndef HDMI_TX_OUTPUT_CHANNEL
#define HDMI_TX_OUTPUT_CHANNEL (0x02U) /* 2,3,4,5,6,7,8 */
#endif
#ifndef HDMI_TX_INPUT_AUDIO_TYPE
#define HDMI_TX_INPUT_AUDIO_TYPE (T_AUDIO_LPCM)
#endif
#ifndef HDMI_TX_INPUT_AUDIO_INTERFACE
#define HDMI_TX_INPUT_AUDIO_INTERFACE (AUDIO_IF_I2S)
#endif
#ifndef HDMI_TX_INPUT_AUDIO_SAMPLE_FREQ
#define HDMI_TX_INPUT_AUDIO_SAMPLE_FREQ (AUDFS_48KHz)
#endif
#ifndef HDMI_TX_PCLK_DIV2
#define HDMI_TX_PCLK_DIV2 (false)
#endif
#define NRTXRCLK                         (0x01U) /* true:set TRCLK by self */
#define FORCE_TXCLK_STABLE               (0x01U)
#define STABLE_LINEPIEXELCNT_SENSITIVITY (0x01U)
#define RCLK_FREQ_SEL                    (0x01U) /* false: 10MHz(div1); true: 20 MHz(OSSDIV2) */
#define FORCE_TX_CLK_STABLE              (0x01U)
#define FORCE_TX_VID_STABLE              (0x01U)
#define V_SYNC_POL                       (0x00U) /* 0: active low; 1: active high */
#define H_SYNC_POL                       (0x00U) /* 0: active low; 1: active high */
#if (EN_MIPIRX_BYPASS_MODE == 0x01U)
#define EN_HDMITX_BYPASS_MODE (0x01U)
#else
#define EN_HDMITX_BYPASS_MODE (0x00U)
#endif

/* DEBUG MACROS */
#ifndef DEBUG_DUMP_HDMITX_REGISTER
#define DEBUG_DUMP_HDMITX_REGISTER (0x00U)
#endif
#ifndef DEBUG_DUMP_MIPIRX_REGISTER
#define DEBUG_DUMP_MIPIRX_REGISTER (0x00U)
#endif

#if 1
#define MIPIRX_DEBUG_PRINTF(...)
#else
#define MIPIRX_DEBUG_PRINTF PRINTF
#endif
#if 1
#define HDMITX_DEBUG_PRINTF(...)
#else
#define HDMITX_DEBUG_PRINTF PRINTF
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

status_t IT6161_Init(display_handle_t *handle, const display_config_t *config);

status_t IT6161_Deinit(display_handle_t *handle);

status_t IT6161_Start(display_handle_t *handle);

status_t IT6161_Stop(display_handle_t *handle);

void IT6161_Interrupt(display_handle_t *handle);
#if defined(__cplusplus)
}
#endif

void HDMITX_RegEE_Process(display_handle_t *handle, uint8_t RegEE);

void HDMITX_Reg06_Process(display_handle_t *handle, uint8_t Reg06);

void HDMITX_Reg08_Process(display_handle_t *handle, uint8_t Reg08);

void HDMI_InfoframeSetChecksum(void *buffer, int32_t size);

void HDMI_AviInfoframeInit(struct hdmi_avi_infoframe *frame);

int32_t HDMITX_CalcPclk(display_handle_t *handle);

uint8_t HDMI_InfoframeChecksum(void *buffer, int32_t size);

int32_t HDMI_AviInfoframePack(struct hdmi_avi_infoframe *frame, void *buffer, int32_t size);

int32_t HDMI_AudioInfoframePack(struct hdmi_audio_infoframe *frame, void *buffer, int32_t size);

void it6161_SetIntActiveLevel(display_handle_t *handle, enum it6161_active_level level);

void it6161_IntMaskEnable(display_handle_t *handle);

void it6161_HDMITX_Init(display_handle_t *handle);

#endif /* _FSL_IT6161_H_ */
