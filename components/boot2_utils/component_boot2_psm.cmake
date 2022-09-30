#Description: component_boot2_psm; user_visible: True
include_guard(GLOBAL)
message("component_boot2_psm component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/psm-v2.c
    ${CMAKE_CURRENT_LIST_DIR}/psm-v2-secure.c
    ${CMAKE_CURRENT_LIST_DIR}/wmtlv.c
    ${CMAKE_CURRENT_LIST_DIR}/keystore.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(component_boot2_partition)
