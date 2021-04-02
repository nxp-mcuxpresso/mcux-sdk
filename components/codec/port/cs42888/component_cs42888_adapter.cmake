if(NOT COMPONENT_CS42888_ADAPTER_INCLUDED)

    set(COMPONENT_CS42888_ADAPTER_INCLUDED true CACHE BOOL "component_cs42888_adapter component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_codec_adapter.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_cs42888)

endif()