/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/*==================================================================================================
Include Files
==================================================================================================*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*==================================================================================================
Public macros
==================================================================================================*/
#define TRUE                        (1)
#define FALSE                       (0)

#define PACKED_STRUCT               struct __attribute__ ((__packed__))
#define PACKED_UNION                union __attribute__ ((__packed__))

#define MEM_BufferAlloc(size)       malloc(size)
#define MEM_BufferFree(ptr)         free(ptr)
#define FLib_MemCpy(dest, src, n)   memcpy(dest, src, n)
#define FLib_MemSet(s, c, n)        memset(s, c, n)

#define FSCI_LENGTH_FIELD_SIZE      2

#define SHELL_NEWLINE()             printf("\n")
#define shell_refresh()             SHELL_NEWLINE()
#define shell_write(str)            printf("%s", str)
#define shell_printf                printf

/* Bit shift definitions */
#define BIT0              0x01
#define BIT1              0x02
#define BIT2              0x04
#define BIT3              0x08
#define BIT4              0x10
#define BIT5              0x20
#define BIT6              0x40
#define BIT7              0x80
#define BIT8             0x100
#define BIT9             0x200
#define BIT10            0x400
#define BIT11            0x800
#define BIT12           0x1000
#define BIT13           0x2000
#define BIT14           0x4000
#define BIT15           0x8000
#define BIT16          0x10000
#define BIT17          0x20000
#define BIT18          0x40000
#define BIT19          0x80000
#define BIT20         0x100000
#define BIT21         0x200000
#define BIT22         0x400000
#define BIT23         0x800000
#define BIT24        0x1000000
#define BIT25        0x2000000
#define BIT26        0x4000000
#define BIT27        0x8000000
#define BIT28       0x10000000
#define BIT29       0x20000000
#define BIT30       0x40000000
#define BIT31       0x80000000

/*==================================================================================================
Public type definitions
==================================================================================================*/
typedef uint8_t                     bool_t;

typedef enum {
    MEM_SUCCESS_c = 0,              /* No error occurred */
    MEM_INIT_ERROR_c,               /* Memory initialization error */
    MEM_ALLOC_ERROR_c,              /* Memory allocation error */
    MEM_FREE_ERROR_c,               /* Memory free error */
    MEM_UNKNOWN_ERROR_c             /* something bad has happened... */
} memStatus_t;

typedef struct {
    uint8_t startMarker;
    uint8_t opGroup;
    uint8_t opCode;
#if (FSCI_LENGTH_FIELD_SIZE == 2)
    uint16_t length;
#else
    uint8_t length;
#endif
    uint8_t *data;
} fsciPacket_t;

/*==================================================================================================
Public prototypes
==================================================================================================*/
void FSCI_transmitPayload(void *arg,            /* Optional argument passed to the function */
                          uint8_t og,           /* FSCI operation group */
                          uint8_t oc,           /* FSCI operation code */
                          void *msg,            /* Pointer to payload */
                          uint16_t msgLen,      /* Payload length */
                          uint8_t fsciInterface /* FSCI interface ID */
                         );
