#Description: Component aes; user_visible: False
include_guard(GLOBAL)
message("component_els_pkc_aes component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClAes/src/mcuxClAes_KeyTypes.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClAes/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClAes/inc/internal
)


include(component_els_pkc_key)
