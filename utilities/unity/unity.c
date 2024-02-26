/* ==========================================
    Unity Project - A Test Framework for C
    Copyright (c) 2007 Mike Karlesky, Mark VanderVoord, Greg Williams
    [Released under MIT License. Please refer to license.txt for details]
========================================== */

#include "unity.h"
#include <string.h>
#include <stdarg.h>

#ifdef GCOV_DO_COVERAGE
#include "gcov_support.h"
#endif

/* This is SquishCoco code coverage tool related code */
#ifdef __COVERAGESCANNER__

extern void __coveragescanner_set_custom_io(char *(*csfgets)(char *s, int size, void *stream),
                                            int (*csfputs)(const char *s, void *stream),
                                            void *(*csfopenappend)(const char *path),
                                            void *(*csfopenread)(const char *path),
                                            void *(*csfopenwrite)(const char *path),
                                            int (*csfclose)(void *fp),
                                            int (*csremove)(const char *filename));
extern void __coveragescanner_save(void);
extern void __coveragescanner_testname(const char *name);
extern void __coveragescanner_teststate(const char *state);

/* Use preprocessor macro from the following list to chose the way results are stored:
   SQUISHCOCO_RESULT_DATA_SAVE_TO_FILE
   SQUISHCOCO_RESULT_DATA_SAVE_TO_MEMORY
   SQUISHCOCO_RESULT_DATA_SAVE_TO_CONSOLE
*/
#if ((!defined(SQUISHCOCO_RESULT_DATA_SAVE_TO_FILE)) && (!defined(SQUISHCOCO_RESULT_DATA_SAVE_TO_MEMORY)) && \
     (!defined(SQUISHCOCO_RESULT_DATA_SAVE_TO_CONSOLE)) && (!defined(SQUISHCOCO_RESULT_DATA_SAVE_CUSTOM)))
#define SQUISHCOCO_RESULT_DATA_SAVE_TO_CONSOLE

/* Squish Coco I/O functions set implementation */
int csfputs(const char *s, void *stream);
void *csfopenappend(const char *path);
int csfclose(void *fp);
void *csfopenwrite(const char *path);

#else

/* Squish Coco I/O functions implemented externally */
extern int csfputs(const char *s, void *stream);
extern void *csfopenappend(const char *path);
extern int csfclose(void *fp);
extern void *csfopenwrite(const char *path);

#endif

#if defined(SQUISHCOCO_RESULT_DATA_SAVE_TO_FILE)
void *csfopenwrite(const char *path)
{
    return (void *)fopen("../measurements.csexe", "w");
}

int csfputs(const char *s, void *stream)
{
    return fputs(s, (FILE *)stream);
}

void *csfopenappend(const char *path)
{
    return (void *)fopen(path, "a+");
}

int csfclose(void *fp)
{
    return fclose((FILE *)fp);
}
#elif defined(SQUISHCOCO_RESULT_DATA_SAVE_TO_MEMORY)
uint32_t mem_offset = 0x10U;
#define SH_MEM_TOTAL_SIZE (6144U)
#if defined(__ICCARM__) /* IAR Workbench */
#pragma location = "rpmsg_sh_mem_section"
static uint8_t mem_to_store_coverage_results[SH_MEM_TOTAL_SIZE];
#elif defined(__CC_ARM) || defined(__ARMCC_VERSION) /* Keil MDK */
static char mem_to_store_coverage_results[SH_MEM_TOTAL_SIZE] __attribute__((section("rpmsg_sh_mem_section")));
#elif defined(__GNUC__)
static char mem_to_store_coverage_results[SH_MEM_TOTAL_SIZE] __attribute__((section(".noinit.$rpmsg_sh_mem")));
#endif
int csfputs(const char *s, void *stream)
{
    int return_value = 0;
    uint32_t len     = strlen(s);
    memcpy((void *)(char *)(mem_to_store_coverage_results + mem_offset), s, len);
    mem_offset += len;
    return return_value;
}

static uint32_t stream = 0;
void *csfopenappend(const char *path)
{
    return &stream;
}

int csfclose(void *fp)
{
    return 0;
}
#elif defined(SQUISHCOCO_RESULT_DATA_SAVE_TO_CONSOLE)
int csfputs(const char *s, void *stream)
{
    int return_value = 0;
    uint16_t len     = strlen(s);
    uint16_t status  = PRINTF("%s", (char *)s);
    return return_value;
}

static uint32_t stream = 0;
void *csfopenappend(const char *path)
{
    return &stream;
}

int csfclose(void *fp)
{
    return 0;
}
#endif /* SQUISHCOCO_RESULT_DATA_SAVE_TO_x */
#endif /*__COVERAGESCANNER__*/

#ifdef UNITY_DUMP_RESULT
#if defined(UNITY_DUMP_RESULT_ARRAY_SMALL)
#define DUMP_RESULT_ARRAY_SIZE 20U
#elif defined(UNITY_DUMP_RESULT_ARRAY_LARGE)
#define DUMP_RESULT_ARRAY_SIZE 200U
#else
#define DUMP_RESULT_ARRAY_SIZE 50U // default result array size
#endif

#if defined(UNITY_DUMP_CASE_RESULT_ONLY)
#define CASE_NUM_IN_BYTE 4U
_UU8 g_dumpResultArray[DUMP_RESULT_ARRAY_SIZE] = {0};
#elif defined(UNITY_DUMP_COMPATIBLE_WITH_EU)
#define EU_COUNT_RESETS 4U
_UU8 g_dumpResultArray[DUMP_RESULT_ARRAY_SIZE] = {0};
static UNITY_LINE_TYPE s_IndepAssertId         = 0;
#else
typedef struct DumpTestCaseResult
{
    _UU32 testResultType : 2;
    _UU32 testID : 14;
    _UU32 testFailIgnoreLine : 16;
} DumpTestCaseResultT;

typedef struct DumpTestSummary
{
    _UU32 testResultType : 2;
    _UU32 testTotalNum : 10;
    _UU32 testFailNum : 10;
    _UU32 testIgnoreNum : 10;
} DumpTestSummaryT;

typedef union DumpTestData
{
    DumpTestCaseResultT testCaseResult;
    DumpTestSummaryT testSummary;
    _UU32 testResultData;
} DumpTestDataT;

DumpTestDataT g_dumpResultArray[DUMP_RESULT_ARRAY_SIZE] = {0};
_UU16 g_dumpResultArrayIndex                            = 0;
#endif
#endif
/* add do {} while(0) because of MISRA C 2014 rule 14.3 issue*/
#define UNITY_FAIL_AND_BAIL                     \
    do                                          \
    {                                           \
        UNITY_OUTPUT_CHAR('\r');                \
        UNITY_OUTPUT_CHAR('\n');                \
        if (!Unity.ContinueCurTestIfAssertFail) \
        {                                       \
            longjmp(Unity.AbortFrame, 1);       \
        }                                       \
    } while (0)

/* add do {} while(0) because of MISRA C 2014 rule 14.3 issue*/
#define UNITY_IGNORE_AND_BAIL         \
    do                                \
    {                                 \
        UNITY_OUTPUT_CHAR('\r');      \
        UNITY_OUTPUT_CHAR('\n');      \
        longjmp(Unity.AbortFrame, 1); \
    } while (0)

