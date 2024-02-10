CC = gcc 
INCLUDES = -I/home/jplank/cs360/include
CFLAGS = $(INCLUDES) -g
LIBDIR = /home/jplank/cs360/lib
LIBS = $(LIBDIR)/libfdr.a 

EXECUTABLES = bin/famtree

all: $(EXECUTABLES)

bin/famtree: src/famtree.c
	$(CC) $(CFLAGS) -o bin/famtree src/famtree.c $(LIBS)

clean:
	rm core $(EXECUTABLES) *.o
