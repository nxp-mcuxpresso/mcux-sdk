/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef __FSL_COMPONENT_LOG_H__
#define __FSL_COMPONENT_LOG_H__

/* log component usage:
 *   step 1,
 *     #define LOG_ENABLE 1
 *   step 2,
 *     #include "fsl_component_log.h"
 *   step 3,
 *     LOG_MODULE_DEFINE(<module name>, <module log level>);
 *
 * Note: LOG_ENABLE could be re-defined as a MODULE enabled flag such as
 *       #define LOG_ENABLE module_LOG_ENABLED_FLAG
 *
 *   For example,
 *   In source file 1,
 *     #define LOG_ENABLE MODULE1_LOG_ENABLE
 *     #include "fsl_component_log.h"
 *     LOG_MODULE_DEFINE(module1, kLOG_LevelTrace);
 *   In source file 2,
 *     #define LOG_ENABLE MODULE2_LOG_ENABLE
 *     #include "fsl_component_log.h"
 *     LOG_MODULE_DEFINE(module2, kLOG_LevelDebug);
 */

#include "fsl_common.h"
#include "fsl_component_log_config.h"

/*!
 * @addtogroup fsl_component_log
 * @{
 */

#if defined(__cplusplus)
extern "C" {
#endif /* _cplusplus */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#if LOG_ENABLE_TIMESTAMP
#define LOG_TIMESTAMP_GET LOG_GetTimestamp()
#else
#define LOG_TIMESTAMP_GET 0
#endif

/*! @brief log error code*/
typedef enum _log_status
{
    kStatus_LOG_Success         = kStatus_Success,                  /*!< Success */
    kStatus_LOG_Error           = MAKE_STATUS(kStatusGroup_LOG, 1), /*!< Failed */
    kStatus_LOG_Initialized     = MAKE_STATUS(kStatusGroup_LOG, 2), /*!< Initialized */
    kStatus_LOG_Uninitialized   = MAKE_STATUS(kStatusGroup_LOG, 3), /*!< Uninitialized */
    kStatus_LOG_LackResource    = MAKE_STATUS(kStatusGroup_LOG, 4), /*!< Lack resource */
    kStatus_LOG_BackendExist    = MAKE_STATUS(kStatusGroup_LOG, 5), /*!< Backend exists */
    kStatus_LOG_BackendNotFound = MAKE_STATUS(kStatusGroup_LOG, 6), /*!< Backend not found */
} log_status_t;

#if LOG_ENABLE_FILE_WITH_PATH > 0
/*!
 * @brief Source file name definition
 * @details Define LOG_FILE_NAME with \__FILE\__ when config LOG_ENABLE_FILE_WITH_PATH is enabled.
 */
#define LOG_FILE_NAME __FILE__
#else
#define LOG_FILE_NAME_INTERCEPT(s, n)                                                           \
    ((sizeof(s) >= (n)) && (((s)[sizeof(s) - (n)] == '/') || ((s)[sizeof(s) - (n)] == '\\'))) ? \
        ((s) + sizeof(s) - ((n)-1))
#define LOG_FILE_NAME_RECURSIVE(f, s, n) \
    f(s, n) : f(s, n + 1) : f(s, n + 2) : f(s, n + 3) : f(s, n + 4) : f(s, n + 5) : f(s, n + 6) : f(s, n + 7)
#define LOG_FILE_NAME_SET(f, f1, s, n) \
    f(f1, s, n)                        \
        : f(f1, s, n + 8)              \
        : f(f1, s, n + 16)             \
        : f(f1, s, n + 24) : f(f1, s, n + 32) : f(f1, s, n + 40) : f(f1, s, n + 48) : f(f1, s, n + 56)
/*!
 * @brief Source file name definition
 * @details There is a macro \__BASE_FILE\__ could be used to get the current source file name in GCC. While
 * the macro is unsupported by IAR in default, the \__BASE_FILE\__ is same as \__FILE\__ in IAR.
 * To support the macro \__BASE_FILE\__, the extra option --no_path_in_file_macros should be added
 * for IAR. But on Keil, only the source file name cannot be got through the macro \__BASE_FILE\__.
 *
 * So, log component adds a macro LOG_FILE_NAME to get the current source file name during the
 * compilation phase, when config LOG_ENABLE_FILE_WITH_PATH is disabled.
 * There is a limitation, the length of file name should be not less than 2,
 * and the supported MAX length of file name is 66 bytes. Otherwise the original string of \__FILE\__
 * will be linked.
 */
#define LOG_FILE_NAME LOG_FILE_NAME_SET(LOG_FILE_NAME_RECURSIVE, LOG_FILE_NAME_INTERCEPT, __FILE__, 3) : __FILE__
#endif

#if (LOG_ENABLE_ASYNC_MODE > 0)

/* Define the log argument type */
#ifndef LOG_ARGUMENT_TYPE
#define LOG_ARGUMENT_TYPE unsigned long
#endif

/* Get the log argument count MACRO set. The max argument count is 16 for application. */
#define _LOG_COUNT_ARGUMENT(N0, N1, N2, N3, N4, N5, N6, N7, N8, N9, N10, N11, N12, N13, N14, N15, N16, N17, COUNT, \
                            ...)                                                                                   \
    COUNT
