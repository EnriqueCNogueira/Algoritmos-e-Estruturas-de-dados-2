#include <stdio.h>
#include <stdlib.h>
 
#define MAX 1000
 
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
Tree* Balance(Tree *root){
    if (root == NULL) return NULL;
 
    UpdateHeight(root);
    int balance = Height(root->lef) - Height(root->rig);
 
    if (balance > 1) {  
        if (Height(root->lef->lef) >= Height(root->lef->rig)) {
            root = RotateR(root);
        } 
        else {
            root->lef = RotateL(root->lef);
            root = RotateR(root);
        }
    } 
    else if (balance < -1) {
        if (Height(root->rig->rig) >= Height(root->rig->lef)) {
            root = RotateL(root);
        } 
        else {
            root->rig = RotateR(root->rig);
            root = RotateL(root);
        }
    }
    return root;
}
 
// Insere um valor x e balanceia
Tree* Insert(Tree *root, int x){
    if (root == NULL) {
        Tree *temp = (Tree*)malloc(sizeof(Tree));
        temp->data = x;
        temp->lef = temp->rig = NULL;
        temp->dad = NULL;
        temp->height = 1;
        return temp;
    }
 
    if (x <= root->data) {
        root->lef = Insert(root->lef, x);
        root->lef->dad = root;
    } 
    else {
        root->rig = Insert(root->rig, x);
        root->rig->dad = root;
    }
    return Balance(root);
}
 
// Remove um valor x e balanceia
Tree* Remove(Tree *root, int x){
    if (x < root->data) {
        root->lef = Remove(root->lef, x);
        if (root->lef) 
            root->lef->dad = root;
    } 
    else if (x > root->data) {
        root->rig = Remove(root->rig, x);
        if (root->rig) 
            root->rig->dad = root;
    } 
    else {
        if (root->lef == NULL) {
            Tree *temp = root->rig;
            if (temp) temp->dad = root->dad;
            free(root);
            return temp;
        } 
        else if (root->rig == NULL) {
            Tree *temp = root->lef;
            if (temp) temp->dad = root->dad;
            free(root);
            return temp;
        }
 
        Tree *temp = root->rig;  
        while (temp->lef != NULL) 
            temp = temp->lef;
 
        root->data = temp->data;
        root->rig = Remove(root->rig, temp->data);
        if (root->rig) root->rig->dad = root;
    }
    return Balance(root);
}
 
// Busca um valor x na árvore
Tree* Search(Tree *root, int x){
    if (root == NULL)
        return NULL;
 
    if (x < root->data)
        return Search(root->lef, x);
    if (x > root->data)
        return Search(root->rig, x);
 
    return root;
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
    int i, j = 0, x, y, h, hl, hr, ha, hla, hra, a, b, v[MAX];
    for (i = 0; i < MAX; i++) 
        v[i] = -1;  
 
    // Inserção de valores na árvore
    while (scanf("%d", &x) == 1) {
        if (x < 0)  
            break;         
        root = Insert(root, x);
    }
 
    // Altura da árvore antes das mudanças
    int hb  = root->height;
    int hlb = root->lef ? root->lef->height : 0;
    int hrb = root->rig ? root->rig->height : 0;
 
 
    // Inserção e remoção de valores na árvore 
    while (scanf("%d", &y) == 1) {
        if (y < 0) 
            break;         
        else if (Search(root, y) == NULL)
            root = Insert(root, y);
        else
            root = Remove(root, y);
    }
 
    // Altura da árvore após das mudanças
    if (root != NULL){
        ha  = root->height;
        hla = root->lef ? root->lef->height : 0;
        hra = root->rig ? root->rig->height : 0;
    }
 
    // Leitura do intervalo [a, b]
    scanf("%d %d", &a, &b);
 
    // Imprime as alturas da árvore antes e depois das mudanças
    printf("%d, %d, %d\n", hb-1, hlb, hrb);
 
    if (root == NULL) {
        printf("ARVORE VAZIA\nNADA A EXIBIR\n");
        return 0;
    } else {
        printf("%d, %d, %d\n", ha-1, hla, hra);
    }
 
    // Imprime os valores do intervalo presenter na árvore
    for (i = a; i <= b; i++) {
        if (Search(root, i) != NULL) {
            if (j == 0) printf("%d", i);
            else printf(", %d", i);
            v[j++] = i;
        }
    }
 
    // Imprime as alturas dos nós encontrados
    if (v[0] == -1) {
        printf("NADA A EXIBIR\n");
        FreeTree(root);
        return 0;
    }
    else {
        printf("\n");
        for (int k = 0; k < MAX && v[k] != -1; k++) {
            Tree *temp = Search(root, v[k]);
            if (temp != NULL) {
                h  = Height(temp);
                hl = Height(temp->lef);
                hr = Height(temp->rig);
                printf("%d, %d, %d\n", h-1, hl, hr);
            }
        }
    }
 
    FreeTree(root);
    return 0;
}
