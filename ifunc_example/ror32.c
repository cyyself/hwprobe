#include "riscv_portable.h"
#include <limits.h>

__attribute__((target("arch=+zbb"))) unsigned int ror32_zbb(unsigned int a, unsigned int b) {
    return a >> b | (a << (32 - b));
}

unsigned int ror32_normal(unsigned int a, unsigned int b) {
    return a >> b | (a << (32 - b));
}

static unsigned int (*resolve_ror32(unsigned int a, unsigned int b))() {
    if (riscv_has_zbb()) return ror32_zbb;
    else return ror32_normal;
}

__attribute__ ((ifunc ("resolve_ror32"))) unsigned int ror32(unsigned int a, unsigned int b);
