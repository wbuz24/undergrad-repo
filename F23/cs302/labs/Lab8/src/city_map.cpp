// Will Buziak
// Djikstras algorithm
// Lab 8
// CS302

#include <iostream>
#include "city_map.hpp"
#include <math.h>
#include <vector>
using namespace std;

double City_Map::Dijkstra(int avg_best_worst){
  list <Road_Segment *>::iterator rit;
  double time = 0;
  double a = 0, s = 0;
  vector < vector < double > > visited;
  Intersection *curr;
  Intersection *tmp;
  double d = 0;

  // insert first node
  visited.resize(last->avenue+1);
  tmp = last;
  bfsq.insert(make_pair(0, first));

  for (int i = 0; i < (int)visited.size(); i ++) visited[i].resize(last->street+1,-1);

  visited[0][0] = 0;
  // bfs
  while (!bfsq.empty()) {
    curr = bfsq.begin()->second;
    curr -> bfsq_ptr = bfsq.begin();
    for ( rit = curr->adj.begin(); rit!= curr->adj.end(); rit++){
      // getting correcting time with respect to average, worst, and best case
      switch (avg_best_worst){
        case 'A':
          switch ((*rit)->type){
            case AVENUE: a = (*rit)->to->green[STREET];
              s = (*rit)->to->green[AVENUE];time = (a*a) / (2 * (a + s)); break;
            case STREET: a = (*rit)->to->green[AVENUE];
              s = (*rit)->to->green[STREET];time = (a*a) / (2 * (a + s)); break;
          } break;
        case 'W':
          switch((*rit)->type){
            case STREET: time = (*rit)->to->green[AVENUE];
              break;
            case AVENUE: time = (*rit)->to->green[STREET];
              break;
          }
      }
      // calculate the time from provided equation
      double d = (*rit) ->distance / 30 * 3600 + (*rit)->from->best_time + time;
      // if not visited or you can find a favorable time
      if (visited[(*rit)->to->avenue][(*rit)->to->street] == -1 || d < visited[(*rit)->to->avenue][(*rit)->to->street]){
        if ((*rit)->to->bfsq_ptr != bfsq.end()){
           bfsq.erase((*rit)->to->bfsq_ptr);
        }
        // set the visited field and nodes backedges
        visited[(*rit)->to->avenue][(*rit)->to->street] = d;
        (*rit)->to->backedge = (*rit);
        (*rit)->to->best_time = d;
        (*rit)->to->bfsq_ptr = bfsq.insert(make_pair(d, (*rit)->to));
      }
    }
    bfsq.erase(bfsq.begin());
  }

  // chase the back link
  while (tmp != first){
    path.push_front(tmp->backedge);
    d +=tmp ->backedge->distance;
    tmp = tmp->backedge->from;
  }
  return 0;
}

City_Map::City_Map(){
  string l;
  int street, avenue;
  double x, y, gstreet, gavenue;
  int strt = 0;
  int ave = 0;
  list <Intersection *>::iterator lit;
  list <Intersection *>::iterator sit;

  // reading all Intersections
  while (cin >> street >> avenue >> x >> y >> gstreet >> gavenue){
    // create a new intersection
    Intersection* I = new Intersection();
    I->street = street;
    I->avenue = avenue;
    I->x = x;
    I->y = y;
    I->green[0] = gstreet;
    I->green[1] = gavenue;
    
    I->best_time = 0; // for Djikstras
    I->backedge = NULL;
    I->bfsq_ptr = bfsq.end();

    if (avenue > ave) ave = avenue; // find the highest street and avenure
    if (street > strt) strt = street;
    
    all.push_back(I);
  }

  for (lit = all.begin(); lit != all.end(); lit++){
    // highest street and avenue, set the last node
    if (strt == (*lit)->street && ave == (*lit)->avenue) last = *lit;
    // same with first node
    if (0 == (*lit)->street && 0 == (*lit)->avenue) first = *lit;

    for (sit = all.begin(); sit != all.end(); sit++){
      // must check if the nodes are the same
      if (*sit == *lit) continue;
      Road_Segment* r = new Road_Segment(); // new segment
      r->number = -1; // use the segment to check the placement of the nodes relative to eachother
      // odd streets and multiples of 5
      if ((*lit)->street % 2 != 0 || ((*lit)->street % 5 == 0 )){
        if ((*lit)->street == (*sit)->street && (*lit)->avenue == (*sit)->avenue+1){
          r->type = STREET;
          r->number = (*lit)->street;
        }
      }
      // even numbers and multiples of 5
      if((*lit)->street % 2 == 0 || ( (*lit)->street % 5 == 0)){
        if((*lit)->street == (*sit)->street && (*lit)->avenue == (*sit)->avenue - 1){
          r->type = STREET;
          r->number = (*lit)->street;
        }
      }
      // odd numbers and the highest avenue
      if( (*lit)->avenue % 2 != 0 || (*lit)->avenue == ave || (*lit)->avenue % 5 == 0){
        if ((*lit)->avenue == (*sit)->avenue && (*lit)->street == (*sit)->street + 1 ){
          r->type = AVENUE;
          r->number = (*lit)->avenue;
        }
      }
      // even numbers and highest avenue
      if( (*lit)->avenue % 2 == 0 || (*lit)->avenue% 5 == 0 || (*lit)->avenue == ave){
        if ((*lit)->avenue == (*sit)->avenue && (*lit)->street == (*sit)->street - 1 ){
          r->type = AVENUE;
          r->number = (*lit)->avenue;
        }
      }
      // set distance and pointers
      if (r->number != -1){
        r->from = *lit;
        r->to = *sit;
        r->distance = sqrt(pow((*lit)->x- (*sit)->x,2) +
                           pow((*lit)->y - (*sit)->y,2));
        (*lit)->adj.push_back(r);
      }

      else {
        delete r;
      }
    }
  }
}

