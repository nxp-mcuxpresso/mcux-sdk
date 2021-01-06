if(NOT DRIVER_QTMR_1_INCLUDED)

    set(DRIVER_QTMR_1_INCLUDED true CACHE BOOL "driver_qtmr_1 component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_qtmr.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)

endif()