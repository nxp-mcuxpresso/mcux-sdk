#Description: SAI SDMA Driver; user_visible: True
include_guard(GLOBAL)
message("driver_sai_sdma component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_sai_sdma.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_sai)
include(driver_sdma)
