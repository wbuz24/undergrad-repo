C = gcc
GCC = g++
CFLAGS = -Wall -Wextra -g

EXECUTABLES = bin/LZ77 bin/shrek_gen

all: $(EXECUTABLES)

bin/LZ77: src/LZ77.c
	$(C) $(CFLAGS) -o bin/LZ77 src/LZ77.c

bin/shrek_gen: scripts/shrek_gen.cpp
	$(GCC) $(CFLAGS) -o bin/shrek_gen scripts/shrek_gen.cpp

clean:
	rm $(EXECUTABLES)
