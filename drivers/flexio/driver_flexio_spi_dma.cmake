if(NOT DRIVER_FLEXIO_SPI_DMA_INCLUDED)

    set(DRIVER_FLEXIO_SPI_DMA_INCLUDED true CACHE BOOL "driver_flexio_spi_dma component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_flexio_spi_dma.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_dma)
    include(driver_flexio_spi)

endif()