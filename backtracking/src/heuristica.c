#include <stdio.h>
#include <stdlib.h>
#include "../include/heuristica.h"

int get_max(Graph *g, int capacidade) {
    int max = -1;
    int max_value = 0; // Maior valor possível com a capacidade atual e 1 tipo de item
    float max_razao = 0;
    for (int i = 1; i < g->size; i++) {
        int value = capacidade / g->towns[i]->w * g->towns[i]->v;
        if (!value) continue;

        float razao = (float)g->towns[i]->v / g->towns[i]->w;

        // Valoriza itens que têm uma razão boa e que preenchem bem a mochila
        if (razao > max_razao && value > max_value) {
            max_value = value;
            max_razao = razao;
            max = i;
        }
    }
    return max;
}

neighbor get_max_viz(Graph *g, int capacidade, int viz) {
    int max = -1;
    int max_value = 0;
    for (int i = 0; i < g->towns[viz]->num_neighbors; i++) {
        int id = g->towns[viz]->neighbors[i].id;
        if (g->towns[id]->v == 0) continue; 
        int value = (g->towns[id]->w == 0) ? 0 : (capacidade / g->towns[id]->w) * g->towns[id]->v;
        if (value > max_value) {
            max_value = value;
            max = i;
    }
    }

    neighbor n = {-1, 100, 0};
    return (max != -1) ? g->towns[viz]->neighbors[max] : n;
}


void heuristica(Graph *g, int max_depth, int capacidade) {
    int habilidade = 0;

    int i = get_max(g, capacidade);
    int prev_i = i;

    int d = 0;
    neighbor n_i;
    int *solucao = malloc(sizeof(int) * max_depth*2);
    int j = 0;
    int q = 0;
    while (1) {
        q = capacidade / g->towns[i]->w; 
        habilidade += q * g->towns[i]->v;
        capacidade -= q * g->towns[i]->w;
        g->towns[i]->v = 0; // Deleta
        max_depth -= d;


        if (capacidade < 0 || max_depth < 0) break;

        solucao[j] = i+1;
        solucao[j+1] = q;
        prev_i = i;
        
        // Maior vizinho
        n_i = get_max_viz(g, capacidade, prev_i);
        i = n_i.id;
        d = n_i.dist;
        if (i == -1) break;
        j += 2;
    }
    
    printf("%d", habilidade);

    for(int i = 0; i <= j; i += 2) {
        printf(" %d %d", solucao[i], solucao[i+1]);
    }
    printf("\n");

    free(solucao);
}