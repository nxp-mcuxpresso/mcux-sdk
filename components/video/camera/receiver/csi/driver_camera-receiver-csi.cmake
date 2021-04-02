if(NOT DRIVER_CAMERA-RECEIVER-CSI_INCLUDED)

    set(DRIVER_CAMERA-RECEIVER-CSI_INCLUDED true CACHE BOOL "driver_camera-receiver-csi component is included.")

    target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/fsl_csi_camera_adapter.c
    )

    target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/.
    )


    include(driver_csi)
    include(driver_camera-receiver-common)

endif()