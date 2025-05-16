#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const long int N = 1000000;

int Separa(int p, int r, long int vet[]) {
    int c, j, k, t;
    c = vet[r];
    j = p;
    for (k = p; k < r; k++)
        if (vet[k] <= c) {
            t = vet[j], vet[j] = vet[k], vet[k] = t;
            j++;
        }
    t = vet[j], vet[j] = vet[r], vet[r] = t;
    return j;
}

void QuickSort(int p, int r, long int vet[]) {
    int j;
    if (p < r) {
        j = Separa(p, r, vet);
        QuickSort(p, j - 1, vet);
        QuickSort(j + 1, r, vet);
    }
}

void BuscaLinI(long int vet[], long int N, long int x) {
    for (long int i = 0; i < N; i++) {
        if (vet[i] == x)
            return;
    }
    return;
}

void BuscaBinI(long int vet[], long int N, long int x) {
    long int cabeca = 0;
    long int rabo = N - 1;
    while (cabeca <= rabo) {
        long int meio = cabeca + (rabo - cabeca) / 2;
        if (vet[meio] == x)
            return;
        else if (vet[meio] < x)
            cabeca = meio + 1;
        else
            rabo = meio - 1;
    }
    return;
}

int BuscaBinR(long int vet[], long int cabeca, long int rabo, long int x) {
    if (cabeca > rabo) {
        return -1;
    }
    long int meio = cabeca + (rabo - cabeca) / 2;
    if (vet[meio] == x) {
        return meio;
    } else if (vet[meio] > x) {
        return BuscaBinR(vet, cabeca, meio - 1, x);
    } else {
        return BuscaBinR(vet, meio + 1, rabo, x);
    }
}

int main() {
    long int *vet = malloc(N * sizeof(long int));
    float t;
    srand((unsigned)time(NULL));

    for (long int i = 0; i < N; i++)
        vet[i] = rand() % N;
    QuickSort(0, N - 1, vet);
  
    long int x = vet[0];
    t = clock();
    BuscaLinI(vet, N, x);
    t = clock() - t;
    printf("\nTempo de execucao da Busca linear iterativa: %lf μs\n", ((double)t) / CLOCKS_PER_SEC * 1000000);

    x = vet[(N-1) / 2];
    t = clock();
    BuscaBinI(vet, N, x);
    t = clock() - t;
    printf("\nTempo de execucao da Busca binária iterativa: %lf μs\n", ((double)t) / CLOCKS_PER_SEC * 1000000);

    t = clock();
    BuscaBinR(vet, 0, N - 1, x);
    t = clock() - t;
    printf("\nTempo de execucao da Busca binária recursiva: %lf μs\n", ((double)t) / CLOCKS_PER_SEC * 1000000);

    free(vet);
    return 0;
}
