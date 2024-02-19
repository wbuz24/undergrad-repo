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
  Dllist clist, tmp;
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
  output = fopen("makefile", "w");

  /* Input struct declaration */
  is = new_inputstruct(filename);

  clist = new_dllist();
  while(get_line(is) >= 0) {
    if (is->NF <= 0) {
//      printf("blank line \n");
    }
    /* Grab C lines */
    if (strcmp(is->fields[0], "C") == 0) {
      printf("%s\n", is->text1);
      for (i = 1; i < is->NF; i++) dll_append(clist, new_jval_s(is->fields[i]));
    }
  } 

  /* Traverse the dllist */
  dll_traverse(tmp, clist) printf("%s", tmp->val.s);

  jettison_inputstruct(is);
  fclose(output);
  fclose(def);

}
