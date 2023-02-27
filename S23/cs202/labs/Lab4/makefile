CFLAGS ?= -std=c++98 -Wall -Wextra -Iinclude

# -------------------------
# This means that when you just type "make", you make all of the executables

ALL = bin/read_as_hex bin/hash_tester

all: $(ALL)

# -------------------------
# "make clean" deletes the object files and binaries

clean:
	rm -f obj/* bin/*

# -------------------------
# Object files

obj/hash_202.o: src/hash_202.cpp include/hash_202.hpp
	g++ $(CFLAGS) -g -c -o obj/hash_202.o src/hash_202.cpp

obj/hash_tester.o: src/hash_tester.cpp include/hash_202.hpp
	g++ $(CFLAGS) -g -c -o obj/hash_tester.o src/hash_tester.cpp

# -------------------------
# Executables

bin/hash_tester: obj/hash_tester.o obj/hash_202.o
	g++ $(CFLAGS) -o bin/hash_tester obj/hash_tester.o obj/hash_202.o

bin/read_as_hex: src/read_as_hex.cpp
	g++ $(CFLAGS) -o bin/read_as_hex src/read_as_hex.cpp

