#include <stdio.h>
#include <stdlib.h>

#ifndef TRIE_H
#define TRIE_H

typedef struct Trie_node {
    int valor;
    struct Trie_node **filhos;
    int size;
} Trie_node;

#include "../include/trie.h"

Trie_node *Trie_node_init(int valor, int n);
void free_trie(Trie_node *t, int n);
int crescente(const void *a, const void*b);
int search_and_insert(Trie_node *t, int n, int *set, int set_size);

#endif
