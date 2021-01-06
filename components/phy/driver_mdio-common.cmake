if(NOT DRIVER_MDIO-COMMON_INCLUDED)

    set(DRIVER_MDIO-COMMON_INCLUDED true CACHE BOOL "driver_mdio-common component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)

endif()