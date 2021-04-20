#Description: POWERQUAD Driver; user_visible: True
include_guard(GLOBAL)
message("driver_powerquad component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_powerquad_data.c
    ${CMAKE_CURRENT_LIST_DIR}/fsl_powerquad_basic.c
    ${CMAKE_CURRENT_LIST_DIR}/fsl_powerquad_math.c
    ${CMAKE_CURRENT_LIST_DIR}/fsl_powerquad_matrix.c
    ${CMAKE_CURRENT_LIST_DIR}/fsl_powerquad_filter.c
    ${CMAKE_CURRENT_LIST_DIR}/fsl_powerquad_transform.c
    ${CMAKE_CURRENT_LIST_DIR}/fsl_powerquad_cmsis.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_common)
