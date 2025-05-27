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

/* Incializa o grafo*/
Graph *init_graph(int num_vertices);

/* Adiciona a distancia para vertices conectados*/
void add_conn(Graph *graph, int id1, int id2, int dist);

/* Libera memoria armazenada para o grafo*/
void free_graph(Graph *graph);
#endif