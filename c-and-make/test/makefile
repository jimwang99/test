
CC = clang
CFLAGS = -g -DTEST_DEF -I../include
LDFLAGS = -L../lib

# CC = riscv64-unknown-elf-gcc
# CFLAGS = -DTEST_DEF -I../include --specs=nano.specs
# CFLAGS = -DTEST_DEF -I../include --specs=nano.specs -Os -flto -ffunction-sections -fdata-sections -Wl,--gc-sections -fno-builtin
# CFLAGS = -DTEST_DEF -I../include --specs=nano.specs  -flto -ffunction-sections -fdata-sections -Wl,--gc-sections -fno-builtin
# LDFLAGS = -L../lib -Wl,--start-group -lc -lgcc -lm -Wl,--end-group

ifeq ($(CC),clang)
default: test
	./test
else
default: test
endif

../lib/lib.o: ../lib/lib.c

test: test.c ../lib/lib.o

small_print: small_print.c

clean:
	rm -rf test log ../lib/lib.o
