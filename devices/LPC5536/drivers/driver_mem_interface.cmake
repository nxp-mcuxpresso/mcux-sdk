#Description: ROMAPI MEM_INTERFACE Driver; user_visible: True
include_guard(GLOBAL)
message("driver_mem_interface component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/mem_interface/src/fsl_mem_interface.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/flash
    ${CMAKE_CURRENT_LIST_DIR}/mem_interface
    ${CMAKE_CURRENT_LIST_DIR}/nboot
)


include(driver_common)
