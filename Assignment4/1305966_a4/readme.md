# CIS2520-F24-A4

## Student Information 
Name : Hamza Elmi

Student Number : 1305966

## Assignment Overview
What is the assignment about?  
Explain the purpose of the program and what it accomplishes?
The purpose of this assignment is to gain an understanding of graph theory and algorithm implementation in C. This program will write will read a graph from a file, represent it using different data structures, and perform various graph traversal and pathfinding algorithms. This will help me gain practical experience with graph representations, algorithm design, and efficient memory management.

## Resources 
Did you use any resources (for example book, notes etc) in this assignment?
 -- GraphPath slides from Course notes for the search's / algorithms
https://courselink.uoguelph.ca/d2l/le/content/911255/viewContent/3985634/View 
https://courselink.uoguelph.ca/d2l/le/content/911255/viewContent/3980006/View
https://www.geeksforgeeks.org/stack-data-structure/
https://www.geeksforgeeks.org/difference-between-stack-and-queue-data-structures/

## Implementation
Is the assignment complete? If not, mention what part of the assignment is missing or incomplete. 
## Yes, i completed it.


# Part 1: Assignment

## Skill Focus
- **Graph Theory**: Understanding graph representations (Adjacency Matrix, Adjacency List).
- **Algorithm Implementation**: Breadth-First Search (BFS), Depth-First Search (DFS), and Dijkstra's Algorithm.
- **File Handling**: Reading a graph from a file.
- **Memory Management**: Efficiently using dynamic memory in C (linked lists).
- **Command-Line Arguments**: Using arguments to pass file names.

## Objective
The goal is to write a C program that:
1. Reads a graph's adjacency matrix from a `.txt` file.
2. Provides options to display the graph's adjacency list, perform BFS, DFS, and find the shortest path using Dijkstra’s algorithm.
3. Ensures robust file handling, input validation, and proper memory management.

## Transactions
### Menu Options:
1. **Display Adjacency List**: Convert the adjacency matrix into an adjacency list and display the list for all vertices.
2. **Breadth-First Search (BFS)**: Traverse the graph using BFS starting from vertex 1.
3. **Depth-First Search (DFS)**: Traverse the graph using DFS starting from vertex 1.
4. **Dijkstra’s Algorithm**: Compute and display the shortest path from vertex 1 to all other vertices using Dijkstra’s algorithm.
5. **Exit**: Quit the program.

## Program Quit
The program should continue showing the menu after performing an action until the user selects the "Exit" option. Memory should be cleaned up before quitting.

## Files
Your project will consist of the following files:
1. **graph.h**: Header file containing function declarations and data structure definitions.
2. **main.c**: The main program that handles the menu, reads the graph from the file, and calls the appropriate functions.
3. **graph_functions.c**: File containing the implementations of the graph-related functions (e.g., BFS, DFS, Dijkstra, adjacency list creation).
4. **Makefile**: Makefile for compiling your program.
5. **README.md**: A brief explanation of the project and instructions for compiling and running it.

## Compiling the program
To compile and run the program, follow these steps:

1. In the directory where the assignment files are saved, type:
	make 
This will compile all necessary files into an executable.

2. To run the program type:
`./a4 example-graph.txt`

# Part 2: Assignment Guidelines

## General Requirements
1. Your program must accept the graph’s adjacency matrix file as a command-line argument.
    - Example: `./a4 example-graph.txt`
2. It should handle input errors gracefully (e.g., missing or unreadable files).
3. All graph operations (BFS, DFS, Dijkstra’s) should work on the adjacency list, not the matrix.
4. The program should return to the menu after each operation until the user chooses to exit.
5. Ensure proper memory management. Every dynamically allocated memory (nodes, lists, etc.) should be freed before exiting.

## File Structure
Your submission should contain the following files:

- **graph.h**: Header file containing function declarations and data structure definitions for the graph operations.
- **main.c**: The main program that handles the menu, reads the graph from the file, and calls the appropriate functions.
- **graph_functions.c**: File containing the implementations of the graph-related functions (e.g., BFS, DFS, Dijkstra, adjacency list creation).
- **Makefile**: Makefile for compiling your program. It should compile `main.c` and `graph_functions.c` into a single executable.
- **README.md**: A brief explanation of the project, including instructions for compiling and running it.

### Documentation and Style
You will be graded on both the functionality and readability of your code. This includes:

- Comments:
Each file should start with a comment block containing your name, student ID, date, and the assignment name.
Every function should have a brief comment describing its purpose.
Add comments for any section of code where the functionality is not immediately apparent.

- Code Style: Follow proper indentation and code style conventions. Poor formatting will result in a deduction.

### README File Guidelines
- Use the README template provided for students.
- You can add additional information if needed, such as specific instructions or challenges faced during implementation.


### Submission and Error Handling
- Be sure to handle error conditions gracefully. 
- Any compilation errors or warnings will result in a mark deduction based on the severity of the issue.
- Style, documentation, and code organization will also contribute to your overall mark.

## Program Quit
The program should continue showing the menu after performing an action until the user selects the "Exit" option. Memory should be cleaned up before quitting.



