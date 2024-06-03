#if __has_include(<asm/hwprobe.h>)

#include "riscv_portable.h"
#include <asm/hwprobe.h>
#include <sys/syscall.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

static __u64 portable_riscv_isa_ext_0;
static int portable_riscv_isa_ext_0_useable;

void query_isa() {
    struct riscv_hwprobe pairs[1] = {
        { RISCV_HWPROBE_KEY_IMA_EXT_0, 0}
    };
    asm volatile (
        "mv a0, %0\n"
        "mv a1, %1\n"
        "mv a2, %2\n"
        "mv a3, %3\n"
        "mv a4, %4\n"
        "li a7, %5\n"
        "ecall\n"
        :
        : "r"(pairs), "r"(1), "r"(0), "r"(NULL), "r"(0), "i"(__NR_riscv_hwprobe)
        : "a0", "a1", "a2", "a3", "a4", "a7", "memory"
    );
    /*
      We don't use syscall(...) here since the __syscall_error handler may
      not be available in the current context. Using syscall(...) might
      cause SEGSEV when compiled with -static option and running on kernel
      version < 6.4.

      We also didn't handle the return value of the syscall even if it
      fails since the value in riscv_hwprobe will not be updated if the
      syscall fails. In this case, the value will be zero, and we will not
      use any isa extension.
     */
    portable_riscv_isa_ext_0 = pairs[0].value;
    __sync_synchronize();
    portable_riscv_isa_ext_0_useable = 1;
}

int riscv_has_zbb() {
#ifdef RISCV_HWPROBE_EXT_ZBB
    if (!portable_riscv_isa_ext_0_useable) query_isa();
    return portable_riscv_isa_ext_0 & RISCV_HWPROBE_EXT_ZBB ? 1 : 0;
#else
    return 0;
#endif
}

int riscv_has_v() {
#ifdef RISCV_HWPROBE_IMA_V
    if (!portable_riscv_isa_ext_0_useable) query_isa();
    return portable_riscv_isa_ext_0 & RISCV_HWPROBE_IMA_V ? 1 : 0;
#else
    return 0;
#endif
}

int riscv_has_zvbb() {
#ifdef RISCV_HWPROBE_EXT_ZVBB
    if (!portable_riscv_isa_ext_0_useable) query_isa();
    return portable_riscv_isa_ext_0 & RISCV_HWPROBE_EXT_ZVBB ? 1 : 0;
#else
    return 0;
#endif
}

#else /* __has_include(<asm/hwprobe.h>) */

int riscv_has_zbb() {
    return 0;
}

int riscv_has_v() {
    return 0;
}

int riscv_has_zvbb() {
    return 0;
}

#endif