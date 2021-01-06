if(NOT DRIVER_IS42SM16800H_INCLUDED)

    set(DRIVER_IS42SM16800H_INCLUDED true CACHE BOOL "driver_IS42SM16800H component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_sdram.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_sdramc)

endif()