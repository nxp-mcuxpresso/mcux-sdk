#Description: Driver nand_flash-controller-semc; user_visible: True
include_guard(GLOBAL)
message("driver_nand_flash-controller-semc component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_semc_nand_flash.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_semc)
include(driver_nand_flash-common)