// return prematurely if we are already in failure or ignore state
/* add do {} while(0) because of MISRA C 2014 rule 14.3 issue*/
#define UNITY_SKIP_EXECUTION                                                     \
    do                                                                           \
    {                                                                            \
        if ((!Unity.ContinueCurTestIfAssertFail) &&                              \
            ((Unity.CurrentTestFailed != 0) || (Unity.CurrentTestIgnored != 0))) \
        {                                                                        \
            return;                                                              \
        }                                                                        \
    } while (0)
#define UNITY_PRINT_EOL          \
    do                           \
    {                            \
        UNITY_OUTPUT_CHAR('\r'); \
        UNITY_OUTPUT_CHAR('\n'); \
    } while (0)

/* static struct _Unity Unity = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0, {{ 0 }} }; */
/* The "jmp_buf AbortFrame" is defined as array[] for armgcc and keil, while array[][] for iar.
 */
static struct _Unity Unity = {0};

const char *UnityStrNull                   = "NULL";
const char *UnityStrSpacer                 = ". ";
const char *UnityStrExpected               = " Expected ";
const char *UnityStrWas                    = " Was ";
const char *UnityStrTo                     = " To ";
const char *UnityStrElement                = " Element ";
const char *UnityStrByte                   = " Byte ";
const char *UnityStrMemory                 = " Memory Mismatch.";
const char *UnityStrDelta                  = " Values Not Within Delta ";
const char *UnityStrPointless              = " You Asked Me To Compare Nothing, Which Was Pointless.";
const char *UnityStrNullPointerForExpected = " Expected pointer to be NULL";
const char *UnityStrNullPointerForActual   = " Actual pointer was NULL";
const char *UnityStrInf                    = "Infinity";
const char *UnityStrNegInf                 = "Negative Infinity";
const char *UnityStrNaN                    = "NaN";

/* f_zero and d_zero are no longer used in modified Unity. */
/*
#ifndef UNITY_EXCLUDE_FLOAT
// Dividing by these constants produces +/- infinity.
// The rationale is given in UnityAssertFloatIsInf's body.
static const _UF f_zero = 0.0f;
#ifndef UNITY_EXCLUDE_DOUBLE
static const _UD d_zero = 0.0;
#endif
#endif
*/

// compiler-generic print formatting masks
const _U_UINT UnitySizeMask[] = {255u,   // 0xFF
                                 65535u, // 0xFFFF
                                 65535u,
                                 4294967295u, // 0xFFFFFFFF
                                 4294967295u,
                                 4294967295u,
                                 4294967295u
#ifdef UNITY_SUPPORT_64
                                 ,
                                 0xFFFFFFFFFFFFFFFF
#endif
};

#ifdef UNITY_DUMP_RESULT
#if defined(UNITY_DUMP_COMPATIBLE_WITH_EU) || defined(UNITY_DUMP_CASE_RESULT_ONLY)
static void UnityDumpFillResult(const _UU8 result, _U_UINT id, _U_UINT numInByte);
#endif
#endif

#ifdef UNITY_NOT_PRINT_LOG
/* add do {} while(0) because of MISRA C 2014 rule 14.3 issue*/
#define UnityPrintFail() \
    do                   \
    {                    \
    } while (0)
#define UnityPrintOk() \
    do                 \
    {                  \
    } while (0)
#define UnityAddMsgIfSpecified(a) \
    do                            \
    {                             \
    } while (0)
#define UnityPrintExpectedAndActualStrings(a, b) \
    do                                           \
    {                                            \
    } while (0)
#else
void UnityPrintFail(void);
void UnityPrintOk(void);
/* Static function need be defined in C file */
static void UnityPrintNumberByStyle(const _U_SINT number, const UNITY_DISPLAY_STYLE_T style);

//-----------------------------------------------
// Pretty Printers & Test Result Output Handlers
//-----------------------------------------------
// not conver "\r", "\n", just print all strings
void UnityPrintf(const char *format, ...)
{
    if (NULL == format)
    {
        return;
    }

    int charNum;
    va_list ap;
    char printfBuffer[MAX_CMD_CHAR_CNT] = {0};
    va_start(ap, format);
    charNum = vsprintf(printfBuffer, format, ap);

    char *pBuffer = printfBuffer;
    int printNum  = 0;
    while (*pBuffer)
    {
        UNITY_OUTPUT_CHAR(*pBuffer);
        pBuffer++;
        printNum++;
        if ((printNum > charNum) || (printNum >= MAX_CMD_CHAR_CNT))
        {
            break;
        }
    }

    va_end(ap);
}

// conver "\r", "\n" to show its char
void UnityPrint(const char *string)
{
    const char *pch = string;

    if (pch != NULL)
    {
        while (*pch)
        {
            // printable characters plus CR & LF are printed
            if ((*pch <= 126) && (*pch >= 10))
            {
                UNITY_OUTPUT_CHAR(*pch);
            }
            /*
            //write escaped carriage returns
            else if (*pch == 13)
            {
                UNITY_OUTPUT_CHAR('\\');
                UNITY_OUTPUT_CHAR('r');
            }
            //write escaped line feeds
            else if (*pch == 10)
            {
                UNITY_OUTPUT_CHAR('\\');
                UNITY_OUTPUT_CHAR('n');
            }*/
            // unprintable characters are shown as codes
            else
            {
                UNITY_OUTPUT_CHAR('\\');
                UnityPrintNumberHex((_U_SINT)*pch, 2);
            }
            pch++;
        }
    }
}

//-----------------------------------------------
static void UnityPrintNumberByStyle(const _U_SINT number, const UNITY_DISPLAY_STYLE_T style)
{
    if ((style & UNITY_DISPLAY_RANGE_INT) == UNITY_DISPLAY_RANGE_INT)
    {
        UnityPrintNumber(number);
    }
    else if ((style & UNITY_DISPLAY_RANGE_UINT) == UNITY_DISPLAY_RANGE_UINT)
    {
        UnityPrintNumberUnsigned((_U_UINT)number & UnitySizeMask[((_U_UINT)style & (_U_UINT)0x0F) - 1]);
    }
    else
    {
        UnityPrintNumberHex((_U_UINT)number, (style & 0x000FU) << 1);
    }
}

//-----------------------------------------------
/// basically do an itoa using as little ram as possible
void UnityPrintNumber(const _U_SINT number_to_print)
{
    _U_SINT divisor = 1;
    _U_SINT next_divisor;
    _U_SINT number = number_to_print;

    if (number < 0)
    {
        UNITY_OUTPUT_CHAR('-');
        number = -number;
    }

    // figure out initial divisor
    while (number / divisor > 9)
    {
        next_divisor = divisor * 10;
        if (next_divisor > divisor)
        {
            divisor = next_divisor;
        }
        else
        {
            break;
        }
    }

    // now mod and print, then divide divisor
    do
    {
        UNITY_OUTPUT_CHAR((char)('0' + (number / divisor % 10)));
        divisor /= 10;
    } while (divisor > 0);
}

//-----------------------------------------------
/// basically do an itoa using as little ram as possible
void UnityPrintNumberUnsigned(const _U_UINT number)
{
    _U_UINT divisor = 1;
    _U_UINT next_divisor;

    // figure out initial divisor
    while (number / divisor > 9)
    {
        next_divisor = divisor * 10;
        if (next_divisor > divisor)
        {
            divisor = next_divisor;
        }
        else
        {
            break;
        }
    }

    // now mod and print, then divide divisor
    do
    {
        UNITY_OUTPUT_CHAR((char)('0' + (number / divisor % 10)));
        divisor /= 10;
    } while (divisor > 0);
}

