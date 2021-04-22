#Description: RTC Driver; user_visible: True
include_guard(GLOBAL)
message("driver_sc_event component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_sc_event.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_scfw_api)
include(driver_mu)
