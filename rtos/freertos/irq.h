/*
 * Copyright 2021-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _IRQ_H_
#define _IRQ_H_

int irq_register(int nr, void (*func)(void *data), void *data, unsigned int prio);
int irq_unregister(int nr);

#endif /* _IRQ_H_ */
