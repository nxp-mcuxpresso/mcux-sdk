#Description: Component prng; user_visible: False
include_guard(GLOBAL)
message("component_els_pkc_prng component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClPrng/src/mcuxClPrng_ELS.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClPrng/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClPrng/inc/internal
)


include(component_els_pkc_ecc)
include(component_els_pkc_math)
include(component_els_pkc_rsa)
