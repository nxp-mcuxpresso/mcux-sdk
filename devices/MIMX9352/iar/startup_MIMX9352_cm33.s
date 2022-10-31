; -------------------------------------------------------------------------
;  @file:    startup_MIMX9352_cm33.s
;  @purpose: CMSIS Cortex-M33 Core Device Startup File
;            MIMX9352_cm33
;  @version: 1.0
;  @date:    2021-11-16
;  @build:   b220830
; -------------------------------------------------------------------------
;
; Copyright 1997-2016 Freescale Semiconductor, Inc.
; Copyright 2016-2022 NXP
; All rights reserved.
;
; SPDX-License-Identifier: BSD-3-Clause
;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)
        SECTION HEAP:DATA:NOROOT(3)
        SECTION RW:DATA:NOROOT(2)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table
        PUBLIC  __vector_table_0x1c
        PUBLIC  __Vectors
        PUBLIC  __Vectors_End
        PUBLIC  __Vectors_Size

        DATA

__iar_init$$done:              ; The vector table is not needed
                      ; until after copy initialization is done

__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler

        DCD     NMI_Handler                                   ;NMI Handler
        DCD     HardFault_Handler                             ;Hard Fault Handler
        DCD     MemManage_Handler                             ;MPU Fault Handler
        DCD     BusFault_Handler                              ;Bus Fault Handler
        DCD     UsageFault_Handler                            ;Usage Fault Handler
