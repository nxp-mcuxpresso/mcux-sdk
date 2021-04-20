#Description: FLEXIO UART EDMA Driver; user_visible: True
include_guard(GLOBAL)
message("driver_flexio_uart_edma component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_flexio_uart_edma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_flexio_uart)
include(driver_edma)
