#Description: Component els_pkc.cipher_modes; user_visible: False
include_guard(GLOBAL)
message("component_els_pkc_cipher_modes component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClCipherModes/src/mcuxClCipherModes_Els_Aes.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClCipherModes/src/mcuxClCipherModes_Els_EngineAes.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClCipherModes/src/mcuxClCipherModes_Helper.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClCipherModes/src/mcuxClCipherModes_Modes.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClCipherModes/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClCipherModes/inc/internal
)


include(component_els_pkc_cipher)
