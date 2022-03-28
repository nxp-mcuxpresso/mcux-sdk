/* ==========================================
    Unity Project - A Test Framework for C
    Copyright (c) 2007 Mike Karlesky, Mark VanderVoord, Greg Williams
    [Released under MIT License. Please refer to license.txt for details]
========================================== */

#ifndef UNITY_INTERNALS_H
#define UNITY_INTERNALS_H

#include <stdio.h>
#include <setjmp.h>

// Unity attempts to determine sizeof(various types)
// based on UINT_MAX, ULONG_MAX, etc. These are typically
// defined in limits.h.
#ifdef UNITY_USE_LIMITS_H
#include <limits.h>
#endif
// As a fallback, hope that including stdint.h will
// provide this information.
#ifndef UNITY_EXCLUDE_STDINT_H
#include <stdint.h>
#endif

//-------------------------------------------------------
// Guess Widths If Not Specified
//-------------------------------------------------------

// Determine the size of an int, if not already specificied.
// We cannot use sizeof(int), because it is not yet defined
// at this stage in the trnslation of the C program.
// Therefore, infer it from UINT_MAX if possible.
#ifndef UNITY_INT_WIDTH
#ifdef UINT_MAX
#if (UINT_MAX == 0xFFFF)
#define UNITY_INT_WIDTH (16)
#elif (UINT_MAX == 0xFFFFFFFF)
#define UNITY_INT_WIDTH (32)
#elif (UINT_MAX == 0xFFFFFFFFFFFFFFFF)
#define UNITY_INT_WIDTH (64)
#ifndef UNITY_SUPPORT_64
#define UNITY_SUPPORT_64
#endif
#endif
#endif
#endif
#ifndef UNITY_INT_WIDTH
#define UNITY_INT_WIDTH (32)
#endif

// Determine the size of a long, if not already specified,
// by following the process used above to define
// UNITY_INT_WIDTH.
#ifndef UNITY_LONG_WIDTH
#ifdef ULONG_MAX
#if (ULONG_MAX == 0xFFFF)
#define UNITY_LONG_WIDTH (16)
#elif (ULONG_MAX == 0xFFFFFFFF)
#define UNITY_LONG_WIDTH (32)
#elif (ULONG_MAX == 0xFFFFFFFFFFFFFFFF)
#define UNITY_LONG_WIDTH (64)
#ifndef UNITY_SUPPORT_64
#define UNITY_SUPPORT_64
#endif
#endif
#endif
#endif
#ifndef UNITY_LONG_WIDTH
#define UNITY_LONG_WIDTH (32)
#endif

// Determine the size of a pointer, if not already specified,
// by following the process used above to define
// UNITY_INT_WIDTH.
#ifndef UNITY_POINTER_WIDTH
#ifdef UINTPTR_MAX
#if (UINTPTR_MAX <= 0xFFFF)
#define UNITY_POINTER_WIDTH (16)
#elif (UINTPTR_MAX <= 0xFFFFFFFF)
#define UNITY_POINTER_WIDTH (32)
#elif (UINTPTR_MAX <= 0xFFFFFFFFFFFFFFFF)
#define UNITY_POINTER_WIDTH (64)
#ifndef UNITY_SUPPORT_64
#define UNITY_SUPPORT_64
#endif
#endif
#endif
#endif
#ifndef UNITY_POINTER_WIDTH
#ifdef INTPTR_MAX
#if (INTPTR_MAX <= 0x7FFF)
#define UNITY_POINTER_WIDTH (16)
#elif (INTPTR_MAX <= 0x7FFFFFFF)
#define UNITY_POINTER_WIDTH (32)
#elif (INTPTR_MAX <= 0x7FFFFFFFFFFFFFFF)
#define UNITY_POINTER_WIDTH (64)
#ifndef UNITY_SUPPORT_64
#define UNITY_SUPPORT_64
#endif
#endif
#endif
#endif
#ifndef UNITY_POINTER_WIDTH
#define UNITY_POINTER_WIDTH (32)
#endif

#ifdef UNITY_CONTINUE_CUR_TEST_IF_ASSERT_FAIL
#define IS_CONTINUE_CUR_TEST_IF_ASSERT_FAIL 1
#else
#define IS_CONTINUE_CUR_TEST_IF_ASSERT_FAIL 0
#endif

//-------------------------------------------------------
// Int Support
//-------------------------------------------------------

#if (UNITY_INT_WIDTH == 32)
typedef unsigned char _UU8;
typedef unsigned short _UU16;
typedef unsigned int _UU32;
typedef signed char _US8;
typedef signed short _US16;
typedef signed int _US32;
#elif (UNITY_INT_WIDTH == 16)
typedef unsigned char _UU8;
typedef unsigned int _UU16;
typedef unsigned long _UU32;
typedef signed char _US8;
typedef signed int _US16;
typedef signed long _US32;
#else
#error Invalid UNITY_INT_WIDTH specified! (16 or 32 are supported)
#endif

//-------------------------------------------------------
// 64-bit Support
//-------------------------------------------------------

#ifndef UNITY_SUPPORT_64

// No 64-bit Support
typedef _UU32 _U_UINT;
typedef _US32 _U_SINT;

#else

// 64-bit Support
#if (UNITY_LONG_WIDTH == 32)
typedef unsigned long long _UU64;
typedef signed long long _US64;
#elif (UNITY_LONG_WIDTH == 64)
typedef unsigned long _UU64;
typedef signed long _US64;
#else
#error Invalid UNITY_LONG_WIDTH specified! (32 or 64 are supported)
#endif
typedef _UU64 _U_UINT;
typedef _US64 _U_SINT;