//-----------------------------------------------
void UnityPrintNumberHex(const _U_UINT number, const char nibbles_to_print)
{
    _U_UINT nibble;
    char nibbles = nibbles_to_print;
    UNITY_OUTPUT_CHAR('0');
    UNITY_OUTPUT_CHAR('x');

    while (nibbles > 0)
    {
        nibble = (number >> (--nibbles << 2)) & 0x0000000F;
        if (nibble <= 9)
        {
            UNITY_OUTPUT_CHAR((char)('0' + nibble));
        }
        else
        {
            UNITY_OUTPUT_CHAR((char)('A' - 10 + nibble));
        }
    }
}

//-----------------------------------------------
void UnityPrintMask(const _U_UINT mask, const _U_UINT number)
{
    _U_UINT current_bit = (_U_UINT)1 << (UNITY_INT_WIDTH - 1);
    _US32 i;

    for (i = 0; i < UNITY_INT_WIDTH; i++)
    {
        if (current_bit & mask)
        {
            if (current_bit & number)
            {
                UNITY_OUTPUT_CHAR('1');
            }
            else
            {
                UNITY_OUTPUT_CHAR('0');
            }
        }
        else
        {
            UNITY_OUTPUT_CHAR('X');
        }
        current_bit = current_bit >> 1;
    }
}

//-----------------------------------------------
#ifdef UNITY_FLOAT_VERBOSE
void UnityPrintFloat(_UF number)
{
    char TempBuffer[32];
    sprintf(TempBuffer, "%.6f", number);
    UnityPrint(TempBuffer);
}
#endif

//-----------------------------------------------

void UnityPrintFail(void)
{
    UnityPrint("FAIL");
}

void UnityPrintOk(void)
{
    UnityPrint("OK");
}
#endif //#ifdef UNITY_NOT_PRINT_LOG

//-----------------------------------------------
void UnityTestResultsBegin(const char *file, const UNITY_LINE_TYPE line)
{
    Unity.CurrentTestLineNumber = line;

    UnityPrintNumber(Unity.CurrentTestId);
    UNITY_OUTPUT_CHAR(':');
    UnityPrint(Unity.CurrentTestName);
    UNITY_OUTPUT_CHAR(':');
    if ((Unity.CurrentTestFailed) || (Unity.CurrentTestIgnored))
    {
#ifdef UNITY_SHOW_TEST_FILE_PATH
        UnityPrint(file);
#endif
        UNITY_OUTPUT_CHAR(':');
        UnityPrintNumber(line);
        UNITY_OUTPUT_CHAR(':');
    }
}

//-----------------------------------------------
void UnityTestResultsFailBegin(const UNITY_LINE_TYPE line)
{
    Unity.CurrentTestFailed = 1;
    UnityDumpAssertResult(DUMP_RESULT_TEST_RESULT_FAIL, line);
    UnityDumpCaseResult(DUMP_RESULT_TEST_RESULT_FAIL, line);
    UnityTestResultsBegin(Unity.TestFile, line);
    UnityPrint("FAIL:");
}

//-----------------------------------------------
void UnityConcludeTest(void)
{
    if (Unity.CurrentTestIgnored)
    {
        Unity.TestIgnores++;
    }
    else if (!Unity.CurrentTestFailed)
    {
        UnityTestResultsBegin(Unity.TestFile, Unity.CurrentTestLineNumber);
        UnityPrint("PASS");
        UNITY_PRINT_EOL;
        UnityDumpCaseResult(DUMP_RESULT_TEST_RESULT_PASS, Unity.CurrentTestLineNumber);
    }
    else
    {
        Unity.TestFailures++;
    }

    Unity.CurrentTestFailed  = 0;
    Unity.CurrentTestIgnored = 0;
}

#ifndef UNITY_NOT_PRINT_LOG
//-----------------------------------------------
void UnityAddMsgIfSpecified(const char *msg)
{
    if (msg)
    {
        UnityPrint(UnityStrSpacer);
        UnityPrint(msg);
    }
}

//-----------------------------------------------
void UnityPrintExpectedAndActualStrings(const char *expected, const char *actual)
{
    UnityPrint(UnityStrExpected);
    if (expected != NULL)
    {
        UNITY_OUTPUT_CHAR('\'');
        UnityPrint(expected);
        UNITY_OUTPUT_CHAR('\'');
    }
    else
    {
        UnityPrint(UnityStrNull);
    }
    UnityPrint(UnityStrWas);
    if (actual != NULL)
    {
        UNITY_OUTPUT_CHAR('\'');
        UnityPrint(actual);
        UNITY_OUTPUT_CHAR('\'');
    }
    else
    {
        UnityPrint(UnityStrNull);
    }
}
#endif //#ifndef UNITY_NOT_PRINT_LOG

//-----------------------------------------------
// Assertion & Control Helpers
//-----------------------------------------------

int UnityCheckArraysForNull(const void *expected, const void *actual, const UNITY_LINE_TYPE lineNumber, const char *msg)
{
    // return true if they are both NULL
    if ((expected == NULL) && (actual == NULL))
    {
        return 1;
    }
    // throw error if just expected is NULL
    if (expected == NULL)
    {
        UnityTestResultsFailBegin(lineNumber);
        UnityPrint(UnityStrNullPointerForExpected);
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
        return 1;
    }

    // throw error if just actual is NULL
    if (actual == NULL)
    {
        UnityTestResultsFailBegin(lineNumber);
        UnityPrint(UnityStrNullPointerForActual);
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
        return 1;
    }
    return 0;
}

//-----------------------------------------------
// Assertion Functions
//-----------------------------------------------

void UnityAssertBits(
    const _U_UINT mask, const _U_UINT expected, const _U_UINT actual, const char *msg, const UNITY_LINE_TYPE lineNumber)
{
    UNITY_SKIP_EXECUTION;

    if ((mask & expected) != (mask & actual))
    {
        UnityTestResultsFailBegin(lineNumber);
        UnityPrint(UnityStrExpected);
        UnityPrintMask(mask, expected);
        UnityPrint(UnityStrWas);
        UnityPrintMask(mask, actual);
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
    }
    else
    {
        UnityDumpAssertResult(DUMP_RESULT_TEST_RESULT_PASS, lineNumber);
    }
}

//-----------------------------------------------
void UnityAssertEqualNumber(const _U_SINT expected,
                            const _U_SINT actual,
                            const char *msg,
                            const UNITY_LINE_TYPE lineNumber,
                            const UNITY_DISPLAY_STYLE_T style)
{
    UNITY_SKIP_EXECUTION;

    if (expected != actual)
    {
        UnityTestResultsFailBegin(lineNumber);
        UnityPrint(UnityStrExpected);
        UnityPrintNumberByStyle(expected, style);
        UnityPrint(UnityStrWas);
        UnityPrintNumberByStyle(actual, style);
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
    }
    else
    {
        UnityDumpAssertResult(DUMP_RESULT_TEST_RESULT_PASS, lineNumber);
    }
}

