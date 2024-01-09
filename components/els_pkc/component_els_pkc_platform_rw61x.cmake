#Description: els_pkc_rw61x; user_visible: True
include_guard(GLOBAL)
message("component_els_pkc_platform_rw61x component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/platforms/rw61x
)


include(component_els_pkc_platform_rw61x_interface_files)
include(component_els_pkc_trng_type_rng4)
include(component_els_pkc)
