/* ==========================================
    Unity Project - A Test Framework for C
    Copyright (c) 2007 Mike Karlesky, Mark VanderVoord, Greg Williams
    [Released under MIT License. Please refer to license.txt for details]
========================================== */

#ifndef UNITY_FRAMEWORK_H
#define UNITY_FRAMEWORK_H

#define UNITY

#include "unity_internals.h"

enum _unity_module
{
    k_unity_i2c                = 1,
    k_unity_acmp               = 2,
    k_unity_adc12              = 3,
    k_unity_adc16              = 4,
    k_unity_cmp                = 5,
    k_unity_cadc               = 6,
    k_unity_dac                = 7,
    k_unity_dac32              = 8,
    k_unity_dcdc               = 9,
    k_unity_enc                = 10,
    k_unity_pdb                = 11,
    k_unity_uart               = 12,
    k_unity_crc                = 13,
    k_unity_ltc                = 14,
    k_unity_rnga               = 15,
    k_unity_trng               = 16,
    k_unity_vref               = 17,
    k_unity_flexbus            = 18,
    k_unity_dspi               = 19,
    k_unity_lpspi              = 20,
    k_unity_sai                = 21,
    k_unity_mmcau              = 22,
    k_unity_sdramc             = 23,
    k_unity_aoi                = 24,
    k_unity_mmdvsq             = 25,
    k_unity_mmau               = 26,
    k_unity_xbar               = 27,
    k_unity_xbara              = 28,
    k_unity_xbarb              = 29,
    k_unity_sim                = 30,
    k_unity_dryice             = 31,
    k_unity_sd                 = 32,
    k_unity_spi                = 33,
    k_unity_mmc                = 34,
    k_unity_sdspi              = 35,
    k_unity_sema42             = 36,
    k_unity_xrdc               = 37,
    k_unity_mu                 = 38,
    k_unity_lmem               = 39,
    k_unity_wdog32             = 40,
    k_unity_cop                = 41,
    k_unity_ewm                = 42,
    k_unity_wdog               = 43,
    k_unity_scg                = 44,
    k_unity_flexcan            = 45,
    k_unity_tsi_v2             = 46,
    k_unity_tsi_v4             = 47,
    k_unity_rtos_uart          = 48,
    k_unity_rtos_lpuart        = 49,
    k_unity_smartcard          = 50,
    k_unity_afe                = 51,
    k_unity_rtos_i2c           = 52,
    k_unity_rtos_spi           = 53,
    k_unity_rtos_dspi          = 54,
    k_unity_mcmgr              = 55,
    k_unity_rpmsg              = 56,
    k_unity_flexio_spi         = 57,
    k_unity_hsadc              = 58,
    k_unity_rdmgr              = 59,
    k_unity_enet               = 60,
    k_unity_qspi               = 61,
    k_unity_dmamux             = 62,
    k_unity_dma                = 63,
    k_unity_edma               = 64,
    k_unity_slcd               = 65,
    k_unity_sysmpu             = 66,
    k_unity_cmt                = 67,
    k_unity_intmux             = 68,
    k_unity_irtc               = 69,
    k_unity_port               = 70,
    k_unity_rtc                = 71,
    k_unity_trgmux             = 72,
    k_unity_qtmr               = 73,
    k_unity_tpm                = 74,
    k_unity_pmc                = 75,
    k_unity_gpio               = 76,
    k_unity_ftm                = 77,
    k_unity_lpsci              = 78,
    k_unity_lpuart             = 79,
    k_unity_pit                = 80,
    k_unity_lpit               = 81,
    k_unity_rcm                = 82,
    k_unity_pwm                = 83,
    k_unity_lptmr              = 84,
    k_unity_lpi2c              = 85,
    k_unity_pwt                = 86,
    k_unity_sdhc               = 87,
    k_unity_tsi_v5             = 88,
    k_unity_llwu               = 89,
    k_unity_flexio             = 90,
    k_unity_lpadc              = 91,
    k_unity_tstmr              = 92,
    k_unity_smc                = 93,
    k_unity_mailbox            = 94,
    k_unity_flashiap           = 95,
    k_unity_fmeas              = 96,
    k_unity_caam               = 97,
    k_unity_flexspi            = 98,
    k_unity_lpc_adc            = 99,
    k_unity_rtos_usart         = 100,
    k_unity_flexio_i2c         = 101,
    k_unity_i2s                = 102,
    k_unity_gint               = 103,
    k_unity_pint               = 104,
    k_unity_mrt                = 105,
    k_unity_ctimer             = 106,
    k_unity_sctimer            = 107,
    k_unity_flexio_uart        = 108,
    k_unity_flexio_i2s         = 109,
    k_unity_aes                = 110,
    k_unity_mmdc               = 111,
    k_unity_rtos_lpsci         = 112,
    k_unity_eeprom             = 113,
    k_unity_sha                = 114,
    k_unity_lcd                = 115,
    k_unity_emc                = 116,
    k_unity_sdif               = 117,
    k_unity_spifi              = 118,
    k_unity_rit                = 119,
    k_unity_irqsteer           = 120,
    k_unity_flexio_mculcd      = 121,
    k_unity_isi                = 122,
    k_unity_adc_12b1msps_sar   = 123,
    k_unity_dac_1              = 124,
    k_unity_cache              = 125,
    k_unity_esai               = 126,
    k_unity_usdhc              = 127,
    k_unity_src                = 128,
    k_unity_tsc                = 129,
    k_unity_ecspi              = 130,
    k_unity_dryice_digital     = 131,
    k_unity_dac12              = 132,
    k_unity_elcdif             = 133,
    k_unity_pxp                = 134,
    k_unity_lpcmp              = 135,
    k_unity_csi                = 136,
    k_unity_cau3               = 137,
    k_unity_adc_5v12b_ll18_015 = 138,
    k_unity_dcdc_1             = 139,
    k_unity_flexram            = 140,
    k_unity_adc_etc            = 141,
    k_unity_dcp                = 142,
    k_unity_semc               = 143,
    k_unity_tmu                = 144,
    k_unity_dpu                = 145,
    k_unity_rdc                = 146,
    k_unity_sema4              = 147,
    k_unity_miniusart          = 148,
    k_unity_minispi            = 149,
    k_unity_prince             = 150,
    k_unity_puf                = 151,
    k_unity_hashcrypt          = 152,
    k_unity_lin                = 153,
    k_unity_lcdif              = 154,
    k_unity_swm                = 155,
    k_unity_powerquad          = 156,
    k_unity_otp_nxh2004        = 157,
    k_unity_rng_nxh2004        = 158,
    k_unity_rsa_nxh2004        = 159,
    k_unity_asrc               = 160,
    k_unity_syscon_nxh2004     = 161,
    k_unity_i3c                = 162,
    k_unity_ftfx               = 163,
    k_unity_dsp                = 164,
    k_unity_common             = 165,
    k_unity_dcic               = 166,
    k_unity_imu                = 167,
    k_unity_maestro            = 168,
    k_unity_clock              = 169,
    k_unity_spc                = 170,
    k_unity_cmc                = 171,
    k_unity_ccm32k             = 172,
    k_unity_wuu                = 173,
    k_unity_sfa                = 174,
    k_unity_pm                 = 175,
    k_unity_dac14              = 176,
};

