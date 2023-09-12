#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <list>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "cs302-midi.h"
using namespace std;

static void Print_Event(Event *e, FILE *f)
{
  if (e->key == 'O') {
    fprintf(f, "ON %d %d %d\n", e->time, e->v1, e->v2);
  } else if (e->key == 'F') {
    fprintf(f, "OFF %d %d\n", e->time, e->v1);
  } else if (e->key == 'D') {
    fprintf(f, "DAMPER %d %s\n", e->time, ((e->v1 == 1) ? "DOWN" : "UP"));
  } else {
    fprintf(stderr, "Bad event: %c\n", e->key);
  }
}

static void Print_ND(ND *n, FILE *f)
{
  if (n->key == 'N') {
    fprintf(f, "NOTE %d %d %.8lg %.8lg\n", n->pitch, n->volume, n->start, n->stop);
  } else if (n->key == 'D') {
    fprintf(f, "DAMPER %.8lg %.8lg\n", n->start, n->stop);
  }
}

CS302_Midi::~CS302_Midi()
{
  destroy_nd();
  destroy_el();
}

void CS302_Midi::destroy_el()
{
  EventList::iterator eit;
  
  if (el == NULL) return;
  for (eit = el->begin(); eit != el->end(); eit++) delete(*eit);
  delete el;
  el = NULL;
}

void CS302_Midi::destroy_nd()
{
  NDMap::iterator nit;
  
  if (nd == NULL) return;
  for (nit = nd->begin(); nit != nd->end(); nit++) delete (nit->second);
  delete nd;
  nd = NULL;
}

CS302_Midi::CS302_Midi(string file)
{
  EventList::iterator eit;
  ifstream fin;
  string s;
  int time, pitch, volume, i;
  double start, stop;
  Event *e;
  ND *n;

  fin.open(file.c_str());
  if (fin.fail()) {
    cerr << "Could not open " << file << endl;
    exit(1);
  }
  
  fin >> s;
  if (fin.fail()) {
    cerr << "Bad file: " << file << " -- no CS302-Midi-XXX-File\n";
    exit(1);
  }
  if (s == "CS302-Midi-Event-File") {
    el = new EventList;
    nd = NULL;
    while (fin >> s) {
      if (s == "ON") {
        if (!(fin >> time) || time < 0) {
          cerr << "Bad file: " << file << " -- bad time for ON event\n";
          exit(1);
        }
        if (!(fin >> pitch) || pitch < 0 || pitch > 127) {
          cerr << "Bad file: " << file << " -- bad pitch for ON event\n";
          exit(1);
        }
        if (!(fin >> volume) || volume <= 0 || volume > 127) {
          cerr << "Bad file: " << file << " -- bad volume for ON event\n";
          exit(1);
        }
        e = new Event;
        e->key = 'O';
        e->time = time;
        e->v1 = pitch;
        e->v2 = volume;
      } else if (s == "OFF") {
        if (!(fin >> time) || time < 0) {
          cerr << "Bad file: " << file << " -- bad time for OFF event\n";
          exit(1);
        }
        if (!(fin >> pitch) || pitch < 0 || pitch > 127) {
          cerr << "Bad file: " << file << " -- bad pitch for OFF event\n";
          exit(1);
        }
        e = new Event;
        e->key = 'F';
        e->time = time;
        e->v1 = pitch;
      } else if (s == "DAMPER") {
        if (!(fin >> time) || time < 0) {
          cerr << "Bad file: " << file << " -- bad time for DAMPER event\n";
          exit(1);
        }
        if (!(fin >> s) || (s != "DOWN" && s != "UP")) {
          cerr << "Bad file: " << file << " -- bad pitch for OFF event\n";
          exit(1);
        }
        e = new Event;
        e->key = 'D';
        e->time = time;
        e->v1 = (s == "DOWN") ? 1 : 0;
      } else {
        cerr << "Bad File: Unknown Key " << s << endl;
        exit(1);
      }
      el->push_back(e);
    }
    el_to_nd();
  } else if (s == "CS302-Midi-Note-File") {
    nd = new NDMap;
    el = NULL;
    while (fin >> s) {
      if (s == "NOTE") {
        if (!(fin >> pitch) || pitch < 0 || pitch > 127) {
          cerr << "Bad file: " << file << " -- bad pitch for NOTE event\n";
          exit(1);
        }
        if (!(fin >> volume) || volume <= 0 || volume > 127) {
          cerr << "Bad file: " << file << " -- bad volume for NOTE event\n";
          exit(1);
        }
        if (!(fin >> start) || start < 0) {
          cerr << "Bad file: " << file << " -- bad start for NOTE event\n";
          exit(1);
        }
        if (!(fin >> stop) || stop <= start) {
          cerr << "Bad file: " << file << " -- bad stop for NOTE event\n";
          exit(1);
        }
        n = new ND;
        n->key = 'N';
        n->pitch = pitch;
        n->volume = volume;
        n->start = start;
        n->stop = stop;
      } else if (s == "DAMPER") {
        if (!(fin >> start) || start < 0) {
          cerr << "Bad file: " << file << " -- bad start for DAMPER event\n";
          exit(1);
        }
        if (!(fin >> stop) || stop <= start) {
          cerr << "Bad file: " << file << " -- bad stop for DAMPER event\n";
          exit(1);
        }
        n = new ND;
        n->key = 'D';
        n->start = start;
        n->stop = stop;
      } else {
        cerr << "Bad File: Unknown Key " << s << endl;
        exit(1);
      }
      nd->insert(make_pair(n->start, n));
    }
    nd_to_el();
  } else {
    cerr << "Unknown file format" << s << endl;
    exit(1);
  }
}

void CS302_Midi::Add_Pause(double starttime, double duration)
{
  EventList::iterator eit;
  int ttime;
  int iduration;
  double dtime;
  Event *e;

  iduration = (duration * 480.0);

  ttime = 0;
  for (eit = el->begin(); eit != el->end(); eit++) {
    e = *eit;
    ttime += e->time;
    dtime = ((double) ttime) / 480.0;
    if (dtime >= starttime) {
      e->time += iduration;
      destroy_nd();
      el_to_nd();
      return;
    }
  }
}

void CS302_Midi::Scale(double factor)
{
  NDMap::iterator mit;
  ND *n;
  NDMap *newmap;

  newmap = new NDMap;

  while (!nd->empty()) {
    mit = nd->begin();
    n = mit->second;
    nd->erase(mit);
    n->start /= factor;
    n->stop /= factor;
    newmap->insert(make_pair(n->start, n));
  }

  delete nd;
  nd = newmap;
  destroy_el();
  nd_to_el();
}

void CS302_Midi::Write(string file, char format)
{
  FILE *f;
  EventList::iterator eit;
  NDMap::iterator nit;

  f = fopen(file.c_str(), "w");
  if (f == NULL) {
    cerr << "Could not open " << file << endl;
    exit(1);
  }
  if (format == 'E') {
    fprintf(f, "CS302-Midi-Event-File\n");
    for (eit = el->begin(); eit != el->end(); eit++) {
      Print_Event(*eit, f);
    }
  } else if (format == 'N') {
    fprintf(f, "CS302-Midi-Note-File\n");
    for (nit = nd->begin(); nit != nd->end(); nit++) {
      Print_ND(nit->second, f);
    }
  }
  fclose(f);
}
