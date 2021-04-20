#Description: Swm_connections Driver; user_visible: True
include_guard(GLOBAL)
message("driver_swm_connections component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_common)
