#Description: Component els_pkc.flow_protection; user_visible: False
include_guard(GLOBAL)
message("component_els_pkc_flow_protection component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxCsslFlowProtection/inc
)


include(component_els_pkc_core)
