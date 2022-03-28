/*--------------------------------------------------------------------------*/
/* Copyright 2020-2021 NXP                                                  */
/*                                                                          */
/* NXP Confidential. This software is owned or controlled by NXP and may    */
/* only be used strictly in accordance with the applicable license terms.   */
/* By expressly accepting such terms or by downloading, installing,         */
/* activating and/or otherwise using the software, you are agreeing that    */
/* you have read, and that you agree to comply with and are bound by, such  */
/* license terms. If you do not agree to be bound by the applicable license */
/* terms, then you may not retain, install, activate or otherwise use the   */
/* software.                                                                */
/*--------------------------------------------------------------------------*/

/**
 * @file  mcuxClCss_Types.h
 * @brief CSSv2 type header.
 * 
 * This header defines types that are used by other mcuxClCss headers.
 */
/**
 * @defgroup mcuxClCss_Types mcuxClCss_Types
 * @brief This part of the @ref mcuxClCss driver defines common types
 * @ingroup mcuxClCss
 * @{
 */
#ifndef MCUXCLCSS_TYPES_H_
#define MCUXCLCSS_TYPES_H_

#include <stdint.h>
#include <stddef.h>

/**********************************************
 * MACROS
 **********************************************/
/**
 * @defgroup mcuxClCss_Types_Macros mcuxClCss_Types_Macros
 * @brief Defines all macros of @ref mcuxClCss_Types
 * @ingroup mcuxClCss_Types
 * @{
 */

#define MCUXCLCSS_KEY_SLOTS (20U) ///< Number of key slots in the CSS key store.

/** @defgroup MCUXCLCSS_KEYPROPERTY_VALUE_ MCUXCLCSS_KEYPROPERTY_VALUE_
 * @brief Constants for initalizing #mcuxClCss_KeyProp_t.word
 * @ingroup mcuxClCss_Types_Macros
 * @{
 */
#define MCUXCLCSS_KEYPROPERTY_VALUE_KEY_SIZE_128         ((uint32_t) 0u<< 0u) ///< 128-bit key
#define MCUXCLCSS_KEYPROPERTY_VALUE_KEY_SIZE_256         ((uint32_t) 1u<< 0u) ///< 256-bit key
#define MCUXCLCSS_KEYPROPERTY_VALUE_ACTIVE               ((uint32_t) 1u<< 5u) ///< Key is active (loaded)
#define MCUXCLCSS_KEYPROPERTY_VALUE_BASE_SLOT            ((uint32_t) 1u<< 6u) ///< First part of multi-slot key
#define MCUXCLCSS_KEYPROPERTY_VALUE_GENERAL_PURPOSE_SLOT ((uint32_t) 1u<< 7u) ///< General purpose key slot
#define MCUXCLCSS_KEYPROPERTY_VALUE_RETENTION_SLOT       ((uint32_t) 1u<< 8u) ///< Retention key slot
#define MCUXCLCSS_KEYPROPERTY_VALUE_HW_OUT_SLOT          ((uint32_t) 1u<< 9u) ///< Hardware output key slot
#define MCUXCLCSS_KEYPROPERTY_VALUE_CMAC                 ((uint32_t) 1u<<13u) ///< CMAC key
#define MCUXCLCSS_KEYPROPERTY_VALUE_KSK                  ((uint32_t) 1u<<14u) ///< Key signing key
#define MCUXCLCSS_KEYPROPERTY_VALUE_RTF                  ((uint32_t) 1u<<15u) ///< RTF signing key
#define MCUXCLCSS_KEYPROPERTY_VALUE_CKDF                 ((uint32_t) 1u<<16u) ///< CKDF signing key
#define MCUXCLCSS_KEYPROPERTY_VALUE_HKDF                 ((uint32_t) 1u<<17u) ///< HKDF signing key
#define MCUXCLCSS_KEYPROPERTY_VALUE_ECSGN                ((uint32_t) 1u<<18u) ///< ECC signing key
#define MCUXCLCSS_KEYPROPERTY_VALUE_ECDH                 ((uint32_t) 1u<<19u) ///< ECC Diffie Hellman private key
#define MCUXCLCSS_KEYPROPERTY_VALUE_AES                  ((uint32_t) 1u<<20u) ///< AES key
#define MCUXCLCSS_KEYPROPERTY_VALUE_HMAC                 ((uint32_t) 1u<<21u) ///< HMAC key
#define MCUXCLCSS_KEYPROPERTY_VALUE_KWK                  ((uint32_t) 1u<<22u) ///< Key Wrapping Key
#define MCUXCLCSS_KEYPROPERTY_VALUE_KUOK                 ((uint32_t) 1u<<23u) ///< Key Unwrapping Only Key
#define MCUXCLCSS_KEYPROPERTY_VALUE_TLS_PREMASTER_SECRET ((uint32_t) 1u<<24u) ///< TLS Premaster Secret
#define MCUXCLCSS_KEYPROPERTY_VALUE_TLS_MASTER_SECRET    ((uint32_t) 1u<<25u) ///< TLS Master Secret
#define MCUXCLCSS_KEYPROPERTY_VALUE_KGSRC                ((uint32_t) 1u<<26u) ///< Can provide key material input for ECC key generation
#define MCUXCLCSS_KEYPROPERTY_VALUE_HW_OUT               ((uint32_t) 1u<<27u) ///< A key to be used in a hardware out key slot
#define MCUXCLCSS_KEYPROPERTY_VALUE_WRPOK                ((uint32_t) 1u<<28u) ///< The key can be wrapped
#define MCUXCLCSS_KEYPROPERTY_VALUE_DUK                  ((uint32_t) 1u<<29u) ///< Device Unique Key
#define MCUXCLCSS_KEYPROPERTY_VALUE_PRIVILEGED           ((uint32_t) 1u<<30u) ///< Caller must be in privileged mode to use the key
#define MCUXCLCSS_KEYPROPERTY_VALUE_NOTPRIVILEGED        ((uint32_t) 0u<<30u) ///< Caller does not have to be in privileged mode to use the key
#define MCUXCLCSS_KEYPROPERTY_VALUE_SECURE               ((uint32_t) 0u<<31u) ///< Caller must be in secure mode to use the key
#define MCUXCLCSS_KEYPROPERTY_VALUE_NOTSECURE            ((uint32_t) 1u<<31u) ///< Caller does not have to be in secure mode to use the key
/**
 * @}
 */

