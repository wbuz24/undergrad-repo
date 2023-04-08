#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define VIT(i, v) for (i = 0; i < v.size(); i++) 
#define IT(it, ds) for (it = ds.begin(); it != ds.end(); it++)
#define FUP(i, n) for (i = 0; i < n; i++)

static string keys[757] = { "Aaa", "Aau", "Aba", "Abc", "Abe", "Abo", "Ace", "Acm", "Acs", "Act",
"Ada", "Add", "Ado", "Aft", "Age", "Ago", "Aid", "Ail", "Aim", "Air", "Ala", "Alb", "Ale", "Ali",
"All", "Alp", "Ama", "Ami", "Amp", "Amy", "Amo", "Ana", "And", "Ani", "Ann", "Ant", "Any", "Ape",
"Apr", "Aps", "Apt", "Arc", "Are", "Ark", "Arm", "Art", "Ash", "Ask", "Ass", "Ate", "Aug", "Auk",
"Ave", "Awe", "Awl", "Awn", "Axe", "Aye", "Bad", "Bag", "Bah", "Bam", "Ban", "Bar", "Bat", "Bay",
"Bed", "Bee", "Beg", "Bel", "Ben", "Bet", "Bey", "Bib", "Bid", "Big", "Bin", "Bit", "Biz", "Bmw",
"Boa", "Bob", "Bog", "Bon", "Boo", "Bop", "Bow", "Box", "Boy", "Btl", "Btu", "Bub", "Bud", "Bug",
"Bum", "Bun", "Bus", "But", "Buy", "Bye", "Cab", "Cal", "Cam", "Can", "Cap", "Car", "Cat", "Caw",
"Cbs", "Cdc", "Ceq", "Chi", "Cia", "Cit", "Cod", "Cog", "Col", "Con", "Coo", "Cop", "Cos", "Cot",
"Cow", "Cox", "Coy", "Cpa", "Cpu", "Crt", "Cry", "Cub", "Cud", "Cue", "Cup", "Cur", "Cut", "Dab",
"Dad", "Dam", "Dan", "Dar", "Day", "Dec", "Dee", "Del", "Den", "Des", "Dew", "Dey", "Did", "Die",
"Dig", "Dim", "Din", "Dip", "Dis", "Dna", "Dod", "Doe", "Dog", "Don", "Dot", "Dow", "Dry", "Dub",
"Dud", "Due", "Dug", "Dun", "Dye", "Ear", "Eat", "Ebb", "Edt", "Eel", "Eft", "Egg", "Ego", "Eke",
"Eli", "Elk", "Ell", "Elm", "Ely", "End", "Eng", "Epa", "Era", "Ere", "Erg", "Err", "Est", "Eta",
"Etc", "Eva", "Eve", "Ewe", "Eye", "Faa", "Fad", "Fag", "Fan", "Far", "Fat", "Fay", "Fbi", "Fcc",
"Fda", "Feb", "Fed", "Fee", "Few", "Fib", "Fig", "Fin", "Fir", "Fit", "Fix", "Flo", "Flu", "Fly",
"Fmc", "Fob", "Foe", "Fog", "Fop", "For", "Fox", "Fpc", "Fro", "Fry", "Ftc", "Fum", "Fun", "Fur",
"Gab", "Gad", "Gag", "Gal", "Gam", "Gao", "Gap", "Gar", "Gas", "Gay", "Gee", "Gel", "Gem", "Get",
"Gig", "Gil", "Gin", "Gmt", "Gnp", "Gnu", "Goa", "Gob", "God", "Gog", "Gop", "Got", "Gpo", "Gsa",
"Gum", "Gun", "Gus", "Gut", "Guy", "Gym", "Gyp", "Had", "Hal", "Ham", "Han", "Hap", "Hat", "Haw",
"Hay", "Hem", "Hen", "Her", "Hew", "Hex", "Hey", "Hid", "Him", "Hip", "His", "Hit", "Hob", "Hoc",
"Hoe", "Hog", "Hoi", "Hom", "Hop", "Hot", "How", "Hoy", "Hub", "Hue", "Hug", "Huh", "Hum", "Hun",
"Hut", "Ian", "Ibm", "Ibn", "Icc", "Ice", "Icy", "Ida", "Iii", "Ike", "Ill", "Imp", "Inc", "Ink",
"Inn", "Ion", "Ira", "Ire", "Irk", "Irs", "Ito", "Itt", "Ivy", "Jab", "Jag", "Jam", "Jan", "Jar",
"Jaw", "Jay", "Jed", "Jet", "Jew", "Jig", "Jim", "Job", "Joe", "Jog", "Jon", "Jot", "Joy", "Jug",
"Jut", "Kay", "Keg", "Ken", "Key", "Kid", "Kim", "Kin", "Kit", "Lab", "Lac", "Lad", "Lag", "Lam",
"Lao", "Lap", "Law", "Lax", "Lay", "Lea", "Led", "Lee", "Leg", "Len", "Leo", "Let", "Lev", "Lez",
"Lew", "Lid", "Lie", "Lim", "Lin", "Lip", "Lit", "Liz", "Lob", "Log", "Lop", "Los", "Lot", "Lou",
"Low", "Loy", "Lsi", "Ltd", "Ltv", "Lug", "Lux", "Lye", "Mac", "Mad", "Mae", "Man", "Mao", "Map",
"Mar", "Mat", "Maw", "Maz", "Max", "May", "Mba", "Meg", "Mel", "Men", "Met", "Mew", "Mid", "Mig",
"Min", "Mit", "Mix", "Mob", "Moe", "Moo", "Mop", "Mot", "Mow", "Mph", "Mrs", "Mud", "Mug", "Mum",
"Nab", "Nag", "Nan", "Nap", "Nat", "Nay", "Nbc", "Nbs", "Nco", "Ncr", "Ned", "Nee", "Net", "New",
"Nib", "Nih", "Nil", "Nip", "Nit", "Nne", "Nnw", "Nob", "Nod", "Non", "Nor", "Not", "Nov", "Now",
"Nrc", "Nsf", "Nun", "Nut", "Nyc", "Nyu", "Oaf", "Oak", "Oar", "Oat", "Oct", "Odd", "Ode", "Off",
"Oft", "Ohm", "Oil", "Old", "One", "Opt", "Orb", "Ore", "Orr", "Ott", "Our", "Out", "Ova", "Owe",
"Owl", "Own", "Pad", "Pal", "Pam", "Pan", "Pap", "Par", "Pat", "Paw", "Pax", "Pay", "Paz", "Pbs",
"Pdp", "Pea", "Pee", "Peg", "Pen", "Pep", "Per", "Pet", "Pew", "Phd", "Phi", "Pie", "Pig", "Pin",
"Pip", "Pit", "Ply", "Pod", "Poe", "Poi", "Pol", "Pop", "Pot", "Pow", "Ppm", "Pro", "Pry", "Psi",
"Pta", "Pub", "Puc", "Pug", "Pun", "Pup", "Pus", "Put", "Pvc", "Qed", "Qua", "Quo", "Rae", "Rag",
"Raj", "Ram", "Ran", "Rap", "Rat", "Raw", "Ray", "Rca", "Reb", "Red", "Rep", "Ret", "Rev", "Rex",
"Rho", "Rib", "Rid", "Rig", "Rim", "Rio", "Rip", "Rna", "Rob", "Rod", "Roe", "Ron", "Rot", "Row",
"Roy", "Rpm", "Rub", "Rue", "Rug", "Rum", "Run", "Rut", "Rye", "Sac", "Sad", "Sag", "Sal", "Sam",
"San", "Sao", "Sap", "Sat", "Saw", "Sax", "Say", "Sci", "Scm", "Sea", "Sec", "See", "Sen", "Seq",
"Set", "Sew", "Sex", "She", "Shu", "Shy", "Sib", "Sic", "Sin", "Sip", "Sir", "Sis", "Sit", "Six",
"Ski", "Sky", "Sly", "Sob", "Soc", "Sod", "Sol", "Son", "Sop", "Sou", "Sow", "Soy", "Spa", "Spy",
"Sri", "Sse", "Sst", "Ssw", "Stu", "Sub", "Sud", "Sue", "Sum", "Sun", "Sup", "Sus", "Tab", "Tad",
"Tag", "Tam", "Tan", "Tao", "Tap", "Tar", "Tat", "Tau", "Tax", "Tea", "Tef", "Ted", "Tee", "Tel",
"Ten", "The", "Thy", "Tic", "Tid", "Tie", "Til", "Tim", "Tin", "Tip", "Tit", "Tnt", "Toe", "Tog",
"Tom", "Ton", "Too", "Top", "Tor", "Tot", "Tow", "Toy", "Trw", "Try", "Ttl", "Tty", "Tub", "Tug",
"Tum", "Tun", "Tva", "Twa", "Two", "Twx", "Ugh", "Uhf", "Uri", "Urn", "Usa", "USC", "Use", "Usn",
"Van", "Vat", "Vee", "Vet", "Vex", "Vhf", "Via", "Vie", "Vii", "Vis", "Viz", "Von", "Vow", "Wac",
"Wad", "Wag", "Wah", "Wan", "War", "Was", "Wax", "Way", "Web", "Wed", "Wee", "Wei", "Wet", "Who",
"Why", "Wig", "Win", "Wit", "Woe", "Wok", "Won", "Woo", "Wop", "Wow", "Wry", "Yah", "Yak", "Yam",
"Yap", "Yaw", "Yea", "Yen", "Yet", "Yin", "Yip", "Yon", "You", "Yow", "Yuh", "Zag", "Zan", "Zap",
"Zen", "Zig", "Zip", "Zoe", "Zoo" };

