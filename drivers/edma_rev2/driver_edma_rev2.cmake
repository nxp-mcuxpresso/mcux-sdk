include_guard(GLOBAL)
message("driver_edma_rev2 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/fsl_edma_rev2.c)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/.)
