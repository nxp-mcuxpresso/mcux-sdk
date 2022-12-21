#Description: Middleware issdk drivers systick_utils; user_visible: True
include_guard(GLOBAL)
message("middleware_issdk_drivers_systick_utils component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/drivers/systick/systick_utils.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/drivers/systick
)


