if(NOT MIDDLEWARE_ISSDK_ALGORITHMS_PEDOMETER_COMMON_INCLUDED)

    set(MIDDLEWARE_ISSDK_ALGORITHMS_PEDOMETER_COMMON_INCLUDED true CACHE BOOL "middleware_issdk_algorithms_pedometer_common component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/algorithms/pedometer/source/pedometer.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/algorithms/pedometer/include
        ${CMAKE_CURRENT_LIST_DIR}/algorithms/pedometer/include/libinclude
    )


    include(CMSIS_Driver_Include_I2C)
    include(CMSIS_Driver_Include_SPI)

endif()