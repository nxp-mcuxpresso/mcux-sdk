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

#include <internal/mcuxClHash_Internal.h>
#include <internal/mcuxClOsccaSm3_Core_sm3.h>
#include <internal/mcuxClOsccaSm3_SfrAccess.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClOscca_FunctionIdentifiers.h>

static void mcuxClOsccaSm3_SafoWaitforFinish(void)
{
    do{

    } while(0u != MCUXCLOSCCASM3_SAFO_SGI_SFR_BITREAD(STATUS, BUSY));
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm3_Safo_Hash_PreLoad)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm3_Safo_Hash_PreLoad(uint32_t *workArea)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm3_Safo_Hash_PreLoad);
    uint32_t i;

    //step1:Setup the SM3 control SFRs for Loading partial HASH into SGI
    //SM3_MODE = 1'b1 (AUTO mode)
    //SM3_LOW_LIM = 4'b0000
    //SM3_HIGH_LIM = 4'b1111
    //SM3_COUNT_EN = 1'b0
    //HASH_RELOAD =1'b1
    //SM3_STOP = 1'b0
    //NO_AUTO_INIT = 1'b1
    //SM3_EN = 1'b1
    //SM3_SGI_SM3_CTRL =0x0001AF02;
    uint32_t sgi_sm3_ctrl = MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(SM3_CTRL, SM3_MODE, 1u)
                          | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(SM3_CTRL, SM3_LOW_LIM, 0u)
                          | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(SM3_CTRL, SM3_HIGH_LIM, 15u)
                          | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(SM3_CTRL, SM3_COUNT_EN, 0u)
                          | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(SM3_CTRL, HASH_RELOAD, 1u)
                          | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(SM3_CTRL, SM3_STOP, 0u)
                          | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(SM3_CTRL, NO_AUTO_INIT, 1u)
                          | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(SM3_CTRL, SM3_EN, 1u);
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(SM3_CTRL, sgi_sm3_ctrl);

    //Step2:Setup the SGI Control SFRs
    // START = 1'b1
    //CRYPTO_OP = 3'b111
    //DATOUT_RES = 2'b00 (END_UP)
    //SM3_SGI_CTRL = 0x00000071;
    uint32_t sgi_ctrl = MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_MASK(CTRL,START)
                      | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(CTRL, CRYPTO_OP, 7u)
                      | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(CTRL, DATOUT_RES, 0u);
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(CTRL, sgi_ctrl);

    uint32_t sgi_ctrl2 = MCUXCLOSCCASM3_SAFO_SGI_SFR_READ(CTRL2);
    sgi_ctrl2 &= ~MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(CTRL2, BYTES_ORDER, 1);
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(CTRL2, sgi_ctrl2);

    //Step3: Load partial Hash
    for(i=0u;i<=7u;i++)
    {
        /* MISRA Ex. 12 - Rule 11.8 */
        MCUXCLOSCCASM3_SET_FIFO_FIELD(0u);
    }
    for(i=8u;i<=15u;i++)
    {
        /* MISRA Ex. 12 - Rule 11.8 */
        MCUXCLOSCCASM3_SET_FIFO_FIELD(workArea[15u - ((i) & 15u)]);
    }

    //Step4:Configure SGI_SM3_CTRL SFRs to stop AUTO mode
    // SM3_STOP = 1'b1
    sgi_sm3_ctrl = MCUXCLOSCCASM3_SAFO_SGI_SFR_READ(SM3_CTRL);
    sgi_sm3_ctrl |= MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(SM3_CTRL, SM3_STOP, 1u);
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(SM3_CTRL, sgi_sm3_ctrl);

    //Step5:Wait for the SM3 operation to complete
    mcuxClOsccaSm3_SafoWaitforFinish();

    /* update SC and return */
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaSm3_Safo_Hash_PreLoad);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm3_Safo_Hash_Norm)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm3_Safo_Hash_Norm(uint32_t *workArea, uint32_t *data)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm3_Safo_Hash_Norm);

    //step1:Setup the SM3 control SFRs
    //SM3_MODE = 1'b0 (NORM mode)
    //SM3_LOW_LIM = 4'b0000
    //SM3_HIGH_LIM = 4'b1111
    //SM3_COUNT_EN = 1'b0
    //SM3_STOP = 1'b0
    //NO_AUTO_INIT = 1'b0
    //SM3_EN = 1'b1
    uint32_t sgi_sm3_ctrl = MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(SM3_CTRL, SM3_MODE, 0u)
                          | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(SM3_CTRL, SM3_LOW_LIM, 0u)
                          | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(SM3_CTRL, SM3_HIGH_LIM, 15u)
                          | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(SM3_CTRL, SM3_COUNT_EN, 0u)
                          | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(SM3_CTRL, SM3_STOP, 0u)
                          | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(SM3_CTRL, NO_AUTO_INIT, 0u)
                          | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(SM3_CTRL, SM3_EN, 1u);
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(SM3_CTRL, sgi_sm3_ctrl);

    //Step2:Load message into SFRs
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(DATIN0A, data[15]);
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(DATIN0B, data[14]);
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(DATIN0C, data[13]);
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(DATIN0D, data[12]);
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(DATIN1A, data[11]);
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(DATIN1B, data[10]);
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(DATIN1C, data[9]);
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(DATIN1D, data[8]);
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(KEY0A, data[7]);
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(KEY0B, data[6]);
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(KEY0C, data[5]);
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(KEY0D, data[4]);
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(KEY1A, data[3]);
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(KEY1B, data[2]);
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(KEY1C, data[1]);
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(KEY1D, data[0]);

    //Step3:Setup the SGI control SRFs
    // START = 1'b1
    //CRYPTO_OP = 3'b111
    //DATOUT_RES = 2'b00 (END_UP)
    //SM3_SGI_CTRL = 0x00000070;
    uint32_t sgi_ctrl = MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_MASK(CTRL,START)
                      | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(CTRL, CRYPTO_OP, 7u)
                      | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(CTRL, DATOUT_RES, 0u);
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(CTRL, sgi_ctrl);

    //Step4:Wait for the SM3 operation to complete
    mcuxClOsccaSm3_SafoWaitforFinish();
    workArea[0] = MCUXCLOSCCASM3_SAFO_SGI_SFR_READ(DATOUTA);
    workArea[1] = MCUXCLOSCCASM3_SAFO_SGI_SFR_READ(DATOUTB);
    workArea[2] = MCUXCLOSCCASM3_SAFO_SGI_SFR_READ(DATOUTC);
    workArea[3] = MCUXCLOSCCASM3_SAFO_SGI_SFR_READ(DATOUTD);

    //Step5:Set the DATOUT_RES to TRIGGER_UP mode,then get the upper 128bits output
    //DATOUT_RES = 2'b10 (TRIGGER_UP)
    //START = 1'b1
    sgi_ctrl = MCUXCLOSCCASM3_SAFO_SGI_SFR_READ(CTRL);
    sgi_ctrl |= MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(CTRL, DATOUT_RES, 2u);
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(CTRL, sgi_ctrl);

    mcuxClOsccaSm3_SafoWaitforFinish();
    workArea[4] = MCUXCLOSCCASM3_SAFO_SGI_SFR_READ(DATOUTA);
    workArea[5] = MCUXCLOSCCASM3_SAFO_SGI_SFR_READ(DATOUTB);
    workArea[6] = MCUXCLOSCCASM3_SAFO_SGI_SFR_READ(DATOUTC);
    workArea[7] = MCUXCLOSCCASM3_SAFO_SGI_SFR_READ(DATOUTD);
    /* update SC and return */
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaSm3_Safo_Hash_Norm);
}

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSm3_Safo_Hash_Auto)
MCUX_CSSL_FP_PROTECTED_TYPE(void) mcuxClOsccaSm3_Safo_Hash_Auto(uint32_t *workArea, uint32_t *data)
{
    MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClOsccaSm3_Safo_Hash_Auto);

    //step1:Setup the SM3 control SFRs
    //SM3_MODE = 1'b1 (AUTO mode)
    //SM3_LOW_LIM = 4'b0000
    //SM3_HIGH_LIM = 4'b1111
    //SM3_COUNT_EN = 1'b0
    //HASH_RELOAD =1'b0
    //SM3_STOP = 1'b0
    //NO_AUTO_INIT = 1'b1
    //SM3_EN = 1'b1
    //SM3_SGI_SM3_CTRL =0x00018F02;
    uint32_t sgi_sm3_ctrl = MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(SM3_CTRL, SM3_MODE, 1u)
                          | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(SM3_CTRL, SM3_LOW_LIM, 0u)
                          | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(SM3_CTRL, SM3_HIGH_LIM, 15u)
                          | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(SM3_CTRL, SM3_COUNT_EN, 0u)
                          | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(SM3_CTRL, HASH_RELOAD, 0u)
                          | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(SM3_CTRL, SM3_STOP, 0u)
                          | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(SM3_CTRL, NO_AUTO_INIT, 1u)
                          | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(SM3_CTRL, SM3_EN, 1u);
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(SM3_CTRL, sgi_sm3_ctrl);

    //Step2:Setup the SGI Control SFRs
    // START = 1'b1
    //CRYPTO_OP = 3'b111
    //DATOUT_RES = 2'b00 (END_UP)
    //SM3_SGI_CTRL = 0x00000071;
    uint32_t sgi_ctrl = MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_MASK(CTRL,START)
                      | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(CTRL, CRYPTO_OP, 7u)
                      | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(CTRL, DATOUT_RES, 0u);
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(CTRL, sgi_ctrl);

    //Step3:Load message into SGI_SM3_FIFO SFRs
    for(uint32_t i=0u;i<=15u;i++)
    {
        /* MISRA Ex. 12 - Rule 11.8 */
        MCUXCLOSCCASM3_SET_FIFO_FIELD(data[15u - ((i) & 15u)]);
    }

    //Step4:Configure SGI_SM3_CTRL SFRs to stop AUTO mode
    // SM3_STOP = 1'b1
    sgi_sm3_ctrl = MCUXCLOSCCASM3_SAFO_SGI_SFR_READ(SM3_CTRL);
    sgi_sm3_ctrl |= MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(SM3_CTRL, SM3_STOP, 1u);
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(SM3_CTRL, sgi_sm3_ctrl);

    //Step5:Wait for the SM3 operation to complete
    mcuxClOsccaSm3_SafoWaitforFinish();
    workArea[0] = MCUXCLOSCCASM3_SAFO_SGI_SFR_READ(DATOUTA);
    workArea[1] = MCUXCLOSCCASM3_SAFO_SGI_SFR_READ(DATOUTB);
    workArea[2] = MCUXCLOSCCASM3_SAFO_SGI_SFR_READ(DATOUTC);
    workArea[3] = MCUXCLOSCCASM3_SAFO_SGI_SFR_READ(DATOUTD);

    //Step6:Set the DATOUT_RES to TRIGGER_UP mode,then get the upper 128bits output
    //DATOUT_RES = 2'b10 (TRIGGER_UP)
    //START = 1'b1
    sgi_ctrl = MCUXCLOSCCASM3_SAFO_SGI_SFR_READ(CTRL);
    sgi_ctrl |= MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(CTRL, DATOUT_RES, 2u)
              | MCUXCLOSCCASM3_SAFO_SGI_SFR_FIELD_FORMAT(CTRL, START, 1u);
    MCUXCLOSCCASM3_SAFO_SGI_SFR_WRITE(CTRL, sgi_ctrl);

    mcuxClOsccaSm3_SafoWaitforFinish();
    workArea[4] = MCUXCLOSCCASM3_SAFO_SGI_SFR_READ(DATOUTA);
    workArea[5] = MCUXCLOSCCASM3_SAFO_SGI_SFR_READ(DATOUTB);
    workArea[6] = MCUXCLOSCCASM3_SAFO_SGI_SFR_READ(DATOUTC);
    workArea[7] = MCUXCLOSCCASM3_SAFO_SGI_SFR_READ(DATOUTD);

    /* update SC and return */
    MCUX_CSSL_FP_FUNCTION_EXIT_VOID(mcuxClOsccaSm3_Safo_Hash_Auto);
}
