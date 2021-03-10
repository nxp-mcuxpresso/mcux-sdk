if(NOT COMPONENT_I3C_ADAPTER_INCLUDED)

    set(COMPONENT_I3C_ADAPTER_INCLUDED true CACHE BOOL "component_i3c_adapter component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_adapter_i3c.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)
    include(driver_i3c)

endif()