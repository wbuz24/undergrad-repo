/********************************  Will Buziak **************************************/
/********************************     CS494    **************************************/
/********************************     Lab 3    **************************************/
/********************************     B Tree   **************************************/
/********************************              **************************************/

#include <stdio.h>
#include <stdlib.h>
#include "jdisk.h"
#include <sys/stat.h>
#include "b_tree.h"

typedef struct {
  int key_size;                 /* These are the first 16/12 bytes in sector 0 */
  unsigned int root_lba;
  unsigned long first_free_block;

  void *disk;                   /* The jdisk */
  unsigned long size;           /* The jdisk's size */
  unsigned long num_lbas;       /* size/JDISK_SECTOR_SIZE */
  int keys_per_block;           /* MAXKEY */
  int lbas_per_block;           /* MAXKEY+1 */
  struct Tree_Node *free_list;         /* Free list of nodes */
  
  struct Tree_Node *tmp_e;             /* When find() fails, this is a pointer to the external node */
  int tmp_e_index;              /* and the index where the key should have gone */
 
  int flush;                    /* Should I flush sector[0] to disk after b_tree_insert() */
} B_Tree;

typedef struct tnode {
  unsigned char bytes[JDISK_SECTOR_SIZE+256]; /* This holds the sector for reading and writing.
                                                 It has extra room because your internal representation
                                                 will hold an extra key. */
  unsigned char nkeys;                      /* Number of keys in the node */
  unsigned char flush;                      /* Should I flush this to disk at the end of b_tree_insert()? */
  unsigned char internal;                   /* Internal or external node */
  unsigned int lba;                         /* LBA when the node is flushed */
  unsigned char **keys;                     /* Pointers to the keys.  Size = MAXKEY+1 */
  unsigned int *lbas;                       /* Pointer to the array of LBA's.  Size = MAXKEY+2 */
  struct tnode *parent;                     /* Pointer to my parent -- useful for splitting */
  int parent_index;                         /* My index in my parent */
  struct tnode *ptr;                        /* Free list link */
} Tree_Node;

/* Create the first sector of a B Tree and return a pointer to it */
void *b_tree_create(char *filename, long size, int key_size) {
  B_Tree *newTree;
  struct Disk *jd;
  int MAXKEY;

  /* Create the jdisk */
  jd = jdisk_create(filename, size);
  if (jd == NULL) { fprintf(stderr, "Jdisk create error - %s\n", filename); exit(1); }

  /* Create the first sector */
  newTree = (B_Tree *) malloc(sizeof(B_Tree)); 
  if (newTree == NULL) { fprintf(stderr, "Malloc error creating new B Tree\n"); exit(1); }

  /* Edit sector zero */
  newTree->key_size = key_size;
  newTree->root_lba = 1;
  newTree->first_free_block = 1;

  /* Attach the jdisk */
  newTree->disk = jd;
  newTree->size = size;
  newTree->num_lbas = size/JDISK_SECTOR_SIZE;

  /* Calculate MAXKEY */
  MAXKEY = (JDISK_SECTOR_SIZE - 6) / (key_size + 4);
  newTree->keys_per_block = MAXKEY;
  newTree->lbas_per_block = MAXKEY + 1;
  
  newTree->flush = 0;

  return newTree;
}

void *b_tree_attach(char *filename) {
  B_Tree *newTree;
  struct Disk *jd;
  struct stat buf;
  char *sector;
  int MAXKEY, exists;

  /* Attach the jdisk */

  jd = jdisk_attach(filename);
  if (jd == NULL) { fprintf(stderr, "Error attaching %s as a jdisk\n", filename); exit(1); }

  exists = stat(filename, &buf);
  if (exists < 0) { fprintf(stderr, "%s does not exist\n", filename); exit(1); }
  if (buf.st_size % JDISK_SECTOR_SIZE != 0) { fprintf(stderr, "%s is not a valid jdisk\n", filename); exit(1); }

  /* Create a new B Tree */
  newTree = (B_Tree *) malloc(sizeof(B_Tree)); 
  if (newTree == NULL) { fprintf(stderr, "Malloc error creating new B Tree\n"); exit(1); }

  /* Extract the first sector from the jdisk */
  sector = (char *) malloc(sizeof(char) * JDISK_SECTOR_SIZE);
  if (sector == NULL) { fprintf(stderr, "Error allocating %d bytes to read the jdisk\n", JDISK_SECTOR_SIZE); exit(1); }

  /* Read sector 0 */
  jdisk_read(jd, 0, sector);

  /* First four bytes is the key size */ 
  newTree->key_size = (int) sector[0];
  /* Next four bytes are the lba of the root */
  newTree->root_lba = (unsigned int) sector[4];
  /* Then 4-8 bytes for the first free block */
  newTree->first_free_block = (unsigned long) sector[8];

  /* Connect the existing jdisk information into the B Tree */
  newTree->disk = jd;
  newTree->size = buf.st_size;
  newTree->num_lbas = buf.st_size / JDISK_SECTOR_SIZE;
  MAXKEY = (JDISK_SECTOR_SIZE - 6) / (newTree->key_size + 4);
  newTree->keys_per_block = MAXKEY;
  newTree->lbas_per_block = MAXKEY + 1;

  /* Connect the first node in the freelist */ 

  newTree->flush = 0;

}

unsigned int b_tree_insert(void *b_tree, void *key, void *record) {

}
unsigned int b_tree_find(void *b_tree, void *key) {

}

void *b_tree_disk(void *b_tree) {

}

int b_tree_key_size(void *b_tree) {
  B_Tree *tree;
  tree = b_tree;
  return tree->key_size;
}

void b_tree_print_tree(void *b_tree) {

}
