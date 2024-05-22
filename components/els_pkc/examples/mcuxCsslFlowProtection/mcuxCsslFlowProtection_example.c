/*--------------------------------------------------------------------------*/
/* Copyright 2020-2023 NXP                                                  */
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


#define MCUX_CSSL_FP_ASSERT_CALLBACK() assertCallback()


#include <mcuxCsslExamples.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxCsslFlowProtection_FunctionIdentifiers.h>

/* Example global SC */
static volatile uint32_t testVariable = 0u; 

/* Protected function pointer type */
MCUX_CSSL_FP_FUNCTION_POINTER(functionPointerType_t,
typedef MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) (*functionPointerType_t)(void));


/****************************************************************************/
/* Function declaration                                                     */
/****************************************************************************/

uint32_t functionOnly(void);
void assertCallback(void);


/****************************************************************************/
/* Protected function declarations                                          */
/****************************************************************************/

MCUX_CSSL_FP_FUNCTION_DECL(functionOnly0) /* Important: no semicolon here! */
MCUX_CSSL_FP_PROTECTED_TYPE(void) functionOnly0(void);

MCUX_CSSL_FP_FUNCTION_DECL(functionOnly1) /* Important: no semicolon here! */
MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) functionOnly1(void);

MCUX_CSSL_FP_FUNCTION_DECL(functionOnly2, functionPointerType_t) /* Important: no semicolon here & adding functionPointerType info! */
MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) functionOnly2(void);

MCUX_CSSL_FP_FUNCTION_DECL(functionCall) /* Important: no semicolon here! */
MCUX_CSSL_FP_PROTECTED_TYPE(void) functionCall(void);

MCUX_CSSL_FP_FUNCTION_DECL(functionCalls) /* Important: no semicolon here! */
MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) functionCalls(void);

MCUX_CSSL_FP_FUNCTION_DECL(functionLoop) /* Important: no semicolon here! */
MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) functionLoop(uint32_t count);

MCUX_CSSL_FP_FUNCTION_DECL(functionBranch) /* Important: no semicolon here! */
MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) functionBranch(uint32_t arg);

MCUX_CSSL_FP_FUNCTION_DECL(functionSwitch) /* Important: no semicolon here! */
MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) functionSwitch(uint32_t arg);

MCUX_CSSL_FP_FUNCTION_DECL(functionAssert) /* Important: no semicolon here! */
MCUX_CSSL_FP_PROTECTED_TYPE(void) functionAssert(void);



/****************************************************************************/
/* Function definitions                                                     */
/****************************************************************************/

uint32_t functionOnly(void)
{
  return 0xC0DEu;
}

void assertCallback(void)
{
  testVariable += 1UL;
}

/****************************************************************************/
/* Protected function definitions                                           */
/****************************************************************************/

/*
 * Example for a very basic protected function (without any protected code).
 */
MCUX_CSSL_FP_FUNCTION_DEF(functionOnly0) /* Important: no semicolon here! */
MCUX_CSSL_FP_PROTECTED_TYPE(void) functionOnly0(void)
{
  /* FUNCTION_ENTRY initializes the flow protection for this function. */
  MCUX_CSSL_FP_FUNCTION_ENTRY(functionOnly0);

  /* FUNCTION_EXIT encodes the result together with a protection token in the
   * return code. */
  MCUX_CSSL_FP_FUNCTION_EXIT_VOID(functionOnly0);
}

/*
 * Example of a function that performs a protected function call.
 */
MCUX_CSSL_FP_FUNCTION_DEF(functionCall) /* Important: no semicolon here! */
MCUX_CSSL_FP_PROTECTED_TYPE(void) functionCall(void)
{
  /* The protected function that will be called must be declared as expected,
   * either in the FUNCTION_ENTRY, FUNCTION_EXIT, EXPECT, or an event that
   * accepts expectation declarations.
   * FUNCTION_ENTRY can be used with and without providing expectations. */
  MCUX_CSSL_FP_FUNCTION_ENTRY(functionCall,
  	MCUX_CSSL_FP_FUNCTION_CALLED(functionOnly0)
  );

  /* A call to a protected function must be wrapped using FUNCTION_CALL. This
   * is needed to capture and process the protection token, returned by the
   * function that is called, and inform the flow protection mechanism of this
   * function call event. */
  MCUX_CSSL_FP_FUNCTION_CALL_VOID(functionOnly0());

  /* FUNCTION_EXIT can be used with and without providing expectations. */
  MCUX_CSSL_FP_FUNCTION_EXIT_VOID(functionCall);
}

/* Another simple protected function, used in functionCalls example. */
MCUX_CSSL_FP_FUNCTION_DEF(functionOnly1)
MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) functionOnly1(void)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(functionOnly1);
  MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(functionOnly1, 1u, 0xFAFAu);
}

