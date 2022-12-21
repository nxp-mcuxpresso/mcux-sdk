#Description: Middleware issdk drivers gpio_kinetis_ke15z; user_visible: True
include_guard(GLOBAL)
message("middleware_issdk_drivers_gpio_kinetis_ke15z component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/drivers/gpio/kinetis/gpio_driver_irq_ke15z.c
    ${CMAKE_CURRENT_LIST_DIR}/drivers/gpio/kinetis/gpio_driver.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/drivers/gpio
    ${CMAKE_CURRENT_LIST_DIR}/drivers/gpio/kinetis
)


include(middleware_issdk_drivers_cmsis_drivers)
