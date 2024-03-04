CC = g++
CFLAGS = $(INCLUDES) -Wall -Wextra -g

EXECUTABLES = bin/motd

all: $(EXECUTABLES)

bin/motd: src/motd.cpp
	$(CC) $(CFLAGS) -o bin/motd src/motd.cpp

clean:
	rm $(EXECUTABLES)
