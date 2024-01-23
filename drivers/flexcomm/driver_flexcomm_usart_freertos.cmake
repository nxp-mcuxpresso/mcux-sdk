#Description: FLEXCOMM USART FREERTOS Driver; user_visible: True
include_guard(GLOBAL)
message("driver_flexcomm_usart_freertos component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/usart/fsl_usart_freertos.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/usart/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "RW612")
    include(middleware_freertos-kernel_RW612)
endif()
if(${MCUX_DEVICE} STREQUAL "RW610")
    include(middleware_freertos-kernel_RW612)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC5506CPXXXX")
    include(middleware_freertos-kernel_LPC5506CPXXXX)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC55S66_cm33_core0")
    include(middleware_freertos-kernel_LPC55S69_cm33_core0)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC55S69_cm33_core0")
    include(middleware_freertos-kernel_LPC55S69_cm33_core0)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT595S_cm33")
    include(middleware_freertos-kernel_MIMXRT595S_cm33)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC5502")
    include(middleware_freertos-kernel_LPC55S06)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54114_cm4")
    include(middleware_freertos-kernel_LPC54114_cm4)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54113_cm4")
    include(middleware_freertos-kernel_LPC54114_cm4)
endif()

include(driver_flexcomm_usart)
