EXECUTABLES = bin/checkerboard bin/moonglow

CFLAGS ?= -Wall -Wextra -std=c++11

all: $(EXECUTABLES)

clean:
	rm -f a.out bin/*

bin/checkerboard: src/checkerboard.cpp
	g++ $(CFLAGS) -o bin/checkerboard src/checkerboard.cpp

bin/moonglow: src/moonglow.cpp
	g++ $(CFLAGS) -o bin/moonglow src/moonglow.cpp
