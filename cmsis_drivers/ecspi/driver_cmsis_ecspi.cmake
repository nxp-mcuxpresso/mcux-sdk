#Description: ECSPI CMSIS Driver; user_visible: True
include_guard(GLOBAL)
message("driver_cmsis_ecspi component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_ecspi_cmsis.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "MIMX8MQ6")
    include(driver_ecspi)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8MM6")
    include(driver_ecspi_sdma)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8MN6")
    include(driver_ecspi_sdma)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8ML8")
    include(driver_ecspi_sdma)
endif()

include(CMSIS_Driver_Include_SPI)
