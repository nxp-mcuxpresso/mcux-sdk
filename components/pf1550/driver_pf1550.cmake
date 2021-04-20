#Description: Driver pf1550; user_visible: True
include_guard(GLOBAL)
message("driver_pf1550 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_pf1550.c
    ${CMAKE_CURRENT_LIST_DIR}/fsl_pf1550_charger.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


