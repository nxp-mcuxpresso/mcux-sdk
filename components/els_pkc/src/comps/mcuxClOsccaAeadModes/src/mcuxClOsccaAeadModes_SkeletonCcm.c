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

/** @file  mcuxClOsccaAeadModes_SkeletonCcm.c
 *  @brief implementation of the SM4 CCM skeleton functions of the mcuxClOsccaAeadModes component */

#include <mcuxClAead.h>
#include <mcuxClOsccaAeadModes.h>
#include <mcuxClMemory.h>
#include <mcuxClSession.h>
#include <mcuxCsslAnalysis.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>
#include <internal/mcuxClOsccaAeadModes_Internal_Types.h>
#include <internal/mcuxClOsccaAeadModes_Internal_Functions.h>
#include <internal/mcuxClOsccaSm4_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaAeadModes_SkeletonCcm, mcuxClOsccaAeadModes_Skeleton_t)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t) mcuxClOsccaAeadModes_SkeletonCcm(
    mcuxClSession_Handle_t session,
    mcuxClOsccaAeadModes_Context_t * const pContext,
    mcuxCl_InputBuffer_t pNonce,
    uint32_t nonceLength,
    mcuxCl_InputBuffer_t pIn,
    uint32_t inLength,
    mcuxCl_InputBuffer_t pAdata,
    uint32_t adataLength,
    mcuxCl_Buffer_t pOut,
    uint32_t * const pOutLength,
    mcuxCl_Buffer_t pTag,
    uint32_t tagLength,
    uint32_t options //!< options is a bitmask with one bit reserved for each of the operations
)
{
    /* [Design]
        ATTN: pOutLength will be _incremented_ by the number of bytes of encrypted data that have been
              written to the @p pOut buffer. Except otherwise mentioned processing steps _output_ data
              to pOut and update pOutLength

        Note:
            - options is a bitmask: 1: init, 2: aad, 4: process, 8: finish, 15: oneshot, 16: verify

        - Preconditions
            - aadLength in context has been initialized
            - dataLength in context has been initialized
            - tagLength in context has been initialized
            - key in context has been initialized
            - mode in context has been initialized
            - processedDataLength in context has been initialized and maintained

        - Context usage:
            - the state contains both the CTR counter and the partial CBC-MAC

        - Common IV processing (options == oneshot / init)
            - set partialDataLength in context to zero
            - construct the first block using the nonce from the input and the dataLength, aadLength and tagLength from the
              context. partialData can be used for this as it is not in use yet.
            - process the first block using pEngine(option: auth+init) with zero IV (the engine will update the state in context)
            - construct the counter for CTR mode encryption and output to state in context, let it start at 'one'

        - AAD processing (options == oneshot / update aad)
            - if adataLength != 0 add the new data from the input to partialData[partialDataLength] and process using
              pEngine(option: auth) if possible, adapt partialDataLength and processedDataLength
            - process remaining complete blocks from the input using pEngine(option: auth), adapt processedDataLength
            - add remaining data to partialData, adapt partialDataLength and processedDataLength
            - [Assertion] aadLength <= processedDataLength
            - if aadLength == processedDataLength padd partialData with zeros and process using pEngine(option: auth), set
              partialDataLength to zero

        - Data processing (options == oneshot / update data)
            - if inLength != 0 add the new data from the input to partialData and process using pEngine(option: auth+enc) if possible,
              adapt partialDataLength and processedDataLength (this will never be the case for oneshot)
            - process remaining complete blocks from the input using pEngine(option: auth+enc), adapt processedDataLength
            - add remaining data to partialData, adapt partialDataLength and processedDataLength
            - [Assertion] aadLength + dataLength  <= processedDataLength
            - if aadLength + dataLength == processedDataLength padd partialData with zeros
              and process using pEngine(option: auth+enc), set partialDataLength to zero

        - Finalization processing (options == oneshot / finish / verify)
            - if partialDataLength != 0 exit with ERROR
            - reset counter value to 'zero' (leaving the other fields intact)
            - process the CBC-MAC state with pEngine(option: enc), and store the result in partialData

        - Finalization processing (options == oneshot / finish)
            - copy tagLength bytes from partialData to the tag
            - clean up context

        - Finalization processing (options == verify)
            - compare tagLength bytes from partialData to the tag
            - clean up context

        - exit
    */

    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaAeadModes_SkeletonCcm);
    mcuxClOsccaAeadModes_Context_t * pCtx = (mcuxClOsccaAeadModes_Context_t *) pContext;

/*
        - Common IV processing (options == oneshot / init)
            - set partialDataLength in context to zero
            - construct the first block using the nonce from the input and the dataLength, aadLength and tagLength from the
              context. partialData can be used for this as it is not in use yet.
            - process the first block using pEngine(option: auth+init) with zero IV (the engine will update the state in context)
            - construct the counter for CTR mode encryption and output to state in context, let it start at 'one'
*/
    if ((options == MCUXCLOSCCAAEADMODES_OPTION_ONESHOT) || (options == MCUXCLOSCCAAEADMODES_OPTION_INIT))
    {
        MCUX_CSSL_FP_FUNCTION_CALL(initRet, mcuxClOsccaAeadModes_Ccm_Internal_Init(session,
                                                                                 pCtx,
                                                                                 pNonce,
                                                                                 nonceLength,
                                                                                 inLength,
                                                                                 adataLength,
                                                                                 tagLength));

        if(MCUXCLAEAD_STATUS_OK != initRet)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaAeadModes_SkeletonCcm, MCUXCLAEAD_STATUS_ERROR);
        }
    }

