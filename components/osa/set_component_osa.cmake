include_guard(GLOBAL)


if (CONFIG_USE_component_osa_zephyr)
# Add set(CONFIG_USE_component_osa_zephyr true) in config.cmake to use this component

message("component_osa_zephyr component is included from ${CMAKE_CURRENT_LIST_FILE}.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./fsl_os_abstraction_zephyr.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)


endif()


if (CONFIG_USE_component_common_task)
# Add set(CONFIG_USE_component_common_task true) in config.cmake to use this component

message("component_common_task component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_component_osa)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../common_task/fsl_component_common_task.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../common_task/.
)

else()

message(SEND_ERROR "component_common_task dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_osa_bm)
# Add set(CONFIG_USE_component_osa_bm true) in config.cmake to use this component

message("component_osa_bm component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_component_lists AND CONFIG_USE_component_osa_interface)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./fsl_os_abstraction_bm.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)

else()

message(SEND_ERROR "component_osa_bm dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_osa_free_rtos)
# Add set(CONFIG_USE_component_osa_free_rtos true) in config.cmake to use this component

message("component_osa_free_rtos component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_middleware_freertos-kernel AND CONFIG_USE_driver_common AND CONFIG_USE_component_lists AND CONFIG_USE_component_osa_interface)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./fsl_os_abstraction_free_rtos.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)

else()

message(SEND_ERROR "component_osa_free_rtos dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_osa)
# Add set(CONFIG_USE_component_osa true) in config.cmake to use this component

message("component_osa component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_component_lists)

if(CONFIG_USE_middleware_baremetal)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/./fsl_os_abstraction_bm.c
  )
endif()

if(CONFIG_USE_middleware_freertos-kernel)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/./fsl_os_abstraction_free_rtos.c
  )
endif()

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)

else()

message(SEND_ERROR "component_osa dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_osa_interface)
# Add set(CONFIG_USE_component_osa_interface true) in config.cmake to use this component

message("component_osa_interface component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_component_lists)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)

else()

message(SEND_ERROR "component_osa_interface dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_osa_thread)
# Add set(CONFIG_USE_component_osa_thread true) in config.cmake to use this component

message("component_osa_thread component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_component_lists AND CONFIG_USE_component_osa_interface AND (CONFIG_USE_middleware_azure_rtos_tx OR CONFIG_USE_middleware_azure_rtos_tx_sp))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./fsl_os_abstraction_threadx.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)

else()

message(SEND_ERROR "component_osa_thread dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_component_common_task)
# Add set(CONFIG_USE_component_common_task true) in config.cmake to use this component

message("component_common_task component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common AND CONFIG_USE_component_osa)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/../common_task/fsl_component_common_task.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/../common_task/.
)

else()

message(SEND_ERROR "component_common_task dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()