#define MAKE_UNITY_NUM(unity_module, caseID) (((uint32_t)(unity_module)*10000) + (uint32_t)(caseID))

//-------------------------------------------------------
// Configuration Options
//-------------------------------------------------------
// All options described below should be passed as a compiler flag to all files using Unity. If you must add #defines,
// place them BEFORE the #include above.

// Integers/longs/pointers
//     - Unity assumes 32 bit integers, longs, and pointers by default
//     - If your compiler treats ints of a different size, options are:
//       - define UNITY_USE_LIMITS_H to use limits.h to determine sizes
//       - define UNITY_INT_WIDTH, UNITY_LONG_WIDTH, nand UNITY_POINTER_WIDTH

// Floats
//     - define UNITY_EXCLUDE_FLOAT to disallow floating point comparisons
//     - define UNITY_FLOAT_PRECISION to specify the precision to use when doing TEST_ASSERT_EQUAL_FLOAT
//     - define UNITY_FLOAT_TYPE to specify doubles instead of single precision floats
//     - define UNITY_FLOAT_VERBOSE to print floating point values in errors (uses sprintf)
//     - define UNITY_INCLUDE_DOUBLE to allow double floating point comparisons
//     - define UNITY_EXCLUDE_DOUBLE to disallow double floating point comparisons (default)
//     - define UNITY_DOUBLE_PRECISION to specify the precision to use when doing TEST_ASSERT_EQUAL_DOUBLE
//     - define UNITY_DOUBLE_TYPE to specify something other than double
//     - define UNITY_DOUBLE_VERBOSE to print floating point values in errors (uses sprintf)

// Output
//     - by default, Unity prints to standard out with putchar.  define UNITY_OUTPUT_CHAR(a) with a different function
//     if desired

// Optimization
//     - by default, line numbers are stored in unsigned shorts.  Define UNITY_LINE_TYPE with a different type if your
//     files are huge
//     - by default, test and failure counters are unsigned shorts.  Define UNITY_COUNTER_TYPE with a different type if
//     you want to save space or have more than 65535 Tests.

