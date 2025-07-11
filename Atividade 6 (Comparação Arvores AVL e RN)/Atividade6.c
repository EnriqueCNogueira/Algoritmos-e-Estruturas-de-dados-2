#include <stdio.h>
#include <stdlib.h>
 
typedef struct nodeAVL {
    int data, height;
    struct nodeAVL *left, *right, *parent;
} TreeAVL;
 
typedef struct nodeRN {
    int data, color; // 0 = RED, 1 = BLACK
    struct nodeRN *left, *right, *parent;
} TreeRN;
 
#define RED 0
#define BLACK 1
 
int HeightAVL(TreeAVL *rootAVL){
    if (rootAVL == NULL)
        return 0;
    else
        return rootAVL->height;
}
 
void UpdateHeight(TreeAVL *rootAVL) {
    int hl = HeightAVL(rootAVL->left);
    int hr = HeightAVL(rootAVL->right);
    if (hl > hr)
        rootAVL->height = hl + 1;
    else
        rootAVL->height = hr + 1;
}
 
TreeAVL* RotateLeftAVL(TreeAVL *rootAVL) {
    TreeAVL *temp = rootAVL->right;
    rootAVL->right = temp->left;
    if (temp->left)
        temp->left->parent = rootAVL;
    temp->left = rootAVL;
    temp->parent = rootAVL->parent;
    rootAVL->parent = temp;
    if (temp->parent) {
        if (temp->parent->left == rootAVL)
            temp->parent->left = temp;
        else if (temp->parent->right == rootAVL)
            temp->parent->right = temp;
    }
    UpdateHeight(rootAVL);
    UpdateHeight(temp);
    return temp;
}
 
TreeAVL* RotateRightAVL(TreeAVL *rootAVL) {
    TreeAVL *temp = rootAVL->left;
    rootAVL->left = temp->right;
    if (temp->right)
        temp->right->parent = rootAVL;
    temp->right = rootAVL;
    temp->parent = rootAVL->parent;
    rootAVL->parent = temp;
    if (temp->parent) {
        if (temp->parent->left == rootAVL)
            temp->parent->left = temp;
        else if (temp->parent->right == rootAVL)
            temp->parent->right = temp;
    }
    UpdateHeight(rootAVL);
    UpdateHeight(temp);
    return temp;
}
 
TreeAVL* BalanceAVL(TreeAVL *rootAVL, int *rotateAVL) {
    if (rootAVL == NULL) return NULL;
 
    UpdateHeight(rootAVL);
    int balance = HeightAVL(rootAVL->left) - HeightAVL(rootAVL->right);
 
    if (balance > 1) {
        if (HeightAVL(rootAVL->left->left) >= HeightAVL(rootAVL->left->right)) {
            rootAVL = RotateRightAVL(rootAVL);
            (*rotateAVL)++;
        } else {
            rootAVL->left = RotateLeftAVL(rootAVL->left);
            rootAVL = RotateRightAVL(rootAVL);
            (*rotateAVL)++;
        }
    } else if (balance < -1) {
        if (HeightAVL(rootAVL->right->right) >= HeightAVL(rootAVL->right->left)) {
            rootAVL = RotateLeftAVL(rootAVL);
            (*rotateAVL)++;
        } else {
            rootAVL->right = RotateRightAVL(rootAVL->right);
            rootAVL = RotateLeftAVL(rootAVL);
            (*rotateAVL)++;
        }
    }
    return rootAVL;
}
 
TreeAVL* InsertAVL(TreeAVL *rootAVL, int x, int *rotateAVL) {
    if (rootAVL == NULL) {
        TreeAVL *temp = (TreeAVL*)malloc(sizeof(TreeAVL));
        temp->data = x;
        temp->left = temp->right = NULL;
        temp->parent = NULL;
        temp->height = 1;
        return temp;
    }
 
    if (x <= rootAVL->data) {
        rootAVL->left = InsertAVL(rootAVL->left, x, rotateAVL);
        rootAVL->left->parent = rootAVL;
    } else {
        rootAVL->right = InsertAVL(rootAVL->right, x, rotateAVL);
        rootAVL->right->parent = rootAVL;
    }
    return BalanceAVL(rootAVL, rotateAVL);
}
 
void FreeTreeAVL(TreeAVL *rootAVL) {
    if (rootAVL == NULL) return;
    FreeTreeAVL(rootAVL->left);
    FreeTreeAVL(rootAVL->right);
    free(rootAVL);
}
 
void RotateLeftRN(TreeRN **root, TreeRN *x) {
    TreeRN *y = x->right;
    if (y == NULL) return;
 
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
 
    if (x->parent == NULL) {
        *root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
 
    y->left = x;
    x->parent = y;
}
 
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
    TreeAVL *rootAVL = NULL;
    TreeRN *rootRN = NULL;
    int x, rotateRN=0, colorRN=0, rotateAVL=0;
 
    // Inserção de valores nas árvores 
    while (1) {
        scanf("%d", &x);
        if (x == -1) break;  
        rootAVL = InsertAVL(rootAVL, x, &rotateAVL);
        InsertRN(&rootRN, x, &rotateRN, &colorRN);
    }
 
    // Imprime a altura da árvore AVL
    int height=0, leftHeight=0, rightHeight=0;
    height = HeightAVL(rootAVL);
    leftHeight = HeightAVL(rootAVL->left);
    rightHeight = HeightAVL(rootAVL->right);
    printf("%d, %d, %d\n", height - 1, leftHeight, rightHeight);
 
    // Imprime a altura da árvore rubro-negra
    height=0, leftHeight=0, rightHeight=0;
    height = HeightRN(rootRN);
    leftHeight = HeightRN(rootRN->left);
    rightHeight = HeightRN(rootRN->right);
    printf("%d, %d, %d\n", height - 1, leftHeight, rightHeight);
 
    // Imprime a altura preta da árvore
    int blackHeight = BlackHeight(rootRN);
    printf("%d\n", blackHeight);
 
    // Imprime o número de cores alteradas e rotações realizadas
    printf("%d, %d, %d\n", colorRN, rotateRN, rotateAVL);
 
    // Libera a memória
    FreeTreeAVL(rootAVL);
    FreeTreeRN(&rootRN);
 
    return 0;
}
