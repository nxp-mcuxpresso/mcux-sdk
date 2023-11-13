if(NOT DEVICE_CMSIS_INCLUDED)

    set(DEVICE_CMSIS_LPC54114_CM4_INCLUDED true CACHE BOOL "device_CMSIS component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    include(CMSIS_Include_core_cm OPTIONAL)


endif()