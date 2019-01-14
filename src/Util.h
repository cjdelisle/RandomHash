#ifndef BITS_H
#define BITS_H

#include <stdint.h>
#include <assert.h>
#include <stdio.h>

// floor(log2(x))
static inline int Util_log2floor(uint64_t x) {
    assert(x);
    return 63 - _Generic(x,
        unsigned long long: __builtin_clzll(x),
        unsigned long: __builtin_clzl(x)
    );
}
// ceiling(log2(x))
static inline int Util_log2ceil(uint64_t x) {
	return ((x & (x - 1)) != 0) + Util_log2floor(x);
}

static inline uint64_t Util_reverse64(uint64_t x)
{
    #define RM(in, mask, rb) ((((in) >> (rb)) & (mask)) | (((in) & (mask)) << (rb)))
    x = RM(x, 0x5555555555555555ull, 1);
    x = RM(x, 0x3333333333333333ull, 2);
    x = RM(x, 0x0F0F0F0F0F0F0F0Full, 4);
    return __builtin_bswap64(x);
    #undef RM
}

//#define DEBUG
#ifdef DEBUG
#define Util_INVAL_IF(expr) assert(!(expr))
#define Util_BUG_IF(expr) assert(!(expr))
#else
#define Util_INVAL_IF(expr) do { if (expr) { return -1; } } while (0)
#define Util_BUG_IF(expr) do { \
    if (!(expr)) { break; } \
    fprintf(stderr, "BUG %s:%d (%s)\n", __FILE__, __LINE__, #expr); \
    return -2; \
} while (0)
#endif


#endif
