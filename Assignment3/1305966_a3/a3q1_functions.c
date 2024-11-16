#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "a3q1_header.h"

Variable variables[10];
int varCount;

// The createNode function allocates memory to the tree and creates a new node using the given data before returning the node.
Node* createNode(char *data){
    // begin by dynamically allocating memory for new node. (shouldnt use static because while executing the program, memory cant be changed)
    Node* newNode = (Node*)malloc(sizeof(Node));
    
    // checking if memory has been allocated properly
    if (newNode == NULL){
        printf("The memory hasnt been allocated.");
        exit(1);
    }
    // need to initialize its data now, copying the input data to the new node
    strcpy(newNode->data, data);

    // initializing the child pointers to NULL
    newNode->left = NULL;
    newNode->right = NULL;
    
    // finally return the newNode
    return newNode;

}

// The parseExpression function parses the expression string passed in from command line, stores the information in a new node, and returns the root node of the tree.
Node* parseExpression(char *expr) {
    // Check if the expression is empty
    if (expr == NULL || strlen(expr) == 0) {
        printf("The expression is empty\n");
        return NULL;
    }

    int length = strlen(expr);
    // Remove outer parentheses if they exist
    if (expr[0] == '(' || expr[length - 1] == ')'){
        expr[length - 1] = '\0'; // Null-terminate the string before the last parenthesis
        expr++; // Move the pointer to the next character
        length -= 2; // Adjust the length
    }

    // will use this to increm/decrement and go through the expression 
    int countParenthesis = 0;
    // Scan the expression from right to left to find the main operator
    for (int i = length - 1; i >= 0; i--) {
        if (expr[i] == ')') {
            countParenthesis++;
        } else if (expr[i] == '(') {
            countParenthesis--;
        } else if (countParenthesis == 0) {
            // Check for '+' or '-' operators outside parentheses
            if (expr[i] == '+' || expr[i] == '-') {
                char operator[2] = {expr[i], '\0'};
                Node* node = createNode(operator); // Create a new node for the operator
                expr[i] = '\0'; // Null-terminate the left sub-expression
                node->left = parseExpression(expr); // Recursively parse the left sub-expression
                node->right = parseExpression(expr + i + 1); // Recursively parse the right sub-expression
                return node; // Return the created node
            }
        }
    }

    // if we cant find any + or - , we look for * or /
    for (int j = length - 1; j >= 0; j--){
        if (expr[j] == ')'){
            countParenthesis++;
        } else if (expr[j] == '('){
            countParenthesis--;
        } else if (countParenthesis == 0){
            // checking if * or / operaters outisde the paranthesis
            if (expr[j] == '*' || expr[j] == '/'){
                char operator[2] = {expr[j], '\0'}; // creating a string for the operator
                Node* node = createNode(operator); // creating new node for either * or /
                expr[j] = '\0'; // when main operator found,  i use \0 to insert a null character at the operator’s position
                node->left = parseExpression(expr); // parsing the left sub-expression
                node->right = parseExpression(expr + j + 1); // parsing the right sub expression
                return node;
            }
        }
    }

    // if no operators are found, then the expression is likely just a number or var, so we create a node for the #
    return createNode(expr);
}


// The preOrder function prints tree nodes in preorder traversal.
void preorder(Node *root){
    // preorder works by printing the root node, traverses to the left tree as far as it can, then the right subtree
    // preorder Resource: https://courselink.uoguelph.ca/d2l/le/content/911255/viewContent/3962993/View

    // if the current node is empty, then we return
    if (root == NULL){
        return;
    }

    // processing current node by printing its data
    printf("%s ", root->data);

    // now, recursively traverse to left subtree, and print its data
    preorder(root->left);

    // then, recursively traverse to the right subtree, print its data
    preorder(root->right);

}

// The inOrder function prints tree nodes in inorder traversal fully parenthesized.
void inorder(Node *root){
    // The Inorder Traversal visits the nodes in the following order: Left, Root, Right.

    // Resource: https://www.geeksforgeeks.org/inorder-traversal-of-binary-tree/?ref=header_outind

    // if the current node is empty, we return
    if (root == NULL){
        return;
    }
    // printing the opening paranthesis before the left subtree
    printf("(");

    // first we recursively print the left subtree
    inorder(root->left);

    // now print the node
    printf("%s", root->data);

    // then go to the right subtree recursively
    inorder(root->right);

    // printing the closing paranthesis after the right subtree
    printf(")");

}

// The postOrder function prints tree nodes in postorder traversal.
void postorder(Node *root){
    // Post order: left subtree, then right, then root

    // if current node empty, we return
    if (root == NULL){
        return;
    }

    // first we recursively go the left subtree
    postorder(root->left);

    // then we recursively go to the right subtree
    postorder(root->right);

    // Finally, process the root node by printing its data
    printf("%s ", root->data);
}

// The promptVariables function prompts the user to assign values to each variable found in the expression tree. The values should be stored in the Variables struct.
void promptVariables(Node *root){
    // checking if the root is null
    if (root == NULL){
        return;
    }
    
    // if the current node is a variable
    if (root->data[0] == 'x'){
    int doesItExist = 0;
    // checking if a vairbale has already been prompted for
    for (int j = 0; j < varCount; j++){
        if (strcmp(variables[j].varName, root->data) == 0){
            doesItExist = 1;
            break;
        }
    }

    // Only prompt if it's a new variable
    if (!doesItExist){
        // prompt user for a value
        printf("Assign a value to the variable %s: ", root->data);
        float varX;
        scanf("%f", &varX);
        
        // storing the variables name and value in the global array variables
        strcpy(variables[varCount].varName, root->data);
        variables[varCount].value = varX;
        varCount++;
    }

}
  
    // recursively prompt for variables in left and right subtree
    promptVariables(root->left);
    promptVariables(root->right);
}

// The calculate function calculates the expression and returns its result. Division by 0 and/or other error scenarios should be checked.
float calculate(Node *root){
    // checking if the root is null
    if (root == NULL){
        return 0;
    }

    // checking if the current leaf is a number, 
    if (isdigit(root->data[0])){
        return atof(root->data);
    }


    // checking if the current leaf is a variable
    if (root->data[0] == 'x'){
        // loop through the variables array
        for (int j = 0;  j < varCount; j++){
            if (strcmp(variables[j].varName, root->data) == 0){
                return variables[j].value;
            }
        }
        printf("Error: Variable %s not found\n", root->data);
        return 0;

    } 

        // calculating the values from the left and right subtree's
        float leftResult = calculate(root->left);
        float rightResult = calculate(root->right);
        
        // If not leaf, this must be an operator
        switch(root->data[0])  {
            case '+':
                return leftResult + rightResult;
            case '-':
                return leftResult - rightResult;
            case '*':
                return leftResult * rightResult;
            case '/':
                if (rightResult == 0){
                    printf("cant do division by zero\n");
                    return 0;
                }
                return leftResult/ rightResult;
            default:
                printf("please make sure valid operator");
                return 0;
    }
}