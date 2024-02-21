/* Will Buziak
 * CS360
 * Fakemake
 * February 2024
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include "fields.h"
#include "dllist.h"

long cProcess(Dllist clist, long hmax) {
	Dllist tmp;
	struct stat buf;
	int exists;
	DIR *d;
	struct dirent *de;

  /* Check and open the directory */
	d = opendir(".");
	if (d == NULL) {
		fprintf(stderr, "Couldn't open \".\"\n");
		exit(0);
	}

	/* Traverse the Dllist and check that each file exists */
	dll_traverse(tmp, clist) {
		exists = stat(tmp->val.s, &buf);
		if (exists < 0) fprintf(stderr, "%s not found\n");
		else {
			/* Search for the .o file */
			
			/* If .o doesn't exist or less recent than c file, remake it */
		}
	}
	closedir(d);
	return 0;
}

/* Check that each header exists and return maximum st_mtime */
long hProcess(Dllist hlist) {
	long max;
	Dllist tmp;
	struct stat buf;
	int exists;

  max = 0;
	dll_traverse(tmp, hlist) {
		exists = stat(tmp->val.s, &buf);
		if (exists < 0) fprintf(stderr, "%s not found\n", tmp->val.s);
		else {
			if (buf.st_mtime > max) max = buf.st_mtime;
		}	
	}

  return max;
}

/* Grab all words from the line and return the dllist */
Dllist listAppend(Dllist list, IS is) {
  int i;

  for (i = 1; i < is->NF; i++) dll_append(list, new_jval_s(strdup(is->fields[i])));

	return list;
}

int main(int argc, char **argv) {
  IS is;
  FILE *def, *output;
  Dllist clist, hlist, llist, flist, tmp;
  char *filename, *executable;
  int i, exec;
	long hmax;

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
  llist = new_dllist();
  flist = new_dllist();
	exec = 0;
  while(get_line(is) >= 0) {
    if (is->NF <= 0) {
      //      printf("blank line \n");
    }
    else {
			/* E line - Executable name */
			if (strcmp(is->fields[0], "E") == 0) {
				if (is->NF > 1) executable = strdup(is->fields[1]); 
				exec++;
			}

      /* Grab C lines - C code files */
      if (strcmp(is->fields[0], "C") == 0) clist = listAppend(clist, is);
      /* Grab H lines - header files */
      if (strcmp(is->fields[0], "H") == 0) hlist = listAppend(hlist, is);
			/* L lines - libraries */
			if (strcmp(is->fields[0], "L") == 0) llist = listAppend(llist, is); 
			/* F lines - flags */
			if (strcmp(is->fields[0], "F") == 0) flist = listAppend(flist, is); 
    }
  } 

  hmax = 0;
  hmax = hProcess(hlist);

	if (exec != 1) printf("Executable error\n"); 
	else printf("E: %s\n\n", executable);

  /* Traverse the dllist */
  dll_traverse(tmp, clist) printf("C: %s\n", tmp->val.s);
  printf("\n");
  dll_traverse(tmp, hlist) printf("H: %s\n", tmp->val.s);
  printf("Hmax: %li\n\n", hmax);
  dll_traverse(tmp, llist) printf("L: %s\n", tmp->val.s);
  printf("\n");
  dll_traverse(tmp, flist) printf("F: %s\n", tmp->val.s);
  printf("\n");

  jettison_inputstruct(is);
  //  fclose(output);
  fclose(def);

}
