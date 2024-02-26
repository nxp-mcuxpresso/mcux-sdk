include_guard(GLOBAL)


if (CONFIG_USE_component_els_pkc_core)
# Add set(CONFIG_USE_component_els_pkc_core true) in config.cmake to use this component

message("component_els_pkc_core component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClCore/inc
)


endif()


if (CONFIG_USE_component_els_pkc_data_integrity)
# Add set(CONFIG_USE_component_els_pkc_data_integrity true) in config.cmake to use this component

message("component_els_pkc_data_integrity component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxCsslDataIntegrity/inc
)


endif()


if (CONFIG_USE_component_els_pkc_els_header_only)
# Add set(CONFIG_USE_component_els_pkc_els_header_only true) in config.cmake to use this component

message("component_els_pkc_els_header_only component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEls/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEls/inc/internal
)


endif()


if (CONFIG_USE_component_els_pkc_padding)
# Add set(CONFIG_USE_component_els_pkc_padding true) in config.cmake to use this component

message("component_els_pkc_padding component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPadding/src/mcuxClPadding.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPadding/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPadding/inc/internal
)


endif()


if (CONFIG_USE_component_els_pkc_pre_processor)
# Add set(CONFIG_USE_component_els_pkc_pre_processor true) in config.cmake to use this component

message("component_els_pkc_pre_processor component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxCsslCPreProcessor/inc
)


endif()


if (CONFIG_USE_component_els_pkc_secure_counter)
# Add set(CONFIG_USE_component_els_pkc_secure_counter true) in config.cmake to use this component

message("component_els_pkc_secure_counter component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxCsslSecureCounter/inc
)


endif()


if (CONFIG_USE_component_els_pkc_toolchain)
# Add set(CONFIG_USE_component_els_pkc_toolchain true) in config.cmake to use this component

message("component_els_pkc_toolchain component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/compiler
)


endif()


if (CONFIG_USE_component_els_pkc_doc_mcxn)
# Add set(CONFIG_USE_component_els_pkc_doc_mcxn true) in config.cmake to use this component

message("component_els_pkc_doc_mcxn component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MCXN546 OR CONFIG_DEVICE_ID STREQUAL MCXN547 OR CONFIG_DEVICE_ID STREQUAL MCXN946 OR CONFIG_DEVICE_ID STREQUAL MCXN947))

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)

else()

