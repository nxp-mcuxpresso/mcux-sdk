#Description: MIPI DSI Driver; user_visible: True
include_guard(GLOBAL)
message("driver_mipi_dsi component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_mipi_dsi.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "MIMXRT595S_cm33")
    include(driver_soc_mipi_dsi)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core1")
    include(driver_common)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8QX6")
    include(driver_common)
endif()

