if(NOT DEVICE_STARTUP_LPC55S69_CM33_CORE0_INCLUDED)

    set(DEVICE_STARTUP_LPC55S69_CM33_CORE0_INCLUDED true CACHE BOOL "device_startup component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/gcc/startup_LPC55S69_cm33_core0.S
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    )


    include(device_system_LPC55S69_cm33_core0)

endif()