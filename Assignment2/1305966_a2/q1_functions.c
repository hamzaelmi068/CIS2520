#include "q1.h"

/*
Name: Hamza Elmi
Student ID: 1305966
Assignment 2, Question 1
*/

/* function will display the primary user interface
    This  done for you*/
void prompt(){

  printf("1. Add a new car to the available-for-rent list,\n");
  printf("2. Add a returned car to the available-for-rent list,\n");
  printf("3. Add a returned car to the repair list,\n");
  printf("4. Transfer a car from the repair list to the available-for-rent list,\n");
  printf("5. Rent the first available car,\n");
  printf("6. Print all the lists,\n");
  printf("7. Quit.\n");
}

/**
 * Inserts a new car into the linked list.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @param mileage Integer representing the car's mileage.
 * @param return_date Integer representing the car's return date, you can have -1 represent no return date.
 * @return Pointer to the newly added car in the list.
 */
struct car * insert_to_list(struct car ** head, char plate[], int mileage, int return_date){
    // check if a plate is already in the list
    if (is_plate_in_list(*head, plate)){
        printf("Car with plate %s is already in the list, try adding a different one.\n", plate);
        return NULL; // returning null if we dont insert anything at all
    }
    // ill begin by creating a new node that'll hold the car info, and allcoate memory too
    struct car *new_car = (struct car*)malloc(sizeof(struct car));
    // null check below
    if (new_car == NULL){
        printf("memory couldnt be allocated.\n");
        return NULL;
    }

    // Initialize the new car's data
    strcpy(new_car->plate, plate);
    new_car->mileage = mileage;
    new_car->return_date = return_date;
    new_car->next = NULL;

    // inserting at the beginning if the list is empty or new car has lower mileage than the first car
    if (*head == NULL || (*head)->mileage > new_car->mileage){
        new_car->next = *head;
        *head = new_car;
    }
    else{
        // inserting in the middle or end of the list
        struct car *current = *head;
        // traversing through list to find correct position
        while(current->next != NULL && current->next->mileage < new_car->mileage){
            current = current->next;
        }
        // now, insert new car at the right position
        new_car->next = current->next;
        current->next = new_car;
    }
    // sorting the entire list after inserting all of the car nodes we did above
    // sort_list(head, true, false); // doesnt make sense to sort here because we dont know if its sorting by mileage or return date
    return new_car;
}

/**
 * Prints all the cars in the list.
 * @param head Pointer to the head of the list.
 * This function prints out the car details, it should not print return date if it does not exist.
 */
void print_list(struct car *head){
    // setting the current pointer to head of the list
    struct car *current = head;
    // while the LL isnt empty, we loop through the LL
    while (current != NULL){
        printf("plate: %s, Mileage: %d, Return date: %d\n", current->plate, current->mileage, current->return_date);
        if (current->return_date != -1){
            date(current->return_date); // using data helper to format the date
        } else{
            printf("Not found.");
        }
        printf("\n");
        // move current to next pointer
        current = current->next;
    }
}

/**
 * Checks if a car's plate is already in the list.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @return Boolean value indicating if the plate is found.
 */
bool is_plate_in_list(struct car * head, char plate[]){
    // starting with a ptr to traverse our list
    struct car *current = head;

    // loop through the list
    while (current != NULL){
        // if we've gone through the list, and the plate is there, return true
        int comparisonResult = strcasecmp(current->plate, plate);
        if (comparisonResult == 0){
            return true;
        }
        current = current->next;
    }
    // If we've gone through the entire list without finding a match, return false
    return false;
}

/**
 * Swaps two cars in the list.
 * @param a Pointer to the first car.
 * @param b Pointer to the second car.
 * Swaps the plate, mileage, and return date of two cars.
 */
