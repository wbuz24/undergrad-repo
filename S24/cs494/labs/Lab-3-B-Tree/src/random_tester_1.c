#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "b_tree.h"
#include "jrb.h"

void usage(char *s)
{
  fprintf(stderr, "usage: random_tester_1 seed nevents key_size val_size tree_file input_file output_file\n");
  if (s != NULL) fprintf(stderr, "%s\n", s);
  exit(1);
}

typedef struct {
  char *key;
  char *val;
  double rn;
  unsigned int lba;
  JRB dtree_ptr;
} Entry;

int main(int argc, char **argv)
{
  int nevents;
  int key_size;
  char *fn;
  long seed;
  struct stat sbuf;
  void *t;
  void *jd;
  char *ifn, *ofn;
  JRB random_tree, key_tree, tmp, tmp2;
  unsigned int lba;
  int ts;
  double d;
  int ks, vs, i, j, val_size;
  Entry *e, *e2;
  char val[JDISK_SECTOR_SIZE+1];
  char buf[JDISK_SECTOR_SIZE*2];
  char key[300];
  FILE *f;

  if (argc != 8) usage(NULL);
  if (sscanf(argv[1], "%ld", &seed) == 0) usage("Bad Seed");
  if (sscanf(argv[2], "%d", &nevents) == 0) usage("Bad Seed");
  if (sscanf(argv[3], "%d", &key_size) == 0) usage("Bad Key Size");
  if (sscanf(argv[4], "%d", &val_size) == 0) usage("Bad Val Size");
  fn = argv[5];
  ifn = argv[6];
  ofn = argv[7];
  srand48(seed);

  if (stat(fn, &sbuf) == 0) {
    t = b_tree_attach(fn);
    if (t == NULL) { perror(fn); exit(1); }
    if (b_tree_key_size(t) != key_size) {
      fprintf(stderr, "Error -- key_size (%d) doesn't match key_size in the file (%d)\n", 
        key_size, b_tree_key_size(t));
      exit(1);
    }
  } else {
    t = b_tree_create(fn, JDISK_SECTOR_SIZE * (nevents * 2), key_size);
    if (t == NULL) { perror(fn); exit(1); }
  }
  jd = b_tree_disk(t);
  
  random_tree = make_jrb();
  key_tree = make_jrb();

  ts = 0;

  if (strcmp(ifn, "-") != 0) {
    f = fopen(ifn, "r");
    if (f == NULL) { perror(ifn); exit(1); }
    while (fgets(buf, JDISK_SECTOR_SIZE*2, f) != NULL) {
      if (sscanf(buf, "%lf %u %s %s", &d, &lba, key, val) != 4) {
        fprintf(stderr, "Bad input file format\n");
        exit(1);
      }
      e = (Entry *) malloc(sizeof(Entry));
      e->rn = d;
      e->key = (char *) calloc(key_size+1, sizeof(char));
      e->lba = lba;
      strcpy(e->key, key);
      e->val = (char *) calloc(JDISK_SECTOR_SIZE+1, sizeof(char));
      strcpy(e->val, val);
      e->dtree_ptr = jrb_insert_dbl(random_tree, e->rn, new_jval_v((void *) e));
      jrb_insert_str(key_tree, e->key, new_jval_v((void *) e));
      ts++;
    }
    fclose(f);
  }
    
  for (i = 0; i < nevents; i++) {

    if (ts == 0 || drand48() < .5) {
      e = (Entry *) malloc(sizeof(Entry));
      e->rn = drand48();
      e->key = (char *) calloc(key_size+1, sizeof(char));
      e->val = (char *) calloc(JDISK_SECTOR_SIZE+1, sizeof(char));
      ks = lrand48()%(key_size-1)+1;
      for (j = 0; j < ks; j++) e->key[j] = 'a' + (lrand48() %26);
      vs = lrand48()%(val_size)+1;
      for (j = 0; j < vs; j++) e->val[j] = 'a' + (lrand48() %26);
      e->lba = b_tree_insert(t, e->key, e->val);      
      printf("I %s %s\n", e->key, e->val); fflush(stdout);
      tmp = jrb_find_str(key_tree, e->key);
      if (tmp != NULL) {
        e2 = tmp->val.v;
        if (e->lba != e2->lba) {
          printf("Problem at event %d.\n", i);
          printf("  Key %s already in tree.\n", e->key);
          printf("  Old lba: %d.  Returned lba: %d\n", e2->lba, e->lba);
        }
        jrb_delete_node(e2->dtree_ptr);
        free(e2->key);
        free(e2->val);
        free(e2);
        jrb_delete_node(tmp);
        ts--;
      }
  
      jrb_insert_str(key_tree, e->key, new_jval_v((void *) e));
      e->dtree_ptr = jrb_insert_dbl(random_tree, e->rn, new_jval_v((void *) e));
      ts++;
    } else {
      tmp = jrb_find_gte_dbl(random_tree, drand48(), &j);
      if (tmp == random_tree) tmp = random_tree->flink;
      e = (Entry *) tmp->val.v;
      printf("F %s\n", e->key); fflush(stdout);
      j = b_tree_find(t, e->key);
      if (e->lba != j) {
        printf("Problem at event %d.\n", i);
        printf("  Key %s should have lba %d.\n", e->key, e->lba);
        printf("  However, b_tree_find() returned %d.\n", j);
        exit(1);
      }
      jdisk_read(jd, e->lba, val);
      val[JDISK_SECTOR_SIZE] = '\0';
      if (strcmp(val, e->val) != 0) {
        printf("Problem at event %d.\n", i);
        printf("  Val should be %s\n", e->val);
        printf("  But it is %s\n", val);
        exit(1);
      }
      if (memcmp(val, e->val, JDISK_SECTOR_SIZE) != 0) {
        printf("Problem at event %d.\n", i);
        printf("  Bytes after the two val strings don't equal each other.\n");
        exit(1);
      }
    }
  }

  if (strcmp(ofn, "-") != 0) {
    f = fopen(ofn, "w");
    if (f == NULL) { perror(ofn); exit(1); }
    jrb_traverse(tmp, random_tree) {
      e = (Entry *) tmp->val.v;
      fprintf(f, "%.12lf %u %s %s\n", e->rn, e->lba, e->key, e->val);
    }
    fclose(f);
  }

  printf("Reads: %ld\n", jdisk_reads(jd));
  printf("Writes: %ld\n", jdisk_writes(jd));

  exit(0);
}
