#Description: Component els_pkc; user_visible: False
include_guard(GLOBAL)
message("component_els_pkc component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/inc/impl
)


include(component_els_pkc_trng)
include(component_els_pkc_pkc)
