
ELF = main.elf

MUTEXT_FPATH = .mutex.lock

CC = clang
CFLAGS =
LDFLAGS =

default: $(ELF)
	./main.elf "worker-1" $(MUTEXT_FPATH) &
	./main.elf "worker-2" $(MUTEXT_FPATH)

$(ELF): $(wildcard *.c)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

clean:
	-rm -rf $(ELF) *.o $(MUTEXT_FPATH)
