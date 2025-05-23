#include "headers.h"
#include "mochila.h"

Dp *dp_init(int n, int m) {
    Dp *dp = (Dp*)malloc(sizeof(Dp));
    dp->n = n;
    dp->m = m;
    dp->h = 0;
    m++;
    n++;
    dp->data = (DpItem**)malloc((n) * sizeof(DpItem*));
    dp->line_weight = (int*)malloc((n) * sizeof(int));
    dp->line_v = (int*)malloc((n) * sizeof(int));
    for (int i = 0; i < n; i++) {
        dp->data[i] = (DpItem*)malloc((m) * sizeof(DpItem));
        dp->line_weight[i] = 0;
        dp->line_v[i] = 0;
        for (int j = 0; j < m; j++) {
            DpItem item = {0, 0};
            dp->data[i][j] = item;
        }
    }
    return dp;
}

void show(Dp *dp, int *w, int *v) {
    int max = dp->data[dp->h][dp->m].value;
    int idx = dp->m;
    for (int i = dp->h; i > 0; i--) {
        max -= dp->data[i][idx].q * v[i-1];
        
        // printf("i: %d, q: %d, idx, %d\n", i, dp->data[i][idx].q, dp->data[i][idx].prev_q);
        if(dp->data[i][idx].q >= 0) {
            printf("Item (%d, %d): %d\n", dp->line_weight[i], dp->line_v[i], dp->data[i][idx].q);
        }
        idx = dp->data[i][idx].prev_q;
        if (max <= 0);
    }
}
void undo(Dp *dp) {
    if (dp->h <= 0) return;
    for (int j = 0; j <= dp->m; j++) {
        dp->data[dp->h][j].value = 0;
        dp->data[dp->h][j].q = 0;
        dp->data[dp->h][j].prev_q = 0;
    }
    dp->line_weight[dp->h] = 0;
    dp->line_v[dp->h] = 0;
    dp->h--;
    return;
}

// https://youtu.be/OahcuBXLFlE
void calc(Dp *dp, int *w, int *v) {
    for (int i = 1; i <= dp->n; i++) {
        int w_atual = w[i-1];
        int v_atual = v[i-1];
        dp->line_weight[i] = w_atual;
        dp->line_v[i] = v_atual;
        for (int j = 1; j <= dp->m; j++) { // j capacidade
            for (int k = 0; k <= j / w_atual; k++) {
                if (dp->data[i][j].value < dp->data[i-1][j - k * w_atual].value + v_atual * k) {
                    dp->data[i][j].value = dp->data[i-1][j - k * w_atual].value + v_atual * k;
                    dp->data[i][j].q = k; // Quantidade do item atual
                    dp->data[i][j].prev_q = j - k * w_atual; // Quantidade do item anterior 
                }
            }
        }
        dp->h = i;
    }
}

void iter(Dp *dp, int w_atual, int v_atual) {
    if (dp->h >= dp->n) {
        printf("[ ! ] Profundidade maior do que o numero de itens\n");
        return;
    }

    if (w_atual == 0) {
        printf("[ ! ] Peso atual igual a 0\n");
        return;
    }
    int i = dp->h + 1;
    dp->line_weight[i] = w_atual;
    dp->line_v[i] = v_atual;
    for (int j = 1; j <= dp->m; j++) { // j capacidade
        for (int k = 0; k <= j / w_atual; k++) {
            if (dp->data[i][j].value < dp->data[i-1][j - k * w_atual].value + v_atual * k) {
                dp->data[i][j].value = dp->data[i-1][j - k * w_atual].value + v_atual * k;
                dp->data[i][j].q = k; // Quantidade do item atual
                dp->data[i][j].prev_q = j - k * w_atual; // Quantidade do item anterior 
            }
        }
    }
    dp->h = i;

    return;

}

void print_dp(Dp *dp) {
    for (int i = 0; i <= dp->n; i++) {
        for (int j = 0; j <= dp->m; j++) {
            printf("(%d %d) + %dv ", i+1, j, dp->data[i][j].q);
        }
        printf("\n");
    }
}

// int main() {
//     int v[] = {2, 3, 4, 7, 3, 1};
//     int w[] = {70, 100, 90, 20, 20, 10};
//     int n = 6;
//     int capacidade = 310;

//     Dp *dp = dp_init(n, capacidade);

//     for (int i = 0; i < n; i++) {
//         iter(dp, w[i], v[i]);
//     }

//     for (int i = 0; i < n; i++) {
//         undo(dp);
//     }

//     for (int i = 0; i < n; i++) {
//         iter(dp, w[i], v[i]);
//     }

//     show(dp, w, v);
//     free(dp->data);
//     free(dp);
//     return 0;
// }