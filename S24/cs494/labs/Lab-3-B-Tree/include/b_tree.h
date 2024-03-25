#ifndef _BP_TREE_
#define _BP_TREE_

#include "jdisk.h"

void *b_tree_create(char *filename, long size, int key_size);
void *b_tree_attach(char *filename);

unsigned int b_tree_insert(void *b_tree, void *key, void *record);
unsigned int b_tree_find(void *b_tree, void *key);
void *b_tree_disk(void *b_tree);
int b_tree_key_size(void *b_tree);
void b_tree_print_tree(void *b_tree);

#endif
