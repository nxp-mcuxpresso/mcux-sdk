#Description: Component power manager EVK-MIMXRT595; user_visible: True
include_guard(GLOBAL)
message("component_power_manager_evkmimxrt595 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_pm_board.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(component_power_manager_core)
