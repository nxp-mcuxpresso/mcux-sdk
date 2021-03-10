if(NOT DRIVER_SPIFI_DMA_INCLUDED)

    set(DRIVER_SPIFI_DMA_INCLUDED true CACHE BOOL "driver_spifi_dma component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_spifi_dma.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_lpc_dma)
    include(driver_spifi)

endif()