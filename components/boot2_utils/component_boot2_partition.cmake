#Description: component_boot2_partition; user_visible: True
include_guard(GLOBAL)
message("component_boot2_partition component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/partition.c
    ${CMAKE_CURRENT_LIST_DIR}/crc32.c
    ${CMAKE_CURRENT_LIST_DIR}/boot_flags.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_common)
