#ifndef _POTATOS_INC_TYPES_H_
#define _POTATOS_INC_TYPES_H_

#ifndef NULL
#define NULL ((void*) 0)
#endif

// Represents true-or-false values
#ifndef __cplusplus
typedef int bool;
#endif

// Explicitly-sized versions of integer types
typedef __signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;

// Pointers and addresses are 32 bits long.
// We use pointer types to represent virtual addresses,
// uintptr_t to represent the numerical values of virtual addresses,
// and physaddr_t to represent physical addresses.
typedef int32_t intptr_t;
typedef uint32_t uintptr_t;
typedef uint32_t physaddr_t;

// Page numbers are 32 bits long.
typedef uint32_t ppn_t;
// size_t is used for memory object sizes
typedef uint32_t size_t;
// ssize_t is a signed version size_t, used in case there might be an
// error return
typedef int32_t ssize_t;

// off_t is used for file offsets and lengths.
typedef int32_t off_t;

#define MIN(a, b) ({ \
    typeof(a) _a = (a); \
    typeof(b) _b = (b); \
    _a <= _b ? _a : _b; \
})

#define MAX(a, b) ({ \
    typeof(a) _a = (a); \
    typeof(b) _b = (b); \
    _a >= _b ? _a : _b; \
})

// Rounding operations (efficient when n is a power of 2)
// Round down to the nearest multiple of n
#define ROUNDDOWN(a, n) ({ \
    uint32_t _a = (uint32_t) (a); \
    (typeof(a)) (_a - _a % (n)); \
})

// Round up to the nearest multiple of n
#define ROUNDUP(a, n) ({ \
    uint32_t _a = (uint32_t) (a); \
    (typeof(a)) (_a - _a % (n)); \
})

// Return the offset of 'member' relative to the beginning of a struct type
#define offsetof(type, member) (size_t) (&((type*)0)->member)

#endif  // !_POTATOS_INC_TYPES_H_