/* Another simple protected function, used in functionCalls example. */
MCUX_CSSL_FP_FUNCTION_DEF(functionOnly2, functionPointerType_t)
MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) functionOnly2(void)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(functionOnly2);
  MCUX_CSSL_FP_FUNCTION_EXIT(functionOnly2, 2u);
}

/*
 * Example of a function that performs multiple function calls.
 */
MCUX_CSSL_FP_FUNCTION_DEF(functionCalls) /* Important: no semicolon here! */
MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) functionCalls(void)
{
  /* FUNCTION_ENTRY can be used with multiple expectations. */
  MCUX_CSSL_FP_FUNCTION_ENTRY(functionCalls,
  	MCUX_CSSL_FP_FUNCTION_CALLED(functionOnly0),
  	MCUX_CSSL_FP_FUNCTION_CALLED(functionOnly1)
  );

  /* Multiple calls to protected functions.
   * Note: the provided result variables must be unique. */
  MCUX_CSSL_FP_FUNCTION_CALL_VOID(functionOnly0());
  MCUX_CSSL_FP_FUNCTION_CALL(result1, functionOnly1());
  MCUX_CSSL_FP_FUNCTION_CALL(result2, functionOnly2());

  /* EXPECT can be used to provide expectations in the body of the function.
   * Note: using it with a single expectation is considered unsecure. */
  MCUX_CSSL_FP_EXPECT(
    MCUX_CSSL_FP_FUNCTION_CALLED(functionOnly0)
  );

  /* It is still possible to call unprotected functions. */
  uint32_t result = functionOnly();

  /* Another block of protected function calls.
   * Note: the provided result variables must be unique. */
  MCUX_CSSL_FP_FUNCTION_CALL_VOID(functionOnly0());
  MCUX_CSSL_FP_FUNCTION_CALL(result1_, functionOnly1());
  MCUX_CSSL_FP_FUNCTION_CALL(result2_, functionOnly2());

  /* EXPECT can also be used with multiple expectations. */
  MCUX_CSSL_FP_EXPECT(
    MCUX_CSSL_FP_FUNCTION_CALLED(functionOnly0),
    MCUX_CSSL_FP_FUNCTION_CALLED(functionOnly2)
  );

  /* Another protected function call */
  MCUX_CSSL_FP_FUNCTION_CALL_VOID(functionOnly0());

  result += result1 + result2 + result1_ + result2_;
  /* FUNCTION_EXIT can also be used with multiple expectations. */
  MCUX_CSSL_FP_FUNCTION_EXIT(functionCalls, result,
  	MCUX_CSSL_FP_FUNCTION_CALLED(functionOnly1),
  	MCUX_CSSL_FP_FUNCTION_CALLED(functionOnly2)
  );

  /* In this function we have had various calls, i.e. call events:
   *  - functionOnly0 (3 times)
   *  - functionOnly1 (2 times)
   *  - functionOnly2 (2 times)
   *  - functionOnly (unprotected, so not considered as a protected event)
   *
   * Every one of these events needs to be declared as expected for the flow
   * protection mechanism to be able operate properly, in this example:
   *  - functionOnly0, in FUNCTION_ENTRY and twice in EXPECT
   *  - functionOnly1, in FUNCTION_EXIT and EXPECT
   *  - functionOnly2, in FUNCTION_EXIT and EXPECT
   *  - functionOnly, no need to declare, since unprotected.
   */
}

/*
 * Example of a function that performs a protected loop.
 */
MCUX_CSSL_FP_FUNCTION_DEF(functionLoop) /* Important: no semicolon here! */
MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) functionLoop(uint32_t count)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(functionLoop);

  /* Every protected entity needs to be declared, hence also this loop. */
  MCUX_CSSL_FP_LOOP_DECL(loop);
  for (uint32_t i = 0; i < count; ++i)
  {
    /* Within the protected loop, a LOOP_ITERATION event must be placed, to
     * indicate to the flow protection mechanism that a loop iteration event
     * occured. */
    MCUX_CSSL_FP_LOOP_ITERATION(loop);
  }

  /* For a protected loop the expectation is that it should perform an certain
   * number of iterations. This can be indicated to the flow protection
   * mechanism by using the LOOP_ITERATIONS expectation. */
  MCUX_CSSL_FP_FUNCTION_EXIT(functionLoop, 0xC0DEu,
    MCUX_CSSL_FP_LOOP_ITERATIONS(loop, count)
  );
}

/*
 * Example of a function that performs a protected branch.
 */
