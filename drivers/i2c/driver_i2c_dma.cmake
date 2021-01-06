if(NOT DRIVER_I2C_DMA_INCLUDED)

    set(DRIVER_I2C_DMA_INCLUDED true CACHE BOOL "driver_i2c_dma component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_i2c_dma.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_dma)
    include(driver_i2c)

endif()