#Description: Driver nor_flash-controller-flexspi; user_visible: True
include_guard(GLOBAL)
message("driver_nor_flash-controller-flexspi component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_flexspi_nor_flash.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_flexspi)
include(driver_nor_flash-common)
