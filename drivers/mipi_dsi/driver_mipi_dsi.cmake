if(NOT DRIVER_MIPI_DSI_INCLUDED)

    set(DRIVER_MIPI_DSI_INCLUDED true CACHE BOOL "driver_mipi_dsi component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_mipi_dsi.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)

endif()