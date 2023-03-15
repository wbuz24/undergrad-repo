CFLAGS ?= -std=c++98 -Wall -Wextra -Iinclude

# -------------------------
# This means that when you just type "make", you make all of the executables

ALL = bin/bitmatrix_editor

all: $(ALL)

# -------------------------
# "make clean" deletes the object files and binaries

clean:
	rm -f obj/* bin/*

# -------------------------
# Object files

obj/bitmatrix.o: src/bitmatrix.cpp include/bitmatrix.hpp
	g++ $(CFLAGS) -c -o obj/bitmatrix.o src/bitmatrix.cpp

obj/bitmatrix_editor.o: src/bitmatrix_editor.cpp include/bitmatrix.hpp
	g++ $(CFLAGS) -c -o obj/bitmatrix_editor.o src/bitmatrix_editor.cpp

# -------------------------
# Executables

bin/bitmatrix_editor: obj/bitmatrix_editor.o obj/bitmatrix.o
	g++ $(CFLAGS) -o bin/bitmatrix_editor obj/bitmatrix_editor.o obj/bitmatrix.o

