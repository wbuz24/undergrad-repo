EXECUTABLES = bin/pgminfo \
              bin/graycard \
              bin/neg \
              bin/hflip \
              bin/vflip \

CFLAGS ?= -Wall -Wextra -std=c++11

all: $(EXECUTABLES)

clean:
	rm -f a.out bin/*

bin/graycard: src/graycard.cpp
	g++ $(CFLAGS) -o bin/graycard src/graycard.cpp

bin/pgminfo: src/pgminfo.cpp
	g++ $(CFLAGS) -o bin/pgminfo src/pgminfo.cpp

bin/neg: src/neg.cpp
	g++ $(CFLAGS) -o bin/neg src/neg.cpp

bin/hflip: src/hflip.cpp
	g++ $(CFLAGS) -o bin/hflip src/hflip.cpp

bin/vflip: src/vflip.cpp
	g++ $(CFLAGS) -o bin/vflip src/vflip.cpp
