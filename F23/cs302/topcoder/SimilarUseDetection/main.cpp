#include "SimilarUserDetection.cpp"

int main(int argc, char **argv)
{
  int i;
  class SimilarUserDetection TheClass;
  string retval, s;
  vector <string> handles;

  if (argc != 2) { fprintf(stderr, "usage: a.out num (or - to enter the vector on stdin)\n"); exit(1); }

  if (((string) argv[1]) == "-") {
    while (cin >> s) handles.push_back(s);
  } else {

    if (atoi(argv[1]) == 0) {
      handles.push_back("top");
      handles.push_back("coder");
      handles.push_back("TOPCODER");
      handles.push_back("TOPC0DER");
    }
  
    if (atoi(argv[1]) == 1) {
      handles.push_back("Topcoder");
      handles.push_back("topcoder");
      handles.push_back("t0pcoder");
      handles.push_back("topcOder");
    }
  
    if (atoi(argv[1]) == 2) {
      handles.push_back("same");
      handles.push_back("same");
      handles.push_back("same");
      handles.push_back("d ifferent");
    }
  
    if (atoi(argv[1]) == 3) {
      handles.push_back("0123");
      handles.push_back("0I23");
      handles.push_back("0l23");
      handles.push_back("O123");
      handles.push_back("OI23");
      handles.push_back("Ol23");
    }
  
    if (atoi(argv[1]) == 4) {
      handles.push_back("i23");
      handles.push_back("123");
      handles.push_back("456");
      handles.push_back("789");
      handles.push_back("000");
      handles.push_back("o");
      handles.push_back("O");
    }
  }

  retval = TheClass.haveSimilar(handles);
  cout << retval << endl;

  exit(0);
}

