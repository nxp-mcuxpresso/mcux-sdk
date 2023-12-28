#Description: Component els_header_only; user_visible: False
include_guard(GLOBAL)
message("component_els_pkc_els_header_only component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEls/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEls/inc/internal
)


