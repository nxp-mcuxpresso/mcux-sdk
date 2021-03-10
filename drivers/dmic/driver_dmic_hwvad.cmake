if(NOT DRIVER_DMIC_HWVAD_INCLUDED)

    set(DRIVER_DMIC_HWVAD_INCLUDED true CACHE BOOL "driver_dmic_hwvad component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_dmic.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)
    include(driver_dmic)

endif()