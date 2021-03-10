if(NOT DEVICE_CMSIS_INCLUDED)

    set(DEVICE_CMSIS_INCLUDED true CACHE BOOL "device_CMSIS component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(${MCUX_DEVICE} STREQUAL "LPC55S69_cm33_core0")
        include(CMSIS_Include_core_cm33)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC55S69_cm33_core1")
        include(CMSIS_Include_core_cm33)
    endif()


endif()