//-----------------------------------------------
void UnityAssertEqualIntArray(const _U_SINT *expected,
                              const _U_SINT *actual,
                              const _UU32 num_elements,
                              const char *msg,
                              const UNITY_LINE_TYPE lineNumber,
                              const UNITY_DISPLAY_STYLE_T style)
{
    _UU32 elements      = num_elements;
    const _US8 *ptr_exp = (const _US8 *)expected;
    const _US8 *ptr_act = (const _US8 *)actual;

    UNITY_SKIP_EXECUTION;

    if (elements == 0)
    {
        UnityTestResultsFailBegin(lineNumber);
        UnityPrint(UnityStrPointless);
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
    }

    /* type "_US32 const *" to "void const *" (MISRA C 2004 rule 11.2)
    if (UnityCheckArraysForNull((const void*)expected, (const void*)actual, lineNumber, msg) == 1)
    */
    if (expected == NULL)
    {
        UnityTestResultsFailBegin(lineNumber);
        UnityPrint(UnityStrNullPointerForExpected);
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
        return;
    }

    if (actual == NULL)
    {
        UnityTestResultsFailBegin(lineNumber);
        UnityPrint(UnityStrNullPointerForActual);
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
        return;
    }

    // If style is UNITY_DISPLAY_STYLE_INT, we'll fall into the default case rather than the INT16 or INT32 (etc) case
    // as UNITY_DISPLAY_STYLE_INT includes a flag for UNITY_DISPLAY_RANGE_AUTO, which the width-specific
    // variants do not. Therefore remove this flag.
    switch (style & ~UNITY_DISPLAY_RANGE_AUTO)
    {
        case UNITY_DISPLAY_STYLE_HEX8:
        case UNITY_DISPLAY_STYLE_INT8:
        case UNITY_DISPLAY_STYLE_UINT8:
            while (elements--)
            {
                if (*ptr_exp != *ptr_act)
                {
                    UnityTestResultsFailBegin(lineNumber);
                    UnityPrint(UnityStrElement);
                    UnityPrintNumberByStyle((num_elements - elements - 1), UNITY_DISPLAY_STYLE_UINT);
                    UnityPrint(UnityStrExpected);
                    UnityPrintNumberByStyle(*ptr_exp, style);
                    UnityPrint(UnityStrWas);
                    UnityPrintNumberByStyle(*ptr_act, style);
                    UnityAddMsgIfSpecified(msg);
                    UNITY_FAIL_AND_BAIL;
                }
                ptr_exp += 1;
                ptr_act += 1;
            }
            break;
        case UNITY_DISPLAY_STYLE_HEX16:
        case UNITY_DISPLAY_STYLE_INT16:
        case UNITY_DISPLAY_STYLE_UINT16:
            while (elements--)
            {
                if (*(const _US16 *)ptr_exp != *(const _US16 *)ptr_act)
                {
                    UnityTestResultsFailBegin(lineNumber);
                    UnityPrint(UnityStrElement);
                    UnityPrintNumberByStyle((num_elements - elements - 1), UNITY_DISPLAY_STYLE_UINT);
                    UnityPrint(UnityStrExpected);
                    UnityPrintNumberByStyle(*(const _US16 *)ptr_exp, style);
                    UnityPrint(UnityStrWas);
                    UnityPrintNumberByStyle(*(const _US16 *)ptr_act, style);
                    UnityAddMsgIfSpecified(msg);
                    UNITY_FAIL_AND_BAIL;
                }
                ptr_exp += 2;
                ptr_act += 2;
            }
            break;
#ifdef UNITY_SUPPORT_64
        case UNITY_DISPLAY_STYLE_HEX64:
        case UNITY_DISPLAY_STYLE_INT64:
        case UNITY_DISPLAY_STYLE_UINT64:
            while (elements--)
            {
                if (*(_US64 *)ptr_exp != *(_US64 *)ptr_act)
                {
                    UnityTestResultsFailBegin(lineNumber);
                    UnityPrint(UnityStrElement);
                    UnityPrintNumberByStyle((num_elements - elements - 1), UNITY_DISPLAY_STYLE_UINT);
                    UnityPrint(UnityStrExpected);
                    UnityPrintNumberByStyle(*(_US64 *)ptr_exp, style);
                    UnityPrint(UnityStrWas);
                    UnityPrintNumberByStyle(*(_US64 *)ptr_act, style);
                    UnityAddMsgIfSpecified(msg);
                    UNITY_FAIL_AND_BAIL;
                }
                ptr_exp += 8;
                ptr_act += 8;
            }
            break;
#endif
        default:
            while (elements--)
            {
                if (*(const _US32 *)ptr_exp != *(const _US32 *)ptr_act)
                {
                    UnityTestResultsFailBegin(lineNumber);
                    UnityPrint(UnityStrElement);
                    UnityPrintNumberByStyle((num_elements - elements - 1), UNITY_DISPLAY_STYLE_UINT);
                    UnityPrint(UnityStrExpected);
                    UnityPrintNumberByStyle(*(const _US32 *)ptr_exp, style);
                    UnityPrint(UnityStrWas);
                    UnityPrintNumberByStyle(*(const _US32 *)ptr_act, style);
                    UnityAddMsgIfSpecified(msg);
                    UNITY_FAIL_AND_BAIL;
                }
                ptr_exp += 4;
                ptr_act += 4;
            }
            break;
    }

    if (!Unity.CurrentTestFailed)
    {
        UnityDumpAssertResult(DUMP_RESULT_TEST_RESULT_PASS, lineNumber);
    }
}

//-----------------------------------------------
#ifndef UNITY_EXCLUDE_FLOAT
void UnityAssertEqualFloatArray(
    const _UF *expected, const _UF *actual, const _UU32 num_elements, const char *msg, const UNITY_LINE_TYPE lineNumber)
{
    _UU32 elements          = num_elements;
    const _UF *ptr_expected = expected;
    const _UF *ptr_actual   = actual;
    _UF diff, tol;

    UNITY_SKIP_EXECUTION;

    if (elements == 0)
    {
        UnityTestResultsFailBegin(lineNumber);
        UnityPrint(UnityStrPointless);
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
    }

    /* type "_US32 const *" to "void const *" (MISRA C 2004 rule 11.2)
    if (UnityCheckArraysForNull((const void*)expected, (const void*)actual, lineNumber, msg) == 1)
    */
    if (expected == NULL)
    {
        UnityTestResultsFailBegin(lineNumber);
        UnityPrint(UnityStrNullPointerForExpected);
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
        return;
    }

    if (actual == NULL)
    {
        UnityTestResultsFailBegin(lineNumber);
        UnityPrint(UnityStrNullPointerForActual);
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
        return;
    }

    while (elements--)
    {
        diff = *ptr_expected - *ptr_actual;
        if (diff < 0.0f)
        {
            diff = 0.0f - diff;
        }
        tol = UNITY_FLOAT_PRECISION * *ptr_expected;
        if (tol < 0.0f)
        {
            tol = 0.0f - tol;
        }

        /*
        Error[Pm046]: floating point values shall not be tested for exact equality or inequality (MISRA C 2004 rule
        13.3)
        //This first part of this condition will catch any NaN or Infinite values, but it almost doesn't happen, disable
        it for MIRSA issue
        */
        if (/*(diff * 0.0f != 0.0f) || */ (diff > tol))
        {
            UnityTestResultsFailBegin(lineNumber);
            UnityPrint(UnityStrElement);
            UnityPrintNumberByStyle((num_elements - elements - 1), UNITY_DISPLAY_STYLE_UINT);
#ifdef UNITY_FLOAT_VERBOSE
            UnityPrint(UnityStrExpected);
            UnityPrintFloat(*ptr_expected);
            UnityPrint(UnityStrWas);
            UnityPrintFloat(*ptr_actual);
#else
            UnityPrint(UnityStrDelta);
#endif
            UnityAddMsgIfSpecified(msg);
            UNITY_FAIL_AND_BAIL;
        }
        ptr_expected++;
        ptr_actual++;
    }

    if (!Unity.CurrentTestFailed)
    {
        UnityDumpAssertResult(DUMP_RESULT_TEST_RESULT_PASS, lineNumber);
    }
}

