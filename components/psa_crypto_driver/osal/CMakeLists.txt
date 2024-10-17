 #
 # Copyright 2023 NXP
 #
 # SPDX-License-Identifier: BSD-3-Clause
 #

target_include_directories(
    McuxPsaCryptoDriverElsPkc 
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/.
        #baremetal
        #frtos
        zephyr/.
)

target_sources(
    McuxPsaCryptoDriverElsPkc 
    PRIVATE
        #baremetal/osal_mutex.c
        #frtos/osal_mutex.c
        zephyr/osal_mutex.c
)
