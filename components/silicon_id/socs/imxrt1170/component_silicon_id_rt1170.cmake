#Description: Driver silicon_id_rt1170; user_visible: True
include_guard(GLOBAL)
message("component_silicon_id_rt1170 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_silicon_id_soc.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/..
)


include(component_silicon_id)
