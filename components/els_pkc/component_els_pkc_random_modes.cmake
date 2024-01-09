#Description: Component els_pkc.random_modes; user_visible: False
include_guard(GLOBAL)
message("component_els_pkc_random_modes component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRandomModes/src/mcuxClRandomModes_CtrDrbg.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRandomModes/src/mcuxClRandomModes_CtrDrbg_Els.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRandomModes/src/mcuxClRandomModes_CtrDrbg_PrDisabled.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRandomModes/src/mcuxClRandomModes_ElsMode.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRandomModes/src/mcuxClRandomModes_NormalMode.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRandomModes/src/mcuxClRandomModes_PrDisabled.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRandomModes/src/mcuxClRandomModes_PatchMode.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRandomModes/src/mcuxClRandomModes_TestMode.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRandomModes/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRandomModes/inc/internal
)


include(component_els_pkc_aes)
include(component_els_pkc_trng)
