#-------------------------------------------------------------------------------
# Copyright (c) 2023 NXP.
# SPDX-License-Identifier: BSD-3-Clause
#
#-------------------------------------------------------------------------------
#Description: Component els_pkc_test; user_visible: False
include_guard(GLOBAL)
message("component_els_pkc_examples component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClAeadModes/mcuxClAeadModes_Els_Ccm_Aes128_Multipart_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClAeadModes/mcuxClAeadModes_Els_Ccm_Aes128_Oneshot_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClAeadModes/mcuxClAeadModes_Els_Gcm_Aes128_Oneshot_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClCipherModes/mcuxClCipherModes_Els_Cbc_Aes128_Multipart_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClCipherModes/mcuxClCipherModes_Els_Cbc_Aes128_Oneshot_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClCipherModes/mcuxClCipherModes_Els_Cbc_Aes128_Oneshot_PaddingZero_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClCipherModes/mcuxClCipherModes_Els_Ctr_Aes128_Multipart_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClCipherModes/mcuxClCipherModes_Els_Ctr_Aes128_Oneshot_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClCipherModes/mcuxClCipherModes_Els_Ecb_Aes128_Multipart_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClCipherModes/mcuxClCipherModes_Els_Ecb_Aes128_Multipart_PaddingPKCS7_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClCipherModes/mcuxClCipherModes_Els_Ecb_Aes128_Oneshot_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClCipherModes/mcuxClCipherModes_Els_Ecb_Aes128_Oneshot_PaddingPKCS7_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClCipherModes/mcuxClCipherModes_Els_Ecb_Aes128_Oneshot_PaddingZero_example.c
	
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClEcc/mcuxClEcc_EdDSA_Ed25519ctx_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClEcc/mcuxClEcc_EdDSA_Ed25519ph_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClEcc/mcuxClEcc_EdDSA_Ed25519_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClEcc/mcuxClEcc_EdDSA_GenerateSignature_Ed25519_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClEcc/mcuxClEcc_EdDSA_VerifySignature_Ed25519_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClEcc/mcuxClEcc_MontDH_Curve25519_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClEcc/mcuxClEcc_MontDH_Curve448_example.c
	
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClEls/mcuxClEls_Cipher_Aes128_Cbc_Encrypt_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClEls/mcuxClEls_Cipher_Aes128_Ecb_Encrypt_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClEls/mcuxClEls_Common_Get_Info_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClEls/mcuxClEls_Ecc_Keygen_Sign_Verify_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClEls/mcuxClEls_Hash_HW_Security_Counter_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClEls/mcuxClEls_Hash_Sha224_One_Block_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClEls/mcuxClEls_Hash_Sha256_One_Block_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClEls/mcuxClEls_Hash_Sha384_One_Block_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClEls/mcuxClEls_Hash_Sha512_One_Block_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClEls/mcuxClEls_Rng_Prng_Get_Random_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClEls/mcuxClEls_Tls_Master_Key_Session_Keys_example.c
	
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClHashModes/mcuxClHashModes_sha1_longMsgOneshot_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClHashModes/mcuxClHashModes_sha1_oneshot_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClHashModes/mcuxClHashModes_sha1_streaming_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClHashModes/mcuxClHashModes_sha224_oneshot_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClHashModes/mcuxClHashModes_sha256_longMsgOneshot_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClHashModes/mcuxClHashModes_sha256_oneshot_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClHashModes/mcuxClHashModes_sha256_streaming_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClHashModes/mcuxClHashModes_sha384_oneshot_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClHashModes/mcuxClHashModes_sha512_224_oneshot_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClHashModes/mcuxClHashModes_sha512_256_oneshot_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClHashModes/mcuxClHashModes_sha512_256_streaming_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClHashModes/mcuxClHashModes_sha512_oneshot_example.c
	

    ${CMAKE_CURRENT_LIST_DIR}/mcuxClHmac/mcuxClHmac_Els_Oneshot_External_Key_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClHmac/mcuxClHmac_Sw_Multipart_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClHmac/mcuxClHmac_Sw_Oneshot_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClKey/mcuxClKey_example.c
	
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClMacModes/mcuxClMacModes_Els_Cbcmac_Aes128_Oneshot_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClMacModes/mcuxClMacModes_Els_Cbcmac_Aes256_Multipart_PaddingZero_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClMacModes/mcuxClMacModes_Els_Cmac_Aes128_Oneshot_example.c
	
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClRandom/mcuxClRandom_PRNG_Patch_example.c

    ${CMAKE_CURRENT_LIST_DIR}/mcuxClRandomModes/mcuxClRandomModes_CtrDrbg_AES256_DRG3_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClRandomModes/mcuxClRandomModes_CtrDrbg_AES256_DRG4_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClRandomModes/mcuxClRandomModes_CtrDrbg_AES256_ELS_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClRandomModes/mcuxClRandomModes_Different_Sessions_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClRandomModes/mcuxClRandomModes_ELS_example.c
	

    ${CMAKE_CURRENT_LIST_DIR}/mcuxClRsa/mcuxClRsa_sign_NoEncode_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClRsa/mcuxClRsa_sign_pss_sha2_256_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClRsa/mcuxClRsa_verify_NoVerify_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxClRsa/mcuxClRsa_verify_pssverify_sha2_256_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxCsslFlowProtection/inc
    ${CMAKE_CURRENT_LIST_DIR}/mcuxCsslFlowProtection/mcuxCsslFlowProtection_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxCsslFlowProtection/inc/mcuxCsslExamples.h
    ${CMAKE_CURRENT_LIST_DIR}/mcuxCsslMemory/inc
    ${CMAKE_CURRENT_LIST_DIR}/mcuxCsslMemory/mcuxCsslMemory_Clear_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxCsslMemory/mcuxCsslMemory_Compare_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxCsslMemory/mcuxCsslMemory_Copy_example.c
    ${CMAKE_CURRENT_LIST_DIR}/mcuxCsslMemory/mcuxCsslMemory_Set_example.c
)

target_compile_options(${MCUX_SDK_PROJECT_NAME}
    PRIVATE
        $<$<C_COMPILER_ID:GNU>:-Wno-unused-variable>
        $<$<C_COMPILER_ID:ARMClang>:-Wno-unused-variable>
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/mcuxCsslFlowProtection/inc
    ${CMAKE_CURRENT_LIST_DIR}/mcuxCsslMemory/inc
    ${CMAKE_CURRENT_LIST_DIR}/../src/comps/mcuxClExample/inc
	"$<TARGET_PROPERTY:McuxElsPkc,INTERFACE_INCLUDE_DIRECTORIES>"
)

target_link_libraries(${MCUX_SDK_PROJECT_NAME}
    PUBLIC
        McuxElsPkc
)

