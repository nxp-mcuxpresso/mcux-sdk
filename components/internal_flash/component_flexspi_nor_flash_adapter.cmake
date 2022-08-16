#Description: Component flexspi_nor_flash_adapter; user_visible: True
include_guard(GLOBAL)
message("component_flexspi_nor_flash_adapter component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "MIMXRT1052")
    include(component_flexspi_hyper_flash_adapter)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1062")
    include(component_flexspi_nor_flash_adapter_rt1060evk)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1176_cm7")
    include(component_flexspi_nor_flash_adapter_rt1060evk)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1171_cm7")
    include(component_flexspi_nor_flash_adapter_rt1060evk)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1173_cm7")
    include(component_flexspi_nor_flash_adapter_rt1060evk)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1172_cm7")
    include(component_flexspi_nor_flash_adapter_rt1060evk)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1175_cm7")
    include(component_flexspi_nor_flash_adapter_rt1060evk)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT685S_cm33")
    include(component_flexspi_nor_flash_adapter_rt685evk)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT595S_cm33")
    include(component_flexspi_nor_flash_adapter_rt595evk)
endif()

