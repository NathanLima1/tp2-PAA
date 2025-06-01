#ifndef HEURISTICA_H
#define HEURISTICA_H

#include "../include/solve.h"

int get_max(Graph *g, int capacidade);
neighbor get_max_viz(Graph *g, int capacidade, int viz);
void heuristica(Graph *g, int max_depth, int capacidade, FILE* fp_out);

#endif