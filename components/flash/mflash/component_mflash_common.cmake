#Description: statically allocated file system for mflash; user_visible: False
include_guard(GLOBAL)
message("component_mflash_common component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


