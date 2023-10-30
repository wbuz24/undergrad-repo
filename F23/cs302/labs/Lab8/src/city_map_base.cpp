#include <vector>
#include <math.h>
#include "city_map.hpp"

typedef vector <Intersection *> Ivec;

void City_Map::Spit_Jgraph()
{
  Intersection *l;
  Road_Segment *rs;
  list <Intersection *>::iterator ait;
  list <Road_Segment *>::iterator adjit;
  double minx, miny, maxx, maxy;
  

  for (ait = all.begin(); ait != all.end(); ait++) {
    l = *ait;
    if (ait == all.begin()) {
      minx = l->x;
      miny = l->y;
      maxx = l->x;
      maxy = l->y;
    }
    if (minx > l->x) minx = l->x;
    if (maxx < l->x) maxx = l->x;
    if (miny > l->y) miny = l->y;
    if (maxy < l->y) maxy = l->y;
  }

  minx -= .5;
  maxx += .5;
  miny -= .5;
  maxy += .5;

  printf("newgraph xaxis size 8 nodraw min %lf max %lf yaxis nodraw size 8 min %lf max %lf\n", minx, maxx, miny, maxy);

  for (ait = all.begin(); ait != all.end(); ait++) {
    l = *ait;
    for (adjit = l->adj.begin(); adjit != l->adj.end(); adjit++) {
      rs = *adjit;
      printf("newline marktype circle rarrow pts %lf %lf %lf %lf\n", rs->from->x, rs->from->y, rs->to->x, rs->to->y);
    }
  }
  for (adjit = path.begin(); adjit != path.end(); adjit++) {
    rs = *adjit;
    printf("newline linethickness 2 marktype circle color 1 0 0 rarrow acfill 1 0 0 pts %lf %lf %lf %lf\n", rs->from->x, rs->from->y, rs->to->x, rs->to->y);
  }
}

void City_Map::Print()
{
  int i;
  Intersection *l;
  Road_Segment *rs;

  list <Intersection *>::iterator ait;
  list <Road_Segment *>::iterator adjit;
  
  i = 0;

  for (ait = all.begin(); ait != all.end(); ait++) {
    l = *ait;
    printf("%7d : Intersection: %4d %4d - %12.6lf %12.6lf - %12.6lf %12.6lf\n",
           i, l->street, l->avenue, l->x, l->y, l->green[STREET], l->green[AVENUE]);
    i++;
    for (adjit = l->adj.begin(); adjit != l->adj.end(); adjit++) {
      rs = *adjit;
      if (rs->from != l) {
        cout << "Error: road segment ->from not equal to intersection\n";
        exit(1);
      }
      printf("%7d :    Segment to %4d %4d       Distance %12.6lf\n", i, rs->to->street, rs->to->avenue,
        rs->distance);
    }
    i++;
  }

  for (adjit = path.begin(); adjit != path.end(); adjit++) {
    rs = *adjit;
    printf("%7d : PATH: [%04d,%04d] -> [%04d,%04d] - Time: %12.6lf\n", i, 
       rs->from->street, rs->from->avenue, rs->to->street, rs->to->avenue, rs->to->best_time);
    i++;
  }
}
  
void usage()
{
  cerr << "usage: city_map none|best|worst|avg time|print|jgraph - map on standard input\n";
  exit(1);
}

int main(int argc, char **argv)
{
  City_Map *cm;
  string a1, a2;
  double t;

  if (argc != 3) usage();
  a1 = argv[1];
  a2 = argv[2];
    
  cm = new City_Map();

  if (a1 == "none") {
    t = 0;
  } else if (a1 == "best") {
    t = cm->Dijkstra('B');
  } else if (a1 == "avg") {
    t = cm->Dijkstra('A');
  } else if (a1 == "worst") {
    t = cm->Dijkstra('W');
  } else {
    usage();
  }

  if (a2 == "time") {
    cout << t << endl;
  } else if (a2 == "print") {
    cm->Print();
  } else if (a2 == "jgraph") {
    cm->Spit_Jgraph();
  } else usage();
}
