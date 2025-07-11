#include <stdio.h>
#include <stdlib.h>
 
#define EMPTY -10
#define REMOVED -100
 
// Funções de transformação
int h1(int key, int size) {
    return key % size;
}
 
int h2(int key, int size) {
    return 1 + (key % (size - 1));
}
 
int h(int key, int i, int size) {
    return (h1(key, size) + i * h2(key, size)) % size;
}
 
// Insere a chave na Tabela Hash
void Insert(int *Hash, int key, int size) {
    int i = 0;
    while (i < size) {
        int pos = h(key, i, size);
        if (Hash[pos] == EMPTY || Hash[pos] == REMOVED) {
            Hash[pos] = key;
            return;
        }
        i++;
    }
}
 
// Procura e remove a chave na Tabela Hash
int Search(int *Hash, int key, int size) {
    int i = 0;
    int found = 0;
    int comp = 0;
    while (comp < size) {
        int position = h(key, i, size);
        if (Hash[position] == EMPTY) {
            break;
        } else if (Hash[position] == key) {
            Hash[position] = REMOVED;
            found = 1;
        }
        i++;
        comp++;
    }
    return found;
}
 
int main() {
    int key, searchKey, size;
 
    // Lê o tamanho da tabela e inicializa
    scanf("%d", &size);
 
    int *Hash;
    Hash = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        Hash[i] = EMPTY;
    }
 
    // Lê os valores a serem inseridos
    while (scanf("%d", &key) == 1 && key != -1) {
        Insert(Hash, key, size);
    }
 
    // Lê e procura a chave na tabela
    scanf("%d", &searchKey);
 
    int keyFound = Search(Hash, searchKey, size);
    if (!keyFound) {
        printf("Valor nao encontrado\n");
    }
 
    // Imprime a tabela
    for (int i = 0; i < size; i++) {
        if (Hash[i] == EMPTY) {
            printf("\\");
        } else if (Hash[i] == REMOVED) {
            printf("D");
        } else {
            printf("%d", Hash[i]);
        }
        if (i < size - 1) {
            printf(" ");
        }
    }
    printf("\n");
 
    // Libera a mamória
    free(Hash);
    return 0;
}
