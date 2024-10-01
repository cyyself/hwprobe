#include "riscv_portable.h"
#include "ror32.h"
#include <limits.h>
#include <stdint.h>

__attribute__((target("arch=+zbb,+v,+zvbb")))
size_t ror32_zbb_zvbb(unsigned int *a, unsigned int b, size_t size) {
    for (size_t i = 0; i < size; i++) {
        a[i] = a[i] >> b | (a[i] << (32 - b));
    }
    return size;
}

__attribute__((target("arch=+zbb,+v")))
size_t ror32_zbb_v(unsigned int *a, unsigned int b, size_t size) {
    for (size_t i = 0; i < size; i++) {
        a[i] = a[i] >> b | (a[i] << (32 - b));
    }
    return size;
}

__attribute__((target("arch=+zbb")))
size_t ror32_zbb(unsigned int *a, unsigned int b, size_t size) {
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

static __typeof(ror32_normal)*
resolve_ror32(uint64_t dl_hwcap, void* hwprobe_func) {
    if (riscv_has_zvbb() && riscv_has_zbb()) return ror32_zbb_zvbb;
    else if (riscv_has_zbb() && riscv_has_v()) return ror32_zbb_v;
    else if (riscv_has_zbb()) return ror32_zbb;
    else return ror32_normal;
}

__attribute__ ((ifunc ("resolve_ror32")))
size_t ror32(unsigned int *a, unsigned int b, size_t size);
