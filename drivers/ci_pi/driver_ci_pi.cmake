if(NOT DRIVER_CI_PI_INCLUDED)

    set(DRIVER_CI_PI_INCLUDED true CACHE BOOL "driver_ci_pi component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_ci_pi.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)

endif()