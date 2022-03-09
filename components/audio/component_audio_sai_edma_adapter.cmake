#Description: Component sai_edma_adapter; user_visible: True
include_guard(GLOBAL)
message("component_audio_sai_edma_adapter component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_adapter_sai.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_common)
include(driver_sai_edma)
