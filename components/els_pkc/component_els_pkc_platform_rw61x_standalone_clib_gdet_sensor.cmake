#Description: els_pkc_standalone_clib_gdet_sensor; user_visible: False
include_guard(GLOBAL)
message("component_els_pkc_platform_rw61x_standalone_clib_gdet_sensor component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/platforms/rw61x
)


include(component_els_pkc_els_common)
include(component_els_pkc_standalone_gdet)
include(component_els_pkc_standalone_keyManagement)
include(component_els_pkc_platform_rw61x_interface_files)
