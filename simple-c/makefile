
ELF = main.elf

CC = clang
CFLAGS =
LDFLAGS =

default: $(ELF)
	./$(ELF)

$(ELF): $(wildcard *.c)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

clean:
	-rm -rf $(ELF) *.o