#endif

//-------------------------------------------------------
// Pointer Support
//-------------------------------------------------------

#if (UNITY_POINTER_WIDTH == 32)
typedef _UU32 _UP;
#define UNITY_DISPLAY_STYLE_POINTER UNITY_DISPLAY_STYLE_HEX32
#elif (UNITY_POINTER_WIDTH == 64)
#ifndef UNITY_SUPPORT_64
#error "You've Specified 64-bit pointers without enabling 64-bit Support. Define UNITY_SUPPORT_64"
#endif
typedef _UU64 _UP;
#define UNITY_DISPLAY_STYLE_POINTER UNITY_DISPLAY_STYLE_HEX64
#elif (UNITY_POINTER_WIDTH == 16)
typedef _UU16 _UP;
#define UNITY_DISPLAY_STYLE_POINTER UNITY_DISPLAY_STYLE_HEX16
#else
#error Invalid UNITY_POINTER_WIDTH specified! (16, 32 or 64 are supported)
#endif

//-------------------------------------------------------
// Float Support
//-------------------------------------------------------

#ifdef UNITY_EXCLUDE_FLOAT

//-------------------------------------------------------
// Error[Pm081]: #undef should not be used (MISRA C 2004 rule 19.6)
// Need manual control defined symbols by generator projects
//-------------------------------------------------------

// No Floating Point Support
//#undef UNITY_FLOAT_PRECISION
//#undef UNITY_FLOAT_TYPE
//#undef UNITY_FLOAT_VERBOSE

#else

// Floating Point Support
#ifndef UNITY_FLOAT_PRECISION
#define UNITY_FLOAT_PRECISION (0.00001f)
#endif
#ifndef UNITY_FLOAT_TYPE
#define UNITY_FLOAT_TYPE float
#endif
typedef UNITY_FLOAT_TYPE _UF;

#endif

//-------------------------------------------------------
// Double Float Support
//-------------------------------------------------------

// unlike FLOAT, we DON'T include by default
#ifndef UNITY_EXCLUDE_DOUBLE
#ifndef UNITY_INCLUDE_DOUBLE
#define UNITY_EXCLUDE_DOUBLE
#endif
#endif

#ifdef UNITY_EXCLUDE_DOUBLE

//-------------------------------------------------------
// Error[Pm081]: #undef should not be used (MISRA C 2004 rule 19.6)
// Need manual control defined symbols by generator projects
//-------------------------------------------------------

// No Floating Point Support
//#undef UNITY_DOUBLE_PRECISION
//#undef UNITY_DOUBLE_TYPE
//#undef UNITY_DOUBLE_VERBOSE

#else

// Floating Point Support
#ifndef UNITY_DOUBLE_PRECISION
#define UNITY_DOUBLE_PRECISION (1e-12f)
#endif
#ifndef UNITY_DOUBLE_TYPE
#define UNITY_DOUBLE_TYPE double
#endif
typedef UNITY_DOUBLE_TYPE _UD;

#endif

//-------------------------------------------------------
// Output Method
//-------------------------------------------------------
#ifdef UNITY_NOT_PRINT_LOG
/* add do {} while(0) because of MISRA C 2014 rule 14.3 issue*/
#define UNITY_OUTPUT_CHAR(a) \
    do                       \
    {                        \
    } while (0)
#else
#ifdef UNITY_CUSTOM_OUTPUT_CHAR
// If defined as something else, make sure we declare it here so it's ready for use
#include "fsl_debug_console.h"
#define UNITY_OUTPUT_CHAR(a) PUTCHAR(a)
#else
// Default to using putchar, which is defined in stdio.h above
#define UNITY_OUTPUT_CHAR(a) putchar(a)
#endif
#endif

//-------------------------------------------------------
// Footprint
//-------------------------------------------------------

#ifndef UNITY_LINE_TYPE
#define UNITY_LINE_TYPE _U_UINT
#endif

#ifndef UNITY_COUNTER_TYPE
#define UNITY_COUNTER_TYPE _U_UINT
#endif

//-------------------------------------------------------
// Internal Structs Needed
//-------------------------------------------------------
typedef void (*UnityTestSetUpFunction)(void);
typedef void (*UnityTestFunction)(void);
typedef void (*UnityTestTearDownFunction)(void);

#define UNITY_DISPLAY_RANGE_INT     (0x10U)
#define UNITY_DISPLAY_RANGE_UINT    (0x20U)
#define UNITY_DISPLAY_RANGE_HEX     (0x40U)
#define UNITY_DISPLAY_RANGE_AUTO    (0x80U)
#define UNITY_DISPLAY_RANGE_UNKNOWN (0xffU)

