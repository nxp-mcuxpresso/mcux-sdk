if(NOT DRIVER_LPC_DMA_INCLUDED)

    set(DRIVER_LPC_DMA_INCLUDED true CACHE BOOL "driver_lpc_dma component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_dma.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)

endif()