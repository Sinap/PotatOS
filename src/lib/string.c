#include <inc/string.h>

// Using assembly for memset/memmove
// makes some difference on real hardware,
// but it makes an even bigger difference on bochs.
// Primespipe runs 3x faster this way.
#define ASM 1

int strlen(const char *s) {
    int n;
    for (n = 0; *s != '\0'; ++s) {
        ++n;
    }
    return n;
}

int strnlen(const char *s, size_t size) {
    int n;
    for (n = 0; size > 0 && *s != '\0'; ++s, --size) {
        ++n;
    }
    return n;
}

char *strcpy(char *dst, const char *src) {
    char *ret;
    ret = dst;
    while ((*dst++ = *src++) != '\0') {
        // do nothing
    }
    return ret;
}
