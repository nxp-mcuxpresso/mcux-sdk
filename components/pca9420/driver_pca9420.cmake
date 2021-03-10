if(NOT DRIVER_PCA9420_INCLUDED)

    set(DRIVER_PCA9420_INCLUDED true CACHE BOOL "driver_pca9420 component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_pca9420.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_power)

endif()