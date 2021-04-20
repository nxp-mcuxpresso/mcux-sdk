#Description: Flash Driver; user_visible: True
include_guard(GLOBAL)
message("driver_flash component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_ftfx_controller.c
    ${CMAKE_CURRENT_LIST_DIR}/fsl_ftfx_flash.c
    ${CMAKE_CURRENT_LIST_DIR}/fsl_ftfx_cache.c
    ${CMAKE_CURRENT_LIST_DIR}/fsl_ftfx_flexnvm.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_common)
