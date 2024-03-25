#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include "b_tree.h"
#include "jrb.h"

void usage(char *s)
{
  fprintf(stderr, "usage: random_tester_2 seed nevents key_size tree_file input_file output_file\n");
  if (s != NULL) fprintf(stderr, "%s\n", s);
  exit(1);
}

static void print_bytes(unsigned char *buf, int n)
{
  int i;
  int string;
  unsigned char *b;

  string = 1;
  for (i = 0; i < n && isprint(buf[i]); i++) ;
  if (i == n) {
    string = 0;
  } else {
    for (; i < n && buf[i] == '\0'; i++);
    if (i != n) string = 0;
  }
  if (string) {
    printf("S %s\n", buf);
  } else {
    printf("H ");
    b = (unsigned char *) buf;
    for (i = 0; i < n; i++) printf("%02X", b[i]);
    printf("\n");
  }
}

int KS;

typedef struct {
  unsigned char *key;
  unsigned char *val;
  double rn;
  unsigned int lba;
  JRB dtree_ptr;
} Entry;

int compare(Jval v1, Jval v2)
{
  Entry *e1, *e2;

  e1 = (Entry *) v1.v;
  e2 = (Entry *) v2.v;
  return memcmp(e1->key, e2->key, KS);
}

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
  int i, j, val_size;
  Entry *e, *e2;
  char val[JDISK_SECTOR_SIZE+1];
  char buf[JDISK_SECTOR_SIZE*2];
  char key[300];
  FILE *f;

  if (argc != 7) usage(NULL);
  if (sscanf(argv[1], "%ld", &seed) == 0) usage("Bad Seed");
  if (sscanf(argv[2], "%d", &nevents) == 0) usage("Bad Seed");
  if (sscanf(argv[3], "%d", &key_size) == 0) usage("Bad Key Size");
  val_size = JDISK_SECTOR_SIZE;
  KS = key_size;
  fn = argv[4];
  ifn = argv[5];
  ofn = argv[6];
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
    while (fread(&d, sizeof(double), 1, f) == 1) {
      e = (Entry *) malloc(sizeof(Entry));
      e->rn = d;
      e->key = (unsigned char *) calloc(key_size, sizeof(char));
      e->val = (unsigned char *) calloc(JDISK_SECTOR_SIZE, sizeof(char));
      fread(&e->lba, sizeof(unsigned int), 1, f);
      fread(e->key, 1, key_size, f);
      fread(e->val, 1, val_size, f);
      e->dtree_ptr = jrb_insert_dbl(random_tree, e->rn, new_jval_v((void *) e));
      jrb_insert_gen(key_tree, new_jval_v((void *) e), new_jval_v((void *) e), compare);
      ts++;
    }
    fclose(f);
  }
    
  for (i = 0; i < nevents; i++) {
    if (ts == 0 || drand48() < .5) {
      e = (Entry *) malloc(sizeof(Entry));
      e->rn = drand48();
      e->key = (unsigned char *) calloc(key_size, sizeof(char));
      e->val = (unsigned char *) calloc(JDISK_SECTOR_SIZE, sizeof(char));
      for (j = 0; j < key_size; j++) e->key[j] = lrand48()&0xff;
      for (j = 0; j < val_size; j++) e->val[j] = lrand48()&0xff;
      printf("I\n");
      print_bytes(e->key, key_size);
      print_bytes(e->val, JDISK_SECTOR_SIZE);
      e->lba = b_tree_insert(t, e->key, e->val);      
      tmp = jrb_find_gen(key_tree, new_jval_v((void *) e), compare);
      if (tmp != NULL) {
        e2 = tmp->val.v;
        if (e->lba != e2->lba) {
          printf("Problem at event %d.\n", i);
          printf("  Key already in tree.\n");
          printf("  Old lba: %d.  Returned lba: %d\n", e2->lba, e->lba);
        }
        jrb_delete_node(e2->dtree_ptr);
        free(e2->key);
        free(e2->val);
        free(e2);
        jrb_delete_node(tmp);
        ts--;
      }
  
      jrb_insert_gen(key_tree, new_jval_v((void *) e), new_jval_v((void *) e), compare);
      e->dtree_ptr = jrb_insert_dbl(random_tree, e->rn, new_jval_v((void *) e));
      ts++;
    } else {
      tmp = jrb_find_gte_dbl(random_tree, drand48(), &j);
      if (tmp == random_tree) tmp = random_tree->flink;
      e = (Entry *) tmp->val.v;
      printf("F\n");
      print_bytes(e->key, key_size);
      j = b_tree_find(t, e->key);
      if (e->lba != j) {
        printf("Problem at event %d.\n", i);
        printf("  Key should have lba %d.\n", e->lba);
        printf("  However, b_tree_find() returned %d.\n", j);
        exit(1);
      }
      jdisk_read(jd, e->lba, val);
      val[JDISK_SECTOR_SIZE] = '\0';
      if (memcmp(val, e->val, JDISK_SECTOR_SIZE) != 0) {
        printf("Problem at event %d.\n", i);
        printf("  The two val strings don't equal each other.\n");
        printf("  Here's the val it found:\n");
        print_bytes(val, JDISK_SECTOR_SIZE);
        printf("  Here's the val it should be:\n");
        print_bytes(e->val, JDISK_SECTOR_SIZE);
        exit(1);
      }
    }
    /* b_tree_double_check(t); */
  }

  if (strcmp(ofn, "-") != 0) {
    f = fopen(ofn, "w");
    if (f == NULL) { perror(ofn); exit(1); }
    jrb_traverse(tmp, random_tree) {
      e = (Entry *) tmp->val.v;
      fwrite(&e->rn, sizeof(double), 1, f);
      fwrite(&e->lba, sizeof(unsigned int), 1, f);
      fwrite(e->key, 1, key_size, f);
      fwrite(e->val, 1, val_size, f);
    }
    fclose(f);
  }
  printf("Reads: %ld\n", jdisk_reads(jd));
  printf("Writes: %ld\n", jdisk_writes(jd));

  exit(0);
}
