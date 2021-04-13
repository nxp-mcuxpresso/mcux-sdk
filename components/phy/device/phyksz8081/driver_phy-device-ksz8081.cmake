if(NOT DRIVER_PHY-DEVICE-KSZ8081_INCLUDED)

    set(DRIVER_PHY-DEVICE-KSZ8081_INCLUDED true CACHE BOOL "driver_phy-device-ksz8081 component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_phyksz8081.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_phy-common)

endif()