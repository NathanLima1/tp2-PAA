#include "mochila.h"

typedef struct {
    int id;
    int dist;
} neighbor;

typedef struct town{
    int id;
    int weight;
    int skill;

    neighbor *neighbors;
    int num_neighbors;
    int size;
    int visitado; // Posso retroceder apenas em vizinhos que já foram visitados
}Town;

typedef struct graph
{
    int size;
    Town** towns;
}Graph;

Town *create_town(int id, int weight, int skill){
    Town *town = (Town*)malloc(sizeof(Town));
    town->id = id;
    town->weight = weight;
    town->skill = skill;

    town->num_neighbors = 0;
    town->size = 1;
    town->neighbors = malloc(sizeof(neighbor));

    town->visitado = 0;
    return town;
}
Graph *create_graph(int num_towns){
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->size = num_towns;
    graph->towns = (Town**)malloc(num_towns * sizeof(Town*));
    for(int i = 0; i < num_towns; i++){
        graph->towns[i] = create_town(i, 0, 0);
    }
    return graph;
}

void add_conn(Graph *graph, int id1, int id2, int dist){
    neighbor n1 = {id1, dist};
    neighbor n2 = {id2, dist};

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
        dp2->line_weight[i] = dp1->line_weight[i];
        dp2->line_v[i] = dp1->line_v[i];
        for (int j = 0; j <= dp2->m; j++) {
            dp2->data[i][j].value = dp1->data[i][j].value;
            dp2->data[i][j].q = dp1->data[i][j].q;
            dp2->data[i][j].prev_q = dp1->data[i][j].prev_q;
        }
    }
}
void dfs(Graph *g, int start, int depth, Dp *dp, Dp *max_dp) {
    Town *atual = g->towns[start];

    if (!atual->visitado) iter(dp, atual->weight, atual->skill);
    int atual_visitado = atual->visitado;
    atual->visitado = 1;

    int nao_tem_vizinho = 1;
    for(int i = 0; i < atual->num_neighbors; i++) {
        int id = atual->neighbors[i].id;
        int visitado = g->towns[id]->visitado;

        // Visita avançando ou retrocedendo nos visitados, para permitir o retorno e acesso simultâneo a bifurcações
        // Avança apenas para ids maiores e retrocede para os menores
        if ((!visitado && start < id) || (visitado && start > id)) {
            int new_depth = depth - atual->neighbors[i].dist;

            if (new_depth >= 0) {
                nao_tem_vizinho = 0;
                dfs(g, id, new_depth, dp, max_dp);
            }
            }
        }
        if (nao_tem_vizinho) {
            if (dp->data[dp->h][dp->m].value > max_dp->data[max_dp->h][max_dp->m].value) {
                copy_dp(dp, max_dp);
            }
    }
    if (!atual_visitado) {
        atual->visitado = 0;
        undo(dp);
    }
}

typedef struct {
    Dp *dp;
} DpGrafoItem;

typedef struct {
    DpGrafoItem *data;
} DpGrafo;

int main() {
    Graph *g = create_graph(6);
    int v[] = {2, 3, 7, 4, 3, 1};
    int w[] = {70, 100, 20, 90, 20, 10};
    int n = 6;
    int max_depth = 10;
    int m = 310;

    for (int i = 0; i < n; i++){
        g->towns[i]->weight = w[i];
        g->towns[i]->skill = v[i];
    }
    add_conn(g, 0, 1, 3);
    add_conn(g, 0, 4, 2);
    add_conn(g, 1, 2, 4);
    add_conn(g, 1, 3, 2);
    add_conn(g, 2, 5, 3);
    add_conn(g, 3, 4, 3);
    add_conn(g, 3, 5, 5);

    Dp *dp = dp_init(n, m);
    Dp *max_dp = dp_init(n, m);

    // O algoritmo inicia aqui
    for(int i = 0; i < n; i++){
        dfs(g, i, max_depth, dp, max_dp);
        reset_graph(g);
    };

    show(max_dp, w, v);

    free_graph(g);
    free_dp(dp);
    free_dp(max_dp);
    return 0;
}