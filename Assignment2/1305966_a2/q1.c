#include "q1.h"

/*
 * A basic menu based structure has been provided
*/

int main(){

    //Our three Linked Lists
    struct car *available_head = NULL;
	struct car *rented_head = NULL;
	struct car *repair_head = NULL;

    // reading the existing data from the 3 files
    read_file_into_list("available.txt", &available_head);
    read_file_into_list("rented.txt", &rented_head);
    read_file_into_list("repair.txt", &repair_head);


    int choice;
    /* variable declarations*/
    char plate[9];
    int mileage;
    int return_date;

    /* Profit calculation */
    //int initial_mileage;
    //int final_mileage;

    // Write list to file functions vars
    //char filename[20] = "available.txt"; // Filename for writing/reading (decided to hardcode using readfile function)
    //int date; // date in YYMMDD format


    do
    {   
        // calling the prompt from my header file with the menu
        prompt();
        // user enters choice for my menu below
        printf("Enter a Choice: ");
        scanf("%d", &choice);
        // error check , the menu choice needs to be between 1-7, if it isnt then we prompt again with menu
        if (choice > 7 || choice < 1){
            printf("Invalid choice, please re enter your choice\n");
            continue;
        }
        
        /*
         * You will need to add all the cases
         * Call the appropriate functions
         * You would also need to save data to disc upon exit
         * File Format: plate,mileage,return_date
         * Error Handling needs to happen too
        */

        switch (choice)
        {
         case 1:
            // prompt for plate
            printf("Enter the plate: ");
            scanf("%8s", plate);
            // user input for the mileage
            printf("Enter the mileage: ");
            scanf("%d", &mileage);
            if (isThisValidPlate(plate)) {
                // if the plate is valid we can insert the plate and other info as needed below here
                printf("Plate %s is valid.\n", plate);
                insert_to_list(&available_head, plate, mileage, -1);
                sort_list(&available_head, true, false); // sorting by mileage
                printf("Car with plate %s added to available-for-rent list.\n", plate);
            } else {
                printf("The plate %s is invalid.\n", plate);
            }
            break;
        case 2:
            // user input for returend car plate
            printf("enter the plate for the returned car: ");
            scanf("%8s", plate);
            // prompt for mileage
            printf("Enter the mileage for returned car: ");
            scanf("%d", &mileage);
            // move car from rented list to availble for rent list
            struct car*returned_car = remove_car_from_list(&rented_head, plate);
            if (returned_car == NULL){
                printf("Error: Car with plate %s not found in the rented list.\n", plate);
                break;
            }
            // calculating profit
            double profit_case2 = profit_calculator(returned_car->mileage, mileage);
            printf("Charge for the car with plate %s is $%.2f\n", plate, profit_case2);
            returned_car->mileage = mileage;
            returned_car->return_date = -1;
            insert_to_list(&available_head, returned_car->plate, returned_car->mileage, returned_car->return_date);
            sort_list(&available_head, true, false); // sorting for mileage. 
            printf("Car with plate %s moved to available-for-rent list. \n", plate);
            break;
        case 3:
            printf("Enter the plate for the returned car: ");
            scanf("%s", plate);
            // prompt for mileage
            printf("Enter the mileage for returned car: ");
            scanf("%d", &mileage);
            // Move car from rented list to the repair list
            struct car *repair_car = remove_car_from_list(&rented_head, plate);
            // calculating profit
            double profit_case3 = profit_calculator(repair_car->mileage, mileage);
            printf("Charge for the car with plate %s is $%.2f\n", plate, profit_case3);
            repair_car->mileage = mileage;
            repair_car->return_date = -1;
            insert_to_list(&repair_head, repair_car->plate, repair_car->mileage, repair_car->return_date);
            printf("Car with plate %s moved to in-repair list.\n", plate);
            break;
        case 4:
            // User input for plate number
            printf("Enter the plate number for the car to be moved to available-for-rent: ");
            scanf("%s", plate);
            // Move car from in-repair list to available-for-rent list
            struct car *available_car = remove_car_from_list(&repair_head, plate);
            // checking if returned 
            if (available_car == NULL){
                printf("Error: Car with plate %s not found in the rented list.\n", plate);
                break;
            }
            available_car->return_date = -1;
            insert_to_list(&available_head, available_car->plate, available_car->mileage, available_car->return_date);
            sort_list(&available_head, true, false); // sorting by mileage
            printf("Car with plate %s moved to available-for-rent list.\n", plate);
            break;
        case 5:
            // rent the first availble car
            if (available_head == NULL){
                printf("no available cars for rent");
                break;
            }
            struct car *rent_car = remove_first_from_list(&available_head);
            printf("Enter the expected return date: ");
            scanf("%d", &return_date);

            // Validate and print the date using the date function
            if (return_date < 10101 || return_date > 991231) {
                printf("Error: Invalid date format.\n");
                break;
            }

            date(return_date); // using the date function to print the date
            if ((return_date / 10000) % 100 < 1 || (return_date / 10000) % 100 > 12) {
            // If date() printed an error message about invalid month, break
            break;
        }    
            rent_car->return_date = return_date;
            insert_to_list(&rented_head, rent_car->plate, rent_car->mileage, rent_car->return_date);
            sort_list(&rented_head, false, true); // sorting by return date, using helper
            printf("Car with plate %s rented.\n", plate);
            break;
        case 6:
            // print all the lists
            printf("Available-for-rent cars:\n");
            print_list(available_head);
            // renting cars :
            printf("Rented cars:\n");
            print_list(rented_head);
            // repaired cars LL
            printf("In-repair cars:\n");
            print_list(repair_head);
            break;

        case 7:
            // Save data to files and exit
            write_list_to_file("available.txt", available_head);
            write_list_to_file("rented.txt", rented_head);
            write_list_to_file("repair.txt", repair_head);
            printf("The Data has been saved to files. Now we are exiting program.\n");
            // freeing all the lists
            free_list(&available_head);
            free_list(&rented_head);
            free_list(&repair_head);
            exit(0);

        default:
            printf("Invalid choice, please re enter your choice again");
            break;
        }
        
    } while (choice != 7);
    

    return 0;
}