#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
// Define a estrutura do nó
typedef struct node {
    int data;
    int color; // 0 = RED, 1 = BLACK
    struct node *left, *right, *parent;
} Tree;
 
#define RED   0
#define BLACK 1
 
Tree *NIL;
 
// Rotaciona à esquerda
void LeftRotate(Tree **root, Tree *node1) {
    Tree *node2 = node1->right;
    node1->right = node2->left;
    if (node2->left != NIL) {
        node2->left->parent = node1;
    }
    node2->parent = node1->parent;
 
    if (node1->parent == NIL) {
        *root = node2;
    } else if (node1 == node1->parent->left) {
        node1->parent->left = node2;
    } else {
        node1->parent->right = node2;
    }
    node2->left = node1;
    node1->parent = node2;
}
 
// Rotaciona à direita
void RightRotate(Tree **root, Tree *node1) {
    Tree *node2 = node1->left;
    node1->left = node2->right;
    if (node2->right != NIL) {
        node2->right->parent = node1;
    }
    node2->parent = node1->parent;
 
    if (node1->parent == NIL) {
        *root = node2;
    } else if (node1 == node1->parent->left) {
        node1->parent->left = node2;
    } else {
        node1->parent->right = node2;
    }
    node2->right = node1;
    node1->parent = node2;
}
 
// Cria um novo nó
Tree *CreateNode(int data) {
    Tree *node1 = (Tree *)malloc(sizeof(Tree));
    node1->data = data;
    node1->color = RED;
    node1->left = NIL;
    node1->right = NIL;
    node1->parent = NIL;
    return node1;
}
 
