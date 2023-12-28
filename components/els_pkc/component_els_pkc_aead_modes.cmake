#Description: Component els_pkc.aead_modes; user_visible: False
include_guard(GLOBAL)
message("component_els_pkc_aead_modes component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClAeadModes/src/mcuxClAeadModes_Els_AesCcm.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClAeadModes/src/mcuxClAeadModes_Els_AesGcm.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClAeadModes/src/mcuxClAeadModes_Els_CcmEngineAes.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClAeadModes/src/mcuxClAeadModes_Els_Modes.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClAeadModes/src/mcuxClAeadModes_Els_GcmEngineAes.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClAeadModes/src/mcuxClAeadModes_Els_Multipart.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClAeadModes/src/mcuxClAeadModes_Els_Oneshot.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClAeadModes/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClAeadModes/inc/internal
)


include(component_els_pkc_aead)
