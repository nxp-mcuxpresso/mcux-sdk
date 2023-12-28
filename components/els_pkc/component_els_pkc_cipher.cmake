#Description: Component els_pkc.cipher; user_visible: False
include_guard(GLOBAL)
message("component_els_pkc_cipher component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClCipher/src/mcuxClCipher.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClCipher/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClCipher/inc/internal
)


include(component_els_pkc_els)
