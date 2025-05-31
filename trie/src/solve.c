#include "../include/dp.h"
#include "../include/solve.h"
#include "../include/trie.h"

List *list_init(int size) {
    List *list = (List*)malloc(sizeof(List));
    list->data = (int*)malloc(size * sizeof(int));
    list->size = 0;

    return list;
}

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

void processar_extremidade(Graph *g, Dp *dp, Dp *max_dp, Trie_node *t, List *set) {
    int is_new_set = !search_and_insert(t, g->size, set->data, set->size);
    if (is_new_set) {
        dp->h = 0;
        for (int i = 0; i < set->size; i++) {
            iter(dp, g->towns[set->data[i]]->w, g->towns[set->data[i]]->v, set->data[i] + 1);
        }
        if (dp->data[dp->h][dp->m].value > max_dp->data[max_dp->h][max_dp->m].value) {
            copy_dp(dp, max_dp); // Salva o melhor DP
        }
    }
}

void dfs(Graph *g, int start, int depth, List *caminho, List *set, Dp *dp, Dp *max_dp, Trie_node *t) {
    Town *atual = g->towns[start];

    int atual_visitado = atual->visitado;

    // Salva o caminho e o set do caminho
    caminho->data[caminho->size] = atual->id;
    caminho->size++;
    if (!atual_visitado) {
        set->data[set->size] = atual->id;
        set->size++;
    }

    atual->visitado = 1; // Visita para não adicionar duas vezes no set

    int tem_vizinho = 0;
    for(int i = 0; i < atual->num_neighbors; i++) {
        int id = atual->neighbors[i].id;
        // Visitado apenas em uma direção, para permitir retorno para acessar bifurcações
        int visitado = atual->neighbors[i].visitado;

        if (!visitado) {
            int new_depth = depth - atual->neighbors[i].dist;

            // Se pode visitar, visita
            if (new_depth >= 0) {
                tem_vizinho = 1;
                atual->neighbors[i].visitado = 1;
                dfs(g, id, new_depth, caminho, set, dp, max_dp, t);
                atual->neighbors[i].visitado = 0;
            }
        }
    }

    if (!tem_vizinho) processar_extremidade(g, dp, max_dp, t, set);

    // Antes de retroceder, reseta o caminho, set e o estado de visitação
    caminho->size--;
    if (!atual_visitado) {
        atual->visitado = 0;
        set->size--;
    }
}

void show(Dp *dp) {
    int idx = dp->m;
    printf("%d ", dp->data[dp->h][dp->m].value);
    for (int i = dp->h; i > 0; i--) {
        printf("%d %d ", dp->line_vertice[i], dp->data[i][idx].q);
        idx = dp->data[i][idx].prev_q;
    }

    printf("\b\n");
}

// Soluciona o problema
void solve(Graph *g) {
    Dp *dp = dp_init(g->size, g->capacidade);
    Dp *max_dp = dp_init(g->size, g->capacidade);

    Trie_node *t = Trie_node_init(-1, g->size);

    for(int i = 0; i < g->size; i++){
        List *caminho = list_init(g->size);
        List *set = list_init(g->size);
        dfs(g, i, g->max_depth, caminho, set, dp, max_dp, t);
        free(caminho);
        free(set);
    };

    show(max_dp);
    free_dp(dp);
    free_dp(max_dp);
    free_trie(t, g->size);
}