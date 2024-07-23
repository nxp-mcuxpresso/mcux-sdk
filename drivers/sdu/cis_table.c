/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <RW612.h>
#include "cis_table.h"

#define CISTPL_VERS_1 0x15U
#define CISTPL_MANFID 0x20U
#define CISTPL_FUNCID 0x21U
#define CISTPL_FUNCE  0x22U
#define CISTPL_END    0xffU

#define TPLLV1_MAJOR 1U
#define TPLLV1_MINOR 0U

#define ROM_SDIO_F0_BLKSIZE  0x1UL
#define ROM_SDIO_FN_BLKSIZE  0x200UL
#define ROM_SDIO_SPEED       0xbUL
#define ROM_SDIO_TIMEOUT_VAL 0x14UL
#define ROM_SDIO_REV         0x30UL

// 4bit input only
static uint8_t tohex(uint8_t c)
{
    if (c < 10U)
    {
        return (uint8_t)(c + '0');
    }
    else
    {
        return (uint8_t)((c - 10U) + 'A');
    }
}

void emit1(uint32_t *p_cis_addr, uint8_t x)
{
    REG8(*p_cis_addr) = x;
    *p_cis_addr += 1U;
}

void emit2(uint32_t *p_cis_addr, uint16_t x)
{
    REG8(*p_cis_addr) = (uint8_t)(x & 0xffU);
    REG8(*p_cis_addr + 1U) = (uint8_t)((x >> 8U) & 0xffU);
    *p_cis_addr += 2U;
}

void emit4(uint32_t *p_cis_addr, uint32_t x)
{
    REG8(*p_cis_addr) = (uint8_t)(x & 0xffU);
    REG8(*p_cis_addr + 1U) = (uint8_t)((x >> 8U) & 0xffU);
    REG8(*p_cis_addr + 2U) = (uint8_t)((x >> 16U) & 0xffU);
    REG8(*p_cis_addr + 3U) = (uint8_t)((x >> 24U) & 0xffU);
    *p_cis_addr += 4U;
}

static int32_t findlen(uint8_t *a)
{
    uint32_t done = 0U;
    uint32_t i    = 0U;
    int32_t len   = 0;

    while (done == 0U)
    {
        if (a[i] == (uint8_t)'\377')
        {
            done = 1U;
        }
        i += 1U;
        len += 1;
    }

    return len;
}

void emitvers(uint32_t *p_cis_addr, uint8_t *s, uint32_t subs)
{
    int32_t slen;
    uint32_t i;
    uint32_t addr;

    emit1(p_cis_addr, CISTPL_VERS_1);
    slen = findlen(s);

    if(slen < 0)
    {
        // This is a bad failure. On the default, it cannot happen since
        // all our strings end in 0xFF but a user provided str may have this
        // issue.
        return;
    }

    emit1(p_cis_addr, (uint8_t)(slen + 2));
    emit1(p_cis_addr, TPLLV1_MAJOR);
    emit1(p_cis_addr, TPLLV1_MINOR);

    addr = *p_cis_addr; // Where we are now

    for(i = 0; i < (uint32_t)slen; i++)
    {
        emit1(p_cis_addr, s[i]);
    }

    if (subs != 0U)
    {
        uint32_t id = (uint32_t)((SOCCTRL->CHIP_INFO & SOCCIU_CHIP_INFO_ID_MASK) >> SOCCIU_CHIP_INFO_ID_SHIFT);

        for (i = 0; i < slen; i++)
        {
            if ((i < ((uint32_t)slen - 2U)) && (s[i] == (uint8_t)'X' && s[i + 1U] == (uint8_t)'X'))
            {
                REG8(addr + i)      = (uint8_t)tohex((id >> 4U) & 0xfU);
                REG8(addr + i + 1U) = (uint8_t)tohex(id & 0xfU);
            }
        }
    }
}

void emitvidpid(uint32_t *p_cis_addr, uint32_t vid, uint32_t pid)
{
    emit1(p_cis_addr, CISTPL_MANFID);
    emit1(p_cis_addr, 4U); // fixed len
    emit2(p_cis_addr, (uint16_t)vid);
    emit2(p_cis_addr, (uint16_t)pid);
}

void emitfuncid(uint32_t *p_cis_addr)
{
    emit1(p_cis_addr, CISTPL_FUNCID);
    emit1(p_cis_addr, 2U);
    emit1(p_cis_addr, 0xcU);
    emit1(p_cis_addr, 0x0U);
}

void emitfunce(uint32_t *p_cis_addr)
{
    uint32_t blksize;
    uint32_t speed;
    blksize = ROM_SDIO_F0_BLKSIZE;
    speed = ROM_SDIO_SPEED;
    emit1(p_cis_addr, CISTPL_FUNCE);
    emit1(p_cis_addr, 4U);
    emit1(p_cis_addr, 0x0U);
    emit2(p_cis_addr, (uint16_t)blksize);
    emit1(p_cis_addr, (uint8_t)speed);
}

