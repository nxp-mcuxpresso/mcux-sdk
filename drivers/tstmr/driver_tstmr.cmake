if(NOT DRIVER_TSTMR_INCLUDED)

    set(DRIVER_TSTMR_INCLUDED true CACHE BOOL "driver_tstmr component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)

endif()