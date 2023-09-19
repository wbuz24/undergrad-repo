#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <list>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include "cs302-midi.h"
using namespace std;

void CS302_Midi::el_to_nd()
{
  nd = new NDMap;
}

void CS302_Midi::nd_to_el()
{
  el = new EventList;

  multimap < double, ND * >::iterator mit;
  map < int, multimap < int, Event * > >tmp;
  map < int, multimap < int, Event * > >::iterator i;
  multimap < int, Event * >::iterator it;

  int pt = 0;
  double ltime = 0;

  for (mit = nd->begin(); mit != nd->end(); mit++) {
    Event* on = new Event;
    Event* off = new Event;

    if (mit->second->key == 'N') {
      on->key = 'O';
      off->key = 'F';

      on->time = rint(mit->second->start * 480);
      off->time = rint(mit->second->stop * 480);

      on->v1 = mit->second->pitch;
      on->v2 = mit->second->volume;

      off->v1 = mit->second->pitch;
      off->v2 = 0;

      tmp[off->time].insert(make_pair(1, off));
      tmp[on->time].insert(make_pair(4, on));
    }
    else if (mit->second->key == 'D') {
      on->key = 'D';
      off->key = 'D';

      on->time = rint(mit->second->start * 480);
      off->time = rint(mit->second->stop * 480);

      on->v1 = 1;
      on->v2 = 0;

      off->v1 = 0;
      off->v2 = 0;

      tmp[off->time].insert(make_pair(2, off));
      tmp[on->time].insert(make_pair(3, on));
    }
  }
  
  for (i = tmp.begin(); i != tmp.end(); i++) {

    for (it = i->second.begin(); it != i->second.end(); it++) {
      it->second->time -= ltime;
      if (it->second->time == pt) it->second->time = 0;
      el->push_back(it->second);
      ltime = i->first;
    }
    pt = i->first;
  }
}
