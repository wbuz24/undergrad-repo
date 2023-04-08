CFLAGS ?= -std=c++11 -Wall -Wextra -Iinclude

# -------------------------
# This means that when you just type "make", you make all of the executables

ALL = \
      bin/dlist_rev_1 \
      bin/dlist_rev_2 \
      bin/dlist_rev_3 \
      bin/dlist_rev_4 \
      bin/dlist_rev_5 \
      bin/dlist_rev_6 \
      bin/dlist_editor \

all: $(ALL)

# -------------------------
# "make clean" deletes the object files and binaries

clean:
	rm -f obj/* bin/*

# -------------------------
# Object files

obj/dlist.o: src/dlist.cpp include/dlist.hpp
	g++ $(CFLAGS) -c -o obj/dlist.o src/dlist.cpp

obj/dlist_rev_1.o: src/dlist_rev_1.cpp include/dlist.hpp
	g++ $(CFLAGS) -c -o obj/dlist_rev_1.o src/dlist_rev_1.cpp

obj/dlist_rev_2.o: src/dlist_rev_2.cpp include/dlist.hpp
	g++ $(CFLAGS) -c -o obj/dlist_rev_2.o src/dlist_rev_2.cpp

obj/dlist_rev_3.o: src/dlist_rev_3.cpp include/dlist.hpp
	g++ $(CFLAGS) -c -o obj/dlist_rev_3.o src/dlist_rev_3.cpp

obj/dlist_rev_4.o: src/dlist_rev_4.cpp include/dlist.hpp
	g++ $(CFLAGS) -c -o obj/dlist_rev_4.o src/dlist_rev_4.cpp

obj/dlist_rev_5.o: src/dlist_rev_5.cpp include/dlist.hpp
	g++ $(CFLAGS) -c -o obj/dlist_rev_5.o src/dlist_rev_5.cpp

obj/dlist_rev_6.o: src/dlist_rev_6.cpp include/dlist.hpp
	g++ $(CFLAGS) -c -o obj/dlist_rev_6.o src/dlist_rev_6.cpp

obj/dlist_editor.o: src/dlist_editor.cpp include/dlist.hpp
	g++ $(CFLAGS) -c -o obj/dlist_editor.o src/dlist_editor.cpp


# -------------------------
# Executables

bin/dlist_rev_1: obj/dlist_rev_1.o obj/dlist.o
	g++ $(CFLAGS) -o bin/dlist_rev_1 obj/dlist_rev_1.o obj/dlist.o

bin/dlist_rev_2: obj/dlist_rev_2.o obj/dlist.o
	g++ $(CFLAGS) -o bin/dlist_rev_2 obj/dlist_rev_2.o obj/dlist.o

bin/dlist_rev_3: obj/dlist_rev_3.o obj/dlist.o
	g++ $(CFLAGS) -o bin/dlist_rev_3 obj/dlist_rev_3.o obj/dlist.o

bin/dlist_rev_4: obj/dlist_rev_4.o obj/dlist.o
	g++ $(CFLAGS) -o bin/dlist_rev_4 obj/dlist_rev_4.o obj/dlist.o

bin/dlist_rev_5: obj/dlist_rev_5.o obj/dlist.o
	g++ $(CFLAGS) -o bin/dlist_rev_5 obj/dlist_rev_5.o obj/dlist.o

bin/dlist_rev_6: obj/dlist_rev_6.o obj/dlist.o
	g++ $(CFLAGS) -o bin/dlist_rev_6 obj/dlist_rev_6.o obj/dlist.o

bin/dlist_editor: obj/dlist_editor.o obj/dlist.o
	g++ $(CFLAGS) -o bin/dlist_editor obj/dlist_editor.o obj/dlist.o

