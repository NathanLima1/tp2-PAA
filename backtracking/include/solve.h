#ifndef SOLVE_H
#define SOLVE_H

#include "../include/dp.h"
#include "../include/graph.h"

// Funções auxiliares para DP
void copy_dp(Dp *dp1, Dp *dp2);

// DFS para resolver o problema
void dfs(Graph *g, int start, int root, int depth, Dp *dp, Dp *max_dp);

// Mostra a solução
void show(Dp *dp, FILE* fp_out);

#endif