typedef enum
{
#if (UNITY_INT_WIDTH == 16)
    UNITY_DISPLAY_STYLE_INT = 2 + UNITY_DISPLAY_RANGE_INT + UNITY_DISPLAY_RANGE_AUTO,
#elif (UNITY_INT_WIDTH == 32)
    UNITY_DISPLAY_STYLE_INT  = 4 + UNITY_DISPLAY_RANGE_INT + UNITY_DISPLAY_RANGE_AUTO,
#elif (UNITY_INT_WIDTH == 64)
    UNITY_DISPLAY_STYLE_INT  = 8 + UNITY_DISPLAY_RANGE_INT + UNITY_DISPLAY_RANGE_AUTO,
#endif
    UNITY_DISPLAY_STYLE_INT8  = 1 + UNITY_DISPLAY_RANGE_INT,
    UNITY_DISPLAY_STYLE_INT16 = 2 + UNITY_DISPLAY_RANGE_INT,
    UNITY_DISPLAY_STYLE_INT32 = 4 + UNITY_DISPLAY_RANGE_INT,
#ifdef UNITY_SUPPORT_64
    UNITY_DISPLAY_STYLE_INT64 = 8 + UNITY_DISPLAY_RANGE_INT,
#endif

#if (UNITY_INT_WIDTH == 16)
    UNITY_DISPLAY_STYLE_UINT = 2 + UNITY_DISPLAY_RANGE_UINT + UNITY_DISPLAY_RANGE_AUTO,
#elif (UNITY_INT_WIDTH == 32)
    UNITY_DISPLAY_STYLE_UINT = 4 + UNITY_DISPLAY_RANGE_UINT + UNITY_DISPLAY_RANGE_AUTO,
#elif (UNITY_INT_WIDTH == 64)
    UNITY_DISPLAY_STYLE_UINT = 8 + UNITY_DISPLAY_RANGE_UINT + UNITY_DISPLAY_RANGE_AUTO,
#endif
    UNITY_DISPLAY_STYLE_UINT8  = 1 + UNITY_DISPLAY_RANGE_UINT,
    UNITY_DISPLAY_STYLE_UINT16 = 2 + UNITY_DISPLAY_RANGE_UINT,
    UNITY_DISPLAY_STYLE_UINT32 = 4 + UNITY_DISPLAY_RANGE_UINT,
#ifdef UNITY_SUPPORT_64
    UNITY_DISPLAY_STYLE_UINT64 = 8 + UNITY_DISPLAY_RANGE_UINT,
#endif
    UNITY_DISPLAY_STYLE_HEX8  = 1 + UNITY_DISPLAY_RANGE_HEX,
    UNITY_DISPLAY_STYLE_HEX16 = 2 + UNITY_DISPLAY_RANGE_HEX,
    UNITY_DISPLAY_STYLE_HEX32 = 4 + UNITY_DISPLAY_RANGE_HEX,
#ifdef UNITY_SUPPORT_64
    UNITY_DISPLAY_STYLE_HEX64 = 8 + UNITY_DISPLAY_RANGE_HEX,
#endif
    UNITY_DISPLAY_STYLE_UNKNOWN = UNITY_DISPLAY_RANGE_UNKNOWN,
} UNITY_DISPLAY_STYLE_T;

struct _Unity
{
    const char *TestFile;
    const char *CurrentTestName;
    UNITY_LINE_TYPE CurrentTestId;
    UNITY_LINE_TYPE CurrentTestLineNumber;
    UNITY_COUNTER_TYPE NumberOfTests;
    UNITY_COUNTER_TYPE TestFailures;
    UNITY_COUNTER_TYPE TestIgnores;
    UNITY_COUNTER_TYPE CurrentTestFailed;
    UNITY_COUNTER_TYPE CurrentTestIgnored;
    UNITY_COUNTER_TYPE ContinueCurTestIfAssertFail;
    jmp_buf AbortFrame;
};

//-------------------------------------------------------
// Test Suite Management
//-------------------------------------------------------
void setUp(void);
void tearDown(void);

void UnityBegin(void);
int UnityEnd(void);

#ifdef UNITY_DUMP_RESULT
void UnityMemDumpEntry(void);
#endif

void UnityConcludeTest(void);
#ifdef UNITY_SHOW_TEST_FILE_PATH
void UnityDefaultTestRun(UnityTestSetUpFunction SetUpFunc,
                         UnityTestFunction Func,
                         UnityTestTearDownFunction TearDownFunc,
                         const char *FuncName,
                         const int CaseId,
                         const char *TestFile);
#else
void UnityDefaultTestRun(UnityTestSetUpFunction SetUpFunc,
                         UnityTestFunction Func,
                         UnityTestTearDownFunction TearDownFunc,
                         const char *FuncName,
                         const int CaseId);
#endif
void UnityContinueCurTestIfAssertFail(int enabled);

//-------------------------------------------------------
// Test Output
//-------------------------------------------------------

#ifdef UNITY_NOT_PRINT_LOG
// define empty macro
/* add do {} while(0) because of MISRA C 2014 rule 14.3 issue*/
#define UnityPrintf(a...) \
    do                    \
    {                     \
    } while (0)
#define UnityPrint(a) \
    do                \
    {                 \
    } while (0)
#define UnityPrintMask(a, b) \
    do                       \
    {                        \
    } while (0)
#define UnityPrintNumber(a) \
    do                      \
    {                       \
    } while (0)
#define UnityPrintNumberUnsigned(a) \
    do                              \
    {                               \
    } while (0)
#define UnityPrintNumberHex(a) \
    do                         \
    {                          \
    } while (0)
#define UnityPrintFloat(a) \
    do                     \
    {                      \
    } while (0)
#define UnityPrintNumberByStyle(a, b) \
    do                                \
    {                                 \
    } while (0)
