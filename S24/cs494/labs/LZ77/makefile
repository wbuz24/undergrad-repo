C = gcc
GCC = g++
CFLAGS = -Wall -Wextra -g

EXECUTABLES = bin/LZ77 bin/bytes_gen

all: $(EXECUTABLES)

bin/LZ77: src/LZ77.c
	$(C) $(CFLAGS) -o bin/LZ77 src/LZ77.c

bin/bytes_gen: scripts/bytes_gen.cpp
	$(GCC) $(CFLAGS) -o bin/bytes_gen scripts/bytes_gen.cpp

clean:
	rm $(EXECUTABLES)
