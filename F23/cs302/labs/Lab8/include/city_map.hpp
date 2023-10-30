#include <iostream>
#include <map>
#include <list>
#include <cstdio>
#include <cstdlib>
using namespace std;

typedef enum { STREET, AVENUE } Road_Type;

class Intersection {
  public:
    int street;
    int avenue;
    double x;
    double y;
    double green[2];    // Light green times for STREET & AVENUE
    list <class Road_Segment *> adj;
    double best_time;
    class Road_Segment *backedge;
    multimap <double, Intersection *>::iterator bfsq_ptr;
};

class Road_Segment {
   public:
     Road_Type type;
     int number;
     double distance;
     Intersection *from;
     Intersection *to;
};

class City_Map {
  public:
    City_Map();  
    void Print();
    void Spit_Jgraph();
    double Dijkstra(int avg_best_worst);   // 'A' for avg, 'B' for best, 'W' for worst
    Intersection *first;
    Intersection *last;
    list <Intersection *> all;
    multimap <double, Intersection *> bfsq;
    list <Road_Segment *> path;
};
