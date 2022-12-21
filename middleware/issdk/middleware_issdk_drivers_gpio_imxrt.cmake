#Description: Middleware issdk drivers gpio_imxrt; user_visible: False
include_guard(GLOBAL)
message("middleware_issdk_drivers_gpio_imxrt component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/drivers/gpio/i.mx/gpio_driver.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/drivers/gpio
    ${CMAKE_CURRENT_LIST_DIR}/drivers/gpio/i.mx
)


include(middleware_issdk_drivers_cmsis_drivers)