// Test Cases
//     - define UNITY_SUPPORT_TEST_CASES to include the TEST_CASE macro, though really it's mostly about the runner
//     generator script

// Parameterized Tests
//     - you'll want to create a define of TEST_CASE(...) which basically evaluates to nothing

//-------------------------------------------------------
// Test Running Macros
//-------------------------------------------------------

#define TEST_PROTECT() (setjmp(Unity.AbortFrame) == 0)

#define TEST_ABORT()                  \
    {                                 \
        longjmp(Unity.AbortFrame, 1); \
    }

#ifndef RUN_EXAMPLE
#ifdef UNITY_SHOW_TEST_FILE_PATH
#define RUN_EXAMPLE(func, caseId) UnityDefaultTestRun(&setUp, func, &tearDown, #func, caseId, __FILE__)
#else
#define RUN_EXAMPLE(func, caseId) UnityDefaultTestRun(&setUp, func, &tearDown, #func, caseId)
#endif
#endif

#ifndef RUN_EXAMPLE_EX
#ifdef UNITY_SHOW_TEST_FILE_PATH
#define RUN_EXAMPLE_EX(setUpFunc, func, tearDownFunc, caseId) \
    UnityDefaultTestRun(setUpFunc, func, tearDownFunc, #func, caseId, __FILE__)
#else
#define RUN_EXAMPLE_EX(setUpFunc, func, tearDownFunc, caseId) \
    UnityDefaultTestRun(setUpFunc, func, tearDownFunc, #func, caseId)
#endif
#endif

#define TEST_LINE_NUM   (Unity.CurrentTestLineNumber)
#define TEST_IS_IGNORED (Unity.CurrentTestIgnored)

/* Remove unused ## to fix gcc build error*/
#define FSL_TEST(testCase, message, assertWithoutTEST, param...) \
    SET_INDEP_ASSERT_ID(testCase, __LINE__);                     \
    TEST_##assertWithoutTEST(param)

/* Remove unused ## to fix gcc build error*/
#define FSL_TEST_ASSERT(testCase, message, assertWithoutTEST_ASSERT, param...) \
    SET_INDEP_ASSERT_ID(testCase, __LINE__);                                   \
    TEST_ASSERT_##assertWithoutTEST_ASSERT(param)

//-------------------------------------------------------
// Basic Fail and Ignore
//-------------------------------------------------------

#define TEST_FAIL_MESSAGE(message)   UNITY_TEST_FAIL(__LINE__, message)
#define TEST_FAIL()                  UNITY_TEST_FAIL(__LINE__, NULL)
#define TEST_IGNORE_MESSAGE(message) UNITY_TEST_IGNORE(__LINE__, message)
#define TEST_IGNORE()                UNITY_TEST_IGNORE(__LINE__, NULL)
#define TEST_ONLY()

//-------------------------------------------------------
// Test Asserts (simple)
//-------------------------------------------------------

// Boolean
#define TEST_ASSERT(condition)        UNITY_TEST_ASSERT((condition), __LINE__, " Expression Evaluated To FALSE")
#define TEST_ASSERT_TRUE(condition)   UNITY_TEST_ASSERT((condition), __LINE__, " Expected TRUE Was FALSE")
#define TEST_ASSERT_UNLESS(condition) UNITY_TEST_ASSERT(!(condition), __LINE__, " Expression Evaluated To TRUE")
#define TEST_ASSERT_FALSE(condition)  UNITY_TEST_ASSERT(!(condition), __LINE__, " Expected FALSE Was TRUE")
#define TEST_ASSERT_NULL(pointer)     UNITY_TEST_ASSERT_NULL((pointer), __LINE__, " Expected NULL")
#define TEST_ASSERT_NOT_NULL(pointer) UNITY_TEST_ASSERT_NOT_NULL((pointer), __LINE__, " Expected Non-NULL")

// Integers (of all sizes)
#define TEST_ASSERT_EQUAL_INT(expected, actual)   UNITY_TEST_ASSERT_EQUAL_INT((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_INT8(expected, actual)  UNITY_TEST_ASSERT_EQUAL_INT8((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_INT16(expected, actual) UNITY_TEST_ASSERT_EQUAL_INT16((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_INT32(expected, actual) UNITY_TEST_ASSERT_EQUAL_INT32((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_INT64(expected, actual) UNITY_TEST_ASSERT_EQUAL_INT64((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL(expected, actual)       UNITY_TEST_ASSERT_EQUAL_INT((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_NOT_EQUAL(expected, actual) \
    UNITY_TEST_ASSERT(((expected) != (actual)), __LINE__, " Expected Not-Equal")
#define TEST_ASSERT_EQUAL_UINT(expected, actual)   UNITY_TEST_ASSERT_EQUAL_UINT((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_UINT8(expected, actual)  UNITY_TEST_ASSERT_EQUAL_UINT8((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_UINT16(expected, actual) UNITY_TEST_ASSERT_EQUAL_UINT16((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_UINT32(expected, actual) UNITY_TEST_ASSERT_EQUAL_UINT32((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_UINT64(expected, actual) UNITY_TEST_ASSERT_EQUAL_UINT64((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX(expected, actual)    UNITY_TEST_ASSERT_EQUAL_HEX32((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX8(expected, actual)   UNITY_TEST_ASSERT_EQUAL_HEX8((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX16(expected, actual)  UNITY_TEST_ASSERT_EQUAL_HEX16((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX32(expected, actual)  UNITY_TEST_ASSERT_EQUAL_HEX32((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX64(expected, actual)  UNITY_TEST_ASSERT_EQUAL_HEX64((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_BITS(mask, expected, actual)   UNITY_TEST_ASSERT_BITS((mask), (expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_BITS_HIGH(mask, actual)        UNITY_TEST_ASSERT_BITS((mask), (_UU32)(-1), (actual), __LINE__, NULL)
#define TEST_ASSERT_BITS_LOW(mask, actual)         UNITY_TEST_ASSERT_BITS((mask), (_UU32)(0), (actual), __LINE__, NULL)
#define TEST_ASSERT_BIT_HIGH(bit, actual) \
    UNITY_TEST_ASSERT_BITS(((_UU32)1 << bit), (_UU32)(-1), (actual), __LINE__, NULL)
#define TEST_ASSERT_BIT_LOW(bit, actual) UNITY_TEST_ASSERT_BITS(((_UU32)1 << bit), (_UU32)(0), (actual), __LINE__, NULL)

// Integer Ranges (of all sizes)
#define TEST_ASSERT_INT_WITHIN(delta, expected, actual) \
    UNITY_TEST_ASSERT_INT_WITHIN(delta, expected, actual, __LINE__, NULL)
#define TEST_ASSERT_UINT_WITHIN(delta, expected, actual) \
    UNITY_TEST_ASSERT_UINT_WITHIN(delta, expected, actual, __LINE__, NULL)
#define TEST_ASSERT_HEX_WITHIN(delta, expected, actual) \
    UNITY_TEST_ASSERT_HEX32_WITHIN(delta, expected, actual, __LINE__, NULL)
#define TEST_ASSERT_HEX8_WITHIN(delta, expected, actual) \
    UNITY_TEST_ASSERT_HEX8_WITHIN(delta, expected, actual, __LINE__, NULL)
#define TEST_ASSERT_HEX16_WITHIN(delta, expected, actual) \
    UNITY_TEST_ASSERT_HEX16_WITHIN(delta, expected, actual, __LINE__, NULL)
#define TEST_ASSERT_HEX32_WITHIN(delta, expected, actual) \
    UNITY_TEST_ASSERT_HEX32_WITHIN(delta, expected, actual, __LINE__, NULL)
#define TEST_ASSERT_HEX64_WITHIN(delta, expected, actual) \
    UNITY_TEST_ASSERT_HEX64_WITHIN(delta, expected, actual, __LINE__, NULL)

// Structs and Strings
#define TEST_ASSERT_EQUAL_PTR(expected, actual)    UNITY_TEST_ASSERT_EQUAL_PTR((expected), (actual), __LINE__, NULL)
#define TEST_ASSERT_EQUAL_STRING(expected, actual) UNITY_TEST_ASSERT_EQUAL_STRING(expected, actual, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_MEMORY(expected, actual, len) \
    UNITY_TEST_ASSERT_EQUAL_MEMORY(expected, actual, len, __LINE__, NULL)

// Arrays
#define TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, num_elements) \
    UNITY_TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, num_elements, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_INT8_ARRAY(expected, actual, num_elements) \
    UNITY_TEST_ASSERT_EQUAL_INT8_ARRAY(expected, actual, num_elements, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_INT16_ARRAY(expected, actual, num_elements) \
    UNITY_TEST_ASSERT_EQUAL_INT16_ARRAY(expected, actual, num_elements, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_INT32_ARRAY(expected, actual, num_elements) \
    UNITY_TEST_ASSERT_EQUAL_INT32_ARRAY(expected, actual, num_elements, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_INT64_ARRAY(expected, actual, num_elements) \
    UNITY_TEST_ASSERT_EQUAL_INT64_ARRAY(expected, actual, num_elements, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_UINT_ARRAY(expected, actual, num_elements) \
    UNITY_TEST_ASSERT_EQUAL_UINT_ARRAY(expected, actual, num_elements, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, num_elements) \
    UNITY_TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, num_elements, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, actual, num_elements) \
    UNITY_TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, actual, num_elements, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, actual, num_elements) \
    UNITY_TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, actual, num_elements, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_UINT64_ARRAY(expected, actual, num_elements) \
    UNITY_TEST_ASSERT_EQUAL_UINT64_ARRAY(expected, actual, num_elements, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX_ARRAY(expected, actual, num_elements) \
    UNITY_TEST_ASSERT_EQUAL_HEX32_ARRAY(expected, actual, num_elements, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, actual, num_elements) \
    UNITY_TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, actual, num_elements, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX16_ARRAY(expected, actual, num_elements) \
    UNITY_TEST_ASSERT_EQUAL_HEX16_ARRAY(expected, actual, num_elements, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX32_ARRAY(expected, actual, num_elements) \
    UNITY_TEST_ASSERT_EQUAL_HEX32_ARRAY(expected, actual, num_elements, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_HEX64_ARRAY(expected, actual, num_elements) \
    UNITY_TEST_ASSERT_EQUAL_HEX64_ARRAY(expected, actual, num_elements, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_PTR_ARRAY(expected, actual, num_elements) \
    UNITY_TEST_ASSERT_EQUAL_PTR_ARRAY(expected, actual, num_elements, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_STRING_ARRAY(expected, actual, num_elements) \
    UNITY_TEST_ASSERT_EQUAL_STRING_ARRAY(expected, actual, num_elements, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, actual, len, num_elements) \
    UNITY_TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, actual, len, num_elements, __LINE__, NULL)

// Floating Point (If Enabled)
#define TEST_ASSERT_FLOAT_WITHIN(delta, expected, actual) \
    UNITY_TEST_ASSERT_FLOAT_WITHIN(delta, expected, actual, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_FLOAT(expected, actual) UNITY_TEST_ASSERT_EQUAL_FLOAT(expected, actual, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, actual, num_elements) \
    UNITY_TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, actual, num_elements, __LINE__, NULL)
#define TEST_ASSERT_FLOAT_IS_INF(actual)     UNITY_TEST_ASSERT_FLOAT_IS_INF(actual, __LINE__, NULL)
#define TEST_ASSERT_FLOAT_IS_NEG_INF(actual) UNITY_TEST_ASSERT_FLOAT_IS_NEG_INF(actual, __LINE__, NULL)
#define TEST_ASSERT_FLOAT_IS_NAN(actual)     UNITY_TEST_ASSERT_FLOAT_IS_NAN(actual, __LINE__, NULL)

// Double (If Enabled)
#define TEST_ASSERT_DOUBLE_WITHIN(delta, expected, actual) \
    UNITY_TEST_ASSERT_DOUBLE_WITHIN(delta, expected, actual, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_DOUBLE(expected, actual) UNITY_TEST_ASSERT_EQUAL_DOUBLE(expected, actual, __LINE__, NULL)
#define TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected, actual, num_elements) \
    UNITY_TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected, actual, num_elements, __LINE__, NULL)
#define TEST_ASSERT_DOUBLE_IS_INF(actual)     UNITY_TEST_ASSERT_DOUBLE_IS_INF(actual, __LINE__, NULL)
#define TEST_ASSERT_DOUBLE_IS_NEG_INF(actual) UNITY_TEST_ASSERT_DOUBLE_IS_NEG_INF(actual, __LINE__, NULL)
#define TEST_ASSERT_DOUBLE_IS_NAN(actual)     UNITY_TEST_ASSERT_DOUBLE_IS_NAN(actual, __LINE__, NULL)

//-------------------------------------------------------
// Test Asserts (with additional messages)
//-------------------------------------------------------

// Boolean
#define TEST_ASSERT_MESSAGE(condition, message)        UNITY_TEST_ASSERT((condition), __LINE__, message)
#define TEST_ASSERT_TRUE_MESSAGE(condition, message)   UNITY_TEST_ASSERT((condition), __LINE__, message)
#define TEST_ASSERT_UNLESS_MESSAGE(condition, message) UNITY_TEST_ASSERT(!(condition), __LINE__, message)
#define TEST_ASSERT_FALSE_MESSAGE(condition, message)  UNITY_TEST_ASSERT(!(condition), __LINE__, message)
#define TEST_ASSERT_NULL_MESSAGE(pointer, message)     UNITY_TEST_ASSERT_NULL((pointer), __LINE__, message)
#define TEST_ASSERT_NOT_NULL_MESSAGE(pointer, message) UNITY_TEST_ASSERT_NOT_NULL((pointer), __LINE__, message)

// Integers (of all sizes)
#define TEST_ASSERT_EQUAL_INT_MESSAGE(expected, actual, message) \
    UNITY_TEST_ASSERT_EQUAL_INT((expected), (actual), __LINE__, message)
#define TEST_ASSERT_EQUAL_INT8_MESSAGE(expected, actual, message) \
    UNITY_TEST_ASSERT_EQUAL_INT8((expected), (actual), __LINE__, message)
#define TEST_ASSERT_EQUAL_INT16_MESSAGE(expected, actual, message) \
    UNITY_TEST_ASSERT_EQUAL_INT16((expected), (actual), __LINE__, message)
#define TEST_ASSERT_EQUAL_INT32_MESSAGE(expected, actual, message) \
    UNITY_TEST_ASSERT_EQUAL_INT32((expected), (actual), __LINE__, message)
#define TEST_ASSERT_EQUAL_INT64_MESSAGE(expected, actual, message) \
    UNITY_TEST_ASSERT_EQUAL_INT64((expected), (actual), __LINE__, message)
#define TEST_ASSERT_EQUAL_MESSAGE(expected, actual, message) \
    UNITY_TEST_ASSERT_EQUAL_INT((expected), (actual), __LINE__, message)
#define TEST_ASSERT_NOT_EQUAL_MESSAGE(expected, actual, message) \
    UNITY_TEST_ASSERT(((expected) != (actual)), __LINE__, message)
#define TEST_ASSERT_EQUAL_UINT_MESSAGE(expected, actual, message) \
    UNITY_TEST_ASSERT_EQUAL_UINT((expected), (actual), __LINE__, message)
#define TEST_ASSERT_EQUAL_UINT8_MESSAGE(expected, actual, message) \
    UNITY_TEST_ASSERT_EQUAL_UINT8((expected), (actual), __LINE__, message)
#define TEST_ASSERT_EQUAL_UINT16_MESSAGE(expected, actual, message) \
    UNITY_TEST_ASSERT_EQUAL_UINT16((expected), (actual), __LINE__, message)
#define TEST_ASSERT_EQUAL_UINT32_MESSAGE(expected, actual, message) \
    UNITY_TEST_ASSERT_EQUAL_UINT32((expected), (actual), __LINE__, message)
#define TEST_ASSERT_EQUAL_UINT64_MESSAGE(expected, actual, message) \
    UNITY_TEST_ASSERT_EQUAL_UINT64((expected), (actual), __LINE__, message)
#define TEST_ASSERT_EQUAL_HEX_MESSAGE(expected, actual, message) \
    UNITY_TEST_ASSERT_EQUAL_HEX32((expected), (actual), __LINE__, message)
#define TEST_ASSERT_EQUAL_HEX8_MESSAGE(expected, actual, message) \
    UNITY_TEST_ASSERT_EQUAL_HEX8((expected), (actual), __LINE__, message)
#define TEST_ASSERT_EQUAL_HEX16_MESSAGE(expected, actual, message) \
    UNITY_TEST_ASSERT_EQUAL_HEX16((expected), (actual), __LINE__, message)
#define TEST_ASSERT_EQUAL_HEX32_MESSAGE(expected, actual, message) \
    UNITY_TEST_ASSERT_EQUAL_HEX32((expected), (actual), __LINE__, message)
#define TEST_ASSERT_EQUAL_HEX64_MESSAGE(expected, actual, message) \
    UNITY_TEST_ASSERT_EQUAL_HEX64((expected), (actual), __LINE__, message)
#define TEST_ASSERT_BITS_MESSAGE(mask, expected, actual, message) \
    UNITY_TEST_ASSERT_BITS((mask), (expected), (actual), __LINE__, message)
#define TEST_ASSERT_BITS_HIGH_MESSAGE(mask, actual, message) \
    UNITY_TEST_ASSERT_BITS((mask), (_UU32)(-1), (actual), __LINE__, message)
#define TEST_ASSERT_BITS_LOW_MESSAGE(mask, actual, message) \
    UNITY_TEST_ASSERT_BITS((mask), (_UU32)(0), (actual), __LINE__, message)
#define TEST_ASSERT_BIT_HIGH_MESSAGE(bit, actual, message) \
    UNITY_TEST_ASSERT_BITS(((_UU32)1 << bit), (_UU32)(-1), (actual), __LINE__, message)
#define TEST_ASSERT_BIT_LOW_MESSAGE(bit, actual, message) \
    UNITY_TEST_ASSERT_BITS(((_UU32)1 << bit), (_UU32)(0), (actual), __LINE__, message)

// Integer Ranges (of all sizes)
#define TEST_ASSERT_INT_WITHIN_MESSAGE(delta, expected, actual, message) \
    UNITY_TEST_ASSERT_INT_WITHIN(delta, expected, actual, __LINE__, message)
#define TEST_ASSERT_UINT_WITHIN_MESSAGE(delta, expected, actual, message) \
    UNITY_TEST_ASSERT_UINT_WITHIN(delta, expected, actual, __LINE__, message)
#define TEST_ASSERT_HEX_WITHIN_MESSAGE(delta, expected, actual, message) \
    UNITY_TEST_ASSERT_HEX32_WITHIN(delta, expected, actual, __LINE__, message)
#define TEST_ASSERT_HEX8_WITHIN_MESSAGE(delta, expected, actual, message) \
    UNITY_TEST_ASSERT_HEX8_WITHIN(delta, expected, actual, __LINE__, message)
#define TEST_ASSERT_HEX16_WITHIN_MESSAGE(delta, expected, actual, message) \
    UNITY_TEST_ASSERT_HEX16_WITHIN(delta, expected, actual, __LINE__, message)
#define TEST_ASSERT_HEX32_WITHIN_MESSAGE(delta, expected, actual, message) \
    UNITY_TEST_ASSERT_HEX32_WITHIN(delta, expected, actual, __LINE__, message)
#define TEST_ASSERT_HEX64_WITHIN_MESSAGE(delta, expected, actual, message) \
    UNITY_TEST_ASSERT_HEX64_WITHIN(delta, expected, actual, __LINE__, message)

// Structs and Strings
#define TEST_ASSERT_EQUAL_PTR_MESSAGE(expected, actual, message) \
    UNITY_TEST_ASSERT_EQUAL_PTR(expected, actual, __LINE__, message)
#define TEST_ASSERT_EQUAL_STRING_MESSAGE(expected, actual, message) \
    UNITY_TEST_ASSERT_EQUAL_STRING(expected, actual, __LINE__, message)
#define TEST_ASSERT_EQUAL_MEMORY_MESSAGE(expected, actual, len, message) \
    UNITY_TEST_ASSERT_EQUAL_MEMORY(expected, actual, len, __LINE__, message)

// Arrays
#define TEST_ASSERT_EQUAL_INT_ARRAY_MESSAGE(expected, actual, num_elements, message) \
    UNITY_TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, num_elements, __LINE__, message)
#define TEST_ASSERT_EQUAL_INT8_ARRAY_MESSAGE(expected, actual, num_elements, message) \
    UNITY_TEST_ASSERT_EQUAL_INT8_ARRAY(expected, actual, num_elements, __LINE__, message)
#define TEST_ASSERT_EQUAL_INT16_ARRAY_MESSAGE(expected, actual, num_elements, message) \
    UNITY_TEST_ASSERT_EQUAL_INT16_ARRAY(expected, actual, num_elements, __LINE__, message)
#define TEST_ASSERT_EQUAL_INT32_ARRAY_MESSAGE(expected, actual, num_elements, message) \
    UNITY_TEST_ASSERT_EQUAL_INT32_ARRAY(expected, actual, num_elements, __LINE__, message)
#define TEST_ASSERT_EQUAL_INT64_ARRAY_MESSAGE(expected, actual, num_elements, message) \
    UNITY_TEST_ASSERT_EQUAL_INT64_ARRAY(expected, actual, num_elements, __LINE__, message)
#define TEST_ASSERT_EQUAL_UINT_ARRAY_MESSAGE(expected, actual, num_elements, message) \
    UNITY_TEST_ASSERT_EQUAL_UINT_ARRAY(expected, actual, num_elements, __LINE__, message)
#define TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(expected, actual, num_elements, message) \
    UNITY_TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, num_elements, __LINE__, message)
#define TEST_ASSERT_EQUAL_UINT16_ARRAY_MESSAGE(expected, actual, num_elements, message) \
    UNITY_TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, actual, num_elements, __LINE__, message)
#define TEST_ASSERT_EQUAL_UINT32_ARRAY_MESSAGE(expected, actual, num_elements, message) \
    UNITY_TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, actual, num_elements, __LINE__, message)
#define TEST_ASSERT_EQUAL_UINT64_ARRAY_MESSAGE(expected, actual, num_elements, message) \
    UNITY_TEST_ASSERT_EQUAL_UINT64_ARRAY(expected, actual, num_elements, __LINE__, message)
#define TEST_ASSERT_EQUAL_HEX_ARRAY_MESSAGE(expected, actual, num_elements, message) \
    UNITY_TEST_ASSERT_EQUAL_HEX32_ARRAY(expected, actual, num_elements, __LINE__, message)
#define TEST_ASSERT_EQUAL_HEX8_ARRAY_MESSAGE(expected, actual, num_elements, message) \
    UNITY_TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, actual, num_elements, __LINE__, message)
#define TEST_ASSERT_EQUAL_HEX16_ARRAY_MESSAGE(expected, actual, num_elements, message) \
    UNITY_TEST_ASSERT_EQUAL_HEX16_ARRAY(expected, actual, num_elements, __LINE__, message)
#define TEST_ASSERT_EQUAL_HEX32_ARRAY_MESSAGE(expected, actual, num_elements, message) \
    UNITY_TEST_ASSERT_EQUAL_HEX32_ARRAY(expected, actual, num_elements, __LINE__, message)
#define TEST_ASSERT_EQUAL_HEX64_ARRAY_MESSAGE(expected, actual, num_elements, message) \
    UNITY_TEST_ASSERT_EQUAL_HEX64_ARRAY(expected, actual, num_elements, __LINE__, message)
#define TEST_ASSERT_EQUAL_PTR_ARRAY_MESSAGE(expected, actual, num_elements, message) \
    UNITY_TEST_ASSERT_EQUAL_PTR_ARRAY(expected, actual, num_elements, __LINE__, message)
#define TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected, actual, num_elements, message) \
    UNITY_TEST_ASSERT_EQUAL_STRING_ARRAY(expected, actual, num_elements, __LINE__, message)
#define TEST_ASSERT_EQUAL_MEMORY_ARRAY_MESSAGE(expected, actual, len, num_elements, message) \
    UNITY_TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, actual, len, num_elements, __LINE__, message)

// Floating Point (If Enabled)
#define TEST_ASSERT_FLOAT_WITHIN_MESSAGE(delta, expected, actual, message) \
    UNITY_TEST_ASSERT_FLOAT_WITHIN(delta, expected, actual, __LINE__, message)
#define TEST_ASSERT_EQUAL_FLOAT_MESSAGE(expected, actual, message) \
    UNITY_TEST_ASSERT_EQUAL_FLOAT(expected, actual, __LINE__, message)
#define TEST_ASSERT_EQUAL_FLOAT_ARRAY_MESSAGE(expected, actual, num_elements, message) \
    UNITY_TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, actual, num_elements, __LINE__, message)
/*
Error[Pm046]: floating point values shall not be tested for exact equality or inequality (MISRA C 2004 rule 13.3)
#define TEST_ASSERT_FLOAT_IS_INF_MESSAGE(actual, message) UNITY_TEST_ASSERT_FLOAT_IS_INF(actual, __LINE__, message)
#define TEST_ASSERT_FLOAT_IS_NEG_INF_MESSAGE(actual, message)
UNITY_TEST_ASSERT_FLOAT_IS_NEG_INF(actual, __LINE__, message)
#define TEST_ASSERT_FLOAT_IS_NAN_MESSAGE(actual, message) UNITY_TEST_ASSERT_FLOAT_IS_NAN(actual, __LINE__, message)
*/
// Double (If Enabled)
#define TEST_ASSERT_DOUBLE_WITHIN_MESSAGE(delta, expected, actual, message) \
    UNITY_TEST_ASSERT_DOUBLE_WITHIN(delta, expected, actual, __LINE__, message)
#define TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(expected, actual, message) \
    UNITY_TEST_ASSERT_EQUAL_DOUBLE(expected, actual, __LINE__, message)
#define TEST_ASSERT_EQUAL_DOUBLE_ARRAY_MESSAGE(expected, actual, num_elements, message) \
    UNITY_TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected, actual, num_elements, __LINE__, message)
/*
Error[Pm046]: floating point values shall not be tested for exact equality or inequality (MISRA C 2004 rule 13.3)
#define TEST_ASSERT_DOUBLE_IS_INF_MESSAGE(actual, message) UNITY_TEST_ASSERT_DOUBLE_IS_INF(actual, __LINE__, message)
#define TEST_ASSERT_DOUBLE_IS_NEG_INF_MESSAGE(actual, message)
UNITY_TEST_ASSERT_DOUBLE_IS_NEG_INF(actual, __LINE__, message)
#define TEST_ASSERT_DOUBLE_IS_NAN_MESSAGE(actual, message) UNITY_TEST_ASSERT_DOUBLE_IS_NAN(actual, __LINE__, message)
*/
#ifdef DO_GCOV_COVERAGE
void static_init(void);
int _read(int file, char *ptr, int len);
int _write(int file, char *ptr, int len);
#endif
#endif
