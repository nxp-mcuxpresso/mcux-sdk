if(NOT DRIVER_MIPI_CSI2RX_INCLUDED)

    set(DRIVER_MIPI_CSI2RX_INCLUDED true CACHE BOOL "driver_mipi_csi2rx component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_mipi_csi2rx.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)

endif()