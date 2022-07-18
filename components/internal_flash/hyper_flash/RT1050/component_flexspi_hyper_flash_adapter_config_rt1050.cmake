#Description: Component flexspi_hyper_flash_adapter_rt1050_config; user_visible: False
include_guard(GLOBAL)
message("component_flexspi_hyper_flash_adapter_config_rt1050 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_adapter_flexspi_hyper_flash_config.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


