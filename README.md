# RISC-V hwprobe Example

This example demonstrates how to use the hwprobe syscall to probe hardware features of the RISC-V processor in Linux.

## How to use?

1. Compile the example program:

```bash
gcc -o hwprobe hwprobe.c
```

If it failed due to missing `.h` or some extension is not in the header files, you should use the builtin `hwprobe.`h` as a workaround:

```bash
gcc -o hwprobe hwprobe.c -I./include
```

2. Run the program:

```console
$ ./hwprobe
MVENDORID: 0
MARCHID: 0
MIMPID: 0
BASE_BEHAVIOR: IMA_
IMA_EXT_0: FD_C_V_Zba_Zbb_Zbs_
CPUPERF_0: MISALIGNED-FAST_
ZICBOZ_BLOCK_SIZE: 64 Bytes
```
