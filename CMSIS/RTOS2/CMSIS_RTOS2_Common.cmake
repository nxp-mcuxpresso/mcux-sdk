#Description: CMSIS RTOS2 Keil RTX5 Common; user_visible: False
include_guard(GLOBAL)
message("CMSIS_RTOS2_Common component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/RTX/Source/rtx_lib.c
    ${CMAKE_CURRENT_LIST_DIR}/RTX/Config/RTX_Config.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/RTX/Config
    ${CMAKE_CURRENT_LIST_DIR}/RTX/Include
    ${CMAKE_CURRENT_LIST_DIR}/RTX/Source
)


include(CMSIS_Device_API_OSTick)
include(CMSIS_Device_API_RTOS2)