MCUX_CSSL_FP_FUNCTION_DEF(functionBranch) /* Important: no semicolon here! */
MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) functionBranch(uint32_t arg)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(functionBranch);

  /* Every protected entity needs to be declared, hence also this branch. */
  MCUX_CSSL_FP_BRANCH_DECL(argCheck);
  uint32_t result;
  if (0xC0DEu == arg)
  {
    result = 0xC0DEu;

    /* Within the positive scenario of a protected branch, a BRANCH_POSITIVE
     * event must be placed, to indicate to the flow protection mechanism that
     * the positive scenario of the protected branch has been executed. */
    MCUX_CSSL_FP_BRANCH_POSITIVE(argCheck);
  }
  else
  {
    result = 0xDEADu;

    /* Within the negative scenario of a protected branch, a BRANCH_NEGATIVE
     * event must be placed, to indicate to the flow protection mechanism that
     * the negative scenario of the protected branch has been executed. */
    MCUX_CSSL_FP_BRANCH_NEGATIVE(argCheck);
  }

  MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(functionBranch, result, 0xFAFAu,
    /* Option 1: provide the condition as part of the branch expectation. */
    MCUX_CSSL_FP_BRANCH_TAKEN_POSITIVE(argCheck, 0xC0DEu == arg),
    /* Option 2: place the branch expectation in a conditional block. */
    MCUX_CSSL_FP_CONDITIONAL(0xC0DEu != arg,
      MCUX_CSSL_FP_BRANCH_TAKEN_NEGATIVE(argCheck)
    )
  );
}

/*
 * Example of a function that performs a protected switch.
 */
MCUX_CSSL_FP_FUNCTION_DEF(functionSwitch) /* Important: no semicolon here! */
MCUX_CSSL_FP_PROTECTED_TYPE(uint32_t) functionSwitch(uint32_t arg)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(functionSwitch);

  /* Every protected entity needs to be declared, hence also this switch. */
  MCUX_CSSL_FP_SWITCH_DECL(argSwitch);
  uint32_t result;
  switch (arg)
  {
    case 0xC0DEu:
    {
      result = 0xC0DEu;

      /* Within a case of a protected switch, a SWITCH_CASE event must be
       * placed, to indicate to the flow protection mechanism that this
       * particular case has been executed. */
      MCUX_CSSL_FP_SWITCH_CASE(argSwitch, 0xC0DEu);
      break;
    }
    case 0xDEADu:
    {
      result = 0xDEADu;

      /* Within a case of a protected switch, a SWITCH_CASE event must be
       * placed, to indicate to the flow protection mechanism that this
       * particular case has been executed. */
      MCUX_CSSL_FP_SWITCH_CASE(argSwitch, 0xDEADu);
      break;
    }
    default:
    {
      result = 0;

      /* Within the default case of a protected switch, a SWITCH_DEFAULT event
       * must be placed, to indicate to the flow protection mechanism that the
       * default case has been executed. */
      MCUX_CSSL_FP_SWITCH_DEFAULT(argSwitch);
      break;
    }
  }

  MCUX_CSSL_FP_FUNCTION_EXIT(functionSwitch, result,
    /* Option 1: provide the condition as part of the switch expectation. */
    MCUX_CSSL_FP_SWITCH_TAKEN(argSwitch, 0xC0DEu, 0xC0DEu == arg),
    MCUX_CSSL_FP_SWITCH_TAKEN(argSwitch, 0xDEADu, 0xDEADu == arg),
    /* Option 2: place the switch expectation in a conditional block. */
    MCUX_CSSL_FP_CONDITIONAL((0xC0DEu != arg) && (0xDEADu != arg),
      MCUX_CSSL_FP_SWITCH_TAKEN_DEFAULT(argSwitch)
    )
  );
}

/*
 * Example of a function that performs an assertion.
 */
