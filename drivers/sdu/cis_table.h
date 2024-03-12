/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef CIS_TABLE_H
#define CIS_TABLE_H

#include <stdint.h>

#define REG8(x)  ((*(volatile uint8_t *)(x)))
#define REG16(x) ((*(volatile uint16_t *)(x)))
#define REG32(x) ((*(volatile uint32_t *)(x)))

void rmw2(volatile uint32_t *addr, uint32_t mask, uint32_t shift, uint32_t val);
void rmwb(uint32_t addr, uint32_t hi, uint32_t lo, uint32_t val);
void set_iomux(uint32_t hi, uint32_t lo);

void emit1(uint32_t *p_cis_addr, uint8_t x);
void emit2(uint32_t *p_cis_addr, uint16_t x);
void emit4(uint32_t *p_cis_addr, uint32_t x);
void emitvers(uint32_t *p_cis_addr, uint8_t *s, uint32_t subs);
void emitvidpid(uint32_t *p_cis_addr, uint32_t vid, uint32_t pid);
void emitfuncid(uint32_t *p_cis_addr);
void emitfunce(uint32_t *p_cis_addr);
void emitfunce_extended(uint32_t *p_cis_addr, uint32_t fn);

#endif
