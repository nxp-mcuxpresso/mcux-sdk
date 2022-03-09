#if defined(__CC_ARM) || defined(__ARMCC_VERSION) || defined(__GNUC__) || defined(__MCUXPRESSO) // ARMGCC and MCUXPRESSO
__attribute__((section(".mflash_fs"), used))

#elif defined(__ICCARM__) // IAR

#pragma location = ".mflash_fs"
#endif

#if defined(__arm) // MDK
#define MFLASH_SECTION_ATTR __attribute__((section(".mflash_fs")))

#else

#define MFLASH_SECTION_ATTR
#endif

const char blank_fs[32] MFLASH_SECTION_ATTR = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                               0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                               0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