/** @defgroup MCUXCLCSS_KEYPROPERTY_ MCUXCLCSS_KEYPROPERTY_
 * @brief Constants for initalizing #mcuxClCss_KeyProp_t.bits
 * @ingroup mcuxClCss_Types_Macros
 * @{
 */
#define MCUXCLCSS_KEYPROPERTY_KEY_SIZE_128               0U ///< This value of #mcuxClCss_KeyProp_t.ksize indicates a 128 bit key
#define MCUXCLCSS_KEYPROPERTY_KEY_SIZE_256               1U ///< This value of #mcuxClCss_KeyProp_t.ksize indicates a 256 bit key
#define MCUXCLCSS_KEYPROPERTY_ACTIVE_TRUE                1U ///< This value of #mcuxClCss_KeyProp_t.kactv indicates that the slot contains an active key
#define MCUXCLCSS_KEYPROPERTY_ACTIVE_FALSE               0U ///< This value of #mcuxClCss_KeyProp_t.kactv indicates that the slot does not contain active key
#define MCUXCLCSS_KEYPROPERTY_BASE_SLOT                  1U ///< This value of #mcuxClCss_KeyProp_t.kbase indicates that the slot is the base slot of a 2-slot key
#define MCUXCLCSS_KEYPROPERTY_SECOND_SLOT                0U ///< This value of #mcuxClCss_KeyProp_t.kbase indicates that the slot is the second slot of a 2-slot key
#define MCUXCLCSS_KEYPROPERTY_GENERAL_PURPOSE_SLOT_TRUE  1U ///< This value of #mcuxClCss_KeyProp_t.fgp indicates that the slot is a retention key slot or a hardware out key slot
#define MCUXCLCSS_KEYPROPERTY_GENERAL_PURPOSE_SLOT_FALSE 0U ///< This value of #mcuxClCss_KeyProp_t.fgp indicates that the slot is a neither retention key slot nor hardware out key slot
#define MCUXCLCSS_KEYPROPERTY_RETENTION_SLOT_TRUE        1U ///< This value of #mcuxClCss_KeyProp_t.frtn indicates that the slot is a retention key slot
#define MCUXCLCSS_KEYPROPERTY_RETENTION_SLOT_FALSE       0U ///< This value of #mcuxClCss_KeyProp_t.frtn indicates that the slot is not a retention key slot
#define MCUXCLCSS_KEYPROPERTY_HW_OUT_SLOT_TRUE           1U ///< This value of #mcuxClCss_KeyProp_t.fhwo indicates that the slot is a hardware out key slot
#define MCUXCLCSS_KEYPROPERTY_HW_OUT_SLOT_FALSE          0U ///< This value of #mcuxClCss_KeyProp_t.fhwo indicates that the slot is not a hardware out key slot
#define MCUXCLCSS_KEYPROPERTY_CMAC_TRUE                  1U ///< This value of #mcuxClCss_KeyProp_t.ucmac indicates that the key can be used for CMAC
#define MCUXCLCSS_KEYPROPERTY_CMAC_FALSE                 0U ///< This value of #mcuxClCss_KeyProp_t.ucmac indicates that the key cannot be used for CMAC
#define MCUXCLCSS_KEYPROPERTY_KSK_TRUE                   1U ///< This value of #mcuxClCss_KeyProp_t.uksk indicates that the key can be used for key signing
#define MCUXCLCSS_KEYPROPERTY_KSK_FALSE                  0U ///< This value of #mcuxClCss_KeyProp_t.uksk indicates that the key cannot be used for key signing
#define MCUXCLCSS_KEYPROPERTY_RTF_TRUE                   1U ///< This value of #mcuxClCss_KeyProp_t.urtf indicates that the key can be used for RTF signing
#define MCUXCLCSS_KEYPROPERTY_RTF_FALSE                  0U ///< This value of #mcuxClCss_KeyProp_t.urtf indicates that the key cannot be used for RTF signing
#define MCUXCLCSS_KEYPROPERTY_CKDF_TRUE                  1U ///< This value of #mcuxClCss_KeyProp_t.uckdf indicates that the key can be used for CKDF
#define MCUXCLCSS_KEYPROPERTY_CKDF_FALSE                 0U ///< This value of #mcuxClCss_KeyProp_t.uckdf indicates that the key cannot be used for CKDF
#define MCUXCLCSS_KEYPROPERTY_HKDF_TRUE                  1U ///< This value of #mcuxClCss_KeyProp_t.uhkdf indicates that the key can be used for HKDF
#define MCUXCLCSS_KEYPROPERTY_HKDF_FALSE                 0U ///< This value of #mcuxClCss_KeyProp_t.uhkdf indicates that the key cannot be used for HKDF
#define MCUXCLCSS_KEYPROPERTY_ECC_TRUE                   1U ///< This value of #mcuxClCss_KeyProp_t.uecsg indicates that the key can be used for ECC signing
#define MCUXCLCSS_KEYPROPERTY_ECC_FALSE                  0U ///< This value of #mcuxClCss_KeyProp_t.uecsg indicates that the key cannot be used for ECC signing 
#define MCUXCLCSS_KEYPROPERTY_ECC_DH_PRIVATE_TRUE        1U ///< This value of #mcuxClCss_KeyProp_t.uecdh indicates that the key is a ECC Diffie Hellman private key
#define MCUXCLCSS_KEYPROPERTY_ECC_DH_PRIVATE_FALSE       0U ///< This value of #mcuxClCss_KeyProp_t.uecdh indicates that the key is not an ECC Diffie Hellman private key
#define MCUXCLCSS_KEYPROPERTY_AES_TRUE                   1U ///< This value of #mcuxClCss_KeyProp_t.uaes indicates that the key is an AES key
#define MCUXCLCSS_KEYPROPERTY_AES_FALSE                  0U ///< This value of #mcuxClCss_KeyProp_t.uaes indicates that the key is not an AES key
#define MCUXCLCSS_KEYPROPERTY_HMAC_TRUE                  1U ///< This value of #mcuxClCss_KeyProp_t.uhmac indicates that the key is an HMAC key
#define MCUXCLCSS_KEYPROPERTY_HMAC_FALSE                 0U ///< This value of #mcuxClCss_KeyProp_t.uhmac indicates that the key is not an HMAC key
#define MCUXCLCSS_KEYPROPERTY_KWK_TRUE                   1U ///< This value of #mcuxClCss_KeyProp_t.ukwk indicates that the key is a Key Wrapping Key
#define MCUXCLCSS_KEYPROPERTY_KWK_FALSE                  0U ///< This value of #mcuxClCss_KeyProp_t.ukwk indicates that the key is not a Key Wrapping Key
#define MCUXCLCSS_KEYPROPERTY_KUOK_TRUE                  1U ///< This value of #mcuxClCss_KeyProp_t.ukuok indicates that the key is a Key Unwrapping Only Key
#define MCUXCLCSS_KEYPROPERTY_KUOK_FALSE                 0U ///< This value of #mcuxClCss_KeyProp_t.ukuok indicates that the key is not a Key Unwrapping Only Key
#define MCUXCLCSS_KEYPROPERTY_TLS_PREMASTER_SECRET_TRUE  1U ///< This value of #mcuxClCss_KeyProp_t.utlspms indicates that the key is a TLS Premaster Secret
#define MCUXCLCSS_KEYPROPERTY_TLS_PREMASTER_SECRET_FALSE 0U ///< This value of #mcuxClCss_KeyProp_t.utlspms indicates that the key is not a TLS Premaster Secret
#define MCUXCLCSS_KEYPROPERTY_TLS_MASTER_SECRET_TRUE     1U ///< This value of #mcuxClCss_KeyProp_t.utlsms indicates that the key is a TLS Master Secret
#define MCUXCLCSS_KEYPROPERTY_TLS_MASTER_SECRET_FALSE    0U ///< This value of #mcuxClCss_KeyProp_t.utlsms indicates that the key is not a TLS Master Secret
#define MCUXCLCSS_KEYPROPERTY_INPUT_FOR_ECC_TRUE         1U ///< This value of #mcuxClCss_KeyProp_t.ukgsrc indicates that the key can be used as key material input for ECC key generation
#define MCUXCLCSS_KEYPROPERTY_INPUT_FOR_ECC_FALSE        0U ///< This value of #mcuxClCss_KeyProp_t.ukgsrc indicates that the key cannot be used as key material input for ECC key generation
#define MCUXCLCSS_KEYPROPERTY_HW_OUT_TRUE                1U ///< This value of #mcuxClCss_KeyProp_t.uhwo indicates that the key can be used in a hardware out key slot
#define MCUXCLCSS_KEYPROPERTY_HW_OUT_FALSE               0U ///< This value of #mcuxClCss_KeyProp_t.uhwo indicates that the key cannot be used in a hardware out key slot
#define MCUXCLCSS_KEYPROPERTY_WRAP_TRUE                  1U ///< This value of #mcuxClCss_KeyProp_t.wrpok indicates that the key can be wrapped
#define MCUXCLCSS_KEYPROPERTY_WRAP_FALSE                 0U ///< This value of #mcuxClCss_KeyProp_t.wrpok indicates that the key cannot be wrapped
#define MCUXCLCSS_KEYPROPERTY_DEVICE_UNIQUE_TRUE         1U ///< This value of #mcuxClCss_KeyProp_t.duk indicates that the key is a Device Unique Key
#define MCUXCLCSS_KEYPROPERTY_DEVICE_UNIQUE_FALSE        0U ///< This value of #mcuxClCss_KeyProp_t.duk indicates that the key is not a Device Unique Key
#define MCUXCLCSS_KEYPROPERTY_PRIVILEGED_TRUE            1U ///< This value of #mcuxClCss_KeyProp_t.upprot_priv indicates that the caller must be in privileged mode to use the key
#define MCUXCLCSS_KEYPROPERTY_PRIVILEGED_FALSE           0U ///< This value of #mcuxClCss_KeyProp_t.upprot_priv indicates that the caller does not need to be in privileged mode to use the key
#define MCUXCLCSS_KEYPROPERTY_SECURE_TRUE                0U ///< This value of #mcuxClCss_KeyProp_t.upprot_sec indicates that the caller must be in secure mode to use the key
#define MCUXCLCSS_KEYPROPERTY_SECURE_FALSE               1U ///< This value of #mcuxClCss_KeyProp_t.upprot_sec indicates that the caller does not need to be in secure mode to use the key
/**
 * @}
 */

