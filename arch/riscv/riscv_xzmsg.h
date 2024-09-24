/*
 * Copyright 2023-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef RISCV_XZMSG_H_
#define RISCV_XZMSG_H_

#include <stdint.h>

/*!
 * @ingroup RISCV_CoreCustomExt
 * @defgroup RISCV_CoreCustomExtXzmsg Message Send and Receive Extension (Xzmsg)
 * @details Message Send and Receive Extension 0.1 supported.
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Send EZH-V given int-channel Interrupt To Arm  */
/*! @{ */
#define XZMSG_INTCHAN_MSK       (0xFFFFU)
#define XZMSG_INTCHAN_SHIFT     (0U)
/*! INTCHAN - send the interrupt of given channel request */
#define XZMSG_INTCHAN_EN(x)     (((uint32_t)(((uint32_t)(x)) << XZMSG_INTCHAN_SHIFT)) & XZMSG_INTCHAN_MSK)
/*! @} */

/*! @name Send toggle IO message  */
/*! @{ */
#define XZMSG_GPIO_BYTE_WISE        (0x8U)
#define XZMSG_GPIO_TOGGLE_MSK       (0xFFU)
#define XZMSG_GPIO_TOGGLE_SHIFT     (0U)
/*! @brief Toggle PIO */
#define XZMSG_GPIO_TOGGLE_EN(x)     (((uint32_t)(((uint32_t)(x)) << XZMSG_GPIO_TOGGLE_SHIFT)) & XZMSG_GPIO_TOGGLE_MSK)

#define XZMSG_GPIO_SET_MSK          (0xFF00U)
#define XZMSG_GPIO_SET_SHIFT        (8U)
/*! @brief Set PIO */
#define XZMSG_GPIO_SET_EN(x)        (((uint32_t)(((uint32_t)(x)) << XZMSG_GPIO_SET_SHIFT)) & XZMSG_GPIO_SET_MSK)

#define XZMSG_GPIO_CLR_MSK          (0xFF0000U)
#define XZMSG_GPIO_CLR_SHIFT        (16U)
/*! @brief Clear PIO */
#define XZMSG_GPIO_CLR_EN(x)        (((uint32_t)(((uint32_t)(x)) << XZMSG_GPIO_CLR_SHIFT)) & XZMSG_GPIO_CLR_MSK)
/*! @} */

/*! @brief Define Message Send Type rs2 in the message send interface(XZMSG_Send(rs1, rs2) */
typedef enum _xzmsg_snd_type
{
    kXZMSG_UpdateGpio7ToGpio0    = 0x1U,  /*!< message to update state of EZH_GPIOs[7:0]   */
    kXZMSG_UpdateGpio15ToGpio8   = 0x2U,  /*!< message to update state of EZH_GPIOs[15:8]  */
    kXZMSG_UpdateGpio23ToGpio16  = 0x4U,  /*!< message to update state of EZH_GPIOs[23:16] */
    kXZMSG_UpdateGpio31ToGpio24  = 0x8U,  /*!< message to update state of EZH_GPIOs[31:24] */
    kXZMSG_SetIntChain           = 0x10U, /*!< message to set ezhv_int_chain[15:0]=rs1[15:0] and
        issue a 1 cycle pulse on ezhv_int_ind (only if int_chan != 0) */
} xzmsg_snd_type;

/*!
 * @brief Define Message data Received from each port
 *
 * The receive messages [7:0] are {dbiu_data[3:0], gpio_i, ev_stat, ev_vect, ev_stat}
 */
