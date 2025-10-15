#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Tree {
    int n;
    int *keys;
    struct Tree **C;
    bool leaf;
} Tree;

typedef struct BTree {
    Tree *root;
    int t;
    int m;
} BTree;

Tree *createNode(int m, bool leaf) {
    Tree *node = (Tree *)malloc(sizeof(Tree));
    if (!node) exit(EXIT_FAILURE);
    node->n = 0;
    node->leaf = leaf;
    node->keys = (int *)malloc((m - 1) * sizeof(int));
    node->C = (Tree **)malloc(m * sizeof(Tree *));
    if (!node->keys || !node->C) exit(EXIT_FAILURE);
    for (int i = 0; i < m; i++)
        node->C[i] = NULL;
    return node;
}

Tree *searchNode(Tree *x, int k) {
    int i = 0;
    while (i < x->n && k > x->keys[i])
        i++;
    if (i < x->n && x->keys[i] == k)
        return x;
    if (x->leaf)
        return NULL;
    return searchNode(x->C[i], k);
}

void splitChild(BTree *T, Tree *x, int i) {
    int t = T->t;
    Tree *y = x->C[i];
    Tree *z = createNode(T->m, y->leaf);
    z->n = t - 1;
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];
    if (!y->leaf) {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }
    y->n = t - 1;
    for (int j = x->n; j >= i + 1; j--)
        x->C[j + 1] = x->C[j];
    x->C[i + 1] = z;
    for (int j = x->n - 1; j >= i; j--)
        x->keys[j + 1] = x->keys[j];
    x->keys[i] = y->keys[t - 1];
    x->n++;
}

void insertNonFull(BTree *T, Tree *x, int k) {
    int i = x->n - 1;
    if (x->leaf) {
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->n++;
    } else {
        while (i >= 0 && k < x->keys[i])
            i--;
        i++;
        if (x->C[i]->n == 2 * T->t - 1) {
            splitChild(T, x, i);
            if (k > x->keys[i])
                i++;
        }
        insertNonFull(T, x->C[i], k);
    }
}

void BTreeInsert(BTree *T, int k) {
    Tree *r = T->root;
    if (r->n == 2 * T->t - 1) {
        Tree *s = createNode(T->m, false);
        s->C[0] = r;
        T->root = s;
        splitChild(T, s, 0);
        insertNonFull(T, s, k);
    } else {
        insertNonFull(T, r, k);
    }
}

int main() {
    int m;
    if (scanf("%d", &m) != 1) return 0;
    int minDegree = (m + 1) / 2;
    BTree T;
    T.m = m;
    T.t = minDegree;
    T.root = createNode(m, true);

    int value;
    while (scanf("%d", &value) == 1 && value != -1) {
        if (!searchNode(T.root, value))
            BTreeInsert(&T, value);
    }
    int key;
    scanf("%d", &key);

    printf("%d\n", T.root->n);

    Tree *found = searchNode(T.root, key);
    if (!found) {
        printf("Valor nao encontrado\n");
    } else {
        printf("%d\n", found->n);
        for (int i = 0; i < found->n; i++) {
            printf("%d", found->keys[i]);
            if (i < found->n - 1) printf(" ");
        }
        printf("\n");
    }
    return 0;
}