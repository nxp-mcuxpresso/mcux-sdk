if(NOT DRIVER_ADC_12B1MSPS_SAR_INCLUDED)

    set(DRIVER_ADC_12B1MSPS_SAR_INCLUDED true CACHE BOOL "driver_adc_12b1msps_sar component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_adc.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)

endif()