/**
 * @defgroup MCUXCLCSS_STATUS_ MCUXCLCSS_STATUS_
 * @brief Return code definitions
 * @ingroup mcuxClCss_Types_Macros
 * @{
 */
#define MCUXCLCSS_STATUS_OK                   ((mcuxClCss_Status_t) 0xF0F0F0F0U) ///< No error occurred
#define MCUXCLCSS_STATUS_OK_WAIT              ((mcuxClCss_Status_t) 0xF0F0F0E1U) ///< An <tt>_Async</tt> function successfully started a CSS command. Call #mcuxClCss_WaitForOperation to complete it
#define MCUXCLCSS_STATUS_HW_FAULT             ((mcuxClCss_Status_t) 0xF0F0E1E1U) ///< CSSv2 hardware detected a fault
#define MCUXCLCSS_STATUS_HW_ALGORITHM         ((mcuxClCss_Status_t) 0xF0F0E1E2U) ///< An algorithm failed in hardware
#define MCUXCLCSS_STATUS_HW_OPERATIONAL       ((mcuxClCss_Status_t) 0xF0F0E1E4U) ///< CSSv2 was operated incorrectly
#define MCUXCLCSS_STATUS_HW_BUS               ((mcuxClCss_Status_t) 0xF0F0E1E8U) ///< A bus access failed
#define MCUXCLCSS_STATUS_HW_INTEGRITY         ((mcuxClCss_Status_t) 0xF0F0E1D1U) ///< An integrity check failed in hardware
#define MCUXCLCSS_STATUS_HW_PRNG              ((mcuxClCss_Status_t) 0xF0F0E1D2U) ///< Read access to PRNG output while PRNG is not in ready state
#define MCUXCLCSS_STATUS_HW_DTRNG             ((mcuxClCss_Status_t) 0xF0F0E1D4U) ///< Unable to get entropy from dTRNG with current configuration
#define MCUXCLCSS_STATUS_SW_FAULT             ((mcuxClCss_Status_t) 0xF0F0F0E2U) ///< Software detected a fault
#define MCUXCLCSS_STATUS_SW_CANNOT_INTERRUPT  ((mcuxClCss_Status_t) 0xF0F0F0E4U) ///< A CSS command was started while the CSS was still busy, or a SHA-Direct command was started while the SHA kernel was still busy
#define MCUXCLCSS_STATUS_SW_INVALID_PARAM     ((mcuxClCss_Status_t) 0xF0F0F0E8U) ///< Incorrect parameters were supplied
#define MCUXCLCSS_STATUS_SW_INVALID_STATE     ((mcuxClCss_Status_t) 0xF0F0F0D1U) ///< This can happen when CSS is in a wrong state for the requested CSS command
#define MCUXCLCSS_STATUS_SW_COUNTER_EXPIRED   ((mcuxClCss_Status_t) 0xF0F0F0D2U) ///< A software counter expired while waiting for a CSS operation to finish
#define MCUXCLCSS_STATUS_SW_COMPARISON_FAILED ((mcuxClCss_Status_t) 0xF0F0F0D4U) ///< A comparison between a CSS flag and its expected value failed
/** @} */

