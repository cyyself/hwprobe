CFLAGS := -static -O3 -march=rv64gc
CROSS_COMPILE :=
CC := $(CROSS_COMPILE)gcc
OBJ := ror32.o riscv_portable.o ror32_main.o

ror32_main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

ror32_main.s: ror32_main
	$(CROSS_COMPILE)objdump -d $< > $@

%.s: %.o
	$(CROSS_COMPILE)objdump -d $< > $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
