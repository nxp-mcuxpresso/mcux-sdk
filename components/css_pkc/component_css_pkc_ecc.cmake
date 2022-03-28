#Description: Component css_pkc_ecc; user_visible: True
include_guard(GLOBAL)
message("component_css_pkc_ecc component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Constants.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_FUP.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal_FUP.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal_GenerateMultiplicativeBlinding.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal_KeyGen.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal_KeyGen_FUP.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal_NIST.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal_PointArithmetic.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal_PointCheck.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal_PointCheck_FUP.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal_PointMult.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal_SecurePointMult_CoZMontLadder.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal_SecurePointMult_CoZMontLadder_FUP.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal_SecureScalarMult_XZMontLadder.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal_SecureScalarMult_XZMontLadder_FUP.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal_SetupEnvironment.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal_SetupEnvironment_FUP.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_KeyGen.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_KeyGen_FUP.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Mont_DhKeyAgreement.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Mont_DhKeyGeneration.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Mont_Internal.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Mont_MontDhX.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Mont_MontDhX_FUP.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_NIST_FUP.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_PointMult.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_PointMult_FUP.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Sign.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Sign_FUP.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Verify.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Verify_FUP.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Verify_P384.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Verify_P384_FUP.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/size/size.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/inc/internal
)


include(component_css_pkc_key)
include(component_pkc)
