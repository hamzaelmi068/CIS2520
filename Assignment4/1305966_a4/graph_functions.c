#include "graph.h"

/*
Name: Hamza Elmi
Student ID: 1305966
Assignment 4 Functions
*/


/* function will display the primary user interface
    This is already done for you*/
void prompt(void)
{

    printf("\nMenu:\n");
    printf("1. Display Adjacency List\n");
    printf("2. Perform Breadth-First Search (BFS)\n");
    printf("3. Perform Depth-First Search (DFS)\n");
    printf("4. Find Shortest Path using Dijkstra's Algorithm\n");
    printf("5. Exit\n");
}

/**
 * Reads a graph from a file and constructs the graph structure.
 * @param filename The name of the file containing the adjacency matrix.
 * @return Pointer to the created Graph structure, or NULL if an error occurs.
 */Graph *readGraph(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return NULL;
    }

    // Create and initialize the graph
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (graph == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for graph\n");
        fclose(file);
        return NULL;
    }

    // Initialize graph properties
    graph->numVertices = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->adjList[i] = NULL;
        for (int j = 0; j < MAX_VERTICES; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }

    // Count number of vertices (first line)
    char line[1024];
    if (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, " \t\n");
        while (token != NULL) {
            graph->numVertices++;
            token = strtok(NULL, " \t\n");
        }
    }

    // Reset file pointer to start
    rewind(file);

    // Read the adjacency matrix
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            if (fscanf(file, "%d", &graph->adjMatrix[i][j]) != 1) {
                fprintf(stderr, "Error: Invalid matrix format in file\n");
                fclose(file);
                free(graph);
                return NULL;
            }
        }
    }

    fclose(file);
    return graph;
}
/**
 * Creates a new node for the adjacency list.
 * @param vertex The vertex number that this node will represent.
 * @return Pointer to the newly created Node structure.
 */
Node *createNode(int vertex)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL){
        printf("error, cant allocate");
    }
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

/**
 * Displays the adjacency list of the graph.
 * @param graph Pointer to the Graph structure.
 */
void displayAdjacencyList(Graph *graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node *temp = graph->adjList[i];
        printf("Vertex %d: ", i + 1);
        while (temp) {
            printf(" -> %d (%d)", temp->vertex + 1, graph->adjMatrix[i][temp->vertex]);
            temp = temp->next;
        }
        printf(" NULL\n");
    }
}

/**
 * Converts the adjacency matrix of the graph to an adjacency list.
 * @param graph Pointer to the Graph structure.
 */void createAdjacencyList(Graph *graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        graph->adjList[i] = NULL;
        Node *last = NULL; // Pointer to keep track of the last node in the list
        for (int j = 0; j < graph->numVertices; j++) {
            if (graph->adjMatrix[i][j] != 0) {
                Node *newNode = createNode(j);
                if (graph->adjList[i] == NULL) {
                    graph->adjList[i] = newNode;
                } else {
                    last->next = newNode;
                }
                last = newNode; // Update the last node
            }
        }
    }
}

// Helper Functions for BFS
// simple queue structure for BFS
typedef struct Queue {
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

void initializeQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->rear == -1;
}

void enqueue(Queue *q, int value) {
    if (q->rear == MAX_VERTICES - 1) {
        printf("Queue is full\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->items[++q->rear] = value;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    int item = q->items[q->front];
    if (q->front >= q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return item;
}

/**
 * Performs Breadth-First Search (BFS) starting from a given vertex.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which BFS starts (0-based index).
 */
void bfs(Graph *graph, int startVertex)
{
    // initilaize queue with startvertex
    Queue queue;
    initializeQueue(&queue);

    int discovered[MAX_VERTICES] = {0};
    discovered[startVertex] = 1;

    enqueue(&queue, startVertex);

    while (!isEmpty(&queue)) {
        int currentVertex = dequeue(&queue);
        printf("%d ", currentVertex + 1);

        Node *temp = graph->adjList[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!discovered[adjVertex]) {
                discovered[adjVertex] = 1;
                enqueue(&queue, adjVertex);
            }
            temp = temp->next;
        }
    }
    printf("\n");

}


// Helper Functions for DFS
// using  a simple stack structure for DFS
typedef struct Stack {
    int items[MAX_VERTICES];
    int top;
} Stack;

void initializeStack(Stack *stack) {
    stack->top = -1;
}

int isStackEmpty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, int value) {
    if (stack->top == MAX_VERTICES - 1) {
        printf("Stack is full\n");
        return;
    }
    stack->items[++stack->top] = value;
}

int pop(Stack *stack) {
    if (isStackEmpty(stack)) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->items[stack->top--];
}

/**
 * Performs Depth-First Search (DFS) starting from a given vertex.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which DFS starts (0-based index).
 */
void dfs(Graph *graph, int startVertex)
{
    // Implement the function logic here
    Stack stack;
    initializeStack(&stack);

    
    int visited[MAX_VERTICES] = {0};

    push(&stack, startVertex);

    while (!isStackEmpty(&stack)) {
        int currentVertex = pop(&stack);

        if (!visited[currentVertex]) {
            printf("%d ", currentVertex + 1);
            visited[currentVertex] = 1;

            Node *temp = graph->adjList[currentVertex];
            while (temp) {
                int adjVertex = temp->vertex;
                if (!visited[adjVertex]) {
                    push(&stack, adjVertex);
                }
                temp = temp->next;
            }
        }
    }
    printf("\n");
}

/**
 * Finds the shortest path from the start vertex to all other vertices using Dijkstra's algorithm.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which to start the algorithm (0-based index).
 */
void dijkstra(Graph *graph, int startVertex)
{
    int distance[MAX_VERTICES];
    bool visited[MAX_VERTICES];
    int previous[MAX_VERTICES];

    // Initialize distances and visited array
    for (int i = 0; i < graph->numVertices; i++) {
        distance[i] = INT_MAX;
        visited[i] = false;
        previous[i] = -1;
    }
    distance[startVertex] = 0;

    for (int i = 0; i < graph->numVertices; i++) {
        // Find the vertex with the smallest distance
        int minDistance = INT_MAX;
        int u = -1;
        for (int j = 0; j < graph->numVertices; j++) {
            if (!visited[j] && distance[j] < minDistance) {
                minDistance = distance[j];
                u = j;
            }
        }

        // Mark the chosen vertex as visited
        visited[u] = true;

        // Update distances to neighbors
        for (int v = 0; v < graph->numVertices; v++) {
            if (graph->adjMatrix[u][v] && !visited[v]) {
                int alt = distance[u] + graph->adjMatrix[u][v];
                if (alt < distance[v]) {
                    distance[v] = alt;
                    previous[v] = u;
                }
            }
        }
    }

    // Print the results
    for (int i = 0; i < graph->numVertices; i++) {
        printf("Shortest distance from vertex %d to vertex %d: %d\n", startVertex + 1 , i + 1, distance[i]);    
    }
}

/**
 * Frees the memory allocated for the graph, including the adjacency list.
 * @param graph Pointer to the Graph structure to be freed.
 */
void freeGraph(Graph *graph)
{
    // traversing through the adjacency list
    for (int j = 0; j < graph->numVertices; j++){
        // Use a temporary pointer temp to traverse the list.
        Node *temp = graph->adjList[j];
        while (temp){
            // Store the next node in next before freeing the current node.
            Node *next = temp->next;
            free(temp);
            temp = next;
        }
    }
    // now freeing the graph structure
    free(graph);

}