__vector_table_0x1c
        DCD     SecureFault_Handler                           ;Secure Fault Handler
        DCD     0                                             ;Reserved
        DCD     0                                             ;Reserved
        DCD     0                                             ;Reserved
        DCD     SVC_Handler                                   ;SVCall Handler
        DCD     DebugMon_Handler                              ;Debug Monitor Handler
        DCD     0                                             ;Reserved
        DCD     PendSV_Handler                                ;PendSV Handler
        DCD     SysTick_Handler                               ;SysTick Handler

                                                              ;External Interrupts
        DCD     Reserved16_IRQHandler                         ;Exception condition notification while boot
        DCD     Reserved17_IRQHandler                         ;DAP interrupt
        DCD     Reserved18_IRQHandler                         ;Reserved interrupt
        DCD     Reserved19_IRQHandler                         ;CTI trigger outputs from CM33 platform
        DCD     Reserved20_IRQHandler                         ;CTI trigger outputs from CA55 platform
        DCD     Reserved21_IRQHandler                         ;Performance Unit Interrupts from CA55 platform
        DCD     Reserved22_IRQHandler                         ;ECC error from CA55 platform cache
        DCD     Reserved23_IRQHandler                         ;1-bit or 2-bit ECC or Parity error from CA55 platform cache
        DCD     CAN1_IRQHandler                               ;CAN1 interrupt
        DCD     CAN1_ERROR_IRQHandler                         ;CAN1 error interrupt
        DCD     Reserved26_IRQHandler                         ;General Purpose Input/Output 1 interrupt 0
        DCD     Reserved27_IRQHandler                         ;General Purpose Input/Output 1 interrupt 1
        DCD     I3C1_IRQHandler                               ;Improved Inter-Integrated Circuit 1 interrupt
        DCD     LPI2C1_IRQHandler                             ;Low Power Inter-Integrated Circuit module 1
        DCD     LPI2C2_IRQHandler                             ;Low Power Inter-Integrated Circuit module 2
        DCD     LPIT1_IRQHandler                              ;Low Power Periodic Interrupt Timer 1
        DCD     LPSPI1_IRQHandler                             ;Low Power Serial Peripheral Interface 1
        DCD     LPSPI2_IRQHandler                             ;Low Power Serial Peripheral Interface 2
        DCD     LPTMR1_IRQHandler                             ;Low Power Timer 1
        DCD     LPUART1_IRQHandler                            ;Low Power UART 1
        DCD     LPUART2_IRQHandler                            ;Low Power UART 2
        DCD     MU1_A_IRQHandler                              ;Messaging Unit 1 - Side A (to communicate with M7 core)
        DCD     MU1_B_IRQHandler                              ;Messaging Unit 1 - Side B (to communicate with M33 core)
        DCD     MU2_A_IRQHandler                              ;Messaging Unit 2 - Side A (to communicate with M7 core)
        DCD     MU2_B_IRQHandler                              ;Messaging Unit 2 - Side B (to communicate with A55 core)
        DCD     Reserved41_IRQHandler                         ;Reserved interrupt
        DCD     Reserved42_IRQHandler                         ;Reserved interrupt
        DCD     Reserved43_IRQHandler                         ;Reserved interrupt
        DCD     Reserved44_IRQHandler                         ;Edgelock Trust MUA RX full interrupt
        DCD     Reserved45_IRQHandler                         ;Edgelock Trust MUA TX empty interrupt
        DCD     Reserved46_IRQHandler                         ;Edgelock Apps Core MUA RX full interrupt
        DCD     Reserved47_IRQHandler                         ;Edgelock Apps Core MUA TX empty interrupt
        DCD     Reserved48_IRQHandler                         ;Edgelock Realtime Core MUA RX full interrupt
        DCD     Reserved49_IRQHandler                         ;Edgelock Realtime Core MUA TX empty interrupt
        DCD     Reserved50_IRQHandler                         ;Edgelock secure interrupt
        DCD     Reserved51_IRQHandler                         ;Edgelock non-secure interrupt
        DCD     TPM1_IRQHandler                               ;Timer PWM module 1
        DCD     TPM2_IRQHandler                               ;Timer PWM module 2
        DCD     WDOG1_IRQHandler                              ;Watchdog 1 Interrupt
        DCD     WDOG2_IRQHandler                              ;Watchdog 2 Interrupt
        DCD     TRDC_IRQHandler                               ;AONMIX TRDC transfer error interrupt
        DCD     Reserved57_IRQHandler                         ;Reserved interrupt
        DCD     Reserved58_IRQHandler                         ;Reserved interrupt
        DCD     Reserved59_IRQHandler                         ;Reserved interrupt
        DCD     Reserved60_IRQHandler                         ;Reserved interrupt
        DCD     SAI1_IRQHandler                               ;Serial Audio Interface 1
        DCD     Reserved62_IRQHandler                         ;M33 PS Tag/Data Parity Error
        DCD     Reserved63_IRQHandler                         ;M33 TCM ECC interrupt
        DCD     Reserved64_IRQHandler                         ;M33 TCM Error interrupt
        DCD     Reserved65_IRQHandler                         ;Reserved interrupt
        DCD     Reserved66_IRQHandler                         ;Reserved interrupt
        DCD     CAN2_IRQHandler                               ;CAN2 interrupt
        DCD     CAN2_ERROR_IRQHandler                         ;CAN2 error interrupt
        DCD     FLEXIO1_IRQHandler                            ;Flexible IO 1 interrupt
        DCD     FLEXIO2_IRQHandler                            ;Flexible IO 2 interrupt
        DCD     FlexSPI1_IRQHandler                           ;FlexSPI controller interface interrupt 1
        DCD     Reserved72_IRQHandler                         ;Reserved interrupt
        DCD     Reserved73_IRQHandler                         ;General Purpose Input/Output 2 interrupt 0
        DCD     Reserved74_IRQHandler                         ;General Purpose Input/Output 2 interrupt 1
        DCD     Reserved75_IRQHandler                         ;General Purpose Input/Output 3 interrupt 0
        DCD     Reserved76_IRQHandler                         ;General Purpose Input/Output 3 interrupt 1
        DCD     I3C2_IRQHandler                               ;Improved Inter-Integrated Circuit 2 interrupt
        DCD     LPI2C3_IRQHandler                             ;Low Power Inter-Integrated Circuit module 3
        DCD     LPI2C4_IRQHandler                             ;Low Power Inter-Integrated Circuit module 4
        DCD     LPIT2_IRQHandler                              ;Low Power Periodic Interrupt Timer 2
        DCD     LPSPI3_IRQHandler                             ;Low Power Serial Peripheral Interface 3
        DCD     LPSPI4_IRQHandler                             ;Low Power Serial Peripheral Interface 4
        DCD     LPTMR2_IRQHandler                             ;Low Power Timer 2
        DCD     LPUART3_IRQHandler                            ;Low Power UART 3
        DCD     LPUART4_IRQHandler                            ;Low Power UART 4
        DCD     LPUART5_IRQHandler                            ;Low Power UART 5
        DCD     LPUART6_IRQHandler                            ;Low Power UART 6
        DCD     Reserved88_IRQHandler                         ;MTR Master error interrupt
        DCD     Reserved89_IRQHandler                         ;BBNSM Non-Secure interrupt
        DCD     Reserved90_IRQHandler                         ;System Counter compare interrupt
        DCD     TPM3_IRQHandler                               ;Timer PWM module 3
        DCD     TPM4_IRQHandler                               ;Timer PWM module 4
        DCD     TPM5_IRQHandler                               ;Timer PWM module 5
        DCD     TPM6_IRQHandler                               ;Timer PWM module 6
        DCD     WDOG3_IRQHandler                              ;Watchdog 3 Interrupt
        DCD     WDOG4_IRQHandler                              ;Watchdog 4 Interrupt
        DCD     WDOG5_IRQHandler                              ;Watchdog 5 Interrupt
        DCD     Reserved98_IRQHandler                         ;WAKEUPMIX TRDC transfer error interrupt
        DCD     Reserved99_IRQHandler                         ;TempSensor interrupt
        DCD     Reserved100_IRQHandler                        ;Reserved interrupt
        DCD     Reserved101_IRQHandler                        ;Reserved interrupt
        DCD     uSDHC1_IRQHandler                             ;ultra Secure Digital Host Controller interrupt 1
        DCD     uSDHC2_IRQHandler                             ;ultra Secure Digital Host Controller interrupt 2
        DCD     Reserved104_IRQHandler                        ;MEGAMIX TRDC transfer error interrupt
        DCD     Reserved105_IRQHandler                        ;NIC_WRAPPER TRDC transfer error interrupt
        DCD     Reserved106_IRQHandler                        ;DRAM controller Performance Monitor Interrupt
        DCD     Reserved107_IRQHandler                        ;DRAM controller Critical Interrupt
        DCD     Reserved108_IRQHandler                        ;DRAM Phy Critical Interrupt
        DCD     Reserved109_IRQHandler                        ;Reserved interrupt
        DCD     DMA3_ERROR_IRQHandler                         ;eDMA1 error interrupt
        DCD     DMA3_0_IRQHandler                             ;eDMA1 Channel 0 interrupt
        DCD     DMA3_1_IRQHandler                             ;eDMA1 Channel 1 interrupt
        DCD     DMA3_2_IRQHandler                             ;eDMA1 Channel 2 interrupt
        DCD     DMA3_3_IRQHandler                             ;eDMA1 Channel 3 interrupt
        DCD     DMA3_4_IRQHandler                             ;eDMA1 Channel 4 interrupt
        DCD     DMA3_5_IRQHandler                             ;eDMA1 Channel 5 interrupt
        DCD     DMA3_6_IRQHandler                             ;eDMA1 Channel 6 interrupt
        DCD     DMA3_7_IRQHandler                             ;eDMA1 Channel 7 interrupt
        DCD     DMA3_8_IRQHandler                             ;eDMA1 Channel 8 interrupt
        DCD     DMA3_9_IRQHandler                             ;eDMA1 Channel 9 interrupt
        DCD     DMA3_10_IRQHandler                            ;eDMA1 Channel 10 interrupt
        DCD     DMA3_11_IRQHandler                            ;eDMA1 Channel 11 interrupt
        DCD     DMA3_12_IRQHandler                            ;eDMA1 Channel 12 interrupt
        DCD     DMA3_13_IRQHandler                            ;eDMA1 Channel 13 interrupt
        DCD     DMA3_14_IRQHandler                            ;eDMA1 Channel 14 interrupt
        DCD     DMA3_15_IRQHandler                            ;eDMA1 Channel 15 interrupt
        DCD     DMA3_16_IRQHandler                            ;eDMA1 Channel 16 interrupt
        DCD     DMA3_17_IRQHandler                            ;eDMA1 Channel 17 interrupt
        DCD     DMA3_18_IRQHandler                            ;eDMA1 Channel 18 interrupt
        DCD     DMA3_19_IRQHandler                            ;eDMA1 Channel 19 interrupt
        DCD     DMA3_20_IRQHandler                            ;eDMA1 Channel 20 interrupt
        DCD     DMA3_21_IRQHandler                            ;eDMA1 Channel 21 interrupt
        DCD     DMA3_22_IRQHandler                            ;eDMA1 Channel 22 interrupt
        DCD     DMA3_23_IRQHandler                            ;eDMA1 Channel 23 interrupt
        DCD     DMA3_24_IRQHandler                            ;eDMA1 Channel 24 interrupt
        DCD     DMA3_25_IRQHandler                            ;eDMA1 Channel 25 interrupt
        DCD     DMA3_26_IRQHandler                            ;eDMA1 Channel 26 interrupt
        DCD     DMA3_27_IRQHandler                            ;eDMA1 Channel 27 interrupt
        DCD     DMA3_28_IRQHandler                            ;eDMA1 Channel 28 interrupt
        DCD     DMA3_29_IRQHandler                            ;eDMA1 Channel 29 interrupt
        DCD     DMA3_30_IRQHandler                            ;eDMA1 Channel 30 interrupt
        DCD     Reserved142_IRQHandler                        ;Reserved interrupt
        DCD     DMA4_ERROR_IRQHandler                         ;eDMA2 error interrupt
        DCD     DMA4_0_1_IRQHandler                           ;eDMA2 channel 0/1 interrupt
        DCD     DMA4_2_3_IRQHandler                           ;eDMA2 channel 2/3 interrupt
        DCD     DMA4_4_5_IRQHandler                           ;eDMA2 channel 4/5 interrupt
        DCD     DMA4_6_7_IRQHandler                           ;eDMA2 channel 6/7 interrupt
        DCD     DMA4_8_9_IRQHandler                           ;eDMA2 channel 8/9 interrupt
        DCD     DMA4_10_11_IRQHandler                         ;eDMA2 channel 10/11 interrupt
        DCD     DMA4_12_13_IRQHandler                         ;eDMA2 channel 12/13 interrupt
        DCD     DMA4_14_15_IRQHandler                         ;eDMA2 channel 14/15 interrupt
        DCD     DMA4_16_17_IRQHandler                         ;eDMA2 channel 16/17 interrupt
        DCD     DMA4_18_19_IRQHandler                         ;eDMA2 channel 18/19 interrupt
        DCD     DMA4_20_21_IRQHandler                         ;eDMA2 channel 20/21 interrupt
        DCD     DMA4_22_23_IRQHandler                         ;eDMA2 channel 22/23 interrupt
        DCD     DMA4_24_25_IRQHandler                         ;eDMA2 channel 24/25 interrupt
        DCD     DMA4_26_27_IRQHandler                         ;eDMA2 channel 26/27 interrupt
        DCD     DMA4_28_29_IRQHandler                         ;eDMA2 channel 28/29 interrupt
        DCD     DMA4_30_31_IRQHandler                         ;eDMA2 channel 30/31 interrupt
        DCD     DMA4_32_33_IRQHandler                         ;eDMA2 channel 32/33 interrupt
        DCD     DMA4_34_35_IRQHandler                         ;eDMA2 channel 34/35 interrupt
        DCD     DMA4_36_37_IRQHandler                         ;eDMA2 channel 36/37 interrupt
        DCD     DMA4_38_39_IRQHandler                         ;eDMA2 channel 38/39 interrupt
        DCD     DMA4_40_41_IRQHandler                         ;eDMA2 channel 40/41 interrupt
        DCD     DMA4_42_43_IRQHandler                         ;eDMA2 channel 42/43 interrupt
        DCD     DMA4_44_45_IRQHandler                         ;eDMA2 channel 44/45 interrupt
        DCD     DMA4_46_47_IRQHandler                         ;eDMA2 channel 46/47 interrupt
        DCD     DMA4_48_49_IRQHandler                         ;eDMA2 channel 48/49 interrupt
        DCD     DMA4_50_51_IRQHandler                         ;eDMA2 channel 50/51 interrupt
        DCD     DMA4_52_53_IRQHandler                         ;eDMA2 channel 52/53 interrupt
        DCD     DMA4_54_55_IRQHandler                         ;eDMA2 channel 54/55 interrupt
        DCD     DMA4_56_57_IRQHandler                         ;eDMA2 channel 56/57 interrupt
        DCD     DMA4_58_59_IRQHandler                         ;eDMA2 channel 58/59 interrupt
        DCD     DMA4_60_61_IRQHandler                         ;eDMA2 channel 60/61 interrupt
        DCD     DMA4_62_63_IRQHandler                         ;eDMA2 channel 62/63 interrupt
        DCD     Reserved176_IRQHandler                        ;Reserved interrupt
        DCD     Reserved177_IRQHandler                        ;Edgelock Group 1 reset source
        DCD     Reserved178_IRQHandler                        ;Edgelock Group 2 reset source
        DCD     Reserved179_IRQHandler                        ;Edgelock Group 2 reset source
        DCD     Reserved180_IRQHandler                        ;JTAGSW DAP MDM-AP SRC reset source
        DCD     Reserved181_IRQHandler                        ;JTAGC SRC reset source
        DCD     Reserved182_IRQHandler                        ;CM33 SYSREQRST SRC reset source
        DCD     Reserved183_IRQHandler                        ;CM33 LOCKUP SRC reset source
        DCD     Reserved184_IRQHandler                        ;Reserved interrupt
        DCD     Reserved185_IRQHandler                        ;Reserved interrupt
        DCD     SAI2_IRQHandler                               ;Serial Audio Interface 2
        DCD     SAI3_IRQHandler                               ;Serial Audio Interface 3
        DCD     ISI_IRQHandler                                ;ISI interrupt
        DCD     Reserved189_IRQHandler                        ;PXP interrupt 0
        DCD     Reserved190_IRQHandler                        ;PXP interrupt 1
        DCD     CSI_IRQHandler                                ;CSI interrupt
        DCD     Reserved192_IRQHandler                        ;LCDIF Sync Interrupt
        DCD     DSI_IRQHandler                                ;MIPI DSI Interrupt Request
        DCD     Reserved194_IRQHandler                        ;Machine learning processor interrupt
        DCD     ENET_MAC0_Rx_Tx_Done1_IRQHandler              ;MAC 0 Receive / Trasmit Frame / Buffer Done
        DCD     ENET_MAC0_Rx_Tx_Done2_IRQHandler              ;MAC 0 Receive / Trasmit Frame / Buffer Done
        DCD     ENET_IRQHandler                               ;MAC 0 IRQ
        DCD     ENET_1588_IRQHandler                          ;MAC 0 1588 Timer Interrupt - synchronous
        DCD     ENET_QOS_PMT_IRQHandler                       ;ENET QOS PMT interrupt
        DCD     ENET_QOS_IRQHandler                           ;ENET QOS interrupt
        DCD     Reserved201_IRQHandler                        ;Reserved interrupt
        DCD     Reserved202_IRQHandler                        ;Reserved interrupt
        DCD     Reserved203_IRQHandler                        ;USB-1 Wake-up Interrupt
        DCD     Reserved204_IRQHandler                        ;USB-2 Wake-up Interrupt
        DCD     Reserved205_IRQHandler                        ;General Purpose Input/Output 4 interrupt 0
        DCD     Reserved206_IRQHandler                        ;General Purpose Input/Output 4 interrupt 1
        DCD     LPSPI5_IRQHandler                             ;Low Power Serial Peripheral Interface 5
        DCD     LPSPI6_IRQHandler                             ;Low Power Serial Peripheral Interface 6
        DCD     LPSPI7_IRQHandler                             ;Low Power Serial Peripheral Interface 7
        DCD     LPSPI8_IRQHandler                             ;Low Power Serial Peripheral Interface 8
        DCD     LPI2C5_IRQHandler                             ;Low Power Inter-Integrated Circuit module 5
        DCD     LPI2C6_IRQHandler                             ;Low Power Inter-Integrated Circuit module 6
        DCD     LPI2C7_IRQHandler                             ;Low Power Inter-Integrated Circuit module 7
        DCD     LPI2C8_IRQHandler                             ;Low Power Inter-Integrated Circuit module 8
        DCD     PDM_HWVAD_ERROR_IRQHandler                    ;PDM interrupt
        DCD     PDM_HWVAD_EVENT_IRQHandler                    ;PDM interrupt
        DCD     PDM_ERROR_IRQHandler                          ;PDM interrupt
        DCD     PDM_EVENT_IRQHandler                          ;PDM interrupt
        DCD     Reserved219_IRQHandler                        ;AUDIO XCVR interrupt
        DCD     Reserved220_IRQHandler                        ;AUDIO XCVR interrupt
        DCD     uSDHC3_IRQHandler                             ;ultra Secure Digital Host Controller interrupt 3
        DCD     Reserved222_IRQHandler                        ;OCRAM MECC interrupt
        DCD     Reserved223_IRQHandler                        ;OCRAM MECC interrupt
        DCD     Reserved224_IRQHandler                        ;HSIOMIX TRDC transfer error interrupt
        DCD     Reserved225_IRQHandler                        ;MEDIAMIX TRDC transfer error interrupt
        DCD     LPUART7_IRQHandler                            ;Low Power UART 7
        DCD     LPUART8_IRQHandler                            ;Low Power UART 8
        DCD     Reserved228_IRQHandler                        ;CM33 MCM interrupt
        DCD     Reserved229_IRQHandler                        ;SFA interrupt
        DCD     Reserved230_IRQHandler                        ;GIC600 INTERRUPT
        DCD     Reserved231_IRQHandler                        ;GIC600 INTERRUPT
        DCD     Reserved232_IRQHandler                        ;GIC600 INTERRUPT
        DCD     Reserved233_IRQHandler                        ;ADC interrupt
        DCD     Reserved234_IRQHandler                        ;ADC interrupt
        DCD     Reserved235_IRQHandler                        ;ADC interrupt
        DCD     Reserved236_IRQHandler                        ;Reserved interrupt
        DCD     Reserved237_IRQHandler                        ;I3C1 wakeup irq after double sync
        DCD     Reserved238_IRQHandler                        ;I3C2 wakeup irq after double sync
        DCD     Reserved239_IRQHandler                        ;Reserved interrupt
        DCD     Reserved240_IRQHandler                        ;Reserved interrupt
        DCD     Reserved241_IRQHandler                        ;Reserved interrupt
        DCD     Reserved242_IRQHandler                        ;Reserved interrupt
        DCD     Reserved243_IRQHandler                        ;Reserved interrupt
        DCD     Reserved244_IRQHandler                        ;Reserved interrupt
        DCD     Reserved245_IRQHandler                        ;Reserved interrupt
        DCD     Reserved246_IRQHandler                        ;Reserved interrupt
        DCD     Reserved247_IRQHandler                        ;Reserved interrupt
        DCD     Reserved248_IRQHandler                        ;Reserved interrupt
        DCD     Reserved249_IRQHandler                        ;Reserved interrupt
        DCD     Reserved250_IRQHandler                        ;Reserved interrupt
        DCD     Reserved251_IRQHandler                        ;Reserved interrupt
        DCD     Reserved252_IRQHandler                        ;Reserved interrupt
        DCD     Reserved253_IRQHandler                        ;Reserved interrupt
        DCD     Reserved254_IRQHandler                        ;Reserved interrupt
        DCD     Reserved255_IRQHandler                        ;Reserved interrupt
        DCD     Reserved256_IRQHandler                        ;Reserved interrupt
        DCD     Reserved257_IRQHandler                        ;Reserved interrupt
        DCD     Reserved258_IRQHandler                        ;Reserved interrupt
        DCD     Reserved259_IRQHandler                        ;Reserved interrupt
        DCD     Reserved260_IRQHandler                        ;Reserved interrupt
        DCD     Reserved261_IRQHandler                        ;Reserved interrupt
        DCD     Reserved262_IRQHandler                        ;Reserved interrupt
        DCD     Reserved263_IRQHandler                        ;Reserved interrupt
        DCD     Reserved264_IRQHandler                        ;Reserved interrupt
        DCD     Reserved265_IRQHandler                        ;Reserved interrupt
        DCD     Reserved266_IRQHandler                        ;Reserved interrupt
        DCD     Reserved267_IRQHandler                        ;Reserved interrupt
        DCD     Reserved268_IRQHandler                        ;Reserved interrupt
        DCD     Reserved269_IRQHandler                        ;Reserved interrupt
        DCD     Reserved270_IRQHandler                        ;Reserved interrupt
        DCD     Reserved271_IRQHandler                        ;Reserved interrupt
        DCD     Reserved272_IRQHandler                        ;Reserved interrupt
        DCD     Reserved273_IRQHandler                        ;Reserved interrupt
        DCD     Reserved274_IRQHandler                        ;Reserved interrupt
        DCD     Reserved275_IRQHandler                        ;Reserved interrupt
        DCD     Reserved276_IRQHandler                        ;Reserved interrupt
        DCD     Reserved277_IRQHandler                        ;Reserved interrupt
        DCD     Reserved278_IRQHandler                        ;Reserved interrupt
        DCD     Reserved279_IRQHandler                        ;Reserved interrupt
        DCD     Reserved280_IRQHandler                        ;Reserved interrupt
        DCD     Reserved281_IRQHandler                        ;Reserved interrupt
        DCD     Reserved282_IRQHandler                        ;Reserved interrupt
        DCD     Reserved283_IRQHandler                        ;Reserved interrupt
        DCD     Reserved284_IRQHandler                        ;ADC Asynchronous Interrupt
