#include <stdlib.h>
#include <stdio.h>
#include "dp.h"

Dp *dp_init(int profundidade, int num_vertices, int capacidade) {
    Dp *dp = (Dp*)malloc(sizeof(Dp));
    dp->dist = profundidade;
    dp->vertice = num_vertices;
    dp->capacidade = capacidade;
    profundidade++;
    num_vertices++;
    capacidade++;
    dp->data = (DpItem***)malloc((profundidade) * sizeof(DpItem**));
    for (int i = 0; i < profundidade; i++) {
        dp->data[i] = (DpItem**)malloc(num_vertices * sizeof(DpItem*));
        for (int j = 0; j < num_vertices; j++) {
            dp->data[i][j] = (DpItem*)malloc(capacidade * sizeof(DpItem));

            for (int k = 0; k < capacidade; k++) {
                dp->data[i][j][k].value = 0;
                dp->data[i][j][k].q = 0;
                dp->data[i][j][k].prev_c = 0;
                dp->data[i][j][k].prev = 0;
                dp->data[i][j][k].prev_d = 0;
            }

        }
    }
    return dp;
}

void free_dp(Dp *dp) {
    for (int i = 0; i <= dp->dist; i++) {
        for (int j = 0; j <= dp->vertice; j++) {
            free(dp->data[i][j]);
        }
        free(dp->data[i]);
    }
    free(dp->data);
    free(dp);
}

void preencher_dist_inacessiveis(Dp* dp, int capacidade, int v_atual, int w_atual, int dist, int vertice){
    int l = capacidade / w_atual;
    int new_v = l * v_atual;
    dp->data[dist][vertice][capacidade].value = new_v;
    dp->data[dist][vertice][capacidade].q = l;
    dp->data[dist][vertice][capacidade].prev_c = capacidade - new_v;
    dp->data[dist][vertice][capacidade].prev = vertice;
    dp->data[dist][vertice][capacidade].prev_d = dist > 0 ? dist - 1 : 0;
}

void calc(Dp *dp, Graph *g) {
    for (int dist = 0; dist <= dp->dist; dist++) {
        for (int vertice = 1; vertice <= dp->vertice; vertice++) {
            int w_atual = g->towns[vertice - 1].w;
            int v_atual = g->towns[vertice - 1].v;
            for (int capacidade = 0; capacidade <= dp->capacidade; capacidade++) {
                preencher_dist_inacessiveis(dp, capacidade, v_atual, w_atual, dist, vertice);

                // Para todos os vizinhos alcançáveis
                for (int u = 1; u <= dp->vertice; u++) {
                    int d = g->data[u - 1][vertice - 1];
                    if (d == 0 || dist - d < 0) continue;

                    for (int l = 0; l <= (capacidade / w_atual); l++) {
                        int prev_c = capacidade - l * w_atual;
                        int new_v = dp->data[dist - d][u][prev_c].value + l * v_atual;
                        if (dp->data[dist][vertice][capacidade].value <= new_v) {
                            dp->data[dist][vertice][capacidade].value = new_v;
                            dp->data[dist][vertice][capacidade].q = l;
                            dp->data[dist][vertice][capacidade].prev_c = prev_c;
                            dp->data[dist][vertice][capacidade].prev = u;
                            dp->data[dist][vertice][capacidade].prev_d = dist - d;
                        }
                    }
                }
            }
        }
    }
}


void minimizar_solucao(int *solucao, int n) {
    for (int i = 0; i <= n; i += 2) {
        int pivo_v = solucao[i];
        int pivo_q = solucao[i + 1];
        if (pivo_v == -1) {
            continue;
        }
        int last_zero = i;
        int j;
        for (j = i + 2; j <= n; j += 2) {
            int next_pivo_v = solucao[j];
            int next_pivo_q = solucao[j + 1];
            if (next_pivo_q) {
                break;
            }

            if (next_pivo_v == pivo_v) {
                last_zero = j;
            }
        }

        for(int k = i+2; k <= last_zero; k += 2) {
            solucao[k] = -1; // Invalida a solução
        }
    }
}
void reconstruir(Dp *dp, FILE* fp_out) {
    DpItem *atual;
    int max_v = 1;
    int max_value = 0;
    int i;
    for (i = 1; i <= dp->vertice; i++) {
        atual = &dp->data[dp->dist][i][dp->capacidade];
        // Dá prioridade para vértices em que q soldados foram escolhidos
        if ((atual->q && atual->value >= max_value) || atual->value > max_value) {
            max_value = atual->value;
            max_v = i;
        }
    }
    atual = &dp->data[dp->dist][max_v][dp->capacidade];
    fprintf(fp_out, "%d ", atual->value);
    int v = max_v;
    int dist = dp->dist;
    int capacidade = dp->capacidade;

    int *solucao = (int*)malloc(sizeof(int)*dp->dist*2 + 2);
    i = 0;
    int last_index = 0;
    while (1) {
        solucao[i] = v;
        solucao[i+1] = atual->q;
        if (atual->q != 0) {
            last_index = i + 1;
        }
        dist = atual->prev_d;

        capacidade = atual->prev_c;

        // Para quando entra em um ciclo ou não há mais distância
        if (v == atual->prev || !dist) {
            break;
        }

        v = atual->prev;
        atual = &dp->data[dist][v][capacidade];
        i += 2;
    }

    minimizar_solucao(solucao, last_index);
    for (int i = 0; i <= last_index; i += 2) {
        if (solucao[i] != -1){
            fprintf(fp_out, "%d %d ", solucao[i], solucao[i + 1]);
        }
    }
    free(solucao);
    //printf("\b\n");
}