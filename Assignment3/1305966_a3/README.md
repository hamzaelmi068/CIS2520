# **CIS2520-F24-A3: Binary Tree and Heap Program**

**Author**: Hamza Elmi  
**Student ID**: 1305966  
**Course**: CIS*2520 (Fall 2024)  
**Assignment**: Assignment Three  
---

## Overview

This assignment demonstrates the implementation and manipulation of **Binary Trees** and **Heaps** to manage data structures. Key topics include binary tree traversals, expression evaluation, and min/max-heap operations.

### Skills Developed

- Working with **Binary Trees** and **Heaps**
- Performing **Tree Traversals**: Preorder, Inorder, and Postorder
- Implementing **Min-Heaps** and **Max-Heaps**
- Managing data structures and handling **Heap Operations** (insertion, deletion, heapification)

---

## Objectives

This program is divided into two main parts:

### Part 1: Binary Tree
- Construct a **Binary Expression Tree** from a fully parenthesized arithmetic expression
- Perform **Preorder**, **Inorder**, and **Postorder** traversals on the expression tree
- **Evaluate** the result of the expression tree

### Part 2: Heaps
- Implement a **Min-Heap** data structure
- Perform essential heap operations: **Insertion**, **Deletion**, and **Heapification**

---

## Compiling and Running the Program

To compile and run the program, follow these steps:

1. **Compile**: In the directory with the assignment files, type:
    ```bash
    make
    ```
   This command will compile all necessary files and create an executable.

2. **Run Part 1: Binary Tree**:
    ```bash
    ./a3q1
    ```
   - Enter your desired expression to build and traverse the binary tree.

3. **Run Part 2: Heaps**:
    ```bash
    ./a3q2
    ```

---

## Part 1: Binary Tree

The program will prompt the user to input a **transaction code** to perform actions on the binary tree:

- **PreOrder**: Traverse the tree in preorder
- **InOrder**: Traverse the tree in inorder
- **PostOrder**: Traverse the tree in postorder
- **Calculate**: Evaluate and display the result of the expression
- **Exit**: Exit the program

### Files in Part 1

- `a3q1_main.c`: Contains the `main()` function, controlling program flow
- `a3q1_functions.h`: Contains structure definitions and function prototypes
- `a3q1_functions.c`: Implements all functions called by `main()`

---

## Part 2: Heaps

### Program Description

- The program reads **200 two-digit integers** from a file called `f.dat`, storing them in a **20x10 array**.
- Each row is treated as an **object**:
    - The **key** is the sum of the first three integers in each row
    - The remaining seven integers hold the **information content**
- A **MAX-HEAP** is created using an array representation, applying a **downheap algorithm** on the parental nodes.
- Finally, the heap is displayed as a **20x10 array**.

### Files in Part 2

- `a3q2_main.c`: Contains the `main()` function, controlling program flow
- `a3q2_functions.h`: Contains structure definitions and function prototypes
- `a3q2_functions.c`: Implements all functions called by `main()`

---

## Program Exit

The program will exit upon selecting the quit option in the menu.

---

## Notes

- Ensure that `f.dat` is in the same directory as the program for Part 2 to function correctly.
- Modify or extend transaction codes if additional functionality is required.

## How to Build the Makefile

1. **Define the Overall Targets**:
   - Start by listing the executables you want to create. In this example, we have two executables: `a3q1` and `a3q2`.

2. **Set Rules for the Executables**:
   - Each executable depends on object files that are compiled from source files. 
     - `a3q1` depends on `a3q1_main.o` and `a3q1_functions.o`.
     - `a3q2` depends on `a3q2_main.o` and `a3q2_functions.o`.

3. **Define How to Compile Object Files**:
   - You need to define the rules for creating the object files (`a3q1_main.o`, `a3q1_functions.o`, `a3q2_main.o`, and `a3q2_functions.o`).
   - Each object file is compiled from its corresponding C source file, and you need to include any necessary header files for the dependencies.

4. **Add a Clean Rule**:
   - It's a good practice to include a clean rule to remove all the object files and executables when you're done.

## Compiling the Programs

Make sure your makefile compiles both programs into separate executable files:
- `a3q1` for the binary tree program.
- `a3q2` for the min-heap or max-heap program.

## Documentation and Style

You will be graded on both the functionality and readability of your code. This includes:

### Comments:
- Each file should start with a comment block containing your name, student ID, date, and the assignment name.
- Every function should have a brief comment describing its purpose.
- Add comments for any section of code where the functionality is not immediately apparent.

### Code Style:
- Follow proper indentation and code style conventions. Poor formatting will result in a deduction.

## README File Guidelines

- Use the provided README template.
- You can add additional information if needed, such as specific instructions or challenges faced during implementation.

## Submission and Error Handling

- Be sure to handle error conditions gracefully. For example, the binary tree program should check for invalid transaction codes or invalid expressions.
- Any compilation errors or warnings will result in a mark deduction based on the severity of the issue.
- Style, documentation, and code organization will also contribute to your overall mark.

## #Instructor and TA support

You can email [cis2520@socs.uoguelph.ca](mailto:cis2520@socs.uoguelph.ca) which will reach the entire instructional team.  Any email sent to this address will be answered by the first member of the instructional team available to respond.  You will get a response within 24 hours, and probably sooner.  Note that staff are not generally available outside of daytime working hours (for this or any course), so it is in your interest to start work early so that if you have questions you can ask them in time to get a good response.

Additional support is available during lab times when teaching staff will be available to answer lab related questions and general questions if time permits.  Note that lab exercises are designed specifically to build your skills within the focus of current and upcoming assignments.