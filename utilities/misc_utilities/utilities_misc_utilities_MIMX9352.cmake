#Description: utilities_misc_utilities; user_visible: True
include_guard(GLOBAL)
message("utilities_misc_utilities component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_sbrk.c
    ${CMAKE_CURRENT_LIST_DIR}/fsl_memcpy.S
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
)
