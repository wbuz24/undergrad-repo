GCC = g++
CFLAGS = -Wall -Wextra -g

EXECUTABLES = bin/LZ77

all: $(EXECUTABLES)

bin/LZ77: src/LZ77.cpp
	$(GCC) $(CFLAGS) -o bin/LZ77 src/LZ77.cpp

clean:
	rm $(EXECUTABLES)