__Vectors_End

__Vectors       EQU   __vector_table
__Vectors_Size  EQU   __Vectors_End - __Vectors


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
        CPSID   I               ; Mask interrupts
        LDR     R0, =0xE000ED08
        LDR     R1, =__vector_table
        STR     R1, [R0]
        LDR     R2, [R1]
        MSR     MSP, R2
        LDR     R0, =SystemInit
        BLX     R0
;
; Add RW / stack / heap initializaiton
; TCM controller must perform a read-modify-write for any access < 32-bit to keep the ECC updated.
; The Software must ensure the TCM is ECC clean by initializing all memories that have the potential to be accessed as < 32-bit.
        MOV    R0, #0
        LDR    R1, =SFB(RW)
        LDR    R2, =SFE(RW)
.LC0:
        CMP    R1, R2
        ITT    LT
        STRLT  R0, [R1], #4
        BLT    .LC0

        MOV    R0, #0
        LDR    R1, =SFB(HEAP)
        LDR    R2, =SFE(HEAP)
.LC1:
        CMP    R1, R2
        ITT    LT
        STRLT  R0, [R1], #4
        BLT    .LC1

        LDR     R1, =SFB(CSTACK)
        LDR     R2, =SFE(CSTACK)
.LC2:
        CMP     R1, R2
        ITT     LT
        STRLT   R0, [R1], #4
        BLT     .LC2
