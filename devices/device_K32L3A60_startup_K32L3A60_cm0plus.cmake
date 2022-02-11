#Description: Device K32L3A60_startup; user_visible: True
include_guard(GLOBAL)
message("device_K32L3A60_startup component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/K32L3A60/gcc/startup_K32L3A60_cm0plus.S
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
)


include(device_system_K32L3A60_cm0plus)
