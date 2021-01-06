if(NOT UTILITY_INCBIN_INCLUDED)

    set(UTILITY_INCBIN_INCLUDED true CACHE BOOL "utility_incbin component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_incbin.S
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    )



endif()