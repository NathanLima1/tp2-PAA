
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
        int visitado;
    } Town;

    typedef struct graph {
        int size;
        int max_depth;
        int capacidade;

        Town **towns;
        int *values;
        int *weights;
    } Graph;


    Graph *init_graph(int num_towns);
    Town *create_town(int id, int w, int v);
    void free_graph(Graph *graph);
    void add_conn(Graph *graph, int id1, int id2, int dist);

    #endif // GRAPH_H