//-----------------------------------------------
void UnityAssertFloatsWithin(
    const _UF delta, const _UF expected, const _UF actual, const char *msg, const UNITY_LINE_TYPE lineNumber)
{
    _UF diff      = actual - expected;
    _UF pos_delta = delta;

    UNITY_SKIP_EXECUTION;

    if (diff < 0.0f)
    {
        diff = 0.0f - diff;
    }
    if (pos_delta < 0.0f)
    {
        pos_delta = 0.0f - pos_delta;
    }

    /*
    Error[Pm046]: floating point values shall not be tested for exact equality or inequality (MISRA C 2004 rule 13.3)
    //This first part of this condition will catch any NaN or Infinite values, but it almost doesn't happen, disable it
    for MIRSA issue
    */
    if (/*(diff * 0.0f != 0.0f) || */ (pos_delta < diff))
    {
        UnityTestResultsFailBegin(lineNumber);
#ifdef UNITY_FLOAT_VERBOSE
        UnityPrint(UnityStrExpected);
        UnityPrintFloat(expected);
        UnityPrint(UnityStrWas);
        UnityPrintFloat(actual);
#else
        UnityPrint(UnityStrDelta);
#endif
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
    }
    else
    {
        UnityDumpAssertResult(DUMP_RESULT_TEST_RESULT_PASS, lineNumber);
    }
}

/*
Error[Pm046]: floating point values shall not be tested for exact equality or inequality (MISRA C 2004 rule 13.3)
//-----------------------------------------------
void UnityAssertFloatIsInf(const _UF actual,
                           const char* msg,
                           const UNITY_LINE_TYPE lineNumber)
{
    UNITY_SKIP_EXECUTION;

    // In Microsoft Visual C++ Express Edition 2008,
    //   if ((1.0f / f_zero) != actual)
    // produces
    //   error C2124: divide or mod by zero
    // As a workaround, place 0 into a variable.
    if ((1.0f / f_zero) != actual)
    {
        UnityTestResultsFailBegin(lineNumber);
#ifdef UNITY_FLOAT_VERBOSE
        UnityPrint(UnityStrExpected);
        UnityPrint(UnityStrInf);
        UnityPrint(UnityStrWas);
        UnityPrintFloat(actual);
#else
        UnityPrint(UnityStrDelta);
#endif
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
    } else
    {
      UnityDumpAssertResult(DUMP_RESULT_TEST_RESULT_PASS, lineNumber);
    }
}

//-----------------------------------------------
void UnityAssertFloatIsNegInf(const _UF actual,
                              const char* msg,
                              const UNITY_LINE_TYPE lineNumber)
{
    UNITY_SKIP_EXECUTION;

    // The rationale for not using 1.0f/0.0f is given in UnityAssertFloatIsInf's body.
    if ((-1.0f / f_zero) != actual)
    {
        UnityTestResultsFailBegin(lineNumber);
#ifdef UNITY_FLOAT_VERBOSE
        UnityPrint(UnityStrExpected);
        UnityPrint(UnityStrNegInf);
        UnityPrint(UnityStrWas);
        UnityPrintFloat(actual);
#else
        UnityPrint(UnityStrDelta);
#endif
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
    } else
    {
      UnityDumpAssertResult(DUMP_RESULT_TEST_RESULT_PASS, lineNumber);
    }
}

//-----------------------------------------------
void UnityAssertFloatIsNaN(const _UF actual,
                           const char* msg,
                           const UNITY_LINE_TYPE lineNumber)
{
    UNITY_SKIP_EXECUTION;

    if (actual == actual)
    {
        UnityTestResultsFailBegin(lineNumber);
#ifdef UNITY_FLOAT_VERBOSE
        UnityPrint(UnityStrExpected);
        UnityPrint(UnityStrNaN);
        UnityPrint(UnityStrWas);
        UnityPrintFloat(actual);
#else
        UnityPrint(UnityStrDelta);
#endif
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
    } else
    {
      UnityDumpAssertResult(DUMP_RESULT_TEST_RESULT_PASS, lineNumber);
    }
}
Error[Pm046]: floating point values shall not be tested for exact equality or inequality (MISRA C 2004 rule 13.3)*/

#endif // not UNITY_EXCLUDE_FLOAT

//-----------------------------------------------
#ifndef UNITY_EXCLUDE_DOUBLE
void UnityAssertEqualDoubleArray(
    const _UD *expected, const _UD *actual, const _UU32 num_elements, const char *msg, const UNITY_LINE_TYPE lineNumber)
{
    _UU32 elements          = num_elements;
    const _UD *ptr_expected = expected;
    const _UD *ptr_actual   = actual;
    _UD diff, tol;

    UNITY_SKIP_EXECUTION;

    if (elements == 0)
    {
        UnityTestResultsFailBegin(lineNumber);
        UnityPrint(UnityStrPointless);
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
    }

    if (UnityCheckArraysForNull((void *)expected, (void *)actual, lineNumber, msg) == 1)
        return;

    while (elements--)
    {
        diff = *ptr_expected - *ptr_actual;
        if (diff < 0.0)
            diff = 0.0 - diff;
        tol = UNITY_DOUBLE_PRECISION * *ptr_expected;
        if (tol < 0.0)
            tol = 0.0 - tol;

        // This first part of this condition will catch any NaN or Infinite values
        if ((diff * 0.0 != 0.0) || (diff > tol))
        {
            UnityTestResultsFailBegin(lineNumber);
            UnityPrint(UnityStrElement);
            UnityPrintNumberByStyle((num_elements - elements - 1), UNITY_DISPLAY_STYLE_UINT);
#ifdef UNITY_DOUBLE_VERBOSE
            UnityPrint(UnityStrExpected);
            UnityPrintFloat((float)(*ptr_expected));
            UnityPrint(UnityStrWas);
            UnityPrintFloat((float)(*ptr_actual));
#else
            UnityPrint(UnityStrDelta);
#endif
            UnityAddMsgIfSpecified(msg);
            UNITY_FAIL_AND_BAIL;
        }
        ptr_expected++;
        ptr_actual++;
    }

    if (!Unity.CurrentTestFailed)
    {
        UnityDumpAssertResult(DUMP_RESULT_TEST_RESULT_PASS, lineNumber);
    }
}

