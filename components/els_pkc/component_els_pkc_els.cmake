#Description: Component els; user_visible: False
include_guard(GLOBAL)
message("component_els_pkc_els component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEls/src/mcuxClEls_Aead.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEls/src/mcuxClEls_Cipher.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEls/src/mcuxClEls_Cmac.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEls/src/mcuxClEls_Ecc.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEls/src/mcuxClEls_Hash.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEls/src/mcuxClEls_Hmac.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEls/src/mcuxClEls_Kdf.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEls/src/mcuxClEls_Rng.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(component_els_pkc_cipher_modes)
include(component_els_pkc_mac_modes)
include(component_els_pkc_hash)
include(component_els_pkc_key)
include(component_els_pkc_standalone_gdet)
include(component_els_pkc_hmac)
include(component_els_pkc_standalone_keyManagement)
include(component_els_pkc_aead_modes)
include(component_els_pkc_els_common)
