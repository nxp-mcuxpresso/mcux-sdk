if(NOT DRIVER_CAMERA-DEVICE-OV7725_INCLUDED)

    set(DRIVER_CAMERA-DEVICE-OV7725_INCLUDED true CACHE BOOL "driver_camera-device-ov7725 component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_ov7725.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_camera-device-sccb)
    include(driver_camera-common)
    include(driver_video-common)
    include(driver_camera-device-common)

endif()