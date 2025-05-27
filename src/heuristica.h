#ifndef HEURISTICA_H
#define HEURISTICA_H

#include "solve.h"

int get_max(Graph *g, int capacidade, int viz, int toggle);
void heuristica(Graph *g, int max_depth, int capacidade, FILE* fp_out);

#endif