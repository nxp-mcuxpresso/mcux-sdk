if(NOT DRIVER_ESAI_INCLUDED)

    set(DRIVER_ESAI_INCLUDED true CACHE BOOL "driver_esai component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_esai.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )



endif()