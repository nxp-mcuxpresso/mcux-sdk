if(NOT DRIVER_FLEXIO_MCULCD_INCLUDED)

    set(DRIVER_FLEXIO_MCULCD_INCLUDED true CACHE BOOL "driver_flexio_mculcd component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_flexio_mculcd.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_flexio)

endif()