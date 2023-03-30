#Description: Middleware issdk drivers gpio_lpc; user_visible: False
include_guard(GLOBAL)
message("middleware_issdk_drivers_gpio_lpc component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/drivers/gpio/lpc/gpio_driver_irq.c
    ${CMAKE_CURRENT_LIST_DIR}/drivers/gpio/lpc/gpio_driver.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/drivers/gpio
    ${CMAKE_CURRENT_LIST_DIR}/drivers/gpio/lpc
)


include(middleware_issdk_drivers_cmsis_drivers)