void swap(struct car *a, struct car *b){
    // swapping blueprint:
    // temp = a;
    // a = b;
    // b = temp;

    // for plate string, ill use a temp array
    char temp_plate[8];
    // swapping the plates
    strcpy(temp_plate, a->plate);
    strcpy(temp_plate, b->plate);
    strcpy(b->plate, temp_plate);

    // for mileage and return_date, ill use a another temp var to swap
    int temp_Mileage;
    // swapping the mileage
    temp_Mileage = a->mileage;
    a->mileage = b->mileage;
    b->mileage = temp_Mileage;

    // swapping the return_date
    int tempReturnDate;
    tempReturnDate = a->return_date;
    a->return_date = b->return_date;
    b->return_date = tempReturnDate;
}

/**
 * Sorts the list of cars based on mileage or return date.
 * @param head Pointer to the head of the list.
 * @param sort_by_mileage Boolean to sort by mileage.
 * @param sort_by_return_date Boolean to sort by return date.
 */
void sort_list(struct car ** head, bool sort_by_mileage, bool sort_by_return_date){
    // check if the list is empty
    if (*head == NULL || (*head)->next == NULL){
        return;
    }

    bool swapped;
    struct car *current1;
    struct car *lastcurrent = NULL;

    // Implementing bubble sort to sort the list based on the criteria
    do{
        swapped = false;
        current1 = *head; // starting from the head of the list
        
        // traverse the list up to the last sorted element
        while (current1->next != lastcurrent){
            bool should_swap = false; // using this flag to see if swap is needed
            // Determine if we should swap based on the sorting criteria
            if (sort_by_mileage && current1->mileage > current1->next->mileage){
                should_swap = true; // swap if sorting by mileage and current node mileage is greater
                } else if (sort_by_return_date && current1->return_date > current1->next->return_date){
                should_swap = true; // swap if sorting by return date and current 
            }
            if (should_swap){
                // Swap the data of the nodes using the swap function
                swap(current1, current1->next);
                swapped = true; // set swapped flag to true as a swap has occured
            }
            // move on to the next node
            current1 = current1->next;

        }
        
        lastcurrent = current1;
    } while (swapped);
}

/**
 * Removes a car from the list by its plate number.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @return Pointer to the removed car.
 */
struct car * remove_car_from_list(struct car **head, char plate[]) {
    struct car *current = *head;  // Start from the head of the list
    struct car *previous = NULL;

    if (*head == NULL){
        printf("error: list is empty.\n");
        return NULL;
    }

    // Iterate through the list
    while (current != NULL) {
        // Compare current car's plate with given plate
        if (strcmp(current->plate, plate) == 0) {
            // Found the car to remove

            // Handling case if it's the first node
            if (previous == NULL) {
                *head = current->next;
            } else {
                // Car to remove isn't the first node
                previous->next = current->next;
            }

            // taking out current node from list
            current->next = NULL;
            return current;  // Return removed car
        }

        // Move to next node
        previous = current;
        current = current->next;
    }
    
    // if we've gone through entire list and without funding a match, we return null
    return NULL;
}

/**
 * Removes the first car from the list.
 * @param head Pointer to the head of the list.
 * @return Pointer to the removed car.
 */
struct car * remove_first_from_list(struct car **head){
    
    // check if the list is empty
    if (*head == NULL){
        return NULL; // cant really remove from an empty list
    }
    // saving the first node
    struct car *very_first_car = *head;
    
    // update the head to point to the next node (this will become the first node now)
    *head = (*head)->next;

    // detaching and removing first car node from list
    very_first_car->next = NULL;
    
    // returning the removed car
    return very_first_car;
}


/**
 * Calculates the profit based on the mileage difference.
 * @param initial_mileage Integer representing the car's starting mileage.
 * @param final_mileage Integer representing the car's final mileage.
 * @return Double value representing the calculated profit.
 */
double profit_calculator(int initial_mileage, int final_mileage){
    // calculating mileage different
    int mileageDifference = final_mileage - initial_mileage;
    
    // need to check if mileage difference is valid
    if (final_mileage < initial_mileage){
        printf("The mileage is invalid, final mileage should be greater.\n");
        return -1;
    }

    // calculating profit based on mileage difference
    double profitBased;
    if (mileageDifference < 200){
        profitBased = 80.0; // flat rate for up too 200 km
    } else{
        profitBased = 80.0 + (mileageDifference - 200) * 0.15; // flat rate plus additional charge
    }
    // returning the profit
    return profitBased;
}

