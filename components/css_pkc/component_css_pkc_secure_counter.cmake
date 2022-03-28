#Description: Component css_pkc_secure_counter; user_visible: True
include_guard(GLOBAL)
message("component_css_pkc_secure_counter component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxCsslSecureCounter/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxCsslSecureCounter/inc/internal
)


