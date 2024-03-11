/*--------------------------------------------------------------------------*/
/* Copyright 2021-2024 NXP                                                  */
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

/** @file  mcuxClRsa_MillerRabinTest.c
 *  @brief mcuxClRsa: function, which is called to perform  the Miller-Rabin
 *  probabilistic primality tests.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <mcuxClBuffer.h>
#include <mcuxClCore_Macros.h>

#include <mcuxClRandom_Constants.h>
#include <mcuxClMath_Functions.h>
#include <internal/mcuxClSession_Internal.h>
#include <internal/mcuxClPkc_ImportExport.h>
#include <internal/mcuxClPkc_Macros.h>
#include <internal/mcuxClPkc_Operations.h>
#include <internal/mcuxClRsa_Internal_Macros.h>
#include <internal/mcuxClRsa_Internal_PkcDefs.h>
#include <mcuxClRandom_Functions.h>
#include <mcuxClRsa.h>
#include <internal/mcuxClRsa_Internal_Functions.h>
#include <internal/mcuxClRsa_Internal_Types.h>
#include <internal/mcuxClRsa_MillerRabinTest_FUP.h>
#include <internal/mcuxClRsa_Internal_MemoryConsumption.h>
#include <internal/mcuxClRsa_Internal_PkcTypes.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClRsa_MillerRabinTest)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClRsa_Status_t) mcuxClRsa_MillerRabinTest(
  mcuxClSession_Handle_t pSession,
  uint32_t              iP_iT,
  uint32_t              keyBitLength,
  const uint32_t        numberTestIterations
)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClRsa_MillerRabinTest);


  /****************************************************************************/
  /* Initialization - Prepare buffers in PKC workarea, setup UPTR table       */
  /****************************************************************************/

  /* Set init status to FAILED */
  mcuxClRsa_Status_t status = MCUXCLRSA_STATUS_INTERNAL_TESTPRIME_MRT_FAILED;

  /* Backup Uptrt to recover in the end */
  const uint16_t *backupPtrUptrt = MCUXCLPKC_GETUPTRT();

  /* Create and set local Uptrt table. */
  uint32_t pOperands32[(MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_UPTRT_SIZE + 1u) / 2u];

  MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("16-bit UPTRT table is assigned in CPU workarea")
  uint16_t *pOperands = (uint16_t *) pOperands32;
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()

  /* Get iP and iT indices */
  uint32_t uptrtIndexTmp = (iP_iT) & 0xFFu;
  uint32_t uptrtIndexPrimeCandidate = (iP_iT >> 8) & 0xFFu;

  /* PKC buffer sizes */
  const uint32_t byteLenPrime = (keyBitLength / 2u) / 8u; /* keyBitLength is multiple of 8 */
  const uint32_t pkcOperandSize = MCUXCLRSA_ALIGN_TO_PKC_WORDSIZE(byteLenPrime);
  const uint32_t pkcBlindSize = MCUXCLRSA_ALIGN_TO_PKC_WORDSIZE(MCUXCLRSA_INTERNAL_MOD_BLINDING_SIZE);
  const uint32_t pkcBlindOperandSize = pkcOperandSize + pkcBlindSize;
  const uint32_t bufferSizeQSquared = pkcBlindOperandSize;                        // size of temp buffer QSquared
  const uint32_t bufferSizeResult = pkcBlindOperandSize + MCUXCLRSA_PKC_WORDSIZE;  // size of the result of the exponentiation
  const uint32_t bufferSizeX = pkcBlindOperandSize + MCUXCLRSA_PKC_WORDSIZE;       // size of the base number of the exponentiation
  const uint32_t bufferSizeT0 = pkcBlindOperandSize + MCUXCLRSA_PKC_WORDSIZE;      // size of temp buffer T0
  const uint32_t bufferSizeT1 = pkcBlindOperandSize + MCUXCLRSA_PKC_WORDSIZE;      // size of temp buffer T1
  const uint32_t bufferSizeT2 = pkcBlindOperandSize + MCUXCLRSA_PKC_WORDSIZE;      // size of temp buffer T2
  const uint32_t bufferSizeT3 = pkcBlindOperandSize + MCUXCLRSA_PKC_WORDSIZE;      // size of temp buffer T3
  const uint32_t bufferSizeTE = 6u * MCUXCLRSA_PKC_WORDSIZE;                       // size of temp buffer TE

  /* Setup UPTR table */
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_PRIMECANDIDATE] = backupPtrUptrt[uptrtIndexPrimeCandidate];
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_NB] = backupPtrUptrt[uptrtIndexTmp] + MCUXCLRSA_PKC_WORDSIZE /* Offset for nDash */;
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_QSQUARED] = pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_NB] + (uint16_t) pkcBlindOperandSize;
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_RESULT] = pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_QSQUARED] + (uint16_t)bufferSizeQSquared;
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_X] = pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_RESULT] + (uint16_t)bufferSizeResult;
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_T0] = pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_X] + (uint16_t)bufferSizeX;
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_T1] = pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_T0] + (uint16_t)bufferSizeT0;
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_T2] = pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_T1] + (uint16_t)bufferSizeT1;
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_T3] = pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_T2] + (uint16_t)bufferSizeT2;
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_TE] = pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_T3] + (uint16_t)bufferSizeT3;
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_R32] = pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_TE]; /* uses the same space as TW */
  pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_CONSTANT] = 1u;

  /* Set UPTRT table */
  MCUXCLPKC_WAITFORREADY();
  MCUXCLPKC_SETUPTRT(pOperands);

  /* Set length of operands */
  MCUXCLPKC_PS1_SETLENGTH(pkcBlindOperandSize, pkcBlindOperandSize);
  MCUXCLPKC_PS2_SETLENGTH_REG(pkcOperandSize);  /* MCLEN on higher 16 bits is not used. */


  /*****************************************************************/
  /* Compute m (exp) = (PrimeCandidate-1) / 2^a                    */
  /* NOTE: a=1 since the PrimeCandidate is congruent 3 mod 4       */
  /*****************************************************************/

  MCUXCLPKC_FP_CALC_OP2_SHR(MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_X, MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_PRIMECANDIDATE, 1);

  /* Revert exponent to big-endian - keep it in FXRAM memory */
  uint8_t * pExp = MCUXCLPKC_OFFSET2PTR(pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_TE]) + bufferSizeTE; //allocate space for it in the FXRAM, if there is not enough memory it can be in CPU
  MCUXCLPKC_FP_EXPORTBIGENDIANFROMPKC(pExp, MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_X, byteLenPrime);
  /* Allocate space for the temporary buffer for exponent (aligned to CPU word, length shall be a multiple of CPU word and greater than @p byteLenExp) */
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("Cast to CPU word aligned")
  uint32_t * pExpTemp = (uint32_t *) pExp + MCUXCLCORE_NUM_OF_CPUWORDS_CEIL(byteLenPrime);
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()


  /*****************************************************************/
  /* Compute blinded modulus w_b=w*r32 (w:=PrimeCandidate).        */
  /*****************************************************************/

  /* Generate r32 - odd random number used for blinding */
  MCUX_CSSL_ANALYSIS_START_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES("Cast to CPU word aligned")
  uint32_t *pR32 = (uint32_t *)  MCUXCLPKC_OFFSET2PTR(pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_R32]);
  MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_REINTERPRET_MEMORY_BETWEEN_INAPT_ESSENTIAL_TYPES()

  MCUXCLBUFFER_INIT(pBufR32, NULL, (uint8_t *) pR32, MCUXCLRSA_INTERNAL_MOD_BLINDING_SIZE);
  MCUX_CSSL_FP_FUNCTION_CALL(ret_Random_ncGenerate1, mcuxClRandom_ncGenerate(pSession, pBufR32, MCUXCLRSA_INTERNAL_MOD_BLINDING_SIZE));
  if (MCUXCLRANDOM_STATUS_OK != ret_Random_ncGenerate1)
  {
    MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_MillerRabinTest, MCUXCLRSA_STATUS_ERROR);
  }
  /* Make it odd */
  pR32[0] |= 0x1u;

  /* Clear part not overwritten when generating r32. */
