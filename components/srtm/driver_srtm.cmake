#Description: Driver srtm; user_visible: True
include_guard(GLOBAL)
message("driver_srtm component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/srtm/srtm_channel.c
    ${CMAKE_CURRENT_LIST_DIR}/srtm/srtm_dispatcher.c
    ${CMAKE_CURRENT_LIST_DIR}/srtm/srtm_message.c
    ${CMAKE_CURRENT_LIST_DIR}/srtm/srtm_peercore.c
    ${CMAKE_CURRENT_LIST_DIR}/srtm/srtm_service.c
    ${CMAKE_CURRENT_LIST_DIR}/port/srtm_message_pool.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/srtm
)


