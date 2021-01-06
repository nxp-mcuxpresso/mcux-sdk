if(NOT DRIVER_PDM_SDMA_INCLUDED)

    set(DRIVER_PDM_SDMA_INCLUDED true CACHE BOOL "driver_pdm_sdma component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_pdm_sdma.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(${MCUX_DEVICE} STREQUAL "MIMX8MM6")
        include(driver_pdm)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8MN6")
        include(driver_pdm)
    endif()


endif()