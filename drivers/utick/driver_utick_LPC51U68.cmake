if(NOT DRIVER_UTICK_LPC51U68_INCLUDED)

    set(DRIVER_UTICK_LPC51U68_INCLUDED true CACHE BOOL "driver_utick component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_utick.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)

endif()