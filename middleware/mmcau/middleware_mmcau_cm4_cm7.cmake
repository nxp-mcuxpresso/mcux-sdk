if(NOT MIDDLEWARE_MMCAU_CM4_CM7_INCLUDED)

    set(MIDDLEWARE_MMCAU_CM4_CM7_INCLUDED true CACHE BOOL "middleware_mmcau_cm4_cm7 component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_clock)
    include(driver_common)
    include(middleware_mmcau_common_files)

endif()