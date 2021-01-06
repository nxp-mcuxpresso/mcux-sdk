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
 * Security (SECO) function.
 *
 * @addtogroup SECO_SVC SECO: Security Service
 *
 * Module for the Security (SECO) service.
 *
 * @anchor seco_err
 *
 * @includedoc seco/details.dox
 *
 * @{
 */

#ifndef SC_SECO_API_H
#define SC_SECO_API_H

/* Includes */

#include "main/types.h"
#include "svc/rm/rm_api.h"

/* Defines */

/*!
 * @name Defines for sc_seco_auth_cmd_t
 */
/*@{*/
#define SC_SECO_AUTH_CONTAINER          0U   /*!< Authenticate container */
#define SC_SECO_VERIFY_IMAGE            1U   /*!< Verify image */
#define SC_SECO_REL_CONTAINER           2U   /*!< Release container */
#define SC_SECO_AUTH_SECO_FW            3U   /*!< SECO Firmware */
#define SC_SECO_AUTH_HDMI_TX_FW         4U   /*!< HDMI TX Firmware */
#define SC_SECO_AUTH_HDMI_RX_FW         5U   /*!< HDMI RX Firmware */
#define SC_SECO_EVERIFY_IMAGE           6U   /*!< Enhanced verify image */
/*@}*/

/*!
 * @name Defines for seco_rng_stat_t
 */
/*@{*/
#define SC_SECO_RNG_STAT_UNAVAILABLE    0U  /*!< Unable to initialize the RNG */
#define SC_SECO_RNG_STAT_INPROGRESS     1U  /*!< Initialization is on-going */
#define SC_SECO_RNG_STAT_READY          2U  /*!< Initialized */
/*@}*/

/* Types */

/*!
 * This type is used to issue SECO authenticate commands.
 */
typedef uint8_t sc_seco_auth_cmd_t;

/*!
 * This type is used to return the RNG initialization status.
 */
typedef uint32_t sc_seco_rng_stat_t;

/* Functions */

/*!
 * @name Image Functions
 * @{
 */

/*!
 * This function loads a SECO image.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     addr_src    address of image source
 * @param[in]     addr_dst    address of image destination
 * @param[in]     len         length of image to load
 * @param[in]     fw          SC_TRUE = firmware load
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors codes:
 * - SC_ERR_PARM if word fuse index param out of range or invalid,
 * - SC_ERR_UNAVAILABLE if SECO not available,
 * - SC_ERR_IPC if SECO response has bad header tag or size,
 * - SC_ERR_VERSION if SECO response has bad version,
 * - Others, see the [Security Service Detailed Description](\ref seco_err) section
 *
 * This is used to load images via the SECO. Examples include SECO
 * Firmware and IVT/CSF data used for authentication. These are usually
 * loaded into SECO TCM. \a addr_src is in secure memory.
 *
 * See the <em>SECO API Reference Guide</em> for more info.
 */
sc_err_t sc_seco_image_load(sc_ipc_t ipc, sc_faddr_t addr_src,
    sc_faddr_t addr_dst, uint32_t len, sc_bool_t fw);

/*!
 * This function is used to authenticate a SECO image or command.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     cmd         authenticate command
 * @param[in]     addr        address of/or metadata
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors codes:
 * - SC_ERR_PARM if word fuse index param out of range or invalid,
 * - SC_ERR_UNAVAILABLE if SECO not available,
 * - SC_ERR_BUSY if SECO is busy with another authentication request,
 * - SC_ERR_FAIL if SECO response is bad,
 * - SC_ERR_IPC if SECO response has bad header tag or size,
 * - SC_ERR_VERSION if SECO response has bad version,
 * - Others, see the [Security Service Detailed Description](\ref seco_err) section
 *
 * This is used to authenticate a SECO image or issue a security
 * command. \a addr often points to an container. It is also
 * just data (or even unused) for some commands.
 *
 * Implementation of this command depends on the underlying security
 * architecture of the device. For example, on devices with SECO FW,
 * the following options apply:
 *
 * - cmd=SC_SECO_AUTH_CONTAINER, addr=container address (sends AHAB_AUTH_CONTAINER_REQ to SECO)
 * - cmd=SC_SECO_VERIFY_IMAGE, addr=image mask (sends AHAB_VERIFY_IMAGE_REQ to SECO)
 * - cmd=SC_SECO_REL_CONTAINER, addr unused (sends AHAB_RELEASE_CONTAINER_REQ to SECO)
 * - cmd=SC_SECO_AUTH_HDMI_TX_FW, addr unused (sends AHAB_ENABLE_HDMI_X_REQ with Subsystem=0 to SECO)
 * - cmd=SC_SECO_AUTH_HDMI_RX_FW, addr unused (sends AHAB_ENABLE_HDMI_X_REQ with Subsystem=1 to SECO)
 *
 * See the <em>SECO API Reference Guide</em> for more info.
 */
sc_err_t sc_seco_authenticate(sc_ipc_t ipc,
    sc_seco_auth_cmd_t cmd, sc_faddr_t addr);

/*!
 * This function is used to authenticate a SECO image or command. This is an
 * enhanced version that has additional mask arguments.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     cmd         authenticate command
 * @param[in]     addr        address of/or metadata
 * @param[in]     mask1       metadata
 * @param[in]     mask2       metadata
 *
 * Return errors codes:
 * - SC_ERR_PARM if word fuse index param out of range or invalid,
 * - SC_ERR_UNAVAILABLE if SECO not available,
 * - SC_ERR_BUSY if SECO is busy with another authentication request,
 * - SC_ERR_FAIL if SECO response is bad,
 * - SC_ERR_IPC if SECO response has bad header tag or size,
 * - SC_ERR_VERSION if SECO response has bad version,
 * - Others, see the [Security Service Detailed Description](\ref seco_err) section
 *
 * This supports all the commands found in sc_seco_authenticate(). Those
 * commands should set both masks to 0 (except SC_SECO_VERIFY_IMAGE).

 * New commands are as follows:
 *
 * - cmd=SC_SECO_VERIFY_IMAGE, addr unused, mask1=image mask, mask2 unused (sends AHAB_VERIFY_IMAGE_REQ to SECO)
 * - cmd=SC_SECO_EVERIFY_IMAGE, addr=container address, mask1=image mask, mask2=move mask (sends AHAB_EVERIFY_IMAGE_REQ to SECO)
 *
 * See the <em>SECO API Reference Guide</em> for more info.
 */
sc_err_t sc_seco_enh_authenticate(sc_ipc_t ipc,
    sc_seco_auth_cmd_t cmd, sc_faddr_t addr,
    uint32_t mask1, uint32_t mask2);

/* @} */

/*!
 * @name Lifecycle Functions
 * @{
 */

/*!
 * This function updates the lifecycle of the device.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     change      desired lifecycle transition
 *
 * @return Returns and error code (SC_ERR_NONE = success).
 *
 * Return errors codes:
 * - SC_ERR_UNAVAILABLE if SECO not available,
 * - SC_ERR_IPC if SECO response has bad header tag or size,
 * - SC_ERR_VERSION if SECO response has bad version,
 * - Others, see the [Security Service Detailed Description](\ref seco_err) section
 *
 * This function is used for going from Open to NXP Closed to OEM Closed.
 * Note \a change is NOT the new desired lifecycle. It is a lifecycle
 * transition as documented in the <em>SECO API Reference Guide</em>.
 *
 * If any SECO request fails or only succeeds because the part is in an
 * "OEM open" lifecycle, then a request to transition from "NXP closed"
 * to "OEM closed" will also fail. For example, booting a signed container
 * when the OEM SRK is not fused will succeed, but as it is an abnormal
 * situation, a subsequent request to transition the lifecycle will return
 * an error.
 */
sc_err_t sc_seco_forward_lifecycle(sc_ipc_t ipc, uint32_t change);

/*!
 * This function updates the lifecycle to one of the return lifecycles.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     addr        address of message block
 *
 * @return Returns and error code (SC_ERR_NONE = success).
 *
 * Return errors codes:
 * - SC_ERR_UNAVAILABLE if SECO not available,
 * - SC_ERR_IPC if SECO response has bad header tag or size,
 * - SC_ERR_VERSION if SECO response has bad version,
 * - Others, see the [Security Service Detailed Description](\ref seco_err) section
 *
 * Note \a addr must be a pointer to a signed message block.
 *
 * To switch back to NXP states (Full Field Return), message must be signed
 * by NXP SRK. For OEM States (Partial Field Return), must be signed by OEM
 * SRK.
 *
 * See the <em>SECO API Reference Guide</em> for more info.
 */
sc_err_t sc_seco_return_lifecycle(sc_ipc_t ipc, sc_faddr_t addr);

/*!
 * This function is used to commit into the fuses any new SRK revocation
 * and FW version information that have been found in the primary and
 * secondary containers.
 *
 * @param[in]     ipc         IPC handle
 * @param[in,out] info        pointer to information type to be committed
 *
 * The return \a info will contain what was actually committed.
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors codes:
 * - SC_ERR_PARM if \a info is invalid,
 * - SC_ERR_UNAVAILABLE if SECO not available,
 * - SC_ERR_IPC if SECO response has bad header tag or size,
 * - SC_ERR_VERSION if SECO response has bad version,
 * - Others, see the [Security Service Detailed Description](\ref seco_err) section
 */
sc_err_t sc_seco_commit(sc_ipc_t ipc, uint32_t *info);

/* @} */

/*!
 * @name Attestation Functions
 * @{
 */

/*!
 * This function is used to set the attestation mode. Only the owner of
 * the SC_R_ATTESTATION resource may make this call.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     mode        mode
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors codes:
 * - SC_ERR_PARM if \a mode is invalid,
 * - SC_ERR_NOACCESS if SC_R_ATTESTATON not owned by caller,
 * - SC_ERR_UNAVAILABLE if SECO not available,
 * - SC_ERR_IPC if SECO response has bad header tag or size,
 * - SC_ERR_VERSION if SECO response has bad version,
 * - Others, see the [Security Service Detailed Description](\ref seco_err) section
 *
 * This is used to set the SECO attestation mode. This can be prover
 * or verifier. See the <em>SECO API Reference Guide</em> for more on the
 * supported modes, mode values, and mode behavior.
 */
sc_err_t sc_seco_attest_mode(sc_ipc_t ipc, uint32_t mode);

/*!
 * This function is used to request attestation. Only the owner of
 * the SC_R_ATTESTATION resource may make this call.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     nonce       unique value
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors codes:
 * - SC_ERR_NOACCESS if SC_R_ATTESTATON not owned by caller,
 * - SC_ERR_UNAVAILABLE if SECO not available,
 * - SC_ERR_IPC if SECO response has bad header tag or size,
 * - SC_ERR_VERSION if SECO response has bad version,
 * - Others, see the [Security Service Detailed Description](\ref seco_err) section
 *
 * This is used to ask SECO to perform an attestation. The result depends
 * on the attestation mode. After this call, the signature can be
 * requested or a verify can be requested.
 *
 * See the <em>SECO API Reference Guide</em> for more info.
 */
sc_err_t sc_seco_attest(sc_ipc_t ipc, uint64_t nonce);

/*!
 * This function is used to retrieve the attestation public key.
 * Mode must be verifier. Only the owner of the SC_R_ATTESTATION resource
 * may make this call.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     addr        address to write response
 *
 * Result will be written to \a addr. The \a addr parameter must point
 * to an address SECO can access. It must be 64-bit aligned. There
 * should be 96 bytes of space.
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors codes:
 * - SC_ERR_PARM if \a addr bad or attestation has not been requested,
 * - SC_ERR_NOACCESS if SC_R_ATTESTATON not owned by caller,
 * - SC_ERR_UNAVAILABLE if SECO not available,
 * - SC_ERR_IPC if SECO response has bad header tag or size,
 * - SC_ERR_VERSION if SECO response has bad version,
 * - Others, see the [Security Service Detailed Description](\ref seco_err) section
 *
 * See the <em>SECO API Reference Guide</em> for more info.
 */
sc_err_t sc_seco_get_attest_pkey(sc_ipc_t ipc, sc_faddr_t addr);

/*!
 * This function is used to retrieve attestation signature and parameters.
 * Mode must be provider. Only the owner of the SC_R_ATTESTATION resource
 * may make this call.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     addr        address to write response
 *
 * Result will be written to \a addr. The \a addr parameter must point
 * to an address SECO can access. It must be 64-bit aligned. There
 * should be 120 bytes of space.
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors codes:
 * - SC_ERR_PARM if \a addr bad or attestation has not been requested,
 * - SC_ERR_NOACCESS if SC_R_ATTESTATON not owned by caller,
 * - SC_ERR_UNAVAILABLE if SECO not available,
 * - SC_ERR_IPC if SECO response has bad header tag or size,
 * - SC_ERR_VERSION if SECO response has bad version,
 * - Others, see the [Security Service Detailed Description](\ref seco_err) section
 *
 * See the <em>SECO API Reference Guide</em> for more info.
 */
sc_err_t sc_seco_get_attest_sign(sc_ipc_t ipc, sc_faddr_t addr);

/*!
 * This function is used to verify attestation. Mode must be verifier.
 * Only the owner of the SC_R_ATTESTATION resource may make this call.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     addr        address of signature
 *
 * The \a addr parameter must point to an address SECO can access. It must be
 * 64-bit aligned.
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors codes:
 * - SC_ERR_PARM if \a addr bad or attestation has not been requested,
 * - SC_ERR_NOACCESS if SC_R_ATTESTATON not owned by caller,
 * - SC_ERR_UNAVAILABLE if SECO not available,
 * - SC_ERR_FAIL if signature doesn't match,
 * - SC_ERR_IPC if SECO response has bad header tag or size,
 * - SC_ERR_VERSION if SECO response has bad version,
 * - Others, see the [Security Service Detailed Description](\ref seco_err) section
 *
 * See the <em>SECO API Reference Guide</em> for more info.
 */
sc_err_t sc_seco_attest_verify(sc_ipc_t ipc, sc_faddr_t addr);

/* @} */

/*!
 * @name Key Functions
 * @{
 */

/*!
 * This function is used to generate a SECO key blob.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     id          key identifier
 * @param[in]     load_addr   load address
 * @param[in]     export_addr export address
 * @param[in]     max_size    max export size
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors codes:
 * - SC_ERR_PARM if word fuse index param out of range or invalid,
 * - SC_ERR_UNAVAILABLE if SECO not available,
 * - SC_ERR_IPC if SECO response has bad header tag or size,
 * - SC_ERR_VERSION if SECO response has bad version,
 * - Others, see the [Security Service Detailed Description](\ref seco_err) section
 *
 * This function is used to encapsulate sensitive keys in a specific structure
 * called a blob, which provides both confidentiality and integrity protection.
 *
 * See the <em>SECO API Reference Guide</em> for more info.
 */
sc_err_t sc_seco_gen_key_blob(sc_ipc_t ipc, uint32_t id,
    sc_faddr_t load_addr, sc_faddr_t export_addr, uint16_t max_size);

/*!
 * This function is used to load a SECO key.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     id          key identifier
 * @param[in]     addr        key address
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors codes:
 * - SC_ERR_PARM if word fuse index param out of range or invalid,
 * - SC_ERR_UNAVAILABLE if SECO not available,
 * - SC_ERR_IPC if SECO response has bad header tag or size,
 * - SC_ERR_VERSION if SECO response has bad version,
 * - Others, see the [Security Service Detailed Description](\ref seco_err) section
 *
 * This function is used to install private cryptographic keys encapsulated
 * in a blob previously generated by SECO. The controller can be either the
 * IEE or the VPU. The blob header carries the controller type and the key
 * size, as provided by the user when generating the key blob.
 *
 * See the <em>SECO API Reference Guide</em> for more info.
 */
sc_err_t sc_seco_load_key(sc_ipc_t ipc, uint32_t id,
    sc_faddr_t addr);

/* @} */

/*!
 * @name Manufacturing Protection Functions
 * @{
 */

/*!
 * This function is used to get the manufacturing protection public key.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     dst_addr    destination address
 * @param[in]     dst_size    destination size
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors codes:
 * - SC_ERR_PARM if word fuse index param out of range or invalid,
 * - SC_ERR_UNAVAILABLE if SECO not available,
 * - SC_ERR_IPC if SECO response has bad header tag or size,
 * - SC_ERR_VERSION if SECO response has bad version,
 * - Others, see the [Security Service Detailed Description](\ref seco_err) section
 *
 * This function is supported only in OEM-closed lifecycle. It generates
 * the mfg public key and stores it in a specific location in the secure
 * memory.
 *
 * See the <em>SECO API Reference Guide</em> for more info.
 */
sc_err_t sc_seco_get_mp_key(sc_ipc_t ipc, sc_faddr_t dst_addr,
    uint16_t dst_size);

/*!
 * This function is used to update the manufacturing protection message
 * register.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     addr        data address
 * @param[in]     size        size
 * @param[in]     lock        lock_reg
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors codes:
 * - SC_ERR_PARM if word fuse index param out of range or invalid,
 * - SC_ERR_UNAVAILABLE if SECO not available,
 * - SC_ERR_IPC if SECO response has bad header tag or size,
 * - SC_ERR_VERSION if SECO response has bad version,
 * - Others, see the [Security Service Detailed Description](\ref seco_err) section
 *
 * This function is supported only in OEM-closed lifecycle. It updates the
 * content of the MPMR (Manufacturing Protection Message register of 256
 * bits). This register will be appended to the input-data message when
 * generating the signature. Please refer to the CAAM block guide for details.
 *
 * See the <em>SECO API Reference Guide</em> for more info.
 */
sc_err_t sc_seco_update_mpmr(sc_ipc_t ipc, sc_faddr_t addr,
    uint8_t size, uint8_t lock);

/*!
 * This function is used to get the manufacturing protection signature.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     msg_addr    message address
 * @param[in]     msg_size    message size
 * @param[in]     dst_addr    destination address
 * @param[in]     dst_size    destination size
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors codes:
 * - SC_ERR_PARM if word fuse index param out of range or invalid,
 * - SC_ERR_UNAVAILABLE if SECO not available,
 * - SC_ERR_IPC if SECO response has bad header tag or size,
 * - SC_ERR_VERSION if SECO response has bad version,
 * - Others, see the [Security Service Detailed Description](\ref seco_err) section
 *
 * This function is used to generate an ECDSA signature for an input-data
 * message and to store it in a specific location in the secure memory. It
 * is only supported in OEM-closed lifecycle. In order to get the ECDSA
 * signature, the RNG must be initialized. In case it has not been started
 * an error will be returned.
 *
 * See the <em>SECO API Reference Guide</em> for more info.
 */
sc_err_t sc_seco_get_mp_sign(sc_ipc_t ipc, sc_faddr_t msg_addr,
    uint16_t msg_size, sc_faddr_t dst_addr, uint16_t dst_size);

/* @} */

/*!
 * @name Debug Functions
 * @{
 */

/*!
 * This function is used to return the SECO FW build info.
 *
 * @param[in]     ipc         IPC handle
 * @param[out]    version     pointer to return build number
 * @param[out]    commit      pointer to return commit ID (git SHA-1)
 */
void sc_seco_build_info(sc_ipc_t ipc, uint32_t *version,
    uint32_t *commit);

/*!
 * This function is used to return SECO chip info.
 *
 * @param[in]     ipc         IPC handle
 * @param[out]    lc          pointer to return lifecycle
 * @param[out]    monotonic   pointer to return monotonic counter
 * @param[out]    uid_l       pointer to return UID (lower 32 bits)
 * @param[out]    uid_h       pointer to return UID (upper 32 bits)
 *
 * @return Returns and error code (SC_ERR_NONE = success).
 *
 * Return errors codes:
 * - SC_ERR_UNAVAILABLE if SECO not available,
 * - SC_ERR_IPC if SECO response has bad header tag or size,
 * - SC_ERR_VERSION if SECO response has bad version,
 * - Others, see the [Security Service Detailed Description](\ref seco_err) section
 */
sc_err_t sc_seco_chip_info(sc_ipc_t ipc, uint16_t *lc,
    uint16_t *monotonic, uint32_t *uid_l, uint32_t *uid_h);

/*!
 * This function securely enables debug.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     addr        address of message block
 *
 * @return Returns and error code (SC_ERR_NONE = success).
 *
 * Return errors codes:
 * - SC_ERR_UNAVAILABLE if SECO not available,
 * - SC_ERR_IPC if SECO response has bad header tag or size,
 * - SC_ERR_VERSION if SECO response has bad version,
 * - Others, see the [Security Service Detailed Description](\ref seco_err) section
 *
 * Note \a addr must be a pointer to a signed message block.
 *
 * See the <em>SECO API Reference Guide</em> for more info.
 */
sc_err_t sc_seco_enable_debug(sc_ipc_t ipc, sc_faddr_t addr);

/*!
 * This function is used to return an event from the SECO error log.
 *
 * @param[in]     ipc         IPC handle
 * @param[out]    idx         index of event to return
 * @param[out]    event       pointer to return event
 *
 * @return Returns an error code (SC_ERR_NONE = success).
 *
 * Return errors codes:
 * - SC_ERR_UNAVAILABLE if SECO not available,
 * - SC_ERR_IPC if SECO response has bad header tag or size,
 * - SC_ERR_VERSION if SECO response has bad version,
 * - Others, see the [Security Service Detailed Description](\ref seco_err) section
 *
 * Read of \a idx 0 captures events from SECO. Loop starting
 * with 0 until an error is returned to dump all events.
 */
sc_err_t sc_seco_get_event(sc_ipc_t ipc, uint8_t idx,
    uint32_t *event);

/* @} */

/*!
 * @name Miscellaneous Functions
 * @{
 */

/*!
 * This function securely writes a group of fuse words.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     addr        address of message block
 *
 * @return Returns and error code (SC_ERR_NONE = success).
 *
 * Return errors codes:
 * - SC_ERR_UNAVAILABLE if SECO not available,
 * - SC_ERR_IPC if SECO response has bad header tag or size,
 * - SC_ERR_VERSION if SECO response has bad version,
 * - Others, see the [Security Service Detailed Description](\ref seco_err) section
 *
 * Note \a addr must be a pointer to a signed message block.
 *
 * See the <em>SECO API Reference Guide</em> for more info.
 */
sc_err_t sc_seco_fuse_write(sc_ipc_t ipc, sc_faddr_t addr);

/*!
 * This function applies a patch.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     addr        address of message block
 *
 * @return Returns and error code (SC_ERR_NONE = success).
 *
 * Return errors codes:
 * - SC_ERR_UNAVAILABLE if SECO not available,
 * - SC_ERR_IPC if SECO response has bad header tag or size,
 * - SC_ERR_VERSION if SECO response has bad version,
 * - Others, see the [Security Service Detailed Description](\ref seco_err) section
 *
 * Note \a addr must be a pointer to a signed message block.
 *
 * See the <em>SECO API Reference Guide</em> for more info.
 */
sc_err_t sc_seco_patch(sc_ipc_t ipc, sc_faddr_t addr);

/*!
 * This function starts the random number generator.
 *
 * @param[in]     ipc         IPC handle
 * @param[out]    status      pointer to return state of RNG
 *
 * @return Returns and error code (SC_ERR_NONE = success).
 *
 * Return errors codes:
 * - SC_ERR_UNAVAILABLE if SECO not available,
 * - SC_ERR_IPC if SECO response has bad header tag or size,
 * - SC_ERR_VERSION if SECO response has bad version,
 * - Others, see the [Security Service Detailed Description](\ref seco_err) section
 *
 * The RNG is started automatically after all CPUs are booted. This
 * function can be used to start earlier and to check the status.
 *
 * See the <em>SECO API Reference Guide</em> for more info.
 */
sc_err_t sc_seco_start_rng(sc_ipc_t ipc, sc_seco_rng_stat_t *status);

/*!
 * This function sends a generic signed message to the
 * SECO SHE/HSM components.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     addr        address of message block
 *
 * @return Returns and error code (SC_ERR_NONE = success).
 *
 * Return errors codes:
 * - SC_ERR_UNAVAILABLE if SECO not available,
 * - SC_ERR_IPC if SECO response has bad header tag or size,
 * - SC_ERR_VERSION if SECO response has bad version,
 * - Others, see the [Security Service Detailed Description](\ref seco_err) section
 *
 * Note \a addr must be a pointer to a signed message block.
 *
 * See the <em>SECO API Reference Guide</em> for more info.
 */
sc_err_t sc_seco_sab_msg(sc_ipc_t ipc, sc_faddr_t addr);

/*!
 * This function is used to enable security violation and tamper interrupts.
 * These are then reported using the IRQ service via the SC_IRQ_SECVIO
 * interrupt. Note it is automatically enabled at boot.
 *
 * @param[in]     ipc         IPC handle
 *
 * @return Returns and error code (SC_ERR_NONE = success).
 *
 * Return errors codes:
 * - SC_ERR_NOACCESS if caller does not own SC_R_SECVIO,
 * - SC_ERR_UNAVAILABLE if SECO not available,
 * - SC_ERR_IPC if SECO response has bad header tag or size,
 * - SC_ERR_VERSION if SECO response has bad version,
 * - Others, see the [Security Service Detailed Description](\ref seco_err) section
 *
 * The security violation interrupt is self-masking. Once it is cleared in
 * the SNVS it must be re-enabled using this function.
 */
sc_err_t sc_seco_secvio_enable(sc_ipc_t ipc);

/*!
 * This function is used to read/write SNVS security violation
 * and tamper registers.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     id          register ID
 * @param[in]     access      0=read, 1=write
 * @param[in]     data0       pointer to data to read or write
 * @param[in]     data1       pointer to data to read or write
 * @param[in]     data2       pointer to data to read or write
 * @param[in]     data3       pointer to data to read or write
 * @param[in]     data4       pointer to data to read or write
 * @param[in]     size        number of valid data words
 *
 * @return Returns and error code (SC_ERR_NONE = success).
 *
 * Return errors codes:
 * - SC_ERR_NOACCESS if caller does not own SC_R_SECVIO,
 * - SC_ERR_UNAVAILABLE if SECO not available,
 * - SC_ERR_IPC if SECO response has bad header tag or size,
 * - SC_ERR_VERSION if SECO response has bad version,
 * - Others, see the [Security Service Detailed Description](\ref seco_err) section
 *
 * Unused data words can be passed a NULL pointer.
 *
 * See AHAB_MANAGE_SNVS_REQ in the <em>SECO API Reference Guide</em> for
 * more info.
 */
sc_err_t sc_seco_secvio_config(sc_ipc_t ipc, uint8_t id, uint8_t access,
    uint32_t *data0, uint32_t *data1, uint32_t *data2, uint32_t *data3,
    uint32_t *data4, uint8_t size);

/*!
 * This function is used to read/write SNVS security violation
 * and tamper DGO registers.
 *
 * @param[in]     ipc         IPC handle
 * @param[in]     id          regsiter ID
 * @param[in]     access      0=read, 1=write
 * @param[in]     data        pointer to data to read or write
 *
 * @return Returns and error code (SC_ERR_NONE = success).
 *
 * Return errors codes:
 * - SC_ERR_NOACCESS if caller does not own SC_R_SECVIO,
 * - SC_ERR_UNAVAILABLE if SECO not available,
 * - SC_ERR_IPC if SECO response has bad header tag or size,
 * - SC_ERR_VERSION if SECO response has bad version,
 * - Others, see the [Security Service Detailed Description](\ref seco_err) section
 *
 * See AHAB_MANAGE_SNVS_DGO_REQ in the <em>SECO API Reference Guide</em>
 * for more info.
 */
sc_err_t sc_seco_secvio_dgo_config(sc_ipc_t ipc, uint8_t id,
    uint8_t access, uint32_t *data);

/* @} */

#endif /* SC_SECO_API_H */

/**@}*/

