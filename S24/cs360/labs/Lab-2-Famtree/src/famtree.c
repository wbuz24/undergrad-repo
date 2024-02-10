/* Will Buziak */
/* CS360 */
/* Lab 3 - Famtree */
/* February 2024 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "dllist.h" /* Includes jvals */
#include "jrb.h"

typedef struct person {
  char *Name;
  char *Sex; /* 'M' for male, 'F' for Female, 'U' for Unknown */
  struct person *Father;
  struct person *Mother;
  Dllist Children;
  int Visited, Kids;
} Person;

int is_ancestor(Person *mother, Person *child) {
  Dllist tmp;
  Person *p;

  p = (Person *) malloc(sizeof(Person));

  dll_traverse(tmp, mother->Children) {
    p = tmp->val.v;
    if (strcmp(p->Name, child->Name) == 0) return 1;
  }

  return 0;
}

/* Depth first search for cycle detection */
int DFS(Person *p) {
  Dllist tmp;

  //if (p->Visited == 1) return 0;
  if (p->Visited == 1) return 1;
  p->Visited = 1;

  dll_traverse(tmp, p->Children) {
    if (DFS(tmp->val.v)) return 1;
  }

  p->Visited = 0;
  return 0;
}


int main(int argc, char **argv) {
  IS is; /* Input struct */
  JRB tmp, fam;
  Dllist tmp2, order;
  Person *p, *my;
  int i, n;
  char *name;
  char *sex;

  fam = make_jrb();
  is = new_inputstruct(argv[1]);
  my = (Person *) malloc(sizeof(Person));
  sex = (char *) malloc(sizeof(char) * 10);
  order = new_dllist();
  while (get_line(is) >= 0) {
    if (is->NF > 0) {
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
          p = (Person *) malloc(sizeof(Person));
          p->Name = strdup(name);
          p->Sex = strdup("Unknown");
          p->Father = NULL;
          p->Mother = NULL;
          p->Visited = 0;
          p->Children = new_dllist();
          p->Kids = 0;
          jrb_insert_str(fam, p->Name, new_jval_v((void *) p));
          dll_append(order, new_jval_v((void *) p));
        }
        else p = (Person *) jrb_find_str(fam, name)->val.v;
          

        /* Set a pointer to the person you a currently processing */
        if (strcmp(is->fields[0], "PERSON") == 0) {
          my = p;
          my->Name = strdup(p->Name);
        }

        /* Create Father links */
        if (strcmp(is->fields[0], "FATHER") == 0) {
          if (my->Father != NULL && strcmp(p->Name, my->Father->Name) != 0) fprintf(stderr, "Bad input - parent mismatch on line %d\n", is->line);
          else {
            if (strcmp(p->Sex, "Unknown") == 0) strcpy(p->Sex, "Male");
            if (strcmp(p->Sex, "Female") == 0) fprintf(stderr, "Bad input - sex mismatch on line %d\n", is->line);
            else {
              /* Set the Father's children */
              if (is_ancestor(p, my) <= 0) {
                dll_append(p->Children, new_jval_v((void *) my));
                my->Father = p;
                p->Kids++;
              }
            }
          }
        } 

        /* Create mother links */
        if (strcmp(is->fields[0], "MOTHER") == 0) {
          if (my->Mother != NULL && strcmp(p->Name, my->Mother->Name) != 0) fprintf(stderr, "Bad input - parent %s mismatch on line %d\n", p->Name, is->line);
          else {
            if (strcmp(p->Sex, "Unknown") == 0) strcpy(p->Sex, "Female");
            if (strcmp(p->Sex, "Male") == 0) fprintf(stderr, "Bad input - %s sex mismatch on line %d\n", p->Name, is->line);
            else {
              /* Set the Mother's children */
              if (is_ancestor(p, my) <= 0) {
                my->Mother = p;
                dll_append(p->Children, new_jval_v((void *) my));
                p->Kids++;
              }
            }
          }
        }

        /* Mother or Father of my */
        if (strcmp(is->fields[0], "MOTHER_OF") == 0) {
          if (p->Mother != NULL && strcmp(p->Mother->Name, my->Name) != 0) fprintf(stderr, "Bad input - parent mismatch on line %d\n", is->line);
          else {
            if (strcmp(my->Sex, "Unknown") == 0) strcpy(my->Sex, "Female");
            if (strcmp(my->Sex, "Male") == 0) fprintf(stderr, "Bad input - sex mismatch on line %d\n", is->line);
            else {
              /* Check if p is one of my children, if not, insert it */
              if (is_ancestor(my, p) <= 0) {
                p->Mother = my;
                dll_append(my->Children, new_jval_v((void *) p));
                my->Kids++;
              }
            }
          }
        }

        if (strcmp(is->fields[0], "FATHER_OF") == 0) {
          if (p->Father != NULL && strcmp(p->Father->Name, my->Name) != 0) fprintf(stderr, "Bad input - parent mismatch on line %d\n", is->line);
          else {
            if (strcmp(my->Sex, "Unknown") == 0) strcpy(my->Sex, "Male");
            if (strcmp(my->Sex, "Female") == 0) fprintf(stderr, "Bad input - sex mismatch on line %d\n", is->line);
            else {
              /* Check if p is one of my children, if not, insert it */
              if (is_ancestor(my, p) <= 0) {
                p->Father = my;
                dll_append(my->Children, new_jval_v((void *) p));
                my->Kids++;
              }
            }
          }
        }
      }

      /* Define the sex */
      if (strcmp(is->fields[0], "SEX") == 0) {
        strcpy(sex, is->fields[1]);
        if (strcmp(sex, "F") == 0) sex = strdup("Female");
        if (strcmp(sex, "M") == 0) sex = strdup("Male");
        if (strcmp(my->Sex, "Unknown") != 0 && strcmp(my->Sex, sex) != 0) fprintf(stderr, "Bad input - sex mismatch on line %d\n", p->Name, is->line, my->Sex, sex);
        else {
          if (strcmp(sex, "Male") == 0) strcpy(my->Sex, "Male");
          if (strcmp(sex, "Female") == 0) strcpy(my->Sex, "Female");
        }
      }
    }
  }

  /* Check for cycles */
  if (DFS((Person *) fam->flink->val.v) <= 0) {
    /* Print the tree with a topological sort */
    while (!dll_empty(order)) {
      p = (Person *) order->flink->val.v;
     // if (p->Mother != NULL) printf("%s %d\n", p->Mother->Name, p->Mother->Visited);
      if (p->Visited == 0 && (p->Mother == NULL || p->Mother->Visited > 0) && (p->Father == NULL || p->Father->Visited > 0)) {
        printf("%s\n", p->Name);
        if (strcmp(p->Sex, "Unknown") != 0) printf("Sex: %s\n", p->Sex);
        else printf("Sex: Unknown\n");
        if (p->Father != NULL) printf("  Father: %s\n", p->Father->Name);
        else printf("  Father: Unknown\n");
        if (p->Mother != NULL) printf("  Mother: %s\n", p->Mother->Name);
        else printf("  Mother: Unknown\n");
        if (p->Kids <= 0) printf("  Children: None\n");
        else {
          printf("  Children:\n");
          dll_traverse(tmp2, p->Children) {
            my = (Person *) tmp2->val.v;
            printf("    %s\n", my->Name);
            dll_append(order, new_jval_v((void *) my));
          }
        }
        printf("\n");
        p->Visited = 1;
      }
      dll_delete_node(order->flink);
    }
  }
  else fprintf(stderr, "Bad input -- cycle in specification\n");

  jettison_inputstruct(is); /* Clear the memory in the input struct */

  return 0;

}
