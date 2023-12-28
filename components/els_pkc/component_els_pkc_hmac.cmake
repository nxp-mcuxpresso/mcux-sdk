#Description: Component els_pkc.hmac; user_visible: False
include_guard(GLOBAL)
message("component_els_pkc_hmac component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClHmac/src/mcuxClHmac_Els.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClHmac/src/mcuxClHmac_Functions.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClHmac/src/mcuxClHmac_Helper.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClHmac/src/mcuxClHmac_Modes.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClHmac/src/mcuxClHmac_KeyTypes.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClHmac/src/mcuxClHmac_Sw.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClHmac/inc
)


include(component_els_pkc_els)
