/* Will Buziak
 * CS360
 * Fakemake
 * February 2024
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "dllist.h"

int main(int argc, char **argv) {
  IS is;
  FILE *def, *output;
  Dllist clist, hlist, tmp, htmp;
  char *filename;
  int i;

  /* Grab definition file from command line */
  if (argc != 2) {
    filename = strdup("fmakefile");
  }
  else filename = strdup(argv[1]);

  def = fopen(filename, "r");

  /* Check existence of definition file */
  if (def == NULL) {
    printf("fakemake: %s No such file or directory\n", filename);
    return 0; 
  }

  /* Open the output makefile */
  //  output = fopen("makefile", "w");

  /* Input struct declaration */
  is = new_inputstruct(filename);

  clist = new_dllist();
  hlist = new_dllist();
  while(get_line(is) >= 0) {
    if (is->NF <= 0) {
      //      printf("blank line \n");
    }
    else {
      /* Grab C lines */
      if (strcmp(is->fields[0], "C") == 0) {
        for (i = 1; i < is->NF; i++) {
          printf("%s\n", is->fields[1]);
          dll_append(clist, new_jval_s(strdup(is->fields[i])));
        }
      }
      /* Grab H lines */
      if (strcmp(is->fields[0], "H") == 0) {
        for (i = 1; i < is->NF; i++) {
          printf("%s\n", is->fields[1]);
          dll_append(hlist, new_jval_s(strdup(is->fields[i])));
        }
      }
    }
  } 

  /* Traverse the dllist */
  dll_traverse(tmp, clist) printf("%s ", tmp->val.s);
  printf("\n");
  dll_traverse(htmp, hlist) printf("%s ", htmp->val.s);
  printf("\n");

  jettison_inputstruct(is);
  //  fclose(output);
  fclose(def);

}
