#Description: Driver camera-device-mt9m114; user_visible: True
include_guard(GLOBAL)
message("driver_camera-device-mt9m114 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_mt9m114.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_camera-device-common)
include(driver_video-i2c)