MCUX_CSSL_FP_FUNCTION_DEF(functionAssert) /* Important: no semicolon here! */
MCUX_CSSL_FP_PROTECTED_TYPE(void) functionAssert(void)
{
  /* The protected function that will be called must be declared as expected,
   * either in the FUNCTION_ENTRY, FUNCTION_EXIT, EXPECT, or an event that
   * accepts expectation declarations.
   * FUNCTION_ENTRY can be used with and without providing expectations. */
  MCUX_CSSL_FP_FUNCTION_ENTRY(functionAssert,
    MCUX_CSSL_FP_FUNCTION_CALLED(functionOnly0)
  );
 
  MCUX_CSSL_FP_FUNCTION_CALL_VOID(functionOnly0());

  /* The ASSERT macro allows the currently recorded code flow to be checked.
   * The call to functionOnly has already been recorded as expected at the
   * function entry, so at this point the only remaining expectation is that
   * the function has been entered. */
  MCUX_CSSL_FP_ASSERT(
    MCUX_CSSL_FP_FUNCTION_ENTERED(functionAssert)
  );

  (void) functionOnly1();

  /* At this point the functionOnly1 call event should have happened, but not
   * yet recorded as an expectation. Therefore it should be specified as an
   * expected event for the assertion to pass. */
  MCUX_CSSL_FP_ASSERT(
    MCUX_CSSL_FP_FUNCTION_ENTERED(functionAssert),
    MCUX_CSSL_FP_FUNCTION_CALLED(functionOnly1)
  );

  /* This assertion will fail since it misses the expectation for the
   * functionOnly1 call event. */
  MCUX_CSSL_FP_ASSERT(
    MCUX_CSSL_FP_FUNCTION_ENTERED(functionAssert)
  );

  /* At this point MCUX_CSSL_FP_ASSERT_CALLBACK should be already executed 
  testVariable should be set to 0xFF*/

  /* FUNCTION_EXIT can be used with and without providing expectations. */
  MCUX_CSSL_FP_FUNCTION_EXIT_VOID(functionAssert,
    MCUX_CSSL_FP_FUNCTION_CALLED(functionOnly1)
  );
}

MCUX_CSSL_EX_FUNCTION(mcuxCsslFlowProtection_example)
{
  const uint32_t rOnly = functionOnly();
  (void) rOnly;
  functionCall();

  MCUX_CSSL_FP_FUNCTION_CALL_PROTECTED(returnCode, token, functionCalls());

  if (0xC0E4u != returnCode)  
  {
    return MCUX_CSSL_EX_ERROR;
  }

#if !defined(MCUX_CSSL_FP_USE_CODE_SIGNATURE) && !defined(MCUX_CSSL_FP_USE_NONE)
  if (MCUX_CSSL_FP_FUNCTION_CALLED(functionCalls) != token)
  {
    return MCUX_CSSL_EX_ERROR;
  }
#else
  (void) token;
#endif
    
  MCUX_CSSL_FP_FUNCTION_CALL_PROTECTED(returnCode1, token1, functionLoop(10));

  if (0xC0DEu != returnCode1)
  {
    return MCUX_CSSL_EX_ERROR;
  }

#if !defined(MCUX_CSSL_FP_USE_CODE_SIGNATURE) && !defined(MCUX_CSSL_FP_USE_NONE)
  if (!(MCUX_CSSL_FP_FUNCTION_CALLED(functionLoop) == token1))
  {
    return MCUX_CSSL_EX_ERROR;
  }
#else
  (void) token1;
#endif

  MCUX_CSSL_FP_FUNCTION_CALL_PROTECTED(returnCode2, token2, functionBranch(0xC0DEu));

  if (0xC0DEu != returnCode2)
  {
    return MCUX_CSSL_EX_ERROR;
  }

#if !defined(MCUX_CSSL_FP_USE_CODE_SIGNATURE) && !defined(MCUX_CSSL_FP_USE_NONE)
  if (!(MCUX_CSSL_FP_FUNCTION_CALLED(functionBranch) == token2))
  {
    return MCUX_CSSL_EX_ERROR;
  }
#else
  (void) token2;
#endif

  MCUX_CSSL_FP_FUNCTION_CALL_PROTECTED(returnCode3, token3, functionSwitch(0xC0DEu));

  if (0xC0DEu != returnCode3)
  {
    return MCUX_CSSL_EX_ERROR;
  }

#if !defined(MCUX_CSSL_FP_USE_CODE_SIGNATURE) && !defined(MCUX_CSSL_FP_USE_NONE)
  if (!(MCUX_CSSL_FP_FUNCTION_CALLED(functionSwitch) == token3))
  {
    return MCUX_CSSL_EX_ERROR;
  }
#else
  (void) token3;
#endif

  functionPointerType_t funcPtr = functionOnly2;

#if !defined(MCUX_CSSL_FP_USE_CODE_SIGNATURE) && !defined(MCUX_CSSL_FP_USE_NONE)
  const uint32_t funcPtrToken = MCUX_CSSL_FP_FUNCTION_CALLED(functionOnly2);
#endif

  MCUX_CSSL_FP_FUNCTION_CALL_PROTECTED(returnCode4, token4, funcPtr());

  if (0x2u != returnCode4)
  {
    return MCUX_CSSL_EX_ERROR;
  }

#if !defined(MCUX_CSSL_FP_USE_CODE_SIGNATURE) && !defined(MCUX_CSSL_FP_USE_NONE)
  if (!(funcPtrToken == token4))
  {
    return MCUX_CSSL_EX_ERROR;
  }
#else
  (void) token4;
#endif

  functionAssert();

  return MCUX_CSSL_EX_OK;
}
