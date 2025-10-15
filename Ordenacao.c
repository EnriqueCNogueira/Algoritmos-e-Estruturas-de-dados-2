#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void BubbleSort(int v[], int n, int* comparacao, int* troca) {
    for (int i = 0; i < n - 1; i++) {
        bool flag = false;
        for (int j = 0; j < n - i - 1; j++) {
            (*comparacao)++;
            if (v[j] > v[j + 1]) {
                (*troca)++;
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
                flag = true;
            }
        }
        if(!flag) break; 
    }
}

void InsertSort(int v[], int n, int* comparacao, int* troca) {
    int chave, j;
    for (int i = 1; i < n; i++) {
        chave = v[i];
        for (j = i - 1; j >= 0; j--) {
            (*comparacao)++;
            if(v[j] > chave){
                v[j + 1] = v[j];
                (*troca)++;
            } else {
                break; 
            }
        }
        if (v[j + 1] != chave) {
            (*troca)++;
            v[j + 1] = chave;
        }
    }
}







void Troca(int v[], int a, int b) {
    int aux = v[a];
    v[a] = v[b];
    v[b] = aux;
}
 
int Mediana(int v[], int a, int b, int c) {
    if (v[a] > v[b]) Troca(v, a, b);
    if (v[a] > v[c]) Troca(v, a, c);
    if (v[b] > v[c]) Troca(v, b, c);
    return b;
}
 
int Separa(int inicio, int fim, int v[], int *comp) {
    int i = inicio;
    *comp += 3;
    int pivo = Mediana(v, inicio, (inicio + fim) / 2, fim);
    int valorpivo = v[pivo];
    Troca(v, pivo, fim);
 
    for (int k = inicio; k < fim; k++) {
        (*comp)++;
        if (v[k] <= valorpivo) {
            Troca(v, i, k);
            i++;
        }
    }
    Troca(v, i, fim);
    return i;
}
 
void QuickSort(int inicio, int fim, int v[], int *comp) {
    if (inicio < fim) {
        int meio = Separa(inicio, fim, v, comp);
        QuickSort(inicio, meio - 1, v, comp);
        QuickSort(meio + 1, fim, v, comp);
    }
}
 
void QuickSortH(int inicio, int fim, int v[], int *comp) {
    if (fim - inicio < 5) {
        for (int i = inicio + 1; i <= fim; i++) {
            int chave = v[i];
            int j = i - 1;
            while (j >= inicio) {
                (*comp)++;
                if (v[j] > chave) {
                    v[j + 1] = v[j];
                    j--;
                } else {
                    break;
                }
            }
            v[j + 1] = chave;
        }
    } else {
        int meio = Separa(inicio, fim, v, comp);
        QuickSortH(inicio, meio - 1, v, comp);
        QuickSortH(meio + 1, fim, v, comp);
    }
}
 
void Intercala(int inicio, int meio, int fim, int v[], int *comp) {
    int i = inicio, j = meio + 1, k = 0;
    int tam = fim - inicio + 1;
    int *w = malloc(tam * sizeof(int));
 
    while (i <= meio && j <= fim) {
        (*comp)++;
        if (v[i] <= v[j])
            w[k++] = v[i++];
        else
            w[k++] = v[j++];
    }
    
    while (i <= meio) {
        (*comp)++;
        w[k++] = v[i++];
    }
 
    while (j <= fim) {
        (*comp)++;
        w[k++] = v[j++];
    }
 
    for (i = inicio; i <= fim; i++)
        v[i] = w[i - inicio];
 
    free(w);
}
 
void MergeSort(int inicio, int fim, int v[], int *comp) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        MergeSort(inicio, meio, v, comp);
        MergeSort(meio + 1, fim, v, comp);
        Intercala(inicio, meio, fim, v, comp);
    }
}