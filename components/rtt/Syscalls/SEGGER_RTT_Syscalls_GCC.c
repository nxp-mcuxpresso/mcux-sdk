/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*            (c) 1995 - 2021 SEGGER Microcontroller GmbH             *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************
*                                                                    *
*       SEGGER RTT * Real Time Transfer for embedded targets         *
*                                                                    *
**********************************************************************
*                                                                    *
* All rights reserved.                                               *
*                                                                    *
* SEGGER strongly recommends to not make any changes                 *
* to or modify the source code of this software in order to stay     *
* compatible with the RTT protocol and J-Link.                       *
*                                                                    *
* Redistribution and use in source and binary forms, with or         *
* without modification, are permitted provided that the following    *
* condition is met:                                                  *
*                                                                    *
* o Redistributions of source code must retain the above copyright   *
*   notice, this condition and the following disclaimer.             *
*                                                                    *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             *
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        *
* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           *
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
* DISCLAIMED. IN NO EVENT SHALL SEGGER Microcontroller BE LIABLE FOR *
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR           *
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT  *
* OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;    *
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF      *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT          *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE  *
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH   *
* DAMAGE.                                                            *
*                                                                    *
**********************************************************************
*                                                                    *
*       RTT version: 7.22                                           *
*                                                                    *
**********************************************************************

---------------------------END-OF-HEADER------------------------------
File    : SEGGER_RTT_Syscalls_GCC.c
Purpose : Low-level functions for using printf() via RTT in GCC.
          To use RTT for printf output, include this file in your 
          application.
Revision: $Rev: 20755 $
----------------------------------------------------------------------
*/

/*
 * This is to be compatible with other MSDK debug_console.
 *
 * When SDK_DEBUGCONSOLE_UART is defined, the toolchain IO functions like
 * printf, scanf are redirected to RTT.
 */
#if defined(SDK_DEBUGCONSOLE_UART)
#if (defined __GNUC__) && !(defined __SES_ARM) && !(defined __CROSSWORKS_ARM) && !(defined __ARMCC_VERSION) && !(defined __CC_ARM)

#include <reent.h>  // required for _write_r
#include "SEGGER_RTT.h"


/*********************************************************************
*
*       Types
*
**********************************************************************
*/
//
// If necessary define the _reent struct
// to match the one passed by the used standard library.
//
struct _reent;

/*********************************************************************
*
*       Function prototypes
*
**********************************************************************
*/
_ssize_t _write  (int file, const void *ptr, size_t len);
_ssize_t _write_r(struct _reent *r, int file, const void *ptr, size_t len);

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/

/*********************************************************************
*
*       _write()
*
* Function description
*   Low-level write function.
*   libc subroutines will use this system routine for output to all files,
*   including stdout.
*   Write data via RTT.
*/
_ssize_t _write(int file, const void *ptr, size_t len) {
  (void) file;  /* Not used, avoid warning */
  SEGGER_RTT_Write(0, ptr, len);
  return len;
}

/*********************************************************************
*
*       _write_r()
*
* Function description
*   Low-level reentrant write function.
*   libc subroutines will use this system routine for output to all files,
*   including stdout.
*   Write data via RTT.
*/
_ssize_t _write_r(struct _reent *r, int file, const void *ptr, size_t len) {
  (void) file;  /* Not used, avoid warning */
  (void) r;     /* Not used, avoid warning */
  SEGGER_RTT_Write(0, ptr, len);
  return len;
}

/*********************************************************************
*
*       _read()
*
* Function description
*   Low-level read function.
*   Standard library subroutines will use this system routine
*   for reading data via RTT.
*/
_ssize_t _read(int handle, char *buffer, int size)
{
    (void) handle;  /* Not used, avoid warning */

    for (int i = 0; i < bufSize; i++)
    {
        *buf = SEGGER_RTT_WaitKey() ;
        buf++;
    }

    return bufSize;
}

/*********************************************************************
*
*       __sys_write()
*
* Function description
*   Low-level write function used by REDLIB.
*/
int __sys_write(int handle, char *buffer, int size)
{
    if (NULL == buffer)
    {
        /* return -1 if error. */
        return -1;
    }

    /* This function only writes to "standard out" and "standard err" for all other file handles it returns failure. */
    if ((handle != 1) && (handle != 2))
    {
        return -1;
    }

    /* Send data. */
    SEGGER_RTT_Write(0, (const char*)buffer, size);

    return 0;
}

/*********************************************************************
*
*       _read()
*
* Function description
*   Low-level read function, used by REDLIB.
*   Standard library subroutines will use this system routine
*   for reading data via RTT.
*/
int __sys_readc(void)
{
    return SEGGER_RTT_WaitKey() ;
}

#endif

#endif /* SDK_DEBUGCONSOLE_UART */
/****** End Of File *************************************************/
