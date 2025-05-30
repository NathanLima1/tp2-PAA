#include "mochila.h"
#include "solve.h"
#include "trie.h"

Town *create_town(int id, int w, int v){
    Town *town = (Town*)malloc(sizeof(Town));
    town->id = id;
    town->w = w;
    town->v = v;

    town->num_neighbors = 0;
    town->size = 1;
    town->neighbors = malloc(sizeof(neighbor));

    town->visitado = 0;
    return town;
}

Graph *init_graph(int num_towns){
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->size = num_towns;
    graph->towns = (Town**)malloc(num_towns * sizeof(Town*));
    for(int i = 0; i < num_towns; i++){
        graph->towns[i] = create_town(i, 0, 0);
    }
    return graph;
}

void add_conn(Graph *graph, int id1, int id2, int dist){
    neighbor n1 = {id1, dist, 0};
    neighbor n2 = {id2, dist, 0};

    Town *town1 = graph->towns[id1];
    Town *town2 = graph->towns[id2];

    
    town1->neighbors[town1->num_neighbors] = n2;
    town2->neighbors[town2->num_neighbors] = n1;

    town1->num_neighbors++;
    town2->num_neighbors++;

    if (town1->num_neighbors == town1->size){
        town1->size *= 2;
        town1->neighbors = realloc(town1->neighbors, (town1->size) * sizeof(neighbor));
    }
    if (town2->num_neighbors == town2->size){
        town2->size *= 2;
        town2->neighbors = realloc(town2->neighbors, (town2->size) * sizeof(neighbor));
    }


}

void free_graph(Graph *graph){
    for(int i = 0; i < graph->size; i++){
        free(graph->towns[i]->neighbors);
        free(graph->towns[i]);
    }

    free(graph->towns);
    free(graph);
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

List *list_init(int size) {
    List *list = (List*)malloc(sizeof(List));
    list->data = (int*)malloc(size * sizeof(int));
    list->size = 0;

    return list;
}

void processar_extremidade(Graph *g, Dp *dp, Dp *max_dp, Trie_node *t, List *set) {
    int is_new_set = search_and_insert(t, g->size, set->data, set->size);
    if (is_new_set) {
        dp->h = 0;
        for (int i = 0; i < set->size; i++) {
            iter(dp, g->towns[set->data[i]]->w, g->towns[set->data[i]]->v, i + 1);
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
        int visitado = atual->neighbors[i].visitado; // Visitado na aresta (direcionada) para permitir retorno

        if (!visitado) {
            int new_depth = depth - atual->neighbors[i].dist;

            // Se pode visitar, visita
            if (new_depth >= 0 && !g->towns[id]->visitado) {
                tem_vizinho = 1;
                atual->neighbors[i].visitado = 1;
                dfs(g, id, new_depth, caminho, set, dp, max_dp, t);
                atual->neighbors[i].visitado = 0;
            }
        }
    }

    if (!tem_vizinho) {
        processar_extremidade(g, dp, max_dp, t, set);
    }

    // Antes de retroceder
    caminho->size--;
    if (!atual_visitado) {
        atual->visitado = 0;
        set->size--;
    }
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