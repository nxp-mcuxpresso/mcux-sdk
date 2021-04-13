if(NOT DRIVER_SDMA_INCLUDED)

    set(DRIVER_SDMA_INCLUDED true CACHE BOOL "driver_sdma component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_sdma.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_memory)

endif()