#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "a3q2_header.h"

/*
 * The downHeap function performs the downheap algorithm.
 * The key at the passed position is swapped with the key of it's child with the largest value.
 * If the key is smaller, than both of it's children's keys then no swap happens.
 * After swap, the downHeap is called again to the new position of the swapped key and it terminates when it's value is smaller than both children.
*/
void downHeap(int key[20], int pos, int array[20][10]){
    // finding the left and right child positions
    int leftChild = 2 * pos + 1;
    int rightChild = 2 * pos + 2;

    // larger child 
    int largerChild = pos;

    // comparing with left child if it exists
    if (leftChild < 20) {
        if (key[leftChild] > key[largerChild]){ // if the leftchild is greater then the 
        // update largerchild if left is bigger
            largerChild = leftChild;
        }
    }
    
    // comparing with right child, if it exists, and updating largerchild if right is bigger then left
    if (rightChild < 20) {
        if (key[rightChild] > key[largerChild]){
            // updating the larger child if right is bigger, since in maxheap, the current root must have the largest key
            largerChild = rightChild;
        }
    }

    // if larger child found, we swap, then apply recursion
    if (largerChild != pos){
        // swap current pos with larger child
        swap(pos, largerChild, key, array);
        // recursive call to downheap
        downHeap(key, largerChild, array);
    }
}



// The isParent function returns true if the passed position has a child or false if there's no child
bool isParent(int keyPos) {
    // checking if the left child exists within the array bound (which is 20)
    if (2 * keyPos + 1 < 20) { // left child = 2 * keyPos + 1
        printf("A left child exists.\n");
        return true;
    }
    // checking if the right child exists within the array bound (which is 20)
    if (2 * keyPos + 2 < 20) { // right child = 2 * keyPos + 2
        printf("A right child exists.\n");
        return true;
    }
    // if neither left nor right child exists, return false
    printf("The passed position has no child.\n");
    return false;
}


// The swap function swaps 2 rows in the 2D array and the key array. It receives the position of the 2 rows to be swapped, the key array, and the 2D array in its arguements.
void swap(int key1Pos, int key2Pos, int key[20], int array[20][10]){
    // assuming the key1pos and key2pos are 1 based (ranging from 1-20) , so we subtract one because 20-1 = [19], if they're 0-19, we dont subtract 1

    // using a temp variable to swap the keys
    int temp;

    // swapping the keys in the key array
    temp = key[key1Pos];
    key[key1Pos] = key[key2Pos];
    key[key2Pos] = temp;
    

    // now we swap the rows in the 2d array
    for (int j = 0; j < 10; j++){
        temp = array[key1Pos][j];
        array[key1Pos][j] = array[key2Pos][j];
        array[key2Pos][j] = temp;
    }

}
