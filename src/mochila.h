#ifndef MOCHILA_H
#define MOCHILA_H

#include "headers.h"

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
} Dp;

Dp *dp_init(int n, int m);
void calc(Dp *dp, int *w, int *v);
void show(Dp *dp, int *w, int *v);
void undo(Dp *dp);
void iter(Dp *dp, int w_atual, int v_atual);
void print_dp(Dp *dp);

#endif