; End RW / stack / heap initialization
;
        CPSIE   I               ; Unmask interrupts
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B .

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
        B .

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
MemManage_Handler
        B .

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BusFault_Handler
        B .

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UsageFault_Handler
        B .

        PUBWEAK SecureFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SecureFault_Handler
        B .

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B .

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
DebugMon_Handler
        B .

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B .

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B .

        PUBWEAK CAN1_IRQHandler
        PUBWEAK CAN1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN1_IRQHandler
        LDR     R0, =CAN1_DriverIRQHandler
        BX      R0

        PUBWEAK CAN1_ERROR_IRQHandler
        PUBWEAK CAN1_ERROR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN1_ERROR_IRQHandler
        LDR     R0, =CAN1_ERROR_DriverIRQHandler
        BX      R0

        PUBWEAK I3C1_IRQHandler
        PUBWEAK I3C1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
I3C1_IRQHandler
        LDR     R0, =I3C1_DriverIRQHandler
        BX      R0

        PUBWEAK LPI2C1_IRQHandler
        PUBWEAK LPI2C1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPI2C1_IRQHandler
        LDR     R0, =LPI2C1_DriverIRQHandler
        BX      R0

        PUBWEAK LPI2C2_IRQHandler
        PUBWEAK LPI2C2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPI2C2_IRQHandler
        LDR     R0, =LPI2C2_DriverIRQHandler
        BX      R0

        PUBWEAK LPSPI1_IRQHandler
        PUBWEAK LPSPI1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPSPI1_IRQHandler
        LDR     R0, =LPSPI1_DriverIRQHandler
        BX      R0

        PUBWEAK LPSPI2_IRQHandler
        PUBWEAK LPSPI2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPSPI2_IRQHandler
        LDR     R0, =LPSPI2_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART1_IRQHandler
        PUBWEAK LPUART1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART1_IRQHandler
        LDR     R0, =LPUART1_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART2_IRQHandler
        PUBWEAK LPUART2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART2_IRQHandler
        LDR     R0, =LPUART2_DriverIRQHandler
        BX      R0

        PUBWEAK SAI1_IRQHandler
        PUBWEAK SAI1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SAI1_IRQHandler
        LDR     R0, =SAI1_DriverIRQHandler
        BX      R0

        PUBWEAK CAN2_IRQHandler
        PUBWEAK CAN2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN2_IRQHandler
        LDR     R0, =CAN2_DriverIRQHandler
        BX      R0

        PUBWEAK CAN2_ERROR_IRQHandler
        PUBWEAK CAN2_ERROR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN2_ERROR_IRQHandler
        LDR     R0, =CAN2_ERROR_DriverIRQHandler
        BX      R0

        PUBWEAK FLEXIO1_IRQHandler
        PUBWEAK FLEXIO1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXIO1_IRQHandler
        LDR     R0, =FLEXIO1_DriverIRQHandler
        BX      R0

        PUBWEAK FLEXIO2_IRQHandler
        PUBWEAK FLEXIO2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLEXIO2_IRQHandler
        LDR     R0, =FLEXIO2_DriverIRQHandler
        BX      R0

        PUBWEAK FlexSPI1_IRQHandler
        PUBWEAK FlexSPI1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FlexSPI1_IRQHandler
        LDR     R0, =FlexSPI1_DriverIRQHandler
        BX      R0

        PUBWEAK I3C2_IRQHandler
        PUBWEAK I3C2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
