include_guard(GLOBAL)


if (CONFIG_USE_component_psa_crypto_driver_osal)
# Add set(CONFIG_USE_component_psa_crypto_driver_osal true) in config.cmake to use this component

message("component_psa_crypto_driver_osal component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./osal
)


endif()


if (CONFIG_USE_component_psa_crypto_driver_els_pkc_oracle)
# Add set(CONFIG_USE_component_psa_crypto_driver_els_pkc_oracle true) in config.cmake to use this component

message("component_psa_crypto_driver_els_pkc_oracle component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./els_pkc/oracle/src/mcuxClPsaDriver_Oracle.c
  ${CMAKE_CURRENT_LIST_DIR}/./els_pkc/oracle/src/mcuxClPsaDriver_Oracle_ElsUtils.c
  ${CMAKE_CURRENT_LIST_DIR}/./els_pkc/oracle/src/mcuxClPsaDriver_Oracle_Utils.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./els_pkc/oracle/inc
)


endif()


if (CONFIG_USE_component_psa_crypto_driver_els_pkc_common)
# Add set(CONFIG_USE_component_psa_crypto_driver_els_pkc_common true) in config.cmake to use this component

message("component_psa_crypto_driver_els_pkc_common component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./els_pkc/src/common/mcux_psa_els_pkc_common_init.c
  ${CMAKE_CURRENT_LIST_DIR}/./els_pkc/src/common/mcux_psa_els_pkc_entropy.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./els_pkc/include/common
)


endif()


if (CONFIG_USE_component_psa_crypto_driver_els_pkc_transparent)
# Add set(CONFIG_USE_component_psa_crypto_driver_els_pkc_transparent true) in config.cmake to use this component

message("component_psa_crypto_driver_els_pkc_transparent component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./els_pkc/src/transparent/mcux_psa_els_pkc_aead.c
  ${CMAKE_CURRENT_LIST_DIR}/./els_pkc/src/transparent/mcux_psa_els_pkc_asymmetric_signature.c
  ${CMAKE_CURRENT_LIST_DIR}/./els_pkc/src/transparent/mcux_psa_els_pkc_cipher.c
  ${CMAKE_CURRENT_LIST_DIR}/./els_pkc/src/transparent/mcux_psa_els_pkc_hash.c
  ${CMAKE_CURRENT_LIST_DIR}/./els_pkc/src/transparent/mcux_psa_els_pkc_init.c
  ${CMAKE_CURRENT_LIST_DIR}/./els_pkc/src/transparent/mcux_psa_els_pkc_key_generation.c
  ${CMAKE_CURRENT_LIST_DIR}/./els_pkc/src/transparent/mcux_psa_els_pkc_mac.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./els_pkc/include/transparent
)


endif()


if (CONFIG_USE_component_psa_crypto_driver_els_pkc_opaque)
# Add set(CONFIG_USE_component_psa_crypto_driver_els_pkc_opaque true) in config.cmake to use this component

message("component_psa_crypto_driver_els_pkc_opaque component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./els_pkc/src/opaque/mcux_psa_els_pkc_opaque_aead.c
  ${CMAKE_CURRENT_LIST_DIR}/./els_pkc/src/opaque/mcux_psa_els_pkc_opaque_asymmetric_signature.c
  ${CMAKE_CURRENT_LIST_DIR}/./els_pkc/src/opaque/mcux_psa_els_pkc_opaque_cipher.c
  ${CMAKE_CURRENT_LIST_DIR}/./els_pkc/src/opaque/mcux_psa_els_pkc_opaque_init.c
  ${CMAKE_CURRENT_LIST_DIR}/./els_pkc/src/opaque/mcux_psa_els_pkc_opaque_key_generation.c
  ${CMAKE_CURRENT_LIST_DIR}/./els_pkc/src/opaque/mcux_psa_els_pkc_opaque_mac.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./els_pkc/include/opaque
)


endif()


if (CONFIG_USE_component_psa_crypto_driver_osal_frtos)
# Add set(CONFIG_USE_component_psa_crypto_driver_osal_frtos true) in config.cmake to use this component

message("component_psa_crypto_driver_osal_frtos component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_psa_crypto_driver_osal)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./osal/frtos/osal_mutex.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./osal/frtos
)

else()

message(SEND_ERROR "component_psa_crypto_driver_osal_frtos dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_psa_crypto_driver_osal_baremetal)
# Add set(CONFIG_USE_component_psa_crypto_driver_osal_baremetal true) in config.cmake to use this component

message("component_psa_crypto_driver_osal_baremetal component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_component_psa_crypto_driver_osal)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./osal/baremetal/osal_mutex.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./osal/baremetal
)

else()

message(SEND_ERROR "component_psa_crypto_driver_osal_baremetal dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()

