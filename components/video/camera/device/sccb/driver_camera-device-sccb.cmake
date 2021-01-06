if(NOT DRIVER_CAMERA-DEVICE-SCCB_INCLUDED)

    set(DRIVER_CAMERA-DEVICE-SCCB_INCLUDED true CACHE BOOL "driver_camera-device-sccb component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_sccb.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_common)

endif()