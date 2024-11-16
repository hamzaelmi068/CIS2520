#include "q2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char** argv) {
    // Check if correct number of arguments is provided
    if (argc != 2) {
        printf("<blank>: Incorrect input: %s <Make sure to add RPN expression>\n", argv[0]);
        return 1;
    }

    // Initialize the stack pointer
    Operand *stack = NULL;

    // Loop through each character in the input string
    for (int i = 0; i < strlen(argv[1]); ++i) {
        char ch = argv[1][i];

        // If the character is a digit
        if (isdigit(ch)) {
            // Convert char to double and push onto stack
            double value = ch - '0';
            push(&stack, value);
        } 
        // If the character is an operator
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            // Check if there are at least two operands in the stack
            if (stack == NULL || stack->next == NULL) {
                printf("error, there arent enough operands for operation '%c'\n", ch);
                return 1;
            }
            // Pop two operands from the stack
            double second_op = pop(&stack);  // the second operand
            double first_op = pop(&stack);  // the first operand
            double result;

            // Perform the operation based on the operator
            switch (ch) {
                case '+':
                    result = first_op + second_op;
                    break;
                case '-':
                    result = first_op - second_op; // Note: order is important
                    break;
                case '*':
                    result = first_op * second_op;
                    break;
                case '/':
                    // Check for division by zero
                    if (second_op == 0) {
                        printf("Error: Division by zero\n");
                        return 1;
                    }
                    result = first_op / second_op; // Note: order is important
                    break;
            }

            // Push the result back onto the stack
            push(&stack, result);
        } 
        // If the character is neither first_opdigit nor an operator
        else {
            printf("Error: you entered an invalid character %d\n", ch);
            return 1;
        }
    }

    // After processing all characters, check if there's exactly one value left in the stack
    if (stack == NULL || stack->next != NULL) {
        printf("Error: Invalid expression (too many or too few operands)\n");
        return 1;
    }

    // Print the final result (top of the stack)
    printf("Reversed Polished Notation result: %.2f\n", stack->value);

    // Free the remaining node in the stack
    free(stack);

    return 0;
}