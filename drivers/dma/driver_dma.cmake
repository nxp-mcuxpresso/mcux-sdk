if(NOT DRIVER_DMA_INCLUDED)

    set(DRIVER_DMA_INCLUDED true CACHE BOOL "driver_dma component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_dma.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(${MCUX_DEVICE} STREQUAL "K32L2B31A")
        include(driver_dmamux)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MKM35Z7")
        include(driver_dmamux)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MKL27Z644")
        include(driver_dmamux)
    endif()

    include(driver_common)

endif()