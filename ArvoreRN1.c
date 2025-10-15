#include <stdio.h>
#include <stdlib.h>

typedef struct nodeRN {
    int data, color; // 0 = RED, 1 = BLACK
    struct nodeRN *left, *right, *parent;
} TreeRN;

#define RED 0
#define BLACK 1


void RotateRightRN(TreeRN **root, TreeRN *x) {
    TreeRN *y = x->left;
    if (y == NULL) return;

    x->left = y->right;
    if (y->right != NULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;

    if (x->parent == NULL) {
        *root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->right = x;
    x->parent = y;
}

void BalanceRN(TreeRN **root, TreeRN *node, int *rotateRN, int *colorRN) {
    while (node->parent != NULL && node->parent->color == RED) {
        TreeRN *father = node->parent;
        TreeRN *grandpa = father->parent;

        if (grandpa == NULL) break;

        if (father == grandpa->left) {
            TreeRN *uncle = grandpa->right;
            if (uncle != NULL && uncle->color == RED) {
                father->color = BLACK;
                uncle->color = BLACK;
                (*colorRN) += 2;
                if (grandpa != *root) {
                    grandpa->color = RED;
                    (*colorRN)++;
                }
                node = grandpa;
            } else {
                if (node == father->right) {
                    node = father;
                    RotateLeftRN(root, node);
                    (*rotateRN)++;
                    father = node->parent;
                    grandpa = father ? father->parent : NULL;
                }
                if (father != NULL && grandpa != NULL) {
                    father->color = BLACK;
                    grandpa->color = RED;
                    (*colorRN) += 2;
                    RotateRightRN(root, grandpa);
                    (*rotateRN)++;
                }
            }
        } else {
            TreeRN *uncle = grandpa->left;
            if (uncle != NULL && uncle->color == RED) {
                father->color = BLACK;
                uncle->color = BLACK;
                (*colorRN) += 2;
                if (grandpa != *root) {
                    grandpa->color = RED;
                    (*colorRN)++;
                } else {
                    grandpa->color = BLACK;
                    (*colorRN)++;
                }
                node = grandpa;
            } else {
                if (node == father->left) {
                    node = father;
                    RotateRightRN(root, node);
                    (*rotateRN)++;
                    father = node->parent;
                    grandpa = father ? father->parent : NULL;
                }
                if (father != NULL && grandpa != NULL) {
                    father->color = BLACK;
                    grandpa->color = RED;
                    (*colorRN) += 2;
                    RotateLeftRN(root, grandpa);
                    (*rotateRN)++;
                }
            }
        }
    }
    if (*root != NULL && (*root)->color == RED) {
        (*root)->color = BLACK;
        (*colorRN)++;
    }
}

void InsertRN(TreeRN **root, int key, int *rotateRN, int *colorRN) {
    TreeRN *node = (TreeRN*) malloc(sizeof(TreeRN));
    node->data = key;
    node->color = RED;
    node->left = node->right = node->parent = NULL;

    TreeRN *y = NULL;
    TreeRN *x = *root;
    while (x != NULL) {
        y = x;
        if (node->data < x->data) {
            x = x->left;
        } else if (node->data > x->data) {
            x = x->right;
        } else {
            free(node);
            return;
        }
    }

    node->parent = y;
    if (y == NULL) {
        *root = node;
    } else if (node->data < y->data) {
        y->left = node;
    } else {
        y->right = node;
    }

    BalanceRN(root, node, rotateRN, colorRN);
}

int HeightRN(TreeRN *root) {
    if (root == NULL) {
        return 0;
    }
    int h_left = HeightRN(root->left);
    int h_right = HeightRN(root->right);
    return (h_left > h_right ? h_left : h_right) + 1;
}

int BlackHeight(TreeRN *root) {
    if (root == NULL) {
        return 0;
    }
    int bh_left = BlackHeight(root->left);
    int bh_right = BlackHeight(root->right);
    int aux = (root->color == BLACK) ? 1 : 0;
    return (bh_left > bh_right ? bh_left : bh_right) + aux;
}

void FreeTreeRN(TreeRN **root) {
    if (*root == NULL) return;
    FreeTreeRN(&((*root)->left));
    FreeTreeRN(&((*root)->right));
    free(*root);
    *root = NULL;
}

int main() {
    TreeRN *rootRN = NULL;
    int x, rotateRN=0, colorRN=0;

    // Inserção de valores nas árvores 
    while (1) {
        scanf("%d", &x);
        if (x == -1) break;  
        InsertRN(&rootRN, x, &rotateRN, &colorRN);
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
    FreeTreeRN(&rootRN);

    return 0;
}