if(NOT DRIVER_MDIO-LPC-ENET_INCLUDED)

    set(DRIVER_MDIO-LPC-ENET_INCLUDED true CACHE BOOL "driver_mdio-lpc-enet component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_enet_mdio.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_lpc_enet)
    include(driver_mdio-common)

endif()