if(NOT DRIVER_LDB_COMBO_PHY_INCLUDED)

    set(DRIVER_LDB_COMBO_PHY_INCLUDED true CACHE BOOL "driver_ldb_combo_phy component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_ldb.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)

endif()