if(NOT UTILITY_ASSERT_LITE_MIMXRT1011_INCLUDED)

    set(UTILITY_ASSERT_LITE_MIMXRT1011_INCLUDED true CACHE BOOL "utility_assert_lite component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_assert.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    )


    include(utility_debug_console_lite)

endif()