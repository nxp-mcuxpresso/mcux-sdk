#Description: Utilities unity; user_visible: True
include_guard(GLOBAL)
message("utilities_unity component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/unity.c
    ${CMAKE_CURRENT_LIST_DIR}/gcov_support.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


