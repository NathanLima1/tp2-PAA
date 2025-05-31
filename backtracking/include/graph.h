
#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

// Estruturas de dados
typedef struct {
    int id;
    int dist;
    int visitado;
} neighbor;

typedef struct town {
    int id;
    int w;
    int v;
    neighbor *neighbors;
    int num_neighbors;
    int size;
} Town;

typedef struct graph {
    int size;
    Town **towns;
} Graph;

Graph *init_graph(int num_towns);
Town *create_town(int id, int w, int v); // Cria uma cidade para o grafo
void free_graph(Graph *graph);
void add_conn(Graph *graph, int id1, int id2, int dist); // Adiciona uma conexão entre duas cidades

#endif // GRAPH_H