#if !((MCUXCLPKC_WORDSIZE == 8u) && (MCUXCLRSA_INTERNAL_MOD_BLINDING_SIZE == 4u))
  #error "This implementation (clearing of B buffer) only supports 64-bit PKC word and 32-bit blinding value."
#endif
  pR32[1] = 0u;

  /* Compute blinded modulus w_b=w*r32 */
  MCUXCLPKC_FP_CALC_OP2_MUL(MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_NB, MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_R32, MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_PRIMECANDIDATE);


  /*****************************************************************/
  /* Prepare Montgomery parameters for modular operations          */
  /*****************************************************************/

  /* Calculate Ndash of w (it is needed to convert result for exponentiation from Montgomery to normal representation). */
  MCUXCLMATH_FP_NDASH(MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_PRIMECANDIDATE, MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_T0);

  /* Calculate Ndash of w_b. */
  MCUXCLMATH_FP_NDASH(MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_NB, MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_T0);

  /* Calculate QSquared */
  MCUXCLMATH_FP_SHIFTMODULUS(MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_T1, MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_NB); //shift modulus
  MCUXCLMATH_FP_QSQUARED(MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_QSQUARED /* QSquared */, MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_T1,
    MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_NB, MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_T0);

  /* Clear buffer for the witness */
  MCUXCLPKC_FP_CALC_OP1_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_RESULT, 0u);

  /***************************************************************************/
  /* Set iteration counter, length of operands and start Miller Rabin test   */
  /***************************************************************************/
  uint32_t counter = 0;

  /* Variables related to flow protection to count execution of loops */
  uint32_t witnessLoopCounterMain = 0;

  uint32_t zeroFlag_check = MCUXCLPKC_FLAG_NONZERO;

  /* Get pointer to the witness */
  uint8_t * pWitness = MCUXCLPKC_OFFSET2PTR(pOperands[MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_RESULT]);

  /* Set length of operands */
  MCUXCLPKC_WAITFORREADY();
  MCUXCLPKC_PS2_SETLENGTH_REG(pkcOperandSize);  /* MCLEN on higher 16 bits is not used. */

  MCUXCLBUFFER_INIT(pBufWitness, NULL, pWitness, byteLenPrime);

  MCUX_CSSL_FP_LOOP_DECL(mainLoopFp);

  do
  {
    uint32_t carryFlag_check = MCUXCLPKC_FLAG_CARRY;
    do{

      /***************************************************************************/
      /* Get random integer b of length equal to prime candidate from an RBG.    */
      /***************************************************************************/

      ++witnessLoopCounterMain;
#ifdef MCUXCL_FEATURE_ELS_ACCESS_PKCRAM_WORKAROUND
      const uint32_t cpuWaSizeWord = MCUXCLRSA_INTERNAL_MILLERRABINTEST_WACPU_SIZE_WO_RNG(byteLenPrime) / sizeof(uint32_t);
      uint8_t * pWitnessCpu = (uint8_t*) mcuxClSession_allocateWords_cpuWa(pSession, cpuWaSizeWord);
      if (NULL == pWitnessCpu)
      {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_MillerRabinTest, MCUXCLRSA_STATUS_FAULT_ATTACK);
      }

      MCUXCLBUFFER_SET(pBufWitness, pWitnessCpu, byteLenPrime);
      MCUX_CSSL_FP_FUNCTION_CALL(randomGenerateResult, mcuxClRandom_generate(pSession,
                                                               pBufWitness,
                                                               byteLenPrime));
      if(MCUXCLRANDOM_STATUS_OK != randomGenerateResult)
      {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_MillerRabinTest, MCUXCLRSA_STATUS_RNG_ERROR);
      }
      MCUXCLMEMORY_FP_MEMORY_COPY(pWitness, pWitnessCpu, byteLenPrime);

      mcuxClSession_freeWords_cpuWa(pSession, cpuWaSizeWord);
