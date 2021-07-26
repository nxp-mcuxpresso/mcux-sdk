/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef __FSL_COMPONENT_LOG_CONFIG_H__
#define __FSL_COMPONENT_LOG_CONFIG_H__

/*!
 * @addtogroup fsl_component_log_config
 * @ingroup fsl_component_log
 * @{
 */

/*!
 * @brief Whether to enable the log feature in the specific module, 1 - enable, 0 - disable.
 * @details The feature is used to configure the log feature for the specific module.
 * There are three steps should be followed to use the log component in specfic module,
 *
 *   step 1, define the macro LOG_ENABLE, likes as,
 *     @code
 *     #define LOG_ENABLE 1
 *     @endcode
 *     @note LOG_ENABLE could be re-defined as a MODULE enabled flag such as,
 *     @code
 *     #define LOG_ENABLE module_LOG_ENABLED_FLAG
 *     @endcode
 *
 *   step 2, include the log component header file, likes as,
 *     @code
 *     #include "fsl_component_log.h"
 *     @endcode
 *   step 3, define the log module by using macro LOG_MODULE_DEFINE, likes as,
 *     @code
 *     LOG_MODULE_DEFINE(<module name>, <module log level>);
 *     @endcode
 *
 * @note The code block should be placed at the end of the header file including of the source code.
 *
 *   For example,
 *   In source file 1,
 *     @code
 *     #define LOG_ENABLE MODULE1_CONFIG_LOG_ENABLE
 *     #include "fsl_component_log.h"
 *     LOG_MODULE_DEFINE(module1, kLOG_LevelTrace);
 *     @endcode
 *   In source file 2,
 *     @code
 *     #define LOG_ENABLE MODULE2_CONFIG_LOG_ENABLE
 *     #include "fsl_component_log.h"
 *     LOG_MODULE_DEFINE(module2, kLOG_LevelDebug);
 *     @endcode
 */
#ifndef LOG_ENABLE
#define LOG_ENABLE 0
#endif

/*! @brief Whether enable log color global feature, 1 - enable, 0 - disable.
 *  @details The feature is used to configure the log color feature for all of log component.@n
 * The feature should be defined in project setting.@n
 * Below shows how to configure in your project if you want to disable the feature.@n
 * For IAR, right click project and select "Options", define it in "C/C++ Compiler->Preprocessor->Defined symbols".@n
 * For KEIL, click "Options for Target...", define it in "C/C++->Preprocessor Symbols->Define".@n
 * For ARMGCC, open CmakeLists.txt and add the following lines,@n
 * "SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DLOG_ENABLE_COLOR=0")" for debug target.@n
 * "SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DLOG_ENABLE_COLOR=0")" for release target.@n
 * For MCUxpresso, right click project and select "Properties", define it in "C/C++ Build->Settings->MCU C
 * Complier->Preprocessor".@n
 */
#ifndef LOG_ENABLE_COLOR
#define LOG_ENABLE_COLOR 1
#endif

/*! @brief Whether enable timestamp global feature for log, 1 - enable, 0 - disable.
 * @details The feature is used to configure the log timestamp feature for all of log component.@n
 * The feature should be defined in project setting.@n
 * Below shows how to configure in your project if you want to disable the feature.@n
 * For IAR, right click project and select "Options", define it in "C/C++ Compiler->Preprocessor->Defined symbols".@n
 * For KEIL, click "Options for Target...", define it in "C/C++->Preprocessor Symbols->Define".@n
 * For ARMGCC, open CmakeLists.txt and add the following lines,@n
 * "SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DLOG_ENABLE_TIMESTAMP=0")" for debug target.@n
 * "SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DLOG_ENABLE_TIMESTAMP=0")" for release target.@n
 * For MCUxpresso, right click project and select "Properties", define it in "C/C++ Build->Settings->MCU C
 * Complier->Preprocessor".@n
 */
#ifndef LOG_ENABLE_TIMESTAMP
#define LOG_ENABLE_TIMESTAMP 1
#endif

/*! @brief Whether enable source file name with path information global feature, 1 - enable, 0 - disable.
 * @details The feature is used to configure the source file name with path information feature for all of log
 * component.@n The feature should be defined in project setting.@n Below shows how to configure in your project if you
 * want to enable the feature.@n For IAR, right click project and select "Options", define it in "C/C++
 * Compiler->Preprocessor->Defined symbols".@n For KEIL, click "Options for Target...", define it in
 * "C/C++->Preprocessor Symbols->Define".@n For ARMGCC, open CmakeLists.txt and add the following lines,@n
 * "SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DLOG_ENABLE_FILE_WITH_PATH=1")" for debug target.@n
 * "SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DLOG_ENABLE_FILE_WITH_PATH=1")" for release target.@n
 * For MCUxpresso, right click project and select "Properties", define it in "C/C++ Build->Settings->MCU C
 * Complier->Preprocessor".@n
 */
#ifndef LOG_ENABLE_FILE_WITH_PATH
#define LOG_ENABLE_FILE_WITH_PATH 0
#endif

