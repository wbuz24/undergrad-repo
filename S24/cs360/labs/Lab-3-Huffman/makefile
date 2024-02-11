CC = gcc
# INCLUDES = -I/home/jplank/cs360/include
CFLAGS = $(INCLUDES) -Wall -Wextra -g -lm
#LIBDIR = /home/jplank/cs360/lib
#LIBS = $(LIBDIR)/libfdr.a 

EXECUTABLES = bin/huff_dec

all: $(EXECUTABLES)

bin/huff_dec: src/huff_dec.c
	$(CC) $(CFLAGS) -o bin/huff_dec src/huff_dec.c

clean:
	rm $(EXECUTABLES)
