/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _APP_DISPLAY_H_
#define _APP_DISPLAY_H_

#include <stdint.h>
#include <stdbool.h>

/*
 * This code enables the display to show the ISI input frames, in this example,
 * only RGB565 format is supported.
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*
 * The callback function is called when the display controller updated the use
 * the new frame buffer. The previous active frame buffer address is returned
 * so that it could be submited to the camera buffer queue.
 */
typedef void (*app_display_callback_t)(uint32_t frameBuffer);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif
/*
 * Init and start the display controller with the init frame buffer.
 */
void APP_InitDisplay(uint32_t frameBuffer, app_display_callback_t callback);

/*
 * Check whether the new setting frame buffer is still pending.
 */
bool APP_IsDisplayFramePending(void);

/*
 * Set the new frame buffer to display controller.
 */
void APP_SetDisplayFrameBuffer(uint32_t frameBuffer);

/*
 * Display controller IRQ handler that should be installed into the vector table.
 */
void APP_DisplayIRQHandler(void);

/* Set the ISI access permission to frame buffer. */
void APP_SetIsiPermission(uint64_t startAddr, uint64_t endAddr);
/* Unset the ISI access permission to frame buffer. */
void APP_UnsetIsiPermission(void);
/* Prepare the display, such as enable display module clock and interrupts. */
void APP_PrepareDisplay(void);
/* Unprepare the display. */
void APP_UnprepareDisplay(void);
/* Prepare the camera, such as enable camera module clock and interrupts. */
void APP_PrepareCamera(void);
/* Unprepare the camera, such as disable camera module clock and interrupts. */
void APP_UnprepareCamera(void);
/* Initialize the MIPI CSI. */
void APP_InitCameraInterface(void);
/* Deinitialize the MIPI CSI. */
void APP_DeinitCameraInterface(void);
/* Init pixel link. */
void APP_InitPixelLink(void);
/* Start display interface */
void APP_StartDisplayInterface(void);
/* Stop display interface */
void APP_StopDisplayInterface(void);
/*Init LCD Panel*/
void APP_InitLcdPanel(void);
/*Deinit LCD Panel*/
void APP_DeinitLcdPanel(void);

#if defined(__cplusplus)
}
#endif

#endif /* _APP_DISPLAY_H_ */
