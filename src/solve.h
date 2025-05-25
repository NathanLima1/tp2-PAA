typedef struct {
    int value;
    int q; // quantidade
    int prev_c; // quantidade anterior
    int prev_d;
    int prev; // Vértice anterior
} DpItem;

typedef struct {
    DpItem ***data;
    int dist; // Distancia restante
    int capacidade; // Capacidade restante
    int vertice; // Vértice
} Dp;

typedef struct {
    int w;
    int v;
} Town;

typedef struct {
    int **data;
    int num_vertices;
    Town *towns;
} Graph;

Dp *dp_init(int profundidade, int num_vertices, int capacidade);
void calc(Dp *dp, Graph *g);
Graph *init_graph(int num_vertices);
void add_conn(Graph *graph, int id1, int id2, int dist);
void reconstruir(Dp *dp); // Reconstrói a solução com base na matriz da DP
void minimizar_solucao(int *solucao, int n); // Remove os ciclos redundantes da solução