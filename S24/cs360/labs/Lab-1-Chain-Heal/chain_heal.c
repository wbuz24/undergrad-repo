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
  int Adj_size, Visited;
  struct node *Prev;
  struct node **Adj;
} Node;

typedef struct info {
  int initial_range;
  int jump_range;
  int num_jumps;
  int initial_power;
  int ux, uy; /* Urgosa's position */
  double power_reduction;
} Info;

double Findrange(int x1, int y1, int x2, int y2) {
  int xr, yr;
  double r;

  xr = x2 - x1;
  yr = y2 - y1;

  r = (double) (xr * xr + yr * yr);

  return sqrt(r);
}

void DFS(Node *n, int hops, Info *g) {
  int i;

  /* Base Case */
  if (n->Visited) return;
  if (hops > g->num_jumps) return;

  n->Visited++;
  printf("node: %s Hops %d\n", n->Name, hops);

  for (i = 0; i < n->Adj_size; i++) {
    DFS(n->Adj[i], hops+1, g);
  }

  n->Visited--;

  return;
}

int main(int argc, char **argv) {
  int x, y, cpp, mpp; /* Temporary values for reading */
  int i, j, n, in, jn;
  char name[101];
  Node *player, *previous;
  Info *g;

  if (argc != 6) { /* Check command line inputs */
    printf("chain_heal initial_range jump_range num_jumps initial_power power_reduction\n");
    return 0;
  }
  else {

    /* Initialize command line args */
    g = (Info *) malloc(sizeof(Info));
    sscanf(argv[1], "%d", &g->initial_range);
    sscanf(argv[2], "%d", &g->jump_range);
    sscanf(argv[3], "%d", &g->num_jumps);
    sscanf(argv[4], "%d", &g->initial_power);
    sscanf(argv[5], "%lf", &g->power_reduction);

    n = 0; /* track players */
    g->ux = 0;
    g->uy = 0;
    while (scanf("%d %d %d %d %s", &x, &y, &cpp, &mpp, name) == 5) {
      /* make a new player instance */
      player = (Node *) malloc(sizeof(Node));
      player->Name = strdup(name); /* */
      player->X = x;
      player->Y = y;
      player->Curr_pp = cpp;
      player->Max_pp = mpp;
      player->Adj_size = 0;
      player->Visited = 0;

      /* Set the previous pointer */
      if (strcmp("Urgosa_the_Healing_Shaman", name) == 0) {
        player->Prev = NULL;
        g->ux = x; /* Urgosa's positions, in case he is not at (0, 0) */
        g->uy = y;
      }
      else player->Prev = previous; 

      n++;
      previous = player;
    }

    Node *players[n]; /* declare array of node pointers */

    for (i = 0; i < n; i++) { /* Traverse the nodes and store in the array */
      players[i] = player;
      if (player->Prev != NULL) player = player->Prev;
    }

    /* Calculate adjacency size */
    for (i = 0; i < n; i++) {
      for (j = i + 1; j < n; j++) { /* Only need to look forward */
        if (Findrange(players[i]->X, players[i]->Y, players[j]->X, players[j]->Y) <= g->jump_range) {
          players[i]->Adj_size++;
          players[j]->Adj_size++;
        }
      } 
    }

    /* Allocate each adjacency list to the correct size */
    for (i = 0; i < n; i++) {
      players[i]->Adj = (Node **) malloc(sizeof(Node) * players[i]->Adj_size);
      players[i]->Adj_size = 0; /* This is now an index */
    }

    /* Place nodes into their adjacency lists */
    for (i = 0; i < n; i++) {
       for (j = i + 1; j < n; j++) {
        if (Findrange(players[i]->X, players[i]->Y, players[j]->X, players[j]->Y) <= g->jump_range) {
          players[i]->Adj[players[i]->Adj_size] = players[j];
          players[j]->Adj[players[j]->Adj_size] = players[i];
          players[i]->Adj_size++;
          players[j]->Adj_size++;
        }
      }
    }

    /* DFS */
    for (i = n - 1; i >= 0; i--) {
      if (Findrange(g->ux, g->uy, players[i]->X, players[i]->Y) <= g->initial_range) DFS(players[i], 1, g);
      
    }
    return 1;
  }

}
