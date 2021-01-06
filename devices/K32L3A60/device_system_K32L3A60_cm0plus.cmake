if(NOT DEVICE_SYSTEM_K32L3A60_CM0PLUS_INCLUDED)

    set(DEVICE_SYSTEM_K32L3A60_CM0PLUS_INCLUDED true CACHE BOOL "device_system component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/system_K32L3A60_cm0plus.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(device_CMSIS_K32L3A60_cm0plus)

endif()