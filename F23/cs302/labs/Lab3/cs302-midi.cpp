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
  multimap <double, ND*>::iterator mit;
  map <int, multimap <double, ND *> >::iterator it;  
  el = new EventList;

  for (mit = CS302_Midi::nd->begin(); mit != CS302_Midi::nd->end(); mit++) {
    // if (rint(mit->first) != rint(mit++->first)) mit++;
  }
  // traverse the ND multi-map
  // access the "key" element of the ND class
  // create a new event and add it to the events list
}
