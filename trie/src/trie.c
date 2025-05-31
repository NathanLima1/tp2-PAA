#include "../include/trie.h"

Trie_node *Trie_node_init(int valor, int n) {
    Trie_node *t = (Trie_node*)malloc(sizeof(Trie_node));
    t->valor = valor;
    t->filhos = (Trie_node**)malloc(sizeof(Trie_node*) * n);
    for (int i = 0; i < n; i++) {
        t->filhos[i] = NULL;
    }
    return t;
}

void free_trie(Trie_node *t, int n) {
    for (int i = 0; i < n; i++) {
        if (t->filhos[i] != NULL) {
            free_trie(t->filhos[i], n);
        }
    }
    free(t->filhos);
    free(t);
}

int crescente(const void *a, const void*b) {
    return (*(int*)a - *(int*)b);
}


int search_and_insert(Trie_node *t, int n, int *set, int set_size) {
    qsort(set, set_size, sizeof(int), crescente);
    int encontrado = 1;
    for (int i = 0; i < set_size; i++) {
        for (int j = 0; j < n; j++) {

            if (t->filhos[j] == NULL) {
                t->filhos[j] = Trie_node_init(set[i], n);
                t = t->filhos[j];
                encontrado = 0;
                break;
            }

            if (t->filhos[j]->valor == set[i]) {
                t = t->filhos[j];
                break;
            }

        }
    }

    return encontrado;
}