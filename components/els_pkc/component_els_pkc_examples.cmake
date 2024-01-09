#Description: Component els_pkc_test; user_visible: False
include_guard(GLOBAL)
message("component_els_pkc_examples component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClAeadModes/mcuxClAeadModes_Multipart_Els_Ccm_Example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClAeadModes/mcuxClAeadModes_Oneshot_Els_Ccm_Example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClAeadModes/mcuxClAeadModes_Oneshot_Els_Gcm_Example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClCipherModes/mcuxClCipherModes_Multipart_Cbc_Els_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClCipherModes/mcuxClCipherModes_Multipart_Ctr_Els_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClCipherModes/mcuxClCipherModes_Multipart_Ecb_Els_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClCipherModes/mcuxClCipherModes_Multipart_Ecb_PaddingPKCS7_Els_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClCipherModes/mcuxClCipherModes_Oneshot_Cbc_Els_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClCipherModes/mcuxClCipherModes_Oneshot_Cbc_ZeroPadding_Els_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClCipherModes/mcuxClCipherModes_Oneshot_Ctr_Els_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClCipherModes/mcuxClCipherModes_Oneshot_Ecb_Els_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClCipherModes/mcuxClCipherModes_Oneshot_Ecb_PaddingPKCS7_Els_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClCipherModes/mcuxClCipherModes_Oneshot_Ecb_ZeroPadding_Els_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEcc/mcuxClEcc_EdDSA_Ed25519_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEcc/mcuxClEcc_EdDSA_GenerateSignature_Ed25519_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEcc/mcuxClEcc_EdDSA_VerifySignature_Ed25519_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEcc/mcuxClEcc_Mont_Curve25519_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEcc/mcuxClEcc_Mont_Curve448_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEcc/mcuxClEcc_WeierECC_CustomEccWeierType_BN256_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEcc/mcuxClEcc_EdDSA_Ed25519ctx_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEcc/mcuxClEcc_EdDSA_Ed25519ph_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEls/mcuxClEls_Cipher_Aes128_Cbc_Encrypt_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEls/mcuxClEls_Cipher_Aes128_Ecb_Encrypt_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEls/mcuxClEls_Common_Get_Info_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEls/mcuxClEls_Ecc_Keygen_Sign_Verify_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEls/mcuxClEls_Hash_Sha224_One_Block_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEls/mcuxClEls_Hash_Sha256_One_Block_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEls/mcuxClEls_Hash_Sha384_One_Block_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEls/mcuxClEls_Hash_Sha512_One_Block_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEls/mcuxClEls_Rng_Prng_Get_Random_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEls/mcuxClEls_Tls_Master_Key_Session_Keys_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClHashModes/mcuxClHashModes_sha224_oneshot_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClHashModes/mcuxClHashModes_sha256_longMsgOneshot_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClHashModes/mcuxClHashModes_sha256_oneshot_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClHashModes/mcuxClHashModes_sha256_streaming_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClHashModes/mcuxClHashModes_sha384_oneshot_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClHashModes/mcuxClHashModes_sha512_oneshot_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClHmac/mcuxClHmac_Els_Oneshot_External_Key_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClHmac/mcuxClHmac_Sw_Oneshot_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClKey/mcuxClKey_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClMacModes/mcuxClMacModes_cbc_mac_multipart_zero_padding_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClMacModes/mcuxClMacModes_cbc_mac_oneshot_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClMacModes/mcuxClMacModes_cmac_oneshot_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClRandomModes/mcuxClRandomModes_CtrDrbg_AES256_DRG3_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClRandomModes/mcuxClRandomModes_CtrDrbg_AES256_DRG4_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClRandomModes/mcuxClRandomModes_CtrDrbg_AES256_ELS_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClRandomModes/mcuxClRandomModes_Different_Sessions_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClRandomModes/mcuxClRandomModes_PatchMode_CtrDrbg_AES256_DRG3_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClRandomModes/mcuxClRandomModes_TestMode_CtrDrbg_AES256_DRG4_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClRandomModes/mcuxClRandomModes_ELS_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClRsa/mcuxClRsa_sign_NoEncode_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClRsa/mcuxClRsa_sign_pss_sha2_256_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClRsa/mcuxClRsa_verify_NoVerify_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClRsa/mcuxClRsa_verify_pssverify_sha2_256_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxCsslFlowProtection/mcuxCsslFlowProtection_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxCsslMemory/data_invariant_memory_compare.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxCsslMemory/data_invariant_memory_copy.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxCsslMemory/mcuxCsslMemory_Clear_example.c
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxCsslMemory/mcuxCsslMemory_Set_example.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxCsslFlowProtection/inc
    ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxCsslMemory/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClExample/inc
)


include(component_els_pkc)
