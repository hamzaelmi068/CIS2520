/*
Name: Hamza Elmi
Student ID: 1305966 
Assignment 2, Question 2
*/

#include "q2.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Pushes a new value onto the stack.
 * 
 * @param stack Pointer to the pointer of the stack's head.
 * @param value The value to be added to the stack.
 */
void push(Operand **stack, double value){
    // allocating memory for new operand node
    Operand *node = (Operand*)malloc(sizeof(Operand));
    // null check for node allocated
    if (node == NULL){
        printf("memory allocated failed.\n");
        return; 
    }

    // Set the value of the new node to the input value
    node->value = value;

    // set the next pointer of the new node to the current top of the stack
    node->next = *stack;

    // Update the stack pointer to point to the new node
    *stack = node;
}

/**
 * Pops the top value from the stack and returns it.
 * 
 * @param stack Pointer to the pointer of the stack's head.
 * @return The value that was at the top of the stack.
 */
double pop(Operand **stack){
    // Hint 1: Check if the stack is empty (return an error value or handle this case)
    if (*stack == NULL){
        printf("stack is empty, cant pop anything if its empty.\n");
        return -1;
    }

    // storing the value of the top node
    double value = (*stack)->value;

    // creating a temporary pointer to the top node
    Operand *temp = *stack;

    // updating the stack pointer to point to the next node
    *stack = (*stack)->next;

    // Hint 5: Free the memory of the removed node
    free(temp);

    // returning our stored value
    return value;

}


/**
 * Prints all values in the stack.
 * 
 * @param stack Pointer to the stack's head.
 */
void print(Operand *stack){
    // Setting current to the head
    Operand *current = stack;
    
    // null check
    if (current == NULL){
        printf("The stack is empty, cant print anything.\n");
        return;
    }

    // traversing through the list
    while (current != NULL){
        // printing value
        printf("%.2f ", current->value);
        // moving onto the next node
        current = current->next;
    }
    printf("\n");

}