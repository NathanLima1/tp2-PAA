#ifndef HEURISTICA_H
#define HEURISTICA_H

#include "dp.h"

/* Escolhe o vértice com maior razão como inicio do caminho para a heuristica*/
int get_max_inicial(Graph *g, int capacidade);

/* Escolhe o vizinho com maior razão dentre os vizinhos para continuar o caminho*/
int get_max_viz(Graph* g, int capacidade, int viz);

/* Determina quantidade de soldados escolhidos, a habilidade gerada e subtrai o peso dos soldados da nave*/
void recrutar_povo(Graph *g, int i, int *capacidade, int *habilidade, int *qtd);

/* Funnção para resolver o problema a partir da heuristica*/
void heuristica(Graph *g, int max_depth, int capacidade, FILE* fp_out);

#endif