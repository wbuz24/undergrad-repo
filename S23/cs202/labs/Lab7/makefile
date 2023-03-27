CFLAGS ?= -std=c++11 -Wall -Wextra -Iinclude

# -------------------------
# This means that when you just type "make", you make all of the executables

ALL = bin/cp_tester bin/random_codes

all: $(ALL)

# -------------------------
# "make clean" deletes the object files and binaries

clean:
	rm -f obj/* bin/*


all: bin/cp_tester

bin/cp_tester: obj/cp_tester.o obj/code_processor.o obj/double_checker.o
	g++ $(CFLAGS) -o bin/cp_tester obj/cp_tester.o obj/code_processor.o obj/double_checker.o

obj/cp_tester.o: src/cp_tester.cpp include/code_processor.hpp
	g++ $(CFLAGS) -o obj/cp_tester.o -c src/cp_tester.cpp

obj/code_processor.o: src/code_processor.cpp include/code_processor.hpp
	g++ $(CFLAGS) -o obj/code_processor.o -c src/code_processor.cpp

obj/double_checker.o: src/double_checker.cpp include/code_processor.hpp
	g++ $(CFLAGS) -o obj/double_checker.o -c src/double_checker.cpp

bin/random_codes: src/random_codes.cpp 
	g++ $(CFLAGS) -o bin/random_codes src/random_codes.cpp

