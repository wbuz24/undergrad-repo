CFLAGS = -Wall -Wextra -std=c++11 -Iinclude

all: bin/lab_2

clean:
	rm -f bin/*

bin/lab_2: src/lab_2_driver.cpp src/lab_2_solution.cpp include/lab_2.hpp
	g++ $(CFLAGS) -o bin/lab_2  src/lab_2_driver.cpp src/lab_2_solution.cpp

