/*--------------------------------------------------------------------------*/
/* Copyright 2022-2023 NXP                                                  */
/*                                                                          */
/* NXP Confidential. This software is owned or controlled by NXP and may    */
/* only be used strictly in accordance with the applicable license terms.   */
/* By expressly accepting such terms or by downloading, installing,         */
/* activating and/or otherwise using the software, you are agreeing that    */
/* you have read, and that you agree to comply with and are bound by, such  */
/* license terms. If you do not agree to be bound by the applicable license */
/* terms, then you may not retain, install, activate or otherwise use the   */
/* software.                                                                */
/*--------------------------------------------------------------------------*/
/* Security Classification:  Company Confidential                           */
/*--------------------------------------------------------------------------*/

#ifndef MCUX_CSSL_ANALYSIS_H_
#define MCUX_CSSL_ANALYSIS_H_

#define MCUX_CSSL_ANALYSIS_STR(a) #a
#define MCUX_CSSL_ANALYSIS_EMPTY()
#define MCUX_CSSL_ANALYSIS_DEFER(id) id MCUX_CSSL_ANALYSIS_EMPTY()
#define MCUX_CSSL_ANALYSIS_EXPAND(...) __VA_ARGS__

#define MCUX_CSSL_ANALYSIS_PRAGMA(x) _Pragma(#x)

/* Example of common patterns, with either just predefined rationale, or a combination of discards. */
#define MCUX_CSSL_ANALYSIS_START_PATTERN_HW_READ() \
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_CAST_TO_OBJECT("Read from a HW peripheral")
#define MCUX_CSSL_ANALYSIS_STOP_PATTERN_HW_READ() \
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_CAST_TO_OBJECT()

#define MCUX_CSSL_ANALYSIS_START_PATTERN_HW_WRITE() \
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_VOLATILE("Write to a HW peripheral") \
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_CAST_TO_OBJECT("Write to a HW peripheral")

#define MCUX_CSSL_ANALYSIS_STOP_PATTERN_HW_WRITE() \
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_CAST_TO_OBJECT() \
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_VOLATILE()

/* Example of basic violation suppression */
#define MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_VOLATILE(rationale) \
  MCUX_CSSL_ANALYSIS_CLANG_START_SUPPRESS_WARNING("-Wcast-qual", rationale) \
  MCUX_CSSL_ANALYSIS_GHS_START_SUPPRESS_WARNING(1836, rationale) \
  MCUX_CSSL_ANALYSIS_COVERITY_START_SUPPRESS_MISRA(11.8, rationale)


#define MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_VOLATILE() \
  MCUX_CSSL_ANALYSIS_COVERITY_STOP_SUPPRESS_MISRA("11.8") \
  MCUX_CSSL_ANALYSIS_GHS_STOP_SUPPRESS_WARNING("1836") \
  MCUX_CSSL_ANALYSIS_CLANG_STOP_SUPPRESS_WARNING("-Wcast-qual")

#define MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_FALSE_POSITIVE_10_1() \
  MCUX_CSSL_ANALYSIS_COVERITY_STOP_SUPPRESS_MISRA(10.1) \

#define MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_FALSE_POSITIVE_14_3() \
  MCUX_CSSL_ANALYSIS_COVERITY_STOP_SUPPRESS_MISRA(14.3) \

#define MCUX_CSSL_ANALYSIS_START_SUPPRESS_FALSE_POSITIVE_10_1(rationale)  \
  MCUX_CSSL_ANALYSIS_COVERITY_START_SUPPRESS_MISRA(10.1, rationale) \

#define MCUX_CSSL_ANALYSIS_START_SUPPRESS_FALSE_POSITIVE_14_3(rationale)  \
  MCUX_CSSL_ANALYSIS_COVERITY_START_SUPPRESS_MISRA(14.3, rationale) \

/* Tool specific handling: Coverity MISRA */
/* TODO: functionality still to be verified for ICCARM as part of CLNS-5992 */
#if defined(__ghs__) || defined(__gcc__) || defined(__ICCARM__) || defined(__GNUC__)

#define MCUX_CSSL_ANALYSIS_COVERITY_START_SUPPRESS_MISRA(rule_identifier, rationale) \
  MCUX_CSSL_ANALYSIS_EXPAND(MCUX_CSSL_ANALYSIS_DEFER(MCUX_CSSL_ANALYSIS_PRAGMA)(coverity compliance block deviate MCUX_CSSL_ANALYSIS_STR(MISRA C-2012 Rule rule_identifier) MCUX_CSSL_ANALYSIS_STR(rationale)))

#define MCUX_CSSL_ANALYSIS_COVERITY_STOP_SUPPRESS_MISRA(rule_identifier) \
  MCUX_CSSL_ANALYSIS_EXPAND(MCUX_CSSL_ANALYSIS_DEFER(MCUX_CSSL_ANALYSIS_PRAGMA)(coverity compliance end_block MCUX_CSSL_ANALYSIS_STR(MISRA C-2012 Rule rule_identifier)))

  
#elif defined(__clang__) || defined(__CC_ARM) || (defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
  /* ... */
#else
  #error Unsupported toolchain, \
   Please add a proper definition for MCUX_CSSL_ANALYSIS_COVERITY_*_SUPPRESS_MISRA for your toolchain
#endif

/* Tool specific handling: Clang warnings */
#if defined(__clang__)
#define MCUX_CSSL_ANALYSIS_CLANG_START_SUPPRESS_WARNING(warning_identifier, rationale) \
  _Pragma("clang diagnostic push") \
  _Pragma("clang diagnostic ignored \"" warning_identifier "\"")
#define MCUX_CSSL_ANALYSIS_CLANG_STOP_SUPPRESS_WARNING(warning_identifier) \
  _Pragma("clang diagnostic pop")
#else
#define MCUX_CSSL_ANALYSIS_CLANG_START_SUPPRESS_WARNING(warning_identifier, rationale)
#define MCUX_CSSL_ANALYSIS_CLANG_STOP_SUPPRESS_WARNING(warning_identifier)
#endif

/* Tool specific handling: GHS warnings */
#ifdef __ghs__
#define MCUX_CSSL_ANALYSIS_GHS_START_SUPPRESS_WARNING(warning_identifier, rationale) \
  _Pragma("ghs nowarning " ## warning_identifier)
#define MCUX_CSSL_ANALYSIS_GHS_STOP_SUPPRESS_WARNING(warning_identifier) \
  _Pragma("ghs endnowarning")
#else
#define MCUX_CSSL_ANALYSIS_GHS_START_SUPPRESS_WARNING(warning_identifier, rationale)
#define MCUX_CSSL_ANALYSIS_GHS_STOP_SUPPRESS_WARNING(warning_identifier)
#endif

#endif /* MCUX_CSSL_CORE_ANALYSIS_H_ */
