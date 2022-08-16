#Description: device_startup; user_visible: False
include_guard(GLOBAL)
message("device_startup component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/gcc/startup_MKV56F24.S
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
)


include(device_system)
