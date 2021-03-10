if(NOT DRIVER_PRINCE_INCLUDED)

    set(DRIVER_PRINCE_INCLUDED true CACHE BOOL "driver_prince component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_prince.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_puf)
    include(driver_common)
    include(driver_iap1)

endif()