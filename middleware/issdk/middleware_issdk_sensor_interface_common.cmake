#Description: Middleware issdk sensor interface common; user_visible: False
include_guard(GLOBAL)
message("middleware_issdk_sensor_interface_common component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/sensors/register_io_i2c.c
    ${CMAKE_CURRENT_LIST_DIR}/sensors/register_io_spi.c
    ${CMAKE_CURRENT_LIST_DIR}/sensors/sensor_io_spi.c
    ${CMAKE_CURRENT_LIST_DIR}/sensors/sensor_io_i2c.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/sensors
)


include(CMSIS_Driver_Include_I2C)
include(CMSIS_Driver_Include_SPI)
