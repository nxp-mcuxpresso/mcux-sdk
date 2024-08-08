#-------------------------------------------------------------------------------
# Copyright (c) 2023-24 NXP.
# SPDX-License-Identifier: BSD-3-Clause
#
#-------------------------------------------------------------------------------

#Description: Driver conn_fwloader; user_visible: True
include_guard(GLOBAL)
message("driver_conn_fwloader component is included.")

if(NOT CONFIG_BUILD_WITH_TFM)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_loader.c
    ${CMAKE_CURRENT_LIST_DIR}/fsl_loader_utils.c
    ${CMAKE_CURRENT_LIST_DIR}/nboot_hal.c
    ${CMAKE_CURRENT_LIST_DIR}/life_cycle.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)
endif()

if(CONFIG_BUILD_WITH_TFM)
    add_compile_definitions(TFM_PARTITION_LOADER_SERVICE)
endif()

#OR Logic component
if(CONFIG_USE_component_osa_free_rtos_RW612) 
    include(component_osa_free_rtos_RW612)
endif()
if(CONFIG_USE_component_osa_bm) 
    include(component_osa_bm)
endif()

include(driver_ocotp)
