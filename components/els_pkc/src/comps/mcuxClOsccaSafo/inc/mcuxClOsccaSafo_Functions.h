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

#ifndef MCUXCLOSCCASAFO_FUNCTIONS_H_
#define MCUXCLOSCCASAFO_FUNCTIONS_H_

#include <mcuxCsslFlowProtection.h>
#include <stdbool.h>
#include <mcuxClOsccaSafo_Types.h>
#include <mcuxClOsccaSafo_Sfr_Ctrl.h>

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************
 * Functions related to controlling SAFO
 *****************************************************/

/**
 * @brief Waits until SAFO operation finished
 *
 * @return void
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSafo_Drv_wait)
void mcuxClOsccaSafo_Drv_wait(void);

/**
 * @brief Initializes SAFO
 *
 * Initializes SAFO by setting
 * - CTRL to 0
 * - CTRL2 to the given mode
 *
 * @param[in]  mode   Ctrl2 Configuration
 *
 * @return void
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSafo_Drv_init)
void mcuxClOsccaSafo_Drv_init(uint32_t mode);

/**
 * @brief Closes SAFO
 *
 * Closes SAFO after usage:
 * Returns MCUXCLOSCCASAFO_DRV_CLOSE_ERROR in case an error has occured,
 * otherwise returns MCUXCLOSCCASAFO_DRV_CLOSE_OK.
 *
 * @return error status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSafo_Drv_close)
mcuxClOsccaSafo_Status_t mcuxClOsccaSafo_Drv_close(void);

/**
 * @brief Starts an SAFO operation
 *
 * Starts an SAFO operation:
 * mode(Sm3,Sm4...), Enc/Dec, KeySize, inXor,outXor, KeySel, DatinSel
 * by configuring the CTRL register
 *
 * @param[in]  operation   Configuration of operation to be executed
 *
 * @return void
 */
#ifdef MCUXCL_FEATURE_HW_SAFO_SM3
#define MCUXCLOSCCASAFO_DRV_START_SM3   (MCUXCLOSCCASAFO_SFR_CTRL_SM3 | MCUXCLOSCCASAFO_SFR_CTRL_DATOUT_RES_END_UP)
#endif
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSafo_Drv_start)
void mcuxClOsccaSafo_Drv_start(uint32_t operation);

/**
 * @brief Stops a SM3 operation in AUTO mode
 *
 * Stops a SM3 operation, when SAFO is configured to AUTO mode
 *
 * @return void
 */
#ifdef MCUXCL_FEATURE_HW_SAFO_SM3
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSafo_Drv_stopSm3)
void mcuxClOsccaSafo_Drv_stopSm3(void);
#endif

/**
 * @brief Sets control value (CTRL2)
 *
 * @param[in]  control   Configuration, which CTRL2 shall be set to
 *
 * @return Return original CTRL2 register contents for back up.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSafo_Drv_setControl2)
void mcuxClOsccaSafo_Drv_setControl2(uint32_t control);

#ifdef MCUXCL_FEATURE_HW_SAFO_SM3
/**
 * @brief Configures SM3 operation
 *
 * Configures SM3 operation, setting SM3_CTRL value to control.
 *
 * @param[in]  control   Configuration, which SM3_CTRL shall be set to
 *
 * @return void
 */

#define MCUXCLOSCCASAFO_DRV_STATE_SIZE_SM3  (32u)

#define MCUXCLOSCCASAFO_DRV_DIGEST_SIZE_SM3 (32u)

#define MCUXCLOSCCASAFO_DRV_CONFIG_SM3       (MCUXCLOSCCASAFO_SFR_CTRL_SM3_EN \
                                      | MCUXCLOSCCASAFO_SFR_CTRL_SM3_LOW_LIM) ///< Configures SM3

#define MCUXCLOSCCASAFO_DRV_CONFIG_SM3_LOAD_IV (MCUXCLOSCCASAFO_SFR_CTRL_SM3_HASH_RELOAD \
                                          | MCUXCLOSCCASAFO_SFR_CTRL_SM3_NO_AUTO_INIT) ///< Enables loading a custom IV

#define MCUXCLOSCCASAFO_DRV_CONFIG_SM3_USE_LOADED_IV (MCUXCLOSCCASAFO_SFR_CTRL_SM3_NO_AUTO_INIT) ///< Use state that has been loaded

