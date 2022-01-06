#Description: CMSIS Driver SPI; user_visible: False
include_guard(GLOBAL)
message("CMSIS_Driver_Include_SPI component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(CMSIS_Driver_Include_Common)