message(SEND_ERROR "component_els_pkc_doc_mcxn dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_static_lib_mcxn)
# Add set(CONFIG_USE_component_els_pkc_static_lib_mcxn true) in config.cmake to use this component

message("component_els_pkc_static_lib_mcxn component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MCXN546 OR CONFIG_DEVICE_ID STREQUAL MCXN547 OR CONFIG_DEVICE_ID STREQUAL MCXN946 OR CONFIG_DEVICE_ID STREQUAL MCXN947))

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)

else()

message(SEND_ERROR "component_els_pkc_static_lib_mcxn dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_common)
# Add set(CONFIG_USE_component_els_pkc_common true) in config.cmake to use this component

message("component_els_pkc_common component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_memory)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/common/src/mcuxClOscca_CommonOperations.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/common/inc
)

else()

message(SEND_ERROR "component_els_pkc_common dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_aead)
# Add set(CONFIG_USE_component_els_pkc_aead true) in config.cmake to use this component

message("component_els_pkc_aead component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_els)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClAead/src/mcuxClAead.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClAead/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClAead/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_aead dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_aead_modes)
# Add set(CONFIG_USE_component_els_pkc_aead_modes true) in config.cmake to use this component

message("component_els_pkc_aead_modes component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_aead)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClAeadModes/src/mcuxClAeadModes_Els_AesCcm.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClAeadModes/src/mcuxClAeadModes_Els_AesGcm.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClAeadModes/src/mcuxClAeadModes_Els_CcmEngineAes.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClAeadModes/src/mcuxClAeadModes_Els_Modes.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClAeadModes/src/mcuxClAeadModes_Els_GcmEngineAes.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClAeadModes/src/mcuxClAeadModes_Els_Multipart.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClAeadModes/src/mcuxClAeadModes_Els_Oneshot.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClAeadModes/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClAeadModes/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_aead_modes dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_aes)
# Add set(CONFIG_USE_component_els_pkc_aes true) in config.cmake to use this component

message("component_els_pkc_aes component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_key)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClAes/src/mcuxClAes_KeyTypes.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClAes/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClAes/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_aes dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_cipher)
# Add set(CONFIG_USE_component_els_pkc_cipher true) in config.cmake to use this component

message("component_els_pkc_cipher component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_els)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClCipher/src/mcuxClCipher.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClCipher/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClCipher/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_cipher dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_cipher_modes)
# Add set(CONFIG_USE_component_els_pkc_cipher_modes true) in config.cmake to use this component

message("component_els_pkc_cipher_modes component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_cipher)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClCipherModes/src/mcuxClCipherModes_Els_Aes.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClCipherModes/src/mcuxClCipherModes_Els_EngineAes.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClCipherModes/src/mcuxClCipherModes_Helper.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClCipherModes/src/mcuxClCipherModes_Modes.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClCipherModes/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClCipherModes/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_cipher_modes dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_ecc)
# Add set(CONFIG_USE_component_els_pkc_ecc true) in config.cmake to use this component

message("component_els_pkc_ecc component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_pkc AND CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_secure_counter AND CONFIG_USE_component_els_pkc_pre_processor AND CONFIG_USE_component_els_pkc_key AND CONFIG_USE_component_els_pkc_els)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Constants.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_GenerateKeyPair.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_GenerateKeyPair_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_GenerateSignature.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_GenerateSignature_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_GenerateSignatureMode.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_InitPrivKeyInputMode.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_Internal_CalcHashModN.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_Internal_CalcHashModN_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_Internal_DecodePoint_Ed25519.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_Internal_DecodePoint_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_Internal_SetupEnvironment.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_Internal_SignatureMechanisms.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_VerifySignature.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Internal_BlindedScalarMult.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Internal_Convert_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Internal_GenerateMultiplicativeBlinding.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Internal_Interleave_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Internal_InterleaveScalar.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Internal_InterleaveTwoScalars.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Internal_PointComparison_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Internal_RecodeAndReorderScalar.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Internal_SetupEnvironment.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Internal_SetupEnvironment_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Internal_Types.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_KeyTypes.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Mont_DhKeyAgreement.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Mont_DhKeyGeneration.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Mont_Internal_DhSetupEnvironment.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Mont_Internal_MontDhX.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Mont_Internal_MontDhX_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Mont_Internal_SecureScalarMult_XZMontLadder.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Mont_Internal_SecureScalarMult_XZMontLadder_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_SignatureMechanisms.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_TwEd_Internal_FixScalarMult.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_TwEd_Internal_PlainFixScalarMult25519.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_TwEd_Internal_PlainPtrSelectComb.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_TwEd_Internal_PlainPtrSelectML.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_TwEd_Internal_PlainVarScalarMult.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_TwEd_Internal_PointArithmeticEd25519.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_TwEd_Internal_PointArithmeticEd25519_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_TwEd_Internal_PointSubtraction_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_TwEd_Internal_PointValidation_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_TwEd_Internal_PrecPointImportAndValidate.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_TwEd_Internal_VarScalarMult.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_TwEd_Internal_VarScalarMult_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Internal_ConvertPoint_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Internal_KeyGen.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Internal_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Internal_KeyGen_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Internal_PointArithmetic.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Internal_PointArithmetic_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Internal_PointCheck.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Internal_PointCheck_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Internal_PointMult.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Internal_SecurePointMult_CoZMontLadder.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Internal_SecurePointMult_CoZMontLadder_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Internal_SetupEnvironment.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Weier_KeyGen.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Weier_KeyGen_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Weier_PointMult.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Weier_PointMult_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Sign.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Sign_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Verify.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Verify_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_WeierECC_Internal_GenerateCustomKeyType.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_WeierECC_Internal_GenerateDomainParams.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_WeierECC_Internal_GenerateDomainParams_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_WeierECC_Internal_SetupEnvironment.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_Internal_DecodePoint_Ed448.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_ecc dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_els_common)
# Add set(CONFIG_USE_component_els_pkc_els_common true) in config.cmake to use this component

message("component_els_pkc_els_common component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_core)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEls/src/mcuxClEls_Common.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEls/inc
)

else()

message(SEND_ERROR "component_els_pkc_els_common dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_standalone_keyManagement)
# Add set(CONFIG_USE_component_els_pkc_standalone_keyManagement true) in config.cmake to use this component

message("component_els_pkc_standalone_keyManagement component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_memory)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEls/src/mcuxClEls_KeyManagement.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEls/inc
)

else()

message(SEND_ERROR "component_els_pkc_standalone_keyManagement dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_standalone_gdet)
# Add set(CONFIG_USE_component_els_pkc_standalone_gdet true) in config.cmake to use this component

message("component_els_pkc_standalone_gdet component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_els_header_only AND CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_secure_counter AND CONFIG_USE_component_els_pkc_pre_processor)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEls/src/mcuxClEls_GlitchDetector.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEls/inc
)

else()

message(SEND_ERROR "component_els_pkc_standalone_gdet dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_els)
# Add set(CONFIG_USE_component_els_pkc_els true) in config.cmake to use this component

message("component_els_pkc_els component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_els_header_only AND CONFIG_USE_component_els_pkc_els_common AND CONFIG_USE_component_els_pkc_standalone_keyManagement AND CONFIG_USE_component_els_pkc_hash AND CONFIG_USE_component_els_pkc_core AND CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_key AND CONFIG_USE_component_els_pkc_mac_modes AND CONFIG_USE_component_els_pkc_aead_modes AND CONFIG_USE_component_els_pkc_data_integrity AND CONFIG_USE_component_els_pkc_cipher_modes)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEls/src/mcuxClEls_Aead.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEls/src/mcuxClEls_Cipher.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEls/src/mcuxClEls_Cmac.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEls/src/mcuxClEls_Ecc.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEls/src/mcuxClEls_Hash.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEls/src/mcuxClEls_Hmac.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEls/src/mcuxClEls_Kdf.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEls/src/mcuxClEls_Rng.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)

else()

message(SEND_ERROR "component_els_pkc_els dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_hash)
# Add set(CONFIG_USE_component_els_pkc_hash true) in config.cmake to use this component

message("component_els_pkc_hash component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_els AND CONFIG_USE_component_els_pkc_hashmodes)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClHash/src/mcuxClHash_api_multipart_common.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClHash/src/mcuxClHash_api_multipart_compute.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClHash/src/mcuxClHash_api_oneshot_compute.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClHash/inc
)

else()

message(SEND_ERROR "component_els_pkc_hash dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_hashmodes)
# Add set(CONFIG_USE_component_els_pkc_hashmodes true) in config.cmake to use this component

message("component_els_pkc_hashmodes component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_els)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClHashModes/src/mcuxClHashModes_Core_els_sha2.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClHashModes/src/mcuxClHashModes_Internal_els_sha2.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClHashModes/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClHashModes/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_hashmodes dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_key)
# Add set(CONFIG_USE_component_els_pkc_key true) in config.cmake to use this component

message("component_els_pkc_key component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_els AND CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_secure_counter AND CONFIG_USE_component_els_pkc_pre_processor AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_ecc)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClKey/src/mcuxClKey.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClKey/src/mcuxClKey_Protection.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClKey/inc
)

else()

message(SEND_ERROR "component_els_pkc_key dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_mac)
# Add set(CONFIG_USE_component_els_pkc_mac true) in config.cmake to use this component

message("component_els_pkc_mac component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_key AND CONFIG_USE_component_els_pkc_toolchain AND CONFIG_USE_component_els_pkc_padding AND CONFIG_USE_component_els_pkc_hmac)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMac/src/mcuxClMac.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMac/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMac/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_mac dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_hmac)
# Add set(CONFIG_USE_component_els_pkc_hmac true) in config.cmake to use this component

message("component_els_pkc_hmac component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_key AND CONFIG_USE_component_els_pkc_toolchain AND CONFIG_USE_component_els_pkc_padding)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClHmac/src/size/size.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClHmac/src/mcuxClHmac_Els.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClHmac/src/mcuxClHmac_Functions.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClHmac/src/mcuxClHmac_Helper.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClHmac/src/mcuxClHmac_KeyTypes.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClHmac/src/mcuxClHmac_Modes.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClHmac/src/mcuxClHmac_Sw.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClHmac/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClHmac/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_hmac dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_mac_modes)
# Add set(CONFIG_USE_component_els_pkc_mac_modes true) in config.cmake to use this component

message("component_els_pkc_mac_modes component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_mac)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMacModes/src/mcuxClMacModes.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMacModes/src/mcuxClMacModes_Els_Cbcmac.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMacModes/src/mcuxClMacModes_Els_Cmac.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMacModes/src/mcuxClMacModes_Els_Functions.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMacModes/src/mcuxClMacModes_Modes.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMacModes/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMacModes/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_mac_modes dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_math)
# Add set(CONFIG_USE_component_els_pkc_math true) in config.cmake to use this component

message("component_els_pkc_math component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_secure_counter AND CONFIG_USE_component_els_pkc_pre_processor AND CONFIG_USE_component_els_pkc_pkc)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMath/src/mcuxClMath_ExactDivide.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMath/src/mcuxClMath_ExactDivideOdd.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMath/src/mcuxClMath_ExactDivideOdd_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMath/src/mcuxClMath_ModExp_SqrMultL2R.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMath/src/mcuxClMath_ModInv.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMath/src/mcuxClMath_ModInv_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMath/src/mcuxClMath_NDash.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMath/src/mcuxClMath_NDash_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMath/src/mcuxClMath_QDash.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMath/src/mcuxClMath_QDash_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMath/src/mcuxClMath_ReduceModEven.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMath/src/mcuxClMath_SecModExp.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMath/src/mcuxClMath_SecModExp_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMath/src/mcuxClMath_Utils.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMath/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMath/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_math dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_memory)
# Add set(CONFIG_USE_component_els_pkc_memory true) in config.cmake to use this component

message("component_els_pkc_memory component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_param_integrity AND CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_secure_counter AND CONFIG_USE_component_els_pkc_pre_processor AND CONFIG_USE_component_els_pkc_toolchain)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMemory/src/mcuxClMemory.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxCsslMemory/src/mcuxCsslMemory_Clear.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxCsslMemory/src/mcuxCsslMemory_Compare.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxCsslMemory/src/mcuxCsslMemory_Copy.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxCsslMemory/src/mcuxCsslMemory_Internal_SecureCompare_Stub.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxCsslMemory/src/mcuxCsslMemory_Set.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMemory/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxCsslMemory/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxCsslMemory/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_memory dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_oscca_pkc)
# Add set(CONFIG_USE_component_els_pkc_oscca_pkc true) in config.cmake to use this component

message("component_els_pkc_oscca_pkc component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaPkc/src/mcuxClOsccaPkc.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaPkc/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaPkc/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_oscca_pkc dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_oscca_sm3)
# Add set(CONFIG_USE_component_els_pkc_oscca_sm3 true) in config.cmake to use this component

message("component_els_pkc_oscca_sm3 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm3/src/mcuxClOsccaSm3_core_sm3.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm3/src/mcuxClOsccaSm3_internal_sm3.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm3/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm3/inc/internal
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  if(CONFIG_TOOLCHAIN STREQUAL iar)
    target_compile_options(${MCUX_SDK_PROJECT_NAME} PUBLIC
      --diag_suppress Pe177
    )
  endif()
  if(CONFIG_TOOLCHAIN STREQUAL armgcc)
    target_compile_options(${MCUX_SDK_PROJECT_NAME} PUBLIC
      -Wno-unused-function
    )
  endif()

endif()

else()

message(SEND_ERROR "component_els_pkc_oscca_sm3 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_pkc)
# Add set(CONFIG_USE_component_els_pkc_pkc true) in config.cmake to use this component

message("component_els_pkc_pkc component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_ecc AND CONFIG_USE_component_els_pkc_math AND CONFIG_USE_component_els_pkc_rsa)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPkc/src/mcuxClPkc_Calculate.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPkc/src/mcuxClPkc_ImportExport.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPkc/src/mcuxClPkc_Initialize.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPkc/src/mcuxClPkc_UPTRT.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPkc/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPkc/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_pkc dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_prng)
# Add set(CONFIG_USE_component_els_pkc_prng true) in config.cmake to use this component

message("component_els_pkc_prng component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_ecc AND CONFIG_USE_component_els_pkc_math AND CONFIG_USE_component_els_pkc_rsa)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPrng/src/mcuxClPrng_ELS.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPrng/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPrng/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_prng dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_random)
# Add set(CONFIG_USE_component_els_pkc_random true) in config.cmake to use this component

message("component_els_pkc_random component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_secure_counter AND CONFIG_USE_component_els_pkc_pre_processor AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_random_modes AND CONFIG_USE_component_els_pkc_prng)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRandom/src/mcuxClRandom_DRBG.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRandom/src/mcuxClRandom_PRNG.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRandom/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRandom/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_random dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_random_modes)
# Add set(CONFIG_USE_component_els_pkc_random_modes true) in config.cmake to use this component

message("component_els_pkc_random_modes component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_secure_counter AND CONFIG_USE_component_els_pkc_pre_processor AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_aes AND CONFIG_USE_component_els_pkc_trng)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRandomModes/src/mcuxClRandomModes_CtrDrbg_Els.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRandomModes/src/mcuxClRandomModes_ElsMode.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRandomModes/src/mcuxClRandomModes_PatchMode.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRandomModes/src/mcuxClRandomModes_TestMode.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRandomModes/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRandomModes/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_random_modes dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_random_modes_ctr)
# Add set(CONFIG_USE_component_els_pkc_random_modes_ctr true) in config.cmake to use this component

message("component_els_pkc_random_modes_ctr component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_secure_counter AND CONFIG_USE_component_els_pkc_pre_processor AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_aes AND CONFIG_USE_component_els_pkc_trng)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRandomModes/src/mcuxClRandomModes_CtrDrbg.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRandomModes/src/mcuxClRandomModes_CtrDrbg_PrDisabled.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRandomModes/src/mcuxClRandomModes_NormalMode.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRandomModes/src/mcuxClRandomModes_PrDisabled.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRandomModes/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRandomModes/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_random_modes_ctr dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_rsa)
# Add set(CONFIG_USE_component_els_pkc_rsa true) in config.cmake to use this component

message("component_els_pkc_rsa component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_secure_counter AND CONFIG_USE_component_els_pkc_pre_processor AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_pkc AND CONFIG_USE_component_els_pkc_toolchain)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_ComputeD.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_ComputeD_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_GenerateProbablePrime.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_KeyGeneration_Crt.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_KeyGeneration_Crt_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_KeyGeneration_Plain.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_Mgf1.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_MillerRabinTest.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_MillerRabinTest_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_ModInv.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_NoEncode.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_NoVerify.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_Pkcs1v15Encode_sign.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_Pkcs1v15Verify.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_PrivateCrt.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_PrivateCrt_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_PrivatePlain.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_PssEncode.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_PssVerify.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_Public.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_Public_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_Sign.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_TestPQDistance.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_TestPQDistance_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_TestPrimeCandidate.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_TestPrimeCandidate_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_Verify.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_VerifyE.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_RemoveBlinding.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_RemoveBlinding_FUP.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/inc
)

else()

message(SEND_ERROR "component_els_pkc_rsa dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_session)
# Add set(CONFIG_USE_component_els_pkc_session true) in config.cmake to use this component

message("component_els_pkc_session component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_secure_counter AND CONFIG_USE_component_els_pkc_pre_processor AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_toolchain AND CONFIG_USE_component_els_pkc_random)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClSession/src/mcuxClSession.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClSession/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClSession/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_session dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_trng)
# Add set(CONFIG_USE_component_els_pkc_trng true) in config.cmake to use this component

message("component_els_pkc_trng component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_secure_counter AND CONFIG_USE_component_els_pkc_pre_processor AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_els)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClTrng/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClTrng/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_trng dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_trng_type_els)
# Add set(CONFIG_USE_component_els_pkc_trng_type_els true) in config.cmake to use this component

message("component_els_pkc_trng_type_els component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_trng AND CONFIG_USE_component_els_pkc_els)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRandomModes/src/mcuxClRandomModes_NormalMode.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClTrng/src/mcuxClTrng_ELS.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)

else()

message(SEND_ERROR "component_els_pkc_trng_type_els dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_trng_type_rng4)
# Add set(CONFIG_USE_component_els_pkc_trng_type_rng4 true) in config.cmake to use this component

message("component_els_pkc_trng_type_rng4 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_trng)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClTrng/src/mcuxClTrng_SA_TRNG.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClTrng/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClTrng/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_trng_type_rng4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_flow_protection)
# Add set(CONFIG_USE_component_els_pkc_flow_protection true) in config.cmake to use this component

message("component_els_pkc_flow_protection component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_core)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxCsslFlowProtection/inc
)

else()

message(SEND_ERROR "component_els_pkc_flow_protection dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_param_integrity)
# Add set(CONFIG_USE_component_els_pkc_param_integrity true) in config.cmake to use this component

message("component_els_pkc_param_integrity component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_secure_counter AND CONFIG_USE_component_els_pkc_pre_processor)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxCsslParamIntegrity/src/mcuxCsslParamIntegrity.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxCsslParamIntegrity/inc
)

else()

message(SEND_ERROR "component_els_pkc_param_integrity dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc)
# Add set(CONFIG_USE_component_els_pkc true) in config.cmake to use this component

message("component_els_pkc component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_els AND CONFIG_USE_component_els_pkc_pkc AND CONFIG_USE_component_els_pkc_trng AND ((CONFIG_USE_component_els_pkc_platform_mcxn AND CONFIG_USE_component_els_pkc_doc_mcxn AND CONFIG_USE_component_els_pkc_static_lib_mcxn AND (CONFIG_DEVICE_ID STREQUAL MCXN546 OR CONFIG_DEVICE_ID STREQUAL MCXN547 OR CONFIG_DEVICE_ID STREQUAL MCXN946 OR CONFIG_DEVICE_ID STREQUAL MCXN947))))

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/inc/impl
)

else()

message(SEND_ERROR "component_els_pkc dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_platform_mcxn)
# Add set(CONFIG_USE_component_els_pkc_platform_mcxn true) in config.cmake to use this component

message("component_els_pkc_platform_mcxn component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc AND CONFIG_USE_component_els_pkc_random_modes_ctr AND ((CONFIG_USE_component_els_pkc_trng_type_els AND (CONFIG_DEVICE_ID STREQUAL MCXN546 OR CONFIG_DEVICE_ID STREQUAL MCXN547 OR CONFIG_DEVICE_ID STREQUAL MCXN946 OR CONFIG_DEVICE_ID STREQUAL MCXN947))))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/platforms/mcxn/mcux_els.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/platforms/mcxn/mcux_pkc.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/platforms/mcxn
  ${CMAKE_CURRENT_LIST_DIR}/./src/platforms/mcxn/inc
)

else()

message(SEND_ERROR "component_els_pkc_platform_mcxn dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_examples)
# Add set(CONFIG_USE_component_els_pkc_examples true) in config.cmake to use this component

message("component_els_pkc_examples component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_els AND CONFIG_USE_component_els_pkc_pkc AND CONFIG_USE_component_els_pkc)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClAeadModes/mcuxClAeadModes_Multipart_Els_Ccm_Example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClAeadModes/mcuxClAeadModes_Oneshot_Els_Ccm_Example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClAeadModes/mcuxClAeadModes_Oneshot_Els_Gcm_Example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClCipherModes/mcuxClCipherModes_Multipart_Cbc_Els_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClCipherModes/mcuxClCipherModes_Multipart_Ctr_Els_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClCipherModes/mcuxClCipherModes_Multipart_Ecb_Els_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClCipherModes/mcuxClCipherModes_Multipart_Ecb_PaddingPKCS7_Els_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClCipherModes/mcuxClCipherModes_Oneshot_Cbc_Els_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClCipherModes/mcuxClCipherModes_Oneshot_Cbc_ZeroPadding_Els_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClCipherModes/mcuxClCipherModes_Oneshot_Ctr_Els_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClCipherModes/mcuxClCipherModes_Oneshot_Ecb_Els_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClCipherModes/mcuxClCipherModes_Oneshot_Ecb_PaddingPKCS7_Els_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClCipherModes/mcuxClCipherModes_Oneshot_Ecb_ZeroPadding_Els_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEcc/mcuxClEcc_EdDSA_Ed25519_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEcc/mcuxClEcc_EdDSA_GenerateSignature_Ed25519_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEcc/mcuxClEcc_EdDSA_VerifySignature_Ed25519_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEcc/mcuxClEcc_Mont_Curve25519_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEcc/mcuxClEcc_WeierECC_CustomEccWeierType_BN256_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEcc/mcuxClEcc_EdDSA_Ed25519ctx_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEcc/mcuxClEcc_EdDSA_Ed25519ph_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEls/mcuxClEls_Cipher_Aes128_Cbc_Encrypt_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEls/mcuxClEls_Cipher_Aes128_Ecb_Encrypt_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEls/mcuxClEls_Common_Get_Info_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEls/mcuxClEls_Ecc_Keygen_Sign_Verify_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEls/mcuxClEls_Hash_Sha224_One_Block_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEls/mcuxClEls_Hash_Sha256_One_Block_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEls/mcuxClEls_Hash_Sha384_One_Block_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEls/mcuxClEls_Hash_Sha512_One_Block_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEls/mcuxClEls_Rng_Prng_Get_Random_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEls/mcuxClEls_Tls_Master_Key_Session_Keys_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClHashModes/mcuxClHashModes_sha224_oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClHashModes/mcuxClHashModes_sha256_longMsgOneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClHashModes/mcuxClHashModes_sha256_oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClHashModes/mcuxClHashModes_sha256_streaming_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClHashModes/mcuxClHashModes_sha384_oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClHashModes/mcuxClHashModes_sha512_oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClHmac/mcuxClHmac_Els_Oneshot_External_Key_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClHmac/mcuxClHmac_Sw_Oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClKey/mcuxClKey_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClMacModes/mcuxClMacModes_cbc_mac_multipart_zero_padding_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClMacModes/mcuxClMacModes_cbc_mac_oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClMacModes/mcuxClMacModes_cmac_oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClRandomModes/mcuxClRandomModes_ELS_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClRsa/mcuxClRsa_sign_NoEncode_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClRsa/mcuxClRsa_sign_pss_sha2_256_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClRsa/mcuxClRsa_verify_NoVerify_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClRsa/mcuxClRsa_verify_pssverify_sha2_256_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslFlowProtection/mcuxCsslFlowProtection_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslMemory/data_invariant_memory_compare.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslMemory/data_invariant_memory_copy.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslMemory/mcuxCsslMemory_Clear_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslMemory/mcuxCsslMemory_Set_example.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslFlowProtection/inc
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslMemory/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClExample/inc
)

else()

message(SEND_ERROR "component_els_pkc_examples dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()

