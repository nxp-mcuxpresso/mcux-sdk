if(NOT DRIVER_UART_DMA_INCLUDED)

    set(DRIVER_UART_DMA_INCLUDED true CACHE BOOL "driver_uart_dma component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_uart_dma.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_dma)
    include(driver_uart)

endif()