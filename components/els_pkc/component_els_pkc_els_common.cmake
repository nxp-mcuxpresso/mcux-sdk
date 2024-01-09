#Description: Component els_pkc els_common; user_visible: False
include_guard(GLOBAL)
message("component_els_pkc_els_common component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEls/src/mcuxClEls_Common.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEls/inc
)


include(component_els_pkc_core)
