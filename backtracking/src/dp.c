#include "../include/dp.h"

// Vídeo de referência para a mochila com DP 2D: https://youtu.be/OahcuBXLFlE

Dp *dp_init(int n, int m) {
    Dp *dp = (Dp*)malloc(sizeof(Dp));
    dp->n = n;
    dp->m = m;
    dp->h = 0;
    m++;
    n++;
    dp->data = (DpItem**)malloc((n) * sizeof(DpItem*));
    dp->line_vertice = (int*)malloc((n) * sizeof(int));
    for (int i = 0; i < n; i++) {
        dp->data[i] = (DpItem*)malloc((m) * sizeof(DpItem));
        dp->line_vertice[i] = -1;
        for (int j = 0; j < m; j++) {
            DpItem item = {0, 0};
            dp->data[i][j] = item;
        }
    }
    return dp;
}

void free_dp(Dp *dp) {
    if (dp == NULL) return;
    for (int i = 0; i <= dp->n; i++) {
        free(dp->data[i]);
    }
    free(dp->data);
    free(dp->line_vertice);
    free(dp);
}

// Desfaz o último item avaliado
void undo(Dp *dp) {
    if (dp->h <= 0) return;
    dp->h--;
    return;
}

// Avalia um novo item para a mochila
void iter(Dp *dp, int w_atual, int v_atual, int vertice) {
    if (dp->h >= dp->n) {
        printf("[ ! ] Profundidade maior do que o numero de itens\n");
        return;
    }

    if (w_atual == 0) {
        printf("[ ! ] Peso atual igual a 0\n");
        return;
    }

    int i = dp->h + 1;
    dp->line_vertice[i] = vertice;

    int max_w = w_atual <= dp->m ? w_atual : dp->m;

    // Primeiro loop preenche para as capacidadades em que o item não cabe
    for (int j = 0; j < max_w; j++) {
        dp->data[i][j].value = dp->data[i-1][j].value;
        dp->data[i][j].q = 0;
        dp->data[i][j].prev_q = j;
    }
    for (int j = w_atual; j <= dp->m; j++) {
        int prev = dp->data[i-1][j].value;

        // j - w_atual -> Capacidade de um item antes
        // A escolha para a DP nessa posição é somada com o valor do item para ser um candidato à DP na capacidade j
        int atual = dp->data[i][j - w_atual].value + v_atual;
        if (atual > prev) {
            dp->data[i][j].value = atual;
            dp->data[i][j].q = dp->data[i][j - w_atual].q + 1;
            dp->data[i][j].prev_q = dp->data[i][j - w_atual].prev_q;
        } else {
            dp->data[i][j].value = prev;
            dp->data[i][j].q = 0;
            dp->data[i][j].prev_q = j;
        }
    }


    dp->h = i;
}