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
  int Curr_pp, Max_pp, Healing;
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
  int best_healing, best_path_length;
  double power_reduction;
  int *healing;
  Node **best_path;
} Info;

double Findrange(int x1, int y1, int x2, int y2) {
  int xr, yr;
  double r;

  xr = x2 - x1;
  yr = y2 - y1;

  r = (double) (xr * xr + yr * yr);

  return sqrt(r);
}

void DFS(Node *n, Node *from, int hops, int power, double total_healing, Info *g) {
  int i;

  /* Base Case */
  if (n->Visited) return;
  if (hops > g->num_jumps) return;

  n->Visited++;
  n->Prev = from;

  if (power + n->Curr_pp > n->Max_pp) n->Healing = n->Max_pp - n->Curr_pp;
  else n->Healing = power;

  total_healing += n->Healing;
  if (total_healing > g->best_healing) {
    g->best_healing = total_healing;
    g->best_path[g->best_path_length] = n->Prev;
    g->healing[g->best_path_length] = n->Healing;
    g->best_path_length++;
  }

  for (i = 0; i < n->Adj_size; i++) {
      DFS(n->Adj[i], n, hops+1, rint(power * (1 - g->power_reduction)), total_healing, g);
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
    g->best_healing = 0;
    g->best_path_length = 0;
    g->best_path = (Node **) malloc (sizeof(Node) * g->num_jumps);
    g->healing = (int *) malloc (sizeof(int) * g->num_jumps);
    for (i = n - 1; i >= 0; i--) {
      if (Findrange(g->ux, g->uy, players[i]->X, players[i]->Y) <= g->initial_range) DFS(players[i], players[n-1], 1, 500, 0, g); 
    }

    /* Print the optimal path */
    for (i = 0; i < g->best_path_length; i++) {
      printf("%s %d\n", g->best_path[i]->Name, g->healing[i]);
    }

    /* Print the total healing */
    printf("Total_Healing %d\n", g->best_healing);
    
    return 1;
  }

}
