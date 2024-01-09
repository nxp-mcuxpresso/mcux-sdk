#Description: Component flexspi_hyper_flash_adapter; user_visible: True
include_guard(GLOBAL)
message("component_flexspi_hyper_flash_adapter component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_adapter_flexspi_hyper_nor_flash.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(component_flexspi_nor_flash_adapter)
include(driver_flexspi)
include(component_flexspi_hyper_flash_adapter_config_rt1050)
