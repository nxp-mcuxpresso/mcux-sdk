#Description: Driver camera-device-common; user_visible: True
include_guard(GLOBAL)
message("driver_camera-device-common component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_camera-common)
include(driver_common)
