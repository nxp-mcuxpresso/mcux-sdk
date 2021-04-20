#Description: Cmsis_driver_include common; user_visible: False
include_guard(GLOBAL)
message("CMSIS_Driver_Include_Common component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


