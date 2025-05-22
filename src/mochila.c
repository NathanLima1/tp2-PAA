#include "headers.h"

typedef struct {
    int *data;
    int size;
} Dp1D;

typedef struct {
    int **data;
    int n;
    int m;
} Dp2D;

Dp2D *dp2d(int n, int m) {
    Dp2D *dp = (Dp2D *)malloc(sizeof(Dp2D));
    dp->n = n;
    dp->m = m;
    m++;
    n++;
    dp->data = (int **)malloc((n) * sizeof(int *));
    for (int i = 0; i < n; i++) {
        dp->data[i] = (int *)malloc((m) * sizeof(int));
        for (int j = 0; j < m; j++) {
            dp->data[i][j] = 0;
        }
    }
    return dp;
}

Dp1D *dp1d(int size) {
    Dp1D *dp = (Dp1D *)malloc(sizeof(Dp1D));
    dp->size = size; // O tamanho a ser considerado será a capacidade, ignorando a posição 0
    size++; // A primeira posição é 0
    dp->data = (int *)malloc((size) * sizeof(int));
    for (int i = 0; i < size; i++) {
        dp->data[i] = 0;
    }
    return dp;
}

void incrementar(Dp1D *dp, int w, int v) {
    for (int i = w; i <= dp->size; i++) {
        if (dp->data[i] < dp->data[i - w] + v) {
            dp->data[i] = dp->data[i - w] + v;
        }
    }
}

// https://youtu.be/OahcuBXLFlE
void incrementar2D(Dp2D *dp, int *w, int *v) {
    // 0, 0 é o caso base
    for (int i = 1; i <= dp->n; i++) {
        int w_atual = w[i-1];
        int v_atual = v[i-1];
        for (int j = w_atual; j <= dp->m; j++) {
            for (int k = 1; k <= j / w_atual; k++) {
                if (dp->data[i][j] < dp->data[i-1][j - k * w_atual] + v_atual * k) {
                    dp->data[i][j] = dp->data[i-1][j - k * w_atual] + v_atual * k;
                }
            }
        }
    }
}

void executarDP2D() {
    int n = 5;
    int capacidade = 10;
    int w[5] = {3, 4, 5, 6, 2};
    int v[5] = {4, 5, 6, 7, 3};

    Dp2D *dp = dp2d(n, capacidade);
    
    incrementar2D(dp, w, v);

    for (int i = 0; i <= dp->n; i++) {
        for (int j = 0; j <= dp->m; j++) {
            printf("%d ", dp->data[i][j]);
        }
        printf("\n");
    }

    free(dp->data);
    free(dp);
}

int main() {
    executarDP2D();
    return 0;

    int n = 5;
    int capacidade = 10;
    int w[5] = {3, 4, 5, 6, 2};
    int v[5] = {4, 5, 6, 7, 3};

    Dp1D *dp = dp1d(10);

    // Pode incrementar um novo item aos poucos
    // Fazer a interseção dos conjuntos para aproveitar os cálculos que começam iguais é uma alternativa
    // Exemplo: 1, 2, 3, 4, 5
    //          1, 2, 3, 5, 6
    // Calcular para 1, 2, 3 e 5
    // Depois para 4 -> [1, 2, 3, 5], 4
    // Depois para 6 -> [1, 2, 3, 5], 6

    for (int i = 0; i < n; i++) {
        incrementar(dp, w[i], v[i]);

        printf("Incrementando item (%d, %d)\n", w[i], v[i]);
        for (int j = 0; j <= dp->size; j++) printf("%d ", dp->data[j]);
        printf("\n");
    }

    free(dp->data);
    free(dp);

    return 0;
}