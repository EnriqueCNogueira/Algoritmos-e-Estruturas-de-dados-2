#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 
// Estrutura para representar um nó na lista de adjacência
typedef struct Node {
    int dest; // Destino do nó
    int weight; // Peso da aresta
    struct Node* next; // Próximo nó na lista de adjacência
} Node;
 
// Estrutura para representar o grafo
typedef struct Graph {
    int V; // Número de vértices no grafo
    Node** adj; // Lista de adjacência
} Graph;
 
// Cria um novo nó para a lista de adjacência
Node* create_node(int dest, int weight) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->dest = dest;
    new_node->weight = weight;
    new_node->next = NULL;
    return new_node;
}
 
// Inicializa um grafo com V vértices
Graph* create_graph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->adj = (Node**)malloc(V * sizeof(Node*));
    for (int i = 0; i < V; i++) {
        graph->adj[i] = NULL;
    }
    return graph;
}
 
// Insere uma aresta no grafo, mantendo a lista de adjacência ordenada
void insert_edge(Graph* graph, int u, int v, int p) {
    Node* new_node = create_node(v, p);
    
    // Insere na cabeça da lista se ela estiver vazia ou se o novo nó for menor que o primeiro
    if (graph->adj[u] == NULL || graph->adj[u]->dest > v) {
        new_node->next = graph->adj[u];
        graph->adj[u] = new_node;
    } else {
        Node* current = graph->adj[u];
 
        // Encontra a posição correta para inserir o novo nó mantendo a ordem
        while (current->next != NULL && current->next->dest < v) {
            current = current->next;
        }
 
        // Insere o novo nó na posição correta
        new_node->next = current->next;
        current->next = new_node;
    }
}
 
// Imprime o caminho recursivamente a partir do nó de destino
void print_path(int predecessor[], int dest) {
    if (predecessor[dest] != -1) {
        print_path(predecessor, predecessor[dest]);
        printf(" %d", dest);
    } else {
        printf("%d", dest);
    }
}
 
// Executa o algoritmo de Bellman-Ford com restrição de custo
void bellman_ford_restricted(Graph* graph, int start_node, int restriction, int dest_node) {
    int V = graph->V;
    int* dist = (int*)malloc(V * sizeof(int));
    int* predecessor = (int*)malloc(V * sizeof(int));
 
    // Inicialização dos vetores de distância e predecessor
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        predecessor[i] = -1;
    }
    dist[start_node] = 0;
 
    // Loop principal de relaxamento das arestas (V-1) vezes
    for (int i = 1; i <= V - 1; i++) {
        for (int u = 0; u < V; u++) {
            if (dist[u] != INT_MAX) {
                Node* current = graph->adj[u];
 
                // Percorre a lista de adjacência do nó u
                while (current != NULL) {
                    int v = current->dest;
                    int weight = current->weight;
                    
                    // Modificação principal: considera a restrição R
                    if (weight <= restriction) {
                        if (dist[u] + weight < dist[v]) {
                            dist[v] = dist[u] + weight;
                            predecessor[v] = u;
                        }
                    }
                    // Avança para o próximo nó na lista de adjacência
                    current = current->next;
                }
            }
        }
    }
 
    // Saída dos custos mínimos
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX) {
            printf("INF");
        } else {
            printf("%d", dist[i]);
        }
        if (i < V - 1) {
            printf(" ");
        }
    }
    printf("\n");
 
    // Saída do caminho para o destino
    if (dist[dest_node] == INT_MAX) {
        printf("Destino nao alcancado\n");
    } else {
        print_path(predecessor, dest_node);
        printf("\n");
    }
 
    // Libera memória
    free(dist);
    free(predecessor);
}
 
// Libera toda a memória alocada para o grafo
void free_graph(Graph* graph) {
    if (graph) {
        for (int i = 0; i < graph->V; i++) {
            Node* current = graph->adj[i];
            while (current != NULL) {
                Node* temp = current;
                current = current->next;
                free(temp);
            }
        }
        free(graph->adj);
        free(graph);
    }
}
 
// Função principal para ler a entrada, executar o algoritmo e imprimir a saída
int main() {
    int V_start, R, N, M, D;
 
    // Leitura dos dados de entrada
    scanf("%d", &V_start);
    scanf("%d", &R);
    scanf("%d %d", &N, &M);
 
    Graph* graph = create_graph(N);
 
    // Insere as arestas no grafo
    for (int i = 0; i < M; i++) {
        int u, v, p;
        scanf("%d %d %d", &u, &v, &p);
        insert_edge(graph, u, v, p);
    }
 
    // Leitura do nó de destino
    scanf("%d", &D);
 
    // Executa o algoritmo e imprime os resultados
    bellman_ford_restricted(graph, V_start, R, D);
 
    // Libera a memória alocada
    free_graph(graph);
 
    return 0;
}
