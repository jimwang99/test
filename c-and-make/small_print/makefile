
CC = clang
CFLAGS = -g -DTEST_DEF -I../include
LDFLAGS = -L../lib -L.

.PHONY: default clean

default:
	make clean
	make test
	./test

magic_print.o: magic_print.c

test: test.c magic_print.o

clean:
	rm -rf test
