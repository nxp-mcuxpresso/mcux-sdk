#-------------------------------------------------------------------------------
# Copyright (c) 2023-2024 NXP.
# SPDX-License-Identifier: BSD-3-Clause
#
#-------------------------------------------------------------------------------

add_library(McuxElsPkc) 

target_compile_options(
    McuxElsPkc
    PUBLIC
        ${TOOLCHAIN_C_FLAGS}
        -mcmse  # Why is this not even part of the default zephyr build options?
)

target_link_options(
    McuxElsPkc
    PRIVATE
        ${TOOLCHAIN_LD_FLAGS}
)

target_include_directories(McuxElsPkc
    PRIVATE
        # SDK driver header files
        ${CMAKE_CURRENT_SOURCE_DIR}/../../drivers/common
        # psa/crypto.h and psa/crypto_types.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../crypto/mbedtls/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../crypto/mbedtls/include/psa
        # for psa driver wrapper
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../crypto/mbedtls/library
)

if(CONFIG_BUILD_WITH_TFM)
    target_compile_options(
        McuxElsPkc
        PUBLIC
            ${COMPILER_CP_FLAG}
    )
endif()

if(CONFIG_SOC_SERIES_RW6XX)

    target_compile_definitions(
        McuxElsPkc 
        PUBLIC
            CPU_RW612ETA1I
            CPU_RW612ETA2I
    ) 

    target_include_directories(McuxElsPkc
        PRIVATE
            # cmsis required to build els_pkc
            ${CMAKE_CURRENT_SOURCE_DIR}/src/platforms/rw61x/cmsis_cortex_m_5_5_1/inc
    )

    target_include_directories(McuxElsPkc
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/src/platforms/rw61x/
            ${CMAKE_CURRENT_SOURCE_DIR}/src/platforms/rw61x/inc
            ${CMAKE_CURRENT_SOURCE_DIR}/../../devices/RW612
            ${CMAKE_CURRENT_SOURCE_DIR}/../../devices/RW612/drivers
    )

    target_sources(McuxElsPkc
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src/platforms/rw61x/mcux_els.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/platforms/rw61x/mcux_pkc.c
    )
endif()

if(CONFIG_EXPORT_MCUX_ELS_PKC_TARGETS)
export(TARGETS McuxElsPkc
    FILE "${CMAKE_CURRENT_BINARY_DIR}/McuxElsPkcTargets.cmake"
    NAMESPACE McuxElsPkc::
)
endif()
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src)
