if(NOT DRIVER_FLEXCOMM_USART_DMA_INCLUDED)

    set(DRIVER_FLEXCOMM_USART_DMA_INCLUDED true CACHE BOOL "driver_flexcomm_usart_dma component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_usart_dma.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_lpc_dma)
    include(driver_flexcomm_usart)
    include(driver_flexcomm)

endif()