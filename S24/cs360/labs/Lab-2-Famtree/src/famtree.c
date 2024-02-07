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
  struct person *Father;
  struct person *Mother;
  Dllist Children;
} Person;

int main(int argc, char **argv) {
  IS is; /* Input struct */
  JRB tmp, fam;
  Dllist tmp2;
  Person *p, *cpy;
  int i, n;
  char *name;
  char sex;

  fam = make_jrb();
  is = new_inputstruct(argv[1]);
  cpy = (Person *) malloc(sizeof(Person));
  while (get_line(is) >= 0) {
    /* Check if there is a new person */
    if (strcmp(is->fields[0], "PERSON") == 0 || strcmp(is->fields[0], "FATHER") == 0 || strcmp(is->fields[0], "MOTHER") == 0 || strcmp(is->fields[0], "FATHER_OF") == 0 || strcmp(is->fields[0], "MOTHER_OF") == 0) {
      /* Find the size of the entire name */
      n = 0;
      for (i = 1; i < is->NF; i++) n += strlen(is->fields[i]) + 1;
      
      /* Assign the person's name, including many names */
      name = (char *) malloc(sizeof(char) * (n + 1));
      strcpy(name, is->fields[1]);
      n = strlen(is->fields[1]);
      for (i = 2; i < is->NF; i++) {
        name[n] = ' ';
        strcpy(name+n+1, is->fields[i]);
        n += strlen(name+n);
      }

      /* If you cannot find the name in the JRB, insert it */
      if (jrb_find_str(fam, name) == NULL) {
        printf("New person: %s a.k.a:", name);
        printf(" %s", is->text1);
        printf("\n\n");
        p = (Person *) malloc(sizeof(Person));
        p->Name = strdup(name);
        p->Sex = 'U';
        p->Father = NULL;
        p->Mother = NULL;
        p->Children = new_dllist();
        p->Children->val = new_jval_i(0);
        jrb_insert_str(fam, p->Name, new_jval_v((void *) p));
      }
      else p = (Person *) jrb_find_str(fam, name)->val.v;

      /* Set a pointer to the person you a currently processing */
      if (strcmp(is->fields[0], "PERSON") == 0) {
        cpy = p;
        cpy->Name = strdup(p->Name);
      }

      /* Mother or Father of cp */
      if (strcmp(is->fields[0], "MOTHER_OF") == 0) {
        if (cpy->Sex == 'M') fprintf(stderr, "Specified 'Mother' when person is known as Male\n");
        else {
          cpy->Sex = 'F';
          dll_append(cpy->Children, new_jval_v((void *) p));
          cpy->Children->val.i++; 
        }
      }
      if (strcmp(is->fields[0], "FATHER_OF") == 0) {
        if (cpy->Sex == 'F') fprintf(stderr, "Specified 'Father' when person is known as Female\n");
        else {
          cpy->Sex = 'M';
          dll_append(cpy->Children, new_jval_v((void *) p));
          cpy->Children->val.i++; 
        }
      }
      /* Processing on p */
      if (strcmp(is->fields[0], "MOTHER") == 0) {
        if (p->Mother != NULL) fprintf(stderr, "Specifying two Mothers\n");
        else if (p->Sex == 'M') fprintf(stderr, "Specifying a Mother when person is known to be Male\n");
        else {
          p->Sex = 'F';
          cpy->Mother = (Person *) malloc(sizeof(Person));
          *cpy->Mother = *p;
        }
      }
      if (strcmp(is->fields[0], "FATHER") == 0) {
        if (p->Father != NULL) fprintf(stderr, "Specifying two Fathers\n");
        else if (p->Sex == 'F') fprintf(stderr, "Specifying a Father when person is known to be Female\n");
        else {
          p->Sex = 'M';
          cpy->Father = (Person *) malloc(sizeof(Person));
          *cpy->Father = *p;
        }
      } 

    }

    /* Define the sex */
    if (strcmp(is->fields[0], "SEX") == 0) {
      sscanf(is->fields[1], "%c", &sex);
      if (p->Sex != 'U' && p->Sex != sex) fprintf(stderr, "Specified '%c' when person is known as '%c'\n", sex, p->Sex);
      else p->Sex = sex;
    }
  }

  /* Print the tree */
  jrb_traverse(tmp, fam) {
    p = (Person *) tmp->val.v;
    printf("%s\n", p->Name);
    
    if (p->Sex != 'U') printf("Sex: %c\n", p->Sex);
    else printf("Sex: Unknown\n");

    if (p->Father != NULL) printf("  Father: %s\n", p->Father->Name);
    else printf("  Father: Unknown\n");
    if (p->Mother != NULL) printf("  Mother: %s\n", p->Mother->Name);
    else printf("  Mother: Unknown\n");
    if (p->Children->val.i == 0) printf("  Children: None\n");
    else {
      printf("  Children:\n");
      dll_traverse(tmp2, p->Children) {
        cpy = (Person *) tmp2->val.v;
        printf("          %s\n", cpy->Name);
      }
    }
  }

  jettison_inputstruct(is); /* Clear the memory in the input struct */
  return 0;
}
