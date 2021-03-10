if(NOT DEVICE_SYSTEM_LPC54114_CM4_INCLUDED)

    set(DEVICE_SYSTEM_LPC54114_CM4_INCLUDED true CACHE BOOL "device_system component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/system_LPC54114_cm4.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(device_CMSIS_LPC54114_cm4)

endif()