all: maze_solve

clean:
	rm -f *.o maze_solve

.SUFFIXES: .cpp .o

.cpp.o: g++ -c $*.cpp 

maze_solve: maze_solve.o
	g++ -o maze_solve maze_solve.o
