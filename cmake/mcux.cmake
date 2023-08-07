# SPDX-License-Identifier: BSD-3-Clause

set(PROJECT_ROOT ${SdkRootDirPath}/core)
#set(KCONFIG_ROOT ${SdkRootDirPath}/core/Kconfig)
string(REGEX MATCH "examples/([^/]+)/" BOARD_VAR ${CMAKE_SOURCE_DIR})
set(BOARD ${CMAKE_MATCH_1})
set(BOARD_DIR ${SdkRootDirPath}/core/boards/${BOARD})
set(KCONFIG_ROOT ${SdkRootDirPath}/core/Kconfig)

message("PROJECT_ROOT ${CMAKE_SOURCE_DIR}")

if(NOT DEFINED APPLICATION_SOURCE_DIR)
set(APPLICATION_SOURCE_DIR ${CMAKE_SOURCE_DIR} CACHE PATH
    "Application Source Directory"
)
endif()

message("APPLICATION_SOURCE_DIR ${APPLICATION_SOURCE_DIR}")

if(DEFINED APPLICATION_BINARY_DIR)
unset(APPLICATION_BINARY_DIR)
unset(APPLICATION_BINARY_DIR CACHE)
endif()

set(APPLICATION_BINARY_DIR ${CMAKE_SOURCE_DIR}/build CACHE PATH
    "Application Binary Directory"
)

set(AUTOCONF_H ${APPLICATION_BINARY_DIR}/kconfig/include/generated/autoconf.h)

message("APPLICATION_BINARY_DIR ${APPLICATION_BINARY_DIR}")

function(import_kconfig prefix kconfig_fragment)
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
    string(REGEX MATCH "[^=]+" CONF_VARIABLE_NAME ${CONFIG})

    # Match the second part, variable value
    string(REGEX MATCH "=(.+$)" CONF_VARIABLE_VALUE ${CONFIG})
    # The variable name match we just did included the '=' symbol. To just get the
    # part on the RHS we use match group 1
    set(CONF_VARIABLE_VALUE ${CMAKE_MATCH_1})

    if("${CONF_VARIABLE_VALUE}" MATCHES "^\"(.*)\"$") # Is surrounded by quotes
      set(CONF_VARIABLE_VALUE ${CMAKE_MATCH_1})
    endif()

    set("${CONF_VARIABLE_NAME}" "${CONF_VARIABLE_VALUE}" PARENT_SCOPE)
    list(APPEND keys "${CONF_VARIABLE_NAME}")
  endforeach()

  foreach(outvar ${ARGN})
    set(${outvar} "${keys}" PARENT_SCOPE)
  endforeach()
endfunction()

include(${SdkRootDirPath}/core/cmake/python.cmake)
include(${SdkRootDirPath}/core/cmake/kconfig.cmake)

