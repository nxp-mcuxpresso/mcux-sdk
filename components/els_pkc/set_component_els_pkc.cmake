include_guard(GLOBAL)


if (CONFIG_USE_component_els_pkc_core)
# Add set(CONFIG_USE_component_els_pkc_core true) in config.cmake to use this component

message("component_els_pkc_core component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClCore/inc
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


if (CONFIG_USE_component_els_pkc_pre_processor)
# Add set(CONFIG_USE_component_els_pkc_pre_processor true) in config.cmake to use this component

message("component_els_pkc_pre_processor component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxCsslCPreProcessor/inc
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


if (CONFIG_USE_component_els_pkc_doc_lpc)
# Add set(CONFIG_USE_component_els_pkc_doc_lpc true) in config.cmake to use this component

message("component_els_pkc_doc_lpc component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL LPC55S36))

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)

else()

message(SEND_ERROR "component_els_pkc_doc_lpc dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_doc_mcxn)
# Add set(CONFIG_USE_component_els_pkc_doc_mcxn true) in config.cmake to use this component

message("component_els_pkc_doc_mcxn component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MCXN546 OR CONFIG_DEVICE_ID STREQUAL MCXN547 OR CONFIG_DEVICE_ID STREQUAL MCXN946 OR CONFIG_DEVICE_ID STREQUAL MCXN947 OR CONFIG_DEVICE_ID STREQUAL MCXN235 OR CONFIG_DEVICE_ID STREQUAL MCXN236))

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)

else()

message(SEND_ERROR "component_els_pkc_doc_mcxn dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_doc_rw61x)
# Add set(CONFIG_USE_component_els_pkc_doc_rw61x true) in config.cmake to use this component

message("component_els_pkc_doc_rw61x component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL RW610 OR CONFIG_DEVICE_ID STREQUAL RW612))

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)

else()

message(SEND_ERROR "component_els_pkc_doc_rw61x dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_static_lib_mcxn)
# Add set(CONFIG_USE_component_els_pkc_static_lib_mcxn true) in config.cmake to use this component

message("component_els_pkc_static_lib_mcxn component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL MCXN546 OR CONFIG_DEVICE_ID STREQUAL MCXN547 OR CONFIG_DEVICE_ID STREQUAL MCXN946 OR CONFIG_DEVICE_ID STREQUAL MCXN947 OR CONFIG_DEVICE_ID STREQUAL MCXN235 OR CONFIG_DEVICE_ID STREQUAL MCXN236))

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)

else()

message(SEND_ERROR "component_els_pkc_static_lib_mcxn dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_static_lib_rw61x)
# Add set(CONFIG_USE_component_els_pkc_static_lib_rw61x true) in config.cmake to use this component

message("component_els_pkc_static_lib_rw61x component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL RW610 OR CONFIG_DEVICE_ID STREQUAL RW612))

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)

else()

message(SEND_ERROR "component_els_pkc_static_lib_rw61x dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_static_lib_lpc)
# Add set(CONFIG_USE_component_els_pkc_static_lib_lpc true) in config.cmake to use this component

message("component_els_pkc_static_lib_lpc component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL LPC55S36))

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)

else()

message(SEND_ERROR "component_els_pkc_static_lib_lpc dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

if(CONFIG_USE_component_els_pkc_aes AND CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_els AND CONFIG_USE_component_els_pkc_buffer)

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
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClAeadModes/src/mcuxClAeadModes_Els_AesCcmEngine.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClAeadModes/src/mcuxClAeadModes_Els_AesGcm.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClAeadModes/src/mcuxClAeadModes_Els_AesGcmEngine.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClAeadModes/src/mcuxClAeadModes_Els_Modes.c
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


if (CONFIG_USE_component_els_pkc_buffer)
# Add set(CONFIG_USE_component_els_pkc_buffer true) in config.cmake to use this component

message("component_els_pkc_buffer component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_core AND CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_data_integrity AND CONFIG_USE_component_els_pkc_toolchain)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClBuffer/src/mcuxClBuffer.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClBuffer/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClBuffer/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_buffer dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_cipher)
# Add set(CONFIG_USE_component_els_pkc_cipher true) in config.cmake to use this component

message("component_els_pkc_cipher component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_els AND CONFIG_USE_component_els_pkc_buffer)

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
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClCipherModes/src/mcuxClCipherModes_Common_Helper.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClCipherModes/src/mcuxClCipherModes_Crypt_Els_Modes.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClCipherModes/src/mcuxClCipherModes_Els_Aes.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClCipherModes/src/mcuxClCipherModes_Els_AesEngine.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClCipherModes/src/mcuxClCipherModes_Els_Aes_Internal.c
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


if (CONFIG_USE_component_els_pkc_crc)
# Add set(CONFIG_USE_component_els_pkc_crc true) in config.cmake to use this component

message("component_els_pkc_crc component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_core AND CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_data_integrity AND CONFIG_USE_component_els_pkc_toolchain)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClCrc/src/mcuxClCrc.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClCrc/src/mcuxClCrc_Sw.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClCrc/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClCrc/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_crc dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_ecc_deterministic)
# Add set(CONFIG_USE_component_els_pkc_ecc_deterministic true) in config.cmake to use this component

message("component_els_pkc_ecc_deterministic component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_ecc_deterministic)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_DeterministicECDSA.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_DeterministicECDSA_Internal_BlindedSecretKeyGen.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_DeterministicECDSA_Internal_BlindedSecretKeyGen_FUP.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_ecc_deterministic dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_ecc)
# Add set(CONFIG_USE_component_els_pkc_ecc true) in config.cmake to use this component

message("component_els_pkc_ecc component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_pkc AND CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_secure_counter AND CONFIG_USE_component_els_pkc_pre_processor AND CONFIG_USE_component_els_pkc_key AND CONFIG_USE_component_els_pkc_els AND CONFIG_USE_component_els_pkc_buffer)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Constants.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_GenerateKeyPair.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_GenerateKeyPair_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_GenerateSignature.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_GenerateSignatureMode.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_GenerateSignature_FUP.c
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
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Internal_InterleaveScalar.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Internal_InterleaveTwoScalars.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Internal_Interleave_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Internal_PointComparison_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Internal_RecodeAndReorderScalar.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Internal_SetupEnvironment.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Internal_SetupEnvironment_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Internal_Types.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_KeyTypes.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_MontDH_GenerateKeyPair.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_MontDH_KeyAgreement.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Mont_Internal_DhSetupEnvironment.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Mont_Internal_MontDhX.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Mont_Internal_MontDhX_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Mont_Internal_SecureScalarMult_XZMontLadder.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Mont_Internal_SecureScalarMult_XZMontLadder_FUP.c
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
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_WeierECC_Internal_BlindedSecretKeyGen.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_WeierECC_Internal_BlindedSecretKeyGen_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_WeierECC_Internal_GenerateKeyPair.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_WeierECC_Internal_KeyAgreement_ECDH.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_WeierECC_Internal_SetupEnvironment.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Internal_ConvertPoint_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Internal_FUP.c
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
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEls/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_els_common dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

if(CONFIG_USE_component_els_pkc_els_header_only AND CONFIG_USE_component_els_pkc_els_common AND CONFIG_USE_component_els_pkc_hash AND CONFIG_USE_component_els_pkc_core AND CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_key AND CONFIG_USE_component_els_pkc_mac_modes AND CONFIG_USE_component_els_pkc_aead_modes AND CONFIG_USE_component_els_pkc_data_integrity AND CONFIG_USE_component_els_pkc_cipher_modes)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEls/src/mcuxClEls_Aead.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEls/src/mcuxClEls_Cipher.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEls/src/mcuxClEls_Cmac.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEls/src/mcuxClEls_Ecc.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEls/src/mcuxClEls_Hash.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEls/src/mcuxClEls_Hmac.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEls/src/mcuxClEls_Kdf.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEls/src/mcuxClEls_Rng.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClEls/src/mcuxClEls_KeyManagement.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)

else()

message(SEND_ERROR "component_els_pkc_els dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_glikey)
# Add set(CONFIG_USE_component_els_pkc_glikey true) in config.cmake to use this component

message("component_els_pkc_glikey component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_core AND CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_toolchain)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClGlikey/src/mcuxClGlikey.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClGlikey/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClGlikey/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_glikey dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClHash/src/mcuxClHash_Internal.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClHash/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClHash/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_hash dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_hashmodes)
# Add set(CONFIG_USE_component_els_pkc_hashmodes true) in config.cmake to use this component

message("component_els_pkc_hashmodes component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_els AND CONFIG_USE_component_els_pkc_buffer)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClHashModes/src/mcuxClHashModes_Core_c_sha1.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClHashModes/src/mcuxClHashModes_Core_els_sha2.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClHashModes/src/mcuxClHashModes_Internal_c_sha1.c
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


if (CONFIG_USE_component_els_pkc_hmac)
# Add set(CONFIG_USE_component_els_pkc_hmac true) in config.cmake to use this component

message("component_els_pkc_hmac component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_key AND CONFIG_USE_component_els_pkc_toolchain AND CONFIG_USE_component_els_pkc_padding)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
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


if (CONFIG_USE_component_els_pkc_key_derivation)
# Add set(CONFIG_USE_component_els_pkc_key_derivation true) in config.cmake to use this component

message("component_els_pkc_key_derivation component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_key_derivation)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClKey/src/mcuxClKey_agreement.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClKey/src/mcuxClKey_agreement_selftest.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClKey/src/mcuxClKey_Derivation.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClKey/src/mcuxClKey_Derivation_HKDF.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClKey/src/mcuxClKey_Derivation_NIST_SP800_108.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClKey/src/mcuxClKey_Derivation_NIST_SP800_56C.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClKey/src/mcuxClKey_Derivation_PBKDF2.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClKey/src/mcuxClKey_generate_keypair.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClKey/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClKey/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_key_derivation dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_key)
# Add set(CONFIG_USE_component_els_pkc_key true) in config.cmake to use this component

message("component_els_pkc_key component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_els AND CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_secure_counter AND CONFIG_USE_component_els_pkc_pre_processor AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_ecc AND CONFIG_USE_component_els_pkc_buffer)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClKey/src/mcuxClKey.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClKey/src/mcuxClKey_Protection.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClKey/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClKey/inc/internal
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


if (CONFIG_USE_component_els_pkc_mac_modes)
# Add set(CONFIG_USE_component_els_pkc_mac_modes true) in config.cmake to use this component

message("component_els_pkc_mac_modes component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_mac)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMacModes/src/mcuxClMacModes_Common.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMacModes/src/mcuxClMacModes_Common_Modes.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMacModes/src/mcuxClMacModes_Els_Cbcmac.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMacModes/src/mcuxClMacModes_Els_Cmac.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMacModes/src/mcuxClMacModes_Els_Functions.c
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

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_secure_counter AND CONFIG_USE_component_els_pkc_pre_processor AND CONFIG_USE_component_els_pkc_pkc AND CONFIG_USE_component_els_pkc_buffer)

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
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClMemory/inc/internal
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxCsslMemory/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxCsslMemory/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_memory dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_oscca)
# Add set(CONFIG_USE_component_els_pkc_oscca true) in config.cmake to use this component

message("component_els_pkc_oscca component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_oscca_aeadmodes AND CONFIG_USE_component_els_pkc_oscca_ciphermodes AND CONFIG_USE_component_els_pkc_oscca_macmodes AND CONFIG_USE_component_els_pkc_oscca_randommodes AND CONFIG_USE_component_els_pkc_oscca_sm2 AND CONFIG_USE_component_els_pkc_oscca_sm3 AND CONFIG_USE_component_els_pkc_oscca_sm4 AND CONFIG_USE_component_els_pkc_oscca_pkc AND CONFIG_USE_component_els_pkc_oscca_safo AND CONFIG_USE_component_els_pkc_signature AND CONFIG_USE_component_els_pkc_crc)

else()

message(SEND_ERROR "component_els_pkc_oscca dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_oscca_aeadmodes)
# Add set(CONFIG_USE_component_els_pkc_oscca_aeadmodes true) in config.cmake to use this component

message("component_els_pkc_oscca_aeadmodes component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaAeadModes/src/mcuxClOsccaAeadModes_Ccm_Common.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaAeadModes/src/mcuxClOsccaAeadModes_Constants.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaAeadModes/src/mcuxClOsccaAeadModes_EngineCcm.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaAeadModes/src/mcuxClOsccaAeadModes_SkeletonCcm.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaAeadModes/src/mcuxClOsccaAeadModes_SM4Ctr.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaAeadModes/src/mcuxClOsccaAeadModes_SM4_Multipart.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaAeadModes/src/mcuxClOsccaAeadModes_SM4_OneShot.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaAeadModes/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaAeadModes/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_oscca_aeadmodes dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_oscca_ciphermodes)
# Add set(CONFIG_USE_component_els_pkc_oscca_ciphermodes true) in config.cmake to use this component

message("component_els_pkc_oscca_ciphermodes component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaCipherModes/src/mcuxClOsccaCipherModes_Constants.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaCipherModes/src/mcuxClOsccaCipherModes_SM4_Crypt.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaCipherModes/src/mcuxClOsccaCipherModes_SM4_Crypt_Internal.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaCipherModes/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaCipherModes/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_oscca_ciphermodes dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_oscca_macmodes)
# Add set(CONFIG_USE_component_els_pkc_oscca_macmodes true) in config.cmake to use this component

message("component_els_pkc_oscca_macmodes component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaMacModes/src/mcuxClOsccaMacModes.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaMacModes/src/mcuxClOsccaMacModes_CBCMac.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaMacModes/src/mcuxClOsccaMacModes_CMac.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaMacModes/src/mcuxClOsccaMacModes_Helper.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaMacModes/src/mcuxClOsccaMacModes_KeyTypes.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaMacModes/src/mcuxClOsccaMacModes_Modes.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaMacModes/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaMacModes/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_oscca_macmodes dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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


if (CONFIG_USE_component_els_pkc_oscca_randommodes)
# Add set(CONFIG_USE_component_els_pkc_oscca_randommodes true) in config.cmake to use this component

message("component_els_pkc_oscca_randommodes component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaRandomModes/src/mcuxClOsccaRandomModes_OsccaMode.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaRandomModes/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaRandomModes/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_oscca_randommodes dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_oscca_safo)
# Add set(CONFIG_USE_component_els_pkc_oscca_safo true) in config.cmake to use this component

message("component_els_pkc_oscca_safo component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSafo/src/mcuxClOsccaSafo_Drv.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSafo/inc
)

else()

message(SEND_ERROR "component_els_pkc_oscca_safo dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_oscca_sm2)
# Add set(CONFIG_USE_component_els_pkc_oscca_sm2 true) in config.cmake to use this component

message("component_els_pkc_oscca_sm2 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_common AND CONFIG_USE_component_els_pkc_signature)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm2/src/mcuxClOsccaSm2_Cipher_Crypt.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm2/src/mcuxClOsccaSm2_ComputePrehash.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm2/src/mcuxClOsccaSm2_Constants.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm2/src/mcuxClOsccaSm2_CryptoUtils.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm2/src/mcuxClOsccaSm2_Decrypt.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm2/src/mcuxClOsccaSm2_Ecc.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm2/src/mcuxClOsccaSm2_EccUtils.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm2/src/mcuxClOsccaSm2_EncDec_Internal.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm2/src/mcuxClOsccaSm2_Encrypt.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm2/src/mcuxClOsccaSm2_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm2/src/mcuxClOsccaSm2_GenerateKeyPair.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm2/src/mcuxClOsccaSm2_Helper.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm2/src/mcuxClOsccaSm2_InvertPrivateKey.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm2/src/mcuxClOsccaSm2_Keyagreement.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm2/src/mcuxClOsccaSm2_Keyagreement_SelfTest.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm2/src/mcuxClOsccaSm2_KeyExchange.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm2/src/mcuxClOsccaSm2_KeyTypes.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm2/src/mcuxClOsccaSm2_SelfTest.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm2/src/mcuxClOsccaSm2_Sign.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm2/src/mcuxClOsccaSm2_Signature_Internal.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm2/src/mcuxClOsccaSm2_Signature_PreHash.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm2/src/mcuxClOsccaSm2_Signature_SelfTest.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm2/src/mcuxClOsccaSm2_Verify.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm2/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm2/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_oscca_sm2 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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


if (CONFIG_USE_component_els_pkc_oscca_sm4)
# Add set(CONFIG_USE_component_els_pkc_oscca_sm4 true) in config.cmake to use this component

message("component_els_pkc_oscca_sm4 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm4/src/mcuxClOsccaSm4_CommonOperations.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm4/src/mcuxClOsccaSm4_Core.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm4/src/mcuxClOsccaSm4_KeyTypes.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm4/src/mcuxClOsccaSm4_LoadKey.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm4/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClOsccaSm4/inc/internal
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

message(SEND_ERROR "component_els_pkc_oscca_sm4 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_padding)
# Add set(CONFIG_USE_component_els_pkc_padding true) in config.cmake to use this component

message("component_els_pkc_padding component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_buffer)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPadding/src/mcuxClPadding.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPadding/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPadding/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_padding dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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


if (CONFIG_USE_component_els_pkc_psa_driver)
# Add set(CONFIG_USE_component_els_pkc_psa_driver true) in config.cmake to use this component

message("component_els_pkc_psa_driver component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_buffer AND (CONFIG_USE_component_els_pkc_platform_mcxn OR CONFIG_USE_component_els_pkc_platform_rw61x))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_Aead.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_Cipher.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_DER_functions.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_export_public_key.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_generate_ecp_key.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_Hash.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_Key.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_Mac.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_Rsa.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_Sign.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_UpdateKeyStatus.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPsaDriver/src/mcuxClPsaDriver_Verify.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPsaDriver/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClPsaDriver/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_psa_driver dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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


if (CONFIG_USE_component_els_pkc_random_modes_hmacdrbg)
# Add set(CONFIG_USE_component_els_pkc_random_modes_hmacdrbg true) in config.cmake to use this component

message("component_els_pkc_random_modes_hmacdrbg component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_random_modes)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRandomModes/src/mcuxClRandomModes_HmacDrbg.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRandomModes/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_random_modes_hmacdrbg dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_random_modes)
# Add set(CONFIG_USE_component_els_pkc_random_modes true) in config.cmake to use this component

message("component_els_pkc_random_modes component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_secure_counter AND CONFIG_USE_component_els_pkc_pre_processor AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_aes AND CONFIG_USE_component_els_pkc_trng AND CONFIG_USE_component_els_pkc_buffer)

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


if (CONFIG_USE_component_els_pkc_rsa_oaep)
# Add set(CONFIG_USE_component_els_pkc_rsa_oaep true) in config.cmake to use this component

message("component_els_pkc_rsa_oaep component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_rsa)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_KeyTypes.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_ModeConstructors.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_OaepDecode.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_OaepEncode.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_pkcs1v15Decode_decrypt.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_Pkcs1v15Encode_encrypt.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_Util_Decrypt.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_Util_Encrypt.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_rsa_oaep dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_rsa)
# Add set(CONFIG_USE_component_els_pkc_rsa true) in config.cmake to use this component

message("component_els_pkc_rsa component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_secure_counter AND CONFIG_USE_component_els_pkc_pre_processor AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_pkc AND CONFIG_USE_component_els_pkc_toolchain AND CONFIG_USE_component_els_pkc_buffer)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_ComputeD.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_ComputeD_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_GenerateProbablePrime.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_getMillerRabinTestIterations.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_KeyGeneration_Crt.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_KeyGeneration_Crt_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_KeyGeneration_Plain.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_Mgf1.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_MillerRabinTest.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_MillerRabinTest_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_ModInv.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_Pkcs1v15Encode_sign.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_Pkcs1v15Verify.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_PrivateCrt.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_PrivateCrt_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_PrivatePlain.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_PssEncode.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_PssVerify.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_Public.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_PublicExp.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_RemoveBlinding.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_RemoveBlinding_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_Sign.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_Sign_NoEMSA.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_TestPQDistance.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_TestPQDistance_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_TestPrimeCandidate.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_TestPrimeCandidate_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_Verify.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_VerifyE.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/src/mcuxClRsa_Verify_NoEMSA.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClRsa/inc/internal
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


if (CONFIG_USE_component_els_pkc_signature)
# Add set(CONFIG_USE_component_els_pkc_signature true) in config.cmake to use this component

message("component_els_pkc_signature component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_secure_counter AND CONFIG_USE_component_els_pkc_pre_processor AND CONFIG_USE_component_els_pkc_toolchain)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClSignature/src/mcuxClSignature.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClSignature/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClSignature/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_signature dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

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

if(CONFIG_USE_component_els_pkc_els AND CONFIG_USE_component_els_pkc_pkc AND CONFIG_USE_component_els_pkc_trng AND ((CONFIG_USE_component_els_pkc_platform_lpc AND CONFIG_USE_component_els_pkc_doc_lpc AND CONFIG_USE_component_els_pkc_static_lib_lpc AND (CONFIG_DEVICE_ID STREQUAL LPC55S36)) OR (CONFIG_USE_component_els_pkc_platform_mcxn AND CONFIG_USE_component_els_pkc_doc_mcxn AND CONFIG_USE_component_els_pkc_static_lib_mcxn AND (CONFIG_DEVICE_ID STREQUAL MCXN546 OR CONFIG_DEVICE_ID STREQUAL MCXN547 OR CONFIG_DEVICE_ID STREQUAL MCXN946 OR CONFIG_DEVICE_ID STREQUAL MCXN947 OR CONFIG_DEVICE_ID STREQUAL MCXN235 OR CONFIG_DEVICE_ID STREQUAL MCXN236)) OR (CONFIG_USE_component_els_pkc_platform_rw61x AND CONFIG_USE_component_els_pkc_doc_rw61x AND CONFIG_USE_component_els_pkc_static_lib_rw61x AND (CONFIG_DEVICE_ID STREQUAL RW610 OR CONFIG_DEVICE_ID STREQUAL RW612))))

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/inc
)

else()

message(SEND_ERROR "component_els_pkc dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_platform_mcxn)
# Add set(CONFIG_USE_component_els_pkc_platform_mcxn true) in config.cmake to use this component

message("component_els_pkc_platform_mcxn component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc AND CONFIG_USE_component_els_pkc_random_modes_ctr AND ((CONFIG_USE_component_els_pkc_trng_type_els AND (CONFIG_DEVICE_ID STREQUAL MCXN546 OR CONFIG_DEVICE_ID STREQUAL MCXN547 OR CONFIG_DEVICE_ID STREQUAL MCXN946 OR CONFIG_DEVICE_ID STREQUAL MCXN947 OR CONFIG_DEVICE_ID STREQUAL MCXN235 OR CONFIG_DEVICE_ID STREQUAL MCXN236))))

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


if (CONFIG_USE_component_els_pkc_platform_rw61x_inf_header_only)
# Add set(CONFIG_USE_component_els_pkc_platform_rw61x_inf_header_only true) in config.cmake to use this component

message("component_els_pkc_platform_rw61x_inf_header_only component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL RW610 OR CONFIG_DEVICE_ID STREQUAL RW612))

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/platforms/rw61x
  ${CMAKE_CURRENT_LIST_DIR}/./src/platforms/rw61x/inc
)

else()

message(SEND_ERROR "component_els_pkc_platform_rw61x_inf_header_only dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_platform_rw61x_interface_files)
# Add set(CONFIG_USE_component_els_pkc_platform_rw61x_interface_files true) in config.cmake to use this component

message("component_els_pkc_platform_rw61x_interface_files component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_platform_rw61x_inf_header_only AND (CONFIG_DEVICE_ID STREQUAL RW610 OR CONFIG_DEVICE_ID STREQUAL RW612))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/platforms/rw61x/mcux_els.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/platforms/rw61x/mcux_pkc.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/platforms/rw61x
)

else()

message(SEND_ERROR "component_els_pkc_platform_rw61x_interface_files dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_platform_rw61x_standalone_clib_gdet_sensor)
# Add set(CONFIG_USE_component_els_pkc_platform_rw61x_standalone_clib_gdet_sensor true) in config.cmake to use this component

message("component_els_pkc_platform_rw61x_standalone_clib_gdet_sensor component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL RW610 OR CONFIG_DEVICE_ID STREQUAL RW612) AND CONFIG_USE_component_els_pkc_els_header_only AND CONFIG_USE_component_els_pkc_els_common AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_standalone_gdet AND CONFIG_USE_component_els_pkc_platform_rw61x_inf_header_only AND CONFIG_USE_component_els_pkc_buffer)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/platforms/rw61x
)

else()

message(SEND_ERROR "component_els_pkc_platform_rw61x_standalone_clib_gdet_sensor dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_platform_rw61x)
# Add set(CONFIG_USE_component_els_pkc_platform_rw61x true) in config.cmake to use this component

message("component_els_pkc_platform_rw61x component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL RW610 OR CONFIG_DEVICE_ID STREQUAL RW612) AND CONFIG_USE_component_els_pkc_platform_rw61x_interface_files AND CONFIG_USE_component_els_pkc AND CONFIG_USE_component_els_pkc_trng_type_rng4 AND CONFIG_USE_component_els_pkc_standalone_gdet AND CONFIG_USE_component_els_pkc_random_modes_ctr)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/platforms/rw61x
)

else()

message(SEND_ERROR "component_els_pkc_platform_rw61x dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_platform_lpc)
# Add set(CONFIG_USE_component_els_pkc_platform_lpc true) in config.cmake to use this component

message("component_els_pkc_platform_lpc component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL LPC55S36) AND CONFIG_USE_component_els_pkc AND CONFIG_USE_component_els_pkc_standalone_gdet)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./src/platforms/lpc/mcux_els.c
  ${CMAKE_CURRENT_LIST_DIR}/./src/platforms/lpc/mcux_pkc.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./src/platforms/lpc
  ${CMAKE_CURRENT_LIST_DIR}/./src/platforms/lpc/inc
)

else()

message(SEND_ERROR "component_els_pkc_platform_lpc dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_examples)
# Add set(CONFIG_USE_component_els_pkc_examples true) in config.cmake to use this component

message("component_els_pkc_examples component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_els AND CONFIG_USE_component_els_pkc_pkc AND CONFIG_USE_component_els_pkc_random_modes AND CONFIG_USE_component_els_pkc AND CONFIG_USE_component_els_pkc_examples_aead AND CONFIG_USE_component_els_pkc_examples_cipher_modes AND CONFIG_USE_component_els_pkc_examples_ecc AND CONFIG_USE_component_els_pkc_examples_els AND CONFIG_USE_component_els_pkc_examples_hash_modes AND CONFIG_USE_component_els_pkc_examples_hmac AND CONFIG_USE_component_els_pkc_examples_key AND CONFIG_USE_component_els_pkc_examples_mac_modes AND CONFIG_USE_component_els_pkc_examples_rsa AND CONFIG_USE_component_els_pkc_examples_flow_protection AND CONFIG_USE_component_els_pkc_examples_memory AND ((CONFIG_USE_component_els_pkc_examples_random_modes AND (CONFIG_DEVICE_ID STREQUAL MCXN546 OR CONFIG_DEVICE_ID STREQUAL MCXN547 OR CONFIG_DEVICE_ID STREQUAL MCXN946 OR CONFIG_DEVICE_ID STREQUAL MCXN947 OR CONFIG_DEVICE_ID STREQUAL MCXN235 OR CONFIG_DEVICE_ID STREQUAL MCXN236 OR CONFIG_DEVICE_ID STREQUAL RW610 OR CONFIG_DEVICE_ID STREQUAL RW612)) OR (CONFIG_DEVICE_ID STREQUAL LPC55S36)))

else()

message(SEND_ERROR "component_els_pkc_examples dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_examples_memory)
# Add set(CONFIG_USE_component_els_pkc_examples_memory true) in config.cmake to use this component

message("component_els_pkc_examples_memory component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_els)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslMemory/mcuxCsslMemory_Clear_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslMemory/mcuxCsslMemory_Compare_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslMemory/mcuxCsslMemory_Copy_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslMemory/mcuxCsslMemory_Set_example.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslFlowProtection/inc
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslMemory/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClExample/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClBuffer/inc
)

else()

message(SEND_ERROR "component_els_pkc_examples_memory dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_examples_flow_protection)
# Add set(CONFIG_USE_component_els_pkc_examples_flow_protection true) in config.cmake to use this component

message("component_els_pkc_examples_flow_protection component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_els)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslFlowProtection/mcuxCsslFlowProtection_example.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslFlowProtection/inc
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslMemory/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClExample/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClBuffer/inc
)

else()

message(SEND_ERROR "component_els_pkc_examples_flow_protection dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_examples_rsa)
# Add set(CONFIG_USE_component_els_pkc_examples_rsa true) in config.cmake to use this component

message("component_els_pkc_examples_rsa component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_els)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClRsa/mcuxClRsa_sign_NoEncode_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClRsa/mcuxClRsa_sign_pss_sha2_256_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClRsa/mcuxClRsa_verify_NoVerify_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClRsa/mcuxClRsa_verify_pssverify_sha2_256_example.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslFlowProtection/inc
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslMemory/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClExample/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClBuffer/inc
)

else()

message(SEND_ERROR "component_els_pkc_examples_rsa dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_examples_random_modes)
# Add set(CONFIG_USE_component_els_pkc_examples_random_modes true) in config.cmake to use this component

message("component_els_pkc_examples_random_modes component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_els)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClRandomModes/mcuxClRandomModes_CtrDrbg_AES256_DRG3_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClRandomModes/mcuxClRandomModes_CtrDrbg_AES256_DRG4_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClRandomModes/mcuxClRandomModes_CtrDrbg_AES256_ELS_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClRandomModes/mcuxClRandomModes_Different_Sessions_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClRandomModes/mcuxClRandomModes_PatchMode_CtrDrbg_AES256_DRG3_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClRandomModes/mcuxClRandomModes_TestMode_CtrDrbg_AES256_DRG4_example.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslFlowProtection/inc
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslMemory/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClExample/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClBuffer/inc
)

else()

message(SEND_ERROR "component_els_pkc_examples_random_modes dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_examples_mac_modes)
# Add set(CONFIG_USE_component_els_pkc_examples_mac_modes true) in config.cmake to use this component

message("component_els_pkc_examples_mac_modes component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_els AND CONFIG_USE_component_els_pkc_mac)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClMacModes/mcuxClMacModes_Els_Cbcmac_Aes128_Oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClMacModes/mcuxClMacModes_Els_Cbcmac_Aes256_Multipart_PaddingZero_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClMacModes/mcuxClMacModes_Els_Cmac_Aes128_Oneshot_example.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslFlowProtection/inc
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslMemory/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClExample/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClBuffer/inc
)

else()

message(SEND_ERROR "component_els_pkc_examples_mac_modes dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_examples_key)
# Add set(CONFIG_USE_component_els_pkc_examples_key true) in config.cmake to use this component

message("component_els_pkc_examples_key component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_memory)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClKey/mcuxClKey_example.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslFlowProtection/inc
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslMemory/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClExample/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClBuffer/inc
)

else()

message(SEND_ERROR "component_els_pkc_examples_key dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_examples_hmac)
# Add set(CONFIG_USE_component_els_pkc_examples_hmac true) in config.cmake to use this component

message("component_els_pkc_examples_hmac component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_els)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClHmac/mcuxClHmac_Els_Oneshot_External_Key_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClHmac/mcuxClHmac_Sw_Multipart_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClHmac/mcuxClHmac_Sw_Oneshot_example.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslFlowProtection/inc
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslMemory/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClExample/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClBuffer/inc
)

else()

message(SEND_ERROR "component_els_pkc_examples_hmac dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_examples_hash_modes)
# Add set(CONFIG_USE_component_els_pkc_examples_hash_modes true) in config.cmake to use this component

message("component_els_pkc_examples_hash_modes component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_els)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClHashModes/mcuxClHashModes_sha1_longMsgOneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClHashModes/mcuxClHashModes_sha1_oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClHashModes/mcuxClHashModes_sha1_streaming_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClHashModes/mcuxClHashModes_sha224_oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClHashModes/mcuxClHashModes_sha256_longMsgOneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClHashModes/mcuxClHashModes_sha256_oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClHashModes/mcuxClHashModes_sha256_streaming_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClHashModes/mcuxClHashModes_sha384_oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClHashModes/mcuxClHashModes_sha512_224_oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClHashModes/mcuxClHashModes_sha512_256_oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClHashModes/mcuxClHashModes_sha512_256_streaming_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClHashModes/mcuxClHashModes_sha512_oneshot_example.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslFlowProtection/inc
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslMemory/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClExample/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClBuffer/inc
)

else()

message(SEND_ERROR "component_els_pkc_examples_hash_modes dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_examples_els)
# Add set(CONFIG_USE_component_els_pkc_examples_els true) in config.cmake to use this component

message("component_els_pkc_examples_els component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_els)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEls/mcuxClEls_Cipher_Aes128_Cbc_Encrypt_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEls/mcuxClEls_Cipher_Aes128_Ecb_Encrypt_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEls/mcuxClEls_Common_Get_Info_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEls/mcuxClEls_Ecc_Keygen_Sign_Verify_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEls/mcuxClEls_Hash_HW_Security_Counter_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEls/mcuxClEls_Hash_Sha224_One_Block_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEls/mcuxClEls_Hash_Sha256_One_Block_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEls/mcuxClEls_Hash_Sha384_One_Block_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEls/mcuxClEls_Hash_Sha512_One_Block_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEls/mcuxClEls_Rng_Prng_Get_Random_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEls/mcuxClEls_Tls_Master_Key_Session_Keys_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClRandomModes/mcuxClRandomModes_ELS_example.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslFlowProtection/inc
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslMemory/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClExample/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClBuffer/inc
)

else()

message(SEND_ERROR "component_els_pkc_examples_els dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_examples_ecc)
# Add set(CONFIG_USE_component_els_pkc_examples_ecc true) in config.cmake to use this component

message("component_els_pkc_examples_ecc component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_els)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEcc/mcuxClEcc_EdDSA_Ed25519ctx_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEcc/mcuxClEcc_EdDSA_Ed25519ph_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEcc/mcuxClEcc_EdDSA_Ed25519_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEcc/mcuxClEcc_EdDSA_GenerateSignature_Ed25519_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEcc/mcuxClEcc_EdDSA_VerifySignature_Ed25519_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEcc/mcuxClEcc_MontDH_Curve25519_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClEcc/mcuxClEcc_MontDH_Curve448_example.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslFlowProtection/inc
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslMemory/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClExample/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClBuffer/inc
)

else()

message(SEND_ERROR "component_els_pkc_examples_ecc dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_examples_aead)
# Add set(CONFIG_USE_component_els_pkc_examples_aead true) in config.cmake to use this component

message("component_els_pkc_examples_aead component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_els AND CONFIG_USE_component_els_pkc_padding)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClAeadModes/mcuxClAeadModes_Els_Ccm_Aes128_Multipart_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClAeadModes/mcuxClAeadModes_Els_Ccm_Aes128_Oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClAeadModes/mcuxClAeadModes_Els_Gcm_Aes128_Oneshot_example.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslFlowProtection/inc
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslMemory/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClExample/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClBuffer/inc
)

else()

message(SEND_ERROR "component_els_pkc_examples_aead dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_examples_cipher_modes)
# Add set(CONFIG_USE_component_els_pkc_examples_cipher_modes true) in config.cmake to use this component

message("component_els_pkc_examples_cipher_modes component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_els)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClCipherModes/mcuxClCipherModes_Els_Cbc_Aes128_Multipart_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClCipherModes/mcuxClCipherModes_Els_Cbc_Aes128_Oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClCipherModes/mcuxClCipherModes_Els_Cbc_Aes128_Oneshot_PaddingZero_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClCipherModes/mcuxClCipherModes_Els_Ctr_Aes128_Multipart_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClCipherModes/mcuxClCipherModes_Els_Ctr_Aes128_Oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClCipherModes/mcuxClCipherModes_Els_Ecb_Aes128_Multipart_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClCipherModes/mcuxClCipherModes_Els_Ecb_Aes128_Multipart_PaddingPKCS7_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClCipherModes/mcuxClCipherModes_Els_Ecb_Aes128_Oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClCipherModes/mcuxClCipherModes_Els_Ecb_Aes128_Oneshot_PaddingPKCS7_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClCipherModes/mcuxClCipherModes_Els_Ecb_Aes128_Oneshot_PaddingZero_example.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslFlowProtection/inc
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslMemory/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClExample/inc
  ${CMAKE_CURRENT_LIST_DIR}/./src/comps/mcuxClBuffer/inc
)

else()

message(SEND_ERROR "component_els_pkc_examples_cipher_modes dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_els_pkc_psa_driver_examples)
# Add set(CONFIG_USE_component_els_pkc_psa_driver_examples true) in config.cmake to use this component

message("component_els_pkc_psa_driver_examples component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_DEVICE_ID STREQUAL RW610 OR CONFIG_DEVICE_ID STREQUAL RW612) AND CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc AND CONFIG_USE_component_els_pkc_psa_driver)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_aead_ccm_multipart_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_aead_ccm_oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_aead_gcm_multipart_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_aead_gcm_oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_aes_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_cipher_decrypt.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_cipher_multipart_CBC.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_cipher_multipart_CTR.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_cipher_multipart_ECB.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_eccsecp224k1_sign_verify_hash_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_ecdsa_keygen_oracleMemory_sign_verify_hash_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_ecdsa_keygen_oracleS50_sign_verify_hash_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_ecdsa_sign_verify_hash_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_ecdsa_sign_verify_message_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_keygen_export_public_key_brainpoolpr1_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_keygen_export_public_key_mont_curve25519_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_keygen_export_public_key_rsa_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_keygen_export_public_key_secpk1_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_keygen_export_public_key_secpr1_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_key_agreement_CURVE_25519_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_key_agreement_SECP_R1_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_mac_oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_mac_sign_multipart_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_mac_verify_multipart_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_rsa_PKCS1V15_sign_verify_message_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_rsa_PSS_sign_verify_hash_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_sha224_oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_sha256_abort_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_sha256_clone_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_sha256_multipart_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_sha256_oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_sha384_oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_sha512_oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxClPsaDriver/mcuxClPsaDriver_truncated_mac_oneshot_example.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
  ${CMAKE_CURRENT_LIST_DIR}/./examples/mcuxCsslFlowProtection/inc
)

else()

message(SEND_ERROR "component_els_pkc_psa_driver_examples dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()

