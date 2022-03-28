#Description: Component css_pkc_memory; user_visible: False
include_guard(GLOBAL)
message("component_css_pkc_memory component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMemory/src/mcuxClMemory.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxCsslMemory/src/mcuxCsslMemory_Clear.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxCsslMemory/src/mcuxCsslMemory_Compare.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxCsslMemory/src/mcuxCsslMemory_Copy.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMemory/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxCsslMemory/inc
)


include(component_css_pkc_param_integrity)
include(component_css_pkc_common)
