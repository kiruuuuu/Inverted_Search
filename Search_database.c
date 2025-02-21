#include "dll.h"

// Function to search for a specific word in the database
void search_database(Main **arr, char str[])
{
    system("clear");  // Clear the terminal screen for a clean display

    int index;  // Variable to store the index corresponding to the first character of the word

    // Determine the index based on the first character of the word
    if(str[0] >= 'A' && str[0] <= 'Z')  // If the first character is an uppercase letter
    {
        index = str[0] - 'A';  
    }
    else if(str[0] >= 'a' && str[0] <= 'z')  // If the first character is a lowercase letter
    {
        index = str[0] - 'a';  
    }
    else if(str[0] >= '0' && str[0] <= '9')  // If the first character is a digit
    {
        index = 26;  // Assign index 26 for all numbers
    }
    else  // For special characters or any other case
    {
        index = 27;  // Assign index 27 for special characters
    }

    Main *temp = arr[index];  // Get the head of the linked list at the determined index
    int flag = 0;  // Flag to indicate whether the word was found in the database

    // Traverse the linked list at the specified index
    while(temp != NULL)
    {
        // Check if the word matches the current node's word
        if(strcmp(str, temp->word) == 0)
        {
            flag = 1;  // Set flag to 1 to indicate that the word was found
            printf(GREEN"%s is present at index %d\n"RESET, temp->word, index);  // Print the word and its index
            printf(GREEN"%s is present in %d files\n"RESET, temp->word, temp->f_count);  // Print the word and the number of files it appears in

            // Traverse the sublist of files where the word is found
            Sub *temp2 = temp->s_link;
            while(temp2 != NULL)
            {
                // Print each file name and the count of occurrences in that file
                printf(GREEN"%s is present in %s : %d times\n"RESET, temp->word, temp2->f_name, temp2->w_count);
                temp2 = temp2->link;  // Move to the next file in the sublist
            }
        }

        temp = temp->m_link;  // Move to the next word in the linked list
    }

    // If the word was not found in the database, print an error message
    if(flag == 0)
        printf(RED"Data not found\n"RESET);
}
