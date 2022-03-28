#Description: Component css_pkc_flow_protection; user_visible: True
include_guard(GLOBAL)
message("component_css_pkc_flow_protection component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxCsslFlowProtection/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxCsslFlowProtection/inc/internal
)


