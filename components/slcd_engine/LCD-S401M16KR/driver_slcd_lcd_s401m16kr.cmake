#Description: Driver slcd_lcd_s401m16kr; user_visible: True
include_guard(GLOBAL)
message("driver_slcd_lcd_s401m16kr component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/LCD-S401M16KR.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


