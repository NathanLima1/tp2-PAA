#ifndef GRAPH_H
#define GRAPH_H

typedef struct town{
    int id;
    int weight;
    int skill;
}Town;

typedef struct path
{
    int id1;
    int id2;
    int dist;
}Path;

typedef struct graph
{
    int num_towns;
    int num_edges;
    int edge_count;
    Town** towns;
    Path* edges;
}Graph;

Town* create_town(int id, int weight, int skill);
Graph* create_graph(int num_towns, int num_edges);
void add_town(Graph* graph, int id, int weight, int skill);
void add_edge(Graph* graph, int id1, int id2, int dist);
void free_graph(Graph* graph);
void print_graph(Graph* graph);

#endif