if(NOT COMPONENT_MINIUSART_ADAPTER_INCLUDED)

    set(COMPONENT_MINIUSART_ADAPTER_INCLUDED true CACHE BOOL "component_miniusart_adapter component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_adapter_miniusart.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(${MCUX_DEVICE} STREQUAL "LPC845")
        include(driver_lpc_miniusart)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC812")
        include(driver_lpc_miniusart)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC802")
        include(driver_lpc_miniusart)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC824")
        include(driver_lpc_miniusart)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC804")
        include(driver_lpc_miniusart)
    endif()

    include(driver_common)

endif()