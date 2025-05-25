#include <stdio.h>
#include <stdlib.h>
#include "solve.h"




int get_max(int **g, int *w, int *v, int n, int capacidade, int viz, int toggle) {
    int max = -1;
    int max_razao = 0;
    for (int i = 1; i < n; i++) {
        int razao = capacidade / w[i] * v[i];
        if ((g[i][viz] || !toggle) && razao > max_razao) {
            max_razao = razao;
            max = i;
        }
    }

    return max;
}

int main() {
    int **g = init_graph(6);
    int v[] = {2, 3, 7, 4, 3, 1};
    int w[] = {70, 100, 20, 90, 20, 10};
    int c[6] = {0, 0, 0, 0, 0, 0};
    int n = 6;
    int distancia = 10;
    int capacidade = 310;
    int habilidade = 0;

    add_conn(g, 0, 1, 3);
    add_conn(g, 0, 4, 2);
    add_conn(g, 1, 2, 4);
    add_conn(g, 1, 3, 2);
    add_conn(g, 2, 5, 3);
    add_conn(g, 3, 4, 3);
    add_conn(g, 3, 5, 5);

    int cabe = 1;
    int i = get_max(g, w, v, n, capacidade, 0, 0);
    int prev_i = i;
    int *solucao = malloc(sizeof(int) * distancia*2);
    int j = 0;
    while (1) {
        c[i] = capacidade / w[i]; 
        habilidade += c[i] * v[i];
        capacidade -= c[i] * w[i];
        v[i] = 0; // Deleta

        solucao[j] = i+1;
        solucao[j+1] = c[i];

        distancia -= g[i][prev_i];
        prev_i = i;

        // Maior vizinho
        i = get_max(g, w, v, n, capacidade, prev_i, 1);
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
    return 0;
}