#pragma once

#ifdef id8
#define BIG_INT_WORD uint16_t
#define BIG_INT_HALF uint8_t
#define BIG_INT_HALF_PRI ":%03" PRIu8
#define BIG_INT_OVERFLOW_PRI "  OF"
#define BIG_INT_HALF_LEN (8)
#define BIG_INT_SIZE 1
#endif

#ifdef ix8
#define BIG_INT_WORD uint16_t
#define BIG_INT_HALF uint8_t
#define BIG_INT_HALF_PRI ":%02" PRIx8
#define BIG_INT_OVERFLOW_PRI " OF"
#define BIG_INT_HALF_LEN (8)
#define BIG_INT_SIZE 1
#endif

#ifdef id16
#define BIG_INT_WORD uint32_t
#define BIG_INT_HALF uint16_t
#define BIG_INT_HALF_PRI ":%06" PRIu16
#define BIG_INT_OVERFLOW_PRI "     OF"
#define BIG_INT_HALF_LEN (16)
#define BIG_INT_SIZE 1
#endif

#ifdef ix16
#define BIG_INT_WORD uint32_t
#define BIG_INT_HALF uint16_t
#define BIG_INT_HALF_PRI ":%04" PRIx16
#define BIG_INT_OVERFLOW_PRI "   OF"
#define BIG_INT_HALF_LEN (16)
#define BIG_INT_SIZE 1
#endif

#ifdef id32
#define BIG_INT_WORD uint64_t
#define BIG_INT_HALF uint32_t
#define BIG_INT_HALF_PRI ":%010" PRIu32
#define BIG_INT_OVERFLOW_PRI "   OVERFLOW"
#define BIG_INT_HALF_LEN (32)
#define BIG_INT_SIZE 1
#endif

#ifdef ix32
#define BIG_INT_WORD uint64_t
#define BIG_INT_HALF uint32_t
#define BIG_INT_HALF_PRI ":%08" PRIx32
#define BIG_INT_OVERFLOW_PRI " OVERFLOW"
#define BIG_INT_HALF_LEN (32)
#define BIG_INT_SIZE 1
#endif

#ifdef id64
#define BIG_INT_WORD unsigned __int128 
#define BIG_INT_HALF uint64_t
#define BIG_INT_HALF_PRI ":%020" PRIu64
#define BIG_INT_OVERFLOW_PRI "             OVERFLOW"
#define BIG_INT_HALF_LEN (64)
#define BIG_INT_SIZE 1
#endif

#ifdef ix64
#define BIG_INT_WORD unsigned __int128 
#define BIG_INT_HALF uint64_t
#define BIG_INT_HALF_PRI ":%016" PRIx64
#define BIG_INT_OVERFLOW_PRI "         OVERFLOW"
#define BIG_INT_HALF_LEN (64)
#define BIG_INT_SIZE 1
#endif

#ifdef ix128
#define BIG_INT_WORD unsigned __int128 
#define BIG_INT_HALF uint64_t
#define BIG_INT_HALF_PRI ":%016" PRIx64
#define BIG_INT_OVERFLOW_PRI "                          OVERFLOW"
#define BIG_INT_HALF_LEN (64)
#define BIG_INT_SIZE 2
#endif

#ifdef ix256
#define BIG_INT_WORD unsigned __int128 
#define BIG_INT_HALF uint64_t
#define BIG_INT_HALF_PRI ":%016" PRIx64
#define BIG_INT_OVERFLOW_PRI "                                                            OVERFLOW"
#define BIG_INT_HALF_LEN (64)
#define BIG_INT_SIZE 4
#endif

#ifdef ix512
#define BIG_INT_WORD unsigned __int128 
#define BIG_INT_HALF uint64_t
#define BIG_INT_HALF_PRI ":%016" PRIx64
#define BIG_INT_OVERFLOW_PRI "                                                                                                                                OVERFLOW"
#define BIG_INT_HALF_LEN (64)
#define BIG_INT_SIZE 8
#endif