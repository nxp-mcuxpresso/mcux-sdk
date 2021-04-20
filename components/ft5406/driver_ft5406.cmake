#Description: Driver ft5406; user_visible: False
include_guard(GLOBAL)
message("driver_ft5406 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_ft5406.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_common)
