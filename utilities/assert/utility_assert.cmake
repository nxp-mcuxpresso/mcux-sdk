if(NOT UTILITY_ASSERT_INCLUDED)

    set(UTILITY_ASSERT_INCLUDED true CACHE BOOL "utility_assert component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_assert.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    )

    #OR Logic component
    if(${MCUX_DEVICE} STREQUAL "MIMX8MM6")
        include(utility_debug_console)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1064")
        include(utility_debug_console)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1011")
        include(utility_debug_console)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MK28FA15")
        include(utility_debug_console)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1021")
        include(utility_debug_console)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1015")
        include(utility_debug_console)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1024")
        include(utility_debug_console)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1052")
        include(utility_debug_console)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1062")
        include(utility_debug_console)
    endif()


endif()