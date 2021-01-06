if(NOT DRIVER_FLEXCOMM_INCLUDED)

    set(DRIVER_FLEXCOMM_INCLUDED true CACHE BOOL "driver_flexcomm component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_flexcomm.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)

endif()