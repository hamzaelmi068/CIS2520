#include <stdio.h>

int main()
{
    int A[5] = {1, 3, 7, 4, 0};
    
        int *P[5],
        *pA;
    int i, x, y;


    // Set pointer to the base address of array
    //*pA = &A; // incorrect assignment
    pA = &A[0];  // correct version

    // Assign A[1] to x and y
    x = *pA + 1; // correct
    //A++; // incorrect, we cannot just increment an array name itself, its not modifiable this way
    pA = pA + 1; // correct
    //y = *A; // incorrect
    y = *pA;

    printf("x = \t%d", x);
    printf("y = \t%d", y);

    // Set every pointer to one array element
    for (i = 0; i < 5; i++)
        //*P[i] = &A[i]; // incorrect
        P[i] = &A[i];
    // print array elements using pointers
    for (i = 0; i < 5; i++)
        printf("\t%d", *(P[i] + 1)); // incorrect 
    return 0;
}