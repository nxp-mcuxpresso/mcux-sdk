if(NOT COMPONENT_SERIAL_MANAGER_UART_LPC51U68_INCLUDED)

    set(COMPONENT_SERIAL_MANAGER_UART_LPC51U68_INCLUDED true CACHE BOOL "component_serial_manager_uart component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_component_serial_port_uart.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(component_serial_manager_LPC51U68)
    include(driver_flexcomm_usart)
    include(component_usart_adapter)

endif()