#else
#define MAX_CMD_CHAR_CNT (128)
void UnityPrintf(const char *format, ...);
void UnityPrint(const char *string);
void UnityPrintMask(const _U_UINT mask, const _U_UINT number);
void UnityPrintNumber(const _U_SINT number_to_print);
void UnityPrintNumberUnsigned(const _U_UINT number);
void UnityPrintNumberHex(const _U_UINT number, const char nibbles_to_print);
#ifdef UNITY_FLOAT_VERBOSE
void UnityPrintFloat(const _UF number);
#endif
#endif // UNITY_NOT_PRINT_LOG

//-------------------------------------------------------
// Test Assertion Fuctions
//-------------------------------------------------------
//  Use the macros below this section instead of calling
//  these directly. The macros have a consistent naming
//  convention and will pull in file and line information
//  for you.

void UnityAssertEqualNumber(const _U_SINT expected,
                            const _U_SINT actual,
                            const char *msg,
                            const UNITY_LINE_TYPE lineNumber,
                            const UNITY_DISPLAY_STYLE_T style);

void UnityAssertEqualIntArray(const _U_SINT *expected,
                              const _U_SINT *actual,
                              const _UU32 num_elements,
                              const char *msg,
                              const UNITY_LINE_TYPE lineNumber,
                              const UNITY_DISPLAY_STYLE_T style);

void UnityAssertBits(const _U_UINT mask,
                     const _U_UINT expected,
                     const _U_UINT actual,
                     const char *msg,
                     const UNITY_LINE_TYPE lineNumber);

void UnityAssertEqualString(const char *expected,
                            const char *actual,
                            const char *msg,
                            const UNITY_LINE_TYPE lineNumber);

void UnityAssertEqualStringArray(const char **expected,
                                 const char **actual,
                                 const _UU32 num_elements,
                                 const char *msg,
                                 const UNITY_LINE_TYPE lineNumber);

void UnityAssertEqualMemory(unsigned char *expected,
                            unsigned char *actual,
                            const _UU32 length,
                            const _UU32 num_elements,
                            const char *msg,
                            const UNITY_LINE_TYPE lineNumber);

void UnityAssertNumbersWithin(const _U_SINT delta,
                              const _U_SINT expected,
                              const _U_SINT actual,
                              const char *msg,
                              const UNITY_LINE_TYPE lineNumber,
                              const UNITY_DISPLAY_STYLE_T style);

void UnityFail(const char *msg, const UNITY_LINE_TYPE line);

void UnityIgnore(const char *msg, const UNITY_LINE_TYPE line);

#ifndef UNITY_EXCLUDE_FLOAT
void UnityAssertFloatsWithin(
    const _UF delta, const _UF expected, const _UF actual, const char *msg, const UNITY_LINE_TYPE lineNumber);

void UnityAssertEqualFloatArray(const _UF *expected,
                                const _UF *actual,
                                const _UU32 num_elements,
                                const char *msg,
                                const UNITY_LINE_TYPE lineNumber);
/*
Error[Pm046]: floating point values shall not be tested for exact equality or inequality (MISRA C 2004 rule 13.3)
void UnityAssertFloatIsInf(const _UF actual,
                           const char* msg,
                           const UNITY_LINE_TYPE lineNumber);

void UnityAssertFloatIsNegInf(const _UF actual,
                              const char* msg,
                              const UNITY_LINE_TYPE lineNumber);

void UnityAssertFloatIsNaN(const _UF actual,
                           const char* msg,
                           const UNITY_LINE_TYPE lineNumber);
*/
#endif

#ifndef UNITY_EXCLUDE_DOUBLE
void UnityAssertDoublesWithin(
    const _UD delta, const _UD expected, const _UD actual, const char *msg, const UNITY_LINE_TYPE lineNumber);

void UnityAssertEqualDoubleArray(const _UD *expected,
                                 const _UD *actual,
                                 const _UU32 num_elements,
                                 const char *msg,
                                 const UNITY_LINE_TYPE lineNumber);

void UnityAssertDoubleIsInf(const _UD actual, const char *msg, const UNITY_LINE_TYPE lineNumber);

void UnityAssertDoubleIsNegInf(const _UD actual, const char *msg, const UNITY_LINE_TYPE lineNumber);

void UnityAssertDoubleIsNaN(const _UD actual, const char *msg, const UNITY_LINE_TYPE lineNumber);
#endif

#ifdef UNITY_DUMP_RESULT
#define DUMP_RESULT_TEST_RESULT_IGNORE  0x00U
#define DUMP_RESULT_TEST_RESULT_PASS    0x01U
#define DUMP_RESULT_TEST_RESULT_FAIL    0x02U
#define DUMP_RESULT_TEST_RESULT_SUMMARY 0x03U

#define DUMP_RESULT_TEST_RESULT_MASK 0x03U
#define DUMP_RESULT_BIT_NUM          2U

#ifdef UNITY_DUMP_COMPATIBLE_WITH_EU
void setIndepAssertId(const UNITY_LINE_TYPE indepAssertId);
#define INDEP_ASSERT_ID(func, line) INDEP_ASSERT_AT_TEST_##func##_##line
/* add do {} while(0) because of MISRA C 2014 rule 14.3 issue*/
#define SET_INDEP_ASSERT_ID(func, line)                                 \
    do                                                                  \
    {                                                                   \
        setIndepAssertId((UNITY_LINE_TYPE)INDEP_ASSERT_ID(func, line)); \
    } while (0)
#define UnityDumpCaseResult(a, b) \
    do                            \
    {                             \
    } while (0)
