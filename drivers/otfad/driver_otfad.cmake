if(NOT DRIVER_OTFAD_INCLUDED)

    set(DRIVER_OTFAD_INCLUDED true CACHE BOOL "driver_otfad component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_otfad.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)

endif()