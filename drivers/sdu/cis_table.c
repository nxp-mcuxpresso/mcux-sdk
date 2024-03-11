/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <RW612.h>
#include "cis_table.h"

#define CISTPL_VERS_1 0x15
#define CISTPL_MANFID 0x20
#define CISTPL_FUNCID 0x21
#define CISTPL_FUNCE  0x22
#define CISTPL_END    0xff

#define TPLLV1_MAJOR 1
#define TPLLV1_MINOR 0

#define ROM_SDIO_F0_BLKSIZE  0x1ul
#define ROM_SDIO_FN_BLKSIZE  0x200ul
#define ROM_SDIO_SPEED       0xbul
#define ROM_SDIO_TIMEOUT_VAL 0x14ul
#define ROM_SDIO_REV         0x30ul

// 4bit input only
uint8_t tohex(uint8_t c)
{
    if (c < 10)
    {
        return c + '0';
    }
    else
    {
        return (c - 10) + 'A';
    }
}

void emit1(uint32_t *p_cis_addr, uint8_t x)
{
    REG8(*p_cis_addr) = x;
    *p_cis_addr += 1;
}

void emit2(uint32_t *p_cis_addr, uint16_t x)
{
    REG8(*p_cis_addr) = x & 0xff;
    REG8(*p_cis_addr + 1) = (x >> 8) & 0xff;
    *p_cis_addr += 2;
}

void emit4(uint32_t *p_cis_addr, uint32_t x)
{
    REG8(*p_cis_addr) = x & 0xff;
    REG8(*p_cis_addr + 1) = (x >> 8) & 0xff;
    REG8(*p_cis_addr + 2) = (x >> 16) & 0xff;
    REG8(*p_cis_addr + 3) = (x >> 24) & 0xff;
    *p_cis_addr += 4;
}

int32_t findlen(uint8_t *a)
{
    uint32_t done = 0;
    uint32_t i    = 0;
    int32_t len   = 0;

    while (!done)
    {
        if (a[i] == '\377')
        {
            done = 1;
        }
        i += 1;
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

    emit1(p_cis_addr, slen + 2);
    emit1(p_cis_addr, TPLLV1_MAJOR);
    emit1(p_cis_addr, TPLLV1_MINOR);

    addr = *p_cis_addr; // Where we are now

    for(i = 0; i < slen; i++)
    {
        emit1(p_cis_addr, s[i]);
    }

    if (subs)
    {
        uint32_t id = (uint32_t)((SOCCTRL->CHIP_INFO & SOCCIU_CHIP_INFO_ID_MASK) >> SOCCIU_CHIP_INFO_ID_SHIFT);

        for (i = 0; i < slen; i++)
        {
            if ((i < slen - 2) && (s[i] == 'X' && s[i + 1] == 'X'))
            {
                REG8(addr + i)     = tohex((id >> 4) & 0xf);
                REG8(addr + i + 1) = tohex(id & 0xf);
            }
        }
    }
}

void emitvidpid(uint32_t *p_cis_addr, uint32_t vid, uint32_t pid)
{
    emit1(p_cis_addr, CISTPL_MANFID);
    emit1(p_cis_addr, 4); // fixed len
    emit2(p_cis_addr, vid);
    emit2(p_cis_addr, pid);
}

void emitfuncid(uint32_t *p_cis_addr)
{
    emit1(p_cis_addr, CISTPL_FUNCID);
    emit1(p_cis_addr, 2);
    emit1(p_cis_addr, 0xc);
    emit1(p_cis_addr, 0x0);
}

void emitfunce(uint32_t *p_cis_addr)
{
    uint32_t blksize;
    uint32_t speed;
    blksize = ROM_SDIO_F0_BLKSIZE;
    speed = ROM_SDIO_SPEED;
    emit1(p_cis_addr, CISTPL_FUNCE);
    emit1(p_cis_addr, 4);
    emit1(p_cis_addr, 0x0);
    emit2(p_cis_addr, blksize);
    emit1(p_cis_addr, speed);
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
    emit1(p_cis_addr, 0x2a);
    emit1(p_cis_addr, 0x01);
    emit1(p_cis_addr, 0x01);
    emit1(p_cis_addr, rev);
    emit4(p_cis_addr, 0x00000000);
    emit4(p_cis_addr, 0x00000000);
    emit1(p_cis_addr, 0x00);
    emit2(p_cis_addr, blksize);
    emit4(p_cis_addr, 0x01ff8000);
//    emit4(REG32(sdu_fnN_ocr_0(fn)));
    emit1(p_cis_addr, 0x00);
    emit1(p_cis_addr, 0x00);
    emit1(p_cis_addr, 0x00);
    emit1(p_cis_addr, 0x00);
    emit1(p_cis_addr, 0x00);
    emit1(p_cis_addr, 0x00);
    emit2(p_cis_addr, 0x0000);
    emit2(p_cis_addr, 0x0000);
    emit2(p_cis_addr, timeout);
    emit2(p_cis_addr, 0x0000);
    emit2(p_cis_addr, 0x0000);
    emit2(p_cis_addr, 0x0000);
    emit2(p_cis_addr, 0x0000);
    emit2(p_cis_addr, 0x0000);
    emit2(p_cis_addr, 0x0000);
}

uint32_t modify(uint32_t tmp, uint32_t hi, uint32_t lo, uint32_t val)
{
    uint32_t mask;
    uint32_t masklen;
    masklen = (hi - lo) + 1;      // Width of the field
    mask    = (1 << masklen) - 1; // Now as a mask
    val &= mask;                  // mask unshifted val
    val <<= lo;                   // Now move val to field off
    mask <<= lo;                  // mask moves too to field off
    tmp &= ~mask;                 // Clear R[hi:lo]
    tmp |= val;                   // Now M[hi:lo]
    return tmp;
}

uint32_t modify2(uint32_t tmp, uint32_t mask, uint32_t shift, uint32_t val)
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
    REG8(addr) = modify(REG8(addr), hi, lo, val);
}

