if(NOT DRIVER_LPCMP_INCLUDED)

    set(DRIVER_LPCMP_INCLUDED true CACHE BOOL "driver_lpcmp component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_lpcmp.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)

endif()