# Add set(CONFIG_USE_component_sm_imx95_ca55 true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if((CONFIG_BOARD STREQUAL imx95lpd5evk19) AND CONFIG_USE_driver_mu1 AND CONFIG_USE_component_sm_smt AND CONFIG_USE_component_sm_crc AND CONFIG_USE_component_sm_scmi)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/sm_platform.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
)

else()

message(SEND_ERROR "component_sm_imx95_ca55 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
