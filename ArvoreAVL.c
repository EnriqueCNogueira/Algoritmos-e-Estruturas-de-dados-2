#include <stdio.h>
#include <stdlib.h>
 
// Estrutura do nó da árvore AVL
typedef struct node {
    int data, height;
    struct node *lef, *rig, *dad;
} Tree;
 
// Calcula a altura de um nó
int Height(Tree *root){
    if (root == NULL) 
        return 0;
    else 
        return root->height;
}
 
// Atualiza a altura de um nó
void UpdateHeight(Tree *root) {
    int hl = Height(root->lef);
    int hr = Height(root->rig);
    if (hl > hr) 
        root->height = hl + 1;
    else
        root->height = hr + 1;
}

// Rotação à esquerda
Tree* RotateL(Tree *root) {
    Tree *temp = root->rig;
    root->rig = temp->lef;
    if (temp->lef)
        temp->lef->dad = root;
    temp->lef = root;
    temp->dad = root->dad;
    root->dad = temp;
    if (temp->dad) {
        if (temp->dad->lef == root)
            temp->dad->lef = temp;
        else if (temp->dad->rig == root)
            temp->dad->rig = temp;
    }
    UpdateHeight(root);
    UpdateHeight(temp);
    return temp;
}

// Rotação à direita
Tree* RotateR(Tree *root) {
    Tree *temp = root->lef;
    root->lef = temp->rig;
    if (temp->rig)
        temp->rig->dad = root;
    temp->rig = root;
    temp->dad = root->dad;
    root->dad = temp;
    if (temp->dad) {
        if (temp->dad->lef == root)
            temp->dad->lef = temp;
        else if (temp->dad->rig == root)
            temp->dad->rig = temp;
    }
    UpdateHeight(root);
    UpdateHeight(temp);
    return temp;
}
 
// Balanceia a árvore aplicando rotações
Tree* Balance(Tree *root, int *rotate) {
    if (root == NULL) return NULL;
 
    UpdateHeight(root);
    int balance = Height(root->lef) - Height(root->rig);
 
    if (balance > 1) {  
        if (Height(root->lef->lef) >= Height(root->lef->rig)) {
            root = RotateR(root);
            (*rotate)++;
        } 
        else {
            root->lef = RotateL(root->lef);
            root = RotateR(root);
            (*rotate)++;
        }
    } 
    else if (balance < -1) {
        if (Height(root->rig->rig) >= Height(root->rig->lef)) {
            root = RotateL(root);
            (*rotate)++;
        } 
        else {
            root->rig = RotateR(root->rig);
            root = RotateL(root);
            (*rotate)++;
        }
    }
    return root;
}
 
// Insere um valor x e balanceia
Tree* Insert(Tree *root, int x, int *rotate) {
    if (root == NULL) {
        Tree *temp = (Tree*)malloc(sizeof(Tree));
        temp->data = x;
        temp->lef = temp->rig = NULL;
        temp->dad = NULL;
        temp->height = 1;
        return temp;
    }
 
    if (x <= root->data) {
        root->lef = Insert(root->lef, x, rotate);
        root->lef->dad = root;
    } 
    else {
        root->rig = Insert(root->rig, x, rotate);
        root->rig->dad = root;
    }
    return Balance(root, rotate);
}

// Libera todos os nós da árvore
void FreeTree(Tree *root) {
    if (root == NULL) return;
    FreeTree(root->lef);
    FreeTree(root->rig);
    free(root);
}

int main() {
    Tree *root = NULL;
    int x, rotate = 0;

    // Lê os valores a serem inseridos na árvore AVL
    while (1) {
        scanf("%d", &x);
        if (x == -1) break;  
        root = Insert(root, x, &rotate);
    }

    // Imprime a altura da árvore AVL
    printf("%d, %d, %d\n", 
           Height(root) - 1, 
           Height(root->lef), 
           Height(root->rig));

    // Imprime o número de rotações realizadas
    printf("%d\n", rotate);
 
    FreeTree(root);
    return 0;
}