//-----------------------------------------------
void UnityAssertDoublesWithin(
    const _UD delta, const _UD expected, const _UD actual, const char *msg, const UNITY_LINE_TYPE lineNumber)
{
    _UD diff      = actual - expected;
    _UD pos_delta = delta;

    UNITY_SKIP_EXECUTION;

    if (diff < 0.0)
    {
        diff = 0.0 - diff;
    }
    if (pos_delta < 0.0)
    {
        pos_delta = 0.0 - pos_delta;
    }

    // This first part of this condition will catch any NaN or Infinite values
    if ((diff * 0.0 != 0.0) || (pos_delta < diff))
    {
        UnityTestResultsFailBegin(lineNumber);
#ifdef UNITY_DOUBLE_VERBOSE
        UnityPrint(UnityStrExpected);
        UnityPrintFloat((float)expected);
        UnityPrint(UnityStrWas);
        UnityPrintFloat((float)actual);
#else
        UnityPrint(UnityStrDelta);
#endif
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
    }
    else
    {
        UnityDumpAssertResult(DUMP_RESULT_TEST_RESULT_PASS, lineNumber);
    }
}
/*
Error[Pm046]: floating point values shall not be tested for exact equality or inequality (MISRA C 2004 rule 13.3)
//-----------------------------------------------
void UnityAssertDoubleIsInf(const _UD actual,
                            const char* msg,
                            const UNITY_LINE_TYPE lineNumber)
{
    UNITY_SKIP_EXECUTION;

    // The rationale for not using 1.0/0.0 is given in UnityAssertFloatIsInf's body.
    if ((1.0 / d_zero) != actual)
    {
        UnityTestResultsFailBegin(lineNumber);
#ifdef UNITY_DOUBLE_VERBOSE
        UnityPrint(UnityStrExpected);
        UnityPrint(UnityStrInf);
        UnityPrint(UnityStrWas);
        UnityPrintFloat((float)actual);
#else
        UnityPrint(UnityStrDelta);
#endif
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
    }
}

//-----------------------------------------------
void UnityAssertDoubleIsNegInf(const _UD actual,
                               const char* msg,
                               const UNITY_LINE_TYPE lineNumber)
{
    UNITY_SKIP_EXECUTION;

    // The rationale for not using 1.0/0.0 is given in UnityAssertFloatIsInf's body.
    if ((-1.0 / d_zero) != actual)
    {
        UnityTestResultsFailBegin(lineNumber);
#ifdef UNITY_DOUBLE_VERBOSE
        UnityPrint(UnityStrExpected);
        UnityPrint(UnityStrNegInf);
        UnityPrint(UnityStrWas);
        UnityPrintFloat((float)actual);
#else
        UnityPrint(UnityStrDelta);
#endif
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
    }
}

//-----------------------------------------------
void UnityAssertDoubleIsNaN(const _UD actual,
                            const char* msg,
                            const UNITY_LINE_TYPE lineNumber)
{
    UNITY_SKIP_EXECUTION;

    if (actual == actual)
    {
        UnityTestResultsFailBegin(lineNumber);
#ifdef UNITY_DOUBLE_VERBOSE
        UnityPrint(UnityStrExpected);
        UnityPrint(UnityStrNaN);
        UnityPrint(UnityStrWas);
        UnityPrintFloat((float)actual);
#else
        UnityPrint(UnityStrDelta);
#endif
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
    }
}
*/
#endif // not UNITY_EXCLUDE_DOUBLE

//-----------------------------------------------
void UnityAssertNumbersWithin(const _U_SINT delta,
                              const _U_SINT expected,
                              const _U_SINT actual,
                              const char *msg,
                              const UNITY_LINE_TYPE lineNumber,
                              const UNITY_DISPLAY_STYLE_T style)
{
    UNITY_SKIP_EXECUTION;

    if ((style & UNITY_DISPLAY_RANGE_INT) == UNITY_DISPLAY_RANGE_INT)
    {
        if (actual > expected)
        {
            Unity.CurrentTestFailed = ((actual - expected) > delta);
        }
        else
        {
            Unity.CurrentTestFailed = ((expected - actual) > delta);
        }
    }
    else
    {
        if ((_U_UINT)actual > (_U_UINT)expected)
        {
            Unity.CurrentTestFailed = ((_U_UINT)(actual - expected) > (_U_UINT)delta);
        }
        else
        {
            Unity.CurrentTestFailed = ((_U_UINT)(expected - actual) > (_U_UINT)delta);
        }
    }

    if (Unity.CurrentTestFailed)
    {
        UnityTestResultsFailBegin(lineNumber);
        UnityPrint(UnityStrDelta);
        UnityPrintNumberByStyle(delta, style);
        UnityPrint(UnityStrExpected);
        UnityPrintNumberByStyle(expected, style);
        UnityPrint(UnityStrWas);
        UnityPrintNumberByStyle(actual, style);
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
    }
    else
    {
        UnityDumpAssertResult(DUMP_RESULT_TEST_RESULT_PASS, lineNumber);
    }
}

//-----------------------------------------------
void UnityAssertEqualString(const char *expected, const char *actual, const char *msg, const UNITY_LINE_TYPE lineNumber)
{
    _UU32 i;

    UNITY_SKIP_EXECUTION;

    // if both pointers not null compare the strings
    if (expected && actual)
    {
        for (i = 0; (expected[i]) || (actual[i]); i++)
        {
            if (expected[i] != actual[i])
            {
                Unity.CurrentTestFailed = 1;
                break;
            }
        }
    }
    else
    { // handle case of one pointers being null (if both null, test should pass)
        if (expected != actual)
        {
            Unity.CurrentTestFailed = 1;
        }
    }

    if (Unity.CurrentTestFailed)
    {
        UnityTestResultsFailBegin(lineNumber);
        UnityPrintExpectedAndActualStrings(expected, actual);
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
    }
    else
    {
        UnityDumpAssertResult(DUMP_RESULT_TEST_RESULT_PASS, lineNumber);
    }
}

//-----------------------------------------------
void UnityAssertEqualStringArray(const char **expected,
                                 const char **actual,
                                 const _UU32 num_elements,
                                 const char *msg,
                                 const UNITY_LINE_TYPE lineNumber)
{
    _UU32 i, j = 0;

    UNITY_SKIP_EXECUTION;

    // if no elements, it's an error
    if (num_elements == 0)
    {
        UnityTestResultsFailBegin(lineNumber);
        UnityPrint(UnityStrPointless);
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
    }

    if (UnityCheckArraysForNull((void *)expected, (void *)actual, lineNumber, msg) == 1)
    {
        return;
    }
    do
    {
        // if both pointers not null compare the strings
        if ((expected[j]) && (actual[j]))
        {
            for (i = 0; (expected[j][i]) || (actual[j][i]); i++)
            {
                if (expected[j][i] != actual[j][i])
                {
                    Unity.CurrentTestFailed = 1;
                    break;
                }
            }
        }
        else
        { // handle case of one pointers being null (if both null, test should pass)
            if (expected[j] != actual[j])
            {
                Unity.CurrentTestFailed = 1;
            }
        }

        if (Unity.CurrentTestFailed)
        {
            UnityTestResultsFailBegin(lineNumber);
            if (num_elements > 1)
            {
                UnityPrint(UnityStrElement);
                UnityPrintNumberByStyle((j), UNITY_DISPLAY_STYLE_UINT);
            }
            UnityPrintExpectedAndActualStrings((const char *)(expected[j]), (const char *)(actual[j]));
            UnityAddMsgIfSpecified(msg);
            UNITY_FAIL_AND_BAIL;
        }
    } while (++j < num_elements);

    if (!Unity.CurrentTestFailed)
    {
        UnityDumpAssertResult(DUMP_RESULT_TEST_RESULT_PASS, lineNumber);
    }
}

