#include <stdio.h>
#include <stdlib.h>
#include "heuristica.h"

int get_max_viz(Graph* g, int capacidade, int viz){
    int max = -1;
    int max_razao = 0;
    for (int i = 1; i < g->num_vertices; i++) {
        int razao = capacidade / g->towns[i].w * g->towns[i].v;
        if (g->data[i][viz] && razao > max_razao) {
            max_razao = razao;
            max = i;
        }
    }

    return max;
}

int get_max_inicial(Graph* g, int capacidade){
    int max = -1;
    int max_razao = 0;
    for (int i = 1; i < g->num_vertices; i++) {
        int razao = capacidade / g->towns[i].w * g->towns[i].v;
        if (razao > max_razao) {
            max_razao = razao;
            max = i;
        }
    }

    return max;
}

void recrutar_povo(Graph *g, int i, int *capacidade, int *habilidade, int *qtd) {
    *qtd = *capacidade / g->towns[i].w;
    *habilidade += *qtd * g->towns[i].v;
    *capacidade -= *qtd * g->towns[i].w;
    g->towns[i].v = 0; // Deleta
}

void heuristica(Graph *g, int max_depth, int capacidade, FILE* fp_out) {
    int habilidade = 0;

    int i = get_max_inicial(g, capacidade);
    int prev_i = i;
    int *solucao = malloc(sizeof(int) * max_depth*2);
    int j = 0;
    int q = 0;
    while (1) {
        recrutar_povo(g, i, &capacidade, &habilidade, &q);
        max_depth -= g->data[i][prev_i];

        if (capacidade < 0 || max_depth < 0) break;

        solucao[j] = i+1;
        solucao[j+1] = q;
        prev_i = i;

        i = get_max_viz(g, capacidade, prev_i);
        if (i == -1) break;
        j += 2;
    }

    fprintf(fp_out, "%d ", habilidade);

    for(int i = 0; i <= j; i += 2) {
        fprintf(fp_out, "%d %d ", solucao[i], solucao[i+1]);
    }
    fprintf(fp_out, "\n");

    free(solucao);
}