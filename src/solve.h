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

Dp *dp_init(int profundidade, int num_vertices, int capacidade);
void calc(Dp *dp, int *w, int *v, int **g);
int **init_graph(int num_vertices);
void add_conn(int **graph, int id1, int id2, int dist);
void reconstruir(Dp *dp);