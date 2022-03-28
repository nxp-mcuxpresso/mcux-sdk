#Description: Component css_pkc_param_integrity; user_visible: False
include_guard(GLOBAL)
message("component_css_pkc_param_integrity component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxCsslParamIntegrity/src/mcuxCsslParamIntegrity.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxCsslParamIntegrity/inc
)


include(component_css_pkc_flow_protection)
include(component_css_pkc_secure_counter)
include(component_css_pkc_pre_processor)
