#ifndef DP_H
#define DP_H

#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int value;
    int q; // quantidade selecionada do item atual
    int prev_q; // quantidade selecionada do item anterior
} DpItem;

typedef struct {
    DpItem **data;
    int n; // Número máximo de itens
    int m; // Capacidade máxima da mochila
    int h; // Profundidade calculada na matriz
    int *line_vertice; // Vértice da linha
} Dp;

Dp *dp_init(int n, int m);
void free_dp(Dp *dp);

void undo(Dp *dp); // Desfaz o último item avaliado para a mochila
void iter(Dp *dp, int w_atual, int v_atual, int vertice); // Avalia um novo item para a mochila

#endif