/*
 * Copyright 2021-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "stddef.h"
#include "stdint.h"

#include "FreeRTOS.h"

#include "irq.h"

#define NR_IRQS 0x3FFUL

struct irq_handler {
	void (*func)(void *data);
	void *data;
};

static struct irq_handler handler[NR_IRQS];


int irq_register(int nr, void (*func)(void *data), void *data, unsigned int prio)
{
	struct irq_handler *hdlr;
	int ret = -1;

	if (nr >= NR_IRQS)
		goto exit;

	portDISABLE_INTERRUPTS();

	hdlr = &handler[nr];

	hdlr->func = func;
	hdlr->data = data;

	if (prio)
		GIC_SetPriority(nr, prio);

	ret = 0;

	portENABLE_INTERRUPTS();
exit:
	return ret;
}

int irq_unregister(int nr)
{
	struct irq_handler *hdlr;
	int ret = -1;

	if (nr >= NR_IRQS)
		goto exit;

	portDISABLE_INTERRUPTS();

	hdlr = &handler[nr];

	hdlr->func = NULL;
	hdlr->data = NULL;

	ret = 0;

	portENABLE_INTERRUPTS();
exit:
	return ret;
}

/* Called from port FreeRTOS_IRQ_Handler */
void vApplicationIRQHandler(uint32_t ulICCIAR)
{
	struct irq_handler *hdlr = NULL;
	unsigned int nr;

	/*
	 * TODO: For now interrupt nesting is disabled,
	 * IRQ stays disabled until the handler returns
	 */

	nr = ulICCIAR & NR_IRQS;

	if (nr < NR_IRQS)
		hdlr = &handler[nr];

	if (hdlr && hdlr->func)
		hdlr->func(hdlr->data);
}
