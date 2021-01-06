/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2017-2019 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * Header file containing the public API for the System Controller (SC)
 * Power Management (PM) function. This includes functions for power state
 * control, clock control, reset control, and wake-up event control.
 *
 * @addtogroup PM_SVC PM: Power Management Service
 *
 * Module for the Power Management (PM) service.
 *
 * @includedoc pm/details.dox
 *
 * @{
 */

#ifndef SC_PM_API_H
#define SC_PM_API_H

/* Includes */

#include "main/types.h"
#include "svc/rm/rm_api.h"

/* Defines */

/*!
 * @name Defines for type widths
 */
/*@{*/
#define SC_PM_POWER_MODE_W      2U      /*!< Width of sc_pm_power_mode_t */
#define SC_PM_CLOCK_MODE_W      3U      /*!< Width of sc_pm_clock_mode_t */
#define SC_PM_RESET_TYPE_W      2U      /*!< Width of sc_pm_reset_type_t */
#define SC_PM_RESET_REASON_W    4U      /*!< Width of sc_pm_reset_reason_t */
/*@}*/

/*!
 * @name Defines for clock indexes (sc_pm_clk_t)
 */
/*@{*/
/*@}*/

/*!
 * @name Defines for ALL parameters
 */
/*@{*/
#define SC_PM_CLK_ALL   ((sc_pm_clk_t) UINT8_MAX)   /*!< All clocks */
/*@}*/

/*!
 * @name Defines for sc_pm_power_mode_t
 */
/*@{*/
#define SC_PM_PW_MODE_OFF       0U      /*!< Power off */
#define SC_PM_PW_MODE_STBY      1U      /*!< Power in standby */
#define SC_PM_PW_MODE_LP        2U      /*!< Power in low-power */
#define SC_PM_PW_MODE_ON        3U      /*!< Power on */
/*@}*/

/*!
 * @name Defines for sc_pm_clk_t
 */
/*@{*/
#define SC_PM_CLK_SLV_BUS       0U      /*!< Slave bus clock */
#define SC_PM_CLK_MST_BUS       1U      /*!< Master bus clock */
#define SC_PM_CLK_PER           2U      /*!< Peripheral clock */
#define SC_PM_CLK_PHY           3U      /*!< Phy clock */
#define SC_PM_CLK_MISC          4U      /*!< Misc clock */
#define SC_PM_CLK_MISC0         0U      /*!< Misc 0 clock */
#define SC_PM_CLK_MISC1         1U      /*!< Misc 1 clock */
#define SC_PM_CLK_MISC2         2U      /*!< Misc 2 clock */
#define SC_PM_CLK_MISC3         3U      /*!< Misc 3 clock */
#define SC_PM_CLK_MISC4         4U      /*!< Misc 4 clock */
#define SC_PM_CLK_CPU           2U      /*!< CPU clock */
#define SC_PM_CLK_PLL           4U      /*!< PLL */
#define SC_PM_CLK_BYPASS        4U      /*!< Bypass clock */
/*@}*/

/*!
 * @name Defines for sc_pm_clk_mode_t
 */
/*@{*/
#define SC_PM_CLK_MODE_ROM_INIT        0U    /*!< Clock is initialized by ROM */
#define SC_PM_CLK_MODE_OFF             1U    /*!< Clock is disabled */
#define SC_PM_CLK_MODE_ON              2U    /*!< Clock is enabled */
#define SC_PM_CLK_MODE_AUTOGATE_SW     3U    /*!< Clock is in SW autogate mode */
#define SC_PM_CLK_MODE_AUTOGATE_HW     4U    /*!< Clock is in HW autogate mode */
#define SC_PM_CLK_MODE_AUTOGATE_SW_HW  5U    /*!< Clock is in SW-HW autogate mode */
/*@}*/

/*!
 * @name Defines for sc_pm_clk_parent_t
 */
/*@{*/
#define SC_PM_PARENT_XTAL              0U    /*!< Parent is XTAL */
#define SC_PM_PARENT_PLL0              1U    /*!< Parent is PLL0 */
#define SC_PM_PARENT_PLL1              2U    /*!< Parent is PLL1 or PLL0/2 */
#define SC_PM_PARENT_PLL2              3U    /*!< Parent in PLL2 or PLL0/4 */
#define SC_PM_PARENT_BYPS              4U    /*!< Parent is a bypass clock. */
/*@}*/

/*!
 * @name Defines for sc_pm_reset_type_t
 */
/*@{*/
#define SC_PM_RESET_TYPE_COLD          0U    /*!< Cold reset */
#define SC_PM_RESET_TYPE_WARM          1U    /*!< Warm reset */
#define SC_PM_RESET_TYPE_BOARD         2U    /*!< Board reset */
/*@}*/

/*!
 * @name Defines for sc_pm_reset_reason_t
 */
/*@{*/
#define SC_PM_RESET_REASON_POR         0U    /*!< Power on reset */
#define SC_PM_RESET_REASON_JTAG        1U    /*!< JTAG reset */
#define SC_PM_RESET_REASON_SW          2U    /*!< Software reset */
#define SC_PM_RESET_REASON_WDOG        3U    /*!< Partition watchdog reset */
#define SC_PM_RESET_REASON_LOCKUP      4U    /*!< SCU lockup reset */
#define SC_PM_RESET_REASON_SNVS        5U    /*!< SNVS reset */
#define SC_PM_RESET_REASON_TEMP        6U    /*!< Temp panic reset */
#define SC_PM_RESET_REASON_MSI         7U    /*!< MSI reset */
#define SC_PM_RESET_REASON_UECC        8U    /*!< ECC reset */
#define SC_PM_RESET_REASON_SCFW_WDOG   9U    /*!< SCFW watchdog reset */
#define SC_PM_RESET_REASON_ROM_WDOG    10U   /*!< SCU ROM watchdog reset */
#define SC_PM_RESET_REASON_SECO        11U   /*!< SECO reset */
#define SC_PM_RESET_REASON_SCFW_FAULT  12U   /*!< SCFW fault reset */
/*@}*/

/*!
 * @name Defines for sc_pm_sys_if_t
 */
/*@{*/
#define SC_PM_SYS_IF_INTERCONNECT       0U   /*!< System interconnect */
#define SC_PM_SYS_IF_MU                 1U   /*!< AP -> SCU message units */
#define SC_PM_SYS_IF_OCMEM              2U   /*!< On-chip memory (ROM/OCRAM) */
#define SC_PM_SYS_IF_DDR                3U   /*!< DDR memory */
/*@}*/

/*!
 * @name Defines for sc_pm_wake_src_t
 */
/*@{*/
#define SC_PM_WAKE_SRC_NONE             0U   /*!< No wake source, used for self-kill */
#define SC_PM_WAKE_SRC_SCU              1U   /*!< Wakeup from SCU to resume CPU (IRQSTEER & GIC powered down) */
#define SC_PM_WAKE_SRC_IRQSTEER         2U   /*!< Wakeup from IRQSTEER to resume CPU (GIC powered down) */
#define SC_PM_WAKE_SRC_IRQSTEER_GIC     3U   /*!< Wakeup from IRQSTEER+GIC to wake CPU  (GIC clock gated) */
#define SC_PM_WAKE_SRC_GIC              4U   /*!< Wakeup from GIC to wake CPU */
/*@}*/

/* Types */

/*!
 * This type is used to declare a power mode. Note resources only use
 * SC_PM_PW_MODE_OFF and SC_PM_PW_MODE_ON. The other modes are used only
 * as system power modes.
 */
typedef uint8_t sc_pm_power_mode_t;

/*!
 * This type is used to declare a clock.
 */
typedef uint8_t sc_pm_clk_t;

/*!
 * This type is used to declare a clock mode.
 */
typedef uint8_t sc_pm_clk_mode_t;

/*!
 * This type is used to declare the clock parent.
 */
typedef uint8_t sc_pm_clk_parent_t;

/*!
 * This type is used to declare clock rates.
 */
typedef uint32_t sc_pm_clock_rate_t;

/*!
 * This type is used to declare a desired reset type.
 */
typedef uint8_t sc_pm_reset_type_t;

/*!
 * This type is used to declare a reason for a reset.
 */
typedef uint8_t sc_pm_reset_reason_t;

/*!
 * This type is used to specify a system-level interface to be power managed.
 */
typedef uint8_t sc_pm_sys_if_t;

/*!
 * This type is used to specify a wake source for CPU resources.
 */
typedef uint8_t sc_pm_wake_src_t;

/* Functions */

/*!
 * @name Power Functions
 * @{
 */

/*!
 * This function sets the system power mode. Only the owner of the
 * SC_R_SYSTEM resource or a partition with access permissions to
 * SC_R_SYSTEM can do this.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     mode        power mode to apply
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors:
 * - SC_ERR_PARM if invalid mode,
 * - SC_ERR_NOACCESS if caller does not have SC_R_SYSTEM access
 *
 * @see sc_pm_set_sys_power_mode().
 */
sc_err_t sc_pm_set_sys_power_mode(sc_ipc_t ipc, sc_pm_power_mode_t mode);

/*!
 * This function sets the power mode of a partition.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     pt          handle of partition
 * @param[in]     mode        power mode to apply
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors:
 * - SC_ERR_PARM if invalid partition or mode != SC_PM_PW_MODE_OFF,
 * - SC_ERR_NOACCESS if caller's partition is not the owner or
 *   parent of \a pt
 *
 * This function can only be used to turn off a partition by calling
 * with mode equal to SC_PM_PW_MODE_OFF. After turning off, the partition
 * can be booted with sc_pm_reboot_partition() or sc_pm_boot(). It cannot
 * be used to turn off the calling partition as the MU could not return
 * the an error response.
 *
 * For dynamic power management of a partition, use
 * sc_pm_req_low_power_mode(), sc_pm_req_cpu_low_power_mode(),
 * and sc_pm_req_sys_if_power_mode() with a WFI for controlled power
 * state transitions.
 */
sc_err_t sc_pm_set_partition_power_mode(sc_ipc_t ipc, sc_rm_pt_t pt,
    sc_pm_power_mode_t mode);

/*!
 * This function gets the power mode of a partition.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     pt          handle of partition
 * @param[out]    mode        pointer to return power mode
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors:
 * - SC_ERR_PARM if invalid partition
 */
sc_err_t sc_pm_get_sys_power_mode(sc_ipc_t ipc, sc_rm_pt_t pt,
    sc_pm_power_mode_t *mode);

/*!
 * This function sends a wake interrupt to a partition.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     pt          handle of partition to wake
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * An SC_IRQ_SW_WAKE interrupt is sent to all MUs owned by the
 * partition that have this interrupt enabled. The CPU using an
 * MU will exit a low-power state to service the MU interrupt.
 *
 * Return errors:
 * - SC_ERR_PARM if invalid partition
 */
sc_err_t sc_pm_partition_wake(sc_ipc_t ipc, sc_rm_pt_t pt);

/*!
 * This function sets the power mode of a resource.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     resource    ID of the resource
 * @param[in]     mode        power mode to apply
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors:
 * - SC_ERR_PARM if invalid resource or mode,
 * - SC_ERR_PARM if resource is the MU used to make the call,
 * - SC_ERR_NOACCESS if caller's partition is not the resource owner
 *   or parent of the owner
 *
 * Resources must be at SC_PM_PW_MODE_LP mode or higher to access them,
 * otherwise the master will get a bus error or hang.
 *
 * Note some resources are still not accessible even when powered up if bus
 * transactions go through a fabric not powered up. Examples of this are
 * resources in display and capture subsystems which require the display
 * controller or the imaging subsystem to be powered up first.
 *
 * Not that resources are grouped into power domains by the underlying
 * hardware. If any resource in the domain is on, the entire power domain
 * will be on. Other power domains required to access the resource will
 * also be turned on. Clocks required to access the peripheral will be
 * turned on. Refer to the SoC RM for more info on power domains and access
 * infrastructure (bus fabrics, clock domains, etc.).
 */
sc_err_t sc_pm_set_resource_power_mode(sc_ipc_t ipc, sc_rsrc_t resource,
    sc_pm_power_mode_t mode);

/*!
* This function sets the power mode for all the resources owned
* by a child partition.
*
* @param[in]     ipc         IPC handle
* @param[in]     pt          handle of child partition
* @param[in]     mode        power mode to apply
* @param[in]     exclude     resource to exclude
*
* @return Returns an error code (SC_ERR_NONE = success).
*
* Return errors:
* - SC_ERR_PARM if invalid partition or mode,
* - SC_ERR_NOACCESS if caller's partition is not the parent
*   (with grant) of \a pt
*
* This functions loops through all the resources owned by \a pt
* and sets the power mode to \a mode. It will skip setting
* \a exclude (SC_R_LAST to skip none).
*
* This function can only be called by the parent. It is used to
* implement some aspects of virtualization.
*/
sc_err_t sc_pm_set_resource_power_mode_all(sc_ipc_t ipc,
    sc_rm_pt_t pt, sc_pm_power_mode_t mode, sc_rsrc_t exclude);

/*!
 * This function gets the power mode of a resource.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     resource    ID of the resource
 * @param[out]    mode        pointer to return power mode
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Note only SC_PM_PW_MODE_OFF and SC_PM_PW_MODE_ON are valid. The value
 * returned does not reflect the power mode of the partition..
 */
sc_err_t sc_pm_get_resource_power_mode(sc_ipc_t ipc, sc_rsrc_t resource,
    sc_pm_power_mode_t *mode);

/*!
 * This function specifies the low power mode some of the resources
 * can enter based on their state. This API is only valid for the
 * following resources : SC_R_A53, SC_R_A53_0, SC_R_A53_1, SC_A53_2,
 * SC_A53_3, SC_R_A72, SC_R_A72_0, SC_R_A72_1, SC_R_CC1, SC_R_A35,
 * SC_R_A35_0, SC_R_A35_1, SC_R_A35_2, SC_R_A35_3.
 * For all other resources it will return SC_ERR_PARAM.
 * This function will set the low power mode the cores, cluster
 * and cluster associated resources will enter when all the cores
 * in a given cluster execute WFI
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     resource    ID of the resource
 * @param[in]     mode        power mode to apply
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 */
sc_err_t sc_pm_req_low_power_mode(sc_ipc_t ipc, sc_rsrc_t resource,
    sc_pm_power_mode_t mode);

/*!
 * This function requests low-power mode entry for CPU/cluster
 * resources. This API is only valid for the following resources:
 * SC_R_A53, SC_R_A53_x, SC_R_A72, SC_R_A72_x, SC_R_A35, SC_R_A35_x,
 * SC_R_CCI. For all other resources it will return SC_ERR_PARAM.
 * For individual core resources, the specified power mode
 * and wake source will be applied after the core has entered
 * WFI.  For cluster resources, the specified power mode is
 * applied after all cores in the cluster have entered low-power mode.
 * For multicluster resources, the specified power mode is applied
 * after all clusters have reached low-power mode.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     resource    ID of the resource
 * @param[in]     mode        power mode to apply
 * @param[in]     wake_src    wake source for low-power exit
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 */
sc_err_t sc_pm_req_cpu_low_power_mode(sc_ipc_t ipc, sc_rsrc_t resource,
    sc_pm_power_mode_t mode, sc_pm_wake_src_t wake_src);

/*!
 * This function is used to set the resume address of a CPU.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     resource    ID of the CPU resource
 * @param[in]     address     64-bit resume address
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors:
 * - SC_ERR_PARM if invalid resource or address,
 * - SC_ERR_NOACCESS if caller's partition is not the parent of the
 *   resource (CPU) owner
 *
 * Note the address is limited by the hardware implementation. See the
 * [CPU Start Address](@ref BOOT_ADDR) section in the Porting Guide.
 */
sc_err_t sc_pm_set_cpu_resume_addr(sc_ipc_t ipc, sc_rsrc_t resource,
    sc_faddr_t address);

/*!
 * This function is used to set parameters for CPU resume from
 * low-power mode.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     resource    ID of the CPU resource
 * @param[in]     isPrimary   set SC_TRUE if primary wake CPU
 * @param[in]     address     64-bit resume address
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors:
 * - SC_ERR_PARM if invalid resource or address,
 * - SC_ERR_NOACCESS if caller's partition is not the parent of the
 *   resource (CPU) owner
 *
 * Note the address is limited by the hardware implementation. See the
 * [CPU Start Address](@ref BOOT_ADDR) section in the Porting Guide.
 */
sc_err_t sc_pm_set_cpu_resume(sc_ipc_t ipc, sc_rsrc_t resource,
    sc_bool_t isPrimary, sc_faddr_t address);

/*!
 * This function requests the power mode configuration for system-level
 * interfaces including messaging units, interconnect, and memories. This API
 * is only valid for the following resources : SC_R_A53, SC_R_A72, and
 * SC_R_M4_x_PID_y.  For all other resources, it will return SC_ERR_PARAM.
 * The requested power mode will be captured and applied to system-level
 * resources as system conditions allow.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     resource    ID of the resource
 * @param[in]     sys_if      system-level interface to be configured
 * @param[in]     hpm         high-power mode for the system interface
 * @param[in]     lpm         low-power mode for the system interface
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 */
sc_err_t sc_pm_req_sys_if_power_mode(sc_ipc_t ipc, sc_rsrc_t resource,
    sc_pm_sys_if_t sys_if, sc_pm_power_mode_t hpm, sc_pm_power_mode_t lpm);

/* @} */

/*!
 * @name Clock/PLL Functions
 * @{
 */

/*!
 * This function sets the rate of a resource's clock/PLL.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     resource    ID of the resource
 * @param[in]     clk         clock/PLL to affect
 * @param[in,out] rate        pointer to rate to set,
 *                            return actual rate
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors:
 * - SC_ERR_PARM if invalid resource or clock/PLL,
 * - SC_ERR_NOACCESS if caller's partition is not the resource owner
 *   or parent of the owner,
 * - SC_ERR_UNAVAILABLE if clock/PLL not applicable to this resource,
 * - SC_ERR_LOCKED if rate locked (usually because shared clock/PLL)
 *
 * Refer to the [Clock List](@ref CLOCKS) for valid clock/PLL values.
 */
sc_err_t sc_pm_set_clock_rate(sc_ipc_t ipc, sc_rsrc_t resource,
    sc_pm_clk_t clk, sc_pm_clock_rate_t *rate);

/*!
 * This function gets the rate of a resource's clock/PLL.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     resource    ID of the resource
 * @param[in]     clk         clock/PLL to affect
 * @param[out]    rate        pointer to return rate
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors:
 * - SC_ERR_PARM if invalid resource or clock/PLL,
 * - SC_ERR_NOACCESS if caller's partition is not the resource owner
 *   or parent of the owner,
 * - SC_ERR_UNAVAILABLE if clock/PLL not applicable to this resource
 *
 * This function returns the actual clock rate of the hardware. This rate
 * may be different from the original requested clock rate if the resource
 * is set to a low power mode.
 *
 * Refer to the [Clock List](@ref CLOCKS) for valid clock/PLL values.
 */
sc_err_t sc_pm_get_clock_rate(sc_ipc_t ipc, sc_rsrc_t resource,
    sc_pm_clk_t clk, sc_pm_clock_rate_t *rate);

/*!
 * This function enables/disables a resource's clock.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     resource    ID of the resource
 * @param[in]     clk         clock to affect
 * @param[in]     enable      enable if SC_TRUE; otherwise disabled
 * @param[in]     autog       HW auto clock gating
 *
 * If \a resource is SC_R_ALL then all resources owned will be affected.
 * No error will be returned.
 *
 * If \a clk is SC_PM_CLK_ALL, then an error will be returned if any
 * of the available clocks returns an error.
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors:
 * - SC_ERR_PARM if invalid resource or clock,
 * - SC_ERR_NOACCESS if caller's partition is not the resource owner
 *   or parent (with grant) of the owner,
 * - SC_ERR_UNAVAILABLE if clock not applicable to this resource
 *
 * Refer to the [Clock List](@ref CLOCKS) for valid clock values.
 */
sc_err_t sc_pm_clock_enable(sc_ipc_t ipc, sc_rsrc_t resource,
    sc_pm_clk_t clk, sc_bool_t enable, sc_bool_t autog);

/*!
 * This function sets the parent of a resource's clock.
 * This function should only be called when the clock is disabled.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     resource    ID of the resource
 * @param[in]     clk         clock to affect
 * @param[in]     parent      New parent of the clock
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors:
 * - SC_ERR_PARM if invalid resource or clock,
 * - SC_ERR_NOACCESS if caller's partition is not the resource owner
 *   or parent (with grant) of the owner,
 * - SC_ERR_UNAVAILABLE if clock not applicable to this resource
 * - SC_ERR_BUSY if clock is currently enabled.
 * - SC_ERR_NOPOWER if resource not powered
 *
 * Refer to the [Clock List](@ref CLOCKS) for valid clock values.
 */
sc_err_t sc_pm_set_clock_parent(sc_ipc_t ipc, sc_rsrc_t resource,
    sc_pm_clk_t clk, sc_pm_clk_parent_t parent);

/*!
 * This function gets the parent of a resource's clock.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     resource    ID of the resource
 * @param[in]     clk         clock to affect
 * @param[out]     parent     pointer to return parent of clock
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors:
 * - SC_ERR_PARM if invalid resource or clock,
 * - SC_ERR_NOACCESS if caller's partition is not the resource owner
 *   or parent of the owner,
 * - SC_ERR_UNAVAILABLE if clock not applicable to this resource
 *
 * Refer to the [Clock List](@ref CLOCKS) for valid clock values.
 */
sc_err_t sc_pm_get_clock_parent(sc_ipc_t ipc, sc_rsrc_t resource,
    sc_pm_clk_t clk, sc_pm_clk_parent_t *parent);

/* @} */

/*!
 * @name Reset Functions
 * @{
 */

/*!
 * This function is used to reset the system. Only the owner of the
 * SC_R_SYSTEM resource or a partition with access permissions to
 * SC_R_SYSTEM can do this.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     type        reset type
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors:
 * - SC_ERR_PARM if invalid type,
 * - SC_ERR_NOACCESS if caller cannot access SC_R_SYSTEM
 *
 * If this function returns, then the reset did not occur due to an
 * invalid parameter.
 */
sc_err_t sc_pm_reset(sc_ipc_t ipc, sc_pm_reset_type_t type);

/*!
 * This function gets a caller's reset reason.
 *
 * @param[in]     ipc         IPC handle
 * @param[out]    reason      pointer to return the reset reason
 *
 * This function returns the reason a partition was reset. If the reason
 * is POR, then the system reset reason will be returned.
 *
 * Note depending on the connection of the WDOG_OUT signal and the OTP
 * programming of the PMIC, some resets may trigger a system POR
 * and the original reason will be lost.
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 */
sc_err_t sc_pm_reset_reason(sc_ipc_t ipc, sc_pm_reset_reason_t *reason);

/*!
 * This function gets the partition that caused a reset.
 *
 * @param[in]     ipc         IPC handle
 * @param[out]    pt          pointer to return the resetting partition
 *
 * If the reset reason obtained via sc_pm_reset_reason() is POR then the
 * result from this function will be 0. Some SECO causes of reset will
 * also return 0.
 *
 * Note depending on the connection of the WDOG_OUT signal and the OTP
 * programming of the PMIC, some resets may trigger a system POR
 * and the partition info will be lost.
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 */
sc_err_t sc_pm_get_reset_part(sc_ipc_t ipc, sc_rm_pt_t *pt);

/*!
 * This function is used to boot a partition.
 *
 * @param[in]     ipc          IPC handle
 * @param[in]     pt           handle of partition to boot
 * @param[in]     resource_cpu ID of the CPU resource to start
 * @param[in]     boot_addr    64-bit boot address
 * @param[in]     resource_mu  ID of the MU that must be powered
 * @param[in]     resource_dev ID of the boot device that must be powered
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors:
 * - SC_ERR_PARM if invalid partition, resource, or addr,
 * - SC_ERR_NOACCESS if caller's partition is not the parent of the
 *   partition to boot
 *
 * This must be used to boot a partition. Only a partition booted this
 * way can be rebooted using the watchdog, sc_pm_boot() or
 * sc_pm_reboot_partition().
 *
 * Note the address is limited by the hardware implementation. See the
 * [CPU Start Address](@ref BOOT_ADDR) section in the Porting Guide.
 */
sc_err_t sc_pm_boot(sc_ipc_t ipc, sc_rm_pt_t pt,
    sc_rsrc_t resource_cpu, sc_faddr_t boot_addr,
    sc_rsrc_t resource_mu, sc_rsrc_t resource_dev);

/*!
 * This function is used to change the boot parameters for a partition.
 *
 * @param[in]     ipc          IPC handle
 * @param[in]     resource_cpu ID of the CPU resource to start
 * @param[in]     boot_addr    64-bit boot address
 * @param[in]     resource_mu  ID of the MU that must be powered (0=none)
 * @param[in]     resource_dev ID of the boot device that must be powered (0=none)
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors:
 * - SC_ERR_PARM if invalid resource, or addr
 *
 * This function can be used to change the boot parameters for a partition.
 * This can be useful if a partitions reboots differently from the initial
 * boot done via sc_pm_boot() or via ROM.
 *
 * Note the address is limited by the hardware implementation. See the
 * [CPU Start Address](@ref BOOT_ADDR) section in the Porting Guide.
 */
sc_err_t sc_pm_set_boot_parm(sc_ipc_t ipc,
    sc_rsrc_t resource_cpu, sc_faddr_t boot_addr,
    sc_rsrc_t resource_mu, sc_rsrc_t resource_dev);

/*!
 * This function is used to reboot the caller's partition.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     type        reset type
 *
 * If \a type is SC_PM_RESET_TYPE_COLD, then most peripherals owned by
 * the calling partition will be reset if possible. SC state (partitions,
 * power, clocks, etc.) is reset. The boot SW of the booting CPU must be
 * able to handle peripherals that that are not reset.
 *
 * If \a type is SC_PM_RESET_TYPE_WARM or SC_PM_RESET_TYPE_BOARD, then
 * returns SC_ERR_PARM as these are not supported.
 *
 * If this function returns, then the reset did not occur due to an
 * invalid parameter.
 */
void sc_pm_reboot(sc_ipc_t ipc, sc_pm_reset_type_t type);

/*!
 * This function is used to reboot a partition.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     pt          handle of partition to reboot
 * @param[in]     type        reset type
 *
 * If \a type is SC_PM_RESET_TYPE_COLD, then most peripherals owned by
 * the calling partition will be reset if possible. SC state (partitions,
 * power, clocks, etc.) is reset. The boot SW of the booting CPU must be
 * able to handle peripherals that that are not reset.
 *
 * If \a type is SC_PM_RESET_TYPE_WARM or SC_PM_RESET_TYPE_BOARD, then
 * returns SC_ERR_PARM as these are not supported.
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors:
 * - SC_ERR_PARM if invalid partition or type
 * - SC_ERR_NOACCESS if caller's partition is not the parent of \a pt
 *   and the caller does not have access to SC_R_SYSTEM
 *
 * Most peripherals owned by the partition will be reset if
 * possible. SC state (partitions, power, clocks, etc.) is reset. The
 * boot SW of the booting CPU must be able to handle peripherals that
 * that are not reset.
 *
 * If board_reboot_part() returns a non-0 mask, then the reboot will
 * be delayed until all partitions indicated in the mask have called
 * sc_pm_reboot_continue() to continue the boot.
 */
sc_err_t sc_pm_reboot_partition(sc_ipc_t ipc, sc_rm_pt_t pt,
    sc_pm_reset_type_t type);

/*!
 * This function is used to continue the reboot a partition.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     pt          handle of partition to continue
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors:
 * - SC_ERR_PARM if invalid partition
 */
sc_err_t sc_pm_reboot_continue(sc_ipc_t ipc, sc_rm_pt_t pt);

/*!
 * This function is used to start/stop a CPU.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     resource    ID of the CPU resource
 * @param[in]     enable      start if SC_TRUE; otherwise stop
 * @param[in]     address     64-bit boot address
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors:
 * - SC_ERR_PARM if invalid resource or address,
 * - SC_ERR_NOACCESS if caller's partition is not the parent of the
 *   resource (CPU) owner
 *
 * This function is usually used to start a secondary CPU in the
 * same partition as the caller. It is not used to start the first
 * CPU in a dedicated partition. That would be started by calling
 * sc_pm_boot().
 *
 * A CPU started with sc_pm_cpu_start() will not restart as a result
 * of a watchdog event or calling sc_pm_reboot() or sc_pm_reboot_partition().
 * Those will reboot that partition which will start the CPU started with
 * sc_pm_boot().
 *
 * Note the address is limited by the hardware implementation. See the
 * [CPU Start Address](@ref BOOT_ADDR) section in the Porting Guide.
 */
sc_err_t sc_pm_cpu_start(sc_ipc_t ipc, sc_rsrc_t resource, sc_bool_t enable,
    sc_faddr_t address);

/*!
 * This function is used to reset a CPU.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     resource    ID of the CPU resource
 * @param[in]     address     64-bit boot address
 *
 * This function does not return anything as the calling core may have been
 * reset. It can still fail if the resource or address is invalid. It can also
 * fail if the caller's partition is not the owner of the CPU, not the parent
 * of the CPU resource owner, or has access to SC_R_SYSTEM. Will also fail if
 * the resource is not powered on. No indication of failure is returned.
 *
 * Note this just resets the CPU. None of the peripherals or bus fabric used by
 * the CPU is reset. State configured in the SCFW is not reset. The SW running
 * on the core has to understand and deal with this.
 *
 * The address is limited by the hardware implementation. See the
 * [CPU Start Address](@ref BOOT_ADDR) section in the Porting Guide.
 */
void sc_pm_cpu_reset(sc_ipc_t ipc, sc_rsrc_t resource, sc_faddr_t address);

/*!
 * This function is used to reset a peripheral.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     resource    resource to reset
 *
 * This function will reset a resource. Most resources cannot be reset unless
 * the SoC design specifically allows it. In the case on MUs, the IPC/RPC
 * protocol is also reset. Note a caller cannot reset an MU that this API
 * call is sent on.
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors:
 * - SC_ERR_PARM if invalid resource,
 * - SC_ERR_PARM if resource is the MU used to make the call,
 * - SC_ERR_NOACCESS if caller's partition is not the resource owner or parent
 *   (with grant) of the owner,
 * - SC_ERR_BUSY if the resource cannot be reset due to power state of buses,
 * - SC_ERR_UNAVAILABLE if the resource cannot be reset due to hardware limitations
 */
sc_err_t sc_pm_resource_reset(sc_ipc_t ipc, sc_rsrc_t resource);

/*!
 * This function returns a bool indicating if a partition was started.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     pt          handle of partition to check
 *
 * @return Returns a bool (SC_TRUE = started).
 *
 * Note this indicates if a partition was started. It does not indicate if a
 * partition is currently running or in a low power state.
 */
sc_bool_t sc_pm_is_partition_started(sc_ipc_t ipc, sc_rm_pt_t pt);

/* @} */

#endif /* SC_PM_API_H */

/**@}*/

