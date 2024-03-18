C = gcc
GCC = g++
CFLAGS = -Wall -Wextra -g

EXECUTABLES = bin/LZ77 bin/bytes

all: $(EXECUTABLES)

bin/LZ77: src/LZ77.c
	$(C) $(CFLAGS) -o bin/LZ77 src/LZ77.c

bin/bytes: scripts/bytes.c
	$(C) $(CFLAGS) -o bin/bytes scripts/bytes.c

clean:
	rm $(EXECUTABLES)