I3C2_IRQHandler
        LDR     R0, =I3C2_DriverIRQHandler
        BX      R0

        PUBWEAK LPI2C3_IRQHandler
        PUBWEAK LPI2C3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPI2C3_IRQHandler
        LDR     R0, =LPI2C3_DriverIRQHandler
        BX      R0

        PUBWEAK LPI2C4_IRQHandler
        PUBWEAK LPI2C4_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPI2C4_IRQHandler
        LDR     R0, =LPI2C4_DriverIRQHandler
        BX      R0

        PUBWEAK LPSPI3_IRQHandler
        PUBWEAK LPSPI3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPSPI3_IRQHandler
        LDR     R0, =LPSPI3_DriverIRQHandler
        BX      R0

        PUBWEAK LPSPI4_IRQHandler
        PUBWEAK LPSPI4_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPSPI4_IRQHandler
        LDR     R0, =LPSPI4_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART3_IRQHandler
        PUBWEAK LPUART3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART3_IRQHandler
        LDR     R0, =LPUART3_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART4_IRQHandler
        PUBWEAK LPUART4_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART4_IRQHandler
        LDR     R0, =LPUART4_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART5_IRQHandler
        PUBWEAK LPUART5_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART5_IRQHandler
        LDR     R0, =LPUART5_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART6_IRQHandler
        PUBWEAK LPUART6_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART6_IRQHandler
        LDR     R0, =LPUART6_DriverIRQHandler
        BX      R0

        PUBWEAK uSDHC1_IRQHandler
        PUBWEAK uSDHC1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
uSDHC1_IRQHandler
        LDR     R0, =uSDHC1_DriverIRQHandler
        BX      R0

        PUBWEAK uSDHC2_IRQHandler
        PUBWEAK uSDHC2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
uSDHC2_IRQHandler
        LDR     R0, =uSDHC2_DriverIRQHandler
        BX      R0

        PUBWEAK DMA3_ERROR_IRQHandler
        PUBWEAK DMA3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_ERROR_IRQHandler
        MOV     R0, #1
        LDR     R1, =DMA3_DriverIRQHandler
        BX      R1

        PUBWEAK DMA3_0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_0_IRQHandler
        MOV     R0, #0
        MOV     R1, #0
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_1_IRQHandler
        MOV     R0, #0
        MOV     R1, #1
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_2_IRQHandler
        MOV     R0, #0
        MOV     R1, #2
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_3_IRQHandler
        MOV     R0, #0
        MOV     R1, #3
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_4_IRQHandler
        MOV     R0, #0
        MOV     R1, #4
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_5_IRQHandler
        MOV     R0, #0
        MOV     R1, #5
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_6_IRQHandler
        MOV     R0, #0
        MOV     R1, #6
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_7_IRQHandler
        MOV     R0, #0
        MOV     R1, #7
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_8_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_8_IRQHandler
        MOV     R0, #0
        MOV     R1, #8
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_9_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_9_IRQHandler
        MOV     R0, #0
        MOV     R1, #9
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_10_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_10_IRQHandler
        MOV     R0, #0
        MOV     R1, #10
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_11_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_11_IRQHandler
        MOV     R0, #0
        MOV     R1, #11
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_12_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_12_IRQHandler
        MOV     R0, #0
        MOV     R1, #12
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_13_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_13_IRQHandler
        MOV     R0, #0
        MOV     R1, #13
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_14_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_14_IRQHandler
        MOV     R0, #0
        MOV     R1, #14
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_15_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_15_IRQHandler
        MOV     R0, #0
        MOV     R1, #15
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_16_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_16_IRQHandler
        MOV     R0, #0
        MOV     R1, #16
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_17_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_17_IRQHandler
        MOV     R0, #0
        MOV     R1, #17
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_18_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_18_IRQHandler
        MOV     R0, #0
        MOV     R1, #18
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_19_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_19_IRQHandler
        MOV     R0, #0
        MOV     R1, #19
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_20_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_20_IRQHandler
        MOV     R0, #0
        MOV     R1, #20
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_21_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_21_IRQHandler
        MOV     R0, #0
        MOV     R1, #21
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_22_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_22_IRQHandler
        MOV     R0, #0
        MOV     R1, #22
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_23_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_23_IRQHandler
        MOV     R0, #0
        MOV     R1, #23
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_24_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_24_IRQHandler
        MOV     R0, #0
        MOV     R1, #24
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_25_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_25_IRQHandler
        MOV     R0, #0
        MOV     R1, #25
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_26_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_26_IRQHandler
        MOV     R0, #0
        MOV     R1, #26
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_27_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_27_IRQHandler
        MOV     R0, #0
        MOV     R1, #27
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_28_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_28_IRQHandler
        MOV     R0, #0
        MOV     R1, #28
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_29_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_29_IRQHandler
        MOV     R0, #0
        MOV     R1, #29
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA3_30_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA3_30_IRQHandler
        MOV     R0, #0
        MOV     R1, #30
        LDR     R2, =DMA3_DriverIRQHandler
        BX      R2

        PUBWEAK DMA4_ERROR_IRQHandler
        PUBWEAK DMA4_ERROR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_ERROR_IRQHandler
        LDR     R0, =DMA4_ERROR_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_0_1_IRQHandler
        PUBWEAK DMA4_0_1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_0_1_IRQHandler
        LDR     R0, =DMA4_0_1_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_2_3_IRQHandler
        PUBWEAK DMA4_2_3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_2_3_IRQHandler
        LDR     R0, =DMA4_2_3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_4_5_IRQHandler
        PUBWEAK DMA4_4_5_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_4_5_IRQHandler
        LDR     R0, =DMA4_4_5_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_6_7_IRQHandler
        PUBWEAK DMA4_6_7_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_6_7_IRQHandler
        LDR     R0, =DMA4_6_7_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_8_9_IRQHandler
        PUBWEAK DMA4_8_9_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_8_9_IRQHandler
        LDR     R0, =DMA4_8_9_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_10_11_IRQHandler
        PUBWEAK DMA4_10_11_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_10_11_IRQHandler
        LDR     R0, =DMA4_10_11_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_12_13_IRQHandler
        PUBWEAK DMA4_12_13_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_12_13_IRQHandler
        LDR     R0, =DMA4_12_13_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_14_15_IRQHandler
        PUBWEAK DMA4_14_15_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_14_15_IRQHandler
        LDR     R0, =DMA4_14_15_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_16_17_IRQHandler
        PUBWEAK DMA4_16_17_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_16_17_IRQHandler
        LDR     R0, =DMA4_16_17_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_18_19_IRQHandler
        PUBWEAK DMA4_18_19_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_18_19_IRQHandler
        LDR     R0, =DMA4_18_19_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_20_21_IRQHandler
        PUBWEAK DMA4_20_21_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_20_21_IRQHandler
        LDR     R0, =DMA4_20_21_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_22_23_IRQHandler
        PUBWEAK DMA4_22_23_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_22_23_IRQHandler
        LDR     R0, =DMA4_22_23_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_24_25_IRQHandler
        PUBWEAK DMA4_24_25_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_24_25_IRQHandler
        LDR     R0, =DMA4_24_25_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_26_27_IRQHandler
        PUBWEAK DMA4_26_27_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_26_27_IRQHandler
        LDR     R0, =DMA4_26_27_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_28_29_IRQHandler
        PUBWEAK DMA4_28_29_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_28_29_IRQHandler
        LDR     R0, =DMA4_28_29_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_30_31_IRQHandler
        PUBWEAK DMA4_30_31_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_30_31_IRQHandler
        LDR     R0, =DMA4_30_31_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_32_33_IRQHandler
        PUBWEAK DMA4_32_33_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_32_33_IRQHandler
        LDR     R0, =DMA4_32_33_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_34_35_IRQHandler
        PUBWEAK DMA4_34_35_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_34_35_IRQHandler
        LDR     R0, =DMA4_34_35_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_36_37_IRQHandler
        PUBWEAK DMA4_36_37_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_36_37_IRQHandler
        LDR     R0, =DMA4_36_37_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_38_39_IRQHandler
        PUBWEAK DMA4_38_39_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_38_39_IRQHandler
        LDR     R0, =DMA4_38_39_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_40_41_IRQHandler
        PUBWEAK DMA4_40_41_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_40_41_IRQHandler
        LDR     R0, =DMA4_40_41_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_42_43_IRQHandler
        PUBWEAK DMA4_42_43_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_42_43_IRQHandler
        LDR     R0, =DMA4_42_43_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_44_45_IRQHandler
        PUBWEAK DMA4_44_45_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_44_45_IRQHandler
        LDR     R0, =DMA4_44_45_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_46_47_IRQHandler
        PUBWEAK DMA4_46_47_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_46_47_IRQHandler
        LDR     R0, =DMA4_46_47_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_48_49_IRQHandler
        PUBWEAK DMA4_48_49_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_48_49_IRQHandler
        LDR     R0, =DMA4_48_49_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_50_51_IRQHandler
        PUBWEAK DMA4_50_51_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_50_51_IRQHandler
        LDR     R0, =DMA4_50_51_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_52_53_IRQHandler
        PUBWEAK DMA4_52_53_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_52_53_IRQHandler
        LDR     R0, =DMA4_52_53_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_54_55_IRQHandler
        PUBWEAK DMA4_54_55_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_54_55_IRQHandler
        LDR     R0, =DMA4_54_55_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_56_57_IRQHandler
        PUBWEAK DMA4_56_57_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_56_57_IRQHandler
        LDR     R0, =DMA4_56_57_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_58_59_IRQHandler
        PUBWEAK DMA4_58_59_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_58_59_IRQHandler
        LDR     R0, =DMA4_58_59_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_60_61_IRQHandler
        PUBWEAK DMA4_60_61_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_60_61_IRQHandler
        LDR     R0, =DMA4_60_61_DriverIRQHandler
        BX      R0

        PUBWEAK DMA4_62_63_IRQHandler
        PUBWEAK DMA4_62_63_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4_62_63_IRQHandler
        LDR     R0, =DMA4_62_63_DriverIRQHandler
        BX      R0

        PUBWEAK SAI2_IRQHandler
        PUBWEAK SAI2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SAI2_IRQHandler
        LDR     R0, =SAI2_DriverIRQHandler
        BX      R0

        PUBWEAK SAI3_IRQHandler
        PUBWEAK SAI3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SAI3_IRQHandler
        LDR     R0, =SAI3_DriverIRQHandler
        BX      R0

        PUBWEAK ENET_MAC0_Rx_Tx_Done1_IRQHandler
        PUBWEAK ENET_MAC0_Rx_Tx_Done1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ENET_MAC0_Rx_Tx_Done1_IRQHandler
        LDR     R0, =ENET_MAC0_Rx_Tx_Done1_DriverIRQHandler
        BX      R0

        PUBWEAK ENET_MAC0_Rx_Tx_Done2_IRQHandler
        PUBWEAK ENET_MAC0_Rx_Tx_Done2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ENET_MAC0_Rx_Tx_Done2_IRQHandler
        LDR     R0, =ENET_MAC0_Rx_Tx_Done2_DriverIRQHandler
        BX      R0

        PUBWEAK ENET_IRQHandler
        PUBWEAK ENET_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ENET_IRQHandler
        LDR     R0, =ENET_DriverIRQHandler
        BX      R0

        PUBWEAK ENET_1588_IRQHandler
        PUBWEAK ENET_1588_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ENET_1588_IRQHandler
        LDR     R0, =ENET_1588_DriverIRQHandler
        BX      R0

        PUBWEAK ENET_QOS_IRQHandler
        PUBWEAK ENET_QOS_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ENET_QOS_IRQHandler
        LDR     R0, =ENET_QOS_DriverIRQHandler
        BX      R0

        PUBWEAK LPSPI5_IRQHandler
        PUBWEAK LPSPI5_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPSPI5_IRQHandler
        LDR     R0, =LPSPI5_DriverIRQHandler
        BX      R0

        PUBWEAK LPSPI6_IRQHandler
        PUBWEAK LPSPI6_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPSPI6_IRQHandler
        LDR     R0, =LPSPI6_DriverIRQHandler
        BX      R0

        PUBWEAK LPSPI7_IRQHandler
        PUBWEAK LPSPI7_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPSPI7_IRQHandler
        LDR     R0, =LPSPI7_DriverIRQHandler
        BX      R0

        PUBWEAK LPSPI8_IRQHandler
        PUBWEAK LPSPI8_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPSPI8_IRQHandler
        LDR     R0, =LPSPI8_DriverIRQHandler
        BX      R0

        PUBWEAK LPI2C5_IRQHandler
        PUBWEAK LPI2C5_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPI2C5_IRQHandler
        LDR     R0, =LPI2C5_DriverIRQHandler
        BX      R0

        PUBWEAK LPI2C6_IRQHandler
        PUBWEAK LPI2C6_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPI2C6_IRQHandler
        LDR     R0, =LPI2C6_DriverIRQHandler
        BX      R0

        PUBWEAK LPI2C7_IRQHandler
        PUBWEAK LPI2C7_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPI2C7_IRQHandler
        LDR     R0, =LPI2C7_DriverIRQHandler
        BX      R0

        PUBWEAK LPI2C8_IRQHandler
        PUBWEAK LPI2C8_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPI2C8_IRQHandler
        LDR     R0, =LPI2C8_DriverIRQHandler
        BX      R0

        PUBWEAK PDM_HWVAD_ERROR_IRQHandler
        PUBWEAK PDM_HWVAD_ERROR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PDM_HWVAD_ERROR_IRQHandler
        LDR     R0, =PDM_HWVAD_ERROR_DriverIRQHandler
        BX      R0

        PUBWEAK PDM_HWVAD_EVENT_IRQHandler
        PUBWEAK PDM_HWVAD_EVENT_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PDM_HWVAD_EVENT_IRQHandler
        LDR     R0, =PDM_HWVAD_EVENT_DriverIRQHandler
        BX      R0

        PUBWEAK PDM_ERROR_IRQHandler
        PUBWEAK PDM_ERROR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PDM_ERROR_IRQHandler
        LDR     R0, =PDM_ERROR_DriverIRQHandler
        BX      R0

        PUBWEAK PDM_EVENT_IRQHandler
        PUBWEAK PDM_EVENT_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PDM_EVENT_IRQHandler
        LDR     R0, =PDM_EVENT_DriverIRQHandler
        BX      R0

        PUBWEAK uSDHC3_IRQHandler
        PUBWEAK uSDHC3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
