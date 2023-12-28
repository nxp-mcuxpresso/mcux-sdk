#Description: Component els_pkc.hashmodes; user_visible: False
include_guard(GLOBAL)
message("component_els_pkc_hashmodes component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClHashModes/src/mcuxClHashModes_Core_els_sha2.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClHashModes/src/mcuxClHashModes_Internal_els_sha2.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClHashModes/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClHashModes/inc/internal
)


include(component_els_pkc_els)
