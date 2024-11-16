//Libraries Used Add more here if needed
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>

//Our Linked List Node
struct car{
  char plate[9];
  int mileage;
  int return_date; //Return date should be -1 for a car with no return date
  struct car *next;
};


//Function definitions
void prompt();
int isThisValidPlate(char *plate);

// Main functions
void prompt(); // Option 1: Add a new car to the available-for-rent list
struct car *insert_to_list(struct car **head, char plate[], int mileage, int return_date); // Option 1: Main function
void print_list(struct car *head); // Option 6: Main function
struct car *remove_first_from_list(struct car **head); // Option 5: Main function


double profit_calculator(int initial_mileage, int final_mileage); // turns out this is a helper for returned transaction codes (2 & 3)

// Helper functions
bool is_plate_in_list(struct car *head, char plate[]); // Helper: used for checking if plate is in list. Used it in insert_to_list function
void swap(struct car *a, struct car *b); // Helper: used to swap two car nodes, used in sorting list function  
void sort_list(struct car **head, bool sort_by_mileage, bool sort_by_return_date); // Helper: used in insert to list, to maintain the order of cars in the list
struct car *remove_car_from_list(struct car **head, char plate[]); // Helper
void write_list_to_file(char *filename, struct car *head); // Helper: used for saving current state of lists to the files we have
void read_file_into_list(char *filename, struct car **head); // Helper: helps initilize files from saved files 
void date(int date); // Helper: used in printlist
void free_list(struct car **head); // Helper: used during exit process, case 7 in main.