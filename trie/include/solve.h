#ifndef SOLVE_H
#define SOLVE_H

#include "../include/dp.h"
#include "../include/trie.h"
#include "../include/graph.h"

typedef struct {
    int *data;
    int size;
} List;

// Funções de manipulação do grafo
List *list_inint(int size);

// Funções auxiliares para DP
void copy_dp(Dp *dp1, Dp *dp2);

// DFS para resolver o problema
void dfs(Graph *g, int start, int depth, List *caminho, List *set, Dp *dp, Dp *max_dp, Trie_node *t);

// Chama o DFS a partir de cada vértice para chegar na solução e a exibe
void solve(Graph *g);

// Mostra a solução
void show(Dp *dp);

#endif // SOLVE_H