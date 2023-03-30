#Description: Middleware issdk sensor mag3110; user_visible: False
include_guard(GLOBAL)
message("middleware_issdk_sensor_mag3110 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/sensors/mag3110_drv.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/sensors
)


include(CMSIS_Driver_Include_I2C)
include(CMSIS_Driver_Include_SPI)
