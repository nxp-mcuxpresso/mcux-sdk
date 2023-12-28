#Description: Component els_pkc.session; user_visible: False
include_guard(GLOBAL)
message("component_els_pkc_session component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClSession/src/mcuxClSession.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClSession/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClSession/inc/internal
)


include(component_els_pkc_random)
