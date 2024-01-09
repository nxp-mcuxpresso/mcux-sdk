#Description: Component lpc_gpio_adapter; user_visible: True
include_guard(GLOBAL)
message("component_lpc_gpio_adapter component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_adapter_lpc_gpio.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_pint)
include(driver_inputmux)
include(driver_lpc_gpio)
