#Description: SOC FLEXRAM ALLOCATE Driver; user_visible: True
include_guard(GLOBAL)
message("driver_soc_flexram_allocate component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_flexram_allocate.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_common)
