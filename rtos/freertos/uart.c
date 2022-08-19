/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "FreeRTOS.h"
#include "task.h"

#include "fsl_debug_console.h"

#include "board.h"
#include "irq.h"

#if (defined(UART_ADAPTER_NON_BLOCKING_MODE) && (UART_ADAPTER_NON_BLOCKING_MODE > 0U))
#define uart_task_PRIORITY   (1)

extern void BOARD_UART_IRQ_HANDLER(void);

static TaskHandle_t uart_task_h;

static void uart_task(void *pvParameters)
{
	while (1) {
		xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
		BOARD_UART_IRQ_HANDLER();
		EnableIRQ(BOARD_UART_IRQ);
	}
}

static void uart_irq_handler(void *data)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	DisableIRQ(BOARD_UART_IRQ);

	vTaskNotifyGiveFromISR(uart_task_h, &xHigherPriorityTaskWoken);

	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

static void uart_irq_init(void)
{
	BaseType_t xResult;

	irq_register(BOARD_UART_IRQ, uart_irq_handler, NULL, 0);

	GIC_SetRedistPriority(BOARD_UART_IRQ, (portLOWEST_USABLE_INTERRUPT_PRIORITY - 1) << portPRIORITY_SHIFT);

	GIC_SetPriority(BOARD_UART_IRQ, (portLOWEST_USABLE_INTERRUPT_PRIORITY - 1) << portPRIORITY_SHIFT);

	xResult = xTaskCreate(uart_task, "uart_task",
			configMINIMAL_STACK_SIZE + 200, NULL,
			uart_task_PRIORITY, &uart_task_h);

	configASSERT(xResult == pdPASS);

	EnableIRQ(BOARD_UART_IRQ);
}
#else
static void uart_irq_init(void) {}
#endif

void uart_init(void)
{
	uint32_t uartClkSrcFreq = BOARD_DEBUG_UART_CLK_FREQ;

	DbgConsole_Init(BOARD_DEBUG_UART_INSTANCE, BOARD_DEBUG_UART_BAUDRATE, BOARD_DEBUG_UART_TYPE, uartClkSrcFreq);

	uart_irq_init();
}
