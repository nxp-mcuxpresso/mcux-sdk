/*--------------------------------------------------------------------------*/
/* Copyright 2020-2022 NXP                                                  */
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

/** @file  mcuxClOsccaSm3.h
 *  @brief Top-level include file for the @ref mcuxClOsccaSm3 component
 *
 *  This includes headers for all of the functionality provided by the @ref mcuxClOsccaSm3 component.
 *
 *  @defgroup mcuxClOsccaSm3 mcuxClOsccaSm3
 *  @brief Hash component
 *
 *  The mcuxClOsccaSm3 component implements the Hash functionality supported by CLNS.
 *
 *  An example of how to use the @ref mcuxClOsccaSm3 component can be found in /mcuxClOsccaSm3/ex.
 *
 *  The @ref mcuxClOsccaSm3 component supports interfaces to either hash a message in one shot
 *  (mcuxClOsccaSm3_compute) or to hash it in parts (mcuxClOsccaSm3_init, mcuxClOsccaSm3_process,
 *  and mcuxClOsccaSm3_finish). In case of hashing a message in parts, first an initialization
 *  has to be performed (mcuxClOsccaSm3_init), followed by zero, one, or multiple updates
 *  (mcuxClOsccaSm3_process), followed by a finalization (mcuxClOsccaSm3_finish). The finalization
 *  generates the output data (digest) and destroys the context. After the finalization step,
 *  no further updates are possible.
 *
 *  The targeted hash algorithm is selected by passing one of the offered algorithm mode
 *  descriptors (@ref mcuxClOsccaSm3_Modes), which are listed in file mcuxClOsccaSm3_Algorithms.h
 *
 *  Note: In case the hashing functionality is based on a hardware co-processor, it might
 *  be necessary to initialize the co-processor, before it's use in the @ref mcuxClOsccaSm3
 *  component. Please refer to the example for further information on this.
 *
 * */

#ifndef MCUXCLOSCCASM3_H_
#define MCUXCLOSCCASM3_H_

#include <mcuxClOsccaSm3_Algorithms.h>
#include <mcuxClOsccaSm3_Constants.h>
#include <mcuxClOsccaSm3_MemoryConsumption.h>

#endif /* MCUXCLOSCCASM3_H_ */
