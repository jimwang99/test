
ELF = main.elf

CC = clang
CFLAGS =
LDFLAGS =

default: $(ELF)
	touch exchange.txt
	touch exchange.txt.lock
	sleep 0.2

producer: $(ELF)
	./main.elf "producer" "./exchange.txt" "./exchange.txt.lock"

consumer: $(ELF)
	./main.elf "consumer" "./exchange.txt" "./exchange.txt.lock"

$(ELF): $(wildcard *.c)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

clean:
	-rm -rf $(ELF) *.o
