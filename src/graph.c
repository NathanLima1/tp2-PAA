#include "graph.h"

Town* create_town(int id, int weight, int skill){
    Town* p = (Town*)malloc(sizeof(Town));
    p->id = id;
    p->weight = weight;
    p->skill = skill;
    return p;
}

Node* create_node(Town* town, int dist){
    Node* node = (Node*)malloc(sizeof(Node));
    node->p= town;
    node->dist = dist;
    node->next = NULL;
    return node;
}

Graph* create_graph(int num_towns){
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->num_towns = num_towns;
    graph->towns = (Town**)malloc(num_towns*sizeof(Town*));
    graph->edges = (Node**)malloc(num_towns*sizeof(Node*));

    for(int i = 0; i < num_towns; i++){
        graph->towns[i] = NULL;
        graph->edges[i] = NULL;
    }

    return graph;
}

void add_town(Graph* graph, int id, int weight, int skill){
    graph->towns[id] = create_town(id, weight, skill);
}

void add_edge(Graph* graph, int id1, int id2, int dist){
    Town* p1 = graph->towns[id1];
    Town* p2 = graph->towns[id2];

    Node* n1 = create_node(p2, dist);
    n1->next = graph->edges[id1];
    graph->edges[id1] = n1;

    Node* n2 = create_node(p1, dist);
    n2->next = graph->edges[id2];
    graph->edges[id2] = n2;
}

void free_graph(Graph* graph){
    if(!graph) return;

    for(int i = 0; i < graph->num_towns; i++){
        Node* current = graph->edges[i];
        while(current != NULL){
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }

    for(int i = 0; i < graph->num_towns; i++){
        if(graph->towns[i] != NULL){
            free(graph->towns[i]);
        }
    }

    free(graph->edges);
    free(graph->towns);
    free(graph);
}