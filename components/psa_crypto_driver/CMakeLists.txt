#-------------------------------------------------------------------------------
# Copyright 2023-2024 NXP
# SPDX-License-Identifier: BSD-3-Clause
#
#-------------------------------------------------------------------------------

if(NOT CONFIG_BUILD_WITH_TFM)
    find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
endif()

add_library(McuxPsaCryptoDriverElsPkc)

# set path of crypto modules in zephyr subsystem
if(CONFIG_BUILD_WITH_TFM)
set(NXP_MODULE_CRYPTO_PATH ${MBEDCRYPTO_PATH}/../)
set(NXP_MODULE_ELS_PKC_PATH ${NXP_MODULE_CRYPTO_PATH}/els_pkc)
else()
set(NXP_MODULE_CRYPTO_PATH ${ZEPHYR_MBEDTLS_MODULE_DIR}/../)
set(NXP_MODULE_ELS_PKC_PATH ${ZEPHYR_ELS_PKC_MODULE_DIR})
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
    target_compile_options(
        McuxPsaCryptoDriverElsPkc
        PUBLIC
            ${COMPILER_CP_FLAG}
    )
    set(TFM_SOURCE_DIR ${CMAKE_SOURCE_DIR})
    target_compile_definitions(
        McuxPsaCryptoDriverElsPkc 
        PRIVATE
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
            # SDK driver header files path
            ${NXP_HAL_FILE_PATH}/common/Native_Driver/drivers

            #tf-m src include paths
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
                # SDK driver header files path of rw61x
                ${NXP_HAL_FILE_PATH}/rdrw61x/Native_Driver
                ${NXP_HAL_FILE_PATH}/rdrw61x/Native_Driver/drivers
        )
        target_sources(
            McuxPsaCryptoDriverElsPkc 
            PRIVATE
                # SDK driver files
                ${NXP_HAL_FILE_PATH}/common/Native_Driver/drivers/fsl_trng.c
        )
    endif()
else()

    target_include_directories(McuxPsaCryptoDriverElsPkc
        PRIVATE
            # SDK driver header files
            ${ZEPHYR_HAL_NXP_MODULE_DIR}/mcux/mcux-sdk/drivers/common
            ${ZEPHYR_HAL_NXP_MODULE_DIR}/mcux/mcux-sdk/drivers/trng
            # zephyr includes for mutex functions for psa-crypto-driver
            ${CMAKE_CURRENT_LIST_DIR}/osal/zephyr
            ${CMAKE_CURRENT_LIST_DIR}/osal/.
            # include zephyr directories include path
            "$<TARGET_PROPERTY:zephyr,INTERFACE_INCLUDE_DIRECTORIES>"
    )

    target_sources(
        McuxPsaCryptoDriverElsPkc 
        PRIVATE
            # SDK driver files
            ${ZEPHYR_HAL_NXP_MODULE_DIR}/mcux/mcux-sdk/drivers/trng/fsl_trng.c
    )

    target_compile_options(
        McuxPsaCryptoDriverElsPkc 
        PRIVATE
            "$<TARGET_PROPERTY:zephyr_interface,INTERFACE_COMPILE_OPTIONS>"
    )
    if(CONFIG_SOC_SERIES_RW6XX)
        add_dependencies(McuxPsaCryptoDriverElsPkc zephyr_interface)
        if (CONFIG_MCUX_PSA_CRYPTO_DRIVER_ELS_PKC_THREAD)
            target_include_directories(McuxPsaCryptoDriverElsPkc
                PUBLIC
                    # zephyr includes for mutex functions for mbedtls layer
                    ${CMAKE_CURRENT_LIST_DIR}/mbedtls_thread_alt/.
                    ${ZEPHYR_BASE}/include
                    ${CMAKE_BINARY_DIR}
            )
            target_sources(
                McuxPsaCryptoDriverElsPkc 
                PRIVATE
                    # Providing threading alt source for mbedtls
                    ${CMAKE_CURRENT_LIST_DIR}/mbedtls_thread_alt/threading_alt.c
            )
            target_compile_definitions(
                McuxPsaCryptoDriverElsPkc 
                PRIVATE
                    PSA_CRYPTO_DRIVER_THREAD_EN
                    __ZEPHYR__
                    #$<$<BOOL:${CONFIG_MBEDTLS_CFG_FILE}>:MBEDTLS_CONFIG_FILE="${CONFIG_MBEDTLS_CFG_FILE}">
                    $<$<BOOL:${CONFIG_MBEDTLS_USER_CONFIG_FILE}>:MBEDTLS_USER_CONFIG_FILE="${CONFIG_MBEDTLS_USER_CONFIG_FILE}">
            )
        endif()
    endif()

endif()

