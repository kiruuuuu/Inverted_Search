#include "dll.h"

// Global variables to track database creation and update status
int create;
int update;

// Main function to execute the program
int main(int argc, char *argv[])
{
    flist *head = NULL; // Linked list to store file names
    flist *head2 = NULL; // Backup file name list
    Main *arr[28] = {NULL}; // Array of 28 pointers for the database (A-Z, numbers, special characters)

    // Validate the input files and populate the linked list
    read_validate(argc, argv, &head);

    char data[10]; // Input string for search
    char file_name[10]; // File name for saving the database
    char f_name[10]; // Backup file name for updating the database
    int choice; // User's menu choice
    char ch = 'y'; // To continue or exit the menu loop

    // Main menu loop
    while (ch == 'y' || ch == 'Y')
    {
        // Display menu options
		//system("clear");
        printf("1. Create Database\n2. Display Database\n3. Search Database\n4. Save Database\n5. Update Database\nEnter the choice\n");
        scanf(" %d", &choice);

        // Switch-case to handle user choice
        switch (choice)
        {
        case 1: // Create Database
            if (argc == 1) // No input files provided
            {
                printf(RED "Error: Invalid number of arguments\n" RESET);
                printf(RED "Please provide input files like: f1.txt f2.txt\n" RESET);
                return 0;
            }
            if (create == 1) // Check if the database is already created
            {
                printf(RED "INFO: Database already created, creation not possible\n" RESET);
                return 0;
            }
            // Call the Create_database function
            if (Create_database(&head, arr, &head2) == FAILURE)
            {
                printf(RED "INFO: Create database failed\n" RESET);
            }
            else
            {
                printf(GREEN "INFO: Create database succeeded\n" RESET);
            }
            break;

        case 2: // Display Database
            // Call the display_database function
            if (display_database(arr) == FAILURE)
            {
                printf(RED "INFO: Display database failed\n" RESET);
            }
            else
            {
                printf(GREEN "INFO: Display database succeeded\n" RESET);
            }
            break;

        case 3: // Search Database
            printf("Enter the word to search: ");
            scanf(" %s", data);
            // Call the search_database function
            search_database(arr, data);
            break;

        case 4: // Save Database
            system("clear");
            printf("Enter the file name to save the database: ");
            scanf("%s", file_name);
            // Call the save_database function
            if (save_database(arr, file_name) == SUCCESS)
            {
                printf(GREEN "INFO: Database saved successfully\n" RESET);
            }
            else
            {
                printf(RED "INFO: Database save failed\n" RESET);
            }
            break;

        case 5: // Update Database
            system("clear");
            if (create == 1) // Check if the database is already created
            {
                printf(RED "INFO: Database already created, update not possible\n" RESET);
                create = 0;
                return 0;
            }
            if (update == 1) // Check if the database is already updated
            {
                printf(RED "INFO: Database already updated, update not possible\n" RESET);
                return 0;
            }
            if (argc == 1 || argc > 1) // Check for valid arguments
            {
                printf("Enter the backup file name: ");
                scanf("%s", f_name);
                // Call the update_database function
                if (update_database(&head2, arr, f_name) == SUCCESS)
                {
                    printf(GREEN "INFO: Update database succeeded\n" RESET);
                }
                else
                {
                    printf(RED "INFO: Update database failed\n" RESET);
                }
            }
            break;

        default: // Invalid choice
            printf(RED "INFO: Invalid option\n" RESET);
        }

        // Prompt to continue or exit
        printf("Do you want to continue (y/Y): ");
        scanf(" %c", &ch);
    }
}
