#Description: UART FREERTOS Driver; user_visible: True
include_guard(GLOBAL)
message("driver_uart_freertos component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_uart_freertos.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(middleware_freertos-kernel_MK22F51212)
include(driver_uart)
