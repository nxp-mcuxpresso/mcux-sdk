#Description: Component osa; user_visible: False
include_guard(GLOBAL)
message("component_osa component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

#OR Logic component
if(CONFIG_USE_middleware_baremetal)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_RW612)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MK22F51212)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MIMXRT1062)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MIMXRT1042)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MIMXRT1176_cm4)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MIMXRT1176_cm7)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_LPC55S66_cm33_core0)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC55S66_cm33_core0)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC55S69_cm33_core0)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MIMXRT595S_cm33)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(component_lists)
