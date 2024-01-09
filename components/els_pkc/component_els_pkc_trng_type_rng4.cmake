#Description: Component els_pkc.trng.type_rng4; user_visible: False
include_guard(GLOBAL)
message("component_els_pkc_trng_type_rng4 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClTrng/src/mcuxClTrng_SA_TRNG.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClTrng/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClTrng/inc/internal
)


include(component_els_pkc_trng)
