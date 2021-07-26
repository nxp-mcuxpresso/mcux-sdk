#Description: Component da7212_adapter; user_visible: True
include_guard(GLOBAL)
message("component_da7212_adapter component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/port/da7212/fsl_codec_da7212_adapter.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/port
    ${CMAKE_CURRENT_LIST_DIR}/port/da7212
)


include(driver_dialog7212)
