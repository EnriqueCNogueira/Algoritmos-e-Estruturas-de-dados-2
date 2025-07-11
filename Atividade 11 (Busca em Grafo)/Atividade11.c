#include <stdio.h>
#include <stdlib.h>
 
#define MAX_VERTICES 101
 
// Estrutura para os nós da lista de adjacência e das estruturas auxiliares (Fila/Pilha)
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;
 
// Estrutura da Fila para o BFS
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;
 
// Inicializa a lista de adjacência com NULL
void inicializarGrafo(Node* adj[], int n) {
    for (int i = 0; i < n; i++) {
        adj[i] = NULL;
    }
}
 
// Cria e retorna uma fila vazia
Queue* criarFila() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}
 
// Cria e retorna uma pilha vazia (representada por um ponteiro de nó)
Node* criarPilha() {
    return NULL;
}
 
// Insere uma aresta (u -> v) no grafo, mantendo a lista de adjacência de u ordenada
void inserirAresta(Node* adj[], int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    
    // Caso 1: A lista está vazia ou o novo vértice é menor que o primeiro
    if (adj[u] == NULL || v < adj[u]->vertex) {
        newNode->next = adj[u];
        adj[u] = newNode;
        return;
    }
 
    // Caso 2: Encontra a posição correta para inserir o novo vértice
    Node* current = adj[u];
    while (current->next != NULL && current->next->vertex < v) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}
 
// Adiciona um elemento ao final da fila (BFS)
void enfileirar(Queue* q, int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}
 
// Remove e retorna o elemento da frente da fila (BFS)
int desenfileirar(Queue* q) {
    if (q->front == NULL) return -1;
    Node* temp = q->front;
    int vertex = temp->vertex;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return vertex;
}
 
// Adiciona um elemento ao topo da pilha (DFS)
void push(Node** topo, int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = *topo;
    *topo = newNode;
}
 
// Remove e retorna o elemento do topo da pilha (DFS)
int pop(Node** topo) {
    if (*topo == NULL) return -1;
    Node* temp = *topo;
    int vertex = temp->vertex;
    *topo = (*topo)->next;
    free(temp);
    return vertex;
}
 
// Executa a Busca em Largura (BFS)
void bfs(Node* adj[], int startNode, int nVertices) {
    int visitado[MAX_VERTICES] = {0};
    Queue* q = criarFila();
 
    visitado[startNode] = 1;
    enfileirar(q, startNode);
 
    int first = 1;
    while (q->front != NULL) {
        int u = desenfileirar(q);
        if (!first) printf(" ");
        printf("%d", u);
        first = 0;
 
        Node* temp = adj[u];
        while (temp != NULL) {
            int v = temp->vertex;
            if (!visitado[v]) {
                visitado[v] = 1;
                enfileirar(q, v);
            }
            temp = temp->next;
        }
    }
    free(q);
}
 
// Executa a Busca em Profundidade (DFS)
void dfs(Node* adj[], int startNode, int nVertices) {
    int visitado[MAX_VERTICES] = {0};
    Node* pilha = criarPilha();
 
    push(&pilha, startNode);
 
    int first = 1;
    while (pilha != NULL) {
        int u = pop(&pilha);
 
        if (!visitado[u]) {
            visitado[u] = 1;
            if (!first) printf(" ");
            printf("%d", u);
            first = 0;
 
            // Para manter a ordem de visita correta, os vizinhos são empilhados na ordem inversa
            // da lista de adjacência (que está em ordem crescente).
            Node* temp = adj[u];
            Node* vizinhosInvertidos = NULL;
            while (temp != NULL) {
                push(&vizinhosInvertidos, temp->vertex);
                temp = temp->next;
            }
 
            while(vizinhosInvertidos != NULL) {
                int v = pop(&vizinhosInvertidos);
                if (!visitado[v]) {
                    push(&pilha, v);
                }
            }
        }
    }
}
 
// Libera a memória alocada para a lista de adjacência
void liberarGrafo(Node* adj[], int n) {
    for (int i = 0; i < n; i++) {
        Node* current = adj[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
}
 
 
int main() {
    Node* adj[MAX_VERTICES];
    int startNode, nVertices, nArestas;
 
    // Leitura dos dados de entrada 
    scanf("%d", &startNode);
    scanf("%d %d", &nVertices, &nArestas);
 
    inicializarGrafo(adj, nVertices);
 
    for (int i = 0; i < nArestas; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        inserirAresta(adj, u, v);
    }
 
    // Saída da Busca em Largura (BFS)
    bfs(adj, startNode, nVertices);
    printf("\n");
 
    // Saída da Busca em Profundidade (DFS)
    dfs(adj, startNode, nVertices);
    printf("\n");
    
    liberarGrafo(adj, nVertices);
 
    return 0;
}
