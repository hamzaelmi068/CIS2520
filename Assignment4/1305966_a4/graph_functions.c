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
 */
Graph *readGraph(const char *filename)
{
    // opening the file in r mode
    FILE *file = fopen(filename, "r");
    // null check
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return NULL;
    }

    // Create and initialize the graph
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (graph == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed for graph\n");
        fclose(file);
        return NULL;
    }

    // Initialize graph properties
    graph->numVertices = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        graph->adjList[i] = NULL;
        for (int j = 0; j < MAX_VERTICES; j++)
        {
            graph->adjMatrix[i][j] = 0;
        }
    }

    // Count number of vertices (first line)
    char line[1024];
    if (fgets(line, sizeof(line), file))
    {
        char *token = strtok(line, " \t\n");
        while (token != NULL)
        {
            graph->numVertices++;
            token = strtok(NULL, " \t\n");
        }
    }

    // Reset file pointer to start
    rewind(file);

    // Read the adjacency matrix
    for (int i = 0; i < graph->numVertices; i++)
    {
        for (int j = 0; j < graph->numVertices; j++)
        {
            if (fscanf(file, "%d", &graph->adjMatrix[i][j]) != 1)
            {
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
    // dynamically allocating memory for the new node
    Node *newNode = (Node *)malloc(sizeof(Node));
    // null check for the new node
    if (newNode == NULL)
    {
        printf("error, cant allocate");
    }
    // initializing new nodes vertex
    newNode->vertex = vertex;
    // initialize new nodes next pointer
    newNode->next = NULL;
    return newNode;
}

/**
 * Displays the adjacency list of the graph.
 * @param graph Pointer to the Graph structure.
 */
void displayAdjacencyList(Graph *graph)
{
    // iterating through each vertex in the graph
    for (int i = 0; i < graph->numVertices; i++)
    {
        Node *temp = graph->adjList[i];
        printf("Vertex %d: ", i + 1);
        // going through the adjacency list of the current vertex
        while (temp)
        {
            // print connected vertex and weight of the edge
            printf(" -> %d (%d)", temp->vertex + 1, graph->adjMatrix[i][temp->vertex]);
            temp = temp->next; // move on to next node
        }
        printf(" NULL\n"); // end of the list, we put null
    }
}

/**
 * Converts the adjacency matrix of the graph to an adjacency list.
 * @param graph Pointer to the Graph structure.
 */
void createAdjacencyList(Graph *graph)
{
    // iterate through each vertex in the graph
    for (int i = 0; i < graph->numVertices; i++)
    {
        graph->adjList[i] = NULL; // initializing adjanecy list for current vertex
        Node *last = NULL;        // Pointer to keep track of the last node in the list
        // iterating through adjacnecy row for current vertex
        for (int j = 0; j < graph->numVertices; j++)
        {
            // if theres an edge between vertex i and vertex j
            if (graph->adjMatrix[i][j] != 0)
            {
                Node *newNode = createNode(j); // create new node
                // if the list is empty, set the new node head
                if (graph->adjList[i] == NULL)
                {
                    graph->adjList[i] = newNode;
                }
                else
                {
                    last->next = newNode;
                }
                last = newNode; // Update the last node
            }
        }
    }
}

// Helper Functions for BFS
// simple queue structure for BFS
typedef struct Queue
{
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

void initializeQueue(Queue *q)
{
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue *q)
{
    return q->rear == -1;
}

void enqueue(Queue *q, int value)
{
    if (q->rear == MAX_VERTICES - 1)
    {
        printf("Queue is full\n");
        return;
    }
    if (q->front == -1)
    {
        q->front = 0;
    }
    q->items[++q->rear] = value;
}

int dequeue(Queue *q)
{
    if (isEmpty(q))
    {
        printf("Queue is empty\n");
        return -1;
    }
    int item = q->items[q->front];
    if (q->front >= q->rear)
    {
        q->front = q->rear = -1;
    }
    else
    {
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
    // marking the start vertex
    discovered[startVertex] = 1;
    // adding the start vertex
    enqueue(&queue, startVertex);
    // while the queue isnt empty
    while (!isEmpty(&queue))
    {
        // dequeue the current vertex
        int currentVertex = dequeue(&queue);
        printf("%d ", currentVertex + 1);
        // traversing the adjacency list of current vertex
        Node *temp = graph->adjList[currentVertex];
        while (temp)
        {
            int adjVertex = temp->vertex;
            // If the adjacent vertex has not been discovered
            if (!discovered[adjVertex])
            {
                discovered[adjVertex] = 1;  // marking it as found
                enqueue(&queue, adjVertex); // adding the vertex if its found
            }
            temp = temp->next; // moving onto the  next node in the list
        }
    }
    printf("\n");
}

// Helper Functions for DFS
// using  a simple stack structure for DFS
typedef struct Stack
{
    int items[MAX_VERTICES];
    int top;
} Stack;

void initializeStack(Stack *stack)
{
    stack->top = -1;
}

int isStackEmpty(Stack *stack)
{
    return stack->top == -1;
}

void push(Stack *stack, int value)
{
    if (stack->top == MAX_VERTICES - 1)
    {
        printf("Stack is full\n");
        return;
    }
    stack->items[++stack->top] = value;
}

int pop(Stack *stack)
{
    if (isStackEmpty(stack))
    {
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
    // Array to keep track of visited vertices
    bool visited[MAX_VERTICES] = {false};
    // Stack to manage the vertices for DFS
    int stack[MAX_VERTICES];
    int top = -1;
    // Push the start vertex onto the stack
    stack[++top] = startVertex;
    // searching until the stack is empty
    while (top != -1)
    {
        int currentVertex = stack[top--];
        // If the current vertex has not been visited
        if (!visited[currentVertex])
        {
            printf("%d ", currentVertex + 1);
            visited[currentVertex] = true; // Mark the current vertex as visited
        }

        // pushing neihgbors onto stack in reverse order
        Node *temp = graph->adjList[currentVertex];
        int neighbors[MAX_VERTICES];
        int count = 0;
        // Collect all neighbors of the current vertex
        while (temp)
        {
            neighbors[count++] = temp->vertex;
            temp = temp->next;
        }
        // pushing neighbors onto stack in reverse order
        for (int i = count - 1; i >= 0; i--)
        {
            if (!visited[neighbors[i]])
            {
                stack[++top] = neighbors[i];
            }
        }
    }
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

    // Initialize distances and visited array
    for (int i = 0; i < graph->numVertices; i++)
    {
        distance[i] = INT_MAX;
        visited[i] = false;
        // prev[i] = -1;
    }
    distance[startVertex] = 0;

    for (int i = 0; i < graph->numVertices; i++)
    {
        // Find the vertex with the smallest distance
        int minDistance = INT_MAX;
        int u = -1;
        for (int j = 0; j < graph->numVertices; j++)
        {
            if (!visited[j] && distance[j] < minDistance)
            {
                minDistance = distance[j];
                u = j;
            }
        }
        // if no vertex is found, we break the loop
        if (u == -1)
        {
        }

        // Mark the chosen vertex as visited
        visited[u] = true;

        // Update distances to neighbors
        for (int v = 0; v < graph->numVertices; v++)
        {
            if (graph->adjMatrix[u][v] && !visited[v])
            {
                int alt = distance[u] + graph->adjMatrix[u][v];
                if (alt < distance[v])
                {
                    distance[v] = alt;
                    // prev[v] = u;
                }
            }
        }
    }

    // Print the results
    for (int i = 0; i < graph->numVertices; i++)
    {
        printf("Shortest distance from vertex %d to vertex %d: %d\n", startVertex + 1, i + 1, distance[i]);
    }
}

/**
 * Frees the memory allocated for the graph, including the adjacency list.
 * @param graph Pointer to the Graph structure to be freed.
 */
void freeGraph(Graph *graph)
{
    // traversing through the adjacency list
    for (int j = 0; j < graph->numVertices; j++)
    {
        // Use a temporary pointer temp to traverse the list
        Node *temp = graph->adjList[j];
        while (temp)
        {
            // Store the next node in next before freeing the current node
            Node *next = temp->next;
            free(temp);
            temp = next;
        }
    }
    // now freeing the graph structure
    free(graph);
}