uint32_t extract2(uint32_t data, uint32_t mask, uint32_t shift)
{
    uint32_t tmp;
    tmp = data;
    tmp >>= shift; // shift to 0
    mask >>= shift;
    tmp &= mask; // Knock off other bits
    return tmp;
}

uint32_t rd2(volatile uint32_t *addr, uint32_t mask, uint32_t shift)
{
    uint32_t data;
    data = *addr;
    return extract2(data, mask, shift);
}

void set_iomux_helper(uint32_t hi, uint32_t lo)
{
    uint32_t mask;
    uint32_t masklen;
    uint32_t val;
    volatile uint32_t *addr;
    if (hi < 32)
    {
        addr = &SOCCTRL->MCI_IOMUX_EN0;
    }
    else
    {
        hi -= 32;
        lo -= 32;
        addr = &SOCCTRL->MCI_IOMUX_EN1;
    }
    masklen = (hi - lo) + 1; // Field len
    mask    = (1 << masklen) - 1;
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
    if ((hi < 32) || (lo > 32))
    {
        set_iomux_helper(hi, lo);
    }
    else
    { // split
        set_iomux_helper(31, lo);
        set_iomux_helper(hi, 32);
    }
}
// legacy func
void post_gpio(uint32_t val)
{
    uint32_t port = 0;
    // vvvv this write... doesn't take. The loop... does.
    //    SOCCTRL->MCI_IOMUX_EN0 |= bit(3) | bit(2) | bit(1) | bit(0);
    set_iomux(3, 0);
#if 0
    do {
	rmw2(&SOCCTRL->MCI_IOMUX_EN0, 0xf, 0, 0xf);
    } while(rd2(&SOCCTRL->MCI_IOMUX_EN0, 0xf, 0) != 0xf);
#endif
    GPIO->DIRSET[port] = 0xf;
    MCI_IO_MUX->GPIO_GRP0 &= ~0xf;
    MCI_IO_MUX->GPIO_GRP0 |= 0xf;
    GPIO->PIN[port] &= ~0xf;
    GPIO->PIN[port] |= val & 0xf;
}
