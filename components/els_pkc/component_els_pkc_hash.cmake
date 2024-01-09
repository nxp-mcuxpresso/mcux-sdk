#Description: Component els_pkc.hash; user_visible: False
include_guard(GLOBAL)
message("component_els_pkc_hash component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClHash/src/mcuxClHash_api_multipart_common.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClHash/src/mcuxClHash_api_multipart_compute.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClHash/src/mcuxClHash_api_oneshot_compute.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClHash/inc
)


include(component_els_pkc_hashmodes)
