#include "dll.h"

// Function to save the database to a file

int save_database(Main **arr, char file_name[])
{
    system("clear"); // Clear the terminal screen for a clean display

    // Check if the file name has a ".txt" extension
    if (strcmp(strstr(file_name, "."), ".txt") == 0)
    {
        // Open the file in write mode
        FILE *fptr = fopen(file_name, "w");
        if (fptr == NULL) // Check if the file was successfully opened
        {
            return FAILURE; // Return FAILURE if file opening failed
        }

        // Loop through all indices in the array (0-27)
        for (int i = 0; i < 28; i++)
        {
            if (arr[i] == NULL) // If the current index has no data, skip it
            {
                continue;
            }
            else
            {
                Main *temp = arr[i]; // Pointer to traverse the linked list at the current index

                // Traverse the linked list at the current index
                while (temp != NULL)
                {
                    // Write the main node data to the file
                    // Format: #<index>;<word>;<file_count>
                    fprintf(fptr, "#%d;%s;%d", i, temp->word, temp->f_count);

                    Sub *temp2 = temp->s_link; // Pointer to traverse the sublist

                    // Traverse the sublist and write file names and word counts
                    while (temp2 != NULL)
                    {
                        // Format: ;<file_name>;<word_count>
                        fprintf(fptr, ";%s;%d", temp2->f_name, temp2->w_count);
                        temp2 = temp2->link; // Move to the next sublist node
                    }

                    // Add a delimiter (#) and a newline after each main node
                    putc('#', fptr);
                    putc('\n', fptr);

                    temp = temp->m_link; // Move to the next main node
                }
            }
        }

        fclose(fptr); // Close the file after writing is complete
    }
    else
    {
        // Return FAILURE if the file name does not have a ".txt" extension
        return FAILURE;
    }

    return SUCCESS; // Return SUCCESS if the database was successfully saved
}