void UnityDumpAssertResult(const _UU8 result, const UNITY_LINE_TYPE lineNumber);
#else
/* add do {} while(0) because of MISRA C 2014 rule 14.3 issue*/
#define SET_INDEP_ASSERT_ID(func, line) \
    do                                  \
    {                                   \
    } while (0)
#define UnityDumpAssertResult(a, b) \
    do                              \
    {                               \
    } while (0)
void UnityDumpCaseResult(const _UU8 result, const UNITY_LINE_TYPE lineNumber);
#endif
#else
// empty define
/* add do {} while(0) because of MISRA C 2014 rule 14.3 issue*/
#define UnityDumpAssertResult(a, b) \
    do                              \
    {                               \
    } while (0)
#define UnityDumpCaseResult(a, b) \
    do                            \
    {                             \
    } while (0)
#define SET_INDEP_ASSERT_ID(func, line) \
    do                                  \
    {                                   \
    } while (0)
#endif

//-------------------------------------------------------
// Basic Fail and Ignore
//-------------------------------------------------------

#define UNITY_TEST_FAIL(line, message)   UnityFail((message), (UNITY_LINE_TYPE)line)
#define UNITY_TEST_IGNORE(line, message) UnityIgnore((message), (UNITY_LINE_TYPE)line)
//-------------------------------------------------------
// Test Asserts
//-------------------------------------------------------
// return false if neither is NULL
#ifdef UNITY_DUMP_RESULT
#ifdef UNITY_DUMP_COMPATIBLE_WITH_EU
/* add do {} while(0) because of MISRA C 2014 rule 14.3 issue*/
#define UNITY_TEST_ASSERT(condition, line, message)                                     \
    do                                                                                  \
    {                                                                                   \
        if (condition)                                                                  \
        {                                                                               \
            UnityDumpAssertResult(DUMP_RESULT_TEST_RESULT_PASS, (UNITY_LINE_TYPE)line); \
        }                                                                               \
        else                                                                            \
        {                                                                               \
            UNITY_TEST_FAIL(line, message);                                             \
        }                                                                               \
    } while (0)
#else
#define UNITY_TEST_ASSERT(condition, line, message) \
    do                                              \
    {                                               \
        if (!condition)                             \
        {                                           \
            UNITY_TEST_FAIL(line, message);         \
        }                                           \
    } while (0)
#endif
#else
#define UNITY_TEST_ASSERT(condition, line, message) \
    do                                              \
    {                                               \
        if (!condition)                             \
        {                                           \
            UNITY_TEST_FAIL(line, message);         \
        }                                           \
    } while (0)
#endif
#define UNITY_TEST_ASSERT_NULL(pointer, line, message) \
    UNITY_TEST_ASSERT(((pointer) == NULL), (UNITY_LINE_TYPE)line, message)
#define UNITY_TEST_ASSERT_NOT_NULL(pointer, line, message) \
    UNITY_TEST_ASSERT(((pointer) != NULL), (UNITY_LINE_TYPE)line, message)

#define UNITY_TEST_ASSERT_EQUAL_INT(expected, actual, line, message)                                 \
    UnityAssertEqualNumber((_U_SINT)(expected), (_U_SINT)(actual), (message), (UNITY_LINE_TYPE)line, \
                           UNITY_DISPLAY_STYLE_INT)
#define UNITY_TEST_ASSERT_EQUAL_INT8(expected, actual, line, message)                                            \
    UnityAssertEqualNumber((_U_SINT)(_US8)(expected), (_U_SINT)(_US8)(actual), (message), (UNITY_LINE_TYPE)line, \
                           UNITY_DISPLAY_STYLE_INT)
#define UNITY_TEST_ASSERT_EQUAL_INT16(expected, actual, line, message)                                             \
    UnityAssertEqualNumber((_U_SINT)(_US16)(expected), (_U_SINT)(_US16)(actual), (message), (UNITY_LINE_TYPE)line, \
                           UNITY_DISPLAY_STYLE_INT)
#define UNITY_TEST_ASSERT_EQUAL_INT32(expected, actual, line, message)                                             \
    UnityAssertEqualNumber((_U_SINT)(_US32)(expected), (_U_SINT)(_US32)(actual), (message), (UNITY_LINE_TYPE)line, \
                           UNITY_DISPLAY_STYLE_INT)
#define UNITY_TEST_ASSERT_EQUAL_UINT(expected, actual, line, message)                                \
    UnityAssertEqualNumber((_U_SINT)(expected), (_U_SINT)(actual), (message), (UNITY_LINE_TYPE)line, \
                           UNITY_DISPLAY_STYLE_UINT)
#define UNITY_TEST_ASSERT_EQUAL_UINT8(expected, actual, line, message)                                           \
    UnityAssertEqualNumber((_U_SINT)(_US8)(expected), (_U_SINT)(_US8)(actual), (message), (UNITY_LINE_TYPE)line, \
                           UNITY_DISPLAY_STYLE_UINT)
#define UNITY_TEST_ASSERT_EQUAL_UINT16(expected, actual, line, message)                                            \
    UnityAssertEqualNumber((_U_SINT)(_US16)(expected), (_U_SINT)(_US16)(actual), (message), (UNITY_LINE_TYPE)line, \
                           UNITY_DISPLAY_STYLE_UINT)
