if(NOT DRIVER_PMC0_INCLUDED)

    set(DRIVER_PMC0_INCLUDED true CACHE BOOL "driver_pmc0 component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)

endif()