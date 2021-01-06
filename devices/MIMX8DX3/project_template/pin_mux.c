/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2017-2018 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v3.0
processor: MIMX8QX6xxxFZ
mcu_data: i_mx_1_0
processor_version: 0.0.0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

#include "pin_mux.h"
#include "fsl_common.h"
#include "main/imx8qx_pads.h"
#include "svc/pad/pad_api.h"

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: m4}
- pin_list:
  - {pin_num: V30, peripheral: M40__UART0, signal: uart_tx, pin_signal: ADC_IN3, sw_config: sw_config_0}
  - {pin_num: V32, peripheral: M40__UART0, signal: uart_rx, pin_signal: ADC_IN2, sw_config: sw_config_0}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitPins(void) {                                /*!< Function assigned for the core: Cortex-M4F[m4] */
  sc_ipc_t ipc;
  sc_err_t err = SC_ERR_NONE;
  ipc = SystemGetScfwIpcHandle();

  err = sc_pad_set_all(ipc, SC_P_ADC_IN2, 1U, SC_PAD_CONFIG_NORMAL, SC_PAD_ISO_OFF, 0x0 ,SC_PAD_WAKEUP_OFF);/* IOMUXD_REG_ADC_IN2 register modification value */
  if (SC_ERR_NONE != err)
  {
      assert(false);
  }
  err = sc_pad_set_all(ipc, SC_P_ADC_IN3, 1U, SC_PAD_CONFIG_NORMAL, SC_PAD_ISO_OFF, 0x0 ,SC_PAD_WAKEUP_OFF);/* IOMUXD_REG_ADC_IN3 register modification value */
  if (SC_ERR_NONE != err)
  {
      assert(false);
  }
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
