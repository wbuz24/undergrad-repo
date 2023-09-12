#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"

main(int argc, char **argv)
{
  IS is;
  char last1[20], last2[20];
  int on[128];
  int n, i;
  double division;
  int t;
  double total, last, dt;
  FILE *f;

  if (argc != 2) {
    fprintf(stderr, "usage: jmid2mef outputfile < inputfile\n");
    exit(1);
  }
  division = 240;
  total = 0;

  f = fopen(argv[1], "w");
  if (f == NULL) { perror(argv[1]); exit(1); }
  for (i = 0; i < 128; i++) on[i] = 0;

  is = new_inputstruct(NULL);
  strcpy(last1, "");
  strcpy(last2, "");

  fprintf(f, "CS302-Midi-Event-File\n");
  total = 0;
  last = 0;
  while (get_line(is) >= 0) {
    if (is->NF == 6 && strcmp(is->fields[0], "Format:") == 0) {
      sscanf(is->fields[5], "%lf", &division);
    }
    
    if (is->NF > 0) {
       if (sscanf(is->fields[0], "%lf", &dt) == 1) {
         total += dt;
       }
    }
    if (is->NF >= 4 && strlen(is->fields[1]) < 20 && strlen(is->fields[2]) < 20 && strcmp(is->fields[1], "RSTAT") != 0) {
      strcpy(last1, is->fields[1]);
      strcpy(last2, is->fields[2]);
    } 
    if (is->NF == 4 || strcmp(is->fields[1], "RSTAT") == 0) {
      i = 2;
    } else {
      i = 3;
    }
    if (strcmp(last1, "NOTE-ON") == 0 && atoi(is->fields[i+1]) > 0) {
      t = rint((total - last) * 240.0 / division);
      last = total;
      n = atoi(is->fields[i]);
      if (!on[n]) {
        fprintf(f, "ON %d %s %s\n", t, is->fields[i], is->fields[i+1]);
      }
      on[n] = 1;
    } else if (strcmp(last1, "NOTE-OFF") == 0 || strcmp(last1, "NOTE-ON") == 0) {
      t = rint((total - last) * 240.0 / division);
      last = total;
      n = atoi(is->fields[i]);
      if (on[n]) {
        fprintf(f, "OFF %d %s\n", t, is->fields[i]);
      }
      on[n] = 0;
    } else if (strcmp(last1, "CONTROL") == 0 && atoi(is->fields[i]) == 64) {
      t = rint((total - last) * 240.0 / division);
      last = total;
      fprintf(f, "DAMPER %d %s\n", t, (atoi(is->fields[i+1]) == 0 ? "UP" : "DOWN"));
    }
  }
  fclose(f);
  exit(0);
}
