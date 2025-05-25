#include <stdio.h>
#include <stdlib.h>
#include "heuristica.h"

int get_max(Graph *g, int capacidade, int viz, int toggle) {
    int max = -1;
    int max_razao = 0;
    for (int i = 1; i < g->num_vertices; i++) {
        int razao = capacidade / g->towns[i].w * g->towns[i].v;
        if ((g->data[i][viz] || !toggle) && razao > max_razao) {
            max_razao = razao;
            max = i;
        }
    }

    return max;
}


void heuristica(Graph *g, int max_depth, int capacidade) {
    int habilidade = 0;

    int *c = malloc(sizeof(int) * g->num_vertices);
    int i = get_max(g, capacidade, 0, 0);
    int prev_i = i;
    int *solucao = malloc(sizeof(int) * max_depth*2);
    int j = 0;
    while (1) {
        c[i] = capacidade / g->towns[i].w; 
        habilidade += c[i] * g->towns[i].v;
        capacidade -= c[i] * g->towns[i].w;
        g->towns[i].v = 0; // Deleta

        solucao[j] = i+1;
        solucao[j+1] = c[i];

        max_depth -= g->data[i][prev_i];
        prev_i = i;

        // Maior vizinho
        i = get_max(g, capacidade, prev_i, 1);
        if (i == -1 || capacidade < 0) {
            break;
        }
        j += 2;
    }

    printf("%d ", habilidade);

    for(int i = 0; i <= j; i += 2) {
        printf("%d %d ", solucao[i], solucao[i+1]);
    }
    printf("\n");

    free(c);
    free(solucao);
}