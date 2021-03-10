if(NOT DRIVER_LPC_ACOMP_INCLUDED)

    set(DRIVER_LPC_ACOMP_INCLUDED true CACHE BOOL "driver_lpc_acomp component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_acomp.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)

endif()