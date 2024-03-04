include_guard()
message("device_MIMX9352_CMSIS component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/system_MIMX9352_cm33.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(CMSIS_Include_core_cm_MIMX9352 OPTIONAL)
