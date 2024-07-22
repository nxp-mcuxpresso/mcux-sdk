/*--------------------------------------------------------------------------*/
/* Copyright 2023-2024 NXP                                                  */
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

#include <mcuxClOsccaSafo.h>
#include <mcuxClOsccaSafo_Sfr_Status.h>

/** Waits until SAFO operation finished */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_wait)
void mcuxClOsccaSafo_Drv_wait(void)
{
  while(MCUXCLOSCCASAFO_SFR_STATUS_BUSY( mcuxClOsccaSafo_Sfr_readStatus() ) ) {/*nothing*/}
}

/** Initializes SAFO by setting CTRL to 0 and CTRL2 to the provided value. */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_init)
void mcuxClOsccaSafo_Drv_init(uint32_t mode)
{
  mcuxClOsccaSafo_Drv_wait();
  mcuxClOsccaSafo_Sfr_writeCtrl(0u);
  mcuxClOsccaSafo_Sfr_writeCtrl2(mode);
}

/** Closes SAFO after usage, returns error state. */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_close)
mcuxClOsccaSafo_Status_t mcuxClOsccaSafo_Drv_close(void)
{
  if( MCUXCLOSCCASAFO_SFR_STATUS_ERROR( mcuxClOsccaSafo_Sfr_readStatus() ))
  {
    return MCUXCLOSCCASAFO_STATUS_ERROR;
  }
  else
  {
    return MCUXCLOSCCASAFO_STATUS_OK;
  }
}

/** Starts an SAFO operation
  Operation: mode(Sm3, Sm4...), Enc/Dec, KeySize, inXor,outXor, KeySel, DatinSel */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_start)
void mcuxClOsccaSafo_Drv_start(uint32_t operation)
{
  mcuxClOsccaSafo_Sfr_writeCtrl(operation | MCUXCLOSCCASAFO_SFR_CTRL_START);
}

#ifdef MCUXCL_FEATURE_HW_SAFO_SM3
/** Stops SM3 operation */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_stopSm3)
void mcuxClOsccaSafo_Drv_stopSm3(void)
{
  /* Read SM3_CTRL SFR */
  const uint32_t ctrlsm3 = mcuxClOsccaSafo_Sfr_readSm3Ctrl();

  /* Stop SM3 operation */
  mcuxClOsccaSafo_Sfr_writeSm3Ctrl(ctrlsm3 | MCUXCLOSCCASAFO_SFR_CTRL_SM3_SM3_STOP);
}
#endif

/** Sets control value (CTRL2) */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_setControl2)
void mcuxClOsccaSafo_Drv_setControl2(uint32_t control)
{
  mcuxClOsccaSafo_Sfr_writeCtrl2(control);
}

#ifdef MCUXCL_FEATURE_HW_SAFO_SM3
/** Configures SM3 operation (SM3_CTRL) */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_configureSm3)
void mcuxClOsccaSafo_Drv_configureSm3(uint32_t control)
{
    mcuxClOsccaSafo_Sfr_writeSm3Ctrl(control);
}

/** Configures SM3 operation (SM3_CTRL) */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_enableHashReload)
void mcuxClOsccaSafo_Drv_enableHashReload(void)
{
    /* Read SM3_CTRL SFR */
    const uint32_t ctrlsm3 = mcuxClOsccaSafo_Sfr_readSm3Ctrl();

    mcuxClOsccaSafo_Sfr_writeSm3Ctrl(ctrlsm3 | MCUXCLOSCCASAFO_SFR_CTRL_SM3_HASH_RELOAD);
}

/** Configures SM3 operation (SM3_CTRL) */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_disableHashReload)
void mcuxClOsccaSafo_Drv_disableHashReload(void)
{
    /* Read SM3_CTRL SFR */
    const uint32_t ctrlsm3 = mcuxClOsccaSafo_Sfr_readSm3Ctrl();

    mcuxClOsccaSafo_Sfr_writeSm3Ctrl(ctrlsm3 & (~MCUXCLOSCCASAFO_SFR_CTRL_SM3_HASH_RELOAD));
}

