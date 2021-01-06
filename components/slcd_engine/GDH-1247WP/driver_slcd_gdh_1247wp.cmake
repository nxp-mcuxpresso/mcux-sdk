if(NOT DRIVER_SLCD_GDH_1247WP_INCLUDED)

    set(DRIVER_SLCD_GDH_1247WP_INCLUDED true CACHE BOOL "driver_slcd_gdh_1247wp component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/GDH-1247WP.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )



endif()