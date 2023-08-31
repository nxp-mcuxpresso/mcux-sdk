#Description: Common Driver; user_visible: True
include_guard(GLOBAL)
message("driver_common component is included.")

if((DEFINED CMAKE_C_COMPILER) AND ((${CMAKE_C_COMPILER} MATCHES "xtensa") OR (${CMAKE_C_COMPILER} MATCHES "xt-clang")))
    set(MCUX_CPU_ARCH "DSP")
endif()

#Include core specific common file
set(SPECIFIC_COMMON_FILE "")
if(MCUX_CPU_ARCH MATCHES "DSP")
    set(SPECIFIC_COMMON_FILE "fsl_common_dsp.c")
else()
    set(SPECIFIC_COMMON_FILE "fsl_common_arm.c")
endif()

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_common.c
    ${CMAKE_CURRENT_LIST_DIR}/${SPECIFIC_COMMON_FILE}
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

include(driver_reset)

#CMSIS is not needed for Audio DSP
if(NOT (${MCUX_CPU_ARCH} MATCHES "DSP"))
    include(device_CMSIS)
endif()