#define MCUXCLOSCCASAFO_DRV_CONFIG_SM3_AUTO_MODE (MCUXCLOSCCASAFO_SFR_CTRL_SM3_MODE_AUTO \
                                            | MCUXCLOSCCASAFO_SFR_CTRL_SM3_HIGH_LIM) ///< Enable AUTO mode (if not enabled, NORMAL mode is executed, but FIFO limits have to be set explicitly)

#define MCUXCLOSCCASAFO_DRV_CONFIG_SM3_FIFO_HILIM (MCUXCLOSCCASAFO_SFR_CTRL_SM3_HIGH_LIM) ///< Configures FIFO limit for 256-bit data blocks

#define MCUXCLOSCCASAFO_DRV_CONFIG_SM3_AUTOMODE_LOADDATA_USESTANDARDIV (MCUXCLOSCCASAFO_DRV_CONFIG_SM3 \
                                                                      | MCUXCLOSCCASAFO_DRV_CONFIG_SM3_AUTO_MODE) ///< Configures loading data for SM3 in auto mode using the standard IV

#define MCUXCLOSCCASAFO_DRV_CONFIG_SM3_AUTOMODE_LOADIV (MCUXCLOSCCASAFO_DRV_CONFIG_SM3 \
                                                      | MCUXCLOSCCASAFO_DRV_CONFIG_SM3_AUTO_MODE \
                                                      | MCUXCLOSCCASAFO_DRV_CONFIG_SM3_LOAD_IV) ///< Configures loading an IV/state for SM3 in auto mode

#define MCUXCLOSCCASAFO_DRV_CONFIG_SM3_AUTOMODE_LOADDATA_USELOADEDIV (MCUXCLOSCCASAFO_DRV_CONFIG_SM3 \
                                                                    | MCUXCLOSCCASAFO_DRV_CONFIG_SM3_AUTO_MODE \
                                                                    | MCUXCLOSCCASAFO_DRV_CONFIG_SM3_USE_LOADED_IV) ///< Configures loading data for SM3 in auto mode using an already loaded IV

#define MCUXCLOSCCASAFO_DRV_CONFIG_SM3_NORMALMODE_LOADDATA_USESTANDARDIV (MCUXCLOSCCASAFO_DRV_CONFIG_SM3 \
                                                                        | MCUXCLOSCCASAFO_DRV_CONFIG_SM3_FIFO_HILIM) ///< Configures loading data for SM3 in normal mode using the standard IV

#define MCUXCLOSCCASAFO_DRV_CONFIG_SM3_NORMALMODE_LOADIV (MCUXCLOSCCASAFO_DRV_CONFIG_SM3 \
                                                        | MCUXCLOSCCASAFO_DRV_CONFIG_SM3_FIFO_HILIM \
                                                        | MCUXCLOSCCASAFO_DRV_CONFIG_SM3_LOAD_IV) ///< Configures loading loading an IV/state for SM3 in normal mode

#define MCUXCLOSCCASAFO_DRV_CONFIG_SM3_NORMALMODE_LOADDATA_USELOADEDIV (MCUXCLOSCCASAFO_DRV_CONFIG_SM3 \
                                                                      | MCUXCLOSCCASAFO_DRV_CONFIG_SM3_FIFO_HILIM \
                                                                      | MCUXCLOSCCASAFO_DRV_CONFIG_SM3_USE_LOADED_IV) ///< Configures loading data for SM3 in normal mode using an already loaded IV

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSafo_Drv_configureSm3)
void mcuxClOsccaSafo_Drv_configureSm3(uint32_t control);

/**
 * @brief Enable loading a custom hash IV (intermediate state) to the SAFO.
 *
 * Updates control value (SM3_CTRL) to enable loading partial digest to the SAFO.
 * After calling this function, data loaded to DATIN will be interpreted as IV.
 *
 * @note: Alternatively option MCUXCLOSCCASAFO_DRV_CONFIG_SM3_LOAD_IV can be chosen, when configuring SM3.
 *
 * @return void
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSafo_Drv_enableHashReload)
void mcuxClOsccaSafo_Drv_enableHashReload(void);

/**
 * @brief Disable loading a custom hash IV (intermediate state) to the SAFO.
 *
 * Updates control value (SM3_CTRL) to disable reloading the partial digest to the SAFO.
 * After loading an IV, this function can be called to indicate that input data will be loaded in the sequel.
 * Data loaded to DATIN after calling this function is interpreted as input data to hashing.
 *
 * @return void
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSafo_Drv_disableHashReload)
void mcuxClOsccaSafo_Drv_disableHashReload(void);

/**
 * @brief Disable using a standard IV for SAFO operation.
 *
 * Updates control value (SM3_CTRL) to disable using a standard IV for SAFO operation.
 * After initializing SAFO with AUTO_INIT option, this function can be called to load further blocks, without
 * re-initialization of the SAFO.
 *
 * @return void
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSafo_Drv_disableIvAutoInit)
void mcuxClOsccaSafo_Drv_disableIvAutoInit(void);

/**
 * @brief Enable using a standard IV for SAFO operation.
 *
 * Updates control value (SM3_CTRL) to enable using a standard IV for SAFO operation.
 *
 * @return void
 */
