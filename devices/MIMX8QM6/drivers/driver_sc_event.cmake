if(NOT DRIVER_SC_EVENT_INCLUDED)

    set(DRIVER_SC_EVENT_INCLUDED true CACHE BOOL "driver_sc_event component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_sc_event.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)
    include(driver_scfw_api)
    include(driver_mu)

endif()