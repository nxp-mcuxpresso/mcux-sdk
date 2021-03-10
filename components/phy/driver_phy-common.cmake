if(NOT DRIVER_PHY-COMMON_INCLUDED)

    set(DRIVER_PHY-COMMON_INCLUDED true CACHE BOOL "driver_phy-common component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1052")
        include(driver_mdio-common)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1064")
        include(driver_mdio-common)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MK64F12")
        include(driver_mdio-common)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MK66F18")
        include(driver_mdio-common)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core0")
        include(driver_mdio-common)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core1")
        include(driver_mdio-common)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC54628")
        include(driver_mdio-common)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8QX6")
        include(driver_mdio-common)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1021")
        include(driver_mdio-common)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1062")
        include(driver_mdio-common)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC54S018")
        include(driver_mdio-common)
    endif()
    if(${MCUX_DEVICE} STREQUAL "LPC54S018M")
        include(driver_mdio-common)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1024")
        include(driver_mdio-common)
    endif()


endif()