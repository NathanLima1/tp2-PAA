#include "mochila.h"
#include "solve.h"

Town *create_town(int id, int w, int v){
    Town *town = (Town*)malloc(sizeof(Town));
    town->id = id;
    town->w = w;
    town->v = v;

    town->num_neighbors = 0;
    town->size = 1;
    town->neighbors = malloc(sizeof(neighbor));

    town->visitado = 0;
    town->is_root = 0;
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

void reset_graph(Graph *graph){
    for(int i = 0; i < graph->size; i++){
        graph->towns[i]->visitado = 0;
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
void dfs(Graph *g, int start, int depth, Dp *dp, Dp *max_dp) {
    Town *atual = g->towns[start];

    if (!atual->visitado) iter(dp, atual->w, atual->v, start + 1);
    int atual_visitado = atual->visitado;
    atual->visitado = 1; // Visitado do vértice para saber se já calculou na mochila

    int nao_tem_vizinho = 1;
    for(int i = 0; i < atual->num_neighbors; i++) {
        int id = atual->neighbors[i].id;
        int visitado = atual->neighbors[i].visitado; // Visitado na aresta (direcionada) para permitir retorno
        int is_root = g->towns[id]->is_root;

        if (!visitado) {
            int new_depth = depth - atual->neighbors[i].dist;

            if (new_depth >= 0 && !is_root) {
                nao_tem_vizinho = 0;
                atual->neighbors[i].visitado = 1;
                dfs(g, id, new_depth, dp, max_dp);
                atual->neighbors[i].visitado = 0;
            }
            }
        }
        if (nao_tem_vizinho) {
            if (dp->data[dp->h][dp->m].value > max_dp->data[max_dp->h][max_dp->m].value) {
                copy_dp(dp, max_dp); // Salva o melhor DP
            }
    }
    if (!atual_visitado) {
        atual->visitado = 0;
        undo(dp);
    }
}