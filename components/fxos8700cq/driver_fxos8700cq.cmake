if(NOT DRIVER_FXOS8700CQ_INCLUDED)

    set(DRIVER_FXOS8700CQ_INCLUDED true CACHE BOOL "driver_fxos8700cq component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_fxos.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)

endif()