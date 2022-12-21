#Description: Driver phy-device-ar8031; user_visible: True
include_guard(GLOBAL)
message("driver_phy-device-ar8031 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_phyar8031.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "MIMX8MM6")
    include(driver_phy-common_MIMX8MM6)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core0")
    include(driver_phy-common_MIMX8QM6_cm4_core0)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core1")
    include(driver_phy-common_MIMX8QM6_cm4_core1)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMX8QX6")
    include(driver_phy-common_MIMX8QX6)
endif()

