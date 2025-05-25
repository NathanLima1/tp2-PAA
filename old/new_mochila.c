#include "headers.h"

typedef struct {
    int value;
    int q; // quantidade
    int prev_c; // quantidade anterior
    int prev_d;
    int prev; // Vértice anterior
} DpItem;

typedef struct {
    DpItem ***data;
    int dist; // Distancia restante
    int capacidade; // Capacidade restante
    int vertice; // Vértice
} Dp;


Dp *dp_init(int n, int num_vertices, int m) {
    Dp *dp = (Dp*)malloc(sizeof(Dp));
    dp->dist = n;
    dp->vertice = num_vertices;
    dp->capacidade = m;
    n++;
    num_vertices++;
    m++;
    dp->data = (DpItem***)malloc((n) * sizeof(DpItem**));
    for (int i = 0; i < n; i++) {
        dp->data[i] = (DpItem**)malloc(num_vertices * sizeof(DpItem*));
        for (int j = 0; j < num_vertices; j++) {
            dp->data[i][j] = (DpItem*)malloc(m * sizeof(DpItem));
            for (int k = 0; k < m; k++) {
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


int **init_graph(int n) {
    int **graph = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        graph[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }
    return graph;
}

void add_conn(int **graph, int id1, int id2, int dist) {
    graph[id1][id2] = dist;
    graph[id2][id1] = dist;
}

void reconstruir(Dp *dp, int **g, int *w) {
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
    int max_capacidade = atual->value;
    int d = 0;
    while (1) {

        printf("%d %d ", v, atual->q);
        dist = atual->prev_d;

        capacidade = atual->prev_c;

        // Se repetir um vértice ou não houver mais capacidade, pode parar
        if (v == atual->prev || !dist || !capacidade) {
            break;
        }
        v = atual->prev;
        atual = &dp->data[dist][v][capacidade];
    }
    printf("\b\n");
}
int main() {
    
    int **g = init_graph(6);
    int v[] = {2, 3, 7, 4, 3, 1};
    int w[] = {70, 100, 20, 90, 20, 10};
    int num_vertices = 6;
    int max_depth = 10;
    int capacidade = 310;
    add_conn(g, 0, 1, 3);
    add_conn(g, 0, 4, 2);
    add_conn(g, 1, 2, 4);
    add_conn(g, 1, 3, 2);
    add_conn(g, 2, 5, 3);
    add_conn(g, 3, 4, 3);
    add_conn(g, 3, 5, 5);

    
    
    // int **g = init_graph(5);
    // int v[] = {10, 9, 1, 6, 4};
    // int w[] = {10, 30, 1, 3, 2};
    // int num_vertices = 5;
    // int max_depth = 6;
    // int capacidade = 317;
// 
    // add_conn(g, 0, 1, 3);
    // add_conn(g, 0, 2, 2);
    // add_conn(g, 0, 3, 2);
    // add_conn(g, 1, 2, 1);
    // add_conn(g, 2, 4, 3);
    // add_conn(g, 3, 4, 4);

    Dp *dp = dp_init(max_depth, num_vertices, capacidade);
    calc(dp, w, v, g);
    for (int i = 1; i <= dp->vertice; i++) {
        DpItem *atual = &dp->data[6][i][310];
        printf("Vertice %d: v: %d (q: %d, c: %d) %d, %d\n", i, atual->prev, atual->q, atual->prev_c, atual->value, atual->prev_d);
    }

    reconstruir(dp, g, w);
    return 0;
}