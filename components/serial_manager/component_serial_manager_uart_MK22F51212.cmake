if(NOT COMPONENT_SERIAL_MANAGER_UART_MK22F51212_INCLUDED)

    set(COMPONENT_SERIAL_MANAGER_UART_MK22F51212_INCLUDED true CACHE BOOL "component_serial_manager_uart component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_component_serial_port_uart.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(CONFIG_USE_driver_lpuart) 
        include(driver_lpuart)
    endif()
    if(CONFIG_USE_driver_uart) 
        include(driver_uart)
    endif()

    include(component_uart_adapter)
    include(component_serial_manager_MK22F51212)

endif()