typedef enum _xzmsg_rcv_type
{
    kXZMSG_RcvP0EmEventStat    = 0x0U,  /*!< message port0 map to ez_em_cfg0 (2084) register, blocking*/
    kXZMSG_RcvP1EmEventVect    = 0x1U,  /*!< message port1 map to interrupt vector address computed as {VBASE[15:0],VOFFS_1[13:0],2'b0}, when VIE=0, blocking */
    kXZMSG_RcvP2EmEventStat    = 0x2U,  /*!< message port2 map to ez_em_cfg0 (2084) register, non-blocking */
    kXZMSG_RcvP3GpioInput      = 0x3U,  /*!< message port3 map to ez_gpio_i (2102) register, non-blocking */
    kXZMSG_RcvP4DbiuData0      = 0x4U,  /*!< message port4 map to ez_dbiu_data_0 (2097) register, non-blocking */
    kXZMSG_RcvP5DbiuData1      = 0x5U,  /*!< message port5 map to ez_dbiu_data_1 (2098) register, non-blocking */
    kXZMSG_RcvP6DbiuData2      = 0x6U,  /*!< message port6 map to ez_dbiu_data_1 (2099) register, non-blocking */
    kXZMSG_RcvP7DbiuData3      = 0x7U,  /*!< message port7 map to ez_dbiu_data_1 (2100) register, non-blocking */
} xzmsg_rcv_type;

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cpluplus
extern "C" {
#endif

/*!
 * @name Send Messages
 * @{
 *
 * @details Description about the send message instruction(send rd, rs1, rs2)
 *
 * This instruction has limited support in zv2116. It has two usages:
 *   - It can be used to set the ezhv_int_ind and ezhv_int_chan outputs.
 *   - Additionally, it can be used to set ezhv_gpio_out outputs byte-wise with clear/set/toggle.
 *
   @verbatim
   blocking = (rd == X0)
   if (blocking)
       wait for (msg_snd_ready == 1)
   if (msg_snd_ready == 1)
       msg_snd_req = 1
       msg_snd_core = rs2[23:16]
       msg_snd_ctrl = {rs2[12:8],rs2[7:0]}
       msg_snd_data = rs1[31:0]
       rd = 32'b1
    else
       rd = 32'b0
   @endverbatim
 *
 * Supported uses in zv2116:
 * send x0, rs1, rs2
 *
 * @note Only one bit may be set in rs2. If more than one bit is set, the behavior is undefined.!!!
 *
 * (EZH-V Signals:ezhv_int_ind, ezhv_int_chan[23:0], ezhv_gpio_out[31:0])
 *
 * If (rs2[4] == 1), set ezhv_int_chan[23:0]=rs1[23:0] and issue a 1 cycle
 *                   pulse on ezhv_int_ind (only if int_chan != 0).
 *
 * If (rs2[3] == 1), for ezhv_gpio_out[31:24],
 *     clear bits indicated by rs1[23:16],
 *     set bits indicated by rs1[15:8],
 *     toggle bits indicated by rs1[7:0].
 *
 * If (rs2[2] == 1), for ezhv_gpio_out[23:16],
 *     clear bits indicated by rs1[23:16],
 *     set bits indicated by rs1[15:8],
 *     toggle bits indicated by rs1[7:0].
 *
 * If (rs2[1] == 1), for ezhv_gpio_out[15:8],
 *     clear bits indicated by rs1[23:16],
 *     set bits indicated by rs1[15:8],
 *     toggle bits indicated by rs1[7:0].
 *
 * If (rs2[0] == 1), for ezhv_gpio_out[7:0],
 *     clear bits indicated by rs1[23:16],
 *     set bits indicated by rs1[15:8],
 *     toggle bits indicated by rs1[7:0].
 */

/*!
 * @brief blocking way to send message to update EZHV_PIO or set ezhv_int_chan output
 *
 * @param msgVal  message value
 * @param msgType message type, refer to enum "xzmsg_snd_type".
 */
static inline void XZMSG_Send(uint32_t msgVal, xzmsg_snd_type msgType)
{
    asm volatile ("send zero, %0, %1"
            : : "r"(msgVal), "r" (msgType)
            : "memory");
}

/*!
 * @}
 */

/*!
 * @name Receive Messages
 * @{
 *
 * @details Description about message receive instructions
 *
   @verbatim
   recvkd rd, rs2 (r=0, d=1, i=0)
   recvkdi rd, imm (r=0, d=1, i=1)
   recvrd rd, rs2 (r=1, d=1, i=0)
   recvrdi rd, imm (r=1, d=1, i=1)
   @endverbatim
 *
 * Only p=0,1 are supported in zv2116 and may be used as blocking to wait for an event.
 * For p=2-7, the message will always be ready. Retiring this message will act as a read
 * and cause behavior as described in EZH-V Extension. These receive messages map to ez_em_cfg0,
 * ez_gpio_i, and ez_dbiu_data_[0-3], respectively and provide an alternative way to read
 * those registers. Reads to these registers with retire will trigger the same behavior
 * as if they were CSR reads.Ports 8-9 shall not be accessed.
 *
   @verbatim
   rs2 : Source GPR. Message receive port to read.
   imm : Message receive port to read.
   rd : Destination GPR.
   @endverbatim
 *
 * Update with sender information (address, destination port, and command) or data.
   @verbatim
   d = data (d) or content information (c)
   r = retire (r) or keep (k)
   i = immediate (i) or register based port number
   p = (i) ? imm[4:0] : rs2[4:0]
   @endverbatim
 *
 * when WXN=0 (default), the message receive interface is used. In this situation,
 * SW should execute a blocking, retire, wait for data message instruction for p=0.
 * The core will suspend execution and only resume when an enabled event occurs.
 * In this case, the contents of ez_em_cfg0 are presented as the data message.
 * */

/*!
 * @brief receive message, keep, receive message
 *
 * @param type From what message to receive
 *
 * @return the the data from the given port
 */
static inline uint32_t XZMSG_Rcvkd(xzmsg_rcv_type type)
{
    uint32_t ret;
    asm volatile ("recvkd %0, %1"
        : "=r"(ret) : "r"(type) : "memory");
    return ret;
}

/*!
 * @brief retire, receive message, port=rs2[4:0], behavior equal to CSR read
 *
 * @param type From what message to receive
 *
 * @return the the data from the given port
 */
static inline uint32_t XZMSG_Rcvrd(xzmsg_rcv_type type)
{
    uint32_t __ret;
    asm volatile ("recvrd %0, %1"
        : "=r"(__ret) : "r"(type) : "memory");
    return __ret;
}

/*!
 * @brief keep, receive message, port=imm[4:0]
 *
 * @param imm    portid, must be immediate
 *
 * @return the the data from the given port
 */
#define XZMSG_Rcvkdi(imm)                          \
({                                                 \
    uint32_t __ret;                                \
    asm volatile ("recvkdi %0, " #imm              \
                : "=r"(__ret)                      \
                : : "memory");                     \
    __ret;                                         \
})

/*!
 * @brief retire, receive message, port=imm[4:0]
 *
 * @param imm port id, Immediate
 *
 * @return the the data from given port
 */
#define XZMSG_Rcvrdi(imm)                          \
({                                                 \
    uint32_t __ret;                                \
    asm volatile ("recvrdi %0, " #imm              \
                : "=r"(__ret)                      \
                : : "memory");                     \
    __ret;                                         \
})

/*!
 * @}
 */

/*!
 * @brief send EZH-V Interrupt message of given channel to ARM.
 *
 * Set ezhv_int_chan[15:0]=rs1[15:0] and issue a 1 cycle pulse
 * on ezhv_int_ind (only if int_chan != 0)
 *
 * @param channel    channel value.
 */
static inline void XZMSG_IndIntChan(uint32_t channel)
{
    XZMSG_Send(XZMSG_INTCHAN_EN(channel), kXZMSG_SetIntChain);
}

#ifdef __cplusplus
}
#endif

/*! @} */

#endif /* RISCV_XZMSG_H_ */
