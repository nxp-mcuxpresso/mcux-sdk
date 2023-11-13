#Description: device_CMSIS; user_visible: False
include_guard(GLOBAL)
message("device_CMSIS component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


if(${MCUX_DEVICE} STREQUAL "MIMX8MN6")
endif()

if(${MCUX_DEVICE} STREQUAL "MIMX8MN6_ca53")
    include(CMSIS_Include_core_ca)
endif()
