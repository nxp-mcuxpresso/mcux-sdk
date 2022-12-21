#Description: Component flexspi_nor_flash_adapter_rt1040evk; user_visible: True
include_guard(GLOBAL)
message("component_flexspi_nor_flash_adapter_rt1040evk component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/evkmimxrt1040/fsl_adapter_flexspi_nor_flash.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_flexspi)
