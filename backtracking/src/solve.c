#include "../include/dp.h"
#include "../include/solve.h"
#include "../include/graph.h"

void copy_dp(Dp *dp1, Dp *dp2){
    dp2->h = dp1->h;
    dp2->m = dp1->m;
    dp2->n = dp1->n;

    for (int i = 0; i <= dp2->n; i++) {
        dp2->line_vertice[i] = dp1->line_vertice[i];
        for (int j = 0; j <= dp2->m; j++) {
            dp2->data[i][j].value = dp1->data[i][j].value;
            dp2->data[i][j].q = dp1->data[i][j].q;
            dp2->data[i][j].prev_q = dp1->data[i][j].prev_q;
        }
    }
}
void dfs(Graph *g, int start, int root, int depth, Dp *dp, Dp *max_dp) {
    Town *atual = g->towns[start];

    iter(dp, atual->w, atual->v, start + 1);

    int tem_vizinho = 0;
    for(int i = 0; i < atual->num_neighbors; i++) {
        int id = atual->neighbors[i].id;

        // Visita em apenas uma direção na aresta, para permitir retorno em outra direção e acesso à bifurcações
        int visitado = atual->neighbors[i].visitado;

         // Não há necessidade de voltar para a raiz
         // Ela já será acessada futuramente pela mesma combinação e com uma distância restante maior
        if (!visitado && id != root) {

            int new_depth = depth - atual->neighbors[i].dist;

            if (new_depth >= 0) {
                tem_vizinho = 1;
                atual->neighbors[i].visitado = 1;
                dfs(g, id, root, new_depth, dp, max_dp);
                atual->neighbors[i].visitado = 0;
            }
        }
    }

    // Chegou na extremidade
    if (!tem_vizinho && atual->id != root) {
        if (dp->data[dp->h][dp->m].value > max_dp->data[max_dp->h][max_dp->m].value) {
            copy_dp(dp, max_dp); // Salva o melhor DP
        }
    }
    undo(dp);
}

void show(Dp *dp, FILE* fp_out) {
    int idx = dp->m;
    fprintf(fp_out, "%d", dp->data[dp->h][dp->m].value);
    for (int i = dp->h; i > 0; i--) {
        fprintf(fp_out, " %d %d", dp->line_vertice[i], dp->data[i][idx].q);
        idx = dp->data[i][idx].prev_q;
    }

    fprintf(fp_out, "\n");
}
