#Description: Component pkc; user_visible: False
include_guard(GLOBAL)
message("component_els_pkc_pkc component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClPkc/src/mcuxClPkc_Calculate.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClPkc/src/mcuxClPkc_ImportExport.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClPkc/src/mcuxClPkc_Initialize.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClPkc/src/mcuxClPkc_UPTRT.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClPkc/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClPkc/inc/internal
)


include(component_els_pkc_ecc)
include(component_els_pkc_math)
include(component_els_pkc_rsa)
