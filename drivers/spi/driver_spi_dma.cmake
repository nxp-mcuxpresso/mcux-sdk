if(NOT DRIVER_SPI_DMA_INCLUDED)

    set(DRIVER_SPI_DMA_INCLUDED true CACHE BOOL "driver_spi_dma component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_spi_dma.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_spi)
    include(driver_dma)

endif()