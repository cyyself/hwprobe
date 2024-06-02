# RISC-V hwprobe Example

This example demonstrates how to use the hwprobe syscall to probe hardware features of the RISC-V processor in Linux.

## How to use?

1. Compile the example program:

```bash
gcc -o hwprobe hwprobe.c
```

If it failed due to missing `.h` or some extension is not in the header files, you should use the builtin `hwprobe.h` as a workaround:

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

## Creating portable binary with hwprobe + ifunc

We provided an example of creating a portable binary that uses rv64gc as the binary base and uses function attribute `arch=+zbb` to enable the Zbb extension for some specific function in the `./ifunc_exmaple`. The `ifunc` is used to select the correct function and store it in the GOT table so there is no runtime overhead except for inline support. We will use hwprobe syscall to query if the `zbb` extension is supported during `ifunc` resolve function.

There is no lto support in the mainline GCC, if you enable `-flto` in CFLAG you will see the following error:

```console
➜  ifunc_example git:(master) ✗ make CROSS_COMPILE=riscv64-unknown-linux-gnu- CFLAGS='-static -O3 -march=rv64gc -flto'
riscv64-unknown-linux-gnu-gcc -static -O3 -march=rv64gc -flto -c -o ror32.o ror32.c
riscv64-unknown-linux-gnu-gcc -static -O3 -march=rv64gc -flto -c -o riscv_portable.o riscv_portable.c
riscv64-unknown-linux-gnu-gcc -static -O3 -march=rv64gc -flto -c -o ror32_main.o ror32_main.c
riscv64-unknown-linux-gnu-gcc -static -O3 -march=rv64gc -flto -o ror32_main ror32.o riscv_portable.o ror32_main.o
/tmp/ccsIGdZF.s: Assembler messages:
/tmp/ccsIGdZF.s:14: Error: unrecognized opcode `rorw a0,a0,a1', extension `zbb' or `zbkb' required
lto-wrapper: fatal error: riscv64-unknown-linux-gnu-gcc returned 1 exit status
compilation terminated.
/opt/riscv/lib/gcc/riscv64-unknown-linux-gnu/15.0.0/../../../../riscv64-unknown-linux-gnu/bin/ld: error: lto-wrapper failed
collect2: error: ld returned 1 exit status
make: *** [Makefile:7: ror32_main] Error 1
```

Maybe it should be fixed in the future.

Reference:
- [RISC-V Function Attributes (Using GCC)](https://gcc.gnu.org/onlinedocs/gcc/RISC-V-Function-Attributes.html)
- [Common Function Attributes (Using GCC)](https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html)
