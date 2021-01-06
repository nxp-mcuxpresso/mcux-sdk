if(NOT DRIVER_SDRAMC_INCLUDED)

    set(DRIVER_SDRAMC_INCLUDED true CACHE BOOL "driver_sdramc component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_sdramc.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)

endif()