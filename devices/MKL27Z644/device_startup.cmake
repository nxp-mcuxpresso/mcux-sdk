if(NOT DEVICE_STARTUP_INCLUDED)

    set(DEVICE_STARTUP_INCLUDED true CACHE BOOL "device_startup component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/gcc/startup_MKL27Z644.S
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    )


    include(device_system)

endif()