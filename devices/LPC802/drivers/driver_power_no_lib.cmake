if(NOT DRIVER_POWER_NO_LIB_INCLUDED)

    set(DRIVER_POWER_NO_LIB_INCLUDED true CACHE BOOL "driver_power_no_lib component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_power.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)

endif()