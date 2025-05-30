#ifndef SOLVE_H
#define SOLVE_H

#include "mochila.h"
#include "trie.h"

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
} Town;

typedef struct graph {
    int size;
    int max_depth;
    int capacidade;
    Town **towns;
} Graph;

typedef struct {
    int *data;
    int size;
} List;

// Funções de manipulação do grafo
Town *create_town(int id, int w, int v);
Graph *init_graph(int num_towns);
List *list_inint(int size);
void add_conn(Graph *graph, int id1, int id2, int dist);
void free_graph(Graph *graph);

// Funções auxiliares para DP
void copy_dp(Dp *dp1, Dp *dp2);

// DFS para resolver o problema
void dfs(Graph *g, int start, int depth, List *caminho, List *set, Dp *dp, Dp *max_dp, Trie_node *t);

// Chama o DFS a partir de cada vértice para chegar na solução e a exibe
void solve(Graph *g);

#endif // SOLVE_H