if(NOT MIDDLEWARE_BAREMETAL_INCLUDED)

    set(MIDDLEWARE_BAREMETAL_INCLUDED true CACHE BOOL "middleware_baremetal component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    )



endif()