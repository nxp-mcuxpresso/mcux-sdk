if(NOT COMPONENT_OSA_BM_INCLUDED)

    set(COMPONENT_OSA_BM_INCLUDED true CACHE BOOL "component_osa_bm component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1052")
        include(component_lists)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1064")
        include(component_lists)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MK66F18")
        include(component_lists)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1021")
        include(component_lists)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1062")
        include(component_lists)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1024")
        include(component_lists)
    endif()

    include(driver_common)

endif()