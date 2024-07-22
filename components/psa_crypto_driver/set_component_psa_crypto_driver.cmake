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


if (CONFIG_USE_component_psa_crypto_driver_ele_s200_common)
# Add set(CONFIG_USE_component_psa_crypto_driver_ele_s200_common true) in config.cmake to use this component

message("component_psa_crypto_driver_ele_s200_common component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s200/src/common/mcux_psa_s2xx_common_init.c
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s200/src/common/mcux_psa_s2xx_entropy.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s200/include/common
)


endif()


if (CONFIG_USE_component_psa_crypto_driver_ele_s200_transparent)
# Add set(CONFIG_USE_component_psa_crypto_driver_ele_s200_transparent true) in config.cmake to use this component

message("component_psa_crypto_driver_ele_s200_transparent component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s200/src/transparent/mcux_psa_s2xx_aead.c
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s200/src/transparent/mcux_psa_s2xx_cipher.c
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s200/src/transparent/mcux_psa_s2xx_hash.c
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s200/src/transparent/mcux_psa_s2xx_init.c
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s200/src/transparent/mcux_psa_s2xx_mac.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s200/include/transparent
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


if (CONFIG_USE_component_psa_crypto_driver_ele_s4xx_psa_transparent)
# Add set(CONFIG_USE_component_psa_crypto_driver_ele_s4xx_psa_transparent true) in config.cmake to use this component

message("component_psa_crypto_driver_ele_s4xx_psa_transparent component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_s3mu AND CONFIG_USE_component_ele_crypto)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s4xx/src/transparent/mcux_psa_s4xx_init.c
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s4xx/src/transparent/mcux_psa_s4xx_key_generation.c
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s4xx/src/transparent/mcux_psa_s4xx_hash.c
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s4xx/src/common/mcux_psa_s4xx_common_key_management.c
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s4xx/src/transparent/mcux_psa_s4xx_aead.c
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s4xx/src/transparent/mcux_psa_s4xx_cipher.c
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s4xx/src/transparent/mcux_psa_s4xx_asymmetric_encryption.c
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s4xx/src/transparent/mcux_psa_s4xx_asymmetric_signature.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s4xx
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s4xx/include/common
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s4xx/include/transparent
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DPSA_CRYPTO_DRIVER_ELE_S4XX
  )

endif()

else()

message(SEND_ERROR "component_psa_crypto_driver_ele_s4xx_psa_transparent dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_psa_crypto_driver_ele_s4xx_sd_nvm_mgr)
# Add set(CONFIG_USE_component_psa_crypto_driver_ele_s4xx_sd_nvm_mgr true) in config.cmake to use this component

message("component_psa_crypto_driver_ele_s4xx_sd_nvm_mgr component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_usdhc AND CONFIG_USE_component_rgpio_adapter AND CONFIG_USE_middleware_sdmmc_host_usdhc AND CONFIG_USE_middleware_sdmmc_host_usdhc_interrupt AND CONFIG_USE_middleware_sdmmc_sd AND CONFIG_USE_middleware_fatfs_sd AND CONFIG_USE_middleware_fatfs AND CONFIG_USE_component_ele_nvm_manager)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s4xx/src/common/mcux_psa_s4xx_sdmmc_nvm_manager.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s4xx/include/common
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DPSA_ELE_S4XX_SD_NVM_MANAGER
  )

endif()

else()

message(SEND_ERROR "component_psa_crypto_driver_ele_s4xx_sd_nvm_mgr dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_psa_crypto_driver_ele_s4xx_psa_opaque)
# Add set(CONFIG_USE_component_psa_crypto_driver_ele_s4xx_psa_opaque true) in config.cmake to use this component

message("component_psa_crypto_driver_ele_s4xx_psa_opaque component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_s3mu AND CONFIG_USE_component_ele_crypto)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s4xx/src/opaque/mcux_psa_s4xx_opaque_init.c
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s4xx/src/common/mcux_psa_s4xx_common_key_management.c
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s4xx/src/opaque/mcux_psa_s4xx_opaque_key_generation.c
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s4xx/src/opaque/mcux_psa_s4xx_opaque_asymmetric_signature.c
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s4xx/src/opaque/mcux_psa_s4xx_opaque_cipher.c
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s4xx/src/opaque/mcux_psa_s4xx_opaque_aead.c
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s4xx/src/opaque/mcux_psa_s4xx_opaque_mac.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s4xx
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s4xx/include/common
  ${CMAKE_CURRENT_LIST_DIR}/./ele_s4xx/include/opaque
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DPSA_CRYPTO_DRIVER_ELE_S4XX
  )

endif()

else()

message(SEND_ERROR "component_psa_crypto_driver_ele_s4xx_psa_opaque dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()

