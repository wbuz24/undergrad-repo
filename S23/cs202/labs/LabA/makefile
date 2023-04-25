CFLAGS ?= -std=c++98 -Wall -Wextra -Iinclude

# -------------------------
# This means that when you just type "make", you make all of the executables

ALL = bin/bstree_tester \

all: $(ALL)

# -------------------------
# "make clean" deletes the object files and binaries

clean:
	rm -f obj/* bin/*

# -------------------------
# Object files

obj/bstree_tester.o: src/bstree_tester.cpp include/bstree.hpp
	g++ $(CFLAGS) -c -o obj/bstree_tester.o src/bstree_tester.cpp

obj/bstree_notes.o: src/bstree_notes.cpp include/bstree.hpp
	g++ $(CFLAGS) -c -o obj/bstree_notes.o src/bstree_notes.cpp

obj/bstree_lab.o: src/bstree_lab.cpp include/bstree.hpp
	g++ $(CFLAGS) -c -o obj/bstree_lab.o src/bstree_lab.cpp

# -------------------------
# Executables

bin/bstree_tester: obj/bstree_tester.o obj/bstree_notes.o obj/bstree_lab.o
	g++ $(CFLAGS) -o bin/bstree_tester obj/bstree_tester.o obj/bstree_notes.o obj/bstree_lab.o
