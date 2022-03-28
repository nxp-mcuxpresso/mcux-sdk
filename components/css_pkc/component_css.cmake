#Description: Component css; user_visible: True
include_guard(GLOBAL)
message("component_css component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClCss/src/mcuxClCss_Aead.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClCss/src/mcuxClCss_Cipher.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClCss/src/mcuxClCss_Cmac.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClCss/src/mcuxClCss_Common.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClCss/src/mcuxClCss_Ecc.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClCss/src/mcuxClCss_Hash.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClCss/src/mcuxClCss_Hmac.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClCss/src/mcuxClCss_Kdf.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClCss/src/mcuxClCss_KeyManagement.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClCss/src/mcuxClCss_Rng.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClCss/inc
)


include(component_css_hash)
