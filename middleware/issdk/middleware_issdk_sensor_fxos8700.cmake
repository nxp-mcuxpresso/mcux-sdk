#Description: Middleware issdk sensor fxos8700; user_visible: False
include_guard(GLOBAL)
message("middleware_issdk_sensor_fxos8700 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/sensors/fxos8700_drv.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/sensors
)


include(CMSIS_Driver_Include_I2C)
include(CMSIS_Driver_Include_SPI)
