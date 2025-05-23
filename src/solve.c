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
}Town;

typedef struct graph
{
    int size;
    Town** towns;
}Graph;

Town* create_town(int id, int weight, int skill);
Graph* create_graph(int num_towns, int num_edges);
void add_conn(Graph* graph, int id1, int id2, int dist);
void free_graph(Graph* graph);
void print_graph(Graph* graph);

Town *create_town(int id, int weight, int skill){
    Town *town = (Town*)malloc(sizeof(Town));
    town->id = id;
    town->weight = weight;
    town->skill = skill;
    town->num_neighbors = 0;
    town->neighbors = malloc(sizeof(neighbor));
    town->descendente = 0;
    return town;
}
Graph *create_graph(int num_towns, int num_edges){
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

    void dfs(Graph *g, int start, int depth, void *dp, void *max_dp, int max_weight) {
        Town *atual = g->towns[start];
        atual->descendente = 1;
        // mochila.incrementar(dp, atual->weight, atual->skill);
        for(int i = 0; i < atual->num_neighbors; i++) {
            int id = atual->neighbors[i].id;
            if(!atual->neighbors[i].visited) {
                atual->neighbors[i].visited = 1;
                int dist = atual->neighbors[i].dist;

                printf("Ok\n");

                int new_depth = depth - dist;
                if (new_depth >= 0 && (start < id || g->towns[id]->descendente)) {
                    dfs(g, id, new_depth, dp, max_dp, max_weight);
                    atual->neighbors[i].visited = 0;
                } else {
                    // Cheguei no final
                    // if mochila.get_max(dp) > mochila.get_max(max_dp) {
                    //     max_dp = dp
                    //     max_weight = mochila.get_max(dp)
                }
            }
        }
        atual->descendente = 0;
        // mochila.undo()
    }