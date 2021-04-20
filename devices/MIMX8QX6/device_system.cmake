#Description: device_system; user_visible: False
include_guard(GLOBAL)
message("device_system component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/system_MIMX8QX6_cm4.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(device_CMSIS)
