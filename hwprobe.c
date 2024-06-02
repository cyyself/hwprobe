#include <asm/hwprobe.h>
#include <unistd.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <string.h>


long riscv_hwprobe(struct riscv_hwprobe *pairs, size_t pair_count,
                   size_t cpusetsize, unsigned long *cpus, unsigned int flags) {
    return syscall(__NR_riscv_hwprobe, pairs, pair_count, cpusetsize, cpus, flags);
}

void dump_base_behavior(long value, char *s, size_t ssize) {
    if (value & RISCV_HWPROBE_BASE_BEHAVIOR_IMA) strncat(s, "IMA_", ssize);
}

void dump_isa_ext(long value, char *s, size_t ssize) {
    if (value & RISCV_HWPROBE_IMA_FD) strncat(s, "FD_", ssize);
    if (value & RISCV_HWPROBE_IMA_C) strncat(s, "C_", ssize);
    if (value & RISCV_HWPROBE_IMA_V) strncat(s, "V_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZBA) strncat(s, "Zba_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZBB) strncat(s, "Zbb_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZBS) strncat(s, "Zbs_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZICBOZ) strncat(s, "Zicboz_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZBC) strncat(s, "Zbc_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZBKB) strncat(s, "Zbkb_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZBKC) strncat(s, "Zbkc_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZBKX) strncat(s, "Zbkx_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZKND) strncat(s, "Zknd_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZKNE) strncat(s, "Zkne_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZKNH) strncat(s, "Zknh_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZKSED) strncat(s, "Zksed_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZKSH) strncat(s, "Zksh_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZKT) strncat(s, "Zkt_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZVBB) strncat(s, "Zvbb_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZVBC) strncat(s, "Zvbc_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZVKB) strncat(s, "Zvkb_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZVKG) strncat(s, "Zvkg_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZVKNED) strncat(s, "Zvkned_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZVKNHA) strncat(s, "Zvknha_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZVKNHB) strncat(s, "Zvknhb_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZVKSED) strncat(s, "Zvksed_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZVKSH) strncat(s, "Zvksh_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZVKT) strncat(s, "Zvkt_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZFH) strncat(s, "Zfh_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZFHMIN) strncat(s, "Zfhmin_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZIHINTNTL) strncat(s, "Zihintntl_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZVFH) strncat(s, "Zvfh_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZVFHMIN) strncat(s, "Zvfhmin_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZFA) strncat(s, "Zfa_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZTSO) strncat(s, "Ztso_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZACAS) strncat(s, "Zacas_", ssize);
    if (value & RISCV_HWPROBE_EXT_ZICOND) strncat(s, "Zicond_", ssize);
}

void dump_cpu_perf_0(long value, char *s, size_t ssize) {
    long misaligned_info = value & RISCV_HWPROBE_MISALIGNED_MASK;
    switch (misaligned_info) {
        case RISCV_HWPROBE_MISALIGNED_UNKNOWN:
            strncat(s, "MISALIGNED-UNKNOWN_", ssize);
            break;
        case RISCV_HWPROBE_MISALIGNED_EMULATED:
            strncat(s, "MISALIGNED-EMULATED_", ssize);
            break;
        case RISCV_HWPROBE_MISALIGNED_SLOW:
            strncat(s, "MISALIGNED-SLOW_", ssize);
            break;
        case RISCV_HWPROBE_MISALIGNED_FAST:
            strncat(s, "MISALIGNED-FAST_", ssize);
            break;
        case RISCV_HWPROBE_MISALIGNED_UNSUPPORTED:
            strncat(s, "MISALIGNED-UNSUPPORTED_", ssize);
            break;
    }
}


int main() {
    struct riscv_hwprobe pairs[] = {
        {RISCV_HWPROBE_KEY_MVENDORID, 0},
        {RISCV_HWPROBE_KEY_MARCHID, 0},
        {RISCV_HWPROBE_KEY_MIMPID, 0},
        {RISCV_HWPROBE_KEY_BASE_BEHAVIOR, 0},
        {RISCV_HWPROBE_KEY_IMA_EXT_0, 0},
        {RISCV_HWPROBE_KEY_CPUPERF_0, 0},
        {RISCV_HWPROBE_KEY_ZICBOZ_BLOCK_SIZE, 0},
    };
    int ret = riscv_hwprobe(pairs, (sizeof pairs) / (sizeof (struct riscv_hwprobe)), 0, NULL, 0);
    if (ret == 0) {
        char tmp[16384];
        printf("MVENDORID: %llx\n", pairs[0].value);
        printf("MARCHID: %llx\n", pairs[1].value);
        printf("MIMPID: %llx\n", pairs[2].value);
        tmp[0] = 0;
        dump_base_behavior(pairs[3].value, tmp, sizeof tmp);
        printf("BASE_BEHAVIOR: %s\n", tmp);
        tmp[0] = 0;
        dump_isa_ext(pairs[4].value, tmp, sizeof tmp);
        printf("IMA_EXT_0: %s\n", tmp);
        tmp[0] = 0;
        dump_cpu_perf_0(pairs[5].value, tmp, sizeof tmp);
        printf("CPUPERF_0: %s\n", tmp);
        printf("ZICBOZ_BLOCK_SIZE: %lld Bytes\n", pairs[6].value);
    }
    else {
        fprintf(stderr, "riscv_hwprobe failed: %d\n", ret);
    }
    return 0;
}