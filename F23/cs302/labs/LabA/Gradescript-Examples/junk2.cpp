#include <iostream>
using namespace std;

main()
{ int r;
  int i;
  int c;
  int ndiff;
  int v1, v2, v3, v4, v5;
  int nleft, schar;
 
  cin >> v1 >> v2 >> v3 >> v4 >> v5;

  r = (v1%35)+5; 
  c = (v2%35)+5; 
  ndiff = (v3%5) + 1 + (r*c)/100;
  if (ndiff == 1) ndiff = 2;
  printf("../spellgen %d %d %d | tr ", r, c, ndiff);
  for (i = 0; i < ndiff; i++) printf("%c", 'A'+i);
  if (ndiff <= 10) {
    v4 = v4 % 3;
  } else {
    v4 = v4 % 2;
  }
  if (v4 == 2) {
    nleft = 10-ndiff+1;
    schar = '0' + v5%nleft;
  } else {
    nleft = 26-ndiff+1;
    schar = 'A' + v5%nleft;
    if (v4) schar += ('a' - 'A');
  }
  printf(" ");
  for (i = 0; i < ndiff; i++) printf("%c", schar + i);
  printf("\n");
}

