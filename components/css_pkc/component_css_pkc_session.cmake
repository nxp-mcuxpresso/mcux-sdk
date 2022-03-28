#Description: Component css_pkc_session; user_visible: False
include_guard(GLOBAL)
message("component_css_pkc_session component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClSession/src/mcuxClSession.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClSession/inc
)


include(component_css_pkc_memory)