class KeyGen {
public:
  KeyGen();
  string random_new_key();
  string random_old_key();
  void print_old();
  void old_to_new(string s);
  void new_to_old(string s);
  map <string, int> oldmap;
  vector <string> oldvec;
  map <string, int> newmap;
  vector <string> newvec;
};

int seed;

void KeyGen::print_old()
{
  int i;
  printf("# %d %d -", (int) oldvec.size(), (int) oldmap.size());
  VIT(i, oldvec) printf(" %s", oldvec[i].c_str());
  printf("\n");
  fflush(stdout);
}
  
KeyGen::KeyGen()
{
  int i;

  srand48(seed);

  for (i = 0; i < 757; i++) {
    if (newmap.find(keys[i]) != newmap.end()) {
      printf("%s\n", keys[i].c_str());
      exit(1);
    }
    newmap[keys[i]] = i;
    newvec.push_back(keys[i]);
  }
}

string KeyGen::random_old_key()
{
  if (oldvec.size() == 0) return "";
  return oldvec[lrand48()%oldvec.size()];
}
  
string KeyGen::random_new_key()
{
  if (newvec.size() == 0) return "";
  return newvec[lrand48()%newvec.size()];
}
  
void KeyGen::old_to_new(string s)
{
  int i, sz, index;
  map <string, int>::iterator oit;
  
/*  printf("# OTN BEFORE: %s %d %d %d %d\n", s.c_str(), (int) oldmap.size(), (int) oldvec.size(),
    (int) newmap.size(), (int) newvec.size()); */
  oit = oldmap.find(s);
  if (oit == oldmap.end()) { cerr << "Problems old_to_new\n"; exit(1); }
  newmap[s] = newvec.size();
  newvec.push_back(s);
  sz = oldvec.size()-1;
  index = oit->second;
  oldvec[index] = oldvec[sz];
  oldmap[oldvec[index]] = index;
  oldvec.pop_back();
  oldmap.erase(oit);
/*  printf("# OTN  AFTER: %s %d %d %d %d\n", s.c_str(), (int) oldmap.size(),
    (int) oldvec.size(), (int) newmap.size(), (int) newvec.size()); */

  
}

