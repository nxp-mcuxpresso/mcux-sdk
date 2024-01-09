#Description: ROMAPI Driver; user_visible: True
include_guard(GLOBAL)
message("driver_romapi component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/bootloader/fsl_romapi.c
    ${CMAKE_CURRENT_LIST_DIR}/otp/fsl_romapi_otp.c
    ${CMAKE_CURRENT_LIST_DIR}/nboot/fsl_romapi_nboot.c
    ${CMAKE_CURRENT_LIST_DIR}/flexspi/fsl_romapi_flexspi.c
    ${CMAKE_CURRENT_LIST_DIR}/iap/fsl_romapi_iap.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/bootloader
    ${CMAKE_CURRENT_LIST_DIR}/flexspi
    ${CMAKE_CURRENT_LIST_DIR}/iap
    ${CMAKE_CURRENT_LIST_DIR}/nboot
    ${CMAKE_CURRENT_LIST_DIR}/otp
)


include(driver_common)
