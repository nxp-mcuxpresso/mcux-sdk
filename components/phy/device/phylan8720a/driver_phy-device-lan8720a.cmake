if(NOT DRIVER_PHY-DEVICE-LAN8720A_INCLUDED)

    set(DRIVER_PHY-DEVICE-LAN8720A_INCLUDED true CACHE BOOL "driver_phy-device-lan8720a component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_phylan8720a.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_phy-common)

endif()