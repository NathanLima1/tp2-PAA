#ifndef MOCHILA_H
#define MOCHILA_H

#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int value;
    int q; // quantidade
    int prev_q; // quantidade anterior
} DpItem;

typedef struct {
    DpItem **data;
    int n;
    int m;
    int h; // Profundidade calculada na matriz
    int *line_vertice; // Vértice da linha
} Dp;

Dp *dp_init(int n, int m);
void free_dp(Dp *dp);
void show(Dp *dp);
void undo(Dp *dp);
void iter(Dp *dp, int w_atual, int v_atual, int vertice);
void print_dp(Dp *dp);

#endif