uSDHC3_IRQHandler
        LDR     R0, =uSDHC3_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART7_IRQHandler
        PUBWEAK LPUART7_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART7_IRQHandler
        LDR     R0, =LPUART7_DriverIRQHandler
        BX      R0

        PUBWEAK LPUART8_IRQHandler
        PUBWEAK LPUART8_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
LPUART8_IRQHandler
        LDR     R0, =LPUART8_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved16_IRQHandler
        PUBWEAK Reserved17_IRQHandler
        PUBWEAK Reserved18_IRQHandler
        PUBWEAK Reserved19_IRQHandler
        PUBWEAK Reserved20_IRQHandler
        PUBWEAK Reserved21_IRQHandler
        PUBWEAK Reserved22_IRQHandler
        PUBWEAK Reserved23_IRQHandler
        PUBWEAK Reserved26_IRQHandler
        PUBWEAK Reserved27_IRQHandler
        PUBWEAK LPIT1_IRQHandler
        PUBWEAK LPTMR1_IRQHandler
        PUBWEAK MU1_A_IRQHandler
        PUBWEAK MU1_B_IRQHandler
        PUBWEAK MU2_A_IRQHandler
        PUBWEAK MU2_B_IRQHandler
        PUBWEAK Reserved41_IRQHandler
        PUBWEAK Reserved42_IRQHandler
        PUBWEAK Reserved43_IRQHandler
        PUBWEAK Reserved44_IRQHandler
        PUBWEAK Reserved45_IRQHandler
        PUBWEAK Reserved46_IRQHandler
        PUBWEAK Reserved47_IRQHandler
        PUBWEAK Reserved48_IRQHandler
        PUBWEAK Reserved49_IRQHandler
        PUBWEAK Reserved50_IRQHandler
        PUBWEAK Reserved51_IRQHandler
        PUBWEAK TPM1_IRQHandler
        PUBWEAK TPM2_IRQHandler
        PUBWEAK WDOG1_IRQHandler
        PUBWEAK WDOG2_IRQHandler
        PUBWEAK TRDC_IRQHandler
        PUBWEAK Reserved57_IRQHandler
        PUBWEAK Reserved58_IRQHandler
        PUBWEAK Reserved59_IRQHandler
        PUBWEAK Reserved60_IRQHandler
        PUBWEAK Reserved62_IRQHandler
        PUBWEAK Reserved63_IRQHandler
        PUBWEAK Reserved64_IRQHandler
        PUBWEAK Reserved65_IRQHandler
        PUBWEAK Reserved66_IRQHandler
        PUBWEAK Reserved72_IRQHandler
        PUBWEAK Reserved73_IRQHandler
        PUBWEAK Reserved74_IRQHandler
        PUBWEAK Reserved75_IRQHandler
        PUBWEAK Reserved76_IRQHandler
        PUBWEAK LPIT2_IRQHandler
        PUBWEAK LPTMR2_IRQHandler
        PUBWEAK Reserved88_IRQHandler
        PUBWEAK Reserved89_IRQHandler
        PUBWEAK Reserved90_IRQHandler
        PUBWEAK TPM3_IRQHandler
        PUBWEAK TPM4_IRQHandler
        PUBWEAK TPM5_IRQHandler
        PUBWEAK TPM6_IRQHandler
        PUBWEAK WDOG3_IRQHandler
        PUBWEAK WDOG4_IRQHandler
        PUBWEAK WDOG5_IRQHandler
        PUBWEAK Reserved98_IRQHandler
        PUBWEAK Reserved99_IRQHandler
        PUBWEAK Reserved100_IRQHandler
        PUBWEAK Reserved101_IRQHandler
        PUBWEAK Reserved104_IRQHandler
        PUBWEAK Reserved105_IRQHandler
        PUBWEAK Reserved106_IRQHandler
        PUBWEAK Reserved107_IRQHandler
        PUBWEAK Reserved108_IRQHandler
        PUBWEAK Reserved109_IRQHandler
        PUBWEAK Reserved142_IRQHandler
        PUBWEAK Reserved176_IRQHandler
        PUBWEAK Reserved177_IRQHandler
        PUBWEAK Reserved178_IRQHandler
        PUBWEAK Reserved179_IRQHandler
        PUBWEAK Reserved180_IRQHandler
        PUBWEAK Reserved181_IRQHandler
        PUBWEAK Reserved182_IRQHandler
        PUBWEAK Reserved183_IRQHandler
        PUBWEAK Reserved184_IRQHandler
        PUBWEAK Reserved185_IRQHandler
        PUBWEAK ISI_IRQHandler
        PUBWEAK Reserved189_IRQHandler
        PUBWEAK Reserved190_IRQHandler
        PUBWEAK CSI_IRQHandler
        PUBWEAK Reserved192_IRQHandler
        PUBWEAK DSI_IRQHandler
        PUBWEAK Reserved194_IRQHandler
        PUBWEAK ENET_QOS_PMT_IRQHandler
        PUBWEAK Reserved201_IRQHandler
        PUBWEAK Reserved202_IRQHandler
        PUBWEAK Reserved203_IRQHandler
        PUBWEAK Reserved204_IRQHandler
        PUBWEAK Reserved205_IRQHandler
        PUBWEAK Reserved206_IRQHandler
        PUBWEAK Reserved219_IRQHandler
        PUBWEAK Reserved220_IRQHandler
        PUBWEAK Reserved222_IRQHandler
        PUBWEAK Reserved223_IRQHandler
        PUBWEAK Reserved224_IRQHandler
        PUBWEAK Reserved225_IRQHandler
        PUBWEAK Reserved228_IRQHandler
        PUBWEAK Reserved229_IRQHandler
        PUBWEAK Reserved230_IRQHandler
        PUBWEAK Reserved231_IRQHandler
        PUBWEAK Reserved232_IRQHandler
        PUBWEAK Reserved233_IRQHandler
        PUBWEAK Reserved234_IRQHandler
        PUBWEAK Reserved235_IRQHandler
        PUBWEAK Reserved236_IRQHandler
        PUBWEAK Reserved237_IRQHandler
        PUBWEAK Reserved238_IRQHandler
        PUBWEAK Reserved239_IRQHandler
        PUBWEAK Reserved240_IRQHandler
        PUBWEAK Reserved241_IRQHandler
        PUBWEAK Reserved242_IRQHandler
        PUBWEAK Reserved243_IRQHandler
        PUBWEAK Reserved244_IRQHandler
        PUBWEAK Reserved245_IRQHandler
        PUBWEAK Reserved246_IRQHandler
        PUBWEAK Reserved247_IRQHandler
        PUBWEAK Reserved248_IRQHandler
        PUBWEAK Reserved249_IRQHandler
        PUBWEAK Reserved250_IRQHandler
        PUBWEAK Reserved251_IRQHandler
        PUBWEAK Reserved252_IRQHandler
        PUBWEAK Reserved253_IRQHandler
        PUBWEAK Reserved254_IRQHandler
        PUBWEAK Reserved255_IRQHandler
        PUBWEAK Reserved256_IRQHandler
        PUBWEAK Reserved257_IRQHandler
        PUBWEAK Reserved258_IRQHandler
        PUBWEAK Reserved259_IRQHandler
        PUBWEAK Reserved260_IRQHandler
        PUBWEAK Reserved261_IRQHandler
        PUBWEAK Reserved262_IRQHandler
        PUBWEAK Reserved263_IRQHandler
        PUBWEAK Reserved264_IRQHandler
        PUBWEAK Reserved265_IRQHandler
        PUBWEAK Reserved266_IRQHandler
        PUBWEAK Reserved267_IRQHandler
        PUBWEAK Reserved268_IRQHandler
        PUBWEAK Reserved269_IRQHandler
        PUBWEAK Reserved270_IRQHandler
        PUBWEAK Reserved271_IRQHandler
        PUBWEAK Reserved272_IRQHandler
        PUBWEAK Reserved273_IRQHandler
        PUBWEAK Reserved274_IRQHandler
        PUBWEAK Reserved275_IRQHandler
        PUBWEAK Reserved276_IRQHandler
        PUBWEAK Reserved277_IRQHandler
        PUBWEAK Reserved278_IRQHandler
        PUBWEAK Reserved279_IRQHandler
        PUBWEAK Reserved280_IRQHandler
        PUBWEAK Reserved281_IRQHandler
        PUBWEAK Reserved282_IRQHandler
        PUBWEAK Reserved283_IRQHandler
        PUBWEAK Reserved284_IRQHandler

        PUBWEAK DefaultISR
        SECTION .text:CODE:REORDER:NOROOT(1)
