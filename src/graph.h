#ifndef GRAPH_H
#define GRAPH_H

typedef struct town Town;
typedef struct node Node;
typedef struct graph Graph;

Town* create_town(int id, int weight, int skill);
Node* create_node(Town* town, int dist);
Graph* create_graph(int num_towns, int num_edges);
void add_town(Graph* graph, int id, int weight, int skill);
void add_edge(Graph* graph, int id1, int id2, int dist);
void free_graph(Graph* graph);
void print_graph(Graph* graph);

#endif