#Description: els_pkc_rw61x_interface_files; user_visible: False
include_guard(GLOBAL)
message("component_els_pkc_platform_rw61x_interface_files component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/platforms/rw61x/mcux_els.c
    ${CMAKE_CURRENT_LIST_DIR}/src/platforms/rw61x/mcux_pkc.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/platforms/rw61x
    ${CMAKE_CURRENT_LIST_DIR}/src/platforms/rw61x/inc
)


