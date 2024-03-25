CC = gcc 
INCLUDES = -I/home/jplank/cs360/include
#CFLAGS = $(INCLUDES) -g -fsanitize=address
CFLAGS = $(INCLUDES) -g
LIBDIR = /home/jplank/cs360/lib
LIBS = $(LIBDIR)/libfdr.a 

EXECUTABLES = bin/tarx

all: $(EXECUTABLES)

bin/tarx: src/tarx.c
	$(CC) $(CFLAGS) -o bin/tarx src/tarx.c $(LIBS)

clean:
	rm -f $(EXECUTABLES)
