#include "headers.h"
#include "mochila.h"

Dp *dp_init(int n, int m) {
    Dp *dp = (Dp*)malloc(sizeof(Dp));
    dp->n = n;
    dp->m = m;
    dp->h = 1;
    m++;
    n++;
    dp->data = (DpItem**)malloc((n) * sizeof(DpItem*));
    for (int i = 0; i < n; i++) {
        dp->data[i] = (DpItem*)malloc((m) * sizeof(DpItem));
        for (int j = 0; j < m; j++) {
            DpItem item = {0, 0};
            dp->data[i][j] = item;
        }
    }
    return dp;
}

// https://youtu.be/OahcuBXLFlE
void calc(Dp *dp, int *w, int *v) {
    for (int i = 1; i <= dp->n; i++) {
        int w_atual = w[i-1];
        int v_atual = v[i-1];
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

void show(Dp *dp, int *w, int *v) {
    int max = dp->data[dp->h][dp->m].value;
    int idx = dp->m;
    for (int i = dp->h; i > 0; i--) {
        max -= dp->data[i][idx].q * v[i-1];
        
        // printf("i: %d, q: %d, idx, %d\n", i, dp->data[i][idx].q, dp->data[i][idx].j);
        if(dp->data[i][idx].q > 0) {
            printf("Item (%d, %d): %d\n", w[i-1], v[i-1], dp->data[i][idx].q);
        }
        idx = dp->data[i][idx].prev_q;
        if (max <= 0) break;
    }
}
void undo(Dp *dp) {
    if (dp->h <= 0) return;
    for (int j = 0; j <= dp->m; j++) {
        dp->data[dp->h][j].value = 0;
        dp->data[dp->h][j].q = 0;
        dp->data[dp->h][j].prev_q = 0;
    }
    dp->h--;
    return;
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
            printf("%d ", dp->data[i][j].value);
        }
        printf("\n");
    }
}

// int main() {
    
//     int n = 5;
//     int capacidade = 11;
//     int w[5] = {1, 4, 5, 6, 2};
//     int v[5] = {1, 5, 6, 7, 3};

//     Dp *dp = dp_init(n, capacidade);

//     calc(dp, w, v);
//     print_dp(dp);
//     printf("\n");
//     show(dp, w, v);
//     printf("\n");

//     // Desfaz a ultima linha
//     undo(dp);
//     print_dp(dp);
//     printf("\n");
//     show(dp, w, v);
//     printf("\n");

//     // Refaz a ultima linha
//     iter(dp, 2, 3);
//     print_dp(dp);
//     printf("\n");
//     show(dp, w, v);
//     printf("\n");

//     free(dp->data);
//     free(dp);
//     return 0;
// }