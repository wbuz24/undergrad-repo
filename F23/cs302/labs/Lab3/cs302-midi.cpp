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
}

void CS302_Midi::nd_to_el()
{
  map <int, multimap <double, Event *> > tmpmap; // temporary map of events
  multimap <double, Event *> tmpmult; // temporary multimap
  multimap <double, ND*>::iterator mit; // iterators
  multimap <double, Event *>::iterator tmpmit;
  map <int, multimap <double, Event *> >::iterator it;  
  el = new EventList;
  int last_time = 0;

  for (mit = CS302_Midi::nd->begin(); mit != CS302_Midi::nd->end(); mit++) {
    // if (rint(mit->first) != rint(mit++->first)) mit++;
    Event* no = new Event; // Damper Up/ OFF event
    Event* ne = new Event; // create a new Damper Down/ ON event
    if (mit->second->key == 'N') { // Note is found
      no->key = 'F';
      no->time = mit->second->stop;
      no->v1 = mit->second->pitch;

      ne->key = 'O'; // On
      ne->time = mit->second->start; // time = time since last event
      ne->v1 = mit->second->pitch; // v1 = pitch for O/F
      ne->v2 = mit->second->volume;
      
    }
    else { // 'D' for Damper
      no->key = 'D'; // damper UP
      no->time = mit->second->stop;
      no->v1 = 0;

      ne->key = 'D';
      ne->time = mit->second->start;
      ne->v1 = 1; // this denotes a damper DOWN
      
    }
    tmpmult.insert(make_pair(mit->second->stop, no)); // insert into the multimap
    tmpmult.insert(make_pair(mit->second->start, ne)); // now sorted by time

    last_time = rint(mit->second->stop);
  }
  // traverse the Event multi-map
  for (tmpmit = tmpmult.begin(); tmpmit != tmpmult.end(); tmpmit++) {
    // maps dont insert duplicates, therefore inserting the integer should remove competing events
    if (tmpmit->second->key == 'F') { // OFF events
      tmpmap.insert(make_pair(rint(tmpmit->first), tmpmult));
    }
    if (tmpmit->second->key == 'D' && tmpmit->second->v1 == 0) { // damper UP
      tmpmap.insert(make_pair(rint(tmpmit->first), tmpmult));
    }
    if (tmpmit->second->key == 'D' && tmpmit->second->v1 == 1) { // damper DOWN
      tmpmap.insert(make_pair(rint(tmpmit->first), tmpmult));
    }
    if (tmpmit->second->key == 'O') { // ON events
      tmpmap.insert(make_pair(rint(tmpmit->first), tmpmult));
    }
  }

  // traverse the temporary map and push all events onto el(), calculating the correct time.
  for (it = tmpmap.begin(); it != tmpmap.end(); it++) {
    for (tmpmit = it->second.begin(); tmpmit != it->second.end(); tmpmit++) { 
      el->push_back(tmpmit->second);
    }
  }
  // access the "key" element of the ND class
  // create a new event and add it to the events list
}
