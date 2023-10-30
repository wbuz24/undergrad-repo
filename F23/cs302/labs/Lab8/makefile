all: bin/city_map

clean:
	rm -f bin/*

bin/city_map: include/city_map.hpp src/city_map.cpp src/city_map_base.cpp
	g++ -o bin/city_map -Iinclude -Wall -Wextra src/city_map.cpp src/city_map_base.cpp

