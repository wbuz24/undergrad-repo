GCC = g++
CFLAGS = -Wall -Wextra
# LIBDIR = /home/jplank/cs360/lib
# LIBS = $(LIBDIR)/libfdr.a 

EXECUTABLES = bin/boardfolding bin/AliceGame

all: $(EXECUTABLES)

bin/boardfolding: src/Board-Folding.cpp
	$(GCC) $(CFLAGS) -o bin/boardfolding src/Board-Folding.cpp

bin/AliceGame: src/Alice.cpp
	$(GCC) $(CFLAGS) -o bin/AliceGame src/Alice.cpp

clean:
	rm $(EXECUTABLES)
