#Description: Driver display-mipi-dsi-cmd; user_visible: True
include_guard(GLOBAL)
message("driver_display-mipi-dsi-cmd component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_mipi_dsi_cmd.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "MIMXRT1166_cm4")
    include(driver_mipi_dsi_split)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1166_cm7")
    include(driver_mipi_dsi_split)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1176_cm4")
    include(driver_mipi_dsi_split)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1176_cm7")
    include(driver_mipi_dsi_split)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT595S_cm33")
    include(driver_mipi_dsi)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core1")
    include(driver_mipi_dsi)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8QX6")
    include(driver_mipi_dsi)
endif()

