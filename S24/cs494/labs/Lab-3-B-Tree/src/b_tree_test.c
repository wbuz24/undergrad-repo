#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "b_tree.h"

#define BUFSIZE 4000

void usage(char *s)
{
  fprintf(stderr, "usage: b_tree_test file [CREATE file_size key_size]\n");
  if (s != NULL) fprintf(stderr, "%s\n", s);
  exit(1);
}

int main(int argc, char **argv)
{
  void *bp, *jd;
  int key_size, record_size, m, i;
  unsigned long file_size;
  unsigned int lba;
  char line[BUFSIZE];
  char fi[BUFSIZE];
  char key[BUFSIZE];
  char val[BUFSIZE];

  if (argc != 2 && argc != 5) usage(NULL);
  if (argc == 5) {
    if (strcmp(argv[2], "CREATE") != 0) usage(NULL);
    key_size = atoi(argv[4]);
    record_size = JDISK_SECTOR_SIZE;
    if (key_size < 4 || key_size > 254) usage("key_size must be between 4 and 254\n");
    if (sscanf(argv[3], "%lu", &file_size) != 1 || file_size == 0 ||
        file_size % JDISK_SECTOR_SIZE != 0) {
      usage("bad file size.\n");
    }
    bp = b_tree_create(argv[1], file_size, key_size);
    if (bp == NULL) {
      fprintf(stderr, "Couldn't create b_tree -- calling perror()\n");
      perror(argv[1]);
      exit(1);
    }
    jd = b_tree_disk(bp);
  } else {
    bp = b_tree_attach(argv[1]);
    if (bp == NULL) {
      fprintf(stderr, "Couldn't attach to %s.  Calling perror().\n", argv[1]);
      perror(argv[1]);
      exit(1);
    }
    jd = b_tree_disk(bp);
    key_size = b_tree_key_size(bp);
    printf("Attached to %s.  FS: %lu  -  KS: %d\n", argv[1], jdisk_size(jd), key_size);
  }
  while (fgets((char *) line, BUFSIZE, stdin) != NULL) {
    m = sscanf(line, "%s %s %s", fi, key, val);
    if (m == 0) {
    } else if ((m == 1 && strcmp(fi, "P") != 0) 
                      || (m == 2 && strcmp(fi, "F") != 0)
                      || (m == 3 && strcmp(fi, "I") != 0)) {
      printf("Line must be 'I key val' or 'F key'\n");
    } else if (strcmp(fi, "P") == 0) {
       b_tree_print_tree(bp);
    } else if (strcmp(fi, "I") == 0) {
      if (strlen(key) > key_size) {
        printf("Key too big\n");
      } else if (strlen(val) > JDISK_SECTOR_SIZE) {
        printf("Val too big\n");
      } else {
        for (i = strlen(key); i < key_size; i++) key[i] = '\0';
        for (i = strlen(val); i < JDISK_SECTOR_SIZE; i++) val[i] = '\0';
        lba = b_tree_insert(bp, key, val);
        printf("Insert return value: %u\n", lba);
      }
    } else {
      if (strlen(key) > key_size) {
        printf("Key too big\n");
      } else {
        for (i = strlen(key); i < key_size; i++) key[i] = '\0';
        lba = b_tree_find(bp, key);
        printf("Find return value: %d\n", lba);
      }
    }
  }

  printf("Reads: %ld\n", jdisk_reads(jd));
  printf("Writes: %ld\n", jdisk_writes(jd));
      
  exit(0);
}
