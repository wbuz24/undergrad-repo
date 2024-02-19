/* mysort.c
   Jim Plank
   CS360 Fakemake Lab
   10 September, 1999 */

/* This program sorts standard input lexicographically.  It uses a red-black
   tree to do this simply and efficiently.  

   Basically, it reads in a line of input, and inserts it into the 
   tree "sorted_lines".  The insertion performs the sorting using 
   strcmp as a comparison function.  When it's done reading and inserting,
   it traverses the tree's linked list, which is guaranteed to be sorted, 
   and prints out each line.
*/
   
   

#include <stdio.h>
#include <string.h>
#include "jrb.h"
#include "fields.h"

int main()
{
  IS is;
  char *copy;
  JRB sorted_lines, tmp;

  sorted_lines = make_jrb();
  is = new_inputstruct(NULL);

  while(get_line(is) >= 0) {
    copy = strdup(is->text1);
    jrb_insert_str(sorted_lines, copy, JNULL);
  }

  jrb_traverse(tmp, sorted_lines) {
    printf("%s", tmp->key.s);
  }
  return 0;
}
