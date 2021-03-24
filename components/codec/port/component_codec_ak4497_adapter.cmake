if(NOT COMPONENT_CODEC_AK4497_ADAPTER_INCLUDED)

    set(COMPONENT_CODEC_AK4497_ADAPTER_INCLUDED true CACHE BOOL "component_codec_ak4497_adapter component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_ak4497_adapter.c
        ${CMAKE_CURRENT_LIST_DIR}/fsl_codec_adapter.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_ak4497)
    include(driver_codec_MIMX8MM6)

endif()