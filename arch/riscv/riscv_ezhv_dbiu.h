/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef RISCV_EZHV_DBIU_H_
#define RISCV_EZHV_DBIU_H_

#include "riscv_asm.h"

/*!
 * @ingroup RISCV_CoreCustomExtXzezhv
 * @defgroup RISCV_CoreCustomExtXzezhvDbiu EZH-V DBIU
 * @brief Data Bus Interface Unit
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!
 * @name DBIU CSR registers
 * @{
 */
#define CSR_EZ_DBIU_CFG01     (2091U)
#define CSR_EZ_DBIU_CFG23     (2092U)
#define CSR_EZ_DBIU_ADDR0     (2093U)
#define CSR_EZ_DBIU_ADDR1     (2094U)
#define CSR_EZ_DBIU_ADDR2     (2095U)
#define CSR_EZ_DBIU_ADDR3     (2096U)
#define CSR_EZ_DBIU_DATA0     (2097U)
#define CSR_EZ_DBIU_DATA1     (2098U)
#define CSR_EZ_DBIU_DATA2     (2099U)
#define CSR_EZ_DBIU_DATA3     (2100U)
#define CSR_EZ_DBIU_ADDRn(n)  (2093U+(n)) /* n in range 0-3 */
#define CSR_EZ_DBIU_DATAn(n)  (2097U+(n)) /* n in range 0-3 */
/*!
 * @}
 */

/*! @brief dbiu cfg */
#define EZHV_DBIU_CFG_MASK      (0x3FFU)
#define EZHV_DBIU_CFG_OFFSET    (16U)

/*! @brief Bit Offset, AHB transfer size 0:byte 1 half word 2 word 3 resverd */
#define EZHV_DBIU_SZ_OFFSET     (0x8U)

/*! @brief LIST of DBIU channels */
typedef enum _ezhv_dbiu_channel
{
    kDBIU_CH0 = 0, /*!< channel 0 */
    kDBIU_CH1 = 1, /*!< channel 1 */
    kDBIU_CH2 = 2, /*!< channel 2 */
    kDBIU_CH3 = 3, /*!< channel 3 */
    kDBIU_CH_Num,
} ezhv_dbiu_channel_t;

/*! @brief DBIU configure */
enum
{
    kDBIU_RD = 0x1,  /*!< it's a read channel  */
    kDBIU_WR = 0x2,  /*!< it's a write channel */
    kDBIU_HB = 0x4,  /*!< issue on heart beat */
    kDBIU_AU = 0x8,  /*!< enable address auto-update  */
    kDBIU_AD = 0x10, /*!< bit5=1,auto-decrement address. bit5=0,auto-increment address */
    kDBIU_EE = 0x20, /*!< enable channel event out */
    kDBIU_EF = 0x40, /*!< enable or disable error forwarding to core */
    kDBIU_RT = 0x80, /*!< Channel re-trigger on access to data register */
};

/*! @brief DBIU AHB tranfer size */
typedef enum _ezhv_dbiu_sz
{
    kDBIU_SZ_BYTE = 0,     /*!< byte */
    kDBIU_SZ_HALF_WORD =1, /*!< half word */
    kDBIU_SZ_WORD = 2,     /*!< word */
} ezhv_dbiu_sz_t;

/*! @brief Parameter structure used to config dbiu */
typedef struct _ez_dbiu_cfg
{
    uint8_t rwFlag;     /* should be kDBIU_RD or kDBIU_WR */
    uint8_t issueHb;    /* issue on heartbeat */
    uint8_t addMode;    /* should be zero or kDBIU_AU or kDBIU_AU|kDBIU_AD */
    uint8_t eventEn;    /* should be zero or kDBIU_EE */

    uint8_t errForward; /* should be zero or kDBIU_EF */
    uint8_t retrigger;  /* should be zero or kDBIU_RT */
    uint8_t size;       /* should be from the ezhv_dbiu_sz_t */
    uint8_t pad[1];     /* reserved */
} ezhv_dbiu_cfg_t;

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief set the value of dbiu cfg01 register
 *
 * @param mask    bits to set
 */
static inline void EZHV_SetDbiuCfg01(uint32_t mask)
{
    csr_set(CSR_EZ_DBIU_CFG01, mask);
}

