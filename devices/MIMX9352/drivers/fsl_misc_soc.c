/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_common.h"
#include "fsl_misc_soc.h"

int SOC_MixPowerInit(soc_mix_power_domain_e pwr_dom)
{
    soc_src_mem_slice_id_e mem_id;
    soc_src_mem_slice_regs_t *mem_regs;
    soc_src_general_regs_t *global_regs;
    BLK_CTRL_S_AONMIX_Type *aonmix_base;
    uint32_t scr;
    SRC_MIX_SLICE_Type *mix_base;

    switch (pwr_dom)
    {
        case SOC_MIX_PD_MEDIAMIX:
            mix_base = SRC_MEDIA_SLICE;
            mem_id   = SOC_SRC_MEM_MEDIA;
            scr      = BIT(5);

            /* Enable S400 handshake */
            aonmix_base = BLK_CTRL_S_AONMIX2;
            aonmix_base->LP_HANDSHAKE |= BIT(13);
            break;
        case SOC_MIX_PD_MLMIX:
            mix_base = SRC_ML_SLICE;
            mem_id   = SOC_SRC_MEM_ML;
            scr      = BIT(4);
            break;
        case SOC_MIX_PD_DDRMIX:
            mix_base = SRC_DDR_SLICE;
            mem_id   = SOC_SRC_MEM_DDRMIX;
            scr      = BIT(6);
            break;
        default:
            return -1;
    }

    mem_regs    = (soc_src_mem_slice_regs_t *)(uint32_t)(SOC_SRC_IPS_BASE_ADDR + 0x3800 + 0x400 * mem_id);
    global_regs = (soc_src_general_regs_t *)(uint32_t)SOC_SRC_GLOBAL_RBASE;

    /* Allow NS to set it */
    mix_base->AUTHEN_CTRL |= BIT(9);

    mix_base->PSW_ACK_CTRL_0 &= ~(BIT(28) | BIT(29));

    /* mix reset will be held until boot core write this bit to 1 */
    global_regs->scr |= scr;

    /* Enable mem in Low power auto sequence */
    mem_regs->mem_ctrl |= BIT(2);

    /* Set the power down state */
    if (mix_base->FUNC_STAT & SRC_MIX_SLICE_FUNC_STAT_PSW_STAT(1))
    {
        /*
         * The mix is default power off, power down it to make PDN_SFT bit
         *  aligned with FUNC STAT
         */
        mix_base->SLICE_SW_CTRL |= BIT(31);

        /* Since PSW_STAT is 1, can't be used for power off status (SW_CTRL BIT31 set)) */
        /* Check the MEM STAT change to ensure SSAR is completed */
        while (!(mix_base->FUNC_STAT & SRC_MIX_SLICE_FUNC_STAT_MEM_STAT(1)))
        {
        }

        /* wait few ipg clock cycles to ensure FSM done and power off status is correct */
        /* About 5 cycles at 24Mhz, 1us is enough  */
        SDK_DelayAtLeastUs(1, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    }
    else
    {
        /*  The mix is default power on, Do mix power cycle */
        mix_base->SLICE_SW_CTRL |= BIT(31);
        while (!(mix_base->FUNC_STAT & SRC_MIX_SLICE_FUNC_STAT_PSW_STAT(1)))
        {
        }
    }

    /* power on */
    mix_base->SLICE_SW_CTRL &= ~BIT(31);
    while (mix_base->FUNC_STAT & SRC_MIX_SLICE_FUNC_STAT_ISO_STAT(1))
    {
    }

    return 0;
}

void SOC_DisableIsolation(void)
{
    soc_src_general_regs_t *global_regs = (soc_src_general_regs_t *)(uint32_t)SOC_SRC_GLOBAL_RBASE;
    /* clear isolation for usbphy, dsi, csi*/
    global_regs->sp_iso_ctrl = 0x0;
}
