#Description: Utility str; user_visible: True
include_guard(GLOBAL)
message("utility_str component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/str/fsl_str.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/str
)


include(driver_common)
