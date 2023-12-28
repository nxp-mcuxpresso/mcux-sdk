#Description: Component osa_free_rtos; user_visible: True
include_guard(GLOBAL)
message("component_osa_free_rtos component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(component_osa_interface)
include(middleware_freertos-kernel_RW612)
