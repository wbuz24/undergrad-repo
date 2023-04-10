CFLAGS ?= -std=c++11 -Wall -Wextra 

# -------------------------
# This means that when you just type "make", you make all of the executables

ALL = \
      bin/enum \
      bin/ss_solver

OTHER = \
      bin/ss_player \
      bin/ss_random_game

all: $(ALL)
other: $(OTHER)

# -------------------------
# "make clean" deletes the object files and binaries

clean:
	rm -f obj/* bin/*


# -------------------------
# Executables

bin/enum: src/enum.cpp
	g++ $(CFLAGS) -o bin/enum src/enum.cpp

bin/ss_solver: src/ss_solver.cpp 
	g++ $(CFLAGS) -o bin/ss_solver src/ss_solver.cpp

bin/ss_player: src/ss_player.cpp
	g++ $(CFLAGS) -o bin/ss_player src/ss_player.cpp

bin/ss_random_game: src/ss_random_game.cpp
	g++ $(CFLAGS) -o bin/ss_random_game src/ss_random_game.cpp
