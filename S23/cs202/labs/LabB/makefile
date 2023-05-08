CFLAGS ?= -std=c++11 -Wall -Wextra -Iinclude

# -------------------------
# This means that when you just type "make", you make all of the executables

ALL = bin/avltree_tester \

all: $(ALL)

# -------------------------
# "make clean" deletes the object files and binaries

clean:
	rm -f obj/* bin/*

# -------------------------
# Object files

obj/avltree_fixed.o: src/avltree_fixed.cpp include/avltree.hpp
	g++ $(CFLAGS) -c -o obj/avltree_fixed.o src/avltree_fixed.cpp

obj/avltree_lab.o: src/avltree_lab.cpp include/avltree.hpp
	g++ $(CFLAGS) -c -o obj/avltree_lab.o src/avltree_lab.cpp

obj/avltree_tester.o: src/avltree_tester.cpp include/avltree.hpp
	g++ $(CFLAGS) -c -o obj/avltree_tester.o src/avltree_tester.cpp

# -------------------------
# Executables

bin/avltree_tester: obj/avltree_tester.o obj/avltree_fixed.o obj/avltree_lab.o
	g++ $(CFLAGS) -o bin/avltree_tester obj/avltree_tester.o obj/avltree_fixed.o obj/avltree_lab.o
