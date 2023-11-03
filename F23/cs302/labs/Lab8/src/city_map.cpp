// Will Buziak
// CS302
// Lab 8
// Dijkstra's algorithm
// Find the shortest path between two intersections by streets and avenues

#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include "city_map.hpp"
using namespace std;

City_Map::City_Map() {
  // build a graph with the following links format
  
  // streets are x and avenues are y coordinates

  int strt, ave, highest;
  double x, y, gs, ga;
  Intersection *i;
  Road_Segment *r;
  list <Intersection*>::iterator lit;
    
  while (cin >> strt >> ave >> x >> y >> gs >> ga) { // create each intersection
    i = new Intersection;
    i->street = strt;
    i->avenue = ave;
    i->x = x;
    i->y = y;
    i->green[0] = gs;
    i->green[1] = ga;
    if (strt == 0 && ave == 0) first = i;
    all.push_back(i);
  }

  for (lit = all.begin(); lit != all.end(); lit++) {
   // streets ascend from east to west
    if ((*lit)->street % 5 == 0) {
      // if the street or avenue is a multiple of 5, they go in both directions
      (void) r;

    }
    /* else if (*lit->street % 2 == 0) { // even
      // even streets are one way east to west
    }
    else {
      // odd are one way west to east
    }
    
    // avenues ascend from south to north
    if (*lit->avenue == highest || *lit->avenue % 5 == 0) {
      // highest avenue always goes in both direction
      
    }
    else if (*lit->avenue % 2 == 0) { // avenue is even
      // even avenues are one way to the north
    }
    else {
      // odd avenues are one way to the south
    }

    r = new Road_Segment;
    */
  }
  delete i;
}

double City_Map::Dijkstra(int avg_best_worst) {
  // perform Dijkstras algorithm to find the shortest path between the two points
  (void) avg_best_worst;
  // find the path from light at [0, 0] and the light with the largest street and avenue
  return 0;
}
