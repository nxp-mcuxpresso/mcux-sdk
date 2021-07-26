#Description: Component ak4497_adapter; user_visible: True
include_guard(GLOBAL)
message("component_ak4497_adapter component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/port/ak4497/fsl_codec_ak4497_adapter.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/port
    ${CMAKE_CURRENT_LIST_DIR}/port/ak4497
)


include(driver_ak4497)
