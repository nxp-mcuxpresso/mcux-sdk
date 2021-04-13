function(mcux_import_kconfig kconfig_fragment)
  set(prefix "CONFIG_")
  if(NOT EXISTS ${kconfig_fragment})
    return()
  endif()
  message("Parsing .config file, adding modules to build:")
  # Parse the lines prefixed with 'prefix' in ${kconfig_fragment}
  file(
    STRINGS
    ${kconfig_fragment}
    DOT_CONFIG_LIST
    REGEX "^${prefix}"
    ENCODING "UTF-8"
  )

  foreach (CONFIG ${DOT_CONFIG_LIST})
    # CONFIG could look like: CONFIG_NET_BUF=y

    # Match the first part, the variable name
    # string(REGEX MATCH "[^=]+" CONF_VARIABLE_NAME ${CONFIG})
    string(REGEX MATCH "[^=]+" CONF_VARIABLE_NAME ${CONFIG})

    # Match the second part, variable value
    string(REGEX MATCH "=(.+$)" CONF_VARIABLE_VALUE ${CONFIG})
    # The variable name match we just did included the '=' symbol. To just get the
    # part on the RHS we use match group 1
    set(CONF_VARIABLE_VALUE ${CMAKE_MATCH_1})
    if(${CMAKE_MATCH_1} STREQUAL "y")
      set(CONF_VARIABLE_VALUE TRUE)
    endif()
    if(${CONF_VARIABLE_NAME} MATCHES "^CONFIG_MCUX_DEVICE")
      # remove quotation mark for device name
      string(REGEX MATCH "[0-9a-zA-Z_]+" DEVICE_NAME ${CONF_VARIABLE_VALUE})
      set(MCUX_DEVICE "${DEVICE_NAME}" PARENT_SCOPE)
    else()
      set("${CONF_VARIABLE_NAME}" "${CONF_VARIABLE_VALUE}" PARENT_SCOPE)
    endif()
  endforeach()
endfunction()

function(mcux_include_from_kconfig cmake_module)
  if(${CONFIG_USE_${cmake_module}})
   include(${cmake_module})
   message("    ${cmake_module}")
  endif()
endfunction()


