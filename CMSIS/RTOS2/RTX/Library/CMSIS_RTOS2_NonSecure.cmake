#Description: CMSIS RTOS2 Keil RTX5 Non Secure; user_visible: False
include_guard(GLOBAL)
message("CMSIS_RTOS2_NonSecure component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
)


include(CMSIS_RTOS2_Common)