/*!
 * @brief clear the value of dbiu cfg01 register
 *
 * @param mask    bits to clear
 */
static inline void EZHV_ClrDbiuCfg01(uint32_t mask)
{
    csr_clear(CSR_EZ_DBIU_CFG01, mask);
}

/*!
 * @brief write the value of dbiu cfg01 register
 *
 * @param regVal    register value to write
 */
static inline void EZHV_WriteDbiuCfg01(uint32_t regVal)
{
    csr_write(CSR_EZ_DBIU_CFG01, regVal);
}

/*!
 * @brief read the value of the dbiu cfg01 register
 *
 * @return the register value of dbiu cfg01
 */
static inline uint32_t EZHV_ReadDbiuCfg01(void)
{
    return (uint32_t)csr_read(CSR_EZ_DBIU_CFG01);
}

/*!
 * @brief set the value of dbiu cfg23 register
 *
 * @param mask    bits to set
 */
static inline void EZHV_SetDbiuCfg23(uint32_t mask)
{
    csr_set(CSR_EZ_DBIU_CFG23, mask);
}

/*!
 * @brief clear the value of dbiu cfg23 register
 *
 * @param mask   bits to clear
 */
static inline void EZHV_ClrDbiuCfg23(uint32_t mask)
{
    csr_clear(CSR_EZ_DBIU_CFG23, mask);
}

/*!
 * @brief write the value of dbiu cfg23 register
 *
 * @param regVal Value to write
 */
static inline void EZHV_WriteDbiuCfg23(uint32_t regVal)
{
    csr_write(CSR_EZ_DBIU_CFG23, regVal);
}

/*!
 * @brief read the value of the dbiu cfg23 register
 *
 * @return the register value of dbiu cfg23
 */
static inline uint32_t EZHV_ReadDbiuCfg23(void)
{
    return (uint32_t)csr_read(CSR_EZ_DBIU_CFG23);
}

/*!
 * @brief write the address of DBIU channel N
 *
 * @param chIdx    channel to write, refer to ezhv_dbiu_channel_t
 * @param addrVal   address value to write
 */
static inline void EZHV_WriteDbiuAddr(ezhv_dbiu_channel_t chIdx, uint32_t addrVal)
{
    switch(chIdx)
    {
        case kDBIU_CH0:
            csr_write(CSR_EZ_DBIU_ADDR0, addrVal);
            break;
        case kDBIU_CH1:
            csr_write(CSR_EZ_DBIU_ADDR1, addrVal);
            break;
        case kDBIU_CH2:
            csr_write(CSR_EZ_DBIU_ADDR2, addrVal);
            break;
        case kDBIU_CH3:
            csr_write(CSR_EZ_DBIU_ADDR3, addrVal);
            break;
        default:
            break;
    }
}

/*!
 * @brief read address value of DBIU channel N
 *
 * @param chIdx    channel index, refer to ezhv_dbiu_channel_t
 *
 * @return the address value of given DBIU
 */
static inline uint32_t EZHV_ReadDbiuAddr(ezhv_dbiu_channel_t chIdx)
{
    uint32_t addrVal = 0;
    switch(chIdx)
    {
        case kDBIU_CH0:
            addrVal = (uint32_t)csr_read(CSR_EZ_DBIU_ADDR0);
            break;
        case kDBIU_CH1:
            addrVal = (uint32_t)csr_read(CSR_EZ_DBIU_ADDR1);
            break;
        case kDBIU_CH2:
            addrVal = (uint32_t)csr_read(CSR_EZ_DBIU_ADDR2);
            break;
        case kDBIU_CH3:
            addrVal = (uint32_t)csr_read(CSR_EZ_DBIU_ADDR3);
            break;
        default:
            break;
    }
    return addrVal;
}

/*!
 * @brief write the data of DBIU channel N
 *
 * @param chIdx    channel index, refer to ezhv_dbiu_channel_t
 * @param dataVal    data to be written into Data N register
 */
static inline void EZHV_WriteDbiuData(ezhv_dbiu_channel_t chIdx, uint32_t dataVal)
{
    switch(chIdx)
    {
        case kDBIU_CH0:
            csr_write(CSR_EZ_DBIU_DATA0, dataVal);
            break;
        case kDBIU_CH1:
            csr_write(CSR_EZ_DBIU_DATA1, dataVal);
            break;
        case kDBIU_CH2:
            csr_write(CSR_EZ_DBIU_DATA2, dataVal);
            break;
        case kDBIU_CH3:
            csr_write(CSR_EZ_DBIU_DATA3, dataVal);
            break;
        default:
            break;
    }
}

