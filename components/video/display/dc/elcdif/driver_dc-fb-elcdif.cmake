if(NOT DRIVER_DC-FB-ELCDIF_INCLUDED)

    set(DRIVER_DC-FB-ELCDIF_INCLUDED true CACHE BOOL "driver_dc-fb-elcdif component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_dc_fb_elcdif.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_dc-fb-common)
    include(driver_elcdif)

endif()