#else
      MCUX_CSSL_FP_FUNCTION_CALL(randomGenerateResult, mcuxClRandom_generate(pSession,
                                                               pBufWitness,
                                                               byteLenPrime));
      if(MCUXCLRANDOM_STATUS_OK != randomGenerateResult)
      {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_MillerRabinTest, MCUXCLRSA_STATUS_RNG_ERROR);
      }
#endif /* MCUXCL_FEATURE_ELS_ACCESS_PKCRAM_WORKAROUND */

      /* If ((b <= 1) or (b >= PrimeCandidate - 1)), then generate new b, otherwise b is accepted. */

      /* Compute PrimeCandidate-2 */
      MCUXCLPKC_FP_CALC_OP2_SUB_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_T0, MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_PRIMECANDIDATE, 2);
      /* Compare PrimeCandidate-2 and b */
      MCUXCLPKC_FP_CALC_OP2_CMP(MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_T0, MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_RESULT);
      carryFlag_check = MCUXCLPKC_WAITFORFINISH_GETCARRY();
      MCUX_CSSL_FP_EXPECT(MCUX_CSSL_FP_CONDITIONAL((MCUXCLPKC_FLAG_NOCARRY == carryFlag_check), MCUXCLPKC_FP_CALLED_CALC_OP2_SUB_CONST));
      if(MCUXCLPKC_FLAG_NOCARRY == carryFlag_check)
      {
        /* Compare 2 and b */
        MCUXCLPKC_FP_CALC_OP2_SUB_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_X, MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_RESULT, 2);
        carryFlag_check = MCUXCLPKC_WAITFORFINISH_GETCARRY();
      }
    }while(MCUXCLPKC_FLAG_NOCARRY != carryFlag_check);

    /***************************************************************************/
    /* Compute z_m = b_m^m mod w_b (using secure exponentiation)               */
    /***************************************************************************/

    /* Convert b to Montgomery representation i.e. b_m = b*QSquared mod w_b */
    MCUXCLPKC_FP_CALC_MC1_MM(MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_X /* b_m */, MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_RESULT /* b */,
      MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_QSQUARED /* QSquared */, MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_NB);
    MCUXCLPKC_WAITFORFINISH();

    /*
     * Perform secure exponentiation z_m = b_m^m mod w_b.
     * Result z_m is in Montgomery representation.
     * PS1 LEN and MCLEN was already initialized OPLEN = MCLEN = pkcPrimeByteLength + pkcBlindSize,
     */
    MCUX_CSSL_FP_FUNCTION_CALL(secModExpResult,
        MCUXCLMATH_SECMODEXP(
                            pSession,
                            pExp,
                            pExpTemp,
                            byteLenPrime,
                            MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_RESULT,  /* Result (z_bm) */
                            MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_X,  /* Montgomery representation of base number */
                            MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_NB,  /* Modulus, NDash of the modulus should be stored in front of it */
                            MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_TE,
                            MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_T0,
                            MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_T1,
                            MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_T2,
                            MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_T3) );
    if (MCUXCLMATH_STATUS_OK != secModExpResult)
    {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_MillerRabinTest, MCUXCLRSA_STATUS_ERROR);
    }

    /*
     * Call the FUP to do the below steps:
     * Convert from Montgomery to normal representation (modular reduction also removes the blinding from result).
     * Normalize the result (case if R > N).
     * Check if z == 1: if true then the test passed, otherwise another check is performed.
     */
    MCUXCLPKC_WAITFORREADY();
    MCUXCLPKC_PS2_SETLENGTH(pkcBlindOperandSize, pkcOperandSize); // The MCLEN is only relevant to mcuxClRsa_MillerRabinTest_ReducAndCheck_FUP operations
    MCUXCLPKC_FP_CALCFUP(mcuxClRsa_MillerRabinTest_ReducAndCheck_FUP,
        mcuxClRsa_MillerRabinTest_ReducAndCheck_FUP_LEN);

    MCUX_CSSL_FP_LOOP_ITERATION(mainLoopFp, MCUXCLPKC_FP_CALLED_CALC_MC1_MM,
                               MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_SecModExp),
                               MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_CalcFup));

    zeroFlag_check = MCUXCLPKC_WAITFORFINISH_GETZERO();

    MCUX_CSSL_FP_EXPECT(MCUX_CSSL_FP_CONDITIONAL((MCUXCLPKC_FLAG_ZERO != zeroFlag_check), MCUXCLPKC_FP_CALLED_CALC_OP2_SUB_CONST, MCUXCLPKC_FP_CALLED_CALC_OP2_CMP));

    /* Check if z == 1: if true then the test passed, otherwise another check is performed */
    if(MCUXCLPKC_FLAG_ZERO != zeroFlag_check)
    {
      /*******************************************************************************************************************/
      /* Check the second condition.                                                                                     */
      /* if ((z == PrimeCandidate-1), test passed, then continue. Otherwise, it means  that PrimeCandidate is composite, */
      /* and function returns MCUXCLRSA_STATUS_INTERNAL_TESTPRIME_MRT_FAILED error code                                   */
      /*******************************************************************************************************************/

      /* Comput PrimeCandidate-1 */
      MCUXCLPKC_FP_CALC_OP2_SUB_CONST(MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_RESULT /* PrimeCandidate-1 */, MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_PRIMECANDIDATE, 1);
      /* Compare PrimeCandidate-1 and z */
      MCUXCLPKC_FP_CALC_OP2_CMP(MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_RESULT /* PrimeCandidate-1 */, MCUXCLRSA_INTERNAL_UPTRTINDEX_MILLERRABIN_X /* z */);
      zeroFlag_check = MCUXCLPKC_WAITFORFINISH_GETZERO();
      if(MCUXCLPKC_FLAG_ZERO != zeroFlag_check)
      {
        /* Did not pass test, it is not prime, stop MillerRabin test. */
        break;
      }
    }

    /* Increment the M-R test counter */
    ++counter;

  /******************************************************************************************************/
  /* If counter == numberTestIterations, the prime candidate pass the M-R test, it is probably prime,   */
  /* function returns MCUXCLRSA_STATUS_KEYGENERATION_OK.                                                 */
  /* Otherwise, continue the test in loop              .                                                */
  /******************************************************************************************************/
  }while(counter < numberTestIterations);

  if((counter == numberTestIterations) && (MCUXCLPKC_FLAG_ZERO == zeroFlag_check) /* double checking of passing the zero flag */ )
  {
    /* This means all rounds have passed test */
    status = MCUXCLRSA_STATUS_KEYGENERATION_OK;
  }

  /* Recover Uptrt */
  MCUXCLPKC_SETUPTRT(backupPtrUptrt);

  MCUX_CSSL_FP_COUNTER_STMT(uint32_t mainLoopCounter = (counter == numberTestIterations) ? numberTestIterations : (counter + 1u));

