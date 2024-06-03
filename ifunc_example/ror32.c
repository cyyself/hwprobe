#include "riscv_portable.h"
#include "ror32.h"
#include <limits.h>

__attribute__((target("arch=+zbb"))) size_t ror32_zbb(unsigned int *a, unsigned int b, size_t size) {
    for (size_t i = 0; i < size; i++) {
        a[i] = a[i] >> b | (a[i] << (32 - b));
    }
    return size;
}

size_t ror32_normal(unsigned int *a, unsigned int b, size_t size) {
    for (size_t i = 0; i < size; i++) {
        a[i] = a[i] >> b | (a[i] << (32 - b));
    }
    return size;
}

static size_t (*resolve_ror32(unsigned int a, unsigned int b, size_t size))() {
    if (riscv_has_zbb()) return ror32_zbb;
    else return ror32_normal;
}

__attribute__ ((ifunc ("resolve_ror32"))) size_t ror32(unsigned int *a, unsigned int b, size_t size);