void emitfunce_extended(uint32_t *p_cis_addr, uint32_t fn)
{
    uint32_t blksize;
    uint32_t timeout;
    uint32_t rev;
    blksize = ROM_SDIO_FN_BLKSIZE;
    timeout = ROM_SDIO_TIMEOUT_VAL;
    rev = ROM_SDIO_REV;

    emit1(p_cis_addr, CISTPL_FUNCE);
    emit1(p_cis_addr, 0x2aU);
    emit1(p_cis_addr, 0x01U);
    emit1(p_cis_addr, 0x01U);
    emit1(p_cis_addr, (uint8_t)rev);
    emit4(p_cis_addr, 0x00000000);
    emit4(p_cis_addr, 0x00000000);
    emit1(p_cis_addr, 0x00);
    emit2(p_cis_addr, (uint16_t)blksize);
    emit4(p_cis_addr, 0x01ff8000);
//    emit4(REG32(sdu_fnN_ocr_0(fn)));
    emit1(p_cis_addr, 0x00U);
    emit1(p_cis_addr, 0x00U);
    emit1(p_cis_addr, 0x00U);
    emit1(p_cis_addr, 0x00U);
    emit1(p_cis_addr, 0x00U);
    emit1(p_cis_addr, 0x00U);
    emit2(p_cis_addr, 0x0000U);
    emit2(p_cis_addr, 0x0000U);
    emit2(p_cis_addr, (uint16_t)timeout);
    emit2(p_cis_addr, 0x0000U);
    emit2(p_cis_addr, 0x0000U);
    emit2(p_cis_addr, 0x0000U);
    emit2(p_cis_addr, 0x0000U);
    emit2(p_cis_addr, 0x0000U);
    emit2(p_cis_addr, 0x0000U);
}

static uint32_t modify(uint32_t tmp, uint32_t hi, uint32_t lo, uint32_t val)
{
    uint32_t mask;
    uint32_t masklen;
    masklen = (hi - lo) + 1U;       // Width of the field
    mask    = (uint32_t)((1U << masklen) - 1U); // Now as a mask
    val &= mask;                    // mask unshifted val
    val <<= lo;                     // Now move val to field off
    mask <<= lo;                    // mask moves too to field off
    tmp &= ~mask;                   // Clear R[hi:lo]
    tmp |= val;                     // Now M[hi:lo]
    return tmp;
}

static uint32_t modify2(uint32_t tmp, uint32_t mask, uint32_t shift, uint32_t val)
{
    mask >>= shift;
    val &= mask;    // mask unshifted val
    val <<= shift;  // Now move val to field off
    mask <<= shift; // mask moves too to field off
    tmp &= ~mask;   // Clear R[hi:lo]
    tmp |= val;     // Now M[hi:lo]
    return tmp;
}

void rmw2(volatile uint32_t *addr, uint32_t mask, uint32_t shift, uint32_t val)
{
    *addr = modify2(*addr, mask, shift, val);
}

void rmwb(uint32_t addr, uint32_t hi, uint32_t lo, uint32_t val)
{
    REG8(addr) = (uint8_t)modify((uint32_t)REG8(addr), hi, lo, val);
}

static uint32_t extract2(uint32_t data, uint32_t mask, uint32_t shift)
{
    uint32_t tmp;
    tmp = data;
    tmp >>= shift; // shift to 0
    mask >>= shift;
    tmp &= mask; // Knock off other bits
    return tmp;
}

static uint32_t rd2(volatile uint32_t *addr, uint32_t mask, uint32_t shift)
{
    uint32_t data;
    data = *addr;
    return extract2(data, mask, shift);
}

static void set_iomux_helper(uint32_t hi, uint32_t lo)
{
    uint32_t mask;
    uint32_t masklen;
    uint32_t val;
    volatile uint32_t *addr;
    if (hi < 32U)
    {
        addr = &SOCCTRL->MCI_IOMUX_EN0;
    }
    else
    {
        hi -= 32U;
        lo -= 32U;
        addr = &SOCCTRL->MCI_IOMUX_EN1;
    }
    masklen = (hi - lo) + 1U; // Field len
    mask    = (uint32_t)((1U << masklen) - 1U);
    val     = mask;
    mask <<= lo;
    do
    {
        rmw2(addr, mask, lo, val);
    } while (rd2(addr, mask, lo) != val);
}
void set_iomux(uint32_t hi, uint32_t lo)
{
    if (hi < lo)
    {
        return;
    }
    if ((hi < 32U) || (lo > 32U))
    {
        set_iomux_helper(hi, lo);
    }
    else
    { // split
        set_iomux_helper(31U, lo);
        set_iomux_helper(hi, 32U);
    }
}

#if 0
// legacy func
static void post_gpio(uint32_t val)
{
    uint32_t port_id = 0U;
    // vvvv this write... doesn't take. The loop... does.
    //    SOCCTRL->MCI_IOMUX_EN0 |= bit(3) | bit(2) | bit(1) | bit(0);
    set_iomux(3U, 0U);
#if 0
    do {
	rmw2(&SOCCTRL->MCI_IOMUX_EN0, 0xf, 0, 0xf);
    } while(rd2(&SOCCTRL->MCI_IOMUX_EN0, 0xf, 0) != 0xf);
#endif
    GPIO->DIRSET[port_id] = 0xfU;
    MCI_IO_MUX->GPIO_GRP0 &= ~0xfU;
    MCI_IO_MUX->GPIO_GRP0 |= 0xfU;
    GPIO->PIN[port_id] &= ~0xfU;
    GPIO->PIN[port_id] |= val & 0xfU;
}
#endif