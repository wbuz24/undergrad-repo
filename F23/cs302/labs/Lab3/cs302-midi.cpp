// Will Buziak
// CS302 
// Lab 3 
// Midi Manipulation
// write the methods nd_to_el & el_to_nd

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
  vector <ND *> v; // indexed by pitch
  list <Event *>::const_iterator lit; // const iterator for the el list
  size_t i;

  double ltime = 0, c = 0;

  v.resize(128, NULL); // resize vector 128 & initialize to NULL

  for (lit = el->begin(); lit != el->end(); lit++) {

    ND* nn = new ND;
    if ((*lit)->key == 'O') { // on event
      nn->key = 'N';
      nn->pitch = (*lit)->v1;
      nn->start = ((*lit)->time + ltime) / 480;
      nn->volume = (*lit)->v2;
      v[nn->pitch] = nn; // place in the vector
    }

    if ((*lit)->key == 'F') { // off event
      v[(*lit)->v1]->stop = ((*lit)->time + ltime) / 480; // index to the pitch & set the stop
      nd->insert(make_pair(v[(*lit)->v1]->start, v[(*lit)->v1])); // insert into nd map
    }

    if ((*lit)->key == 'D') { // damper DOWN
      if ((*lit)->v1 == 1) c = ((*lit)->time + ltime) / 480;
      else if ((*lit)->v1 == 0) {
      nn->key = 'D';
      nn->start = c;
      nn->stop = ((*lit)->time + ltime) / 480; // set stop time
      nd->insert(make_pair(c, nn)); // insert into the map

      }
    }
    ltime += (*lit)->time;

   
    // traverse the vector & make sure no ON events never end

  }
}

void CS302_Midi::nd_to_el()
{
  el = new EventList;

  map <int, multimap <int, Event *> > tmpmap; // temporary map of events
  multimap <double, ND*>::iterator mit; // iterators
  multimap <int, Event *>::iterator tmpmit;
  map <int, multimap <int, Event *> >::iterator it;  

  int pt = 0;
  double ltime = 0;

  for (mit = nd->begin(); mit != nd->end(); mit++) {
    // create a new event and add it to the events list
    Event* no = new Event; // Damper Up/ OFF event
    Event* ne = new Event; // create a new Damper Down/ ON event
    if (mit->second->key == 'N') { // Note is found
      no->key = 'F'; // off
      no->time = rint(mit->second->stop * 480); // convert to sec
      no->v1 = mit->second->pitch;
      no->v2 = 0;

      ne->key = 'O'; // On
      ne->time = rint(mit->second->start * 480);
      ne->v1 = mit->second->pitch; // v1 = pitch for O/F
      ne->v2 = mit->second->volume;

      tmpmap[no->time].insert(make_pair(1, no));
      tmpmap[ne->time].insert(make_pair(4, ne));
    }
    else { // 'D' for Damper
      no->key = 'D'; // damper UP
      no->time = rint(mit->second->stop * 480);
      no->v1 = 0;
      no->v2 = 0;

      ne->key = 'D';
      ne->time = rint(mit->second->start * 480);
      ne->v1 = 1; // this denotes a damper DOWN
      ne->v2 = 0;

      tmpmap[no->time].insert(make_pair(2, no));
      tmpmap[ne->time].insert(make_pair(3, ne));
    }
  }

  // traverse the temporary map and push all events onto el(), calculating the correct time.
  for (it = tmpmap.begin(); it != tmpmap.end(); it++) {

    for (tmpmit = it->second.begin(); tmpmit != it->second.end(); tmpmit++) {
      tmpmit->second->time -= ltime;
      if (pt == tmpmit->second->time) tmpmit->second->time = 0; // if previous start is equal to the end
      el->push_back(tmpmit->second);
      ltime = it->first; // time since last event
    }
    pt = it->first;
  }
}
