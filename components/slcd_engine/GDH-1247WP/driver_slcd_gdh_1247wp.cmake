#Description: Driver slcd_gdh_1247wp; user_visible: True
include_guard(GLOBAL)
message("driver_slcd_gdh_1247wp component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/GDH-1247WP.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


