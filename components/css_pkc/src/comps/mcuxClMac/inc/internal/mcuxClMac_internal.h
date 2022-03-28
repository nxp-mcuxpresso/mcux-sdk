/*--------------------------------------------------------------------------*/
/* Copyright 2020 NXP                                                       */
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

/** @file  mcuxClMac_internal.h
 *  @brief header for mac helper functions.
 */

#ifndef MCUXCLMAC_INTERNAL_H_
#define MCUXCLMAC_INTERNAL_H_

#include <mcuxClMac_Types.h>

/**********************************************
 * INTERNAL TYPES
 **********************************************/

/**
 * @brief Mac engine function type
 *
 * This function will perform the actual MAC operation
 *
 */
typedef mcuxClMac_Status_Protected_t (*mcuxClMac_ModeEngine_t)(struct mcuxClMac_Context *context, const uint8_t *const in, uint32_t inSize, uint8_t *const out, uint32_t *const outSize);

/**
 * @brief Mac Mode structure
 *
 * This internal structure provides all implementation details for a mode to the top level mcuxClMac functions.
 * It consists of Init, Update, Finalize and Oneshot engines and the output size.
 *
 */
struct mcuxClMac_Mode
{
  mcuxClMac_ModeEngine_t engineInit;     ///< engine function to perform the init operation
  mcuxClMac_ModeEngine_t engineUpdate;   ///< engine function to perform the update operation
  mcuxClMac_ModeEngine_t engineFinalize; ///< engine function to perform the finalize operation
  mcuxClMac_ModeEngine_t engineOneshot;  ///< engine function to perform the Mac operation in one shot
  uint32_t protectionTokenInit;     ///< protection token of the engine function to perform the init operation
  uint32_t protectionTokenUpdate;   ///< protection token of the engine function to perform the update operation
  uint32_t protectionTokenFinalize; ///< protection token of the engine function to perform the finalize operation
  uint32_t protectionTokenOneshot;  ///< protection token of the engine function to perform the Mac operation in one shot
  uint32_t macByteSize; ///< Default value(s) in predefined structs, for custom truncation length, provide a macro or function to construct a suitable structure
};

/**
 * @brief Mac context structure
 *
 * This structure captures all the information that the Mac interface needs to
 * know for a particular Mac mode/algorithm to work.
 */
struct mcuxClMac_Context
{
  mcuxClKey_Descriptor_t * key;  ///< Key descriptor of the key to be used
  mcuxClSession_Descriptor_t * session; ///< Session descriptor to be used
  mcuxClMac_Mode_t mode; ///< Mode of the Mac calculation. e.g mcuxClMac_Mode_CMAC
  uint32_t unprocessed[4]; ///< Not yet processed input data from the input stream
  uint32_t state[4]; ///< state/intermediate result of the mac operation
  uint8_t nrOfUnprocessedBytes; ///< number of not yet processed bytes
  mcuxClCss_CmacOption_t cmac_options; ///< Cmac Css options to be used
};

/**
 * @brief Mac Cpu Work Area structure
 *
 */
struct mcuxClMac_WaCpu_t
{
  uint8_t aesBlock [16];  ///< Mac aes block
};


/**********************************************
 * INTERNAL FUNCTIONS
 **********************************************/
/**
 * @brief Internal functions for the MAC component
 */

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMac_Engine_CMAC_Oneshot)
mcuxClMac_Status_Protected_t mcuxClMac_Engine_CMAC_Oneshot(
    mcuxClMac_Context_t *context,            /*! CMAC context */
    const uint8_t *const in,                /*! CMAC input */
    uint32_t inSize,                        /*! Input size */
    uint8_t *const out,                     /*! CMAC output */
    uint32_t *const outSize                 /*! Output size */
    );

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMac_Engine_HMAC_Oneshot)
mcuxClMac_Status_Protected_t mcuxClMac_Engine_HMAC_Oneshot(
    mcuxClMac_Context_t *context,            /*! HMAC context */
    const uint8_t *const in,                /*! HMAC input */
    uint32_t inSize,                        /*! Input size */
    uint8_t *const out,                     /*! HMAC output */
    uint32_t *const outSize                 /*! Output size */
    );

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMac_Engine_CMAC_Init)
mcuxClMac_Status_Protected_t mcuxClMac_Engine_CMAC_Init(
    mcuxClMac_Context_t *context,            /*! CMAC context */
    const uint8_t *const in,                /*! CMAC input */
    uint32_t inSize,                        /*! Input size */
    uint8_t *const out,                     /*! CMAC output */
    uint32_t *const outSize                 /*! Output size */
    );

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMac_Engine_HMAC_Init)
mcuxClMac_Status_Protected_t mcuxClMac_Engine_HMAC_Init(
    mcuxClMac_Context_t *context,            /*! HMAC context */
    const uint8_t *const in,                /*! HMAC input */
    uint32_t inSize,                        /*! Input size */
    uint8_t *const out,                     /*! HMAC output */
    uint32_t *const outSize                 /*! Output size */
    );

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMac_Engine_CMAC_Update)
mcuxClMac_Status_Protected_t mcuxClMac_Engine_CMAC_Update(
    mcuxClMac_Context_t *context,            /*! CMAC context */
    const uint8_t *const in,                /*! CMAC input */
    uint32_t inSize,                        /*! Input size */
    uint8_t *const out,                     /*! CMAC output */
    uint32_t *const outSize                 /*! Output size */
    );

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMac_Engine_HMAC_Update)
mcuxClMac_Status_Protected_t mcuxClMac_Engine_HMAC_Update(
    mcuxClMac_Context_t *context,            /*! HMAC context */
    const uint8_t *const in,                /*! HMAC input */
    uint32_t inSize,                        /*! Input size */
    uint8_t *const out,                     /*! HMAC output */
    uint32_t *const outSize                 /*! Output size */
    );

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMac_Engine_CMAC_Finalize)
mcuxClMac_Status_Protected_t mcuxClMac_Engine_CMAC_Finalize(
    mcuxClMac_Context_t *context,            /*! CMAC context */
    const uint8_t *const in,                /*! CMAC input */
    uint32_t inSize,                        /*! Input size */
    uint8_t *const out,                     /*! CMAC output */
    uint32_t *const outSize                 /*! Output size */
    );

MCUX_CSSL_FP_FUNCTION_DECL(mcuxClMac_Engine_HMAC_Finalize)
mcuxClMac_Status_Protected_t mcuxClMac_Engine_HMAC_Finalize(
    mcuxClMac_Context_t *context,            /*! HMAC context */
    const uint8_t *const in,                /*! HMAC input */
    uint32_t inSize,                        /*! Input size */
    uint8_t *const out,                     /*! HMAC output */
    uint32_t *const outSize                 /*! Output size */
    );

#endif /* MCUXCLMAC_INTERNAL_H_ */
