if(NOT DRIVER_MMA8451Q_INCLUDED)

    set(DRIVER_MMA8451Q_INCLUDED true CACHE BOOL "driver_mma8451q component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_mma.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)

endif()