CFLAGS ?= -std=c++98 -Wall -Wextra -Iinclude

# -------------------------
# This means that when you just type "make", you make all of the executables

ALL = bin/pgm_tester

all: $(ALL)

# -------------------------
# "make clean" deletes the object files and binaries

clean:
	rm -f obj/* bin/*

# -------------------------
# Object files

obj/pgm.o: src/pgm.cpp include/pgm.hpp
	g++ $(CFLAGS) -c -o obj/pgm.o src/pgm.cpp

obj/pgm_tester.o: src/pgm_tester.cpp include/pgm.hpp
	g++ $(CFLAGS) -c -o obj/pgm_tester.o src/pgm_tester.cpp

# -------------------------
# Executables

bin/pgm_tester: obj/pgm_tester.o obj/pgm.o
	g++ $(CFLAGS) -o bin/pgm_tester obj/pgm_tester.o obj/pgm.o

