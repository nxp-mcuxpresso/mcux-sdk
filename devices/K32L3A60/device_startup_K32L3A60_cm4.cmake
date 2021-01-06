if(NOT DEVICE_STARTUP_K32L3A60_CM4_INCLUDED)

    set(DEVICE_STARTUP_K32L3A60_CM4_INCLUDED true CACHE BOOL "device_startup component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/gcc/startup_K32L3A60_cm4.S
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    )


    include(device_system_K32L3A60_cm4)

endif()