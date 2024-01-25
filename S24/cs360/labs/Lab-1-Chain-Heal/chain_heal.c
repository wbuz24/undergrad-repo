/* Lab 1 Chain Heal 
 * Will Buziak
 * CS360
 * January 2024 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h> /* Compile with -lm */

typedef struct node {
  char *Name;
  int X, Y;
  int Curr_pp, Max_pp;
  struct node *Prev;
} Node;

int main(int argc, char **argv) {
  int initial_range, jump_range, num_jumps, initial_power, n;
  int x, y, cpp, mpp; /* Temporary values for reading */
  int i;
  char name[101];
  double power_reduction;
  Node *player, *previous;

  if (argc != 6) { /* Check command line inputs */
    printf("chain_heal initial_range jump_range num_jumps initial_power power_reduction\n");
    return 0;
  }
  else {
    /* Initialize command line args */
    sscanf(argv[1], "%d", &initial_range);
    sscanf(argv[2], "%d", &jump_range);
    sscanf(argv[3], "%d", &num_jumps);
    sscanf(argv[4], "%d", &initial_power);
    sscanf(argv[5], "%lf", &power_reduction);

    n = 0; /* track players */
    while (scanf("%d %d %d %d %s", &x, &y, &cpp, &mpp, name) == 5) {
      /* make a new player instance */
      player = (Node *) malloc(sizeof(Node));
      player->Name = name;
      player->X = x;
      player->Y = y;
      player->Curr_pp = cpp;
      player->Max_pp = mpp;

      /* Set the previous pointer */
      if (strcmp("Urgosa_the_Healing_Shaman", name) == 0) player->Prev = NULL;
      else player->Prev = previous; 

      n++;
      previous = player;
    }

    Node *players[n]; /* declare array of node pointers */

    for (i = 0; i < n; i++) { /* Traverse the nodes and store in the array */
      if (player->Prev != NULL) printf("%s\n", player->Name);
      player = player->Prev;
    }
    return 1;
  }

}
