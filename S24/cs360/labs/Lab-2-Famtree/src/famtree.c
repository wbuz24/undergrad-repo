/* Will Buziak */
/* CS360 */
/* Lab 3 - Famtree */
/* February 2024 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "dllist.h" /* Includes jvals */
#include "jrb.h"

typedef struct person {
  char *Name;
  char Sex; /* 'M' for male, 'F' for Female, 'U' for Unknown */
  struct person *Parents[2]; /* Father = Parents[0], Mother = Parents[1] */
  struct person **Children;
} Person;

int main(int argc, char** argv) {
  IS is; /* Input struct */
  JRB fam;
  Person *p;
  int i, n;

  fam = make_jrb();
  is = new_inputstruct(argv[1]);
  while (get_line(is) >= 0) {
    /* Check if there is a new person */
    if (strcmp(is->fields[0], "PERSON") == 0) {
      p = (Person *) malloc(sizeof(Person));
      n = 0;
      for (i = 1; i < is->NF; i++) n += strlen(is->fields[i]) + 1;
      
      /* Assign the person's name, including many names */
      p->Name = (char *) malloc(sizeof(char) * (n + 1));
      strcpy(p->Name, is->fields[1]);
      n = strlen(is->fields[1]);
      for (i = 2; i < is->NF; i++) {
        p->Name[n] = ' ';
        strcpy(p->Name+n+1, is->fields[i]);
        n += strlen(p->Name+n);
      }
      p->Sex = 'U';
      jrb_insert_str(fam, p->Name, new_jval_v((void *) p));
    }

    /* Define the sex */
    if (strcmp(is->fields[0], "SEX") == 0) {
      sscanf(is->fields[1], "%c", &p->Sex);
    }
  }

  jettison_inputstruct(is); /* Clear the memory in the input struct */
  return 0;
}
