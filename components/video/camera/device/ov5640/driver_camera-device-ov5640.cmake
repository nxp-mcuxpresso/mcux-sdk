#Description: Driver camera-device-ov5640; user_visible: True
include_guard(GLOBAL)
message("driver_camera-device-ov5640 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_ov5640.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_camera-device-sccb)
include(driver_camera-device-common)
