#Description: Driver phy-device-lan8720a; user_visible: True
include_guard(GLOBAL)
message("driver_phy-device-lan8720a component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_phylan8720a.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "LPC54628")
    include(driver_phy-common_LPC54628)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54S018")
    include(driver_phy-common_LPC54S018)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54S018M")
    include(driver_phy-common_LPC54S018M)
endif()

