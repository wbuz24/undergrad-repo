/* Will Buziak
 * CS360
 * Fakemake
 * February 2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include "fields.h"
#include "dllist.h"

/* Make an executable file */
void makeExec(char *executable, long ctime, Dllist clist) {
	int exists;
	long etime;
  int exec;
	struct stat buf;
	char command[1000], cname[1000];
  Dllist tmp;

  /* Check if the executable file exists */
	exists = stat(executable, &buf);
  exec = 0;

  /* gcc -o twoexec twofile.o threefile.o */

  /* Create the gcc command and append the executable name */
	strcpy(command, "gcc -o ");
	strcat(command, executable);

  dll_traverse(tmp, clist) {
	  strcat(cname, " ");
    strcat(cname, tmp->val.s);  
    cname[strlen(cname) - 1] = 'o';
  }

  /* append each .o file to the gcc command */
	strcat(command, cname);

	/* Does not exist, make it */
	if (exists < 0) {
    exec = 1;
    printf("%s\n", command);
    system(command);
  }
	else {
		/* Executable already exists, if it is older, remake it */
		etime = buf.st_mtime;

//    printf("e: %lld c: %lld\n", etime, ctime);
		if (etime < ctime) {
      exec = 1;
      printf("%s\n", command);
      system(command);
    }
	}

  /* Executable exists and is up to date */
  if (!exec) printf("%s up to date\n", executable);
}

void makeO(char file[]) {
	/* Make the .o file from the .c file */
	char oFile[1000];

  /* Create the string */
	strcpy(oFile, "gcc -c ");
	strcat(oFile, file);

  printf("%s\n", oFile);

	system(oFile);
}

/* Process all C lines */
long cProcess(Dllist clist, long hmax) {
	Dllist tmp;
	struct stat buf, buf1;
	int exists, oex;
	long ctime, otime, ret, omax;
	DIR *d;
	struct dirent *de;
	char fname[1000];

  /* Check and open the directory */
	d = opendir(".");
	if (d == NULL) {
		fprintf(stderr, "Couldn't open \".\"\n");
    return 0;
	}

	ret = 0;
  omax = 0;
	/* Traverse the Dllist and check that each .c file exists */
	dll_traverse(tmp, clist) {
		exists = stat(tmp->val.s, &buf);
		if (exists < 0) fprintf(stderr, "%s does not exist\n", tmp->val.s); 
		/* Process each .o file */
		else {
			ctime = buf.st_mtime;

			/* Grab the first part of the name before .o */
			strcpy(fname, tmp->val.s);
			fname[strlen(fname) - 1] = 'o';
			oex = stat(fname, &buf1);

			/* If .o doesn't exist remake it */
			if (oex < 0) {
				makeO(tmp->val.s); 
				ret++;
			}
			else {
				/* If the o file is older than the .c file */
				otime = buf1.st_mtime;
        if (otime > omax) omax = otime;
				if (otime < ctime || otime < hmax) {
					makeO(tmp->val.s); 
					ret++;
				}
			}
		}
	}
	if (ret == 0) ret = omax;
	closedir(d);
	return ret;
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
		if (exists < 0) { fprintf(stderr, "%s not found\n", tmp->val.s); exit(0); }
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
  FILE *def;
  Dllist clist, hlist, llist, flist, tmp;
  char *filename, *executable;
  int i, exec;
	long hmax, cmax;

  /* Grab definition file from command line */
  if (argc != 2) {
    filename = strdup("fmakefile");
  }
  else filename = strdup(argv[1]);

  def = fopen(filename, "r");

  /* Check existence of definition file */
  if (def == NULL) {
    printf("fakemake: %s No such file or directory\n", filename);
    exit(1); 
  }

  /* Input struct declaration */
  is = new_inputstruct(filename);

  clist = new_dllist();
  hlist = new_dllist();
  llist = new_dllist();
  flist = new_dllist();
	exec = 0;
  while(get_line(is) >= 0) {
    if (is->NF <= 0) {
      //  printf("blank line \n");
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
	if (!exec) {
    fprintf(stderr, "No executable specified\n"); 
    exit(1);
  }
	else {
    hmax = 0;
    hmax = hProcess(hlist);

  	cmax = 0;
  	cmax = cProcess(clist, hmax);

    makeExec(executable, cmax, clist);

    free(executable);
  }

  jettison_inputstruct(is);
  //  fclose(output);
  fclose(def);
	free(filename);
}