/** Configure SM3 operation; disable IV AUTO-INIT */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_disableIvAutoInit)
void mcuxClOsccaSafo_Drv_disableIvAutoInit(void)
{
    /* Read SM3_CTRL SFR */
    const uint32_t ctrlsm3 = mcuxClOsccaSafo_Sfr_readSm3Ctrl();

    mcuxClOsccaSafo_Sfr_writeSm3Ctrl(ctrlsm3 | (MCUXCLOSCCASAFO_SFR_CTRL_SM3_NO_AUTO_INIT));
}

/** Configure SM3 operation; disable IV AUTO-INIT */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_enableIvAutoInit)
void mcuxClOsccaSafo_Drv_enableIvAutoInit(void)
{
    /* Read SM3_CTRL SFR */
    const uint32_t ctrlsm3 = mcuxClOsccaSafo_Sfr_readSm3Ctrl();

    mcuxClOsccaSafo_Sfr_writeSm3Ctrl(ctrlsm3 & (~MCUXCLOSCCASAFO_SFR_CTRL_SM3_NO_AUTO_INIT));
}
#endif

/** Flush all/key/datain */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_enableFlush)
void mcuxClOsccaSafo_Drv_enableFlush(uint32_t option)
{
  /* Backup CTRL2 SFR */
  const uint32_t ctrl2 = mcuxClOsccaSafo_Sfr_readCtrl2();

  /* Enable flush write mode */
  mcuxClOsccaSafo_Sfr_writeCtrl2(ctrl2 | option);

  mcuxClOsccaSafo_Drv_wait();
}

/** Fetch key into a key register  */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_loadKey)
void mcuxClOsccaSafo_Drv_loadKey(uint32_t offset, uint32_t key)
{
    mcuxClOsccaSafo_Sfr_writeKeyWord(offset, key);
}

#ifdef MCUXCL_FEATURE_HW_SAFO_SM4
/** Increments by 1 (with carry) value in datin*/
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_incrementData)
void mcuxClOsccaSafo_Drv_incrementData(uint32_t offset, uint32_t length)
{
  uint32_t config2 = mcuxClOsccaSafo_Sfr_readCtrl2();
  mcuxClOsccaSafo_Sfr_writeCtrl2(config2 | MCUXCLOSCCASAFO_SFR_CTRL2_INCR);

  length >>= MCUXCLOSCCASAFO_SFR_BYTES_TO_32BIT_WORD_SHIFT;    /* calculate length in a word*/
  uint32_t oriLen = length;
  //Increment from last to first
  while(0u != length)
  {
    length --;
    uint32_t offsetLen = (((config2 & MCUXCLOSCCASAFO_SFR_CTRL2_BYTES_ORDER_MASK) == MCUXCLOSCCASAFO_DRV_BYTE_ORDER_LE)
                              ? (oriLen - 1u - length) : (length));
    //writing something to DATIN - this will trigger incrementation
    mcuxClOsccaSafo_Sfr_writeDatinWord(offset + offsetLen, 1u);
    mcuxClOsccaSafo_Sfr_writeCtrl2(config2 | MCUXCLOSCCASAFO_SFR_CTRL2_INCR | MCUXCLOSCCASAFO_SFR_CTRL2_INCR_CIN);
  }

  //Restore config
  mcuxClOsccaSafo_Sfr_writeCtrl2(config2);
}
#endif

/** Set byte order
 * Returns previous control value*/
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_setByteOrder)
uint32_t mcuxClOsccaSafo_Drv_setByteOrder(uint32_t mode)
{
  const uint32_t ctrl2 = mcuxClOsccaSafo_Sfr_readCtrl2();

  mcuxClOsccaSafo_Sfr_writeCtrl2((ctrl2 & (~MCUXCLOSCCASAFO_SFR_CTRL2_BYTES_ORDER_MASK)) | mode );

  return ctrl2;
}

#ifdef MCUXCL_FEATURE_HW_SAFO_SM4
/** Enables xor on write
 * Returns previous control value*/
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_enableXorWrite)
uint32_t mcuxClOsccaSafo_Drv_enableXorWrite(void)
{
  /* Backup CTRL2 SFR */
  const uint32_t ctrl2 = mcuxClOsccaSafo_Sfr_readCtrl2();

  /* Enable flush write mode */
  mcuxClOsccaSafo_Sfr_writeCtrl2(ctrl2 | MCUXCLOSCCASAFO_SFR_CTRL2_XORWR);

  /* Return the backup */
  return ctrl2;
}

