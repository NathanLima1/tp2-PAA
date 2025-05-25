#ifndef GRAPH_H
#define GRAPH_H

typedef struct {
    int w;
    int v;
} Town;

typedef struct {
    int **data;
    int num_vertices;
    Town *towns;
} Graph;


Graph *init_graph(int num_vertices);
void add_conn(Graph *graph, int id1, int id2, int dist);
void free_graph(Graph *graph);
#endif