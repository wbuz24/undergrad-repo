CFLAGS ?= -std=c++11 -Wall -Wextra -Iinclude

# -------------------------
# This means that when you just type "make", you make all of the executables

ALL = bin/fraction_tester \
      bin/keno

all: $(ALL)

# -------------------------
# "make clean" deletes the object files and binaries

clean:
	rm -f obj/* bin/*

# -------------------------
# Object files

obj/fraction.o: src/fraction.cpp include/fraction.hpp
	g++ $(CFLAGS) -c -o obj/fraction.o src/fraction.cpp

obj/fraction_tester.o: src/fraction_tester.cpp include/fraction.hpp
	g++ $(CFLAGS) -c -o obj/fraction_tester.o src/fraction_tester.cpp

obj/keno.o: src/keno.cpp include/fraction.hpp
	g++ $(CFLAGS) -c -o obj/keno.o src/keno.cpp

# -------------------------
# Executables

bin/fraction_tester: obj/fraction_tester.o obj/fraction.o
	g++ $(CFLAGS) -o bin/fraction_tester obj/fraction_tester.o obj/fraction.o

bin/keno: obj/keno.o obj/fraction.o
	g++ $(CFLAGS) -o bin/keno obj/keno.o obj/fraction.o

