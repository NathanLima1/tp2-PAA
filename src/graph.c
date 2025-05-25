#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

Graph *init_graph(int num_vertices) {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->num_vertices = num_vertices;
    graph->data = (int**)malloc(num_vertices * sizeof(int*));
    graph->towns = (Town*)malloc(num_vertices * sizeof(Town));
    for (int i = 0; i < num_vertices; i++) {
        graph->data[i] = (int *)malloc(num_vertices * sizeof(int));
        for (int j = 0; j < num_vertices; j++) {
            graph->data[i][j] = 0;
        }
    }
    return graph;
}

void add_conn(Graph *graph, int id1, int id2, int dist) {
    graph->data[id1][id2] = dist;
    graph->data[id2][id1] = dist;
}

void free_graph(Graph *graph) {
    for (int i = 0; i < graph->num_vertices; i++) {
        free(graph->data[i]);
    }
    free(graph->data);
    free(graph->towns);
    free(graph);
}