//-----------------------------------------------
void UnityAssertEqualMemory(unsigned char *expected,
                            unsigned char *actual,
                            const _UU32 length,
                            const _UU32 num_elements,
                            const char *msg,
                            const UNITY_LINE_TYPE lineNumber)
{
    /* type "void const *" to "unsigned char *" (MISRA C 2004 rule 11.2)*/
    unsigned char *ptr_exp = expected;
    unsigned char *ptr_act = actual;
    _UU32 elements         = num_elements;
    _UU32 bytes;

    UNITY_SKIP_EXECUTION;

    if ((elements == 0) || (length == 0))
    {
        UnityTestResultsFailBegin(lineNumber);
        UnityPrint(UnityStrPointless);
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
    }

    /* type "_US32 const *" to "void const *" (MISRA C 2004 rule 11.2)
    if (UnityCheckArraysForNull((const void*)expected, (const void*)actual, lineNumber, msg) == 1)
    */
    if (expected == NULL)
    {
        UnityTestResultsFailBegin(lineNumber);
        UnityPrint(UnityStrNullPointerForExpected);
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
        return;
    }

    if (actual == NULL)
    {
        UnityTestResultsFailBegin(lineNumber);
        UnityPrint(UnityStrNullPointerForActual);
        UnityAddMsgIfSpecified(msg);
        UNITY_FAIL_AND_BAIL;
        return;
    }

    while (elements--)
    {
        /////////////////////////////////////
        bytes = length;
        while (bytes--)
        {
            if (*ptr_exp != *ptr_act)
            {
                UnityTestResultsFailBegin(lineNumber);
                UnityPrint(UnityStrMemory);
                if (num_elements > 1)
                {
                    UnityPrint(UnityStrElement);
                    UnityPrintNumberByStyle((num_elements - elements - 1), UNITY_DISPLAY_STYLE_UINT);
                }
                UnityPrint(UnityStrByte);
                UnityPrintNumberByStyle((length - bytes - 1), UNITY_DISPLAY_STYLE_UINT);
                UnityPrint(UnityStrExpected);
                UnityPrintNumberByStyle(*ptr_exp, UNITY_DISPLAY_STYLE_HEX8);
                UnityPrint(UnityStrWas);
                UnityPrintNumberByStyle(*ptr_act, UNITY_DISPLAY_STYLE_HEX8);
                UnityAddMsgIfSpecified(msg);
                UNITY_FAIL_AND_BAIL;
            }
            ptr_exp += 1;
            ptr_act += 1;
        }
        /////////////////////////////////////
    }

    if (!Unity.CurrentTestFailed)
    {
        UnityDumpAssertResult(DUMP_RESULT_TEST_RESULT_PASS, lineNumber);
    }
}

//-----------------------------------------------
// Control Functions
//-----------------------------------------------

void UnityFail(const char *msg, const UNITY_LINE_TYPE line)
{
    UNITY_SKIP_EXECUTION;
    Unity.CurrentTestFailed = 1;
    UnityDumpAssertResult(DUMP_RESULT_TEST_RESULT_FAIL, line);
    UnityDumpCaseResult(DUMP_RESULT_TEST_RESULT_FAIL, line);
    UnityTestResultsBegin(Unity.TestFile, line);
    UnityPrintFail();
    if (msg != NULL)
    {
        UNITY_OUTPUT_CHAR(':');
        if (msg[0] != ' ')
        {
            UNITY_OUTPUT_CHAR(' ');
        }
        UnityPrint(msg);
    }
    UNITY_FAIL_AND_BAIL;
}

//-----------------------------------------------
void UnityIgnore(const char *msg, const UNITY_LINE_TYPE line)
{
    UNITY_SKIP_EXECUTION;
    Unity.CurrentTestIgnored = 1;
    UnityDumpAssertResult(DUMP_RESULT_TEST_RESULT_IGNORE, line);
    UnityDumpCaseResult(DUMP_RESULT_TEST_RESULT_IGNORE, line);
    UnityTestResultsBegin(Unity.TestFile, line);
    UnityPrint("IGNORE");
    if (msg != NULL)
    {
        UNITY_OUTPUT_CHAR(':');
        UNITY_OUTPUT_CHAR(' ');
        UnityPrint(msg);
    }
    UNITY_IGNORE_AND_BAIL;
}

