#include "../include/graph.h"

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
    free(graph->values);
    free(graph->weights);

    free(graph);
}