/*! @brief Set the max message length, the default value is 128.
 * @details The feature is used to set the max message length, the default value is 128.@n
 * The feature should be defined in project setting.@n Below shows how to configure in your project if you
 * want to enable the feature.@n For IAR, right click project and select "Options", define it in "C/C++
 * Compiler->Preprocessor->Defined symbols".@n For KEIL, click "Options for Target...", define it in
 * "C/C++->Preprocessor Symbols->Define".@n For ARMGCC, open CmakeLists.txt and add the following lines,@n
 * "SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DLOG_MAX_MEESSAGE_LENGTH=128")" for debug target.@n
 * "SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DLOG_MAX_MEESSAGE_LENGTH=128")" for release target.@n
 * For MCUxpresso, right click project and select "Properties", define it in "C/C++ Build->Settings->MCU C
 * Complier->Preprocessor".@n
 */
#ifndef LOG_MAX_MEESSAGE_LENGTH
#define LOG_MAX_MEESSAGE_LENGTH 128
#endif

/*! @brief Whether enable asynchronous log mode feature, 1 - enable, 0 - disable.
 * @details The feature is used to enable asynchronous log mode feature.@n
 * The feature should be defined in project setting.@n Below shows how to configure in your project if you
 * want to enable the feature.@n For IAR, right click project and select "Options", define it in "C/C++
 * Compiler->Preprocessor->Defined symbols".@n For KEIL, click "Options for Target...", define it in
 * "C/C++->Preprocessor Symbols->Define".@n For ARMGCC, open CmakeLists.txt and add the following lines,@n
 * "SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DLOG_ENABLE_ASYNC_MODE=1")" for debug target.@n
 * "SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DLOG_ENABLE_ASYNC_MODE=1")" for release target.@n
 * For MCUxpresso, right click project and select "Properties", define it in "C/C++ Build->Settings->MCU C
 * Complier->Preprocessor".@n
 */
#ifndef LOG_ENABLE_ASYNC_MODE
#define LOG_ENABLE_ASYNC_MODE 0
#endif

#if (LOG_ENABLE_ASYNC_MODE > 0)
/*! @brief Set the max argument count, the default value is 4.
 * @details The feature is used to set the max argument count.@n
 * The feature should be defined in project setting.@n Below shows how to configure in your project if you
 * want to change the default value.@n For IAR, right click project and select "Options", define it in "C/C++
 * Compiler->Preprocessor->Defined symbols".@n For KEIL, click "Options for Target...", define it in
 * "C/C++->Preprocessor Symbols->Define".@n For ARMGCC, open CmakeLists.txt and add the following lines,@n
 * "SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DLOG_MAX_ARGUMENT_COUNT=4")" for debug target.@n
 * "SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DLOG_MAX_ARGUMENT_COUNT=4")" for release target.@n
 * For MCUxpresso, right click project and select "Properties", define it in "C/C++ Build->Settings->MCU C
 * Complier->Preprocessor".@n
 */
#ifndef LOG_MAX_ARGUMENT_COUNT
#define LOG_MAX_ARGUMENT_COUNT 4
#endif

/*! @brief Set the max bufferred log count, the default value is 16.
 * @details The feature is used to set the max bufferred log count.@n
 * The feature should be defined in project setting.@n Below shows how to configure in your project if you
 * want to change the default value.@n For IAR, right click project and select "Options", define it in "C/C++
 * Compiler->Preprocessor->Defined symbols".@n For KEIL, click "Options for Target...", define it in
 * "C/C++->Preprocessor Symbols->Define".@n For ARMGCC, open CmakeLists.txt and add the following lines,@n
 * "SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DLOG_MAX_ARGUMENT_COUNT=4")" for debug target.@n
 * "SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DLOG_MAX_ARGUMENT_COUNT=4")" for release target.@n
 * For MCUxpresso, right click project and select "Properties", define it in "C/C++ Build->Settings->MCU C
 * Complier->Preprocessor".@n
 */
#ifndef LOG_MAX_BUFF_LOG_COUNT
#define LOG_MAX_BUFF_LOG_COUNT 16
#endif

/*! @brief Whether enable overwrite log feature in asynchronous mode, 1 - enable, 0 - disable.
 * @details The feature is used to enable overwrite log feature in asynchronous mode.@n
 * The feature should be defined in project setting.@n Below shows how to configure in your project if you
 * want to enable the feature.@n For IAR, right click project and select "Options", define it in "C/C++
 * Compiler->Preprocessor->Defined symbols".@n For KEIL, click "Options for Target...", define it in
 * "C/C++->Preprocessor Symbols->Define".@n For ARMGCC, open CmakeLists.txt and add the following lines,@n
 * "SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DLOG_ENABLE_ASYNC_MODE=1")" for debug target.@n
 * "SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DLOG_ENABLE_ASYNC_MODE=1")" for release target.@n
 * For MCUxpresso, right click project and select "Properties", define it in "C/C++ Build->Settings->MCU C
 * Complier->Preprocessor".@n
 */
#ifndef LOG_ENABLE_OVERWRITE
#define LOG_ENABLE_OVERWRITE 1
#endif
#endif

/*! @} */

#endif /* __FSL_COMPONENT_LOG_CONFIG_H__ */
