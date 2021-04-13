if(NOT COMPONENT_UART_ADAPTER_INCLUDED)

    set(COMPONENT_UART_ADAPTER_INCLUDED true CACHE BOOL "component_uart_adapter component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_adapter_uart.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_uart)

endif()