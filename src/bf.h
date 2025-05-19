#ifndef BF_H
#define BF_H

#include "graph.h"

typedef struct adj {
    int to;
    int dist;
    struct adj* next;
} Adj;

int min(int a, int b);
void add_adj(int from, int to, int dist);
int simulate_path(Graph* g, int* path, int len, int max_weight);
void prepare_adjacency(Graph* g);
void dfs(Graph* g, int u, int depth, int path_dist, int d, int max_weight);
void solve_bf(Graph* g, int d, int w);
void print_solution();
void free_adjacency();
void reset_globals();

#endif