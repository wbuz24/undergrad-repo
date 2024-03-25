# Generic makefile

all: bin/jdisk_test \
     bin/b_tree_test \
     bin/random_tester_1 \
     bin/random_tester_2 \

others: bin/b_tree_test_inst \
        bin/b_tree_dcs \

clean:
	rm -f a.out obj/* bin/*

LIBS = /home/jplank/lib/LINUX-X86_64/libfdr.a
INCLUDE = -I/home/jplank/include -Iinclude

# ---------------
# Object files

obj/jdisk.o: include/jdisk.h src/jdisk.c
	$(CC) $(INCLUDE) -c -o obj/jdisk.o src/jdisk.c

obj/jdisk_test.o: include/jdisk.h src/jdisk_test.c
	$(CC) $(INCLUDE) -c -o obj/jdisk_test.o src/jdisk_test.c

obj/b_tree.o: include/jdisk.h include/b_tree.h src/b_tree.c
	$(CC) $(INCLUDE) -c -o obj/b_tree.o src/b_tree.c

obj/b_tree_test.o: include/jdisk.h include/b_tree.h src/b_tree_test.c
	$(CC) $(INCLUDE) -c -o obj/b_tree_test.o src/b_tree_test.c

obj/b_tree_dcs.o: include/jdisk.h include/b_tree.h src/b_tree_dcs.c
	$(CC) $(INCLUDE) -c -o obj/b_tree_dcs.o src/b_tree_dcs.c

obj/random_tester_1.o: include/jdisk.h include/b_tree.h src/random_tester_1.c
	$(CC) $(INCLUDE) -c -o obj/random_tester_1.o src/random_tester_1.c

obj/random_tester_2.o: include/jdisk.h include/b_tree.h src/random_tester_2.c
	$(CC) $(INCLUDE) -c -o obj/random_tester_2.o src/random_tester_2.c

obj/b_tree_instrument.o: include/jdisk.h include/b_tree.h src/b_tree_instrument.c
	$(CC) $(INCLUDE) -c -o obj/b_tree_instrument.o src/b_tree_instrument.c

# -------------------
# Excutables

bin/jdisk_test: obj/jdisk_test.o obj/jdisk.o
	$(CC) -o bin/jdisk_test obj/jdisk_test.o obj/jdisk.o

bin/b_tree_test: obj/b_tree_test.o obj/b_tree.o obj/jdisk.o
	$(CC) -o bin/b_tree_test obj/b_tree_test.o obj/b_tree.o obj/jdisk.o

bin/b_tree_dcs: obj/b_tree_dcs.o obj/b_tree.o obj/jdisk.o
	$(CC) -o bin/b_tree_dcs obj/b_tree_dcs.o obj/b_tree.o obj/jdisk.o

bin/random_tester_1: obj/random_tester_1.o obj/b_tree.o obj/jdisk.o
	$(CC) -o bin/random_tester_1 obj/random_tester_1.o obj/b_tree.o obj/jdisk.o $(LIBS)

bin/random_tester_2: obj/random_tester_2.o obj/b_tree.o obj/jdisk.o
	$(CC) -o bin/random_tester_2 obj/random_tester_2.o obj/b_tree.o obj/jdisk.o $(LIBS)

bin/b_tree_test_inst: obj/b_tree_test.o obj/b_tree_instrument.o obj/jdisk.o
	$(CC) -o bin/b_tree_test_inst obj/b_tree_test.o obj/b_tree_instrument.o obj/jdisk.o

