if(NOT COMPONENT_SERIAL_MANAGER_SWO_INCLUDED)

    set(COMPONENT_SERIAL_MANAGER_SWO_INCLUDED true CACHE BOOL "component_serial_manager_swo component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_component_serial_port_swo.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(${MCUX_DEVICE} STREQUAL "LPC55S16")
        include(component_serial_manager_LPC55S16)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC55S69_cm33_core0")
        include(component_serial_manager_LPC55S69_cm33_core0)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC55S28")
        include(component_serial_manager_LPC55S28)
    endif()

    include(driver_common)

endif()