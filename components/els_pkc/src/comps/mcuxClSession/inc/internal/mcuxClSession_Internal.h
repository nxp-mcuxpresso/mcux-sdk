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

/**
 * @file  mcuxClSession_Internal.h
 * @brief Internal definitions of the mcuxClSession component
 */

#ifndef MCUXCLSESSION_INERNAL_H_
#define MCUXCLSESSION_INERNAL_H_

#include <stddef.h>
#include <mcuxClToolchain.h>
#include <mcuxClConfig.h> // Exported features flags header
#include <mcuxClSession_Types.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************
 * FUNCTIONS
 **********************************************/

/**
 * @brief Allocate a CPU buffer in the CPU workarea of a session.
 *
 * This function allocates a new CPU buffer in the given \p session,
 * and sets the given \p buffer accordingly.
 *
 * @param  pSession        Session handle.
 * @param  buffer          A pointer to the buffer that we want to allocate.
 * @param  bufferLength    The size of the buffer.
 *
 * @return status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClSession_allocateCpuBuffer)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClSession_Status_t) mcuxClSession_allocateCpuBuffer(
    mcuxClSession_Handle_t pSession,
    uint32_t **buffer,
    uint32_t bufferLength
);

/**
 * @brief Free all CPU buffers of a session.
 *
 * This function will free all allocated CPU buffers of the given \p session.
 *
 * @param  pSession Session handle.
 *
 * @return status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClSession_freeAllCpuBuffers)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClSession_Status_t) mcuxClSession_freeAllCpuBuffers(
    mcuxClSession_Handle_t pSession
);


/**
 * @brief (inline) function to allocate CPU buffer.
 *
 * This function allocates a buffer in CPU workarea specified in @p pSession.
 *
 * @param[in] pSession         Session handle.
 * @param[in] wordsToAllocate  The size of buffer to be allocated, in number of CPU words (uint32_t).
 *
 * @return pointer to the buffer if it is allocated successfully;
 *         NULL if the buffer cannot be allocated.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClSession_allocateWords_cpuWa)
static inline uint32_t* mcuxClSession_allocateWords_cpuWa(
    mcuxClSession_Handle_t pSession,
    uint32_t wordsToAllocate)
{
    uint32_t * pCpuBuffer = NULL;
    const uint32_t usedWords = pSession->cpuWa.used;
    const uint32_t expectedUsed = usedWords + wordsToAllocate;
    /* TODO: CLNS-5886 [DEV][Session] enable size checking when allocating buffers */
#if 0  /* checking disabled before all components/tests allocate workarea properly */
    if (expectedUsed <= pSession->cpuWa.size)
    {
#endif
        pCpuBuffer = & (pSession->cpuWa.buffer[usedWords]);
        pSession->cpuWa.used = expectedUsed;

        if (expectedUsed > pSession->cpuWa.dirty)
        {
            pSession->cpuWa.dirty = expectedUsed;
        }
#if 0
    }
#endif

    return pCpuBuffer;
}

/**
 * @brief (inline) function to allocate PKC buffer.
 *
 * This function allocates a buffer in PKC workarea specified in @p pSession.
 *
 * The PKC workarea is assumed to be initialized to be PKC-word aligned.
 * However, size of each buffer (allocated from PKC workarea) is in number of CPU words,
 * and address of each buffer is CPU-word aligned, but might be not PKC-word aligned.
 * Callers need to take care if a buffer is PKC-word aligned, if it is used as a PKC operand.
 * For example, the total size of buffer(s) allocated before a PKC operand buffer shall
 * be a multiple of PKC wordsize.
 *
 * @param[in] pSession         Session handle.
 * @param[in] wordsToAllocate  The size of buffer to be allocated, in number of CPU words (uint32_t).
 *
 * @return pointer to the buffer if it is allocated successfully;
 *         NULL if the buffer cannot be allocated.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClSession_allocateWords_pkcWa)
static inline uint32_t* mcuxClSession_allocateWords_pkcWa(
    mcuxClSession_Handle_t pSession,
    uint32_t wordsToAllocate)
{
    uint32_t * pPkcBuffer = NULL;
    const uint32_t usedWords = pSession->pkcWa.used;
    const uint32_t expectedUsed = usedWords + wordsToAllocate;
    /* TODO: CLNS-5886 [DEV][Session] enable size checking when allocating buffers */
#if 0  /* checking disabled before all components/tests allocate workarea properly */
    if (expectedUsed <= pSession->pkcWa.size)
    {
#endif
        pPkcBuffer = & (pSession->pkcWa.buffer[usedWords]);
        pSession->pkcWa.used = expectedUsed;

        if (expectedUsed > pSession->pkcWa.dirty)
        {
            pSession->pkcWa.dirty = expectedUsed;
        }
#if 0
    }
#endif

    return pPkcBuffer;
}