//-----------------------------------------------
#ifdef UNITY_SHOW_TEST_FILE_PATH
void UnityDefaultTestRun(UnityTestSetUpFunction SetUpFunc,
                         UnityTestFunction Func,
                         UnityTestTearDownFunction TearDownFunc,
                         const char *FuncName,
                         const int CaseId,
                         const char *TestFile)
{
    Unity.TestFile = TestFile;
#else
void UnityDefaultTestRun(UnityTestSetUpFunction SetUpFunc,
                         UnityTestFunction Func,
                         UnityTestTearDownFunction TearDownFunc,
                         const char *FuncName,
                         const int CaseId)
{
#endif
    Unity.CurrentTestName       = FuncName;
    Unity.CurrentTestId         = CaseId;
    Unity.CurrentTestLineNumber = 0;

    Unity.NumberOfTests++;
    Unity.ContinueCurTestIfAssertFail = IS_CONTINUE_CUR_TEST_IF_ASSERT_FAIL;
    if (TEST_PROTECT())
    {
        if (SetUpFunc != NULL)
        {
            SetUpFunc();
        }
        Func();
    }
    if (TEST_PROTECT())
    {
        if (TearDownFunc != NULL)
        {
            TearDownFunc();
        }
    }
    UnityConcludeTest();
}

//-----------------------------------------------
void UnityBegin(void)
{
    Unity.NumberOfTests      = 0;
    Unity.TestFailures       = 0;
    Unity.TestIgnores        = 0;
    Unity.CurrentTestFailed  = 0;
    Unity.CurrentTestIgnored = 0;

#ifdef __COVERAGESCANNER__
    /* Define the Squish Coco set of I/O functions */
#ifdef SQUISHCOCO_RESULT_DATA_SAVE_TO_FILE
    __coveragescanner_set_custom_io(NULL, csfputs, csfopenappend, NULL, csfopenwrite, csfclose, NULL);
#else
    __coveragescanner_set_custom_io(NULL, csfputs, csfopenappend, NULL, NULL, csfclose, NULL);
#endif /* SQUISHCOCO_RESULT_DATA_SAVE_TO_FILE */
#endif /*__COVERAGESCANNER__*/

#if GCOV_DO_COVERAGE
/* Currently, only MCUXPresso support this function. */
#if (defined(__GNUC__) && defined(__MCUXPRESSO))
#if defined(__REDLIB__)
#error "gcov not supported with RedLib"
#else
    gcov_init(); /* do *not* call this for redlib as it does not implement constructors! */
#endif
    if (!gcov_check())
    {
        printf("WARNING: writing coverage does not work! Wrong library used?\n");
    }
#endif /* MCUXPresso IDE used. */
#endif
}

//-----------------------------------------------
int UnityEnd(void)
{
    UnityPrint("-----------------------");
    UNITY_PRINT_EOL;
    UnityPrintNumber(Unity.NumberOfTests);
    UnityPrint(" Tests ");
    UnityPrintNumber(Unity.TestFailures);
    UnityPrint(" Failures ");
    UnityPrintNumber(Unity.TestIgnores);
    UnityPrint(" Ignored");
    UNITY_PRINT_EOL;
    if (Unity.TestFailures == 0U)
    {
        UnityPrintOk();
#ifdef __COVERAGESCANNER__
        /* Set the state of the current test */
        __coveragescanner_teststate("PASSED");
#endif /*__COVERAGESCANNER__*/
    }
    else
    {
        UnityPrintFail();
#ifdef __COVERAGESCANNER__
        /* Set the state of the current test */
        __coveragescanner_teststate("FAILED");
#endif /*__COVERAGESCANNER__*/
    }
    UNITY_PRINT_EOL;

#ifdef UNITY_DUMP_RESULT
#if !defined(UNITY_DUMP_COMPATIBLE_WITH_EU)
#if defined UNITY_DUMP_CASE_RESULT_ONLY
    UnityDumpFillResult(DUMP_RESULT_TEST_RESULT_SUMMARY, Unity.NumberOfTests, CASE_NUM_IN_BYTE);
#else
    if (g_dumpResultArrayIndex < DUMP_RESULT_ARRAY_SIZE)
    {
        /*Last index to record the test summary, how many cases failed totally*/
        DumpTestDataT *pData              = g_dumpResultArray + g_dumpResultArrayIndex;
        pData->testSummary.testResultType = DUMP_RESULT_TEST_RESULT_SUMMARY;
        pData->testSummary.testTotalNum   = Unity.NumberOfTests;
        pData->testSummary.testFailNum    = Unity.TestFailures;
        pData->testSummary.testIgnoreNum  = Unity.TestIgnores;
        g_dumpResultArrayIndex++;
    }
#endif
#endif
#endif

#if defined(GCOV_DO_COVERAGE) && defined(__GNUC__)
    gcov_write(); /* write coverage files */
#endif

#ifdef UNITY_DUMP_RESULT
    UnityMemDumpEntry();
#endif

#ifdef __COVERAGESCANNER__
    //__coveragescanner_testname(Unity.CurrentTestName);
    /* Save the execution report and reset the status of all instrumentations */
    __coveragescanner_save();
#if defined(SQUISHCOCO_RESULT_DATA_SAVE_TO_MEMORY)
    ((uint32_t *)mem_to_store_coverage_results)[0] = mem_offset - 0x10;
#endif
#endif /*__COVERAGESCANNER__*/

    /*do not return for MCU*/
    // while(1);
    return Unity.TestFailures;
}

#ifdef UNITY_DUMP_RESULT
void UnityMemDumpEntry(void)
{
    UnityPrint("-----------------------");
    UNITY_PRINT_EOL;
    UnityPrint("Success to dump test result!\r\n");

#ifdef UNITY_DUMP_RESULT_LOG
#if defined(UNITY_DUMP_CASE_RESULT_ONLY) || defined(UNITY_DUMP_COMPATIBLE_WITH_EU)
    for (int i = 0; i < DUMP_RESULT_ARRAY_SIZE; i++)
    {
        UnityPrintNumberByStyle(g_dumpResultArray[i], UNITY_DISPLAY_STYLE_HEX8);
        UnityPrint("\r\n");
    }
#else
    for (int i = 0; i < g_dumpResultArrayIndex; i++)
    {
        if ((g_dumpResultArrayIndex - 1) == i)
        {
            UnityPrint("\r\nsummary data: ");
            UnityPrintNumberByStyle(g_dumpResultArray[i].testResultData, UNITY_DISPLAY_STYLE_HEX32);

            UnityPrint(", total: ");
            UnityPrintNumberUnsigned(g_dumpResultArray[i].testSummary.testTotalNum);

            UnityPrint(", fail: ");
            UnityPrintNumberUnsigned(g_dumpResultArray[i].testSummary.testFailNum);

            UnityPrint(", ignore: ");
            UnityPrintNumberUnsigned(g_dumpResultArray[i].testSummary.testIgnoreNum);
        }
        else
        {
            UnityPrint("\r\ntest case data: ");
            UnityPrintNumberByStyle(g_dumpResultArray[i].testResultData, UNITY_DISPLAY_STYLE_HEX32);

            UnityPrint(", resultType: ");
            UnityPrintNumberUnsigned(g_dumpResultArray[i].testCaseResult.testResultType);

            UnityPrint(", testId: ");
            UnityPrintNumberUnsigned(g_dumpResultArray[i].testCaseResult.testID);

            UnityPrint(", testFailIgnoreLine: ");
            UnityPrintNumberUnsigned(g_dumpResultArray[i].testCaseResult.testFailIgnoreLine);
        }
    }
#endif
#endif
}
#endif

void UnityContinueCurTestIfAssertFail(int enabled)
{
    Unity.ContinueCurTestIfAssertFail = enabled;
}

#ifdef UNITY_DUMP_RESULT
#if defined(UNITY_DUMP_COMPATIBLE_WITH_EU) || defined(UNITY_DUMP_CASE_RESULT_ONLY)
// common function for fill the test result in bytes
static void UnityDumpFillResult(const _UU8 result, _U_UINT id, _U_UINT numInByte)
{
    _UU16 dumpResultIndex = id / numInByte;
    if (dumpResultIndex < DUMP_RESULT_ARRAY_SIZE)
    {
        // 8 bit _UU8 variable stores 4 asserts/cases result, from high to low
        // assert/case id -- 0, stored in bits 8~7, margintRight is 6
        // assert/case id -- 1, stored in bits 6~5, margintRight is 4
        // assert/case id -- 2, stored in bits 4~3, marginRight is 2
        // assert/case id -- 3, stored in bits 2~1, marginRight is 0

        _UU8 marginRight = DUMP_RESULT_BIT_NUM * (numInByte - 1) - ((id % numInByte) << 1);

        // get the old result, check whether it is failed, don't set pass/ignore if it has failed.
        if (((g_dumpResultArray[dumpResultIndex] >> marginRight) & DUMP_RESULT_TEST_RESULT_MASK) !=
            DUMP_RESULT_TEST_RESULT_FAIL)
        {
            // clear the old result
            g_dumpResultArray[dumpResultIndex] &= ((_UU8)(~((_UU8)(DUMP_RESULT_TEST_RESULT_MASK << marginRight))));
            // set result
            g_dumpResultArray[dumpResultIndex] |= ((_UU8)(result << marginRight));
        }
    }
}
#endif
#endif

#ifdef UNITY_DUMP_RESULT
#if defined(UNITY_DUMP_COMPATIBLE_WITH_EU)
void UnityDumpAssertResult(const _UU8 result, const UNITY_LINE_TYPE lineNumber)
{
    // record assert result
    UnityDumpFillResult(resut, s_IndepAssertId, EU_COUNT_RESETS);
}

void setIndepAssertId(const UNITY_LINE_TYPE indepAssertId)
{
    s_IndepAssertId = indepAssertId;
}
#elif defined(UNITY_DUMP_CASE_RESULT_ONLY)
void UnityDumpCaseResult(const _UU8 result, const UNITY_LINE_TYPE lineNumber)
{
    // record case result
    UnityDumpFillResult(result, (Unity.NumberOfTests - 1), CASE_NUM_IN_BYTE);
}
#else
void UnityDumpCaseResult(const _UU8 result, const UNITY_LINE_TYPE lineNumber)
{
// record all test case result
#ifdef UNMITY_NOT_DUMP_PASS_RESULT
    if (DUMP_RESULT_TEST_RESULT_PASS == result)
    {
        return;
    }
#endif

    // the last one store the test summary
    if (g_dumpResultArrayIndex < (DUMP_RESULT_ARRAY_SIZE - 1))
    {
        DumpTestDataT *pData                     = g_dumpResultArray + g_dumpResultArrayIndex;
        pData->testCaseResult.testResultType     = result;
        pData->testCaseResult.testID             = Unity.CurrentTestId;
        pData->testCaseResult.testFailIgnoreLine = lineNumber;
        g_dumpResultArrayIndex++;
    }
}
#endif
#endif
