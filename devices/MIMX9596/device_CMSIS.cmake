# Add set(CONFIG_USE_device_CMSIS true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


if(${MCUX_DEVICE} STREQUAL "MIMX9596")
    include(CMSIS_Include_core_cm OPTIONAL)
endif()

if(${MCUX_DEVICE} STREQUAL "MIMX9596_ca55")
    include(CMSIS_Include_core_ca OPTIONAL)
endif()
