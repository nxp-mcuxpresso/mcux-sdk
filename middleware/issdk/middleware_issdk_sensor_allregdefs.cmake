if(NOT MIDDLEWARE_ISSDK_SENSOR_ALLREGDEFS_INCLUDED)

    set(MIDDLEWARE_ISSDK_SENSOR_ALLREGDEFS_INCLUDED true CACHE BOOL "middleware_issdk_sensor_allregdefs component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/sensors
    )


    include(CMSIS_Driver_Include_I2C)
    include(CMSIS_Driver_Include_SPI)

endif()