/**
 * @brief (inline) function to free CPU workarea.
 *
 * This function frees specified words from the tail of used CPU workarea.
 * The space is freed but **not** erased (zeroed).
 *
 * @param[in] pSession     Session handle.
 * @param[in] wordsToFree  The size of CPU workarea to be freed, in number of CPU words (uint32_t)
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClSession_freeWords_cpuWa)
static inline void mcuxClSession_freeWords_cpuWa(
    mcuxClSession_Handle_t pSession,
    uint32_t wordsToFree)
{
    if(wordsToFree > pSession->cpuWa.used)
    {
        pSession->cpuWa.used = 0u;
    }
    else
    {
        pSession->cpuWa.used -= wordsToFree;
    }
}

/**
 * @brief (inline) function to free PKC workarea.
 *
 * This function frees specified words from the tail of used PKC workarea.
 * The space is freed but **not** erased (zeroed).
 *
 * @param[in] pSession     Session handle.
 * @param[in] wordsToFree  The size of PKC workarea to be freed, in number of CPU words (uint32_t)
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClSession_freeWords_pkcWa)
static inline void mcuxClSession_freeWords_pkcWa(
    mcuxClSession_Handle_t pSession,
    uint32_t wordsToFree)
{
    if(wordsToFree > pSession->pkcWa.used)
    {
        pSession->pkcWa.used = 0u;
    }
    else
    {
        pSession->pkcWa.used -= wordsToFree;
    }
}

/**
 * @brief (inline) function to get number of used words in CPU workarea
 *
 * This function returns the number of used words in CPU workarea.
 *
 * @param[in] pSession  Session handle.
 *
 * @return The number of CPU words (uint32_t) of used part of CPU workarea.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClSession_getUsage_cpuWa)
static inline uint32_t mcuxClSession_getUsage_cpuWa(
    mcuxClSession_Handle_t pSession)
{
    return pSession->cpuWa.used;
}

/**
 * @brief (inline) function to get number of used words in PKC workarea
 *
 * This function returns the number of used words in PKC workarea.
 *
 * @param[in] pSession  Session handle.
 *
 * @return The number of CPU words (uint32_t) of used part of PKC workarea.
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClSession_getUsage_pkcWa)
static inline uint32_t mcuxClSession_getUsage_pkcWa(
    mcuxClSession_Handle_t pSession)
{
    return pSession->pkcWa.used;
}

/**
 * @brief (inline) function to set number of used words in CPU workarea
 *
 * This function sets (restores) the number of used word(s) in CPU workarea.
 * It frees all space allocated after the corresponding call to #mcuxClSession_getUsage_cpuWa.
 * The space is freed but **not** erased (zeroed).
 *
 * @param[in] pSession         Session handle.
 * @param[in] backupUsedCpuWa  backup of the number of used word(s).
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClSession_setUsage_cpuWa)
static inline void mcuxClSession_setUsage_cpuWa(
    mcuxClSession_Handle_t pSession,
    uint32_t backupUsedCpuWa)
{
    if(backupUsedCpuWa > pSession->cpuWa.size)
    {
        pSession->cpuWa.used = pSession->cpuWa.size;
    }
    else
    {
        pSession->cpuWa.used = backupUsedCpuWa;
    }
}

/**
 * @brief (inline) function to set number of used words in PKC workarea
 *
 * This function sets (restores) the number of used word(s) in PKC workarea.
 * It frees all space allocated after the corresponding call to #mcuxClSession_getUsage_pkcWa.
 * The space is freed but **not** erased (zeroed).
 *
 * @param[in] pSession         Session handle.
 * @param[in] backupUsedPkcWa  backup of the number of used word(s).
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClSession_setUsage_pkcWa)
static inline void mcuxClSession_setUsage_pkcWa(
    mcuxClSession_Handle_t pSession,
    uint32_t backupUsedPkcWa)
{
    if(backupUsedPkcWa > pSession->pkcWa.size)
    {
        pSession->pkcWa.used = pSession->pkcWa.size;
    }
    else
    {
        pSession->pkcWa.used = backupUsedPkcWa;
    }
}


/**
 * @brief Set the Security options in a Crypto Library session.
 *
 * @param  session          Handle for the current CL session.
 * @param  securityOptions  Security options that will be set
 *
 * @return void
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClSession_setSecurityOptions_Internal)
static inline void mcuxClSession_setSecurityOptions_Internal(
  mcuxClSession_Handle_t session,
  mcuxClSession_SecurityOptions_t securityOptions
)
{
/* Unused params*/
    (void) session;
    (void) securityOptions;
}

/**
 * @brief Get the Security options from a Crypto Library session.
 *
 * @param  session          Handle for the current CL session.
 *
 * @return securityOptions  Security options that will be returned
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClSession_getSecurityOptions_Internal)
static inline mcuxClSession_SecurityOptions_t mcuxClSession_getSecurityOptions_Internal(
  mcuxClSession_Handle_t session
)
{
/* Unused param*/
    (void) session;
    return 0u;
}


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLSESSION_INERNAL_H_ */