/**
 * Writes the list of cars to a file.
 * The file would be in the format: plate,mileage,return_date
 * @param filename Character array with the file name.
 * @param head Pointer to the head of the list.
 * Writes the details of each car in the list to a file.
 */
void write_list_to_file(char *filename, struct car *head){
    FILE *fptr = fopen(filename, "w"); // opening the file in write mode
    // checking if the file is empty
    if (fptr == NULL){
        printf("Error opening the file.\n");
        return; // exiting the function if file cant be opened
    }

    // need to iterate through the linked list, starting with the head
    struct car *current = head;
    while (current != NULL){
        // writing each car detail to the file
        fprintf(fptr, "%s, %d, %d\n", current->plate, current->mileage, current->return_date);
        // moving on to the next car
        current = current->next;
    }
    // finally , closing the file
    fclose(fptr);
}

/**
 * Reads car details from a file and adds them to the list.
 * The file would be in the format: plate,mileage,return_date
 * @param filename Character array with the file name.
 * @param head Pointer to the head of the list.
 * Reads data from the file and inserts each car into the list.
 */
void read_file_into_list(char *filename, struct car **head) {
    FILE *fptr = fopen(filename, "r"); // Opening the file in read mode
    if (fptr == NULL) {
        printf("Error opening file %s.\n", filename);
       return;
    }

    char plate[9]; // Ensure the buffer size is correct (8 characters + null terminator)
    int mileage;
    int return_date;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), fptr)) {
        buffer[strcspn(buffer, "\r\n")] = 0; // removing potential spaces or newlines
         if (sscanf(buffer, "%8[^,],%d,%d", plate, &mileage, &return_date) == 3) { // Adjusted for commas
            printf("Read: %s %d %d\n", plate, mileage, return_date); // Debug print
            insert_to_list(head, plate, mileage, return_date);
        } else {
            printf("Error parsing line: %s\n", buffer); // Error message for parsing issues
        }
    }

    if (fclose(fptr) != 0) {
        printf("Error closing file %s.\n", filename);
    }
}



/**
 * Prints the date in the format of year/month/day.
 * @param date Integer representing the date in YYMMDD format.
 */
void date(int date){ /*NEED TO VALIDATE 1-12 FOR MONTH, AND 1-31 FOR THE DATE or day*/
    // declaring the date variables we need
    int year;
    int month;
    int day;

    year = date / 10000;    // first two digits
    month = (date / 100) % 100; // next two digits
    day = date % 100; // last two digits

    // Month validation
    if (month > 12 || month < 1) {
        printf("Error, the month has to be between 1-12\n");
    } else if (day > 31 || day < 1) { // Day validation
        printf("Error, the day has to be between 1-31.\n");
    } else {
        // Printing the date in the format year/month/day
        printf("%02d/%02d/%02d\n", year, month, day);
    }
}


/**
 * Frees all the memory allocated for the cars in the list.
 * @param head Pointer to the head of the list.
 * Frees each car node in the list.
 */
void free_list(struct car ** head){
    struct car *current = *head;
    struct car *next;
    // checking if the list is empty
    if (current == NULL){
        printf("Error, empty list.....");
        return;
    }
    // iterating through the list
    while (current != NULL){
        // storing the next node in next
        next = current->next;
        free(current); // freeing the memory for the car
        current = next; // moving on to the next car
    }

    // setting the head to NULL, after freeing, to avoid pitfalls with ptrs
    *head = NULL;
}

int isThisValidPlate(char *plate) {
    int len = strlen(plate);
    if (len < 2 || len > 8) {
        return 0; // Invalid length
    }
    for (int i = 0; i < len; i++) {
        if (!isalnum(plate[i])) {
            return 0; // Non-alphanumeric character found
        }
    }
    return 1; // Valid plate
}