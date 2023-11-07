// Will Buziak
// CS302
// Lab 8
// Dijkstra's algorithm
// Find the shortest path between two intersections by streets and avenues

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <math.h>
#include <vector>
#include "city_map.hpp"
using namespace std;

City_Map::City_Map() {
  // build a graph with the following links format
  
  // streets are x and avenues are y coordinates

  int strt, ave, highest, hstrt;
  double x, y, gs, ga;
  Intersection *i;
  Road_Segment *r;
  list <Intersection*>::iterator lit;
  vector < vector < Intersection* > > tmp; // temporary adjacency matrix
  size_t j, k;
    
  highest = 0;
  hstrt = 0;
  while (cin >> strt >> ave >> x >> y >> gs >> ga) { // read in the intersections
    // create a new intersection
    i = new Intersection; 

    i->street = strt;
    i->avenue = ave;
    i->x = x;
    i->y = y;
    i->green[0] = gs;
    i->green[1] = ga;

    if (ave > highest) highest = ave; // find highest avenue
    if (strt > hstrt) hstrt = strt; // find highest street

    if (strt == 0 && ave == 0) first = i; // set the first node
    if (strt == hstrt && ave == highest) last = i; // set the last node
    all.push_back(i);
  }

  // resize the temporary vector to the proper sizes (must add one to the highest indices)
  tmp.resize(hstrt + 1);
  for (j = 0; j < tmp.size(); j++) tmp[j].resize(highest + 1);  
  
  for (lit = all.begin(); lit != all.end(); lit++) {
    // store into temporary vector
    tmp[(*lit)->street][(*lit)->avenue] = *lit;
  }

  for (j = 0; j < tmp.size(); j++) {
    for (k = 0; k < tmp[0].size(); k++) {
      r = new Road_Segment;
      // streets ascend from east to west (connect avenues)

      // if the street or avenue is a multiple of 5, they go in both directions
      if (tmp[j][k]->street % 5 == 0) { // check j & k bounds for each case
        if (k < tmp[0].size() - 1) {
          // add street to right (incrementing)
          r->type = STREET;
          r->number = j;
          r->distance = sqrt(pow(abs(tmp[j][k+1]->x - tmp[j][k]->x), 2) + pow(abs(tmp[j][k+1]->y - tmp[j][k]->y), 2));
          r->from = tmp[j][k];
          r->to = tmp[j][k+1];

          tmp[j][k]->adj.push_back(r);
        } 
        if (k > 0) {
          // add street to the left (decrementing)
          r->type = STREET;
          r->number = j;
          r->distance = sqrt(pow(abs(tmp[j][k]->x - tmp[j][k-1]->x), 2) + pow(abs(tmp[j][k]->y - tmp[j][k-1]->y), 2));

          r->from = tmp[j][k];
          r->to = tmp[j][k-1];

          tmp[j][k]->adj.push_back(r);
        }
      }
      else if (tmp[j][k]->street % 2 == 0) { // even
        if (k < tmp[0].size() - 1) {
          // one way street east to west (incrementing)
          r->type = STREET;
          r->number = j;
          r->distance = sqrt(pow(abs(tmp[j][k+1]->x - tmp[j][k]->x), 2) + pow(abs(tmp[j][k+1]->y - tmp[j][k]->y), 2));
          r->from = tmp[j][k];
          r->to = tmp[j][k+1];

          tmp[j][k]->adj.push_back(r);

        }
      }
      else { // odd is left to right (decrementing)
        if (k > 0) {
          // one way street west to east
          r->type = STREET;
          r->number = j;
          r->distance = sqrt(pow(abs(tmp[j][k]->x - tmp[j][k-1]->x), 2) + pow(abs(tmp[j][k]->y - tmp[j][k-1]->y), 2));

          r->from = tmp[j][k];
          r->to = tmp[j][k-1];

          tmp[j][k]->adj.push_back(r);
        }
      }
    
      // avenues ascend from south to north
      if (tmp[j][k]->avenue == highest || tmp[j][k]->avenue % 5 == 0) {
        // highest avenue always goes in both direction
        if (j < tmp.size() - 1) {
          // add avenues going south to north (incrementing)
          r->type = AVENUE;
          r->number = k;
          r->distance = sqrt(pow(tmp[j+1][k]->x - tmp[j][k]->x, 2) + pow(tmp[j+1][k]->y - tmp[j][k]->y, 2));
          r->from = tmp[j][k];
          r->to = tmp[j+1][k];
         
          tmp[j][k]->adj.push_back(r);
        }
        if (j > 0) {
          // add avenues going north to south (decrementing)
          r->type = AVENUE;
          r->number = k;
          r->distance = sqrt(pow(tmp[j-1][k]->x - tmp[j][k]->x, 2) + pow(tmp[j-1][k]->y - tmp[j][k]->y, 2));

          r->from = tmp[j][k];
          r->to = tmp[j-1][k];
          tmp[j][k]->adj.push_back(r);
        }
      }
      else if (tmp[j][k]->avenue % 2 == 0) { // avenue is even
        // even avenues are one way to the north (incrementing)
        if (j < tmp.size() - 1) {
          r->type = AVENUE;
          r->number = k;
          r->distance = sqrt(pow(tmp[j+1][k]->x - tmp[j][k]->x, 2) + pow(tmp[j+1][k]->y - tmp[j][k]->y, 2));

          r->from = tmp[j][k];
          r->to = tmp[j+1][k];

          tmp[j][k]->adj.push_back(r);
        }
      }
      else {
        // odd avenues are one way to the south (decrementing)
        if (j > 0) {
          // odd avenues going north to south
          r->type = AVENUE;
          r->number = k;
          r->distance = sqrt(pow(tmp[j-1][k]->x - tmp[j][k]->x, 2) + pow(tmp[j-1][k]->y - tmp[j][k]->y, 2));

          r->from = tmp[j][k];
          r->to = tmp[j-1][k];
          tmp[j][k]->adj.push_back(r);
        } 
      } 


    }
  }

  
}

double City_Map::Dijkstra(int avg_best_worst) {
  // perform Dijkstras algorithm to find the shortest path between the two points
  (void) avg_best_worst;
  // find the path from light at [0, 0] and the light with the largest street and avenue
  return 0;
}
