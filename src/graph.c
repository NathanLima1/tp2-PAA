#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define INF ((int)((unsigned)(~0) >> 1))

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

// O grafo poderá ser uma matriz de adjacência, pois será completo
void dijkstra(int **graph, int start, int n, int **result) {
    int *dists = malloc(sizeof(int) * n);
    int *abertos = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        dists[i] = INF;
        abertos[i] = 1;
    }

    dists[start] = 0;

    while (1) {
        int min_dist = INF;
        int min_dist_idx = -1;
        for (int i = 0; i < n; i++) {
            // Usar heap aqui
            if (dists[i] < min_dist && abertos[i]) {
                min_dist = dists[i];
                min_dist_idx = i;
            }
        }

        if (min_dist_idx == -1) {
            break;
        }
        abertos[min_dist_idx] = 0;

        for (int i = 0; i < n; i++) {
            if (graph[min_dist_idx][i]) {
                if (min_dist + graph[min_dist_idx][i] < dists[i]) {
                    dists[i] = min_dist + graph[min_dist_idx][i];

                    // Atualiza o gráfico resultante completo
                    result[start][i] = dists[i];
                    result[i][start] = dists[i];
                }
            }
        }
    }

    free(dists);
    free(abertos);
}