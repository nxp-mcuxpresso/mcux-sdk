if(NOT DRIVER_PHY-DEVICE-AR8031_INCLUDED)

    set(DRIVER_PHY-DEVICE-AR8031_INCLUDED true CACHE BOOL "driver_phy-device-ar8031 component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_phyar8031.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core0")
        include(driver_phy-common)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core1")
        include(driver_phy-common)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8QX6")
        include(driver_phy-common)
    endif()


endif()