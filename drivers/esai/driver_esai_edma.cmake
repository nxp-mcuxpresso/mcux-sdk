if(NOT DRIVER_ESAI_EDMA_INCLUDED)

    set(DRIVER_ESAI_EDMA_INCLUDED true CACHE BOOL "driver_esai_edma component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_esai_edma.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_esai)

endif()