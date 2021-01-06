# CROSS COMPILER SETTING
SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_MINIMUM_REQUIRED (VERSION 3.1.1)

# THE VERSION NUMBER
SET (Tutorial_VERSION_MAJOR 1)
SET (Tutorial_VERSION_MINOR 0)

# ENABLE ASM
ENABLE_LANGUAGE(ASM)

SET(CMAKE_STATIC_LIBRARY_PREFIX)
SET(CMAKE_STATIC_LIBRARY_SUFFIX)

SET(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
SET(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)

# CURRENT DIRECTORY
SET(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})

SET(EXECUTABLE_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})
SET(LIBRARY_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})


project(isi_mipi_csi2_yuv422)

set(MCUX_SDK_PROJECT_NAME isi_mipi_csi2_yuv422.elf)

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
"${ProjDirPath}/../isi_mipi_csi2_yuv422.c"
"${ProjDirPath}/../app_display.h"
"${ProjDirPath}/../app_display.c"
"${ProjDirPath}/../pin_mux.c"
"${ProjDirPath}/../pin_mux.h"
"${ProjDirPath}/../isi_board.c"
"${ProjDirPath}/../isi_config.h"
"${ProjDirPath}/../isi_example.h"
"${ProjDirPath}/../../../../../board.c"
"${ProjDirPath}/../../../../../board.h"
"${ProjDirPath}/../../../../../clock_config.c"
"${ProjDirPath}/../../../../../clock_config.h"
"${ProjDirPath}/../empty_rsc_table.c"
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${ProjDirPath}/..
    ${ProjDirPath}/../../../../..
)

#path for entry cmake
set(CMAKE_MODULE_PATH
    ${ProjDirPath}/../../../../../../..
)

#Include Entry cmake component
include(all_devices)

# include modules
include(driver_irqsteer)

include(driver_mipi_dsi)

include(driver_lpi2c)

include(driver_video-common)

include(driver_dpu)

include(driver_video-i2c)

include(driver_display-common)

include(driver_display-adv7535)

include(driver_display-rm67191)

include(driver_display-mipi-dsi-cmd)

include(driver_dpu_irqsteer)

include(driver_camera-device-ov5640)

include(driver_camera-device-sccb)

include(driver_display-it6263)

include(driver_ldb_combo_phy)

include(driver_camera-device-max9286)

include(driver_prg)

include(driver_dpr)

include(utility_debug_console_lite)

include(utility_assert_lite_MIMX8QX6)

include(driver_igpio)

include(driver_isi)

include(driver_mipi_csi2rx)

include(driver_camera-common)

include(driver_camera-device-common)

include(driver_camera-receiver-common)

include(driver_camera-receiver-isi)

include(driver_clock)

include(driver_common)

include(device_CMSIS)

include(component_lpuart_adapter)

include(component_lists)

include(driver_lpuart)

include(device_startup)

include(driver_scfw_api)

include(CMSIS_Include_core_cm4)

include(CMSIS_Include_common)

include(CMSIS_Include_dsp)

include(utilities_misc_utilities)

include(device_system)


TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE m)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE c)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE gcc)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE nosys)

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)

ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY}
-Obinary ${EXECUTABLE_OUTPUT_PATH}/${MCUX_SDK_PROJECT_NAME} ${EXECUTABLE_OUTPUT_PATH}/isi_mipi_csi2_yuv422.bin)

