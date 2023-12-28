#Description: Component els_pkc.mac; user_visible: False
include_guard(GLOBAL)
message("component_els_pkc_mac component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMac/src/mcuxClMac.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMac/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMac/inc/internal
)


include(component_els_pkc_toolchain)
include(component_els_pkc_padding)
include(component_els_pkc_key)
