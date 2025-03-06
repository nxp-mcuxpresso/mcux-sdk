# Add set(CONFIG_USE_component_hal_power_imx95 true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if((CONFIG_BOARD STREQUAL imx95lp4xevk15) OR (CONFIG_BOARD STREQUAL imx95lpd5evk19))

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
)

else()

message(SEND_ERROR "component_hal_power_imx95 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
