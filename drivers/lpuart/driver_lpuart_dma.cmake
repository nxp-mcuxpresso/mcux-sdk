if(NOT DRIVER_LPUART_DMA_INCLUDED)

    set(DRIVER_LPUART_DMA_INCLUDED true CACHE BOOL "driver_lpuart_dma component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_lpuart_dma.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_dma)
    include(driver_lpuart)

endif()