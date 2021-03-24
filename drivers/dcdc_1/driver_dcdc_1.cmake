if(NOT DRIVER_DCDC_1_INCLUDED)

    set(DRIVER_DCDC_1_INCLUDED true CACHE BOOL "driver_dcdc_1 component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_dcdc.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)

endif()