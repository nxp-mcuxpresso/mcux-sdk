#Description: Component osa; user_visible: True
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

if(CONFIG_USE_middleware_freertos-kernel_MIMXRT1166_cm4)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MIMXRT1166_cm7)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MIMXRT1052)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_MK22F12810)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MK22F12810)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_MIMXRT633S_cm33)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MIMXRT633S_cm33)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MIMXRT1064)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_LPC5526)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC5526)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_LPC54607)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC54607)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_LPC54S016)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC54S016)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_LPC54606)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC54606)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_LPC54616)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC54616)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_K32L2B31A)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_LPC54016)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC54016)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_LPC54018)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC54018)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC54628)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_LPC5512)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC5512)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MK22F51212)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_LPC5516)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC5516)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_LPC54605)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC54605)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_MIMXRT1051)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MIMXRT1051)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_LPC54618)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC54618)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MIMXRT1021)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_MIMXRT555S_cm33)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MIMXRT555S_cm33)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_LPC54018M)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC54018M)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_LPC5514)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC5514)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC55S16)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_K32L2B11A)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_K32L2B11A)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_MK02F12810)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MK02F12810)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MIMXRT1062)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC54S018)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_K32L3A60_cm4)
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

if(CONFIG_USE_middleware_freertos-kernel_LPC54S018M)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_MK22F25612)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MK22F25612)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_K32L2B21A)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_K32L2B21A)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC51U68)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_MIMXRT1061)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MIMXRT1061)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_LPC5528)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC5528)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_MIMXRT1165_cm4)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MIMXRT1165_cm4)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_MIMXRT1165_cm7)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MIMXRT1165_cm7)
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

if(CONFIG_USE_middleware_baremetal_LPC54S005)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC54S005)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC55S69_cm33_core0)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_K32L2A31A)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_K32L2A31A)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MIMXRT1024)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MIMXRT1011)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_LPC54005)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC54005)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC55S28)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_MIMXRT533S_cm33)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MIMXRT533S_cm33)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_LPC55S14)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC55S14)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_LPC55S26)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC55S26)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_K32L2A41A)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_baremetal_LPC54608)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC54608)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MIMXRT685S_cm33)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MIMXRT595S_cm33)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MIMXRT1015)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MK64F12)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MK66F18)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_LPC54114_cm4)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

if(CONFIG_USE_middleware_freertos-kernel_MKL27Z644)
target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_free_rtos.c
)
endif()

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(component_lists)
