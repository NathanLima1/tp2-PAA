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

/* Inicializa a DP*/
Dp *dp_init(int profundidade, int num_vertices, int capacidade);

/* Libera a memoria armazenada para DP*/
void free_dp(Dp *dp);

void calc(Dp *dp, Graph *g);

/* Reconstroi a solução com base na matriz DP*/
void reconstruir(Dp *dp, FILE* fp_out);

/* Remove ciclos redundantes da solução*/
void minimizar_solucao(int *solucao, int n);

/* Atualiza os valores para evitar colunas[_:vet:cap] vazias na matriz em distâncias impossíveis pelo grafo
Exemplo para o vértice 3 no caso de teste, é impossível ter uma distância de 1, pois o vértice mais próximo está a 3
Então a menor distância maior do que 0 seria 3, deixando as colunas 0, 1 e 2 sem atualização*/
void preencher_dist_inacessiveis(Dp* dp, int capacidade, int v_atual, int w_atual, int dist, int vertice);

#endif