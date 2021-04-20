#Description: UTICK Driver; user_visible: True
include_guard(GLOBAL)
message("driver_utick component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_utick.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "LPC54114_cm4")
    include(driver_common)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54628")
    include(driver_common)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC55S16")
    include(driver_common)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54S018")
    include(driver_common)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54S018M")
    include(driver_common)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC51U68")
    include(driver_common)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC55S69_cm33_core0")
    include(driver_common)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC55S28")
    include(driver_common)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT685S_cm33")
    include(driver_power)
endif()

