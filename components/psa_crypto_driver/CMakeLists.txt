#-------------------------------------------------------------------------------
# Copyright (c) 2023-2024 NXP
# SPDX-License-Identifier: BSD-3-Clause
#
#-------------------------------------------------------------------------------

if(NOT CONFIG_BUILD_WITH_TFM)
    find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
endif()

add_library(McuxPsaCryptoDriverElsPkc) 

if (NOT TFM_PLATFORM_NXP_HAL_COMP_PATH)
    set(TFM_PLATFORM_NXP_HAL_COMP_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../)
endif()

target_compile_options(
    McuxPsaCryptoDriverElsPkc
    PUBLIC
        ${TOOLCHAIN_C_FLAGS}
        -mcmse  # Why is this not even part of the default zephyr build options?
)

target_link_options(
    McuxPsaCryptoDriverElsPkc
    PRIVATE
        ${TOOLCHAIN_LD_FLAGS}
)
if(CONFIG_BUILD_WITH_TFM)
target_include_directories(McuxPsaCryptoDriverElsPkc
    PRIVATE
        # SDK driver header files
        ${NXP_HAL_FILE_PATH}/common/Native_Driver/drivers
        ${NXP_HAL_FILE_PATH}/rdrw61x/Native_Driver
        ${NXP_HAL_FILE_PATH}/rdrw61x/Native_Driver/drivers
        # psa/crypto.h and psa/crypto_types.h
        ${MBEDCRYPTO_PATH}/include
        ${MBEDCRYPTO_PATH}/include/psa
        # for psa driver wrapper
        ${MBEDCRYPTO_PATH}/library
)
else ()
target_include_directories(McuxPsaCryptoDriverElsPkc
    PRIVATE
        # SDK driver header files
        ${TFM_PLATFORM_NXP_HAL_COMP_PATH}/../drivers/common
        # psa/crypto.h and psa/crypto_types.h
        ${TFM_PLATFORM_NXP_HAL_COMP_PATH}/../../../../../crypto/mbedtls/include
        ${TFM_PLATFORM_NXP_HAL_COMP_PATH}/../../../../../crypto/mbedtls/include/psa
        # for psa driver wrapper
        ${TFM_PLATFORM_NXP_HAL_COMP_PATH}/../../../../../crypto/mbedtls/library

        # zephyr includes for mutex protection
        osal/zephyr
        osal/.
)
endif()

target_include_directories(McuxPsaCryptoDriverElsPkc
    PUBLIC

        #psa-crypto-driver for els_pkc include paths
        els_pkc/.
        els_pkc/include/common
        els_pkc/include/opaque
        els_pkc/include/transparent
        els_pkc/oracle
        els_pkc/oracle/inc
            
        #include the psa-driver inlcude path from clib
        ${TFM_PLATFORM_NXP_HAL_COMP_PATH}/els_pkc/src/comps/mcuxClPsaDriver/inc
        ${TFM_PLATFORM_NXP_HAL_COMP_PATH}/els_pkc/src/comps/mcuxClPsaDriver/inc/internal

        #include McuxElsPkc include directories
        "$<TARGET_PROPERTY:McuxElsPkc,INTERFACE_INCLUDE_DIRECTORIES>"
)

if(CONFIG_BUILD_WITH_TFM)
    target_compile_options(
        McuxPsaCryptoDriverElsPkc
        PUBLIC
            ${COMPILER_CP_FLAG}
    )
    set(TFM_SOURCE_DIR ${CMAKE_SOURCE_DIR})
    target_compile_definitions(
        McuxPsaCryptoDriverElsPkc 
        PRIVATE
            MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
            MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS
            PSA_CRYPTO_DRIVER_TFM_BUILTIN_KEY_LOADER
            # The builtin key for initial attestation is only included if TF-M is 
            # built with initial attestation support enabled.
            $<$<BOOL:TFM_PARTITION_INITIAL_ATTESTATION>:TFM_PARTITION_INITIAL_ATTESTATION>
            MBEDTLS_CONFIG_FILE="${TFM_MBEDCRYPTO_CONFIG_PATH}"
            MBEDTLS_PSA_CRYPTO_CONFIG_FILE="${TFM_MBEDCRYPTO_PSA_CRYPTO_CONFIG_PATH}"
            $<$<BOOL:${TFM_MBEDCRYPTO_PLATFORM_EXTRA_CONFIG_PATH}>:MBEDTLS_USER_CONFIG_FILE="${TFM_MBEDCRYPTO_PLATFORM_EXTRA_CONFIG_PATH}">
    )

    target_include_directories(McuxPsaCryptoDriverElsPkc
        PRIVATE
            ${TFM_SOURCE_DIR}/config
            ${TFM_SOURCE_DIR}/interface/include
            ${TFM_SOURCE_DIR}/platform/include
            ${TFM_SOURCE_DIR}/secure_fw/include
            ${TFM_SOURCE_DIR}/secure_fw/partitions/lib/runtime/include
            ${TFM_SOURCE_DIR}/secure_fw/partitions/crypto
            ${TFM_SOURCE_DIR}/secure_fw/partitions/crypto/psa_driver_api
    )

    if(CONFIG_SOC_SERIES_RW6XX)
        target_include_directories(McuxPsaCryptoDriverElsPkc
            PRIVATE
                ${TFM_SOURCE_DIR}/platform/ext/target/nxp/rdrw61x/Device/Include
        )
    endif()
