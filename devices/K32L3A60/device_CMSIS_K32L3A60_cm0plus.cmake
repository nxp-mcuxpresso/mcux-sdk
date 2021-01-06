if(NOT DEVICE_CMSIS_K32L3A60_CM0PLUS_INCLUDED)

    set(DEVICE_CMSIS_K32L3A60_CM0PLUS_INCLUDED true CACHE BOOL "device_CMSIS component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(CONFIG_USE_CMSIS_Include_core_cm0plus) 
        include(CMSIS_Include_core_cm0plus)
    endif()


endif()