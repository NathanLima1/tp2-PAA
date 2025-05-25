#include "solve.h"
#include <stdlib.h>
#include <stdio.h>

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

void calc(Dp *dp, int *w, int *v, int **g) {
    for (int dist = 0; dist <= dp->dist; dist++) {
        for (int vertice = 1; vertice <= dp->vertice; vertice++) {
            int w_atual = w[vertice - 1];
            int v_atual = v[vertice - 1];
            for (int capacidade = 0; capacidade <= dp->capacidade; capacidade++) {
                // Atualiza os valores para evitar colunas[Vet:Cap] vazias na matriz em distâncias impossíveis pelo grafo
                // Exemplo para o vértice 3 no caso de teste, é impossível ter uma distância de 1, pois o vértice mais próximo está a 3
                // Então a menor distância maior do q 0 seria 3, deixando as colunas 0, 1 e 2 sem atualização
                int l = capacidade / w_atual;
                int new_v = l * v_atual;
                dp->data[dist][vertice][capacidade].value = new_v;
                dp->data[dist][vertice][capacidade].q = l;
                dp->data[dist][vertice][capacidade].prev_c = capacidade - new_v;
                dp->data[dist][vertice][capacidade].prev = vertice;
                dp->data[dist][vertice][capacidade].prev_d = dist;

                for (int u = 1; u <= dp->vertice; u++) {
                    
                    // Para todos os vizinhos alcançáveis
                    int d = g[u - 1][vertice - 1];
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


int **init_graph(int num_vertices) {
    int **graph = (int **)malloc(num_vertices * sizeof(int *));
    for (int i = 0; i < num_vertices; i++) {
        graph[i] = (int *)malloc(num_vertices * sizeof(int));
        for (int j = 0; j < num_vertices; j++) {
            graph[i][j] = 0;
        }
    }
    return graph;
}

void add_conn(int **graph, int id1, int id2, int dist) {
    graph[id1][id2] = dist;
    graph[id2][id1] = dist;
}

void reconstruir(Dp *dp) {
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
    printf("%d ", atual->value);
    int v = max_v;
    int dist = dp->dist;
    int capacidade = dp->capacidade;

    int *solucao = (int*)malloc(sizeof(int)*dp->dist*2);
    i = 0;
    int last_index = 0;
    while (1) {
        solucao[2*i] = v;
        solucao[2*i+1] = atual->q;
        if (atual->q != 0) {
            last_index = 2*i + 1;
        }
        dist = atual->prev_d;

        capacidade = atual->prev_c;

        // Para quando entra em um ciclo ou não há mais distância
        if (v == atual->prev || !dist) {
            break;
        }

        v = atual->prev;
        atual = &dp->data[dist][v][capacidade];
        i++;
    }
    for (int i = 0; i <= last_index; i += 2) {
        printf("%d %d ", solucao[i], solucao[i + 1]);
    }
    free(solucao);
    printf("\b\n");
}