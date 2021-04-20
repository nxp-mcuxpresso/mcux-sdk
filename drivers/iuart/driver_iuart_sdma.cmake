#Description: IUART SDMA Driver; user_visible: True
include_guard(GLOBAL)
message("driver_iuart_sdma component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_uart_sdma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_sdma)
include(driver_iuart)