#define UNITY_TEST_ASSERT_EQUAL_UINT32(expected, actual, line, message)                                            \
    UnityAssertEqualNumber((_U_SINT)(_US32)(expected), (_U_SINT)(_US32)(actual), (message), (UNITY_LINE_TYPE)line, \
                           UNITY_DISPLAY_STYLE_UINT)
#define UNITY_TEST_ASSERT_EQUAL_HEX8(expected, actual, line, message)                                            \
    UnityAssertEqualNumber((_U_SINT)(_US8)(expected), (_U_SINT)(_US8)(actual), (message), (UNITY_LINE_TYPE)line, \
                           UNITY_DISPLAY_STYLE_HEX8)
#define UNITY_TEST_ASSERT_EQUAL_HEX16(expected, actual, line, message)                                             \
    UnityAssertEqualNumber((_U_SINT)(_US16)(expected), (_U_SINT)(_US16)(actual), (message), (UNITY_LINE_TYPE)line, \
                           UNITY_DISPLAY_STYLE_HEX16)
#define UNITY_TEST_ASSERT_EQUAL_HEX32(expected, actual, line, message)                                             \
    UnityAssertEqualNumber((_U_SINT)(_US32)(expected), (_U_SINT)(_US32)(actual), (message), (UNITY_LINE_TYPE)line, \
                           UNITY_DISPLAY_STYLE_HEX32)
#define UNITY_TEST_ASSERT_BITS(mask, expected, actual, line, message) \
    UnityAssertBits((_U_SINT)(mask), (_U_SINT)(expected), (_U_SINT)(actual), (message), (UNITY_LINE_TYPE)line)

