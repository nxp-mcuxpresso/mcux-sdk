#Description: Driver nor_flash-common; user_visible: True
include_guard(GLOBAL)
message("driver_nor_flash-common component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


