// Will Buziak
// CS302
// Lab 8
// Dijkstra's algorithm
// Find the shortest path between two intersections by streets and avenues

#include "city_map.hpp"
using namespace std;

City_Map::City_Map() {
  // build a graph with the following links format
  
  // streets are x and avenues are y coordinates

  // streets ascend from east to west
  // even streets are one way east to west
  // odd are one way west to east

  // avenues ascend from south to north
  // even avenues are one way to the north
  // odd avenues are one way to the south
  
  // if the street or avenue is a multiple of 5, they go in both directions
  // highest avenue always goes in both direction
}

double City_Map::Dijkstra(int avg_best_worst) {
  // perform Dijkstras algorithm to find the shortest path between the two points

  // find the path from light at [0, 0] and the light with the largest street and avenue
  return avg_best_worst;
}
