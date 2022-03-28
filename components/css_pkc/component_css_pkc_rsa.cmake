#Description: Component css_pkc_rsa; user_visible: True
include_guard(GLOBAL)
message("component_css_pkc_rsa component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_Mgf1.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_NoEncode.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_NoVerify.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_Pkcs1v15Encode.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_Pkcs1v15Verify.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_PrivateCrt.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_PrivatePlain.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_PssEncode.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_PssVerify.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_Public.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_Sign.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_Verify.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/inc
)


include(component_css_pkc_memory)
include(component_pkc)
