# Add set(CONFIG_USE_driver_srtm true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/srtm/srtm_channel.c
  ${CMAKE_CURRENT_LIST_DIR}/srtm/srtm_dispatcher.c
  ${CMAKE_CURRENT_LIST_DIR}/srtm/srtm_message.c
  ${CMAKE_CURRENT_LIST_DIR}/srtm/srtm_peercore.c
  ${CMAKE_CURRENT_LIST_DIR}/srtm/srtm_service.c
  ${CMAKE_CURRENT_LIST_DIR}/port/srtm_message_pool.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include
  ${CMAKE_CURRENT_LIST_DIR}/srtm
  ${CMAKE_CURRENT_LIST_DIR}/port
)

