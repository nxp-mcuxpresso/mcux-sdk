#Description: Cmsis_driver_include i2c; user_visible: False
include_guard(GLOBAL)
message("CMSIS_Driver_Include_I2C component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(CMSIS_Driver_Include_Common)
