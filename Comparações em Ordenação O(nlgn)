#include <stdio.h>
#include <stdlib.h>
 
#define MAX 1000
 
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
 
int main() {
    int v1[MAX], v2[MAX], v3[MAX];
    int n, comp, i;
 
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &v1[i]);
        v2[i] = v1[i];
        v3[i] = v1[i];
    }
 
    comp = 0;
    MergeSort(0, n - 1, v1, &comp);
    for (i = 0; i < n; i++) 
        printf("%d ", v1[i]);
    printf("\n%d\n", comp);
 
    comp = 0;
    QuickSort(0, n - 1, v2, &comp);
    for (i = 0; i < n; i++) 
        printf("%d ", v2[i]);
    printf("\n%d\n", comp);
 
    comp = 0;
    QuickSortH(0, n - 1, v3, &comp);
    for (i = 0; i < n; i++) 
        printf("%d ", v3[i]);
    printf("\n%d\n", comp);
 
    return 0;
}
