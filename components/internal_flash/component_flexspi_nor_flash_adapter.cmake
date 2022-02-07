#Description: Component flexspi_nor_flash_adapter; user_visible: True
include_guard(GLOBAL)
message("component_flexspi_nor_flash_adapter component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(component_flexspi_nor_flash_adapter_rt1060evk)
