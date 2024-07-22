
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
