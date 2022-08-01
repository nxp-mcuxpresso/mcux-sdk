#Description: driver_powerquad_cmsis; user_visible: True
include_guard(GLOBAL)
message("driver_powerquad_cmsis component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_powerquad_cmsis.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_powerquad)
include(CMSIS_DSP_Include)
