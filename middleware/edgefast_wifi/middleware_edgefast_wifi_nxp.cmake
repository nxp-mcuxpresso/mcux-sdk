#Description: Middleware Edgefast Wi-Fi NXP; user_visible: True
include_guard(GLOBAL)
message("middleware_edgefast_wifi_nxp component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/source/wpl_nxp.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
)


include(middleware_edgefast_wifi)
