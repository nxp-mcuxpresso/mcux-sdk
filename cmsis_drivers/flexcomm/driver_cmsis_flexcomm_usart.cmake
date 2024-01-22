#Description: USART CMSIS Driver; user_visible: True
include_guard(GLOBAL)
message("driver_cmsis_flexcomm_usart component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_usart_cmsis.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_flexcomm_usart_dma)
include(CMSIS_Driver_Include_USART)
