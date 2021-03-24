if(NOT COMPONENT_SERIAL_MANAGER_K32L2A41A_INCLUDED)

    set(COMPONENT_SERIAL_MANAGER_K32L2A41A_INCLUDED true CACHE BOOL "component_serial_manager component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_component_serial_manager.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(CONFIG_USE_component_serial_manager_uart_K32L2A41A) 
        include(component_serial_manager_uart_K32L2A41A)
    endif()

    include(driver_common)
    include(component_lists)

endif()