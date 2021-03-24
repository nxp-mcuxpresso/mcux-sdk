if(NOT DRIVER_SDHC_INCLUDED)

    set(DRIVER_SDHC_INCLUDED true CACHE BOOL "driver_sdhc component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_sdhc.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)

endif()