MCUX_CSSL_FP_FUNCTION_DEF(mcuxClOsccaSafo_Drv_enableIvAutoInit)
void mcuxClOsccaSafo_Drv_enableIvAutoInit(void);
#endif

/*****************************************************
 * Functions related to security features
 *****************************************************/

/**
 * @brief Flush SAFO
 *
 * Flushes SAFO SFRs and register banks based on configuration (all, key, datain)
 *
 * @param[in]  option   Configuration, which registers shall be flushed
 *
 * @return void
 */
#define MCUXCLOSCCASAFO_DRV_FLUSH_ALL  (MCUXCLOSCCASAFO_SFR_CTRL2_FLUSH)
#define MCUXCLOSCCASAFO_DRV_FLUSH_KEY  (MCUXCLOSCCASAFO_SFR_CTRL2_FLUSHKEY)
#define MCUXCLOSCCASAFO_DRV_FLUSH_DATA (MCUXCLOSCCASAFO_SFR_CTRL2_FLUSHDATA)
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSafo_Drv_enableFlush)
void mcuxClOsccaSafo_Drv_enableFlush(uint32_t option);

/*****************************************************
 * Functions related to input output handling
 *****************************************************/

/**
 * @brief Fetch key into a key register
 *
 * Fetch one word of the key to the key register. Offset specifies
 * the location in the KEY register bank with respect to SAFO->KEY0A,
 * where the word is written to
 *
 * @param[in]  offset   Offset with respect to SAFO->KEY0A. Must be the offset of a valid SAFO KEY register.
 * @param[in]  key      Key to be written to KEY
 *
 * @return void
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSafo_Drv_loadKey)
void mcuxClOsccaSafo_Drv_loadKey(uint32_t offset, uint32_t key);

#ifdef MCUXCL_FEATURE_HW_SAFO_SM4
/**
 * @brief Increments by 1 (with carry) value in datin
 *
 * Increments data in DATIN register bank by one.
 *
 * @param[in]  offset   Offset with respect to SAFO->DATIN0A
 * @param[in]  length   Size of data on which increment shall be applied
 *
 * @return void
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSafo_Drv_incrementData)
void mcuxClOsccaSafo_Drv_incrementData(uint32_t offset, uint32_t length);
#endif

/**
 * @brief Set byte order
 *
 * Sets the byte order of reading from and writing to register banks.
 *
 * @param[in]  mode   Specifies byte order mode to be used
 *
 * @return Return original CTRL2 register contents for back up.
 */
#define MCUXCLOSCCASAFO_DRV_BYTE_ORDER_LE (MCUXCLOSCCASAFO_SFR_CTRL2_BYTES_ORDER)
#define MCUXCLOSCCASAFO_DRV_BYTE_ORDER_BE (0u)
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSafo_Drv_setByteOrder)
uint32_t mcuxClOsccaSafo_Drv_setByteOrder(uint32_t mode);

