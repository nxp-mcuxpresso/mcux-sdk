include_guard(GLOBAL)


if (CONFIG_USE_middleware_mmcau_mmcau_files)
# Add set(CONFIG_USE_middleware_mmcau_mmcau_files true) in config.cmake to use this component

message("middleware_mmcau_mmcau_files component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_CORE STREQUAL cm0p)
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/./asm-cm0p/src/mmcau_aes_functions.s
      ${CMAKE_CURRENT_LIST_DIR}/./asm-cm0p/src/mmcau_des_functions.s
      ${CMAKE_CURRENT_LIST_DIR}/./asm-cm0p/src/mmcau_md5_functions.s
      ${CMAKE_CURRENT_LIST_DIR}/./asm-cm0p/src/mmcau_sha1_functions.s
      ${CMAKE_CURRENT_LIST_DIR}/./asm-cm0p/src/mmcau_sha256_functions.s
  )
endif()

if((CONFIG_CORE STREQUAL cm4f OR CONFIG_CORE STREQUAL cm7f))
  target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/./asm-cm4-cm7/src/mmcau_aes_functions.s
      ${CMAKE_CURRENT_LIST_DIR}/./asm-cm4-cm7/src/mmcau_des_functions.s
      ${CMAKE_CURRENT_LIST_DIR}/./asm-cm4-cm7/src/mmcau_md5_functions.s
      ${CMAKE_CURRENT_LIST_DIR}/./asm-cm4-cm7/src/mmcau_sha1_functions.s
      ${CMAKE_CURRENT_LIST_DIR}/./asm-cm4-cm7/src/mmcau_sha256_functions.s
  )
endif()


endif()


if (CONFIG_USE_middleware_mmcau_cm4_cm7)
# Add set(CONFIG_USE_middleware_mmcau_cm4_cm7 true) in config.cmake to use this component

message("middleware_mmcau_cm4_cm7 component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_CORE STREQUAL cm4f OR CONFIG_CORE STREQUAL cm7f) AND CONFIG_USE_middleware_mmcau_common_files AND CONFIG_USE_driver_clock AND CONFIG_USE_driver_common)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)

if((CONFIG_TOOLCHAIN STREQUAL armgcc OR CONFIG_TOOLCHAIN STREQUAL mcux))
  target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE
    -Wl,--start-group
      ${CMAKE_CURRENT_LIST_DIR}/./asm-cm4-cm7/lib_mmcau.a
      -Wl,--end-group
  )
endif()

else()

message(SEND_ERROR "middleware_mmcau_cm4_cm7 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_mmcau_cm0p)
# Add set(CONFIG_USE_middleware_mmcau_cm0p true) in config.cmake to use this component

message("middleware_mmcau_cm0p component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if((CONFIG_CORE STREQUAL cm0p) AND CONFIG_USE_middleware_mmcau_common_files AND CONFIG_USE_driver_clock AND CONFIG_USE_driver_common)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)

if((CONFIG_TOOLCHAIN STREQUAL armgcc OR CONFIG_TOOLCHAIN STREQUAL mcux))
  target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE
    -Wl,--start-group
      ${CMAKE_CURRENT_LIST_DIR}/./asm-cm0p/lib_mmcau-cm0p.a
      -Wl,--end-group
  )
endif()

else()

message(SEND_ERROR "middleware_mmcau_cm0p dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()


if (CONFIG_USE_middleware_mmcau_common_files)
# Add set(CONFIG_USE_middleware_mmcau_common_files true) in config.cmake to use this component

message("middleware_mmcau_common_files component is included from ${CMAKE_CURRENT_LIST_FILE}.")

if(CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/./fsl_mmcau.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/./.
)

else()

message(SEND_ERROR "middleware_mmcau_common_files dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()

endif()

