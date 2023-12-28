#Description: Component els_pkc.mac_modes; user_visible: False
include_guard(GLOBAL)
message("component_els_pkc_mac_modes component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMacModes/src/mcuxClMacModes.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMacModes/src/mcuxClMacModes_Els_Cbcmac.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMacModes/src/mcuxClMacModes_Els_Cmac.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMacModes/src/mcuxClMacModes_Els_Functions.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMacModes/src/mcuxClMacModes_Modes.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMacModes/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMacModes/inc/internal
)


include(component_els_pkc_mac)
