if(NOT COMPONENT_UART_ADAPTER_INCLUDED)

    set(COMPONENT_UART_ADAPTER_INCLUDED true CACHE BOOL "component_uart_adapter component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_adapter_uart.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(${MCUX_DEVICE} STREQUAL "MK64F12")
        include(driver_uart)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MK66F18")
        include(driver_uart)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MKV11Z7")
        include(driver_uart)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MKV31F51212")
        include(driver_uart)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MK22F51212")
        include(driver_uart)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MKE06Z4")
        include(driver_uart)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MKE02Z4")
        include(driver_uart)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MKE04Z4")
        include(driver_uart)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MKM35Z7")
        include(driver_uart)
    endif()

    include(driver_common)

endif()