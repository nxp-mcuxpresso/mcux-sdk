#Description: device_CMSIS; user_visible: False
include_guard(GLOBAL)
message("device_CMSIS component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/system_MIMXRT595S_cm33.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(CMSIS_Include_core_cm)
