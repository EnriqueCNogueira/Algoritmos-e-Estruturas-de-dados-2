#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100  

// palavras = vetor de palavras, n = número de palavras, maior = tamanho da maior palavra, alf = alfabeto do usuário
void CountingSort(char palavras[][MAX], int n, int maior, char alf[]) {
    int count[MAX][MAX];
    char ordenado[MAX][MAX];

    for (int i = 0; i < maior; i++) {
        // Zera contadores para o passo i
        for (int j = 0; j < 27; j++)
            count[i][j] = 0;

        // Define a posição da letra a ser analisada
        int pos = maior - 1 - i;

        // Conta ocorrências
        for (int k = 0; k < n; k++) {
            char c = palavras[k][pos];
            int ind = 0;
            while (ind < 27 && alf[ind] != c) 
                ind++;

            if (ind < 27) 
                count[i][ind]++;
        }

        // Faz cumulativo
        for (int j = 1; j < 27; j++)
            count[i][j] += count[i][j - 1];

        // Imprime a linha cumulativa
        for (int j = 0; j < 27; j++)
            printf("%d ", count[i][j]);
        printf("\n");

        // Reordena de trás para frente
        for (int k = n - 1; k >= 0; k--) {
            char c = palavras[k][pos];
            int ind = 0;
            while (ind < 27 && alf[ind] != c) 
                ind++;
            
            count[i][ind]--;
            int ord = count[i][ind];
            strcpy(ordenado[ord], palavras[k]);
        }

        // Copia de volta para o principal
        for (int k = 0; k < n; k++)
            strcpy(palavras[k], ordenado[k]);
    }
}

int main() {
    int n, maior = 0;

    // Lê número de palavras
    scanf("%d", &n);

    // Lê alfabeto dado
    char alf[27];
    alf[0] = ' ';
    for (int k = 1; k <= 26; k++)
        scanf(" %c", &alf[k]);

    // Lê palavras
    char palavras[MAX][MAX];
    for (int k = 0; k < n; k++) {
        scanf("%s", palavras[k]);
        int len = strlen(palavras[k]);
        if (len > maior) maior = len;
    }

    // Normaliza (minúsculas + espaços)
    for (int k = 0; k < n; k++) {
        int len = strlen(palavras[k]);
        for (int j = 0; j < maior; j++) {
            if (j < len) {
                if (palavras[k][j] <= 'Z')
                    palavras[k][j] += 32;  // converte para minúscula
            } else {
                palavras[k][j] = ' ';
            }
        }
        palavras[k][maior] = '\0';
    }

    // Imprime antes da ordenação
    for (int k = 0; k < n; k++) {
        for (int j = 0; j < maior; j++) {
            if (palavras[k][j] == ' ') {
                break;
            }
            else {
                printf("%c", palavras[k][j]);
            }
        }
        printf(".\n");
    }

    // Imprime tamanho da maior palavra
    printf("%d\n", maior);

    // Ordena via radix/counting e imprime a matriz cumulativa
    CountingSort(palavras, n, maior, alf);

    // Imprime após a ordenação
    for (int k = 0; k < n; k++)
        printf("%s\n", palavras[k]);

    return 0;
}
