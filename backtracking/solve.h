#ifndef SOLVE_H
#define SOLVE_H

#include "mochila.h"

// Estruturas de dados
typedef struct {
    int id;
    int dist;
    int visitado;
} neighbor;

typedef struct town {
    int id;
    int w;
    int v;
    neighbor *neighbors;
    int num_neighbors;
    int size;
    int visitado;
    int is_root;
    int *capacidade;
} Town;

typedef struct graph {
    int size;
    Town **towns;
} Graph;

// Funções de manipulação do grafo
Town *create_town(int id, int w, int v);
Graph *init_graph(int num_towns);
void add_conn(Graph *graph, int id1, int id2, int dist);
void reset_graph(Graph *graph);
void free_graph(Graph *graph);

// Funções auxiliares para DP
void copy_dp(Dp *dp1, Dp *dp2);

// DFS para resolver o problema
void dfs(Graph *g, int start, int depth, Dp *dp, Dp *max_dp);

#endif // SOLVE_H