if(CONFIG_SOC_SERIES_RW6XX)

    target_compile_definitions(
        McuxPsaCryptoDriverElsPkc 
        PUBLIC
            CPU_RW612ETA1I
    )

    target_compile_definitions(
        McuxPsaCryptoDriverElsPkc 
        PRIVATE
            MBEDTLS_MCUX_ENTROPY
    )

    target_include_directories(McuxPsaCryptoDriverElsPkc
        PUBLIC
            #psa-crypto-driver for els_pkc include paths
            ${CMAKE_CURRENT_LIST_DIR}/els_pkc/.
            ${CMAKE_CURRENT_LIST_DIR}/els_pkc/include/common
            ${CMAKE_CURRENT_LIST_DIR}/els_pkc/include/opaque
            ${CMAKE_CURRENT_LIST_DIR}/els_pkc/include/transparent
            ${CMAKE_CURRENT_LIST_DIR}/els_pkc/oracle
            ${CMAKE_CURRENT_LIST_DIR}/els_pkc/oracle/inc
    
            #include the psa-driver inlcude path from clib
            ${NXP_MODULE_ELS_PKC_PATH}/src/comps/mcuxClPsaDriver/inc
            ${NXP_MODULE_ELS_PKC_PATH}/src/comps/mcuxClPsaDriver/inc/internal

            #include McuxElsPkc include directories
            "$<TARGET_PROPERTY:McuxElsPkc,INTERFACE_INCLUDE_DIRECTORIES>"
    )

    target_include_directories(McuxPsaCryptoDriverElsPkc
        PRIVATE
            # psa/crypto.h and psa/crypto_types.h
            ${NXP_MODULE_CRYPTO_PATH}/mbedtls/include
            ${NXP_MODULE_CRYPTO_PATH}/mbedtls/include/psa
            # for psa driver wrapper
            ${NXP_MODULE_CRYPTO_PATH}/mbedtls/library
            # cmsis required to build els_pkc
            ${NXP_MODULE_ELS_PKC_PATH}/src/platforms/rw61x/cmsis_cortex_m_5_5_1/inc
    )

    target_sources(
        McuxPsaCryptoDriverElsPkc 
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/els_pkc/oracle/src/mcuxClPsaDriver_Oracle.c
            ${CMAKE_CURRENT_LIST_DIR}/els_pkc/oracle/src/mcuxClPsaDriver_Oracle_ElsUtils.c
            ${CMAKE_CURRENT_LIST_DIR}/els_pkc/oracle/src/mcuxClPsaDriver_Oracle_Utils.c
            ${CMAKE_CURRENT_LIST_DIR}/els_pkc/src/common/mcux_psa_els_pkc_common_init.c
            ${CMAKE_CURRENT_LIST_DIR}/els_pkc/src/common/mcux_psa_els_pkc_entropy.c
            ${CMAKE_CURRENT_LIST_DIR}/els_pkc/src/opaque/mcux_psa_els_pkc_opaque_aead.c
            ${CMAKE_CURRENT_LIST_DIR}/els_pkc/src/opaque/mcux_psa_els_pkc_opaque_asymmetric_signature.c
            ${CMAKE_CURRENT_LIST_DIR}/els_pkc/src/opaque/mcux_psa_els_pkc_opaque_cipher.c
            ${CMAKE_CURRENT_LIST_DIR}/els_pkc/src/opaque/mcux_psa_els_pkc_opaque_init.c
            ${CMAKE_CURRENT_LIST_DIR}/els_pkc/src/opaque/mcux_psa_els_pkc_opaque_key_generation.c
            ${CMAKE_CURRENT_LIST_DIR}/els_pkc/src/opaque/mcux_psa_els_pkc_opaque_mac.c
            ${CMAKE_CURRENT_LIST_DIR}/els_pkc/src/transparent/mcux_psa_els_pkc_aead.c
            ${CMAKE_CURRENT_LIST_DIR}/els_pkc/src/transparent/mcux_psa_els_pkc_asymmetric_signature.c
            ${CMAKE_CURRENT_LIST_DIR}/els_pkc/src/transparent/mcux_psa_els_pkc_cipher.c
            ${CMAKE_CURRENT_LIST_DIR}/els_pkc/src/transparent/mcux_psa_els_pkc_hash.c
            ${CMAKE_CURRENT_LIST_DIR}/els_pkc/src/transparent/mcux_psa_els_pkc_init.c
            ${CMAKE_CURRENT_LIST_DIR}/els_pkc/src/transparent/mcux_psa_els_pkc_key_generation.c
            ${CMAKE_CURRENT_LIST_DIR}/els_pkc/src/transparent/mcux_psa_els_pkc_mac.c
            
            # add psa-driver source files from els_pkc(clib) in this (psa_crypto_driver)lib
            ${NXP_MODULE_ELS_PKC_PATH}/src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_Aead.c
            ${NXP_MODULE_ELS_PKC_PATH}/src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_Cipher.c
            ${NXP_MODULE_ELS_PKC_PATH}/src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_DER_functions.c
            ${NXP_MODULE_ELS_PKC_PATH}/src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_Hash.c
            ${NXP_MODULE_ELS_PKC_PATH}/src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_Key.c
            ${NXP_MODULE_ELS_PKC_PATH}/src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_Mac.c
            ${NXP_MODULE_ELS_PKC_PATH}/src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_Rsa.c
            ${NXP_MODULE_ELS_PKC_PATH}/src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_Sign.c
            ${NXP_MODULE_ELS_PKC_PATH}/src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_UpdateKeyStatus.c
            ${NXP_MODULE_ELS_PKC_PATH}/src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_Verify.c
            ${NXP_MODULE_ELS_PKC_PATH}/src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_export_public_key.c
            ${NXP_MODULE_ELS_PKC_PATH}/src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_generate_ecp_key.c
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

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/osal)