else()
    if(CONFIG_SOC_SERIES_RW6XX)
        target_include_directories(McuxPsaCryptoDriverElsPkc
            PRIVATE
                # include zephyr directories include path
                "$<TARGET_PROPERTY:zephyr,INTERFACE_INCLUDE_DIRECTORIES>"
        )
        target_compile_options(
            McuxPsaCryptoDriverElsPkc 
            PRIVATE
                "$<TARGET_PROPERTY:zephyr_interface,INTERFACE_COMPILE_OPTIONS>"
        )
    endif()

endif()

if(CONFIG_SOC_SERIES_RW6XX)

    target_compile_definitions(
        McuxPsaCryptoDriverElsPkc 
        PUBLIC
            CPU_RW612ETA1I
    ) 

    target_include_directories(McuxPsaCryptoDriverElsPkc
        PRIVATE
            # cmsis required to build els_pkc
            ${TFM_PLATFORM_NXP_HAL_COMP_PATH}/els_pkc/src/platforms/rw61x/cmsis_cortex_m_5_5_1/inc
    )

    target_sources(
        McuxPsaCryptoDriverElsPkc 
        PRIVATE
            els_pkc/oracle/src/mcuxClPsaDriver_Oracle.c
            els_pkc/oracle/src/mcuxClPsaDriver_Oracle_ElsUtils.c
            els_pkc/oracle/src/mcuxClPsaDriver_Oracle_Utils.c
            els_pkc/src/common/mcux_psa_els_pkc_common_init.c
            els_pkc/src/common/mcux_psa_els_pkc_entropy.c
            els_pkc/src/opaque/mcux_psa_els_pkc_opaque_aead.c
            els_pkc/src/opaque/mcux_psa_els_pkc_opaque_asymmetric_signature.c
            els_pkc/src/opaque/mcux_psa_els_pkc_opaque_cipher.c
            els_pkc/src/opaque/mcux_psa_els_pkc_opaque_init.c
            els_pkc/src/opaque/mcux_psa_els_pkc_opaque_key_generation.c
            els_pkc/src/opaque/mcux_psa_els_pkc_opaque_mac.c
            els_pkc/src/transparent/mcux_psa_els_pkc_aead.c
            els_pkc/src/transparent/mcux_psa_els_pkc_asymmetric_signature.c
            els_pkc/src/transparent/mcux_psa_els_pkc_cipher.c
            els_pkc/src/transparent/mcux_psa_els_pkc_hash.c
            els_pkc/src/transparent/mcux_psa_els_pkc_init.c
            els_pkc/src/transparent/mcux_psa_els_pkc_key_generation.c
            els_pkc/src/transparent/mcux_psa_els_pkc_mac.c
            
            # add psa-driver source files from els_pkc(clib) in this (psa_crypto_driver)lib
            ${TFM_PLATFORM_NXP_HAL_COMP_PATH}/els_pkc/src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_Aead.c
            ${TFM_PLATFORM_NXP_HAL_COMP_PATH}/els_pkc/src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_Cipher.c
            ${TFM_PLATFORM_NXP_HAL_COMP_PATH}/els_pkc/src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_DER_functions.c
            ${TFM_PLATFORM_NXP_HAL_COMP_PATH}/els_pkc/src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_Hash.c
            ${TFM_PLATFORM_NXP_HAL_COMP_PATH}/els_pkc/src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_Key.c
            ${TFM_PLATFORM_NXP_HAL_COMP_PATH}/els_pkc/src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_Mac.c
            ${TFM_PLATFORM_NXP_HAL_COMP_PATH}/els_pkc/src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_Rsa.c
            ${TFM_PLATFORM_NXP_HAL_COMP_PATH}/els_pkc/src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_Sign.c
            ${TFM_PLATFORM_NXP_HAL_COMP_PATH}/els_pkc/src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_UpdateKeyStatus.c
            ${TFM_PLATFORM_NXP_HAL_COMP_PATH}/els_pkc/src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_Verify.c
            ${TFM_PLATFORM_NXP_HAL_COMP_PATH}/els_pkc/src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_export_public_key.c
            ${TFM_PLATFORM_NXP_HAL_COMP_PATH}/els_pkc/src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_generate_ecp_key.c
    )
endif()


export(TARGETS McuxPsaCryptoDriverElsPkc
    FILE "${CMAKE_CURRENT_BINARY_DIR}/McuxPsaCryptoDriverElsPkcTargets.cmake"
    NAMESPACE McuxPsaCryptoDriverElsPkc::
)

#link McuxElsPkc lib as psa-crypto-driver functions eventually calls els_pkc functions.
target_link_libraries(McuxPsaCryptoDriverElsPkc
    PRIVATE
        McuxElsPkc
)

if (CONFIG_MCUX_PSA_CRYPTO_DRIVER_ELS_PKC_THREAD)
    add_compile_definitions(PSA_CRYPTO_DRIVER_THREAD_EN)
endif()

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/osal)
