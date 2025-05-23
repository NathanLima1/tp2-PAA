#include "mochila.h"

typedef struct {
    int id;
    int dist;
    int visited;
} neighbor;

typedef struct town{
    int id;
    int weight;
    int skill;

    neighbor *neighbors;
    int num_neighbors;
    int descendente; // Posso retroceder apenas em vizinhos que já foram visitados
    int disabled;
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
    town->neighbors = malloc(sizeof(neighbor));
    town->descendente = 0;
    town->disabled = 0;
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
    neighbor n1 = {id1, dist, 0};
    neighbor n2 = {id2, dist, 0};

    Town *town1 = graph->towns[id1];
    Town *town2 = graph->towns[id2];
    town1->neighbors[town1->num_neighbors] = n2;
    town2->neighbors[town2->num_neighbors] = n1;

    town1->num_neighbors++;
    town2->num_neighbors++;
    town1->neighbors = realloc(town1->neighbors, (town1->num_neighbors + 1) * sizeof(neighbor));
    town2->neighbors = realloc(town2->neighbors, (town2->num_neighbors + 1) * sizeof(neighbor));
}

void reset_graph(Graph *graph){
    for(int i = 0; i < graph->size; i++){
        for (int j = 0; j < graph->towns[i]->num_neighbors; j++){
            graph->towns[i]->neighbors[j].visited = 0;
        }
        graph->towns[i]->descendente = 0;
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

void dfs(Graph *g, int start, int depth, Dp *dp, Dp *max_dp) {
    Town *atual = g->towns[start];

    if (!atual->descendente) {
        iter(dp, atual->weight, atual->skill);
    }
    int bak_descendente = atual->descendente;
    atual->descendente = 1;

    for(int i = 0; i < atual->num_neighbors; i++) {
        int id = atual->neighbors[i].id;
        if(!atual->neighbors[i].visited) {
            atual->neighbors[i].visited = 1;

            int new_depth = depth - atual->neighbors[i].dist;
            int descendente = g->towns[id]->descendente;

            if ((!descendente && start < id) || (descendente && start > id)) {
                if (new_depth >= 0) {
                    dfs(g, id, new_depth, dp, max_dp);
                } else {
                    if (dp->data[dp->h][dp->m].value > max_dp->data[max_dp->h][max_dp->m].value) {
                        max_dp->h = dp->h;
                    
                        // Copia os dados do dp atual para o max_dp
                        for (int i = 0; i <= max_dp->n; i++) {
                            max_dp->line_weight[i] = dp->line_weight[i];
                            max_dp->line_v[i] = dp->line_v[i];
                            for (int j = 0; j <= max_dp->m; j++) {
                                max_dp->data[i][j].value = dp->data[i][j].value;
                                max_dp->data[i][j].q = dp->data[i][j].q;
                                max_dp->data[i][j].prev_q = dp->data[i][j].prev_q;
                            }
                        }
                    }
                
                }
            }

            atual->neighbors[i].visited = 0;
        }
    }
    if (!bak_descendente) {
        atual->descendente = 0;
        undo(dp);
    }
}

int main() {
    Graph *g = create_graph(6);
    int v[] = {2, 3, 7, 4, 3, 1};
    int w[] = {70, 100, 20, 90, 20, 10};
    int n = 6;
    int D = 10;
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
    
    for(int i = 0; i < n; i++){
        g->towns[i]->disabled = 1;
        dfs(g, i, D, dp, max_dp);
        reset_graph(g);
    };

    show(max_dp, w, v);

    free_graph(g);
    free_dp(dp);
    free_dp(max_dp);
    return 0;
}