/*
        - AAD processing (options == oneshot / update aad)
            - if adataLength != 0 add the new data from the input to partialData[partialDataLength] and process using
              pEngine(option: auth) if possible, adapt partialDataLength and processedDataLength
            - process remaining complete blocks from the input using pEngine(option: auth), adapt processedDataLength
            - add remaining data to partialData, adapt partialDataLength and processedDataLength
            - [Assertion] aadLength <= processedDataLength
            - if aadLength == processedDataLength padd partialData with zeros and process using pEngine(option: auth), set
              partialDataLength to zero
*/

    if ((options == MCUXCLOSCCAAEADMODES_OPTION_ONESHOT) || (options == MCUXCLOSCCAAEADMODES_OPTION_PROCESS_AAD))
    {
        MCUX_CSSL_FP_FUNCTION_CALL(proAadRet, mcuxClOsccaAeadModes_Ccm_Internal_ProcessAad(session,
                                                                                         pCtx,
                                                                                         pAdata,
                                                                                         adataLength));

        if(MCUXCLAEAD_STATUS_OK != proAadRet)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaAeadModes_SkeletonCcm, MCUXCLAEAD_STATUS_ERROR);
        }
    }


/*
        - Data processing (options == oneshot / update data)
            - if inLength != 0 add the new data from the input to partialData and process using pEngine(option: aead) if possible,
              adapt partialDataLength and processedDataLength (this will never be the case for oneshot)
            - process remaining complete blocks from the input using pEngine(option: aead), adapt processedDataLength
            - add remaining data to partialData, adapt partialDataLength and processedDataLength
            - [Assertion] aadLength + dataLength  <= processedDataLength
            - if aadLength + dataLength == processedDataLength padd partialData with zeros
              and process using pEngine(option: auth+enc), set partialDataLength to zero
*/

    if ((options == MCUXCLOSCCAAEADMODES_OPTION_ONESHOT) || (options == MCUXCLOSCCAAEADMODES_OPTION_PROCESS))
    {
        MCUX_CSSL_FP_FUNCTION_CALL(proRet, mcuxClOsccaAeadModes_Ccm_Internal_Process(session,
                                                                                   pCtx,
                                                                                   pIn,
                                                                                   inLength,
                                                                                   pOut,
                                                                                   pOutLength));

        if(MCUXCLAEAD_STATUS_OK != proRet)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaAeadModes_SkeletonCcm, MCUXCLAEAD_STATUS_ERROR);
        }
    }

/*
        - Finalization processing (options == oneshot / finish / verify)
            - if partialDataLength != 0 exit with ERROR
            - reset counter value to 'zero' (leaving the other fields intact)
            - process the CBC-MAC state with pEngine(option: enc), and store the result in partialData
            - copy tagLength bytes from partialData to the tag (options == oneshot / finish)
            - compare tagLength bytes from partialData to the tag (options == verify)
            - clean up context
*/

    if ((options == MCUXCLOSCCAAEADMODES_OPTION_ONESHOT) || (options == MCUXCLOSCCAAEADMODES_OPTION_FINISH) || (options == MCUXCLOSCCAAEADMODES_OPTION_VERIFY))
    {
        MCUX_CSSL_FP_FUNCTION_CALL(finishRet, mcuxClOsccaAeadModes_Ccm_Internal_Finish(session, pCtx, pTag, options));
        if(MCUXCLAEAD_STATUS_OK != finishRet)
        {
            MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClOsccaAeadModes_SkeletonCcm, MCUXCLAEAD_STATUS_ERROR);
        }
    }

    /* Exit and balance the flow protection. */
    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClOsccaAeadModes_SkeletonCcm, MCUXCLAEAD_STATUS_OK, MCUXCLAEAD_STATUS_FAULT_ATTACK,
        MCUX_CSSL_FP_CONDITIONAL(((options == MCUXCLOSCCAAEADMODES_OPTION_ONESHOT) || (options == MCUXCLOSCCAAEADMODES_OPTION_INIT)),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaAeadModes_Ccm_Internal_Init)),
        MCUX_CSSL_FP_CONDITIONAL((((options == MCUXCLOSCCAAEADMODES_OPTION_ONESHOT) || (options == MCUXCLOSCCAAEADMODES_OPTION_PROCESS_AAD))),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaAeadModes_Ccm_Internal_ProcessAad)),
        MCUX_CSSL_FP_CONDITIONAL((((options == MCUXCLOSCCAAEADMODES_OPTION_ONESHOT) || (options == MCUXCLOSCCAAEADMODES_OPTION_PROCESS))),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaAeadModes_Ccm_Internal_Process)),
        MCUX_CSSL_FP_CONDITIONAL((((options == MCUXCLOSCCAAEADMODES_OPTION_ONESHOT) || (options == MCUXCLOSCCAAEADMODES_OPTION_FINISH) || (options == MCUXCLOSCCAAEADMODES_OPTION_VERIFY))),
            MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClOsccaAeadModes_Ccm_Internal_Finish)));
}