/*!
 * @brief read the data of DBIU channel N
 *
 * @param chIdx Channel index, refer to ezhv_dbiu_channel_t
 *
 * @return The data of DBIU given channel
 */
static inline uint32_t EZHV_ReadDbiuData(ezhv_dbiu_channel_t chIdx)
{
    uint32_t DataVal = 0;

    switch(chIdx)
    {
        case kDBIU_CH0:
            DataVal = (uint32_t)csr_read(CSR_EZ_DBIU_DATA0);
            break;
        case kDBIU_CH1:
            DataVal = (uint32_t)csr_read(CSR_EZ_DBIU_DATA1);
            break;
        case kDBIU_CH2:
            DataVal = (uint32_t)csr_read(CSR_EZ_DBIU_DATA2);
            break;
        case kDBIU_CH3:
            DataVal = (uint32_t)csr_read(CSR_EZ_DBIU_DATA3);
            break;
        default:
            break;
    }

    return DataVal;
}

/*!
 * @brief Initialize the given channel of DBIU
 *
 * @param chIdx   given channel index
 * @param pCfg    pointer to a configure struct parameter
 * @param addrVal address value for dbiu address register
 */
static inline void EZHV_InitDbiuCh(ezhv_dbiu_channel_t chIdx, const ezhv_dbiu_cfg_t *pCfg, uint32_t addrVal)
{
    uint32_t u32cfgmsk = 0;

    u32cfgmsk = pCfg->rwFlag  |
                pCfg->issueHb |
                pCfg->addMode |
                pCfg->eventEn |
                pCfg->errForward |
                pCfg->retrigger  |
               (pCfg->size << EZHV_DBIU_SZ_OFFSET);

    switch (chIdx)
    {
        case kDBIU_CH0:
            EZHV_ClrDbiuCfg01(EZHV_DBIU_CFG_MASK);
            EZHV_SetDbiuCfg01(u32cfgmsk);
            csr_write(CSR_EZ_DBIU_ADDR0, addrVal);
            break;
        case kDBIU_CH1:
            EZHV_ClrDbiuCfg01(EZHV_DBIU_CFG_MASK << EZHV_DBIU_CFG_OFFSET);
            EZHV_SetDbiuCfg01(u32cfgmsk << EZHV_DBIU_CFG_OFFSET);
            csr_write(CSR_EZ_DBIU_ADDR1, addrVal);
            break;
        case kDBIU_CH2:
            EZHV_ClrDbiuCfg23(EZHV_DBIU_CFG_MASK);
            EZHV_SetDbiuCfg23(u32cfgmsk);
            csr_write(CSR_EZ_DBIU_ADDR2, addrVal);
            break;
        case kDBIU_CH3:
            EZHV_ClrDbiuCfg23(EZHV_DBIU_CFG_MASK << EZHV_DBIU_CFG_OFFSET);
            EZHV_SetDbiuCfg23(u32cfgmsk << EZHV_DBIU_CFG_OFFSET);
            csr_write(CSR_EZ_DBIU_ADDR3, addrVal);
            break;
        default:
            break;
    }
}

/*!
 * @brief De-initialize the given channel of DBIU
 *
 * @param chIdx given channel index
 */
static inline void EZHV_DeinitDbiuCh(ezhv_dbiu_channel_t chIdx)
{
    uint32_t u32cfgmsk = EZHV_DBIU_CFG_MASK;

    switch (chIdx)
    {
        case kDBIU_CH0:
            EZHV_ClrDbiuCfg01(u32cfgmsk);
            break;
        case kDBIU_CH1:
            EZHV_ClrDbiuCfg01(u32cfgmsk << EZHV_DBIU_CFG_OFFSET);
            break;
        case kDBIU_CH2:
            EZHV_ClrDbiuCfg23(u32cfgmsk);
            break;
        case kDBIU_CH3:
            EZHV_ClrDbiuCfg23(u32cfgmsk << EZHV_DBIU_CFG_OFFSET);
            break;
        default:
            break;
    }
}

#ifdef __cplusplus
}
#endif

#endif
