#include "headers.h"



typedef struct {
    int *data;
    int size;
} Dp1D;

void incrementar(Dp1D *dp, int w, int v) {
    for (int i = w; i <= dp->size; i++) {
        if (dp->data[i] < dp->data[i - w] + v) {
            dp->data[i] = dp->data[i - w] + v;
        }
    }
}

Dp1D *dp1d(int size) {
    Dp1D *dp = (Dp1D*)malloc(sizeof(Dp1D));
    dp->size = size; // O tamanho a ser considerado será a capacidade, ignorando a posição 0
    size++; // A primeira posição é 0
    dp->data = (int*)malloc((size) * sizeof(int));
    for (int i = 0; i < size; i++) {
        dp->data[i] = 0;
    }
    return dp;
}


// Pode incrementar um novo item aos poucos
// Fazer a interseção dos conjuntos para aproveitar os cálculos que começam iguais é uma alternativa
// Exemplo: 1, 2, 3, 4, 5
//          1, 2, 3, 5, 6
// Calcular para 1, 2, 3 e 5
// Depois para 4 -> [1, 2, 3, 5], 4
// Depois para 6 -> [1, 2, 3, 5], 6

void executarDP1D() {

    int n = 5;
    int capacidade = 11;
    int w[5] = {1, 4, 5, 6, 2};
    int v[5] = {1, 5, 6, 7, 3};

    Dp1D *dp = dp1d(capacidade);
    for (int i = 0; i < n; i++) {
        incrementar(dp, w[i], v[i]);
        for (int j = 0; j <= dp->size; j++) printf("%d ", dp->data[j]);
        printf("\n");
    }

    free(dp->data);
    free(dp);

    return;
}

int main() {
    executarDP1D();
    return 0;
}