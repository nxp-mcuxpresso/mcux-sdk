if(NOT COMPONENT_II2C_ADAPTER_INCLUDED)

    set(COMPONENT_II2C_ADAPTER_INCLUDED true CACHE BOOL "component_ii2c_adapter component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_adapter_ii2c.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)
    include(driver_ii2c)

endif()