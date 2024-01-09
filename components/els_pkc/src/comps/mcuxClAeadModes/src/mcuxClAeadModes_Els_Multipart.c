/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
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

/** @file  mcuxClAeadModes_Els_Multipart.c
 *  @brief implementation of the multipart functions of the mcuxClAeadModes component */

#include <mcuxClAead.h>
#include <internal/mcuxClAeadModes_Els_Types.h>
#include <internal/mcuxClAeadModes_Els_Functions.h>
#include <internal/mcuxClAeadModes_Common_Functions.h>
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClAeadModes_init)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t)  mcuxClAeadModes_init(
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
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClAeadModes_init);
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
    /* MISRA Ex. 9 to Rule 11.3 */
    mcuxClAeadModes_Context_t * pCtx = (mcuxClAeadModes_Context_t * ) pContext;
    pCtx->common.mode = mode;
    pCtx->key = key;
    pCtx->dataLength = inLength;
    pCtx->aadLength = adataLength;
    pCtx->tagLength = tagLength;
    pCtx->processedDataLength = 0u;

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
    MCUX_CSSL_FP_FUNCTION_CALL(ret_Skeleton, pCtx->common.mode->algorithm->pSkeleton(
      /* mcuxClSession_Handle_t session,        */ session,
      /* mcuxClAead_Context_t * const pCtx,     */ pCtx,
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
      /* uint32_t options                      */ MCUXCLAEADMODES_OPTION_INIT
    ));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

    if(MCUXCLAEAD_STATUS_OK != ret_Skeleton)
    {
       MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_init, MCUXCLAEAD_STATUS_ERROR,
                                 pCtx->common.mode->algorithm->protection_token_skeleton);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClAeadModes_init, MCUXCLAEAD_STATUS_OK, MCUXCLAEAD_STATUS_FAULT_ATTACK,
                                         pCtx->common.mode->algorithm->protection_token_skeleton);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClAeadModes_process)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t)  mcuxClAeadModes_process(
  mcuxClSession_Handle_t session,
  mcuxClAead_Context_t * const pContext,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength
)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClAeadModes_process);
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
    /* MISRA Ex. 9 to Rule 11.3 */
    mcuxClAeadModes_Context_t * pCtx = (mcuxClAeadModes_Context_t * ) pContext;
    if((pCtx->processedDataLength < pCtx->aadLength) ||
       ((pCtx->processedDataLength + inLength) > (pCtx->aadLength + pCtx->dataLength)))
    {
         MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAead_process, MCUXCLAEAD_STATUS_ERROR);
    }

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
    MCUX_CSSL_FP_FUNCTION_CALL(ret_Skeleton, pCtx->common.mode->algorithm->pSkeleton(
      /* mcuxClSession_Handle_t session,        */ session,
      /* mcuxClAead_Context_t * const pCtx,     */ pCtx,
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
      /* uint32_t options                      */ MCUXCLAEADMODES_OPTION_PROCESS
    ));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

    if(MCUXCLAEAD_STATUS_OK != ret_Skeleton)
    {
       MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_process, MCUXCLAEAD_STATUS_ERROR,
                                 pCtx->common.mode->algorithm->protection_token_skeleton);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClAeadModes_process, MCUXCLAEAD_STATUS_OK, MCUXCLAEAD_STATUS_FAULT_ATTACK,
                                         pCtx->common.mode->algorithm->protection_token_skeleton);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClAeadModes_process_adata)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t)  mcuxClAeadModes_process_adata(
  mcuxClSession_Handle_t session,
  mcuxClAead_Context_t * const pContext,
  mcuxCl_InputBuffer_t pAdata,
  uint32_t adataLength
)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClAeadModes_process_adata);
    /* [Design]
        - Precondition: processedDataLength(context) contains the total data procesed (incl. partialData, exl. padding)
        - return ERROR in case: processedDataLength(context) + inLength(input) > aadLength(context)
        - call the Skeleton with
            - context
            - options = 2: update adata
            - all other arguments
            - unused arguments = NULL/0
    */
    /* MISRA Ex. 9 to Rule 11.3 */
    mcuxClAeadModes_Context_t * pCtx = (mcuxClAeadModes_Context_t * ) pContext;
    if((pCtx->processedDataLength + adataLength) > pCtx->aadLength)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_process_adata, MCUXCLAEAD_STATUS_ERROR);
    }

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
    MCUX_CSSL_FP_FUNCTION_CALL(ret_Skeleton, pCtx->common.mode->algorithm->pSkeleton(
      /* mcuxClSession_Handle_t session,        */ session,
      /* mcuxClAead_Context_t * const pCtx,     */ pCtx,
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
      /* uint32_t options                      */ MCUXCLAEADMODES_OPTION_PROCESS_AAD
    ));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

    if(MCUXCLAEAD_STATUS_OK != ret_Skeleton)
    {
       MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_process_adata, MCUXCLAEAD_STATUS_ERROR,
                                 pCtx->common.mode->algorithm->protection_token_skeleton);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClAeadModes_process_adata, MCUXCLAEAD_STATUS_OK, MCUXCLAEAD_STATUS_FAULT_ATTACK,
                                         pCtx->common.mode->algorithm->protection_token_skeleton);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClAeadModes_finish)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t)  mcuxClAeadModes_finish(
  mcuxClSession_Handle_t session,
  mcuxClAead_Context_t * const pContext,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength,
  mcuxCl_Buffer_t pTag
)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClAeadModes_finish);
    /* [Design]
        - Precondition: processedDataLength(context) contains the total data procesed (incl. partialData, exl. padding)
        - return ERROR in case: processedDataLength(context) != aadLength(context) + dataLength(context)
        - call the Skeleton with
            - context
            - options = 8: finish
            - all other arguments
            - unused arguments = NULL/0
    */
    /* MISRA Ex. 9 to Rule 11.3 */
    mcuxClAeadModes_Context_t * pCtx = (mcuxClAeadModes_Context_t * ) pContext;
    if(pCtx->processedDataLength != (pCtx->dataLength + pCtx->aadLength))
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_finish, MCUXCLAEAD_STATUS_ERROR);
    }

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
    MCUX_CSSL_FP_FUNCTION_CALL(ret_Skeleton, pCtx->common.mode->algorithm->pSkeleton(
      /* mcuxClSession_Handle_t session,        */ session,
      /* mcuxClAead_Context_t * const pCtx,     */ pCtx,
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
      /* uint32_t options                      */ MCUXCLAEADMODES_OPTION_FINISH
    ));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

    if(MCUXCLAEAD_STATUS_OK != ret_Skeleton)
    {
       MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_finish, MCUXCLAEAD_STATUS_ERROR,
                                 pCtx->common.mode->algorithm->protection_token_skeleton);
    }
    //if in Context->mode->pSkeletonfunction for MCUXCLAEADMODES_OPTION_VERIFY or MCUXCLAEADMODES_OPTION_FINISH options,
    //the context has been clear, ctx.mode->protection_token_skeleton can't be used  here
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClAeadModes_finish, MCUXCLAEAD_STATUS_OK, MCUXCLAEAD_STATUS_FAULT_ATTACK,
                                         pCtx->common.mode->algorithm->protection_token_skeleton);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClAeadModes_verify)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) mcuxClAeadModes_verify(
  mcuxClSession_Handle_t session,
  mcuxClAead_Context_t * const pContext,
  mcuxCl_InputBuffer_t pTag,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength
)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClAeadModes_verify);
    /* [Design]
        - Precondition: processedDataLength(context) contains the total data procesed (incl. partialData, exl. padding)
        - return ERROR in case: processedDataLength(context) != aadLength(context) + dataLength(context)
        - call the Skeleton with
            - context
            - options = 16: verify
            - all other arguments
            - unused arguments = NULL/0
    */
    /* MISRA Ex. 9 to Rule 11.3 */
    mcuxClAeadModes_Context_t * pCtx = (mcuxClAeadModes_Context_t * ) pContext;
    if(pCtx->processedDataLength != pCtx->dataLength + pCtx->aadLength)
    {
        MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_verify, MCUXCLAEAD_STATUS_ERROR);
    }

    MCUX_CSSL_ANALYSIS_START_SUPPRESS_NULL_POINTER_CONSTANT("NULL is used in code")
    MCUX_CSSL_FP_FUNCTION_CALL(ret_Skeleton, pCtx->common.mode->algorithm->pSkeleton(
      /* mcuxClSession_Handle_t session,        */ session,
      /* mcuxClAead_Context_t * const pCtx,     */ pCtx,
      /* mcuxCl_InputBuffer_t pNonce,           */ NULL,
      /* uint32_t nonceLength,                 */ 0u,
      /* mcuxCl_InputBuffer_t pIn,              */ NULL,
      /* uint32_t inLength,                    */ 0u,
      /* mcuxCl_InputBuffer_t pAdata,           */ NULL,
      /* uint32_t adataLength,                 */ 0u,
      /* mcuxCl_Buffer_t pOut,                  */ pOut,
      /* uint32_t * const pOutLength,          */ pOutLength,
      /* mcuxCl_Buffer_t pTag,                  */ (mcuxCl_Buffer_t) pTag,
      /* uint32_t tagLength,                   */ pCtx->tagLength,
      /* uint32_t options                      */ MCUXCLAEADMODES_OPTION_VERIFY
    ));
    MCUX_CSSL_ANALYSIS_STOP_SUPPRESS_NULL_POINTER_CONSTANT()

    if(MCUXCLAEAD_STATUS_OK != ret_Skeleton)
    {
       MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_verify, MCUXCLAEAD_STATUS_ERROR,
                                 pCtx->common.mode->algorithm->protection_token_skeleton);
    }
    //if in Context->mode->pSkeletonfunction for MCUXCLAEADMODES_OPTION_VERIFY or MCUXCLAEADMODES_OPTION_FINISH options,
    //the context has been clear, ctx.mode->protection_token_skeleton can't be used  here
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClAeadModes_verify, MCUXCLAEAD_STATUS_OK, MCUXCLAEAD_STATUS_FAULT_ATTACK,
                                         pCtx->common.mode->algorithm->protection_token_skeleton);
}
