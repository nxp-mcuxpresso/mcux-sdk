#Description: Kinetis MMCAU security function library for Arm Cortex-M4 and Cortex-M7; user_visible: True
include_guard(GLOBAL)
message("middleware_mmcau_cm4_cm7 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "MKV58F24")
    include(middleware_mmcau_common_files)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1166_cm4")
    include(driver_clock)
endif()
if(${MCUX_DEVICE} STREQUAL "MK64F12")
    include(middleware_mmcau_common_files)
endif()
if(${MCUX_DEVICE} STREQUAL "MK66F18")
    include(middleware_mmcau_common_files)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1176_cm4")
    include(driver_clock)
endif()
if(${MCUX_DEVICE} STREQUAL "MCIMX7U5")
    include(middleware_mmcau_common_files)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core0")
    include(middleware_mmcau_common_files)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core1")
    include(middleware_mmcau_common_files)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8QX6")
    include(middleware_mmcau_common_files)
endif()
if(${MCUX_DEVICE} STREQUAL "MK28FA15")
    include(middleware_mmcau_common_files)
endif()