/* Use temporary define to avoid preprocessor directive inside the function exit macro below,
   as this would violate the MISRA rule 20.6 otherwise. */
#ifdef MCUXCL_FEATURE_ELS_ACCESS_PKCRAM_WORKAROUND
  #define TMP_PKCRAM_WORKAROUND \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_generate) * witnessLoopCounterMain, \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_copy) * witnessLoopCounterMain
#else
  #define TMP_PKCRAM_WORKAROUND \
    MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_generate) * witnessLoopCounterMain
#endif

  MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClRsa_MillerRabinTest,
                            status,
                            MCUXCLPKC_FP_CALLED_CALC_OP2_SHR,
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClPkc_ExportBigEndianFromPkc),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClRandom_ncGenerate),
                            MCUXCLPKC_FP_CALLED_CALC_OP2_MUL,
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_NDash),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_NDash),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_ShiftModulus),
                            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMath_QSquared),
                            MCUXCLPKC_FP_CALLED_CALC_OP1_CONST,
                            TMP_PKCRAM_WORKAROUND,
                            MCUXCLPKC_FP_CALLED_CALC_OP2_SUB_CONST * witnessLoopCounterMain,
                            MCUXCLPKC_FP_CALLED_CALC_OP2_CMP * witnessLoopCounterMain,
                            MCUX_CSSL_FP_LOOP_ITERATIONS(mainLoopFp, mainLoopCounter));

#undef TMP_PKCRAM_WORKAROUND
}
