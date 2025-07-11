/*Anotações:
SelectionSort (Troca o menor elemento com o primeiro):
- Conferir se menor = i

BubbleSort (Compara 2 a 2 e troca se necessário, ordenando do maior para o menor):
- se não fez nenhuma troca, não precisa continuar a ordenação (flag)

InsertionSort (Insere o elemento analisado na posição correta do vetor ordenado atrás dele):
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int const MAX = 1000;

void SelectionSort(int v[], int n, int* comparacao, int* troca) {
    for (int i = 0; i < n - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < n; j++) {
            (*comparacao)++;
            if (v[j] < v[menor])
                menor = j;
        }
        if (menor != i) { 
            (*troca)++;
            int temp = v[i];
            v[i] = v[menor];
            v[menor] = temp;
        }
    }
}

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

int main() {
    int v1[MAX], v2[MAX], v3[MAX], n;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &v1[i]);
        v2[i] = v1[i];
        v3[i] = v1[i];
    }

    int comp_sel = 0, troca_sel = 0;
    SelectionSort(v1, n, &comp_sel, &troca_sel);
    printf("%d %d\n", comp_sel, troca_sel);

    int comp_bub = 0, troca_bub = 0;
    BubbleSort(v2, n, &comp_bub, &troca_bub);
    printf("%d %d\n", comp_bub, troca_bub);

    int comp_ins = 0, troca_ins = 0;
    InsertSort(v3, n, &comp_ins, &troca_ins);
    printf("%d %d\n", comp_ins, troca_ins);

    return 0;
}
