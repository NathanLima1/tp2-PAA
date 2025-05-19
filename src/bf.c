#include <stdio.h>
#include <stdlib.h>
#include "bf.h"

#define MAX_P 50

int path[MAX_P];
int vis[MAX_P];
int best_path[MAX_P];
int num_g_bp[MAX_P]; // number of warriors for each town;
int temp_num_g_bp[MAX_P];
int len_best_path = 0;
int best_skill = -1;

int min(int a, int b) { 
    return a < b ? a : b; 
}

Adj* adj_list[MAX_P];

void add_adj(int from, int to, int dist) {
    Adj* a = (Adj*)malloc(sizeof(Adj));
    a->to = to;
    a->dist = dist;
    a->next = adj_list[from];
    adj_list[from] = a;
}

int simulate_path(Graph* g, int* path, int len, int max_weight){
    int total_skill = 0;
    int remaining_weight = max_weight;

    for(int i = 0; i < len; i++){
        Town* t = g->towns[path[i]];
        if(t == NULL || t->weight > remaining_weight) continue;

        int max_units = remaining_weight/t->weight;
        total_skill += max_units*t->skill;
        remaining_weight -= max_units*t->weight;
        temp_num_g_bp[i] = max_units;
    }
    return total_skill;
}

void dfs(Graph* g, int u, int depth, int path_dist, int d, int max_weight){
    if(path_dist > d) return;

    int current_skill = simulate_path(g, path, depth, max_weight);
    if(current_skill > best_skill){
        best_skill = current_skill;
        len_best_path = depth;
        for(int i = 0; i < len_best_path; i++){
            best_path[i] = path[i];
            num_g_bp[i] = temp_num_g_bp[i];
        }
    }

    Adj* a = adj_list[u];

    while(a){
        int v = a->to;
        if(!vis[v]){
            vis[v] = 1;
            path[depth] = v;
            dfs(g, v, depth+1, path_dist + a->dist, d, max_weight);
            vis[v] = 0;
        }
        a = a->next;
    }
}

void solve_bf(Graph* g, int d, int w){
    for(int i = 0; i < g->num_towns; i++){
        vis[i] = 1;
        path[0] = i;
        dfs(g, i, 1, 0, d, w);
        vis[i] = 0;
    }
}

void prepare_adjacency(Graph* g) {
    for (int i = 0; i < g->edge_count; i++) {
        Path p = g->edges[i];
        add_adj(p.id1 - 1, p.id2 - 1, p.dist);
        add_adj(p.id2 - 1, p.id1 - 1, p.dist);
    }
}

void print_solution(){
    printf("%d", best_skill);
    for(int i = 0; i < len_best_path; i++){
        printf(" %d %d", best_path[i] + 1, num_g_bp[i]);
    }
    printf("\n");
}

void free_adjacency() {
    for (int i = 0; i < MAX_P; i++) {
        Adj* a = adj_list[i];
        while (a != NULL) {
            Adj* temp = a;
            a = a->next;
            free(temp);
        }
        adj_list[i] = NULL;
    }
}

void reset_globals() {
    for (int i = 0; i < MAX_P; i++) {
        path[i] = 0;
        vis[i] = 0;
        best_path[i] = 0;
        num_g_bp[i] = 0;
        temp_num_g_bp[i] = 0;
    }
    len_best_path = 0;
    best_skill = -1;
}