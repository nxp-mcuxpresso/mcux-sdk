/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __FSL_RAM_CONSOLE_H__
#define __FSL_RAM_CONSOLE_H__

#define RAM_CONSOLE_HEAD_STR "RAM_CONSOLE"

#define RAM_CONSOLE_HEAD_SIZE 64

struct ram_console_header {
    char flag_string[12];
    char *ram_console_buf_addr;
    size_t ram_console_buf_size;
    uint32_t pos;
};

#endif /* __FSL_RAM_CONSOLE_H__ */
