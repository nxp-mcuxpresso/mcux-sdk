#Description: I2C Freertos Driver; user_visible: True
include_guard(GLOBAL)
message("driver_ii2c_freertos component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_i2c_freertos.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "MIMX8MQ6")
    include(middleware_freertos-kernel_MIMX8MQ6)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8MM6")
    include(middleware_freertos-kernel_MIMX8MM6)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8MN6")
    include(middleware_freertos-kernel_MIMX8MN6)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8ML8")
    include(middleware_freertos-kernel_MIMX8ML8)
endif()

include(driver_ii2c)