#define MCUXCLCSS_STATUS_IS_HW_ERROR(x) ((((mcuxClCss_Status_t) (x)) & 0x0000FF00U) == 0x0000E100U) ///< Checks whether an error code is a hardware error. Indicates that an error was reported by CSSv2 hardware.

#define MCUXCLCSS_STATUS_IS_SW_ERROR(x) ((((mcuxClCss_Status_t) (x)) & 0x0000FF00U) == 0x0000F000U) ///< Checks whether an error code is a software error. Indicates that the error was detected by the driver software and not by CSSv2 hardware.

/**
 * @}
 */

/**********************************************
 * TYPEDEFS
 **********************************************/
/**
 * @defgroup mcuxClCss_Types_Types mcuxClCss_Types_Types
 * @brief Defines all types of @ref mcuxClCss_Types
 * @ingroup mcuxClCss_Types
 * @{
 */
/** 
 * @brief Type for CSS driver protected status codes
 */
typedef uint64_t mcuxClCss_Status_Protected_t;

/**
 * @brief Type for CSS driver status codes
 */
typedef uint32_t mcuxClCss_Status_t;

/**
 * @brief Type for CSS keystore indices
 */
typedef uint8_t mcuxClCss_KeyIndex_t;

/** Type for CSS key store key properties */
typedef union
{
    struct
    {
        uint32_t value;          ///< Accesses the bit field as a full word; initialize with a combination of constants from @ref MCUXCLCSS_KEYPROPERTY_VALUE_
    } word;                      ///< Access #mcuxClCss_KeyProp_t word-wise
    struct
    {
        uint32_t ksize :2;       ///< Key size
        uint32_t :3;             ///< RFU
        uint32_t kactv :1;       ///< Status flag to indicate whether the key slot contains an active key or not
        uint32_t kbase :1;       ///< Status flag to indicate whether the key slot is a base slot or the second slot of a 256-bit key
        uint32_t fgp :1;         ///< Hardware feature flag: General purpose key slot
        uint32_t frtn :1;        ///< Hardware feature flag: Retention key slot
        uint32_t fhwo :1;        ///< Hardware feature flag: Hardware-out key slot
        uint32_t :3;             ///< RFU
        uint32_t ucmac :1;       ///< Usage permission for CMAC
        uint32_t uksk :1;        ///< Usage permission for key signing
        uint32_t urtf :1;        ///< Usage permission for RTF signing
        uint32_t uckdf :1;       ///< Usage permission for CKDF
        uint32_t uhkdf :1;       ///< Usage permission for HKDF
        uint32_t uecsg :1;       ///< Usage permission for ECDSA signing
        uint32_t uecdh :1;       ///< Usage permission for Elliptic Curve Diffie-Hellman
        uint32_t uaes :1;        ///< Usage permission for AES
        uint32_t uhmac :1;       ///< Usage permission for HMAC
        uint32_t ukwk :1;        ///< Usage permission for key wrapping
        uint32_t ukuok :1;       ///< Usage permission for key unwrapping, but not for key wrapping
        uint32_t utlspms :1;     ///< Usage permission as a TLS premaster secret
        uint32_t utlsms :1;      ///< Usage permission as a TLS master secret
        uint32_t ukgsrc :1;      ///< Usage permission as input for ECC key generation
        uint32_t uhwo :1;        ///< Usage permission in a hardware-out key slot
        uint32_t wrpok :1;       ///< Usage permission to wrap
        uint32_t duk :1;         ///< Device-unique key flag
        uint32_t upprot_priv :1; ///< Access restriction to privileged mode
        uint32_t upprot_sec :1;  ///< Access restriction to TrustZone secure mode
    } bits;                      ///< Access #mcuxClCss_KeyProp_t bit-wise
} mcuxClCss_KeyProp_t;


#define utlpsms utlspms ///< Deprecated name for #mcuxClCss_KeyProp_t.utlspms

/**
 * @brief Function type for transfer of data to a memory-mapped register
 * 
 * This function type is used as a callback for handling data transfer from memory to a memory-mapped register.
 * Such a function shall read data from the @c uint8_t array source, and write data via a sequence of writes to @p destRegister.
 * Further specification of this function's behavior can be found in the documentation of the function that accepts this function as a callback parameter.
 * 
 * @param     [out] destRegister  Memory-mapped register that the output data shall be written to
 * @param [in]       source       Array containing the input data
 * @param [in]       size         Size of @p source in bytes
 * @param [in, out] pCallerData   Custom pointer that is provided by the caller and forwarded to the callback function by the operation
 * @return An error code that can be any error code in @ref MCUXCLCSS_STATUS_, see individual documentation for more information
 */
typedef mcuxClCss_Status_t (*mcuxClCss_TransferToRegisterFunction_t)(
    uint32_t volatile * destRegister,
    uint8_t const * source,
    size_t size,
    void * pCallerData);

#endif /* MCUXCLCSS_TYPES_H_ */

/**
 * @}
 * 
 * @}
 */
