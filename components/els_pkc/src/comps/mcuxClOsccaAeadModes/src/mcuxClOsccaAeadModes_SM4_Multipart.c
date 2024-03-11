/*--------------------------------------------------------------------------*/
/* Copyright 2022-2024 NXP                                                  */
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

/** @file  mcuxClOsccaAeadModes_SM4_Multipart.c
 *  @brief implementation of the multipart functions of the mcuxClOsccaAeadModes component */

#include <mcuxClAead.h>
#include <mcuxClSession.h>
#include <mcuxClKey.h>
#include <mcuxClBuffer.h>
#include <mcuxClMemory.h>
#include <internal/mcuxClOsccaAeadModes_Internal_Types.h>
#include <internal/mcuxClOsccaAeadModes_Internal_Functions.h>
#include <internal/mcuxClOsccaSm4_Internal.h>
#include <mcuxCsslAnalysis.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaAeadModes_init, mcuxClAead_init_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t)  mcuxClOsccaAeadModes_init(
  mcuxClSession_Handle_t session,
  mcuxClAead_Context_t * const pContext,
  mcuxClKey_Handle_t key,
  mcuxClAead_Mode_t mode,
  mcuxCl_InputBuffer_t pNonce,
  uint32_t nonceLength,
  uint32_t inLength,
  uint32_t adataLength,
  uint32_t tagLength
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaAeadModes_init);
    /* [Design]
        - initialize the context:
            - copy mode to mode in context
            - copy key to key in context
            - copy inLength to dataLength in context
            - copy adataLength to aadLength in context
            - copy tagLength to tagLength in context
            - initialize processedDataLength in context to zero
        - call the Skeleton with
            - context
            - options = 1: init
            - all other arguments
            - unused arguments = NULL/0
    */
    MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
    const mcuxClOsccaAeadModes_algorithm_t* pAlgo = (const mcuxClOsccaAeadModes_algorithm_t*) mode->algorithm;
    mcuxClOsccaAeadModes_Context_t *pCtx = (mcuxClOsccaAeadModes_Context_t *)pContext;
    MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("change mcuxClAead_Context_t * to mcuxClOsccaAeadModes_Context_t *")
    pCtx->common.mode = mode;
    pCtx->key = key;
    pCtx->dataLength = inLength;
    pCtx->aadLength = adataLength;
    pCtx->tagLength = tagLength;
    pCtx->processedDataLength = 0u;
    pCtx->direction = pAlgo->direction;
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("change mcuxClAead_algorithm * to mcuxClOsccaAeadModes_algorithm_t *")
    MCUX_CSSL_FP_FUNCTION_CALL(ret_Skeleton, pAlgo->pSkeleton(
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
      /* mcuxClSession_Handle_t session,        */ session,
      /* mcuxClAead_Context_t * const pContext, */ pCtx,
      /* mcuxCl_InputBuffer_t pNonce,           */ pNonce,
      /* uint32_t nonceLength,                 */ nonceLength,
      /* mcuxCl_InputBuffer_t pIn,              */ NULL,
      /* uint32_t inLength,                    */ inLength,
      /* mcuxCl_InputBuffer_t pAdata,           */ NULL,
      /* uint32_t adataLength,                 */ adataLength,
      /* mcuxCl_Buffer_t pOut,                  */ NULL,
      /* uint32_t * const pOutLength,          */ NULL,
      /* mcuxCl_Buffer_t pTag,                  */ NULL,
      /* uint32_t tagLength,                   */ tagLength,
      /* uint32_t options                      */ MCUXCLOSCCAAEADMODES_OPTION_INIT
    ));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

    if(MCUXCLAEAD_STATUS_OK != ret_Skeleton)
    {
       MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaAeadModes_init, MCUXCLAEAD_STATUS_ERROR,
                                 pAlgo->protection_token_skeleton);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaAeadModes_init, MCUXCLAEAD_STATUS_OK, MCUXCLAEAD_STATUS_FAULT_ATTACK,
                                         pAlgo->protection_token_skeleton);
}



MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaAeadModes_process, mcuxClAead_process_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t)  mcuxClOsccaAeadModes_process(
  mcuxClSession_Handle_t session,
  mcuxClAead_Context_t * const pContext,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaAeadModes_process);
    /* [Design]
        - Precondition: processedDataLength(context) contains the total data processed (incl. partialData, exl. padding)
        - return ERROR in case: processedDataLength(context) < aadLength(context) [not finished processing adata]
        - return ERROR in case: processedDataLength(context) + inLength(input) > aadLength(context) + dataLength(context)
        - call the Skeleton with
            - context
            - options = 4: update data
            - all other arguments
            - unused arguments = NULL/0
    */
    MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
    mcuxClOsccaAeadModes_Context_t *pCtx = (mcuxClOsccaAeadModes_Context_t *)pContext;
    const mcuxClOsccaAeadModes_algorithm_t* pAlgo = (const mcuxClOsccaAeadModes_algorithm_t*) pCtx->common.mode->algorithm;
    MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP(" (pCtx->processedDataLength + inLength) can't be larger than max(uint32_t) ")
    if((pCtx->processedDataLength < pCtx->aadLength) ||
       ((pCtx->processedDataLength + inLength) > (pCtx->aadLength + pCtx->dataLength)))
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
    {
         MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaAeadModes_process, MCUXCLAEAD_STATUS_ERROR);
    }

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("change mcuxClAead_algorithm * to mcuxClOsccaAeadModes_algorithm_t *")
    MCUX_CSSL_FP_FUNCTION_CALL(ret_Skeleton, pAlgo->pSkeleton(
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
      /* mcuxClSession_Handle_t session,        */ session,
      /* mcuxClAead_Context_t * const pContext, */ pCtx,
      /* mcuxCl_InputBuffer_t pNonce,           */ NULL,
      /* uint32_t nonceLength,                 */ 0u,
      /* mcuxCl_InputBuffer_t pIn,              */ pIn,
      /* uint32_t inLength,                    */ inLength,
      /* mcuxCl_InputBuffer_t pAdata,           */ NULL,
      /* uint32_t adataLength,                 */ 0u,
      /* mcuxCl_Buffer_t pOut,                  */ pOut,
      /* uint32_t * const pOutLength,          */ pOutLength,
      /* mcuxCl_Buffer_t pTag,                  */ NULL,
      /* uint32_t tagLength,                   */ 0u,
      /* uint32_t options                      */ MCUXCLOSCCAAEADMODES_OPTION_PROCESS
    ));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

    if(MCUXCLAEAD_STATUS_OK != ret_Skeleton)
    {
       MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaAeadModes_process, MCUXCLAEAD_STATUS_ERROR,
                                 pAlgo->protection_token_skeleton);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaAeadModes_process, MCUXCLAEAD_STATUS_OK, MCUXCLAEAD_STATUS_FAULT_ATTACK,
                                         pAlgo->protection_token_skeleton);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaAeadModes_process_adata, mcuxClAead_process_aad_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t)  mcuxClOsccaAeadModes_process_adata(
  mcuxClSession_Handle_t session,
  mcuxClAead_Context_t * const pContext,
  mcuxCl_InputBuffer_t pAdata,
  uint32_t adataLength
)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaAeadModes_process_adata);
    /* [Design]
        - Precondition: processedDataLength(context) contains the total data procesed (incl. partialData, exl. padding)
        - return ERROR in case: processedDataLength(context) + inLength(input) > aadLength(context)
        - call the Skeleton with
            - context
            - options = 2: update adata
            - all other arguments
            - unused arguments = NULL/0
    */
    MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
    mcuxClOsccaAeadModes_Context_t *pCtx = (mcuxClOsccaAeadModes_Context_t *)pContext;
    const mcuxClOsccaAeadModes_algorithm_t* pAlgo = (const mcuxClOsccaAeadModes_algorithm_t*) pCtx->common.mode->algorithm;
    MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP(" (pCtx->processedDataLength + adataLength) can't be larger than max(uint32_t) ")
    if((pCtx->processedDataLength + adataLength) > pCtx->aadLength)
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaAeadModes_process_adata, MCUXCLAEAD_STATUS_ERROR);
    }

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("change mcuxClAead_algorithm * to mcuxClOsccaAeadModes_algorithm_t *")
    MCUX_CSSL_FP_FUNCTION_CALL(ret_Skeleton, pAlgo->pSkeleton(
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
      /* mcuxClSession_Handle_t session,        */ session,
      /* mcuxClAead_Context_t * const pContext, */ pCtx,
      /* mcuxCl_InputBuffer_t pNonce,           */ NULL,
      /* uint32_t nonceLength,                 */ 0u,
      /* mcuxCl_InputBuffer_t pIn,              */ NULL,
      /* uint32_t inLength,                    */ 0u,
      /* mcuxCl_InputBuffer_t pAdata,           */ pAdata,
      /* uint32_t adataLength,                 */ adataLength,
      /* mcuxCl_Buffer_t pOut,                  */ NULL,
      /* uint32_t * const pOutLength,          */ NULL,
      /* mcuxCl_Buffer_t pTag,                  */ NULL,
      /* uint32_t tagLength,                   */ 0u,
      /* uint32_t options                      */ MCUXCLOSCCAAEADMODES_OPTION_PROCESS_AAD
    ));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

    if(MCUXCLAEAD_STATUS_OK != ret_Skeleton)
    {
       MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaAeadModes_process_adata, MCUXCLAEAD_STATUS_ERROR,
                                 pAlgo->protection_token_skeleton);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaAeadModes_process_adata, MCUXCLAEAD_STATUS_OK, MCUXCLAEAD_STATUS_FAULT_ATTACK,
                                         pAlgo->protection_token_skeleton);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaAeadModes_finish, mcuxClAead_finish_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t)  mcuxClOsccaAeadModes_finish(
  mcuxClSession_Handle_t session,
  mcuxClAead_Context_t * const pContext,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength,
  mcuxCl_Buffer_t pTag
)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaAeadModes_finish);
    /* [Design]
        - Precondition: processedDataLength(context) contains the total data procesed (incl. partialData, exl. padding)
        - return ERROR in case: processedDataLength(context) != aadLength(context) + dataLength(context)
        - call the Skeleton with
            - context
            - options = 8: finish
            - all other arguments
            - unused arguments = NULL/0
    */
    MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
    mcuxClOsccaAeadModes_Context_t *pCtx = (mcuxClOsccaAeadModes_Context_t *)pContext;
    const mcuxClOsccaAeadModes_algorithm_t* pAlgo = (const mcuxClOsccaAeadModes_algorithm_t*) pCtx->common.mode->algorithm;
    MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP(" (pCtx->dataLength + pCtx->aadLength) can't be larger than max(uint32_t) ")
    if(pCtx->processedDataLength != (pCtx->dataLength + pCtx->aadLength))
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
    {
        MCUXCLMEMORY_FP_MEMORY_CLEAR((uint8_t *)pCtx, sizeof(mcuxClOsccaAeadModes_Context_t));
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaAeadModes_finish, MCUXCLAEAD_STATUS_ERROR,
                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear));
    }

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("change mcuxClAead_algorithm * to mcuxClOsccaAeadModes_algorithm_t *")
    MCUX_CSSL_FP_FUNCTION_CALL(ret_Skeleton, pAlgo->pSkeleton(
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
      /* mcuxClSession_Handle_t session,        */ session,
      /* mcuxClAead_Context_t * const pContext, */ pCtx,
      /* mcuxCl_InputBuffer_t pNonce,           */ NULL,
      /* uint32_t nonceLength,                 */ 0u,
      /* mcuxCl_InputBuffer_t pIn,              */ NULL,
      /* uint32_t inLength,                    */ 0u,
      /* mcuxCl_InputBuffer_t pAdata,           */ NULL,
      /* uint32_t adataLength,                 */ 0u,
      /* mcuxCl_Buffer_t pOut,                  */ pOut,
      /* uint32_t * const pOutLength,          */ pOutLength,
      /* mcuxCl_Buffer_t pTag,                  */ pTag,
      /* uint32_t tagLength,                   */ pCtx->tagLength,
      /* uint32_t options                      */ MCUXCLOSCCAAEADMODES_OPTION_FINISH
    ));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

    if(MCUXCLAEAD_STATUS_OK != ret_Skeleton)
    {
        MCUXCLMEMORY_FP_MEMORY_CLEAR((uint8_t *)pCtx, sizeof(mcuxClOsccaAeadModes_Context_t));
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaAeadModes_finish, MCUXCLAEAD_STATUS_ERROR,
                                MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear),
                                pAlgo->protection_token_skeleton);
    }
    //if in Context->mode->pSkeletonfunction for MCUXCLOSCCAAEADMODES_OPTION_VERIFY or MCUXCLOSCCAAEADMODES_OPTION_FINISH options,
    //the context has been clear, ctx.mode->protection_token_skeleton can't be used  here
    MCUXCLMEMORY_FP_MEMORY_CLEAR((uint8_t *)pCtx, sizeof(mcuxClOsccaAeadModes_Context_t));
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaAeadModes_finish, MCUXCLAEAD_STATUS_OK, MCUXCLAEAD_STATUS_FAULT_ATTACK,
                                         MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear),
                                         pAlgo->protection_token_skeleton);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaAeadModes_verify, mcuxClAead_verify_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) mcuxClOsccaAeadModes_verify(
  mcuxClSession_Handle_t session,
  mcuxClAead_Context_t * const pContext,
  mcuxCl_InputBuffer_t pTag,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength
)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaAeadModes_verify);
    /* [Design]
        - Precondition: processedDataLength(context) contains the total data procesed (incl. partialData, exl. padding)
        - return ERROR in case: processedDataLength(context) != aadLength(context) + dataLength(context)
        - call the Skeleton with
            - context
            - options = 16: verify
            - all other arguments
            - unused arguments = NULL/0
    */
    MCUX_CSSL_ANALYSIS_START_CAST_TO_MORE_SPECIFIC_TYPE()
    mcuxClOsccaAeadModes_Context_t *pCtx = (mcuxClOsccaAeadModes_Context_t *)pContext;
    const mcuxClOsccaAeadModes_algorithm_t* pAlgo = (const mcuxClOsccaAeadModes_algorithm_t*) pCtx->common.mode->algorithm;
    MCUX_CSSL_ANALYSIS_STOP_CAST_TO_MORE_SPECIFIC_TYPE()
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_INTEGER_WRAP(" (pCtx->dataLength + pCtx->aadLength) can't be larger than max(uint32_t) ")
    if(pCtx->processedDataLength != pCtx->dataLength + pCtx->aadLength)
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_INTEGER_WRAP()
    {
        MCUXCLMEMORY_FP_MEMORY_CLEAR((uint8_t *)pCtx, sizeof(mcuxClOsccaAeadModes_Context_t));
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaAeadModes_verify, MCUXCLAEAD_STATUS_ERROR,
                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear));
    }

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
    MCUX_CSSL_ANALYSIS_START_SUPPRESS_POINTER_INCOMPATIBLE("change mcuxClAead_algorithm * to mcuxClOsccaAeadModes_algorithm_t *")
    MCUX_CSSL_FP_FUNCTION_CALL(ret_Skeleton, pAlgo->pSkeleton(
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_POINTER_INCOMPATIBLE()
      /* mcuxClSession_Handle_t session,        */ session,
      /* mcuxClAead_Context_t * const pContext, */ pCtx,
      /* mcuxCl_InputBuffer_t pNonce,           */ NULL,
      /* uint32_t nonceLength,                 */ 0u,
      /* mcuxCl_InputBuffer_t pIn,              */ NULL,
      /* uint32_t inLength,                    */ 0u,
      /* mcuxCl_InputBuffer_t pAdata,           */ NULL,
      /* uint32_t adataLength,                 */ 0u,
      /* mcuxCl_Buffer_t pOut,                  */ pOut,
      /* uint32_t * const pOutLength,          */ pOutLength,
      MCUX_CSSL_ANALYSIS_START_SUPPRESS_DISCARD_CONST_QUALIFIER("Const must be discarded to set the generic pointer.")
      /* mcuxCl_Buffer_t pTag,                  */ (mcuxCl_Buffer_t) pTag,
      MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_DISCARD_CONST_QUALIFIER()
      /* uint32_t tagLength,                   */ pCtx->tagLength,
      /* uint32_t options                      */ MCUXCLOSCCAAEADMODES_OPTION_VERIFY
    ));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

    if(MCUXCLAEAD_STATUS_OK != ret_Skeleton)
    {
       MCUXCLMEMORY_FP_MEMORY_CLEAR((uint8_t *)pCtx, sizeof(mcuxClOsccaAeadModes_Context_t));
       MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaAeadModes_verify, MCUXCLAEAD_STATUS_ERROR,
                                 MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear),
                                 pAlgo->protection_token_skeleton);
    }
    //if in Context->mode->pSkeletonfunction for MCUXCLOSCCAAEADMODES_OPTION_VERIFY or MCUXCLOSCCAAEADMODES_OPTION_FINISH options,
    //the context has been clear, ctx.mode->protection_token_skeleton can't be used  here
    MCUXCLMEMORY_FP_MEMORY_CLEAR((uint8_t *)pCtx, sizeof(mcuxClOsccaAeadModes_Context_t));
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaAeadModes_verify, MCUXCLAEAD_STATUS_OK, MCUXCLAEAD_STATUS_FAULT_ATTACK,
                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClMemory_clear),
                                        pAlgo->protection_token_skeleton);
}
