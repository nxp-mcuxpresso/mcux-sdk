# Add set(CONFIG_USE_component_hal_pinctrl true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_driver_common AND CONFIG_USE_driver_iomuxc AND CONFIG_USE_component_sm_pinctrl AND (CONFIG_USE_component_hal_pinctrl_imx95))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/hal_pinctrl.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
)

else()

message(SEND_ERROR "component_hal_pinctrl dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