void KeyGen::new_to_old(string s)
{
  int i, sz, index;
  map <string, int>::iterator oit;
  
/*  printf("# NTO BEFORE: %s %d %d %d %d\n", s.c_str(), (int) oldmap.size(),
    (int) oldvec.size(), (int) newmap.size(), (int) newvec.size()); */
  oit = newmap.find(s);
  if (oit == newmap.end()) { cerr << "Problems new_to_old\n"; exit(1); }
  oldmap[s] = oldvec.size();
  oldvec.push_back(s);
  sz = newvec.size()-1;
  index = oit->second;
  newvec[index] = newvec[sz];
  newmap[newvec[index]] = index;
  newvec.pop_back();
  newmap.erase(oit);
/*  printf("# NTO  AFTER: %s %d %d %d %d\n", s.c_str(), (int) oldmap.size(),
    (int) oldvec.size(), (int) newmap.size(), (int) newvec.size()); */
}

typedef list <string>::iterator Lit;

int main(int argc, char **argv)
{
  int e, ne, lp, le, ls;
  string s, s2;
  int rn;
  list <string> l;
  map <string, Lit> its;
  Lit lit;

  if (argc != 3) { cerr << "usage: rinp nevents seed(-1)\n"; exit(1); }
  ne = atoi(argv[1]);
  seed = atoi(argv[2]);
  if (seed == -1) seed = time(0);
  KeyGen kg;

  lp = -2;
  le = -2;
  ls = -2;

  for (e = 0; e < ne; e++) {
    /* printf("# %d", e);
    IT(lit, l) cout << " " << *lit;
    printf("\n"); 
    fflush(stdout);
    kg.print_old(); */
    rn = drand48()*100;
    if (rn < 4) {
      if (l.empty()) {
        e--; 
      } else {
        printf("%s\n", (rn < 2) ? "CLEAR" : "DESTROY");
        while (!l.empty()) {
          kg.old_to_new(*(l.begin()));
          l.erase(l.begin());
        }
      }
    } else if (rn < 10) {
      if (lp == e-1) {
        e--;
      } else {
        printf("PRINT_FORWARD\n");
        lp = e;
      }
    } else if (rn < 12) {
      if (lp == e-1) {
        e--;
      } else {
        printf("PRINT_COPY\n");
        lp = e;
      }
    } else if (rn < 20) {
      if (lp == e-1) {
        e--;
      } else {
        printf("PRINT_REVERSE\n");
        lp = e;
      }
    } else if (rn < 44) {
      s = kg.random_new_key();
      if (s == "") {
        e--;
      } else {
        kg.new_to_old(s);
        if (rn < 32) {
          printf("PUSH_BACK %s\n", s.c_str());
          l.push_back(s);
          lit = l.end();
          lit--;
          its[s] = lit;
        } else {
          printf("PUSH_FRONT %s\n", s.c_str());
          l.push_front(s);
          its[s] = l.begin();
        }
      }
    } else if (rn < 52) {
      if (l.size() == 0) {
        e--;
      } else {
        s = *(l.begin());
        printf("POP_FRONT\n");
        l.erase(its[s]);
        kg.old_to_new(s);
      }
    } else if (rn < 60) {
      if (l.size() == 0) {
        e--;
      } else {
        s = *(l.rbegin());
        printf("POP_BACK\n");
        l.erase(its[s]);
        kg.old_to_new(s);
      }
    } else if (rn < 68) {
      if (l.size() == 0) {
        e--;
      } else {
        s = kg.random_old_key();
        l.erase(its[s]);
        kg.old_to_new(s);
        printf("ERASE %s\n", s.c_str());
      }
    } else if (rn < 92) {
      s = kg.random_new_key();
      if (l.size() == 0 || s == "") {
        e--;
      } else {
        s2 = kg.random_old_key();
/*        printf("# INS %s %s\n", s.c_str(), s2.c_str()); fflush(stdout); */
        kg.new_to_old(s);
        lit = its[s2];
        if (rn < 80) {
          printf("INSERT_BEFORE %s %s\n", s.c_str(), s2.c_str());
          l.insert(lit, s);
          lit--;
        } else {
          printf("INSERT_AFTER %s %s\n", s.c_str(), s2.c_str());
          lit++;
          l.insert(lit, s);
          lit--;
        }
        its[s] = lit;
      }
    } else if (rn < 94) {
      printf("AO\n");
    } else if (rn < 96) {
      if (e-1 == le) {
        e--;
      } else {
        printf("EMPTY\n");
        le = e;
      }
    } else {
      if (e-1 == ls) {
        e--;
      } else {
        printf("SIZE\n");
        ls = e;
      }
    }
    fflush(stdout);
  }
  if (e-1 != lp) printf("PRINT_FORWARD\n");
  return 0;
}


/*
2 2 CLEAR
4 2 DESTROY
10 6 PRINT_FORWARD
12 2 PRINT_COPY
20 8 PRINT_REVERSE
32 12 PUSH_BACK s
44 12 PUSH_FRONT s
52 8 POP_BACK s
60 8 POP_FRONT s
68 8 ERASE s
80 12 INSERT_BEFORE s1 s2
92 12 INSERT_AFTER s1 s2
94 2 AO
96 2 EMPTY
100 4 SIZE
*/
