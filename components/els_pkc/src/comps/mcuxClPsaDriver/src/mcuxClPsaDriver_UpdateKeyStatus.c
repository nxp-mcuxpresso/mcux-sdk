/*--------------------------------------------------------------------------*/
/* Copyright 2023 NXP                                                       */
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

#include "common.h"

#include <mcuxClKey_Types.h>
#include <mcuxClPsaDriver.h>
#include <mcuxClPsaDriver_Oracle.h>
#include <internal/mcuxClPsaDriver_Functions.h>
#include <internal/mcuxClPsaDriver_Internal.h>
#include <mcuxCsslAnalysis.h>

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusSuspend(
    mcuxClKey_Descriptor_t *key_descriptor)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    psa_key_attributes_t *attributes =
        (psa_key_attributes_t *)key_descriptor->container.pAuxData;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

    psa_key_location_t location =
        PSA_KEY_LIFETIME_GET_LOCATION( attributes->core.lifetime );

    if(false == (MCUXCLPSADRIVER_IS_LOCAL_STORAGE(location)) )
    {
        return mcuxClPsaDriver_Oracle_SuspendKey(key_descriptor);
    }
    else
    {
        return PSA_SUCCESS;
    }
}

psa_status_t mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusResume(
    mcuxClKey_Descriptor_t *key_descriptor)
{
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    psa_key_attributes_t *attributes =
        (psa_key_attributes_t *)key_descriptor->container.pAuxData;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

    psa_key_location_t location =
        PSA_KEY_LIFETIME_GET_LOCATION( attributes->core.lifetime );

    if(false == (MCUXCLPSADRIVER_IS_LOCAL_STORAGE(location)) )
    {
        return mcuxClPsaDriver_Oracle_ResumeKey(key_descriptor);
    }
    else
    {
        return PSA_SUCCESS;
    }
}

MCUX_CSSL_ANALYSIS_START_PATTERN_DESCRIPTIVE_IDENTIFIER()
psa_status_t mcuxClPsaDriver_psa_driver_wrapper_UpdateKeyStatusUnload(
    mcuxClKey_Descriptor_t *key_descriptor)
MCUX_CSSL_ANALYSIS_STOP_PATTERN_DESCRIPTIVE_IDENTIFIER()
{
    MCUX_CSSL_ANALYSIS_START_PATTERN_REINTERPRET_MEMORY_OF_OPAQUE_TYPES()
    psa_key_attributes_t *attributes = (psa_key_attributes_t *)key_descriptor->container.pAuxData;
    MCUX_CSSL_ANALYSIS_STOP_PATTERN_REINTERPRET_MEMORY()

    psa_key_location_t location =
        PSA_KEY_LIFETIME_GET_LOCATION( attributes->core.lifetime );

    if(false == (MCUXCLPSADRIVER_IS_LOCAL_STORAGE(location)) )
    {
        return mcuxClPsaDriver_Oracle_UnloadKey(key_descriptor);
    }
    else
    {
        // the keydescriptor contains a reference to the key_buffer, wiping it would mean wiping the original
        return PSA_SUCCESS;
    }
}

