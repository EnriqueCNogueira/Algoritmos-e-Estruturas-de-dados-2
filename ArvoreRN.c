#include <stdio.h>
#include <stdlib.h>
 
typedef struct nodeRN {
    int data, color; // 0 = RED, 1 = BLACK
    struct nodeRN *left, *right, *parent;
} TreeRN;
 
#define RED 0
#define BLACK 1
 
// Rotação à esquerda
TreeRN *RotateLeftRN(TreeRN *root, TreeRN *x) {
    TreeRN *y = x->right;
    if (y == NULL) return root;
 
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
 
    if (x->parent == NULL) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
 
    y->left = x;
    x->parent = y;
    return root;
}
 
// Rotação à direita
TreeRN *RotateRightRN(TreeRN *root, TreeRN *x) {
    TreeRN *y = x->left;
    if (y == NULL) return root;
 
    x->left = y->right;
    if (y->right != NULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
 
    if (x->parent == NULL) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
 
    y->right = x;
    x->parent = y;
    return root;
}
 
// Balanceia a árvore rubro-negra após inserção.
TreeRN *BalanceRN(TreeRN *root, TreeRN *node, int *rotateRN, int *colorRN) {
    while (node->parent != NULL && node->parent->color == RED) {
        TreeRN *father = node->parent;
        TreeRN *grandpa = father->parent;
        if (grandpa == NULL) break;

        if (father == grandpa->left) {
            TreeRN *uncle = grandpa->right;
            if (uncle != NULL && uncle->color == RED) {
                // Caso 1: tio é vermelho
                if (father->color != BLACK) {
                    father->color = BLACK;
                    (*colorRN)++;
                }
                if (uncle->color != BLACK) {
                    uncle->color = BLACK;
                    (*colorRN)++;
                }
                if (grandpa != root && grandpa->color != RED) {
                    grandpa->color = RED;
                    (*colorRN)++;
                }
                node = grandpa;
            } else {
                // Caso 2 e 3
                if (node == father->right) {
                    node = father;
                    root = RotateLeftRN(root, node);
                    (*rotateRN)++;
                    father = node->parent;
                    grandpa = (father ? father->parent : NULL);
                }
                if (father != NULL && grandpa != NULL) {
                    if (father->color != BLACK) {
                        father->color = BLACK;
                        (*colorRN)++;
                    }
                    if (grandpa->color != RED) {
                        grandpa->color = RED;
                        (*colorRN)++;
                    }
                    root = RotateRightRN(root, grandpa);
                    (*rotateRN)++;
                }
            }
        } else {
            // Espelhado: father == grandpa->right
            TreeRN *uncle = grandpa->left;
            if (uncle != NULL && uncle->color == RED) {
                // Caso 1 espelhado
                if (father->color != BLACK) {
                    father->color = BLACK;
                    (*colorRN)++;
                }
                if (uncle->color != BLACK) {
                    uncle->color = BLACK;
                    (*colorRN)++;
                }
                if (grandpa != root) {
                    if (grandpa->color != RED) {
                        grandpa->color = RED;
                        (*colorRN)++;
                    }
                } else {
                    if (grandpa->color != BLACK) {
                        grandpa->color = BLACK;
                        (*colorRN)++;
                    }
                }
                node = grandpa;
            } else {
                // Caso 2 e 3 espelhado
                if (node == father->left) {
                    node = father;
                    root = RotateRightRN(root, node);
                    (*rotateRN)++;
                    father = node->parent;
                    grandpa = (father ? father->parent : NULL);
                }
                if (father != NULL && grandpa != NULL) {
                    if (father->color != BLACK) {
                        father->color = BLACK;
                        (*colorRN)++;
                    }
                    if (grandpa->color != RED) {
                        grandpa->color = RED;
                        (*colorRN)++;
                    }
                    root = RotateLeftRN(root, grandpa);
                    (*rotateRN)++;
                }
            }
        }
    }

    // Garante que a raiz seja preta
    if (root != NULL && root->color != BLACK) {
        root->color = BLACK;
        (*colorRN)++;
    }

    return root;
}
 
// Insere um valor x e balanceia a árvore rubro-negra
TreeRN *InsertRN(TreeRN *root, int key, int *rotateRN, int *colorRN) {
    TreeRN *node = (TreeRN *)malloc(sizeof(TreeRN));
    node->data = key;
    node->color = RED;
    node->left = node->right = node->parent = NULL;
 
    TreeRN *y = NULL;
    TreeRN *x = root;
    while (x != NULL) {
        y = x;
        if (node->data < x->data) {
            x = x->left;
        } else if (node->data > x->data) {
            x = x->right;
        } else {
            /* Já existe descarta */
            free(node);
            return root;
        }
    }
 
    node->parent = y;
    if (y == NULL) {
        root = node;
    } else if (node->data < y->data) {
        y->left = node;
    } else {
        y->right = node;
    }
 
    root = BalanceRN(root, node, rotateRN, colorRN);
    return root;
}
 
// Calcula a altura da árvore rubro-negra
int HeightRN(TreeRN *root) {
    if (root == NULL) return 0;
    int hl = HeightRN(root->left);
    int hr = HeightRN(root->right);
    return (hl > hr ? hl : hr) + 1;
}
 
// Calcula a altura preta da árvore rubro-negra
int BlackHeight(TreeRN *root) {
    if (root == NULL) return 0;
    int bh = BlackHeight(root->left);
    return (root->color == BLACK ? bh + 1 : bh);
}
 
// Libera todos os nós da árvore rubro-negra
void FreeTreeRN(TreeRN *root) {
    if (root == NULL) return;
    FreeTreeRN(root->left);
    FreeTreeRN(root->right);
    free(root);
}
 
int main() {
    TreeRN *rootRN = NULL;
    int x, rotateRN=0, colorRN=0;
 
    // Inserção de valores nas árvores 
    while (scanf("%d", &x) == 1 && x != -1) {
        rootRN = InsertRN(rootRN, x, &rotateRN, &colorRN);
    }
 
    // Imprime a altura da árvore rubro-negra
    int height=0, leftHeight=0, rightHeight=0;
    height = HeightRN(rootRN);
    leftHeight = HeightRN(rootRN->left);
    rightHeight = HeightRN(rootRN->right);
    printf("%d, %d, %d\n", height - 1, leftHeight, rightHeight);
 
    // Imprime a altura preta da árvore
    int blackHeight = BlackHeight(rootRN);
    printf("%d\n", blackHeight);
 
    // Imprime o número de cores alteradas e rotações realizadas
    printf("%d, %d\n", colorRN, rotateRN);
 
    // Libera a memória
    FreeTreeRN(rootRN);
 
    return 0;
}