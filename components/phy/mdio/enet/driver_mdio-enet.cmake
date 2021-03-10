if(NOT DRIVER_MDIO-ENET_INCLUDED)

    set(DRIVER_MDIO-ENET_INCLUDED true CACHE BOOL "driver_mdio-enet component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_enet_mdio.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )

    #OR Logic component
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1052")
        include(driver_enet_MIMXRT1052)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1064")
        include(driver_enet_MIMXRT1064)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MK64F12")
        include(driver_enet_MK64F12)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MK66F18")
        include(driver_enet_MK66F18)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core0")
        include(driver_enet_MIMX8QM6_cm4_core0)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8QM6_cm4_core1")
        include(driver_enet_MIMX8QM6_cm4_core1)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMX8QX6")
        include(driver_enet_MIMX8QX6)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1021")
        include(driver_enet_MIMXRT1021)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1062")
        include(driver_enet_MIMXRT1062)
    endif()
    if(${MCUX_DEVICE} STREQUAL "MIMXRT1024")
        include(driver_enet_MIMXRT1024)
    endif()

    include(driver_mdio-common)

endif()