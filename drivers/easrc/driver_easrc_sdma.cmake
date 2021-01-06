if(NOT DRIVER_EASRC_SDMA_INCLUDED)

    set(DRIVER_EASRC_SDMA_INCLUDED true CACHE BOOL "driver_easrc_sdma component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_asrc_sdma.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_easrc)
    include(driver_common)
    include(driver_sdma)

endif()