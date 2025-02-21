#include "dll.h"

// Function to display the contents of the database

int display_database(Main **arr)
{
    // Clear the terminal screen for a clean output
    system("clear");

    // Print the header of the display table
    printf(GREEN"%s\t%s\t  %s\t%s\t%s\n", "Index", "Word", "Filecount", "Files Name", "Wordcount"RESET);

    // Iterate through all the slots in the array
    for (int i = 0; i < 28; i++) {
        // Skip empty slots (no words stored at this index)
        if (arr[i] == NULL) {
            continue;
        } else {
            // If the slot is not empty, traverse the linked list of 'Main' nodes
            Main *temp = arr[i];
            while (temp != NULL) {
                // Print the index, word, and file count for the current 'Main' node
                printf("[%d]\t%s\t\t%d\t", i, temp->word, temp->f_count);

                // Pointer to traverse the linked list of 'Sub' nodes
                Sub *temp2 = temp->s_link;
                int count = 0;

                // Traverse the list of 'Sub' nodes for the current word
                while (temp2 != NULL) {
                    // For the first file, print on the same line as the word
                    if (count == 0)
                        printf("%s\t\t%d\n", temp2->f_name, temp2->w_count);
                    else
                        // For subsequent files, print in a new line with proper formatting
                        printf("\t\t\t\t%s\t\t%d\n", temp2->f_name, temp2->w_count);

                    count++;
                    temp2 = temp2->link; // Move to the next 'Sub' node
                }

                // Move to the next 'Main' node
                temp = temp->m_link;
            }
        }
    }

    return SUCCESS; // Return success after displaying the database
}
