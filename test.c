#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

#define VERTICES 20000
#define ARESTAS 100000
#define INF INT_MAX

// ---------------- MATRIZ DE ADJACÊNCIA ----------------

int grafo_matriz[VERTICES][VERTICES];

void dijkstra_matriz(int origem, int dist[]) {
    bool visitado[VERTICES] = {false};

    for (int i = 0; i < VERTICES; i++)
        dist[i] = INF;
    dist[origem] = 0;

    for (int count = 0; count < VERTICES - 1; count++) {
        int u = -1;
        int min = INF;
        for (int v = 0; v < VERTICES; v++)
            if (!visitado[v] && dist[v] <= min) {
                min = dist[v];
                u = v;
            }

        if (u == -1) break;
        visitado[u] = true;

        for (int v = 0; v < VERTICES; v++) {
            if (!visitado[v] && grafo_matriz[u][v] &&
                dist[u] != INF &&
                dist[u] + grafo_matriz[u][v] < dist[v]) {
                dist[v] = dist[u] + grafo_matriz[u][v];
            }
        }
    }
}

// ---------------- HEAP + LISTA DE ADJACÊNCIA ----------------

typedef struct AdjNode {
    int dest, peso;
    struct AdjNode* prox;
} AdjNode;

typedef struct {
    AdjNode* cabeca;
} ListaAdj;

ListaAdj grafo_lista[VERTICES];

void adicionar_aresta_lista(int src, int dest, int peso) {
    AdjNode* novo = (AdjNode*)malloc(sizeof(AdjNode));
    novo->dest = dest;
    novo->peso = peso;
    novo->prox = grafo_lista[src].cabeca;
    grafo_lista[src].cabeca = novo;
}

// Min-heap
typedef struct {
    int vertice, dist;
} HeapNode;

int heap_size = 0;
HeapNode heap[VERTICES];
int pos[VERTICES];

void trocar(int i, int j) {
    HeapNode temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
    pos[heap[i].vertice] = i;
    pos[heap[j].vertice] = j;
}

void min_heapify(int i) {
    int menor = i, esq = 2*i+1, dir = 2*i+2;
    if (esq < heap_size && heap[esq].dist < heap[menor].dist) menor = esq;
    if (dir < heap_size && heap[dir].dist < heap[menor].dist) menor = dir;
    if (menor != i) {
        trocar(i, menor);
        min_heapify(menor);
    }
}

HeapNode extrair_min() {
    HeapNode raiz = heap[0];
    heap[0] = heap[--heap_size];
    pos[heap[0].vertice] = 0;
    min_heapify(0);
    return raiz;
}

void diminuir_dist(int v, int dist) {
    int i = pos[v];
    heap[i].dist = dist;
    while (i && heap[i].dist < heap[(i - 1) / 2].dist) {
        trocar(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

bool esta_no_heap(int v) {
    return pos[v] < heap_size;
}

void dijkstra_heap(int origem, int dist[]) {
    for (int v = 0; v < VERTICES; v++) {
        dist[v] = INF;
        heap[v].vertice = v;
        heap[v].dist = INF;
        pos[v] = v;
    }

    heap[origem].dist = dist[origem] = 0;
    heap_size = VERTICES;

    for (int i = 0; i < VERTICES; i++)
        heap[i] = (HeapNode){.vertice = i, .dist = dist[i]};
    
    while (heap_size) {
        HeapNode minNode = extrair_min();
        int u = minNode.vertice;

        AdjNode* atual = grafo_lista[u].cabeca;
        while (atual) {
            int v = atual->dest;
            if (esta_no_heap(v) && dist[u] != INF &&
                dist[u] + atual->peso < dist[v]) {
                dist[v] = dist[u] + atual->peso;
                diminuir_dist(v, dist[v]);
            }
            atual = atual->prox;
        }
    }
}

// ---------------- GERADOR E TESTE ----------------

void gerar_grafo_aleatorio() {
    srand(42);
    for (int i = 0; i < ARESTAS; i++) {
        int u = rand() % VERTICES;
        int v = rand() % VERTICES;
        int peso = 1 + rand() % 10;

        if (u != v) {
            grafo_matriz[u][v] = peso;
            grafo_matriz[v][u] = peso;

            adicionar_aresta_lista(u, v, peso);
            adicionar_aresta_lista(v, u, peso);
        }
    }
}

int main() {
    printf("Gerando grafo com %d vértices e %d arestas...\n", VERTICES, ARESTAS);
    gerar_grafo_aleatorio();

    int dist_matriz[VERTICES];
    int dist_heap[VERTICES];

    clock_t inicio, fim;

    // Matriz
    inicio = clock();
    dijkstra_matriz(0, dist_matriz);
    fim = clock();
    double tempo_matriz = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo Dijkstra (Matriz): %.4f segundos\n", tempo_matriz);

    // Heap
    inicio = clock();
    dijkstra_heap(0, dist_heap);
    fim = clock();
    double tempo_heap = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo Dijkstra (Heap):   %.4f segundos\n", tempo_heap);

    return 0;
}
