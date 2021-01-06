if(NOT DRIVER_TSI_V4_INCLUDED)

    set(DRIVER_TSI_V4_INCLUDED true CACHE BOOL "driver_tsi_v4 component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_tsi_v4.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)

endif()