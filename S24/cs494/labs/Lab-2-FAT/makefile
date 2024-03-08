# Generic makefile

all: jdisk_test  FAT FATRW sectordiff

clean:
	rm -f jdisk_test FAT FATRW sectordiff *.o

LIBS = $(HOME)/$(LIB)/libfdr.a
INCLUDE = $(HOME)/include
CC = gcc

.SUFFIXES: .cpp .c .o .out .hist .jgr .jps .eps .nt .bib .tab .tex .dvi .fig .txt .ps .pdf .bin .od .odh .odd .ppm .gif

.cpp.o: 
	g++ -c -I$(INCLUDE) $*.cpp

.c.o: 
	g++ -c -I$(INCLUDE) $*.c

jdisk.o: jdisk.h
jdisk_test.o: jdisk.h

jdisk_test: jdisk_test.o jdisk.o
	g++ -o jdisk_test jdisk_test.o jdisk.o

FAT.o: jdisk.h

FAT: FAT.o jdisk.o
	g++ -o FAT FAT.o jdisk.o

FATRW: FATRW.o jdisk.o
	g++ -o FATRW FATRW.o jdisk.o

