if(NOT MIDDLEWARE_ISSDK_ALGORITHMS_PEDOMETER_LIB_CM4_INCLUDED)

    set(MIDDLEWARE_ISSDK_ALGORITHMS_PEDOMETER_LIB_CM4_INCLUDED true CACHE BOOL "middleware_issdk_algorithms_pedometer_lib_cm4 component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    )



endif()