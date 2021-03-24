if(NOT DRIVER_DBI_FLEXIO_EDMA_INCLUDED)

    set(DRIVER_DBI_FLEXIO_EDMA_INCLUDED true CACHE BOOL "driver_dbi_flexio_edma component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_dbi_flexio_edma.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_flexio_mculcd)
    include(driver_flexio_mculcd_edma)
    include(driver_dbi)

endif()