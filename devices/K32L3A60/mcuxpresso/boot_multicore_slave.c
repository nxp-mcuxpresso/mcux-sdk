/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#if defined (__MULTICORE_MASTER_SLAVE_M0SLAVE) || \
    defined (__MULTICORE_MASTER_SLAVE_M4SLAVE)

#if defined (__USE_CMSIS)
#include "fsl_device_registers.h"
#define    PCC_MUA              (PCC0->CLKCFG[37])
#else
/* Provide access to registers when not linking with standard CMSIS based headers */
#include <stdint.h>

/** Peripheral MUA base address */
#define MUA_BASE                                 (0x40025000u)
/** Peripheral MUA base pointer */
#define MUA                                      ((MU_Type *)MUA_BASE)

#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

/** MU - Register Layout Typedef */
typedef struct {
  __I  uint32_t VER;                               /**< Version ID Register, offset: 0x0 */
  __I  uint32_t PAR;                               /**< Parameter Register, offset: 0x4 */
       uint8_t RESERVED_0[24];
  __IO uint32_t TR[4];                             /**< Transmit Register, array offset: 0x20, array step: 0x4 */
       uint8_t RESERVED_1[16];
  __I  uint32_t RR[4];                             /**< Receive Register, array offset: 0x40, array step: 0x4 */
       uint8_t RESERVED_2[16];
  __IO uint32_t SR;                                /**< Status Register, offset: 0x60 */
  __IO uint32_t CR;                                /**< Control Register, offset: 0x64 */
  __IO uint32_t CCR;                               /**< Core Control Register, offset: 0x68 */
} MU_Type;

typedef enum _mu_core_boot_mode
{
    kMU_CoreBootFromDflashBase = 0x00U, /*!< Boot from Dflash base.  */
    kMU_CoreBootFromCM0PRamBase = 0x02U, /*!< Boot from CM0+ RAM base. */
} mu_core_boot_mode_t;

#define MU_CCR_HR_MASK                           (0x1U)
#define MU_CCR_HR_SHIFT                          (0U)
#define MU_CCR_HR(x)                             (((uint32_t)(((uint32_t)(x)) << MU_CCR_HR_SHIFT)) & MU_CCR_HR_MASK)
#define MU_CCR_HRM_MASK                          (0x2U)
#define MU_CCR_HRM_SHIFT                         (1U)
#define MU_CCR_HRM(x)                            (((uint32_t)(((uint32_t)(x)) << MU_CCR_HRM_SHIFT)) & MU_CCR_HRM_MASK)
#define MU_CCR_RSTH_MASK                         (0x4U)
#define MU_CCR_RSTH_SHIFT                        (2U)
#define MU_CCR_RSTH(x)                           (((uint32_t)(((uint32_t)(x)) << MU_CCR_RSTH_SHIFT)) & MU_CCR_RSTH_MASK)
#define MU_CCR_CLKE_MASK                         (0x8U)
#define MU_CCR_CLKE_SHIFT                        (3U)
#define MU_CCR_CLKE(x)                           (((uint32_t)(((uint32_t)(x)) << MU_CCR_CLKE_SHIFT)) & MU_CCR_CLKE_MASK)
#define MU_CCR_BOOT_MASK                         (0x30U)
#define MU_CCR_BOOT_SHIFT                        (4U)
#define MU_CCR_BOOT(x)                           (((uint32_t)(((uint32_t)(x)) << MU_CCR_BOOT_SHIFT)) & MU_CCR_BOOT_MASK)
#define MU_SR_RDIP_MASK                          (0x200U)
#define MU_SR_RDIP_SHIFT                         (9U)
#define MU_SR_RDIP(x)                            (((uint32_t)(((uint32_t)(x)) << MU_SR_RDIP_SHIFT)) & MU_SR_RDIP_MASK)

/** PCC - Register Layout Typedef */
typedef struct {
  __IO uint32_t CLKCFG[130];                       /**< PCC MSCM Register..PCC EXT_CLK Register, array offset: 0x0, array step: 0x4 */
} PCC_Type;

/* PCC - Peripheral instance base addresses */
/** Peripheral PCC0 base address */
#define PCC0_BASE                                (0x4002B000u)
/** Peripheral PCC0 base pointer */
#define PCC0                                     ((PCC_Type *)PCC0_BASE)

#define    PCC_MUA              (PCC0->CLKCFG[37])

#endif


/* MCMGR boot address of RAM */
#define MCMGR_BOOT_ADDRESS_RAM (0x09000000U)
/* MCMGR boot address of flash memory */
#define MCMGR_BOOT_ADDRESS_FLASH (0x01000000U)


/*
 * Simple function to release slave cpu in a K32L3 MCU from reset.
 * Note that the SDK multicore examples provide a more sophisticated
 * model of a multicore system in the MCMGR component
 */
void boot_multicore_slave(void) {

#if defined (__MULTICORE_MASTER_SLAVE_M0SLAVE)
	extern uint8_t __core_m0slave_START__;
	void *bootAddress = (void *)&__core_m0slave_START__;
#elif defined (__MULTICORE_MASTER_SLAVE_M4SLAVE)
	extern uint8_t __core_m4slave_START__;
	void *bootAddress = (void *)&__core_m4slave_START__;
#error CM4 slave not currently supported
#else
#error Cannot resolve slave core image address
#endif

	mu_core_boot_mode_t bootMode;

    if (bootAddress == (void *)MCMGR_BOOT_ADDRESS_RAM)
    {
        bootMode = kMU_CoreBootFromCM0PRamBase;
    }
    else if (bootAddress == (void *)MCMGR_BOOT_ADDRESS_FLASH)
    {
        bootMode = kMU_CoreBootFromDflashBase;
    }
    else
    {
       /* invalid boot address */
       while(1);
    }

    /* PCC MUA Register (PCC_MUA) : Bit 30 : Clock Gate Control */
	PCC_MUA = 1 << 30;

    /* Clean the reset de-assert pending flag */
    MUA->SR = MU_SR_RDIP_MASK;

    /* Release core from Reset */
    uint32_t reg = MUA->CCR;
    reg = (reg & ~(MU_CCR_HR_MASK | MU_CCR_RSTH_MASK | MU_CCR_BOOT_MASK)) | MU_CCR_BOOT(bootMode);
    MUA->CCR = reg;

    /* Wait for coming out of reset */
    while (!(MUA->SR & MU_SR_RDIP_MASK))
    {
    }
}

#endif /* defined (__MULTICORE_MASTER_SLAVE_M0SLAVE) ||
        *         (__MULTICORE_MASTER_SLAVE_M4SLAVE)
        */
