#Description: Driver silicon_id_imx8; user_visible: True
include_guard(GLOBAL)
message("component_silicon_id_imx8 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_silicon_id_soc.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/..
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "MIMX8MM6")
    include(component_silicon_id_MIMX8MM6)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8ML8")
    include(component_silicon_id_MIMX8ML8)
endif()