/** Disable xor on write */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_disableXorWrite)
void mcuxClOsccaSafo_Drv_disableXorWrite(void)
{
  /* Backup CTRL2 SFR */
  const uint32_t ctrl2 = mcuxClOsccaSafo_Sfr_readCtrl2();

  /* Disable xor on write mode */
  mcuxClOsccaSafo_Sfr_writeCtrl2(ctrl2 & (~MCUXCLOSCCASAFO_SFR_CTRL2_XORWR));
}
#endif

/** Fetch data into a data register  */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_load)
void mcuxClOsccaSafo_Drv_load(uint32_t offset, uint32_t data)
{
  mcuxClOsccaSafo_Sfr_writeDatinWord(offset, data);
}

#ifdef MCUXCL_FEATURE_HW_SAFO_SM3
/** Write SM3 input data to FIFO */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_loadFifo)
void mcuxClOsccaSafo_Drv_loadFifo(uint32_t data)
{
  mcuxClOsccaSafo_Sfr_writeFifoWord(data);
}
#endif

#ifdef MCUXCL_FEATURE_HW_SAFO_SM4
/** Set data out  */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_dataOut_res)
uint32_t mcuxClOsccaSafo_Drv_dataOut_res(uint32_t mode)
{
  const uint32_t ctrl = mcuxClOsccaSafo_Sfr_readCtrl();

   /* Selects whether to store the SAFO result to DATOUT, or whether to XOR it with data from DATIN register banks */
  mcuxClOsccaSafo_Sfr_writeCtrl((ctrl &  ~(MCUXCLOSCCASAFO_SFR_CTRL_OUTSEL_MASK)) | mode);

  /* Return the backup */
  return ctrl;
}

/** Enables storing output in key register
  * Returns previous control value*/
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_enableOutputToKey)
uint32_t mcuxClOsccaSafo_Drv_enableOutputToKey(uint32_t keyIndex)
{
  const uint32_t ctrl2 = mcuxClOsccaSafo_Sfr_readCtrl2();

  /* Enables storing output in key register */
  mcuxClOsccaSafo_Sfr_writeCtrl2((ctrl2 & (~MCUXCLOSCCASAFO_SFR_CTRL2_KEYRES_MASK)) | MCUXCLOSCCASAFO_SFR_CTRL2_KEYRES(keyIndex) | MCUXCLOSCCASAFO_SFR_CTRL2_RKEY);

  /* Return the backup */
  return ctrl2;
}

/** Disable output to key */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_disableOutputToKey)
void mcuxClOsccaSafo_Drv_disableOutputToKey(void)
{
  const uint32_t ctrl2 = mcuxClOsccaSafo_Sfr_readCtrl2();

  mcuxClOsccaSafo_Sfr_writeCtrl2(ctrl2 & (~MCUXCLOSCCASAFO_SFR_CTRL2_RKEY));
}
#endif

/** Trigger writing result to DATOUT */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_triggerOutput)
void mcuxClOsccaSafo_Drv_triggerOutput(void)
{
  const uint32_t ctrl = mcuxClOsccaSafo_Sfr_readCtrl();
  mcuxClOsccaSafo_Sfr_writeCtrl(ctrl | MCUXCLOSCCASAFO_SFR_CTRL_TRIGGER_UP | MCUXCLOSCCASAFO_SFR_CTRL_START);
}

/** Get result from output register */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_store)
uint32_t mcuxClOsccaSafo_Drv_store(uint32_t offset)
{
  return mcuxClOsccaSafo_Sfr_readDatoutWord(offset);
}


/** Get data from input register */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_storeInput)
uint32_t mcuxClOsccaSafo_Drv_storeInput(uint32_t offset)
{
  return mcuxClOsccaSafo_Sfr_readDatinWord(offset);
}

/** Get key from key register */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_storeKey)
uint32_t mcuxClOsccaSafo_Drv_storeKey(uint32_t offset)
{
  return mcuxClOsccaSafo_Sfr_readKeyWord(offset);
}

/** Check error status  */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_isStatusError)
bool mcuxClOsccaSafo_Drv_isStatusError(void)
{
  return MCUXCLOSCCASAFO_SFR_STATUS_ERROR(mcuxClOsccaSafo_Sfr_readStatus());
}

