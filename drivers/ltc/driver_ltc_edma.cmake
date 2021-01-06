if(NOT DRIVER_LTC_EDMA_INCLUDED)

    set(DRIVER_LTC_EDMA_INCLUDED true CACHE BOOL "driver_ltc_edma component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_ltc_edma.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_ltc)
    include(driver_edma)

endif()