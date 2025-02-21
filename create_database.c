#include "dll.h"

// External variable to indicate if the database has been created
extern int create;

// Function to create a database from a list of files

int Create_database(flist **head, Main **arr, flist **head2)
{
    // Clear the terminal screen for a clean output
    system("clear");

    flist *head1 = NULL;

    // If the secondary list is not NULL, remove duplicate files
    if (head2 == NULL) {
        head1 = *head2;
    } else {
        head1 = remove_duplicate_files(head, head2);
    }

    // Set the 'create' flag to indicate the database has been created
    create = 1;

    // Pointer to traverse the list of files
    flist *temp = head1;

    // Iterate through the list of files
    while (temp != NULL) {
        // Open the current file in read mode
        FILE *fptr = fopen(temp->f_name, "r");
        if (!fptr) {
            return FAILURE; // Return failure if the file cannot be opened
        }

        char str[100]; // Buffer to store words read from the file
        int index;     // Index to determine the appropriate slot in the array

    label:
        // Read words from the file one by one
        while (fscanf(fptr, "%s", str) != EOF) {
            // Determine the index based on the first character of the word
            if (str[0] >= 'A' && str[0] <= 'Z') {
                index = str[0] - 'A';
            } else if (str[0] >= 'a' && str[0] <= 'z') {
                index = str[0] - 'a';
            } else if (str[0] >= '0' && str[0] <= '9') {
                index = 26; // Numbers are stored in slot 26
            } else {
                index = 27; // Special characters are stored in slot 27
            }

            // If the slot in the array is empty, create a new main node
            if (arr[index] == NULL) {
                // Allocate memory for the main node and subnode
                Main *mainnode = malloc(sizeof(Main));
                Sub *subnode = malloc(sizeof(Sub));

                if (mainnode == NULL || subnode == NULL) {
                    return FAILURE; // Return failure if memory allocation fails
                }

                // Initialize the main node
                strcpy(mainnode->word, str);
                mainnode->m_link = NULL;
                mainnode->s_link = subnode;
                mainnode->f_count = 1;

                // Initialize the subnode
                strcpy(subnode->f_name, temp->f_name);
                subnode->link = NULL;
                subnode->w_count = 1;

                // Store the main node in the array
                arr[index] = mainnode;
            } 
            // If the slot in the array is not empty, search for the word
            else {
                Main *temp1 = arr[index];
                Main *temp2 = NULL;

                // Traverse the linked list of main nodes at the current index
                while (temp1 != NULL) {
                    // If the word already exists in the database
                    if (strcmp(str, temp1->word) == 0) {
                        Sub *temp2 = temp1->s_link;
                        Sub *t3 = NULL;

                        // Traverse the linked list of subnodes
                        while (temp2 != NULL) {
                            // If the file already exists for the word
                            if (strcmp(temp->f_name, temp2->f_name) == 0) {
                                (temp2->w_count)++; // Increment the word count
                                goto label; // Skip further processing for this word
                            }
                            t3 = temp2;
                            temp2 = temp2->link;
                        }

                        // If the file is not found, create a new subnode
                        Sub *subnode = malloc(sizeof(Sub));
                        if (subnode == NULL) {
                            return FAILURE; // Return failure if memory allocation fails
                        }
                        strcpy(subnode->f_name, temp->f_name);
                        subnode->link = NULL;
                        subnode->w_count = 1;

                        // Add the new subnode to the list
                        t3->link = subnode;

                        // Increment the file count for the main node
                        (temp1->f_count)++;
                        goto label;
                    }

                    // Move to the next main node
                    temp2 = temp1;
                    temp1 = temp1->m_link;
                }

                // If the word is not found, create a new main node
                if (temp1 == NULL) {
                    Main *mainnode = malloc(sizeof(Main));
                    Sub *subnode = malloc(sizeof(Sub));

                    if (mainnode == NULL || subnode == NULL) {
                        return FAILURE; // Return failure if memory allocation fails
                    }

                    // Initialize the main node
                    strcpy(mainnode->word, str);
                    mainnode->m_link = NULL;
                    mainnode->s_link = subnode;
                    mainnode->f_count = 1;

                    // Initialize the subnode
                    strcpy(subnode->f_name, temp->f_name);
                    subnode->link = NULL;
                    subnode->w_count = 1;

                    // Add the new main node to the linked list
                    temp2->m_link = mainnode;
                }
            }
        }

        // Move to the next file in the list
        temp = temp->link;
    }

    return SUCCESS; // Return success after processing all files
}
