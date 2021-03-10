if(NOT COMPONENT_IUART_ADAPTER_INCLUDED)

    set(COMPONENT_IUART_ADAPTER_INCLUDED true CACHE BOOL "component_iuart_adapter component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_adapter_iuart.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(${MCUX_DEVICE} STREQUAL "MIMX8MQ6")
        include(driver_iuart)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8MM6")
        include(driver_iuart)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8MN6")
        include(driver_iuart)
    endif()

    include(driver_common)

endif()