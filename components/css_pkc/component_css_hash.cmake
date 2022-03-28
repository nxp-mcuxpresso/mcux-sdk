#Description: Component css_hash; user_visible: True
include_guard(GLOBAL)
message("component_css_hash component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClHash/src/mcuxClHash.c
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClHash/src/mcuxClHash_Algorithms.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClHash/inc
)


include(component_css)
