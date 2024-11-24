#include "graph.h"

/*
 * A basic menu based structure has been provided
 */

/*

Name: Hamza Elmi
Student ID: 1305966
Assignment 4 Main

*/


int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }   

    // read the graph from the file
    Graph *graph = readGraph(argv[1]);
    if (graph == NULL){
        fprintf(stderr, "Error: Could not create graph from file %s\n", argv[1]);
        return 1;
    }

    // creating the adjaceny lisst representation
    createAdjacencyList(graph);

    int choice;
    int startVertex = 0;

    do
    {
        // Display the options
        prompt();

        // Get user input
        printf("Enter a Choice: ");
        scanf("%d", &choice);

        /*
         * You will need to add all the cases here.
         * Call the relevant functions in each case.
         * Make sure to handle invalid inputs or edge cases.
         */

       // Process user choice
        switch (choice) {
            case 1:
                printf("Adjacency List Representation:\n");
                displayAdjacencyList(graph);
                break;

            case 2:
                printf("Breadth-First Search starting from vertex %d:\n", startVertex);
                bfs(graph, startVertex);
                break;

            case 3:
                printf("Depth-First Search starting from vertex %d:\n", startVertex);
                dfs(graph, startVertex);
                break;

            case 4:
                printf("Shortest Paths from vertex %d (Dijkstra's Algorithm):\n", startVertex);
                dijkstra(graph, startVertex);
                break;

            case 5:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please select a number between 1 and 5.\n");
                break;
        }
        
        // Add newline for better formatting
        printf("\n");
        
    } while (choice != 5);

    return 0;
}
