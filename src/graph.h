#include <stdio.h>
#include <stdlib.h>

typedef struct town{
    int id;
    int weight;
    int skill;
}Town;

typedef struct node
{
    Town* p;
    int dist;
    struct node* next;
}Node;

typedef struct graph
{
    int num_towns;
    Town** towns;
    Node** edges;
}Graph;

Town* create_town(int id, int weight, int skill);
Node* create_node(Town* town, int dist);
Graph* create_graph(int num_nodes);
void add_town(Graph* graph, int id, int weight, int skill);
void add_edge(Graph* graph, int id1, int id2, int dist);
void free_graph(Graph* graph);