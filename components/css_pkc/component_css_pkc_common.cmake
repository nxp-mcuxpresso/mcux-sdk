#Description: Component css_pkc_common; user_visible: False
include_guard(GLOBAL)
message("component_css_pkc_common component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/platforms/fsl_css_pkc.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
    ${CMAKE_CURRENT_LIST_DIR}/src/compiler/iar
    ${CMAKE_CURRENT_LIST_DIR}/src/platforms
    ${CMAKE_CURRENT_LIST_DIR}/src/platforms/LPC55S3x/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/platforms/crypto_ip/inc/css/2.13.4
    ${CMAKE_CURRENT_LIST_DIR}/src/platforms/crypto_ip/inc/fame
)


