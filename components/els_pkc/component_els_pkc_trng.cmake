#Description: Component els_pkc.trng; user_visible: False
include_guard(GLOBAL)
message("component_els_pkc_trng component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClTrng/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClTrng/inc/internal
)


include(component_els_pkc_memory)
include(component_els_pkc_els)