#define LOG_COUNT_ARGUMENT(...) \
    _LOG_COUNT_ARGUMENT(__VA_ARGS__, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define LOG_FORMAT_ARG(x) ((LOG_ARGUMENT_TYPE)(x))

#define LOG_LIST_ARGUMENT_1(arg, ...)  LOG_FORMAT_ARG(arg)
#define LOG_LIST_ARGUMENT_2(arg, ...)  LOG_FORMAT_ARG(arg), LOG_LIST_ARGUMENT_1(__VA_ARGS__)
#define LOG_LIST_ARGUMENT_3(arg, ...)  LOG_FORMAT_ARG(arg), LOG_LIST_ARGUMENT_2(__VA_ARGS__)
#define LOG_LIST_ARGUMENT_4(arg, ...)  LOG_FORMAT_ARG(arg), LOG_LIST_ARGUMENT_3(__VA_ARGS__)
#define LOG_LIST_ARGUMENT_5(arg, ...)  LOG_FORMAT_ARG(arg), LOG_LIST_ARGUMENT_4(__VA_ARGS__)
#define LOG_LIST_ARGUMENT_6(arg, ...)  LOG_FORMAT_ARG(arg), LOG_LIST_ARGUMENT_5(__VA_ARGS__)
#define LOG_LIST_ARGUMENT_7(arg, ...)  LOG_FORMAT_ARG(arg), LOG_LIST_ARGUMENT_6(__VA_ARGS__)
#define LOG_LIST_ARGUMENT_8(arg, ...)  LOG_FORMAT_ARG(arg), LOG_LIST_ARGUMENT_7(__VA_ARGS__)
#define LOG_LIST_ARGUMENT_9(arg, ...)  LOG_FORMAT_ARG(arg), LOG_LIST_ARGUMENT_8(__VA_ARGS__)
#define LOG_LIST_ARGUMENT_10(arg, ...) LOG_FORMAT_ARG(arg), LOG_LIST_ARGUMENT_9(__VA_ARGS__)
#define LOG_LIST_ARGUMENT_11(arg, ...) LOG_FORMAT_ARG(arg), LOG_LIST_ARGUMENT_10(__VA_ARGS__)
#define LOG_LIST_ARGUMENT_12(arg, ...) LOG_FORMAT_ARG(arg), LOG_LIST_ARGUMENT_11(__VA_ARGS__)
#define LOG_LIST_ARGUMENT_13(arg, ...) LOG_FORMAT_ARG(arg), LOG_LIST_ARGUMENT_12(__VA_ARGS__)
#define LOG_LIST_ARGUMENT_14(arg, ...) LOG_FORMAT_ARG(arg), LOG_LIST_ARGUMENT_13(__VA_ARGS__)
#define LOG_LIST_ARGUMENT_15(arg, ...) LOG_FORMAT_ARG(arg), LOG_LIST_ARGUMENT_14(__VA_ARGS__)
#define LOG_LIST_ARGUMENT_16(arg, ...) LOG_FORMAT_ARG(arg), LOG_LIST_ARGUMENT_15(__VA_ARGS__)
#define LOG_LIST_ARGUMENT_17(arg, ...) LOG_FORMAT_ARG(arg), LOG_LIST_ARGUMENT_16(__VA_ARGS__)
#define LOG_LIST_ARGUMENT_18(arg, ...) LOG_FORMAT_ARG(arg), LOG_LIST_ARGUMENT_17(__VA_ARGS__)

#define _LOG_LIST_ARGUMENT_CAT(macro, sub) macro##sub
#define LOG_LIST_ARGUMENT_CAT(macro, sub)  _LOG_LIST_ARGUMENT_CAT(macro, sub)
#define LOG_LIST_ARGUMENT(...)             LOG_LIST_ARGUMENT_CAT(LOG_LIST_ARGUMENT_, LOG_COUNT_ARGUMENT(__VA_ARGS__))(__VA_ARGS__)

#endif

/*!
 * @brief log level definition
 *
 * @details The log level behavior is following,@n
 * If level is kLOG_LevelTrace, trace, debug, info, warning, error, and fatal of log level will be printed.@n
 * If level is kLOG_LevelDebug, debug, info, warning, error, and fatal of log level will be printed.@n
 * If level is kLOG_LevelInfo, info, warning, error, and fatal of log level will be printed.@n
 * If level is kLOG_LevelWarning, warning, error, and fatal of log level will be printed.@n
 * If level is kLOG_LevelError, error, and fatal of log level will be printed.@n
 * If level is kLOG_LevelFatal, only fatal of log level will be printed.@n
 * If level is kLOG_LevelNone, no log level will be printed.@n
 */
typedef enum log_level
{
    kLOG_LevelNone = 0, /*!< LOG level none */
    kLOG_LevelFatal,    /*!< LOG level fatal */
    kLOG_LevelError,    /*!< LOG level error */
    kLOG_LevelWarning,  /*!< LOG level warning */
    kLOG_LevelInfo,     /*!< LOG level info */
    kLOG_LevelDebug,    /*!< LOG level debug */
    kLOG_LevelTrace,    /*!< LOG level trace */
} log_level_t;

/*!
 * @brief log module type
 */
typedef struct log_module
{
    const char *logModuleName; /*!< Log module name */
    log_level_t level;         /*!< Log level of the module */
} log_module_t;

/*!
 * @brief Puts function type for log backend.
 */
typedef void (*log_backend_puts_t)(uint8_t *buffer, size_t length);

/*!
 * @brief Gets dump buffer from log backend.
 */
typedef log_status_t (*log_backend_get_dump_buffer_t)(uint8_t **buffer, size_t *length);

/*!
 * @brief Backend of log
 *
 */
typedef struct log_backend
{
    struct log_backend *next;  /*!< Next log backend pointer */
    log_backend_puts_t putStr; /*!< Put data function of log backend */
} log_backend_t;

/*!
 * @brief Defines the log backend
 *
 * @details This macro is used to define the log backend. The static global variable with
 * parameter name is defined by the macro. And calling the function
 * log_backend_register to register the backend with defined static global
 * variable.
 * For example, if there is a backend named test, the reference code is following,
 * @code
 *   static void puts(uint8_t *buffer, size_t length)
 *   {
 *       ...
 *   }
 *   LOG_BACKEND_DEFINE(test, puts);
 * @endcode
 *
 * @param name The name of the log backend.
 * @param puts The log string output function with log_backend_puts_t type.
 */
#define LOG_BACKEND_DEFINE(name, puts) static log_backend_t name = {NULL, puts}

#if (LOG_ENABLE > 0)

#if (LOG_ENABLE_ASYNC_MODE > 0)
/*!
 * @brief Filter the log
 *
 * @details This macro is used to filter the log. The macro is used by the
 * macro LOG_FATAL/LOG_ERR/LOG_WRN/LOG_INF/LOG_DBG/LOG_TRACE.
 * Only when the following two conditions are met at the same time,
 * 1. The priority of the log message level is valid.
 * 2. The priority of the log message level is higher than the module log
 * level.@n
 * The macro should not be used by application directly.
 */
#define _LOG_PRINTF(logger, logLevel, format, ...)                                                            \
    if (((logLevel > kLOG_LevelNone) && ((logger)->level >= logLevel)))                                       \
    {                                                                                                         \
        LOG_ARGUMENT_TYPE argValueList[] = {LOG_LIST_ARGUMENT(__VA_ARGS__)};                                  \
        LOG_AsyncPrintf(logger, logLevel, LOG_TIMESTAMP_GET, format, ARRAY_SIZE(argValueList), argValueList); \
    }
#else
/*!
 * @brief Filter the log
 *
 * @details This macro is used to filter the log. The macro is used by the
 * macro LOG_FATAL/LOG_ERR/LOG_WRN/LOG_INF/LOG_DBG/LOG_TRACE.
 * Only when the following two conditions are met at the same time,
 * 1. The priority of the log message level is valid.
 * 2. The priority of the log message level is higher than the module log
 * level.@n
 * The macro should not be used by application directly.
 */
#define _LOG_PRINTF(logger, logLevel, format, ...)                            \
    if (((logLevel > kLOG_LevelNone) && ((logger)->level >= logLevel)))       \
    {                                                                         \
        LOG_Printf(logger, logLevel, LOG_TIMESTAMP_GET, format, __VA_ARGS__); \
    }
#endif

/*!
 * @brief Defines the log module
 *
 * @details This macro is used to define the log module for each driver/component/middleware.
 * The macro should be added to source code of each module.
 * This is an example, the code block should be placed at the end of the header file
 * including of the source code.
 * The macro is only valid when LOG_ENABLE is set.
 *
 * @code
 * #define LOG_ENABLE 1
 * #include "fsl_component_log.h"
 * LOG_MODULE_DEFINE(hello_world, kLOG_LevelDebug);
 * @endcode
 *
 * @param name The name string of the log module.
 * @param level The debug level of the log module.
 */
#define LOG_MODULE_DEFINE(name, level) static const log_module_t s_LogModuleLogger = {#name, level};

/*!
 * @brief Writes the fatal level log formatted output to the backend.
 *
 * @details Call this function to write the fatal level log formatted output to the backend.
 * The log string color feature is set by the macro LOG_ENABLE_COLOR.
 * The log string time stamp feature is set by the macro LOG_ENABLE_TIMESTAMP.
 * The macro is only valid when LOG_ENABLE is set.
 * This is an example,
 * The source code is,
 * @code
 *   LOG_ERR("cycle %d", count);
 * @endcode
 * The output string is,
 * @code
 *            0: FATAL hello_world.c:50:cycle 0
 * @endcode
 *
 * @param   format Format control string.
 */
#define LOG_FATAL(format, ...) \
    _LOG_PRINTF(&s_LogModuleLogger, kLOG_LevelFatal, "%s:%d:" format "\r\n", LOG_FILE_NAME, __LINE__, ##__VA_ARGS__);

/*!
 * @brief Writes the error level log formatted output to the backend.
 *
 * @details Call this function to write the error level log formatted output to the backend.
 * The log string color feature is set by the macro LOG_ENABLE_COLOR.
 * The log string time stamp feature is set by the macro LOG_ENABLE_TIMESTAMP.
 * The macro is only valid when LOG_ENABLE is set.
 * This is an example,
 * The source code is,
 * @code
 *   LOG_ERR("cycle %d", count);
 * @endcode
 * The output string is,
 * @code
 *            0: ERROR hello_world.c:50:cycle 0
 * @endcode
 *
 * @param   format Format control string.
 */
#define LOG_ERR(format, ...) \
    _LOG_PRINTF(&s_LogModuleLogger, kLOG_LevelError, "%s:%d:" format "\r\n", LOG_FILE_NAME, __LINE__, ##__VA_ARGS__);

/*!
 * @brief Writes the warning level log formatted output to the backend.
 *
 * @details Call this function to write the warning level log formatted output to the backend.
 * The log string color feature is set by the macro LOG_ENABLE_COLOR.
 * The log string time stamp feature is set by the macro LOG_ENABLE_TIMESTAMP.
 * The macro is only valid when LOG_ENABLE is set.
 * This is an example,
 * The source code is,
 * @code
 *   LOG_WRN("cycle %d", count);
 * @endcode
 * The output string is,
 * @code
 *            0: WARN  hello_world.c:50:cycle 0
 * @endcode
 *
 * @param   format Format control string.
 */
#define LOG_WRN(format, ...) \
    _LOG_PRINTF(&s_LogModuleLogger, kLOG_LevelWarning, "%s:%d:" format "\r\n", LOG_FILE_NAME, __LINE__, ##__VA_ARGS__);

/*!
 * @brief Writes the info level log formatted output to the backend.
 *
 * @details Call this function to write the info level log formatted output to the backend.
 * The log string color feature is set by the macro LOG_ENABLE_COLOR.
 * The log string time stamp feature is set by the macro LOG_ENABLE_TIMESTAMP.
 * The macro is only valid when LOG_ENABLE is set.
 * This is an example,
 * The source code is,
 * @code
 *   LOG_INF("cycle %d", count);
 * @endcode
 * The output string is,
 * @code
 *            0: INFO  hello_world.c:50:cycle 0
 * @endcode
 *
 * @param   format Format control string.
 */
#define LOG_INF(format, ...) \
    _LOG_PRINTF(&s_LogModuleLogger, kLOG_LevelInfo, "%s:%d:" format "\r\n", LOG_FILE_NAME, __LINE__, ##__VA_ARGS__);

/*!
 * @brief Writes the debug level log formatted output to the backend.
 *
 * @details Call this function to write the debug level log formatted output to the backend.
 * The log string color feature is set by the macro LOG_ENABLE_COLOR.
 * The log string time stamp feature is set by the macro LOG_ENABLE_TIMESTAMP.
 * The macro is only valid when LOG_ENABLE is set.
 * This is an example,
 * The source code is,
 * @code
 *   LOG_DBG("cycle %d", count);
 * @endcode
 * The output string is,
 * @code
 *            0: DEBUG hello_world.c:50:cycle 0
 * @endcode
 *
 * @param   format Format control string.
 */
#define LOG_DBG(format, ...) \
    _LOG_PRINTF(&s_LogModuleLogger, kLOG_LevelDebug, "%s:%d:" format "\r\n", LOG_FILE_NAME, __LINE__, ##__VA_ARGS__);

/*!
 * @brief Writes the trace level log formatted output to the backend.
 *
 * @details Call this function to write the trace level log formatted output to the backend.
 * The log string color feature is set by the macro LOG_ENABLE_COLOR.
 * The log string time stamp feature is set by the macro LOG_ENABLE_TIMESTAMP.
 * The macro is only valid when LOG_ENABLE is set.
 * This is an example,
 * The source code is,
 * @code
 *   LOG_TRACE("cycle %d", count);
 * @endcode
 * The output string is,
 * @code
 *            0: TRACE hello_world.c:50:cycle 0
 * @endcode
 *
 * @param   format Format control string.
 */
#define LOG_TRACE(format, ...) \
    _LOG_PRINTF(&s_LogModuleLogger, kLOG_LevelTrace, "%s:%d:" format "\r\n", LOG_FILE_NAME, __LINE__, ##__VA_ARGS__);

#else

#define LOG_MODULE_DEFINE(name, level)
#define LOG_FATAL(format, ...)
#define LOG_ERR(format, ...)
#define LOG_WRN(format, ...)
#define LOG_INF(format, ...)
#define LOG_DBG(format, ...)
#define LOG_TRACE(format, ...)

#endif
#if LOG_ENABLE_TIMESTAMP
/*! @brief get time stamp function */
typedef unsigned int (*log_get_timestamp_callback_t)(void);
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief Initializes the log component with the user configuration structure.
 *
 * @details This function configures the log component with user-defined settings.
 * The user can configure the configuration structure.
 * Example below shows how to use this API to configure the log component.
 *  @code
 *   LOG_Init();
 *  @endcode
 *
 * @retval kStatus_LOG_Success The Log component initialization succeed.
 * @retval kStatus_LOG_Initialized Log component has been initialized.
 * @retval kStatus_LOG_LackResource Lack of resource.
 */
log_status_t LOG_Init(void);

/*!
 * @brief De-initializes the log component.
 *
 * @details This function de-initializes the log component.
 *
 * @retval kStatus_LOG_Success The log component de-initialization succeed.
 */
log_status_t LOG_Deinit(void);

/*!
 * @brief Prints the format log string.
 *
 * @details This function prints the format log string. The timestamp and color are added to prefix by function.
 * The log string color feature is set by the macro LOG_ENABLE_COLOR.
 * The log string time stamp feature is set by the macro LOG_ENABLE_TIMESTAMP.
 *
 * @param module the log module.
 * @param level log level.
 * @param timeStamp current timestamp.
 * @param format formated log string.
 */
void LOG_Printf(log_module_t const *module, log_level_t level, unsigned int timeStamp, char const *format, ...);

#if (LOG_ENABLE_ASYNC_MODE > 0)
/*!
 * @brief Prints the format log string in asynchronous mode.
 *
 * @details This function prints the format log string in asynchronous mode. The timestamp and color are added to prefix
 * by function. The log string color feature is set by the macro LOG_ENABLE_COLOR. The log string time stamp feature is
 * set by the macro LOG_ENABLE_TIMESTAMP.
 *
 * @param module the log module.
 * @param level log level.
 * @param timeStamp current timestamp.
 * @param format formated log string.
 * @param argc argument count.
 * @param argv argument value array.
 */
void LOG_AsyncPrintf(log_module_t const *module,
                     log_level_t level,
                     unsigned int timeStamp,
                     char const *format,
                     uint32_t argc,
                     LOG_ARGUMENT_TYPE argv[]);

/*!
 * @brief Dump the log bufferred in log component.
 *
 * @details This function dumps one log bufferred in log component.
 * Only the buffer and length are valid, the outLength will be filled with valid value.
 * The message will be discarded when the message is more than LOG_MAX_MEESSAGE_LENGTH or buffer length
 * passed by the function.
 *
 * @param buffer The buffer to dump the message.
 * @param length The buffer length of the passed buffer.
 * @param outLength return the message length.
 */
void LOG_Dump(uint8_t *buffer, size_t length, size_t *outLength);
#endif

/*!
 * @brief Registers backend.
 *
 * @details This function registers the backend. The parameter of the function is defined by
 * macro LOG_BACKEND_DEFINE.
 *
 * Example below shows how to use this API to register the backend.
 * step 1, define the backend node by calling LOG_BACKEND_DEFINE.
 *  @code
 *   static void puts(uint8_t *buffer, size_t length)
 *   {
 *       ...
 *   }
 *   LOG_BACKEND_DEFINE(test, puts);
 *  @endcode
 * step 2, call function LOG_BackendRegister to register the backend in
 * same source file.
 *  @code
 *   LOG_BackendRegister(&test);
 *  @endcode
 *
 * @param backend The new backend.
 *
 * @retval kStatus_LOG_Success The backend is registered.
 * @retval kStatus_LOG_Uninitialized The log component is not initialized.
 * @retval kStatus_LOG_BackendExist The backend has been registered.
 */
log_status_t LOG_BackendRegister(log_backend_t *backend);

/*!
 * @brief Unregisters backend.
 *
 * @details This function unregisters the backend.
 *
 * @param backend The backend.
 *
 * @retval kStatus_LOG_Success The backend is unregistered.
 * @retval kStatus_LOG_Uninitialized The log component is not initialized.
 * @retval kStatus_LOG_BackendNotFound the backend is not found.
 */
log_status_t LOG_BackendUnregister(log_backend_t *backend);

#if LOG_ENABLE_TIMESTAMP
/*!
 * @brief Sets the get timestamp function callback.
 *
 * @details This function sets the get timestamp function callback.
 * The feature is controlled by the macro LOG_ENABLE_TIMESTAMP.
 *
 * @param getTimeStamp get time stamp function callback.
 *
 * @retval kStatus_LOG_Success Succeed.
 * @retval kStatus_LOG_Uninitialized The log component is not initialized.
 */
log_status_t LOG_SetTimestamp(log_get_timestamp_callback_t getTimeStamp);
/*!
 * @brief Gets current timestamp.
 *
 * @details This function gets current timestamp.
 * The feature is controlled by the macro LOG_ENABLE_TIMESTAMP.
 *
 * @return Current timestamp.
 */
unsigned int LOG_GetTimestamp(void);
#endif

#if defined(__cplusplus)
}
#endif
/*! @} */
#endif /* __FSL_COMPONENT_LOG_H__ */