// Balanceia a inserção
void BalanceInsert(Tree **root, Tree *node1) {
    while (node1->parent->color == RED) {
        if (node1->parent == node1->parent->parent->left) {
            Tree *node2 = node1->parent->parent->right;
            if (node2->color == RED) {
                node1->parent->color = BLACK;
                node2->color = BLACK;
                node1->parent->parent->color = RED;
                node1 = node1->parent->parent;
            } else {
                if (node1 == node1->parent->right) {
                    node1 = node1->parent;
                    LeftRotate(root, node1);
                }
                node1->parent->color = BLACK;
                node1->parent->parent->color = RED;
                RightRotate(root, node1->parent->parent);
            }
        } else {
            Tree *node2 = node1->parent->parent->left;
            if (node2->color == RED) {
                node1->parent->color = BLACK;
                node2->color = BLACK;
                node1->parent->parent->color = RED;
                node1 = node1->parent->parent;
            } else {
                if (node1 == node1->parent->left) {
                    node1 = node1->parent;
                    RightRotate(root, node1);
                }
                node1->parent->color = BLACK;
                node1->parent->parent->color = RED;
                LeftRotate(root, node1->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}
 
// Insere um valor na árvore
void Insert(Tree **root, int data) {
    Tree *node1 = CreateNode(data);
    Tree *node2 = NIL;
    Tree *node3 = *root;
 
    while (node3 != NIL) {
        node2 = node3;
        if (node1->data < node3->data) {
            node3 = node3->left;
        } else {
            node3 = node3->right;
        }
    }
    node1->parent = node2;
    if (node2 == NIL) {
        *root = node1;
    } else if (node1->data < node2->data) {
        node2->left = node1;
    } else {
        node2->right = node1;
    }
 
    BalanceInsert(root, node1);
}
 
// Transplanta subárvore
void Transplant(Tree **root, Tree *node1, Tree *node2) {
    if (node1->parent == NIL) {
        *root = node2;
    } else if (node1 == node1->parent->left) {
        node1->parent->left = node2;
    } else {
        node1->parent->right = node2;
    }
    node2->parent = node1->parent;
}
 
// Encontra o menor valor da subárvore
Tree *Lower(Tree *node) {
    while (node->left != NIL) {
        node = node->left;
    }
    return node;
}
 
// Balanceia a remoção
void BalanceRemove(Tree **root, Tree *node1) {
    while (node1 != *root && node1->color == BLACK) {
        if (node1 == node1->parent->left) {
            Tree *node2 = node1->parent->right;
            if (node2->color == RED) {
                node2->color = BLACK;
                node1->parent->color = RED;
                LeftRotate(root, node1->parent);
                node2 = node1->parent->right;
            }
            if (node2->left->color == BLACK && node2->right->color == BLACK) {
                node2->color = RED;
                node1 = node1->parent;
            } else {
                if (node2->right->color == BLACK) {
                    node2->left->color = BLACK;
                    node2->color = RED;
                    RightRotate(root, node2);
                    node2 = node1->parent->right;
                }
                node2->color = node1->parent->color;
                node1->parent->color = BLACK;
                node2->right->color = BLACK;
                LeftRotate(root, node1->parent);
                node1 = *root;
            }
        } else {
            Tree *node2 = node1->parent->left;
            if (node2->color == RED) {
                node2->color = BLACK;
                node1->parent->color = RED;
                RightRotate(root, node1->parent);
                node2 = node1->parent->left;
            }
            if (node2->right->color == BLACK && node2->left->color == BLACK) {
                node2->color = RED;
                node1 = node1->parent;
            } else {
                if (node2->left->color == BLACK) {
                    node2->right->color = BLACK;
                    node2->color = RED;
                    LeftRotate(root, node2);
                    node2 = node1->parent->left;
                }
                node2->color = node1->parent->color;
                node1->parent->color = BLACK;
                node2->left->color = BLACK;
                RightRotate(root, node1->parent);
                node1 = *root;
            }
        }
    }
    node1->color = BLACK;
}
 
// Remove um valor da árvore
void Remove(Tree **root, int data) {
    Tree *node1 = *root;
    while (node1 != NIL && node1->data != data) {
        if (data < node1->data) {
            node1 = node1->left;
        } else {
            node1 = node1->right;
        }
    }
 
    Tree *node2 = node1;
    Tree *node3;
    int node2_color = node2->color;
 
    if (node1->left == NIL) {
        node3 = node1->right;
        Transplant(root, node1, node1->right);
    } else if (node1->right == NIL) {
        node3 = node1->left;
        Transplant(root, node1, node1->left);
    } else {
        node2 = Lower(node1->right);
        node2_color = node2->color;
        node3 = node2->right;
 
        if (node2->parent == node1) {
            node3->parent = node2;
        } else {
            Transplant(root, node2, node2->right);
            node2->right = node1->right;
            node2->right->parent = node2;
        }
        Transplant(root, node1, node2);
        node2->left = node1->left;
        node2->left->parent = node2;
        node2->color = node1->color;
    }
    free(node1);
 
    if (node2_color == BLACK) {
        BalanceRemove(root, node3);
    }
}
 
// Busca um valor na árvore
Tree *Search(Tree *node, int data) {
    if (node == NIL || node->data == data) {
        return node;
    }
    if (data < node->data) {
        return Search(node->left, data);
    } else {
        return Search(node->right, data);
    }
}
 
// Calcula a altura do nó
int Height(Tree *node) {
    if (node == NIL) {
        return -1;
    }
    int hl = Height(node->left);
    int hr = Height(node->right);
    return (hl > hr ? hl : hr) + 1;
}
 
// Calcula a altura vermelha do nó (caminho com mais nós vermelhos)
int RedHeight(Tree *node) {
    if (node == NIL) return 0;
    int me = (node->color == RED);
    int rl = RedHeight(node->left);
    int rr = RedHeight(node->right);
    return me + (rl > rr ? rl : rr);
}
 
// Libera a memória da árvore
void FreeTree(Tree *node) {
    if (node != NIL) {
        FreeTree(node->left);
        FreeTree(node->right);
        free(node);
    }
}
 
int main() {
    // Inicialização do NIL (sentinela)
    NIL = (Tree *)malloc(sizeof(Tree));
    NIL->color  = BLACK;
    NIL->left   = NIL;
    NIL->right  = NIL;
    NIL->parent = NIL;
 
    Tree *root = NIL;
    int x;
 
    // Inserção de valores na árvore
    while (scanf("%d", &x) == 1 && x != -1) {
        Insert(&root, x);
    }
 
    // Imprime altura da árvore e de seus filhos
    printf("%d, %d, %d\n", Height(root), Height(root->left) + 1, Height(root->right) + 1);
 
    // Inserção ou remoção de valores
    while (scanf("%d", &x) == 1 && x != -1) {
        Tree *node = Search(root, x);
        if (node != NIL) {
            printf("%d, %d, %d\n", Height(node), Height(node->left) + 1, Height(node->right) + 1);
            Remove(&root, x);
        } else {
            Insert(&root, x);
        }
    }
 
    // Imprime altura vermelha do nó dado
    if (scanf("%d", &x) == 1) {
        Tree *node = Search(root, x);
        if (node != NIL) {
            printf("%d\n", RedHeight(node));
        } else {
            printf("Valor nao encontrado\n");
        }
    }
 
    // Libera toda a memória
    FreeTree(root);
    free(NIL);
    return 0;
}
