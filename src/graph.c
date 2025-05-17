#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

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
    struct path* next;
}Path;

typedef struct graph
{
    int num_towns;
    int num_edges;
    int edge_count;
    Town** towns;
    Path* edges;
}Graph;

Town* create_town(int id, int weight, int skill){
    Town* p = (Town*)malloc(sizeof(Town));
    p->id = id;
    p->weight = weight;
    p->skill = skill;
    return p;
}

Graph* create_graph(int num_towns, int num_edges){
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->num_towns = num_towns;
    graph->num_edges = num_edges;
    graph->edge_count = 0;

    graph->towns = (Town**)malloc(num_towns*sizeof(Town*));
    graph->edges = (Path*)malloc(num_edges*sizeof(Path));

    for(int i = 0; i < num_towns; i++){
        graph->towns[i] = NULL;
    }

    return graph;
}

void add_town(Graph* graph, int id, int weight, int skill){
    graph->towns[id-1] = create_town(id, weight, skill);
}

void add_edge(Graph* graph, int id1, int id2, int dist){
    graph->edges[graph->edge_count].id1 = id1;
    graph->edges[graph->edge_count].id2 = id2;
    graph->edges[graph->edge_count].dist = dist;
    graph->edge_count++;
}

void free_graph(Graph* graph){
    if(!graph) return;

    for(int i = 0; i < graph->num_towns; i++){
        if(graph->towns[i] != NULL){
            free(graph->towns[i]);
        }
    }

    free(graph->edges);
    free(graph->towns);
    free(graph);
}

void print_graph(Graph* graph){
    for(int i = 0; i < graph->num_towns; i++){
        Town* t = graph->towns[i];
        printf("Town %d -> Weight %d -> Skill %d\n", t->id, t->weight, t->skill);
    }

    printf("\n");

    for(int i = 0; i < graph->num_edges; i++){
        Path e = graph->edges[i];
        printf("%d <-> %d -> dist %d\n", e.id1, e.id2, e.dist);
    }
    printf("\n");
}