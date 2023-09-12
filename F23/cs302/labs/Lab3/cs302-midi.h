#include <iostream>
#include <map>
#include <list>
using namespace std;

class ND {
  public:
    int key;          // 'N' for Note, or 'D' for Damper
    int pitch;        // Ignored by 'D'
    int volume;       // Ignored by 'D'
    double start;
    double stop;    
};

class Event {
   public:
     int key;         // 'O':ON, 'F':OFF, 'D':DAMPER, 
     int time;
     int v1;          // Pitch for O/F, 1 for D:DOWN, 0 for D:UP
     int v2;          // Volume for O.  Ignored for everything else.
};

typedef multimap <double, ND *> NDMap;
typedef list <Event *> EventList;

class CS302_Midi {
  public:
    CS302_Midi(string file);
    ~CS302_Midi();
    void Write(string file, char format);   // 'E' for Event, 'N' for Note
    void Add_Pause(double starttime, double duration);
    void Scale(double factor);
  protected:
    void destroy_nd();
    void destroy_el();
    void nd_to_el();
    void el_to_nd();
    NDMap *nd;
    EventList *el;
};
