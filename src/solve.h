#ifndef SOLVE_H
#define SOLVE_H

#include "graph.h"

typedef struct {
    int value;
    int q; // quantidade
    int prev_c; // quantidade anterior
    int prev_d;
    int prev; // Vértice anterior
} DpItem;

typedef struct {
    DpItem ***data;
    int dist; // Distancia restante
    int capacidade; // Capacidade restante
    int vertice; // Vértice
} Dp;

Dp *dp_init(int profundidade, int num_vertices, int capacidade);
void free_dp(Dp *dp);
void calc(Dp *dp, Graph *g);
void reconstruir(Dp *dp); // Reconstrói a solução com base na matriz da DP
void minimizar_solucao(int *solucao, int n); // Remove os ciclos redundantes da solução

#endif