#define UNITY_TEST_ASSERT_INT_WITHIN(delta, expected, actual, line, message)                      \
    UnityAssertNumbersWithin((_U_SINT)(delta), (_U_SINT)(expected), (_U_SINT)(actual), (message), \
                             (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_INT)
#define UNITY_TEST_ASSERT_UINT_WITHIN(delta, expected, actual, line, message)                     \
    UnityAssertNumbersWithin((_U_SINT)(delta), (_U_SINT)(expected), (_U_SINT)(actual), (message), \
                             (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_UINT)
#define UNITY_TEST_ASSERT_HEX8_WITHIN(delta, expected, actual, line, message)                     \
    UnityAssertNumbersWithin((_U_SINT)(_U_UINT)(_UU8)(delta), (_U_SINT)(_U_UINT)(_UU8)(expected), \
                             (_U_SINT)(_U_UINT)(_UU8)(actual), (message), (UNITY_LINE_TYPE)line,  \
                             UNITY_DISPLAY_STYLE_HEX8)
#define UNITY_TEST_ASSERT_HEX16_WITHIN(delta, expected, actual, line, message)                      \
    UnityAssertNumbersWithin((_U_SINT)(_U_UINT)(_UU16)(delta), (_U_SINT)(_U_UINT)(_UU16)(expected), \
                             (_U_SINT)(_U_UINT)(_UU16)(actual), (message), (UNITY_LINE_TYPE)line,   \
                             UNITY_DISPLAY_STYLE_HEX16)
#define UNITY_TEST_ASSERT_HEX32_WITHIN(delta, expected, actual, line, message)                      \
    UnityAssertNumbersWithin((_U_SINT)(_U_UINT)(_UU32)(delta), (_U_SINT)(_U_UINT)(_UU32)(expected), \
                             (_U_SINT)(_U_UINT)(_UU32)(actual), (message), (UNITY_LINE_TYPE)line,   \
                             UNITY_DISPLAY_STYLE_HEX32)

#define UNITY_TEST_ASSERT_EQUAL_PTR(expected, actual, line, message)                                           \
    UnityAssertEqualNumber((_U_SINT)(_UP)(expected), (_U_SINT)(_UP)(actual), (message), (UNITY_LINE_TYPE)line, \
                           UNITY_DISPLAY_STYLE_POINTER)
#define UNITY_TEST_ASSERT_EQUAL_STRING(expected, actual, line, message) \
    UnityAssertEqualString((const char *)(expected), (const char *)(actual), (message), (UNITY_LINE_TYPE)line)
#define UNITY_TEST_ASSERT_EQUAL_MEMORY(expected, actual, len, line, message) \
    UnityAssertEqualMemory((void *)(expected), (void *)(actual), (_UU32)(len), 1, (message), (UNITY_LINE_TYPE)line)

#define UNITY_TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, num_elements, line, message)                               \
    UnityAssertEqualIntArray((const _U_SINT *)(expected), (const _U_SINT *)(actual), (_UU32)(num_elements), (message), \
                             (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_INT)
#define UNITY_TEST_ASSERT_EQUAL_INT8_ARRAY(expected, actual, num_elements, line, message)                              \
    UnityAssertEqualIntArray((const _U_SINT *)(expected), (const _U_SINT *)(actual), (_UU32)(num_elements), (message), \
                             (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_INT8)
#define UNITY_TEST_ASSERT_EQUAL_INT16_ARRAY(expected, actual, num_elements, line, message)                             \
    UnityAssertEqualIntArray((const _U_SINT *)(expected), (const _U_SINT *)(actual), (_UU32)(num_elements), (message), \
                             (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_INT16)
#define UNITY_TEST_ASSERT_EQUAL_INT32_ARRAY(expected, actual, num_elements, line, message)                             \
    UnityAssertEqualIntArray((const _U_SINT *)(expected), (const _U_SINT *)(actual), (_UU32)(num_elements), (message), \
                             (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_INT32)
#define UNITY_TEST_ASSERT_EQUAL_UINT_ARRAY(expected, actual, num_elements, line, message)                              \
    UnityAssertEqualIntArray((const _U_SINT *)(expected), (const _U_SINT *)(actual), (_UU32)(num_elements), (message), \
                             (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_UINT)
#define UNITY_TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, num_elements, line, message)                             \
    UnityAssertEqualIntArray((const _U_SINT *)(expected), (const _U_SINT *)(actual), (_UU32)(num_elements), (message), \
                             (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_UINT8)
#define UNITY_TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, actual, num_elements, line, message)                            \
    UnityAssertEqualIntArray((const _U_SINT *)(expected), (const _U_SINT *)(actual), (_UU32)(num_elements), (message), \
                             (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_UINT16)
#define UNITY_TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, actual, num_elements, line, message)                            \
    UnityAssertEqualIntArray((const _U_SINT *)(expected), (const _U_SINT *)(actual), (_UU32)(num_elements), (message), \
                             (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_UINT32)
#define UNITY_TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, actual, num_elements, line, message)                              \
    UnityAssertEqualIntArray((const _U_SINT *)(expected), (const _U_SINT *)(actual), (_UU32)(num_elements), (message), \
                             (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_HEX8)
#define UNITY_TEST_ASSERT_EQUAL_HEX16_ARRAY(expected, actual, num_elements, line, message)                             \
    UnityAssertEqualIntArray((const _U_SINT *)(expected), (const _U_SINT *)(actual), (_UU32)(num_elements), (message), \
                             (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_HEX16)
#define UNITY_TEST_ASSERT_EQUAL_HEX32_ARRAY(expected, actual, num_elements, line, message)                             \
    UnityAssertEqualIntArray((const _U_SINT *)(expected), (const _U_SINT *)(actual), (_UU32)(num_elements), (message), \
                             (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_HEX32)
#define UNITY_TEST_ASSERT_EQUAL_PTR_ARRAY(expected, actual, num_elements, line, message)           \
    UnityAssertEqualIntArray((const _U_SINT *)(_UP *)(expected), (const _U_SINT *)(_UP *)(actual), \
                             (_UU32)(num_elements), (message), (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_POINTER)
#define UNITY_TEST_ASSERT_EQUAL_STRING_ARRAY(expected, actual, num_elements, line, message)                           \
    UnityAssertEqualStringArray((const char **)(expected), (const char **)(actual), (_UU32)(num_elements), (message), \
                                (UNITY_LINE_TYPE)line)
#define UNITY_TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, actual, len, num_elements, line, message)                 \
    UnityAssertEqualMemory((void *)(expected), (void *)(actual), (_UU32)(len), (_UU32)(num_elements), (message), \
                           (UNITY_LINE_TYPE)line)

#ifdef UNITY_SUPPORT_64
#define UNITY_TEST_ASSERT_EQUAL_INT64(expected, actual, line, message)                               \
    UnityAssertEqualNumber((_U_SINT)(expected), (_U_SINT)(actual), (message), (UNITY_LINE_TYPE)line, \
                           UNITY_DISPLAY_STYLE_INT64)
#define UNITY_TEST_ASSERT_EQUAL_UINT64(expected, actual, line, message)                              \
    UnityAssertEqualNumber((_U_SINT)(expected), (_U_SINT)(actual), (message), (UNITY_LINE_TYPE)line, \
                           UNITY_DISPLAY_STYLE_UINT64)
#define UNITY_TEST_ASSERT_EQUAL_HEX64(expected, actual, line, message)                               \
    UnityAssertEqualNumber((_U_SINT)(expected), (_U_SINT)(actual), (message), (UNITY_LINE_TYPE)line, \
                           UNITY_DISPLAY_STYLE_HEX64)
#define UNITY_TEST_ASSERT_EQUAL_INT64_ARRAY(expected, actual, num_elements, line, message)                             \
    UnityAssertEqualIntArray((const _U_SINT *)(expected), (const _U_SINT *)(actual), (_UU32)(num_elements), (message), \
                             (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_INT64)
#define UNITY_TEST_ASSERT_EQUAL_UINT64_ARRAY(expected, actual, num_elements, line, message)                            \
    UnityAssertEqualIntArray((const _U_SINT *)(expected), (const _U_SINT *)(actual), (_UU32)(num_elements), (message), \
                             (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_UINT64)
#define UNITY_TEST_ASSERT_EQUAL_HEX64_ARRAY(expected, actual, num_elements, line, message)                             \
    UnityAssertEqualIntArray((const _U_SINT *)(expected), (const _U_SINT *)(actual), (_UU32)(num_elements), (message), \
                             (UNITY_LINE_TYPE)line, UNITY_DISPLAY_STYLE_HEX64)
#define UNITY_TEST_ASSERT_HEX64_WITHIN(delta, expected, actual, line, message)                                      \
    UnityAssertNumbersWithin((_U_SINT)(delta), (_U_SINT)(expected), (_U_SINT)(actual), NULL, (UNITY_LINE_TYPE)line, \
                             UNITY_DISPLAY_STYLE_HEX64)
#endif

#ifdef UNITY_EXCLUDE_FLOAT
#define UNITY_TEST_ASSERT_FLOAT_WITHIN(delta, expected, actual, line, message) \
    UNITY_TEST_FAIL((UNITY_LINE_TYPE)line, "Unity Floating Point Disabled")
#define UNITY_TEST_ASSERT_EQUAL_FLOAT(expected, actual, line, message) \
    UNITY_TEST_FAIL((UNITY_LINE_TYPE)line, "Unity Floating Point Disabled")
#define UNITY_TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, actual, num_elements, line, message) \
    UNITY_TEST_FAIL((UNITY_LINE_TYPE)line, "Unity Floating Point Disabled")
#define UNITY_TEST_ASSERT_FLOAT_IS_INF(actual, line, message) \
    UNITY_TEST_FAIL((UNITY_LINE_TYPE)line, "Unity Floating Point Disabled")
#define UNITY_TEST_ASSERT_FLOAT_IS_NEG_INF(actual, line, message) \
    UNITY_TEST_FAIL((UNITY_LINE_TYPE)line, "Unity Floating Point Disabled")
#define UNITY_TEST_ASSERT_FLOAT_IS_NAN(actual, line, message) \
    UNITY_TEST_FAIL((UNITY_LINE_TYPE)line, "Unity Floating Point Disabled")
#else
#define UNITY_TEST_ASSERT_FLOAT_WITHIN(delta, expected, actual, line, message) \
    UnityAssertFloatsWithin((_UF)(delta), (_UF)(expected), (_UF)(actual), (message), (UNITY_LINE_TYPE)line)
#define UNITY_TEST_ASSERT_EQUAL_FLOAT(expected, actual, line, message)                                       \
    UNITY_TEST_ASSERT_FLOAT_WITHIN((_UF)(expected) * (_UF)UNITY_FLOAT_PRECISION, (_UF)expected, (_UF)actual, \
                                   (UNITY_LINE_TYPE)line, message)
#define UNITY_TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, actual, num_elements, line, message)           \
    UnityAssertEqualFloatArray((_UF *)(expected), (_UF *)(actual), (_UU32)(num_elements), (message), \
                               (UNITY_LINE_TYPE)line)
#define UNITY_TEST_ASSERT_FLOAT_IS_INF(actual, line, message) \
    UnityAssertFloatIsInf((_UF)(actual), (message), (UNITY_LINE_TYPE)line)
#define UNITY_TEST_ASSERT_FLOAT_IS_NEG_INF(actual, line, message) \
    UnityAssertFloatIsNegInf((_UF)(actual), (message), (UNITY_LINE_TYPE)line)
#define UNITY_TEST_ASSERT_FLOAT_IS_NAN(actual, line, message) \
    UnityAssertFloatIsNaN((_UF)(actual), (message), (UNITY_LINE_TYPE)line)
#endif

#ifdef UNITY_EXCLUDE_DOUBLE
#define UNITY_TEST_ASSERT_DOUBLE_WITHIN(delta, expected, actual, line, message) \
    UNITY_TEST_FAIL((UNITY_LINE_TYPE)line, "Unity Double Precision Disabled")
#define UNITY_TEST_ASSERT_EQUAL_DOUBLE(expected, actual, line, message) \
    UNITY_TEST_FAIL((UNITY_LINE_TYPE)line, "Unity Double Precision Disabled")
#define UNITY_TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected, actual, num_elements, line, message) \
    UNITY_TEST_FAIL((UNITY_LINE_TYPE)line, "Unity Double Precision Disabled")
#define UNITY_TEST_ASSERT_DOUBLE_IS_INF(actual, line, message) \
    UNITY_TEST_FAIL((UNITY_LINE_TYPE)line, "Unity Double Precision Disabled")
#define UNITY_TEST_ASSERT_DOUBLE_IS_NEG_INF(actual, line, message) \
    UNITY_TEST_FAIL((UNITY_LINE_TYPE)line, "Unity Double Precision Disabled")
#define UNITY_TEST_ASSERT_DOUBLE_IS_NAN(actual, line, message) \
    UNITY_TEST_FAIL((UNITY_LINE_TYPE)line, "Unity Double Precision Disabled")
#else
#define UNITY_TEST_ASSERT_DOUBLE_WITHIN(delta, expected, actual, line, message) \
    UnityAssertDoublesWithin((_UD)(delta), (_UD)(expected), (_UD)(actual), (message), (UNITY_LINE_TYPE)line)
#define UNITY_TEST_ASSERT_EQUAL_DOUBLE(expected, actual, line, message)                                        \
    UNITY_TEST_ASSERT_DOUBLE_WITHIN((_UF)(expected) * (_UD)UNITY_DOUBLE_PRECISION, (_UD)expected, (_UD)actual, \
                                    (UNITY_LINE_TYPE)line, message)
#define UNITY_TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected, actual, num_elements, line, message)           \
    UnityAssertEqualDoubleArray((_UD *)(expected), (_UD *)(actual), (_UU32)(num_elements), (message), \
                                (UNITY_LINE_TYPE)line)
#define UNITY_TEST_ASSERT_DOUBLE_IS_INF(actual, line, message) \
    UnityAssertFloatIsInf((_UF)(actual), (message), (UNITY_LINE_TYPE)line)
#define UNITY_TEST_ASSERT_DOUBLE_IS_NEG_INF(actual, line, message) \
    UnityAssertFloatIsNegInf((_UF)(actual), (message), (UNITY_LINE_TYPE)line)
#define UNITY_TEST_ASSERT_DOUBLE_IS_NAN(actual, line, message) \
    UnityAssertFloatIsNaN((_UF)(actual), (message), (UNITY_LINE_TYPE)line)
#endif

#endif
