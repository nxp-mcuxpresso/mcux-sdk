if(NOT DRIVER_GPC_1_INCLUDED)

    set(DRIVER_GPC_1_INCLUDED true CACHE BOOL "driver_gpc_1 component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_gpc.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)

endif()