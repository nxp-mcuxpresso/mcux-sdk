#Description: Component els_pkc.random; user_visible: False
include_guard(GLOBAL)
message("component_els_pkc_random component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRandom/src/mcuxClRandom_DRBG.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRandom/src/mcuxClRandom_PRNG.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRandom/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRandom/inc/internal
)


include(component_els_pkc_random_modes)
include(component_els_pkc_prng)
