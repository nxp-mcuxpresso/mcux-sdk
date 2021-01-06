if(NOT DRIVER_IPWM_INCLUDED)

    set(DRIVER_IPWM_INCLUDED true CACHE BOOL "driver_ipwm component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_pwm.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )



endif()