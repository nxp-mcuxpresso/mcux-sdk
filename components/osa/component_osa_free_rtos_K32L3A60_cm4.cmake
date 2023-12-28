#Description: Component osa_free_rtos; user_visible: False
include_guard(GLOBAL)
message("component_osa_free_rtos component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(component_lists)
include(middleware_freertos-kernel_K32L3A60_cm4)
