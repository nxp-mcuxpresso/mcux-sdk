#Description: Driver camera-receiver-isi; user_visible: True
include_guard(GLOBAL)
message("driver_camera-receiver-isi component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_isi_camera_adapter.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_isi)
include(driver_camera-receiver-common)
