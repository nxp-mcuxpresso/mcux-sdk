if(NOT DRIVER_ADC_5V12B_LL18_015_INCLUDED)

    set(DRIVER_ADC_5V12B_LL18_015_INCLUDED true CACHE BOOL "driver_adc_5v12b_ll18_015 component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_adc.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)

endif()