Reserved16_IRQHandler
Reserved17_IRQHandler
Reserved18_IRQHandler
Reserved19_IRQHandler
Reserved20_IRQHandler
Reserved21_IRQHandler
Reserved22_IRQHandler
Reserved23_IRQHandler
CAN1_DriverIRQHandler
CAN1_ERROR_DriverIRQHandler
Reserved26_IRQHandler
Reserved27_IRQHandler
I3C1_DriverIRQHandler
LPI2C1_DriverIRQHandler
LPI2C2_DriverIRQHandler
LPIT1_IRQHandler
LPSPI1_DriverIRQHandler
LPSPI2_DriverIRQHandler
LPTMR1_IRQHandler
LPUART1_DriverIRQHandler
LPUART2_DriverIRQHandler
MU1_A_IRQHandler
MU1_B_IRQHandler
MU2_A_IRQHandler
MU2_B_IRQHandler
Reserved41_IRQHandler
Reserved42_IRQHandler
Reserved43_IRQHandler
Reserved44_IRQHandler
Reserved45_IRQHandler
Reserved46_IRQHandler
Reserved47_IRQHandler
Reserved48_IRQHandler
Reserved49_IRQHandler
Reserved50_IRQHandler
Reserved51_IRQHandler
TPM1_IRQHandler
TPM2_IRQHandler
WDOG1_IRQHandler
WDOG2_IRQHandler
TRDC_IRQHandler
Reserved57_IRQHandler
Reserved58_IRQHandler
Reserved59_IRQHandler
Reserved60_IRQHandler
SAI1_DriverIRQHandler
Reserved62_IRQHandler
Reserved63_IRQHandler
Reserved64_IRQHandler
Reserved65_IRQHandler
Reserved66_IRQHandler
CAN2_DriverIRQHandler
CAN2_ERROR_DriverIRQHandler
FLEXIO1_DriverIRQHandler
FLEXIO2_DriverIRQHandler
FlexSPI1_DriverIRQHandler
Reserved72_IRQHandler
Reserved73_IRQHandler
Reserved74_IRQHandler
Reserved75_IRQHandler
Reserved76_IRQHandler
I3C2_DriverIRQHandler
LPI2C3_DriverIRQHandler
LPI2C4_DriverIRQHandler
LPIT2_IRQHandler
LPSPI3_DriverIRQHandler
LPSPI4_DriverIRQHandler
LPTMR2_IRQHandler
LPUART3_DriverIRQHandler
LPUART4_DriverIRQHandler
LPUART5_DriverIRQHandler
LPUART6_DriverIRQHandler
Reserved88_IRQHandler
Reserved89_IRQHandler
Reserved90_IRQHandler
TPM3_IRQHandler
TPM4_IRQHandler
TPM5_IRQHandler
TPM6_IRQHandler
WDOG3_IRQHandler
WDOG4_IRQHandler
WDOG5_IRQHandler
Reserved98_IRQHandler
Reserved99_IRQHandler
Reserved100_IRQHandler
Reserved101_IRQHandler
uSDHC1_DriverIRQHandler
uSDHC2_DriverIRQHandler
Reserved104_IRQHandler
Reserved105_IRQHandler
Reserved106_IRQHandler
Reserved107_IRQHandler
Reserved108_IRQHandler
Reserved109_IRQHandler
DMA3_DriverIRQHandler
Reserved142_IRQHandler
DMA4_ERROR_DriverIRQHandler
DMA4_0_1_DriverIRQHandler
DMA4_2_3_DriverIRQHandler
DMA4_4_5_DriverIRQHandler
DMA4_6_7_DriverIRQHandler
DMA4_8_9_DriverIRQHandler
DMA4_10_11_DriverIRQHandler
DMA4_12_13_DriverIRQHandler
DMA4_14_15_DriverIRQHandler
DMA4_16_17_DriverIRQHandler
DMA4_18_19_DriverIRQHandler
DMA4_20_21_DriverIRQHandler
DMA4_22_23_DriverIRQHandler
DMA4_24_25_DriverIRQHandler
DMA4_26_27_DriverIRQHandler
DMA4_28_29_DriverIRQHandler
DMA4_30_31_DriverIRQHandler
DMA4_32_33_DriverIRQHandler
DMA4_34_35_DriverIRQHandler
DMA4_36_37_DriverIRQHandler
DMA4_38_39_DriverIRQHandler
DMA4_40_41_DriverIRQHandler
DMA4_42_43_DriverIRQHandler
DMA4_44_45_DriverIRQHandler
DMA4_46_47_DriverIRQHandler
DMA4_48_49_DriverIRQHandler
DMA4_50_51_DriverIRQHandler
DMA4_52_53_DriverIRQHandler
DMA4_54_55_DriverIRQHandler
DMA4_56_57_DriverIRQHandler
DMA4_58_59_DriverIRQHandler
DMA4_60_61_DriverIRQHandler
DMA4_62_63_DriverIRQHandler
Reserved176_IRQHandler
Reserved177_IRQHandler
Reserved178_IRQHandler
Reserved179_IRQHandler
Reserved180_IRQHandler
Reserved181_IRQHandler
Reserved182_IRQHandler
Reserved183_IRQHandler
Reserved184_IRQHandler
Reserved185_IRQHandler
SAI2_DriverIRQHandler
SAI3_DriverIRQHandler
ISI_IRQHandler
Reserved189_IRQHandler
Reserved190_IRQHandler
CSI_IRQHandler
Reserved192_IRQHandler
DSI_IRQHandler
Reserved194_IRQHandler
ENET_MAC0_Rx_Tx_Done1_DriverIRQHandler
ENET_MAC0_Rx_Tx_Done2_DriverIRQHandler
ENET_DriverIRQHandler
ENET_1588_DriverIRQHandler
ENET_QOS_PMT_IRQHandler
ENET_QOS_DriverIRQHandler
Reserved201_IRQHandler
Reserved202_IRQHandler
Reserved203_IRQHandler
Reserved204_IRQHandler
Reserved205_IRQHandler
Reserved206_IRQHandler
LPSPI5_DriverIRQHandler
LPSPI6_DriverIRQHandler
LPSPI7_DriverIRQHandler
LPSPI8_DriverIRQHandler
LPI2C5_DriverIRQHandler
LPI2C6_DriverIRQHandler
LPI2C7_DriverIRQHandler
LPI2C8_DriverIRQHandler
PDM_HWVAD_ERROR_DriverIRQHandler
PDM_HWVAD_EVENT_DriverIRQHandler
PDM_ERROR_DriverIRQHandler
PDM_EVENT_DriverIRQHandler
Reserved219_IRQHandler
Reserved220_IRQHandler
uSDHC3_DriverIRQHandler
Reserved222_IRQHandler
Reserved223_IRQHandler
Reserved224_IRQHandler
Reserved225_IRQHandler
LPUART7_DriverIRQHandler
LPUART8_DriverIRQHandler
Reserved228_IRQHandler
Reserved229_IRQHandler
Reserved230_IRQHandler
Reserved231_IRQHandler
Reserved232_IRQHandler
Reserved233_IRQHandler
Reserved234_IRQHandler
Reserved235_IRQHandler
Reserved236_IRQHandler
Reserved237_IRQHandler
Reserved238_IRQHandler
Reserved239_IRQHandler
Reserved240_IRQHandler
Reserved241_IRQHandler
Reserved242_IRQHandler
Reserved243_IRQHandler
Reserved244_IRQHandler
Reserved245_IRQHandler
Reserved246_IRQHandler
Reserved247_IRQHandler
Reserved248_IRQHandler
Reserved249_IRQHandler
Reserved250_IRQHandler
Reserved251_IRQHandler
Reserved252_IRQHandler
Reserved253_IRQHandler
Reserved254_IRQHandler
Reserved255_IRQHandler
Reserved256_IRQHandler
Reserved257_IRQHandler
Reserved258_IRQHandler
Reserved259_IRQHandler
Reserved260_IRQHandler
Reserved261_IRQHandler
Reserved262_IRQHandler
Reserved263_IRQHandler
Reserved264_IRQHandler
Reserved265_IRQHandler
Reserved266_IRQHandler
Reserved267_IRQHandler
Reserved268_IRQHandler
Reserved269_IRQHandler
Reserved270_IRQHandler
Reserved271_IRQHandler
Reserved272_IRQHandler
Reserved273_IRQHandler
Reserved274_IRQHandler
Reserved275_IRQHandler
Reserved276_IRQHandler
Reserved277_IRQHandler
Reserved278_IRQHandler
Reserved279_IRQHandler
Reserved280_IRQHandler
Reserved281_IRQHandler
Reserved282_IRQHandler
Reserved283_IRQHandler
Reserved284_IRQHandler
DefaultISR
        B DefaultISR

        END