#ifdef MCUXCL_FEATURE_HW_SAFO_SM4
/**
 * @brief Enables XOR on write
 *
 * Enables XORWR feature of register banks, such that
 * value is XORed with data currently contained in register bank.
 *
 * @return Return original CTRL2 register contents for back up.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSafo_Drv_enableXorWrite)
uint32_t mcuxClOsccaSafo_Drv_enableXorWrite(void);

/**
 * @brief Disables XOR on write
 *
 * Disables XORWR feature of register banks.
 *
 * @return void
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSafo_Drv_disableXorWrite)
void mcuxClOsccaSafo_Drv_disableXorWrite(void);
#endif

/**
 * @brief Fetch data into a data register
 *
 * Fetch one word of data to data register. Offset specifies
 * the location in the DATIN register bank with respect to SAFO->DATIN0A,
 * where the word is written to
 *
 * @param[in]  offset   Offset with respect to SAFO->DATIN0A. Must be the offset of a valid SAFO DATIN register.
 * @param[in]  data     Data to be written to DATIN
 *
 * @return void
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSafo_Drv_load)
void mcuxClOsccaSafo_Drv_load(uint32_t offset, uint32_t data);

#ifdef MCUXCL_FEATURE_HW_SAFO_SM3
/**
 * @brief Write data into SHA FIFO in AUTO mode
 *
 * Write one word to the SHA FIFO.
 *
 * @param[in]  data   Data to be written to FIFO
 *
 * @return void
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSafo_Drv_loadFifo)
void mcuxClOsccaSafo_Drv_loadFifo(uint32_t data);
#endif

#ifdef MCUXCL_FEATURE_HW_SAFO_SM4
/**
 * @brief Select output mode
 *
 * Selects whether to store the SAFO result to the output
 * register banks in plain, or whether to XOR it with data from DATIN
 * register banks, prior to storing it in DATOUT.
 *
 * @param[in]  mode   Specifies output mode to be used
 *
 * @return Return original CTRL register contents for back up.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSafo_Drv_dataOut_res)
uint32_t mcuxClOsccaSafo_Drv_dataOut_res(uint32_t mode);

/**
 * @brief Enables storing output in key register
 *
 * Enables to store the output of a crypto operation in a key
 * register bank, indicated by keyIndex.
 *
 * @param[in]  keyIndex   Indicates key register bank, which the output shall be written to
 *
 * @return Return original CTRL2 register contents for back up.
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSafo_Drv_enableOutputToKey)
uint32_t mcuxClOsccaSafo_Drv_enableOutputToKey(uint32_t keyIndex);

/**
 * @brief Disable output to key
 *
 * Disables to store the output of a crypto operation in a key
 * register bank. Output will be stored in DATOUT.
 *
 * @return void
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSafo_Drv_disableOutputToKey)
void mcuxClOsccaSafo_Drv_disableOutputToKey(void);
#endif

/**
 * @brief Trigger writing result to DATOUT
 *
 * Only 128 bits of output are stored in the output register
 * in one step. This function triggers writing the next 128 bits
 * of the output to DATOUT.
 *
 * @note: It must be checked, with mcuxClOsccaSafo_Drv_wait that the
 *        writing of output data completed, before fetching it from DATOUT.
 *
 * @return void
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSafo_Drv_triggerOutput)
void mcuxClOsccaSafo_Drv_triggerOutput(void);

/**
 * @brief Get result from output register
 *
 * Get one output word from DATOUT register banks. Offset
 * specifies the word to be read with respect to SAFO->DATOUTA.
 *
 * @param[in]  offset   Offset with respect to SAFO->DATOUTA. Must be the offset of a valid SAFO DATOUT register.
 *
 * @return 32-bit result word
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSafo_Drv_store)
uint32_t mcuxClOsccaSafo_Drv_store(uint32_t offset);

/**
 * @brief Get data from input registers
 *
 * Get one input word from DATINx register banks. Offset
 * specifies the word to be read with respect to SAFO->DATIN0A.
 *
 * @param[in]  offset   Offset with respect to SAFO->DATIN0A. Must be the offset of a valid SAFO DATIN register.
 *
 * @return 32-bit result word
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSafo_Drv_storeInput)
uint32_t mcuxClOsccaSafo_Drv_storeInput(uint32_t offset);



/**
 * @brief Get key from Key registers
 *
 * Get one key word from KEYx register banks. Offset
 * specifies the word to be read with respect to SAFO->KEY0A.
 *
 * @param[in]  offset   Offset with respect to SAFO->KEY0A. Must be the offset of a valid SAFO KEY register.
 *
 * @return 32-bit key word
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSafo_Drv_storeKey)
uint32_t mcuxClOsccaSafo_Drv_storeKey(uint32_t offset);

/**
 * @brief Get result from status register
 *
 * Get status register and check if SAFO raised an error
 *
 * @return bool status
 */
MCUX_CSSL_FP_FUNCTION_DECL(mcuxClOsccaSafo_Drv_isStatusError)
bool mcuxClOsccaSafo_Drv_isStatusError(void);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCUXCLOSCCASAFO_FUNCTIONS_H_ */
