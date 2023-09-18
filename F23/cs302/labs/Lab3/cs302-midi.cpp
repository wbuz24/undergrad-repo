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
  vector <ND *> v;
  list <Event *>::const_iterator lit; // const iterator for the el list

  v.resize(128, NULL); // resize vector 128 & initialize to NULL

  for (lit = CS302_Midi::el->begin(); lit != CS302_Midi::el->end(); lit++) {
    if (*lit->key == 'O') {
      ND* nn = new ND;
      nn->key = 'N';
      nn->pitch = *lit->v1;
    }
  }

}

void CS302_Midi::nd_to_el()
{
  map <int, multimap <int, Event *> > tmpmap; // temporary map of events
  multimap <int, Event *> tmpmult; // temporary multimap
  multimap <double, ND*>::iterator mit; // iterators
  multimap <int, Event *>::iterator tmpmit;
  map <int, multimap <int, Event *> >::iterator it;  
  el = new EventList;
  int last_time = 0;

  for (mit = CS302_Midi::nd->begin(); mit != CS302_Midi::nd->end(); mit++) {
    Event* no = new Event; // Damper Up/ OFF event
    Event* ne = new Event; // create a new Damper Down/ ON event
    if (mit->second->key == 'N') { // Note is found
      no->key = 'F'; // off
      no->time = rint(mit->second->stop);
      no->v1 = rint(mit->second->pitch);

      ne->key = 'O'; // On
      ne->time = rint(mit->second->start); // time = time since last event
      ne->v1 = rint(mit->second->pitch); // v1 = pitch for O/F
      ne->v2 = rint(mit->second->volume);
      
    }
    else { // 'D' for Damper
      no->key = 'D'; // damper UP
      no->time = rint(mit->second->stop);
      no->v1 = 0;

      ne->key = 'D';
      ne->time = rint(mit->second->start);
      ne->v1 = 1; // this denotes a damper DOWN
      
    }
    tmpmult.insert(make_pair(rint(mit->second->start), ne)); // now sorted by time
    tmpmult.insert(make_pair(rint(mit->second->stop), no)); // insert into the multimap

    last_time = rint(mit->second->stop);
  }
  // traverse the Event multi-map
  for (tmpmit = tmpmult.begin(); tmpmit != tmpmult.end(); tmpmit++) {
    // maps dont insert duplicates, therefore inserting the integer should remove competing events
    tmpmap.insert(make_pair(rint(tmpmit->first), tmpmult)); 
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
