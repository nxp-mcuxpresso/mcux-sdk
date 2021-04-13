if(NOT COMPONENT_MINIUSART_ADAPTER_INCLUDED)

    set(COMPONENT_MINIUSART_ADAPTER_INCLUDED true CACHE BOOL "component_miniusart_adapter component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_adapter_miniusart.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_lpc_miniusart)

endif()