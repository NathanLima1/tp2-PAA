#include "../include/dp.h"

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

// https://youtu.be/OahcuBXLFlE
void iter(Dp *dp, int w_atual, int v_atual, int vertice) {
    int i = dp->h + 1;
    dp->line_vertice[i] = vertice;

    int max_w = w_atual <= dp->m ? w_atual : dp->m;

    for (int j = 0; j < max_w; j++) {
        dp->data[i][j].value = dp->data[i-1][j].value;
        dp->data[i][j].q = 0;
        dp->data[i][j].prev_q = j;
    }

    for (int j = w_atual; j <= dp->m; j++) {
        int prev = dp->data[i-1][j].value;
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

void print_dp(Dp *dp) {
    for (int i = 0; i <= dp->n; i++) {
        for (int j = 0; j <= dp->m; j++) {
            printf("%d ", dp->data[i][j].value);
        }
        printf("\n");
    }
}